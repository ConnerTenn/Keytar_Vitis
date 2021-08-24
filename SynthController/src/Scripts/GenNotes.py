
#SampleRate=44800
UpdateFreq=100_000
Bits=24

notes=["A ","A$","B ","C ","C$","D ","D$","E ","F ","F$","G ","G$"]
out=[]
for n in range(0,95+1):
    f=(2**((n-60)/12))*440
    i=round((f*(2**Bits))/UpdateFreq)
    tf=(i*UpdateFreq)/(2**Bits) #True Freq
    # print("Note: "+notes[n%12]+str(int(n/12))+" ("+str(n)+")  Freq: "+str(round(f,3))+"  Incr:"+str(i))
    print("Note: {:3s} ({:2d})    Freq: {:7.2f}Hz   Incr: {:9d}   True Freq: {:7.2f}Hz ({:+6.3f}%)".format(
            notes[n%12]+str(int(n/12)), 
            n, f, i, tf,
            (tf/f-1)*100
        ))
    out+=[i]


# print()
# print()
# print("Python Code:")
# print()
# 
# print("{")
# for i in range(0,len(out)):
    # print("{:5}".format("\""+notes[i%12]+str(int(i/12))+"\"") + ":{:<5}".format(out[i]) + ",", end=('\n' if i%12==11 else ''))
# print("}")

print()
print()
print("C Code:")
print()

print(F"u32 NoteIncrs[{len(out)}] =")
print("{")
print("/*     ", end="")
for n in range(0,12):
    print(F"{notes[n]:<9s}", end="")
print("*/")
for i in range(0,len(out)):
    if i%12==0:
        print(F"/*{i//12}*/  ", end="")
        
    print("{:<9s}".format(str(out[i])+("," if i!=len(out)-1 else "")), end="")
    
    if i%12==11:
        print()
    
print("};")

print()
