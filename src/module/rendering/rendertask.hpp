#pragma once

#include "renderer/vertexarray.hpp"
#include "renderer/framebuffer.hpp"
#include "scene/material.hpp"
#include "scene/camera.hpp"
#include "scene/mesh.hpp"

namespace Vin {

	class RenderTask {
	public:
		RenderTask(std::shared_ptr<Camera> camera, Primitive& primitive, Matrix4x4<float> model);

		std::shared_ptr<Camera> GetCamera();
		Primitive& GetPrimitive();
		Matrix4x4<float>& GetModel();
		bool IsValid();

		unsigned long long GetId();

	private:
		unsigned long long m_Id; // |---4bit ViewPort ID---|---4bit Transluency type---|-----24bit Depth-----|-------32bit Material ID------|
		std::shared_ptr<Camera> m_Camera; //ViewPort
		Primitive* m_Primitive;
		Matrix4x4<float> m_Model;
		bool m_Valid;
	};

}
