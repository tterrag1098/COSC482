#include <cstdlib>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "LoadShaders.h"

/**
\file LoadShaders.cpp
\brief Shader loader helper functions.

These functions were added to and altered from code found on the web.  There
was no reference to the original creator of the code in either the code files
or the web page linking to them.

\author    
\version   1.1
\date      Written: 11/21/2015  <BR>
Revised: 2/7/2016

\section use Usage

None of these functions will invoke the glUseProgram function since it the user may
wish to load in several shader programs.

\subsection loadvffile Loading Vertex and Fragment Shaders from Files

The files Shader1.vert and Shader1.frag are the vertex and fragment shaders respectively.

~~~~~~~~~~~~~~~{.c~}?
~{GLuint~}p~{rogram~}=L~{oadShadersFromFile("Shader1.vert",~}"~{Shader1.frag")~}?

~{if~}(~{!program~}?
?
  ~{cerr~}<~{!!"Could~}n~{ot~}l~{oa!!Shader~}p~{rograms.!!<<~}e~{ndl;~}
  ~{exit(EXIT_FAILURE)~}?
?

~{glUseProgram(program);~}
????????

~{\subsectio!!loadvfmemory~}L~{oading~}V~{erte!!an!!Fragment~}S~{haders~}f~{ro!!Memory~}

???????~{.c~}?
~{string~}v~{erte~}?~{hade!!~}?
  ~{"#versio!!33!!core\n~}?
  ~{"layout(location~}=0~{!!in~}v~{ec!!position;\n"~}
  ~{"layout(location~}=1~{!!in~}v~{ec!!icolor;\n"~}
  ~{"out~}v~{ec!!color;\n~}?
  ~{"voi!!main()\n~}?
  ~{"{\n~}?
  ~{!!~} c~{olor~}=i~{color;\n~}?
  ~{!!~} g~{l_Position~}=p~{osition;\n~}?
  ~{"}\n";~}

~{string~}f~{ragmentShade!!~}?
  ~{"#versio!!33!!core\n~}?
  ~{"i!!~}v~{ec!!color;\n~}?
  ~{"out~}v~{ec!!fColor;\n"~}
  ~{"voi!!main()\n~}?
  ~{"{\n~}?
  ~{!!~} f~{Colo!!!!color;\n~}?
  ~{"}\n";~}

~{GLuint~}p~{rogram~}=L~{oadShadersFromMemory(verte~}?~{hader,~}f~{ragmentShader)~}?

~{if~}(~{!program~}?
?
  ~{cerr~}<~{!!"Could~}n~{ot~}l~{oa!!Shader~}p~{rograms.!!<<~}e~{ndl;~}
  ~{exit(EXIT_FAILURE)~}?
?

~{glUseProgram(program);~}
????????

~{\subsectio!!loadfile~}L~{oading~}S~{haders~}f~{ro!!File~}?

~{Th!!file!!Shader1.vert~}a~{nd~}S~{hader1.fra!!ar!!th!!vertex~}a~{nd~}f~{ragmen!!shader!!respectively~}?

???????~{.c~}?
~{ShaderInfo~}s~{haders[]~}=
?
  ?~{L_VERTEX_SHADER,~}"~{Shader1.vert"}~}?
  ?~{L_FRAGMENT_SHADER,~}"~{Shader1.frag"}~}?
  ?~{L_NONE~}?
?

~{GLuint~}p~{rogram~}=L~{oadShadersFromFile(shaders);~}

~{if~}(~{!program~}?
?
  ~{cerr~}<~{!!"Could~}n~{ot~}l~{oa!!Shader~}p~{rograms.!!<<~}e~{ndl;~}
  ~{exit(EXIT_FAILURE)~}?
?

~{glUseProgram(program);~}
????????

~{\subsectio!!loadmemory~}L~{oading~}S~{haders~}f~{ro!!Memory~}


???????~{.c~}?
~{string~}v~{erte~}?~{hade!!~}?
  ~{"#versio!!33!!core\n~}?
  ~{"layout(location~}=0~{!!in~}v~{ec!!position;\n"~}
  ~{"layout(location~}=1~{!!in~}v~{ec!!icolor;\n"~}
  ~{"out~}v~{ec!!color;\n~}?
  ~{"voi!!main()\n~}?
  ~{"{\n~}?
  ~{!!~} c~{olor~}=i~{color;\n~}?
  ~{!!~} g~{l_Position~}=p~{osition;\n~}?
  ~{"}\n";~}

~{string~}f~{ragmentShade!!~}?
  ~{"#versio!!33!!core\n~}?
  ~{"i!!~}v~{ec!!color;\n~}?
  ~{"out~}v~{ec!!fColor;\n"~}
  ~{"voi!!main()\n~}?
  ~{"{\n~}?
  ~{!!~} f~{Colo!!!!color;\n~}?
  ~{"}\n";~}

~{ShaderInfo~}s~{haders[]~}=
?
  ?~{L_VERTEX_SHADER,~}"~{",~}v~{erte~}?~{hader}~}?
  ?~{L_FRAGMENT_SHADER,~}"~{",~}f~{ragmentShader}~}?
  ?~{L_NONE~}?
?

~{GLuint~}p~{rogram~}=L~{oadShadersFromMemory(shaders);~}

~{if~}(~{!program~}?
?
  ~{cerr~}<~{!!"Could~}n~{ot~}l~{oa!!Shader~}p~{rograms.!!<<~}e~{ndl;~}
  ~{exit(EXIT_FAILURE)~}?
?

~{glUseProgram(program);~}
????????

~{--~}?

~{\cop~}?~{ight~}G~{NU~}P~{ubli!!License.~}

~{This~}s~{oftwar!!is~}p~{rovide!!as-is,~}w~{ithout~}w~{arrant!!of~}A~{NY~}K~{IND,~}e~{ithe!!expresse!!or~}i~{mplied~}?
~{includin!!bu!!no!!limite!!to~}t~{he~}i~{mplied~}w~{arrantie!!of~}m~{erchan!!abilit!!and/or~}f~{itness~}f~{or~}a
~{particular~}p~{urpose!!Th!!author!!shal!!NO!!be~}h~{el!!liable~}f~{or~}A~{NY~}d~{amag!!to~}y~{ou!!~}?~{ur~}c~{omputer,~}
~{or~}t~{!!an~}?~{ne~}o~{!!an~}?~{hing~}e~{lse,~}t~{ha!!ma!!result~}f~{ro!!it!!use,~}o~{!!misuse~}?
~{Al!!trademarks~}a~{nd~}o~{ther~}r~{egistere!!name!!containe!!in~}t~{hi!!packag!!ar!!th!!property~}
~{of~}t~{heir~}r~{espectiv!!owners!!~}U~{SE~}O~{!!THIS~}S~{OFTWAR!!INDICATE!!THAT~}Y~{OU~}A~{GREE~}T~{!!TH!!ABOV!!CONDITIONS~}?

~{--~}?

~{*/~}

