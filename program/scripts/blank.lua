package.path = package.path..";resources/?.lua"..";../resources/?.lua"

---------------------------------
--- Modules
---------------------------------
--- @type file_utils
local file_utils = require("file_utils")

---------------------------------
--- GameEngine global instance, getting a reference right before 'on_initialize' hook.
---------------------------------
--- @type GameEngine
GAME_ENGINE = {}

---------------------------------
--- Locals
---------------------------------


---------------------------------
--- Constants
---------------------------------


---------------------------------
--- This hook is called when the script is loaded.
--- @return nil
function on_initialize()
	GAME_ENGINE:set_width(1280)
	GAME_ENGINE:set_height(720)
	GAME_ENGINE:set_frame_rate(50)

	GAME_ENGINE:set_title("Blank Lua Game")
end

---------------------------------
--- This hook is called once, after the 'on_initialize'.
--- @return nil
function on_start() end

---------------------------------
--- This hook is called once, when the game is about to close.
--- @return nil
function on_end() end

---------------------------------
--- This hook is called per frame, and it's used for the draw logic.
--- @return nil
function on_paint() end

---------------------------------
--- This hook is called per frame, and it's used for the update logic.
--- @return nil
function on_tick() end

---------------------------------
--- This hook is called every time the mouse buttons are pressed.
--- @param is_left boolean # True if left click
--- @param is_down boolean # True if pressed
--- @param x number # Mouse x-coordinate
--- @param y number # Mouse y-coordinate
--- @param w_param number # Types use for passing & returning polymorphic values
--- @return nil
function on_mouse_button_action(is_left, is_down, x, y, w_param) end

---------------------------------
--- This hook is called every time the mouse wheel scrolls.
--- @param x number # Mouse x-coordinate
--- @param y number # Mouse y-coordinate
--- @param distance number # Scroll distance
--- @param w_param number # Types use for passing & returning polymorphic values
--- @return nil
function on_mouse_wheel_action(x, y, distance, w_param) end

---------------------------------
--- This hook is called every time the mouse moves.
--- @param x number # Mouse x-coordinate
--- @param y number # Mouse y-coordinate
--- @param w_param number # Types use for passing & returning polymorphic values
--- @return nil
function on_mouse_move(x, y, w_param) end

---------------------------------
--- This hook is executed when a key is pressed. GameEngine.SetKeyList() must be configured to catch keys!
--- @param v_key number
--- @return nil
function on_key_pressed(v_key) end

---------------------------------	
--- This hook is executed whenever a caller object linked to the game instance fires.
--- @param caller Caller
--- @return nil
function on_call_action(caller) end
