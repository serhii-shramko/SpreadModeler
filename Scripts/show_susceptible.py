import sys

if len(sys.argv) < 2:
    print(f"Usage {sys.argv[0]} <susceptible.log>")
    exit()

susceptible_log_file_name = sys.argv[1]

from os.path import exists

if not exists(susceptible_log_file_name):
    print(f"{susceptible_log_file_name} didn't exists")
    exit()

currently_susceptible_in_time = {}
with open(susceptible_log_file_name, "r") as file:
    for line in file:
        values = line.split(" ")
        time = int(values[0])
        number_of_ill = int(values[1])
        currently_susceptible_in_time[time] = number_of_ill


import matplotlib.pyplot as plt

x, y = zip(*currently_susceptible_in_time.items())

plt.title("Total susceptible in time")
plt.plot(x, y)
plt.xlabel("time")
plt.ylabel("number of susceptible")
plt.show()
