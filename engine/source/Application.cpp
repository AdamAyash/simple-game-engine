#include "Application.h"

namespace engine
{
	void Application::SetNeedsToBeClosed(bool value)
	{
		m_bNeedsToBeClosed = value;
	}

	bool Application::NeedsToBeClosed() const
	{
		return m_bNeedsToBeClosed;
	}
}