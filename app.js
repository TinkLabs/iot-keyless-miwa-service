var express = require('express');
var cmd = require('node-cmd');
var Promise = require('bluebird');
var validator = require('validator');
var empty = require('is-empty');
var dateFormat = require('dateformat');
let dotenv = require('dotenv');
dotenv.config('./.env');

var app = express();

var Sentry = require('@sentry/node');
Sentry.init({
  dsn: process.env.SENTRY_DSN,
  environment: process.env.NODE_ENV,
});

app.get('/', function (req, res) {
  const getAsync = Promise.promisify(cmd.get, { multiArgs: true, context: cmd })
  var hotelCode = req.query.hotelCode;
  var hotelSecret = req.query.hotelSecret;
  var cardType = req.query.cardType;
  var issueNumber = req.query.issueNumber;
  var numOfCardIssue = req.query.numOfCardIssue;
  var checkInDate = req.query.checkInDate;
  var checkOutDate = req.query.checkOutDate;
  var summerTimeFlag = empty(req.query.summerTimeFlag) ? 0 : req.query.summerTimeFlag;
  var shutOutFlag = empty(req.query.shutOutFlag) ? 0 : req.query.shutOutFlag;
  var buzzerFlag = empty(req.query.buzzerFlag) ? 0 : req.query.buzzerFlag;
  var deadboltOverrideFlag = empty(req.query.deadboltOverrideFlag) ? 0 : req.query.deadboltOverrideFlag;
  var mainRoomNo = req.query.mainRoomNo;
  var assoRoom1 = empty(req.query.assoRoom1) ? "0" : req.query.assoRoom1;
  var assoRoom2 = empty(req.query.assoRoom2) ? "0" : req.query.assoRoom2;
  var assoRoom3 = empty(req.query.assoRoom3) ? "0" : req.query.assoRoom3;
  var assoRoom4 = empty(req.query.assoRoom4) ? "0" : req.query.assoRoom4;
  var assoRoom5 = empty(req.query.assoRoom5) ? "0" : req.query.assoRoom5;

  if (empty(hotelCode) || !validator.isHexadecimal(hotelCode) || !validator.isLength(hotelCode, { min: 8, max: 8 })) {
    res.statusCode = 403;
    res.send('Parameters not match');
    return;
  }

  if (empty(hotelSecret) || !validator.isLength(hotelSecret, { min: 14, max: 14 })) {
    res.statusCode = 403;
    res.send('Please enter correct hotel secret');
    return;
  }

  if (empty(cardType) || !validator.isLength(cardType, { min: 3, max: 3 })) {
    res.statusCode = 403;
    res.send('Please enter correct cardType');
    return;
  }

  if (empty(issueNumber) || !validator.isInt(issueNumber, { min: 1, max: 255 })) {
    res.statusCode = 403;
    res.send('Please enter correct issueNumber');
    return;
  } else {
    issueNumber = issueNumber.padStart(3, "0");
  }

  if (empty(numOfCardIssue) || !validator.isInt(numOfCardIssue, { min: 1, max: 255 })) {
    res.statusCode = 403;
    res.send('Please enter correct numOfCardIssue');
    return;
  } else {
    numOfCardIssue = issueNumber.padStart(3, "0");
  }

  if (empty(checkInDate) || !validator.isISO8601(checkInDate)) {
    res.statusCode = 405;
    res.send('Please enter correct checkInDate');
    return;
  } else {
    var date = new Date(checkInDate);
    var timeZoneOffset = date.getTimezoneOffset() * 60000;
    date = new Date(date.getTime() + timeZoneOffset);
    checkInDate = dateFormat(date, "yymmddHHMM");
  }

  if (empty(checkOutDate) || !validator.isISO8601(checkOutDate)) {
    res.statusCode = 403;
    res.send('Please enter correct checkOutDate');
    return;
  } else {
    var date = new Date(checkOutDate);
    var timeZoneOffset = date.getTimezoneOffset() * 60000;
    date = new Date(date.getTime() + timeZoneOffset);
    checkOutDate = dateFormat(date, "yymmddHH");
  }

  if (empty(mainRoomNo) || !validator.isInt(mainRoomNo, { min: 0, max: 999999 })) {
    res.statusCode = 403;
    res.send('Please enter correct mainRoomNo');
    return;
  } else {
    mainRoomNo = mainRoomNo.padStart(6, "0")
  }

  if (!validator.isInt(assoRoom1, { min: 0, max: 999999 })) {
    res.statusCode = 403;
    res.send('Please enter correct assoRoom1');
    return;
  } else {
    assoRoom1 = assoRoom1.padStart(6, "0")
  }

  if (!validator.isInt(assoRoom2, { min: 0, max: 999999 })) {
    res.statusCode = 403;
    res.send('Please enter correct assoRoom2');
    return;
  } else {
    assoRoom2 = assoRoom2.padStart(6, "0")
  }

  if (!validator.isInt(assoRoom3, { min: 0, max: 999999 })) {
    res.statusCode = 403;
    res.send('Please enter correct assoRoom3');
    return;
  } else {
    assoRoom3 = assoRoom3.padStart(6, "0")
  }

  if (!validator.isInt(assoRoom4, { min: 0, max: 999999 })) {
    res.statusCode = 403;
    res.send('Please enter correct assoRoom4');
    return;
  } else {
    assoRoom4 = assoRoom4.padStart(6, "0")
  }

  if (!validator.isInt(assoRoom5, { min: 0, max: 999999 })) {
    res.statusCode = 403;
    res.send('Please enter correct assoRoom5');
    return;
  } else {
    assoRoom5 = assoRoom5.padStart(6, "0")
  }

  var pInf = cardType +
    issueNumber +
    numOfCardIssue +
    ',' +
    checkInDate +
    ',' +
    checkOutDate +
    ',' +
    summerTimeFlag +
    shutOutFlag +
    buzzerFlag +
    deadboltOverrideFlag +
    ',' +
    mainRoomNo +
    ',' +
    assoRoom1 +
    assoRoom2 +
    assoRoom3 +
    assoRoom4 +
    assoRoom5;

  var command_miwa = 'Miwa ' + hotelCode + ' ' + hotelSecret + ' ' + pInf + ' ' + '00000000';
  console.log(command_miwa);

  getAsync(command_miwa).then(data => {
    res.setHeader('Content-Type', 'application/json');
    res.send(data[0]);
  }).catch(err => {
    res.send(data);
  })
});

app.use(Sentry.Handlers.errorHandler());
app.use((err, req, res, next) => {
  res.status(500).end(`${res.sentry}\n`);
});

app.listen(3010, function () {
  console.log('Miwa_RESTful listening on port 3010!');
});
