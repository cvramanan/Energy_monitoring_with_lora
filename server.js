var nodemailer = require('nodemailer');
const SerialPort = require('serialport')




var transporter = nodemailer.createTransport({
  service: 'gmail',

  auth: {
    user: 'santhiya40035@gmail.com',
    pass: 'varatharaj'
  }
});


const port = new SerialPort('/dev/ttyACM0', {
  baudRate: 9600
} ,  function (err) {
  if (err) {
    return console.log('Error: ', err.message)
  }
})
port.on('data', function (data) {
  console.log('Data:', String(data))
//sending email
var mailOptions = {
  from: 'santhiya40035@gmail.com',
  to: 'santhiyavaratharasu@gmail.com',
  subject: 'Energy reading invoice',
  text: "-------------------------\n"+
  "SSS Energies corp"+
  String(data)*9+ // energy unit cost
  "\n------------------------------"
};
//Email response
transporter.sendMail(mailOptions, function(error, info){
  if (error) {
    console.log(error);
  } else {
    console.log('Email sent: ' + info.response);
  }
});
})
