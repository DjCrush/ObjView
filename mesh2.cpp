#include "mesh.h"

Mesh::Mesh() : LightX{ 0 }, LightY{ 0 }, LightZ{ -1 }, Dist{ 100000 } {}

void Mesh::DrawGuro()
{
	double x1, x2, x3, y1, y2, y3;
	double intens1, intens2, intens3, length_normal, ax, ay, az;
	for (size_t l = 0; l < faces.size(); ++l)
	{
		length_normal = sqrtf(faces[l].p1.xn * faces[l].p1.xn + faces[l].p1.yn * faces[l].p1.yn + faces[l].p1.zn * faces[l].p1.zn);
		ax = faces[l].p1.xn / length_normal;
		ay = faces[l].p1.yn / length_normal;
		az = faces[l].p1.zn / length_normal;
		intens1 = (LightX * ax + LightY * ay + LightZ * az) * 255;
		if (intens1 < 0)
		{
			intens1 = -intens1;
		}
		length_normal = sqrtf(faces[l].p2.xn * faces[l].p2.xn + faces[l].p2.yn * faces[l].p2.yn + faces[l].p2.zn * faces[l].p2.zn);
		ax = faces[l].p2.xn / length_normal;
		ay = faces[l].p2.yn / length_normal;
		az = faces[l].p2.zn / length_normal;
		intens2 = (LightX * ax + LightY * ay + LightZ * az) * 255;
		if (intens2 < 0)
		{
			intens2 = -intens2;
		}
		length_normal = sqrtf(faces[l].p3.xn * faces[l].p3.xn + faces[l].p3.yn * faces[l].p3.yn + faces[l].p3.zn * faces[l].p3.zn);
		ax = faces[l].p3.xn / length_normal;
		ay = faces[l].p3.yn / length_normal;
		az = faces[l].p3.zn / length_normal;
		intens3 = (LightX * ax + LightY * ay + LightZ * az) * 255;
		if (intens3 < 0)
		{
			intens3 = -intens3;
		}
		x1 = Dist * faces[l].p1.x / (Dist - faces[l].p1.z) + WIDTH / 2;
		x2 = Dist * faces[l].p2.x / (Dist - faces[l].p2.z) + WIDTH / 2;
		x3 = Dist * faces[l].p3.x / (Dist - faces[l].p3.z) + WIDTH / 2;
		y1 = Dist * faces[l].p1.y / (Dist - faces[l].p1.z) + HEIGHT / 2;
		y2 = Dist * faces[l].p2.y / (Dist - faces[l].p2.z) + HEIGHT / 2;
		y3 = Dist * faces[l].p3.y / (Dist - faces[l].p3.z) + HEIGHT / 2;
		TriangleGradient(x1, x2, x3, y1, y2, y3, faces[l].p1.z, faces[l].p2.z, faces[l].p3.z, intens1, intens2, intens3);
	}
}
void Mesh::Draw()
{
	double x1, x2, x3, y1, y2, y3, col;
	double intens, length_normal, normalX, normalY, normalZ, ax, ay, az, bx, by, bz;
	for (size_t l = 0; l < faces.size(); l++)
	{
		ax = faces[l].p1.x - faces[l].p2.x;
		ay = faces[l].p1.y - faces[l].p2.y;
		az = faces[l].p1.z - faces[l].p2.z;
		bx = faces[l].p2.x - faces[l].p3.x;
		by = faces[l].p2.y - faces[l].p3.y;
		bz = faces[l].p2.z - faces[l].p3.z;
		normalX = ay * bz - az * by;
		normalY = az * bx - ax * bz;
		normalZ = ax * by - ay * bx;
		length_normal = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);
		normalX = normalX / length_normal;
		normalY = normalY / length_normal;
		normalZ = normalZ / length_normal;
		intens = (LightX * normalX + LightY * normalY + LightZ * normalZ);
		if (intens < 0)
		{
			intens = -intens;
		}
		x1 = Dist * faces[l].p1.x / (Dist - faces[l].p1.z) + WIDTH / 2;
		x2 = Dist * faces[l].p2.x / (Dist - faces[l].p2.z) + WIDTH / 2;
		x3 = Dist * faces[l].p3.x / (Dist - faces[l].p3.z) + WIDTH / 2;
		y1 = Dist * faces[l].p1.y / (Dist - faces[l].p1.z) + HEIGHT / 2;
		y2 = Dist * faces[l].p2.y / (Dist - faces[l].p2.z) + HEIGHT / 2;
		y3 = Dist * faces[l].p3.y / (Dist - faces[l].p3.z) + HEIGHT / 2;
		Triangle(x1, x2, x3, y1, y2, y3, faces[l].p1.z, faces[l].p2.z, faces[l].p3.z, intens * 255);
	}
}

