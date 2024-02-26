#include <cmath>
#include <array>
#include <vector>

#include "raylib-cpp.hpp"

#ifndef TILE_SIZE
    #define TILE_SIZE 64
#endif

struct Tile {
    const int xIndex, yIndex;
    const raylib::Rectangle boundingRect;
    const bool collidable;

    Tile(int index_x, int index_y, bool collidable = false) :
        xIndex(index_x), yIndex(index_y),
        boundingRect(index_x * TILE_SIZE, index_y * TILE_SIZE, TILE_SIZE, TILE_SIZE),
        collidable(collidable) {

    }
};

class Map {
private:
    std::vector<std::vector<Tile>> m_Tiles;

public:
    Map(const std::vector<std::vector<int>>& data) : m_Tiles(data.size()) {        
        for(int i = 0; i < data.size(); i++) {
            for(int j = 0; j < data.at(i).size(); j++) {
                switch(data.at(i).at(j)) {
                    case 0:
                        m_Tiles.at(i).push_back(Tile(j, i, false));
                        TraceLog(LOG_INFO, TextFormat("Created tile at index: %i, %i (data value: %i)", j, i, 0));
                        break;

                    case 1:
                        m_Tiles.at(i).push_back(Tile(j, i, true));
                        TraceLog(LOG_INFO, TextFormat("Created tile at index: %i, %i (data value: %i)", j, i, 1));
                        break;
                }
            }
        }
    }

    void Render() {
        for(const auto& i : m_Tiles) {
            for(const auto& j : i) {
                if(j.collidable) {
                    DrawRectangleLinesEx(j.boundingRect, 1.0f, GREEN);
                }
            }
        }
    }
};

class Golfball {
private:
    raylib::Vector2 m_Position;
    raylib::Vector2 m_Direction;
    float const m_Radius = 16.0f;
    float m_Velocity = 0.0f;

    bool m_Selected;

public:
    Golfball(raylib::Vector2 position) :
        m_Position(position),
        m_Direction(0.0f, 0.0f),
        m_Radius(16.0f),
        m_Velocity(0.0f),
        m_Selected(false) {
        
        }
    
    void Update() {
        Push();
        CollisionCheck();

        m_Velocity = Lerp(m_Velocity, 0.0f, 2.0f * GetFrameTime());
        m_Position += m_Direction * m_Velocity * GetFrameTime();
    }

    void Render() {
        DrawCircleV(m_Position, m_Radius, WHITE);

        if(m_Selected) {
            DrawLineEx(m_Position, m_Position + m_Direction * Vector2Distance(m_Position, GetMousePosition()), 1.0f, GREEN);
        }
    }

private:
    void Push() {
        if(CheckCollisionPointCircle(raylib::Mouse::GetPosition(), m_Position, m_Radius) && raylib::Mouse::IsButtonPressed(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) && m_Velocity <= 4.0f) {
            m_Selected = true;
        }

        if(raylib::Mouse::IsButtonDown(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) && m_Selected) {
            m_Direction.x = std::cos(atan2(raylib::Mouse::GetY() - m_Position.y, raylib::Mouse::GetX() - m_Position.x)) * -1;
            m_Direction.y = std::sin(atan2(raylib::Mouse::GetY() - m_Position.y, raylib::Mouse::GetX() - m_Position.x)) * -1;
        }

        if(raylib::Mouse::IsButtonReleased(MOUSE_BUTTON_LEFT) && m_Selected) {
            m_Velocity = Vector2Distance(GetMousePosition(), m_Position) * 4.0;
            m_Selected = false;
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

    std::vector<std::vector<int>> mapData {
        std::vector<int> { 0,0,0,0,0,0,0,0 },
        std::vector<int> { 0,1,0,0,0,0,1,0 },
        std::vector<int> { 0,1,0,0,0,0,1,0 },
        std::vector<int> { 0,1,0,0,0,0,1,0 },
        std::vector<int> { 0,1,0,0,0,0,1,0 },
        std::vector<int> { 0,1,0,0,0,0,1,0 },
        std::vector<int> { 0,1,0,0,0,0,1,0 },
        std::vector<int> { 0,0,0,0,0,0,0,0 },
    };
    
    Map map(mapData);

    while(!window.ShouldClose()) {
        golfball.Update();

        window.BeginDrawing().ClearBackground(BLACK);

        map.Render();
        golfball.Render();

        window.EndDrawing();
    }
}