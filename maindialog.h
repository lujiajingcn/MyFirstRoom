#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "browserwindow.h"
#include "jscontext.h"
#include <QWebChannel>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = nullptr);
    ~MainDialog();


    BrowserWindow *m_window;
private slots:
    void on_pushButton_clicked();
    void slotShowSelectText(QString sSelectText);

private:
    void readJavascript();

private:

    JsContext       *m_jsContext;
    QWebChannel     *m_webChannel;
    QString         m_sJavascript;

    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
