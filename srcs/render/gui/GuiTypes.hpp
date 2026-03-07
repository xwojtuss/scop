#pragma once

namespace render::gui {

struct GuiWindowState {
	bool	open = true;
};

struct GuiState {
	GuiWindowState	debugWindow;
};
}
