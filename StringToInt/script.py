import sys
import subprocess
import os

name = "StringToInt"

for user, dir, files in os.walk('.'):
    if name in files:
        if os.name == "nt": #if run on Windows
            name += ".exe."
            name = user + '\\' + name
        else:
            name = user + '/' + name
        break


def check_results():
    another, res = None, list()
    with open(sys.argv[3], encoding='utf-8', errors='ignore') as file:
        for i in file:
            res.append(i.strip())
    if another is None:
        another = res
    if another != res:
        raise ValueError("Results are different")


if __name__ == "__main__":
    time = 0
    print("The minimum result of each method in microseconds:")
    for i in range(1, 4):
        for amount in range(int(sys.argv[1])):
            sub_run = subprocess.run([name, str(i), sys.argv[2], sys.argv[3]], shell=False,
                                     stdout=subprocess.PIPE)
            time = int(sub_run.stdout.decode().strip().split('\n')[-1])
        check_results()
        print("{} method: {}".format(i, time))
