#include <SourDough_Cellular.hpp>

#define INBOUND_QUEUE_COMMAND_FIELD "my-request-type"
 
void Cellular_Setup(Notecard *NOTE) {

    usbSerial.begin(115200);
    while (!usbSerial) {
    ; // wait for serial port to connect. Needed for native USB
    }
    usbSerial.println("Starting...");
 
    txRxPinsSerial.begin(9600, SERIAL_8N1, 18,17);
    NOTE->begin(txRxPinsSerial, 9600);
    NOTE->setDebugOutputStream(usbSerial);

    J *req = NoteNewRequest("hub.set");
    if (req != NULL) {
        JAddStringToObject(req, "mode", "continuous");
        JAddStringToObject(req, "product", NOTE_PRODUCT_UID);
        JAddBoolToObject(req, "sync", true);
        //NOTE->sendRequest(req);
        NoteRequest(req);
    }
    req = NoteNewRequest("hub.sync");
    if (req != NULL) {
        JAddBoolToObject(req, "allow", true);
        NoteRequest(req);
    }
    req = NoteNewRequest("hub.sync.status");
    if (req != NULL) {
        JAddBoolToObject(req, "sync", true);
        NoteRequest(req);
    }
}

void Cellular_Send(Notecard *NOTE) {
  // put your main code here, to run repeatedly:
  int vehicle_id = 1000;
  int light_id = 1000;

    J *req = NoteNewRequest("web.post");
    JAddStringToObject(req, "route", "Sourdough_ping");

    if (req != NULL) {
        JAddBoolToObject(req, "sync", true);
        J *body = JAddObjectToObject(req, "body");
        if (body) {
            JAddNumberToObject(body, "VehicleID", vehicle_id);
            JAddNumberToObject(body, "LightID", light_id);
        }

        NoteRequest(req);

        //J *rsp = NOTE->requestAndResponse(req);

        // if (rsp != NULL) {
        //     // if(NOTE->responseError(rsp)){
        //     //     NOTE->deleteResponse(rsp);
        //     // }
        //     //else {
        //         J *rsp_body = JGetObject(rsp, "body");
        //         if (rsp_body != NULL) {
        //             char *response = JGetString(rsp_body, INBOUND_QUEUE_COMMAND_FIELD);
        //             NOTE->logDebugf("INBOUND REQUEST: %s\n\n", response);
        //         }
        //     //}
        // }
        // NOTE->deleteResponse(rsp);
        delay(15000);
    }
    
}

 void Cellular_Task(void* p_arg){  
      // Setup RF
      Notecard NOTE;
      Cellular_Setup(&NOTE);
      Cellular_Send(&NOTE);
      Serial.println("Setup Cellular");
      while(1){
            Serial.println("Cellular Task!");
            delay(10);
      }
}