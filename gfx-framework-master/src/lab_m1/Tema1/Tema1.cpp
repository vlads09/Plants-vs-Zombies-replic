#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>


using namespace std;
using namespace m1;
using namespace classes;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}



void Tema1::CreateObjects()
{
    glm::vec3 center = glm::vec3(0, 0, 0);

    Star orangeStar("orange_star", center, length, glm::vec3(1, 0.525f, 0), true, 1);
    Mesh* orStar = orangeStar.Create();
    AddMeshToList(orStar);
    meshes["orange_star"] = orStar;

    Star blueStar("blue_star", center, length, glm::vec3(0, 0, 1), true, 1);
    Mesh* blStar = blueStar.Create();
    AddMeshToList(blStar);
    meshes["blue_star"] = blStar;

    Star yellowStar("yellow_star", center, length, glm::vec3(1, 1, 0), true, 1);
    Mesh* yeStar = yellowStar.Create();
    AddMeshToList(yeStar);
    meshes["yellow_star"] = yeStar;

    Star purpleStar("purple_star", center, length, glm::vec3(0.750f, 0, 1), true, 1);
    Mesh* puStar = purpleStar.Create();
    AddMeshToList(puStar);
    meshes["purple_star"] = puStar;

    Star pinkStar("pink_star", center, length, glm::vec3(1, 0, 0.569f), true, 2);
    Mesh* piStar = pinkStar.Create();
    AddMeshToList(piStar);
    meshes["pink_star"] = piStar;

    Star greyStar("grey_star", center, length - 0.2f, glm::vec3(0.5f, 0.5f, 0.5f), true, 1);
    Mesh* grStar = greyStar.Create();
    AddMeshToList(grStar);
    meshes["grey_star"] = grStar;

    Turret orangeTurret("orange_turret", center, length, glm::vec3(1, 0.525f, 0), true);
    Mesh* orTurret = orangeTurret.Create();
    AddMeshToList(orTurret);
    meshes["orange_turret"] = orTurret;

    Turret blueTurret("blue_turret", center, length, glm::vec3(0, 0, 1), true);
    Mesh* blTurret = blueTurret.Create();
    AddMeshToList(blTurret);
    meshes["blue_turret"] = blTurret;

    Turret yellowTurret("yellow_turret", center, length, glm::vec3(1, 1, 0), true);
    Mesh* yeTurret = yellowTurret.Create();
    AddMeshToList(yeTurret);
    meshes["yellow_turret"] = yeTurret;

    Turret purpleTurret("purple_turret", center, length, glm::vec3(0.750f, 0, 1), true);
    Mesh* puTurret = purpleTurret.Create();
    AddMeshToList(puTurret);
    meshes["purple_turret"] = puTurret;

    Enemy orangeEnemy("orange_enemy", center, length, glm::vec3(1, 0.525f, 0), true);
    Mesh* orEnemy = orangeEnemy.Create();
    AddMeshToList(orEnemy);
    meshes["orange_enemy"] = orEnemy;

    Enemy blueEnemy("blue_enemy", center, length, glm::vec3(0, 0, 1), true);
    Mesh* blEnemy = blueEnemy.Create();
    AddMeshToList(blEnemy);
    meshes["blue_enemy"] = blEnemy;

    Enemy yellowEnemy("yellow_enemy", center, length, glm::vec3(1, 1, 0), true);
    Mesh* yeEnemy = yellowEnemy.Create();
    AddMeshToList(yeEnemy);
    meshes["yellow_enemy"] = yeEnemy;

    Enemy purpleEnemy("purple_enemy", center, length, glm::vec3(0.750f, 0, 1), true);
    Mesh* puEnemy = purpleEnemy.Create();
    AddMeshToList(puEnemy);
    meshes["purple_enemy"] = puEnemy;

    Base redBase("red_base", center, length, glm::vec3(0.8, 0, 0), true);
    Mesh* reBase = redBase.Create();
    AddMeshToList(reBase);
    meshes["red_base"] = reBase;

    Mesh* nothing = new Mesh("nothing");
    AddMeshToList(nothing);

    Tile tile("tile", center, length, glm::vec3(0, 0.9, 0.45f), true, false, "nothing");
    Mesh* aquaTile = tile.Create();
    AddMeshToList(aquaTile);
    meshes["tile"] = aquaTile;

    Tile frame("frame", center, length, glm::vec3(0, 0, 0), false, true, "nothing");
    Mesh* blFrame = frame.Create();
    AddMeshToList(blFrame);
    meshes["frame"] = blFrame;

    Tile heart("heart", center, length, glm::vec3(0.8f, 0, 0), true, true, "nothing");
    Mesh* redHeart = heart.Create();
    AddMeshToList(redHeart);
    meshes["heart"] = redHeart;

    for (int i = 0; i < 3; i++)
    {
        hearts.push_back(1);
    }

    int x = 150;
    int y = 70;
    for (int i = 0; i < 9; i++)
    {
        tiles.push_back(tile);
        tiles[i].setCoord(glm::vec2(x + (i % 3) * 150, y + (i / 3) * 180));
    }

    for (int i = 0; i < 4; i++)
    {
        chooseWeapon.push_back(false);
    }
    
    for (int i = 0; i < 5; i++)
    {
        manaStars.push_back(1);
    }
}

