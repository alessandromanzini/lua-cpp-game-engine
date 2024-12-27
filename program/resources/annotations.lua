--- @meta annotations

---------------------------------
--- FUNCTIONS
---------------------------------
--- Binds a calling object to the game instance.
--- @param caller Caller|Button|TextBox
--- @return nil
function bind_to_game(caller) end

--- Removes a binded object to the game instance.
--- @param caller Caller|Button|TextBox
--- @return nil
function unbind_from_game(caller) end

--- Logs a message in the top-left corner of the window.
--- @param message string
--- @return nil
function log(message) end

---------------------------------
--- ENGINE CORE
---------------------------------
--- @class GameEngine
--- Represents the engine class, containing all the methods related to the flow of the game 
--- as well as setup settings.
GameEngine = {}

--- Sets title of the window.
--- @param title string
--- @return nil
function GameEngine:set_title(title) end

--- Sets window position in the screen.
--- @param left integer
--- @param top integer
--- @return nil
function GameEngine:set_window_position(left, top) end

--- SetWindowRegion (const HitRegion* regionPtr);

--- Sets keys engine should to listen to.
--- @param keys string # Appended keys
--- @return nil
function GameEngine:set_key_list(keys) end

--- Sets FPS for the tick function
--- @param frame_rate integer
--- @return nil
function GameEngine:set_frame_rate(frame_rate) end

--- Sets window width
--- @param width integer
--- @return nil
function GameEngine:set_width(width) end

--- Sets window height
--- @param height integer
--- @return nil
function GameEngine:set_height(height) end

--- Sets the window to fullscreen.
--- @return boolean # True if successful.
function GameEngine:go_fullscreen() end
 
--- Sets the window to windowed.
--- @return boolean # True if successful.
function GameEngine:go_windowed_mode() end

--- Sets visibility of the mouse pointer in the window.
--- @param value boolean
--- @return nil
function GameEngine:show_mouse_pointer(value) end

--- Quits the application.
--- @return nil
function GameEngine:quit() end

--- HasWindowRegion()

--- Returns the fullscreen state of the window.
--- @return boolean # True if the window is fullscreen.
function GameEngine:is_fullscreen() end

--- Returns wether the specified key is being pressed.
--- @param v_key integer # Key idx
--- @return boolean # True if the param 'v_key' is pressed.
function GameEngine:is_key_down(v_key) end

--- Displays a message box in a pop up window.
--- @param message string
--- @return nil
function GameEngine:message_box(message) end

--- Displays a confirm message box in a pop up window.
--- @param message string
--- @return boolean # Confirm result.
function GameEngine:message_continue(message) end

--- CalculateTextDimensions(const tstring& text, const Font* fontPtr) 
--- CalculateTextDimensions(const tstring& text, const Font* fontPtr, RECT rect) 

--- Sets color for drawing shapes.
--- @param color RGB
--- @return nil
function GameEngine:set_color(color) end

--- Sets font for text components in the engine.
--- @param font Font
--- @return nil
function GameEngine:set_font(font) end

--- Fills the screen with a solid color.
--- @param color RGB
--- @return boolean # True if successful
function GameEngine:fill_window_rect(color) end

--- Draws line from (x1, y1) to (x2, y2).
--- @param x1 integer
--- @param y1 integer
--- @param x2 integer
--- @param y2 integer
--- @return boolean # True if successful
function GameEngine:draw_line(x1, y1, x2, y2) end

--- Draw a rect from (left, top) to (right, bottom).
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return boolean # True if successful
--- @overload draw_rect(rect: Rect): boolean
function GameEngine:draw_rect(left, top, right, bottom) end

--- Fill a rect from (left, top) to (right, bottom).
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @param opacity integer # Value in range [0:255] to set the alpha channel
--- @return boolean # True if successful
--- @overload fill_rect(left, top, right, bottom, opacity): boolean
--- @overload fill_rect(rect: Rect): boolean
function GameEngine:fill_rect(left, top, right, bottom) end

