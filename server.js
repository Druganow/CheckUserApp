const users = require('bindings')('CheckUserApp')
const express = require("express");
const app = express();
const urlencodedParser = express.urlencoded({extended: false});

let data = users.GetUsersList().split('@');

app.get("/", function (request, response) {
    response.sendFile(__dirname + "/index.html");
});

app.get("/main", function (request, response) {
    response.sendFile(__dirname + "/index.html");
});

app.post("/", urlencodedParser, function (request, response) {
	if (!request.body) return response.sendStatus(400);

	if (data.includes(request.body.userName)) {
		response.send(`<h2>Пользователь ${request.body.userName} есть</h2><form action="/main"><input type="submit" value="Назад"></form>`);
	}
	else {
		response.send(`<h2>Пользователя ${request.body.userName} нет</h2><form action="/main"><input type="submit" value="Назад"></form>`);
	}
});

app.listen(3000, ()=>console.log("Сервер запущен..."));
