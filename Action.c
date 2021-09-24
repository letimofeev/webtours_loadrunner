Action()
{
	// ----------------------------------------Open flights page----------------------------------------
	
	lr_think_time(5);  // time before pressing the button "flights"

	lr_start_transaction("02_OpenFlightsSearchPage");

	web_url("Search Flights Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=search", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t16.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_3", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t17.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("reservations.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/reservations.pl?page=welcome", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=search", 
		"Snapshot=t20.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);

	web_url("in_flights.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/in_flights.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t18.inf", 
		LAST);

	web_url("home.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/home.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t19.inf", 
		LAST);

	web_concurrent_end(NULL);

	web_url("button_next.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/button_next.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t21.inf", 
		LAST);

	lr_end_transaction("02_OpenFlightsSearchPage",LR_AUTO);
	

	
	// ----------------------------------------Search flight----------------------------------------
	
	lr_think_time(15);  // time of filling out the ticket search form
	
	lr_start_transaction("03_SearchFlight");
	
	web_reg_save_param_ex("ParamName=OUTBOUND_FLIGHT", 
	    "LB=name=\"outboundFlight\" value=\"",
	    "RB=\"",
	    "Ordinal=1",
	    SEARCH_FILTERS,
	    "Scope=body",
		LAST);
	
	web_reg_save_param_ex("ParamName=RETURN_FLIGHT", 
	    "LB=name=\"returnFlight\" value=\"",
	    "RB=\"",
	    "Ordinal=1",
	    SEARCH_FILTERS,
	    "Scope=body",
		LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t22.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value=Denver", ENDITEM, 
		"Name=departDate", "Value={DEPART_DATE}", ENDITEM,  // 09/21/2021
		"Name=arrive", "Value=Denver", ENDITEM, 
		"Name=returnDate", "Value={RETURN_DATE}", ENDITEM,  // 09/22/2021
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=roundtrip", "Value=on", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=seatType", "Value={SEAT_TYPE}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=57", ENDITEM, 
		"Name=findFlights.y", "Value=14", ENDITEM, 
		LAST);

	lr_end_transaction("03_SearchFlight",LR_AUTO);
	
	
	// ----------------------------------------Select flight----------------------------------------
	
	lr_think_time(10);  // ticket selection time

	lr_start_transaction("04_SelectFlight");

	web_submit_data("reservations.pl_3", 
		"Action=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Snapshot=t23.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={OUTBOUND_FLIGHT}", ENDITEM,  // 000;0;09/21/2021 
		"Name=returnFlight", "Value={RETURN_FLIGHT}", ENDITEM,  // 003;0;09/22/2021
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={SEAT_TYPE}", ENDITEM, 
		"Name=seatPref", "Value=None", ENDITEM, 
		"Name=reserveFlights.x", "Value=25", ENDITEM, 
		"Name=reserveFlights.y", "Value=6", ENDITEM, 
		LAST);

	lr_end_transaction("04_SelectFlight",LR_AUTO);

	
	// ----------------------------------------Payment details----------------------------------------
	
	lr_think_time(15);  // time of filling in payment details
	
	lr_start_transaction("05_FillPaymentDetails");

	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=<!-- Flight reserved -->",
		LAST);

	web_submit_data("reservations.pl_4", 
		"Action=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Snapshot=t24.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=firstName", "Value={FIRST_NAME}", ENDITEM, 
		"Name=lastName", "Value={LAST_NAME}", ENDITEM, 
		"Name=address1", "Value={ADDRESS1}", ENDITEM, 
		"Name=address2", "Value={ADDRESS2}", ENDITEM, 
		"Name=pass1", "Value={FULLNAME}", ENDITEM, 
		"Name=creditCard", "Value={CREDIT_CARD}", ENDITEM, 
		"Name=expDate", "Value={EXPDATE}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={SEAT_TYPE}", ENDITEM, 
		"Name=seatPref", "Value={SEAT_PREF}", ENDITEM, 
		"Name=outboundFlight", "Value={OUTBOUND_FLIGHT}", ENDITEM,  // 000;0;09/21/2021 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value={RETURN_FLIGHT}", ENDITEM,  // 003;0;09/22/2021
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=42", ENDITEM, 
		"Name=buyFlights.y", "Value=12", ENDITEM, 
		LAST);

	web_url("bookanother.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/bookanother.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/reservations.pl", 
		"Snapshot=t25.inf", 
		LAST);

	lr_end_transaction("05_FillPaymentDetails",LR_AUTO);

	
	// ----------------------------------------Return start page----------------------------------------
	
	lr_think_time(5);  // time before pressing the button "home"
	
	lr_start_transaction("06_ReturnStartPage");

	web_url("Home Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=menus", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t26.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_4", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=menus", 
		"Snapshot=t27.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("login.pl_3", 
		"URL=http://{HOST}:{PORT}/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=menus", 
		"Snapshot=t28.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("06_ReturnStartPage",LR_AUTO);

	
	// ----------------------------------------Open reservation list----------------------------------------
	
	lr_think_time(5);  // time before pressing the button "itinerary"
	
	lr_start_transaction("07_OpenReservationList");

	web_url("Itinerary Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=itinerary", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t29.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_5", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t30.inf", 
		"Mode=HTTP", 
		LAST);
	
	web_reg_save_param_ex("ParamName=FLIGHT_ID", 
	    "LB=name=\"flightID\" value=\"",
	    "RB=\"",
	    "Ordinal=all",
	    SEARCH_FILTERS,
	    "Scope=body",
		LAST);

	web_url("itinerary.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/itinerary.pl", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?page=itinerary", 
		"Snapshot=t32.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_url("in_itinerary.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/in_itinerary.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t31.inf", 
		LAST);

	web_concurrent_start(NULL);

	web_url("cancelallreservations.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/cancelallreservations.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/itinerary.pl", 
		"Snapshot=t33.inf", 
		LAST);

	web_url("cancelreservation.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/cancelreservation.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/itinerary.pl", 
		"Snapshot=t34.inf", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("07_OpenReservationList",LR_AUTO);


	// ----------------------------------------Cancel reservation----------------------------------------
	
	lr_think_time(5);  // time of cancellation of the selected flight
	
	lr_start_transaction("08_CancelReservation");
	
	// getCancelReservationRequestBody("FLIGHT_ID", "2,4", "CANCEL_RESERVATION_REQUEST_BODY");
	
	getCancelLastReservationRequestBody("FLIGHT_ID", "CANCEL_RESERVATION_REQUEST_BODY");
	
	getCancelReservationVerificationText("FLIGHT_ID", 1, "CANCEL_RESERVATION_VERIFICATION_TEXT");
	
	lr_output_message("Verification text: %s", lr_eval_string("{CANCEL_RESERVATION_VERIFICATION_TEXT}"));

	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text={CANCEL_RESERVATION_VERIFICATION_TEXT}",
		LAST);
	
	web_custom_request("itinerary.pl_2",
	    "URL=http://{HOST}:{PORT}/cgi-bin/itinerary.pl",
	    "Method=POST", 
	    "RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/itinerary.pl",  
		"Mode=HTTP", 
		"Body={CANCEL_RESERVATION_REQUEST_BODY}",
		LAST);

	lr_end_transaction("08_CancelReservation",LR_AUTO);


	return 0;
}