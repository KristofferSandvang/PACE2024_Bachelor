import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('solvers.csv', names=['FileName', 'SolverName' ,'CrossingsSweep', 'DurationSweep', 'Edges', 'n0', 'n1', 'density', 'CrossingsAfter'])

df['SolverName'] = df['SolverName'].replace({0: 'Barycenter', 1: 'Median', 2: 'OptimizedBC', 3: 'OptimiziedMedian',
                                             4: 'Parent', 5: 'Bogo', 6: 'MedianBary', 7: 'MedianRev', 8: 'BarycenterMed', 
                                             9: 'BarycenterRev', 10: 'Assignment'})

# Density & NumVertices
df['Density'] = df['Edges'] / (df['n0']*df['n1'])
df['NumVertices'] = df['n0'] + df['n1']

# Colors
num_solvers = df['SolverName'].nunique()
colors = plt.cm.tab20(range(num_solvers))
colormap = {solver: color for solver, color in zip(df['SolverName'].unique(), colors)}
df['Color'] = df['SolverName'].map(colormap)

# Solver Groups
Barycenters = ['Barycenter', 'OptimizedBC', 'BarycenterMed', 'BarycenterRev']
Medians = ['Median', 'OptimiziedMedian', 'MedianBary', 'MedianRev']
Others = ['Bogo', 'Parent', 'Assignment']
CoreSolvers = ['Barycenter', 'Median']

# DFs for each test set:
tiny_df = df[df['FileName'].str.startswith('T')]
medium_df = df[df['FileName'].str.startswith('M')]
public_df = df[df['FileName'].str.startswith('P')]
testSets = [tiny_df, medium_df, public_df]

# DFs without Bogo
filtered_tiny = tiny_df[~tiny_df['SolverName'].isin(['Bogo', 'Assignment'])]
filtered_medium = medium_df[~medium_df['SolverName'].isin(['Bogo', 'Assignment'])]
filtered_public = public_df[~public_df['SolverName'].isin(['Bogo', 'Assignment'])]
filtered_testSets = [filtered_tiny, filtered_medium, filtered_public]

# Public varients:
core_public = public_df[public_df['SolverName'].isin(CoreSolvers)]
bary_public = public_df[public_df['SolverName'].isin(Barycenters)]
med_public = public_df[public_df['SolverName'].isin(Medians)]
publics = [core_public, bary_public, med_public]



allTests = testSets + filtered_testSets

# Count victories (where victory is achived by the minimum number of crossings)
for testSet in testSets:
    min_crossings_index = testSet.groupby('FileName')['CrossingsAfter'].idxmin()
    victories = testSet.loc[min_crossings_index, 'SolverName']
    victory_counts = victories.value_counts()
    victory_df = pd.DataFrame({'SolverName': victory_counts.index, 'Victories': victory_counts.values})
    test_set_name = testSet['FileName'].iloc[0][0] 
    print(test_set_name)
    print(victory_df)
    print("\n")


# Mean crossings for each test set
""" for testSet in allTests:
    test_set_name = testSet['FileName'].iloc[0][0] 
    mean_crossings = testSet.groupby('SolverName')['CrossingsAfter'].mean()
    mean_crossings.plot(kind='bar', zorder=2, color=df['Color'])
    plt.title('Mean Crossings for each solver in {}'.format(test_set_name))
    plt.xlabel('Solver Name')
    plt.ylabel('Crossings')
    plt.grid(axis='y', linestyle='--', alpha=0.7, zorder=1) 
    plt.xticks(rotation=45)
    plt.tight_layout()  
    plt.show()

# Crossings vs time
for testSet in filtered_testSets:
    for solver, group in testSet.groupby('SolverName'):
        y_transformed = np.log10(np.mean(group['CrossingsAfter']))
        x_transformed = np.mean(group['DurationSweep'])
        test_set_name = testSet['FileName'].iloc[0][0]
        plt.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])
        plt.title('Mean Crossings vs Mean Duration in {}'.format(test_set_name))
        plt.xlabel('Mean Duration')
        plt.ylabel('log10(Mean Crossings)')
        plt.legend()
    plt.show() """

