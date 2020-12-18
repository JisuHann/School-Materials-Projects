var cat = require('./cat');
var url = require('url');
var fs = require('fs');
var http = require('http');

http.createServer(function(request, response){
    var pathname = url.parse(request.url).pathname;
    fs.readFile(pathname.substr(1), function(error, data){
        if(error){
            response.writeHead(404, {'Content-Type': 'text/html'});
            console.log("error");
        }else{
            response.writeHead(404, {'Content-Type': 'text/html'});
            response.write(data.toString());
        }
        response.end();
    })
}).listen(8081);