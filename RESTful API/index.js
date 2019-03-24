//express freamwork
const express = require('express');

const bodyParser = require('body-parser');

const app = express();


app.use(bodyParser.urlencoded({ extended: false }));
app.set('view engine', 'ejs');

app.listen(3000);

app.get('/', function (req, res) { });