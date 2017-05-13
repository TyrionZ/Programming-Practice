#ifndef BARBERSHOP_H
#define BARBERSHOP_H

#include <QThread>
#include <QObject>
#include <QMutex>
#include <QWidget>
#include <QTextBrowser>
#include <QWaitCondition>
#include <QTime>
#include <QLabel>
#include <QMessageBox>
#include <QMdiSubWindow>

namespace Ui {
class BarberShop;
}

class BarberShop : public QWidget {
    Q_OBJECT
public:
    explicit BarberShop(int _chairsNumber = 0, int _customersNumber = 0, int _haircutTime= 0, bool _manual = false, QWidget *parent = 0);
    ~BarberShop();
    void startProcess();

    QMdiSubWindow *window;
    Ui::BarberShop *ui;
    int chairsNumber, customersNumber, haircutTime, count;
    bool manual;
    QMutex chairsMutex, barberMutex, shopMutex;
    QVector<int> chairs;
    QTextBrowser *browser;
    QWaitCondition haveCustomer;

public slots:
    void pause();
    void addCustomer(int waitTime = 0);
    void finished();
};

class Barber : public QObject {
    Q_OBJECT
private:
    BarberShop *shop;
public:
    Barber(BarberShop *s = NULL): shop(s) {}
public slots:
    void process() {
        while (true) {
            shop->chairsMutex.lock();
            if (shop->chairs.empty()) {
                shop->shopMutex.lock();
                if (shop->customersNumber <= shop->count) {
                    shop->browser->insertPlainText(tr("理发店打烊\n"));
                    shop->shopMutex.unlock();
                    return ;
                }
                shop->browser->insertPlainText(tr("理发师睡觉\n"));
                shop->window->show();
                shop->shopMutex.unlock();
                shop->haveCustomer.wait(&shop->chairsMutex);
                shop->shopMutex.lock();
                shop->browser->insertPlainText(tr("理发师醒来\n"));
                shop->window->show();
                shop->shopMutex.unlock();
            }
            int currentCustomer = shop->chairs.back();
            shop->chairs.pop_back();
            shop->chairsMutex.unlock();
            shop->shopMutex.lock();
            shop->browser->insertPlainText(tr("顾客") + QString::number(currentCustomer, 10) + tr("正在被理发\n"));
            shop->window->show();
            shop->shopMutex.unlock();
            QThread::sleep(shop->haircutTime);
            shop->barberMutex.lock();
            shop->barberMutex.unlock();
            shop->shopMutex.lock();
            shop->browser->insertPlainText(tr("顾客") + QString::number(currentCustomer, 10) + tr("理完发走了\n"));
            shop->window->show();
            shop->shopMutex.unlock();
        }
    }
signals:
    void operate(const QString &);
};


class Customer : public QObject {
    Q_OBJECT
private:
    int waitTime, number;
    BarberShop *shop;
public:
    Customer(BarberShop *s = NULL, int n = 0, int w = 0): number(n), waitTime(w), shop(s) {}
public slots:
    void process() {
        shop->shopMutex.lock();
        shop->browser->insertPlainText(tr("顾客") + QString::number(number, 10) + tr("进门\n"));
        shop->window->show();

        if (shop->chairs.size() < shop->chairsNumber) {
            shop->browser->insertPlainText(tr("顾客") + QString::number(number, 10) + tr("占据一把椅子\n"));
            shop->window->show();
            shop->chairsMutex.lock();
            shop->chairs.push_back(number);
            shop->chairsMutex.unlock();
            shop->haveCustomer.wakeAll();
        }
        else {
            shop->browser->insertPlainText(tr("没有椅子，顾客") + QString::number(number, 10) + tr("走了\n"));
            shop->window->show();
        }

        shop->shopMutex.unlock();
    }

signals:
    void operate(const QString &);
};

#endif // BARBERSHOP_H
