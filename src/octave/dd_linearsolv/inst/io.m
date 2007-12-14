## Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
##  
## This file is free software; as a special exception the author gives
## unlimited permission to copy and/or distribute it, with or without 
## modifications, as long as this notice is preserved.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
## implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

## -*- texinfo -*-
## @deftypefn{Loadable Function File} {[@var{A}, @var{v}] = }
##     dd_read (@var{filename}, @var{format} = "-text")
## @cindex File I/O
##
## @var{filename} is the name of the file with the matrix and vector
## specification.
## @var{A} and @var{v} are the in-memory representations of the file
## specification.
## @end deftypefn
##
## @deftypefnx{Loadable Function File} 
##     dd_write (@var{filename}, @var{A}, @var{v}, @var{format} =
##     "-text")
## @cindex File I/O
##
## @var{filename} is the name of the file to store the matrix @var{A}
## and the vector @var{v}.
##
## @end deftypefnx


1;

function [A, v] = dd_read(filename, format="-text")
  if ((nargin < 1) || (nargin > 2) || !ischar(filename))
    usage("dd_read(filename[, format='-text'])");
  endif

  A = [];
  v = [];

  eval(["load ", format, " ", filename, " ", A, " " , v, ";"]);

endfunction


function dd_write(filename, A, v, format="-text")
  if ((nargin < 3) || (nargin > 4) || !ischar(filename))
    usage("dd_write(filename, A, v[, format='-text'])");
  endif

  eval(["save (\"", format, "\", \"", filename, "\", \"A\", \"v\")"]);

endfunction

%!test
%! A = [1, 2; 3, 4];
%! v = [1, 2];
%! dd_write("test.dat", A, v);
%! [B, w] = dd_read("test.dat");
%! assert(A == B);
%! assert(v == w);
%! unlink("test.dat");
