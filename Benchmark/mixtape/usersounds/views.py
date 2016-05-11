from django.shortcuts import render
from django.http import HttpResponse
from usersounds.forms import UserForm
def index(request):
	return HttpResponse("Sup")
def register(request):
	registered = False

	if request.method == 'POST':
		user_form = UserForm(data=request.POST)

		if user_form.is_valid():
			user = user_form.save()

			user.set_password(user.password)
			user.save()

			registered = True

		else:
			print user_form.errors

	else:
		user_form = UserForm()

	return render(request, 'usersounds/register.html', 
		{'user_form': user_form,  
		'registered': registered})
# Create your views here.
