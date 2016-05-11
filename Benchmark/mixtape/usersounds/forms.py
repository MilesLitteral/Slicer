from django import forms
from django.contrib.auth.models import User
from usersounds.models import UserProfile, Sounds
class UserForm(forms.ModelForm):
	password = forms.CharField(widget=forms.PasswordInput())
	class Meta:
		model = User
		fields = ('first_name','last_name','username','email','password')
class SoundsForm(forms.ModelForm):
	class Meta:
		model = Sounds
		fields = ('user', 'path','date')

