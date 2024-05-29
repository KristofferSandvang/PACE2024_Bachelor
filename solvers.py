import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('solvers.csv', names=['FileName', 'SolverName' ,'CrossingsSweep', 'Duration', 'Edges', 'n0', 'n1', 'density', 'CrossingsAfter'])

df['SolverName'] = df['SolverName'].replace({0: 'Barycenter', 1: 'Median', 2: 'BCPermutation', 3: 'MedPermutation',
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
Barycenters = ['Barycenter', 'BCPermutation', 'BarycenterMed', 'BarycenterRev']
Medians = ['Median', 'MedPermutation', 'MedianBary', 'MedianRev']
Others = ['Bogo', 'Parent', 'Assignment']
CoreSolvers = ['Barycenter', 'Median']

# DFs for each test set:
tiny_df = df[df['FileName'].str.startswith('T')]
medium_df = df[df['FileName'].str.startswith('M')]
public_df = df[df['FileName'].str.startswith('P')]
testSets = [tiny_df, medium_df, public_df]
allTests_df = pd.concat(testSets, axis=0)

# DFs without Bogo
filtered_tiny = tiny_df[~tiny_df['SolverName'].isin(['Bogo', 'Assignment'])]
filtered_medium = medium_df[~medium_df['SolverName'].isin(['Bogo'])]
filtered_public = public_df[~public_df['SolverName'].isin(['Bogo', 'Assignment'])]
filtered_testSets = [filtered_tiny, filtered_medium, filtered_public]

# Public varients:
core_public = public_df[public_df['SolverName'].isin(CoreSolvers)]
bary_public = public_df[public_df['SolverName'].isin(Barycenters)]
med_public = public_df[public_df['SolverName'].isin(Medians)]
publics = [core_public, bary_public, med_public]

# Durations 
for solver in [bary_public, med_public]:
    mean_duration = solver.groupby('SolverName')['Duration'].mean()
    ax = mean_duration.plot(kind='bar',zorder=2, color=df['Color'])
    plt.ylabel('Mean Duration (s)')
    plt.xlabel(' ')
    plt.grid(axis='y', linestyle='--', alpha=0.7, zorder=1)
    for i, v in enumerate(mean_duration):
        ax.text(i, v + 0.05, f'{v:.2f}', ha='center', va='bottom', zorder=3) 
    plt.xticks(rotation=45)
    plt.tight_layout()  
    plt.show()




# Permutation limits
permutations = ['BCPermutation', 'MedPermutation']
permutation_df = public_df[public_df['SolverName'].isin(permutations)]

for solver, group in permutation_df.groupby('SolverName'):
    y = group['Duration']
    x_transformed = group['Edges']
    test_set_name = permutation_df['FileName'].iloc[0][0]
    plt.scatter(x_transformed, y, label=solver, color=colormap[solver])
    plt.axhline(y=280, color='red', linestyle='--', linewidth=1.5, zorder=0)
    plt.axvline(x=13000, color='red', linestyle='--', linewidth=1.5, zorder=0)
    plt.axhline(y=5, color='gray', linestyle='--', linewidth=1.5, zorder=0)
    plt.xlabel('Total number of edges')
    plt.ylabel('Duration (s)')
    plt.legend()
plt.show()

for solver, group in permutation_df.groupby('SolverName'):
    y = group['Duration']
    x_transformed = group['NumVertices']
    test_set_name = permutation_df['FileName'].iloc[0][0]
    plt.scatter(x_transformed, y, label=solver, color=colormap[solver])
    plt.axhline(y=280, color='red', linestyle='--', linewidth=1.5, zorder=0)
    plt.axvline(x=13500, color='red', linestyle='--', linewidth=1.5, zorder=0)
    plt.axhline(y=5, color='gray', linestyle='--', linewidth=1.5, zorder=0)
    plt.xlabel('Total number of vertices')
    plt.ylabel('Duration (s)')
    plt.legend()
plt.show()


allTests = testSets + filtered_testSets


filtered_df = pd.concat(filtered_testSets, axis=0)
# Overall victories
min_crossings_index = filtered_df.groupby('FileName')['CrossingsAfter'].idxmin()
victories = filtered_df.loc[min_crossings_index, 'SolverName']
victory_counts = victories.value_counts()
overall_victory_df = pd.DataFrame({'SolverName': victory_counts.index, 'Victories': victory_counts.values})
test_set_name = filtered_df['FileName'].iloc[0][0] 
print(overall_victory_df.to_latex(index=False))

min_crossings_index = filtered_public.groupby('FileName')['CrossingsAfter'].idxmin()
victories = filtered_public.loc[min_crossings_index, 'SolverName']
victory_counts = victories.value_counts()
public_victory_df = pd.DataFrame({'SolverName': victory_counts.index, 'Victories': victory_counts.values})
test_set_name = filtered_df['FileName'].iloc[0][0] 
print("================")
print(public_victory_df.to_latex(index=False))

# Mean crossings for each test set
for testSet in allTests:
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
for testSet in allTests:
    for solver, group in testSet.groupby('SolverName'):
        y_transformed = np.log10(np.mean(group['CrossingsAfter']))
        x_transformed = np.mean(group['Duration'])
        test_set_name = testSet['FileName'].iloc[0][0]
        plt.scatter(x_transformed, y_transformed, label=solver, color=colormap[solver])
        plt.title('Mean Crossings vs Mean Duration in {}'.format(test_set_name))
        plt.xlabel('Mean Duration')
        plt.ylabel('log10(Mean Crossings)')
        plt.legend()
    plt.show()


for testset in testSets:
    print({"Testset": testset['FileName'].iloc[0][0]})
    print(testset['NumVertices'].describe())
    print(testset['Density'].describe())
    print(testset['Edges'].describe())
    print("================================")

# make a new DF with the filenames and which solver won in.
min_crossings_index = filtered_df.groupby('FileName')['CrossingsAfter'].idxmin()
victories = filtered_df.loc[min_crossings_index, ['FileName', 'SolverName']]
test_set_name = filtered_df['FileName'].iloc[0]
victory_df = victories.reset_index(drop=True)

# All files with barycenter victories
barycenter_Wins = victory_df[victory_df['SolverName'].isin(Barycenters)]
barycenter_Wins = filtered_public[filtered_public['FileName'].isin(barycenter_Wins['FileName'])]
barycenter_Wins = barycenter_Wins[barycenter_Wins['SolverName'].isin(CoreSolvers)]
barycenter_Wins = barycenter_Wins[barycenter_Wins['SolverName'].isin(Barycenters)]
med_wins = victory_df[victory_df['SolverName'].isin(Medians)]
med_wins = filtered_public[filtered_public['FileName'].isin(med_wins['FileName'])]
med_wins = med_wins[med_wins['SolverName'].isin(CoreSolvers)]
med_wins = med_wins[med_wins['SolverName'].isin(Medians)]

wins = pd.concat([barycenter_Wins, med_wins], axis=0)
# Density intervals for which median / barycenter is better.
for solver, group in wins.groupby('SolverName'):
    y_transformed = np.log10(group['CrossingsAfter'])
    x = (group['Density'])
    plt.scatter(x, y_transformed, label=solver, color=colormap[solver])
    plt.xlabel('Density)')
    plt.ylabel('log10(Crossings)')
    plt.legend()
plt.xlim(0, 0.006)
plt.axvline(x=0.003, color='grey', linestyle='--')  
plt.axvline(x=0.005, color='grey', linestyle='--')  
plt.show()