# 187. Repeated DNA Sequences [M]
# All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.
# Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.
def hashcode(self, s):
    x = 0
    for c in s:
        x <<= 2
        if c is 'T':
            x += 1
        elif c is 'C':
            x += 2
        elif c is 'G':
            x += 3
    return x

def findRepeatedDnaSequences(self, s):
    """
    :type s: str
    :rtype: List[str]
    """
    d = set()
    a = set()
    ans = []
    for i in range(len(s)-9):
        h = self.hashcode(s[i:i+10])
        if h in d:
            if h not in a:
                ans.append(s[i:i+10])
                a.add(h)
        else:
            d.add(h)
    return ans
    