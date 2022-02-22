#include "counts.h"


static int activity_count = 0;
static int tens_count = 0;
char start_check = 'M'; // Enable
char stop_check = 'K';
uint8_t bluetooth_flag = 0;
const char tens_count_charcaters [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

extern "C"
{
	/*********************************************************************************
	 *	@purpose: initialize counts hardware leds and buttons
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t init_counts()
	{

		pinMode(P1, OUTPUT);
		pinMode(P2, OUTPUT);
		pinMode(P3, OUTPUT);
		pinMode(P4, OUTPUT);
		pinMode(P5, OUTPUT);
		pinMode(P6, OUTPUT);
		pinMode(P7, OUTPUT);
		pinMode(P8, OUTPUT);
		pinMode(P9, OUTPUT);
		pinMode(P10, OUTPUT);


		// Initialize input_pullup pins for buttons press
		pinMode(ACT1, INPUT_PULLUP);
		pinMode(ACT2, INPUT_PULLUP);
		pinMode(ACT3, INPUT_PULLUP);
		pinMode(ACT4, INPUT_PULLUP);
		pinMode(ACT5, INPUT_PULLUP);
		pinMode(ACT6, INPUT_PULLUP);
		pinMode(ACT7, INPUT_PULLUP);
		pinMode(ACT8, INPUT_PULLUP);
		pinMode(ACT9, INPUT_PULLUP);
		pinMode(ACT10, INPUT_PULLUP);

		pinMode(PBR, INPUT_PULLUP);
		pinMode(PBS, INPUT_PULLUP);
		pinMode(PBST, INPUT_PULLUP);

		attachInterrupt(digitalPinToInterrupt(PBS), StartISR, FALLING);

		LowPower.begin();

		LowPower.attachInterruptWakeup(PBS, WakeupISR, FALLING, DEEP_SLEEP_MODE);

		Serial.begin(9600);

		return SUCCESS;
	}

	uint8_t turn_off_leds()
	{

		// Turn off all LEDs
		uint32_t leds[] = {P1, P2, P3, P4, P5, P6, P7, P8, P9, P10};

		for(int i = 0; i < 10; i++)
		{
			digitalWrite(leds[i], LOW);
		}

		return SUCCESS;
	}

	/*********************************************************************************
	 *	@purpose: check new round message from App
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_new_round()
	{
		uint8_t state = FAILED;

		if(Serial.available())
		{
		    if (Serial.peek() == 'N')
		    {
		      Serial.read();
		      activity_count = 0;
		      tens_count = 0;
		      state = SUCCESS;

		    }
		}

		return state;
	}

	/*********************************************************************************
	 *	@purpose: check play message from App
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_program()
	{
		uint8_t state = FAILED;

		if(Serial.available())
		{
		    if (Serial.peek() == 'M') // Enable Play button when M is received from App
		    {
		      Serial.read();
		      activity_count = 0;
		      tens_count = 0;
		      start_check = 'M';
		      stop_check = 'K';
		      state = SUCCESS;
		    }
		}

		return state;
	}

	/*********************************************************************************
	 *	@purpose: check stop messagge from App
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_stop()
	{
		uint8_t state = FAILED;

		if(Serial.available())
		{
		    if (Serial.peek() == 'S')
		    {
		      Serial.read();
		      stop_check = 'S';
		      Serial.println();
		      state = SUCCESS;
		    }
		    else if(Serial.peek() == 'K')
		    {
		    	Serial.read();
		    	stop_check = 'K';
		    	state = SUCCESS;
		    }
		}

		return state;
	}

	/*********************************************************************************
	 *	@purpose: switch to Clicker BLE or main board
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_BLE_mode()
	{
		uint8_t state = FAILED;

	    if (Serial.peek() == 'B')
	    {
	      Serial.read();
	      bluetooth_flag = 1;
	      //Serial.println("bluetooth_flag = 1");
	      state = SUCCESS;
	    }
	    else if (Serial.peek() == 'Z')
	    {
	      Serial.read();
	      bluetooth_flag = 0;
	      //Serial.println("bluetooth_flag = 0");
	      state = SUCCESS;
	    }

		return state;
	}

	/*********************************************************************************
	 *	@purpose: check if sleep message received
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_sleep()
	{

		uint8_t state = FAILED;

	    if (Serial.peek() == 'X')
	    {
	      Serial.read();
	      delay(10);
	      //Serial.println("Sleeping, Program completed");

	      // Turn off all LEDs
  	      uint32_t leds[] = {P1, P2, P3, P4, P5, P6, P7, P8, P9, P10};

	      for(int i = 0; i < 10; i++)
	      {
	      	digitalWrite(leds[i], LOW);
	      }

	      Serial.end();

	      // Go to Sleep
	      LowPower.deepSleep();
	      state = SUCCESS;
	    }

		return state;
	}

	/*********************************************************************************
	 *	@purpose: check if start button pressed
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_start_button()
	{
		if(digitalRead(PBS) == LOW)
		{
		    if (start_check == 'M')
		    {
		      unsigned long time_millis2 = millis();
		      while ((millis() - time_millis2) <= 1000);
		      while (digitalRead(PBS) == LOW);
		      if (digitalRead(PBS) == HIGH)
		      {
		        Serial.print("PL");

		        unsigned long time_millis = millis();
		        while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

		        char buffer[] = {};

		        if (Serial.available())
		        {

		          Serial.readBytes(buffer, 4);
		        }

		        // Flush all bytes
		        while (Serial.available() > 0)
		        {
		          Serial.read();
		        }

		        if (strncmp(buffer, "PACK", 4) == 0)
		        {

		          start_check = 'P';
		          if (bluetooth_flag)
		          {
		            bluetooth_flag = 0;
		            //Serial.println("Sleeping, Bluetooth connected");
		            Serial.end();
		            LowPower.deepSleep();
		          }
		        }
		      }
		    }
		}

		return SUCCESS;
	}

	/*********************************************************************************
	 *	@purpose: check if stop button pressed
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_stop_button()
	{

		if(digitalRead(PBST) == LOW)
		{
		    if (stop_check == 'S')
		    {
		      unsigned long time_millis2 = millis();
		      while ((millis() - time_millis2) <= 1000);
		      while (digitalRead(PBST) == LOW);
		      if (digitalRead(PBST) == HIGH)
		      {
		        Serial.print("SA");

		        unsigned long time_millis = millis();
		        while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

		        char buffer;

		        if (Serial.available())
		        {
		          buffer = Serial.read();
		        }

		        // Flush all bytes
		        while (Serial.available())
		        {
		          Serial.read();
		        }

		        if (buffer == 'K' || buffer == 'M')
		        {
		          stop_check = 'K';
		        }
		      }
		    }
		}

		return SUCCESS;
	}

	/*********************************************************************************
	 *	@purpose: check if reset button pressed
	 *
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_reset_button()
	{
		if(digitalRead(PBR) == LOW)
		{
		    while (digitalRead(PBR) == LOW);
		    Serial.print("R");
		}

		return SUCCESS;
	}


	/*********************************************************************************
	 *	@purpose: check button if its clicked
	 *
	 *  @button: button pin number
	 * 
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t check_button(uint32_t button)
	{
		uint8_t state;

		state = digitalRead(button);

		return (state == LOW) ? SUCCESS: FAILED;
	}

	/*********************************************************************************
	 *	@purpose: toggle corresponding led
	 *
	 *  @led: led pin number
	 * 
	 *	@return: status, SUCCESS or FAILED
	 *********************************************************************************/

	uint8_t toggle_led(uint32_t led)
	{

		uint8_t state = FAILED;

		uint32_t time_millis =  millis();
		while((millis() - time_millis) <= 1000);

		if(WaitButtonReturn(led))
		{
			if (activity_count >= 10)
		    {
		      activity_count = 0;
		      tens_count++;
		    }
		}

		// Flush bytes
		while(Serial.available())
		{
			Serial.read();
		}

		if(tens_count == 0)
		{
			PrintBelow10(led);
		}
		else if(tens_count >= 1)
		{
			PrintAbove10(led);
		}

		time_millis = millis();
		while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

	    if (ReadResponse())
	    {
	      activity_count++;
	      digitalWrite(led, HIGH);

	      state = SUCCESS;
	    }
	    else
	    {
	    	state = FAILED;
	    }

		return state;
	}

	static uint8_t ReadResponse()
	{
		char buffer[] = {0};
		bool status = false;

		if (Serial.available())
		{
			Serial.readBytes(buffer, 3);
		}

		if (strncmp((const char* )buffer, "ACK", 3) == 0)
		{
			status = true;
		} else {
			status = false;
		}

		return status;
	}

	static void PrintBelow10(uint32_t led)
	{
		switch(led)
		{
			case P1:
				Serial.print("1");
				break;

			case P2:
				Serial.print("2");
				break;

			case P3:
				Serial.print("3");
				break;

			case P4:
				Serial.print("4");
				break;

			case P5:
				Serial.print("5");
				break;

			case P6:
				Serial.print("6");
				break;

			case P7:
				Serial.print("7");
				break;

			case P8:
				Serial.print("8");
				break;

			case P9:
				Serial.print("9");
				break;

			case P10:
				Serial.print("10");
				break;

		}
	}

	static void PrintAbove10(uint32_t led)
	{

		char activity[] = {0};

		if(led != P10)
		{

			strncat(activity, &tens_count_charcaters[tens_count], 1);

			switch(led)
			{
				case P1:
	      			strcat(activity, "1");
					break;

				case P2:
	      			strcat(activity, "2");
					break;

				case P3:
	      			strcat(activity, "3");
					break;

				case P4:
	      			strcat(activity, "4");
					break;

				case P5:
	      			strcat(activity, "5");
					break;

				case P6:
	      			strcat(activity, "6");
					break;

				case P7:
	      			strcat(activity, "7");
					break;

				case P8:
	      			strcat(activity, "8");
					break;

				case P9:
	      			strcat(activity, "9");
					break;
			}
		}
		else
		{
			strncat(activity, &tens_count_charcaters[tens_count + 1], 1);
			strcat(activity, "0");
		}

     	Serial.print(activity);
	}

	static uint8_t WaitButtonReturn(uint32_t led)
	{
		uint8_t state = FAILED;

		switch(led)
		{
			case P1:

				while(digitalRead(ACT1) == LOW);
				if(digitalRead(ACT1) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P2:
				while(digitalRead(ACT2) == LOW);
				if(digitalRead(ACT2) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P3:
				while(digitalRead(ACT3) == LOW);
				if(digitalRead(ACT3) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P4:
				while(digitalRead(ACT4) == LOW);
				if(digitalRead(ACT4) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P5:
				while(digitalRead(ACT5) == LOW);
				if(digitalRead(ACT5) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P6:
				while(digitalRead(ACT6) == LOW);
				if(digitalRead(ACT6) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P7:
				while(digitalRead(ACT7) == LOW);
				if(digitalRead(ACT7) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P8:
				while(digitalRead(ACT8) == LOW);
				if(digitalRead(ACT8) == HIGH)
				{
					state = SUCCESS;
				}

				break;


			case P9:
				while(digitalRead(ACT9) == LOW);
				if(digitalRead(ACT9) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			case P10:
				while(digitalRead(ACT10) == LOW);
				if(digitalRead(ACT10) == HIGH)
				{
					state = SUCCESS;
				}

				break;

			default:
				state = FAILED;
				break;

		}	

		return state;
	}


	static void StartISR()
	{
		if (start_check == 'M')
		{

			//Serial.println("Test");

			unsigned long time_millis2 = millis();
			while ((millis() - time_millis2) <= 1000);

			//Serial.println("Test1");

			while (digitalRead(PBS) == LOW);

			//Serial.println("Test2");

			if (digitalRead(PBS) == HIGH)
			{
			  Serial.print("PL");

			  unsigned long time_millis = millis();
			  while (!(Serial.available()) && ((millis() - time_millis) <= TIMEOUT));

			  char buffer[] = {};

			  if (Serial.available())
			  {

			    Serial.readBytes(buffer, 4);
			  }

			  // Flush bytes
			  while (Serial.available() > 0)
			  {
			    Serial.read();
			  }

			  if (strncmp(buffer, "PACK", 4) == 0)
			  {
			    start_check = 'P';
			  }

			}
		}
	}

	static void WakeupISR()
	{
		Serial.begin(9600);
		//Serial.println("I am awake now and have enabled serial!");
	}
}