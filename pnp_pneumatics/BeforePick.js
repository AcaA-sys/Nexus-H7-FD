var P_LEVELS = {"0201":"920", "0402":"880", "1206":"650", "STRONG":"470", "DEFAULT":"750"};
var nozzle = event.getNozzle();
var partId = event.getPlacement().getPart().getId();
var driver = machine.getDefaultDriver();
var nozzleNum = nozzle.getName().match(/\d+/) || "1";

if (nozzle.getPart() == null) {
    var targetP = P_LEVELS["DEFAULT"];
    if (partId.match(/0201/i)) targetP = P_LEVELS["0201"];
    else if (partId.match(/0402|0603/i)) targetP = P_LEVELS["0402"];
    else if (partId.match(/TQFP|BGA|QFP/i)) targetP = P_LEVELS["STRONG"];
    
    driver.sendCommand("M610 S1 P" + targetP + " N" + nozzleNum);
}
