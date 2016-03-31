# hash

print hash
print hash(1)
print(hash(1L))

i = hash("hello world")
j = hash("hello" + " world")
print i == j

o1 = object()
o2 = object()
print hash(o1) == hash(o2)
