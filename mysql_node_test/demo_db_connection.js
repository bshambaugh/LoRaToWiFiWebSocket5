var mysql = require('mysql');
let sql = "SHOW DATABASES";
let lux = '29';

// https://stackoverflow.com/questions/10645994/how-to-format-a-utc-date-as-a-yyyy-mm-dd-hhmmss-string-using-nodejs
let dt = new Date().toISOString().
  replace(/T/, ' ').      // replace T with a space
  replace(/\..+/, '')     // delete the dot and everything after

sql = 'INSERT INTO BH1750 VALUES (NULL, '+lux +', '+'\''+ dt+'\')';

console.log(sql);

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "password",
  database: "scandalux"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
  con.query(sql, function (err, result) {
    if (err) throw err;
    console.log("Result: " + JSON.stringify(result));
  });
});
