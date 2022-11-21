#pragma once

struct tri3 {
	Vec3 p[3];
	int color;
};

struct Mesh {
	std::vector<tri3> polys;

	bool LoadObj(std::string filename) {
		std::ifstream file(filename);
		if (!file.is_open())	return false;

		std::vector<Vec3> vertices;

		while (!file.eof()) {
			char line[128];
			file.getline(line, 128);

			std::stringstream stream;
			stream << line;

			char junk;
			if (line[0] == 'v' && line[1] == ' ') {
				Vec3 v;
				stream >> junk >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}
			if (line[0] == 'f') {
				int f[4];

				//Read line
				for (int i = 0; i < 4; i++) {
					while (' ' != stream.peek()) stream.get();
					stream.get();
					f[i] = stream.get() % 48;

				}

				polys.push_back({ vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] });
				polys.push_back({ vertices[f[0] - 1], vertices[f[2] - 1], vertices[f[3] - 1] });
			}

		}

		return true;
	}
};

Vec3 VectorIntersectPlane(Vec3& plane_p, Vec3& plane_n, Vec3& lineStart, Vec3& lineEnd) {
	plane_n = Norm(plane_n);
	float plane_d = -Dot(plane_n, plane_p);
	float ad = Dot(lineStart, plane_n);
	float bd = Dot(lineEnd, plane_n);
	float t = (-plane_d - ad) / (bd - ad);
	Vec3 lineStartToEnd = lineEnd - lineStart;
	Vec3 lineToIntersect = lineStartToEnd * t;
	return lineStart + lineToIntersect;
};

int ClipTriangleAgainstPlane(Vec3 plane_p, Vec3 plane_n, tri3& in_tri, tri3& out_tri1, tri3& out_tri2) {

	plane_n = Norm(plane_n); //Make sure plane normal is unit vector

	auto dist = [&](Vec3& p) {
		Vec3 n = Norm(p);
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Dot(plane_n, plane_p)); //Return signed distance from point to plane
	};

	//Designate points as in plane or out of plane based on whether signed distance is positive or negative
	Vec3* inside_points[3]; int nInsidePointCount = 0;
	Vec3* outside_points[3]; int nOutsidePointCount = 0;

	float d0 = dist(in_tri.p[0]);
	float d1 = dist(in_tri.p[1]);
	float d2 = dist(in_tri.p[2]);

	if (d0 >= 0)	inside_points[nInsidePointCount++]		= &in_tri.p[0];
	else			outside_points[nOutsidePointCount++]	= &in_tri.p[0];
	if (d1 >= 0)	inside_points[nInsidePointCount++]		= &in_tri.p[1];
	else			outside_points[nOutsidePointCount++]	= &in_tri.p[1];
	if (d2 >= 0)	inside_points[nInsidePointCount++]		= &in_tri.p[2];
	else			outside_points[nOutsidePointCount++]	= &in_tri.p[2];

	if (nInsidePointCount == 0) return 0; //Triangle is complety outside of plane, destroy it
	if (nInsidePointCount == 3) {
		out_tri1 = in_tri; 
		return 1; //3 points are valid, return the orignal triangle
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2) {
		out_tri1.color = in_tri.color;

		out_tri1.p[0] = *inside_points[0];

		out_tri1.p[1] = VectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
		out_tri1.p[2] = VectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

		return 1; //1 point is valed, clip tre triangle down to a new triangle and return the triangle
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1) {
		out_tri1.color = in_tri.color;

		out_tri2.color = in_tri.color;

		out_tri1.p[0] = *inside_points[0];
		out_tri1.p[1] = *inside_points[1];
		out_tri1.p[2] = VectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

		out_tri2.p[0] = *inside_points[1];
		out_tri2.p[1] = out_tri1.p[2];
		out_tri2.p[2] = VectorIntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);
		return 2; //2 points are valid, split valid area into 2 triangles and return those
	}
};