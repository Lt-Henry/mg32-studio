#include "editor.hpp"
#include "core.hpp"

#include <QMimeData>
#include <QFile>
#include <QDebug>

using namespace mg32;
using namespace std;

LuaHighlighter::LuaHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
    m_keywords << "function" << "end"<<"if"<<"else"<<"elseif"<<"then"<<"for"<<"while"<<"do"<<"local"<<"or"<<"and"<<"not";
    m_ops<<"="<<"\\+"<<"\\-"<<"\\+"<<"\\/"<<"=="<<"<"<<">";

    m_keywordFormat.setForeground(QColor("#5b6ee1"));
    m_keywordFormat.setFontWeight(QFont::Bold);

    m_opFormat.setForeground(QColor("#5b6ee1"));
    m_opFormat.setFontWeight(QFont::Bold);

    m_spaceFormat.setForeground(QColor("#9badb7"));
    m_stringFormat.setForeground(QColor("#37946e"));
    m_numberFormat.setForeground(QColor("#d77bba"));

    m_constFormat.setForeground(QColor("#d95763"));
    m_constFormat.setFontWeight(QFont::Bold);

    m_commentFormat.setForeground(QColor("#9badb7"));

    m_rules << qMakePair(QRegularExpression("\\b(" + m_keywords.join("|") + ")\\b"), m_keywordFormat)
                << qMakePair(QRegularExpression("(" + m_ops.join("|") + ")"), m_opFormat)
                << qMakePair(QRegularExpression("\".*\""), m_stringFormat)
                << qMakePair(QRegularExpression("\'.*\'"), m_stringFormat)
                << qMakePair(QRegularExpression("\\b([0-9]+)\\b"), m_numberFormat)
                << qMakePair(QRegularExpression("\\b(0x[0-9a-fA-F]+)\\b"), m_numberFormat)
                << qMakePair(QRegularExpression("\\b(true|false)\\b"), m_numberFormat)
                << qMakePair(QRegularExpression("\\b([A-Z_][A-Z0-9_]*)\\b"), m_constFormat)
                << qMakePair(QRegularExpression("\\s"), m_spaceFormat)
                << qMakePair(QRegularExpression("(--)[^\n]*"), m_commentFormat);
}

LuaHighlighter::~LuaHighlighter()
{

}

void LuaHighlighter::highlightBlock(const QString &text)
{
    for (const auto &rule : m_rules) {
        QRegularExpression expression(rule.first);
        QRegularExpressionMatchIterator iterator = expression.globalMatch(text);
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.second);
        }
    }
}

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    setFont(QFont("Hack", 12));

    QTextCharFormat defaultFormat;
    defaultFormat.setForeground(QColor("#696a6a"));
    setCurrentCharFormat(defaultFormat);

    QTextOption option =  document()->defaultTextOption();
    option.setFlags(option.flags() | QTextOption::ShowTabsAndSpaces);
    document()->setDefaultTextOption(option);

    m_highlighter = new LuaHighlighter(document());

}

Editor::~ Editor()
{

}

void Editor::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls()) {
        QUrl source = event->mimeData()->urls()[0];

        if (source.fileName() == "main.lua") {
            qInfo()<<"loading..."<<source.path();

            QFile file(source.path());

            if (file.open(QFile::ReadOnly)) {
                setPlainText(file.readAll());
                Core::get()->setProject(source.path());
            }

            file.close();
        }
    }
}
