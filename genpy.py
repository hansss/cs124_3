from random import randint

class RandomAData:
	def __init__(self, n):
		self.n = n
		self.A = [randint(0, pow(10,12)) for x in range(n)]
	
	def printAtoFile(self, filename):
		f = open(filename, 'w')
		for i in self.A:
			f.write(str(i) + "\n")

		f.close()

A = RandomAData(100)

A.printAtoFile("input.txt")		
