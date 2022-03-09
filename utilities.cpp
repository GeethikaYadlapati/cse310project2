int getNumberOfWorkers(SOC soc, string literal);
SOC* makeSOCobjects(int argc, char* argv[], int* size);
earnings* makeEarningsObjs(int* size);

int getNumberOfWorkers(SOC soc, string literal)
{
	if ( literal.compare("female") == 0 )
	{
        //cout << soc.female << "\n";
		return soc.female;
	}
	if ( literal.compare("male") == 0 )
	{
		return soc.male;
	}
	if ( literal.compare("total") == 0)
	{
		return soc.total;
	}
    return -1;
}

SOC* makeSOCobjects(int argc, char* argv[], int* size){
//data extraction
    int year = stoi(argv[1]);
    ifstream inputFile;
    string fileName = std::string("Occupation-Dist-All-");
    fileName = fileName + std::to_string(year) + ".csv";
    inputFile.open(fileName);
    string line;
    int count = 0;

    while(getline(inputFile, line)){
        count++;
    }
    //cout << "count=" << count << "\n";
    count = count - 5;
    *size = count;
    SOC *socObjects = (SOC*) malloc(sizeof(SOC)*count);


    //inputFile.seekg(0);
    inputFile.close();
    inputFile.open(fileName);


    int times = 0;
    while(times < 5 && getline(inputFile,line)){
    	//cout << line << "line1 \n";
        times++;
    }
    //getline(inputFile,line);
    //cout << "************************* - line1 \n";
    int index = 0;
    while(getline(inputFile, line)){

        char *line2 = &line[0];
        //cout << line2 << "line2 \n";
        int i = 0;
        int countComma = 0;
        string occupationString;
        string SOCcode;

        int countQuotes = 0;
        string workers;
        string females;
        string males;
        bool isQuoteEnded = false;
        bool isQuoteStarted = false;
    while(line2[i]!= '\0' && line2[i] != '\n'){
        //if(!isQuoteEnded){
         isQuoteEnded =  ( ( line2[i] == '"' ) && isQuoteStarted && !isQuoteEnded );
       // }

         if(!isQuoteStarted){
        isQuoteStarted =  ( ( line2[i] == '"' ) && !isQuoteStarted && !isQuoteEnded );
         }
         if(isQuoteEnded){
            isQuoteStarted = false;
        }
         if(isQuoteStarted){
            isQuoteEnded = false;
         }
        //cout << "started" << isQuoteStarted <<"\n";

        if(countComma == 0 && (isQuoteStarted || line2[i] != ',') && line2[i] != '"'){
            occupationString = occupationString + line2[i];
        }else if(countComma == 1 && line2[i] != ',' ){
            SOCcode = SOCcode + line2[i];
        }
        if(!isQuoteStarted && line2[i] == ','){
            countComma++;
        }
        if(countQuotes == 1 && line2[i] != '"' && line2[i] != ','){
            workers = workers + line2[i];
        }else if(countQuotes == 3 && line2[i] != '"' && line2[i] != ','){
            females = females + line2[i];
        }else if(countQuotes == 5 && line2[i] != '"' && line2[i] != ','){
            males = males + line2[i];
        }
        if(countComma >= 2 && line2[i] == '"'){
            countQuotes++;
            //cout << countQuotes << "count quotes\n";
        }
        if(line2[i] == ',' && countComma == 1){
            //socObjects[index].occupation = occupationString;
             strcpy(socObjects[index].occupation, occupationString.c_str());
        }else if(line2[i] == ',' && countComma == 2){
            //socObjects[index].SOC_code = SOCcode;
            strcpy(socObjects[index].SOC_code, SOCcode.c_str());
        }else if(line2[i] == '"' && countQuotes == 2){
            //cout << "workers" << workers << "\n";
            socObjects[index].total = std::stoi(workers);
        }else if(line2[i] == '"' && countQuotes == 4){
            //cout << "female" << females << "\n";
            socObjects[index].female = std::stoi(females);
            //cout << socObjects[index].female << "\n";
        }else if(line2[i] == '"' && countQuotes == 6){
            //cout << "male" << males << "\n";
            socObjects[index].male = std::stoi(males);
        }

        i++;
    }
    index++;
    line = "";
    }
    inputFile.close();
    return socObjects;
}

