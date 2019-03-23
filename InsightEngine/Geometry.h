#pragma once

namespace insight{
	struct Vertex_Pos_Color {
		XMFLOAT3 pos;
		XMFLOAT4 color;
	};

	struct VSConstBuffer {
		XMFLOAT4X4 world;
		XMFLOAT4X4 view;
		XMFLOAT4X4 proj;
	};

}