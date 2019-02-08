var nodemailer = require('nodemailer');

var transporter = nodemailer.createTransport({
  service: 'gmail',

  auth: {
    user: 'alphajack100@gmail.com',
    pass: '9999988888'
  }
});

var mailOptions = {
  from: 'alphajack100@gmail.com',
  to: 'c.venkataramanan1@gmail.com',
  subject: 'Sending Email using Node.js',
  text: 'That was easy!'
};

transporter.sendMail(mailOptions, function(error, info){
  if (error) {
    console.log(error);
  } else {
    console.log('Email sent: ' + info.response);
  }
});
