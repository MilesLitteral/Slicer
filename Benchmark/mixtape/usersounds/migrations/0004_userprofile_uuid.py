# -*- coding: utf-8 -*-
# Generated by Django 1.9.2 on 2016-03-31 01:55
from __future__ import unicode_literals

from django.db import migrations, models
import uuid


class Migration(migrations.Migration):

    dependencies = [
        ('usersounds', '0003_remove_userprofile_uuid'),
    ]

    operations = [
        migrations.AddField(
            model_name='userprofile',
            name='uuid',
            field=models.UUIDField(default=uuid.uuid4, editable=False),
        ),
    ]