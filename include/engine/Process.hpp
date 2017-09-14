#ifndef PROC_H
#define PROC_H

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

#endif