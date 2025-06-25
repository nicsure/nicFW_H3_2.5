Requires a compatible Keil compiler and 8051 wrapping project for the TA3782F MCU. I cannot supply that due to copyright issues.

To compile you will need to contact SinOne and request their SDK for this chip, then collate the nicFW source into their "Hello World" example Keil project to supply all the required hardware typedefs and defines. Not that they will probably palm you off with their publicly available SDK for their retail chips, this is NOT what you want. You need the proprietary SDK for the TA3782F. 

This code is a singleton pattern and VERY different from what is typically considered normal C.
