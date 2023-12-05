// application.hpp

#pragma once

#include <fstream>
#include <string>
#include "batch.hpp"
#include "PlayerCharacter.h"
#include "Ball.h"
#include "Brick.h"
#include "AssetsManagment.h"
#include "ParallaxBackground.h"

namespace runner
{
   std::string intToString(int score);

   class Application final
   {
   public:
      Application() = default;

      void run();

   private:
      enum class GameState
      {
          win, lose, running, pregame
      };
      enum class TextureName
      {
          Texture_player, Texture_ball, Texture_brick  
      };
      bool enter();
      void exit() noexcept;
      void SetUp();
      bool update();
      void render();
      void CollisionCheck();
      void Restart();
   private:
      void on_mouse_move(const sf::Vector2f &position) noexcept;
      void on_key_pressed(const sf::Keyboard::Key key);
      void on_key_released(const sf::Keyboard::Key key) noexcept;
      void on_button_pressed(const sf::Mouse::Button button) noexcept;
      void on_button_released(const sf::Mouse::Button button) noexcept;
      void loadHighScore();
      void StoreHighScore();
      bool AxisAlignedBoundingBox(const sf::Sprite& box1, const sf::Sprite& box2);


   private:
      sf::RenderWindow m_window{};
      PrimitiveBatch   m_batch{};
      bool             m_running = true;
      sf::Clock        m_clock{};
      sf::Time         m_deltatime{};
      sf::Vector2f     m_mouse_position{};
      sf::Sprite       m_sprite{};
      PlayerCharacter  m_player;
      Ball             m_ball;
      Brick            m_brick;
      AssetsManagement m_AssetsManagement;
      GameState   m_CurrentGameState = GameState::pregame;
      parallaxBackground m_parallaxBackground;
      sf::Text m_startMainuText, m_WinText, m_LoseText, m_ScoreText, m_highScoreText;
      int m_highScoreInt = 0;
      int m_currentScore = 0;
      float m_minOfScreen = 0.0f;
      //Keep the state through enum instead of bool
     
   };
} // !runner
