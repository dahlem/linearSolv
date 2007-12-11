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
## Keywords: linear system, forward substitution, backward substitution
## Created: 11.12.2007
## Version: 1.0




1;


function [M, x_bar] = dd_backwards(M)
  if (nargin != 1)
    usage("dd_backwards(M)");
  endif

  if (matrix_type(M(:,1:columns(M) - 1)) != "Upper")
    error("The matrix M has to be upper triangular.");
  endif

  x_bar = zeros(rows(M), 1);
  
  for i = rows(M):-1:1
    x_temp = 0;
    
    for j = (i + 1) : (columns(M) - 1)
      x_temp += M(i,j) * x_bar(j);
    endfor

    x_bar(i) = (M(i, columns(M)) - x_temp) / M(i,i);
  endfor

endfunction


function [M, x_bar] = dd_forwards(M)
  if (nargin != 1)
    usage("dd_forwards(M)");
  endif

  if (matrix_type(M(:,1:columns(M) - 1)) != "Lower")
    error("The matrix M has to be lower triangular.");
  endif

  x_bar = zeros(rows(M), 1);
  
  for i = 1:rows(M)
    x_temp = 0;
    
    for j = 1 : (i - 1)
      x_temp += M(i,j) * x_bar(j);
    endfor

    x_bar(i) = (M(i, columns(M)) - x_temp) / M(i,i);
  endfor

endfunction


#!test
#! L = [2, 0, 0, 0; 3, -0.5, 0, 0; 2, 2, 1, 0; 1, 1.5, 4, 141]
#! U = [1, 0.5, 1.5, 2; 0, 1, -1, 16; 0, 0, 1, -41; 0, 0, 0, 1]
#! Ub = [5; 16; -40; 1]
#! MU = [U, Ub]
#! [M, x_bar] = dd_backwards(MU)
#! assert(x_bar == [1;1;1;1])
#! Lb = [2; 2.5; 5; 147.5]
#! ML = [L, Lb]
#! [M, x_bar] = dd_forwards(ML)
#! assert(x_bar == [1;1;1;1])
