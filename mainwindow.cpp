#include <QTimer>
#include <QRandomGenerator>
#include <QPushButton>
#include <QPalette>
#include <QBoxLayout>

#include "mainwindow.h"

// === GAME SETTINGS ===
constexpr int deltaY = 3;
constexpr int buttonSizeX = 20;
constexpr int buttonSizeY = 20;
constexpr int timerMovePbMax = 250;
constexpr int timerMovePbMin = 120;
constexpr int timerInitPbMax = 1000;
constexpr int timerInitPbMin = 100;
constexpr int spawnPbHeight = 100;
constexpr int multiplySpeedThenUnderMouse = 2;
// =====================

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    resize(300, 600);

    auto tm = new QTimer(this);

    connect(tm, &QTimer::timeout,
        [this, tm]()
        {

            auto pb = new QPushButton(this);
            auto tmButton = new QTimer(pb);

            pb->setGeometry(
                QRandomGenerator::global()->bounded(0, width()),
                spawnPbHeight,
                buttonSizeX,
                buttonSizeY
            );
            pb->show();
            connect(tmButton, &QTimer::timeout,
                [pb, this]()
                {
                    if (pb->y() > height())
                    {
                        QPalette pal = QPalette();
                        pal.setColor(QPalette::Window, Qt::red);

                        setAutoFillBackground(true);
                        setPalette(pal);
                        setWindowTitle("You Loose!");
                    }
                    pb->setGeometry(
                        pb->x(),
                        pb->y() + deltaY * (pb->underMouse() ? multiplySpeedThenUnderMouse : 1),
                        pb->width(),
                        pb->height()
                    );
                }
            );
            connect(pb, &QPushButton::clicked, pb, &QPushButton::deleteLater);

            tmButton->start(QRandomGenerator::global()->bounded(timerMovePbMin, timerMovePbMax));
            tm->setInterval(QRandomGenerator::global()->bounded(timerInitPbMin, timerInitPbMax));
        }
    );
    tm->start();

}

MainWindow::~MainWindow()
{
}
