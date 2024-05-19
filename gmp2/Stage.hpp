#pragma once

namespace HxH
{
	class Stage
	{
	public:
		virtual void Init() = 0;

		virtual void ProcessInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render(float dt) = 0;

		virtual void Pause() {}
		virtual void Resume() {}
	};
}
