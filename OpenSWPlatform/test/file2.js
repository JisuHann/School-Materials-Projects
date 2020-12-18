var url = require('url');
var http = require('http');
var fs = require('fs');

http.createServer(function(request, response){
    var pathname = url.parse(request.url).pathname;
    fs.readFile(pathname.substr(1), function(err, data){
        if(err){
            response.writeHead(404, 'Content-Type: {text/html}');
        }else{
            response.writeHead(404, 'Content-Type: {text/html}');
            response.write(data.toString());
        }
        response.end("Hello World\n");
    });
}).listen(8081);