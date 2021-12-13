if __name__=="__main__":
    N=int(input('Input N: '))
    p=[0]
    p.append(2)
    print('Prim: ',p[1],end=' ')
    x=1
    lim=1
    for i in range(1,N):
        x=x+2
        if(pow(lim,2)<x):
            lim=lim+1
        k=2
        prim=True
        while prim and k<lim:
            prim=((x%p[k])!=0)
            k=k+1
        while prim==0:
            x=x+2
            if(pow(lim,2)<x):
                lim=lim+1
            k=2
            prim=True
            while prim and k<lim:
                prim=((x%p[k])!=0)
                k=k+1
        p.append(x)
        print(x,end=' ')
        
        
        
