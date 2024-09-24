import keyboard
import turtle

WINDOW = 600

def main():
    width = input('Width? ')
    height = input('Height? ')
    if(width == '' or height == ''):
        width = WINDOW
        height = WINDOW
    width = int(width)
    height = int(height)
    window(width, height)
    width /= 2
    height /= 2
    
    draw_pad = 'stop'
    keyboard.read_key()


    while draw_pad != 'q':
        func_dir = direction()
        if func_dir is not None:
            draw_pad = func_dir
        turtle.forward(1)
        replace = turtle.isdown()
        limits(width, height, draw_pad, replace)


def direction():   
    if keyboard.is_pressed('a'):
        turtle.setheading(180)
        return 'left'
    elif keyboard.is_pressed('w'):
        turtle.setheading(90)
        return 'up'
    elif keyboard.is_pressed('d'):
        turtle.setheading(0)
        return 'right'
    elif keyboard.is_pressed('s'):
        turtle.setheading(270)
        return 'down'
    elif keyboard.is_pressed('q'):
        return 'q'
    while keyboard.is_pressed('p'):
        if turtle.isdown():
            turtle.up()
        else:
            turtle.down()

    return None

def limits(width, height, draw_pad, replace):
    if draw_pad == 'left':
        if turtle.xcor() == (0 - width):
            turtle.up()
            turtle.goto(width, turtle.ycor())
            if replace:
                turtle.down()
    if draw_pad == 'right':
        if turtle.xcor() == width:
            turtle.up()
            turtle.goto((0-width), turtle.ycor())
            if replace:
                turtle.down()
    if draw_pad == 'up':
        if turtle.ycor() == height:
            turtle.up()
            turtle.goto(turtle.xcor(), (0 - height))
            if replace:
                turtle.down()
    if draw_pad == 'down':
        if turtle.ycor() == (0 - height):
            turtle.up()
            turtle.goto(turtle.xcor(), height)
            if replace:
                turtle.down()
        
def window(width, height):
    turtle.setup(width, height)
    turtle.up()
    turtle.speed(10)
    turtle.shape('turtle')
    
main()
