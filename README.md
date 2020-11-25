
This project was created thanks to the [JSON for Modern C++](https://github.com/nlohmann/json) library.

# About 
This repo is a remake of a Hyperskill project **Easy Riders Bus Company** written in `C++`.
This program takes in a JSON-like file which is a representation of a bus company database. The file contains an array of JSON objects representing timetable units. The data contains different kinds of errors, including wrong type, wrong format and logical errors in the schemes of bus lines. The program finds all the mistakes in the database and print the output.

The checks are completed following the below criteria:

**1. Data structure**

|**Filed name**|**Description**   |**Type** |**Format**     |**Other**| 
|:------------ |:-----------------|:--------|:--------------|:-------|
|`bus_id`      |name of the buss line|Integer|              |Required|
|`stop_id`     |Id of stop        |Integer  |              |Required| 
|`stop_name`   |Name of the<br>current stop|String   |**[proper name][suffix]**<br>Suffix: Road/Avenue/Boulevard/Street<br>Proper name starts with a capital letter.|Required|
|`next_stop`   |Id of the next stop|Integer  |              |Required|
|`stop_type`   |Stop type          |Character| S (for starting stop)<br>F(for final stop)<br>O(for stop on demand) ||
|`a_time`      |Arrive time       |String   |HH:MM (24 hour format)|Required |

**2. Special stops**

|**Stop type**|**Description**   |
|:----------- |:-----------------|
|`Start`      |The stop where the line starts.|
|`Transfer`   |A stop where the traveler can change<br>to another line.|
|`Finish`     |The stop where the line ends.|

**3. General rules**
- Stops on a given line have increasing arrival times.
- Transfer, start, and end stops cannot be on demand.

**The diagram of the bus lines is presented below**

[![img](https://github.com/Agnieszka1994/JSON_Data_Check/blob/main/img/diagram.png)](https://github.com/Agnieszka1994/JSON_Data_Check/blob/main/img/)

## Sample usage

**If at least one of the checks fails, the program stops executing the further checks**
**Error in stop_name - stop nr 3:**
```
Please enter file name:
failtest.json
Data types check... Please wait...
Data Types Correct
The following errors were found:
Obj 3 : stop_name
Incorrect Synatx!
Stop_name, Stop_type or Time format did not meet the requirements!
```
**Error in arrival time - line 256: the time at the stop Sesame Street is earlier than at the previous stop**
```
Please enter file name:
failtest2.json
Data types check... Please wait...
Data Types Correct
Syntax correct!
Line names and number of stops:
bus_id: 128, stops: 4
bus_id: 256, stops: 4
bus_id: 512, stops: 2
Start stops: 3 ['Prospekt Avenue', 'Pilotow Street', 'Bourbon Street']
Transfer stops: 3 ['Elm Street', 'Sesame Street', 'Sunset Boulevard']
Finish stops: 3 ['Sesame Street', 'Elm Street', 'Sunset Boulevard']
Arrival time test:
bus_id line 256: wrong time on station Sesame Street
```


**When All checks are passed - the further options are available**
```
Please enter file name:
test.json
Data types check... Please wait...
Data Types Correct
Syntax correct!
Line names and number of stops:
bus_id: 128, stops: 4
bus_id: 256, stops: 4
bus_id: 512, stops: 2
Start stops: 3 ['Prospekt Avenue', 'Pilotow Street', 'Bourbon Street']
Transfer stops: 3 ['Elm Street', 'Sesame Street', 'Sunset Boulevard']
Finish stops: 3 ['Sesame Street', 'Elm Street', 'Sunset Boulevard']
Arrival time test:
Arrival times OK
On demand stops test: OK

All check passed!!!
```
**Display all timetables**
```
What would you like to display?
1. All timetables
2. Lines info
3. All Special Stops
4. Transfer Stops
5. Finish Stops
6. Start Stops
0. Exit
1
    bus_id: 128
stop_id:    1
stop_name:  Prospekt Avenue
next_stop:  3
stop_type:  S
a_time:     08:23


bus_id:     128
stop_id:    3
stop_name:  Elm Street
next_stop:  5
stop_type:
a_time:     08:27


bus_id:     256
stop_id:    3
stop_name:  Elm Street
next_stop:  6
stop_type:  F
a_time:     08:23


bus_id:     128
stop_id:    5
stop_name:  Fifth Avenue
next_stop:  7
stop_type:
a_time:     08:35


bus_id:     128
stop_id:    7
stop_name:  Sesame Street
next_stop:  0
stop_type:  F
a_time:     08:50


bus_id:     256
stop_id:    7
stop_name:  Sesame Street
next_stop:  0
stop_type:
a_time:     09:12


bus_id:     256
stop_id:    2
stop_name:  Pilotow Street
next_stop:  3
stop_type:  S
a_time:     08:15


bus_id:     256
stop_id:    6
stop_name:  Sunset Boulevard
next_stop:  7
stop_type:
a_time:     08:45


bus_id:     512
stop_id:    6
stop_name:  Sunset Boulevard
next_stop:  0
stop_type:  F
a_time:     08:16


bus_id:     512
stop_id:    4
stop_name:  Bourbon Street
next_stop:  6
stop_type:  S
a_time:     08:13

```
**Display lines info**
```
Line names and number of stops:
bus_id: 128, stops: 4
bus_id: 256, stops: 4
bus_id: 512, stops: 2
```
***Display all special stops**
```
Start stops: 3 ['Prospekt Avenue', 'Pilotow Street', 'Bourbon Street']
Transfer stops: 3 ['Elm Street', 'Sesame Street', 'Sunset Boulevard']
Finish stops: 3 ['Sesame Street', 'Elm Street', 'Sunset Boulevard']
```