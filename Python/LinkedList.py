# 160. Intersection of Two Linked Lists
# Write a program to find the node at which the intersection of two singly linked lists begins.
'''
A:          a1 - a2
                   \
                     c1 - c2 - c3
                   /            
B:     b1 - b2 - b3
'''
def getIntersectionNode(self, headA, headB):
	"""
	:type head1, head1: ListNode
	:rtype: ListNode
	"""
	a, b = headA, headB
	res, tailA, tailB = None, None, None
	while a and b:
		if a is b:
			res = a
			break
		if a.next:
			a = a.next
		elif tailA is None:
			tailA = a
			a = headB
		else:
			break
		if b.next:
			b = b.next
		elif tailB is None:
			tailB = b
			b = headA
		else:
			break
	return res