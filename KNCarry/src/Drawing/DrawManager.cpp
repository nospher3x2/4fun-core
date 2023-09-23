#include "./DrawManager.hpp"
#include "./ImGui/imgui_impl_win32.h"
#include "./ImGui/imgui_impl_dx11.h"
#include "./Kiero/kiero.h"
#include "./Console/Console.hpp"

#include "../EventHandler/EventHandler.hpp"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawManager::Draw() {
	ImGui::Begin("[200] CORE");
	{
		ImGui::Text("Start");
	}
	ImGui::End();
}

void DrawManager::Initialize()
{
	const kiero::Status::Enum status = kiero::init(kiero::RenderType::D3D11);
	if (status == kiero::Status::Success)
	{
		kiero::bind(8, reinterpret_cast<void**>(&Present), DrawManager::HookPresent);
	}
}

void DrawManager::Destroy()
{
	kiero::shutdown();
}

HRESULT __stdcall DrawManager::HookPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!DrawManager::KieroInitialized)
		DrawManager::KieroInitialized = true;

	if (!DrawManager::ImGuiInitialized)
		DrawManager::InitRenderer(pSwapChain);

	DrawManager::StartRenderer();

	EventHandler::Trigger(EventType::OnPresentDraw);
	DrawManager::Draw();
	Console::Draw();

	DrawManager::EndRenderer();

	return DrawManager::Present(pSwapChain, SyncInterval, Flags);
}

LRESULT __stdcall DrawManager::HookedWindowProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	bool execute = true;
	EventHandler::Trigger(EventType::OnWndProc, hWnd, uMsg, wParam, lParam, &execute);
	if (!execute)
		return true;
	
	return CallWindowProc(Renderer->WndProc, hWnd, uMsg, wParam, lParam);
}

void DrawManager::InitRenderer(IDXGISwapChain* swapChain)
{
	if (Renderer->SwapChain)
		return;
	
	if (swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&Renderer->Device)) < 0)
		return;

	Renderer->SwapChain = swapChain;

	DrawManager::SetContext();
	DrawManager::SetImGui();

	DrawManager::ImGuiInitialized = true;
}

void DrawManager::SetContext()
{
	Renderer->Device->GetImmediateContext(&Renderer->Context);
	DXGI_SWAP_CHAIN_DESC sd;
	Renderer->SwapChain->GetDesc(&sd);
	Renderer->Window = sd.OutputWindow;

	ID3D11Texture2D* pBackBuffer;
	Renderer->SwapChain->GetBuffer(
		0, 
		__uuidof(ID3D11Texture2D), 
		reinterpret_cast<LPVOID*>(&pBackBuffer)
	);
	if (pBackBuffer == nullptr)
		return;
	
	Renderer->Device->CreateRenderTargetView(
		pBackBuffer, 
		nullptr,
		&Renderer->TargetView
	);

	pBackBuffer->Release();
	Renderer->WndProc = WNDPROC(SetWindowLongPtr(
		Renderer->Window,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(HookedWindowProc)
	));
}

void DrawManager::SetImGui()
{
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(Renderer->Window);
	ImGui_ImplDX11_Init(Renderer->Device, Renderer->Context);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x2000, 0x3000,
		0,
	};

	io.Fonts->AddFontFromFileTTF(
		R"(C:\Windows\Fonts\Consola.ttf)", 
		13.0f, 
		nullptr, 
		ranges
	);
	ImGui::GetIO().Fonts->Build();

	//ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouse;
	ImGui::GetStyle().AntiAliasedFill = true;
	ImGui::GetStyle().AntiAliasedLines = true;

	const auto style = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 8.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 5.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 10.0f;
	style->ScrollbarRounding = 12.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 5.0f;
	style->WindowBorderSize = 0.0f;
	style->Alpha = 0.85f;

	constexpr auto accentColor = ImVec4(0.58f, 0.22f, 0.96f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImVec4(accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.45f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.15f);
	style->Colors[ImGuiCol_TabUnfocused] = ImVec4(accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.45f);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.15f);
	style->Colors[ImGuiCol_TabHovered] = ImVec4(accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.15f);

	//style->Colors[ ImGuiCol_DockingPreview ] = accentColor;
	//style->Colors[ ImGuiCol_DockingEmptyBg ] = ImVec4( accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.90f );

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(accentColor.x, accentColor.y, accentColor.z, accentColor.w - 0.35f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = accentColor;
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = accentColor;
	style->Colors[ImGuiCol_SliderGrab] = accentColor;
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	//style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	//style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	//style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
}

void DrawManager::StartRenderer()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("##overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
	ImGui::SetWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
}

void DrawManager::EndRenderer()
{
	ImGui::GetForegroundDrawList()->PushClipRectFullScreen();

	ImGui::EndFrame();
	ImGui::Render();

	Renderer->Context->OMSetRenderTargets(1, &Renderer->TargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}