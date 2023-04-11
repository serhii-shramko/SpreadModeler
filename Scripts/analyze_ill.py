from enum import Enum


class TileType(Enum):
    ROAD = 2
    WORK = 3
    HOSPITAL = 4
    HOME = 5


get_ill_road = 0
get_ill_work = 0
get_ill_hospital = 0
get_ill_home = 0

time_get_ill = {}

with open("../Build/ill.log", "r") as file:
    for line in file:
        values = line.split(" ")
        if int(values[0]) not in time_get_ill:
            time_get_ill[int(values[0])] = 1
        else:
            time_get_ill[int(values[0])] += 1

        match int(values[3]):
            case TileType.ROAD.value:
                get_ill_road += 1
            case TileType.WORK.value:
                get_ill_work += 1
            case TileType.HOSPITAL.value:
                get_ill_hospital += 1
            case TileType.HOME.value:
                get_ill_home += 1

print(f"{get_ill_road=}")
print(f"{get_ill_work=}")
print(f"{get_ill_hospital=}")
print(f"{get_ill_home=}")
print(f"{time_get_ill=}")

import matplotlib.pyplot as plt

numbers = [get_ill_road, get_ill_work, get_ill_hospital, get_ill_home]
labels = ["road", "work", "hospital", "home"]
pos = list(range(len(numbers)))

plt.title("Get ill in places")
plt.bar(pos, numbers, color="blue")
plt.xticks(ticks=pos, labels=labels)
plt.show()

x,y = zip(*time_get_ill.items())

plt.title("Get ill in time")
plt.plot(x, y)
plt.xlabel("time")
plt.ylabel("get ill")
plt.show()