module PE2 where

-- PE2: Dungeon Crawler
-- Dungeon map is :: Tree Chamber [Encounter]
-- Each encounter is either a fight or a treasure
-- Fights deal you damage (reduce HP) but enemies drop some gold (add
-- gold)
-- Tresures just give gold, or potions (which give hp)
-- Nodes hold encounters, when you visit a node you go through all of them in order
-- You start with a certain amount of HP and 0 gold.
-- You lose HP and accumulate gold as you descend the tree and go through encounters

-- Polymorphic tree structure
data Tree a b = EmptyTree | Leaf a b | Node a b [Tree a b] deriving (Show, Eq)

-- Every location in the tree is of some Chamber type.
data Chamber = Cavern |
               NarrowPassage |
               UndergroundRiver |
               SlipperyRocks deriving (Show, Eq)

-- An enemy has a name, an amount of damage that it deals
-- and an amount of gold that it drops (in that order).
data Enemy = Enemy String Integer Integer deriving (Show, Eq)

-- Gold n gives n amount of gold
-- Potion n heals n hp
data Loot = Gold Integer | Potion Integer deriving (Show, Eq)

-- An encounter is either a Fight with an Enemy, or a treasure where
-- you find Loot
data Encounter = Fight Enemy | Treasure Loot deriving (Show, Eq)

-- This is a type synonym for how we will represents our dungeons
type Dungeon = Tree Chamber [Encounter]

--Traverse Path
encounterResult :: Integer -> Integer -> Encounter -> (Integer, Integer)
encounterResult hp gold (Fight (Enemy _ e_damage e_gold)) = (hp - e_damage, gold + e_gold)
encounterResult hp gold (Treasure (Gold (t_gold)))        = (hp, gold + t_gold)
encounterResult hp gold (Treasure (Potion (t_hp)))        = (hp + t_hp, gold)

encounterResultList :: Integer -> Integer -> [Encounter] -> (Integer, Integer)
encounterResultList hp gold (x:xs) = (hp_2, gold_1 + gold_2)
        where (hp_1, gold_1) = encounterResult hp gold x
              (hp_2, gold_2) = encounterResultList hp_1 gold xs
encounterResultList hp gold _ = (hp, gold)

--Find Max Gain
encounterResultListNonR :: Integer -> Integer -> [Encounter] -> (Integer, Integer)
encounterResultListNonR hp gold [] = (hp, gold)
encounterResultListNonR hp gold (x:xs)
    | (hp_1 <= 0) || (hp_2 <= 0) = (-1, 0)
    | (xs == [])                 = (hp_1, gold_1)
    | otherwise                  = (hp_2, gold_2)
        where (hp_1, gold_1) = encounterResult hp gold x
              (hp_2, gold_2) = encounterResultListNonR hp_1 gold_1 xs

traverseAll :: Integer -> Integer -> Dungeon -> [Integer]
traverseAll _ _ EmptyTree = []
traverseAll hp_s gold (Leaf _ encounter)
    | (hp > 0) = [result]
    | otherwise = []
        where (hp, result) = encounterResultListNonR hp_s gold encounter
traverseAll hp_s gold (Node _ encounter children)
    | (hp > 0) = [result] ++ traverseNode hp result children
    | otherwise = []
        where (hp, result) = encounterResultListNonR hp_s gold encounter

traverseNode :: Integer -> Integer -> [Dungeon] -> [Integer]
traverseNode hp_s gold [] = []
traverseNode hp_s gold (x:xs) = traverseAll hp_s gold x ++ traverseNode hp_s gold xs

--findViablePaths

traverseViable :: Integer -> Dungeon -> Dungeon
traverseViable _ EmptyTree = EmptyTree
traverseViable hp_s l@(Leaf chamber encounter)
    | (hp > 0) = l
    | otherwise = EmptyTree
        where (hp, result) = encounterResultListNonR hp_s 0 encounter
traverseViable hp_s n@(Node chamber encounter children)
    | (hp > 0) && (len > 0)  = Node chamber encounter trees
    | (hp > 0) && (len == 0) = Leaf chamber encounter
    | otherwise              = EmptyTree
        where (hp, result) = encounterResultListNonR hp_s 0 encounter
              trees = traverseViableIter hp children
              len = length trees

traverseViableIter :: Integer -> [Dungeon] -> [Dungeon]
traverseViableIter hp [] = []
traverseViableIter hp (x:xs)
    | (r == EmptyTree) = traverseViableIter hp xs
    | otherwise        = [r] ++ traverseViableIter hp xs
        where r = traverseViable hp x

--maxDistance

