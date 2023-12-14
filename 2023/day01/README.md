# Day 1 - Bash fu

## Part 1

### First, regex

Get two files, one of first digit, and one of last digit

```
$ cat input.txt | sed -nr 's/[^0-9]*([0-9]).*/\1/p' > first.txt
$ cat input.txt | rev | sed -nr 's/[^0-9]*([0-9]).*/\1/p' > last.txt
```

Resources

- regex digits in sed: https://superuser.com/a/513416
- rev: https://www.cyberciti.biz/faq/how-to-reverse-string-in-unix-shell-script/

### Next, glue and add

Glue those numbers all together and add 'em all up

```
$ echo $(($(paste first.txt last.txt | awk -F ' ' '{print $1$2}' | tr '\n' '+')0))
55172
```

Resources

- glue (via paste): https://stackoverflow.com/a/1036015/1406873
- add up: https://stackoverflow.com/a/77164144/1406873

## Part 2

To continue bash-fu'ing my way through, or not?

The same approach could probably still apply, but ..

for `first.txt` maybe we look for the first occurrence of '(one|two|three|...|nine|[0-9])'

and

for `last.txt` maybe we reverse the string and then look for the first occurrence of '(eno|owt|eerht|...|enin|[0-9]'

and 

for both files we sub like: `s/one|eno/1/ | s/two|owt/2/ | ... | s/nine|enin/9`

...

Running into a priority issue here -

```
$ echo twone | sed -nr 's/.*(one|two).*/\1/p' 
one
```

Looks like it favors the label definition order even though the string "two" occurs *before* "one"

### Rabbit hole ...

first letters:

```
one     o
two     t
three   t
four    f
five    f
six     s
seven   s
eight   e
nine    n
```

last letters:

```
one     e
two     o
three   e
four    r
five    e
six     x
seven   n
eight   t
nine    e
```

overlaps:

```
oneight
twone
threeight
fiveight
sevenine
eightwo
eighthree
nineight
```

problem overlaps, where the higher number comes first:

```
twone
eightwo
eighthree
nineight
```

and even these can have problem overlaps:

```
eightwone
nineightwo
nineighthree
```

and one of those can have a problem overlap

```
nineightwone
```

to resolve these, you'd have to replace them all with the first occurring thing:

```
- s/twone/two/
- s/eightwo/eight/
- s/eighthree/eight/
- s/nineight/nine/
- s/eightwone/eight/
- s/nineightwo/nine/
- s/nineighthree/nine/
- s/nineightwone/nine/
```

but then we need to also worry about the reverse strings ... woof

maybe we just use python or something instead ...
