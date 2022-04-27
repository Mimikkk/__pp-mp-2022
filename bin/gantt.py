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

    e.g. ./gantt.py 22022021-14-04-31
    """
    # Read Data
    n: int
    m: int
    max_makespan: int
    schedule: List[List[int]]

    data: Dict
    with open(f"../solutions/{file_path}.json", "r") as file:
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
        plt.savefig(f"../solutions/charts/{save_path}")

    plt.show()


show_gantt(*sys.argv[1:4])
