#pragma once

#include "components/simple_scene.h"

namespace classes
{

    class Star
    {
    private:
        const std::string& name;
        glm::vec3 center;
        float length;
        glm::vec3 color;
        bool fill;
        int layer;

    public:
        Star(const std::string& name, glm::vec3 reper, float length, glm::vec3 color, bool fill, int layer)
            : name(name), center(reper), length(length), color(color), fill(fill), layer(layer)
        {
        }

        const std::string& getName() const
        {
            return name;
        }
        glm::vec3 getColor()
        {
            return color;
        }
        bool isFilled()
        {
            return fill;
        }

        Mesh* Create()
        {
            std::vector<VertexFormat> vertices =
            {
                VertexFormat(center, color), // 0
                VertexFormat(center + glm::vec3(0, 2.5 * length, layer), color), // 1
                VertexFormat(center + glm::vec3(0, -length, layer), color), // 2
                VertexFormat(center + glm::vec3(-2.4 * length, 0.75 * length, layer), color), // 3
                VertexFormat(center + glm::vec3(2.4 * length, 0.75 * length, layer), color), // 4
                VertexFormat(center + glm::vec3(-1.5 * length, -2 * length, layer), color), // 5
                VertexFormat(center + glm::vec3(1.5 * length, -2 * length, layer), color) // 6
            };


            Mesh* star = new Mesh(name);
            std::vector<unsigned int> indices =
            {
                1, 5, 2,
                1, 2, 6,
                2, 4, 3
            };

            if (!fill) {
                star->SetDrawMode(GL_LINE_LOOP);
            }

            star->InitFromData(vertices, indices);
            return star;
        }

    };

    class Turret
    {
    private:
        const std::string& name;
        glm::vec3 center;
        float length;
        glm::vec3 color;
        bool fill;

    public:
        Turret(const std::string& name, glm::vec3 reper, float length, glm::vec3 color, bool fill)
            : name(name), center(reper), length(length), color(color), fill(fill)
        {
        }

        const std::string& getName() const
        {
            return name;
        }
        glm::vec3 getColor()
        {
            return color;
        }
        bool isFilled()
        {
            return fill;
        }

        Mesh* Create()
        {
            glm::vec3 corner = center;

            std::vector<VertexFormat> vertices =
            {
                VertexFormat(corner + glm::vec3(0, 0, 1), color), //0
                VertexFormat(corner + glm::vec3(-2 * length, 0, 1), color), //1
                VertexFormat(corner + glm::vec3(-length, 2 * length, 1), color), //2
                VertexFormat(corner + glm::vec3(-length, 2 * -length, 1), color), //3
                VertexFormat(corner + glm::vec3(-0.4 * length, length / 2, 1), color), //4
                VertexFormat(corner + glm::vec3(-0.4 * length, -length / 2, 1), color), //5
                VertexFormat(corner + glm::vec3(0, -length / 2, 1), color), //6
                VertexFormat(corner + glm::vec3(0, length / 2, 1), color), //7
                VertexFormat(corner + glm::vec3(1.6 * length, length / 2, 1), color), //8
                VertexFormat(corner + glm::vec3(1.6 * length, -length / 2, 1), color), //9
            };


            Mesh* turret = new Mesh(name);
            std::vector<unsigned int> indices =
            {
                0, 1, 2,
                0, 3, 1,
                0, 4, 7,
                0, 6, 5,
                6, 7, 8,
                6, 8, 9
            };

            if (!fill) {
                turret->SetDrawMode(GL_LINE_LOOP);
            }

            turret->InitFromData(vertices, indices);
            return turret;
        }
    };

    class DragTurret
    {
    private:
        std::string name;
        glm::vec2 coord;

    public:
        DragTurret(){}

        DragTurret(const std::string& turretName, const glm::vec2& coordinates) : name(turretName), coord(coordinates) {}

        std::string getName() const {
            return name;
        }

        glm::vec2 getCoordinates() const {
            return coord;
        }

        void setName(const std::string& turretName) {
            name = turretName;
        }

        void setCoordinates(glm::vec2 coordinates) {
            coord = coordinates;
        }
    };

    class Bullet
    {
    private:
        float translate;
        float radians = 0;
        glm::vec2 coord = glm::vec2(0, 0);
        std::string color;
        int line = -1;


    public:
        Bullet(float translate, std::string color, int line)
            : translate(translate), color(color), line(line)
        {

        }

        float getTranslate()
        {
            return translate;
        }
        void setTranslate(float t)
        {
            translate = t;
        }
        void setRadians(float rad)
        {
            radians = rad;
        }
        float getRadians()
        {
            return radians;
        }
        void setCoord(glm::vec2 xy)
        {
            coord = xy;
        }
        glm::vec2 getCoord()
        {
            return coord;
        }
        std::string getColor()
        {
            return color;
        }
        void setLine(int i)
        {
            line = i;
        }
        int getLine()
        {
            return line;
        }

    };

