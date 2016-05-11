##Git Cheat Sheet
Note: text enclosed in lt/gt symbols (e.g., <some text\>) is to be modified by the user; remove the lt/gt symbols after modification.

### Setting up git on your local machine (OS X 10.9 Mavericks)

Follow the directions for installing Macports for OS X 10.9 Mavericks here: [https://www.macports.org/install.php](https://www.macports.org/install.php)

Once installed, run the following command:

	$ sudo port install git

### Setting up your local machine for secure communication with GitHub

	Note that we will store your SSH keys on a USB flash drive,
	since the computers we are working on are insecure.
	
	Make sure your flash drive is formatted Mac OS Extended
	(use /Applications/Utilities/Disk Utility.app).
	
	$ cd "/Volumes/<the name of my USB drive>/"
	
	$ mkdir .ssh
	
	$ chmod 700 .ssh

	$ ssh-keygen -t rsa -C "<your_email_address>"
	  Generating public/private rsa key pair.
	  Enter file in which to save the key (~/.ssh/id_rsa): 
	  
	When prompted above, enter the following:
	  /Volumes/<the name of my USB drive>/.ssh/github_rsa
	  
	Just press return when prompted for a passphrase.

    $ cd .ssh
	
	$ chmod 600 github_rsa
	
    $ cd ~
	
	$ mkdir .ssh

	$ chmod 700 .ssh
	
	$ cd .ssh
	
	$ touch config

    Open the config file in a text editor of your choosing
	(below, we use 'mate'):
    
	$ mate config
	
	Make your config file look like the following, and save:
	
	Host github.com
	    HostName github.com
	    IdentityFile /Volumes/<the name of my USB drive>/.ssh/github_rsa
	    User <your GitHub username>

    $ chmod 700 config
	
	$ mate /Volumes/<the name of my USB drive>/.ssh/github_rsa.pub
	
	Copy your public key out of the code editor launched above and email it,
	along with your Github user name, to the repository admin.

### Cloning and checking out a copy of the 'develop' branch for the first time

	$ cd ~/<your_name>

	$ git clone git@github.com:entertainmenttechnology/Wilson-MTEC4800-Spring-2016-IDTPII.git

	$ cd Wilson-MTEC4800-Spring-2016-IDTPII

	$ git checkout -b <firstname_lastname>_working --track origin/develop

### Committing your changes to a remote copy of your working branch

	$ git branch

	Make sure you are in your <firstname_lastname>_working branch.

	$ git pull --rebase origin develop

	Make modifications to files.
	
	$ git status

	Look over new and modified files.

	$ git diff <file>

	Look over changes to a particular file.

	$ git add -A

	$ git commit -m "<a concise message about what changes you made in this commit>"	  

	$ git pull --rebase origin develop

	$ git push origin <firstname_lastname>_working

### Making a pull request

1. Go to [https://github.com/entertainmenttechnology/Wilson-MTEC4800-Spring-2016-IDTPII](https://github.com/entertainmenttechnology/Wilson-MTEC4800-Spring-2016-IDTPII).
  
2. Locate your branch in the branch dropdown menu.

4. Click the "pull request" text at the top right of your branch changes pane.

3. Select "Edit" at the top to change your request to merge to the "develop" branch instead of the "master" (default) branch.
  
4. If satisfied with your changes, write a subject and summary comment and press the "Create pull request" button.
  
The admin may leave comments in your code requiring further commits before merged to develop.
  
