build: kary-tabesh-curve.cpp
	g++ -std=c++11 -o kary-tabesh-curve kary-tabesh-curve.cpp  -framework OpenGl -framework Glut

run: build
	./kary-tabesh-curve; rm ./kary-tabesh-curve

clean: ./kary-tabesh-curve
	rm ./kary-tabesh-curve
