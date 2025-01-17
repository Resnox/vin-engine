#pragma once

#include "ecs/registry.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "light.hpp"
#include "transform.hpp"
#include "meshrenderer.hpp"
#include "assets/asset.hpp"
#include "module/rendering/rendercontext.hpp"

#include <optick.h>

namespace Vin{
	template<ArchetypeMemoryLayout layout>
	class Scene {
	public:
		void Render(std::shared_ptr<Camera> camera) {
			OPTICK_CATEGORY(OPTICK_FUNC, Optick::Category::Scene);

			m_Registry.Process(MeshRendererSystem, camera);
			m_Registry.Process(LightRendererSystem);
		}

		Registry<layout>* operator->() {
			return &m_Registry;
		}
		
	private:
		static void MeshRendererSystem(Registry<layout>& registry, Query<layout, Transform<float>, MeshRenderer> query, std::shared_ptr<Camera> camera) {
			Asset<RenderContext> m_Ctx = AssetDatabase::GetAsset<RenderContext>(VIN_RENDERCONTEXT_BASEPATH);

			for (auto [transform, meshrenderer] : query) {
				if (!meshrenderer->isDynamicMesh) {
					StaticMesh* mesh = meshrenderer->staticmesh;
					for (auto& primitive : *mesh) {
						if (primitive.material)
							m_Ctx->queue.PushRenderTask(camera, primitive, transform->GetModelMatrix(registry));
					}
				}
			}
		}

		static void LightRendererSystem(Query<layout, Light> query) {
			Asset<RenderContext> m_Ctx = AssetDatabase::GetAsset<RenderContext>(VIN_RENDERCONTEXT_BASEPATH);

			for (auto [light] : query) {
				if (light->type == LightType::Directional) {
					m_Ctx->mainLight = *light;
					continue;
				}

				//Additional Light
			}
		}

	private:
		Registry<layout> m_Registry{};
	};
}