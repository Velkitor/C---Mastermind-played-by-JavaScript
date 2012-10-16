log "hello_world"
@direction = 120
for i in [1..10]
  @speed += i/7
  move()
  log("Java Script says that X: #{@x} Y: #{@y} .")