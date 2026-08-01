TEMPLATE = subdirs

SUBDIRS += \
    cm-lib \
    cm-tests \
    cm-ui

message(cm project dir: $${PWD})

#Project Files (.pro) are Associated with QMAKE AND NOT CMAKE.

#This is a Main Project File (.pro) for a SubDirectry "Project"

#The First Line 'TEMPLATE' Defines the type of Project like if it is "TEMPLATE = lib" then it is a library project
#means the ultimate compiled product of the project will not be an executable (.exe), instead it will be a ".dll" file
#Here it is "TEMPLATE = subdirs" which ensures that the project is a combination of different subprojects and the ultimate
#compiled product will be the combination of compiled products of all the subprojects while the rules of compilation will
#depend upon the Project Files (.pro) of all the inner sub-projects and the established linkage between them.

#The "SUBDIRS" Define the names of all the Subdirectory Projects currently established in this Main Project

#"PWD" is a variable which stores the "Project Working Directory". The working directory of any project is the directory
#where .pro file is placed NORMALLY. The method of obtaining value of any variable of .pro files is "$${variable}" within
#a function while just "$$variable" outside function, and it returns the stored value of the variable even if the variable
#stores a string of path to a particular file or folder as such in this case

#Some ".pro Specific Functions" like message() (NOT ALL) does nothing to project configurations. These are useful to see
#particular projects information like "message" here is displaying the current working directory path. The message is a
#display function and it displays information only once on the console when it is written or when any change is done within
#the file which causes the project to re-evaluate
