#Compile the code
# if the file densemult exits then remove it
if [ -f btree ]; then
    rm btree
fi
g++ -std=c++11 *.cpp -o btree
# if the file densemult does not exit then exit the test
if [ ! -f btree ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
if [ -f *.out ]; then
    rm *.out
fi
if [ -f *.stderr ]; then
    rm *.stderr
fi
if [ -f *.stdcout ]; then
    rm *.stdcout
fi
#rm *.out *.stderr *.stdcout
# For test case 1
# input 1.txt and output 1.out
./btree "input=input71.txt;output=output71.txt;command=command71.txt" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans71.txt output71.txt > 1.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 1    \033[1;91mFAILED.\033[0m"
else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 1    \033[1;92mPASSED.\033[0m"
    # remove the file 1.diff
    rm -f 1.diff
fi
# For test case 2
./btree "input=input72.txt;output=output72.txt;command=command72.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans72.txt output72.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
# For test case 3
./btree "input=input73.txt;output=output73.txt;command=command73.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans73.txt output73.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi
# For test case 4
./btree "input=input74.txt;output=output74.txt;command=command74.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans74.txt output74.txt > 4.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 4    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 4    \033[1;92mPASSED.\033[0m"
    rm -f 4.diff
fi
# For test case 5
./btree "input=input75.txt;output=output75.txt;command=command75.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans75.txt output75.txt > 5.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 5    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 5    \033[1;92mPASSED.\033[0m"
    rm -f 5.diff
fi
# For test case 6
./btree "input=input76.txt;output=output76.txt;command=command76.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans76.txt output76.txt > 6.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 6    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 6    \033[1;92mPASSED.\033[0m"
    rm -f 6.diff
fi
# For test case 7
./btree "input=input77.txt;output=output77.txt;command=command77.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans77.txt output77.txt > 7.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 7    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 7    \033[1;92mPASSED.\033[0m"
    rm -f 7.diff
fi
# For test case 8
./btree "input=input78.txt;output=output78.txt;command=command78.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans78.txt output78.txt > 8.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 8    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 8    \033[1;92mPASSED.\033[0m"
    rm -f 8.diff
fi
# For test case 9
./btree "input=input79.txt;output=output79.txt;command=command79.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans79.txt output79.txt > 9.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 9    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 9    \033[1;92mPASSED.\033[0m"
    rm -f 9.diff
fi
# For test case 10
./btree "input=input80.txt;output=output80.txt;command=command80.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans80.txt output80.txt > 10.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 10    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 10    \033[1;92mPASSED.\033[0m"
    rm -f 10.diff
fi
