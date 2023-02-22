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
    m_window = browser.createWindow();
    QHBoxLayout *lyt = new QHBoxLayout;
    lyt->addWidget(m_window);
    ui->widget->setLayout(lyt);
    m_window->tabWidget()->setUrl(url);

    connect(m_window->tabWidget()->currentWebView(), &WebView::sigShowSelectText, this, &MainDialog::slotShowSelectText);
}

MainDialog::~MainDialog()
{
    delete ui;
    m_window->close();
    delete m_window;
}

void MainDialog::on_pushButton_clicked()
{
    QFile file1("../simplebrowser/static/selectelement.js");
    if (file1.open(QIODevice::ReadOnly))
    {
        QString content = file1.readAll();
        file1.close();
        m_window->tabWidget()->currentWebView()->injectJs(content);
    }
}

void MainDialog::slotShowSelectText(QString sSelectText)
{
    ui->textEdit->setText(sSelectText);
}
