#include "barbershop.h"
#include "ui_barbershop.h"
#include <QThread>

BarberShop::BarberShop(int _chairsNumber, int _customersNumber, int _haircutTime, bool _manual, QWidget *parent) :
    QWidget(parent),
    chairsNumber(_chairsNumber),
    customersNumber(_customersNumber),
    haircutTime(_haircutTime),
    manual(_manual),
    ui(new Ui::BarberShop)
{
    count = 0;
    ui->setupUi(this);
    ui->status->setText("");
    browser = ui->textBrowser;

    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(addCustomer()));
    connect(ui->pauseButton, SIGNAL(clicked(bool)), this, SLOT(pause()));
}

void BarberShop::pause() {
    if (barberMutex.tryLock())
        ui->pauseButton->setText(tr("continue"));
    else {
        ui->pauseButton->setText(tr("pause"));
        barberMutex.unlock();
    }
}

void BarberShop::addCustomer(int waitTime) {
    QThread::sleep(waitTime);
    ++count;
    if (count > customersNumber) {
        QMessageBox::critical(NULL, "critical", "顾客数量达到上限！", QMessageBox::Yes, QMessageBox::Yes);
        return ;
    }
    QThread *customerThread = new QThread;
    Customer *customer = new Customer(this, count, waitTime);
    customer->moveToThread(customerThread);
    connect(customerThread, &QThread::finished, customer, &QThread::deleteLater);
    customer->connect(customerThread ,SIGNAL(started()), SLOT(process()));
    customerThread->start();
}

void BarberShop::finished() {
    ui->status->setText("<h1><font color=red size=\"12px\">理发师下班，理发店打烊。<\font><\h1>");
}

void BarberShop::startProcess() {
    qsrand(QTime::currentTime().second());

    QThread *barberThread = new QThread;
    Barber *barber = new Barber(this);
    barber->moveToThread(barberThread);
    connect(barberThread, &QThread::finished, barber, &QThread::deleteLater);
    connect(barberThread, &QThread::finished, this, &BarberShop::finished);
    barber->connect(barberThread, SIGNAL(started()), SLOT(process()));
    barberThread->start();

    if (!manual) {
        ui->addButton->setEnabled(false);
        int t = haircutTime ? ((haircutTime + 1) >> 1) : 1, restTime = t * customersNumber, sumWaitTime = 0;
        int c = customersNumber;
        while (c--) {
            int waitTime = qrand() % restTime;
            restTime -= waitTime;
            sumWaitTime += waitTime;
            addCustomer(sumWaitTime);
        }
    }
    else ui->addButton->setEnabled(true);
}

BarberShop::~BarberShop() {
    delete ui;
}

