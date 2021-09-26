vuser_init()
{
	lr_message(lr_eval_string("{CURRENT_TIME}: SCRIPT STARTED"));
	lr_message(lr_eval_string("{CURRENT_TIME}: URL  = {HOST}:{PORT}"));
	
	return 0;
}
