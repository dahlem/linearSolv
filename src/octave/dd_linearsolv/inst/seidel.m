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
## @deftypefn{Function File} {[@var{x_bar}, @var{x_error}, @var{max_error}] = }
##     dd_seidel (@var{A}, @var{b}, @var{x})
## @cindex gauss-seidel method, Iterative Method
##
## @var{A} is the matrix to be solved with the solution vector @var{b}
## and a given x vector @var{x}.
## @var{x_bar} is the solution.
##
## @seealso{dd_gauss}
## @end deftypefn


function [x_bar, x_error, max_error] = dd_seidel(A, b, x)
  if (nargin != 3)
    usage("dd_chol(A, b, x)");
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

  x_bar = x;
  x_old = x;
  
  for l = 1:rows(A)
    for i = 1:rows(A)
      temp1 = 0;
      temp2 = 0;
      
      for j = 1:columns(A)
	if (j < i)
	  temp1 += A(i, j) * x_bar(j);
	elseif (j > i)
	  temp2 += A(i, j) * x_old(j);
	endif
      endfor
      
      x_bar(i) = (b(i) - temp1 - temp2) / A(i, i);
    endfor

    x_old = x_bar;
  endfor
  
  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction

#!test
#! A = [1.86279, 0.47863, -0.54877; 0.47863, 1.61609, 0.10628; -0.54877,
#!      0.10628, 2.76115]
#! b = [1;2;3]
#! x = [0;0;0]
#! [x_bar, x_error, max_error] = dd_seidel(A, b, x)
#! assert(A * x_bar, b, 0.001)
