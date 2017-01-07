#include "object.h"

Object::Object()
{

	LightX = 0, LightY = 0, LightZ = -1;
	Dist = 100000;
}
void Object::Draw(SDL_Surface *screen, int x_c2, int y_c2, float type)
{
	int x1, x2, x3, y1, y2, y3, idx, col;
	float intens, length_normal, normalX, normalY, normalZ, ax, ay, az, bx, by, bz;

	for (long l = 0; l < 7864320; l++) Z_buffer[l] = -100000;

	for (int l = 0; l < vv.size(); l++)
	{
		ax = vv[l].x1 - vv[l].x2;
		ay = vv[l].y1 - vv[l].y2;
		az = vv[l].z1 - vv[l].z2;

		bx = vv[l].x2 - vv[l].x3;
		by = vv[l].y2 - vv[l].y3;
		bz = vv[l].z2 - vv[l].z3;

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
		x1 = Dist*type*vv[l].x1 / (vv[l].z1*type + Dist) + x_c2;
		x2 = Dist*type*vv[l].x2 / (vv[l].z2*type + Dist) + x_c2;
		x3 = Dist*type*vv[l].x3 / (vv[l].z3*type + Dist) + x_c2;
		y1 = Dist*type*vv[l].y1 / (vv[l].z1*type + Dist) + y_c2;
		y2 = Dist*type*vv[l].y2 / (vv[l].z2*type + Dist) + y_c2;
		y3 = Dist*type*vv[l].y3 / (vv[l].z3*type + Dist) + y_c2;
		Triangle(screen, x1, x2, x3, y1, y2, y3, vv[l].z1*type, vv[l].z2*type, vv[l].z3*type, intens * 255);
	}
	SDL_Flip(screen);
}
void Object::Rotate(float AngleX)
{
	float ccm, ssm, xt, yt, zt;
	ccm = cos(AngleX * M_PI);
	ssm = sin(AngleX * M_PI);
	for (int l = 0; l < vv.size(); l++)
	{
		xt = vv[l].x1*ccm - vv[l].z1*ssm;
		zt = vv[l].x1*ssm + vv[l].z1*ccm;
		vv[l].x1 = xt;
		vv[l].z1 = zt;
		xt = vv[l].x2*ccm - vv[l].z2*ssm;
		zt = vv[l].x2*ssm + vv[l].z2*ccm;
		vv[l].x2 = xt;
		vv[l].z2 = zt;
		xt = vv[l].x3*ccm - vv[l].z3*ssm;
		zt = vv[l].x3*ssm + vv[l].z3*ccm;
		vv[l].x3 = xt;
		vv[l].z3 = zt;


	}
}
void Object::ReadObjectFromOBJ(const char* filename, SDL_Surface *screen)
{
	vector<my_vertex> vect;

	float x, y, z;
	int vertex1, vertex2, vertex3, vertex4, normal1, normal2, normal3, normal4;
	int texture1, texture2, texture3, texture4;
	Uint32 Old_time, New_time;

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
			vect.push_back(my_vertex(x, -y, z));
		}
		if (token == "f")
		{

			vertex1 = stoi(GetToken(line));
			token = GetToken(line);
			if (token == "/")
			{
				token = GetToken(line);
				if (token == "/")
				{
					normal1 = stoi(GetToken(line));
					token = GetToken(line);
				}
				else
				{
					texture1 = stoi(token);
					token = GetToken(line);
					if (token == "/")
					{
						normal1 = stoi(GetToken(line));
						token = GetToken(line);
					}

				}

			}

			vertex2 = stoi(token);
			token = GetToken(line);
			if (token == "/")
			{
				token = GetToken(line);
				if (token == "/")
				{
					normal2 = stoi(GetToken(line));
					token = GetToken(line);
				}
				else
				{
					texture2 = stoi(token);
					token = GetToken(line);
					if (token == "/")
					{
						normal2 = stoi(GetToken(line));
						token = GetToken(line);
					}

				}

			}

			vertex3 = stoi(token);
			token = GetToken(line);
			if (token == "/")
			{
				token = GetToken(line);
				if (token == "/")
				{
					normal3 = stoi(GetToken(line));
					token = GetToken(line);
				}
				else
				{
					texture3 = stoi(token);
					token = GetToken(line);
					if (token == "/")
					{
						normal3 = stoi(GetToken(line));
						token = GetToken(line);
					}

				}

			}
			if (token != "")
			{
				vertex4 = stoi(token);
				token = GetToken(line);
				if (token == "/")
				{
					token = GetToken(line);
					if (token == "/")
					{
						normal4 = stoi(GetToken(line));
						token = GetToken(line);
					}
					else
					{
						texture4 = stoi(token);
						token = GetToken(line);
						if (token == "/")
						{
							normal4 = stoi(GetToken(line));
							token = GetToken(line);
						}

					}

				}
				vv.push_back(polygon(vect[vertex3 - 1].x, vect[vertex3 - 1].y, vect[vertex3 - 1].z,
					vect[vertex4 - 1].x, vect[vertex4 - 1].y, vect[vertex4 - 1].z,
					vect[vertex1 - 1].x, vect[vertex1 - 1].y, vect[vertex1 - 1].z));

			}
			vv.push_back(polygon(vect[vertex1 - 1].x, vect[vertex1 - 1].y, vect[vertex1 - 1].z,
				vect[vertex2 - 1].x, vect[vertex2 - 1].y, vect[vertex2 - 1].z,
				vect[vertex3 - 1].x, vect[vertex3 - 1].y, vect[vertex3 - 1].z));
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


	vect.~vector();

}
string Object::GetToken(string my_string)
{
	string text;
	bool Word = 0;
	char bb;
	if (marker>=my_string.size()) return text;
	do {
		bb = my_string.at(marker);
		marker++;
		if (bb == 47 && !Word) { text = "/"; break; }
		if (bb == 47 && Word) { marker--; break; }
		if (bb > 32 && !Word) Word = 1;
		if (Word && bb < 33) break;
		if (Word) text.push_back(bb);
	} while (marker < my_string.length());
	return text;
}
