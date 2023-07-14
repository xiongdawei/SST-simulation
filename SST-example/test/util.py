import numpy as np

class SSTopGen:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.cap = '---------'
        self.blank = '|       |'
        self.connect_blank = '    '
        self.left = '|  '
        self.shorter_left = '| '
        self.right = ' |'
        self.horizontal_connection = '----'
        self.vertical_connection = ''
    
    def plot_row(self, base):
        str1 = self.cap
        str2 = self.blank
        if base > 9:
            str3 = self.shorter_left + 'CPU' + str(base) + self.right
        else:
            str3 = self.left + 'CPU' + str(base) + self.right
        str4 = self.blank
        str5 = self.cap
        for i in range(self.x - 1):
            str1 += self.connect_blank + self.cap
            str2 += self.connect_blank + self.blank
            base += 1
            if base > 9:
                str3 += self.horizontal_connection + self.shorter_left + 'CPU' + str(base) + self.right
            else:
                str3 += self.horizontal_connection + self.left + 'CPU' + str(base) + self.right
            str4 += self.connect_blank + self.blank
            str5 += self.connect_blank + self.cap
        str1 += '\n'
        str2 += '\n'
        str3 += '\n'
        str4 += '\n'
        print(str1 + str2 + str3 + str4 + str5)
    
    def plot_ver_connection(self):
        str1 = ''
        for i in range(self.x):
            str1 += self.connect_blank + '|' + self.connect_blank*2
        print(str1 + '\n' + str1) 
    
    def grid_plot(self):
        for i in range(self.y-1):
            self.plot_row(i*self.x)
            self.plot_ver_connection()
        self.plot_row((self.y-1)*self.x)

test = SSTopGen(8,8)
test.plot()