void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 1280;   // logic width
    logicSpace.height = 720;  // logic height
    length = 20;
    turret = DragTurret("nothing", glm::vec2(-1, -1));
    CreateObjects();
}


// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;


    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}



void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw - the left half of the window
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.604, 0.612, 0.267), true);


    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    
    DrawScene(visMatrix, deltaTimeSeconds);
      
}


void Tema1::FrameEnd()
{
}

void Tema1::CreateTable(glm::mat3 visMatrix)
{
    modelMatrix = visMatrix * transform2D::Translate(40, 250);
    RenderMesh2D(meshes["red_base"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(150, 70);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(300, 70);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(450, 70);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(150, 250);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(300, 250);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(450, 250);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(150, 430);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(300, 430);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(450, 430);
    RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
}

void Tema1::CreateWeaponSelection(glm::mat3 visMatrix)
{
    modelMatrix = visMatrix * transform2D::Translate(100, 650);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["orange_turret"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(60, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(300, 650);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["blue_turret"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(260, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(302, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(500, 650);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["yellow_turret"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(460, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(502, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(700, 650);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["purple_turret"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(658, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(700, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(742, 555);
    modelMatrix *= transform2D::Scale(0.5f, 0.5f);
    RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
}

void Tema1::CreateLivesAndMana(glm::mat3 visMatrix)
{
    for (float i = 0; i < hearts.size(); i++) {
        modelMatrix = visMatrix * transform2D::Translate(880 + i * 120, 650);
        modelMatrix *= transform2D::Scale(0.65f, 0.65f);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }
    if (hearts.size() == 0)
    {
        cout << "You lost! GOODBYE! Write q to exit" << endl;
        while (1)
        {
            string input;
            cin >> input;
            if (input == "q")
            {
                exit(0);
            }
            else
            {
                cout << "PRESS q" << endl;
            }
        }
    }

    float startingPoint = 813;
    for (int i = 0; i < manaStars.size(); i++)
    {
        modelMatrix = visMatrix * transform2D::Translate(startingPoint + 42 * i, 575);
        modelMatrix *= transform2D::Scale(0.5f, 0.5f);
        RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::DisplayWeapons(glm::mat3 visMatrix)
{
    int x = 150;
    int y = 70;
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].getWeapon() == "nothing")
        {
            continue;
        }
        else
        {
            float scale = tiles[i].getScaleWeapon();
            modelMatrix = visMatrix * transform2D::Translate(x + (i % 3) * 150, y + (i / 3) * 180);
            modelMatrix *= transform2D::Scale(scale, scale);
            RenderMesh2D(meshes[tiles[i].getWeapon()], shaders["VertexColor"], modelMatrix);
        }
    }
}

void Tema1::DeleteWeapon(glm::mat3 visMatrix, float deltaTimeSeconds, int i)
{
    float scale = tiles[i].getScaleWeapon();
    tiles[i].setScaleWeapon(tiles[i].getScaleWeapon() - 2 * deltaTimeSeconds);
    // shrink the weapon when deleting
    if (scale <= 0)
    {
        deleteWeapon[i] = false;
        tiles[i].setWeapon("nothing");
        tiles[i].setScaleWeapon(1);
        tiles[i].setOccupied(false);
    }
}

void Tema1::PutEnemy(int randomColor, int randomLine)
{
    // find which enemy will be set to spawn
    switch (randomColor)
    {
    case 0: enemies.push_back(SpawnEnemy("orange_enemy", randomLine, 0, "orange"));
        break;
    case 1: enemies.push_back(SpawnEnemy("blue_enemy", randomLine, 0, "blue"));
        break;
    case 2: enemies.push_back(SpawnEnemy("yellow_enemy", randomLine, 0, "yellow"));
        break;
    case 3: enemies.push_back(SpawnEnemy("purple_enemy", randomLine, 0, "purple"));
        break;
    default:
        break;
    }
}

void Tema1::NewEnemy()
{
    // random time for spawning an enemy
    double gameTime = glfwGetTime();
    if (gameTime - nextTime > randomDiff)
    {
        int randomColor = std::rand() % 4;
        int randomLine = std::rand() % 3;
        nextTime = gameTime;
        // set another random time to spawn enemy (from 3 to 13 seconds)
        randomDiff = std::rand() % 10 + 3;
        PutEnemy(randomColor, randomLine);
    }
}

void Tema1::DisplayEnemy(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        float translate = enemies[i].getTranslate();
        if (translate > 1330)
        {
            enemies.erase(enemies.begin() + i);
            hearts.pop_back();
        }
        enemies[i].setCoord(glm::vec2(1350 - translate, 70 + 180 * enemies[i].getLine()));
        modelMatrix = visMatrix * transform2D::Translate(1350 - translate, 70 + 180 * enemies[i].getLine());
        modelMatrix *= transform2D::Rotate(-0.3f);
        modelMatrix *= transform2D::Scale(enemies[i].getScale(), enemies[i].getScale());
        RenderMesh2D(meshes[enemies[i].getEnemy()], shaders["VertexColor"], modelMatrix);
        enemies[i].setTranslate(enemies[i].getTranslate() + 75 * deltaTimeSeconds);
    }
}

void Tema1::Shoot(glm::mat3 vismatrix, float deltatimeseconds)
{
    
    for (int i = 0; i < tiles.size(); i++)
    {
        // see which weapon can shoot
        if (tiles[i].getShoot())
        {
            double gametime = glfwGetTime();
            if (tiles[i].getWeapon() == "orange_turret")
            {
                if (gametime - nextTimeShoot[i] > 1)
                {
                    // add a new bullet on the screen
                    Bullet bullet(190 + i % 3 * 150, "orange_star", i / 3);
                    bullets.push_back(bullet);
                    // set next time a turret can shoot
                    nextTimeShoot[i] = gametime;
                }
            }
            if (tiles[i].getWeapon() == "blue_turret")
            {
                if (gametime - nextTimeShoot[i] > 1)
                {
                    // add a new bullet on the screen
                    Bullet bullet(190 + i % 3 * 150, "blue_star", i / 3);
                    bullets.push_back(bullet);
                    // set next time a turret can shoot
                    nextTimeShoot[i] = gametime;
                }
            }
            if (tiles[i].getWeapon() == "yellow_turret")
            {
                if (gametime - nextTimeShoot[i] > 1)
                {
                    // add a new bullet on the screen
                    Bullet bullet(190 + i % 3 * 150, "yellow_star", i / 3);
                    bullets.push_back(bullet);
                    // set next time a turret can shoot
                    nextTimeShoot[i] = gametime;
                }
            }
            if (tiles[i].getWeapon() == "purple_turret")
            {
                if (gametime - nextTimeShoot[i] > 1)
                {
                    // add a new bullet on the screen
                    Bullet bullet(190 + i % 3 * 150, "purple_star", i / 3);
                    bullets.push_back(bullet);
                    // set next time a turret can shoot
                    nextTimeShoot[i] = gametime;
                }
            }
        }
        
    }

    // display the bullets
    for (int j = 0; j < bullets.size(); j++)
    {
        
        float translate = bullets[j].getTranslate();
        float radians = bullets[j].getRadians();
        bullets[j].setCoord(glm::vec2(translate, 70 + bullets[j].getLine() * 180));
        modelMatrix = vismatrix * transform2D::Translate(translate, 70 + bullets[j].getLine() * 180);
        modelMatrix *= transform2D::Scale(0.3f, 0.3f);
        modelMatrix *= transform2D::Rotate(radians);
        RenderMesh2D(meshes[bullets[j].getColor()], shaders["VertexColor"], modelMatrix);
        bullets[j].setTranslate(translate + 1);
        bullets[j].setRadians(radians - 3 * deltatimeseconds);
    }
    for (int i = 0; i < tiles.size(); i++)
    {
        tiles[i].canShoot(false);
    }
}

void Tema1::SetToShoot()
{
    // verify if there is an enemy, if there is, set tile's weapon to shoot
    bool canShoot[9] = {false};
    for (int i = 0; i < enemies.size(); i++)
    {
        // verify first row
        if (enemies[i].getCoord().y == 70)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tiles[j].getWeapon().find(enemies[i].getColor()) != std::string::npos &&
                    tiles[j].getCoord().x <= enemies[i].getCoord().x)
                {
                    tiles[j].canShoot(true);
                    canShoot[j] = true;
                }
                // let each turret shoot for its enemy type
                else if (!canShoot[j])
                {
                    tiles[j].canShoot(false);
                }
            }
        }
        // verify second row
        if (enemies[i].getCoord().y == 250)
        {
            for (int j = 3; j < 6; j++)
            {
                if (tiles[j].getWeapon().find(enemies[i].getColor()) != std::string::npos &&
                    tiles[j].getCoord().x <= enemies[i].getCoord().x)
                {
                    tiles[j].canShoot(true);
                    canShoot[j] = true;
                }
                // let each turret shoot for its enemy type
                else if (!canShoot[j])
                {
                    tiles[j].canShoot(false);
                }
            }
        }
        // verify third row
        if (enemies[i].getCoord().y == 430)
        {
            for (int j = 6; j < 9; j++)
            {
                if (tiles[j].getWeapon().find(enemies[i].getColor()) != std::string::npos &&
                    tiles[j].getCoord().x <= enemies[i].getCoord().x)
                {
                    tiles[j].canShoot(true);
                    canShoot[j] = true;
                }
                // let each turret shoot for its enemy type
                else if (!canShoot[j])
                {
                    tiles[j].canShoot(false);
                }
            }
        }
    }
}

void Tema1::KillEnemy()
{
    float radius_bullet = 15;
    float radius_enemy = 25;
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < bullets.size(); j++)
        {
            // check if the enemy is on the same row as the bullets and have the same color
            if (bullets[j].getColor().find(enemies[i].getColor()) != std::string::npos &&
                bullets[j].getCoord().x <= enemies[i].getCoord().x &&
                bullets[j].getCoord().y == enemies[i].getCoord().y)
            {
                
                float distance = glm::distance(bullets[j].getCoord().x, enemies[i].getCoord().x);
                // check if the collision happens
                if (distance < radius_bullet + radius_enemy)
                {
                    enemies[i].loseLife();
                    bullets.erase(bullets.begin() + j);
                    if (enemies[i].getLives() == 0)
                    {
                        deleteEnemy = true;
                        whichEnemy = i;
                    }
                }
                
            }    
        }
    }
}

void Tema1::DeleteEnemy(float deltaTimeSeconds)
{
    // shrink enemy until it is gone
    float scale = enemies[whichEnemy].getScale();
    enemies[whichEnemy].setScale(scale - 3 * deltaTimeSeconds);

    if (scale < 0)
    {
        deleteEnemy = false;
        enemies.erase(enemies.begin() + whichEnemy);
    }
}

void Tema1::EnemyKillsTurret()
{
    float radius_turret = 15;
    float radius_enemy = 25;
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < tiles.size(); j++)
        {
            // check if an enemy will intersect a turret
            if (tiles[j].getCoord().x <= enemies[i].getCoord().x &&
                tiles[j].getCoord().y == enemies[i].getCoord().y)
            {
                float distance = glm::distance(tiles[j].getCoord().x, enemies[i].getCoord().x);
                // check if the collision happens
                if (distance < radius_turret + radius_enemy)
                {
                    deleteWeapon[j] = true;
                }
            }
        }
    }
}

void Tema1::ThreeStars(glm::mat3 visMatrix)
{
    double gameTime = glfwGetTime();
    if (gameTime - nextTimeStars > randomDiffStars)
    {
        for (int i = 0; i < 3; i++)
        {
            int randomX = std::rand() % 1280;
            int randomY = std::rand() % 720;
            mana.push_back(glm::vec2(randomX, randomY));
        }
        
        nextTimeStars = gameTime;
        // set another random time to spawn mana (from 10 to 20 seconds)
        randomDiffStars = std::rand() % 10 + 10;
    }
    for (int i = 0; i < mana.size(); i++)
    {
        modelMatrix = visMatrix * transform2D::Translate(mana[i].x, mana[i].y);
        modelMatrix *= transform2D::Scale(0.6f, 0.6f);
        RenderMesh2D(meshes["pink_star"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    CreateTable(visMatrix);
    CreateWeaponSelection(visMatrix);
    CreateLivesAndMana(visMatrix);
    DisplayWeapons(visMatrix);
    if (dragAndDrop)
    {
        modelMatrix = visMatrix * transform2D::Translate(turret.getCoordinates().x, turret.getCoordinates().y);
        RenderMesh2D(meshes[turret.getName()], shaders["VertexColor"], modelMatrix);
    }
    NewEnemy();
    DisplayEnemy(visMatrix, deltaTimeSeconds);
    SetToShoot();
    Shoot(visMatrix, deltaTimeSeconds);
    EnemyKillsTurret();
    for (int i = 0; i < 9; i++)
    {
        if (deleteWeapon[i] && tiles[i].getWeapon() != "nothing")
        {
            DeleteWeapon(visMatrix, deltaTimeSeconds, i);
        }
    }
    KillEnemy();
    if (deleteEnemy)
    {
        DeleteEnemy(deltaTimeSeconds);
    }
    ThreeStars(visMatrix);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
 
}


void Tema1::OnKeyPress(int key, int mods)
{
    
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    // get the coordonates for drag and drop
    if (dragAndDrop)
    {
        for (int i = 0; i < chooseWeapon.size(); i++)
        {
            if (chooseWeapon[i])
            {
                switch (i)
                {
                case 0: turret.setName("orange_turret");
                    turret.setCoordinates(glm::vec2(mouseX, 720 - mouseY));
                    break;
                case 1: turret.setName("blue_turret");
                    turret.setCoordinates(glm::vec2(mouseX, 720 - mouseY));
                    break;
                case 2: turret.setName("yellow_turret");
                    turret.setCoordinates(glm::vec2(mouseX, 720 - mouseY));
                    break;
                case 3: turret.setName("purple_turret");
                    turret.setCoordinates(glm::vec2(mouseX, 720 - mouseY));
                    break;
                default:
                    break;
                }
            }
        }
    }  
}

void Tema1::ChooseWeapon(int button, int mouseX, int mouseY)
{
    if (button == GLFW_MOUSE_BUTTON_2 && mouseX >= 40 && mouseX <= 160 &&
        mouseY >= 720 - 710 && mouseY <= 720 - 590)
    {
        chooseWeapon[0] = true;
        chooseWeapon[1] = false;
        chooseWeapon[2] = false;
        chooseWeapon[3] = false;
        alreadyChoose = true;

    }
    else if (button == GLFW_MOUSE_BUTTON_2 && mouseX >= 240 && mouseX <= 360 &&
        mouseY >= 720 - 710 && mouseY <= 720 - 590)
    {
        chooseWeapon[0] = false;
        chooseWeapon[1] = true;
        chooseWeapon[2] = false;
        chooseWeapon[3] = false;
        alreadyChoose = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_2 && mouseX >= 440 && mouseX <= 560 &&
        mouseY >= 720 - 710 && mouseY <= 720 - 590)
    {
        chooseWeapon[0] = false;
        chooseWeapon[1] = false;
        chooseWeapon[2] = true;
        chooseWeapon[3] = false;
        alreadyChoose = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_2 && mouseX >= 640 && mouseX <= 760 &&
        mouseY >= 720 - 710 && mouseY <= 720 - 590)
    {
        chooseWeapon[0] = false;
        chooseWeapon[1] = false;
        chooseWeapon[2] = false;
        chooseWeapon[3] = true;
        alreadyChoose = true;
    }
}

void Tema1::putWeapon(int tile)
{
    for (int i = 0; i < chooseWeapon.size(); i++)
    {
        if (chooseWeapon[i])
        {
            // before placing a weapon, check if there is enough mana to spawn
            switch (i)
            {
            case 0: if (manaStars.size() >= 1)
                {
                    tiles[tile].setWeapon("orange_turret");
                    manaStars.resize(manaStars.size() - 1);
                }
                else
                {
                    tiles[tile].setOccupied(false);
                }
                 chooseWeapon[i] = false;
                break;
            case 1: if (manaStars.size() >= 2)
                {
                    tiles[tile].setWeapon("blue_turret");
                    manaStars.resize(manaStars.size() - 2);
                }
                else
                {
                    tiles[tile].setOccupied(false);
                }
                  chooseWeapon[i] = false;
                break;
            case 2: if (manaStars.size() >= 2)
                {
                    tiles[tile].setWeapon("yellow_turret");
                    manaStars.resize(manaStars.size() - 2);
                }
                else
                {
                    tiles[tile].setOccupied(false);
                }
                  chooseWeapon[i] = false;
                break;
            case 3: if (manaStars.size() >= 3)
                {
                    tiles[tile].setWeapon("purple_turret");
                    manaStars.resize(manaStars.size() - 3);
                }
                else
                {
                    tiles[tile].setOccupied(false);
                }
                  chooseWeapon[i] = false;
                break;
            default:
                break;
            }
        }
    }
}

void Tema1::OccupyTiles(int mouseX, int mouseY, int button)
{
    // puts the weapon when the player selected an empty tile
    
    // for drag and drop, puts a weapon when the player releases the button
    // in an empty tile
     
    if (alreadyChoose && button == GLFW_MOUSE_BUTTON_2)
    {
        if (mouseX >= 90 && mouseX <= 210)
        {
            if (mouseY >= 720 - 130 && mouseY <= 720 - 10 && !tiles[0].isOccupied())
            {
                deleteWeapon[0] = false;
                tiles[0].setOccupied(true);
                putWeapon(0);
                alreadyChoose = false;
            }
            if (mouseY >= 720 - 310 && mouseY <= 720 - 190 && !tiles[3].isOccupied())
            {
                deleteWeapon[3] = false;
                tiles[3].setOccupied(true);
                putWeapon(3);
                alreadyChoose = false;
            }
            if (mouseY >= 720 - 490 && mouseY <= 720 - 370 && !tiles[6].isOccupied())
            {
                deleteWeapon[6] = false;
                tiles[6].setOccupied(true);
                putWeapon(6);
                alreadyChoose = false;
            }
        }
        else if (mouseX >= 390 && mouseX <= 510)
        {
            if (mouseY >= 720 - 130 && mouseY <= 720 - 10 && !tiles[2].isOccupied())
            {
                deleteWeapon[2] = false;
                tiles[2].setOccupied(true);
                putWeapon(2);
                alreadyChoose = false;
            }
            if (mouseY >= 720 - 310 && mouseY <= 720 - 190 && !tiles[5].isOccupied())
            {
                deleteWeapon[5] = false;
                tiles[5].setOccupied(true);
                putWeapon(5);
                alreadyChoose = false;
            }
            if (mouseY >= 720 - 490 && mouseY <= 720 - 370 && !tiles[8].isOccupied())
            {
                deleteWeapon[8] = false;
                tiles[8].setOccupied(true);
                putWeapon(8);
                alreadyChoose = false;
            }
        }
        else if (mouseX >= 240 && mouseX <= 360)
        {
            if (mouseY >= 720 - 130 && mouseY <= 720 - 10 && !tiles[1].isOccupied())
            {
                deleteWeapon[1] = false;
                tiles[1].setOccupied(true);
                putWeapon(1);
                alreadyChoose = false;
            }
            if (mouseY >= 720 - 310 && mouseY <= 720 - 190 && !tiles[4].isOccupied())
            {
                deleteWeapon[4] = false;
                tiles[4].setOccupied(true);
                putWeapon(4);
                alreadyChoose = false;
            }
            if (mouseY >= 720 - 490 && mouseY <= 720 - 370 && !tiles[7].isOccupied())
            {
                deleteWeapon[7] = false;
                tiles[7].setOccupied(true);
                putWeapon(7);
                alreadyChoose = false;
            }
        }
    }
}

void Tema1::getStarsBack(int tile)
{
    int numStars = 0;
    if (tiles[tile].getWeapon() == "orange_turret")
    {
        numStars = 1;
    }
    else if (tiles[tile].getWeapon() == "blue_turret")
    {
        numStars = 2;
    }
    else if (tiles[tile].getWeapon() == "yellow_turret")
    {
        numStars = 2;
    }
    else if (tiles[tile].getWeapon() == "purple_turret")
    {
        numStars = 3;
    }

    for (int i = 0; i < numStars; i++)
    {
        manaStars.push_back(1);
    }
}

void Tema1::DeleteTurret(int mouseX, int mouseY, int button)
{
    float del = 1;
    if (mouseX >= 90 && mouseX <= 210)
    {
        if (mouseY >= 720 - 130 && mouseY <= 720 - 10 && tiles[0].isOccupied())
        {
            tiles[0].setOccupied(false);
            deleteWeapon[0] = true;
            getStarsBack(0);
        }
        if (mouseY >= 720 - 310 && mouseY <= 720 - 190 && tiles[3].isOccupied())
        {
            tiles[3].setOccupied(false);
            deleteWeapon[3] = true;
            getStarsBack(3);
        }
        if (mouseY >= 720 - 490 && mouseY <= 720 - 370 && tiles[6].isOccupied())
        {

            tiles[6].setOccupied(false);
            deleteWeapon[6] = true;
            getStarsBack(6);
        }
    }
    else if (mouseX >= 390 && mouseX <= 510)
    {
        if (mouseY >= 720 - 130 && mouseY <= 720 - 10 && tiles[2].isOccupied())
        {
            tiles[2].setOccupied(false);
            deleteWeapon[2] = true;
            getStarsBack(2);
        }
        if (mouseY >= 720 - 310 && mouseY <= 720 - 190 && tiles[5].isOccupied())
        {
            tiles[5].setOccupied(false);
            deleteWeapon[5] = true;
            getStarsBack(5);
        }
        if (mouseY >= 720 - 490 && mouseY <= 720 - 370 && tiles[8].isOccupied())
        {
            tiles[8].setOccupied(false);
            deleteWeapon[8] = true;
            getStarsBack(8);
        }
    }
    else if (mouseX >= 240 && mouseX <= 360)
    {
        if (mouseY >= 720 - 130 && mouseY <= 720 - 10 && tiles[1].isOccupied())
        {
            tiles[1].setOccupied(false);
            deleteWeapon[1] = true;
            getStarsBack(1);
        }
        if (mouseY >= 720 - 310 && mouseY <= 720 - 190 && tiles[4].isOccupied())
        {
            tiles[4].setOccupied(false);
            deleteWeapon[4] = true;
            getStarsBack(4);
        }
        if (mouseY >= 720 - 490 && mouseY <= 720 - 370 && tiles[7].isOccupied())
        {
            tiles[7].setOccupied(false);
            deleteWeapon[7] = true;
            getStarsBack(7);
        }
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    // check if a weapon has been clicked by the player
    if (!alreadyChoose)
    {
        ChooseWeapon(button, mouseX, mouseY);
        // for the drag and drop functionality
        dragAndDrop = true;
    }
    OccupyTiles(mouseX, mouseY, button);
    if (button == GLFW_MOUSE_BUTTON_3)
    {
        for (int i = 0; i < mana.size(); i++)
        {
            if (mouseX >= mana[i].x - 1.4 * length && mouseX <= mana[i].x + 1.4 * length &&
                720 - mouseY >= mana[i].y - 1.4 * length && 720 - mouseY <= mana[i].y + 1.4 * length)
            {  
                manaStars.push_back(1);
                mana.erase(mana.begin() + i);
            }
        }
    }
    
    if (button == GLFW_MOUSE_BUTTON_5)
    {
        DeleteTurret(mouseX, mouseY, button);
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    OccupyTiles(mouseX, mouseY, button);
    // operation finished
    dragAndDrop = false;
    turret.setName("nothing");
    turret.setCoordinates(glm::vec2(-1, -1));
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
