Image-Organizer
---------------
Photo Organizer app

A user friendly desktop app for organize your photos.

Features:
1) Finding all matching images.
2) Finding all similar images.
3) Searching for the image you are looking for.


Project Back-end structure: html/index.html
Project Front-end structure: ImgOrganizer/html/index.html



Usage
----------------
First the user chooses a root folder to recursively search for images. 
Then the user chooses a functionality to execute. There are three main functionalities to choose from:
Finding Duplicate images. Recursively searching a file system for images that have the same image but perhaps in a different format, png/jpg/bmp. 
Finding similar images. Finding images that have been modified i.e. changed dimensions, brightness, cropped or rotated and presenting them in groups. 
Searching for images based on a particular characteristic. This feature is still in development. 
Searching for images with a particular amount of people in them.
Searching for images similar to another image.
Searching for a person.
Then the user presses scan and the resulting images are presented alongside a portal to the filesystem: 
Finally, the user can choose between three choices of how to organize the images: by either deleting the images, opening the file, or removing the images.

Installation 
----------------
First choose the installer that matches your Operating system. At the moment only x32 and x64 for windows have been created. An installation wizard will open up. Choose a folder to install to and press install.


Testing
----------------
Make sure you have the following installed in order to run tests:
A terminal to run bash scripts. 
Python version 3.4 or higher. 
The following Python distributions:  pillow, matplotlib, numpy, pandas. These all can be installed with pip install command easily 	from a terminal.
	

Manual testing
----------------
Make sure you have a folder with images in it to test.
Create duplicate or similar images to look for. You can generate these with one of the python scripts in “testing” folder or create 	them manually.
Run: “./ ImgOrganizer.exe –b –s <folder name>” in the folder: ImgOrganizer/x64/Release or go to “testing” folder and use “./test_cmd <folder name>” which will run ImgOrganizer.exe for you.  
Two .txt files are generated with the groups that were found. 
You can use summarize.py to summarize the output into an excel file.
 You can use draw_chart.py to create a pdf with charts from the excel file.

Automated testing
----------------
Since manually testing is a cumbersome task I created a script which automates the testing.
This is by far the simplest way to test this application and get a clear performance overview.
How to use it:
Go to “testing” folder.
In your terminal use the command: auto_run <path to folder with images> <number of images to duplicate>
A folder is generated with various tests with a timestamp with summary excel files and pdf’s with charts. You can still view the 	raw data in the folder “raw_output_data”.


Videos
----------------
https://youtu.be/CU6yEAYrcCE
	
https://youtu.be/S83lezZL7fQ
	
https://youtu.be/WIgs_fdcHVc
	
https://youtu.be/AitqRuXbYOY
