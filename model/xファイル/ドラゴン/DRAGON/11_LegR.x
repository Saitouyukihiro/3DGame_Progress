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
 124;
 2.74327;-34.40760;-8.79729;,
 10.33013;-18.70596;-7.82171;,
 10.95219;-18.73858;-3.79244;,
 4.06345;-34.40760;-0.46200;,
 -5.33090;-35.08000;2.96394;,
 -7.24998;-35.08000;-9.15253;,
 -1.73989;-19.50405;-8.15046;,
 -7.24998;-35.08000;-9.15253;,
 -0.55588;-19.53667;-0.03527;,
 -10.09793;-20.33986;-6.76345;,
 -6.72728;6.45169;1.91467;,
 6.38275;-2.79712;-2.28744;,
 -1.73989;-19.50405;-8.15046;,
 -10.09793;-20.33986;-6.76345;,
 -8.77774;-20.33986;1.57187;,
 -8.77774;-20.33986;1.57187;,
 -0.55588;-19.53667;-0.03527;,
 6.38275;-2.79712;-2.28744;,
 -6.72728;6.45169;1.91467;,
 4.57022;-12.60124;-6.83626;,
 5.19500;-12.60124;-2.89160;,
 10.95219;-18.73858;-3.79244;,
 10.33013;-18.70596;-7.82171;,
 -1.73989;-19.50405;-8.15046;,
 4.57022;-12.60124;-6.83626;,
 10.33013;-18.70596;-7.82171;,
 -0.55588;-19.53667;-0.03527;,
 10.95219;-18.73858;-3.79244;,
 5.19500;-12.60124;-2.89160;,
 6.38275;-2.79712;-2.28744;,
 6.38275;-2.79712;-2.28744;,
 -6.72728;6.45169;1.91467;,
 6.38275;-2.79712;-2.28744;,
 -11.94378;-36.24763;-11.51813;,
 -8.70879;-33.69738;-9.86808;,
 -8.12608;-34.37967;-10.49068;,
 -11.94378;-36.24763;-11.51813;,
 -9.07091;-33.89221;-9.11183;,
 -8.70879;-33.69738;-9.86808;,
 -11.94378;-36.24763;-11.51813;,
 -9.03526;-34.65121;-8.72169;,
 -11.94378;-36.24763;-11.51813;,
 -8.27074;-35.45353;-9.59391;,
 -9.03526;-34.65121;-8.72169;,
 -11.94378;-36.24763;-11.51813;,
 -8.12608;-34.37967;-10.49068;,
 -8.27074;-35.45353;-9.59391;,
 -8.27074;-35.45353;-9.59391;,
 -8.12608;-34.37967;-10.49068;,
 -5.46102;-33.63909;-9.60724;,
 -6.14688;-35.41451;-8.45796;,
 -8.12608;-34.37967;-10.49068;,
 -8.70879;-33.69738;-9.86808;,
 -6.08505;-32.51107;-8.46432;,
 -5.46102;-33.63909;-9.60724;,
 -8.27074;-35.45353;-9.59391;,
 -6.14688;-35.41451;-8.45796;,
 -6.93998;-33.89122;-7.00210;,
 -9.03526;-34.65121;-8.72169;,
 -8.70879;-33.69738;-9.86808;,
 -9.07091;-33.89221;-9.11183;,
 -6.93998;-33.89122;-7.00210;,
 -6.08505;-32.51107;-8.46432;,
 -4.51345;-34.06401;-7.32733;,
 -4.51345;-34.06401;-7.32733;,
 -11.73141;-36.77994;-1.74884;,
 -7.77409;-33.46962;-2.14102;,
 -7.49879;-34.98953;-3.48865;,
 -11.73141;-36.77994;-1.74884;,
 -7.08967;-34.98232;-0.86747;,
 -7.77409;-33.46962;-2.14102;,
 -11.73141;-36.77994;-1.74884;,
 -7.49879;-34.98953;-3.48865;,
 -7.08967;-34.98232;-0.86747;,
 -7.49879;-34.98953;-3.48865;,
 -4.66234;-33.89837;-4.53221;,
 -4.13588;-34.29872;-0.89289;,
 -7.08967;-34.98232;-0.86747;,
 -7.49879;-34.98953;-3.48865;,
 -7.77409;-33.46962;-2.14102;,
 -4.64416;-31.61182;-3.27787;,
 -4.66234;-33.89837;-4.53221;,
 -7.08967;-34.98232;-0.86747;,
 -4.13588;-34.29872;-0.89289;,
 -4.34404;-31.98538;-1.76468;,
 -7.77409;-33.46962;-2.14102;,
 -9.52853;-36.14607;5.78185;,
 -6.66472;-34.08614;3.59891;,
 -7.50259;-34.58015;2.64903;,
 -9.52853;-36.14607;5.78185;,
 -6.36449;-35.34407;3.45708;,
 -6.66472;-34.08614;3.59891;,
 -9.52853;-36.14607;5.78185;,
 -7.50259;-34.58015;2.64903;,
 -6.36449;-35.34407;3.45708;,
 -7.50259;-34.58015;2.64903;,
 -5.15833;-34.68000;0.65696;,
 -4.43042;-34.91702;2.01561;,
 -6.36449;-35.34407;3.45708;,
 -6.36449;-35.34407;3.45708;,
 -4.43042;-34.91702;2.01561;,
 -4.41137;-33.28641;1.99445;,
 -6.66472;-34.08614;3.59891;,
 -4.13315;-34.07906;-0.22648;,
 -6.66472;-34.08614;3.59891;,
 -4.41137;-33.28641;1.99445;,
 -5.50593;-32.60903;0.99302;,
 -7.50259;-34.58015;2.64903;,
 -5.50593;-32.60903;0.99302;,
 -5.64400;-33.67689;0.18214;,
 -7.50259;-34.58015;2.64903;,
 -5.64400;-33.67689;0.18214;,
 -5.15833;-34.68000;0.65696;,
 -5.50593;-32.60903;0.99302;,
 -7.50259;-34.58015;2.64903;,
 -6.66472;-34.08614;3.59891;,
 -6.93998;-33.89122;-7.00210;,
 -9.03526;-34.65121;-8.72169;,
 -7.77409;-33.46962;-2.14102;,
 -4.64416;-31.61182;-3.27787;,
 -1.73989;-19.50405;-8.15046;,
 10.33013;-18.70596;-7.82171;,
 10.95219;-18.73858;-3.79244;,
 -0.55588;-19.53667;-0.03527;;
 
 44;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;6,7,4,8;,
 4;9,10,11,12;,
 4;13,6,8,14;,
 4;15,16,17,18;,
 4;19,20,21,22;,
 3;23,24,25;,
 3;26,27,28;,
 3;29,24,12;,
 3;30,16,28;,
 3;31,13,14;,
 3;32,20,19;,
 3;33,34,35;,
 3;36,37,38;,
 3;39,40,37;,
 3;41,42,43;,
 3;44,45,46;,
 4;47,48,49,50;,
 4;51,52,53,54;,
 4;55,56,57,58;,
 4;59,60,61,62;,
 3;63,54,53;,
 3;64,50,49;,
 3;65,66,67;,
 3;68,69,70;,
 3;71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 3;86,87,88;,
 3;89,90,91;,
 3;92,93,94;,
 4;95,96,97,98;,
 4;99,100,101,102;,
 3;103,101,100;,
 3;104,105,106;,
 3;107,108,109;,
 3;110,111,112;,
 3;113,114,115;,
 3;116,60,117;,
 3;118,84,119;,
 4;5,120,121,0;,
 4;3,122,123,4;;
 
 MeshMaterialList {
  7;
  44;
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  1,
  2,
  1,
  1,
  2,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\色々使う用画像\\ドラゴン.jpeg";
   }
  }
  Material {
   0.800000;0.204000;0.112800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.659200;0.367200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.746400;0.671200;0.395200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.668000;0.668000;0.668000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "TEXTURE\\eyes.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  65;
  -0.118824;0.339057;-0.933232;,
  0.067508;-0.997661;-0.010692;,
  -0.218149;0.395827;-0.892038;,
  0.894749;-0.423513;-0.141639;,
  -0.936727;0.319447;0.143166;,
  0.095420;-0.995300;-0.016511;,
  0.936044;0.320199;-0.145924;,
  -0.383352;0.792825;-0.473782;,
  -0.026654;0.669150;-0.742649;,
  -0.318357;0.868723;-0.379432;,
  -0.674464;0.619865;0.401082;,
  -0.705187;0.297657;0.643516;,
  -0.200871;-0.783116;0.588541;,
  0.757931;0.621164;-0.199239;,
  0.574864;-0.594579;-0.562145;,
  0.446307;0.740160;-0.502965;,
  -0.257600;-0.775719;0.576109;,
  -0.503589;0.520305;-0.689696;,
  -0.498481;0.499225;-0.708725;,
  -0.268753;0.490293;0.829086;,
  0.266872;-0.959483;-0.090397;,
  -0.492958;0.477729;-0.727164;,
  -0.319592;0.715912;0.620750;,
  -0.554085;0.830519;0.056812;,
  -0.694481;0.715150;-0.079101;,
  -0.401091;0.878498;0.259552;,
  0.584092;0.037359;0.810828;,
  0.991753;-0.009928;0.127782;,
  -0.788990;0.433007;-0.435889;,
  -0.306832;0.880065;0.362409;,
  -0.365363;-0.798225;-0.478902;,
  0.859171;0.009223;0.511605;,
  -0.139890;-0.948223;-0.285137;,
  -0.099775;0.258747;-0.960778;,
  0.250628;-0.013114;0.967995;,
  0.360235;0.021057;0.932624;,
  0.407580;-0.066450;0.910748;,
  0.715564;0.689974;-0.109107;,
  -0.153430;0.318357;-0.935472;,
  0.021661;0.112793;-0.993382;,
  0.309932;0.107062;0.944712;,
  0.433134;0.012020;0.901249;,
  -0.985025;0.073392;0.156013;,
  0.981764;-0.109357;-0.155498;,
  -0.740737;0.279271;0.610996;,
  -0.143453;-0.787829;0.598955;,
  0.468674;-0.602566;-0.645956;,
  0.428509;-0.608173;-0.668211;,
  -0.599584;0.628479;0.495493;,
  -0.450619;0.857026;0.249900;,
  0.732664;-0.546027;-0.406274;,
  -0.346356;0.507521;0.788961;,
  -0.331680;0.648499;0.685155;,
  0.369676;-0.927523;-0.055149;,
  0.318786;-0.945020;-0.072890;,
  -0.189018;0.469178;0.862638;,
  0.583519;0.047864;0.810688;,
  -0.179627;-0.828556;-0.530310;,
  -0.302380;-0.812229;-0.498849;,
  -0.161298;-0.896953;-0.411653;,
  0.061033;0.856452;0.512607;,
  -0.550324;-0.559717;-0.619565;,
  -0.406563;0.864969;0.294170;,
  0.027887;0.051715;-0.998272;,
  0.321085;0.072642;0.944260;;
  44;
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;0,0,2,33;,
  4;5,5,5,5;,
  4;34,35,36,34;,
  4;6,6,37,37;,
  3;33,38,39;,
  3;35,40,41;,
  3;2,38,33;,
  3;36,35,41;,
  3;42,42,42;,
  3;43,6,6;,
  3;7,9,8;,
  3;7,10,9;,
  3;44,11,10;,
  3;45,12,12;,
  3;46,47,47;,
  4;47,47,14,14;,
  4;8,9,15,15;,
  4;12,16,16,12;,
  4;9,10,48,49;,
  3;13,15,15;,
  3;50,14,14;,
  3;17,18,18;,
  3;51,19,52;,
  3;53,54,54;,
  4;54,20,20,54;,
  4;18,18,21,21;,
  4;19,55,22,52;,
  3;23,25,24;,
  3;56,26,26;,
  3;57,58,59;,
  4;58,30,32,59;,
  4;26,31,31,26;,
  3;27,31,31;,
  3;25,60,29;,
  3;24,28,28;,
  3;58,61,30;,
  3;29,24,25;,
  3;48,10,11;,
  3;52,22,62;,
  4;63,33,39,63;,
  4;64,40,35,64;;
 }
 MeshTextureCoords {
  124;
  0.473130;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.473130;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.487540;,
  1.000000;1.000000;,
  0.000000;0.487540;,
  0.000000;0.423910;,
  0.000000;0.000000;,
  0.473130;0.000000;,
  0.473130;0.423910;,
  1.000000;0.423910;,
  0.000000;0.423910;,
  1.000000;0.423910;,
  0.526870;0.423910;,
  0.526870;0.000000;,
  1.000000;0.000000;,
  0.000000;0.423910;,
  1.000000;0.423910;,
  1.000000;0.487540;,
  0.000000;0.487540;,
  0.473130;0.455730;,
  1.000000;0.423910;,
  1.000000;0.487540;,
  0.526870;0.455730;,
  0.000000;0.487540;,
  0.000000;0.423910;,
  0.736560;0.000000;,
  0.263440;0.000000;,
  0.500000;0.000000;,
  0.500000;0.000000;,
  0.136360;0.000000;,
  0.181820;0.000000;,
  0.090910;0.000000;,
  0.318180;0.000000;,
  0.363640;0.000000;,
  0.272730;0.000000;,
  0.409090;0.000000;,
  0.454550;0.000000;,
  0.590910;0.000000;,
  0.636360;0.000000;,
  0.545450;0.000000;,
  0.954550;0.000000;,
  1.000000;0.000000;,
  0.909090;0.000000;,
  0.909090;0.421770;,
  1.000000;0.421770;,
  1.000000;0.543580;,
  0.909090;0.543580;,
  0.090910;0.421770;,
  0.181820;0.421770;,
  0.181820;0.543580;,
  0.090910;0.543580;,
  0.636360;0.421770;,
  0.636360;0.543580;,
  0.545450;0.543580;,
  0.545450;0.421770;,
  0.272730;0.421770;,
  0.363640;0.421770;,
  0.363640;0.543580;,
  0.272730;0.543580;,
  0.136360;1.000000;,
  0.954550;1.000000;,
  0.136360;0.000000;,
  0.181820;0.000000;,
  0.090910;0.000000;,
  0.409090;0.000000;,
  0.454550;0.000000;,
  0.363640;0.000000;,
  0.772730;0.000000;,
  0.818180;0.000000;,
  0.727270;0.000000;,
  0.818180;0.421770;,
  0.818180;0.543580;,
  0.727270;0.543580;,
  0.727270;0.421770;,
  0.090910;0.421770;,
  0.181820;0.421770;,
  0.181820;0.543580;,
  0.090910;0.543580;,
  0.454550;0.421770;,
  0.454550;0.543580;,
  0.363640;0.543580;,
  0.363640;0.421770;,
  0.227270;0.000000;,
  0.272730;0.000000;,
  0.181820;0.000000;,
  0.500000;0.000000;,
  0.545450;0.000000;,
  0.454550;0.000000;,
  0.681820;0.000000;,
  0.727270;0.000000;,
  0.636360;0.000000;,
  0.727270;0.421770;,
  0.727270;0.543580;,
  0.636360;0.543580;,
  0.636360;0.421770;,
  0.545450;0.421770;,
  0.545450;0.543580;,
  0.454550;0.543580;,
  0.454550;0.421770;,
  0.500000;1.000000;,
  0.318190;0.421770;,
  0.363640;0.543580;,
  0.272730;0.543580;,
  0.136360;0.421770;,
  0.181820;0.543580;,
  0.090910;0.543580;,
  0.954550;0.421770;,
  1.000000;0.543580;,
  0.909090;0.543580;,
  0.227270;0.543580;,
  0.181820;0.421770;,
  0.272730;0.421770;,
  0.409090;0.543580;,
  0.454550;0.421770;,
  0.318190;0.421770;,
  0.272730;0.543580;,
  0.000000;0.000000;,
  0.473130;0.000000;,
  0.473130;1.000000;,
  0.000000;1.000000;;
 }
}
