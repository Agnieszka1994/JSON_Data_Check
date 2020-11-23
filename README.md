https://github.com/nlohmann/json

# About 
This repo is a remake of a Hyperskill project **Easy Riders Bus Company** written in `C++`.
This program takes in a JSON-like file which is a representation of a bus company database. The file contains an array of JSON objects representing timetable units. The data contains different kinds of errors, including wrong type, wrong format and logical errors in the schemes of bus lines. The program finds all the mistakes in the database and print the output.

The checks are completed following the below criteria:

|Filed name    | Description       |Type     |Format          |Other    | 
|:------------ |:-----------------:|:-------:|:--------------:|--------:|
|bus_id        |name of the buss line|Integer|                 |Required|
|stop_id       |centered           |Integer  |                 |Required| 
|stop_name     |are neat           |String   |                 |Required|
|next_stop     |id of the next stop|Integer  |                 |Required|
|stop_type     |stop type          |Character| S (for starting stop)<br\>F(for final stop)<br>O(for stop on demand) ||
|a_time        | arrive_time       |String   |HH:MM (24 hour format)|Required |