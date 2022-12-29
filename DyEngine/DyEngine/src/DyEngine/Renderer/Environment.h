#pragma once
#include "Shader.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace DyEngine
{

	class Environment
	{
	public:
		struct SunStats
		{
			float sunEnergy = 1.0f;
			glm::vec3 sunColor = glm::vec3(1.0, 1.0, 1.0);
		};

		// Stats
		struct CloudsStats
		{
			float windStrength = 0.0005f;
			glm::vec3 windDirection = glm::vec3(0.35f, 0, 0);

			glm::vec4 CloudBaseColor = glm::vec4(0, 0, 0, 0);
			glm::vec4 CloudTopColor = glm::vec4(0, 0, 0, 0);

			float NoiseThreshold = 0.6f;
			float NoiseMax = 0.9f;

			float cloudVolumeStartHeight = 1500.0f;
			float cloudVolumeHeight = 2000.0f;

			float groundRadius = 6371000.0f;

			float cloudTopOffset = 1.0f;
			glm::vec3 weatherTexMod = glm::vec3(3.0f, 0, 0);
			float precipiFactor = 0.08f;
			float coverageFactor = 0.0f;

			float detailScale = 0.1f;
			float curlNoiseMultiple = 1.0f;

			glm::vec3 detailwindDirection = glm::vec3(0.005, 0.0, 0.005);
			float cloudSpeed = 3.912f;
		};

		struct EnvData
		{
			SunStats	sunData;
			CloudsStats cloudsData;
		};
		EnvData env_data;
	public:
		static Ref<Environment> Create(EnvData& env_data, Ref<Shader>& env_shader);
		virtual ~Environment() = default;

		virtual void draw() = 0;

		EnvData& GetEnvData() { return env_data; }
		static SunStats GetSunStats();
	};
}
