#ifndef PROCM_H
#define PROCM_H

#include <list>
#include <memory>
#include "components/engine/Process.hpp"

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