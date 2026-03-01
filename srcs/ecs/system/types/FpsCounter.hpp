#pragma once

#include <string>

#include "../ASystem.hpp"
#include "../DispatcherEvents.hpp"
#include "../../component/Components.hpp"

namespace ecs {
class World;

class FpsCounter : public ASystem {
private:
	double	m_lastTime = 0.0;
	double	m_timePassed = 0.0;
	int		m_frameCount = 0;

public:
	FpsCounter();
	~FpsCounter() = default;

	void					onRender(const RenderEvent& event);
	virtual void			bindEvents(Dispatcher& dispatcher) override;
};
}
