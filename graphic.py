import matplotlib.pyplot as plt
import numpy as np

with open("new.txt", mode='r') as f:
    al = [[float(i)for i in el.split(", ")] for el in (f.readlines()[1:])]
    print(al)
    x = [el[0] for el in al]
    y = [el[1] for el in al]
    print(x, y, sep='\n')

plt.scatter(x, y)
plt.errorbar(x, y, ecolor='blue', elinewidth=1)
plt.ylabel('oC')
plt.xlabel('t, c')
plt.legend()
plt.show()