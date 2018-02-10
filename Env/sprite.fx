#include "./union.fx"

struct PS_INPUT {
	float4 PosProj	: SV_POSITION; //頂点座標（プロジェクション）
	float2 Tex	: TEXTURE;	//テクスチャ座標
};


VS_INPUT VS_MAIN(VS_INPUT input) {
	VS_INPUT output;
	output = input;
	return output;
}

// ジオメトリ シェーダの関数
[maxvertexcount(3)]
void GS_MAIN(triangle VS_INPUT input[3],
	inout TriangleStream<PS_INPUT> TriStream) {

	PS_INPUT output;

	for (int i = 0; i < 3; ++i) {
		
		//float4 lPosWor = mul(float4(input[i].Pos, 1.0f), World);
		//float4 lPosView = mul(lPosWor, View);
		//float4 lPosProj = mul(lPosView, Projection);
		output.PosProj = float4(input[i].Pos, 1.0f);

		output.Tex = input[i].Tex;

		TriStream.Append(output);
	}
	TriStream.RestartStrip();
}


struct PS_OUTPUT {
	float4 Diffuse	: SV_TARGET0;
};


PS_OUTPUT PS_MAIN(PS_INPUT input) {

	PS_OUTPUT output;

	float4 diffuseTexel = DiffuseTexture.Sample(DiffuseSampler, input.Tex);
	
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	color *= diffuseTexel;
	output.Diffuse = color;

	return output;
}
