#include "newprojectdialog.hpp"
#include "core.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDir>

using namespace mg32;
using namespace std;

NewProjectDialog::NewProjectDialog(QWidget* parent)
{
    setModal(true);
    setWindowTitle("New Project");
    setFixedSize(400, 300);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);

    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    QHBoxLayout* row = new QHBoxLayout();
    row->addWidget(new QLabel("Name"));
    m_txtName = new QLineEdit();
    m_txtName->setText("NewProject");
    connect(m_txtName, &QLineEdit::textEdited, [this]()
    {

    });

    row->addWidget(m_txtName);

    layout->addLayout(row);

    row = new QHBoxLayout();
    row->addWidget(new QLabel("Path"));
    m_txtPath = new QLineEdit();
    m_txtPath->setText(QDir::homePath());
    connect(m_txtPath, &QLineEdit::textEdited, [this]()
    {

    });

    row->addWidget(m_txtPath);
    QPushButton* btn = new QPushButton(this);
    btn->setIcon(QIcon::fromTheme("folder"));
    connect(btn, &QPushButton::clicked, [this]()
    {
        QString directory = QFileDialog::getExistingDirectory(
            this,
            "Select Directory",
            m_txtPath->text(),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

        if (!directory.isEmpty()) {
            m_txtPath->setText(directory);
        }
    });
    row->addWidget(btn);

    layout->addLayout(row);
    layout->addStretch();

    row = new QHBoxLayout();
    row->addStretch();
    m_btnCreate = new QPushButton("Create");
    m_btnCreate->setEnabled(false);
    connect(m_btnCreate, &QPushButton::clicked, [this]()
    {
        //Core::get()->createProject();
    });
    row->addWidget(m_btnCreate);

    btn = new QPushButton("Cancel");
    connect(btn, &QPushButton::clicked, [this]()
    {
        done(0);
    });
    row->addWidget(btn);

    layout->addLayout(row);

}

NewProjectDialog::~NewProjectDialog()
{

}

bool NewProjectDialog::isAvailable()
{
    return false;
}
