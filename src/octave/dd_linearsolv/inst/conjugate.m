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


function [x_bar, x_error, max_error] = dd_conjugate(A, b, x)
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
  p = b - A * x_bar;
  r = p;
  r_old = r;
  alpha = zeros(rows(A), 1);
  beta = zeros(rows(A), 1);
  k = 1;
  dp = norm(r)^2;

  while ((k <= rows(A)) || (dp > 1 * e^-12))
    alpha = dp / (dot(p, A * p));
    x_bar = x_bar + (alpha * p);
    r = r_old - alpha * A * p;
    beta = norm(r)^2 / norm(r_old)^2;
    p = r + beta * p;
    r_old = r;
    dp = norm(r)^2;
    k++;
  endwhile  
  
  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction

#!test
#! A = [1.86279, 0.47863, -0.54877; 0.47863, 1.61609, 0.10628; -0.54877,
#!      0.10628, 2.76115]
#! b = [1;2;3]
#! x = [0;0;0]
#! [x_bar, x_error, max_error] = dd_conjugate(A, b, x)
#! assert(A * x_bar, b, 0.001)
