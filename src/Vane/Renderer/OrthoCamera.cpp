#include "OrthoCamera.h"

namespace Vane::Graphics2D {
void OrthoCamera::Project() {
    VANE_PROFILE_FUNC();
    m_View = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position));
}

void OrthoCamera::UpdateProjection() {
    VANE_PROFILE_FUNC();

    // For a normal 16/9 monitor orthographic projection (aka the screen bounds)
    // would be:
    //                   1.0 (scale)
    // -1.77*1.0(scale)     0.0      1.77*1.0(scale)
    //                  -1.0 (scale)
    //
    m_Projection = glm::ortho(-m_AspectRatio * m_Scale, m_AspectRatio * m_Scale,
                              -m_Scale, m_Scale);
}

void OrthoCamera::OnResize(int width, int height) {
    VANE_PROFILE_FUNC();
    float aspectRatio = (float)width / (float)height;

    SetAspectRatio(aspectRatio);
}
} // namespace Vane::Graphics2D
