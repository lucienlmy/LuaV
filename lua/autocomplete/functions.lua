---@meta

do return end -- Prevent accidental execution.

---Checks if the [key](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) was pressed.
---@param key Keys The key to check.
---@return boolean # true if the key was pressed, false otherwise.
function wasKeyPressed(key) end

---Checks if the [key](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) is pressed.
---@param key Keys The key to check.
---@return boolean # true if the key is currently down, false otherwise.
function isKeyDown(key) end

---Checks if the [key](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) was released.
---@param key Keys The key to check.
---@return boolean # true if the key was released, false otherwise.
function wasKeyReleased(key) end

---Gets all vehicles in the game world.
---@return Vehicle[] # a table containing all vehicles in the game world.
function worldGetAllVehicles() end

---Gets all peds in the game world.
---@return Ped[] # a table containing all peds in the game world.
function worldGetAllPeds() end

---Gets all objects in the game world.
---@return Object[] # a table containing all objects in the game world.
function worldGetAllObjects() end

---Gets all pickups in the game world.
---@return Pickup[] # a table containing all pickups in the game world.
function worldGetAllPickups() end

---Gets the current game version.
---@return integer # the game version.
function getGameVersion() end

---Gets the current plugin version.
---
---It has this format: *.x.x (MAJOR.MINOR.PATCH)
---@return integer # the plugin version.
function getPluginVersion() end

---Sets the function to be called when one of the following happens:
---
---- The script throws an error
---- The script finishes
---- The scripts are being reloaded
---- The plugin is being reloaded
---@param f function? # the function to be called on unload. If nil, removes the unload handler.
function setUnloadHandler(f) end