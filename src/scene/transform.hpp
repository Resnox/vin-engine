#pragma once

#include "math/math.hpp"

namespace Vin {

	template<typename T>
	struct Transform {
		Vector3<T> position{};
		Quaternion<T> rotation{};
		Vector3<T> scale{};

		Transform() : position{}, rotation{}, scale{ (T)1.0 } {};
		Transform(Vector3<T> position) : position{ position }, rotation{}, scale{ (T)1.0 } {};

		Matrix4x4<T> GetModelMatrix() {
			Matrix4x4<T> model{ Matrix4x4<T>::identity };

			Vin::Scale(model, scale);
			model = model * rotation.GetRotationMatrix();
			Vin::Translate(model, position);

			return model;
		}

		//POSITION

		void Translate(Vector3<T>& translation) {
			position += translation;
		}

		void SetPosition(Vector3<T>& position) {
			this->position = position;
		} 

		Vector3<T> GetPosition() {
			return position;
		}

		//ROTATION

		void SetRotation(Quaternion<T>& quaternion) {
			rotation = quaternion;
		}

		Quaternion<T> GetRotation() {
			return rotation;
		}

		//SCALE

		void SetScale(Vector3<T>& scale) {
			this->scale = scale;
		}

		Vector3<T> GetScale() {
			return scale;
		}
	};
}