import matplotlib.pyplot as plt
from typing import *
import sys
import json


def show_gantt(file_path: str, title: Optional[str] = None, save_path: Optional[str] = None):
    """
    Function which produces the Gantt Chart and displays it and/or saves it
    :param file_path: solution file PATH location
    :param title: Title of the figure
    :param save_path: If SAVE_PATH is present the Gantt chart will be save to the given SAVE_PATH
    {
      "info": {
        "name": "abz5.txt",
        "instance": {
           "job_count": 5,
           "machine_count": 5,
        },
        "solution": {
            "makespan": 5,
            "schedule": [
              [8, 0, 94, 9, 94, 153, 2, 431, 514, 6, 633, 728, 4, 728, 827, 1, 827, 919, 3, 921, 997, 7, 997, 1059, 0, 1059, 1145, 5, 1145, 1233],
              [5, 0, 99, 9, 153, 235, 6, 235, 321, 8, 331, 397, 3, 397, 458, 7, 458, 529, 2, 529, 594, 0, 594, 661, 1, 919, 1001, 4, 1193, 1279],
              [3, 144, 212, 7, 378, 429, 8, 429, 519, 1, 519, 613, 5, 613, 693, 0, 693, 782, 4, 827, 894, 6, 894, 960, 2, 1018, 1073, 9, 1073, 1169],
              [9, 0, 50, 4, 50, 119, 8, 165, 246, 1, 246, 296, 7, 296, 378, 6, 537, 633, 3, 636, 690, 5, 921, 1000, 2, 1073, 1150, 0, 1150, 1242],
              [0, 0, 88, 7, 88, 186, 4, 186, 274, 5, 274, 355, 1, 365, 440, 6, 440, 537, 3, 537, 636, 8, 636, 712, 9, 716, 797, 2, 933, 1018],
              [1, 0, 72, 5, 355, 419, 0, 464, 563, 7, 563, 657, 8, 712, 770, 2, 770, 855, 3, 855, 921, 9, 921, 980, 4, 989, 1057, 6, 1057, 1156],
              [8, 94, 165, 7, 186, 259, 1, 296, 365, 0, 370, 464, 5, 464, 530, 2, 594, 658, 9, 658, 716, 3, 716, 791, 4, 894, 989, 6, 1156, 1208],
              [6, 0, 50, 3, 50, 144, 8, 246, 331, 9, 331, 387, 7, 657, 742, 5, 742, 811, 2, 855, 933, 0, 933, 1032, 1, 1032, 1126, 4, 1126, 1193],
              [9, 235, 302, 0, 302, 370, 2, 370, 431, 5, 530, 610, 4, 610, 705, 1, 705, 771, 6, 771, 868, 8, 868, 961, 7, 1059, 1154, 3, 1154, 1221],
              [2, 0, 83, 9, 387, 483, 4, 483, 565, 0, 782, 859, 5, 859, 921, 8, 961, 1058, 3, 1058, 1121, 7, 1154, 1233, 6, 1233, 1304, 1, 1304, 1367]
          ],
        }
      }
    }
    e.g. ./gantt.py 22022021-14-04-31
    """
    # Read Data
    n: int
    m: int
    max_makespan: int
    schedule: list[list[int]]

    data: dict
    with open(f"./solutions/{file_path}.json", "r") as file:
        data = json.load(file)

        (n, m) = (data['info']['instance']['job_count'], data['info']['instance']['machine_count'])
        max_makespan = data['solution']['makespan']
        schedule = data['solution']['schedule']

    colors = plt.get_cmap('hsv', n + 1)
    (figure, gantt) = plt.subplots()

    # Settings:
    if title:
        plt.title(title)

    # Axes limits
    gantt.set_ylim(0, (m + 2) * 10)
    gantt.set_xlim(0, round(max_makespan * 1.05))

    # Labels for axes
    gantt.set_xlabel('Time units since the beginning')
    gantt.set_ylabel('Machine')

    # Ticks on axes
    gantt.set_yticks([13 + 10 * i for i in range(m)])
    gantt.set_yticklabels([f'M{i}' for i in range(1, m + 1)])

    # Graph attribute
    gantt.grid(False)

    end: int
    job: int
    start: int
    for (machine, schedule) in enumerate(map(iter, schedule), 1):
        for _ in range(n):
            (job, start, end) = next(schedule), next(schedule), next(schedule)
            gantt.broken_barh([(start, end)], (10 * machine, 6), facecolors=colors(job))
            gantt.broken_barh([(end, max_makespan)], (10 * machine, 6), facecolors='w')

    brake = max_makespan / n

    # Label Jobs
    i: int = 0
    for i in range(n):
        gantt.broken_barh([(brake * i, brake + brake * i)], (0, 4), facecolors=colors(i))
        plt.text(brake * (i + 0.5), 0, f"{i + 1}")
    else:
        gantt.broken_barh([(brake + brake * i, max_makespan)], (0, 4), facecolors='w')
        gantt.axvline(x=max_makespan, color='r')

    plt.text(max_makespan - brake * (n - 1), 15 + 10 * m, f"Max Makespan: {max_makespan}", color='r')
    if save_path:
        plt.savefig(f"./solutions/charts/{save_path}")

    plt.show()


show_gantt(*sys.argv[1:4])
