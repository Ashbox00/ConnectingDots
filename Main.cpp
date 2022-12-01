#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class DotsNLine : public  olc::PixelGameEngine
{
public:
	class Dots {
	public:
		float radius = 1 + rand() % 4;
		float yspeed = -50 + rand() % 100;
		float xspeed = -50 + rand() % 100;
		float y = rand() % 1080;
		float x = rand() % 1920;
	};

	DotsNLine() {
		sAppName = "DotsNLine";
	}
public:
	bool OnUserCreate() override

	{
		
		SetPixelMode(olc::Pixel::ALPHA);

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {


		
		Clear(olc::Pixel(12,12,12));

		//tracking mouse position
		float mousex = GetMousePos().x;
		float mousey = GetMousePos().y;

		//making the dots
		if(GetMouse(olc::Mouse::LEFT).bPressed) {
			d.emplace_back(Dots());
			d.back().x = mousex;
			d.back().y = mousey;
			objnum += 1;

		}
		for (int i = 0; i < objnum; i++) {
			FillCircle(d[i].x, d[i].y, d[i].radius, olc::WHITE);
			
			d[i].y += fElapsedTime * d[i].yspeed;
			d[i].x += fElapsedTime * d[i].xspeed;
			if (d[i].y >= 1080 || d[i].y <= -2) {
				d[i].y = fmod(d[i].y + 1080, 1080);
			}
			if (d[i].x >= 1920 || d[i].x <= -2) {
				d[i].x = fmod(d[i].x + 1920, 1920);
			}
		}

		//checking for lines
		for (int a = 0; a < objnum; a++) {
			for (int b = 1; b < objnum; b++) {
				if (d[a].x < d[b].x) {
					xmag = abs(d[a].x - d[b].x);
					ymag = abs(d[a].y - d[b].y);
					mag = (xmag * xmag + ymag * ymag);
					if (mag <= 150 * 150) {
						int alph = (255 * (150 * 150 - mag) / (150 * 150));
						olc::Pixel op(255, 255, 255, alph);
						DrawLine(d[a].x, d[a].y, d[b].x, d[b].y, op);
						DrawLine(d[a].x+1, d[a].y+1, d[b].x+1, d[b].y+1, op);
					}
				}
			}
		}
		return true;
	}
private:
	int objnum = 150;
	std::vector<Dots> d{ 150 };
	float xmag;
	float ymag;
	float mag;
	
};

int main() {
	srand(time(NULL));
	DotsNLine demo;
	if (demo.Construct(1920, 1080, 1, 1))
		demo.Start();
	return 0;
}
