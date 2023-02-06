#include <SFML/Graphics.hpp>
#include <string>
sf::Font GlobalFont;
int match = 0; //which match in a row
int player1_points = 0;
int player2_points = 0;
char name[9] = "";
char second_name[9] = "";
bool first = true; //first movement of the match

void Welcome_Game(sf::RenderWindow &W);
//Check the winner
int Check(int tab[])
{
    if(tab[0] != 2 && tab[0] == tab[1] && tab[1] == tab[2])
        return tab[0];
    else if(tab[3] != 2 && tab[3] == tab[4] && tab[4] == tab[5])
        return tab[3];
    else if(tab[6] != 2 && tab[6] == tab[7] && tab[7] == tab[8])
        return tab[6];
    else if(tab[0] != 2 && tab[0] == tab[3] && tab[3] == tab[6])
        return tab[0];
    else if(tab[1] != 2 && tab[1] == tab[4] && tab[4] == tab[7])
        return tab[1];
    else if(tab[2] != 2 && tab[2] == tab[5] && tab[5] == tab[8])
        return tab[2];
    else if(tab[0] != 2 && tab[0] == tab[4] && tab[4] == tab[8])
        return tab[0];
    else if(tab[2] != 2 && tab[2] == tab[4] && tab[4] == tab[6])
        return tab[2];
    else
        return 2;
}
//input first name
void first_player(sf::RenderWindow &W, sf::RectangleShape input1, sf::Text show_name)
{

            static int name1_length = 0;
                while(true)
                {
                    sf::Event e;
                    if(e.type == sf::Event::Closed)
                        W.close();


                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && name1_length < 8)
                    {
                        name[name1_length] = 'Q';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && name1_length < 8)
                    {
                        name[name1_length] = 'W';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && name1_length < 8)
                    {
                        name[name1_length] = 'E';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && name1_length < 8)
                    {
                        name[name1_length] = 'R';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::T) && name1_length < 8)
                    {
                        name[name1_length] = 'T';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && name1_length < 8)
                    {
                        name[name1_length] = 'Y';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::U) && name1_length < 8)
                    {
                        name[name1_length] = 'U';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I) && name1_length < 8)
                    {
                        name[name1_length] = 'I';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::O) && name1_length < 8)
                    {
                        name[name1_length] = 'O';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && name1_length < 8)
                    {
                        name[name1_length] = 'P';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    /////////////////////////////////////////////////
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && name1_length < 8)
                    {
                        name[name1_length] = 'A';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && name1_length < 8)
                    {
                        name[name1_length] = 'S';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && name1_length < 8)
                    {
                        name[name1_length] = 'D';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && name1_length < 8)
                    {
                        name[name1_length] = 'F';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G) && name1_length < 8)
                    {
                        name[name1_length] = 'G';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::H) && name1_length < 8)
                    {
                        name[name1_length] = 'H';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J) && name1_length < 8)
                    {
                        name[name1_length] = 'J';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::K) && name1_length < 8)
                    {
                        name[name1_length] = 'K';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L) && name1_length < 8)
                    {
                        name[name1_length] = 'L';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && name1_length < 8)
                    {
                        name[name1_length] = 'Z';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) && name1_length < 8)
                    {
                        name[name1_length] = 'X';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) && name1_length < 8)
                    {
                        name[name1_length] = 'C';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::V) && name1_length < 8)
                    {
                        name[name1_length] = 'V';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::B) && name1_length < 8)
                    {
                        name[name1_length] = 'B';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::N) && name1_length < 8)
                    {
                        name[name1_length] = 'N';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) && name1_length < 8)
                    {
                        name[name1_length] = 'M';
                        sf::sleep(sf::milliseconds(100));
                        name1_length++;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && name1_length >= 1)
                    {
                        name1_length--;
                        sf::sleep(sf::milliseconds(100));
                        name[name1_length] = ' ';
                    }
                    if(!(sf::Mouse::getPosition(W).x > 300 && sf::Mouse::getPosition(W).x < 500 && sf::Mouse::getPosition(W).y > 150 && sf::Mouse::getPosition(W).y < 190) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                       input1.setOutlineThickness(0);
                       break;
                    }



                    show_name.setString(name);
                    W.draw(input1);
                    W.draw(show_name);
                    W.display();
                }
}
