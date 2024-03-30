import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv', names=['FileName', 'Crossings', 'DurationSweep', 'CrossingsNaive', 'DurationNaive', 'edges', 'vertices'])

#df['FileName'] = df['FileName'].str.lstrip('/')

""" # Sort by FileName
df = df.sort_values('FileName') """


df = df.sort_values('edges')

plt.figure(figsize=(10, 7))
plt.plot(df['edges'], df['Crossings'], label='Sweep')
plt.plot(df['edges'], df['CrossingsNaive'], label='Naive', linestyle=":")
plt.xlabel('Number of edges')
plt.ylabel('Number of Crossings')
plt.xticks(rotation=90)
plt.legend()
plt.show()

plt.figure(figsize=(10, 7))
plt.scatter(df['edges'], df['DurationSweep'], label='Sweep')
plt.scatter(df['edges'], df['DurationNaive'], label='Naive')
plt.xlabel('Number of edges')
plt.ylabel('Duration (s)')
plt.xticks(rotation=90)
plt.legend()
plt.show()



df = df.sort_values('vertices')

plt.figure(figsize=(10, 7))
plt.plot(df['vertices'], df['Crossings'], label='Sweep')
plt.plot(df['vertices'], df['CrossingsNaive'], ':', label='Naive')
plt.xlabel('Number of vertices')
plt.ylabel('Number of Crossings')
plt.xticks(rotation=90)
plt.legend()
plt.show()

plt.figure(figsize=(10, 7))
plt.scatter(df['vertices'], df['DurationSweep'], label='Sweep')
plt.scatter(df['vertices'], df['DurationNaive'], label='Naive')
plt.xlabel('Number of vertices')
plt.ylabel('Duration (s)')
plt.xticks(rotation=90)
plt.legend()
plt.show()



print("Average number of crossings (Sweep):", df['Crossings'].mean())
print("Average number of crossings (Naive):", df['CrossingsNaive'].mean())
print("Average duration (Sweep):", df['DurationSweep'].mean())
print("Average duration (Naive):", df['DurationNaive'].mean())