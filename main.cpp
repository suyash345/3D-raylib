#include <raylib.h>
#include  <iostream>

int main() {
	InitWindow(1920, 1080, "3D base");
	Camera3D camera;
	camera.position = Vector3{ 0.0f, 5.0f, 5.0f };
	camera.target = Vector3{0.0f,0.0f,0.0f};
	camera.up = Vector3{ 0,1,0 };
	camera.fovy = 90.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	//Mesh mesh = GenMeshCube(1, 1, 1);
	//Model model = LoadModelFromMesh(mesh);

	Mesh cylinder = GenMeshCylinder(1, 2, 20); // more slices for round objects
	Model model = LoadModelFromMesh(cylinder);


	// texture

	Image image = GenImageGradientLinear(20, 20, 1, RED, YELLOW);
	Texture texture = LoadTextureFromImage(image);
	SetMaterialTexture(&model.materials[0], MATERIAL_MAP_ALBEDO, texture);


	// Move
	Vector3 pos = { 0.0f,0.0f,0.0f };

	while (!WindowShouldClose()) {
		float delta_time = GetFrameTime();
		pos.x += 2 * delta_time;
		std::cout << pos.x << std::endl;
		ClearBackground(WHITE);
		BeginDrawing();
		BeginMode3D(camera);
		DrawGrid(10, 1);
		DrawLine3D({ -4.0f,0.0f,-2.0f }, { 5.0f,2.0f,3.0f }, BLACK);
		DrawModel(model, pos, 1, WHITE);
		EndMode3D();

		EndDrawing();
	}
	CloseWindow();
}