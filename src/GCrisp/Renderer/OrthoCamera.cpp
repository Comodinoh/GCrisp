#include "OrthoCamera.h"

namespace GCrisp
{
    namespace Graphics2D
    {
        void OrthoCamera::Project()
        {
            GC_PROFILE_FUNC();
            m_View = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position));
        }

        void OrthoCamera::UpdateProjection()
        {
            GC_PROFILE_FUNC();
            m_Projection = glm::ortho(-m_AspectRatio * m_Scale, m_AspectRatio * m_Scale, -m_Scale, m_Scale);
        }

        void OrthoCamera::OnResize(const int& width, const int& height)
        {
            GC_PROFILE_FUNC();
            float aspectRatio = (float)width / (float)height;

            SetAspectRatio(aspectRatio);
        }
    }
}
