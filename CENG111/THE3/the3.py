from math import exp
def forward_pass(network, final):
	def lin(lst1, lst2):
		lst3 =[]
		for i in range(len(lst2)):
			nsum = 0
			for j in range(len(lst1)): nsum = nsum + (lst1[j] * lst2[i][j])
			lst3.append(nsum)
		return lst3
	def rel(x): return 0 if x<0 else x
	def sgm(x):
		if x <= (-700): return 0
		elif x >= 700: return 1
		else : return (1 / ( 1 + exp(-x)))
	for d in range(len(network)):
		if type(network[d]) == list: final = lin(final, network[d][1])
		else:
			if network[d][0] == "r": final = list(map(rel, final))
			else: final = list(map(sgm, final))
	return final