--- Draw a rect from (left, top) to (right, bottom). You can specify border radius.
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @param radius integer
--- @return boolean # True if successful
--- @overload draw_round_rect(rect: Rect, radius: integer): boolean
function GameEngine:draw_round_rect(left, top, right, bottom, radius) end

--- Fill a rect from (left, top) to (right, bottom). You can specify border radius.
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @param radius integer
--- @return boolean # True if successful
---@overload fill_round_rect(rect: Rect, radius: integer): boolean
function GameEngine:fill_round_rect(left, top, right, bottom, radius) end 

--- Draw an oval from (left, top) to (right, bottom).
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return boolean # True if successful
function GameEngine:draw_oval(left, top, right, bottom) end

--- Draw an oval from (left, top) to (right, bottom).
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return boolean # True if successful
--- @overload fill_oval(left, top, right, bottom, opacity)
function GameEngine:fill_oval(left, top, right, bottom) end

--- Draw an arc from (left, top) to (right, bottom).
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @param start_degree integer # Starting angle from [-360:360]
--- @param angle integer # Extention of the arc from start_degree from [-360:360]
--- @return boolean # True if successful
function GameEngine:draw_arc(left, top, right, bottom, start_degree, angle) end

--- Fill an arc from (left, top) to (right, bottom).
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @param start_degree integer # Starting angle from [-360:360]
--- @param angle integer # Extention of the arc from start_degree from [-360:360]
--- @return boolean # True if successful
function GameEngine:fill_arc(left, top, right, bottom, start_degree, angle) end

--- Draw a string at (left, top).
--- @param text string
--- @param left integer
--- @param top integer
--- @return integer # Non-zero if successful
--- @overload DrawString(text, left, top, right, bottom) end
function GameEngine:draw_string(text, left, top) end

--- Draw a Bitmap at (left, top)
--- @param bitmap Bitmap
--- @param left integer
--- @param top integer
--- @return boolean # True if successful
--- @overload draw_bitmap(bitmap, left, top, source_rect) end
function GameEngine:draw_bitmap(bitmap, left, top) end

--- Draw a polygon.
--- @param points Point[] # Array of Point constituting the polygon
--- @param count integer # Number of vertices of the polygon
--- @param close boolean # Whether the polygon is a closed shape or not
--- @return boolean # True if successful
--- @overload draw_polygon(points, count) end
function GameEngine:draw_polygon(points, count, close) end

--- Fill a polygon.
--- @param points Point[] # Array of Point constituting the polygon
--- @param count integer # Number of vertices of the polygon
--- @param close boolean # Whether the polygon is a closed shape or not
--- @return boolean # True if successful
--- @overload fill_polygon(points, count) end
function GameEngine:fill_polygon(points, count, close) end

--- Get current draw color.
--- @return RGB
function GameEngine:get_draw_color() end

--- Clear the window.
--- @return boolean # True if successful
function GameEngine:repaint() end

--- Get the window title.
--- @return string
function GameEngine:get_title() end

--function GameEngine:GetInstance () end
--function GameEngine:GetWindow () end

--- Get the window width.
--- @return integer
function GameEngine:get_width() end

--- Get the window height.
--- @return integer
function GameEngine:get_height() end

--- Get the frame rate.
--- @return integer
function GameEngine:get_frame_rate() end

--- Get the frame delay.
--- @return integer
function GameEngine:get_frame_delay () end

--- Get the window position.
--- @return Point
function GameEngine:get_window_position() end

--function GameEngine:TabNext (HWND ChildWindow) end
--function GameEngine:TabPrevious (HWND ChildWindow) end

---------------------------------
--- ENUMS
---------------------------------
--- Defines the types of caller.
--- @enum CallerType
CALLER_TYPE = {
    text_box = 0,
    button = 1,
    timer = 2,
    audio = 3,
    video = 4
}

--- Defines shapes. Used in the HitRegion.
--- @enum Shape
SHAPE = {
    ellipse = 0,
    rectangle = 1
}

