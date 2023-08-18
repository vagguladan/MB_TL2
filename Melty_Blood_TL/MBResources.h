#pragma once
#include "MBResource.h"
#include "MBTexture.h"

namespace MB
{
	class Resources
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& name)
		{
			auto iter = _mResources.find(name);
			if (iter == _mResources.end())
				return nullptr;

			// �ڽ� ���·� ����ȯ 
			return dynamic_cast<T*>(iter->second);
		}

		template<typename T>
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(name);

			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;
				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			_mResources.insert(std::make_pair(name, resource));

			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			_mResources.insert(std::make_pair(name, resource));
		}


		static void Release()
		{
			for (auto iter : _mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}
	private:
		static std::map<std::wstring, Resource* > _mResources;
	};
}