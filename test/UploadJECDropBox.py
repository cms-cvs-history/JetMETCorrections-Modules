#! /usr/bin/env python
import os
import re
import sys
import subprocess

#******************   template file  **********************************
templateFile = open('templateForDropbox.txt', 'r')
fileContents = templateFile.read(-1)
print '--------------- TEMPLATE :  -----------------'
print fileContents
p1 = re.compile(r'TAGNAME')
p2 = re.compile(r'PRODNAME')

#******************   definitions  **********************************
ERA         = 'Summer09_7TeV_ReReco332'
TYPE_LIST   = ['JPT','Calo','PF']
ALGO_LIST   = ['IC5','AK5','AK7','KT4','KT6']
LEVEL_LIST  = ['L2Relative','L3Absolute']
FLAVOR_LIST = ['bJ','cJ','qJ','gJ','bT','cT','qT','gT']
PARTON_LIST = ['bJ','cJ','qJ','gJ','jJ','bT','cT','qT','tT']
#*********************************************************************

files = []


### L2+L3 Corrections
for ll in LEVEL_LIST: #loop for default corrections
  for aa in ALGO_LIST: #loop for jet algorithms
    for tt in TYPE_LIST: #loop for jet types
      if ((tt=='Calo') or (tt=='PF') or ((tt=='JPT') and ((aa=='IC5') or (aa=='AK5')))):
        ss = ll+'_'+aa+tt
        print ss 
        s1 = ss
        s2 = ERA + '_' + s1
        k1 = p1.sub( s1, fileContents )
        k2 = p2.sub( s2, k1 )
        k2outfile = s2 + '.txt'
        print '--------------------------------------'
        print 'ORCOFF File for jet correction : ' + s1
        print 'Written to ' + k2outfile
        FILE = open(k2outfile,"w")
        FILE.write(k2)        
        files.append( k2outfile )


        
### L5 Corrections
for ff in FLAVOR_LIST: #loop over flavor correction options
  ss = 'L5Flavor_IC5Calo_'+ff
  s1 = ss
  s2 = ERA + '_' + s1
  k1 = p1.sub( s1, fileContents )
  k2 = p2.sub( s2, k1 )
  k2outfile = s2 + '.txt'
  print '--------------------------------------'
  print 'ORCOFF File for jet correction : ' + s1
  print 'Written to ' + k2outfile
  FILE = open(k2outfile,"w")
  FILE.write(k2)        
  files.append( k2outfile )


### L7 Corrections
for pp in PARTON_LIST: #loop over flavor correction options
  for aa in ALGO_LIST:
    ss = 'L7Parton_'+aa+'_'+pp
    s1 = ss
    s2 = ERA + '_' + s1
    k1 = p1.sub( s1, fileContents )
    k2 = p2.sub( s2, k1 )
    k2outfile = s2 + '.txt'
    print '--------------------------------------'
    print 'ORCOFF File for jet correction : ' + s1
    print 'Written to ' + k2outfile
    FILE = open(k2outfile,"w")
    FILE.write(k2)        
    files.append( k2outfile )



### L4 Corrections
for aa in ALGO_LIST :
  for tt in TYPE_LIST: #loop for jet types
    if ( (tt=='Calo') and (aa=='AK5') ):
      ss = 'L4EMF_' + aa + tt
      s1 = ss
      s2 = ERA + '_' + s1
      k1 = p1.sub( s1, fileContents )
      k2 = p2.sub( s2, k1 )
      k2outfile = s2 + '.txt'
      print '--------------------------------------'
      print 'ORCOFF File for jet correction : ' + s1
      print 'Written to ' + k2outfile
      FILE = open(k2outfile,"w")
      FILE.write(k2)        
      files.append( k2outfile )
      



for file in files :
  subprocess.call( ["./dropBoxOffline_test.sh", "JEC_"+ERA+".db", file])
