#include <cmath>
#include <array>

#include "raylib-cpp.hpp"

template<int W, int H>
using Map = std::array<std::array<char, W + 1>, H>;

class Golfball {
private:
    raylib::Vector2 m_Position;
    raylib::Vector2 m_Direction;
    float const m_Radius = 16.0f;
    float m_Velocity = 0.0f;

public:
    Golfball(raylib::Vector2 position) :
        m_Position(position),
        m_Direction(0.0f, 0.0f),
        m_Radius(16.0f),
        m_Velocity(0.0f) {
        
        }
    
    void Update() {
        Push();
        CollisionCheck();

        m_Velocity = Lerp(m_Velocity, 0.0f, 2.0f * GetFrameTime());

        m_Position += m_Direction * m_Velocity * GetFrameTime();
    }

    void Render() {
        DrawCircleV(m_Position, m_Radius, WHITE);
        DrawCircleLinesV(m_Position, m_Radius, BLACK);
    }

private:
    void Push() {
        if(raylib::Mouse::IsButtonDown(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) && m_Velocity <= 2.0f) {
            m_Direction.x = std::cos(atan2(raylib::Mouse::GetY() - m_Position.y, raylib::Mouse::GetX() - m_Position.x)) * -1;
            m_Direction.y = std::sin(atan2(raylib::Mouse::GetY() - m_Position.y, raylib::Mouse::GetX() - m_Position.x)) * -1;
        }

        if(raylib::Mouse::IsButtonReleased(MOUSE_BUTTON_LEFT) && m_Velocity <= 2.0f) {
               m_Velocity = Vector2Distance(GetMousePosition(), m_Position) * 4.0;
        }
    }

    void CollisionCheck() {
        if(m_Position.x - m_Radius <= 0 || m_Position.x + m_Radius >= GetScreenWidth()) {
            BounceHorizontal(0, GetScreenWidth());
        }

        if(m_Position.y - m_Radius <= 0 || m_Position.y + m_Radius >= GetScreenHeight()) {
            BounceVertical(0, GetScreenHeight());
        } 
    }

    void BounceHorizontal(int bound_left, int bound_right) {
        if(m_Position.x - m_Radius < bound_left - m_Radius * 2) {
            m_Position.x = bound_left + m_Radius * 2;
        }

        else if(m_Position.x + m_Radius > bound_right + m_Radius * 2) {
            m_Position.x = bound_right - m_Radius * 2;
        }

        m_Direction.x *= -1;
    }

    void BounceVertical(int bound_up, int bound_down) {
        if(m_Position.y - m_Radius < bound_up - m_Radius * 2) {
            m_Position.y = bound_up + m_Radius * 2;
        }

        else if(m_Position.y + m_Radius > bound_down + m_Radius * 2) {
            m_Position.y = bound_down - m_Radius * 2;
        }

        m_Direction.y *= -1;
    }
};

int main() {
    raylib::Window window(786, 786, TextFormat("Raylib %s - Golf Game %s", RAYLIB_VERSION, "1.0.0"), FLAG_VSYNC_HINT);
    raylib::AudioDevice audio;

    Golfball golfball(raylib::Vector2(GetScreenWidth() / 2, GetScreenHeight() / 2));

    Map<16, 16> map = {
        "################",
        "#              #",
        "# #            #",
        "#          #   #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#              #",
        "#  #           #",
        "#            # #",
        "#              #",
        "################"
    };

    int map_cell_size = 48;

    while(!window.ShouldClose()) {
        golfball.Update();

        window.BeginDrawing().ClearBackground(BLACK);

        for(int i = 0; i < map.size(); i++) {
            for(int j = 0; j < map.at(0).size(); j++) {
                if(map[i][j] == '#') {
                    DrawRectangle(i * map_cell_size, j * map_cell_size, map_cell_size, map_cell_size, WHITE);
                }
            }
        }

        golfball.Render();

        window.EndDrawing();
    }
}