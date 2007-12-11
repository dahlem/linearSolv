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
## Keywords: linear system, LU decomposition, Crout reduction
## Created: 10.12.2007
## Version: 1.0




1;


function [L, U] = dd_crout(A)
  if (nargin != 1)
    usage("dd_crout(A)");
  endif

  if (rows(A) == columns(A))
    error("The matrix A has to be a square matrix.");
  endif

  U = eye(rows(A));
  L = zeros(rows(A), columns(A));

  for i = 1:rows(A)
    L(i, 1) = A(i, 1);
    U(1, i) = A(1, i) / A(1, 1);
  endfor

  for i = 1:rows(A)
    for j = 2:i
      if j <= i
	temp = 0;

	for k = 1 : (j - 1)
	  temp += L(i, k) * U(k, j);
	endfor
	
	L(i, j) = A(i, j) - temp;
      endif
    endfor

    for j = 2:columns(A)
      if (i > 1) && (i <= j)
	temp = 0;
	
	for k = 1 : (i - 1)
	  temp += L(i, k) * U(k, j);
	endfor
	
	U(i, j) = (A(i, j) - temp) / L(i, i);
      endif
    endfor
  endfor
endfunction


function [x_bar, x_error, max_error] = dd_lu(A, b, x)
  if (nargin != 3)
    usage("dd_lu(A, b, x)");
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

  [L, U] = dd_crout(A);
  
  ML = [L, b];
  [ML, y_bar] = dd_forwards(ML);

  MU = [U, y_bar];
  [MU, x_bar] = dd_forwards(MU);
  
  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction


#!test
#! A = [2, 1, 3, 4; 3, 1, 5, -2; 2, 3, 2, -5; 1, 2, 4, 3];
#! [L, U] = dd_crout(A);
#! assert(L == [2, 0, 0, 0; 3, -0.5, 0, 0; 2, 2, 1, 0; 1, 1.5, 4, 141])
#! assert(U == [1, 0.5, 1.5, 2; 0, 1, -1, 16; 0, 0, 1, -41; 0, 0, 0, 1])
