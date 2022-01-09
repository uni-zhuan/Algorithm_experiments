def queens(A,k=0):
    global count
    if k==len(A):
        print(A)
        count +=1
        return 0
    for i in range(len(A)):
        A[k]=i
        if not check(A,k):
            continue
        else:
            queens(A,k+1)
 
def check(a,n):
    for i in range(n):
        if a[i]==a[n] or abs(a[n]-a[i])==n-i:
                return False
    return True
                    
count =0
queens([None]*8,k=0)
print(count)