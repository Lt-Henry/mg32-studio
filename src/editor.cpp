#include "editor.hpp"

using namespace mg32;
using namespace std;

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    setFont(QFont("Hack", 12));
    QTextOption option =  document()->defaultTextOption();
    option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
    document()->setDefaultTextOption(option);

}

Editor::~ Editor()
{

}
