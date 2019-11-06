import pandas as pd
import os
df = pd.read_csv('test.csv', header=None)
ds = df.sample(frac=1)
ds.to_csv('shuffle.csv')
os.system('awk \'{sub(/[^,]*/,"");sub(/,/,"")} 1\' shuffle.csv | tail -n +2 > shuffled.csv' )