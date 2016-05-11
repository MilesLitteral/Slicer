#!/bin/bash

# Disable system locale check
sudo touch /var/lib/cloud/instance/locale-check.skip

# Update package repositories
sudo apt-get update -y --force-yes

# Install OS-level dependencies
sudo apt-get install libmysqlclient-dev python-dev debconf-utils -y --force-yes

# Install MySQL
echo "Installing MySQL..."
echo "mysql-server-5.5 mysql-server/root_password password root" | sudo debconf-set-selections
echo "mysql-server-5.5 mysql-server/root_password_again password root" | sudo debconf-set-selections
sudo apt-get install mysql-server -y --force-yes

# Install PHPMyAdmin
echo "Installing PHPMyAdmin..."
echo "phpmyadmin phpmyadmin/setup-password password root" | sudo debconf-set-selections
echo "phpmyadmin phpmyadmin/mysql/app-pass password root" | sudo debconf-set-selections
echo "phpmyadmin phpmyadmin/mysql/admin-pass password root" | sudo debconf-set-selections
echo "phpmyadmin phpmyadmin/app-password-confirm password root" | sudo debconf-set-selections
echo "phpmyadmin phpmyadmin/password-confirm password root" | sudo debconf-set-selections
echo "phpmyadmin phpmyadmin/dbconfig-install boolean true" | sudo debconf-set-selections
echo "phpmyadmin phpmyadmin/reconfigure-webserver multiselect apache2" | sudo debconf-set-selections
sudo apt-get install phpmyadmin -y --force-yes

# Set up offline db
mysql -u root -proot -e 'create database dev'

# Install git for version control, pip for install python packages
echo 'Installing git and python-pip...'
sudo apt-get install git python-pip -y --force-yes

# Install HubFlow
git clone https://github.com/datasift/gitflow
cd gitflow
sudo ./install.sh
cd /vagrant
git hf init

# Install requirements
pip install -r /vagrant/requirements.txt

# Complete
echo ""
echo "Vagrant install complete."
echo "Now try logging in:"
echo "    $ vagrant ssh"