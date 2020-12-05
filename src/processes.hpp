#pragma once
#include "process_manager.hpp"
#include <variant>
#include <array>

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
        class Callback : public Process
        {
        public:
            Callback(C callback) : callback_(callback)
            {}

            void Init() override
            {
                callback_();
            }

            void Update(double delta) override
            {
                Stop();
            }

        private:
            C callback_;
        };

        template<typename C>
        class WhileTrue : public Process
        {
        public:
            WhileTrue(C callback) : callback_(callback)
            {}

            void Init() override
            {
            }

            void Update(double delta) override
            {
                callback_(delta);
            }

        private:
            C callback_;
        };

        template<typename C>
        class Generic : public Process
        {
        public:
            Generic(C callback) : callback_(callback)
            {}

            void Init() override
            {
            }

            void Update(double delta) override
            {
                if (!callback_(delta))
                {
                    Stop();
                }
            }

        private:
            C callback_;
        };

        template<typename T>
        class ProcessWrapper
        {
        public:
            ProcessWrapper(T&& t) : t_(std::forward<T>(t))
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

        //TODO ignores child processes
        //TODO Use std::array instead of vector
        template<typename ...Args>
        class Consecutive : public Process
        {
        private:
            using Variant = std::variant<ProcessWrapper<Args>...>;
            using Container =
                std::vector<Variant>;
        public:
            Consecutive(ProcessWrapper<Args>&&... args)
                : Consecutive(std::make_index_sequence<sizeof...(Args)>{},
                              std::forward<ProcessWrapper<Args>>(args)...)
            {
            }

            void Init() override
            {
                std::visit([](auto& pr)
                {
                    pr.Init();
                }, *current_);
            }

            void Update(double delta) override
            {
                if (std::visit([delta](auto& pr)
                    {
                        pr.Update(delta);
                        return pr.GetState() == Process::State::ENDED;
                    }, *current_))
                {
                    ++current_;
                    if (current_ == container_.end())
                    {
                        Stop();
                        return;
                    }
                    std::visit([](auto& pr)
                    {
                        pr.Init();
                    }, *current_);
                }
            }

        private:
            template<std::size_t ... Is>
            Consecutive(const std::index_sequence<Is...>&,
                        ProcessWrapper<Args>&&... args)
            {
                (... , container_.emplace_back(Variant(std::in_place_index<Is>,
                                   std::forward<ProcessWrapper<Args>>(args))));
                current_ = container_.begin();
            }

            Container container_;
            typename Container::iterator current_ = container_.begin();
        };

        template<typename ... Args>
        class And : public Process
        {
        public:
            And(ProcessWrapper<Args>&& ... args)
                : args_(std::forward<ProcessWrapper<Args>>(args)...)
            {
            }

            void Init() override
            {
                std::apply([](auto && ... args)
                {
                    (..., args.Init());
                }, args_);
            }

            void Update(double delta) override
            {
                if (!std::apply([delta](auto && ... args)
                {
                    return (... && (args.Update(delta),
                                    args.GetState() != Process::State::ENDED));
                }, args_))
                {
                    Stop();
                }
            }

        private:
            std::tuple<ProcessWrapper<Args>...> args_;
        };

        template<typename ... Args>
        Consecutive<Args...> MakeConsecutive(Args&& ... args)
        {
            return Consecutive<Args...>(ProcessWrapper(std::forward<Args>(args))...);
        }

        template<typename ... Args>
        And<Args...> MakeAnd(Args&& ... args)
        {
            return And<Args...>(ProcessWrapper(std::forward<Args>(args))...);
        }

        template<typename P>
        ProcessPtr ToPtr(P&& p)
        {
            return std::make_unique<P>(std::forward<P>(p));
        }
    }
}
