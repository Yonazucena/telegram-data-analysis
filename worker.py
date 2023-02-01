import json
import vars 
#vars.py contains userid of the two ppl
import time
import csv
import math

year = input("input year you want to see: ")

f = open('result.json', encoding="utf8")
data = json.load(f)

#total messages
total1 = 0
total2 = 0

#calls
calls1 = 0
calls2 = 0
timeCall = 0

#stickers
emojisDict1 = {}
emojisDict2 = {}

monthsList = [
    {'month': 'January', 'count': 0},
    {'month': 'February', 'count': 0},
    {'month': 'March', 'count': 0},
    {'month': 'April', 'count': 0},
    {'month': 'May', 'count': 0},
    {'month': 'June', 'count': 0},
    {'month': 'July', 'count': 0},
    {'month': 'August', 'count': 0},
    {'month': 'September', 'count': 0},
    {'month': 'October', 'count': 0},
    {'month': 'November', 'count': 0},
    {'month': 'December', 'count': 0}
]

hoursList = [
    {'hour': '00', 'count': 0},
    {'hour': '01', 'count': 0},
    {'hour': '02', 'count': 0},
    {'hour': '03', 'count': 0},
    {'hour': '04', 'count': 0},
    {'hour': '05', 'count': 0},
    {'hour': '06', 'count': 0},
    {'hour': '07', 'count': 0},
    {'hour': '08', 'count': 0},
    {'hour': '09', 'count': 0},
    {'hour': '10', 'count': 0},
    {'hour': '11', 'count': 0},
    {'hour': '12', 'count': 0},
    {'hour': '13', 'count': 0},
    {'hour': '14', 'count': 0},
    {'hour': '15', 'count': 0},
    {'hour': '16', 'count': 0},
    {'hour': '17', 'count': 0},
    {'hour': '18', 'count': 0},
    {'hour': '19', 'count': 0},
    {'hour': '20', 'count': 0},
    {'hour': '21', 'count': 0},
    {'hour': '22', 'count': 0},
    {'hour': '23', 'count': 0},
]

dayWeekList = [
    {'day': 'Monday', 'count': 0},
    {'day': 'Tuesday', 'count': 0},
    {'day': 'Wednesday', 'count': 0},
    {'day': 'Thursday', 'count': 0},
    {'day': 'Friday', 'count': 0},
    {'day': 'Saturday', 'count': 0},
    {'day': 'Sunday', 'count': 0}
]

def find(lst, key, value):
    for i, dic in enumerate(lst):
        if dic[key] == value:
            return i

totalItems = len(data['messages'])
countItem = 0

for i in data['messages']:
    #print(i['id'])

    #print progress
    countItem += 1
    if (countItem == math.trunc(totalItems*25/100)):
        print("25%")
    if (countItem == math.trunc(totalItems*50/100)):
        print("50%")
    if (countItem == math.trunc(totalItems*75/100)):
        print("75%")
    if (countItem == totalItems):
        print("100%")

    if(i['date'][0:4] == year):
        if (i['type'] == 'message'):
            #number of messages
            if (i['from_id'] == vars.me):
                total1 += 1

                if "sticker_emoji" in i:
                    if (i['sticker_emoji'] in emojisDict1):
                        emojisDict1[i['sticker_emoji']] += 1
                    else:
                        emojisDict1[i['sticker_emoji']] = 1

            elif (i['from_id'] == vars.him):
                total2 += 1

                if "sticker_emoji" in i:
                    if (i['sticker_emoji'] in emojisDict2):
                        emojisDict2[i['sticker_emoji']] += 1
                    else:
                        emojisDict2[i['sticker_emoji']] = 1

            #by month
            current_month = i['date'][5:7]
            monthsList[int(current_month)-1]['count'] += 1

            #by hour
            current_hour = i['date'][11:13]
            hoursList[int(current_hour)]['count'] += 1

            #by day of the week
            epoch = int(i['date_unixtime'])
            day = time.strftime('%A', time.localtime(epoch))
            dayWeekList[find(dayWeekList, 'day', day)]['count'] += 1

        if (i['type'] == 'service'):
            if (i['actor_id'] == vars.me):
                calls1 += 1
            elif (i['actor_id'] == vars.him):
                calls2 += 1
            if "duration_seconds" in i:
                timeCall += i['duration_seconds']

with open('stats.txt', "w", encoding="utf-8") as f:
    f.write("messages me: " + str(total1) + "\n")
    f.write("messages him: " + str(total2) + "\n")
    f.write("calls me: " + str(calls1) + "\n")
    f.write("calls him: " + str(calls2) + "\n")
    f.write("time called: " + str(timeCall/60) + "hrs\n")
    f.write(str(sorted(emojisDict1.items(), key=lambda x: x[1], reverse=True)[0:10]) + "\n")
    f.write(str(sorted(emojisDict2.items(), key=lambda x: x[1], reverse=True)[0:10]) + "\n")

dayFields = ['day', 'count']
monthFields = ['month', 'count']
hourFields = ['hour', 'count']

with open('daily.csv', 'w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames = dayFields)
    writer.writeheader()
    writer.writerows(dayWeekList)

with open('monthly.csv', 'w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames = monthFields)
    writer.writeheader()
    writer.writerows(monthsList)

with open('hourly.csv', 'w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames = hourFields)
    writer.writeheader()
    writer.writerows(hoursList)

with open('total.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['nMessages1', 'nMessages2', 'nCalls1', 'nCalls2'])
    writer.writerow([total1, total2, calls1, calls2])

with open('calls.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['calls1', 'calls2'])
    writer.writerow([calls1, calls2])

f.close()