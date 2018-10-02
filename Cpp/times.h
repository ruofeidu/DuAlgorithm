#pragma once
#include "common.h"

namespace Times {
	int calcWeekday(int day, int month, int year) {
		// monday - sunday: 0 - 6
		int weekday;
		if (month == 1 || month == 2) {
			month += 12;
			--year;
		}
		if ((year < 1752) || (year == 1752 && month < 9) ||
			(year == 1752 && month == 9 && day < 3)) {
			weekday = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 + 5) % 7;
		}
		else {
			weekday = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
		}
		return weekday;
	}
}