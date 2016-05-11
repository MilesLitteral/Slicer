Requirements:
* Windows:
 * Virtualbox 5.0.4
 * Vagrant 1.7.4

* Mac OS X 10.10:
 * Virtualbox 5.0.4
 * Vagrant 1.7.4

* Ubuntu:
 * Use what is provided from your package manager

Steps:
# 1: add wily64 box: vagrant box add ubuntu/wily64 https://vagrantcloud.com/ubuntu/boxes/wily64/versions/20160222.0.0/providers/virtualbox.box
# 2: Navigate to the repository: cd <path to repo>
# 3: Start the virtual machine: vagrant up
 # 3a: On Windows 
  * After installing VirtualBox you need to go to your Network Connections from the control  panel
  * Right click on the device VirtualBox created, and click Poperties
  * Make sure the option VirtualBox NDIS6 Bridged Networking Driver is checked.
   * If it is already checked, uncheck it, and repeat the above two steps
# 4: Update your hosts file:
 # 4a: On Mac OS X:
  * sudo nano /private/etc/hosts
  * Add the line: 127.0.0.1 13.3.7.19
 # 4b: On Ubuntu:
  * sudo nano /etc/hosts
  * Add the line: 127.0.0.1 13.3.7.19
 # 4c: On Windows:
  * Navigate to C:\Windows\System32\drivers\etc
  * Copy hosts somewhere in your user folder (like the Desktop)
  * Open it with Notepad or Wordpad or Notepad++ or Sublime
  * Add the line: 127.0.0.1 13.3.7.19
# 5: Go into the virtual machine:
 # 5a: On Mac and Linux
  * vagrant ssh
 # 5b: On Windows
  * Download a program called PuTTY
  * Open it
  * Put in 127.0.0.1 for the host
  * Enter 2222 for the port
  * When asked what to log in as, type vagrant and press enter
  * Password is vagrant
# 6: Nagivate to /vagrant. This is your shared folder between the host and VM
# 7: Run the Django server with the command ```python manage.py runserver 13.3.7.19```
