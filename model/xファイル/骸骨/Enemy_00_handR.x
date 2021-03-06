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
 46;
 -0.01206;-0.16771;-0.40651;,
 0.34596;-0.16771;-0.19982;,
 0.34596;-3.55662;-0.19982;,
 -0.01206;-3.55662;-0.40651;,
 0.34596;-0.16771;0.21358;,
 0.34596;-3.55662;0.21358;,
 -0.01206;-0.16771;0.42028;,
 -0.01206;-3.55662;0.42028;,
 -0.37006;-0.16771;0.21358;,
 -0.37006;-3.55662;0.21358;,
 -0.37006;-0.16771;-0.19982;,
 -0.37006;-3.55662;-0.19982;,
 -0.01206;-0.16771;-0.40651;,
 -0.01206;-3.55662;-0.40651;,
 -0.01206;-0.02916;0.00688;,
 -0.01206;-0.02916;0.00688;,
 -0.01206;-0.02916;0.00688;,
 -0.01206;-0.02916;0.00688;,
 -0.01206;-0.02916;0.00688;,
 -0.01206;-0.02916;0.00688;,
 -0.01206;-3.68096;0.00688;,
 -0.01206;-3.68096;0.00688;,
 -0.01206;-3.68096;0.00688;,
 -0.01206;-3.68096;0.00688;,
 -0.01206;-3.68096;0.00688;,
 -0.01206;-3.68096;0.00688;,
 -0.40480;-3.65274;-0.00448;,
 0.39274;-3.65274;-0.00448;,
 0.39274;-3.65274;-0.21717;,
 -0.40480;-3.65274;-0.21717;,
 0.39274;-3.65274;-0.00448;,
 0.39274;-4.80631;-0.00448;,
 0.39274;-4.80631;-0.21717;,
 0.39274;-3.65274;-0.21717;,
 0.39274;-4.80631;-0.00448;,
 -0.40480;-4.80631;-0.00448;,
 -0.40480;-4.80631;-0.21717;,
 0.39274;-4.80631;-0.21717;,
 -0.40480;-4.80631;-0.00448;,
 -0.40480;-3.65274;-0.00448;,
 -0.40480;-3.65274;-0.21717;,
 -0.40480;-4.80631;-0.21717;,
 0.39274;-3.65274;-0.00448;,
 -0.40480;-3.65274;-0.00448;,
 -0.40480;-3.65274;-0.21717;,
 0.39274;-3.65274;-0.21717;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;14,1,0;,
 3;15,4,1;,
 3;16,6,4;,
 3;17,8,6;,
 3;18,10,8;,
 3;19,12,10;,
 3;20,3,2;,
 3;21,2,5;,
 3;22,5,7;,
 3;23,7,9;,
 3;24,9,11;,
 3;25,11,13;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;38,31,42,43;,
 4;44,45,32,41;;
 
 MeshMaterialList {
  2;
  24;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  -0.000007;1.000000;-0.000003;,
  0.499977;0.000000;-0.866039;,
  1.000000;0.000000;0.000000;,
  0.499995;0.000000;0.866028;,
  -0.500016;0.000000;0.866016;,
  -1.000000;0.000000;0.000000;,
  -0.000006;-1.000000;-0.000002;,
  -0.499997;0.000000;-0.866027;,
  0.275196;0.948167;-0.158892;,
  -0.000005;0.948164;-0.317782;,
  0.275198;0.948167;0.158888;,
  -0.000005;0.948166;0.317775;,
  -0.275212;0.948163;0.158888;,
  -0.275210;0.948163;-0.158891;,
  -0.000005;-0.957620;-0.288034;,
  0.249434;-0.957623;-0.144017;,
  0.249436;-0.957623;0.144014;,
  -0.000005;-0.957622;0.288028;,
  -0.249449;-0.957619;0.144014;,
  -0.249447;-0.957619;-0.144017;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;;
  24;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,7,7,7;,
  3;0,8,9;,
  3;0,10,8;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,9,13;,
  3;6,14,15;,
  3;6,15,16;,
  3;6,16,17;,
  3;6,17,18;,
  3;6,18,19;,
  3;6,19,14;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;;
 }
 MeshTextureCoords {
  46;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
