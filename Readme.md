# CS50 Problem Set 5 - Forensic Card Image Recovery

This repository contains my solution for Problem Set 5 of CS50's Intro to Computer Science course. The task is to recover JPEG files from a forensic card image.

## Description

The program scans a forensic image of a memory card and recovers JPEG files. It reads the data in 512-byte chunks and identifies the beginning of a JPEG file by checking for specific byte patterns. When a new JPEG file is detected, it is saved with a sequential filename.

## Usage

To compile the program, use:

```bash
gcc -o recover recover.c
```

To run the program, use:

```bash
./recover forensic_image.raw
```

Replace `forensic_image.raw` with the path to your forensic card image file.

## Files

- `recover.c`: The main program file containing the logic for recovering JPEG files.

## License

This project is licensed under the [MIT License](https://opensource.org/license/mit)
