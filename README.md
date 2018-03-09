## ChatAPP
# Simple TCP Socket client chat program.

This program is a client program for text messaging. The program is written in c++ using the Qt framework and uses QTCP socket library for communications with the server.

Releases:
Executable for windows ChatAPP_RC1.0.zip (2018-03-08) [here](https://github.com/NeumanShowcase/ChatAPP/blob/Releases/ChatAPP_RC1.0.zip) </br></br>
Source code in ChatAPP_Source_RC1.0.zip (2018-03-08)</br>
Documentation:
DOCS_README.pdf   [here](https://github.com/NeumanShowcase/ChatAPP/blob/docs/ChatAPP_README.pdf) </br>
DOCS_Pictures_UI.pdf [here](https://github.com/NeumanShowcase/ChatAPP/blob/docs/DOCS_Pictures_UI.pdf)</br>

## Prerequisites:
Windows OS for EXE, cross platform Qt code.
Neuman chatAPP server running on python 3.x
                         	                         	

## The client provides the following features: 

* Connect to server with status indicators and error handling
* Sending to,  and receiving messages from server while typing
* Simple “enter click” to send.
* UTF-8 char support.
* Resizable windows.
* Scrollable message window automatically scrolls to last message.
* Slick and minimalistic UI with anti tired eyes color scheme.
* Nickname support through command line arguments or text field input
* Disconnect from server and connect to other.
* Quit handled with real disconnect, asks “are you sure” before quitting.
* Funny icon.

## Connection mode:
User starts application and are greeted by an UI that contains:
 a drop down menu with the options to disconnect or quit the application. The “disconnect” option is not clickable until the program is connected.
The Logo-like connection sign is an indicator of connection state. Gray: inactive, Red: connection lost, Green: connected.
Nickname input for screen name in chat
Ip address field where user can tell address of host
Port field where user can tell port the service is running on (default is 1337)
Big fat connect button.

The user puts the adress (IP) to the hosting server and the portnumber the service is running on. When user presses “connect” an connection attempt is being made to this address through TCP socket request. This is a try method and the program waits a maximum of 2 seconds before throwing the user an error box telling the user that the remote address is not reachable. The indicator turn to red. 
If attempt to connect is successful the application switches to “message mode”.


![alt text](https://i.imgur.com/Xl8NzgO.png)

## Messaging mode:
User is presented with two input text boxes, one with the server welcome message in and another for writing your message. Next to the message writing a large button with the label “send” is located but user can also press “enter” key to send msg to server. Application takes for granted that the user is familiar with the modern way chat programs work, therefore application gives no guidance here. From the top drop down menu user can disconnect from server or quit the application. If user chooses to disconnect user is taken to the connection mode again showing a red cat5 cable as indicator of being offline.



![alt text](https://i.imgur.com/jVMixeT.png)
