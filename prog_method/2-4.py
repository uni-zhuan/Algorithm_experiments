# 确定a是否为素数
def prime(a):
    k=1
    if (a != 2):
        for i in range(2,a):
            if (a % i == 0):
                k = 0;
    else:
        k=1
    return k

if __name__=="__main__":
    for i in range(4,101,2):
        # 找到在2~n之间的所有素数对的组合
        q=0
        for j in range(2,i):
            if (prime(j)==1):
                for k in range(2,i):
                    if(prime(k)==1):
                        # 判断x + y是否等于n ，是输出结果
                        if (j+k==i and q==0):
                            # 按要求输出结果
                            print(i,"=",j,"+",k)
                            q=1
