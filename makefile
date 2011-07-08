project.exe: Single_list_int_driver.o
	g++ Single_list_int_driver.o -o project.exe

Single_list_int_driver.o: ece250.h Exception.h Single_list_int_driver.cpp Single_list_tester.h Single_list.h Single_node_tester.h Single_node.h Tester.h 
	g++ -c Single_list_int_driver.cpp

clean: 
	rm -f project.exe *.o *~ *#

run: 
	./project.exe<int.in
