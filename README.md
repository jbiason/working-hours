# Working Hours

A small projects built in as many languages as possible.

## The Idea

The whole idea of this project is to build a command line tool that:

- Receive at least the starting time the person started working;
- Get the time they went to lunch; as it is optional, it should be considered
	"12:00" if the user doesn't make this input;
- Get the time they returned from lunch; as it is option, it should be
	considered "13:00" if the user doesn't make this input.

The result would be showing how long the user still have to work to complete
their daily working hours (or if they are doing extra time).

For the total hours a person should work in the day, we'll consider 08:48 (or
8.8h, or 528 minutes).

## Examples

At 09:00

```
$ wh 08:00
So far, you worked 01:00
You still need to work 07:48
```

Reasoning: By starting at 08:00, up to 12:00, the user would've worked 4
hours; going back to work at 13:00, they would still need to work 4h48m, till
17:48.

At 18:00

```
$ wh 08:00 12:00 13:00
So far, you worked 09:00.
You did 00:12 hours of extra work.
```

## Languages

- [x] C
- [x] Clojure
- [ ] Elixir
- [ ] Erlang
- [ ] Haskell
- [ ] Java
- [ ] Lua
- [ ] Objective-C
- [ ] Pascal
- [ ] PHP
- [ ] Python
- [ ] Rust
- [ ] Swift
- [ ] TypeScript
- [ ] Bash?
