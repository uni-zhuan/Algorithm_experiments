import networkx as nx
import matplotlib.pyplot as plt
import time
# start1 = time.perf_counter()
#print(start)

def knightGraph(bdSize):#形成无向图
    ktGraph = nx.Graph()
    for row in range(bdSize):
       for col in range(bdSize):
           nodeId = posToNodeId(row,col,bdSize)
           newPositions = genLegalMoves(row,col,bdSize)
           for e in newPositions:
               nid = posToNodeId(e[0],e[1],bdSize)
               ktGraph.add_edge(nodeId,nid,color='black')
    return ktGraph
def posToNodeId(row,col,bdSize):#节点标签：根据位置定义
    return row*bdSize+col
def genLegalMoves(x,y,bdSize):#从位置(x,y)出发，可到达的位置
    newMoves = []
    moveOffsets = [(-1,-2),(-1,2),(-2,-1),(-2,1),
                   ( 1,-2),( 1,2),( 2,-1),( 2,1)]
    for i in moveOffsets:
        newX = x + i[0]
        newY = y + i[1]
        if legalCoord(newX,bdSize) and legalCoord(newY,bdSize):
            newMoves.append((newX,newY))
    return newMoves
def legalCoord(x,bdSize):#是否超出棋盘范围
    if x >= 0 and x < bdSize:
        return True
    else:
        return False

def knightTour(n,path,u,limit):
        kg.node[u]['color']='gray'#已遍历到此节点
        #u.setColor('gray')
        path.append(u)#加入到队列中
        if n < limit:#未搜索到一条可行路径
            nbrList = list(kg.neighbors(u))#下一个可搜索的节点集合
            i = 0
            done = False
            while i < len(nbrList) and not done:
                if kg.node[nbrList[i]]['color'] == 'white':#节点未经过
                    done = knightTour(n+1, path, nbrList[i], limit)
                i = i + 1
            if not done:  # prepare to backtrack
                path.pop()
                kg.node[u]['color']='white'#设置成未搜索
                #u.setColor('white')
        else:
            done = True
        return done

def orderByAvail(n):#排序，边少的点优先
    resList = []
    for v in kg.neighbors(n):
        if kg.node[v]['color'] == 'white':#计算未走过的节点的所连接边的个数
            c = 0#计数
            for w in kg.neighbors(v):
                if kg.node[w]['color'] == 'white':
                    c = c + 1
            resList.append((c,v))
    resList.sort(key=lambda x: x[0])#按边的个数从小到大排序
    return [y[1] for y in resList]
def knightTourBetter(n,path,u,limit):  #use order by available function
        kg.node[u]['color']='gray'
        #u.setColor('gray')
        path.append(u)
        if n < limit:
            nbrList = orderByAvail(u)
            i = 0
            done = False
            while i < len(nbrList) and not done:
                if kg.node[nbrList[i]]['color'] == 'white':
                    done = knightTourBetter(n+1, path, nbrList[i], limit)
                i = i + 1
            if not done:  # prepare to backtrack
                path.pop()
                kg.node[u]['color']='white'
        else:
            done = True
        return done

n=8
kg = knightGraph(n)  #five by five solution
pos=[]
for i in range(n):
    for j in range(n):
        pos.append((i,j))
nx.draw(kg, pos, with_labels=True)#画出无向图
plt.show()

thepath = []#路径
for i in range(n*n):
    kg.node[i]['color'] = 'white'
start = 4#开始节点
knightTour(0,thepath,start,n*n-1)
print("可行路径为：")
for i in range(len(thepath)):#输出路径
    if i!=len(thepath)-1:
        print(thepath[i],end=' ->')
        kg[thepath[i]][thepath[i+1]]['color'] = 'blue'
    else:
        print(thepath[i])
nx.draw(kg,pos,with_labels=True,width=3,edge_color=[(v['color']) for x,y,v in kg.edges(data=True)])#
#走过的边为蓝色，没走过为黑色
nx.draw_networkx(kg,pos,with_labels=True,edge_color='blue')
nx.draw(kg,pos,with_labels=True,width=3,edge_color=(2,255,0))
plt.show()