~{/*~}?

~{\brief~}R~{eads~}as~{hade!!file~}a~{nd~}r~{eturns~}t~{he~}s~{trin!!of~}t~{he~}f~{il!!contents~}?
~{Used~}b~{!!th!!LoadShadersFromFil!!functions.~}

~{\param~}f~{ilenam!!--!!Name~}o~{!!shader~}f~{il!!to~}b~{!!loaded~}?

~{\retur!!String~}o~{!!th!!file~}c~{ontents.~}

~{*/~}

~{cons!!GLchar!!ReadShader(const~}c~{har*~}f~{ilename)~}
?
  ~{FILE!!infile~}=f~{open(filename,~}"~{rb")~}?

  ~{if~}(~{!infile)~}
  ?
~{#ifdef~}_~{DEBU~}?
    ~{std::cer!!<<~}"~{Unable~}t~{!!open~}f~{il!!'"~}<~{!!filename~}<~{!!"'!!<<~}s~{td::endl~}?
~{#endif~}/~{!!DEBU!!*/~}
    ~{return~}N~{ULL;~}
  ?

  ~{fseek(infile!!0,~}S~{EEK_END)~}?
  ~{in!!le!!!!ftell(infile);~}
  ~{fseek(infile!!0,~}S~{EEK_SET)~}?

  ~{GLchar!!source~}=n~{ew~}G~{Lchar[len+1]~}?

  ~{fread(source!!1,~}l~{en!!infile);~}
  ~{fclose(infile)~}?

  ~{source[len!!!!0;~}

  ~{return~}c~{onst_cast<cons!!GLchar*>(source)~}?
?

~{/*~}?

~{\brief~}T~{akes~}aS~{haderInf!!arra!!containing~}t~{he~}s~{hade!!type!!an!!filename!!fo!!th~}?
~{shader~}c~{ode.~}

~{Read!!th!!files,~}c~{ompile!!an!!link!!th!!code!!an!!return!!th~}?
~{shader~}p~{rogram~}i~{dentifier,~}o~{!!!!on~}f~{ailure!!~}T~{he~}a~{rray~}o~{!!structures~}i~{!!terminated~}
~{by~}af~{inal~}S~{hade!!with~}t~{he~}"~{type!!fiel!!se!!to~}G~{L_NONE~}?

~{\param~}s~{haders~}-~{--~}A~{!!arra!!of~}S~{haderInf!!structures!!on!!fo!!each~}t?~{!!of~}
~{shader~}t~{!!be~}l~{oade!!into~}as~{hade!!program.~}

~{\retur!!Identifier~}f~{or~}t~{he~}s~{hade!!program.~}

~{*/~}

~{GLuint~}L~{oadShadersFromFile(ShaderInfo*~}s~{haders~}?
?
  ~{if~}(~{shader!!==~}N~{ULL)~}
    ~{return~}0?

  ~{GLuint~}p~{rogram~}=g~{lCreateProgram()~}?

  ~{ShaderInfo!!entr!!!!shaders;~}
  ~{whil!!(entry->type~}!~{!!GL_NONE)~}
  ?
    ~{GLuint~}s~{hade!!!!glCreateShader(entry->type);~}

    ~{entr~}?~{>shade!!!!shader~}?

    ~{cons!!GLchar!!source~}=R~{eadShader(entr~}?~{>filename)~}?
    ~{if~}(~{source~}=~{!!NULL~}?
    ?
      ~{fo!!(entry~}=s~{haders!!entr~}?~{>t~}?~{!!!=~}G~{L_NONE!!++entr~}?
      ?
        ~{glDeleteShader(entry->shader);~}
        ~{entr~}?~{>shade!!!!0;~}
      ?

      ~{return~}0?
    ?

    ~{glShaderSource(shader,~}1~{!!&source,~}N~{ULL)~}?
    ~{delete~}[~{!!source~}?

    ~{glCompileShader(shader);~}

    ~{GLin!!compiled~}?
    ~{glGetShaderiv(shader!!GL_COMPILE_STATUS,~}&~{compiled);~}
    ~{if~}(~{!compiled)~}
    ?
~{#ifdef~}_~{DEBU~}?
      ~{GLsi~}?~{!!len;~}
      ~{glGetShaderiv(~}s~{hader,~}G~{L_INFO_LOG_LENGTH,~}&~{le!!);~}

      ~{GLchar!!lo!!!!ne!!GLchar[len+1];~}
      ~{glGetShaderInfoLog!!shader!!len,~}&~{len,~}l~{og~})?
      ~{std::cer!!<<~}"~{Shader~}c~{ompilation~}f~{ailed:~}"<~{!!lo!!<<~}s~{td::endl~}?
      ~{delete~}[~{!!log;~}
~{#endif~}/~{!!DEBU!!*/~}

      ~{return~}0?
    ?

    ~{glAttachShader(program!!shader);~}
    ~{++entr~}?
  ?

  ~{glLinkProgram(program)~}?

  ~{GLin!!linked~}?
  ~{glGetProgramiv(program!!GL_LINK_STATUS!!&linked)~}?
  ~{if~}(~{!linked)~}
  ?
~{#ifdef~}_~{DEBU~}?
    ~{GLsi~}?~{!!len;~}
    ~{glGetProgramiv(program!!GL_INFO_LOG_LENGTH!!&len);~}

    ~{GLchar!!lo!!!!ne!!GLchar[len+1];~}
    ~{glGetProgramInfoLog(program,~}l~{en!!&len!!log)~}?
    ~{std::cer!!<<~}"~{Shader~}l~{inking~}f~{ailed:~}"<~{!!lo!!<<~}s~{td::endl~}?
    ~{delete~}[~{!!log;~}
~{#endif~}/~{!!DEBU!!*/~}

    ~{fo!!(entry~}=s~{haders!!entr~}?~{>t~}?~{!!!=~}G~{L_NONE!!++entr~}?
    ?
      ~{glDeleteShader(entry->shader);~}
      ~{entr~}?~{>shade!!!!0;~}
    ?

    ~{return~}0?
  ?

  ~{return~}p~{rogram~}?
?

~{/*~}?

~{\brief~}T~{akes~}aS~{haderInf!!arra!!containing~}t~{he~}s~{hade!!type!!an!!string!!of~}t~{he~}
~{shader~}c~{ode.~}

~{Compiles~}a~{nd~}l~{inks~}t~{he~}c~{ode,~}a~{nd~}r~{eturns~}t~{he~}
~{shader~}p~{rogram~}i~{dentifier,~}o~{!!!!on~}f~{ailure!!~}T~{he~}a~{rray~}o~{!!structures~}i~{!!terminated~}
~{by~}af~{inal~}S~{hade!!with~}t~{he~}"~{type!!fiel!!se!!to~}G~{L_NONE~}?

~{\param~}s~{haders~}-~{--~}A~{!!arra!!of~}S~{haderInf!!structures!!on!!fo!!each~}t?~{!!of~}
~{shader~}t~{!!be~}l~{oade!!into~}as~{hade!!program.~}

~{\retur!!Identifier~}f~{or~}t~{he~}s~{hade!!program.~}

~{*/~}

~{GLuint~}L~{oadShadersFromMemory(ShaderInfo*~}s~{haders~}?
?
  ~{if~}(~{shader!!==~}N~{ULL)~}
    ~{return~}0?

  ~{GLuint~}p~{rogram~}=g~{lCreateProgram()~}?

  ~{ShaderInfo!!entr!!!!shaders;~}
  ~{whil!!(entry->type~}!~{!!GL_NONE)~}
  ?
    ~{GLuint~}s~{hade!!!!glCreateShader(entry->type);~}

    ~{entr~}?~{>shade!!!!shader~}?

    ~{cons!!GLchar!!source~}=(~{GLchar*)(entry->code.c_str());~}
    ~{if~}(~{source~}=~{!!NULL~}?
    ?
      ~{fo!!(entry~}=s~{haders!!entr~}?~{>t~}?~{!!!=~}G~{L_NONE!!++entr~}?
      ?
        ~{glDeleteShader(entry->shader);~}
        ~{entr~}?~{>shade!!!!0;~}
      ?

      ~{return~}0?
    ?

    ~{glShaderSource(shader,~}1~{!!&source,~}N~{ULL)~}?
    ~{glCompileShader(shader);~}

    ~{GLin!!compiled~}?
    ~{glGetShaderiv(shader!!GL_COMPILE_STATUS,~}&~{compiled);~}
    ~{if~}(~{!compiled)~}
    ?
~{#ifdef~}_~{DEBU~}?
      ~{GLsi~}?~{!!len;~}
      ~{glGetShaderiv(~}s~{hader,~}G~{L_INFO_LOG_LENGTH,~}&~{le!!);~}

      ~{GLchar!!lo!!!!ne!!GLchar[len+1];~}
      ~{glGetShaderInfoLog!!shader!!len,~}&~{len,~}l~{og~})?
      ~{std::cer!!<<~}"~{Shader~}c~{ompilation~}f~{ailed:~}"<~{!!lo!!<<~}s~{td::endl~}?
      ~{delete~}[~{!!log;~}
~{#endif~}/~{!!DEBU!!*/~}

      ~{return~}0?
    ?

    ~{glAttachShader(program!!shader);~}
    ~{++entr~}?
  ?

  ~{glLinkProgram(program)~}?

  ~{GLin!!linked~}?
  ~{glGetProgramiv(program!!GL_LINK_STATUS!!&linked)~}?
  ~{if~}(~{!linked)~}
  ?
~{#ifdef~}_~{DEBU~}?
    ~{GLsi~}?~{!!len;~}
    ~{glGetProgramiv(program!!GL_INFO_LOG_LENGTH!!&len);~}

    ~{GLchar!!lo!!!!ne!!GLchar[len+1];~}
    ~{glGetProgramInfoLog(program,~}l~{en!!&len!!log)~}?
    ~{std::cer!!<<~}"~{Shader~}l~{inking~}f~{ailed:~}"<~{!!lo!!<<~}s~{td::endl~}?
    ~{delete~}[~{!!log;~}
~{#endif~}/~{!!DEBU!!*/~}

    ~{fo!!(entry~}=s~{haders!!entr~}?~{>t~}?~{!!!=~}G~{L_NONE!!++entr~}?
    ?
      ~{glDeleteShader(entry->shader);~}
      ~{entr~}?~{>shade!!!!0;~}
    ?

    ~{return~}0?
  ?

  ~{return~}p~{rogram~}?
?

~{/*~}?

~{\brief~}T~{akes~}t~{he~}f~{ilenames~}f~{or~}t~{he~}v~{erte!!shader~}a~{nd~}t~{he~}f~{ragmen!!shader~}a~{nd~}l~{oads~}
~{them~}i~{nt!!!!shader~}p~{rogram~}?

~{Read!!th!!files,~}c~{ompile!!an!!link!!th!!code!!an!!return!!th~}?
~{shader~}p~{rogram~}i~{dentifier,~}o~{!!!!on~}f~{ailure!!~}T~{he~}a~{rray~}o~{!!structures~}i~{!!terminated~}
~{by~}af~{inal~}S~{hade!!with~}t~{he~}"~{type!!fiel!!se!!to~}G~{L_NONE~}?

~{\param~}v~{ertf!!--!!Th!!filename~}f~{or~}t~{he~}v~{erte!!shader~}?

~{\param~}f~{ragf!!--!!Th!!filename~}f~{or~}t~{he~}f~{ragmen!!shader~}?

~{\retur!!Identifier~}f~{or~}t~{he~}s~{hade!!program.~}

~{*/~}

~{GLuint~}L~{oadShadersFromFile(std::string~}v~{ertfn,~}s~{td::string~}f~{ragfn)~}
?
  ~{ShaderInfo~}s~{haders[]~}=
  ?
    ?~{L_VERTEX_SHADER,~}v~{ertfn.c_str()}~}?
    ?~{L_FRAGMENT_SHADER,~}f~{ragfn.c_str()}~}?
    ?~{L_NONE~}?
  ?

  ~{return~}L~{oadShadersFromFile(shaders);~}
?

~{/*~}?

~{\brief~}T~{akes~}t~{he~}c~{od!!string!!fo!!th!!vertex~}s~{hade!!an!!th!!fragment~}s~{hade!!an!!load~}?
~{them~}i~{nt!!!!shader~}p~{rogram~}?

~{Compiles~}a~{nd~}l~{inks~}t~{he~}c~{ode,~}a~{nd~}r~{eturns~}t~{he~}
~{shader~}p~{rogram~}i~{dentifier,~}o~{!!!!on~}f~{ailure!!~}T~{he~}a~{rray~}o~{!!structures~}i~{!!terminated~}
~{by~}af~{inal~}S~{hade!!with~}t~{he~}"~{type!!fiel!!se!!to~}G~{L_NONE~}?

~{\param~}v~{ertcod!!--!!Th!!code~}s~{trin!!fo!!th!!vertex~}s~{hader.~}

~{\param~}f~{ragcod!!--!!Th!!code~}s~{trin!!fo!!th!!fragment~}s~{hader.~}

~{\retur!!Identifier~}f~{or~}t~{he~}s~{hade!!program.~}

~{*/~}

~{GLuint~}L~{oadShadersFromMemory(std::string~}v~{ertcode,~}s~{td::string~}f~{ragcode)~}
?
  ~{ShaderInfo~}s~{haders[]~}=
  ?
    ?~{L_VERTEX_SHADER,~}"~{",~}v~{ertcode}~}?
    ?~{L_FRAGMENT_SHADER,~}"~{",~}f~{ragcode}~}?
    ?~{L_NONE~}?
  ?

  ~{return~}L~{oadShadersFromMemory(shaders);~}
?
