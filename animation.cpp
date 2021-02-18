#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "menu.cpp"
using namespace sf;
using namespace std;

class ball
{
    public:
        double x;
        double y;
        Sprite s;

        ball(Texture &image,double sc_x, double sc_y,double sx, double sy)
        {
            s.setTexture(image);
            s.setOrigin (int((sx)/2), int((sy/2)));
            s.setScale(sc_x,sc_y);
        }
};

struct Point
{
    double t;
    double x;
    double v;
};

void pause(RenderWindow & window,bool* restart)
{
    while (true)
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case(Event::Closed):
                    {window.close();*restart = false; return;};
                case(Event::KeyReleased):
                {
                if (event.key.code == Keyboard::Space) return ;
                if (event.key.code == Keyboard::Escape) {window.close(); return;};
                }
            }
        }
    }
}

void pyty (RenderTexture & path, int x , int y, int xpre, int ypre, bool draw_line)
{
    if(draw_line)
    {
        VertexArray line(Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[1].position = sf::Vector2f(xpre, ypre);
        line[0].color = sf::Color::Red;
        line[1].color = sf::Color::Red;

        path.draw(line);
        path.display();
    }

}

double Fx(double x, double y, double vx, double vy, Con c)
{
    return (c.l + x) * vy * vy - c.k * x / c.m + c.g * cos(y);
}

double Fy(double x, double y, double vx, double vy, Con c)
{
    return -(c.m * c.g * sin(y) + 2 * vx * vy) / (c.l + x);
}

int animation(bool* restart)
{
    cout.fixed;
    cout.precision(10);

//--------------------Загрузка шрифта для отображения текста------------------//
    Font font;
    if (!font.loadFromFile("Fonts/18341.ttf"))
    {
        return EXIT_FAILURE;
    }

//---------Переменные для контроля отрисовки------------//
    bool risovattshar = true;
    int discr = 40;
    float time_otris;
    int fps = 15;
    bool draw_line = true;
    int w = 2000; //---контроль рамера---//
    int win_x = 860;
    int win_y = 860;

//-------------------Текстуры для отрисовки-------------//
    Texture pod;
    pod.loadFromFile("images/podvass.png");

    RenderTexture path;
    path.create(960,960);
    double x_prev_for_path;
    double y_prev_for_path;

    Texture t;
    t.loadFromFile("images/ball.png");
    t.setSmooth(true);
    t.getSize();

    VertexArray line(Lines, 2); //----прототип линии----//

    Texture BackgroundTexture;
    BackgroundTexture.loadFromFile("images/background1.jpg");

    Text t_out;
    t_out.setString("If you want to close animation\n press Escape");
    t_out.setPosition(500,0);
    t_out.setFont(font);
    t_out.setCharacterSize(20);
    t_out.setFillColor(Color::Black);
    t_out.setStyle(Text::Bold);
//-------------Спрайты для отрисовки---------------//
    ball b(t,0.09,0.09,512,512);
    ball podv(pod,0.3,0.3,67,67);
    Sprite bg(BackgroundTexture);
    bg.setScale(0.7,0.7);

//------------Подвес-----------//
    podv.x = (int)win_x/2;
    podv.y = 100;//(int)win_y/2;

//------------Время----------------//
    Clock clock;
    Clock otr;
    float T = 0;
    int i1 = 0;//----счётчик итераций для контроля времени----//

//---------------------------Объявление переменных для численного расчёта-----------------------//

    double x, vx, y, vy, x_prev, vx_prev, y_prev, vy_prev;
    const double pi = 3.141592;
        Con cnst;
        cnst.l = 0.07;
        cnst.m = 0.1;
        cnst.g = 9.81;
        cnst.k = 40;
        PhaseSpace in; //initial conditions
        in.x = ((cnst.m*cnst.g)/cnst.k) - ((cnst.m*cnst.g)/cnst.k)/2;
        in.y = 0.0001;
        in.vx = 0;
        in.vy = 0;

        PhaseSpace k[5];
        double h = 0.0005;

        Point tempx, tempy;
        double c[] = {0, 0, 1.0 / 2, 1.0 / 2, 1}; //-------вектор с в классической схеме РК4----------
        k[0].x = 0;
        k[0].y = 0;
        k[0].vx = 0;
        k[0].vy = 0;

//-----------------------------Начало работы проги---------------------------
        if (!beginm(restart, &in ,&cnst)) return 0;

        if (cnst.m < 1) {cnst.m *= 10; cnst.k *= 10;};
        //w = (int) 6000*0.055/(cnst.l);
        in.x = ((cnst.m*cnst.g)/cnst.k) - ((cnst.m*cnst.g)/cnst.k)/2.5;
        Point x0, y0;
        x0.t = 0;
        x0.x = in.x;
        x0.v = in.vx;
        y0.t = 0;
        y0.x = in.y;
        y0.v = in.vy;

        x_prev = x0.x;
        vx_prev = x0.v;
        y_prev = y0.x;
        vy_prev = y0.v;

        x_prev_for_path = x_prev;
        y_prev_for_path = y_prev;

        RenderWindow window(VideoMode(win_x, win_y), "Elastic pendulum",Style::Titlebar);

//---------------------------Обработка окна-----------------------
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case(Event::Closed):
                    {window.close(); *restart = false; return 0;};
                case(Event::KeyReleased):
                {
                    if (event.key.code == Keyboard::Escape) window.close();
                    if (event.key.code == Keyboard::Space) pause(window,restart);
                    if (event.key.code == Keyboard::R) if (risovattshar == false) risovattshar = true; else risovattshar = false;
                    if (event.key.code == Keyboard::Delete) path.clear(Color(255,255,255,0));
                    if (event.key.code == Keyboard::O) if (draw_line) {draw_line = false;path.clear(Color(255,255,255,0));} else draw_line = true;
                }
            }
        }
