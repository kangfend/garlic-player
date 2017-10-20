#include "debug_infos.h"
#include "ui_debug_infos.h"

DebugInfos::DebugInfos(LibFacade *lib_facade, QWidget *parent) :  QDialog(parent), ui(new Ui::DebugInfos)
{
    MyLibFacade = lib_facade;
    ui->setupUi(this);
    timer_id = startTimer(500);
    setWindowOpacity(0.8);
}


DebugInfos::~DebugInfos()
{
    delete ui;
    killTimer(timer_id);
}

void DebugInfos::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    outputResourcesUsage();
}

void DebugInfos::outputResourcesUsage()
{
    MyMemoryInfos.refresh();

    qint64  total_mem = MyMemoryInfos.getTotal();
    qint64  free_mem = MyMemoryInfos.getFree();
    double d_total = (double)total_mem / (double)1048576;
    double d_free = (double)free_mem / (double)1048576;
    ui->TotalSystemMemory->setText(QString("Total Memory System:: %1" ).arg(d_total, 0, 'f', 2) + " MiB");
    ui->FreeSystemMemory->setText(QString("Free Memory System:: %1" ).arg(d_free, 0, 'f', 2) + " MiB");

    qint64  current_rss = MyMemoryInfos.getRSS();
    if (current_rss > max_memory_used)
        max_memory_used = current_rss;
    double d_current = (double)current_rss / (double)1048576;
    double d_max = (double)max_memory_used / (double)1048576;
    ui->OutputMemoryUse->setText(QString("App Memory use: <b>%1" ).arg(d_current, 0, 'f', 2) + " MiB</b>");
    ui->MaxMemoryUsed->setText(QString("Max Memory App used: %1" ).arg(d_max, 0, 'f', 2) + " MiB");

    qint64  current_threads = MyGeneralInfos.countThreads();
    if (current_threads > max_threads_used)
        max_threads_used = current_threads;
    ui->ThreadsNumber->setText("Threads: " + QString::number(current_threads));
    ui->MaxThreadsNumber->setText("Max Threads: " + QString::number(max_threads_used));

    ui->CurrentFileInUse->setText("playing: "+MyLibFacade->getCurrentMedia()->getLoadablePath());
    ui->PlaylistTitle->setText(MyLibFacade->getHead()->getTitle());

}
