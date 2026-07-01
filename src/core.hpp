#ifndef MG32_CORE
#define MG32_CORE

#include <QString>
#include <QProcess>
#include <QObject>

namespace mg32
{
    class Core: public QObject
    {
        Q_OBJECT
        public:

        static Core* get();

        void setProject(QString path);

        void run();

        private:
        Core(QObject* parent = nullptr);

        static Core* m_core;

        QString m_path;
        QProcess m_process;

        public slots:

        void openProject(const QString& file);
    };
}

#endif
