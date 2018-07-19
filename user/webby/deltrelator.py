import sys

drlSig = b'D31431'

C = 1
D = 2

in0 = open(sys.argv[1], "rb")
in1 = open(sys.argv[2], "rb")
out = open(sys.argv[3], "wb") # .drl

cont0 = bytearray(in0.read())
cont1 = bytearray(in1.read())
length = len(cont0)
contOut = bytearray(length)
offTab = bytearray()

i = 0

while i < length:
    diff0 = (cont1[i] - cont0[i]) & 0xFF
    if diff0 == 0:
        contOut[i] = cont0[i]
    elif diff0 == 1:
        offTab.extend([C, i & 0xFF, (i >> 8) & 0xFF]);
        contOut[i] = cont0[i]
        i += 1
        if i == length:
            print("ERROR: Only words can be relocated")
            exit(1)
        diff1 = (cont1[i] - cont0[i]) & 0xFF
        if not (diff1 == 2 or diff1 == 3):
            print("ERROR: Only words can be relocated")
            exit(1)
        contOut[i] = cont0[i]
    elif diff0 == 4:
        offTab.extend([D, i & 0xFF, (i >> 8) & 0xFF]);
        contOut[i] = cont0[i]
        i += 1
        if i == length:
            print("ERROR: Only words can be relocated")
            exit(1)
        diff1 = (cont1[i] - cont0[i]) & 0xFF
        if not (diff1 == 5 or diff1 == 6):
            print("ERROR: Only words can be relocated")
            exit(1)
        contOut[i] = cont0[i]
    else:
        print("ERROR: Mismatched bytes")
        exit(1)
        
    i += 1

drlOut = bytearray()
drlOut.extend(drlSig)
drlOut.extend([(len(offTab) / 3) & 0xFF, ((len(offTab) / 3) >> 8) & 0xFF])
drlOut.extend(offTab)
drlOut.extend(contOut)

out.write(drlOut)