void Mesh::Rotate(double AngleX)
{
	double ccm = cos(AngleX * DEG);
	double ssm = sin(AngleX * DEG);
	for (size_t l = 0; l < faces.size(); l++)
	{
		// Rotate vertexes
		double temp = faces[l].p1.x * ccm - faces[l].p1.z * ssm;
		faces[l].p1.z = faces[l].p1.x * ssm + faces[l].p1.z * ccm;
		faces[l].p1.x = temp;
		temp = faces[l].p2.x * ccm - faces[l].p2.z * ssm;
		faces[l].p2.z = faces[l].p2.x * ssm + faces[l].p2.z * ccm;
		faces[l].p2.x = temp;
		temp = faces[l].p3.x * ccm - faces[l].p3.z * ssm;
		faces[l].p3.z = faces[l].p3.x * ssm + faces[l].p3.z * ccm;
		faces[l].p3.x = temp;

		// Rotate normals
		temp = faces[l].p1.xn * ccm - faces[l].p1.zn * ssm;
		faces[l].p1.zn = faces[l].p1.xn * ssm + faces[l].p1.zn * ccm;
		faces[l].p1.xn = temp;
		temp = faces[l].p2.xn * ccm - faces[l].p2.zn * ssm;
		faces[l].p2.zn = faces[l].p2.xn * ssm + faces[l].p2.zn * ccm;
		faces[l].p2.xn = temp;
		temp = faces[l].p3.xn * ccm - faces[l].p3.zn * ssm;
		faces[l].p3.zn = faces[l].p3.xn * ssm + faces[l].p3.zn * ccm;
		faces[l].p3.xn = temp;
	}
}

void Mesh::Read(const char* filename)
{
	struct point
	{
		double x, y, z;
	};
	vector<point> vertex, normal;
	double x, y, z;
	int point1, point2, point3, point4, point_normal1, point_normal2, point_normal3, point_normal4;
	int point_texture1, point_texture2, point_texture3, point_texture4;
	Uint32 Old_time;
	size_t length_of_file;
	string line;

	ifstream in(filename, ios::in);
	if (in.fail()) return;
	// get length of file
	in.seekg(0, in.end);
	length_of_file = in.tellg();
	in.seekg(0, in.beg);
	Old_time = SDL_GetTicks() + 200;
	while (getline(in, line))
	{
		string t_line;
		stringstream t_stream(line);
		t_stream >> t_line;
		if (t_line == "v")
		{
			double x, y, z;
			t_stream >> x >> y >> z;
			vertex.push_back({ x, -y, z });
			cout << "v" << endl;
		}
		if (t_line == "vn")
		{
			double x, y, z;
			t_stream >> x >> y >> z;
			normal.push_back({ x, y, z });
		}
		if (t_line == "f")
		{
			string t_line2;
			t_stream >> t_line2;
			stringstream t_stream2(t_line2);
			string trash;
			getline(t_stream2, trash, '/');
			point1 = stod(trash) - 1;
			getline(t_stream2, trash, '/');
			point_normal1 = stod(trash) - 1;
			getline(t_stream2, trash);
			point_texture1 = stod(trash) - 1;
			cout << t_line2 << ' ';
			t_stream >> t_line2;
			
			getline(t_stream2, trash, '/');
			point2 = stod(trash) - 1;
			getline(t_stream2, trash, '/');
			point_normal2 = stod(trash) - 1;
			getline(t_stream2, trash);
			point_texture2 = stod(trash) - 1;

			t_stream >> t_line2;

			getline(t_stream2, trash, '/');
			point3 = stod(trash) - 1;
			getline(t_stream2, trash, '/');
			point_normal3 = stod(trash) - 1;
			getline(t_stream2, trash);
			point_texture3 = stod(trash) - 1;

			t_stream >> t_line2;
			if (!t_line2.empty())
			{
				stringstream t_stream2(t_line2);
				getline(t_stream2, trash, '/');
				point4 = stod(trash) - 1;
				getline(t_stream2, trash, '/');
				point_normal3 = stod(trash) - 1;
				getline(t_stream2, trash);
				point_texture3 = stod(trash) - 1;


				faces.push_back(Polygon(Point(vertex[point3].x, vertex[point3].y, vertex[point3].z, normal[point_normal3].x, normal[point_normal3].y, normal[point_normal3].z),
					Point(vertex[point4].x, vertex[point4].y, vertex[point4].z, normal[point_normal4].x, normal[point_normal4].y, normal[point_normal4].z),
					Point(vertex[point1].x, vertex[point1].y, vertex[point1].z, normal[point_normal1].x, normal[point_normal1].y, normal[point_normal1].z)));

			}
			faces.push_back(Polygon(Point(vertex[point1].x, vertex[point1].y, vertex[point1].z, normal[point_normal1].x, normal[point_normal1].y, normal[point_normal1].z),
				Point(vertex[point2].x, vertex[point2].y, vertex[point2].z, normal[point_normal2].x, normal[point_normal2].y, normal[point_normal2].z),
				Point(vertex[point3].x, vertex[point3].y, vertex[point3].z, normal[point_normal3].x, normal[point_normal3].y, normal[point_normal3].z)));
		}

		if (SDL_GetTicks() > Old_time)
		{
			Old_time = SDL_GetTicks() + 200;
			SDL_Rect rect = { 0, 0, 38, 1024 * in.tellg() / length_of_file };
			SDL_FillRect(screen, &rect, 255);
			SDL_Flip(screen);
		}
	}
	SDL_Rect rect = { 0, 0, 38, WIDTH };
	SDL_FillRect(screen, &rect, 255);
	SDL_Flip(screen);
}
