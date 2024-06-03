# page size

the offset has 5 bits => $2^5=32$

# virtual -> physical

virtual memory addr => |page number|offset|
 
=> tlb: 
- hit => access the page frame
- miss => fetch from physical disk
