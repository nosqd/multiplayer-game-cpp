#include "CGame.hpp"

Game::CGame *Game::CGame::instance = nullptr;

Game::CGame::CGame()
{
    CGame::instance = this;
    this->left = new CPlayer(LEFT, true);
    this->right = new CPlayer(RIGHT, false);
    this->ball = new CBall();
    this->font = new sf::Font();
    if (!this->font->loadFromFile("res/font.ttf"))
    {
        std::cerr << "Failed to load default font from res/font.ttf\n";
        std::exit(1);
    }
    this->font->setSmooth(false);
    std::cout << "Successfully loaded default font from res/font.ttf (Family: " << this->font->getInfo().family << ")\n";
}
Game::CGame *Game::CGame::get()
{
    return CGame::instance;
}
void Game::CGame::Start()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game | Starting");
    sf::Clock deltaClock;
    this->window = &window;
    this->deltaClock = &deltaClock;
    if (!ImGui::SFML::Init(window))
        std::exit(1);

    this->window->setTitle(string_format("Game | DT: %f", 0.f));
    while (window.isOpen())
    {
        this->Loop();
    }
    ImGui::SFML::Shutdown();
}
void Game::CGame::Loop()
{
    sf::Time dt = this->deltaClock->restart();
    this->lastDt = dt;
    sf::Event event{};
    while (this->window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(*this->window, event);
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            Game::CInput::get()->HandleKeyEvent(event);
        }
        else if (event.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }

    this->Update(dt.asSeconds());
    this->window->setTitle("Game");

    ImGui::SFML::Update(*this->window, dt);
    this->DrawDebugInfo();

    this->Draw();
    ImGui::SFML::Render(*this->window);
    this->window->display();
}
void Game::CGame::Draw()
{
    this->window->clear(sf::Color::Black);
    this->left->Draw(this->window);
    this->right->Draw(this->window);
    this->ball->Draw(this->window);
    sf::Text scoreText;
    scoreText.setFont(*this->font);
    scoreText.setString(string_format("%d | %d", this->left->GetScore(), this->right->GetScore()));
    scoreText.setPosition(sf::Vector2f(1280.f / 2.f, 20.f) - sf::Vector2f(scoreText.getLocalBounds().width / 2.f, scoreText.getLocalBounds().height / 2.f));
    this->window->draw(scoreText);
}
void Game::CGame::Update(float dt)
{
    this->left->Update(dt);
    this->right->Update(dt);
    this->ball->Update(dt);
}
void Game::CGame::DrawDebugInfo()
{
    ImGui::Begin("Debug Info");
    ImGui::Text("FPS: %f (DT: %f)", 1.f / this->lastDt.asSeconds(), this->lastDt.asSeconds());
    ImGui::Separator();
    ImGui::Text("Left Player");
    ImGui::Text("> Side: %s, Position: %d", Game::PlayerSideToString(this->left->GetSide()).c_str(), (int)this->left->GetPosition());
    ImGui::Text("> Score: %d", this->left->GetScore());
    ImGui::Separator();
    ImGui::Text("Right Player");
    ImGui::Text("> Side: %s, Position: %d", Game::PlayerSideToString(this->right->GetSide()).c_str(), (int)this->right->GetPosition());
    ImGui::Text("> Score: %d", this->right->GetScore());
    ImGui::Separator();
    ImGui::Text("Ball");
    ImGui::Text("> Position: %f %f", this->ball->GetPosition().x, this->ball->GetPosition().y);
    ImGui::Text("> Velocity: %f %f", this->ball->GetVelocity().x, this->ball->GetVelocity().y);
    ImGui::End();
}
void Game::CGame::ResetPositions()
{
    this->left->ResetPosition();
    this->right->ResetPosition();
    this->ball->ResetPosition();
}