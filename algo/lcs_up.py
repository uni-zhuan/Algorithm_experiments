import tkinter as tk
from tkinter import *
import numpy as np

#计算最优值
def LCSLength(m, n, x, y, c, b):
    for i in range(m):
        for j in range(n):
            if x[i] == y[j]:
                c[i+1][j+1] = c[i][j]+1
                b[i+1][j+1] = 1
            elif c[i+1][j] >= c[i][j+1]:
                c[i+1][j+1] = c[i+1][j]
                b[i+1][j+1] = 2
            else:
                c[i+1][j+1] = c[i][j+1]
                b[i+1][j+1] = 3

#构造最长公共子序列
def LCS(i, j, x, b):
    if i==0 or j==0:#递归出口
        return
    if b[i][j] == 1:#是构成LCS的元素
        LCS(i-1,j-1,x,b)
        print(x[i-1], end=' ')
        text.insert(tk.INSERT, x[i-1]+' ')
    elif b[i][j] == 2:#上行递归继续查找
        LCS(i,j-1,x,b)
    else:#左行递归继续查找
        LCS(i-1,j,x,b)

#得出所有最长公共子序列
def allInSet(i,j,c,x,y,s,m,n):
    while i>0 and j>0:
        if x[i-1]==y[j-1]:
            # 是构成最长公共子序列的元素
            canvas.create_oval(30+(j+1)*40, 230+(i)*40, 70+(j+1)*40, 270+(i)*40,width=2,outline="red")
            s+=x[i-1]
            i-=1
            j-=1
        else:
            # 不是构成最长公共子序列的元素,根据表c数据向序列开始处回退
            if c[i-1][j]>c[i][j-1]:
                i-=1
            elif c[i-1][j]<c[i][j-1]:
                j-=1
            else:
                # c[i-1][j]=c[i][j-1],分支产生,进行递归
               allInSet(i-1,j,c,x,y,s,m,n)
               allInSet(i,j-1,c,x,y,s,m,n)
               return
    # 向输出中加入最长公共子序列之一
    allResult.insert(tk.INSERT,s[::-1]+'\n')
    print(s[::-1])

def Input():
    length.delete('1.0','end')
    text.delete('1.0', 'end')
    formC.delete('1.0', 'end')
    formB.delete('1.0', 'end')
    m = int(input_m.get())
    n = int(input_n.get())
    x = input_x.get()
    y = input_y.get()
    c = [[0 for x in range(n+1)]for y in range(m+1)]
    b = [[0 for x in range(n+1)] for y in range(m+1)]

    LCSLength(m,n,x,y,c,b)
    LCS(m,n,x,b)
    s=''
    y1=230
    y2=270
    for i in range(n+2):
        x1=70
        x2=110
        for j in range(m):
            canvas.create_rectangle(x1,y1,x2,y2,fill="white",width=1,outline="black")         
            fillnum=c[i][j]
            canvas.create_text(x1+20,y1+20,text=fillnum)
            x1+=40
            x2+=40
        y1+=40
        y2+=40
    allInSet(m,n,c,x,y,s,m,n)

    length.insert(tk.INSERT,c[m][n])
    formC.insert(tk.INSERT,np.matrix(c))
    formB.insert(tk.INSERT,np.matrix(b))
    # print(c)
    # print(b)

#Input()

window = tk.Tk()
window.title('最长公共子序列')
window.geometry('750x550')
canvas=Canvas(width=750,height=550)
tk.Label(window, text = 'LCS problem', font=(20)).place(x=290,y=50)

btn = tk.Button(window, text = "start", font=(8),command = Input)
btn.place(x=420,y=45)

tk.Label(window, text = "X sequence length").place(x=50, y=100)
var_XLength = tk.StringVar()
input_m = tk.Entry(window, textvariable=var_XLength)
input_m.place(x=180, y=100)
tk.Label(window, text = "Y sequence length").place(x=50,y=130)
var_YLength = tk.StringVar()
input_n = tk.Entry(window, textvariable=var_YLength)
input_n.place(x=180, y=130)

tk.Label(window, text = "X sequence").place(x=50,y=160)
var_XSequence = tk.StringVar()
input_x = tk.Entry(window, textvariable=var_XSequence)
input_x.place(x=180, y=160)
tk.Label(window, text = "Y sequence").place(x=50,y=190)
var_YSequence = tk.StringVar()
input_y = tk.Entry(window, textvariable=var_YSequence)
input_y.place(x=180, y=190)



tk.Label(window, text = "longest").place(x=400,y=100)
length = tk.Text(window)
length.place(x=500, y=100,height=20,width=100)

tk.Label(window, text = "LCS").place(x=400,y=130)
text = tk.Text(window)
text.place(x=500, y=130, width=200,height=20)

tk.Label(window, text = "all LCS").place(x=400,y=160)
allResult = tk.Text(window)
allResult.place(x=500, y=160, width=200,height=60)

tk.Label(window, text = "b(m,n)").place(x=400,y=220)
formB = tk.Text(window)
formB.place(x=500, y=220, width=200,height=150)


tk.Label(window, text = "c(m,n)").place(x=400,y=380)
formC = tk.Text(window)
formC.place(x=500, y=380, width=200,height=150)
canvas.pack()
window.mainloop()
