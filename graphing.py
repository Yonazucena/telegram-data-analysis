import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

dayFreq = pd.read_csv('daily.csv')
hourFreq = pd.read_csv('hourly.csv')
monthFreq = pd.read_csv('monthly.csv')
totalFreq = pd.read_csv('total.csv')

dayFreq.columns = dayFreq.columns.str.strip()
hourFreq.columns = hourFreq.columns.str.strip()
monthFreq.columns = monthFreq.columns.str.strip()
totalFreq.columns = totalFreq.columns.str.strip()

#day frequency
plt.plot(dayFreq.day, dayFreq.nMessages)
plt.suptitle('Day Frequency')
plt.show()

#hour frequency
plt.plot(hourFreq.hour, hourFreq.nMessages)
plt.suptitle('Hour Frequency')
plt.show()

#month frequency
plt.suptitle('Month Frequency')
messagesME = monthFreq.nMessagesMe
messagesTHEM = monthFreq.nMessagesFriend
p1 = plt.bar(monthFreq.months,  messagesME)
p2 = plt.bar(monthFreq.months,  messagesTHEM, bottom=messagesME)
plt.xticks(rotation = 45)
plt.show()

#message frequency
labels = 'Me', 'Them'
sizes = [totalFreq.at[0, "nMessagesMe"], totalFreq.at[0, "nMessagesFriend"]]
print(sizes)
fig1, ax1 = plt.subplots()
ax1.pie(sizes, labels=labels)
ax1.axis('equal')
plt.title('Message Frequency')
plt.show()

#message frequency by character
labels = 'Me', 'Them'
sizes = [totalFreq.at[0, "indMsgsMe"], totalFreq.at[0, "indMsgsFriend"]]
fig1, ax1 = plt.subplots()
ax1.pie(sizes, labels=labels)
ax1.axis('equal')
plt.title('Message Frequency by character')
plt.show()