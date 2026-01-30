#include <raylib.h>
#include <raymath.h>
#include <iostream>

int main() {
	InitWindow(1920, 1080, "collisions");
	Camera3D camera;
	camera.position = { 0.0f,5.0f,5.0f };
	camera.target = { 0.0f,0.0f,0.0f };
	camera.up = { 0.0f,1.0f,0.0f };
	camera.fovy = 45;
	camera.projection = CAMERA_PERSPECTIVE;

	Model player = LoadModelFromMesh(GenMeshSphere(0.5, 12, 12));
	Vector3 pos = {0.0f,0.0f,0.0f};
	Vector3 direction = {0.0f,0.0f,0.0f};
	float speed = 5;

	Model obstacle = LoadModelFromMesh(GenMeshSphere(0.5, 12, 12));
	Vector3 obstacle_pos = { 3,0,0 };

	while (!WindowShouldClose()) {
		direction.x = float(int(IsKeyDown(KEY_RIGHT) - int(IsKeyDown(KEY_LEFT))));
		direction.z = float(int(IsKeyDown(KEY_DOWN) - int(IsKeyDown(KEY_UP))));

		float delta_time = GetFrameTime();

		pos.x+= direction.x * speed * delta_time;
		pos.z+= direction.z * speed * delta_time;

		std::cout << pos.x << pos.z << std::endl;

		BeginDrawing();
		ClearBackground(WHITE);
		BeginMode3D(camera);
		DrawGrid(10, 1);
		DrawModel(player, pos, 1.0, RED);
		DrawModel(obstacle, obstacle_pos, 1.0, GRAY);
		EndMode3D();
		EndDrawing();
	}
	CloseWindow();

}