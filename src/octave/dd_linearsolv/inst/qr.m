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
##     dd_qr (@var{A}, @var{b}, @var{x})
## @cindex QR Factorisation, Iterative method
##
## @var{A} is the matrix to be solved with the solution vector @var{b}
## and a given x vector @var{x}.
## @var{x_bar} carries the solution.
##
## @end deftypefn

function [x_bar, x_error, max_error] = dd_qr(A, b, x)
  if (nargin != 3)
    usage("dd_qr(A, b, x)");
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

  [Q, R] = dd_qr_fact(A);

  M = [R, Q' * b];

  [M, x_bar] = dd_backwards(M);
  x_error = x - x_bar;
  max_error = max(abs(x_error));
  
endfunction


function [Q, R] = dd_qr_fact(A)
  Q = A;
  R = zeros(rows(Q));

  for j = 1:rows(Q)
    R(j, j) = norm(Q(:, j));
    if (R(j, j) == 0)
      error("QR cannot proceed because A has linear dependent columns.");
    else
      Q(:, j) = Q(:, j) / R(j, j);
    endif

    for k = (j + 1) : columns(Q)
      R(j, k) = dot(Q(:, j), Q(:, k));
      Q(:, k) = Q(:, k) - Q(:, j) * R(j, k);
    endfor
  endfor
endfunction


function [e] = dd_eigen(A, prec = 0.000001)
  if (matrix_type(A) != "Positive Definite")
    error("The matrix A has to be positive definite.");
  endif

  e = zeros(rows(A), 1);
  Ak = A;

  do
    d = diag(Ak);
    [Q, R] = dd_qr_fact(Ak);
    Ak = R * Q;
    error = max(abs(d - diag(Ak)));
  until (error < prec)

  i = 1;
  for k = rows(Ak):-1:1
    e(i++) = Ak(k, k);
  endfor
endfunction


#!test
#! A = [1.86279, 0.47863, -0.54877; 0.47863, 1.61609, 0.10628; -0.54877,
#!      0.10628, 2.76115]
#! b = [1;2;3]
#! x = [0;0;0]
#! [Q, R] = dd_qr_fact(A);
#! assert(Q * R, A, 0.001)
#! [x_bar, x_error, max_error] = dd_qr(A, b, x)
#! assert(A * x_bar, b, 0.02)
