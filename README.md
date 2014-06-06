PARSER
======

C++ Parser


### Installation Steps:

#### Install gumbo-parser
follow the web site guide https://github.com/google/gumbo-parser
```js
Check your system has already install the following tools (libtool, make, g++, autoconf, autogen, automake) and is up-to-date.
```

#### Install json-cpp

Download the json-cpp source code from this web site http://sourceforge.net/projects/jsoncpp

```js
	First, you need to install the 'scons' tool, make sure the version is higher than 2.1.0.
	
	Second, change the current path to the jsoncpp-src-0.5.0, and assign the platform. for example.
		
		~$ scons platform=linux-gcc
		
	Third, mv the libs and include files to the assign path
	
		~$ cp jsoncpp-src-0.5.0/libs/linux-gcc-4.8/libjson_linux-gcc-4.8_libmt.* /usr/local/lib/libjsoncpp.*
		
		~$ cp -r jsoncpp-src-0.5.0/include/json /usr/include/
		
	Forth, execute the command ldconfig to make the dynamic linker of ljsocpp
```

#### Test of compile the program
```js
	~$ make parserX
```
