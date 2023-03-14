#include "maindialog.h"
#include "ui_maindialog.h"
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include "browser.h"
#include <QWebEngineView>
#include "webview.h"
#include "tabwidget.h"
#include <QFile>

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("https://www.baidu.com"));
}

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();

    QUrl url = commandLineUrlArgument();

    Browser browser;
    m_browserWindow = browser.createWindow();
    QHBoxLayout *lyt = new QHBoxLayout;
    lyt->addWidget(m_browserWindow);
    ui->widget->setLayout(lyt);
    m_browserWindow->tabWidget()->setUrl(url);

    readJavascript();

    connect(m_browserWindow->tabWidget()->currentWebView(), &WebView::sigShowSelectText, this, &MainDialog::slotShowSelectText);
}

MainDialog::~MainDialog()
{
    delete ui;
    m_browserWindow->close();
    delete m_browserWindow;
}

BrowserWindow *MainDialog::GetBrowserWindow()
{
    return m_browserWindow;
}

void MainDialog::closeEvent(QCloseEvent *event)
{
    m_browserWindow->close();
}

void MainDialog::readJavascript()
{
    QFile file("../WebCollector/static/qwebchannel.js");
    if (file.open(QIODevice::ReadOnly))
    {
        m_sJavascript = file.readAll();
        file.close();
    }

    file.setFileName("../WebCollector/static/selectelement.js");
    if (file.open(QIODevice::ReadOnly))
    {
        m_sJavascript += file.readAll();
        file.close();
    }

    file.setFileName("../WebCollector/static/msgutils.js");
    if (file.open(QIODevice::ReadOnly))
    {
        m_sJavascript += file.readAll();
        file.close();
    }
}

void MainDialog::slotShowSelectText(QString sSelectText)
{
    ui->textEdit->setText(sSelectText);
}

void MainDialog::on_rbCollect_clicked()
{
    m_jsContext = new JsContext(this);
    m_webChannel = new QWebChannel(this);
    m_webChannel->registerObject("context", m_jsContext);
    m_browserWindow->tabWidget()->currentWebView()->page()->setWebChannel(m_webChannel);
    connect(m_jsContext, &JsContext::recvdMsg, this, &MainDialog::slotShowSelectText);

    m_browserWindow->tabWidget()->currentWebView()->page()->runJavaScript(m_sJavascript);
    m_nRunType = RUNTYPE::COLLECT;
}

void MainDialog::on_rbBrowse_clicked()
{
    delete m_jsContext;
    delete m_webChannel;

    QString sCurUrl = m_browserWindow->tabWidget()->currentWebView()->page()->url().toString();
    m_browserWindow->tabWidget()->currentWebView()->page()->load(sCurUrl);
    m_nRunType = RUNTYPE::BROWSE;
}
