#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "browserwindow.h"
#include "jscontext.h"
#include <QWebChannel>
#include "commonheader.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog() override;
    void readParseTemplate();

    BrowserWindow *GetBrowserWindow();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void slotShowSelectText(QString sSelectText);

    void on_rbCollect_clicked();

    void on_rbBrowse_clicked();

    void on_cbParseTemplate_activated(const QString &arg1);

private:
    void readJavascript();

private:
    BrowserWindow           *m_browserWindow;

    JsContext               *m_jsContext;
    QWebChannel             *m_webChannel;
    QString                 m_sJavascript;

    RUNTYPE                 m_nRunType;

    QMap<QString, QString>  m_mapParseTemplate;

    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
