# telegram data analysis
 visual data analysis for telegram chats
 
 ### Data tracked:
 - total number of messages from each
 - total number of calls from each
 - total time called
 - number of messages based on: hour, day of the week, month
 - top 10 emojis based on sticker usage

## Getting Started
Extract telegram chat history at the desktop app
```
chat > ... > Export Chat History > uncheck everything and format: Machine-readable JSON > Export
```

Install the requirements to run the program with 
```sh
pip install -r requirements.txt
```

Create a file called vars.py with two lines of text:
```py
me='userID'
him='userID'
```
You can get your userID's checking the .json file

## Running the program
Start the program with

```sh
python3 worker.py
```
and insert which year you want to see the data from in the console

Then use
```sh
python3 graphing.py
```
graphs will pop up and a new text file called `stats.txt` with total number of messages, number of calls, time called and top 10 emojis for each
