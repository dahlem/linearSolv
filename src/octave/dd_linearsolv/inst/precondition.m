## Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>
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
##     dd_precondition (@var{A}, @var{b}, @var{x})
## @cindex Conjugate Gradient, Iterative Method, Preconditioning, Jacobi
## Preconditioning
##
## @var{A} is the matrix to be solved with the solution vector @var{b}
## and a given x vector @var{x}.
## @var{x_bar} carries the solution.
##
## @seealso{dd_seidel}
## @end deftypefn


function [x_bar, x_error, max_error] = dd_precondition(A, b, x)
  if (nargin != 3)
    usage("dd_precondition(A, b, x)");
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

  k = 1;
  n = rows(A);
  x_bar = x;
  r = b - A * x_bar;
  M = dd_jacobi_precondition(A);
  z = inv(M) * r;
  d = z;
  rho = (z' * r);
  
  while ((k <= n) && (rho > 1 * 10^-8))
    alpha = rho / (d' * A * d);
    x_bar = x_bar + alpha * d;
    r = r - alpha * A * d;
    z = inv(M) * r;
    beta = (z' * r) / rho;
    rho = (z' * r);
    d = z + beta * d;
    k++;
  endwhile  

  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction


function M1 = dd_jacobi_precondition(A)
  if (nargin != 1)
    usage("dd_jacobi_precondition(A)");
  endif

  if (rows(A) != columns(A))
    error("The matrix A has to be a square matrix.");
  endif

  M1 = zeros(rows(A));
  
  for i = 1:rows(A)
    M1(i, i) = sqrt(A(i, i));
  endfor
endfunction


#!test precondition
#! A = [1.86279, 0.47863, -0.54877; 0.47863, 1.61609, 0.10628; -0.54877,
#!      0.10628, 2.76115]
#! b = [1;2;3]
#! x = [0;0;0]
#! [x_bar, x_error, max_error] = dd_precondition(A, b, x)
#! assert(A * x_bar, b, 0.001)
