import os

# 每个方格对应的棋子类型
class Role:
    Player = 1
    Empty = 0
    AI = -1
# 剩余空表格总数，为0时判断平局
EmptyCount=9
# 游戏表格
Tabel=[[0,0,0],[0,0,0],[0,0,0]]
# 是否让 AI 先手
AIFirst=True

def ShouldAttack():
    return HaveTwoPiece(Role.AI)

def ShouldDefend():
    return HaveTwoPiece(Role.Player)

def SetPiece(x,y,role):
    global EmptyCount
    EmptyCount  -= 1
    #print(role ,"在 ",x ,"," , y ," 落子 ")
    global Tabel
    Tabel[x][y] = role

def HaveTwoPiece(role):
    global Tabel
    for i in range(0,3):
        #横向匹配行
        if (Tabel[i][0] == Tabel[i][1] and Tabel[i][0] ==role and Tabel[i][2] ==  Role.Empty):
            SetPiece(i,2,Role.AI)
            return True
        elif (Tabel[i][0] == Tabel[i][2] and Tabel[i][0] == role and Tabel[i][1] ==  Role.Empty):
            SetPiece(i, 1, Role.AI)
            return True
        elif (Tabel[i][1] == Tabel[i][2] and Tabel[i][1] == role and Tabel[i][0] ==  Role.Empty):
            SetPiece(i, 0, Role.AI)
            return True
        #纵向匹配行
        elif (Tabel[0][i] == Tabel[1][i] and Tabel[0][i] == role and Tabel[2][i] ==  Role.Empty):
            SetPiece(2, i, Role.AI)
            return True
        elif (Tabel[0][i] == Tabel[2][i] and Tabel[0][i] == role and Tabel[1][i] ==  Role.Empty):
            SetPiece(1, i, Role.AI)
            return True
        elif (Tabel[1][i] == Tabel[2][i] and Tabel[1][i] == role and Tabel[0][i] ==  Role.Empty):
            SetPiece(0, i, Role.AI)
            return True

    #对角线匹配行
    if (Tabel[0][0] == Tabel[1][1] and Tabel[0][0] == role and Tabel[2][2] ==  Role.Empty):
        SetPiece(2,2, Role.AI)
        return True
    elif (Tabel[1][1] == Tabel[2][2] and Tabel[1][1] == role and Tabel[0][0] ==  Role.Empty):
        SetPiece(0, 0, Role.AI)
        return True
    elif (Tabel[0][2] == Tabel[1][1] and Tabel[0][2] == role and Tabel[2][0] ==  Role.Empty):
        SetPiece(2, 0, Role.AI)
        return True
    elif (Tabel[1][1] == Tabel[2][0] and Tabel[1][1] == role and Tabel[0][2] ==  Role.Empty):
        SetPiece(0, 2, Role.AI)
        return True
    else:
        #不存在上述行
        return False

def AIStart():
    if (ShouldAttack()):
        print("AI 发起攻击！")
    elif (ShouldDefend()):
        print("AI 发起拦截！")
    elif (Center()):
        print("AI 占领中心点！")
    else:
        print("AI 进入垃圾时间...")
        PlanB()

def Center():
    global Tabel
    if (Tabel[1][1] ==  Role.Empty):
        SetPiece(1,1,Role.AI)
        return True
    else:
        return False
