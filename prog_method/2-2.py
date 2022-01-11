def p3(ih):
    return pow(ih,3)
def p4(ih):
    return pow(ih,4)
    
if __name__=="__main__":
    # j=[0,1,1]
    # s=[0,1,8]
    # p=[0,1,9]
    j=[0]*200
    s=[0]*200
    p=[0]*200
    j[1]=1
    j[2]=1
    s[1]=1
    p[1]=1
    # s[2]=8
    # p[2]=9
    p[2] = 16
    s[2] = 17
    i=1
    ih=2
    il=1
    min=0
    while s[i]!=min:
        min=s[i]
        a=i
        b=j[i]
        if j[i]==i:
            il=il+1
        else:
            if j[i]==1:
                ih=ih+1
                # p[ih]=p3(ih)
                p[ih]=p4(ih)
                j[ih]=1
                s[ih]=p[ih]+1
            j[i]=j[i]+1
            s[i]=p[i]+p[j[i]]
        i=il
        k=i
        while k<ih:
            k=k+1
            if s[k]<s[i]:
                i=k
    # print("s=",min,"=",a,"^3+",b,"^3=",i,"^3+",j[i],"^3")
    print("s=",min,"=",a,"^4+",b,"^4=",i,"^4+",j[i],"^4")
