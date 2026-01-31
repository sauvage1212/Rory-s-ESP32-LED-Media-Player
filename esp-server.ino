#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Remember to replace this.";
const char* password = "You thought I left it in!";

WebServer server(80);

const int controlPin1 = 17;
const int controlPin2 = 19;
const int controlPin3 = 18;
// Mary had a little lamb: 12321112221111232111322123

String currentTune = "";

void playMusic(String tuneName, int tempoInBPM, int tuneLength, int notes[]) {
  // Serial.println(notes[26]);
  int tempoInMS = 60000/tempoInBPM;
  currentTune = tuneName;
  for(int i = 0; i<tuneLength; i++){
    Serial.println(notes[i]);
    int note = notes[i];
    if (note == 0) {
      delay(tempoInMS);
    } else if (note == 1) {
      digitalWrite(controlPin1, HIGH);
      delay(tempoInMS*0.95);
      digitalWrite(controlPin1, LOW);
      delay(tempoInMS*0.05);
  } else if (note == 2) {
    digitalWrite(controlPin2, HIGH);
    delay(tempoInMS*0.95);
    digitalWrite(controlPin2, LOW);
    delay(tempoInMS*0.05); 
  } else if (note == 3) {
    digitalWrite(controlPin3, HIGH);
    delay(tempoInMS*0.95);
    digitalWrite(controlPin3, LOW);
    delay(tempoInMS*0.05); 
  }else if (note == 11) {
    digitalWrite(controlPin1, HIGH);
    delay(tempoInMS*2-tempoInMS*0.05);
    digitalWrite(controlPin1, LOW);
    delay(tempoInMS*0.05); 
  } else if (note == 22) {
    digitalWrite(controlPin2, HIGH);
    delay(tempoInMS*2-tempoInMS*0.05);
    digitalWrite(controlPin2, LOW);
    delay(tempoInMS*0.05); 
  } else if (note == 33) {
    digitalWrite(controlPin3, HIGH);
    delay(tempoInMS*2-tempoInMS*0.05);
    digitalWrite(controlPin3, LOW);
    delay(tempoInMS*0.05); 
  } else if (note == 123) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, HIGH);
    digitalWrite(controlPin3, HIGH);
    delay(tempoInMS*0.95);
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, LOW);
    delay(tempoInMS*0.05); 
  } else if (note == 1234) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, HIGH);
    digitalWrite(controlPin3, HIGH);
    delay(tempoInMS*4-tempoInMS*0.05);
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, LOW);
    digitalWrite(controlPin3, LOW);
    delay(tempoInMS*0.05); 
  };
  };
  currentTune = "";
};

void uploadTune() {
  if (currentTune != "") {
    // 409: Conflict, tune already playing.
    server.send(409, "text/html", "Tune already playing, sorry :( !");
    return;
  };
  // Example: Getting a query parameter "tuneName" from /upload?tuneName=myTune
  String tuneName = server.arg("name");
  int tempo = server.arg("tempo").toInt();
  int tuneLength = server.arg("length").toInt();
  String notesStr = server.arg("notes");
  int notes[tuneLength] = {};
  int positionInArray = 0;
  String note = "";
  // Serial.println(notesStr.length());
  for (int i=0; i<=notesStr.length(); i++) {
    char c = notesStr[i];
    // Serial.println(i);
    // Serial.println(c);
    // Serial.println("Note: "+note);
    if (c==',') {
      notes[positionInArray] = note.toInt();
      positionInArray++;
      note = "";
    } else if (i == notesStr.length()) {
      note +=c;
      // Serial.println("End-note: "+note);
      notes[positionInArray] = note.toInt();
      positionInArray++;
      note = "";
    } else {
      note += c;
    };
  };
  // Serial.println(tuneName);
  // Serial.println(tempo);
  // Serial.println(tuneLength);
  Serial.println(notesStr);
  Serial.println("Array: ");
  for (int i = 0; i < 26; i++) {
    Serial.print(",");
    Serial.print(notes[i]);
  };
  // return;
  // String html = "<!DOCTYPE html><html><body>"+tuneName+"</body></html>";
  // html += "<h1>ESP32 Button Control</h1>";
  // html += "<p>Pin is currently: " + String(pinState ? "ON" : "OFF") + "</p>";
  // html += "<a href=\"/toggle\"><button>Toggle</button></a>";
  // html += "</body></html>";
  // server.send(200, "text/html", html);
  // pinState = !pinState;       // flip state
  // digitalWrite(controlPin, pinState ? HIGH : LOW);
  // Serial.println(String("Pin state changed to ") + (pinState ? "HIGH" : "LOW"));
  server.sendHeader("Location", "/"); // redirect back to root
  server.send(303);

  playMusic(tuneName, tempo, tuneLength, notes);
}

void homePage() {
  String html = "<!DOCTYPE html><html><body>";
  html += "<h1>Rory's ESP32 LED Media Player</h1>";
  if (currentTune != "") {
    html += "<p>Currently playing: "+currentTune+"</p>";
  };
  html += "<button onclick=\"impFile();\">Play file</button>";
  html += "<script>function impFile() {const input = document.createElement(\"input\");input.type = \"file\";input.accept = \".rory\";input.multiple = false;input.click();\
input.onchange = async () => {\
// console.log(input.files);\n \
//   for(i=0; i<input.files.length; i++) {\n \
// console.log(input.files[0].name.substring(0, input.files[0].name.length - 5));\n \
let importFilePromise = new Promise((resolve, reject) => {\
const file = input.files?.[0];\
const reader = new FileReader();\
reader.readAsText(file);\
reader.onload = (e) => {\
let importFileContents = JSON.parse(e.target.result);\
// console.log(\"File content:\", importFileContents);\n \
resolve(importFileContents);\
};\
reader.onerror = function(e) {\
console.log(\"File failed to import file, \", e);\
alert(\"File failed to import, \", e);\
reject(e);\
};\
});\
importFilePromise.then((fileJSON) => window.location.href = `/upload?name=${input.files[0].name.substring(0, input.files[0].name.length - 5)}&&tempo=${fileJSON.tempo}&&length=${fileJSON.length}&&notes=${fileJSON.notes}`);\
//   };\n\
};};</script>";
  html += "</br>";
  html += "<a href=\"/upload?name=Mary%20Had%20a%20Little%20Lamb&&tempo=120&&length=26&&notes=1,2,3,2,1,1,11,2,2,22,1,1,11,1,2,3,2,1,1,1,3,2,2,1,2,1234\"><button>Play \"Mary Had a Little Lamb\".</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  // pinState = !pinState;       // flip state
  // digitalWrite(controlPin, pinState ? HIGH : LOW);
  // Serial.println(String("Pin state changed to ") + (pinState ? "HIGH" : "LOW"));
  // server.sendHeader("Location", "/"); // redirect back to root
  // server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(controlPin3, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", homePage);
  server.on("/upload", uploadTune);
  // server.on("/toggle", handleToggle);
  // server.on("/auto-toggle", handleAutoToggle);
  server.begin();
  Serial.println("HTTP server started");

  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
  digitalWrite(controlPin3, LOW);
  delay(1000);
}

void loop() {
  server.handleClient();
  // int tune[] = {1, 2, 3, 2, 1, 1, 11, 2, 2, 22, 1, 1, 11,    1, 2, 3, 2, 1, 1, 11, 3, 2, 2, 1, 2, 123123};
  // playMusic("Mary Had a Little Lamb", 120, 26, tune);
  // delay(840);
}
