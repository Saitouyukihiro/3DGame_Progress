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
 26;
 -6.35945;4.13111;6.33314;,
 -12.62354;-5.14073;5.79287;,
 -11.89788;-3.27725;12.59321;,
 -6.35945;4.13111;6.33314;,
 -5.78548;-7.00422;5.68438;,
 -6.35945;4.13111;6.33314;,
 -5.05981;-5.14073;12.48471;,
 -6.35945;4.13111;6.33314;,
 -11.89788;-3.27725;12.59321;,
 -11.32391;-14.41257;11.94445;,
 -11.32391;-14.41257;11.94445;,
 -11.32391;-14.41257;11.94445;,
 -11.32391;-14.41257;11.94445;,
 0.03485;0.04454;0.25879;,
 -6.35995;-1.14061;1.90908;,
 -4.55825;1.12223;5.01345;,
 0.03485;0.04454;0.25879;,
 -3.99820;-4.49274;3.05148;,
 0.03485;0.04454;0.25879;,
 -2.19650;-2.22990;6.15583;,
 0.03485;0.04454;0.25879;,
 -4.55825;1.12223;5.01345;,
 -8.59133;-3.41505;7.80614;,
 -8.59133;-3.41505;7.80614;,
 -8.59133;-3.41505;7.80614;,
 -8.59133;-3.41505;7.80614;;
 
 16;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;2,1,9;,
 3;1,4,10;,
 3;4,6,11;,
 3;6,8,12;,
 3;13,14,15;,
 3;16,17,14;,
 3;18,19,17;,
 3;20,21,19;,
 3;15,14,22;,
 3;14,17,23;,
 3;17,19,24;,
 3;19,21,25;;
 
 MeshMaterialList {
  1;
  16;
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
   0.364000;0.003200;0.517600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  -0.825042;0.561233;-0.065754;,
  -0.963278;0.266862;0.029663;,
  -0.087951;-0.266862;-0.959713;,
  0.963278;-0.266862;-0.029664;,
  -0.990865;-0.058163;0.121673;,
  -0.274743;0.845897;-0.457138;,
  -0.547844;0.794716;-0.261330;,
  -0.418779;-0.543083;-0.727795;,
  0.547846;-0.794715;0.261330;,
  -0.757645;0.651710;-0.035326;,
  0.000012;0.058163;-0.998307;,
  0.990865;0.058163;-0.121675;,
  0.165811;0.561234;0.810878;,
  0.087952;0.266862;0.959713;,
  -0.165811;-0.561234;-0.810878;,
  0.825042;-0.561233;0.065753;,
  -0.000010;-0.058163;0.998307;,
  -0.154605;-0.414553;-0.896796;,
  0.757647;-0.651708;0.035324;,
  0.634851;0.609227;0.475192;,
  0.418782;0.543080;0.727795;,
  -0.634848;-0.609229;-0.475193;,
  0.274743;-0.845896;0.457140;,
  0.154607;0.414550;0.896797;;
  16;
  3;0,1,1;,
  3;10,2,2;,
  3;11,3,3;,
  3;12,13,13;,
  3;1,1,4;,
  3;2,2,14;,
  3;3,3,15;,
  3;13,13,16;,
  3;5,6,6;,
  3;17,7,7;,
  3;18,8,8;,
  3;19,20,20;,
  3;6,6,9;,
  3;7,7,21;,
  3;8,8,22;,
  3;20,20,23;;
 }
 MeshTextureCoords {
  26;
  0.125000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.375000;0.000000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  1.000000;0.500000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.125000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.375000;0.000000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  1.000000;0.500000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
