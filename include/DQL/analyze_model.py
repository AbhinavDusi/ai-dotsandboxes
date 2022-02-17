import pandas as pd
import matplotlib.pyplot as plt

dataset = pd.read_csv("include/DQL/training_output.csv")

error_fig, error_ax = plt.subplots(1, figsize=(6, 4), constrained_layout=True)

episode = dataset["Episode"]
error = dataset["Error"]

error_ax.set_xlabel("Episode")
error_ax.set_ylabel("Error")

error_ax.plot(episode, error)

error_fig.savefig("include/DQL/training_error.pdf")