#pragma once

struct stRange
{
	float	fMin;
	float	fMax;

	stRange();
	stRange(float min, float max);
	void UpdateMinMax();
	bool OverlappedRange(const stRange &ohter, OUT stRange* overlappedRange) const;

	static bool OverlappedRange(const stRange &range, const stRange &range2, OUT stRange* overlappedRange);
};