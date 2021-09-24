Library()
{
	return 0;
}

int splitStringToNumArr(char* str, char* seps, int** nums)
{
	char* token;
	char* strCopy = (char*)strdup(str);
	int* res = NULL;
    int i = 0;
    
    token = (char*)strtok(strCopy, seps);
   
    while(token != NULL)
    {
    	res = (int*)realloc(res, sizeof(int) * ++i);
        res[i - 1] = atoi(token);
        token = (char*)strtok(NULL, seps);
    }
    
    *nums = res;
    
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
	int* numsToDeleteIntArr;
	int numsToDeleteSize;
	int added;
	int elemCount;
	int i;
	int j;
	
	elemCount = getParamCount(flightIdParamName);
	numsToDeleteSize = splitStringToNumArr(numsToDeleteStr, sep, &numsToDeleteIntArr);
	
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

	free(numsToDeleteIntArr);
	
	return 0;
}

getCancelLastReservationRequestBody(char* flightIdParamName, char* cgiFlightParamName, char* argName) 
{	
	char numLast[64];
	
	sprintf(numLast, "%d", getParamCount(flightIdParamName));	
	getCancelReservationRequestBody(flightIdParamName, cgiFlightParamName, numLast, argName);
	
	return 0;
}

getCancelReservationVerificationText(char* flightIdParamName, int deletedNum, char* argName)
{
	char verificationText[64] = "";
	char elemCountStr[64];
	
	sprintf(elemCountStr, "%d", getParamCount(flightIdParamName)-deletedNum);
	
	if (elemCountStr == "0") 
	{
		sprintf(verificationText, "No flights have been reserved.");
	}
	else
	{
		strcat(verificationText, "<b>A total of ");
		strcat(verificationText, elemCountStr);
	}
	
	lr_save_string(verificationText, argName);
	
	return 0;
}

getCitiesPair(char* citiesParamName, char* departCityParamName, char* arriveCityParamName) 
{
	char departCityParam[32];
	char arriveCityParam[32];
	
	for(;;)
	{
		lr_save_string(lr_paramarr_random(citiesParamName), departCityParamName);
		lr_save_string(lr_paramarr_random(citiesParamName), arriveCityParamName);
		
		sprintf(departCityParam, "{%s}", departCityParamName);
		sprintf(arriveCityParam, "{%s}", arriveCityParamName);
		
		if (departCityParam != arriveCityParam)
		{
			break;
		}
	}
	
	return 0;
}