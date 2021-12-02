import math

import numpy
import scipy

from scipy.signal import freqs,freqz,bilinear


import matplotlib.pyplot as plt


class BellFilter():

    #Specified in Hz
    samplingFrequency : int

    #Specified in Hz
    centreFrequency : int

    #Specified in dB
    boostFactor : float

    #Integer
    qFactor : int

    def __init__(self, samplingFrequency = None, centreFrequency = None, boostFactor = None, qFactor = None):
        self.samplingFrequency = samplingFrequency
        self.centreFrequency = centreFrequency
        self.boostFactor = boostFactor
        self.qFactor = qFactor




        self.b1 = None
        self.b2 = None
        self.b3 = None

        self.a1 = None
        self.a2 = None
        self.a3 = None

        #Analogue prototype filter

        self.__analogHa = numpy.array(0)
        self.__analogWa = numpy.array(0)
        self.__analogA = None
        self.__analogB = None


        #BZT coefficients
        self.__BZTa1 = numpy.array(0)
        self.__BZTb1 = numpy.array(0)



        self.__period = None
        self.__criticalFrequency = None
        self.__prewarpFactor = None
        self.__linearGain = None
        self.__kConstant = None

        #Quick check to see if valid values are inserted
        self.performInitialCheck()




    #Sanity check
    def performInitialCheck(self):
        if (self.samplingFrequency == 0) or (self.samplingFrequency is None):
            self.samplingFrequency = 10000
            print("Sampling frequency not specified. Defaulted to 10kHz \r\n")
        elif(self.centreFrequency == 0) or (self.centreFrequency is None):
            self.centreFrequency = 1000
            print("Centre frequency not specified.Defaulted to 1kHz \r\n")
        elif self.boostFactor is None:
            self.boostFactor = 1
            print("Boost factor not specified. Defaulted to 1 \r\n")
        elif self.qFactor is None:
            self.qFactor = 1
            print("qFactor not specified.Defaulted to 1 \r\n")

        print("Sampling frequency is:" + str(self.samplingFrequency))
        print("Centre frequency is:" + str(self.centreFrequency))
        print("Boost factor is:" + str(self.boostFactor))
        print("Qfactor is:" + str(self.qFactor))


    #Convert gain to linear ratio
    def __convertGainToLinear(self):
        self.__linearGain = math.pow(10,(self.boostFactor/20))

    #Compute k coefficient
    def __computeK(self):
        self.__kConstant = 3*( (self.__linearGain-1) / (self.__linearGain+1) )

    #Compute the critical freq. term
    def __computeCriticalFreq(self):
        self.__criticalFrequency = 2 * math.pi * self.centreFrequency


    #Compute period
    def __computePeriod(self):
        self.__period = 1/self.samplingFrequency

    #Compute the pre-warp factor
    def __computePrewarp(self):
        self.__prewarpFactor = math.tan( (self.__criticalFrequency*self.__period)/2)


    def __computePrototypeAnalogueCoefficients(self):
        # Analogue prototype function
        self.__analogA = numpy.array([1, (3 + self.__kConstant) * (self.__criticalFrequency / self.qFactor),
                                      self.__criticalFrequency * self.__criticalFrequency])

        self.__analogB = numpy.array([1, (3- self.__kConstant) * (self.__criticalFrequency / self.qFactor),
                                      self.__criticalFrequency*self.__criticalFrequency])

        self.__analogHa, self.__analogWa = freqs(self.__analogB,self.__analogA)

        # print(self.__analogA)
        # print(self.__analogB)
        # print(self.__analogHa)
        # plt.semilogx(self.__analogHa, 20* numpy.log10(abs(self.__analogWa)))
        # plt.xlabel("Frequency")
        # plt.ylabel("Amplitude")
        # plt.grid()
        # plt.show()


    def __computeBZT(self):
        self.prewarpstuff = (3.1415*self.centreFrequency)/self.samplingFrequency
        self.__BZTb1,self.__BZTa1 = bilinear(self.__analogB,self.__analogA,self.samplingFrequency )
        self.w,self.h = freqz(self.__BZTa1,self.__BZTb1,self.samplingFrequency)
        print(self.w)
        print(self.h)
        fig,ax1 = plt.subplots()
        ax1.set_title("Digital response")
        ax1.plot(self.w,20*numpy.log10(abs(self.h)),'b')
        plt.grid()
        plt.show()


    def computeCoefficients(self):

        #Convert gain to linear
        self.__convertGainToLinear()
        #Compute k coefficient
        self.__computeK()
        #Compute the critical frequency
        self.__computeCriticalFreq()
        #Compute the period
        self.__computePeriod()
        #Compute period
        self.__computePrewarp()
        #Compute the analog coefficients
        self.__computePrototypeAnalogueCoefficients()

        #Apply BZT
        self.__computeBZT()


