# **JSON PARSER AND APPLICATION**  
### 2019 OSS TEAM PROJECT
  
## What does this project do?
This project consists of two parts : Json Parser and Application.

### Json Parser
This program takes .json file name as an input argument.  
It then implements functions that can parse the text and find tokens.  

### Application : Country-pedia
This Application takes list of country names in a json file.   
It parses the text into tokens and displays the following functions respectively:   

  1 : Display the parsed tokens - prints out the parsed tokens on the screen  
  2 : Search country information by country names - information of the country selected by user is displayed  
  3 : List the country names according to the continent- country names according to the continent selected by user is               displayed.  
  4 : List country names according to GDP ranking - ranking of the countries according to GDP is displayed  
  5 : Test your Knowledge (Quiz)- Capital/Country quiz of 10 questions  


## Why is this project useful?


## How do I get started?

1. Compile the json_parser.c file with gcc or other c compilers

```bash
gcc -c json_parser.c
gcc -o json_parser json_parser.c
```
  
2. Run the program with "./json_parser"
```bash
./json_parser
```

3. See the results



## Where can I get more help, if I need it?

If you need more help, you can contact any one of our team members.

#### Team Members:

1. 21200532 Lee Sungmin  
2. 21800662 Susanna Jung  
3. 21500850 Jaehyung Baek   
4. 21400150 YeEun Kim     

Also, you can find more information about JSON format at [json.org][1]
And Library sources are available at https://github.com/zserge/jsmn

[1]: http://www.json.org/
[2]: http://zserge.com/jsmn.html
