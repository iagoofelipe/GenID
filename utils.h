#pragma once

#include <string>


namespace genid
{
	void copy_to_clipboard(const std::string& text);

	std::string make_time_random_id();
}
