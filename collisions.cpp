#include <raylib.h>
#include <raymath.h>
#include <iostream>

BoundingBox GetUpdatedBoundingBox(const Model& model, Vector3 pos) {
    BoundingBox box = GetMeshBoundingBox(model.meshes[0]);
    box.min = Vector3Add(box.min, pos);
    box.max = Vector3Add(box.max, pos);
    return box;
}

bool CheckCollisionAndResolve(Vector3& pos, const Vector3& dir,
                              const Model& player, const Model& obstacle,
                              Vector3 obstacle_pos, char axis)
{
    BoundingBox pb = GetUpdatedBoundingBox(player, pos);
    BoundingBox ob = GetUpdatedBoundingBox(obstacle, obstacle_pos);

    if (!CheckCollisionBoxes(pb, ob)) return false;

    // player half-extents from its bbox (more robust than hardcoding 0.5)
    float halfX = (pb.max.x - pb.min.x) * 0.5f;
    float halfZ = (pb.max.z - pb.min.z) * 0.5f;

    if (axis == 'x') {
        if (dir.x > 0) pos.x = ob.min.x - halfX;
        else if (dir.x < 0) pos.x = ob.max.x + halfX;
    } else if (axis == 'z') {
        if (dir.z > 0) pos.z = ob.min.z - halfZ;
        else if (dir.z < 0) pos.z = ob.max.z + halfZ;
    }
    return true;
}

int main() {
    InitWindow(1920, 1080, "collisions");

    Camera3D camera{};
    camera.position = { 0.0f, 7.0f, 7.0f };
    camera.target   = { 0.0f, 0.0f, 0.0f };
    camera.up       = { 0.0f, 1.0f, 0.0f };
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model player   = LoadModelFromMesh(GenMeshCube(1, 1, 1));
    Model obstacle = LoadModelFromMesh(GenMeshCube(2, 1, 4));

    Vector3 pos = {0,0,0};
    Vector3 dir = {0,0,0};
    float speed = 5.0f;

    Vector3 obstacle_pos = {3,0,0};

    while (!WindowShouldClose()) {
        dir.x = (float)(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
        dir.z = (float)(IsKeyDown(KEY_DOWN)  - IsKeyDown(KEY_UP));

        float dt = GetFrameTime();

        pos.x += dir.x * speed * dt;
        CheckCollisionAndResolve(pos, dir, player, obstacle, obstacle_pos, 'x');

        pos.z += dir.z * speed * dt;
        CheckCollisionAndResolve(pos, dir, player, obstacle, obstacle_pos, 'z');

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode3D(camera);

        DrawGrid(10, 1);
        DrawModel(player, pos, 1.0f, RED);
        DrawModel(obstacle, obstacle_pos, 1.0f, GRAY);

        DrawBoundingBox(GetUpdatedBoundingBox(player, pos), GREEN);
        DrawBoundingBox(GetUpdatedBoundingBox(obstacle, obstacle_pos), RED);

        EndMode3D();
        EndDrawing();
    }

    UnloadModel(player);
    UnloadModel(obstacle);
    CloseWindow();
}
