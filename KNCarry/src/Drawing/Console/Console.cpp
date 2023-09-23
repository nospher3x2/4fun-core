#include "Console.hpp"
#include <string>
#include <Windows.h>

int CommandLineImGuiCallback(ImGuiInputTextCallbackData* data) {
	const char* historyLine;

	switch (data->EventFlag) {
	case ImGuiInputTextFlags_CallbackHistory:
		if (Console::CommandHistory.empty())
			return 0;

		/// Reset the offset counter if we ask for the first time for a history command
		if (!data->HasSelection())
			Console::CommandHistoryOffset = Console::CommandHistory.size() - 1;

		/// Increment/decrement history index accordingly
		else if (data->EventKey == ImGuiKey_DownArrow) {
			if (Console::CommandHistoryOffset < Console::CommandHistory.size() - 1)
				Console::CommandHistoryOffset++;
		}
		else if (Console::CommandHistoryOffset > 0)
			Console::CommandHistoryOffset--;

		/// Copy history line to current line
		historyLine = Console::CommandHistory[Console::CommandHistoryOffset].c_str();
		memcpy(data->Buf, historyLine, strlen(historyLine));
		data->BufTextLen = strlen(historyLine);
		data->BufDirty = true;
		data->SelectAll();

		break;
	default:
		break;
	}

	return 0;
}

void ConsoleStringLine::ImDraw()
{
	ImGui::Text(">>>");
	ImGui::SameLine();
	ImGui::TextColored(color, text.c_str());
}
void Console::Draw()
{
	static LONGLONG lastTick = 0;
	if (GetAsyncKeyState(VK_SHIFT) & 1 && lastTick - GetTickCount64() > 100)
	{
		ShouldDraw = !ShouldDraw;
		lastTick = GetTickCount64();
	}

	if (!ShouldDraw)
		return;

	static bool scrollDownConsole = false;

	const auto& io = ImGui::GetIO();
	ImVec2 size;
	size.x = io.DisplaySize.x * 0.3f;
	size.y = 50.f;

	ImGui::Begin("Console");
	{
		/// Draw options: clear & context selection
		ImGui::BeginChild("ConsoleOptions", ImVec2(size), true);

		if (ImGui::Button("Clear")) {
			Buffer.clear();
		}

		ImGui::EndChild();

		/// Draw console log
		size.y = io.DisplaySize.y - 600.f;
		ImGui::BeginChild("ConsoleLog", size, true);

		for (const auto& l : Buffer) {
			l->ImDraw();
		}

		if (scrollDownConsole) {
			ImGui::SetScrollHereY(1.f);
			scrollDownConsole = !scrollDownConsole;
		}

		ImGui::EndChild();

		/// Draw & process command line
		ImGui::BeginChild("ConsoleCmd", ImVec2(size.x, 40.f), true, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetNextItemWidth(size.x);
		if (ImGui::InputText("###CommandLine", &line[0], SizeLine, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory, CommandLineImGuiCallback, nullptr)) {

			scrollDownConsole = true;
			ImGui::SetKeyboardFocusHere(0);

			const auto command = new ConsoleStringLine{};
			command->color = ImVec4(0.f, 1.f, 1.f, 1.f);
			command->text = line;

			Buffer.push_back(command);

			CommandHistory.emplace_back(line);
			memset(line, 0, SizeLine);
		}

		ImGui::EndChild();
	}
	ImGui::End();
}

void Console::AddLine(ConsoleLine* line)
{
	Buffer.push_back(line);
}

void ConsoleSeparatorLine::ImDraw()
{
	ImGui::Separator();
}