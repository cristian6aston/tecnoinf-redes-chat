all : server client
server: server.cc
	g++ -o server server.cc
client: client.cc
	g++ -o client client.cc