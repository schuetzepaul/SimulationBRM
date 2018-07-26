import measurement

target = 0.07784
current = 1400.

meas = measurement.Measurement(current, target)
#meas.setVerbose()
meas.findMomentum()
print("The momentum was " + str(meas.getMomentum()) + " GeV")
