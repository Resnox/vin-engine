#include "renderer.hpp"

#include "core/assert.hpp"

#include "platform/opengl/renderer_opengl.hpp"

Vin::Renderer::Api Vin::Renderer::s_api = Vin::Renderer::None;
Vin::Renderer::RenderingApi* Vin::Renderer::s_renderingapi = nullptr;

void Vin::Renderer::Init()
{
	VIN_ASSERT(s_api == None, "Rendering api already initialized.");

	s_api = Renderer::OpenGL;
	s_renderingapi = new OpenGLRenderingApi{};
}

void Vin::Renderer::InitApi()
{
	s_renderingapi->Init();
}

void Vin::Renderer::Terminate()
{
	delete s_renderingapi;
	s_api = Renderer::None;
}

Vin::Renderer::Api Vin::Renderer::GetApi()
{
	return s_api;
}

void Vin::Renderer::SetViewport(int x, int y, int width, int height)
{
	VIN_ASSERT(s_renderingapi != nullptr, "Rendering api is not initialized.");
	s_renderingapi->SetViewport(x, y, width, height);
}

void Vin::Renderer::Clear(float r, float g, float b, float a)
{
	VIN_ASSERT(s_renderingapi != nullptr, "Rendering api is not initialized.");
	s_renderingapi->Clear(r, g, b, a);
}

void Vin::Renderer::DrawArrays(const std::shared_ptr<VertexArray>& vertexArray, size_t verticiesCount)
{
	VIN_ASSERT(s_renderingapi != nullptr, "Rendering api is not initialized.");
	s_renderingapi->DrawArrays(vertexArray, verticiesCount);
}

void Vin::Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, size_t indexCount)
{
	VIN_ASSERT(s_renderingapi != nullptr, "Rendering api is not initialized.");
	indexCount = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
	s_renderingapi->DrawIndexed(vertexArray, indexCount);
}