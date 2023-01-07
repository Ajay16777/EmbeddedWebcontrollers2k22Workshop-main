# EmbeddedWebcontrollers2k22Workshop



//////////////////////////////
const testConnection = async () => {
    await CLIENT.db("admin").command({ ping: 1 });
    console.log("Connected successfully to MongoDB");
    return "MongoDB insertion test succesful";
}
const insertTest = async (temp,humidity,pressure,altitude) => {
    await CLIENT.connect();
    await testConnection().then((res => { console.log(res) }))
    let newElement = {
        "Temperature": temp,
        "humidity": humidity,
        "pressure": pressure, 
        "altitude": altitude, 
        "stamp": new Date()
    }
    const insertResult = await DB.insertMany([newElement]);
    return insertResult;
}
const insertEntry = async (value) => {
    await CLIENT.connect();
    const insertResult = await DB.insertMany([value]);
    return insertResult;
}
const findTest = async () => {
    await CLIENT.connect();
    const findResult = await DB.find({ "age": 24 }).toArray();
    // const findResult = await DB.find({
    //  name: "Lemony Snicket",
    //  date: {
    //      $gte: new Date(new Date().setHours(00, 00, 00)),
    //      $lt: new Date(new Date().setHours(23, 59, 59)),
    //  },
    // });
    return findResult;
}
const findEntry = async (param) => {
    await CLIENT.connect();
    const findResult = await DB.find(param).toArray(); // { "afe": { "$exists": true } }
    return findResult;
}
////////////
//#endregion

//#region // ROUTER END POINTS //
/////////////////////////////////
GO.route('/insert')
    .get((req, res) => {
        insertTest(req.params.entry)
            .then((result) => {
                res.send(result)
            })
            .catch(console.error)
            .finally(() => CLIENT.close());
    })
    .post(X.json(),(req, res) => {
        insertEntry(req.body)
            .then((result) => {
                res.send(result)
            })
            .catch(console.error)
            .finally(() => CLIENT.close());
    })
GO.route('/query/:param?')
    .get((req, res) => {
        findTest()
            .then(
                (x) => {
                    res.send(x);
                }
            )
            .catch(console.error)
            .finally(() => CLIENT.close());
    })
    .post(X.json(),(req, res) => {
        findEntry(req.body)
            .then(
                (x) => {
                    res.send(x);
                }
            )
            .catch(console.error)
            .finally(() => CLIENT.close());
    });
////////////
//#endregion

module.exports = GO;