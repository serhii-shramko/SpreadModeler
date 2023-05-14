currently_susceptible_in_time = {}
with open("../Build/susceptible_number.log", "r") as file:
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
