# Rockette 🚀

Rockette (/ʁɔ.kɛt/, borrowed from French [_roquette_](https://fr.wikipedia.org/wiki/Roquette_(plante))) is an open source platform for development of graphical applications for embedded systems.

Its purpose is to simplify development of custom graphical applications using OpenGL ES 2.0. It enables development on Windows/Linux/macOS using OpenGL ES 2.0 (using [ANGLE](https://github.com/google/angle)), so you can implement everything on your favourite development platform, and then just cross-compile it to run on the target platform.

It's super light-weight, and has basic features already included:

- Basic OTF/TTF font loading/rendering
- TGA texture loader
- Basic shaders
- Example [gRPC](https://grpc.io/) integration

The main use case, for now, is to create graphical applications for the Raspberry Pi, but it should work on any other embedded system that runs Linux and supports OpenGL ES 2.0.

## Integration

Rockette uses [gRPC](https://grpc.io/) to receive the data to be displayed. You can use any programming language supported by gRPC to send the data to be displayed, even over a network if you prefer.

Check [INTEGRATION.md](INTEGRATION.md).

## Development

It's written in C++ with very minimal dependencies. Development can be done on Windows, Linux or macOS, and then cross-compiled to run on a Raspberry Pi, for example.

Check the development environment instructions:

- [Windows](README-dev-windows.md)
- [macOS](README-dev-mac.md)
- [Linux](README-dev-linux.md)

## Documentation

Check [DOCUMENTATION.md](DOCUMENTATION.md).