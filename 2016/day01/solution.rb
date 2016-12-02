

UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

TURN_RIGHT = 'R'
TURN_LEFT = 'L'

MAP_TURN_RIGHT = {
    UP => RIGHT,
    RIGHT => DOWN,
    DOWN => LEFT,
    LEFT => UP,
}

MAP_TURN_LEFT = {
    UP => LEFT,
    LEFT => DOWN,
    DOWN => RIGHT,
    RIGHT => UP,
}

MAP_TURN = {
    TURN_RIGHT => MAP_TURN_RIGHT,
    TURN_LEFT => MAP_TURN_LEFT,
}

def input_to_directions(input)
    return input.tr(',', '').split
end

def get_directions_test_1()
    return input_to_directions("R2, L3")
end

def get_directions_test_2()
    return input_to_directions("R2, R2, R2")
end

def get_directions_test_3()
    return input_to_directions("R5, L5, R5, R3")
end

def get_directions()
    return input_to_directions(File.read('input.txt'))
end

def main()
    direction_current = UP
    x = y = 0
    directions = get_directions
    directions.each do |direction|
        turn = direction[0]
        blocks = direction[1..-1].to_i
        # puts direction_current, turn, blocks
        direction_current = MAP_TURN[turn][direction_current]
        if direction_current == UP
            y += blocks
        elsif direction_current == RIGHT
            x += blocks
        elsif direction_current == DOWN
            y -= blocks
        elsif direction_current == LEFT
            x -= blocks
        else
            raise "INVALID DIRECTION!!!"
        end
    end
    puts "End coordinates: (#{x}, #{y})"
    distance = x.abs + y.abs
    puts "Distance from start: #{distance}"
end

main
