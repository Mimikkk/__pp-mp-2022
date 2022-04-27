from typing import *
import plotly as plt
import sys
import json


def create_scatter_plot(*files: str):
    """
    :param files: Files to add to scatter plots

    e.g. ./scatter.py 11022021-06-01-09 11022021-06-29-48
    """
    if len(files) < 1:
        print("Provide files", file=sys.stderr)
        return

    fig: plt.graph_objs.Figure = plt.graph_objs.Figure()

    for (i, filename) in enumerate(map(str.lower, files)):
        with open(f"../solutions/{filename}.json", "r") as file:
            file = json.load(file)
            if i == 0:
                fig.update_layout(
                    title=f"JSSP - Instance: {file['info']['instance']['name'].capitalize()}",
                    legend_title="Algorithms:")
            (x, y) = zip(*file['history'])
            fig.add_scatter(x=x, y=y, name=file['info']['metaheurestic'].capitalize(), mode='markers')
    fig.show()


create_scatter_plot(*sys.argv[1:])
