#pragma once
#include "MBEntity.h"

namespace MB
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		void SetPath(const std::wstring& path) { mPath = path; }
		std::wstring& GetPath() { return mPath; }

	private:
		std::wstring mPath;
	};
}