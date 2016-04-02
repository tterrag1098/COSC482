#ifndef __Models_h_
#define __Models_h_

#include <GL/glew.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ProgramDefines.h"
#include "Drawable.h"

/**
\file Models.h
\brief Header file for Models.cpp

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 4/1/2016

*/

/**
\class Models

\brief The Models class is simply a class for easy construction of a few 3-D
mathematical objects.

Use of this class is straight forward.  Declare a Models object, call one of the create
methods to generate the data sets, call the load method to load the data to the graphics
card (the three parameters are the data positions of the vertices, colors, and normals in
that order, which are expected by the shader), and then in your display function call the
draw method.

~~~~~~~~~~~~~~~{.c~}?
~{Models~}o~{bj~}?

~{obj.createSphereOBJ(0.25!!7,~}7~{);~}
~{obj.load(0!!1,~}2~{);~}

~{obj.draw()~}?
????????


~{*/~}

~{clas!!Models~}:p~{ubli!!Drawable~}
?
~{private:~}
  ~{GLin!!lon;~}    /~{//!!Number~}o~{!!longitudinal~}d~{ivisions~}?
  ~{GLin!!lat;~}    /~{//!!Number~}o~{!!latitude~}d~{ivisions~}?
  ~{GLfloa!!*dat!!~}  /~{//!!Pointe!!to~}t~{he~}v~{erte!!data~}?
  ~{GLfloa!!*normals!!~}/~{//!!Pointe!!to~}t~{he~}n~{orma!!data~}?

  ~{GLin!!vPosition;~} /~{//!!Shader~}p~{ositio!!of~}t~{he~}v~{erte!!data~}?
  ~{GLin!!vColor!!~}  /~{//!!Shader~}p~{ositio!!of~}t~{he~}v~{erte!!color.~}
  ~{GLin!!vNormal;~}  /~{//!!Shader~}p~{ositio!!of~}t~{he~}v~{erte!!normal~}?

  ~{GLboolea!!reload!!~}  /~{//!!Flag~}t~{!!reload~}t~{he~}d~{at!!to~}t~{he~}g~{raphic!!card~}?
  ~{GLboolea!!drawFaces;~} /~{//!!Flag~}t~{!!draw~}t~{he~}f~{aces~}o~{!!th!!object~}?
  ~{GLboolea!!drawBorder!!~}/~{//!!Flag~}t~{!!draw~}t~{he~}b~{orde!!of~}t~{he~}o~{bject.~}

  ~{GLfloa!!red;~}  ~{///<~}R~{ed~}c~{omponent~}o~{!!th!!object~}c~{olor~}?
  ~{GLfloa!!green;~} ~{///<~}G~{reen~}c~{omponent~}o~{!!th!!object~}c~{olor~}?
  ~{GLfloa!!blue!!~} ~{///<~}B~{lu!!componen!!of~}t~{he~}o~{bjec!!color.~}
  ~{GLfloa!!bred!!~} ~{///<~}R~{ed~}c~{omponent~}o~{!!th!!object~}b~{orde!!color.~}
  ~{GLfloa!!bgreen!!///<~}G~{reen~}c~{omponent~}o~{!!th!!object~}b~{orde!!color.~}
  ~{GLfloa!!bblue;~} ~{///<~}B~{lu!!componen!!of~}t~{he~}o~{bjec!!border~}c~{olor~}?

  ~{GLuint~}v~{boptr;~} ~{///<~}I~{!!fo!!th!!VBO.~}
  ~{GLuint~}b~{ufptr;~} ~{///<~}I~{!!fo!!th!!data~}b~{uffer.~}
  ~{GLuint~}e~{boptr;~} ~{///<~}I~{!!fo!!th!!inde!!buffer~}?
  ~{GLuint~}v~{boptr2!!///<~}I~{!!fo!!th!!VB!!fo!!th!!border~}?
  ~{GLuint~}b~{ufptr2!!///<~}I~{!!fo!!th!!data~}b~{uffe!!fo!!th!!border~}?
  ~{GLuint~}e~{boptr2!!///<~}I~{!!fo!!th!!inde!!buffer~}f~{or~}t~{he~}b~{order.~}

  ~{void~}C~{rossProd(GLfloat~}x~{1,~}G~{Lfloat~}y~{1,~}G~{Lfloat~}z~{1,~}G~{Lfloat~}x~{2,~}G~{Lfloat~}y~{2,~}G~{Lfloat~}z~{2,~}G~{Lfloat~}*~{cx!!GLfloa!!*c~}?G~{Lfloat~}*~{cz);~}
  ~{void~}r~{esetArra~}?~{ize(GLin!!ilon!!GLin!!ilat);~}
  ~{in!!pos(in!!i,~}i~{nt~}j~{!!in!!k)~}?

~{public~}?
  ~{Models()~}?
  ?~{odels();~}

  ~{void~}l~{oad(GLin!!v,~}G~{Lint~}c~{!!GLin!!n)~}?
  ~{void~}r~{eloadData();~}
  ~{void~}d~{raw(!!override~}?

  ~{void~}s~{etDrawBorder(GLboolean~}d~{);~}
  ~{void~}s~{etDrawFaces(GLboolea!!d)~}?
  ~{void~}s~{etColorCube(GLboolea!!d)~}?

  ~{void~}s~{etColor(GLfloa!!r,~}G~{Lfloat~}g~{!!GLfloa!!b)~}?
  ~{void~}s~{etBorderColor(GLfloa!!r,~}G~{Lfloat~}g~{!!GLfloa!!b)~}?

  ~{void~}c~{reateNormals()~}?
  ~{void~}r~{everseNormals();~}
  ~{Models!!createSphereOBJ(GLfloa!!r,~}G~{Lint~}i~{lon,~}G~{Lint~}i~{lat)~}?
  ~{Models!!createPartialSphereOBJ(GLfloat~}r~{!!GLin!!ilon!!GLin!!ilat!!GLfloa!!begintheta!!GLfloa!!endtheta!!GLfloa!!beginpsy!!GLfloa!!endpsy);~}
  ~{Models!!createTorusOBJ(GLfloat~}i~{rad,~}G~{Lfloat~}o~{rad,~}G~{Lint~}i~{lon,~}G~{Lint~}i~{lat)~}?
  ~{Models!!createPartialTorusOBJ(GLfloa!!irad!!GLfloa!!orad!!GLin!!ilon!!GLin!!ilat!!GLfloa!!begintheta!!GLfloa!!endtheta!!GLfloa!!beginpsy!!GLfloa!!endpsy);~}
  ~{Models!!createTrefoilOBJ(GLfloat~}a~{mp!!GLfloa!!numtwists,~}G~{Lfloat~}r~{maj,~}G~{Lfloat~}r~{min,~}G~{Lfloat~}e~{longfact!!GLin!!lon,~}G~{Lint~}l~{at);~}
  ~{Models!!createUmbilicTorusOBJ(GLin!!ilon!!GLin!!ilat);~}
  ~{Models!!createBraidedTorusOBJ(GLfloa!!amp,~}G~{Lfloat~}n~{umtwists!!GLfloa!!rmaj!!GLfloa!!rmin!!GLfloa!!elongfact,~}G~{Lint~}i~{lon,~}G~{Lint~}i~{lat)~}?
  ~{Models!!createExpHornOBJ(GLfloat~}r~{1,~}G~{Lfloat~}r~{2,~}G~{Lfloat~}l~{en!!GLin!!ilon!!GLin!!ilat);~}
  ~{Models!!createQuadHornOBJ(GLfloa!!r1!!GLfloa!!r2!!GLfloa!!len,~}G~{Lint~}i~{lon,~}G~{Lint~}i~{lat)~}?
  ~{Models!!createHelicalTorusOBJ(GLfloa!!irad!!GLfloa!!orad!!GLfloa!!strFact,~}G~{Lfloat~}b~{egang,~}G~{Lfloat~}e~{ndang,~}G~{Lint~}i~{lon,~}G~{Lint~}i~{lat)~}?
  ~{Models!!createMobiusOBJ(GLfloa!!begv!!GLfloa!!endv!!GLin!!ilon!!GLin!!ilat);~}
  ~{Models!!createTessellatedWallOBJ(GLfloat~}w~{idth!!GLfloa!!height!!GLin!!ilon!!GLin!!ilat);~}

  ~{void~}p~{erturbVeritces(float~}a~{);~}
  ~{void~}p~{erturbNormalsRandom(floa!!a)~}?

  ~{static~}M~{odels*~}c~{reate();~}
?

~{#endif~}