maxDistanceMain :: Integer -> Dungeon -> (Integer, Dungeon)
maxDistanceMain hp EmptyTree = (0, EmptyTree)
maxDistanceMain hp l@(Leaf chamber encounter) = (0, l)
maxDistanceMain hp n@(Node chamber encounter (children@(x:xs)))
    | (len == 1) = (1 + v, n)
    | otherwise  = (sf1 + sf2 + 2, n)
        where len = length children
              (v, ty) = maxDistanceMain hp x
              sf1 = maximum (maxDistanceIter hp children)
              sf2 = maximum (remove sf1 (maxDistanceIter hp children))

maxDistance :: Integer -> Dungeon -> (Integer, Dungeon)
maxDistance hp EmptyTree = (0, EmptyTree)
maxDistance hp l@(Leaf chamber encounter) = (0, l)
maxDistance hp n@(Node chamber encounter children) = (1 + x, n)
    where x = maximum (maxDistanceIter hp children)

maxDistanceIter :: Integer -> [Dungeon] -> [Integer]
maxDistanceIter hp [] = []
maxDistanceIter hp (x:xs) = [r] ++ maxDistanceIter hp xs
    where (r, f) = maxDistance hp x

remove :: Integer -> [Integer] -> [Integer]
remove _ [] = []
remove x (y:ys)
    | (x == y)  = ys
    | otherwise = y : remove x ys

-- mostEfficientSubtree

findSubtree :: Dungeon -> [Dungeon]
findSubtree EmptyTree = []
findSubtree (Leaf chamber encounter) = [Leaf chamber encounter]
findSubtree (Node chamber encounter children) = [Leaf chamber encounter] ++ [Node chamber encounter children] ++ traverseFindSubtree children

traverseFindSubtree :: [Dungeon] -> [Dungeon]
traverseFindSubtree [] = []
traverseFindSubtree (x:xs) = findSubtree x ++ traverseFindSubtree xs

findSubtreeEfficiency :: Dungeon -> Integer
findSubtreeEfficiency EmptyTree = 0
findSubtreeEfficiency (Leaf chamber encounter) = ratio
    where ratio = r_gold / r_hp
          (r_hp, r_gold) = encounterResultList encounter

-- First argument is starting HP
-- Second argument is the dungeon map
-- Third argument is the path (each integer in the list shows what child
-- you descend into)
-- Calculate how much HP you have left and how much gold you've
-- accumulated after traversing the given path

traversePath :: Integer -> Dungeon -> [Int] -> (Integer, Integer)
traversePath _ (EmptyTree) _ = (0, 0)
traversePath hp (Leaf _ encounter) _ = encounterResultList hp 0 encounter
traversePath hp (Node _ encounter children) (x:xs) = (hp_t, gold_t)
    where hp_t = hp_r
          gold_t = gold_n + gold_r
          (hp_n, gold_n) = encounterResultList hp 0 encounter
          (hp_r, gold_r) = traversePath hp_n (children !! x) xs
traversePath _ _ _ = (0, 0)

-- First argument is starting HP
-- Second argument is dungeon map
-- Find which path down the tree yields the most gold for you
-- You cannot turn back, i.e. you'll find a non-branching path
-- You do not need to reach the bottom of the tree
-- Return how much gold you've accumulated

findMaximumGain :: Integer -> Dungeon -> Integer
findMaximumGain hp dungeon = maximum (traverseAll hp 0 dungeon)
findMaximumGain _ _ = 0

-- First argument is starting HP
-- Second argument is the dungeon map
-- Remove paths that you cannot go thorugh with your starting HP. (By
-- removing nodes from tree).
-- Some internal nodes may become leafs during this process, make the
-- necessary changes in such a case.
findViablePaths :: Integer -> Dungeon -> Dungeon
findViablePaths hp dung = traverseViable hp dung
findViablePaths _ _ = EmptyTree

-- First argument is starting HP
-- Second Argument is dungeon map
-- Find, among the viable paths in the tree (so the nodes you cannot
-- visit is already removed) the two most distant nodes, i.e. the two
-- nodes that are furthest awat from each other.
mostDistantPair :: Integer -> Dungeon -> (Integer, Dungeon)
mostDistantPair int dun = maxDistanceMain int dun_k
   where dun_k = findViablePaths int dun
mostDistantPair _ _ = (0, EmptyTree)

-- Find the subtree that has the highest total gold/damage ratio
-- Simply divide the total gold in the subtree by the total damage
-- in the subtree. You only take whole subtrees (i.e you can take a new
-- node as the root of your subtree, but you cannot remove nodes
-- below it). Note that the answer may be the whole tree.
mostEfficientSubtree :: Dungeon -> Dungeon
mostEfficientSubtree _ = EmptyTree
