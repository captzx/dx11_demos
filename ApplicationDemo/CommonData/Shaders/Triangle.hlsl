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
    vOut.posH = float4(vIn.posL, 1.0f);
    vOut.color = vIn.color;
    return vOut;
}

float4 PS(VertexOut pIn) : SV_Target{
    return pIn.color;
}
