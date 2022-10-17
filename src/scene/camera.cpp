#include "camera.hpp"

Vin::Camera::Camera(Vector2<int> size, int samples, bool HDR) 
	: m_Size{ size }, m_Near{ 0.1 }, m_Far{ 1000 }, m_FOV{ 90 }, m_RenderTarget{}
{
	RenderTargetSpecification specification{ (size_t)size.x, (size_t)size.y, (size_t)samples };
	specification.AddRenderBuffer({ HDR ? RenderBufferFormat::RGBA16F : RenderBufferFormat::RGBA32, true });
	specification.AddRenderBuffer({ RenderBufferFormat::DEPTH24_STENCIL8, false });

	m_RenderTarget = RenderTarget::Create(specification);
}

void Vin::Camera::SetNearPlane(float near)
{
	m_Near = near;
}

float Vin::Camera::GetNearPlane()
{
	return m_Near;
}

void Vin::Camera::SetFarPlane(float far)
{
	m_Far = far;
}

float Vin::Camera::GetFarPlane()
{
	return m_Far;
}

void Vin::Camera::SetFOV(float fov)
{
	m_FOV = fov;
}

float Vin::Camera::GetFOV()
{
	return m_FOV;
}

void Vin::Camera::Resize(Vector2<int> size)
{
	m_RenderTarget->Resize((size_t)size.x, (size_t)size.y);
	m_Size = size;
}

Vin::Vector2<int> Vin::Camera::GetSize()
{
	return m_Size;
}

void Vin::Camera::Bind()
{
	m_RenderTarget->Bind();
}

void Vin::Camera::Unbind()
{
	m_RenderTarget->Unbind();
}

Vin::Matrix4x4<float> Vin::Camera::GetProjectionMatrix()
{
	return Perspective<float>(m_FOV * deg2rad, (float)m_Size.x / (float)m_Size.y, m_Near, m_Far);
}

Vin::Matrix4x4<float> Vin::Camera::GetViewMatrix()
{
	return Matrix4x4<float>::identity;
}