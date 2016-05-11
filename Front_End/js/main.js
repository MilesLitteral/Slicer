(function () {


    /* Grab the credentials From an external JSON file */
    $.getJSON('settings-development.json', function (data) {
        AWS.config.update({
            accessKeyId: data.AWSAccessKeyId,
            secretAccessKey: data.AWSSecretAccessKey
        });
        AWS.config.region = data.AWSRegion;


    });

    /* Create the context and start stream */

    var audioCtx,
        recorder,
        i = 0,
        arrayOfBlobs = new Array();

    function startUserMedia(stream) {
        var context = audioCtx.createMediaStreamSource(stream);
        recorder = new Recorder(context);

        console.log(context);

    }


    /* Start the recording */

    function begin() {
        recorder.record();
    }

    function makeLink() {
        recorder && recorder.exportWAV(function (blob) {
            var url = URL.createObjectURL(blob),
                title = 'recording' + i + '.wav';

            uploadBlob(blob, title);



            arrayOfBlobs.push(url);

            addAnother(title, i, arrayOfBlobs);
            console.log(arrayOfBlobs);

            i++;


        });
    }


    function uploadBlob(blob, title) {

        var bucket = new AWS.S3({
            params: {
                Bucket: 'soundshake'
            }
        });

        if (blob) {

            var params = {
                Key: title,
                ContentType: blob.type,
                Body: blob
            };
            bucket.upload(params).on('httpUploadProgress', function (evt) {
                console.log("Uploaded :: " + parseInt((evt.loaded * 100) / evt.total) + '%');
            }).send(function (err, data) {

                /* success callback */

            });
        }
        return false;

    }



    function end() {
        recorder.stop();

        makeLink();

        recorder.clear();
        console.log(arrayOfBlobs);
    }

    /* Make sure there's audio capabilities */

    function init() {
        try {
            // webkit shim
            window.AudioContext = window.AudioContext || window.webkitAudioContext;
            navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia;
            window.URL = window.URL || window.webkitURL;

            audioCtx = new AudioContext();

        } catch (e) {
            alert('No web audio support in this browser!');
        }

        navigator.getUserMedia({
            audio: true
        }, startUserMedia, function (e) {

        });
    }


    /* This grabs the content of the html element, stores it in a varible, then removes that element from the dom, and clones it into an an empty div */


    function addAnother(title, i, blob) {

        var content = d3.select('div').html();
        $('#temp').detach(); // change to vanilla JS

        var div = d3.select('body').append('div')
            .html(content);

        var sound = blob[i];

        div.select('svg').attr('id', 'soundFile' + i)
            .attr('class', 'sf shadow')
            .each(function (d, i) {
                touchEventListener(this, d, sound);
            });
        div.select('#soundFile' + i + ' .soundFileText').text(title);

        var coords = $(window).height(); // Change to vanilla JS

        div.select('#soundFile' + i)
            .style('top', -coords)
            .transition()
            .style('top', (coords * .01))
            .duration(1000).ease('bounce');

    }



    function touchEventListener(e, d, blobSound) {
        var elToSlide = d3.select(e),
            wholeElement = Hammer(e),
            playButton = Hammer(e.children[3]),
            outer = d3.select(e.children[2]);



        wholeElement.on("panright", function (event) {


            elToSlide.style('left', (event.deltaX / 2) + 'px');
        });

        wholeElement.on("panend", function (event) {
            elToSlide.transition()
                .style('left', 0)
                .duration(1000)
                .ease('bounce');


        });

        playButton.on('tap', function (event) {
            var audio = new Audio(blobSound);
            audio.load();
            audio.play();



            outer
                .transition('rotation')
                .style('-webkit-transform', 'rotate(360deg)')
                .duration(1000);

        })



    }




    init();

    var recordButton = Hammer(d3.select('#recordButton')[0][0]),
        collection_SigSVG = d3.selectAll('.cls-2');



    recordButton.on('press', function () {

        begin();

        collection_SigSVG.each(function repeat(d, i) {
            d3.select(this).transition('boom')
                .style('fill', '#51464e')
                .duration(i * 500)
                .transition('boom')
                .style('fill', '#000')
                .duration(1000);

            collection_SigSVG.transition('somethingelse')
                .style('fill', '#baf4b9')
                .duration(500).delay(1500).each('end', repeat);



        });

    }).on('pressup', function () {

        end();

        collection_SigSVG.transition('somethingelse')
            .style('fill', '#baf4b9').duration(3000);
    });









})();
