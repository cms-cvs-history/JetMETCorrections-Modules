#!/usr/bin/env python

import subprocess

iovs = [
    'JetCorrectorParametersCollection_Jec10V3_AK5Calo',
    'JetCorrectorParametersCollection_Jec10V3_AK5PF',
    'JetCorrectorParametersCollection_Jec10V3_AK5PFchs',
    'JetCorrectorParametersCollection_Jec10V3_AK5JPT',
    'JetCorrectorParametersCollection_Jec10V3_AK7Calo',
    'JetCorrectorParametersCollection_Jec10V3_AK7PF',
    'JetCorrectorParametersCollection_Jec10V3_KT4Calo',
    'JetCorrectorParametersCollection_Jec10V3_KT4PF',
    'JetCorrectorParametersCollection_Jec10V3_KT6Calo',    
    'JetCorrectorParametersCollection_Jec10V3_KT6PF'


    
#    'JetCorrectorParametersCollection_Spring10_V8_AK5Calo',
#    'JetCorrectorParametersCollection_Spring10_V8_AK5PF',
#    'JetCorrectorParametersCollection_Summer10_V8_AK5JPT',
#    'JetCorrectorParametersCollection_Spring10_V8_AK5TRK',
#    'JetCorrectorParametersCollection_Spring10_V8_AK7Calo',
#    'JetCorrectorParametersCollection_Spring10_V8_AK7PF',
#    'JetCorrectorParametersCollection_Spring10_V8_AK7JPT',
#    'JetCorrectorParametersCollection_Spring10_V8_KT4Calo',
#    'JetCorrectorParametersCollection_Spring10_V8_KT4PF',
#    'JetCorrectorParametersCollection_Spring10_V8_KT6Calo',
#    'JetCorrectorParametersCollection_Spring10_V8_KT6PF',
#    'JetCorrectorParametersCollection_Spring10_V8_IC5Calo',
#    'JetCorrectorParametersCollection_Spring10_V8_IC5PF',
    
    ]

for iov in iovs :
    s = 'cmscond_list_iov -c sqlite_file:Jec10V3.db -t ' + iov
    subprocess.call( [s, ""], shell=True )    
