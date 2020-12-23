#pragma once
#include "process_manager.hpp"
#include <glm/vec2.hpp>

namespace transport
{
    class SmoothZoom : public Process
    {
        float m_speed;
        float& m_scale;
        glm::vec2& m_position;
        float m_fScale;
        glm::vec2 m_CCPosition;
        glm::vec2 m_WCCPosition;

    public:
        SmoothZoom(float &t_scale, glm::vec2& t_position)
            : m_scale{t_scale}, m_position{t_position},
              m_fScale{t_scale}
        {}

        //takes scale to add and cursor position in camera pixel coordinates
        void addScale(float t_addScale, float t_speed, glm::vec2 t_CCPosition = glm::vec2())
        {
            m_speed = t_speed;
            m_fScale += t_addScale;
            m_CCPosition = t_CCPosition;
            //Update world cursor position relative to camera
            m_WCCPosition = m_CCPosition * (1.f / m_scale);
            Run();
        }

        float inline getFinalScale() const { return m_fScale; }
        void Update(double t_delta) override
        {
            //Update scale and adjust position, so mouse stay in the same place
            m_scale += (m_fScale - m_scale) * m_speed * (float) t_delta;
            m_position += m_CCPosition * (1.f / m_scale) - m_WCCPosition;
            m_WCCPosition = m_CCPosition * (1.f / m_scale);
            //Stop moving when the scale is near final
            if (m_fScale - m_scale < 0.001f * m_scale && m_fScale - m_scale > -0.001f * m_scale)
            {
                Stop();
            }
        }
        void Init() override { }
    };

}
