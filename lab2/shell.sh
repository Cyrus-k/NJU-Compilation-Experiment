path="./Tests_1_Normal/Tests/inputs/"
files=$(ls $path)
for filename in $files
do
   echo -e "\n"$filename >> filename.txt
   ./parser $path$filename >> filename.txt
done


