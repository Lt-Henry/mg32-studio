#include "mainwindow.hpp"
#include "newprojectdialog.hpp"
#include "core.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QSplitter>
#include <QFileDialog>
#include <QRegularExpression>
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
    connect(btn, &QPushButton::clicked, [this]()
    {
        qDebug()<<"clicked";
        m_txtOutput->clear();
        m_txtError->clear();
        Core::get()->run();
    });
    toolbar->addWidget(btn);

    toolbar->addStretch();

    setWindowTitle("MG32");
    resize(800, 600);

    m_editor = new Editor(this);
    layout->addLayout(toolbar);

    QSplitter* splitter = new QSplitter(Qt::Vertical, centralWidget);
    splitter->addWidget(m_editor);
    layout->addWidget(splitter);

    m_editor->setFocus();
    m_editor->setFocusPolicy(Qt::StrongFocus);
    m_editor->ensureCursorVisible();

    QTabWidget* tabs = new QTabWidget();
    splitter->addWidget(tabs);
    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 1);
    splitter->setChildrenCollapsible(false);

    m_txtOutput = new QPlainTextEdit();
    tabs->addTab(m_txtOutput, "Output");

    m_txtError = new QPlainTextEdit();
    tabs->addTab(m_txtError, "Error");

    connect(Core::get(),&Core::outputAvailable,[this](const QString & line)
    {
        m_txtOutput->appendPlainText(line);
    });

    connect(Core::get(),&Core::errorAvailable,[this](const QString & line)
    {
        m_txtError->appendPlainText(line);

        // Errors have the format TEXT:PATH:LINE:DETAILS
        QRegularExpression expression("^(.*):([^:]*):(\\d+):(.*)$");
        QRegularExpressionMatch match = expression.match(line);

        if (match.hasMatch()) {
            bool ok = false;
            int lineNumber = match.captured(3).toInt(&ok);

            if (ok and lineNumber > 0) {
                m_editor->highlightLine(lineNumber);
            }
        }
    });

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
