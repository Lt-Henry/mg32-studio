#ifndef MG32_NEWPROJECTDIALOG
#define MG32_NEWPROJECTDIALOG

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace mg32
{
    class NewProjectDialog: public QDialog
    {
        public:

        explicit NewProjectDialog(QWidget* parent = nullptr);
        ~NewProjectDialog();

        bool isAvailable();

        private:

        QLineEdit* m_txtName;
        QLineEdit* m_txtPath;
        QPushButton* m_btnCreate;
    };
}

#endif
