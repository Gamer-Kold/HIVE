import nimraylib_now
import std/math
var 
    width : int = 500
    height : int = 500

let
    window_title = "HIVE by Kodin"

initWindow(width, height, window_title)

while not windowShouldClose():
    beginDrawing()
    clearBackground(GRAY)
    endDrawing()

closeWindow()