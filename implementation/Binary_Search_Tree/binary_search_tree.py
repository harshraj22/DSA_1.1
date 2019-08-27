class node(object):
	"""This serves as nodes for the binary search tree"""
	def __init__(self,parent=None,right=None,left=None,data=None):
		self.parent = parent
		self.right = right
		self.left = left
		self.data = data

	def describe(self):
		print("node with parent: {}, right: {}, left: {}, data: {}".format(self.parent,self.right,self.left,self.data))


class BinarySearchTree(object):
	"""docstring for BinarySearchTree"""

	__root = None
	__numOfNodes = 0

	def __init__(self):
		pass

	def __insert(self,value,head):
		if head.right is None and head.data < value:
			head.right = node(data=value,parent=head)
			self.__numOfNodes += 1
		elif head.data < value:
			self.__insert(value,head.right)
		elif head.left is None:
			head.left = node(data=value,parent=head)
			self.__numOfNodes += 1
		else:
			self.__insert(value,head.left)

	def __search(self,value,head):
		# if head is not None:
		# 	head.describe()

		if head is None:
			return (False,None)
		elif head.data is value:
			return (True,head)
		elif head.data <= value:
			return self.__search(value,head.right)
		else:
			return self.__search(value,head.left)

	# ---------------------------Public Methods -----------------------

	def insert(self,value):
		if self.__root is None:
			self.__root = node(data=value)
			self.__numOfNodes += 1
		else:
			self.__insert(value,self.__root)

	def search(self,value):
		return self.__search(value,self.__root)[0]

b = BinarySearchTree()
b.insert(3)
b.insert(4)
b.insert(5)
b.insert(6)
b.insert(1)
b.insert(50)
b.insert(23)
print(b.search(32))