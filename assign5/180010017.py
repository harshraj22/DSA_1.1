import sys
# class based implementation to understand it better

class CountingSort():
	def __init__(self):
		pass

	@classmethod	
	def sort(cls, numbers, index):
		"""
			class method don't need object
		"""
		newNumbers = [[] for _ in range(10)]
		for ind, num in enumerate(numbers):
			# add try catch later for numbers of different num of digits
			newNumbers[int(num[index])].append(num)
		ans = []
		for num in newNumbers:
			ans.extend(num)
		return ans


class RadixSort():
	def __init__(self, numbers):
		"""
			numbers: list of strings of integers to be sorted
		"""	
		self.numbers = numbers
	
	def sort(self):
		"""
			do a counting sort for each number right to left as key
		"""
		for index in range(len(self.numbers[0])-1,-1,-1):
			self.numbers = CountingSort.sort(self.numbers, index)

	def print(self, outputFile):
		with open(outputFile, 'w') as f:
			# print(self.numbers)
			f.write('\n'.join(self.numbers))
	

if __name__=='__main__':
	inputFile = sys.argv[1]
	numbers = []
	with open(inputFile) as f:
		numbers = f.read().split()
	obj = RadixSort(numbers)
	obj.sort()
	obj.print('radix.txt')
	