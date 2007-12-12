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
## Keywords: linear system, gaussian elimination, partial pivoting
## Created: 10.12.2007
## Version: 1.0




1;

function k = dd_largestPivot(A, r, c)
  if (nargin != 3)
    usage("dd_largestPivot(A, r, c)");
  endif

  if (r > rows(A))
    error("r is greater than the number of rows.");
  endif

  if (c > columns(A))
    error("c is greater than the number of columns.");
  endif
  
  k = r;
  
  if (r == rows(A))
    warning("r is the bottom row of A.");
    return;
  endif

  maxElem = A(r, c);

  for i = r:rows(A)
    elem = A(i, c);
    if (elem > maxElem)
      maxElem = elem;
      k = i;
    endif
  endfor
endfunction


function A = dd_pivotRow(A, r, c)
  if (nargin != 3)
    usage("dd_largestPivot(A, r, c)");
  endif

  if (r > rows(A))
    error("r is greater than the number of rows.");
  endif

  if (c > columns(A))
    error("c is greater than the number of columns.");
  endif

  if (A(r, c) == 0)
    return;
  endif

  k = dd_largestPivot(A, r, c);

  if (k == r)
    return;
  endif

  temp = A(r, :);
  A(r, :) = A(k, :);
  A(k, :) = temp;
endfunction


function M = dd_triangular(M)
  if (nargin != 1)
    usage("dd_triangular(M)");
  endif

  if (rows(M) != (columns(M) - 1))
    error("The matrix A has to be rectangular.");
  endif

  for i = 1 : (columns(M) - 2)
    M = dd_pivotRow(M, i, i);

    for j = (i + 1) : rows(M)
      M(j,:) = abs(M(j,:) - M(j,i)/M(i,i) * M(i,:));
    endfor
  endfor
endfunction


function [x_bar, x_error, max_error] = dd_gauss(A, b, x)
  if (nargin != 3)
    usage("dd_gauss(A, b, x)");
  endif

  if (matrix_type(A) != "Positive Definite")
    error("The matrix A has to be positive definite.");
  endif

  if (rows(b) != rows(A))
    error("The vector b has to have the same dimension as rows in matrix A");
  endif

  if (!isvector(b))
    error("b must be an array.");
  endif

  M = [A, b];
  M = dd_triangular(M);

  [M, x_bar] = dd_backwards(M);

  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction


#! A = [1.86279, 0.47863, -0.54877; 0.47863, 1.61609, 0.10628; -0.54877,
#!      0.10628, 2.76115]
#! b = [1;2;3]
#! x = [1;1;1]
#! [x_bar, x_error, max_error] = dd_gauss(A, b, x)
#! assert(A * x_bar, b, 0.001)
