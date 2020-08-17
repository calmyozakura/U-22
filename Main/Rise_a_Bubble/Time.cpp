#include "Scene.h"

void TIME::ScoreTimer() {
	ScoreTime = ((GetNowHiPerformanceCount() - StartTime) / 1000000.0f)-PauseTime;
	DrawFormatString(WINDOW_HALF_X,0,0xff00ff,"%.2f",ScoreTime);
}
void TIME::PauseTimer() {
	PauseTime = ((GetNowHiPerformanceCount() - StartTime) / 1000000.0f)-ScoreTime;
}