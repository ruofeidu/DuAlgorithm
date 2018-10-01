#pragma once
#include "common.h"

namespace Bin2Ply {
	using byte = unsigned char;
	class Vertex {
	public:
		float position[3], normal[3];
		byte color[3];
	};

	class Face {
	public:
		unsigned int id[3];
	};

	class Model	{
	public:
		int n;
		int m;
		Vertex* vertex;
		Face* face;
	};


	int bin2ply()
	{
		FILE *fin = fopen("model.bin", "rb");
		freopen("model.ply", "w", stdout);

		Model model;
		fread(&model.n, sizeof(model.n), 1, fin);
		fread(&model.m, sizeof(model.m), 1, fin);

		model.vertex = new Vertex[model.n];
		model.face = new Face[model.m];
		byte blank;

		for (int i = 0; i < model.n; ++i) {
			fread(&model.vertex[i].position, sizeof(float), 3, fin);
			fread(&model.vertex[i].normal, sizeof(float), 3, fin);
			fread(&model.vertex[i].color, sizeof(byte), 3, fin);
			fread(&blank, sizeof(byte), 1, fin);
		}
		for (int i = 0; i < model.m; ++i) {
			fread(&model.face[i].id, sizeof(unsigned int), 3, fin);
		}
		fclose(fin);

		printf("ply\n");
		printf("format ascii 1.0\n");
		printf("element vertex %d\n", model.n);
		printf("property float x\n");
		printf("property float y\n");
		printf("property float z\n");
		printf("property float nx\n");
		printf("property float ny\n");
		printf("property float nz\n");
		printf("property uchar diffuse_red\n");
		printf("property uchar diffuse_green\n");
		printf("property uchar diffuse_blue\n");
		printf("element face %d\n", model.m);
		printf("property list uchar int vertex_index\n");
		printf("end_header\n");

		for (int i = 0; i < model.n; ++i)
		{
			printf("%.8f %.8f %.8f ", model.vertex[i].position[0], model.vertex[i].position[1], model.vertex[i].position[2]);
			printf("%.8f %.8f %.8f ", model.vertex[i].normal[0], model.vertex[i].normal[1], model.vertex[i].normal[2]);
			printf("%d %d %d\n", model.vertex[i].color[0], model.vertex[i].color[1], model.vertex[i].color[2]);
		}
		for (int i = 0; i < model.m; ++i)
		{
			printf("3 %d %d %d\n", model.face[i].id[0], model.face[i].id[1], model.face[i].id[2]);
		}
		printf("\n");
		fclose(stdout);

		freopen("model.inc", "w", stdout);
		printf("#declare m_solid_hand = mesh {\n");
		for (int i = 0; i < model.m; ++i) {
			printf("  triangle { // #%d\n", i);
			for (int j = 0; j < 3; ++j)	{
				printf("    <%.6f, %.6f, %.6f>", model.vertex[model.face[i].id[j]].position[0], model.vertex[model.face[i].id[j]].position[1], model.vertex[model.face[i].id[j]].position[2]);
				if (j != 2) printf(",\n"); else printf("\n");
			}
			printf("  }\n");
		}
		printf("} // end of mesh\n");
		return 0;
	}
}
