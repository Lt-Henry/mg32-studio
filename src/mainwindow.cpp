#include "mainwindow.hpp"
#include "newprojectdialog.hpp"
#include "core.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QFileDialog>
#include <QIcon>

using namespace mg32;
using namespace std;

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    QHBoxLayout* toolbar = new QHBoxLayout();

    QPushButton* btn;

    btn = new QPushButton(this);
    btn->setIcon(QIcon::fromTheme("document-new"));
    connect(btn, &QPushButton::clicked, [this]()
    {
        NewProjectDialog dialog(this);

        dialog.exec();
    });
    toolbar->addWidget(btn);

    btn = new QPushButton(this);
    btn->setIcon(QIcon::fromTheme("document-open"));
    connect(btn, &QPushButton::clicked, [this]()
    {
        QStringList filters({"main.lua"});
        QFileDialog dialog(this);
        dialog.setNameFilters(filters);
        connect(&dialog,&QFileDialog::fileSelected,Core::get(),&Core::openProject);
        dialog.exec();

    });
    toolbar->addWidget(btn);

    btn = new QPushButton(this);
    m_buttonSave = btn;
    //btn->setEnabled(false);
    btn->setIcon(QIcon::fromTheme("document-save"));
    connect(btn, &QPushButton::clicked, []()
    {
        emit Core::get()->saveRequest();
    });
    toolbar->addWidget(btn);

    toolbar->addSpacing(32);

    btn = new QPushButton(this);
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
    m_editor->setFocus();
    m_editor->setFocusPolicy(Qt::StrongFocus);
    m_editor->ensureCursorVisible();

    QTabWidget* tabs = new QTabWidget();
    layout->addWidget(tabs);

    m_txtOutput = new QPlainTextEdit();
    tabs->addTab(m_txtOutput, "Output");

    m_txtError = new QPlainTextEdit();
    tabs->addTab(m_txtError, "Error");

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
