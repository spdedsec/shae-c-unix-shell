# SHAE C Unix Shell

A Unix-style command shell written in C.

## Features
- Command prompt with SHAE styling
- Built-in commands: cd, help, exit
- External command execution via fork/execvp
- Command history (readline)
- Argument tokenization

## Install
```bash
./scripts/install.sh
# Or manually:
gcc -O2 -std=c11 -o shae-shell src/shell.c -lreadline
./shae-shell
```

## Usage
```bash
./shae-shell
> ls -la
> cd /tmp
> help
> exit
```

## Design
Follows SHAE Field Manual: warm paper #F2EEE5, ink #191712, oxide #B3341B, 0px radius, 1px borders.
