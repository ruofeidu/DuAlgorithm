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
    
    
# 203. Remove Linked List Elements
# Remove all elements from a linked list of integers that have value val.
# Input:  1->2->6->3->4->5->6, val = 6
# Output: 1->2->3->4->5
def removeElements(self, head, val):
    """
    :type head: ListNode
    :type val: int
    :rtype: ListNode
    """
    while head and head.val is val:
        head = head.next
    v = head
    while v:
        while v.next and v.next.val is val:
            v.next = v.next.next
        v = v.next
    return head