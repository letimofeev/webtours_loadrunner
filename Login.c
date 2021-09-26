Login()
{
	lr_message(lr_eval_string("{CURRENT_TIME}: [INFO]: Iteration {ITER_NUM} started"));
	
	
	// ----------------------------------------Open start page----------------------------------------
	
	lr_start_transaction("00_OpenStartPage");
	
	lr_save_string("00_OpenStartPage", "CUR_TRANSACTION_NAME");
	
	lr_message(lr_eval_string("{CURRENT_TIME}: [INFO]: Transaction {CUR_TRANSACTION_NAME} started"));
	lr_message(lr_eval_string("  {CURRENT_TIME}: [INFO]: Loading start page..."));

	web_url("WebTours", 
		"URL=http://{HOST}:{PORT}/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("header.html", 
		"URL=http://{HOST}:{PORT}/WebTours/header.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/WebTours/", 
		"Snapshot=t2.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("welcome.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/WebTours/", 
		"Snapshot=t5.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);

	web_url("hp_logo.png", 
		"URL=http://{HOST}:{PORT}/WebTours/images/hp_logo.png", 
		"Resource=1", 
		"RecContentType=image/png", 
		"Referer=http://{HOST}:{PORT}/WebTours/header.html", 
		"Snapshot=t3.inf", 
		LAST);

	web_url("webtours.png", 
		"URL=http://{HOST}:{PORT}/WebTours/images/webtours.png", 
		"Resource=1", 
		"RecContentType=image/png", 
		"Referer=http://{HOST}:{PORT}/WebTours/header.html", 
		"Snapshot=t4.inf", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=Welcome to the Web Tours site.",
		LAST);

	web_url("home.html", 
		"URL=http://{HOST}:{PORT}/WebTours/home.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t6.inf", 
		"Mode=HTTP", 
		LAST);
	
	web_reg_save_param_ex("ParamName=USER_SESSION", 
	    "LB/IC=name=\"userSession\" value=\"",
	    "RB/IC=\"",
	    "Ordinal=1",
	    SEARCH_FILTERS,
	    "Scope=body",
		LAST);

	web_url("nav.pl", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=true", 
		"Snapshot=t7.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_url("mer_login.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/mer_login.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Snapshot=t8.inf", 
		LAST);
	
	lr_message(lr_eval_string("  {CURRENT_TIME}: [INFO]: Start page loaded"));

	lr_end_transaction("00_OpenStartPage",LR_AUTO);
	
	lr_message(lr_eval_string("{CURRENT_TIME}: [INFO]: Transaction {CUR_TRANSACTION_NAME} ended"));
	
	
	// ----------------------------------------Login----------------------------------------
	
	lr_think_time(10);  // login and password entry time
	
	lr_start_transaction("01_Login");
	
	lr_save_string("01_Login", "CUR_TRANSACTION_NAME");
	
	lr_message(lr_eval_string("{CURRENT_TIME}: [INFO]: Transaction {CUR_TRANSACTION_NAME} started"));
	
	web_reg_find("Fail=NotFound",
		"Search=Body",
		"Text=User password was correct",
		LAST);
	
	lr_message(lr_eval_string("  {CURRENT_TIME}: [INFO]: Login start"));

	web_submit_data("login.pl", 
		"Action=http://{HOST}:{PORT}/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Snapshot=t9.inf", 
		"Mode=HTTP", 
		ITEMDATA, 
		"Name=userSession", "Value={USER_SESSION}", ENDITEM,  // 132210.915431349ziAAfQipQzcftAiADpfQDHHf
		"Name=username", "Value={USERNAME}", ENDITEM, 
		"Name=password", "Value={PASSWORD}", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=login.x", "Value=44", ENDITEM, 
		"Name=login.y", "Value=4", ENDITEM, 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_2", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/login.pl", 
		"Snapshot=t10.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("login.pl_2", 
		"URL=http://{HOST}:{PORT}/cgi-bin/login.pl?intro=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/login.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	web_concurrent_start(NULL);

	web_url("in_home.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/in_home.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t11.inf", 
		LAST);

	web_url("flights.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/flights.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t12.inf", 
		LAST);

	web_url("signoff.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/signoff.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t13.inf", 
		LAST);

	web_url("itinerary.gif", 
		"URL=http://{HOST}:{PORT}/WebTours/images/itinerary.gif", 
		"Resource=1", 
		"RecContentType=image/gif", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t15.inf", 
		LAST);

	web_concurrent_end(NULL);
	
	lr_message(lr_eval_string("  {CURRENT_TIME}: [INFO]: User logged in with the following data:")); 
	lr_message(lr_eval_string("    USER SESSION = {USER_SESSION}")); 
	lr_message(lr_eval_string("    USERNAME     = {USERNAME}"));	
	lr_message(lr_eval_string("    PASSWORD     = {PASSWORD}"));

	lr_end_transaction("01_Login",LR_AUTO);
	
	lr_message(lr_eval_string("{CURRENT_TIME}: [INFO]: Transaction {CUR_TRANSACTION_NAME} ended"));
	
	
	return 0;
}
