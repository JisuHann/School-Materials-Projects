var http = require('http');
var fs = require('fs');
var url = require('url');


// 서버 생성
http.createServer( function (request, response) { 
   var pathname = url.parse(request.url).pathname;

   fs.readFile(__dirname.toString()+pathname, function (err, data) {
      if (err) {
         console.log(err);
         response.writeHead(404, {'Content-Type': 'text/html'});
      }else{	
         console.log("okay");
         response.writeHead(200, {'Content-Type': 'text/html'});	
         response.write(data.toString());		
      }
      
      response.end();
   });   
}).listen(8081);


console.log('Server running at http://127.0.0.1:8081/');