{-# LANGUAGE FlexibleInstances #-}

module PE3 where

import Data.List (sort, sortBy)
import Text.Printf (printf)

data Term = Const Integer | Pw Integer Power | Trig Integer Power Trigonometric | Exp Integer Power Exponential

data Power = Power Integer
data Polynomial = Polynomial [(Integer, Power)]
data Exponential = Exponential Polynomial
data Trigonometric = Sin Polynomial | Cos Polynomial

class Evaluable a where
    function :: a -> (Integer -> Double)

class Differentiable a where
    derivative :: a -> [Term]

-- You can use this as is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- You don't have to follow the order the functions appear in the file
-- For example, you could first define all Show instances, then all Eq instances etc.
-- if that implementation order is more convenient for you.



-- INSTANCES FOR POWER

instance Show Power where
    show (Power x)
        | x == 0  = "1"
        | x == 1  = "x"
        | x >  1  = "x^" ++ show x
        | x <  0  = "x^(" ++ show x ++ ")"
        
instance Eq Power where
    (Power x) == (Power y) = x == y

instance Ord Power where
    (Power x) <= (Power y) = x <= y

instance Evaluable Power where
    function (Power y) = \x -> ((fromIntegral (x)) ** (fromIntegral (y)))

instance Differentiable Power where
    derivative a = calculatePowerDerivative a



calculatePowerDerivative :: Power -> [Term]
calculatePowerDerivative (Power x)
    | x == 0    = []
    | x == 1    = [(Const 1)]
    | otherwise = [(Pw x (Power y))]
        where y = x-1



-- INSTANCES FOR POLYNOMIAL

instance Show Polynomial where
    show (Polynomial x@((s, p):xs))
        | x  == []  = show "0"
        | xs /= [] && s == -1         = show "-" ++ show p ++ " + " ++ show (Polynomial xs)
        | xs /= [] && s == 1          = show p ++ " + " ++ show (Polynomial xs)
        | xs /= [] && s == 0          = show (Polynomial xs)
        | xs /= [] && (show p) == "1" = show s ++ " + " ++ show (Polynomial xs)
        | xs /= []                    = show s ++ show p ++ " + " ++ show (Polynomial xs)
        | xs == [] && s == -1         = show "-" ++ show p 
        | xs == [] && s == 1          = show p
        | xs == [] && s == 0          = ""
        | xs == [] && (show p) == "1" = show s
        | xs == []                    = show s ++ show p

instance Evaluable Polynomial where
  function (Polynomial y) = \x -> sum[fromIntegral z * (fromIntegral x ^^ p) | (z, Power p) <- y]

instance Differentiable Polynomial where
    derivative y = calculatePolDer y
    
calculatePolDer :: Polynomial -> [Term]
calculatePolDer (Polynomial x@((s, Power p):xs))
    | x == []              = []
    | xs /= [] && s == 0   = [] ++ calculatePolDer (Polynomial xs)
    | xs /= [] && p == 0   = [] ++ calculatePolDer (Polynomial xs)
    | xs /= [] && p == 1   = [(Const s)] ++ calculatePolDer (Polynomial xs)
    | xs /= []             = [(Pw tot_s der_p)] ++ calculatePolDer (Polynomial xs)
    | xs == [] && s == 0   = []
    | xs == [] && p == 0   = []
    | xs == [] && p == 1   = [(Const s)]
    | xs == []             = [(Pw tot_s der_p)]
        where [(Pw der_s der_p)] = derivative (Power p)
              tot_s = s*der_s


-- INSTANCES FOR TRIGONOMETRIC

instance Show Trigonometric where
    show (Sin x)
        | (elem '^' (show x)) || (elem '+' (show x)) || (elem '-' (show x)) = "sin(" ++ show x ++ ")"
        | otherwise                                  = "sin" ++ show x
    show (Cos x)
        | (elem '^' (show x)) || (elem '+' (show x)) || (elem '-' (show x)) = "cos(" ++ show x ++ ")"
        | otherwise                                  = "cos" ++ show x

instance Evaluable Trigonometric where
  function (Sin p) = \x -> getRounded(sin(function p x))
  function (Cos p) = \x -> getRounded(cos(function p x))

instance Differentiable Trigonometric where
    derivative t = calculateTriDer t
    
calculateTriDer :: Trigonometric -> [Term]
calculateTriDer (t@(Sin p)) = [Trig int pow (Cos p) | (Pw int pow) <- r]
    where r = derivative p
calculateTriDer (t@(Cos p)) = [Trig (-1*int) pow (Sin p) | (Pw int pow) <- r]
    where r = derivative p

-- INSTANCES FOR EXPONENTIAL

instance Show Exponential where
    show (Exponential x)
        | show x == ""                               = ""
        | show x == "1"                              = "e"
        | (elem '^' (show x)) || (elem '+' (show x)) = "e^(" ++ show x ++ ")"
        | otherwise                                  = "e^" ++ show x

instance Evaluable Exponential where
    function (Exponential p) = \x -> getRounded(exp(function p x))

instance Differentiable Exponential where
    derivative e  = calculateExpDer e

calculateExpDer :: Exponential -> [Term]
calculateExpDer (e@(Exponential p)) = [Exp int pow e | (Pw int pow) <- r]
    where r = derivative p

-- INSTANCES FOR TERM

instance Show Term where
    show (Const x) = show x
    show (Pw x y)
        | x == 0    = show "0"
        | x == 1    = show y
        | x == -1   = "-" ++ show y
        | otherwise = show x ++ show y
    show (Trig x y t)
        | x == 0    = show "0"
        | otherwise = show (Pw x y) ++ show t
    show (Exp x y e)  = show (Pw x y) ++ show e

instance Evaluable Term where
    function (Const x) = \_ -> getRounded(fromIntegral x)
    function (Pw x y) = \a -> getRounded(fromIntegral(x) * function y a)
    function (Trig x y t) = \a -> getRounded(fromIntegral(x) * (function y a) * (function t a))
    function (Exp x y e) = \a -> getRounded(fromIntegral(x) * (function y a) * (function e a))

instance Differentiable Term where
    derivative d = calculateTerDer d
    
calculateTerDer :: Term -> [Term]
calculateTerDer (Const int) = []
calculateTerDer (Pw 0 pow_m) = []
calculateTerDer (Pw int_m pow_m) = [Pw (int*int_m) pow | (Pw int pow) <- r]
    where r = derivative pow_m
calculateTerDer (Trig 0 (Power pw_int_m) tri_m) = []
calculateTerDer (Trig int_m (Power pw_int_m) tri_m) = [Trig (int_m*int) (Power (pw_int_m*pw_int)) tri | (Trig int (Power pw_int) tri) <- r] ++ [Trig (int_n*int_m) pow tri_m | (Pw int_n pow) <- p]
    where r = derivative tri_m
          p = derivative (Power pw_int_m)
calculateTerDer (Exp 0 (Power pw_int_m) exn_m) = []
calculateTerDer (Exp int_m (Power pw_int_m) exn_m) = [Exp (int_m*int) (Power (pw_int_m*pw_int)) exn | (Exp int (Power pw_int) exn) <- r] ++ [Exp (int_n*int_m) pow exn_m | (Pw int_n pow) <- p]
    where r = derivative exn_m
          p = derivative (Power pw_int_m)

-- INSTANCES FOR [TERM]

instance Evaluable [Term] where
    function t = \x -> getRounded(sum[function b x | b <- t])
    
instance Differentiable [Term] where
    derivative (x:xs) = derivative x ++ derivative xs
