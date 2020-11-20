#pragma once
#include <memory>

namespace transport
{
    class Process
    {
    public:
        enum class State
        {
            UNINITIALIZED,
            RUNNING,
            ENDED
        };

        virtual void Init() {}
        virtual void Update(double delta) = 0;
        virtual ~Process() = default;
        void SetNext(std::unique_ptr<Process>);
        const Process& GetNext() const;
        std::unique_ptr<Process> TakeNext();
    protected:
        State state = State::UNINITIALIZED;
    };

    using ProcessPtr = std::unique_ptr<Process>;

    class ProcessManager
    {
    public:
        template<typename InputIterator>
        void Add(InputIterator begin, InputIterator end);
        void Add(std::unique_ptr<Process>);
    };
}
