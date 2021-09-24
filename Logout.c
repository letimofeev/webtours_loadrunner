Logout()
{
	// ----------------------------------------Logout----------------------------------------
	
	lr_think_time(5);  // time before pressing the button "sing off"
	
	lr_start_transaction("09_Logout");

	web_url("SignOff Button", 
		"URL=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=1", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t37.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_start(NULL);

	web_url("nav.pl_6", 
		"URL=http://{HOST}:{PORT}/cgi-bin/nav.pl?in=home", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t38.inf", 
		"Mode=HTTP", 
		LAST);

	web_url("home.html_2", 
		"URL=http://{HOST}:{PORT}/WebTours/home.html", 
		"Resource=0", 
		"Referer=http://{HOST}:{PORT}/cgi-bin/welcome.pl?signOff=1", 
		"Snapshot=t39.inf", 
		"Mode=HTTP", 
		LAST);

	web_concurrent_end(NULL);

	lr_end_transaction("09_Logout",LR_AUTO);
	
	return 0;
}
