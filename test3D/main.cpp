#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <fstream>
#include <list>
#include "Vec3.hpp"
#include "Mat4.hpp"
#include "Mesh.hpp"
#include "RenderSettings.hpp"
#include <iostream>
using namespace std;

RenderSettings InitRS() {
	RenderSettings ini;
	ini.Watermark = true;
	ini.Wireframe = true;
	ini.xRes = 1920;
	ini.yRes = 1080;
	ini.depth = 32;
	ini.FOV = 105.0f;
	ini.xSens = 1.0f;
	ini.ySens = 1.0f;
	ini.DefaultText.r = 230;
	ini.DefaultText.g = 210;
	ini.DefaultText.b = 210;
	ini.DefaultText.a = 200;
	ini.windowMode = sf::Style::Default;
	return ini;
}
int main() {
	RenderSettings renderSettings = InitRS();

	//Version Number
	sf::String versionno = "Test 3D";
	sf::String watermark;
	sf::String sFPS;
	sf::String cameraX;
	sf::String cameraY;
	sf::String cameraZ;
	sf::String cameraYaw;
	int FPS;

	//Init Text
	sf::Font courierNew;
	courierNew.loadFromFile("Assets/courier-new.ttf");
	sf::Text watermarkText;
	watermarkText.setPosition(10.0f, 10.0f);
	watermarkText.setFont(courierNew);
	watermarkText.setCharacterSize(25);
	watermarkText.setFillColor(renderSettings.DefaultText);

	//Init Graphics
	Mesh obj;
	obj.LoadObj("Assets/Cube.obj");
	Vec3 camera = { 1,0,0 };
	float yaw = 0.0f;
	float pitch = 0.0f;
	Vec3 lookdir;
	Mat4 projection = ProjectionMatrix(renderSettings.FOV, float(renderSettings.yRes) / float(renderSettings.xRes), 0.1f, 1000.0f);
	float theta = 0.1f;

	//Define Monochrome Tint
	sf::Color sky(30, 30, 50, 255);

	//Open Window
	sf::RenderWindow window(
		sf::VideoMode(renderSettings.xRes, renderSettings.yRes),
		versionno, renderSettings.windowMode
	);

	//Init Time
	sf::Clock clock;
	float runtime = 0.0f;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)	window.close();

			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::F3)			renderSettings.Watermark = !renderSettings.Watermark;
				else if (event.key.code == sf::Keyboard::F4)	renderSettings.Wireframe = !renderSettings.Wireframe;
			}
		}

		//Get deltatime
		sf::Time delta = clock.restart();
		runtime += delta.asSeconds();

		//Clear with blank background
		window.clear(sky);

		//Update Game Logic
		Vec3 forward = VecxScalar(lookdir, 20.0f * delta.asSeconds());
		Vec3 up = { 0,0,1 };
		Vec3 right = Cross(lookdir, up);
		Vec3 cameraUp = Cross(right, lookdir);
		right = right * (20.0f * delta.asSeconds());
		cameraUp = cameraUp * (20.0f * delta.asSeconds());

		//Move Cam
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))		camera = camera + cameraUp;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))		camera = camera - cameraUp;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))		camera = camera + forward;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))		camera = camera - right;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))		camera = camera - forward;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))		camera = camera + right;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		yaw -= 2.0f * delta.asSeconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	yaw += 2.0f * delta.asSeconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		pitch += 2.0f * delta.asSeconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		pitch -= 2.0f * delta.asSeconds();

		//Clamp Cam
		if (yaw		>= 2.0f * 3.14159f)		yaw -= 2.0f * 3.14159f;
		if (yaw		<= 0.0f)				yaw += 2.0f * 3.14159f;
		if (pitch	>= 3.14159f / 2.0f)		pitch = 3.14100f / 2.0f;
		if (pitch	<= -3.14159f / 2.0f)	pitch = -3.14100f / 2.0f;

		Mat4 rotX, rotY, rotZ;
		theta += 1.0f * delta.asSeconds();

		//Define Cam rotation matrices
		rotZ = ZRotationMatrix(theta * 0.2f);
		rotY = YRotationMatrix(theta * 0.1f);
		rotX = XRotationMatrix(theta * 1.0f);

		//Move Triangles Away from cam
		Mat4 translation = TranslationMatrix(5.0f, 0.0f, 0.0f);

		Mat4 world = IdentityMatrix();
		world = rotZ * rotX;
		world = world * translation;
		Vec3 target = { 1,0,0 };
		Mat4 cameraRotation = ZRotationMatrix(-yaw);
		Mat4 pitchRotation = YRotationMatrix(pitch);
		cameraRotation = pitchRotation * cameraRotation;
		lookdir = cameraRotation * target;
		target = camera + lookdir;
		Mat4 cameraMatrix = PointingMatrix(camera, target, up);
		Mat4 viewMatrix = MatrixQuickInverse(cameraMatrix);

		//Draw mesh
		vector<tri3> triVector;
		for (auto tri : obj.polys) {
			tri3 projected, transformed, viewed;
			transformed.p[0] = world * tri.p[0];
			transformed.p[1] = world * tri.p[1];
			transformed.p[2] = world * tri.p[2];

			//Get normal
			Vec3 normal, line1, line2;
			line1 = transformed.p[1] - transformed.p[0];
			line2 = transformed.p[2] - transformed.p[0];
			normal = Cross(line1, line2);
			normal = Norm(normal);

			Vec3 cameraRay = transformed.p[0] - camera;

			if (Dot(normal, cameraRay) < 0.0f) {
				//Light Triangle
				Vec3 light = { -0.5f, -0.5f, -0.5f };
				light = Norm(light);
				float dotproduct = Dot(light, normal);

				//Move from World Frame to Camera Frame
				viewed.p[0] = viewMatrix * transformed.p[0];
				viewed.p[1] = viewMatrix * transformed.p[1];
				viewed.p[2] = viewMatrix * transformed.p[2];

				// Clip Viewed Triangle against near plane, this could form two additional triangles. 
				int nClippedTriangles = 0;
				tri3 clipped[2];
				nClippedTriangles = ClipTriangleAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, viewed, clipped[0], clipped[1]);

				// We may end up with multiple triangles form the clip, so project as required
				for (int n = 0; n < nClippedTriangles; n++) {

					//Project Triangles onto 2D
					projected.p[0] = projection * clipped[n].p[0];
					projected.p[1] = projection * clipped[n].p[1];
					projected.p[2] = projection * clipped[n].p[2];

					projected.p[0] = projected.p[0] / projected.p[0].w;
					projected.p[1] = projected.p[1] / projected.p[1].w;
					projected.p[2] = projected.p[2] / projected.p[2].w;

					//Unfuck perspective
					projected.p[0].x *= -1.0f;
					projected.p[1].x *= -1.0f;
					projected.p[2].x *= -1.0f;
					projected.p[0].y *= -1.0f;
					projected.p[1].y *= -1.0f;
					projected.p[2].y *= -1.0f;

					//Scale Triangles to Screen Size
					Vec3 offset = { 1, 1, 0 };
					projected.p[0] = projected.p[0] + offset;
					projected.p[1] = projected.p[1] + offset;
					projected.p[2] = projected.p[2] + offset;

					projected.p[0].x *= 0.5f * renderSettings.xRes;
					projected.p[0].y *= 0.5f * renderSettings.yRes;
					projected.p[1].x *= 0.5f * renderSettings.xRes;
					projected.p[1].y *= 0.5f * renderSettings.yRes;
					projected.p[2].x *= 0.5f * renderSettings.xRes;
					projected.p[2].y *= 0.5f * renderSettings.yRes;

					projected.color = 101 - dotproduct * 50;

					//Store Triangles For Sorting
					triVector.push_back(projected);
				}
			}
		}

		sort(triVector.begin(), triVector.end(), [](tri3& t1, tri3& t2) {
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
			return z1 > z2;
		});

		for (auto& triToRaster : triVector) {
			tri3 clipped[2];
			list<tri3> listTriangles;

			listTriangles.push_back(triToRaster);
			int nNewTriangles = 1;

			for (int p = 0; p < 4; p++) {
				int nTrisToAdd = 0;
				while (nNewTriangles > 0) {
					tri3 test = listTriangles.front();
					listTriangles.pop_front();
					nNewTriangles--;

					switch (p) {
					case 0:	nTrisToAdd = ClipTriangleAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]);							break;
					case 1:	nTrisToAdd = ClipTriangleAgainstPlane({ 0.0f, float(renderSettings.yRes) - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
					case 2:	nTrisToAdd = ClipTriangleAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]);							break;
					case 3:	nTrisToAdd = ClipTriangleAgainstPlane({ float(renderSettings.xRes) - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
					}

					for (int w = 0; w < nTrisToAdd; w++)
						listTriangles.push_back(clipped[w]);
				}
				nNewTriangles = listTriangles.size();
			}


			for (auto& Final : listTriangles) {
				//Draw Triangles to Window
				sf::VertexArray poly(sf::Triangles, 3);

				poly[0].position = sf::Vector2f(Final.p[0].x, Final.p[0].y);
				poly[1].position = sf::Vector2f(Final.p[1].x, Final.p[1].y);
				poly[2].position = sf::Vector2f(Final.p[2].x, Final.p[2].y);
				poly[0].color = sf::Color(Final.color + 100, Final.color, Final.color);
				poly[1].color = sf::Color(Final.color, Final.color + 100, Final.color);
				poly[2].color = sf::Color(Final.color, Final.color, Final.color + 100);

				window.draw(poly);

				//Draw Triangle's Wireframe if Wireframe is Enabled
				if (renderSettings.Wireframe == true) {
					sf::VertexArray wire(sf::LineStrip, 4);

					wire[0].position = sf::Vector2f(Final.p[0].x, Final.p[0].y);
					wire[1].position = sf::Vector2f(Final.p[1].x, Final.p[1].y);
					wire[2].position = sf::Vector2f(Final.p[2].x, Final.p[2].y);
					wire[3].position = sf::Vector2f(Final.p[0].x, Final.p[0].y);

					wire[0].color = sf::Color(200, 200, 200, 255);
					wire[1].color = sf::Color(200, 200, 200, 255);
					wire[2].color = sf::Color(200, 200, 200, 255);
					wire[3].color = sf::Color(200, 200, 200, 255);

					window.draw(wire);
				}
			}
		}

		//Draw Watermark
		if (renderSettings.Watermark) {
			FPS = 1;
			FPS /= delta.asSeconds();
			watermark = versionno;
			watermark += " (";
			watermark += to_string(FPS);
			watermark += " FPS)\nX: ";
			watermark += to_string(camera.x);
			watermark += "ft Y: ";
			watermark += to_string(camera.y);
			watermark += "ft Z: ";
			watermark += to_string(camera.z);
			watermark += L"ft\nθY:";
			watermark += to_string(yaw);
			watermark += L"RAD θP:";
			watermark += to_string(pitch);
			watermark += L"RAD";

			watermarkText.setString(watermark);
			window.draw(watermarkText);
		}

		window.display();
	}
	return 0;
}