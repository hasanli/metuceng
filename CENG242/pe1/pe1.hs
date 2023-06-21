module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- Helper funcs
cpg :: Price -> Double
cpg (Price _ x y) = y/x

findPrice :: String -> [Price] -> Price
findPrice ing (p@(Price c_ing _ _):ps)
    | c_ing == ing = p
    | otherwise    = findPrice ing ps

checkStock :: (String, Double) -> [(String, Double)] -> [(String, Double)]
checkStock ((x, y)) (t@((name, amt):ts))
    | (x == name) && (y >  amt) = [(x, getRounded(y - amt))]
    | (x == name) && (y <= amt) = []
    | (x /= name) && ts == []   = [(x, y)]
    | (x /= name) && ts /= []   = checkStock ((x,y)) ts
checkStock _ _ = []

checkStock3 :: (String, Double) -> [(String, Double)] -> [(String, Double)]
checkStock3 ((x, y)) (t@((name, amt):ts))
    | (x == name)             = [(name, getRounded(y - amt))]
    | (x /= name) && ts /= [] = checkStock3 ((x,y)) ts
    | (x /= name) && ts == [] = [(x, y)]

checkStock2 :: [(String, Double)] -> [(String, Double)] -> [(String, Double)]
checkStock2 r@((stock_name, stock_amt):rs) t@((recipe_name, recipe_amt):ts) = checkStock3 ((stock_name, stock_amt)) t ++ checkStock2 rs t
checkStock2 _ _ = []

getIngredient :: Recipe -> [(String, Double)]
getIngredient (r@(Recipe _ ((name, amt):rs))) = [(name, amt)] ++ getIngredient (Recipe "iter" (rs))
getIngredient _ = []

getIngredient2 :: [Recipe] -> [(String, Double)]
getIngredient2 (r@(recipe:rs)) = getIngredient recipe ++ getIngredient2 rs
getIngredient2 _ = []

removeDuped :: [(String, Double)] -> [(String, Double)]
removeDuped xs = removeDuped2 xs []
removeDuped _ = []

removeDuped2 :: [(String, Double)] -> [(String, Double)] -> [(String, Double)]
removeDuped2 [] rs = rs
removeDuped2 (x@((name, amt):xs)) rs
    | (name `elem` map fst rs) = removeDuped2 xs (removeDuped3 name amt rs)
    | otherwise                = removeDuped2 xs ((name, amt):rs)

removeDuped3 :: String -> Double -> [(String, Double)] -> [(String, Double)]
removeDuped3 name amt (x@((name2, amt2):xs))
    | (name2) == name = (name2, amt2 + amt):xs
    | otherwise       = (name2, amt2): removeDuped3 name amt xs 
removeDuped3 _ _ _ = []

recipeCost2 :: (String, Double) -> [Price] -> Double
recipeCost2 (x, y) price = getIngredientCost (x, y) price
recipeCost2 _ _ = 0

addPrices :: [(String, Double)] -> [Price] -> [(String, Double, Double)]
addPrices ((x, y):xs) price = [(x, y, getRounded(recipeCost2 (x, y) price))] ++ addPrices xs price
addPrices _ _ = []

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- Calculate how much the given amount of the given ingredient costs
getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost (ingredient,amount) price = getRounded(cpg (findPrice ingredient price) * amount)
getIngredientCost _ _ = 0

-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost (r@(Recipe _ ((x, y):rs))) price = getRounded(getIngredientCost (x, y) price + recipeCost (Recipe "iter" rs) price)
recipeCost _ _ = 0

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients ( r@(Recipe _ ((x, y):rs))) (t@((name, amt):ts)) = checkStock ((x,y)) t ++ missingIngredients (Recipe "iter" rs) t
missingIngredients _ _ = []

-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe (t@((name, amt):ts)) (r@(Recipe _ ((x, y):rs)))
    |  check /= [] = t
    |  otherwise   = checkStock2 t ((x,y):rs)
    where check = missingIngredients r t
makeRecipe _ _ = []

-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList stock recipe price = addPrices (missingIngredients (Recipe "decoy" (removeDuped (getIngredient2 recipe))) stock) price
--makeShoppingList stock recipe price = 
makeShoppingList _ _ _ = []