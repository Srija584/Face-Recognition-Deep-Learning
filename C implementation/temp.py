#!/usr/bin/python
import subprocess, sys

num_persons = 23

make_process = subprocess.Popen("make", stderr=subprocess.STDOUT)
print "Compiling......"
if make_process.wait() != 0:
	print "Make failed. Exiting..."
	sys.exit()
print "Compilation complete."

for itr in range(1,num_persons+1):
	print "Executing for iteration : ", itr, " ......",
        prediction_process = subprocess.Popen(["./cnn_weights", str(itr)], stderr=subprocess.STDOUT)
	if prediction_process.wait() != 0:
		print "\nError occurred while executing cnn_weights for iteration ", str(itr)
		#sys.exit()
        print "Success"
 	# print "Executing for iteration : ", itr, " ......",
        # prediction_process = subprocess.Popen(["./cnn_prediction", str(itr)], stderr=subprocess.STDOUT)
	# if prediction_process.wait() != 0:
	# 	print "\nError occurred while executing cnn_prediction for iteration ", str(itr)
	# 	sys.exit()
        # print "Success"
	
for itr in range(1,num_persons+1):
	print "Executing prediction iteration : ", itr, " ......",
	for itr_sub in range(1, num_persons+1):
		prediction_process = subprocess.Popen(["./cnn_prediction", str(itr), str(itr_sub)], stderr=subprocess.STDOUT)
		if prediction_process.wait() != 0:
			print "\nError occurred while executing cnn_weights for iteration ", str(itr)
			#sys.exit()
		print "Success"
