import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('solvers.csv', names=['FileName', 'SolverName' ,'CrossingsSweep', 'DurationSweep', 'edges', 'vertices', 'density', 'CrossingsAfter'])

df['SolverName'] = df['SolverName'].replace({0: 'Barycenter', 1: 'Median', 2: 'OptimizedBC', 3: 'OptimizedBCRight', 4: 'OptimiziedMedian', 5: 'Parent', 6: 'Bogo'})


filtered_df = df[df['SolverName'] != 'Bogo']
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


df_grouped = filtered_df.groupby('SolverName')
plt.figure(figsize=(10, 7))
ax = plt.gca()

for solver, group in df_grouped:
    y_transformed = np.log10(group['CrossingsAfter'])
    x_transformed = np.log10(group['edges'])
    ax.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])

ax.set_xlabel('log10(Edges)')
ax.set_ylabel('log10(Crossings)')
plt.xticks(rotation=45)
ax.legend()
plt.show()

plt.figure(figsize=(10, 7))
ax = plt.gca()

for solver, group in df_grouped:
    y_transformed = np.log10(group['CrossingsAfter'])
    x_transformed = np.log10(group['vertices'])
    ax.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])

ax.set_xlabel('log10(vertices)')
ax.set_ylabel('log10(Crossings)')
plt.xticks(rotation=45)
ax.legend()
plt.show()


for solver, group in df_grouped:
    y_transformed = np.log10(np.mean(group['CrossingsAfter']))
    x_transformed = np.mean(group['DurationSweep'])
    plt.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])

plt.xlabel('log10(Mean Duration)')
plt.ylabel('Mean Crossings')
plt.legend()
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