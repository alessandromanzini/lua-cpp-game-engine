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
--- @type Audio
local track

--- @type Button
local btn

--- @type TextBox
local tb

--- @type HitRegion
local hr
local hr_hover = false
local hr_click = false

--- @type Point
local mouse_pos

--- @type Bitmap
local char_bitmap
--- @type Sprite
local sprite

---------------------------------
--- Constants
---------------------------------
local COLORS = {}

local function populate_colors()
	COLORS.yellow = RGB.new(255, 255, 0)
	COLORS.green = RGB.new(0, 255, 0)
	COLORS.red = RGB.new(255, 0, 0)
	COLORS.magenta = RGB.new(255, 0, 255)
	COLORS.background = RGB.new(10, 300, 30) -- Overflow from 255
end

---------------------------------
--- This hook is called when the script is loaded.
--- @return nil
function on_initialize()
	populate_colors()

	GAME_ENGINE:set_width(1280)
	GAME_ENGINE:set_height(720)
	GAME_ENGINE:set_frame_rate(50)

	GAME_ENGINE:set_title("Lua Game Example")

	GAME_ENGINE:set_key_list("K".."L".."M".."O")
	GAME_ENGINE:show_mouse_pointer(false)

	--- Initialize audio track
	track = file_utils.CreateAudio("test.mp3")
	bind_to_game(track)

	--- Define a hitregion to capture collisions
	hr = HitRegion.new(SHAPE.rectangle, 500, 100, 600, 200)
	mouse_pos = Point.new(0, 0)

	--- Create a sprite, define rows, cols and animation delay
	char_bitmap = Bitmap.new(file_utils.get_resource("test.png"), true)
	sprite = Sprite.new(char_bitmap, 3, 17, 2)
end

---------------------------------
--- This hook is called once, after the 'on_initialize'.
--- @return nil
function on_start() 
	--- Create button and bind it to the game.
	btn = Button.new()
	btn:set_text("Audio test")
	bind_to_game(btn)
	btn:set_bounds(10,35,100,85)
	btn:show()

	--- Create textbox and bind it to the game.
	tb = TextBox.new()
	bind_to_game(tb)
	tb:set_bounds(120, 35, 320, 85)
	tb:show()
end

---------------------------------
--- This hook is called once, when the game is about to close.
--- @return nil
function on_end() end

---------------------------------
--- This hook is called per frame, and it's used for the draw logic.
--- @return nil
function on_paint()
	--- Clear the screen.
	GAME_ENGINE:fill_window_rect(COLORS.background)

	--- HitRegion draw logic
	local bounds = hr:get_bounds()
	GAME_ENGINE:set_color(COLORS.magenta)
	GAME_ENGINE:draw_rect(bounds)
	if hr_click then
		GAME_ENGINE:set_color(COLORS.green)
		GAME_ENGINE:fill_rect(bounds)
	elseif hr_hover then
		GAME_ENGINE:set_color(COLORS.yellow)
		GAME_ENGINE:fill_rect(bounds)
	end

	--- Draw sprite
	if not sprite:paint(mouse_pos) then
		GAME_ENGINE:message_box("There's an issue with your bitmap!")
	end
end

---------------------------------
--- This hook is called per frame, and it's used for the update logic.
--- @return nil
function on_tick() 
	track:tick()
	sprite:tick()

	local speed = 2
	local bounds = hr:get_bounds()
	local current_pos = Point.new((bounds.left + bounds.right) / 2.0, (bounds.top + bounds.bottom) / 2.0)
	local direction = float2.new(current_pos, mouse_pos)

	if direction:normalize() > 1.0 then
		direction = direction * speed
		direction:round()
		log("From ("..current_pos.x..", "..current_pos.y..") to ("..mouse_pos.x..", "..mouse_pos.y.."). RESULT=> ("..direction.x..", "..direction.y..")")
		hr:move(direction.x, direction.y)
	end
	log(sprite:get_frame().."")
end

---------------------------------
--- This hook is called every time the mouse buttons are pressed.
--- @param is_left boolean # True if left click
--- @param is_down boolean # True if pressed
--- @param x number # Mouse x-coordinate
--- @param y number # Mouse y-coordinate
--- @param w_param number # Types use for passing & returning polymorphic values
--- @return nil
function on_mouse_button_action(is_left, is_down, x, y, w_param) 
	hr_click = hr:hit_test(x, y)
end

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
function on_mouse_move(x, y, w_param) 
	hr_hover = hr:hit_test(x, y)
	hr_click = hr_click and hr_hover

	mouse_pos.x = x
	mouse_pos.y = y
end

---------------------------------
--- This hook is executed when a key is pressed. GameEngine.SetKeyList() must be configured to catch keys!
--- @param v_key number
--- @return nil
function on_key_pressed(v_key) end

---------------------------------	
--- This hook is executed whenever a caller object linked to the game instance fires.
--- @param caller Caller
--- @return nil
function on_call_action(caller) 
	if caller == btn or caller == tb then
		track:play()
		tb:set_backcolor(COLORS.yellow)
		tb:set_text("Starting...")
	elseif caller == track then
		tb:set_backcolor(COLORS.green)
		tb:set_text("go!")
	end
end
