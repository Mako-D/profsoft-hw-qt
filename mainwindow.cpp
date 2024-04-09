#include <QTimer>
#include <QRandomGenerator>
#include <QPushButton>
#include <QPalette>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 600);

    // If you use Qt5, may you need to change next line to "ui->setupUi(this);"
    ui.setupUi(this);

    auto tm = new QTimer(this);
    tm->setSingleShot(true);

    connect(tm, &QTimer::timeout,
        [this, tm]()
        {
            // === GAME SETTINGS ===
            int deltaY = 3;
            int buttonSizeX = 20;
            int buttonSizeY = 20;
            int timerMovePbMax = 250;
            int timerMovePbMin = 120;
            int timerInitPbMax = 1000;
            int timerInitPbMin = 100;
            int spawnPbHeight = 100;
            int increaseSpeedThenUnderMouse = 2;
            // =====================

            auto pb = new QPushButton(this);
            auto tmButton = new QTimer(pb);

            pb->setGeometry(
                QRandomGenerator::global()->bounded(0, this->height()),
                spawnPbHeight,
                buttonSizeX,
                buttonSizeY
            );
            pb->show();
            connect(tmButton, &QTimer::timeout, 
                [pb, deltaY, increaseSpeedThenUnderMouse, this]() 
                {    
                    if (pb->y() > this->height())
                    {
                        QPalette pal = QPalette();
                        pal.setColor(QPalette::Window, Qt::red);

                        this->setAutoFillBackground(true);
                        this->setPalette(pal);
                        this->setWindowTitle("You Loose!");
                    }
                    pb->setGeometry(
                        pb->x(), 
                        pb->y() + deltaY * (pb->underMouse() ? increaseSpeedThenUnderMouse : 1),
                        pb->width(), 
                        pb->height()
                    );  
                }
            );
            connect(pb, &QPushButton::clicked,
                [pb]() {   pb->deleteLater();  }
            );

            tmButton->start(timerMovePbMin + QRandomGenerator::global()->bounded(timerMovePbMax - timerMovePbMin));

            tm->setInterval(QRandomGenerator::global()->bounded(timerInitPbMin, timerInitPbMax));
            tm->start();
        }
    );
    tm->start();
}

MainWindow::~MainWindow()
{
}
