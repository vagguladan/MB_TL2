#pragma once
#include "CommonInclude.h"

namespace MB
{
	class Time
	{
	public:
		void static Initialize();
		void static Update();
		void static Render(HDC hdc);

		__forceinline static float DeltaTime() { return mDeltaTime; }

	private:
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
		static float mDeltaTime;
	};
}