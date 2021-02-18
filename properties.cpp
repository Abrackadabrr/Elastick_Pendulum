#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
using namespace sf;
using namespace std;

struct prop_of_box
{
    int sx;int sy;
    int x;int y;
    int cx;int cy;
    int lcornx;int lcorny;
};

struct PhaseSpace
{
    double x, y, vx, vy;
};

struct Con
{
    double l;
    double m;
    double g;
    double k;
};

class TextField
{

    public:
        Font font;
        prop_of_box prop_box;
        String s;
        Text txt;
        Sprite box;
        int b_size;
        bool active;

    public:

        TextField (int x,int y,Texture& t_box, double d)
        {
            prop_box.x = x; prop_box.y = y;
            prop_box.sx = 242; prop_box.sy = 68;
            prop_box.cx = int((prop_box.sx)/2);
            prop_box.cy = int((prop_box.sy)/2);
            prop_box.lcornx = prop_box.x - prop_box.cx;
            prop_box.lcorny =  prop_box.y - prop_box.cy;

            box.setTexture(t_box);
            box.setOrigin(prop_box.cx, prop_box.cy);
            box.setPosition(prop_box.x, prop_box.y);

            active = false;



            font.loadFromFile("Fonts/18341.ttf");
            s = to_string(d);
            b_size = s.getSize();
            txt.setString(s);
            txt.setFont(font);
            txt.setPosition(prop_box.lcornx,prop_box.lcorny);
            txt.setCharacterSize(35);
            txt.setFillColor(Color::Black);
            txt.setStyle(Text::Bold);


        }

        bool isActive()
        {
            return active;
        }

        bool setActive()
        {
            active = true;
            box.setColor(Color(128,128,128));
        }

        bool setPassive()
        {
            active = false;
            box.setColor(Color::White);
        }

        int getTextLength()
        {
            return b_size;
        }

        void displayBox(RenderWindow& b_win)
        {
            b_win.draw(box);
            b_win.draw(txt);
        }

        void getText(string& str)
        {
            str = txt.getString();
        }


        void input(Event& event)
        {
            if (isActive())
            {
                if (event.type == Event::TextEntered)
                {
                    switch ( event.text.unicode )
                    {
                        case (0xD):
                            {
                                setPassive();
                                return;
                            }
                        case (8):            //Backspace
                            if ( !getTextLength()) return;
                            else
                            {
                                s.erase((getTextLength()-1),1);
                                b_size--;
                                txt.setString(s);
                                return;
                            }
                        default :
                        {
                            s += (char)(event.text.unicode);
                            txt.setString(s);b_size++; return;
                        }
                    }
                }
            }
            return;
        }
};

void set_text_prop(Text& t1, Font& font)
{
    t1.setFont(font);
    t1.setCharacterSize(25);
    t1.setFillColor(Color::Black);
    t1.setStyle(Text::Bold);
}

