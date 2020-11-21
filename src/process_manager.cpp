#include "process_manager.hpp"

namespace transport
{

    void ProcessManager::Update(double delta)
    {
        auto processIt = processes_.begin();
        while (processIt != processes_.end())
        {
            auto& processPtr = *processIt;
            if (processPtr->GetState() == Process::State::UNINITIALIZED)
            {
                processPtr->Init();
                processPtr->state_ = Process::State::RUNNING;
                processPtr->Update(delta);
            }
            else if (processPtr->GetState() == Process::State::RUNNING)
            {
                processPtr->Update(delta);
            }

            if (processPtr->GetState() == Process::State::ENDED)
            {
                if (processPtr->GetNext())
                {
                    Add(processPtr->TakeNext());
                }
                processIt = processes_.erase(processIt);
            }
            else
            {
                ++processIt;
            }
        }
    }
}
