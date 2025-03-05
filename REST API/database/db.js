const mysql = require('mysql2');
var fs = require("fs");
const constants = require("../constants")



/**
 * Método que configura un objeto conexión y lo regresa a quien lo solicite.
 */
function getConnection(){
  const connection = mysql.createConnection({
    host: constants.dbHost,
    user: constants.dbUser,
    port: constants.dbPort,
    password: constants.dbPass,
    database: "defaultdb",
    dateStrings: true, 
  });

  return connection;
}

module.exports = {getConnection};
