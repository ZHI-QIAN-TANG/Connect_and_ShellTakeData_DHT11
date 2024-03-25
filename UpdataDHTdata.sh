#!/bin/bash
HTData= HTData.txt
data= curl -L https://script.google.com/macros/s/AKfycbz8ZkHWngYTZ-KLWl-dK1Pk3St4NUlcVN7ueogBjvIRcpLMouWdzU7AbWKypkaAhYuF_g/exec > DHTata

cat << EOF > creatEexcel.py
import xlsxwriter
import ast
workbook = xlsxwriter.Workbook('DHTdata.xlsx')
worksheet = workbook.add_worksheet()
f = open('HTData','r')
allData = f.read()
allDataList = ast.literal_eval(allData)
for i in range(len(allDataList)):
	worksheet.write('A{}'.format(i+1),str(allDataList[i][0]))
	worksheet.write('B{}'.format(i+1),str(allDataList[i][1]))
	worksheet.write('C{}'.format(i+1),str(allDataList[i][2]))
	worksheet.write('D{}'.format(i+1),str(allDataList[i][3]))
f.close()
workbook.close()
EOF
python3 creatEexcel.py
rm creatEexcel.py
#gedit HTData.txt


