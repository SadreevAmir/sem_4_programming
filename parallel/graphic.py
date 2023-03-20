import json
import matplotlib.pyplot as plt

x = [1, 2, 3, 4, 5, 6, 7]
y = []
with open('data.json') as json_file:
    data = json.load(json_file)

for i in data:
    y.append(int(i))

fig, ax = plt.subplots()
ax.plot(x, y, marker='.', markersize=10)
ax.set_ylabel("duration")
ax.set_xlabel("threads")
plt.show()