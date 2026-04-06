total = 78_000_000
BPS, SPF, FACES = 1024, 60, 4

pos = total % BPS
total_sect = total // BPS

s = total_sect % SPF
h = (total_sect // SPF) % FACES
c = (total_sect // SPF) // FACES

print(f"Cyl:{c}, Face:{h}, Sect:{s}, Pos:{pos}")