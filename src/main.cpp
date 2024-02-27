#include <cmath>
#include <array>
#include <vector>

#include "raylib-cpp.hpp"

#ifndef TILE_SIZE
    #define TILE_SIZE 48
#endif

struct Tile {
    const int xIndex, yIndex;
    const raylib::Rectangle rect;
    const bool collidable;

    Tile(int index_x, int index_y, bool collidable) :
        xIndex(index_x), yIndex(index_y),
        rect(index_x * TILE_SIZE, index_y * TILE_SIZE, TILE_SIZE, TILE_SIZE),
        collidable(collidable) { }
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
                        break;

                    case 1:
                        m_Tiles.at(i).push_back(Tile(j, i, true));
                        break;
                }
            }
        }
    }

    void Render() {
        for(const auto& i : m_Tiles) {
            for(const auto& j : i) {
                if(j.collidable) {
                    DrawRectangleLinesEx(j.rect, 1.0f, GREEN);
                }
            }
        }
    }

    raylib::Vector2 GetPositionToIndex(raylib::Vector2 position) {
        int x = std::floor(position.x / TILE_SIZE);
        int y = std::floor(position.y / TILE_SIZE);

        return raylib::Vector2(x, y);
    }

    const int GetWidth() { return m_Tiles.at(0).size(); }
    const int GetHeight() { return m_Tiles.size(); }

    const std::vector<std::vector<Tile>>& GetData() { return m_Tiles; }
    const Tile& GetTile(int x, int y) { return m_Tiles.at(y).at(x); }
};

class Golfball {
private:
    raylib::Vector2 m_Position;
    raylib::Vector2 m_DragDirrection;
    raylib::Vector2 m_Direction;

    float const m_Radius;
    float m_Velocity;

    bool m_Selected;

public:
    Golfball(raylib::Vector2 position) :
        m_Position(position),
        m_DragDirrection(0.0f, 0.0f),
        m_Direction(0.0f, 0.0f),
        m_Radius(16.0f),
        m_Velocity(0.0f),
        m_Selected(false) { }
    
    void Update() {
        Push();

        m_Velocity = Lerp(m_Velocity, 0.0f, 2.0f * GetFrameTime());
        m_Position = Vector2Lerp(m_Position, m_Position + m_Direction * m_Velocity, GetFrameTime());
    }

    void Render() {
        DrawCircleLinesV(m_Position, m_Radius, GREEN);

        if(m_Selected) {
            DrawLineEx(m_Position, m_Position + m_DragDirrection * Vector2Distance(m_Position, GetMousePosition()), 1.0f, GREEN);
        }
    }

    void CollisionCheck(Map& map) {
        for(int y = -1; y <= 1; y++) {
            for(int x = -1; x <= 1; x++) {
                if(x == 0 && y == 0) {
                    continue;
                }

                const Tile& tile = map.GetTile(map.GetPositionToIndex(m_Position).x + x, map.GetPositionToIndex(m_Position).y + y);

                if(CheckCollisionCircleRec(m_Position, m_Radius, tile.rect)) {
                    Bounce(tile);
                }
            }
        }
    }

private:
    void Push() {
        if(CheckCollisionPointCircle(raylib::Mouse::GetPosition(), m_Position, m_Radius) && raylib::Mouse::IsButtonPressed(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))) {
            m_Selected = true;
        }

        if(raylib::Mouse::IsButtonDown(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) && m_Selected) {
            m_DragDirrection.x = std::cos(atan2(raylib::Mouse::GetY() - m_Position.y, raylib::Mouse::GetX() - m_Position.x)) * -1;
            m_DragDirrection.y = std::sin(atan2(raylib::Mouse::GetY() - m_Position.y, raylib::Mouse::GetX() - m_Position.x)) * -1;
        }

        if(raylib::Mouse::IsButtonReleased(MOUSE_BUTTON_LEFT) && m_Selected) {
            m_Direction = m_DragDirrection;
            m_Velocity = Clamp(Vector2Distance(GetMousePosition(), m_Position), -256, 256) * 4.0;
            m_Selected = false;
        }
    }

    void Bounce(const Tile& tile) {
        raylib::Rectangle rect = tile.rect;

        bool collisionUp = CheckCollisionPointLine(m_Position, raylib::Vector2(rect.x, rect.y), raylib::Vector2(rect.x + rect.width, rect.y), m_Radius) && tile.collidable;
        bool collisionDown = CheckCollisionPointLine(m_Position, raylib::Vector2(rect.x, rect.y + rect.height), raylib::Vector2(rect.x + rect.width, rect.y + rect.height), m_Radius) && tile.collidable;

        bool collisionLeft = CheckCollisionPointLine(m_Position, raylib::Vector2(rect.x, rect.y), raylib::Vector2(rect.x, rect.y + rect.height), m_Radius) && tile.collidable;
        bool collisionRight = CheckCollisionPointLine(m_Position, raylib::Vector2(rect.x + rect.width, rect.y), raylib::Vector2(rect.x + rect.width, rect.y + rect.height), m_Radius) && tile.collidable;

        if(collisionLeft || collisionRight) {
            if(collisionLeft) {
                m_Position.x = rect.x - m_Radius;
            }

            else if(collisionRight) {
                m_Position.x = rect.x + rect.width + m_Radius;
            }

            m_Direction.x *= -1;
        }

        if(collisionUp || collisionDown) {
            if(collisionUp) {
                m_Position.y = rect.y - m_Radius;
            }

            else if(collisionDown) {
                m_Position.y = rect.y + rect.height + m_Radius;
            }

            m_Direction.y *= -1;
        }    
    }
};

int main() {
    raylib::Window window(786, 786, TextFormat("Raylib %s - Golf Game %s", RAYLIB_VERSION, "1.0.0"), FLAG_VSYNC_HINT);
    raylib::AudioDevice audio;

    Golfball golfball(raylib::Vector2(GetScreenWidth() / 2, GetScreenHeight() / 2));

    std::vector<std::vector<int>> mapData {
        std::vector<int> { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1},
        std::vector<int> { 1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
        std::vector<int> { 1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,1},
        std::vector<int> { 1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1},
        std::vector<int> { 1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        std::vector<int> { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    Map map(mapData);

    while(!window.ShouldClose()) {
        golfball.Update();
        golfball.CollisionCheck(map);

        window.BeginDrawing().ClearBackground(BLACK);

        map.Render();
        golfball.Render();

        window.EndDrawing();
    }
}
