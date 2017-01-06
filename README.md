# Recovery.unity

This program allows to read Unity scene's hierarchy and remove objects. It is useful if  the scene gets corrupted or does not load due to too many objects inside it.

### Compiling

Run make.

Enjoy.

### Usage

1. Enter input and output paths (relative to current dirrectory).
2. Press 1 to enter edit mode.
3. After finishing making changes, type -2 until you get to the main options.
4. Press 2 to save changes if needed.
5. Press 3 to quit.

### Limitations

1. Only works with text serialized scenes. Even if the scene does not load, unity should be able to reserialize it into text, you need to force text serialization in edit/editor settings.

### TODO

1. Make the interface easier and more efficent. It would work similarly like Midnight Commander.
