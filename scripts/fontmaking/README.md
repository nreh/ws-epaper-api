# 🔤 Font Making

This file contains scripts for creating fonts from font files and images that can then be used by `TextElement`.

- **Font2Images.py**: Generate .bmp images of characters from a fontfile (supports truetype, bcf, pdf).

- **CreateEmpty.py**: Generate empty .bmp images from a characterset. Useful when you want to create a font from scratch.

- **Images2FontHeaders.py**: From a folder of .bmp images, create a C++ headerfile that can be imported and used by the the
  ws-epaper-api's `TextElement`.

## 🖼️ Step 1. Generate Images

The first step to using a font is to generate images for it. Use the **Font2Images.py** script to create images for each
character in the character set.

For example, this will generate 4 folders for 8pt, 12pt, 14pt, and 16pt sizes of the _Courier Prime_ font:

```
python3 Font2Images.py CourierPrime.ttf 'Courier Prime' 8 12 14 16
```

```
./CourierPrime_8pt/
./CourierPrime_12pt/
./CourierPrime_14pt/
./CourierPrime_16pt/
```

Alternatively, if you want to create a font from scratch, you can use the **CreateEmpty.py** script to generate blank images.

## ✏️ Step 2: Tweak Images

You can manually edit the generated bitmap files to fix any artifacts and rendering issues.

## 📃 Step 3: Convert to Header Files

Use the **Images2FontHeaders.py** script to generate C++ header files for each of the font-sizes generated. There will be 1
header file for each font size.

```
python3 Images2FontHeaders.py CourierPrime_8pt/ CourierPrime_12pt/ CourierPrime_14pt/ CourierPrime_16pt/
```

```
CourierPrime_8pt.h
CourierPrime_12pt.h
CourierPrime_14pt.h
CourierPrime_16pt.h
```

Now you can move these files into your include directory and use them in the `TextElement`!

```cpp
TextElement<CourierPrime_14pt font1> text1("Hello World!");
```

## 💡 Tips

- Sometimes, when converting to header files, some characters may have inverted coloring. This can happen when you edit the
  .bmp files manually. The **Images2FontHeaders.py** attempts to detect this and notifies you. You can rerun with the
  `--autoinvert` flag as a quick fix. If that doesn't work, you can get more granular control with the `--invertmask`
  argument.

- Use the `--license` argument in **Images2FontHeaders.py** to include a link to a license for all generated files.

- If you're having trouble generating fonts, you can use the `--nopack` flag which generates an uncompressed header file. You
  can then copy the generated 0s and 1s into a text editor and rearrange them until you see your characters appear. (_Note:
  the resulting header file will not be usable by TextElement_)

- Finally, run each script with the `-h` for extra details and features not mentioned here.
