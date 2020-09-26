#pragma once
#include <memory>

namespace Transport
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

        virtual void init() {}
        virtual void update(double delta) = 0;
        virtual ~Process() = default;
        void setNext(std::unique_ptr<Process>);
        const Process& getNext() const;
        std::unique_ptr<Process> takeNext();
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
