cc = g++  # use g++ compiler
path = ..
standard = c++2a

flags = -std=$(standard) 
flags += -Wall  
flags += -pedantic  
flags += -I $(path)  
flags += -g  

link = $(cc) $(flags) -o  

compile = $(cc) $(flags) -c -o  


all = client server


# executables
#
client : client.o socket.o calculator.o
	$(link) $@ $^
#
server : server.o socket.o filereader.o
	$(link) $@ $^


# objects
#
client.o : src/text-client.cc include/text-client.h \
                         include/socket.h
	$(compile) $@ $<
#
server.o : src/text-server.cc include/text-server.h \
                         include/socket.h include/filereader.h
	$(compile) $@ $<
#
socket.o : src/socket.cc include/socket.h
	$(compile) $@ $<

filereader.o : src/filereader.cc include/filereader.h
	$(compile) $@ $<

calculator.o : src/calculator.cc include/calculator.h
	$(compile) $@ $<

clean:
	$(RM) *.o $(all)