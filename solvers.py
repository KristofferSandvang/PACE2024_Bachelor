import pandas as pd
import matplotlib.pyplot as plt
import numpy as np





df = pd.read_csv('solvers.csv', names=['FileName', 'SolverName' ,'CrossingsSweep', 'DurationSweep', 'edges', 'vertices', 'density', 'CrossingsAfter'])


filtered_df = df[df['SolverName'] != 'bogoMinimizer']
#filtered_df = df[df['SolverName'] != 'parentMinimizer']
mean_crossings_after = filtered_df.groupby('SolverName')['CrossingsAfter'].mean()
num_solvers = df['SolverName'].nunique()

colors = plt.cm.tab10(range(num_solvers))

colormap = {solver: color for solver, color in zip(df['SolverName'].unique(), colors)}
# Plotting
colors = [colormap[solver] for solver in mean_crossings_after.index]

mean_crossings_after.plot(kind='bar', figsize=(10, 6), zorder=2, color=colors)
plt.title('Mean Crossings for each Solver')
plt.xlabel('Solver Name')
plt.ylabel('Mean CrossingsAfter')
plt.grid(axis='y', linestyle='--', alpha=0.7, zorder=1) 
plt.xticks(rotation=45)
plt.tight_layout()  
plt.show()


df_grouped = df.groupby('SolverName')
jitter = 0.1
plt.figure(figsize=(10, 7))
ax = plt.gca()

for solver, group in df_grouped:
    y_transformed = np.log(group['CrossingsAfter'])
    group_sorted = group.sort_values('density')
    ax.scatter(group_sorted['density'], y_transformed, label=solver, color=colormap[solver])

ax.set_xlabel('graph density')
ax.set_ylabel('log(Crossings)')
plt.xticks(rotation=45)
ax.legend()
plt.show()

""" testDF = df[(df['density'] <= 0.06) & (df['SolverName'] != 'bogoMinimizer')]
testdf_grouped = testDF.groupby('SolverName')
jitter = 0.1
plt.figure(figsize=(10, 7))
ax = plt.gca()

for solver, group in testdf_grouped:
    y_transformed = np.log(group['CrossingsAfter'])
    group_sorted = group.sort_values('density')
    ax.scatter(group_sorted['density'], y_transformed, label=solver, color=colormap[solver])

ax.set_xlabel('graph density')
ax.set_ylabel('log(Crossings)')
plt.xticks(rotation=45)
ax.legend()
plt.show() """



mean_crossings_after = df.groupby('SolverName')['CrossingsAfter'].mean()

print(mean_crossings_after)

mean_duration = df.groupby('SolverName')['DurationSweep'].mean()
print(mean_duration)