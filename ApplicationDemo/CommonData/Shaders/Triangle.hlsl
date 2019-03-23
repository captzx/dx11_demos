cbuffer VSConstBuffer{
    float4x4 WorldMatrix;
    float4x4 ViewMatrix;
    float4x4 ProjMatrix;
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
    vOut.posH = mul(float4(vIn.posL, 1.0f),WorldMatrix);
    vOut.posH = mul(vOut.posH, ViewMatrix);
    vOut.posH = mul(vOut.posH, ProjMatrix);
    vOut.color = vIn.color;
    return vOut;
}

float4 PS(VertexOut pIn) : SV_Target{
    return pIn.color;
}
