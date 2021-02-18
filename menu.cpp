#include <iostream>
#include <SFML/Graphics.hpp>
#include<string>
#include <fstream>
#include "properties.cpp"
#include <Windows.h>
using namespace sf;
using namespace std;

struct poz_of_button
{
    int sx;int sy;
    int x;int y;
    int cx;int cy;
    int lcornx;int lcorny;
};
struct size_of
{
    int x;
    int y;
    int cx;
    int cy;
};

void set_button_prop (poz_of_button* b, Sprite& sp)
{
    b->cx = int((b->sx)/2); b->cy = int((b->sy)/2);
	b->lcornx = b->x - b->cx; b->lcorny =  b->y - b->cy;
	sp.setOrigin(b->cx, b->cy);
    sp.setPosition(b->x, b->y);
}

bool def_about(RenderWindow& window, Sprite& Bg, Text& text_about, Font& font, bool* restart, int* i)
{
    bool t = true; int y=0;
     while (!Keyboard::isKeyPressed(Keyboard::Space))
     {
        Event event1;
        while (window.pollEvent(event1))
        {
            switch (event1.type)
            {
                case(Event::Closed):
                    {window.close(); *restart = false; return false;};
            }
        }

        string s_text_about;
        ifstream in("text_about.txt");
        if ((in.is_open())&& (t))
        {
            Text t_out;
            t_out.setString("If you want to go back\n press Space");
            t_out.setPosition(800,0);
            t_out.setFont(font);
            t_out.setCharacterSize(35);
            t_out.setFillColor(Color::Black);
            t_out.setStyle(Text::Bold);
            window.draw(Bg);
            window.draw(t_out);
            while (getline(in, s_text_about))
            {
                 text_about.setString(s_text_about);
                 text_about.setPosition(0,y);
                 window.draw(text_about);y+= 40;

            }
            t = false;
            window.display();
            in.close();
        }
     }
     *i = 0;
     return true;
}

void lost_focus (RenderWindow & window)
{
     while (true)
     {
         Event event1;
            while (window.pollEvent(event1))
            {
                switch (event1.type)
                {
                    case(Event::GainedFocus):
                         return;
                }
            }
     }
}

bool beginm(bool* restart,PhaseSpace* in, Con* cnst)
{
   // ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    Font font;
    if (!font.loadFromFile("Fonts/18341.ttf"))
    {
        return false;
    }
    int size_of_text = 35;
    int between_b = 100;
    size_of size_of_menu;
    size_of_menu.x = 1200; size_of_menu.y = 700;
    size_of_menu.cy =int((size_of_menu.y)/2);
    size_of_menu.cx = int((size_of_menu.x)/2);
    RenderWindow window(VideoMode(size_of_menu.x, size_of_menu.y), "Main Menu of Elastic pendulum",Style::Titlebar);
	Texture startTexture, headTexture, menuTexture3, aboutTexture, BackgroundTexture, exitTexture, propTexture;

	headTexture.loadFromFile("images/head.png");
	startTexture.loadFromFile("images/start.png");
	BackgroundTexture.loadFromFile("images/background.jpg");
	aboutTexture.loadFromFile("images/about.png");
	exitTexture.loadFromFile("images/exit.png");
	propTexture.loadFromFile("images/setprop.png");

	Sprite head(headTexture), Bg(BackgroundTexture), start(startTexture), about(aboutTexture), exit(exitTexture),prop(propTexture);

	head.setPosition(20, 0);

	Bg.setColor(Color(255, 255, 255, 255)); Bg.setScale(0.7,0.7);
	Bg.setPosition(0, 0);

	poz_of_button b_start;
	b_start.sx = 211; b_start.sy = 76;
	b_start.x = size_of_menu.cx ; b_start.y = size_of_menu.cy;
	set_button_prop (&b_start,start);

	poz_of_button b_about;
	b_about.sx = 764; b_about.sy = 79;
	b_about.x = size_of_menu.cx; b_about.y = size_of_menu.cy + between_b;
	set_button_prop (&b_about,about);

	poz_of_button b_prop;
	b_prop.sx = 507; b_prop.sy = 77;
	b_prop.x = size_of_menu.cx ; b_prop.y = size_of_menu.cy + 2*between_b;
	set_button_prop (&b_prop,prop);

	poz_of_button b_exit;
	b_exit.sx = 150; b_exit.sy = 67;
	b_exit.x = size_of_menu.cx; b_exit.y = size_of_menu.cy + 3*between_b ;
	set_button_prop(&b_exit,exit);

	Text text_about;
	text_about.setFont(font);
    text_about.setCharacterSize(size_of_text);
    text_about.setFillColor(Color(242,112,0,255));
    text_about.setStyle(Text::Bold);
    text_about.setOutlineColor (Color(96,0,0,255));
    text_about.setOutlineThickness(2);

	int menuNum = 0;

 //---------------------------------Запуск менюшки-------------------------//
	while (window.isOpen())
	{
	    Event event1;
        while (window.pollEvent(event1))
        {
            switch (event1.type)
            {
                case(Event::Closed):
                    {window.close(); return false;};
                case(Event::LostFocus):
                lost_focus(window);
            }
        }
		head.setColor(Color::White);
		start.setColor(Color::White);
		about.setColor(Color::White);
		exit.setColor(Color::White);
		prop.setColor(Color::White);

		menuNum = 0;

		window.clear(Color(129, 181, 221));

		if (IntRect(b_start.lcornx, b_start.lcorny, b_start.sx, b_start.sy).contains(Mouse::getPosition(window))) { start.setColor(Color(128,128,128)); menuNum = 1; }
		if (IntRect(b_about.lcornx, b_about.lcorny, b_about.sx, b_about.sy).contains(Mouse::getPosition(window))) { about.setColor(Color(128,128,128)); menuNum = 2; }
		if (IntRect(b_exit.lcornx, b_exit.lcorny, b_exit.sx, b_exit.sy).contains(Mouse::getPosition(window))) { exit.setColor(Color(128,128,128)); menuNum = 3; }
		if (IntRect(b_prop.lcornx, b_prop.lcorny, b_prop.sx, b_prop.sy).contains(Mouse::getPosition(window))) { prop.setColor(Color(128,128,128)); menuNum = 400; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)  {window.close();menuNum = 0; return true;};
			if (menuNum == 2)  if(!def_about(window,Bg,text_about,font,restart,&menuNum)) return false;
            if (menuNum == 3)  { window.close(); *restart = false;menuNum = 0;return false;};
            if (menuNum == 400)   {aaaaaaaaa(in,cnst);menuNum = 0;};
        }

		window.draw(Bg);
		window.draw(head);
		window.draw(start);
		window.draw(about);
		window.draw(exit);
		window.draw(prop);

		window.display();
	}
	return true;
}

