#pragma once
#include <cstdint>
#include <string>

#include "../../Math/Vector.h"

#define RGBA(iRed, iGreen, iBlue, iAlpha)    (((std::uint32_t)(iAlpha)<<24) | ((std::uint32_t)(iBlue)<<16) | ((std::uint32_t)(iGreen)<<8) | ((std::uint32_t)(iRed)<<0))
#define ARGB(iAlpha, iRed, iGreen, iBlue)    RGBA(iRed, iGreen, iBlue, iAlpha)

class R3DRenderer
{
public:
	// TODO: Refactor WorldToScreen, Rewrite W2S function to not use game call.
	static void Initialize();

	static int GetScreenWidth();
	static int GetScreenHeight();
	static bool WorldToScreen(const Vector3& position, Vector2* out);

	static void	 DrawTextCentered(const char* text, const Vector2& position, float size, uint32_t color, std::string fontName, bool outline = false, bool shadow = false);
	static void	 DrawTextX(const char* text, float size, const Vector3& position, uint32_t color, std::string fontName, bool outline = false, bool shadow = false);
	static void	 CalcTextSize(const char* text, float size, Vector2* outSize, std::string fontName);
	
	// 3D Drawing (World)
	static void	DrawLine(const Vector3& start, const Vector3& end, uint32_t color, float thickness);
	static void	DrawRect(const Vector4& rect, uint32_t color, float thickness, bool filled = false);
	static void DrawCircle(const Vector3& position, float radius, uint32_t color, float thickness, bool filled = false);
	static void DrawBox(const Vector3& position, Vector2 size, uint32_t color, float thickness, bool filled = false);
	static void DrawTriangle(const Vector3& position, Vector2 size, uint32_t color, float thickness, bool filled = false);
private:
	static inline uintptr_t RendererInstance = 0;

	static inline int* ScreenWidth = nullptr;
	static inline int* ScreenHeight = nullptr;
};

