import pandas as pd
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser('Creates a bar chart of the given excel where'
                                     'y axis is \'Params:\' and x axis is \'Found\'')
    parser.add_argument('name', help='name of summary file.', type=str)
    args = parser.parse_args()

    xls_name = args.name
    summary = pd.read_excel(xls_name)

    bar_chart = summary.plot.bar(x='Found:', y='Params')
    bar_chart = bar_chart.figure
    bar_chart.savefig(xls_name.strip('.xlsx').strip('.xls')+'_chart.pdf')


