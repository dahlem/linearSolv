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


function L = dd_cholcrout(A)
  if (nargin != 1)
    usage("dd_cholcrout(A)");
  endif

  if (matrix_type(A) != "Positive Definite")
    error("The matrix A has to be positive definite.");
  endif

  L = zeros(rows(A), columns(A));

  for j = 1:columns(A)
    for i = j:rows(A)
      temp = 0;
      
      if (i > j)
	for k = 1 : (j - 1)
	  temp += L(i, k) * L(j, k);
	endfor
	
	L(i, j) = (A(i, j) - temp) / L(j, j);
      elseif (i == j)
	for k = 1 : (i - 1)
	  temp += L(i, k)^2;
	endfor
	
	L(i, i) = sqrt(A(i, i) - temp);
      endif
    endfor
  endfor
endfunction
