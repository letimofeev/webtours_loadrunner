Library()
{
	return 0;
}


/**
 * 
 * Splitting a string of numbers by separators and storing them in an array
 *
 * @param str String to be split
 * @param seps Separator string by which to split str
 * @param nums The array in which numbers are written
 *
 * @return The number of elements by which the line was split
 */
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


/**
 * 
 * Create a request body to cancel a set of reservations
 *
 * @param flightIdParamName Name of the parameter in which the flight IDs were saved.
 *     Parameter name must be without {} 
 * @param cgiFieldParamName Name of the parameter in which the cgi fields were saved.
 *     Parameter name must be without {} 
 * @param numsToDeleteStr String with reservation numbers, separated by comma, to be canceled
 *     For examle, numsToDeleteStr="1,3" reservations with numbers 1 and 3 will be canceled
 * @param requestBodyParamName  Name of the parameter to which the request body will be saved
 *
 * @return Function exit status
 */
getCancelReservationRequestBody(char* flightIdParamName, char* cgiFieldParamName, char* numsToDeleteStr, char* requestBodyParamName)
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
	
	elemCount = lr_paramarr_len(flightIdParamName);
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
	
	lr_save_string(requestBody, requestBodyParamName);
	
	return 0;
}


/**
 * 
 * Create a request body to cancel the last reservation
 *
 * @param flightIdParamName Name of the parameter in which the flight IDs were saved.
 *     Parameter name must be without {} 
 * @param cgiFieldParamName Name of the parameter in which the cgi fields were saved.
 *     Parameter name must be without {} 
 * @param requestBodyParamName  Name of the parameter to which the request body will be saved
 *
 * @return Function exit status
 */
getCancelLastReservationRequestBody(char* flightIdParamName, char* cgiFlightParamName, char* requestBodyParamName) 
{	
	char numLast[64];
	
	sprintf(numLast, "%d", lr_paramarr_len(flightIdParamName));	
	getCancelReservationRequestBody(flightIdParamName, cgiFlightParamName, numLast, requestBodyParamName);
	
	return 0;
}


/**
 * 
 * Create a verification text for cancelling the set of reservations
 *
 * @param flightIdParamName Name of the parameter in which the flight IDs were saved.
 *     Parameter name must be without {} 
 * @param numsToDeleteStr String with reservation numbers, separated by comma, to be canceled
 * @param VerificationTextParamName  Name of the parameter to which the verification text will be saved
 *
 * @return Function exit status
 */
getCancelReservationVerificationText(char* flightIdParamName, char* numsToDeleteStr, char* VerificationTextParamName)
{
	char elemCountStr[64];
	char verificationText[64] = "";
	char sep[] = ",";
	int numsToDeleteIntArr[128];
	int numsToDeleteSize;
	int elemCount;
	
	elemCount = lr_paramarr_len(flightIdParamName);
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
	
	lr_save_string(verificationText, VerificationTextParamName);
	
	return 0;
}


/**
 * 
 * Create a verification text for cancelling the last reservation
 *
 * @param flightIdParamName Name of the parameter in which the flight IDs were saved.
 *     Parameter name must be without {} 
 * @param VerificationTextParamName  Name of the parameter to which the verification text will be saved
 *
 * @return Function exit status
 */
getCancelLastReservationVerificationText(char* flightIdParamName, char* VerificationTextParamName)
{
	char numLast[64];
	
	sprintf(numLast, "%d", lr_paramarr_len(flightIdParamName));	
	getCancelReservationVerificationText(flightIdParamName, numLast, VerificationTextParamName);
	
	return 0;
}

/**
 * 
 * Getting random cities of departure and arrival
 *
 * @param citiesParamName Name of the parameter in which the city names were saved.
 *     Parameter name must be without {} 
 * @param departCityParamName  Name of the parameter to which the random departure city will be saved
 * @param arriveCityParamName  Name of the parameter to which the random arrival city will be saved
 *
 * @return Function exit status
 */
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


/**
 * 
 * Getting a random set of reservations for cancellation
 *
 * @param flightIdParamName Name of the parameter in which the flight IDs were saved.
 *     Parameter name must be without {} 
 * @param randomNumsParamName  Name of the parameter to which the random set will be saved
 *
 * @return Function exit status
 */
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
	
	elemCount = lr_paramarr_len(flightIdParamName);
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