
// https://stackoverflow.com/questions/10645994/how-to-format-a-utc-date-as-a-yyyy-mm-dd-hhmmss-string-using-nodejs
let dt = new Date().toISOString().
  replace(/T/, ' ').      // replace T with a space
  replace(/\..+/, '')     // delete the dot and everything after

let lux = '45'

sql = 'INSERT INTO BH1750 VALUES (NULL, '+lux +', '+'\''+ dt+'\')';

console.log(sql);
