var ss = SpreadsheetApp.openById("YOUR_SPREADSHEET_ID");
var sheet = ss.getSheetByName("Sheet1");

// GET → read current stock
function doGet(e) {
  var rice  = sheet.getRange("A2").getValue();
  var wheat = sheet.getRange("B2").getValue();
  var sugar = sheet.getRange("C2").getValue();

  var data = {
    rice: rice,
    wheat: wheat,
    sugar: sugar
  };

  return ContentService
    .createTextOutput(JSON.stringify(data))
    .setMimeType(ContentService.MimeType.JSON);
}

// POST → update stock from ESP8266
function doPost(e) {
  var params = JSON.parse(e.postData.contents);

  if (params.rice  !== undefined) sheet.getRange("A2").setValue(params.rice);
  if (params.wheat !== undefined) sheet.getRange("B2").setValue(params.wheat);
  if (params.sugar !== undefined) sheet.getRange("C2").setValue(params.sugar);

  // Update timestamp
  sheet.getRange("D2").setValue(new Date());

  return ContentService
    .createTextOutput(JSON.stringify({ status: "ok" }))
    .setMimeType(ContentService.MimeType.JSON);
}