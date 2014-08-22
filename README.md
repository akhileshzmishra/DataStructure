DataStructure And Algorithm
============================

1)Index Tree : _O(log n)_ operation for insertion, deletion and finding and yet preserves the order or index of the data.
=========================================================================================================================


As an example
There are 10 elements indexed from 1 - to - 10.

|Operation Type |Data with index. eg. 1 is index and A is data|
|---------------|---------------------------------------------|
|Initially      |1(A) 2(B) 3(C) 4(D) 5(E) 6(F) 7(G) 8(H) 9(I) 10(J)|
|Insertion at 4 |1(A) 2(B) 3(C) 4(Insert) 5(D) 6(E) 7(F) 8(G) 9(H) 10(I) 11(J)|
|Deletion at 8  |1(A) 2(B) 3(C) 4(Insert) 5(D) 6(E) 7(F) 8(H) 9(I) 10(J)|



Sure you could do the same with Linked list. But _O(n)_ cost for insertion, deletion and finding.
See the table below.


|Sn | Parameter   |Index Tree       |  Linked list |
|---|-------------|-----------------|--------------|
|1. |Insertion    | _O(log(n))_     |     _O(n)_   |
|2. |Deletion     | _O(log(n))_     |     _O(n)_   |
|3. |Look up      | _O(log(n))_     |     _O(n)_   |
|4. |Memory       |Potentially 50% memory can be wastage|  No memory wastage _O(n)_ Memory requirement|


