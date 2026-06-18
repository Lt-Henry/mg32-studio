#include "mainwindow.hpp"

#include <QVBoxLayout>

using namespace mg32;
using namespace std;

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    setWindowTitle("MG32");
    resize(800, 600);

    m_editor = new Editor(this);
    layout->addWidget(m_editor);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
