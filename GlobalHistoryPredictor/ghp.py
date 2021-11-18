# table =[]
# GHR ="0000"
# STA ="00"
# DST ="00"
# GHD ={}

# def updateGHR(ghr, table):
#     temp =table[-1]
    
#     if(temp[5] ==temp[6]):
#         return temp[3][1:] +"0"
#     return temp[3][1:] +"1"

# def updateST(state, predic, act):
#     if ((predic ==act) and (state =="00" or state =="11")):
#         return state
#     elif ((predic =="NT" and act =="T") or(predic =="T" and act =="T")):
#         if state =="00":
#             state ="01"
#         elif state =="01":
#             state ="10"
#         elif state =="10":
#             state ="11"
#     elif ((predic =="T" and act =="NT") or(predic =="NT" and act =="NT")):
#         if state =="01":
#             state ="00"
#         elif state =="10":
#             state ="01"
#         elif state =="11":
#             state ="10"
#     return state

# def actual(number):
#     if (4 >= number >=1):
#         return "T"
#     return "NT"
    
# def predict(state):
#     if state =="00" or state =="01":
#         return "NT"
#     return "T"

# cc =0
# for i in range(100):
#     for k in range(5):
#         if GHR in GHD:
#             temp =GHD[GHR]
#             STA =updateST(temp[0], temp[1], temp[2])
#             GHD[GHR] =[STA, predict(STA), actual(k +1)]
#             table.append([i, k +1, "X", GHR, STA, predict(STA), actual(k +1)])
#         else:
#             GHD[GHR] =[DST, predict(DST), actual(k +1)]
#             table.append([i, k +1, "X", GHR, DST, predict(DST), actual(k +1)])

#         # if k +1 ==4 and cc <3:
#         #     print(table[-1])
#         #     print(GHR)
#         GHR =updateGHR(GHR, table)
#         # if k +1 ==4 and cc <3:
#         #     print(GHR)
#         #     cc +=1
#         #     print()
        
#     if GHR in GHD:
#         temp =GHD[GHR]
#         STA =updateST(temp[0], temp[1], temp[2])
#         GHD[GHR] =[STA, predict(STA), "T"]
#         table.append([i +1, k +1, "Y", GHR, STA, predict(STA), "T"])
#     else:
#         GHD[GHR] =[DST, predict(DST), "T"]
#         table.append([i +1, k +1, "Y", GHR, DST, predict(DST), "T"])
#     GHR =updateGHR(GHR, table)

# counter =0
# correct =0
# correctX =0
# correctY =0
# for i in table:
#     if i[5] ==i[6]:
#         correct +=1
#         if i[2] =="X":
#             correctX +=1
#         else:
#             correctY +=1
#     # counter +=1
#     print(i)
#     # if counter ==12:
#     #     break
# print(correct, "/", len(table))
# print("correctX =", correctX)
# print("correctY =", correctY)

table =[]
GHR ="0000"
STA ="00"
DST ="00"
GHD ={}

def updateGHR(ghr, table):
    temp =table[-1]
    
    if(temp[6] =="T"):
        return temp[3][1:] +"1"
    return temp[3][1:] +"0"

def updateST(state, predic, act):
    if ((predic ==act) and (state =="00" or state =="11")):
        return state
    elif ((predic =="NT" and act =="T") or(predic =="T" and act =="T")):
        if state =="00":
            state ="01"
        elif state =="01":
            state ="10"
        elif state =="10":
            state ="11"
    elif ((predic =="T" and act =="NT") or(predic =="NT" and act =="NT")):
        if state =="01":
            state ="00"
        elif state =="10":
            state ="01"
        elif state =="11":
            state ="10"
    return state

def actual(number):
    if (4 >= number >=1):
        return "T"
    return "NT"
    
def predict(state):
    if state =="00" or state =="01":
        return "NT"
    return "T"

cc =0
for i in range(100):
    for k in range(5):
        if GHR in GHD:
            temp =GHD[GHR]
            STA =updateST(temp[0], temp[1], temp[2])
            GHD[GHR] =[STA, predict(STA), actual(k +1)]
            table.append([i, k +1, "X", GHR, STA, predict(STA), actual(k +1)])
        else:
            GHD[GHR] =[DST, predict(DST), actual(k +1)]
            table.append([i, k +1, "X", GHR, DST, predict(DST), actual(k +1)])

        # if k +1 ==4 and cc <3:
        #     print(table[-1])
        #     print(GHR)
        GHR =updateGHR(GHR, table)
        # if k +1 ==4 and cc <3:
        #     print(GHR)
        #     cc +=1
        #     print()
        
    if GHR in GHD:
        temp =GHD[GHR]
        STA =updateST(temp[0], temp[1], temp[2])
        GHD[GHR] =[STA, predict(STA), "T"]
        table.append([i +1, k +1, "Y", GHR, STA, predict(STA), "T"])
    else:
        GHD[GHR] =[DST, predict(DST), "T"]
        table.append([i +1, k +1, "Y", GHR, DST, predict(DST), "T"])
    GHR =updateGHR(GHR, table)

counter =0
correct =0
correctX =0
correctY =0
for i in table:
    if i[5] ==i[6]:
        correct +=1
        if i[2] =="X":
            correctX +=1
        else:
            correctY +=1
    # counter +=1
    print(i)
    # if counter ==12:
    #     break
print(correct, "/", len(table))
print("correctX =", correctX)
print("correctY =", correctY)