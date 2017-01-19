author: Jianye Liu 
Student ID: 104522497

fibonacci.sh will calcuate the fibonacci number. It should run with the number you want to calcuate. 

for example: 10 fibonacci

cd /the/path/of/the/fibonacci.sh
./fibonacci.sh 10

0 1 1 2 3 5 8 13 21 34 55
the fibonacci of 10 is 55

you will get two line output, where the first is show all the fibonacci from 0 to the number. and the second line is to show the final result.

we assume you would not calculate extreme large number.


minimize.sh is to compress file with specific extensions in current directory such as doc, jpg. and the output will be compress.tar.

for example compress all files with jpg or doc extension in current directory. 

cd /the/path/of/the/minimize.sh
./minimize.sh jpg doc

handling files with extension doc
file1.doc
file2.doc
file3.doc
done

handling files with extension jpg
file1.jpg
file2.jpg
file3.jpg
done

if the compress.tar file exists, this script will remove this old file. the output will look like this.

remove old file compress.tar
handling files with extension doc
file1.doc
file2.doc
file3.doc
done

handling files with extension jpg
file1.jpg
file2.jpg
file3.jpg
done