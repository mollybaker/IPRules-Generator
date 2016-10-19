IPRulesGen: IPRulesGen.o
	c++ -o IPRulesGen IPRulesGen.o

IPRulesGen.o: IPRulesGen.cpp IPRulesGen.h  
	c++ -c IPRulesGen.cpp 

clean: 
	$(RM) IPRulesGen IPRulesGen.o
