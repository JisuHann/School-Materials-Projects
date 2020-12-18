var md = require('./myfirstmodule');
console.log(md.Date());

var http = require('http');
var fs = require('fs');
var url = require('url');

http.createServer(function(request, response){
    response.writeHead(200, {'Content-Type':'text/plain'});
    response.end("The date and time are currrently: "+md.Date());
}).listen(8080);

console.log('Server running at http://127.0.0.1:8080/');