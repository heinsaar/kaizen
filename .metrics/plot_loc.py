# This script is for later. Its purpose is to run in CI pipeline as part of the following steps:
# > cloc . --csv --quiet --report-file=loc.csv       # to count the lines of code in the repo
# > python .\plot_loc.py

import pandas as pd
import matplotlib.pyplot as plt

def main():
    # Load the CSV into a DataFrame
    df = pd.read_csv('loc.csv')
    
    # Filter out data for your language of interest, say, C++
    df_cpp = df[df['language'] == 'C++']

    # Generate the plot using row indices as a makeshift timestamp
    plt.figure(figsize=(10, 5))
    plt.plot(df_cpp.index, df_cpp['code'], marker='o')
    plt.xlabel('Day')
    plt.ylabel('LOC')
    plt.title('C++ Codebase Growth Over Time')
    plt.grid(True)

    # Optionally, annotate the latest point
    latest_point = (df_cpp.index[-1], df_cpp['code'].iloc[-1])
    plt.annotate(f'LOC: {latest_point[1]}', xy=latest_point, textcoords="offset points", xytext=(0,10), ha='center')

    # Save the plot as a PNG file
    plt.savefig('plot.png')

if __name__ == '__main__':
    main()