---------------------------------
--- CALLERS
---------------------------------
--- @class Caller
--- Base class of caller onjects like button, audio ...
Caller = {}

--- Gets type of the caller.
--- @return CallerType
function Caller:get_type() end

---------------------------------

--- @class Button
--- Class that creates a bindable button in the window.
Button = {}

--- Creates a new Button instance.
--- @param label? string
--- @return Button
function Button.new(label)

--- Sets external bounds of the button.
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return nil
function Button:set_bounds(left, top, right, bottom ) end

--- Changes the button label.
--- @param label string
--- @return nil
function Button:set_text(label) end

--- Sets font for the button's label.
--- @param font Font
--- @return nil
function Button:set_font(font) end

--- Set whether the button registers events or not.
--- @param enable boolean
--- @return nil
function Button:set_enabled(enable) end

--- Set button visibility to visible.
--- @return nil
function Button:show() end

--- Set button visibility to invisible.
--- @return nil
function Button:hide() end

--- Get the bounds of the button.
--- @return Rect
function Button:get_bounds() end

--- Get the label of the button.
--- @return string
function Button:get_text() end

--- Inherited Caller:get_type()
--- @return CallerType
function Button:get_type() end

---------------------------------

--- @class TextBox
--- Class that represents a user input text box located in the window.
TextBox = {}

--- Creates a new TextBox instance.
--- @param text? string
--- @return TextBox
function TextBox.new(text)

--- Sets external bounds of the TextBox.
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return nil
function TextBox:set_bounds(left, top, right, bottom ) end

--- Changes the TextBox's text.
--- @param text string
--- @return nil
function TextBox:set_text(text) end

--- Sets font for the TextBox.
--- @param font Font
--- @return nil
function TextBox:set_font(font) end

--- Sets the background color.
--- @param color RGB
--- @return nil
function TextBox:set_backcolor(color) end

--- Sets the text color.
--- @param color RGB
--- @return nil
function TextBox:set_forecolor(color) end

--- Set whether the button registers events or not.
--- @param enable boolean
--- @return nil
function TextBox:set_enabled(enable) end

--- Set button visibility to visible.
--- @return nil
function TextBox:show() end

--- Set button visibility to invisible.
--- @return nil
function TextBox:hide() end

--- Get the bounds of the TextBox.
--- @return Rect
function TextBox:get_bounds() end

--- Get the label of the TextBox.
--- @return string
function TextBox:get_text() end

--- Inherited Caller:get_type()
--- @return CallerType
function TextBox:get_type() end

---------------------------------

--- @class Audio
--- Class to manage and import audio files.
Audio = {}

--- This method needs to be invoked on a tick basis to progress the audio playtime.
--- @return nil
function Audio:tick( ) end

--- Start playing the audio track or unpause.
--- @param ms_start? integer # Starting point for the play in milliseconds
--- @param ms_stop? integer # Stopping point for the play in milliseconds
--- @return nil
function Audio:play( ms_start, ms_stop ) end

--- Pause play.
--- @return nil
function Audio:pause() end

--- Stop play.
--- @return nil
function Audio:stop() end

--- Set volume for the audio track.
--- @param volume integer
--- @return nil
function Audio:set_volume(volume) end

--- Set the track to repeat itself.
--- @param value boolean
--- @return nil 
function Audio:set_repeat(value) end

--- Get the name of the track.
--- @return string
function Audio:get_name() end

--- Get alias.
--- @return string
function Audio:get_alias() end

--- Get duration of the track.
--- @return integer
function Audio:get_duration() end

--- Is the track playing?
--- @return boolean
function Audio:is_playing() end

--- Is the track paused?
--- @return boolean
function Audio:is_paused() end

--- Is the track on repeat?
--- @return boolean
function Audio:get_repeat( ) end

--- Does the track exist?
--- @return boolean
function Audio:exists() end

--- Get the volume value.
--- @return integer
function Audio:get_volume() end

---------------------------------
--- RESOURCE TYPES
---------------------------------
--- @class Font
--- Class that points and manages fonts.
Font = {}

