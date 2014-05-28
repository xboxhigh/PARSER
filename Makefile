parserJ : parser_json_version.cpp normJSON.cpp
	g++ parser_json_version.cpp normJSON.cpp -ljsonlib -lgumbo -o parserJ