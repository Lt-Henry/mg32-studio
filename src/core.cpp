#include "core.hpp"

#include <QStringList>
#include <QFileInfo>

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

void Core::run()
{
    if (m_process.state() == QProcess::NotRunning) {
        m_process.setWorkingDirectory(QFileInfo(m_path).path());
        QStringList args;
        args << m_path;
        m_process.start("mg32",args);
    }
}
