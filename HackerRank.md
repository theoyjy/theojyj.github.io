#### `cin.ignore()`
```cpp
cin >> n >> p;
cin.ignore() // ignores the leftover '\n' after the integers
```
#### read string
```cpp
getline(cin, str);
```

#### string split
1. find `size_t pos = str.find_first_of("<>\" ", offset)`:
2. trim `str.substr(start, length)`
```cpp
while(start < str.length())
{
	size_t pos = str.find_first_of(delimiters, start);
	if(pos != string::npos)
	{
		if(pos > start)
		{
			string token = str.substr(offset, pos - start);
		}
		start = pos + 1;
	}
	else
	{
		string token = sub.substr(start); // pre dilimeter to the end
		start = str.length();// to exit the loop
	}
}
```

#### try catch

1. catch 所有想要截取的特殊exception 比如
	- `invalid_argument`
	- `out_of_range`
	- `runtime_error`
	- `bad_malloc`
2. 剩下的 catch `exception` 
3. 之后可以catch `int` `float` 等
4. 最后`catch(...)`
```cpp
try { 
	// Uncomment one of these throw statements to test 
	// throw std::invalid_argument("Invalid argument exception"); 
	// throw std::out_of_range("Out of range exception"); 
	// throw std::runtime_error("Runtime error exception");
	// throw CustomException(); 
	// throw 42;
	// throw 3.14; 
	// throw "A C-style string exception"; 
	// throw std::string("A C++ string exception"); 
	} 
	catch (const std::invalid_argument& e) { 
		std::cout << "Caught std::invalid_argument: " << e.what() << std::endl; 
	} 
	catch (const std::out_of_range& e) { 
		std::cout << "Caught std::out_of_range: " << e.what() << std::endl; 
	} 
	catch (const std::runtime_error& e) { 
		std::cout << "Caught std::runtime_error: " << e.what() << std::endl; 
	} 
	catch (const std::exception& e) { 
		// Catches any other standard exceptions derived from std::exception
		 std::cout << "Caught std::exception: " << e.what() << std::endl; 
	} 
	catch (const CustomException& e) { 
		std::cout << "Caught CustomException: " << e.what() << std::endl; 
	} 
	catch (int e) { 
		std::cout << "Caught an integer: " << e << std::endl; 
	} 
	catch (double e) { 
		std::cout << "Caught a double: " << e << std::endl; 
	} 
	catch (const char* e) { 
		std::cout << "Caught a C-style string: " << e << std::endl; 
	} 
	catch (const std::string& e) { 
		std::cout << "Caught a C++ string: " << e << std::endl; 
	} 
	catch (...) { // Generic catch-all for any other exception types 
		std::cout << "Caught an unknown exception!" << std::endl; 
	}
```