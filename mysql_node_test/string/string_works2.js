let dt = new Date().toISOString().
  replace(/T/, ' ').      // replace T with a space
  replace(/\..+/, '')     // delete the dot and everything after


let lux = '45678';

query = 'INSERT INTO BH1750 VALUES ( NULL, '+lux+', '+dt+' )';

console.log(query);