    class Enemy
    {
    private:
        const std::string& name;
        glm::vec3 center;
        float length;
        glm::vec3 color;
        bool fill;

    public:
        Enemy(const std::string& name, glm::vec3 reper, float length, glm::vec3 color, bool fill)
            : name(name), center(reper), length(length), color(color), fill(fill)
        {
        }

        const std::string& getName() const
        {
            return name;
        }
        glm::vec3 getColor()
        {
            return color;
        }
        bool isFilled()
        {
            return fill;
        }

        Mesh* Create()
        {
            glm::vec3 corner = center;

            std::vector<VertexFormat> vertices =
            {
                VertexFormat(corner + glm::vec3(0, 0, 1), glm::vec3(0, 0.812f, 0.639f)), //0
                VertexFormat(corner + glm::vec3(-0.6 * length, 1.1 * length, 1), glm::vec3(0, 0.651f, 0.514f)), //1
                VertexFormat(corner + glm::vec3(0.6 * length, 1.1 * length, 1), glm::vec3(0, 0.651f, 0.514f)), //2
                VertexFormat(corner + glm::vec3(1.25 * length, 0, 1), glm::vec3(0, 0.651f, 0.514f)), //3
                VertexFormat(corner + glm::vec3(0.6 * length, -1.1 * length, 1), glm::vec3(0, 0.651f, 0.514f)), //4
                VertexFormat(corner + glm::vec3(-0.6 * length, -1.1 * length, 1), glm::vec3(0, 0.651f, 0.514f)), //5
                VertexFormat(corner + glm::vec3(-1.25 * length, 0, 1), glm::vec3(0, 0.651f, 0.514f)), //6

                VertexFormat(corner + glm::vec3(-1.2 * length, 2.2 * length, 1), color), //7
                VertexFormat(corner + glm::vec3(1.2 * length, 2.2 * length, 1), color), //8
                VertexFormat(corner + glm::vec3(2.5 * length, 0, 1), color), //9
                VertexFormat(corner + glm::vec3(1.2 * length, -2.2 * length, 1), color), //10
                VertexFormat(corner + glm::vec3(-1.2 * length, -2.2 * length, 1), color), //11
                VertexFormat(corner + glm::vec3(-2.5 * length, 0, 1), color) //12
            };


            Mesh* enemy = new Mesh(name);
            std::vector<unsigned int> indices =
            {
                0, 2, 1,
                0, 3, 2,
                0, 4, 3,
                0, 5, 4,
                0, 6, 5,
                0, 1, 6,
                0, 8, 7,
                0, 9, 8,
                0, 10, 9,
                0, 11, 10,
                0, 12, 11,
                0, 7, 12
            };

            if (!fill) {
                enemy->SetDrawMode(GL_LINE_LOOP);
            }

            enemy->InitFromData(vertices, indices);
            return enemy;
        }
    };

    class Base
    {
    private:
        const std::string& name;
        glm::vec3 center;
        float length;
        glm::vec3 color;
        bool fill;

    public:
        Base(const std::string& name, glm::vec3 reper, float length, glm::vec3 color, bool fill)
            : name(name), center(reper), length(length), color(color), fill(fill)
        {
        }

        const std::string& getName() const
        {
            return name;
        }
        glm::vec3 getColor()
        {
            return color;
        }
        bool isFilled()
        {
            return fill;
        }

        Mesh* Create()
        {
            std::vector<VertexFormat> vertices =
            {
                VertexFormat(center + glm::vec3(-length / 0.65, -12 * length, 1), color), //0
                VertexFormat(center + glm::vec3(-length / 0.65f, 12 * length, 1), color), //1
                VertexFormat(center + glm::vec3(length / 0.65f, 12 * length, 1), color), //2
                VertexFormat(center + glm::vec3(length / 0.65f, -12 * length, 1), color), //3
            };


            Mesh* base = new Mesh(name);
            std::vector<unsigned int> indices =
            {
                0, 1, 2,
                0, 2, 3,
            };

            if (!fill) {
                base->SetDrawMode(GL_LINE_LOOP);
            }

            base->InitFromData(vertices, indices);
            return base;
        }
    };

    class Tile
    {
    private:
        const std::string& name;
        glm::vec3 center;
        float length;
        glm::vec3 color;
        bool fill;
        bool occupied;
        std::string weapon;
        float scaleWeapon = 1.0f;
        float translateStar = 0;
        bool shoot = false;
        glm::vec2 coord = glm::vec2(0, 0);

    public:
        Tile(const std::string& name, glm::vec3 reper, float length, glm::vec3 color, bool fill, bool occupied, std::string weapon)
            : name(name), center(reper), length(length), color(color), fill(fill), occupied(occupied), weapon(weapon)
        {
        }

