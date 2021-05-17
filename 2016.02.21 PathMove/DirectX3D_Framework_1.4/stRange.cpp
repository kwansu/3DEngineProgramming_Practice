#include "stdafx.h"
#include "stRange.h"

stRange::stRange()
	: fMax(FLT_MAX)
	, fMin(-FLT_MAX)
{
}

stRange::stRange(float min, float max)
	: fMax(max)
	, fMin(min)
{
}

void stRange::UpdateMinMax()
{
	if (fMax < fMin)
	{
		float temp = fMax;
		fMax = fMin;
		fMin = temp;
	}
}

bool stRange::OverlappedRange(const stRange & other, OUT stRange * overlappedRange) const
{
	if(fMin >= other.fMax || fMax <= other.fMin)
		return false;

	if (overlappedRange)
	{
		overlappedRange->fMax = Smaller(fMax, other.fMax);
		overlappedRange->fMin = Greater(fMin, other.fMin);
	}

	return true;
}

bool stRange::OverlappedRange(const stRange & range, const stRange & range2, OUT stRange * overlappedRange)
{
	return range.OverlappedRange(range2, overlappedRange);
}

