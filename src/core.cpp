#include "core.hpp"

#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

using namespace mg32;
using namespace std;

mg32::Core* mg32::Core::m_core = nullptr;

Core::Core(QObject* parent):QObject(parent)
{

}

Core* mg32::Core::get()
{
    if (mg32::Core::m_core == nullptr) {
        mg32::Core::m_core = new Core();
    }

    return mg32::Core::m_core;
}

void Core::setProject(QString path)
{
    m_path = path;
}

void Core::createProject(QString path,QString name)
{
    QDir base(path);
    base.mkdir(name);

    base = QDir(path+"/"+name);

    QFile file(base.filePath("main.lua"));

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        QTextStream stream(&file);
        stream << "-- MG32 Studio:" << name<<"\n\n"
        <<"function  main()\n\n\twhile true do\n\tframe()\n\tend\nend\n"<<
        Qt::endl;
        file.close();

    } else {
        qDebug() << "cannot crate main.lua";
        return;
    }

    openProject(path+"/"+name+"/main.lua");
}

void Core::run()
{
    emit saveRequest();

    qDebug()<<"ready:"<<ready();

    if (m_process.state() == QProcess::NotRunning) {
        m_process.setWorkingDirectory(QFileInfo(m_path).path());
        QStringList args;
        args << m_path;
        m_process.start("mg32",args);
    }
}

void Core::acquire(QObject* who)
{
    m_ready[who] = false;
}

void Core::release(QObject* who)
{
    m_ready[who] = true;
}

bool Core::ready()
{
    bool value = true;

    for (auto it = m_ready.begin(); it != m_ready.end(); it++) {
        value = value and it.value();
    }

    return value;
}

void Core::openProject(const QString& path)
{
    qDebug()<<"opening "<<path;
    setProject(path);

    emit projectLoaded(path);
}
