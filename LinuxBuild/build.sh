BuildDirectory="./Build"
CMakeDirectory="./"
EnvDirectory="../Env"
ExeName="Main"

mkdir $BuildDirectory
cd $BuildDirectory

cmake ../${CMakeDirectory}
make

cp -f -p $ExeName ../${EnvDirectory}/$ExeName
