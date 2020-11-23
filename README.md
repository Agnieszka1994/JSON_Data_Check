https://github.com/nlohmann/json

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