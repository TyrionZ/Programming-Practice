#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "barbershop.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    count = 0;
    ui->setupUi(this);
    setWindowTitle("Barber Shop");
    // tool bar
    comboBoxModel = new QComboBox(this);
    comboBoxModel->addItem("-select model-");
    comboBoxModel->addItem("Auto");
    comboBoxModel->addItem("Manual");
    ui->toolBar->addWidget(comboBoxModel);
    labelChairs = new QLabel("Number of Chairs", this);
    ui->toolBar->addWidget(labelChairs);
    spinChairs = new QSpinBox(this);
    spinChairs->setMinimum(0);
    spinChairs->setValue(1);
    ui->toolBar->addWidget(spinChairs);
    labelCustomers = new QLabel("Number of Customers", this);
    ui->toolBar->addWidget(labelCustomers);
    spinCustomers = new QSpinBox(this);
    spinCustomers->setMinimum(0);
    spinCustomers->setValue(5);
    ui->toolBar->addWidget(spinCustomers);
    labelTime = new QLabel("Haircut Time", this);
    ui->toolBar->addWidget(labelTime);
    spinTime = new QSpinBox(this);
    spinTime->setMinimum(0);
    spinTime->setSuffix("seconds");
    spinTime->setValue(1);
    spinTime->setMaximum(10);
    ui->toolBar->addWidget(spinTime);

    // connect slot
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(newBarberShop()));
    connect(ui->actionNew_1, SIGNAL(triggered(bool)), this, SLOT(newBarberShop()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save));
    // debug

}

void MainWindow::newBarberShop() {
    int chairs = spinChairs->value(), customers = spinCustomers->value(), time = spinTime->value();
    QString mode = comboBoxModel->currentText();
    bool manual;
    if (mode == "Manual")
        manual = true;
    else if (mode == "Auto")
        manual = false;
    else {
        QMessageBox::critical(this, "critical", "请选择模式！", QMessageBox::Yes, QMessageBox::Yes);
        return ;
    }
    BarberShop *point = new BarberShop(chairs, customers, time, manual);
    QMdiSubWindow *window = ui->mdiArea->addSubWindow(point);
    point->window = window;
    window->setWindowTitle(tr("Barber Shop ") + QString::number(count++, 10));
    window->showMaximized();
    point->startProcess();
}

void MainWindow::save() {
    QString filename = QFileDialog::getSaveFileName(this, "Save", "", "*.txt"); //选择路径
    if(filename.isEmpty())
        return;
    else{
        //我也不知道save是要干嘛……文档里没有，示例程序也不知道在干什么
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
