cbuffer CB{
    matrix w;
    matrix v;
    matrix p;
}

struct VertexIn{
	float3 posL : POSITION;
	float4 color : COLOR;
};

struct VertexOut{
	float4 posH : SV_POSITION;
	float4 color : COLOR;
};

VertexOut VS(VertexIn vIn){
    VertexOut vOut;
    vOut.posH = mul(float4(vIn.posL, 1.0f),w);
    vOut.posH = mul(vOut.posH, v);
    vOut.posH = mul(vOut.posH, p);
    vOut.color = vIn.color;
    return vOut;
}

float4 PS(VertexOut pIn) : SV_Target{
    return pIn.color;
}
