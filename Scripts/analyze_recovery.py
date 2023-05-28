import sys

if len(sys.argv) < 2:
    print(f"Usage {sys.argv[0]} <recovery.log>")
    exit()

recovery_log_file_name = sys.argv[1]

from os.path import exists

if not exists(recovery_log_file_name):
    print(f"{recovery_log_file_name} didn't exists")
    exit()

from enum import Enum


class TileType(Enum):
    ROAD = 2
    WORK = 3
    HOSPITAL = 4
    HOME = 5


get_recover_road = 0
get_recover_work = 0
get_recover_hospital = 0
get_recover_home = 0

time_get_recovered_dict = {}

coordinates_where_get_recover = {}


def check_dict_key_and_add(key, dictionary):
    if key not in dictionary:
        dictionary[key] = 1
    else:
        dictionary[key] += 1


with open(recovery_log_file_name, "r") as file:
    for line in file:
        values = line.split(" ")
        time_get_ill = int(values[0])

        check_dict_key_and_add(time_get_ill, time_get_recovered_dict)

        x = int(values[1])
        y = int(values[2])
        check_dict_key_and_add((x, y), coordinates_where_get_recover)

        match int(values[3]):
            case TileType.ROAD.value:
                get_recover_road += 1
            case TileType.WORK.value:
                get_recover_work += 1
            case TileType.HOSPITAL.value:
                get_recover_hospital += 1
            case TileType.HOME.value:
                get_recover_home += 1

print(f"{get_recover_road=}")
print(f"{get_recover_work=}")
print(f"{get_recover_hospital=}")
print(f"{get_recover_home=}")

max_x = 0
max_y = 0
for (x, y), _ in coordinates_where_get_recover.items():
    max_x = max(x, max_x)
    max_y = max(y, max_y)

with open("../Build/recovery_table.csv", "w") as file:
    for x in range(max_x + 1):
        for y in range(max_y + 1):
            if (x, y) not in coordinates_where_get_recover:
                file.write("0")
            else:
                file.write(str(coordinates_where_get_recover[(x, y)]))
            file.write(",")
        file.write("\n")

print(f"{max_x=}")
print(f"{max_y=}")

import matplotlib.pyplot as plt

numbers = [get_recover_road, get_recover_work, get_recover_hospital, get_recover_home]
labels = ["road", "work", "hospital", "home"]
pos = list(range(len(numbers)))

plt.title("Recovered in places")
plt.bar(pos, numbers, color="blue")
plt.xticks(ticks=pos, labels=labels)
plt.show()

total_recovered = {}
_, sum_of_recovered = next(iter(time_get_recovered_dict.items()))
for time, get_recover in time_get_recovered_dict.items():
    total_recovered[time] = sum_of_recovered
    sum_of_recovered += get_recover

x, y = zip(*total_recovered.items())

plt.title("Total recovered in time")
plt.plot(x, y)
plt.xlabel("time")
plt.ylabel("number of recovered")
plt.show()

day = 1440
counter_days = 0
time_get_recovered_in_days = {}
for time, get_recover in time_get_recovered_dict.items():
    if counter_days not in time_get_recovered_in_days:
        time_get_recovered_in_days[counter_days] = 0

    time_get_recovered_in_days[counter_days] += get_recover

    if time > counter_days * day:
        counter_days += 1


x, y = zip(*time_get_recovered_in_days.items())

plt.title("Recovered in days")
plt.plot(x, y)
plt.xlabel("days")
plt.ylabel("recovered")
plt.show()
