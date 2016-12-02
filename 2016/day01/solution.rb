
require 'set'

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
    return "R2, L3"
end

def get_directions_test_2()
    return "R2, R2, R2"
end

def get_directions_test_3()
    return "R5, L5, R5, R3"
end

def get_directions_test_4()
    return "R8, R4, R4, R8"
end

def get_directions()
    return File.read('input.txt')
end

def coordinate_to_s(x, y)
    return "#{x},#{y}"
end

def main()
    direction_current = UP
    x = y = 0
    coordinate = coordinate_to_s(x, y)
    coordinates_seen = Set.new([coordinate])
    has_seen_dupe = false
    input = get_directions
    # puts input
    directions = input_to_directions(input)
    directions.each do |direction|
        turn = direction[0]
        blocks = direction[1..-1].to_i
        # puts direction_current, turn, blocks
        direction_current = MAP_TURN[turn][direction_current]
        blocks.times do
            if direction_current == UP
                y += 1
            elsif direction_current == RIGHT
                x += 1
            elsif direction_current == DOWN
                y -= 1
            elsif direction_current == LEFT
                x -= 1
            else
                raise "INVALID DIRECTION!!!"
            end
            coordinate = coordinate_to_s(x, y)
            if coordinates_seen.add?(coordinate).nil? and not has_seen_dupe
                distance = x.abs + y.abs
                puts "First dupe coordinate: (#{x}, #{y}) (distance: #{distance})"
                has_seen_dupe = true
            end
        end
    end
    puts "End coordinates: (#{x}, #{y})"
    distance = x.abs + y.abs
    puts "Distance from start: #{distance}"
end

main
