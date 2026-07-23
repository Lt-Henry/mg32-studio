#ifndef MG32_NEWPROJECTDIALOG
#define MG32_NEWPROJECTDIALOG

#include <QDialog>

namespace mg32
{
    class NewProjectDialog: public QDialog
    {
        public:

        explicit NewProjectDialog(QWidget* parent = nullptr);
        ~NewProjectDialog();
    };
}

#endif
