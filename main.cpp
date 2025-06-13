#include "raylib.h"
#include <math.h>

typedef struct
{
    Vector3 position;
    float width;
    float height;
    float length;
} StairCube;

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TRANSPARENT);
    const int screenWidth = 1100;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - M3D model loading");

    // Define the camera to look into our 3d world
    Camera camera = {0};
    camera.position = (Vector3){1.5f, 1.5f, 1.5f}; // Camera position
    camera.target = (Vector3){0.0f, 0.4f, 0.0f};   // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera projection type

    Vector3 position = {0.0f, 0.0f, 0.0f}; // Set model position
    Vector3 cubePosition = {7.0f, 2.0f, 0.0f};
    float moveSpeed = 0.01f;
    float fallSpeed = 0.005f;
    float jumpSpeed = 0.2f;
    float yVelocity = 0.0f;
    float facingAngle = 0.0f;
    const float gridSize = 7.0f;
    StairCube stairs[40];
    // {{0.0f, 0.25f, 2.0f}, 2.0f, 0.5f, 2.0f},  // Step 1
    // {{0.0f, 0.75f, 3.0f}, 2.0f, 0.5f, 2.0f},   // Step 2
    // {{0.0f, 1.25f, 4.0f}, 2.0f, 0.5f, 2.0f},   // Step 3
    // {{0.0f, 1.75f, 5.0f}, 2.0f, 0.5f, 2.0f},   // Step 4
    // {{0.0f, 2.25f, 6.0f}, 2.0f, 0.5f, 2.0f},   // Step 5
    // {{0.0f, 2.75f, 7.0f}, 2.0f, 0.5f, 2.0f},   // Step 6
    // {{0.0f, 3.25f, 8.0f}, 2.0f, 0.5f, 2.0f},   // Step 7
    // {{0.0f, 3.75f, 9.0f}, 2.0f, 0.5f, 2.0f},   // Step 8
    // {{0.0f, 4.25f, 10.0f}, 2.0f, 0.5f, 2.0f},  // Step 9
    // {{0.0f, 4.75f, 11.0f}, 2.0f, 0.5f, 2.0f},  // Step 10
    // {{0.0f, 5.25f, 12.0f}, 2.0f, 0.5f, 2.0f},  // Step 11
    // {{0.0f, 5.75f, 13.0f}, 2.0f, 0.5f, 2.0f},  // Step 12
    // {{0.0f, 6.25f, 14.0f}, 2.0f, 0.5f, 2.0f},  // Step 13
    // {{0.0f, 6.75f, 15.0f}, 2.0f, 0.5f, 2.0f},  // Step 14
    // {{0.0f, 7.25f, 16.0f}, 2.0f, 0.5f, 2.0f},  // Step 15
    // {{0.0f, 7.75f, 17.0f}, 2.0f, 0.5f, 2.0f},  // Step 16
    // {{0.0f, 8.25f, 18.0f}, 2.0f, 0.5f, 2.0f},  // Step 17
    // {{0.0f, 8.75f, 19.0f}, 2.0f, 0.5f, 2.0f},  // Step 18
    // {{0.0f, 9.25f, 20.0f}, 2.0f, 0.5f, 2.0f},  // Step 19
    // {{0.0f, 9.75f, 21.0f}, 2.0f, 0.5f, 2.0f},  // Step 20
    // {{0.0f, 10.25f, 22.0f}, 2.0f, 0.5f, 2.0f}, // Step 21
    // {{0.0f, 10.75f, 23.0f}, 2.0f, 0.5f, 2.0f}, // Step 22
    // {{0.0f, 11.25f, 24.0f}, 2.0f, 0.5f, 2.0f}, // Step 23
    // {{0.0f, 11.75f, 25.0f}, 2.0f, 0.5f, 2.0f}, // Step 24
    // {{0.0f, 12.25f, 26.0f}, 2.0f, 0.5f, 2.0f}, // Step 25
    // {{0.0f, 12.75f, 27.0f}, 2.0f, 0.5f, 2.0f}, // Step 26
    // {{0.0f, 13.25f, 28.0f}, 2.0f, 0.5f, 2.0f}, // Step 27
    // {{0.0f, 13.75f, 29.0f}, 2.0f, 0.5f, 2.0f}, // Step 28
    // {{0.0f, 14.25f, 30.0f}, 2.0f, 0.5f, 2.0f}, // Step 29
    // {{0.0f, 14.75f, 31.0f}, 2.0f, 0.5f, 2.0f}, // Step 30
    // {{0.0f, 15.25f, 32.0f}, 2.0f, 0.5f, 2.0f}, // Step 31
    // {{0.0f, 15.75f, 33.0f}, 2.0f, 0.5f, 2.0f}, // Step 32
    // {{0.0f, 16.25f, 34.0f}, 2.0f, 0.5f, 2.0f}, // Step 33
    // {{0.0f, 16.75f, 35.0f}, 2.0f, 0.5f, 2.0f}, // Step 34
    // {{0.0f, 17.25f, 36.0f}, 2.0f, 0.5f, 2.0f}, // Step 35
    // {{0.0f, 17.75f, 37.0f}, 2.0f, 0.5f, 2.0f}, // Step 36
    // {{0.0f, 18.25f, 38.0f}, 2.0f, 0.5f, 2.0f}, // Step 37
    // {{0.0f, 18.75f, 39.0f}, 2.0f, 0.5f, 2.0f}, // Step 38
    // {{0.0f, 19.25f, 40.0f}, 2.0f, 0.5f, 2.0f}, // Step 39
    // {{0.0f, 19.75f, 41.0f}, 2.0f, 0.5f, 2.0f}  // Step 40
    for (int i = 0; i < 40; i++)
    {
        stairs[i] = (StairCube){{0.0f, 0.25f + i * 0.5f, 2.0f + i * 1.0f}, 2.0f, 0.5f, 1.0f};
    }
    int stairCount = 40;
    bool drawStairs = false;
    bool onStairs = false;

    char modelFileName[128] = "resources/models/m3d/m3d/cesium_man.m3d";
    bool drawMesh = 1;
    // bool drawSkeleton = 1;
    bool animPlaying = false; // Store anim state, what to draw
    bool isBackflipping = false;
    float backflipAngle = 0.0f;
    float backflipSpeed = 9.0f;

    // Load model
    Model model = LoadModel(modelFileName); // Load the bind-pose model mesh and basic data

    // Load animations
    int animsCount = 0;
    int animFrameCounter = 0, animId = 0;
    ModelAnimation *anims = LoadModelAnimations(modelFileName, &animsCount); // Load skeletal animation data

    DisableCursor(); // Limit cursor to relative movement inside the window

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {

        // Update
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        bool isOffGrid =
            (position.x < -gridSize || position.x > gridSize || position.z < -gridSize || position.z > gridSize);

        if (animsCount)
        {
            // Play animation when spacebar is held down (or step one frame with N)
            if ((IsKeyDown(KEY_SPACE) || IsKeyPressed(KEY_N)) && !isBackflipping)
            {
                animFrameCounter++;

                if (animFrameCounter >= anims[animId].frameCount)
                {
                    animFrameCounter = 0;
                }

                UpdateModelAnimation(model, anims[animId], animFrameCounter);
                animPlaying = true;
            }
            if (IsKeyPressed(KEY_P))
            {
                drawStairs = !drawStairs;
            }
            if (IsKeyPressed(KEY_F) && !isBackflipping)
            {
                isBackflipping = true;
                backflipAngle = 0.0f;
                yVelocity = jumpSpeed * 0.7f;
                animPlaying = false;
            }
            if (isBackflipping)
            {
                backflipAngle += backflipSpeed;
                if (backflipAngle >= 360.0f)
                {
                    backflipAngle = 0.0f;
                    isBackflipping = false;
                }
            }
            if (IsKeyDown(KEY_H) && !isOffGrid && !onStairs)
            {
                position.z += moveSpeed;
            }
            if (IsKeyDown(KEY_L) && !isOffGrid && !onStairs)
            {
                position.z -= moveSpeed;
            }
            if (IsKeyDown(KEY_K) && !isOffGrid && !onStairs)
            {
                position.x -= moveSpeed;
            }
            else if (IsKeyDown(KEY_J) && !isOffGrid && !onStairs)
            {
                position.x += moveSpeed;
            }
            if (!isBackflipping)
            {
                float dx = 0.0f, dz = 0.0f;
                Vector3 newPosition = position;

                if (IsKeyDown(KEY_H) && !onStairs)
                    dz += moveSpeed;
                if (IsKeyDown(KEY_L) && !onStairs)
                    dz -= moveSpeed;
                if (IsKeyDown(KEY_K) && !onStairs)
                    dx -= moveSpeed;
                if (IsKeyDown(KEY_J) && !onStairs)
                    dx += moveSpeed;

                // Update facing angle if moving
                if (dx != 0.0f || dz != 0.0f)
                    facingAngle = atan2f(dx, dz) * RAD2DEG;

                // Check collision before moving
                newPosition.x += dx;
                newPosition.z += dz;

                if (drawStairs)
                {
                    for (int i = 0; i < stairCount; i++)
                    {
                        StairCube stair = stairs[i];
                        float halfW = stair.width / 2.0f;
                        float halfH = stair.height / 2.0f;
                        float halfL = stair.length / 2.0f;

                        // Check if new position collides with stair sides
                        if (newPosition.x >= stair.position.x - halfW - 0.25f &&
                            newPosition.x <= stair.position.x + halfW + 0.25f &&
                            newPosition.z >= stair.position.z - halfL - 0.25f &&
                            newPosition.z <= stair.position.z + halfL + 0.25f &&
                            newPosition.y <= stair.position.y + halfH &&
                            newPosition.y >= stair.position.y - halfH - 1.0f) // Model height ~1.0
                        {
                            // Snap to stair top if close enough
                            if (newPosition.z >= stair.position.z - halfL - 0.1f &&
                                newPosition.y >= stair.position.y - 0.5f &&
                                newPosition.y <= stair.position.y + halfH + 0.1f)
                            {
                                position.y = stair.position.y + halfH;
                                yVelocity = 0.0f;
                            }
                            else
                            {
                                // Block movement if hitting side
                                newPosition.x = position.x;
                                newPosition.z = position.z;
                            }
                            break;
                        }
                    }
                }
                position.x = newPosition.x;
                position.z = newPosition.z;
            }

            // Select animation by pressing C
            if (IsKeyPressed(KEY_C))
            {
                animFrameCounter = 0;
                animId++;

                if (animId >= (int)animsCount)
                    animId = 0;
                UpdateModelAnimation(model, anims[animId], 0);
                animPlaying = true;
            }
        }

        if (IsKeyPressed(KEY_T))
        {
            yVelocity = jumpSpeed;
        }

        yVelocity -= fallSpeed;
        position.y += yVelocity;

        onStairs = false;
        if (drawStairs)
        {
            for (int i = 0; i < stairCount; i++)
            {
                StairCube stair = stairs[i];
                float halfW = stair.width / 2.0f;
                float halfH = stair.height / 2.0f;
                float halfL = stair.length / 2.0f;

                // Simple AABB collision check (assume model is roughly 0.5x0.5x1.0 units)
                if (position.x >= stair.position.x - halfW - 0.25f && position.x <= stair.position.x + halfW + 0.25f &&
                    position.z >= stair.position.z - halfL - 0.25f && position.z <= stair.position.z + halfL + 0.25f &&
                    position.y <= stair.position.y + halfH && position.y + yVelocity >= stair.position.y + halfH)
                {
                    position.y = stair.position.y + halfH; // Land on top of stair
                    yVelocity = 0.0f;
                    onStairs = true;
                    break;
                }
            }
        }
        if (!onStairs && !isOffGrid && position.y < 0.0f)
        {
            position.y = 0.0f;
            yVelocity = 0.0f;
        }
        if (position.y < -25.0f)
        {
            position = (Vector3){0.0f, 0.0f, 0.0f}; // Reset to starting position
        }

        // // Toggle skeleton drawing
        // if (IsKeyPressed(KEY_B))
        //     drawSkeleton ^= 1;
        // Toggle mesh drawing
        if (IsKeyPressed(KEY_M))
            drawMesh ^= 1;

        // Draw
        BeginDrawing();
        ClearBackground((Color){0, 0, 0, 0});
        BeginMode3D(camera);

        if (drawStairs)
        {
            for (int i = 0; i < stairCount; i++)
            {
                DrawCube(stairs[i].position, stairs[i].width, stairs[i].height, stairs[i].length, WHITE);
            }
        }
        // Draw 3d model with texture
        if (drawMesh)
        {
            float dx = 0.0f, dz = 0.0f;
            if (IsKeyDown(KEY_H))
                dz += moveSpeed;
            if (IsKeyDown(KEY_L))
                dz -= moveSpeed;
            if (IsKeyDown(KEY_K))
                dx -= moveSpeed;
            if (IsKeyDown(KEY_J))
                dx += moveSpeed;

            if (isBackflipping)
            {
                // Draw model with backflip rotation (around X-axis for backward flip)
                DrawModelEx(model, position, (Vector3){1.0f, 0.0f, 0.0f}, -backflipAngle, (Vector3){1.0f, 1.0f, 1.0f},
                            WHITE);
            }
            else if (dx != 0.0f || dz != 0.0f)
            {
                float angle = atan2f(dx, dz) * RAD2DEG;
                DrawModelEx(model, position, (Vector3){0.0f, 1.0f, 0.0f}, angle, (Vector3){1.0f, 1.0f, 1.0f}, WHITE);
            }
            else
            {
                DrawModel(model, position, 1.0f, WHITE);
            }
        }

        // Draw the animated skeleton
        // if (drawSkeleton)
        // {
        //     // Loop to (boneCount - 1) because the last one is a special "no bone" bone,
        //     // needed to workaround buggy models
        //     // without a -1, we would always draw a cube at the origin
        //     for (int i = 0; i < model.boneCount - 1; i++)
        //     {
        //         // By default the model is loaded in bind-pose by LoadModel().
        //         // But if UpdateModelAnimation() has been called at least once
        //         // then the model is already in animation pose, so we need the animated skeleton
        //         if (!animPlaying || !animsCount)
        //         {
        //             // Display the bind-pose skeleton
        //             DrawCube(model.bindPose[i].translation, 0.04f, 0.04f, 0.04f, RED);
        //
        //             if (model.bones[i].parent >= 0)
        //             {
        //                 DrawLine3D(model.bindPose[i].translation,
        //                 model.bindPose[model.bones[i].parent].translation,
        //                            RED);
        //             }
        //         }
        //         else
        //         {
        //             // Display the frame-pose skeleton
        //             DrawCube(anims[animId].framePoses[animFrameCounter][i].translation, 0.05f, 0.05f, 0.05f,
        //             RED);
        //
        //         if (anims[animId].bones[i].parent >= 0)
        //         {
        //             DrawLine3D(anims[animId].framePoses[animFrameCounter][i].translation,
        //                        anims[animId].framePoses[animFrameCounter][anims[animId].bones[i].parent].translation,
        //                        RED);
        //         }
        //     }
        // }
        // }

        DrawGrid(15, 1.0f); // Draw a grid
        EndMode3D();

        DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, GetScreenHeight() - 80, 10, WHITE);
        DrawText("PRESS N to STEP ONE ANIMATION FRAME", 10, GetScreenHeight() - 60, 10, WHITE);
        DrawText("PRESS C to CYCLE THROUGH ANIMATIONS", 10, GetScreenHeight() - 40, 10, WHITE);
        DrawText("PRESS M to toggle MESH", 10, GetScreenHeight() - 20, 10, WHITE);

        EndDrawing();
    }

    // Unload model animations data
    UnloadModelAnimations(anims, animsCount);

    UnloadModel(model); // Unload model

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
