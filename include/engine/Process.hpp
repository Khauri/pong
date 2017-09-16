#ifndef PROC_H
#define PROC_H

#include <list>
#include <memory>

class Process
{
    public:
        enum states {UNINIT, RUNNING, PAUSED, SUCCESS, FAILED, ABORTED};
        int state;
        Process* child;
        virtual init();
        virtual update(int dt);
        virtual onSuccess();
        virtual onFailure();
        virtual onAbort();

        void pause();
        void resume();
        bool isDead();
};

class ProcessManager
{
    private:
        std::list<std::shared_ptr<Process>> processList;
        void updateProcessList(int dt);
    public:
        void attach(Process *p);
        void remove(Process *p);
        void abortAll(); 
};


#endif