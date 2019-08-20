# The basic class that will hold the info about another chains in the linked list
class Node:
	def __init__(self,data):
		self.prev = None
		self.next = None
		self.data = data

class Doubly_linked_list:

	def __init__(self):
		self.head = None
		self.tail_index = -1

	def size(self):
		return self.tail_index+1

	def empty(self):
		return self.tail_index is -1

	def insert(self,data,pos):
		if pos>self.tail_index+1 or pos<0:
			print("Can't insert outside the bounds")
			raise Exception("Out of bounds")
		# if inserting at head
		elif pos is 0:
			# if the list is empty
			if self.head is None:
				self.head = Node(data)
				self.tail_index += 1
				return
			# make new data point as head of list
			temp = Node(data)
			temp.next = self.head
			self.head.prev = temp
			self.head = temp
			self.tail_index += 1
			return
		# if inserting at the last position
		elif pos is self.tail_index:
			temp = self.head
			# find the last link of the list
			while temp.next is not None:
				temp = temp.next
			var = Node(data)
			temp.prev.next = var 
			var.prev = temp.prev
			var.next = temp
			temp.prev = var
			self.tail_index += 1
			return
		# if appending the data at tail
		elif pos is self.tail_index+1:
			temp = self.head
			while temp.next is not None:
				temp = temp.next
			temp.next = Node(data)
			temp.next.prev = temp
			self.tail_index += 1
			return
		# inserting somewhere in middle
		else:
			temp = self.head
			cur_index = 0
			while cur_index<pos:
				cur_index += 1
				temp = temp.next
			var = Node(data)
			temp.prev.next = var
			var.prev = temp.prev
			temp.next.prev = var
			var.next = temp.next
			self.tail_index += 1
			return

	# to erase the link at the given position
	def erase(self,pos):
		if pos > self.tail_index+1 or pos<0:
			print("can't access out of bounds")
			raise Exception("out of bounds")
		# if link at head is to be erased
		elif pos is 0:
			self.head = self.head.next
			self.tail_index = -1
			return
		# if link at tail is to be erased
		elif pos is self.tail_index:
			temp = self.head
			cur_index = 0
			while cur_index+1 < pos:
				cur_index += 1
				temp = temp.next
			temp.next = None
			self.tail_index -= 1
			return
		# if link to be erased lies somewhere in middle of list
		else:
			temp = self.head
			cur_index = 0
			while cur_index is not pos:
				cur_index += 1
				temp = temp.next
			temp.prev.next = temp.next
			temp.next.prev = temp.prev
			self.tail_index -= 1
			return

	# gives the data stored at the given position
	def at(self,pos):
		if pos > self.tail_index or pos<0:
			print("Can't access unavailable indexes")
			raise Exception("Out of bounds")
		temp = self.head
		cur_index = 0
		while cur_index is not pos:
			cur_index += 1
			temp = temp.next
		return temp.data

if __name__=="__main__":
	# print("The test cases :")
	# l = Doubly_linked_list()
	# l.insert(12,0)
	# l.insert(13,1)
	# l.insert(132,1)
	# print(l.at(1))
	# l.erase(1)