import sys

drlSig = b'D31431'

CLo = 1
CHi = 2
CHiOvfl = 3
DLo = 4
DHi = 5
DHiOvfl = 6

in0 = open(sys.argv[1], "rb")
in1 = open(sys.argv[2], "rb")
out = open(sys.argv[3], "wb") # .drl

cont0 = bytearray(in0.read())
cont1 = bytearray(in1.read())
length = len(cont0)
contOut = bytearray(length)
offTab = bytearray()

for i in range(0, length):
    diff = (cont1[i] - cont0[i]) & 0xFF
    if diff == 0:
        contOut[i] = cont0[i]
    elif diff == 1:
        contOut[i] = cont0[i]
        offTab.extend([CLo, i & 0xFF, (i >> 8) & 0xFF]);
    elif diff == 2:
        contOut[i] = cont0[i]
        offTab.extend([CHi, i & 0xFF, (i >> 8) & 0xFF]);
    elif diff == 3:
        contOut[i] = cont0[i]
        offTab.extend([CHiOvfl, i & 0xFF, (i >> 8) & 0xFF]);
    elif diff == 4:
        contOut[i] = cont0[i]
        offTab.extend([DLo, i & 0xFF, (i >> 8) & 0xFF]);
    elif diff == 5:
        contOut[i] = cont0[i] - 0x80
        offTab.extend([DHi, i & 0xFF, (i >> 8) & 0xFF]);
    elif diff == 6:
        contOut[i] = cont0[i] - 0x80
        offTab.extend([DHiOvfl, i & 0xFF, (i >> 8) & 0xFF]);
    else:
        print("ERROR: Mismatched bytes at index")
        print(i)
        print(diff)
        print(".")

drlOut = bytearray()
drlOut.extend(drlSig)
drlOut.extend([len(offTab) & 0xFF, (len(offTab) >> 8) & 0xFF])
drlOut.extend(offTab)
drlOut.extend(contOut)

out.write(drlOut)
