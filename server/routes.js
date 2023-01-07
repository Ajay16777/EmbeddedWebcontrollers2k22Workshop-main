const X = require('express');
const GO = X.Router();


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