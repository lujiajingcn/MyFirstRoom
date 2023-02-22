#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "browserwindow.h"
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
    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
