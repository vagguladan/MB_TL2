#pragma once
#include "MBComponent.h"
#include "MBTexture.h"

namespace MB
{
	using namespace math;
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetImage(Texture* image) { mTexture = image; }
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetAffectCamera(bool enable) { mbAffectCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

	private:
		//Gdiplus::Image* mImage;
		bool mbAffectCamera;
		Texture* mTexture;
		Vector2 mScale;
		float mAlpha;
	};
}
