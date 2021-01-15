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
 5.61043;3.99552;7.06766;,
 4.52627;-5.27633;13.26084;,
 11.36398;-3.41285;13.13063;,
 5.61043;3.99552;7.06766;,
 5.01416;-7.13982;6.43933;,
 5.61043;3.99552;7.06766;,
 11.85188;-5.27633;6.30911;,
 5.61043;3.99552;7.06766;,
 11.36398;-3.41285;13.13063;,
 10.76772;-14.54816;12.50230;,
 10.76772;-14.54816;12.50230;,
 10.76772;-14.54816;12.50230;,
 10.76772;-14.54816;12.50230;,
 0.11649;-0.09106;0.16827;,
 1.20316;-1.27621;6.68257;,
 4.45274;0.98663;5.15829;,
 0.11649;-0.09106;0.16827;,
 2.54706;-4.62834;4.42938;,
 0.11649;-0.09106;0.16827;,
 5.79662;-2.36550;2.90509;,
 0.11649;-0.09106;0.16827;,
 4.45274;0.98663;5.15829;,
 6.88331;-3.55065;9.41943;,
 6.88331;-3.55065;9.41943;,
 6.88331;-3.55065;9.41943;,
 6.88331;-3.55065;9.41943;;
 
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
   0.452000;0.000000;0.558400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  -0.137411;0.561233;0.816171;,
  -0.054405;0.266862;0.962198;,
  -0.963726;-0.266863;0.003973;,
  0.054404;-0.266863;-0.962198;,
  0.034850;-0.058163;0.997699;,
  -0.479344;0.845896;0.233855;,
  -0.308084;0.794716;0.522983;,
  -0.761524;-0.543083;0.353754;,
  0.308083;-0.794715;-0.522985;,
  -0.101225;0.651710;0.751683;,
  -0.994507;0.058164;-0.087019;,
  -0.034852;0.058163;-0.997699;,
  0.822244;0.561234;-0.094506;,
  0.963726;0.266863;-0.003971;,
  -0.822243;-0.561235;0.094509;,
  0.137410;-0.561235;-0.816170;,
  0.994507;-0.058163;0.087019;,
  -0.906857;-0.414555;0.075855;,
  0.101222;-0.651709;-0.751685;,
  0.528714;0.609228;-0.591019;,
  0.761524;0.543082;-0.353756;,
  -0.528715;-0.609228;0.591017;,
  0.479346;-0.845896;-0.233855;,
  0.906858;0.414552;-0.075858;;
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
