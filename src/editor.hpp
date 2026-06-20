
#ifndef MG32_EDITOR
#define MG32_EDITOR

#include <QStringList>
#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QFont>
#include <QColor>
#include <QList>
#include <QPair>

#include <iostream>

namespace mg32
{

    class LuaHighlighter : public QSyntaxHighlighter
    {
        public:

        LuaHighlighter(QTextDocument* parent);
        virtual ~LuaHighlighter();

        protected:

        void highlightBlock(const QString& text) override;

        private:

        QStringList m_keywords;
        QStringList m_ops;

        QList<QPair<QRegularExpression, QTextCharFormat>> m_rules;

        QTextCharFormat m_keywordFormat;
        QTextCharFormat m_opFormat;
        QTextCharFormat m_stringFormat;
        QTextCharFormat m_numberFormat;
        QTextCharFormat m_constFormat;
        QTextCharFormat m_commentFormat;
        QTextCharFormat m_spaceFormat;

    };

    class Editor: public QPlainTextEdit
    {
        public:

        Editor(QWidget *parent = nullptr);
        virtual ~Editor();

        void dropEvent(QDropEvent *event) override;

        private:

        LuaHighlighter* m_highlighter;
    };
}

#endif
