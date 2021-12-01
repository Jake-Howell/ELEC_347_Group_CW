from bellfilter import BellFilter



# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    testFilter = BellFilter(96000,16000,20,1)
    testFilter.computeCoefficients()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
