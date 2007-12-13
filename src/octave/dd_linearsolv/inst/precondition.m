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
## Keywords: linear system, Conjugate Gradient
## Created: 12.12.2007
## Version: 1.0




1;


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
  M1 = dd_jacobi_precondition(A);
  A_bar = inv(M1) * A * inv(M1');
  r = inv(M1) * (b - A * x_bar);
  rho = r' * r;
  rho_old = rho;
  p = zeros(n);
  q = zeros(n);
  alpha = zeros(n);
  beta = zeros(n);

  while ((k <= n) && (rho > 1 * 10^-6))
    if (k == 1)
      p = r;
    else
      rho = r' * r;
      beta = rho / rho_old;
      rho_old = rho;
      p = p + beta * p;
    endif

    q = A_bar * p;
    alpha = rho / (p' * q);
    x_bar = x_bar + alpha * p;
    r = r - alpha * q;
    k++;
  endwhile  

  x_bar = inv(M1') * x_bar;
  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction

#!test
#! A = [1.86279, 0.47863, -0.54877; 0.47863, 1.61609, 0.10628; -0.54877,
#!      0.10628, 2.76115]
#! b = [1;2;3]
#! x = [0;0;0]
#! [x_bar, x_error, max_error] = dd_precondition(A, b, x)
#! assert(A * x_bar, b, 0.001)
