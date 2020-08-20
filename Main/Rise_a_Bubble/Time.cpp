#include "Scene.h"
Scene S;
float TIME::ScoreTimer() {
	if(S.GoalFlg!=TRUE)ScoreTime = ((GetNowHiPerformanceCount() - StartTime) / 1000000.0f)-PauseTime;
	DrawFormatString(WINDOW_HALF_X,0,0xff00ff,"%.2f",ScoreTime);
	return ScoreTime;
}
void TIME::PauseTimer() {
	PauseTime = ((GetNowHiPerformanceCount() - StartTime) / 1000000.0f)-ScoreTime;
}