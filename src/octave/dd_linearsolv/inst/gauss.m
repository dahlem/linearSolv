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
## Keywords: linear system, gaussian eliminatin
## Created: 10.12.2007
## Version: 0.1




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

