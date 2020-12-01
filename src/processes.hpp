#pragma once
#include "process_manager.hpp"

namespace transport
{
    namespace processes
    {
        class Wait : public Process
        {
        public:
            Wait(double time) : time_(time)
            {}

            void Update(double delta)
            {
                time_passed_ += delta;
                if (time_passed_ > time_)
                    Stop();
            }

        private:
            double time_;
            double time_passed_ = 0.;
        };

        class Endless : public Process
        {
        public:
            void Update(double delta) {}
        };

        template<typename C>
        class CallBack : public Process
        {
        public:
            CallBack(C callback) : callback_(callback)
            {}

            void Init() override
            {
                callback_();
            }

            void Update(double delta)
            {
                Stop();
            }

        private:
            C callback_;
        };

        template<typename T>
        class ProcessWrapper
        {
        public:
            ProcessWrapper(T&& t) : t_(std::move(t))
            {}
            ProcessWrapper(const T& t) : t_(t)
            {}

            void Init() { t_.Init(); }
            void Update(double delta) { t_.Update(delta); }
            void SetNext(ProcessPtr n) { t_.SetNext(std::move(n)); }
            const Process* GetNext() const { return t_.GetNext(); }
            Process* GetNext() { return t_.GetNext(); }
            ProcessPtr TakeNext() { return t_.TakeNext(); }
            void Stop() { t_.Stop(); }
            Process::State GetState() { return t_.GetState(); }
        private:
            T t_;
        };

        template<typename T>
        class ProcessWrapper<std::unique_ptr<T>>
        {
        public:
            ProcessWrapper(std::unique_ptr<T> t) : t_(std::move(t))
            {}

            void Init() { t_->Init(); }
            void Update(double delta) { t_->Update(delta); }
            void SetNext(ProcessPtr n) { t_->SetNext(std::move(n)); }
            const Process* GetNext() const { return t_->GetNext(); }
            Process* GetNext() { return t_->GetNext(); }
            ProcessPtr TakeNext() { return t_->TakeNext(); }
            void Stop() { t_->Stop(); }
            Process::State GetState() { return t_->GetState(); }
        private:
            std::unique_ptr<T> t_;
        };
    }
}
