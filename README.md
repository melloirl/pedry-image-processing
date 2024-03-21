# Pedry's Image Processing 🖼️

Compact, opinionated BMP image processing algorithms in C

*No external dependencies*

## Install 🛠️
To install and use the library, clone the repository and navigate to the project's root directory.

```bash
git clone https://github.com/melloirl/pedry-image-processing.git

cd pedry-image-processing
```

A Makefile is provided for your convenience, to compile the library. GCC compiler is required.

```bash
make # Build the library main file

make clean # Remove the compiled files
```

## Supported Formats 🖼️
Currently, only BMP images are supported. The library is designed to work with 24-bit uncompressed BMP images. Moving further, support for other formats might be added.

## Operations 🎨
### Copying images 🌑
Utilizes the internal BMP helpers to read, parse and copy BMP files down to its headers and pixel data. Works with both colored and greyscale images.

### Greyscale and colored blur 🔍
Utilizes simple convolutional filters to blur images. The kernel is generated programmatically and can be adjusted to fit the user's needs.

## Acknowledgements 🙏
 - [Abhijit Nathwani's Blog](https://abhijitnathwani.github.io/blog/)

## Reach out 📧
- [@melloirl](https://www.github.com/melloirl)

## License 📜
[MIT](https://choosealicense.com/licenses/mit/)
