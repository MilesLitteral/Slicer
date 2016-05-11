
## BENCHMARKS

### Benchmark 1

| Name                            | Task | Due Date      | Status     |
|---------------------------------|------|---------------|-------------
| Alberto Josue (design)          | 1    | 6:00 PM 3/2   | complete   |
| Jonathan Alicea (server side)   | 2    | 6:00 PM 3/2   | complete   |
| Dwayne Carolina (design)        | 1    | 6:00 PM 3/2   | complete   |
| Remy Cucui (server side)        | 3    | 6:00 PM 3/2   | complete   |
| Ryan Husband (design)           | 1    | 6:00 PM 3/2   | complete   |
| Miles Litteral (server side)    | 4    | 6:00 PM 3/2   | complete   |
| Will Maldonado (front end)      | 5    | 6:00 PM 3/2   | complete   |
| Tamanda Msosa (front end)       | 6    | 6:00 PM 3/2   | complete   |
| Suly Paredes (design)           | 1    | 6:00 PM 3/2   | complete   |
| Carlos Viera (design/front end) | 1,7  | 6:00 PM 3/2   | complete   |
| Ahmad Woods (server side)       | 2    | 6:00 PM 3/2   | complete   |
|---------------------------------|------|---------------|-------------
| Alberto Josue (design)          | 11   | 6:00 PM 3/30  | incomplete |
| Jonathan Alicea (server side)   | 8    | 6:00 PM 3/30  | incomplete |
| Dwayne Carolina (design)        | 11   | 6:00 PM 3/30  | incomplete |
| Remy Cucui (server side)        | 10   | 6:00 PM 3/30  | incomplete |
| Ryan Husband (design)           | 11   | 6:00 PM 3/30  | incomplete |
| Miles Litteral (server side)    | 10   | 6:00 PM 3/30  | incomplete |
| Will Maldonado (front end)      | 8    | 6:00 PM 3/30  | incomplete |
| Tamanda Msosa (front end)       | 9    | 6:00 PM 3/30  | incomplete |
| Suly Paredes (design)           | 11   | 6:00 PM 3/30  | incomplete |
| Carlos Viera (design/front end) | 8,9  | 6:00 PM 3/30  | incomplete |
| Ahmad Woods (server side)       | 8    | 6:00 PM 3/30  | incomplete |

## Task Descriptions

1. All designers meet and agree on the major functional components of the application. Each designer to individually interprets these functions to create a front-end user experience in Adobe Illustrator (or similar).

2. Build a test app in Django that starts with a view containing an HTTP POST form. When the POST is submitted, route the request via controller to a model that populates a database with the POST data, and then return a confirmation view.

3. Build a virtual machine with Vagrant and Virtual Box (using the versions of these apps installed in v314). It should be an Ubuntu machine, containing all components necessary for development (except for design software): Django, python, git, OpenSSL, mySQL, appropriate VBox guest additions, sublime (or similar), etc. Vagrant file and any build scripts should be committed to the class repo, along with a HOWTO.md.

4. Compile libsndfile and write a wrapper C program to chop a wav file into multiple smaller wav files with the libsndfile library.

5. Make an ajax request using AngularJS, and return a modification to the DOM to confirm success.

6. Use the Greeensock JS library to drag and drop an object; add a callback to the drop to make something obvious happen.

7. Capture audio from computer microphone using the Chrome browser.

8. Get AWS accounts; check if S3 is free. Upload and store audio file in S3 generated from Chrome recording. Create a user table with password hash for login. Create a table for associating user_id with sound. Create sound table. Routines for retrieving sounds.

9. Drag icon associated with sound to a bucket and it triggers the HTTP POST via ajax of that sound. Invesitage using Amazon cloudfront to stream -- make sure it's free -- vs. using soundcloud API.

10. Split up files based on ryhtmic maps in arbirtrary fractions of a second.

11. UEx: how does the user associate chosen soundfiles with beat maps, submit them for processing, and receive and audition the result.

## Useful links

1. Illustrator tuturials: [https://helpx.adobe.com/illustrator/atv/cs6-tutorials.html](https://helpx.adobe.com/illustrator/atv/cs6-tutorials.html). 

2. AngularJS: [https://angularjs.org](https://angularjs.org).

3. Libsndfile: [http://www.mega-nerd.com/libsndfile/](http://www.mega-nerd.com/libsndfile/).

4. Django: [https://www.djangoproject.com](https://www.djangoproject.com).

5. Greensock: [https://greensock.com](https://greensock.com).

6. Vagrant: [https://www.vagrantup.com](https://www.vagrantup.com).

7. Virtual Box: [https://www.virtualbox.org/wiki/Downloads](https://www.virtualbox.org/wiki/Downloads).

