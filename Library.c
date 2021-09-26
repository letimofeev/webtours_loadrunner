Library()
{
	return 0;
}

int splitStringToNumArr(char* str, char* seps, int* nums)
{
	char* token;
	char* strCopy = (char*)strdup(str);
    int i = 0;
    
    token = (char*)strtok(strCopy, seps);
   
    while(token != NULL)
    {	
        nums[i] = atoi(token);
        token = (char*)strtok(NULL, seps);
        ++i;
    }
    
    return i;
}

int getParamCount(char* paramName)
{
	char paramCountStr[64];
	char paramNameWithCount[64];
	
	sprintf(paramNameWithCount, "{%s_count}", paramName);
	sprintf(paramCountStr, "%s", lr_eval_string(paramNameWithCount));
	
	return atoi(paramCountStr);
}

getCancelReservationRequestBody(char* flightIdParamName, char* cgiFieldParamName, char* numsToDeleteStr, char* argName)
{
	char requestBody[4096] = "";
	char sep[] = ",";
	char flightIdParamNameWithNumber[64];
	char flightId[64];
	char cgiFieldParamNameWithNumber[64];
	char cgiField[64];
	char numToDeleteStr[64];
	int numsToDeleteIntArr[128];
	int numsToDeleteSize;
	int added;
	int elemCount;
	int i;
	int j;
	
	elemCount = getParamCount(flightIdParamName);
	numsToDeleteSize = splitStringToNumArr(numsToDeleteStr, sep, numsToDeleteIntArr);
	
	for (i=1;i<=elemCount;++i)
	{
		added = 0;
		
		for(j=0;j<numsToDeleteSize;++j)
		{	
			sprintf(flightIdParamNameWithNumber, "{%s_%d}", flightIdParamName, i);
	    	sprintf(flightId, "%s", lr_eval_string(flightIdParamNameWithNumber));
	    	
			if (i==numsToDeleteIntArr[j])
			{
				sprintf(numToDeleteStr, "%d", i);
				strcat(requestBody, numToDeleteStr);
				strcat(requestBody, "=on&flightID=");
				strcat(requestBody, flightId);
				added = 1;
			}
		}
		
		if (!added)
		{
			strcat(requestBody, "flightID=");
		    strcat(requestBody, flightId);
		}
			
		strcat(requestBody, "&");
	}
	
	strcat(requestBody, "removeFlights.x=53&removeFlights.y=11"); 
	
	for (i=1;i<=elemCount;++i)
	{
		strcat(requestBody, "&");
		sprintf(cgiFieldParamNameWithNumber, "{%s_%d}", cgiFieldParamName, i);
    	sprintf(cgiField, "%s", lr_eval_string(cgiFieldParamNameWithNumber));
    	
		strcat(requestBody, ".cgifields=");
	    strcat(requestBody, cgiField);		
	}
	
	lr_save_string(requestBody, argName);
	
	return 0;
}

getCancelLastReservationRequestBody(char* flightIdParamName, char* cgiFlightParamName, char* requestBodyParamName) 
{	
	char numLast[64];
	
	sprintf(numLast, "%d", getParamCount(flightIdParamName));	
	getCancelReservationRequestBody(flightIdParamName, cgiFlightParamName, numLast, requestBodyParamName);
	
	return 0;
}

getCancelReservationVerificationText(char* flightIdParamName, char* numsToDeleteStr, char* requestBodyParamName)
{
	char elemCountStr[64];
	char verificationText[64] = "";
	char sep[] = ",";
	int numsToDeleteIntArr[128];
	int numsToDeleteSize;
	int elemCount;
	
	elemCount = getParamCount(flightIdParamName);
	numsToDeleteSize = splitStringToNumArr(numsToDeleteStr, sep, numsToDeleteIntArr);
	
	sprintf(elemCountStr, "%d", elemCount-numsToDeleteSize);
	
	if (!strcmp(elemCountStr, "0"))
	{
		sprintf(verificationText, "No flights have been reserved.");
	}
	else
	{
		strcat(verificationText, "<b>A total of ");
		strcat(verificationText, elemCountStr);
	}
	
	lr_save_string(verificationText, requestBodyParamName);
	
	return 0;
}

getCancelLastReservationVerificationText(char* flightIdParamName, char* requestBodyParamName)
{
	char numLast[64];
	
	sprintf(numLast, "%d", getParamCount(flightIdParamName));	
	getCancelReservationVerificationText(flightIdParamName, numLast, requestBodyParamName);
	
	return 0;
}

getCitiesPair(char* citiesParamName, char* departCityParamName, char* arriveCityParamName) 
{
	char departCityParam[32];
	char arriveCityParam[32];
	
	for (;;)
	{
		lr_save_string(lr_paramarr_random(citiesParamName), departCityParamName);
		lr_save_string(lr_paramarr_random(citiesParamName), arriveCityParamName);
		
		sprintf(departCityParam, "{%s}", departCityParamName);
		sprintf(arriveCityParam, "{%s}", arriveCityParamName);
		
		if (strcmp(lr_eval_string(departCityParam), lr_eval_string(arriveCityParam)))
		{
			break;
		}
	}
	
	return 0;
}

getRandomNumsToDeleteString(char* flightIdParamName, char* randomNumsParamName) 
{
	char numsToDeleteStr[256];
	char randomIntStr[8];
	char* tmp;
	int numsToDeleteIntArr[128];
	int numsToDeleteSize;
	int j;
	int r;
	int i = 0;
	int elemCount;
	int unique;
	
	srand(time(NULL));
	
	elemCount = getParamCount(flightIdParamName);
	numsToDeleteSize = rand()%elemCount + 1;

	while (i<numsToDeleteSize)
	{
		unique = 1;
		r = rand()%elemCount + 1;
		
		for (j=0;j<numsToDeleteSize;++j)
		{
			if (r==numsToDeleteIntArr[j])
			{
				unique = 0;
			}
		}
		
		if (unique)
		{
			tmp = (i==numsToDeleteSize-1) ? "%d" : "%d,";
			sprintf(randomIntStr, tmp, r);		
			strcat(numsToDeleteStr, randomIntStr);
			numsToDeleteIntArr[i] = r;
			++i;
		}
	}
	
	lr_save_string(numsToDeleteStr, randomNumsParamName);
	
	return 0;
}