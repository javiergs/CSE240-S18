
var globals = globals || {};
(function init() {
  globals.isListening = globals.isListening || false;
  
  globals.speechEnd = globals.speechEnd || function speechEnd(x) {
    console.log("Received: " + x);
  };

  globals.listenOnce = function listenOnce() {
    if(globals.grammar) {
      if(!globals.recognition) {

        globals.recognition = new webkitSpeechRecognition();
        globals.speechRecognitionList = new webkitSpeechGrammarList();
        globals.speechRecognitionList.addFromString(globals.grammar, 1);
        globals.recognition.grammars = globals.speechRecognitionList;

        globals.recognition.language = 'en-US';
        globals.recognition.interimResults = false;
        globals.recognition.maxAlternatives = 1;

        globals.recognition.onend = globals.speechEnd();
        globals.recognition.onresult = globals.speechEnd();

      }
      if(!globals.isListening) {
        globals.recognition.start();
        globals.isListening = true;
        console.log("Listening: " + globals.isListening);

        $("#listen-btn").css({"background-color": "#FF0000"});
      } else {
        globals.isListening = false;
        globals.recognition.abort();
        console.log("Listening: " + globals.isListening);

        $("#listen-btn").css({"background-color": "#FFFFFF"});
      }
    } else {
      var xhr = $.get("res/grammar.txt", function(data) {
        console.log("Grammar List: " + data);
        globals.grammar = data;
        globals.listenOnce();
      });
    }
  };

  $(document).ready(function() {
    $("#listen-btn").click(function iWasClicked() {
      globals.listenOnce();
    });
  });
})();
