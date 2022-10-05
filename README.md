# c template

Sample C project.

## Requirements

- GCC compilator
- GNU Make

> NOTE: It's possible to replace compilator. Just change `CC` variable in `Makefile` and be sure all flags was matched by your compilator.

## Run

1. Build project

```shell
make
```

2. Run

```shell
make run
```

OR

```shell
./build/main
```

3. Rebuild and run

```shell
make all run
```

## Clean

In case if you want to clean your project from generated object files and executables run:

```shell
make clean
```

