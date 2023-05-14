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

time_get_ill_dict = {}

coordinates_where_get_ill = {}


def check_dict_key_and_add(key, dictionary):
    if key not in dictionary:
        dictionary[key] = 1
    else:
        dictionary[key] += 1


currently_ill_in_time = {}
with open("../Build/currently_ill.log", "r") as file:
    for line in file:
        values = line.split(" ")
        time = int(values[0])
        number_of_ill = int(values[1])
        currently_ill_in_time[time] = number_of_ill

with open("../Build/ill.log", "r") as file:
    for line in file:
        values = line.split(" ")
        time_get_ill = int(values[0])

        check_dict_key_and_add(time_get_ill, time_get_ill_dict)

        x = int(values[1])
        y = int(values[2])
        check_dict_key_and_add((x, y), coordinates_where_get_ill)

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

max_x = 0
max_y = 0
for (x, y), _ in coordinates_where_get_ill.items():
    max_x = max(x, max_x)
    max_y = max(y, max_y)

with open("../Build/ill_table.csv", "w") as file:
    for x in range(max_x + 1):
        for y in range(max_y + 1):
            if (x, y) not in coordinates_where_get_ill:
                file.write("0")
            else:
                file.write(str(coordinates_where_get_ill[(x, y)]))
            file.write(",")
        file.write("\n")

print(f"{max_x=}")
print(f"{max_y=}")

import matplotlib.pyplot as plt

numbers = [get_ill_road, get_ill_work, get_ill_hospital, get_ill_home]
labels = ["road", "work", "hospital", "home"]
pos = list(range(len(numbers)))

plt.title("Get ill in places")
plt.bar(pos, numbers, color="blue")
plt.xticks(ticks=pos, labels=labels)
plt.show()

x, y = zip(*currently_ill_in_time.items())

plt.title("Total ill in time")
plt.plot(x, y)
plt.xlabel("time")
plt.ylabel("number of ill")
plt.show()

day = 1440
counter_days = 0
time_get_ill_in_days_dict = {}
for time, get_ill in time_get_ill_dict.items():
    if counter_days not in time_get_ill_in_days_dict:
        time_get_ill_in_days_dict[counter_days] = 0

    time_get_ill_in_days_dict[counter_days] += get_ill

    if time > counter_days * day:
        counter_days += 1

x, y = zip(*time_get_ill_in_days_dict.items())

plt.title("Get ill in days")
plt.plot(x, y)
plt.xlabel("days")
plt.ylabel("get ill")
plt.show()
