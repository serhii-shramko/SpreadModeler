from enum import Enum
class TileType(Enum):
    ROAD=2
    WORK=3
    HOSPITAL=4
    HOME=5

get_ill_road = 0
get_ill_work = 0
get_ill_hospital = 0
get_ill_home = 0

with open("../Build/ill.log","r") as file:
    for line in file:
        values = line.split(" ")
        match int(values[3]):
            case TileType.ROAD.value:
                get_ill_road+=1
            case TileType.WORK.value:
                get_ill_work+=1
            case TileType.HOSPITAL.value:
                get_ill_hospital+=1
            case TileType.HOME.value:
                get_ill_home+=1

print(f"{get_ill_road=}")
print(f"{get_ill_work=}")
print(f"{get_ill_hospital=}")
print(f"{get_ill_home=}")

