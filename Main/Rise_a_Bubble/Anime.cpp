#include "Scene.h"

struct ANIME {
	int tornado[3];

}anime;
void Tornado() {
	static int Tor=0;
	static int count=0;
	Scene A;
	count = A.Cnt(count);
	if (count % 5 == 0)Tor++;
	if (Tor == 3)Tor = 0;
	DrawGraph(0, 0, anime.tornado[Tor], TRUE);
}