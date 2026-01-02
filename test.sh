#!bin/bash

./client $1 "$(<Minitalk_Test/text.txt)";
echo "send text 1"
./client $1 "$(<Minitalk_Test/text2.txt)";
echo "send text 2"
./client $1 "$(<Minitalk_Test/text3.txt)";
echo "send text 3"
./client $1 "$(<Minitalk_Test/text4.txt)";
echo "send text 4"
./client $1 "$(<Minitalk_Test/text5.txt)";
echo "send text 5"
./client $1 "$(<Minitalk_Test/text_foreign_language.txt)";
echo "send text foreign_language"
./client $1 "$(<Minitalk_Test/long.txt)";
echo "send text long"
./client $1 "$(<Minitalk_Test/joli.txt)";
echo "send text joli"
