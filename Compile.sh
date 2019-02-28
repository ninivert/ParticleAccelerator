# Compilation de Vector3D
g++ -c src/lib/Vector3D.cpp -o build/Vector3D.o -I ./

# Compilation des tests
g++ -c test/src/Vector3D.cpp -o test/build/Vector3D.o -I ./
g++ -c test/lib/Test.cpp -o test/build/Test.o -I ./

# Edition de liens
g++ test/build/Vector3D.o test/build/Test.o build/Vector3D.o  -o test/bin/Vector3D

