## Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
##  
## This file is free software; as a special exception the author gives
## unlimited permission to copy and/or distribute it, with or without 
## modifications, as long as this notice is preserved.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
## implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

## Author: Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
## Maintainer: Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
## Keywords: matrix symmetric positive-definite
## Created: 07.12.2007
## Version: 0.1




1;

function rnd = dd_rnd
  rnd = -1 + 2 * rand();
endfunction


function A = dd_rndSPD(N, scale = 1)
  if ((nargin < 1) || (nargin > 2))
    usage("dd_rndSPD(N > 1[, scale=1])");
  elseif (N < 2)
    error("The dimension of the matrix has to be larger than 1.");
  endif

  A = zeros(N, N);
  
  for i = 1:N
    for j = i+1:N
      A(i,j) = scale * dd_rnd();
      A(j,i) = A(i,j);
    endfor
  endfor

  abs_row_sum = 0;

  for i = 1:N
    for j = 1:N
      abs_row_sum += abs(A(i,j));
    endfor

    A(i,i) = abs_row_sum + scale * rand();
  endfor
  
endfunction


function [A, b] = dd_linsolv(N, scale = 1)
  if ((nargin < 1) || (nargin > 2))
    usage("dd_linsolv(N > 1, scale)");
  elseif (N < 2)
    error("The dimension of the matrix has to be larger than 1.");
  endif

  A = dd_rndSPD(N, scale);
  x = ones(N, 1);
  x = x * (-1);
  b = A * x;

endfunction


%!test
%! A = dd_rndSPD(1000, 10);
%! assert(marix_type(A) == "Positive Definite");
%! [A, b] = dd_linsolv(3, 10);
%! assert(A\b == [-1; -1; -1]);
