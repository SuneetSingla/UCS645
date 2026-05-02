
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

if df["Utilization"].max() <= 1:
    df["Utilization"] = df["Utilization"] * 100


df_avg = df.groupby("Algorithm").mean(numeric_only=True).reset_index()

plt.figure()
plt.bar(df_avg["Algorithm"], df_avg["Makespan"])
plt.title("Average Makespan Comparison")
plt.xlabel("Algorithm")
plt.ylabel("Makespan")
plt.xticks(rotation=30)
plt.tight_layout()
plt.savefig("makespan.png")

plt.figure()
plt.bar(df_avg["Algorithm"], df_avg["Speedup"])
plt.title("Average Speedup Comparison")
plt.xlabel("Algorithm")
plt.ylabel("Speedup")
plt.xticks(rotation=30)
plt.tight_layout()
plt.savefig("speedup.png")

plt.figure()
plt.bar(df_avg["Algorithm"], df_avg["Utilization"])
plt.title("Average Utilization Comparison")
plt.xlabel("Algorithm")
plt.ylabel("Utilization (%)")
plt.xticks(rotation=30)
plt.tight_layout()
plt.savefig("utilization.png")

print("Graphs generated successfully!")
