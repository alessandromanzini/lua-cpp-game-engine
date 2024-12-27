--- @class file_utils
--- Helper class to manage project resources.
local file_utils = {}

local resources_path = "./resources/"

--- Checks whether a file exists.
--- @param path string
--- @return boolean
function file_utils.file_exists(path)
   local f = io.open(path, "r")
   return f ~= nil and io.close(f)
end

--- Function that returns the path to the requested resource.
--- @param filename string
--- @return string|nil # Returns nil if filename was not found
function file_utils.get_resource(filename)
    local resource = resources_path..filename
    if file_utils.file_exists(resource) then
        return resource 
    else 
        error("Cannot locate resource file '"..filename.."' ...\nPerhaps you forgot to re-configure globbed cache?\n")
        return nil
    end
end

--- Audio class factory.
--- @param filename string
--- @return Audio
function file_utils.CreateAudio(filename)
    return Audio.new(file_utils.get_resource(filename))
end

return file_utils