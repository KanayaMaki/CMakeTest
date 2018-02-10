#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

namespace cpot {


struct PmxData {
public:
	#pragma pack(push,1)

	struct TextBuf {
		Vector<CHAR> buf;
	};

	String<256> fileName;

	struct Header {
		u8 pmx[4];
		f32 ver;
		u8 byteSize;
		u8 byteSizes[8];	//本来は上のbyteSizeの大きさ
	} header;

	struct ModelData {
		TextBuf name;
		TextBuf nameEng;
		TextBuf comment;
		TextBuf commentEng;
	} modelData;

	struct Vertex {
		f32 location[3];
		f32 normal[3];
		f32 uv[2];
		VectorSimple<f32> addUV;	//追加UV * 16バイト
		u8 weightType;	//ウェイト変形方式
		struct BoneWeight {
			u8 index[4];
			f32 weight[3];
		} weight;
		f32 edgeTimes;
	};
	VectorSimple<Vertex> vertexs;

	VectorSimple<s32> indexs;

	struct Texture {
		TextBuf fileName;
	};
	VectorSimple<Texture> textures;
	
	struct Material {
		TextBuf name;
		TextBuf nameEng;
		f32 diffuse[4];
		f32 specular[3];
		f32 specularPow;
		f32 ambient[3];
		u8 drawFlag;
		f32 edgeColor[4];
		f32 edgeSize;
		s32 textureRef;	//型が可変
		s32 sphereRef;	//型が可変
		u8 sphereMode;
		u8 unionToonFlag;
		s32 toonTexture;
		TextBuf memo;
		s32 indexNum;
	};
	VectorSimple<Material> materials;

	struct Bone {
		TextBuf name;
		TextBuf nameEng;
		f32 location[3];
		s32 parentIndex;	//親ボーンのIndex
		s32 transe;	//変形階層
		u16 boneFlag;
		VectorSimple<u8> addData;	//ボーンフラグによって変化
	};
	VectorSimple<Bone> bones;

	struct Morph {
		TextBuf name;
		TextBuf nameEng;
		u8 panel;
		u8 morphType;
		s32 offsetNum;
		VectorSimple<u8> offsetData;
	};
	VectorSimple<Morph> morphs;

	struct VertexMorph {
		s32 vertexIndex;
		f32 locOffset[3];
	};
	struct UVMorph {
		s32 vertexIndex;
		f32 uvOffset[4];
	};
	struct BoneMorph {
		s32 boneIndex;
		f32 move[3];
		f32 rotate[4];
	};
	struct MaterialMorph {
		s32 materialIndex;
		u8 offsetCalMode;
		f32 diffuse[4];
		f32 specular[3];
		f32 supecularPow;
		f32 ambient[3];
		f32 edgeColor[4];
		f32 edgeSize;
		f32 texTimes[4];	//テクスチャ係数
		f32 sphereTexTimes[4];
		f32 toonTexTimes[4];
	};
	struct GroupMorph {
		s32 morphIndex;
		f32 times;
	};

	struct ShowFrame {
		TextBuf name;
		TextBuf nameEng;
		u8 flag;
		struct Element {
			u8 type;
			s32 data;
		};
		VectorSimple<Element> elements;
	};
	VectorSimple<ShowFrame> showFrames;

	struct Physics {
		TextBuf name;
		TextBuf nameEng;
		s32 boneIndex;
		u8 group;
		u16 noHitGroupFlag;
		u8 shapeType;
		f32 size[3];
		f32 location[3];
		f32 rotate[3];
		f32 mass;
		f32 moveDec;
		f32 rotateDec;
		f32 counterPower;
		f32 masatuPower;
		u8 calType;
	};
	VectorSimple<Physics> physicses;

	struct Joint {
		TextBuf name;
		TextBuf nameEng;
		u8 type;
		s32 aIndex;
		s32 bIndex;
		f32 location[3];
		f32 rotate[3];
		f32 moveLimitMin[3];
		f32 moveLimitMax[3];
		f32 rotateLimitMin[3];
		f32 rotateLimitMax[3];
		f32 springConstantMove[3];
		f32 springConstantRotate[3];
	};
	VectorSimple<Joint> joints;

	#pragma pack(pop)
};


}
