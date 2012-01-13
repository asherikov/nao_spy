#!/usr/bin/python
#-*- coding: iso-8859-15 -*-

# Remote control of walking module

import os
import sys
import time

from naoqi import ALProxy
from optparse import OptionParser


parser = OptionParser()
parser.add_option("-a", "--action", action="store", type="int", dest="nao_action", default=0)
parser.add_option("-b", "--broker-ip", action="store", type="string", dest="IP", default="127.0.0.1")
parser.add_option("-p", "--broker-port", action="store", type="int", dest="PORT", default=9559)
(options, args) = parser.parse_args();


try:
    spy_proxy = ALProxy("nao_spy", options.IP, options.PORT)
except Exception,e:
    print "Error when creating proxy:"
    print str(e)
    exit(1)

# execute action
try:
    spy_proxy.spy()
except Exception,e:
    print "Execution of the action was failed."
    exit(1)


exit (0)
