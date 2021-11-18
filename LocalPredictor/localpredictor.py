table =[]
STA ="00"
DST ="00"
STD ={}

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

for i in range(100):
    for k in range(5):
        if "X" in STD:
            temp =STD["X"]
            STA =updateST(temp[0], temp[1], temp[2])
            STD["X"] =[STA, predict(STA), actual(k +1)]
            table.append([i, k +1, "X", STA, predict(STA), actual(k +1)])
        else:
            STD["X"] =[DST, predict(DST), actual(k +1)]
            table.append([i, k +1, "X", DST, predict(DST), actual(k +1)])
        
    if "Y" in STD:
        temp =STD["Y"]
        STA =updateST(temp[0], temp[1], temp[2])
        STD["Y"] =[STA, predict(STA), "T"]
        table.append([i +1, k +1, "Y", STA, predict(STA), "T"])
    else:
        STD["Y"] =[DST, predict(DST), "T"]
        table.append([i +1, k +1, "Y", DST, predict(DST), "T"])

counter =0
correct =0
for i in table:
    if i[4] ==i[5]:
        correct +=1
    counter +=1
    print(i)
    # if counter ==12:
    #     break
print(correct, "/", len(table))