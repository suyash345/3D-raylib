#include <raylib.h>

int main() {
	InitWindow(1920, 1080, "3D base");
	Camera3D camera;
	camera.position = Vector3(0.0f, 5.0f, 5.0f);
	camera.target = Vector3{0.0f,0.0f,0.0f};
	camera.up = Vector3{ 0,1,0 };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	Mesh mesh = GenMeshCube(1, 1, 1);
	Model model = LoadModelFromMesh(mesh);


	while (!WindowShouldClose()) {
		int delta_time = GetFrameTime();
		ClearBackground(WHITE);
		BeginDrawing();
		BeginMode3D(camera);
		DrawGrid(10, 1);
		DrawLine3D({ -4.0f,0.0f,-2.0f }, { 5.0f,2.0f,3.0f }, BLACK);
		DrawModel(model, Vector3{ 0.0f,0.0f,0.0f }, 1, RED);
		EndMode3D();

		EndDrawing();
	}
	CloseWindow();
}