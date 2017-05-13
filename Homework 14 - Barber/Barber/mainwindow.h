#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QMouseEvent>
#include <QSpinBox>
#include <QTextBrowser>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QString>
#include <QThread>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newBarberShop();
    void save();

private:
    int count;
    Ui::MainWindow *ui;
    QLabel *labelChairs, *labelTime, *labelCustomers;
    QSpinBox *spinChairs, *spinTime, *spinCustomers;
    QComboBox *comboBoxModel;    
};

#endif // MAINWINDOW_H
