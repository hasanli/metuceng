input_string = input()
main = list(input_string)
main.pop(4)
qmark = input_string.find("?")
if input_string.find("X") == 5: main[4] = 10
if qmark != 0: main[0] = int(main[0])
if qmark != 1: main[1] = int(main[1])
if qmark != 2: main[2] = int(main[2])
if qmark != 3: main[3] = int(main[3])
if qmark != 5: main[4] = int(main[4])
if qmark == -1:
        if (main[0]*2 + main[1]*3 + main[2]*5 + main[3]*7) % 11 == main[4]: print("VALID")
        else: print("INVALID")
elif qmark == 5:
        if (main[0]*2 + main[1]*3 + main[2]*5 + main[3]*7) % 11 == 10: print(input_string[:4] + "-X")
        else: print(input_string[:4] + "-" + str((main[0]*2 + main[1]*3 + main[2]*5 + main[3]*7) % 11))
elif  0 <= qmark <= 3:
        if qmark == 0:
                hsum = main[1]*3 + main[2]*5 + main[3]*7 - main[4]
                mvalue = hsum // 11
                if ((mvalue + 1) * 11 - hsum) % 2 == 0: main[0] = int(((mvalue + 1) * 11 - hsum) / 2)
                else: main[0] = int(((mvalue + 2) * 11 - hsum) / 2)
        elif qmark == 1:
                hsum = main[0]*2 + main[2]*5 + main[3]*7 - main[4]
                mvalue = hsum // 11
                if   ((mvalue + 1) * 11 - hsum) % 3 == 0: main[1] = int(((mvalue + 1) * 11 - hsum) / 3)
                elif ((mvalue + 2) * 11 - hsum) % 3 == 0: main[1] = int(((mvalue + 2) * 11 - hsum) / 3)
                else: main[1] = int(((mvalue + 3) * 11 - hsum) / 3)
        elif qmark == 2:
                hsum = main[0]*2 + main[1]*3 + main[3]*7 - main[4]
                mvalue = hsum // 11
                if   ((mvalue + 1) * 11 - hsum) % 5 == 0: main[2] = int(((mvalue + 1) * 11 - hsum) / 5)
                elif ((mvalue + 2) * 11 - hsum) % 5 == 0: main[2] = int(((mvalue + 2) * 11 - hsum) / 5)
                elif ((mvalue + 3) * 11 - hsum) % 5 == 0: main[2] = int(((mvalue + 3) * 11 - hsum) / 5)
                elif ((mvalue + 4) * 11 - hsum) % 5 == 0: main[2] = int(((mvalue + 4) * 11 - hsum) / 5)
                else: main[2] = int(((mvalue + 5) * 11 - hsum) / 5)
        elif qmark == 3:
                hsum = main[0]*2 + main[2]*5 + main[1]*3 - main[4]
                mvalue = hsum // 11
                if   ((mvalue + 1) * 11 - hsum) % 7 == 0: main[3] = int(((mvalue + 1) * 11 - hsum) / 7)
                elif ((mvalue + 2) * 11 - hsum) % 7 == 0: main[3] = int(((mvalue + 2) * 11 - hsum) / 7)
                elif ((mvalue + 3) * 11 - hsum) % 7 == 0: main[3] = int(((mvalue + 3) * 11 - hsum) / 7)
                elif ((mvalue + 4) * 11 - hsum) % 7 == 0: main[3] = int(((mvalue + 4) * 11 - hsum) / 7)
                elif ((mvalue + 5) * 11 - hsum) % 7 == 0: main[3] = int(((mvalue + 5) * 11 - hsum) / 7)
                elif ((mvalue + 6) * 11 - hsum) % 7 == 0: main[3] = int(((mvalue + 6) * 11 - hsum) / 7)
                else: main[3] = int(((mvalue + 7) * 11 - hsum) / 7)
        if main[0] == 11: main[0] = 0
        if main[1] == 11: main[1] = 0
        if main[2] == 11: main[2] = 0
        if main[3] == 11: main[3] = 0
        if main[4] == 10: main[4] = "X"
        print(str(main[0]) + str(main[1]) + str(main[2]) + str(main[3]) + "-" + str(main[4]))