#ifndef MG32_CORE
#define MG32_CORE

#include <QString>
#include <QProcess>
#include <QObject>
#include <QMap>

namespace mg32
{
    class Core: public QObject
    {
        Q_OBJECT
        public:

        static Core* get();

        void setProject(QString path);
        void createProject(QString path);

        void run();

        void acquire(QObject* who);
        void release(QObject* who);
        bool ready();

        private:
        Core(QObject* parent = nullptr);

        static Core* m_core;

        QString m_path;
        QProcess m_process;
        QMap<QObject*,bool> m_ready;

        signals:

        void projectLoaded(const QString& path);
        void saveRequest();

        public slots:

        void openProject(const QString& path);
    };
}

#endif
