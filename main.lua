local app = require('goso')
local r1 = app:new()

print("context", app.application)
print('obj', r1)

app:call(r1)

while true do
    app:gc()
    app:call(r1)
    app:sleep(1000*1000)
end