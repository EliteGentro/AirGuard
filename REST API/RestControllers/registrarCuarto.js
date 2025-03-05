const mysql = require("../database/db");
const constants = require("../constants")



async function getLogRegistros(req,res){
  try{

    var sql = constants.selectRegistros;
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

async function getLogByRoom(req,res){
  try{
    var sql = constants.selectRegistrosByRoom;

    var sensor =req.body.sensor;
    var id_cuarto = req.body.id_cuarto;

    sql = sql.replace('{sensor}', sensor);
    console.log(sql);
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

async function insertLogRegistro(req,res){
  try{

    var sql = constants.insertRegistro;

    //el valor se recibe en el cuerpo de correo
    //cualquier dato que vaya a ir en el insert deberás guardarlo en una variable local
    var id_cuarto = req.body.id_cuarto;
    var temp = req.body.temp;
    var humedad = req.body.humedad;
    var calidad = req.body.calidad;

    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;

        // así mismo, cualquier dato que vaya a insertarse, deberá incluirse en
        // los valores de los parámetros del Insert
        var params = [id_cuarto,temp, humedad, calidad]; 
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

async function getRangeValues(req,res){
  try{
    var sql = constants.selectRange;

    var sensor =req.body.sensor;
    var id_cuarto = req.body.id_cuarto;

    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;
        var params = [id_cuarto, sensor];
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

async function modifyRangeValues(req,res){
  try{

    var sql = constants.modifyRange;

    //el valor se recibe en el cuerpo de correo
    //cualquier dato que vaya a ir en el insert deberás guardarlo en una variable local
    var minimum = req.body.minimum;
    var maximum = req.body.maximum;
    var sensor = req.body.sensor;
    var id_cuarto = req.body.id_cuarto;

    var conn = mysql.getConnection();
    conn.connect((error)=>{
        if (error) throw error;

        // así mismo, cualquier dato que vaya a insertarse, deberá incluirse en
        // los valores de los parámetros del Insert
        var params = [minimum, maximum, id_cuarto, sensor]; 
        conn.execute(sql, params, (error, data, fields) => {
            if (error) {
              res.status(500);
              res.send(error.message);
            } else {
              console.log(data);
              res.json({
                status: 200,
                message: "Valor Modificado",
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


module.exports = {getLogRegistros, getLogByRoom, insertLogRegistro, getRangeValues, modifyRangeValues};
