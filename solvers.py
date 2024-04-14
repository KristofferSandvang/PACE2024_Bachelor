import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('solvers.csv', names=['FileName', 'SolverName' ,'CrossingsSweep', 'DurationSweep', 'CrossingsNaive', 'DurationNaive', 'edges', 'vertices', 'CrossingsAfter'])

grouped = df.groupby(['FileName', 'SolverName'])['CrossingsAfter'].mean()

unstacked = grouped.unstack()

unstacked.plot(kind='bar', figsize=(10, 6))
plt.title('Comparison of CrossingsAfter for each Solver per File')
plt.xlabel('File Name')
plt.ylabel('Mean CrossingsAfter')
plt.show()

mean_crossings_after = df.groupby('SolverName')['CrossingsAfter'].mean()

print(mean_crossings_after)

mean_duration = df.groupby('SolverName')['DurationSweep'].mean()
print(mean_duration)