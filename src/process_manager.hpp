#pragma once
#include <memory>
#include <list>
#include <vector>

namespace transport
{
    class ProcessManager;

    class Process
    {
    public:
        friend class ProcessManager;
        enum class State
        {
            UNINITIALIZED,
            RUNNING,
            PAUSED,
            ENDED
        };

        virtual void Init() {}
        virtual void Update(double delta) = 0;
        virtual ~Process() = default;
        void SetNext(std::unique_ptr<Process> n) { next_ = std::move(n); }
        const Process* GetNext() const { return next_.get(); }
        Process* GetNext() { return next_.get(); }
        std::unique_ptr<Process> TakeNext() { return std::move(next_); };
        void Stop() { state_ = State::ENDED; }
        State GetState() { return state_; }
    private:
        State state_ = State::UNINITIALIZED;
        std::unique_ptr<Process> next_;
    };

    using ProcessPtr = std::unique_ptr<Process>;

    class ProcessManager
    {
    public:
        void Add(ProcessPtr ptr) { processes_.push_back(std::move(ptr)); }
        void Update(double delta);
    private:
        std::list<ProcessPtr> processes_;
    };
}
