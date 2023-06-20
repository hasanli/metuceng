def inheritance(desc):
	departed = []
	married = []
	parent = []
	child = []
	subject = ""
	wealth = 0
	output = []
	desc_length = len(desc)
	for i in range(0, desc_length): desc[i] = list(filter(lambda x: x != "", desc[i].split(" ")))
	#eliminates the empty spaces and creates a nested list consisting of the input

	for j in desc: #collects data individually for checks
		if j[0] == "DEPARTED": #collects the departed
			departed.append(j[1])
		if j[0] == "DECEASED": #collects the subject
			subject = j[1]
			wealth = float(j[2])
		if j[0] == "CHILD": #collects the parents
			parent.append(j[1])
			parent.append(j[2])
			j_length = len(j)
			for i in range(3, j_length):
					child.append(j[i])

		if j[0] == "MARRIED": #collects the married
			married.append(j[1])
			married.append(j[2])

	def departed_check(var): #checks if a person is departed
		if var in departed:
			return True
		else:
			return False

	def married_check(var): #checks if a person is married
		if var in married:
			return True
		else:
			return False

	def spouse_finder(var): #returns the spouse of an individual
		var_index = married.index(var)
		if var_index % 2 == 0:
			return married[var_index + 1]
		else:
			return married[var_index - 1]

	def children_check(var): #checks if a person has children
		if var in parent:
			return True
		else:
			return False

	def children_finder(var): #returns the spouse of an individual
		var_list = []
		for j in desc:
			j_length = len(j)
			if j[0] == "CHILD":
				if (var == j[1]) or (var == j[2]):
					for i in range(3, j_length):
						var_list.append(j[i])
		return var_list

	def children_departed_check(var): #checks if the children of an individual is dead
		for b in children_finder(var):
			if not departed_check(b):
				return False
		else:
			return True

	def parent_departed_check(var): #checks if the parents of an individual is dead
		for b in parent_finder(var):
			if not departed_check(b):
				return False
				break
		else:
			return True

	def children_share(var, value):
		output = []
		child_count = len(able_children_finder(var))

		for i in able_children_finder(var):
			if i in departed:
				output.extend(children_share(var, value / child_count))
			else:
				output.append((i , value / child_count))

		return output

	def parent_share(var, value):
		final_list = [] #checks if the parents of an individual is dead
		mother = parent_finder(var)[0]
		father = parent_finder(var)[1]
		if (mother in departed) and (father in departed):
			if descendant_check(mother) and descendant_check(father):
				final_list.extend(descendant_share(mother, value / 2))
				final_list.extend(descendant_share(father, value / 2))
			elif descendant_check(mother) and not descendant_check(father):
				final_list.extend(descendant_share(mother, value))
			elif not descendant_check(mother) and descendant_check(father):
				final_list.extend(descendant_share(father, value))

		elif (mother not in departed) and (father in departed):
			if descendant_check(father):
				final_list.append((mother, value / 2))
				final_list.extend(descendant_share(father, value / 2))
			elif not descendant_check(father):
				final_list.append((mother, value))

		elif (mother in departed) and (father not in departed):
			if descendant_check(mother):
				final_list.append((father, value / 2))
				final_list.extend(descendant_share(mother, value / 2))
			elif not descendant_check(mother):
				final_list.append((father, value))

		elif (mother not in departed) and (father not in departed):
			final_list.append((mother, value / 2))
			final_list.append((father, value / 2))

		return final_list

	def grandparent_share(var, value):

		final_list = []

		grandparents = []
		for i in parent_finder(var):
			grandparents.extend(parent_finder(i))

		able_grandparents = []
		for k in grandparents:
			if k not in departed or descendant_check(k) == True:
				able_grandparents.append(k)

		gp_count = len(able_grandparents)

		for j in grandparents:
			if j in departed:
				final_list.extend(descendant_share(j, value / gp_count))
			else:
				final_list.append((j, float(value / gp_count)))

		return final_list

	def parent_exist_check(var):
		if var in child:
			return True
		else:
			return False

	def grandparent_exist_check(var):
		for i in parent_finder(var):
			if parent_exist_check(i):
				return True
		else:
			return False

	def grandparent_check(var):
		grandparents = []
		for i in parent_finder(var):
			grandparents.extend(parent_finder(i))
		for i in grandparents:
			if descendant_check(i) or i not in departed:
				return True
		else:
			return False

	def parent_finder(var): #returns the parents of an individual
		if parent_exist_check(var):
			for j in desc:
				j_length = len(j)
				if j[0] == "CHILD":
					for i in range(3, j_length):
						if j[i] == var:
							return [j[1],j[2]]
		else:
			return []

	def descendant_check(var): #checks if an individual has a descendant
		if children_check(var) == False:
			return False
		elif children_departed_check(var) == False:
			return True
		else:
			for b in children_finder(var):
				if descendant_check(b):
					return True
			else:
				return False

	def parent_descendant_check(var): #USED IN PG3, CLEARED
			if (descendant_check(parent_finder(var)[0]) == False) and (descendant_check(parent_finder(var)[1]) == False):
				return False
			else:
				return True

	def able_children_finder(var):

		able_children = children_finder(var)

		get_deleted = []

		for b in able_children:
			if (b in departed) and (descendant_check(b) == False):
				get_deleted.append(b)

		for i in get_deleted:
			able_children.remove(i)
			
		return able_children

	def descendant_share(var, value): #determines the share of the descendants

		final_list = []

		child_count = len(able_children_finder(var))

		for i in able_children_finder(var):
			if i in departed:
				final_list.extend(descendant_share(i, float(value / child_count)))
			else:
				final_list.append((i, float(value / child_count)))

		return final_list

	def duplicate_remove(var):

		heirs = []
		bing = []

		for i in var:
			if i[0] not in heirs:
				heirs.append(i[0])

		for i in heirs:
			sum = 0
			for k in var:
				if k[0] == i:
					sum += k[1]
			bing.append((i, sum))

		return bing

	if descendant_check(subject):
		if (married_check(subject)) and (spouse_finder(subject) not in departed):
			output.append((spouse_finder(subject), float(wealth / 4)))
			output.extend(descendant_share(subject, float(wealth * 3 / 4)))
		else:
			output.extend(descendant_share(subject, float(wealth)))

	else:
		if parent_exist_check(subject) == True:
			if parent_descendant_check(subject) or parent_finder(subject)[0] not in departed or parent_finder(subject)[1] not in departed:
				if (married_check(subject)) and (spouse_finder(subject) not in departed):
					output.append((spouse_finder(subject), float(wealth / 2)))
					output.extend(parent_share(subject, float(wealth / 2)))
				else:
					output.extend(parent_share(subject, float(wealth)))
			else:
				if grandparent_exist_check(subject) == True:
					if grandparent_check(subject) == True:
						if (married_check(subject)) and (spouse_finder(subject) not in departed):
							output.append((spouse_finder(subject), float(wealth * 3 / 4)))
							output.extend(grandparent_share(subject, float(wealth / 4)))
						else:
							output.extend(grandparent_share(subject, float(wealth)))
					else:
						if (married_check(subject)) and (spouse_finder(subject) not in departed):
							output.append((spouse_finder(subject), float(wealth)))
						else:
							output = []
				else:
					if (married_check(subject)) and (spouse_finder(subject) not in departed):
						output.append((spouse_finder(subject), float(wealth)))
					else:
						output = []
		else:
			if (married_check(subject)) and (spouse_finder(subject) not in departed):
				output.append((spouse_finder(subject), float(wealth)))
			else:
				output = []

	return duplicate_remove(output)