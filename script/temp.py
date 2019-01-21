#!/usr/bin/python
import subprocess, sys

make_process = subprocess.Popen("make", stderr=subprocess.STDOUT)
print "Compiling......"
if make_process.wait() != 0:
	print "Make failed. Exiting..."
	sys.exit()
print "Compilation complete."

for itr in range(1,3):
	print "Executing for iteration : ", itr, " ......",
        prediction_process = subprocess.Popen(["./cnn_weights", str(itr)], stderr=subprocess.STDOUT)
	if prediction_process.wait() != 0:
		print "\nError occurred while executing cnn_weights for iteration ", str(itr)
		sys.exit()
        print "Success"
 	print "Executing for iteration : ", itr, " ......",
        prediction_process = subprocess.Popen(["./cnn_prediction", str(itr)], stderr=subprocess.STDOUT)
	if prediction_process.wait() != 0:
		print "\nError occurred while executing cnn_prediction for iteration ", str(itr)
		sys.exit()
        print "Success"
	
