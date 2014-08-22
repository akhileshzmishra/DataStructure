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

The data is stored consecutively. When you query to get 4th element, you would get D. After Insertion, if you query to get 4th element, you would get "Insert". Thus after insertion/deletion, the indices is manipulated to reflect new position of the member data.

Sure you could do the same with Linked list. But with _O(n)_ cost for insertion, deletion and finding.
See the table below.


|Sn | Parameter   |Index Tree       |  Linked list |
|---|-------------|-----------------|--------------|
|1. |Insertion    | _O(log(n))_     |     _O(n)_   |
|2. |Deletion     | _O(log(n))_     |     _O(n)_   |
|3. |Look up      | _O(log(n))_     |     _O(n)_   |
|4. |Memory       |Potentially 50% memory can be wastage|  No memory wastage _O(n)_ Memory requirement|

With careful deletion techniques, we can minimize the memory wastage (memory that is left unused due to regular bifurcation)

Testing: 
-------
Testing has been done thoroughly for this data structure. The data structure would serve the purpose a linked list does but with faster operation time. However, if found not suitable for your specific purpose, please send me the detail at akhileshzmishra@gmail.com with purpose you are trying to use (not the actual business purpose) and error if any that is being caused. I will get back to you on this.

2) TrieSet and TrieMap
======================
These are tries. If you know about them good. If you dont, please find them up on wiki. They are best used for map with string unique keys. However, here they are implemented as templates. So you can use any other key if you want. the operation cost is _O(l(Key)_ where l(Key) is the length of the key. In string, this is equal to string length. For integer, it can be bit size. (< 32 bits on a 32 bit machine)

Testing: 
-------
Testing has been done thoroughly for this data structure. However, if found not suitable for your specific purpose, please send me the detail at akhileshzmishra@gmail.com with purpose you are trying to use (not the actual business purpose) and error if any that is being caused. I will get back to you on this.


3 Boyer Moore (algorithm)
=========================
It is for sub string search. This algorithm performs substring search in _O(m)_ time.
Suppose the length of substring is _n_ and that of string is _m_
The total cost to search is _O(n*n)_ +  _O(m)_
When you have to search multiple times and/or m >> n, the first term is irrelevant.

It has been implemented as template. You can use it with wchar_t or char or any other key deem fit.

Testing: 
--------
Testing has been done thoroughly for this algorithm. However, if found not suitable for your specific purpose, please send me the detail at akhileshzmishra@gmail.com with purpose you are trying to use (not the actual business purpose) and error if any that is being caused. I will get back to you on this.


Finally
=======
I would introduce other data structure (not linked list, vectors or trees) which are not easily available later.
Keep me posted at akhileshzmishra@gmail.com

Thank you