void aaaaaaaaa(PhaseSpace* in, Con* cnst)
{
    Font font;
    if (!font.loadFromFile("Fonts/18341.ttf"));

    RenderWindow window(sf::VideoMode(800, 950), "Set properties");
    Texture textboxTexture; textboxTexture.loadFromFile("images/text_field.png");

    Text t1,t2,t3,t4,t5,t6;

    TextField txt_field_l(400,100,textboxTexture,cnst->l);
    t1.setString("Length (meters)");
    t1.setPosition(100,150);
    set_text_prop(t1,font);

    TextField txt_field_m(400,250,textboxTexture,cnst->m);
    t3.setString("Free fall acceleration (meters / seconds squared)");
    t3.setPosition(100,450);
    set_text_prop(t3,font);

    TextField txt_field_g(400,400,textboxTexture,cnst->g);
    t2.setString("Cargo weight (kilograms) ");
    t2.setPosition(100,300);
    set_text_prop(t2,font);

    TextField txt_field_k(400,550,textboxTexture,cnst->k);
    t4.setString("Spring rate (Newton / meter)");
    t4.setPosition(100,600);
    set_text_prop(t4,font);

    TextField txt_field_phi(400,700,textboxTexture,in->y);
    t5.setString("Angle start value");
    t5.setPosition(100,750);
    set_text_prop(t5,font);

    t6.setString("When you set all properties you want, close this window");
    t6.setPosition(50,850);
    set_text_prop(t6,font);

    bool is_any_box_active = false;

    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
            txt_field_l.input(event);
            txt_field_g.input(event);
            txt_field_m.input(event);
            txt_field_k.input(event);
            txt_field_phi.input(event);
        }

        if(Mouse::isButtonPressed(Mouse::Left)&& is_any_box_active)
            {
                txt_field_phi.setPassive();
                txt_field_l.setPassive();
                txt_field_g.setPassive();
                txt_field_m.setPassive();
                txt_field_k.setPassive();
            }

        int act = 0;

        if (IntRect(txt_field_l.prop_box.lcornx,txt_field_l.prop_box.lcorny, txt_field_l.prop_box.sx, txt_field_l.prop_box.sy).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
                { act = 1;}
        else if (IntRect(txt_field_g.prop_box.lcornx,txt_field_g.prop_box.lcorny, txt_field_g.prop_box.sx, txt_field_g.prop_box.sy).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
                { act = 2;}
        else if (IntRect(txt_field_m.prop_box.lcornx,txt_field_m.prop_box.lcorny, txt_field_m.prop_box.sx, txt_field_m.prop_box.sy).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
                { act = 3;}
        else if (IntRect(txt_field_k.prop_box.lcornx,txt_field_k.prop_box.lcorny, txt_field_k.prop_box.sx, txt_field_k.prop_box.sy).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
                { act = 4;}
        else if (IntRect(txt_field_phi.prop_box.lcornx,txt_field_phi.prop_box.lcorny, txt_field_phi.prop_box.sx, txt_field_phi.prop_box.sy).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
                { act = 5;}
       // if (IntRect(txt_field_l.prop_box.lcornx,txt_field_l.prop_box.lcorny, txt_field_l.prop_box.sx, txt_field_l.prop_box.sy).contains(Mouse::getPosition(window)))
            //    { act = 6;}

			if (act == 1)
            {
                txt_field_l.setActive();
                txt_field_g.setPassive();
                txt_field_m.setPassive();
                txt_field_k.setPassive();
                txt_field_phi.setPassive();
                is_any_box_active = true;
            }
			else if (act == 2)
            {
                txt_field_g.setActive();
                txt_field_l.setPassive();
                txt_field_m.setPassive();
                txt_field_k.setPassive();
                txt_field_phi.setPassive();
                is_any_box_active = true;
            }
            else if (act == 4)
            {
                txt_field_k.setActive();
                txt_field_l.setPassive();
                txt_field_g.setPassive();
                txt_field_m.setPassive();
                txt_field_phi.setPassive();
                is_any_box_active = true;
            }
            else if (act == 3)
            {
                txt_field_m.setActive();
                txt_field_l.setPassive();
                txt_field_g.setPassive();
                txt_field_k.setPassive();
                txt_field_phi.setPassive();
                is_any_box_active = true;
            }
            else if (act == 5)
            {
                txt_field_phi.setActive();
                txt_field_l.setPassive();
                txt_field_g.setPassive();
                txt_field_m.setPassive();
                txt_field_k.setPassive();
                is_any_box_active = true;
            }

        window.clear(Color::White);

        txt_field_l.displayBox(window);
        txt_field_g.displayBox(window);
        txt_field_m.displayBox(window);
        txt_field_k.displayBox(window);
        txt_field_phi.displayBox(window);

        window.draw(t1);
        window.draw(t2);
        window.draw(t3);
        window.draw(t4);
        window.draw(t5);
        window.draw(t6);

        window.display();

    }
    string str; txt_field_l.getText(str);
    if (atof(str.c_str())) cnst->l = atof(str.c_str());
    txt_field_g.getText(str);
    if (atof(str.c_str())) cnst->g = atof(str.c_str());
    txt_field_m.getText(str);
    if (atof(str.c_str())) cnst->m = atof(str.c_str());
    txt_field_k.getText(str);
    if (atof(str.c_str())) cnst->k = atof(str.c_str());

    txt_field_phi.getText(str);
    if (atof(str.c_str())) in->y = atof(str.c_str());

    cout << cnst->l<<endl<< cnst->g<<endl<< cnst->m<<endl<< cnst->k<<endl<< in->y<<endl;
    return;
}


