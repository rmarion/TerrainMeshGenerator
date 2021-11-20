# Terrain Mesh Generator

## What is it?

This is a library for generating generic terrain meshes for use with various engines / systems.
It's intended to be lightweight and fast, while easily integrating with consumers (particularly
UE4 at this point).

## Usage

### Terrain Mesh

The terrain mesh class can be constructed using a vector of floats, and contains a variety of
properties that are commonly used by game engines in their meshes. A spacing value must also be
provided, which will be the space between vertices.

Terrain meshes are template classes, so the consumer can determine what numeric value (eg float)
works best for them.

### Vec2 / Vec3

Represents a two / three dimensional point respectively. These contain floats, as they are
typically used by game engines.

Vec2s and Vec3s are both template classes, and their types will match the one used for the
terrain mesh.
