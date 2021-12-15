def p3(ih):
    return pow(ih,3)
def p4(ih):
    return pow(ih,4)
    
if __name__=="__main__":
    # j=[0,1,1]
    # s=[0,1,8]
    # p=[0,1,9]
    j=[0]*150
    s=[0]*150
    p=[0]*150
    j[1]=1
    j[2]=1
    s[1]=1
    s[2]=8
    p[1]=1
    p[2]=9
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
                p[ih]=p3(ih)
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
    print("s = ",min," = ",a,"^4 + ",b,"^4 = ",i,"^4 + ",j[i],"^4 + ")

