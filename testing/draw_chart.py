from matplotlib import pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import pandas as pd
import argparse
import math
import numpy as np

if __name__ == '__main__':
    parser = argparse.ArgumentParser('Creates a bar chart of the given excel where'
                                     'y axis is \'Params:\' and x axis is \'Found\'')
    parser.add_argument('name', help='name of summary excel file.', type=str)
    args = parser.parse_args()
    # plt.style.use('fivethirtyeight')

    # -----
    xls_name = args.name
    summary_excel = pd.read_excel(xls_name, sheet_name=None)
    pdf = PdfPages(xls_name.strip('.xlsx').strip('.xls') + '.pdf', keep_empty=False)
    percent_info = {}
    for sheet in summary_excel:
        summary = summary_excel.get(sheet)
        # if len(summary) <= 1:
        #     continue

        found, count = summary.iloc[-1]['Found:'].split('/')
        percent = (int(found) / int(count)) * 100
        percent_info[sheet] = [percent]

    names = set()
    for name in percent_info:
        names.add(''.join([s for s in name if not s.isnumeric()]).strip('-'))

    for name in names:
        df = pd.DataFrame({x: y for x, y in percent_info.items() if x.startswith(name)})
        fig = df.plot.bar()
        fig = fig.figure
        pdf.savefig(fig)
    pdf.close()

    # for sheet in summary_excel:
    #     summary = summary_excel.get(sheet)
    #     if len(summary) <= 1:
    #         continue
    #     summary = summary[:-1]   # removing summary at the end
    #
    #     # grouping data by <value, number of TRUE/FALSE>
    #     df = summary.groupby(['Params', 'Found:']).count()
    #     df = df.reset_index()
    #     df = df.pivot(index='Params', columns='Found:', values='Test Image')
    #     pdf = PdfPages(xls_name.strip('.xlsx').strip('.xls')+'_{}_chart.pdf'.format(sheet), keep_empty=False)
    #
    #     bar_chart = df.plot.bar(color=['r', 'b'])
    #     bar_chart.autoscale()
    #     bar_chart = bar_chart.figure
    #     # bar_chart.savefig(xls_name.strip('.xlsx').strip('.xls')+'_{}_chart.pdf'.format(sheet))
    #
    #     df2 = df.replace(float('nan'), 0)
    #     df2['%'] = [100 * x / (y + x) for x, y in zip(list(df2.get('TRUE', [0] * df2.size)),
    #                                                   list(df2.get('FALSE', [0] * df2.size)))]
    #
    #     df2.drop(['TRUE', 'FALSE'], axis=1, inplace=True, errors='ignore')
    #
    #     # -- set xlabel distribution
    #     ax = plt.gca()
    #
    #     max_value = df2['%'].max()
    #     min_value = df2['%'].min()
    #     number_of_steps = 5
    #
    #     l = np.arange(min_value, max_value + 1, number_of_steps)
    #     ax.set(xticks=l, xticklabels=l)
    #
    #     #  -- saving figure
    #     fig = df2.plot(rot=90)
    #     fig.autoscale()
    #     fig = fig.figure
    #     fig.suptitle('{} % Hist'.format(sheet))
    #     hist = df2.hist('%')
    #     pdf.savefig(hist)
    #     # pdf.savefig(fig)
    #     pdf.close()




