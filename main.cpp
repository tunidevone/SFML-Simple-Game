#include <SFML/Graphics.hpp>

void initShape(sf::RectangleShape& shape, sf::Vector2f const &pos, sf::Color const &color);

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animation", sf::Style::Default, settings);

    bool isMovingRight{false}, isMovingLeft{false}, isMovingUp{false}, isMovingDown{false};

    sf::Vector2f start_pos = sf::Vector2f(50.f, 50.f);

    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    initShape(player, start_pos, sf::Color::White);

    sf::RectangleShape target(sf::Vector2f(50.f, 50.f));
    initShape(target, sf::Vector2f(750.f, 300.f), sf::Color::Green);

    sf::RectangleShape barrier(sf::Vector2f(30.f, 150.f));
    initShape(barrier, sf::Vector2f(400.f, 75.f), sf::Color::Red);

    float barrier_speed = 3.5f;
    sf::Vector2f barrier_size = barrier.getSize();
    sf::Vector2u win_size = window.getSize();

    sf::Clock clock;
    sf::Time elapsed_time = sf::Time::Zero;
    sf::Time frame_time = sf::seconds(1.f / 60.f);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    if (event.key.code == sf::Keyboard::Right)
                        isMovingRight = true;
                    if (event.key.code == sf::Keyboard::Left)
                        isMovingLeft = true;
                    if (event.key.code == sf::Keyboard::Up)
                        isMovingUp = true;
                    if (event.key.code == sf::Keyboard::Down)
                        isMovingDown = true;
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Right)
                        isMovingRight = false;
                    if (event.key.code == sf::Keyboard::Left)
                        isMovingLeft = false;
                    if (event.key.code == sf::Keyboard::Up)
                        isMovingUp = false;
                    if (event.key.code == sf::Keyboard::Down)
                        isMovingDown = false;
                    break;
                default:
                    break;
            }
        }

        sf::Vector2f barrier_pos = barrier.getPosition();
        if(barrier_pos.y < barrier_size.y / 2)
        {
            barrier_speed = abs(barrier_speed);
        }
        else if (barrier_pos.y > win_size.y - barrier_size.y / 2)
        {
            barrier_speed = -abs(barrier_speed);
        }

        elapsed_time += clock.restart();
        while (elapsed_time > frame_time)
        {
            barrier.move(0.f, barrier_speed);

            if (isMovingRight)
                player.move(sf::Vector2f(1.f, 0.f));
            if (isMovingLeft)
                player.move(sf::Vector2f(-1.f, 0.f));
            if (isMovingUp)
                player.move(sf::Vector2f(0.f, -1.f));
            if (isMovingDown)
                player.move(sf::Vector2f(0.f, 1.f));

            elapsed_time -= frame_time;
        }

        if (player.getGlobalBounds().intersects(target.getGlobalBounds()))
            player.setPosition(start_pos);
        else if (player.getGlobalBounds().intersects(barrier.getGlobalBounds()))
            window.close();

        window.clear();
        window.draw(target);
        window.draw(barrier);
        window.draw(player);
        window.display();
    }

    return 0;
}

void initShape(sf::RectangleShape& shape, sf::Vector2f const &pos, sf::Color const &color)
{
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setOrigin(shape.getSize() * 0.5f);
}