--- Creates a new Font instance.
--- @param font_name string # Path to font resource
--- @param bold boolean
--- @param italic boolean
--- @param underline boolean
--- @param size integer
--- @return Font
function Font.new(font_name, bold, italic, underline, size ) end

---------------------------------

--- @class Bitmap
--- Class representing a texture.
Bitmap = {}

--- Creates a bew Bitmap instance.
--- @param filename string # Path to resource.
--- @param create_alpha_channel? boolean # Needed for alpha channel textures. True by default.
--- @return Bitmap # A new Bitmap instance.
function Bitmap.new(filename, create_alpha_channel?) end

--- Sets a color to transparency for the texture.
--- @param color Color
--- @return nil
function Bitmap:set_transparency_color(color) end

--- Sets opacity of the texture.
--- @param opacity integer # Opacity value in percentage [0:100]
--- @return nil 
function Bitmap:set_opacity(opacity) end

--- Check whether the path provided exists or not.
--- @return boolean
function Bitmap:exists() end

--- Gets the width of the texture in pixels.
--- @return integer
function Bitmap:get_width()	end

--- Gets the height of the texture in pixels.
--- @return integer 
function Bitmap:get_height() end

--- Gets the color set to transparency for the texture.
--- @return Color
function Bitmap:get_transparency_color() end

--- Gets the opacity.
--- @return integer
function Bitmap:get_opacity() end

--- Returns true if the Bitmap has an alpha channel.
--- @return boolean
function Bitmap:has_alpha_channel() end

--- Saves the texture in the drive.
--- @param filename string # Path to the drive
--- @return boolean # True if successful
function Bitmap:save_to_file(filename) end

---------------------------------
--- DATA TYPES
---------------------------------
--- @class RGB
--- Struct containing 3 numbers to represent red, green, blue.
--- @field r integer # Red component [0:255]
--- @field g integer # Green component [0:255]
--- @field b integer # Blue component [0:255]
RGB = {}

--- Creates a new Color instance.
--- @param r integer # Red component [0:255]
--- @param g integer # Green component [0:255]
--- @param b integer # Blue component [0:255]
--- @return RGB # A new Color instance.
function RGB.new(r, g, b) end

---------------------------------

--- @class Rect
--- Struct representing a rectangle in 2D space.
--- @field left integer
--- @field top integer
--- @field right integer
--- @field bottom integer
Rect = {}

--- Creates a new Rect instance.
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return Rect
function Rect.new(left, top, right, bottom) end

---------------------------------

--- @class Point
--- Struct representing a point.
--- @field x? integer
--- @field y? integer
Point = {}

--- Creates a new Point instance.
--- @param x integer
--- @param y integer
--- @return Point
function Point.new(x, y) end

---------------------------------

--- @class float2
--- Struct representing a vector as a combination of 2 floating point numbers. It provides vector utility methods.
--- @field x number
--- @field y number
float2 = {}

--- Create a new float2 instance.
--- @param x? number
--- @param y? number
--- @return float2
--- @overload new(point: Point): float2
--- @overload new(from: Point, to: Point): float2
function float2.new(x, y) end

--- Get magnitude of vector.
--- @return number
function float2:magnitude() end

--- Get squared magnitude of vector.
--- @return number
function float2:sqr_magnitude() end

--- Normalize the vector.
--- @return number # The magnitude of the vector before normalization
function float2:normalize() end

--- Return a new normalized instance of the vector.
--- @return float2
function float2:normalized() end

--- Rounds the components to the nearest decimal
--- @return nil
function float2:round() end

--- -STATIC- Calculate dot product.
--- @param v0 float2 # First operand
--- @param v1 float2 # Second operand
--- @return number
function float2.dot(v0, v1) end

--- -STATIC- Calculate cross product.
--- @param v0 float2 # First operand
--- @param v1 float2 # Second operand
--- @return float2
function float2.cross(v0, v1) end

