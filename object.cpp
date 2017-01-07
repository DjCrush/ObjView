#include "object.h"

Object::Object()
{

	LightX = 0, LightY = 0, LightZ = -1;
	Dist = 100000;
}

void Object::DrawGuro(int x_c2, int y_c2, float type)
{
	float x1, x2, x3, y1, y2, y3;
	float intens1, intens2, intens3, length_normal, ax, ay, az;

	for (int l = 0; l < 7864320; l++) Z_buffer[l] = -100000;

	for (size_t l = 0; l < faces.size(); l++)
	{
		length_normal = sqrtf(faces[l].xn1*faces[l].xn1 + faces[l].yn1*faces[l].yn1 + faces[l].zn1*faces[l].zn1);
		ax = faces[l].xn1 / length_normal;
		ay = faces[l].yn1 / length_normal;
		az = faces[l].zn1 / length_normal;
		intens1 = (LightX * ax + LightY * ay + LightZ * az) * 255;
		if (intens1 < 0) intens1 =  -intens1;

		length_normal = sqrtf(faces[l].xn2*faces[l].xn2 + faces[l].yn2*faces[l].yn2 + faces[l].zn2*faces[l].zn2);
		ax = faces[l].xn2 / length_normal;
		ay = faces[l].yn2 / length_normal;
		az = faces[l].zn2 / length_normal;
		intens2 = (LightX * ax + LightY * ay + LightZ * az) * 255;
		if (intens2 < 0) intens2 =  -intens2;

		length_normal = sqrtf(faces[l].xn3*faces[l].xn3 + faces[l].yn3*faces[l].yn3 + faces[l].zn3*faces[l].zn3);
		ax = faces[l].xn3 / length_normal;
		ay = faces[l].yn3 / length_normal;
		az = faces[l].zn3 / length_normal;
		intens3 = (LightX * ax + LightY * ay + LightZ * az) * 255;
		if (intens3 < 0) intens3 =  -intens3;


		x1 = Dist*type*faces[l].x1 / (faces[l].z1*type + Dist) + x_c2;
		x2 = Dist*type*faces[l].x2 / (faces[l].z2*type + Dist) + x_c2;
		x3 = Dist*type*faces[l].x3 / (faces[l].z3*type + Dist) + x_c2;
		y1 = Dist*type*faces[l].y1 / (faces[l].z1*type + Dist) + y_c2;
		y2 = Dist*type*faces[l].y2 / (faces[l].z2*type + Dist) + y_c2;
		y3 = Dist*type*faces[l].y3 / (faces[l].z3*type + Dist) + y_c2;
		TriangleGradient(x1, x2, x3, y1, y2, y3, faces[l].z1*type, faces[l].z2*type, faces[l].z3*type, intens1, intens2, intens3);
	}
	SDL_Flip(screen);
}
void Object::Draw(int x_c2, int y_c2, float type)
{
	float x1, x2, x3, y1, y2, y3, col;
	float intens, length_normal, normalX, normalY, normalZ, ax, ay, az, bx, by, bz;

	for (int l = 0; l < 7864320; l++) Z_buffer[l] = -100000;

	for (size_t l = 0; l < faces.size(); l++)
	{
		ax = faces[l].x1 - faces[l].x2;
		ay = faces[l].y1 - faces[l].y2;
		az = faces[l].z1 - faces[l].z2;

		bx = faces[l].x2 - faces[l].x3;
		by = faces[l].y2 - faces[l].y3;
		bz = faces[l].z2 - faces[l].z3;

		normalX = ay * bz - az * by;
		normalY = az * bx - ax * bz;
		normalZ = ax * by - ay * bx;
		length_normal = sqrtf(normalX*normalX + normalY*normalY + normalZ*normalZ);
		normalX = normalX / length_normal;
		normalY = normalY / length_normal;
		normalZ = normalZ / length_normal;

		intens = (LightX * normalX + LightY * normalY + LightZ * normalZ);
		col = intens * 255;
		if (intens < 0) intens = -intens;
		x1 = Dist*type*faces[l].x1 / (faces[l].z1*type + Dist) + x_c2;
		x2 = Dist*type*faces[l].x2 / (faces[l].z2*type + Dist) + x_c2;
		x3 = Dist*type*faces[l].x3 / (faces[l].z3*type + Dist) + x_c2;
		y1 = Dist*type*faces[l].y1 / (faces[l].z1*type + Dist) + y_c2;
		y2 = Dist*type*faces[l].y2 / (faces[l].z2*type + Dist) + y_c2;
		y3 = Dist*type*faces[l].y3 / (faces[l].z3*type + Dist) + y_c2;
		Triangle(x1, x2, x3, y1, y2, y3, faces[l].z1*type, faces[l].z2*type, faces[l].z3*type, intens * 255);
	}
	SDL_Flip(screen);
}
void Object::Rotate(float AngleX)
{
	float ccm, ssm, temp;
	ccm = cos(AngleX * M_PI);
	ssm = sin(AngleX * M_PI);
	for (size_t l = 0; l < faces.size(); l++)
	{
		
		// Rotate vertexes
		temp = faces[l].x1*ccm - faces[l].z1*ssm;
		faces[l].z1 = faces[l].x1*ssm + faces[l].z1*ccm;
		faces[l].x1 = temp;
		temp = faces[l].x2*ccm - faces[l].z2*ssm;
		faces[l].z2 = faces[l].x2*ssm + faces[l].z2*ccm;
		faces[l].x2 = temp;
		 
		temp = faces[l].x3*ccm - faces[l].z3*ssm;
		faces[l].z3 = faces[l].x3*ssm + faces[l].z3*ccm;
		faces[l].x3 = temp;

		// Rotate normals
		temp = faces[l].xn1*ccm - faces[l].zn1*ssm;
		faces[l].zn1 = faces[l].xn1*ssm + faces[l].zn1*ccm;
		faces[l].xn1 = temp;
		temp = faces[l].xn2*ccm - faces[l].zn2*ssm;
		faces[l].zn2 = faces[l].xn2*ssm + faces[l].zn2*ccm;
		faces[l].xn2 = temp;

		temp = faces[l].xn3*ccm - faces[l].zn3*ssm;
		faces[l].zn3 = faces[l].xn3*ssm + faces[l].zn3*ccm;
		faces[l].xn3 = temp;



	}
}
void Object::ReadObjectFromOBJ(const char* filename)
{
	vector<point> vertex;
	vector<point> normal;

	float x, y, z;
	int point1, point2, point3, point4, point_normal1, point_normal2, point_normal3, point_normal4;
	int point_texture1, point_texture2, point_texture3, point_texture4;
	Uint32 Old_time;

	size_t length_of_file;
	string line, token;
	ifstream in;

	SDL_Rect Begunok;

	int n = 0;

	in.open(filename, ifstream::in);
	if (in.fail()) return;
	// get length of file
	in.seekg(0, in.end);
	length_of_file = in.tellg();
	in.seekg(0, in.beg);  
	
	Old_time = SDL_GetTicks()+200;
	
	while (!in.eof())
	{
		getline(in, line);
		marker = 0;
		token = GetToken(line);
		if (token == "v") {
			x = stof(GetToken(line));
			y = stof(GetToken(line));
			z = stof(GetToken(line));
			vertex.push_back(point(x, -y, z));
		}
		if (token == "vn") {
			x = stof(GetToken(line));
			y = stof(GetToken(line));
			z = stof(GetToken(line));
			normal.push_back(point(x, y, z));
		}
		if (token == "f")
		{

			point1 = stoi(GetToken(line)) - 1;
			token = GetToken(line);
			if (token == "/")
			{
				token = GetToken(line);
				if (token == "/")
				{
					point_normal1 = stoi(GetToken(line)) - 1;
					token = GetToken(line);
				}
				else
				{
					point_texture1 = stoi(token) - 1;
					token = GetToken(line);
					if (token == "/")
					{
						point_normal1 = stoi(GetToken(line)) - 1;
						token = GetToken(line);
					}

				}

			}

			point2 = stoi(token) - 1;
			token = GetToken(line);
			if (token == "/")
			{
				token = GetToken(line);
				if (token == "/")
				{
					point_normal2 = stoi(GetToken(line)) - 1;
					token = GetToken(line);
				}
				else
				{
					point_texture2 = stoi(token) - 1;
					token = GetToken(line);
					if (token == "/")
					{
						point_normal2 = stoi(GetToken(line)) - 1;
						token = GetToken(line);
					}

				}

			}

			point3 = stoi(token) - 1;
			token = GetToken(line);
			if (token == "/")
			{
				token = GetToken(line);
				if (token == "/")
				{
					point_normal3 = stoi(GetToken(line)) - 1;
					token = GetToken(line);
				}
				else
				{
					point_texture3 = stoi(token) - 1;
					token = GetToken(line);
					if (token == "/")
					{
						point_normal3 = stoi(GetToken(line)) - 1;
						token = GetToken(line);
					}

				}

			}
			if (token != "")
			{
				point4 = stoi(token) - 1;
				token = GetToken(line);
				if (token == "/")
				{
					token = GetToken(line);
					if (token == "/")
					{
						point_normal4 = stoi(GetToken(line)) - 1;
						token = GetToken(line);
					}
					else
					{
						point_texture4 = stoi(token) - 1;
						token = GetToken(line);
						if (token == "/")
						{
							point_normal4 = stoi(GetToken(line)) - 1;
							token = GetToken(line);
						}

					}

				}
				
				
				faces.push_back(polygon(vertex[point3].x, vertex[point3].y, vertex[point3].z,
					vertex[point4].x, vertex[point4].y, vertex[point4].z,
					vertex[point1].x, vertex[point1].y, vertex[point1].z,
					normal[point_normal3].x, normal[point_normal3].y, normal[point_normal3].z,
					normal[point_normal4].x, normal[point_normal4].y, normal[point_normal4].z,
					normal[point_normal1].x, normal[point_normal1].y, normal[point_normal1].z));

			}
			faces.push_back(polygon(vertex[point1].x, vertex[point1].y, vertex[point1].z,
				vertex[point2].x, vertex[point2].y, vertex[point2].z,
				vertex[point3].x, vertex[point3].y, vertex[point3].z,
				normal[point_normal1].x, normal[point_normal1].y, normal[point_normal1].z,
				normal[point_normal2].x, normal[point_normal2].y, normal[point_normal2].z,
				normal[point_normal3].x, normal[point_normal3].y, normal[point_normal3].z));
		}


		if (SDL_GetTicks() > Old_time)
		{
			Old_time = SDL_GetTicks() + 200;
			Begunok.x = 0;
			Begunok.y = 0;
			Begunok.h = 38;
			Begunok.w = 1024 * in.tellg() / length_of_file;
			SDL_FillRect(screen, &Begunok, 255);
			SDL_Flip(screen);
		}

		
	}

	
	Begunok.w = 1024;
	SDL_FillRect(screen, &Begunok, 255);
	SDL_Flip(screen);


	vertex.~vector();

}
string Object::GetToken(string my_string)
{
	string text;
	bool Word = 0;
	char bb;
	if (marker>=my_string.size()) return text;
	do {
		bb = my_string.at(marker++);
		if (bb == 47 && !Word) { text = "/"; break; }
		if (bb == 47 && Word) { marker--; break; }
		if (bb > 32 && !Word) Word = 1;
		if (Word && bb < 33) break;
		if (Word) text.push_back(bb);
	} while (marker < my_string.length());
	return text;
}
