#include <string>

#include <time.h>
#include <stdio.h>

#include "progress.h"

void ProgressBar::Refresh(const double progress)
{
	double seconds = (clock() - time_begin) / double(CLOCKS_PER_SEC);

	std::string hashes(size_t(progress * 50), '#');

	printf("\r%-11s | %-50s | %3i%%  %.2fs", process_name, hashes.c_str(), int(progress * 100), seconds);
	fflush(stdout);
}
