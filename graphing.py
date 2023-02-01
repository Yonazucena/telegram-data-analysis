import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

dayFreq = pd.read_csv('daily.csv')
hourFreq = pd.read_csv('hourly.csv')
monthFreq = pd.read_csv('monthly.csv')
totalFreq = pd.read_csv('total.csv')

#day frequency
dayFreq.plot(x='day', y='count')
plt.gca().set_ylim(bottom=0)
plt.suptitle('Day Frequency')
plt.show()

#hour frequency
hourFreq.plot(x='hour', y='count')
plt.suptitle('Hour Frequency')
plt.show()

#month frequency
monthFreq.plot(x='month', y='count')
plt.suptitle('Month Frequency')
x_ticks = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
x_labels = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
plt.xticks(ticks=x_ticks, labels=x_labels)
plt.gca().set_ylim(bottom=0)
plt.show()

#message frequency
labels = 'Me', 'You'
sizes = [totalFreq.at[0, "nMessages1"], totalFreq.at[0, "nMessages2"]]
print(sizes)
colors = ['#FFC0CB', '#BCD2EB']
fig1, ax1 = plt.subplots()
ax1.pie(sizes, labels=labels, colors=colors)
ax1.axis('equal')
plt.title('Message Frequency')
plt.show()

#calls frequency
labels = 'Me', 'You'
sizes = [totalFreq.at[0, "nCalls1"], totalFreq.at[0, "nCalls2"]]
print(sizes)
colors = ['#FFC0CB', '#BCD2EB']
fig1, ax1 = plt.subplots()
ax1.pie(sizes, labels=labels, colors=colors)
ax1.axis('equal')
plt.title('Call Frequency')
plt.show()