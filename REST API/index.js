
//Incluye en tu proyecto las dependencias necesarias
const constants = require("./constants")
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const router = require('./route')


/**
 * Express Server.
 */
const app = express();
const port = constants.serverPort;


/** 
 * Configuración del servidor web.
 */
app.use(cors());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

/**
 * For endpoints routing
 */
app.use(router);

//arranque del server 
app.listen(port, () => {
    console.log('Server started running on : ' + port)
})