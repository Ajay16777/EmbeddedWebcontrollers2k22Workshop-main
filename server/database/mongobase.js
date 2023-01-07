import mongoose from 'mongoose';

//create a schema
const sensorSchema = new mongoose.Schema({
    temperature: Number,
    humidity: Number,
    altitude: Number,
    pressure: Number,
});

//create a model
const Sensor = mongoose.model("Sensor", sensorSchema);

//create function to insert data
const insertTest = async (data) => {
    try {
        const sensor = new Sensor(data);
        await sensor.save();
        console.log("Data inserted");
    } catch (error) {
        console.log(error);
    }
}

//create function to find data
const findTest = async () => {
    try {
        const data = await Sensor.find();
        console.log(data);
    } catch (error) {
        console.log(error);
    }
}

export default insertTest;
export { findTest };
