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
    }
}
