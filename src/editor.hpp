
#ifndef MG32_EDITOR
#define MG32_EDITOR

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QFont>
#include <QColor>

#include <iostream>

namespace mg32
{
    class Editor: public QPlainTextEdit
    {
        public:

        Editor(QWidget *parent = nullptr);
        virtual ~Editor();
    };
}

#endif