# check if n0 > n1
greater = core_public[(core_public['n0'] > core_public['n1']) & (core_public['CrossingsAfter'] != 0)]
lesser = core_public[(core_public['n0'] < core_public['n1'])  & (core_public['CrossingsAfter'] != 0)]
equal = core_public[(core_public['n0'] == core_public['n1'])  & (core_public['CrossingsAfter'] != 0)]

vertices_variants = [greater, lesser, equal]
width = 0.35
for variant in vertices_variants:
    x = np.arange(len(variant['FileName'].unique()))
    y1 = np.log10(variant[variant['SolverName'] == 'Barycenter']['CrossingsAfter'])
    y2 = np.log10(variant[variant['SolverName'] == 'Median']['CrossingsAfter'])
    plt.bar(x, y1, width=width, color=colormap['Barycenter'], label='Barycenter', zorder=2)
    plt.bar(x + width, y2, width=width, color=colormap['Median'], label='Median', zorder=2)
    plt.xticks(x + width/2,variant['FileName'].unique()) 
    plt.grid(linestyle='--', zorder=1) 
    plt.legend()
    plt.show()
    

    """ for solver, group in variant.groupby('SolverName'):
        y_transformed = np.log10(group['CrossingsAfter'])
        x = np.log10(group['NumVertices'])
        test_set_name = testSet['FileName'].iloc[0][0]
        plt.scatter(x, y_transformed, label=solver, color=colormap[solver])
        plt.title('{}'.format(test_set_name))
        plt.xlabel('log10(NumVertices)')
        plt.ylabel('log10(Crossings)')
        plt.legend()
    plt.show()
 """




# Note if edges > 50000 median wins
""" df['Density1'] = df['edges'] / (df['vertices1']*df['vertices2'])
filtered_df = df[~df['SolverName'].isin(['Bogo'])].copy()
filtered_df.loc[:, 'NunVertices'] = filtered_df['vertices1'] + filtered_df['vertices2']

mean_crossings_after = filtered_df.groupby('SolverName')['CrossingsAfter'].mean()

colors = plt.cm.tab10(range(num_solvers))

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
    x_transformed = np.log10(group['NunVertices'])
    ax.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])

ax.set_xlabel('log10(NunVertices)')
ax.set_ylabel('log10(Crossings)')
plt.xticks(rotation=45)
ax.legend()
plt.show()


for solver, group in df_grouped:
    y_transformed = np.log10(np.mean(group['CrossingsAfter']))
    x_transformed = np.mean(group['DurationSweep'])
    plt.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])

plt.xlabel('Mean Duration')
plt.ylabel('log10(Mean Crossings)')
plt.legend()
plt.show()


testDF = df[(df['Density1'] <= 0.06) & (df['SolverName'] != 'bogoMinimizer')]
testdf_grouped = testDF.groupby('SolverName')
jitter = 0.1
plt.figure(figsize=(10, 7))
ax = plt.gca()

for solver, group in testdf_grouped:
    y_transformed = np.log(group['CrossingsAfter'])
    group_sorted = group.sort_values('Density1')
    ax.scatter(group_sorted['Density1'], y_transformed, label=solver, color=colormap[solver])

ax.set_xlabel('graph density')
ax.set_ylabel('log(Crossings)')
plt.xticks(rotation=45)
ax.legend()
plt.show()



mean_crossings_after = df.groupby('SolverName')['CrossingsAfter'].mean()
sum_crossings_after = df.groupby('SolverName')['CrossingsAfter'].sum()

print(mean_crossings_after.sort_values())
print(sum_crossings_after.sort_values())

mean_duration = df.groupby('SolverName')['DurationSweep'].mean()
print(mean_duration)

solvers = ['Barycenter', 'Median', 'OptimizedBC', 'OptimiziedMedian', 'MedianBary', 'MedianRev', 'BarycenterMed', 'barycenterRev']

plt.figure(figsize=(10, 6))

for solver in solvers:
    solver_df = df[df['SolverName'] == solver]
    plt.scatter(solver_df['Density1'], np.log10(solver_df['CrossingsAfter']), label=solver)

plt.title('Density vs CrossingsAfter')
plt.xlabel('Density1')
plt.ylabel('CrossingsAfter')
plt.legend()

plt.show()

negative_values = df[df['Density1'] > 0.4]['Density1'] 
print(negative_values)
print(df['Density1'].describe())


 """