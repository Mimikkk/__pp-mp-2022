import json
from typing import *
import plotly as plt

import plotly.express as px


def async_perf():
    data: List[int]
    with open(f"../experimental/async_performance.json", "r") as file:
        data = json.load(file)

    (x, y) = zip(*enumerate(data))
    fig = px.scatter(x=x, y=y, render_mode="markers+lines", trendline='lowess')
    fig.update_layout(title=f"JSSP - Async Performance: ta02 | 15 machines 15 jobs | 10 sec each")
    fig.show()


async_perf()
