#include "R3DRenderer.hpp"
#include <chrono>
#include "../../Patchables/Offsets.hpp"
#include "../Game.hpp"

void R3DRenderer::Initialize()
{
	R3DRenderer::RendererInstance = *reinterpret_cast<uintptr_t*>(DEFINE_RVA(Offsets::R3DRenderer::INSTANCE));
	//R3DRenderer::ViewProjectionMatrix = *reinterpret_cast<uintptr_t*>(DEFINE_RVA(Offsets::R3DRenderer::VIEW_PROJECTION_MATRIX));

	R3DRenderer::ScreenWidth = reinterpret_cast<int*>(R3DRenderer::RendererInstance + 0x10);
	R3DRenderer::ScreenHeight = reinterpret_cast<int*>(R3DRenderer::RendererInstance + 0xC);
}

int R3DRenderer::GetScreenWidth()
{
	return *R3DRenderer::ScreenWidth;
}

int R3DRenderer::GetScreenHeight()
{
	return *R3DRenderer::ScreenHeight;
}

bool R3DRenderer::WorldToScreen(const Vector3& position, Vector2* out)
{
	static const uintptr_t* worldInstance{ reinterpret_cast<uintptr_t*>(
		*reinterpret_cast<uintptr_t*>
		(DEFINE_RVA(Offsets::R3DRenderer::WORLD_INSTANCE)) 
		+ Offsets::R3DRenderer::WORLD_INSTANCE_OFFSET)
	};

	static const auto fnWorldToScreen{
		reinterpret_cast<bool(__fastcall*)(const uintptr_t*, const Vector3*, Vector2*)>
		(DEFINE_RVA(Offsets::R3DRenderer::WORLD_TO_SCREEN_FUNCTION))
	};

	return fnWorldToScreen(
		worldInstance, 
		&position, 
		out
	);
}

void R3DRenderer::DrawTextX(const char* text, float size, const Vector3& position, uint32_t color, std::string fontName, bool outline, bool shadow)
{
	if ((color & IM_COL32_A_MASK) == 0)
		return;

	Vector2 screenPosition{};
	R3DRenderer::WorldToScreen(position, &screenPosition);

	ImGui::GetWindowDrawList()->AddText(
		ImVec2(screenPosition.x, screenPosition.y),
		color,
		text
	);
}



void R3DRenderer::DrawCircle(const Vector3& position, const float radius, const uint32_t color, const float thickness, bool filled)
{
	if ((color & IM_COL32_A_MASK) == 0)
		return;

	Vector3 worldPosition = position;
	for (auto i = 0; i <= 99; i++) {
		const auto angle = static_cast<float>(i) * M_PI * 1.98f / 98.0f;
		worldPosition.x = position.x + cos(angle) * radius;
		worldPosition.z = position.z + sin(angle) * radius;

		Vector2 screenPosition{};
		R3DRenderer::WorldToScreen(worldPosition, &screenPosition);
		ImGui::GetWindowDrawList()->PathLineTo(ImVec2(screenPosition.x, screenPosition.y));
	}
	if (!filled)
		ImGui::GetWindowDrawList()->PathStroke(color, 0, thickness);
	else
		ImGui::GetWindowDrawList()->PathFillConvex(color);
}

void R3DRenderer::DrawLine(const Vector3& start, const Vector3& end, const uint32_t color, const float thickness)
{
	if ((color & IM_COL32_A_MASK) == 0)
		return;

	Vector2 from = {};
	R3DRenderer::WorldToScreen(start, &from);

	Vector2 to = {};
	R3DRenderer::WorldToScreen(end, &to);

	ImGui::GetWindowDrawList()->AddLine(
		ImVec2(from.x, from.y),
		ImVec2(to.x, to.y), 
		color, 
		thickness
	);
}