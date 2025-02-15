#pragma once


#include <GCrisp/Events/ApplicationEvent.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace GCrisp
{
    namespace Graphics
    {
        class Camera
        {
        public:
            Camera(glm::vec3 position) : m_Position(position), m_View(glm::mat4(1.0f)), m_Projection(glm::mat4(1.0f))
            {
            }

            virtual ~Camera() = default;

            virtual void Project() = 0;
            virtual void OnResize(const int& newWidth, const int& newHeight) = 0;

            inline const glm::vec3& GetPosition() const { return m_Position; }
            inline const glm::mat4& GetView() const { return m_View; }
            inline const glm::mat4& GetProjection() const { return m_Projection; }

            inline void SetPosition(const glm::vec3& position) { m_Position = position; }
            inline void SetView(const glm::mat4& view) { m_View = view; }
            inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }

            inline glm::mat4 GetViewProj() const { return m_Projection * m_View; }

        protected:
            glm::vec3 m_Position;
            glm::mat4 m_View;
            glm::mat4 m_Projection;
        };
    }
}
