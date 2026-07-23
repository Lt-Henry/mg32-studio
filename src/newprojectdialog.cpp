#include "newprojectdialog.hpp"

using namespace mg32;
using namespace std;

NewProjectDialog::NewProjectDialog(QWidget* parent)
{
    setModal(true);
    setWindowTitle("New Project");
    setFixedSize(400, 300);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
}

NewProjectDialog::~NewProjectDialog()
{

}
