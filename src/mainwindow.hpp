
#ifndef MG32_MAINWINDOW
#define MG32_MAINWINDOW

#include "editor.hpp"

#include <QMainWindow>

namespace mg32
{
    class MainWindow: public QMainWindow
    {
        public:

        MainWindow(QWidget* parent = nullptr);
        virtual ~MainWindow();

        private:

        Editor* m_editor;
    };
}

#endif
