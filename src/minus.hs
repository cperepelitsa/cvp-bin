module Main where

import qualified Data.Set as S
import Data.Set (Set)

import System.Environment (getArgs)

main :: IO ()
main = do
    inLines <- getContents >>= return . lines
    argSet <- getArgs >>= return . S.fromList 
    mapM_ putStrLn [ line | line <- inLines, not (S.member line argSet) ]
