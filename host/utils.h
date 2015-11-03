#pragma once

std::string int2str(const int i);
std::string int2hex(const unsigned short i);

#ifdef _MSC_VER
# define		snprintf	sprintf_s
#endif
