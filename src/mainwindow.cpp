#include "mainwindow.hpp"
#include "core.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>

using namespace mg32;
using namespace std;

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    QHBoxLayout* toolbar = new QHBoxLayout();

    QPushButton* btn;

    btn = new QPushButton();
    btn->setIcon(QIcon::fromTheme("media-playback-playing"));
    connect(btn, &QPushButton::clicked, []()
    {
        qDebug()<<"clicked";
        Core::get()->run();
    });

    toolbar->addWidget(btn);
    toolbar->addStretch();

    setWindowTitle("MG32");
    resize(800, 600);

    m_editor = new Editor(this);
    layout->addLayout(toolbar);
    layout->addWidget(m_editor);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
