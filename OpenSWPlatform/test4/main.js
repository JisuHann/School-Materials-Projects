var cat = require('./cat');
var http = require('http');
var url = require('url');
var fs = require('fs');
console.log(cat.sayHello());
http.createServer(function(request, response){
    var pathname = url.parse(request.url).pathname;

    fs.readFile(pathname.substr(1), function(error, data){
        if(error){
            console.log("error");
            response.writeHead(404, {'Content-Type': 'text/html'});
        }
        else{
            response.writeHead(200, {'Content-Type':'text/html'});
            response.write(data.toString());
        }
        response.end();
    });
}).listen(8080);