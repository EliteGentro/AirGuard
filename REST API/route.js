/*
    Constants
 * 
 */
const constants = require("./constants")
const express = require('express');
const temperaturaController = require('./RestControllers/sensorTemperatura.js'); 
const aireController = require('./RestControllers/sensorAire.js'); 
const registroController = require('./RestControllers/registrarCuarto.js'); 
const router = express.Router();

router.get("/",function(req,res){
    res.send('<html><head><title>API IoT</title></head><body><h1>Hello World!</h1></body></html>');
});

/**
 * Get And Posts
 * 
 */
router.get(constants.contextURL + constants.api + constants.getTemperatureSensor, temperaturaController.getLogTemperatura);
router.post(constants.contextURL + constants.api + constants.getTemperatureSensorByDate, temperaturaController.getLogByDateBetween);
router.post(constants.contextURL + constants.api + constants.postTemperatureSensor,temperaturaController.insertLogTemperatura);

router.get(constants.contextURL + constants.api + constants.getAirSensor, aireController.getLogAire);
router.post(constants.contextURL + constants.api + constants.getAirSensorByRoom, aireController.getLogByRoom);
router.post(constants.contextURL + constants.api + constants.postAirSensor,aireController.insertLogAire);

router.get(constants.contextURL + constants.api + constants.getRegistros, registroController.getLogRegistros);
router.post(constants.contextURL + constants.api + constants.getRegistrosByRoom, registroController.getLogByRoom);
router.post(constants.contextURL + constants.api + constants.postRegistro,registroController.insertLogRegistro);
router.post(constants.contextURL + constants.api + constants.getRange,registroController.getRangeValues);
router.post(constants.contextURL + constants.api + constants.changeRange,registroController.modifyRangeValues);


//le decimos a Node que queremos hacer uso de nuestro router en otros archivos (como por ejemplo, app.js)
module.exports = router;