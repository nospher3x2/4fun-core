#pragma once

#include <string>
#include "../ImGui/imgui.h"
#include <string>
#include <vector>

class ConsoleLine {

public:
	virtual ~ConsoleLine() = default;
	virtual void ImDraw() = 0;
};

class ConsoleStringLine : public ConsoleLine {

public:
	virtual void ImDraw() override;

public:
	ImVec4      color;
	std::string text;

};

class ConsoleSeparatorLine : ConsoleLine {
public:
	virtual void ImDraw() override;
};


class Console {

public:
	constexpr static size_t SizeLine = 1024;

	static void Draw();
	static void AddLine(ConsoleLine* line);

	static inline std::vector<std::string> CommandHistory = {};
	static inline size_t                   CommandHistoryOffset = 0;
	static inline bool                     ShowHistoryPopUp = false;
	static inline char                line[SizeLine] = {};

private:
	static inline bool ShouldDraw = false;
	static inline std::vector<ConsoleLine*> Buffer = {};
};