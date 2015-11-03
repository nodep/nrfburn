#pragma once

struct ProgressBar
{
	clock_t			time_begin;
	const char* 	process_name;
	
	ProgressBar(const char* pn)
		: time_begin(clock()), process_name(pn)
	{}
	
	~ProgressBar()
	{
		printf("\n");
	}

	void Refresh(const double progress);
};
