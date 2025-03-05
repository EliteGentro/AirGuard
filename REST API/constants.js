
/*
 * LOCAL DATABASE Config
 *  DELETED FOR GITHUB REPO
 */




/*
 * Server General Configuration
 */
const serverPort = 3000
const contextURL = '/iot'; //If needed, project context
const api = '/api'; // Sugested API URL

//SENSOR 1 URLS. Configurar URLS por cada sensor.
const getTemperatureSensor = '/getTemperatures'
const getTemperatureSensorByDate = '/getTemperatures'
const postTemperatureSensor = '/insertTemperature'; //Implemented Endpoint URL

const getAirSensor = '/getAir';
const getAirSensorByRoom = '/getAir';
const postAirSensor = '/insertAir'; 

const getRegistros = '/getRegistros';
const getRegistrosByRoom = '/getRegistros';
const postRegistro = '/insertRegistro'; 
const getRange = '/getRange';
const changeRange = '/changeRange';


/*
 * DB Queries
 */
const selectTemperature = 'SELECT * FROM temps';
const selectTemperatureByDate = 'SELECT * FROM temps WHERE fecha between ? and ?';
const insertTemperature = 'INSERT INTO temps (valor) values (?)';

const selectAir = 'SELECT * FROM calidad_aire';
const selectAirByRoom = 'SELECT * FROM calidad_aire WHERE id_cuarto = ?';
const insertAir = 'INSERT INTO calidad_aire (id_cuarto, ppm) VALUES (?,?)';

const selectRegistros = 'SELECT * FROM registros';
const selectRegistrosByRoom = 'SELECT {sensor} FROM registros WHERE id_cuarto = ?'; //{"sensor": temp/humedad/calidad, "id_cuarto":1/2/3}
const insertRegistro = 'INSERT INTO registros (id_cuarto, temp, humedad, calidad) VALUES (?,?,?,?)'; //{"id_cuarto":1/2/3, "temp":x,"humedad":x,"calidad":x}
const selectRange = 'SELECT minimum, maximum FROM valores WHERE id_cuarto = ? AND sensor = ?'; //{"sensor": temp/humedad/calidad, "id_cuarto":1/2/3}
const modifyRange = 'UPDATE valores SET minimum = ? , maximum = ? WHERE id_cuarto = ? AND sensor = ?'; //{"minimum": x, "maximum":x, "sensor": temp/humedad/calidad, "id_cuarto":1/2/3}


module.exports= {
   dbHost,dbPort,dbUser,dbPass,dbName,serverPort, contextURL,api,getTemperatureSensor,
   getTemperatureSensorByDate,postTemperatureSensor,selectTemperature,selectTemperatureByDate,insertTemperature,
   getAirSensor, getAirSensorByRoom, postAirSensor, selectAir, selectAirByRoom, insertAir, getRegistros, 
   getRegistrosByRoom, postRegistro, getRange, selectRegistros, selectRegistrosByRoom, insertRegistro, selectRange,
   changeRange, modifyRange
}