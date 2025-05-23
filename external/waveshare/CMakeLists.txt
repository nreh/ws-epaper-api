cmake_minimum_required(VERSION 3.14)

# VALID EPD FILES:
set(
    HEADER_FILES

    DrawTargets/EPD_2in13_V4.h
    DrawTargets/EPD_4in2_V2.h
    DrawTargets/EPD_13in3b.h
    DrawTargets/EPD_10in2b.h
    DrawTargets/EPD_13in3b.h
    DrawTargets/EPD_13in3k.h
    DrawTargets/EPD_1in02d.h
    DrawTargets/EPD_1in54.h
    DrawTargets/EPD_1in54_DES.h
    DrawTargets/EPD_1in54_V2.h
    DrawTargets/EPD_1in54b.h
    DrawTargets/EPD_1in54b_V2.h
    DrawTargets/EPD_1in54c.h
    DrawTargets/EPD_1in64g.h
    DrawTargets/EPD_2in13.h
    DrawTargets/EPD_2in13_DES.h
    DrawTargets/EPD_2in13_V2.h
    DrawTargets/EPD_2in13_V3.h
    DrawTargets/EPD_2in13_V4.h
    DrawTargets/EPD_2in13b_V3.h
    DrawTargets/EPD_2in13b_V4.h
    DrawTargets/EPD_2in13bc.h
    DrawTargets/EPD_2in13d.h
    DrawTargets/EPD_2in13g.h
    DrawTargets/EPD_2in15b.h
    DrawTargets/EPD_2in15g.h
    DrawTargets/EPD_2in36g.h
    DrawTargets/EPD_2in66.h
    DrawTargets/EPD_2in66b.h
    DrawTargets/EPD_2in66g.h
    DrawTargets/EPD_2in7.h
    DrawTargets/EPD_2in7_V2.h
    DrawTargets/EPD_2in7b.h
    DrawTargets/EPD_2in7b_V2.h
    DrawTargets/EPD_2in9.h
    DrawTargets/EPD_2in9_DES.h
    DrawTargets/EPD_2in9_V2.h
    DrawTargets/EPD_2in9b_V3.h
    DrawTargets/EPD_2in9b_V4.h
    DrawTargets/EPD_2in9bc.h
    DrawTargets/EPD_2in9d.h
    DrawTargets/EPD_3in0g.h
    DrawTargets/EPD_3in52.h
    DrawTargets/EPD_3in7.h
    DrawTargets/EPD_4in01f.h
    DrawTargets/EPD_4in2.h
    DrawTargets/EPD_4in26.h
    DrawTargets/EPD_4in2_V2.h
    DrawTargets/EPD_4in2b_V2.h
    DrawTargets/EPD_4in2bc.h
    DrawTargets/EPD_4in37b.h
    DrawTargets/EPD_4in37g.h
    DrawTargets/EPD_5in65f.h
    DrawTargets/EPD_5in79.h
    DrawTargets/EPD_5in79b.h
    DrawTargets/EPD_5in79g.h
    DrawTargets/EPD_5in83.h
    DrawTargets/EPD_5in83_V2.h
    DrawTargets/EPD_5in83b_V2.h
    DrawTargets/EPD_5in83bc.h
    DrawTargets/EPD_5in84.h
    DrawTargets/EPD_7in3e.h
    DrawTargets/EPD_7in3f.h
    DrawTargets/EPD_7in3g.h
    DrawTargets/EPD_7in5.h
    DrawTargets/EPD_7in5_HD.h
    DrawTargets/EPD_7in5_V2.h
    DrawTargets/EPD_7in5b_HD.h
)
set(
    NAMESPACED_SOURCE_FILES

    DrawTargets/EPD_2in13_V4.cpp
    DrawTargets/EPD_4in2_V2.cpp
    DrawTargets/EPD_13in3b.cpp
    DrawTargets/EPD_10in2b.cpp
    DrawTargets/EPD_13in3b.cpp
    DrawTargets/EPD_13in3k.cpp
    DrawTargets/EPD_1in02d.cpp
    DrawTargets/EPD_1in54.cpp
    DrawTargets/EPD_1in54_DES.cpp
    DrawTargets/EPD_1in54_V2.cpp
    DrawTargets/EPD_1in54b.cpp
    DrawTargets/EPD_1in54b_V2.cpp
    DrawTargets/EPD_1in54c.cpp
    DrawTargets/EPD_1in64g.cpp
    DrawTargets/EPD_2in13.cpp
    DrawTargets/EPD_2in13_DES.cpp
    DrawTargets/EPD_2in13_V2.cpp
    DrawTargets/EPD_2in13_V3.cpp
    DrawTargets/EPD_2in13_V4.cpp
    DrawTargets/EPD_2in13b_V3.cpp
    DrawTargets/EPD_2in13b_V4.cpp
    DrawTargets/EPD_2in13bc.cpp
    DrawTargets/EPD_2in13d.cpp
    DrawTargets/EPD_2in13g.cpp
    DrawTargets/EPD_2in15b.cpp
    DrawTargets/EPD_2in15g.cpp
    DrawTargets/EPD_2in36g.cpp
    DrawTargets/EPD_2in66.cpp
    DrawTargets/EPD_2in66b.cpp
    DrawTargets/EPD_2in66g.cpp
    DrawTargets/EPD_2in7.cpp
    DrawTargets/EPD_2in7_V2.cpp
    DrawTargets/EPD_2in7b.cpp
    DrawTargets/EPD_2in7b_V2.cpp
    DrawTargets/EPD_2in9.cpp
    DrawTargets/EPD_2in9_DES.cpp
    DrawTargets/EPD_2in9_V2.cpp
    DrawTargets/EPD_2in9b_V3.cpp
    DrawTargets/EPD_2in9b_V4.cpp
    DrawTargets/EPD_2in9bc.cpp
    DrawTargets/EPD_2in9d.cpp
    DrawTargets/EPD_3in0g.cpp
    DrawTargets/EPD_3in52.cpp
    DrawTargets/EPD_3in7.cpp
    DrawTargets/EPD_4in01f.cpp
    DrawTargets/EPD_4in2.cpp
    DrawTargets/EPD_4in26.cpp
    DrawTargets/EPD_4in2_V2.cpp
    DrawTargets/EPD_4in2b_V2.cpp
    DrawTargets/EPD_4in2bc.cpp
    DrawTargets/EPD_4in37b.cpp
    DrawTargets/EPD_4in37g.cpp
    DrawTargets/EPD_5in65f.cpp
    DrawTargets/EPD_5in79.cpp
    DrawTargets/EPD_5in79b.cpp
    DrawTargets/EPD_5in79g.cpp
    DrawTargets/EPD_5in83.cpp
    DrawTargets/EPD_5in83_V2.cpp
    DrawTargets/EPD_5in83b_V2.cpp
    DrawTargets/EPD_5in83bc.cpp
    DrawTargets/EPD_5in84.cpp
    DrawTargets/EPD_7in3e.cpp
    DrawTargets/EPD_7in3f.cpp
    DrawTargets/EPD_7in3g.cpp
    DrawTargets/EPD_7in5.cpp
    DrawTargets/EPD_7in5_HD.cpp
    DrawTargets/EPD_7in5_V2.cpp
    DrawTargets/EPD_7in5b_HD.cpp
)

add_library(
    epaper STATIC

    epaper/Config/DEV_Config.c

    # epaper/Config/DEV_Config.h
    epaper/Config/Debug.h
    ${NAMESPACED_SOURCE_FILES}

    # ${SOURCE_FILE}
    # ${HEADER_FILE}
    epaper/Fonts/font12.c
    epaper/Fonts/font12CN.c
    epaper/Fonts/font16.c
    epaper/Fonts/font20.c
    epaper/Fonts/font24.c
    epaper/Fonts/font24CN.c
    epaper/Fonts/font8.c
    epaper/Fonts/fonts.h
)
target_compile_features(
    epaper PRIVATE cxx_std_17
)
target_include_directories(epaper PUBLIC ./epaper/Config ./epaper ./epaper/Fonts ./epaper/GUI ../bcm2835/src ./DrawTargets/)