const mysql = require("../database/db");
const constants = require("../constants")



/**
  * Endpoint #1. getLogAire
  * 
  * Este método realiza un select de todos los registros ubicados en
  * una tabla llamada calidad_aire.
  * 
  * Resultado: Obtendrá todos los registros de la tabla calidad_aire 
  * Todas las columnas están contempladas. 
  * 
  * Puedes sustituirla utilizando una proyección a tu tabla incluyendo las columnas que necesites.
  * 
  * Te servirá para crear reportes especializados si utilizas algún metodo de despliegue web para los
  * Dashboards.
  */
async function getLogAire(req,res){
  try{

    var sql = constants.selectAir;
    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        conn.query(sql, (error, data, fields) => {
            if (error) {
              res.status(500);
              res.send(error.message);
            } else {
              console.log(data);
              res.json({
                data,
              });
            }
            conn.end();
        });
    });
  }catch(error){
    console.log(error)
    res.status(500)
    res.send(error)
  }
}


/**
  * Endpoint #2. getLogByDateBetween
  * 
  * Este método realiza un select de todos los registros ubicados en
  * una tabla llamada calidad_aire que se encuentren entre dos fechas.
  * 
  * Resultado: Obtendrá todos los registros de la tabla calidad_aire 
  * Todas las columnas están contempladas. Se regresa solo los valores generados entre dos fechas
  * 
  * Puedes sustituirla utilizando una proyección a tu tabla incluyendo las columnas que necesites.
  * 
  * Te servirá para crear reportes especializados si utilizas algún metodo de despliegue web para los
  * Dashboards.
  */
async function getLogByRoom(req,res){
  try{
    var sql = constants.selectAirByRoom;

    var id_cuarto = req.body.id_cuarto;

    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        var params = [id_cuarto];
        conn.execute(sql, params, (error, data, fields) => {
            if (error) {
              res.status(500);
              res.send(error.message);
            } else {
              console.log(data);
              res.json({
                data,
              });
            }
            conn.end();
        });
    });
  }catch(error){
    console.log(error)
    res.status(500)
    res.send(error)
  }
  
}



/**
  * Endpoint #3. insertLogAire
  * 
  * Este método realiza un insert sobre la tabla calidad_aire.
  * Deberás enviar todos los datos desde tu sensor a este endpoint.
  * 
  * Sustituye:
  *    1. El nombre de tu tabla.
  *    2. Las columnas correspondientes a tu tabla en la Base de Datos.
  *    3. Realiza el insert
  * 
  * Consideraciones:
  *   a. Solo se especificaron 2 columnas (el valor leido, y por fecha de registro se indica la fecha actual al momento.)
  *   b. Debes sustituir los valores de las columnas de tu tabla
  *   c. Si tienes un id que no se autogenere, deberás enviarlo tambien
  *  
  */
async function insertLogAire(req,res){
  try{

    var sql = constants.insertAir;

    //el valor se recibe en el cuerpo de correo
    //cualquier dato que vaya a ir en el insert deberás guardarlo en una variable local
    var id_cuarto = req.body.id_cuarto;
    var ppm = req.body.ppm;

    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;

        // así mismo, cualquier dato que vaya a insertarse, deberá incluirse en
        // los valores de los parámetros del Insert
        var params = [id_cuarto,ppm]; 
        conn.execute(sql, params, (error, data, fields) => {
            if (error) {
              res.status(500);
              res.send(error.message);
            } else {
              console.log(data);
              res.json({
                status: 200,
                message: "Valor insertado",
                affectedRows: data.affectedRows,
              });
            }
            conn.end();
        });
    });

  }catch(error){
    console.log(error)
    res.status(500)
    res.send(error)
  }
  
}



module.exports = {insertLogAire, getLogAire,getLogByRoom};
