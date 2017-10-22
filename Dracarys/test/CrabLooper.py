import commands as cmd
import sys
import time

if len(sys.argv) < 2:
    raise Exception("You need to give a command and a folder to Crab Looper")

CrabFolder = sys.argv[1]
CrabAction = sys.argv[2]

ITime=time.localtime()
StringITime=str(ITime.tm_year)+'_'+str(ITime.tm_mon)+'_'+str(ITime.tm_mday)+'_'+str(ITime.tm_hour)+'_'+str(ITime.tm_min)
print "Starting Crab Looper! at "+StringITime

ListOfFolders=cmd.getoutput('ls '+CrabFolder)
ListOfFolders=ListOfFolders.split('\n')

for i in ListOfFolders:
    if 'crab' not in i: continue
    print 'Executing action over: '+i
    CrabOutput = cmd.getoutput('crab '+CrabAction+' -d '+CrabFolder+'/'+i)
    print CrabOutput
    print '---------------------------------------------------------------------------------------------------------------'
