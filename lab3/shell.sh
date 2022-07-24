path="./Tests/"
respath="./Result/"
files=$(ls $path)
for filename in $files
do
   ./parser $path$filename $respath$filename.ir
done