        const std::string& getName() const
        {
            return name;
        }
        glm::vec3 getColor()
        {
            return color;
        }
        bool isFilled()
        {
            return fill;
        }
        bool isOccupied()
        {
            return occupied;
        }
        void setOccupied(bool isOccupied)
        {
            occupied = isOccupied;
        }
        std::string getWeapon()
        {
            return weapon;
        }
        void setWeapon(std::string w)
        {
            weapon = w;
        }
        float getScaleWeapon()
        {
            return scaleWeapon;
        }
        void setScaleWeapon(float scale)
        {
            scaleWeapon = scale;
        }
        void canShoot(bool s)
        {
            shoot = s;
        }
        bool getShoot()
        {
            return shoot;
        }
        void setCoord(glm::vec2 xy)
        {
            coord = xy;
        }
        glm::vec2 getCoord()
        {
            return coord;
        }

        Mesh* Create()
        {
            std::vector<VertexFormat> vertices =
            {
                VertexFormat(center + glm::vec3(-3 * length, -3 * length, 0), color), //0
                VertexFormat(center + glm::vec3(-3 * length, 3 * length, 0), color), //1
                VertexFormat(center + glm::vec3(3 * length, 3 * length, 0), color), //2
                VertexFormat(center + glm::vec3(3 * length, -3 * length, 0), color), //3
            };


            Mesh* tile = new Mesh(name);
            std::vector<unsigned int> indices;

            if (!fill) {
                indices = { 0, 1, 2, 3, 0 };
                tile->SetDrawMode(GL_LINE_LOOP);
            }
            else
            {
                indices =
                {
                    0, 1, 2,
                    0, 2, 3,
                };
            }

            tile->InitFromData(vertices, indices);
            return tile;
        }
    };

    class SpawnEnemy
    {
    private:
        std::string enemy;
        int line;
        float translate;
        glm::vec2 coord = glm::vec2(0, 0);
        std::string color;
        int lives = 3;
        float scale = 1;

    public:
        SpawnEnemy(std::string enemy, int line, float translate, std::string color)
            : enemy(enemy), line(line), translate(translate), color(color)
        {
        }
        std::string getEnemy()
        {
            return enemy;
        }
        int getLine()
        {
            return line;
        }
        float getTranslate()
        {
            return translate;
        }
        void setTranslate(float trans)
        {
            translate = trans;
        }
        void setCoord(glm::vec2 xy)
        {
            coord = xy;
        }
        glm::vec2 getCoord()
        {
            return coord;
        }
        std::string getColor()
        {
            return color;
        }
        void loseLife()
        {
            lives--;
        }
        int getLives()
        {
            return lives;
        }
        void setScale(float s)
        {
            scale = s;
        }
        float getScale()
        {
            return scale;
        }
    };

}

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };
       
    public:

        Tema1();
        ~Tema1();

        void Init() override;
    
    protected:
        std::vector<int> hearts;
        std::vector<classes::Tile> tiles;
        std::vector<bool> chooseWeapon;
        std::vector<classes::SpawnEnemy> enemies;
        std::vector<int> manaStars;
        bool alreadyChoose = false;
        int randomDiff = std::rand() % 5 + 2;
        bool deleteWeapon[9] = { false };
        bool deleteEnemy = false;
        int whichEnemy = -1;
        std::vector<classes::Bullet> bullets;
        int randStars;
        double nextTime = 0;
        double nextTimeShoot[9] = { 0 };
        std::vector<glm::vec2> mana;
        double nextTimeStars = 0;
        int randomDiffStars = 0;
        bool dragAndDrop = false;
        classes::DragTurret turret;

    private:
      
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void CreateObjects();
        void CreateTable(glm::mat3 visMatrix);
        void CreateWeaponSelection(glm::mat3 visMatrix);
        void CreateLivesAndMana(glm::mat3 visMatrix);
        void ChooseWeapon(int button, int mouseX, int mouseY);
        void putWeapon(int tile);
        void OccupyTiles(int mouseX, int mouseY, int button);
        void DeleteTurret(int mouseX, int mouseY, int button);
        void DisplayWeapons(glm::mat3 visMatrix);
        void DeleteWeapon(glm::mat3 visMatrix, float deltaTimeSeconds, int tile);
        void getStarsBack(int tile);
        void NewEnemy();
        void PutEnemy(int randomColor, int randomLine);
        void DisplayEnemy(glm::mat3 visMatrix, float deltaTimeSeconds);
        void Shoot(glm::mat3 visMatrix, float deltaTimeSeconds);
        void SetToShoot();
        void KillEnemy();
        void DeleteEnemy(float deltaTimeSeconds);
        void EnemyKillsTurret();
        void ThreeStars(glm::mat3 vismatrix);
        void DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
    };

}   // namespace m1

namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // TODO(student): Implement the translation matrix
        return glm::mat3(1, 0, 0,
            0, 1, 0,
            translateX, translateY, 1);

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        // TODO(student): Implement the scaling matrix
        return glm::mat3(scaleX, 0, 0,
            0, scaleY, 0,
            0, 0, 1);

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::mat3(cos(radians), sin(radians), 0,
            -sin(radians), cos(radians), 0,
            0, 0, 1);

    }
}   // namespace transform2D