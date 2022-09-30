#!/usr/bin/env python3
import random


def main():
    for i in range(random.randint(1,20)):
        R = random.randint(10,100)
        r = random.randint(1,R)
        d = random.randint(2,100)
        angle = random.randint(0,360)

        red = random.randint(0,255)
        green = random.randint(0,255)
        blue = random.randint(0,255)
        print(f"{R} {r} {d} 10000 10000 {angle} {red} {green} {blue}")
if __name__ == "__main__":
    main()
