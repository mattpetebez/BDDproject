import sys
import cgi
import cgitb
import subprocess

username = sys.argv[1]
password = sys.argv[2]
requestType = sys.argv[3]

subprocess.call("./UserViewFileRules "+username+" "+password, shell=True) 
subprocess.call("./shutdown Larry",shell=True)
print("Location://UserRulesFiles/"+username+"-FileRules.html")
print
