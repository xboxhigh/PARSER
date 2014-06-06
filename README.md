PARSER
======

C++ Parser


### Installation Steps:

#### Install gumbo-parser, follow this web site https://github.com/google/gumbo-parser
```js
	Check your system has already install the following tools (libtool, make, g++, autoconf, autogen, automake) and is up-to-date.
```

#### Install json-cpp
```js
	First, you need to install the scons tool, make sure the version is higher than 2.1.0.
	Second, download the json-cpp source code from this web site http://sourceforge.net/projects/jsoncpp/
		Use the 0.5.0 version is enough.
	Third, change the current path to the jsoncpp-src-0.5.0, and assign the platform. for example.
		~$ scons platform=linux-gcc
	Forth, mv the libs and include files to the assign path
		~$ cp jsoncpp-src-0.5.0/libs/linux-gcc-4.8/libjson_linux-gcc-4.8_libmt.* /usr/local/lib/libjsoncpp.*
		~$ cp -r jsoncpp-src-0.5.0/include/json /usr/include/
	Fifth, execute the command ldconfig to make the dynamic linker of ljsocpp
```

#### Test of compile the program
```js
	~$ make parserX
```
