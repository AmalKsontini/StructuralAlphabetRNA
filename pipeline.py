
import os, sys


pdbdatafile=sys.argv[1]
result_file = sys.argv[1]

cmd1 = "./listeArns1/my_RNAAssessment/src/angle_calc -d ~/Documents/listeArns1/my_RNAAssessment/src/ -l ./listeArns1/my_RNAAssessment/src/"+pdbdatafile+" -o ./Projet_AmalK/testlecturefichier/"+result_file+" -RA"
cmd2 = "./Projet_AmalK/testlecturefichier/a.out -f ./Projet_AmalK/testlecturefichier/cluster.txt -r ./Projet_AmalK/testlecturefichier/"+result_file+".txt"

os.system(cmd1)
os.system(cmd2)


