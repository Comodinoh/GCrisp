#pragma once

#include "Camera.h"

namespace GCrisp::Graphics2D
{
class OrthoCamera : public Graphics::Camera
{
  public:
	OrthoCamera(glm::vec3 position, float aspectRatio, float scale = 1.0f)
		: Graphics::Camera(position), m_AspectRatio(aspectRatio), m_Scale(scale)
	{
		UpdateProjection();
		OrthoCamera::Project();
	}

	virtual void Project() override;
	virtual void OnResize(int newWidth, int newHeight) override;

	void UpdateProjection();

	inline float GetAspectRatio() const { return m_AspectRatio; }
	inline float GetScale() const { return m_Scale; }

	inline void SetAspectRatio(const float& aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		UpdateProjection();
	}

	inline void SetScale(const float& scale)
	{
		m_Scale = scale;
		UpdateProjection();
	}

  private:
	float m_AspectRatio;
	float m_Scale;
};
} // namespace GCrisp::Graphics2D
