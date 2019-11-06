#!/usr/bin/python
import csv

with open('test.csv','wb') as csv_file:
    writer = csv.writer(csv_file, delimiter=' ')
    for i in range(11):
        for j in range(11):
            writer.writerow([str(i)+".00",str(j)+".00",str(i+j)+".00"])



            