# Project: Mars-Exploration
#### - Same as the Base Project [*here*](https://github.com/AhmedAlaa2024/Mars-Exploration)


#### I added a GUI to the Program instead of the console.
> Feel free to add whatever features you see

#### Setting-Up The Lib
* **Open Properties**
  1. In the C/C++ -> general:  
	set the (\include\msvc) and (\include) dir
  2. In the Linker -> general:
    set the lib dir (\lib\vc14x_x64_dll)
  3. In the C/C++ -> preprocessor: change the definitions to be:  
	>	_DEBUG  
	>	_CONSOLE  
	>	WXUSINGDLL  
	>	wxMSVC_VERSION_AUTO  
	>	wxMSVC_VERSION_ABI_COMPAT  
	>	_CRT_SECURE_NO_WARNINGS


* Save and Restart Vs and it should work.


#### Image from the Program:

![Image](assests/im1.png "step-by-step simulation")
