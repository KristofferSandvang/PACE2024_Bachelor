import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv', names=['FileName', 'Crossings', 'DurationSweep', 'CrossingsNaive', 'DurationNaive'])

df['FileName'] = df['FileName'].str.lstrip('/')

""" # Sort by FileName
df = df.sort_values('FileName') """

plt.figure(figsize=(10, 5))
plt.plot(df['FileName'], df['Crossings'], label='Sweep')
plt.plot(df['FileName'], df['CrossingsNaive'], ':', label='Naive')
plt.xlabel('File Name')
plt.ylabel('Number of Crossings')
plt.xticks(rotation=90)
plt.legend()
plt.show()

plt.figure(figsize=(10, 5))
plt.plot(df['FileName'], df['DurationSweep'], label='Sweep')
plt.plot(df['FileName'], df['DurationNaive'], label='Naive')
plt.xlabel('File Name')
plt.ylabel('Duration (s)')
plt.xticks(rotation=90)
plt.legend()
plt.show()