earnings* makeEarningsObjs(int* size){
    ifstream input;
    input.open("Earnings-1960-2019.csv");
    string linestring;
    int counter = 0;
    while(getline(input, linestring)){
        counter++;
    }

    counter = counter - 8;
    *size = counter;
    //cout << counter;
    earnings *earningsObj = (earnings*) malloc(sizeof(earnings)*counter);
    input.close();
    input.open("Earnings-1960-2019.csv");


    int times = 0;
    while(times < 8 && getline(input,linestring) ){
        times++;
    }
    //getline(input,linestring);
    int numOfObj = 0;

    while(getline(input, linestring)){
        string YEAR;
        char *linestring2 = &linestring[0];
        //cout << linestring2 << "linestring2\n";
        int j = 0;
        int comma = 0;
        int quotes = 0;
        string feEarnMOE;
        string maEarnMOE;
        string maTotal;
        string numMaleEarn;
        string maleEarnings;
        string feTotal;
        string numFemaleEarn;
        string femaleEarnings;
        bool isQuoteEnded = false;
        bool isQuoteStarted = false;

       while(linestring2[j]!= '\0' && linestring2[j] != '\n'){

           //if(!isQuoteEnded){
            isQuoteEnded =  ( ( linestring2[j] == '"' ) && isQuoteStarted && !isQuoteEnded );
          // }

            if(!isQuoteStarted){
           isQuoteStarted =  ( ( linestring2[j] == '"' ) && !isQuoteStarted && !isQuoteEnded );
            }
            if(isQuoteEnded){
               isQuoteStarted = false;
           }
            if(isQuoteStarted){
               isQuoteEnded = false;
            }

        if(linestring2[j] != ',' && comma == 0){
            YEAR = YEAR + linestring2[j];
        }
        if(!isQuoteStarted && linestring2[j] == ','){
            comma++;
        }

        if(comma == 4 && linestring2[j] != ',' && linestring2[j] != '"'){
            maEarnMOE = maEarnMOE + linestring2[j];
        }else if(comma == 1 && linestring2[j] != '"' && linestring2[j] != ','){
            maTotal = maTotal + linestring2[j];
        }else if(comma == 2 && linestring2[j] != '"' && linestring2[j] != ','){
            numMaleEarn = numMaleEarn + linestring2[j];
        }else if(comma == 3 && linestring2[j] != '"' && linestring2[j] != ','){
            maleEarnings = maleEarnings + linestring2[j];
        }else if(comma == 5 && linestring2[j] != '"' && linestring2[j] != ','){
            feTotal = feTotal + linestring2[j];
        }else if(comma == 6 && linestring2[j] != '"' && linestring2[j] != ','){
            numFemaleEarn = numFemaleEarn +linestring2[j];
        }else if(comma == 7 && linestring2[j] != '"' && linestring2[j] != ','){
            femaleEarnings = femaleEarnings + linestring2[j];
        }else if(comma == 8 && linestring2[j] != ',' && linestring2[j] != '"'){
            feEarnMOE = feEarnMOE + linestring2[j];
        }
        if(comma >= 1 && linestring2[j] == '"'){
            quotes++;
        }
        //cout << "maleEarnings=" << "linestring2[j]=" << linestring2[j] << "-" << comma << "-" << maleEarnings << "\n";
         if(linestring2[j] == ',' && comma == 1){
            earningsObj[numOfObj].year = std::stoi(YEAR);
        }else if(linestring2[j] == ',' && comma == 2 && maTotal.find("N") == -1){
            earningsObj[numOfObj].male_total = std::stoi(maTotal);
        }else if(linestring2[j] == ',' && comma == 3 && numMaleEarn.find("N") == -1 ){
            earningsObj[numOfObj].male_with_earnings = std::stoi(numMaleEarn);
        }else if(linestring2[j] == ',' && comma == 4 && maleEarnings.find("N") == -1 ){
            earningsObj[numOfObj].male_earnings = std::stoi(maleEarnings);
        }else if(linestring2[j] == ',' && comma == 6 && feTotal.find("N") == -1 ){
            earningsObj[numOfObj].female_total = std::stoi(feTotal);
        }else if(linestring2[j] == ',' && comma == 7 && numFemaleEarn.find("N") == -1){
            earningsObj[numOfObj].female_with_earnings = std::stoi(numFemaleEarn);
        }else if(linestring2[j] == ',' && comma == 8 && femaleEarnings.find("N") == -1){
            earningsObj[numOfObj].female_earnings = std::stoi(femaleEarnings);
        }else if(linestring2[j] == ',' && comma == 5 && maEarnMOE.find("N") == -1){
            earningsObj[numOfObj].male_earnings_moe = std::stoi(maEarnMOE);
        }
        j++;
       }
       if ( feEarnMOE.find("N") == -1 )
       {
    	   earningsObj[numOfObj].female_earnings_moe = std::stoi(feEarnMOE);
       }
       numOfObj++;
        linestring = "";
    }
    input.close();
    return earningsObj;
}
    //editings left to do in the above code
    //check if .seekg works orelse open and close the file again
    //inquire about the updated changes especially the commma append

    //end of data extraction

    //start of queries