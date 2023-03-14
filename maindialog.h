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

    BrowserWindow *GetBrowserWindow();
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void slotShowSelectText(QString sSelectText);

    void on_rbCollect_clicked();

    void on_rbBrowse_clicked();

private:
    void readJavascript();

private:
    BrowserWindow   *m_browserWindow;

    JsContext       *m_jsContext;
    QWebChannel     *m_webChannel;
    QString         m_sJavascript;

    RUNTYPE         m_nRunType;

    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
