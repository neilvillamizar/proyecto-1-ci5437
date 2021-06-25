c = ["RED", "YELLOW", "GREEN", "BLUE"]
ed = [3, 11, 13, 17, 19, 21, 23, 29, 31, 41, 43, 45]

for col in c:
    with open("12edges3colours" + col[0] + ".txt", "w") as f:
        #for n in ed:
        #    print("project " + str(n), file=f)
        for i in range(1, 49):
            if i % 2 == 0:
                print("project " + str(i), file=f)
        for i in range(4):
            if c[i] != col:
                print("map colour " + c[i] + " "  + col, file = f)