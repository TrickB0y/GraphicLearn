cd ..

cmake --build .

mkdir "test-dir"

cd test-dir

del /F /Q *

cd ..

rmdir "test-dir"
mkdir "test-dir"

cd src

copy shader.frag "../test-dir/"
copy shader.vert "../test-dir/"

cd Debug

copy GraphicLearn.exe "../../test-dir/"

cd "../../test-dir"

explorer %cd%

cd ../src
