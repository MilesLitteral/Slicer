var audioCtx,
    recorder,
    i = 0,
    download = $('#downloads');

function startUserMedia(stream) {
    var context = audioCtx.createMediaStreamSource(stream);
    recorder = new Recorder(context);

}



/* Start the recording */

function begin() {
    recorder.record();

    $(this)
        .prop('disabled', true)
        .next()
        .prop('disabled', false);
}

function makeLink() {
    recorder && recorder.exportWAV(function (blob) {
        var url = URL.createObjectURL(blob),
            title = 'recording' + i + '.wav';

        download.append('<li><a href="' + url + '" download="' + title + '">' + title + '</a></li>');

        i++;
    });
}


function end() {
    recorder.stop();

    makeLink();

    recorder.clear();
    $(this)
        .prop('disabled', true)
        .prev()
        .prop('disabled', false);

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




$(function () {
    init();

    var recordButton = $('#recordButton'),
        stopButton = $('#stopButton');

    recordButton.on('click', begin);
    stopButton.on('click', end);

});