--- Convert float2 to Point.
--- @return Point
function float2:to_point( ) end

--- Adds the elements of the first operand to the corresponding elements of the second.
--- @param rhs float2
--- @return float2 # The resulting instance of float2
--- @overload __add(rhs: Point): Point end
function float2:__add(rhs) end

--- Subtracts the elements of the first operand to the corresponding elements of the second.
--- @param rhs float2
--- @return float2 # The resulting instance of float2
--- @overload __sub(rhs: Point): Point end
function float2:__sub(rhs) end

--- Scales the float2.
--- @param scale number
--- @return float2 # The resulting scaled instance of float2
function float2:__mul(scale) end

--- Scales the float2.
--- @param inverse_scale number
--- @return float2 # The resulting scaled instance of float2
function float2:__div(scale) end

--- Gets the opposite float2.
--- @return float2 # The resulting opposite instance of float2
function float2:__unm() end

--- Applies dot product between the 2 operands.
--- @param rhs float2
--- @return number # dot result
function float2:_bor(rhs) end

--- Applies cross product between the 2 operands.
--- @param rhs float2
--- @return float2 # dot result
function float2:_band(rhs) end

---------------------------------

--- @class HitRegion
--- Class that defines a portion of screen and grants helper methods to determine collisions with other points, bitmaps or hit-regions.
HitRegion = {}

--- Creates a new instance of HitRegion.
--- new(Shape, int, int, int, int) will create shape region within the specified bounds.
--- new(Point[], int) will create a segmented enclosed region following the points.
--- new(Bitmap) will create a region tracing using the bitmap info. Empty spots must be marked in magenta (RGB: [255, 0, 255]).
--- @param shape Shape
--- @param left integer
--- @param top integer
--- @param right integer
--- @param bottom integer
--- @return HitRegion
--- @overload new(point: Point[], count: integer): HitRegion
--- @overload new(bitmap: Bitmap): HitRegion
function HitRegion.new(shape, left, top, right, bottom) end

--- Moves the region over the given displacement
--- @param delta_x integer
--- @param delta_y integer
--- @return nil
function HitRegion:move(delta_x, delta_y) end

--- Checks for collision.
--- @param x integer
--- @param y integer
--- @return boolean
--- @overload hit_test(other: HitRegion): boolean
function HitRegion:hit_test(x, y)	end

--- Checks for collision. It's useful to determine the hitting point of two forms that barely touch.
--- @param other HitRegion
--- @return Point # Returns {-1000000, -1000000} if the regions don't overlap, and the center point of the overlapping region if they do overlap
function HitRegion:collision_test(other) end

--- Get the outer bounds of the region.
--- @return Rect # Returns the position + width and height of the smallest rectangle that encloses this region (in case of a rectangular region: the region itself).
function HitRegion:get_bounds() end		

--- Returns true if the hitregion was successfully created, false if not.
--- @return boolean
function HitRegion:exists() end

---------------------------------
--- @class SpriteInfo
--- Initializer class for Sprite.
--- @field bitmap Bitmap
--- @field rows integer
--- @field cols integer
--- @field delay integer
SpriteInfo = {}

--- Creates a new SpriteInfo instance.
--- @param bitmap Bitmap
--- @param rows integer
--- @param cols integer
--- @param delay integer
--- @return SpriteInfo
function SpriteInfo.new(bitmap, rows, cols, delay) end

---------------------------------
--- @class Sprite
--- Class that manages a sprite bitmap.
Sprite = {}

--- Creates a new Sprite instance.
--- @param info SpriteInfo
--- @return Sprite
--- @overload new(bitmap: Bitmap, rows: integer, cols: integer, delay: integer): Sprite
function Sprite.new(info) end

--- Paints the current frame at the position.
--- @param position Point
--- @return boolean # True if successful
--- @overload paint(x: integer, y: integer): boolean
function Sprite:paint(position) end

--- Elapses the sprite state.
--- @return nil
function Sprite:tick() end

--- Get current frame.
--- @return nil
function Sprite:get_frame() end