def PlanB():
    global Tabel
    #先角原则：
    #判断敌方是否占领了对角线两端，若存在则尝试占领剩余两角
    if (Tabel[0][0] == Tabel[2][2] and Tabel[0][0] == Role.Player):
        if (Tabel[0][2] == Role.Empty): SetPiece(0, 2, Role.AI)
        elif (Tabel[2][0]==  Role.Empty): SetPiece(2, 0, Role.AI)
    elif (Tabel[0][2] == Tabel[2][0] and Tabel[0][2] == Role.Player):
        if (Tabel[0][0] == Role.Empty): SetPiece(0, 0, Role.AI)
        elif (Tabel[2][2] == Role.Empty): SetPiece(2, 2, Role.AI)

    #判断敌方是否占领了相邻两棱，若存在则尝试占领两棱相对的一角
    elif ((Tabel[0][1] == Role.Player and Tabel[1][0] == Role.Player) and Tabel[0][0] == Role.Empty):
        SetPiece(0, 0, Role.AI)
    elif ((Tabel[0][1] == Role.Player and Tabel[1][2] == Role.Player) and Tabel[0][2] == Role.Empty):
        SetPiece(0, 2, Role.AI)
    elif ((Tabel[2][1] == Role.Player and Tabel[1][0] == Role.Player) and Tabel[2][0] == Role.Empty):
        SetPiece(2, 0, Role.AI)
    elif ((Tabel[2][1] == Role.Player and Tabel[1][2] == Role.Player) and Tabel[2][2] == Role.Empty):
        SetPiece(2, 2, Role.AI)

    #玩家占领棱位，我方占领对角
    elif ((Tabel[0][1] == Role.Player or Tabel[1][0] == Role.Player) and Tabel[2][2] == Role.Empty):
        SetPiece(2, 2, Role.AI)
    elif ((Tabel[0][1] == Role.Player or Tabel[1][2] == Role.Player) and Tabel[2][0] == Role.Empty):
        SetPiece(2, 0, Role.AI)
    elif ((Tabel[2][1] == Role.Player or Tabel[1][0] == Role.Player) and Tabel[0][2] == Role.Empty):
        SetPiece(0, 2, Role.AI)
    elif ((Tabel[2][1] == Role.Player or Tabel[1][2] == Role.Player) and Tabel[0][0] == Role.Empty):
        SetPiece(0, 0, Role.AI)

    #随便找空角下子
    elif (Tabel[0][0] == Role.Empty):
        SetPiece(0, 0, Role.AI)
    elif (Tabel[0][2] == Role.Empty):
        SetPiece(0, 2, Role.AI)
    elif (Tabel[2][0] == Role.Empty):
        SetPiece(2, 0, Role.AI)
    elif (Tabel[2][2] == Role.Empty):
        SetPiece(2, 2, Role.AI)
    elif (Tabel[0][1] == Role.Empty):
        SetPiece(0, 1, Role.AI)
    elif (Tabel[1][0] == Role.Empty):
        SetPiece(1, 0, Role.AI)
    elif (Tabel[1][2] == Role.Empty):
        SetPiece(1, 2, Role.AI)
    elif (Tabel[2][1] == Role.Empty):
        SetPiece(2, 1, Role.AI)

def GetWinner():
    global Tabel
    for i in range(0,3):
        if (Tabel[i][0] == Tabel[i][1] and Tabel[i][0] == Tabel[i][2] and Tabel[i][0] != 0):
            return Tabel[i][0]
        if (Tabel[0][i] == Tabel[1][i] and Tabel[0][i] == Tabel[2][i] and Tabel[0][i] != 0):
            return Tabel[0][i]

    #对角线
    if (Tabel[0][0] == Tabel[1][1] and Tabel[1][1] == Tabel[2][2] and Tabel[1][1]!=0):
        return Tabel[1][1]
    if (Tabel[0][2] == Tabel[1][1] and Tabel[1][1] == Tabel[2][0] and Tabel[1][1] != 0):
        return Tabel[1][1]
    else:
        #平局
        return Role.Empty

def PlayerInput(Error=0):
    global Tabel
    # 把错误代码传送给输出函数，用于显示错误信息
    PrintGame(Error)
    #这里严防输入参数过多或过少，必须要是两个数字用逗号分开，否则出错
    x,y=map(int,input("\n请输入落子坐标（以逗号分开，介于[0~2],[0~2]之间）:").split(","))
    if (0<= x and x <=2) and (0<=y and y<=2):
        if (Tabel[x][y]==Role.Empty):
            SetPiece(x,y,Role.Player)
        else:
            PlayerInput(2)
    else:
        PlayerInput(1)

def PrintGame(Error=0):
    global Tabel
    os.system('cls')
    print("※ 0  1  2")
    for x in range(0,3):
        Line =" " + str(x)
        for y in range(0,3):
            if Tabel[x][y]==Role.Player:
                Line += " ●"
            elif Tabel[x][y]==Role.AI:
                Line +=" ×"
            elif Tabel[x][y]==Role.Empty:
                Line +=" □"
        print(Line)
    if Error ==1:
        print("\n输入坐标越界，请重新输入！")
    elif Error ==2:
        print("\n输入的坐标已经有棋子，请重新输入！")

def ResetGame():
    os.system('cls')
    global AIFirst
    global Tabel
    global EmptyCount
    print("\n游戏结束，重置游戏！");
    Tabel = [[0,0,0],[0,0,0],[0,0,0]];
    EmptyCount = 9;
    #每次游戏结束后，交换AI和玩家先手
    AIFirst = not AIFirst
    if AIFirst: AIStart()
    PrintGame();

if AIFirst: AIStart()
while True:
    PlayerInput()
    AIStart()
    Winner = GetWinner()
    PrintGame()
    if (Winner == Role.Empty):
        if (EmptyCount<=0):
            print("\n棋逢对手！201621123034与AI双方平局！\n")
            ResetGame()
    else:
        if Winner==Role.Player:
            print("\n游戏结束！胜利者：201621123034\n")
        elif Winner ==Role.AI:
            print("\n游戏结束！胜利者：AI\n")
        os.system("pause")
        ResetGame()