//--------------------------------------Численный расчёт---------------------------------------
        float time = 0;
        clock.restart();

        for (int j = 1; j < 5; j++)
        {
            k[j].x = vx_prev + k[j - 1].vx * h * c[j];
            k[j].vx = Fx(x_prev + k[j - 1].x * h * c[j], y_prev + k[j - 1].y * h * c[j],
                            vx_prev + k[j - 1].vx * h * c[j], vy_prev + k[j - 1].vy * h * c[j], cnst);
            k[j].y = vy_prev + k[j - 1].vy * h * c[j];
            k[j].vy = Fy(x_prev + k[j - 1].x * h * c[j], y_prev + k[j - 1].y * h * c[j],
                            vx_prev + k[j - 1].vx * h * c[j], vy_prev + k[j - 1].vy * h * c[j], cnst);
        }
        x = x_prev + (k[1].x + 2 * k[2].x + 2 * k[3].x + k[4].x) * h / 6;
        y = y_prev + (k[1].y + 2 * k[2].y + 2 * k[3].y + k[4].y) * h / 6;
        vx = vx_prev + (k[1].vx + 2 * k[2].vx + 2 * k[3].vx + k[4].vx) * h / 6;
        vy = vy_prev + (k[1].vy + 2 * k[2].vy + 2 * k[3].vy + k[4].vy) * h / 6;

        time = clock.getElapsedTime().asSeconds();

        x_prev = x;
        y_prev = y;
        vx_prev = vx;
        vy_prev = vy;
//--------------------------Контроль времени (шаг должен совпадать со временем цикла)----------------------
        while (time < h)
        {
            time = clock.getElapsedTime().asSeconds();
            //cout <<"aaaaaaa"<<endl;
        }
//--------------------------------------Отрисовка---------------------------------------
        if (i1 % (discr) == 0)
        {
            otr.restart();

            window.clear(Color(255,255,255,255));

            b.x =podv.x+w*(cnst.l+x)*sin(y);
            b.y =podv.y+w*(cnst.l+x)*cos(y);

            pyty (path, b.x , b.y, podv.x+w*(cnst.l+x_prev_for_path)*sin(y_prev_for_path) , podv.y+w*(cnst.l+x_prev_for_path)*cos(y_prev_for_path), draw_line);

            Texture texture = path.getTexture();
            Sprite s(texture);

            //-----Line----

            line[0].position = sf::Vector2f(podv.x, podv.y);
            line[1].position = sf::Vector2f(b.x, b.y);
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;

            //--------------

            b.s.setPosition(b.x,b.y);
            podv.s.setPosition(podv.x,podv.y);

            window.draw(bg);
            if (draw_line) window.draw(s);
            window.draw(line);
            if (risovattshar) window.draw(b.s);
            window.draw(podv.s);
            window.draw(t_out);
            window.display();

            x_prev_for_path = x_prev;
            y_prev_for_path = y_prev;


            time_otris = otr.getElapsedTime().asSeconds();

            if (((int)((time_otris/h) + 0.5)) > fps || (fps > discr))
                fps = (int)((time_otris/h) + 0.5);
        }
//--------------------Счёт времени работы----------------------
        T = T+time;
        i1++;
    }

    cout<<"all time: \t\t\t\t" <<T <<" " << h*i1 <<endl << "amount if iterations: \t\t\t"<<i1 <<endl;
    return 0;
}

int main()
{
    bool restart = true;
    while (restart)
        animation(&restart);
    return 0;
}
