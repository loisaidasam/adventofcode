
KEYPAD = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
]

MIN = 0
MAX = 2

MAP_MOVEMENT = {
    'U' => [0, -1],
    'R' => [1, 0],
    'D' => [0, 1],
    'L' => [-1, 0],
}

def get_input()
    return File.readlines('input.txt')
end

def get_input_test()
    return ["ULL", "RRDDD", "LURDL", "UUUUD"]
end

def get_key(line, x, y)
    # puts line
    line.length.times do |position|
        key = line[position]
        movement = MAP_MOVEMENT[key]
        next if movement.nil?
        x += movement[0]
        y += movement[1]
        if x < MIN
            x = MIN
        elsif x > MAX
            x = MAX
        end
        if y < MIN
            y = MIN
        elsif y > MAX
            y = MAX
        end
        # puts "(#{x}, #{y})"
    end
    return x, y
end

def main()
    lines = get_input
    # puts lines
    x = y = 1
    lines.each do |line|
        x, y = get_key(line, x, y)
        print KEYPAD[y][x]
    end
    puts
end

main