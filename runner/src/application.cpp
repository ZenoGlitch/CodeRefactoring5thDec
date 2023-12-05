// application.cpp

#include "application.hpp"
#include <iostream>
namespace runner
{
    static const char* kPlayerID    = "player";
    static const char* kBallID      = "ball";
    static const char* kBrickID     = "brick";
    static const char* kFallingStarID = "fallingStar";

    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;
    constexpr sf::Uint32 flags = sf::Style::Titlebar | sf::Style::Close;

   void Application::run()
   {
      const sf::VideoMode mode{ screenWidth, screenHeight };
      m_window.create(mode, "pineapple", flags);
      if (!m_window.isOpen() || !enter()) {
         return;
      }

      m_window.setKeyRepeatEnabled(false);
      
      while (m_window.isOpen()) {
         sf::Event event;
         
         while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::MouseMoved) {
               on_mouse_move({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) });
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
               on_button_pressed(event.mouseButton.button);
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
               on_button_released(event.mouseButton.button);
            } 
            else if (event.type == sf::Event::KeyPressed) {
               on_key_pressed(event.key.code);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
               on_key_released(event.key.code);
            }
            else if (event.type == sf::Event::Closed) {
               m_window.close();
            }
         }
         
         if (!update()) {
            m_window.close();
         }

         render();
      }

      exit();
   }

   bool Application::enter()
   {
      SetUp();
      return true;
   }

   void Application::exit() noexcept
   {
   }

   void Application::SetUp()
   {
       m_AssetsManagement.LoadTexture(kPlayerID, "assets/player.png");
       m_AssetsManagement.LoadTexture(kBallID, "assets/Ball.png");
       m_AssetsManagement.LoadTexture(kBrickID, "assets/WhiteHitBrick.png");
       m_AssetsManagement.LoadTexture(kFallingStarID, "assets/FallingStar.png");
       m_AssetsManagement.LoadFontFile("assets/sunny-spells-font/SunnyspellsRegular-MV9ze.otf");
       
       // Made simple that function that just set indivual each sf::Text variable for text in the screen
       m_startMainuText = m_AssetsManagement.SetText("Press `space´ to start", 100, sf::Text::Bold, 250, 250);
       m_WinText = m_AssetsManagement.SetText("Winner", 50, sf::Text::Bold, 550, 300);
       m_LoseText = m_AssetsManagement.SetText("Game Over", 50, sf::Text::Bold, 550, 300);
       m_ScoreText = m_AssetsManagement.SetText("Score", 50, sf::Text::Bold, 1100, 5);
       m_highScoreText = m_AssetsManagement.SetText("", 50, sf::Text::Bold, 0, 5);
      
       
       m_currentScore = 0;
       m_highScoreInt = 0;
       m_minOfScreen = 0.0f;
       loadHighScore();
       
       m_player.SetUp(m_AssetsManagement.GetTexture(kPlayerID), m_minOfScreen, static_cast<float>(m_window.getSize().x));
       m_ball.SetUp(*m_AssetsManagement.GetTexture(kBallID), m_window.getSize().x, m_window.getSize().y, static_cast<int>(m_minOfScreen), static_cast<int>(m_minOfScreen));
       m_brick.SetUp(m_AssetsManagement.GetTexture(kBrickID));
       m_parallaxBackground.SetUp(m_AssetsManagement.GetTexture(kFallingStarID));
   }

   bool Application::update()
   {
      m_deltatime = m_clock.restart();
      if(m_CurrentGameState == GameState::running)
      {
        m_parallaxBackground.Update(m_deltatime.asSeconds());
        m_ScoreText.setString("Score: " + intToString(m_currentScore));
        m_player.PlayerUpdate(m_deltatime.asSeconds());
        m_ball.BallUpdate(m_deltatime.asSeconds());
        CollisionCheck();
      } 
      else
      {
          m_highScoreText.setString("HighScore: " + intToString(m_highScoreInt));
      }
      
      if(m_brick.m_brickObject.empty())
      {
        //win
          m_CurrentGameState = GameState::win;
      }

      return m_running;
   }

   void Application::render()
   {
      m_batch.clear();
      {}
      m_window.clear(sf::Color{ 0x44, 0x55, 0x66, 0xff });

      if(m_CurrentGameState == GameState::pregame)
      {
          m_window.draw(m_startMainuText);
      }

      if(m_CurrentGameState == GameState::running)
      {
        for (auto& yellowStar : m_parallaxBackground.m_fallingStarYellow)
        {
            m_window.draw(yellowStar.sprite);
        }

        for (auto& redStar : m_parallaxBackground.m_fallingStarRed)
        {
            m_window.draw(redStar.sprite);
        }

        m_window.draw(m_ScoreText);
        m_window.draw(m_player.m_playerSprite);
        m_window.draw(m_ball.m_ballSprite);

        for (auto& brick : m_brick.m_brickObject)
        {
            m_window.draw(brick.sprite);
        }
      }

      if(m_CurrentGameState == GameState::lose)
      {
        m_window.draw(m_LoseText);
        StoreHighScore();
      }
      
      if(m_CurrentGameState == GameState::win)
      {
          m_window.draw(m_WinText);
          StoreHighScore();
      }

      m_window.draw(m_highScoreText);

      m_batch.present(m_window);
      m_window.display();
   }

   void Application::on_mouse_move(const sf::Vector2f &position) noexcept
   {
      m_mouse_position = position;
   }

   void Application::on_key_pressed(const sf::Keyboard::Key key)
   {
      if (key == sf::Keyboard::Key::Escape) {
         m_running = false;
      }
      if(key == sf::Keyboard::Key::Left)
      {
          m_player.pressedLeft = true;
      } else
      {
          m_player.pressedLeft = false;
      }
      
      if(key == sf::Keyboard::Right)
      {
          m_player.pressedRight = true;
      }
      else
      {
          m_player.pressedRight = false;
      }

      if(m_CurrentGameState == GameState::pregame)
      {
          if (key == sf::Keyboard::Key::Space) {
              m_CurrentGameState = GameState::running;
          }
      }

      if(m_CurrentGameState == GameState::lose || m_CurrentGameState == GameState::win)
      {
          if (key == sf::Keyboard::Key::Space) {
              m_CurrentGameState = GameState::running;
              Restart();
          }
      }
   }

   void Application::on_key_released(const sf::Keyboard::Key key) noexcept
   {
       if (key == sf::Keyboard::Right)
       {
           m_player.pressedRight = false;
       }
       if (key == sf::Keyboard::Key::Left)
       {
           m_player.pressedLeft = false;
       }  
   }

   void Application::on_button_pressed(const  sf::Mouse::Button button) noexcept
   {

   }

   void Application::on_button_released(const sf::Mouse::Button button) noexcept
   {
   
   }

   

   void Application::Restart()
   {
       m_currentScore = 0;
       m_ball.Restart();
       m_player.Restart();
       m_brick.Restart();
   }

   void Application::CollisionCheck()
   {
       const float r1RightEdge = m_player.m_playerSprite.getPosition().y + m_player.m_playerSprite.getTexture()->getSize().y;
       if (r1RightEdge >= m_ball.m_ballSprite.getPosition().y)
       {
           std::cout << " right side someting" << std::endl;
       };
       if (AxisAlignedBoundingBox(m_player.m_playerSprite, m_ball.m_ballSprite))
       {
           
           m_ball.hasCollided = true;
           m_ball.m_direction.y = -m_ball.m_direction.y;
           //std::cout << "hitted a player" << std::endl;
       }

       for (int i = 0; i < m_brick.m_brickObject.size(); i++)
       {
           if (AxisAlignedBoundingBox(m_brick.m_brickObject.at(i).sprite, m_ball.m_ballSprite))
           {
               m_ball.m_direction.y = -m_ball.m_direction.y;
               m_ball.m_speed += 10.0f;
               m_brick.m_brickObject.erase(m_brick.m_brickObject.begin() + i);
               m_currentScore++;
               //std::cout << "hitted a brick" << std::endl;
           }
       }
       for (int i = 0; i < m_parallaxBackground.m_fallingStarYellow.size(); i++)
       {
           if(m_parallaxBackground.m_fallingStarYellow.at(i).positionY >= m_window.getSize().y)
           {
               m_parallaxBackground.m_fallingStarYellow.at(i).positionY = -100;
           }
       }
       for (int i = 0; i < m_parallaxBackground.m_fallingStarRed.size(); i++)
       {
           if (m_parallaxBackground.m_fallingStarRed.at(i).positionY >= m_window.getSize().y)
           {
               m_parallaxBackground.m_fallingStarRed.at(i).positionY = -100;
           }
       }
       // If the player is out of bounds or edge of the bottom screen that should give trigger fail condition.
       if(m_ball.m_ballSprite.getPosition().y >= m_window.getSize().y)
       {
           m_CurrentGameState = GameState::lose;
           //std::cout << "lose" << std::endl;
       }
   }

   void Application::loadHighScore()
   {
              std::ifstream readFile;
       readFile.open("assets/HighScore.txt");
       if (readFile.is_open())
       {
           while (!readFile.eof())
           {
               readFile >> m_highScoreInt;
           }

       }
       readFile.close();
   };

   void Application::StoreHighScore()
   {

       std::ofstream writeFile("assets/HighScore.txt");
       if (writeFile.is_open())
       {
           if (m_currentScore > m_highScoreInt)
           {
               m_highScoreInt = m_currentScore;
           }
           writeFile << m_highScoreInt;
       }
       writeFile.close();
   }

   std::string runner::intToString(int score)
   {
       std::string string = std::to_string(score);
       return string;
   }

   bool Application::AxisAlignedBoundingBox(const sf::Sprite& box1, const sf::Sprite& box2)
   {
       const bool collisionX = box1.getPosition().x + box1.getTexture()->getSize().x >= box2.getPosition().x &&
           box2.getPosition().x + box2.getTexture()->getSize().x >= box1.getPosition().x;

       const bool collisionY = box1.getPosition().y + box1.getTexture()->getSize().y >= box2.getPosition().y &&
           box2.getPosition().y + box2.getTexture()->getSize().y >= box1.getPosition().y;
       return collisionX && collisionY;
   }
} // !runner
