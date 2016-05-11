from __future__ import unicode_literals
from django.contrib.auth.models import User
from django.db import models
import uuid

class UserProfile(models.Model):
	user = models.OneToOneField(User)
	uuid = models.UUIDField(default=uuid.uuid4, editable=False)
	def __unicode__(self):
		return self.name
		
class Sounds(models.Model):
	user = models.OneToOneField(
		UserProfile,
		on_delete=models.CASCADE,
		primary_key=True,
		)
	path = models.URLField()
	date = models.DateTimeField()

	def __unicode__(self):
		return self.name
# Create your models here.
