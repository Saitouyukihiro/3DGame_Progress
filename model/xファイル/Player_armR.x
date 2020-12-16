xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 92;
 8.72870;2.26401;-2.21700;,
 8.72870;0.78568;-2.21700;,
 5.83009;0.78568;-2.21700;,
 5.83009;2.26401;-2.21700;,
 8.72870;-0.69265;-2.21700;,
 5.83009;-0.69265;-2.21700;,
 8.72870;-2.17099;-2.21700;,
 5.83009;-2.17099;-2.21700;,
 2.93147;0.78568;-2.21700;,
 2.93147;2.26401;-2.21700;,
 2.93147;-0.69265;-2.21700;,
 2.93147;-2.17099;-2.21700;,
 0.03286;0.78568;-2.21700;,
 0.03286;2.26401;-2.21700;,
 0.03286;-0.69265;-2.21700;,
 0.03286;-2.17099;-2.21700;,
 8.72870;-2.17099;-2.21700;,
 8.72870;-2.17099;-0.73867;,
 5.83009;-2.17099;-0.73867;,
 5.83009;-2.17099;-2.21700;,
 8.72870;-2.17099;0.73967;,
 5.83009;-2.17099;0.73967;,
 8.72870;-2.17099;2.21800;,
 5.83009;-2.17099;2.21800;,
 2.93147;-2.17099;-0.73867;,
 2.93147;-2.17099;-2.21700;,
 2.93147;-2.17099;0.73967;,
 2.93147;-2.17099;2.21800;,
 0.03286;-2.17099;-0.73867;,
 0.03286;-2.17099;-2.21700;,
 0.03286;-2.17099;0.73967;,
 0.03286;-2.17099;2.21800;,
 8.72870;-2.17099;2.21800;,
 8.72870;-0.69265;2.21800;,
 5.83009;-0.69265;2.21800;,
 5.83009;-2.17099;2.21800;,
 8.72870;0.78568;2.21800;,
 5.83009;0.78568;2.21800;,
 8.72870;2.26401;2.21800;,
 5.83009;2.26401;2.21800;,
 2.93147;-0.69265;2.21800;,
 2.93147;-2.17099;2.21800;,
 2.93147;0.78568;2.21800;,
 2.93147;2.26401;2.21800;,
 0.03286;-0.69265;2.21800;,
 0.03286;-2.17099;2.21800;,
 0.03286;0.78568;2.21800;,
 0.03286;2.26401;2.21800;,
 8.72870;2.26401;2.21800;,
 8.72870;2.26401;0.73967;,
 5.83009;2.26401;0.73967;,
 5.83009;2.26401;2.21800;,
 8.72870;2.26401;-0.73867;,
 5.83009;2.26401;-0.73867;,
 8.72870;2.26401;-2.21700;,
 5.83009;2.26401;-2.21700;,
 2.93147;2.26401;0.73967;,
 2.93147;2.26401;2.21800;,
 2.93147;2.26401;-0.73867;,
 2.93147;2.26401;-2.21700;,
 0.03286;2.26401;0.73967;,
 0.03286;2.26401;2.21800;,
 0.03286;2.26401;-0.73867;,
 0.03286;2.26401;-2.21700;,
 8.72870;0.78568;2.21800;,
 8.72870;0.78568;0.73967;,
 8.72870;2.26401;0.73967;,
 8.72870;-0.69265;2.21800;,
 8.72870;-0.69265;0.73967;,
 8.72870;-2.17099;0.73967;,
 8.72870;0.78568;-0.73867;,
 8.72870;2.26401;-0.73867;,
 8.72870;-0.69265;-0.73867;,
 8.72870;-2.17099;-0.73867;,
 8.72870;0.78568;-2.21700;,
 8.72870;2.26401;-2.21700;,
 8.72870;-0.69265;-2.21700;,
 8.72870;-2.17099;-2.21700;,
 0.03286;2.26401;0.73967;,
 0.03286;0.78568;0.73967;,
 0.03286;0.78568;2.21800;,
 0.03286;-0.69265;0.73967;,
 0.03286;-0.69265;2.21800;,
 0.03286;-2.17099;0.73967;,
 0.03286;2.26401;-0.73867;,
 0.03286;0.78568;-0.73867;,
 0.03286;-0.69265;-0.73867;,
 0.03286;-2.17099;-0.73867;,
 0.03286;2.26401;-2.21700;,
 0.03286;0.78568;-2.21700;,
 0.03286;-0.69265;-2.21700;,
 0.03286;-2.17099;-2.21700;;
 
 54;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;16,17,18,19;,
 4;17,20,21,18;,
 4;20,22,23,21;,
 4;19,18,24,25;,
 4;18,21,26,24;,
 4;21,23,27,26;,
 4;25,24,28,29;,
 4;24,26,30,28;,
 4;26,27,31,30;,
 4;32,33,34,35;,
 4;33,36,37,34;,
 4;36,38,39,37;,
 4;35,34,40,41;,
 4;34,37,42,40;,
 4;37,39,43,42;,
 4;41,40,44,45;,
 4;40,42,46,44;,
 4;42,43,47,46;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;52,54,55,53;,
 4;51,50,56,57;,
 4;50,53,58,56;,
 4;53,55,59,58;,
 4;57,56,60,61;,
 4;56,58,62,60;,
 4;58,59,63,62;,
 4;48,64,65,66;,
 4;64,67,68,65;,
 4;67,22,69,68;,
 4;66,65,70,71;,
 4;65,68,72,70;,
 4;68,69,73,72;,
 4;71,70,74,75;,
 4;70,72,76,74;,
 4;72,73,77,76;,
 4;78,79,80,61;,
 4;79,81,82,80;,
 4;81,83,31,82;,
 4;84,85,79,78;,
 4;85,86,81,79;,
 4;86,87,83,81;,
 4;88,89,85,84;,
 4;89,90,86,85;,
 4;90,91,87,86;;
 
 MeshMaterialList {
  4;
  54;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.649600;0.072000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.712000;0.580000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.075200;0.455200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.282400;0.031200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  54;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  92;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.333330;,
  0.000000;0.333330;,
  0.666670;0.000000;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.333330;0.666670;,
  0.000000;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.333330;1.000000;,
  0.666670;0.666670;,
  0.666670;1.000000;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;;
 }
}
