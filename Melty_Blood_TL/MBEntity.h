#pragma once
#include "CommonInclude.h"

namespace MB
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		virtual void Initialize();
		virtual void Update();
		virtual void Redner(HDC hdc);

		void SetName(const std::wstring& name) { mName = name; }
		std::wstring& GetName() { return mName; }
	private:
		std::wstring mName;
	};
}