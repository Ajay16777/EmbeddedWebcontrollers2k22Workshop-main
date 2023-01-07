import express from 'express';
import mongoose from 'mongoose';
import insertTest from './database/mongobase.js'


// #endregion

// #region Variables
const APP = express();
const PORT = 2022;
let sensorData = [];
// #endregion

// #region EXPRESS CODE
// ---------------------------------------
APP.use("/", express.static("../client/dashboard"));

/* ---ACTIVATE MIDDLEWARE--- */
APP.use(express.json());

/* ---MONGOOSE--- */
mongoose.connect("mongodb://localhost:27017/sensorData");


/* ---ENDPOINTS--- */
APP.get("/getData", (req, res) => {
    res.send(JSON.stringify(sensorData));
});


//http://192.168.0.4:2022/update-sensor
APP.post("/update-sensor", async (req, res) => {
    
    req.body =  { "temperature": 23, "humidity": 45, "altitude": 67, "pressure": 89}
    console.log(req.body);
    insertTest(req.body)
        .then((result) => {
            res.send(result)
        }
    )
    .catch(console.error)
    .finally(() => CLIENT.close());
});


/* ---START SERVER--- */
APP.listen(PORT, () => {
    console.log(`App running at http://localhost:${PORT}`);
});

// ---------------------------------------
// #endregion