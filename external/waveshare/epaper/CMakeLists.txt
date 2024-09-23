cmake_minimum_required(VERSION 3.14)

# VALID EPD FILES:

# e-Paper/EPD_10in2b.c
# e-Paper/EPD_10in2b.h
# e-Paper/EPD_13in3b.c
# e-Paper/EPD_13in3b.h
# e-Paper/EPD_13in3k.c
# e-Paper/EPD_13in3k.h
# e-Paper/EPD_1in02d.c
# e-Paper/EPD_1in02d.h
# e-Paper/EPD_1in54.c
# e-Paper/EPD_1in54.h
# e-Paper/EPD_1in54_DES.c
# e-Paper/EPD_1in54_DES.h
# e-Paper/EPD_1in54_V2.c
# e-Paper/EPD_1in54_V2.h
# e-Paper/EPD_1in54b.c
# e-Paper/EPD_1in54b.h
# e-Paper/EPD_1in54b_V2.c
# e-Paper/EPD_1in54b_V2.h
# e-Paper/EPD_1in54c.c
# e-Paper/EPD_1in54c.h
# e-Paper/EPD_1in64g.c
# e-Paper/EPD_1in64g.h
# e-Paper/EPD_2in13.c
# e-Paper/EPD_2in13.h
# e-Paper/EPD_2in13_DES.c
# e-Paper/EPD_2in13_DES.h
# e-Paper/EPD_2in13_V2.c
# e-Paper/EPD_2in13_V2.h
# e-Paper/EPD_2in13_V3.c
# e-Paper/EPD_2in13_V3.h
# e-Paper/EPD_2in13_V4.c
# e-Paper/EPD_2in13_V4.h
# e-Paper/EPD_2in13b_V3.c
# e-Paper/EPD_2in13b_V3.h
# e-Paper/EPD_2in13b_V4.c
# e-Paper/EPD_2in13b_V4.h
# e-Paper/EPD_2in13bc.c
# e-Paper/EPD_2in13bc.h
# e-Paper/EPD_2in13d.c
# e-Paper/EPD_2in13d.h
# e-Paper/EPD_2in13g.c
# e-Paper/EPD_2in13g.h
# e-Paper/EPD_2in15b.c
# e-Paper/EPD_2in15b.h
# e-Paper/EPD_2in15g.c
# e-Paper/EPD_2in15g.h
# e-Paper/EPD_2in36g.c
# e-Paper/EPD_2in36g.h
# e-Paper/EPD_2in66.c
# e-Paper/EPD_2in66.h
# e-Paper/EPD_2in66b.c
# e-Paper/EPD_2in66b.h
# e-Paper/EPD_2in66g.c
# e-Paper/EPD_2in66g.h
# e-Paper/EPD_2in7.c
# e-Paper/EPD_2in7.h
# e-Paper/EPD_2in7_V2.c
# e-Paper/EPD_2in7_V2.h
# e-Paper/EPD_2in7b.c
# e-Paper/EPD_2in7b.h
# e-Paper/EPD_2in7b_V2.c
# e-Paper/EPD_2in7b_V2.h
# e-Paper/EPD_2in9.c
# e-Paper/EPD_2in9.h
# e-Paper/EPD_2in9_DES.c
# e-Paper/EPD_2in9_DES.h
# e-Paper/EPD_2in9_V2.c
# e-Paper/EPD_2in9_V2.h
# e-Paper/EPD_2in9b_V3.c
# e-Paper/EPD_2in9b_V3.h
# e-Paper/EPD_2in9b_V4.c
# e-Paper/EPD_2in9b_V4.h
# e-Paper/EPD_2in9bc.c
# e-Paper/EPD_2in9bc.h
# e-Paper/EPD_2in9d.c
# e-Paper/EPD_2in9d.h
# e-Paper/EPD_3in0g.c
# e-Paper/EPD_3in0g.h
# e-Paper/EPD_3in52.c
# e-Paper/EPD_3in52.h
# e-Paper/EPD_3in7.c
# e-Paper/EPD_3in7.h
# e-Paper/EPD_4in01f.c
# e-Paper/EPD_4in01f.h
# e-Paper/EPD_4in0e.c
# e-Paper/EPD_4in0e.h
# e-Paper/EPD_4in2.c
# e-Paper/EPD_4in2.h
# e-Paper/EPD_4in26.c
# e-Paper/EPD_4in26.h
# e-Paper/EPD_4in2_V2.c
# e-Paper/EPD_4in2_V2.h
# e-Paper/EPD_4in2b_V2.c
# e-Paper/EPD_4in2b_V2.h
# e-Paper/EPD_4in2b_V2_old.c
# e-Paper/EPD_4in2b_V2_old.h
# e-Paper/EPD_4in2bc.c
# e-Paper/EPD_4in2bc.h
# e-Paper/EPD_4in37b.c
# e-Paper/EPD_4in37b.h
# e-Paper/EPD_4in37g.c
# e-Paper/EPD_4in37g.h
# e-Paper/EPD_5in65f.c
# e-Paper/EPD_5in65f.h
# e-Paper/EPD_5in79.c
# e-Paper/EPD_5in79.h
# e-Paper/EPD_5in79b.c
# e-Paper/EPD_5in79b.h
# e-Paper/EPD_5in79g.c
# e-Paper/EPD_5in79g.h
# e-Paper/EPD_5in83.c
# e-Paper/EPD_5in83.h
# e-Paper/EPD_5in83_V2.c
# e-Paper/EPD_5in83_V2.h
# e-Paper/EPD_5in83b_V2.c
# e-Paper/EPD_5in83b_V2.h
# e-Paper/EPD_5in83bc.c
# e-Paper/EPD_5in83bc.h
# e-Paper/EPD_5in84.c
# e-Paper/EPD_5in84.h
# e-Paper/EPD_7in3e.c
# e-Paper/EPD_7in3e.h
# e-Paper/EPD_7in3f.c
# e-Paper/EPD_7in3f.h
# e-Paper/EPD_7in3g.c
# e-Paper/EPD_7in3g.h
# e-Paper/EPD_7in5.c
# e-Paper/EPD_7in5.h
# e-Paper/EPD_7in5_HD.c
# e-Paper/EPD_7in5_HD.h
# e-Paper/EPD_7in5_V2.c
# e-Paper/EPD_7in5_V2.h
# e-Paper/EPD_7in5_V2_old.c
# e-Paper/EPD_7in5_V2_old.h
# e-Paper/EPD_7in5b_HD.c
# e-Paper/EPD_7in5b_HD.h
# e-Paper/EPD_7in5b_V2.c
# e-Paper/EPD_7in5b_V2.h
# e-Paper/EPD_7in5b_V2_old.c
# e-Paper/EPD_7in5b_V2_old.h
# e-Paper/EPD_7in5bc.c
# e-Paper/EPD_7in5bc.h
if(NOT DEFINED EPD_MODEL)
    message(
        FATAL_ERROR
        "You must define an EPD_MODEL that matches the E-Paper display you're using"
        "\nSee the README for details on each model to help you understand which one to choose."
    )
endif()

set(SOURCE_FILE "${CMAKE_SOURCE_DIR}/external/waveshare/epaper/e-Paper/${EPD_MODEL}.c")
set(HEADER_FILE "${CMAKE_SOURCE_DIR}/external/waveshare/epaper/e-Paper/${EPD_MODEL}.h")

if(EXISTS ${SOURCE_FILE} AND EXISTS ${HEADER_FILE})
    add_library(
        epaper SHARED

        Config/DEV_Config.c
        Config/DEV_Config.h
        Config/Debug.h

        ${SOURCE_FILE}
        ${HEADER_FILE}

        Fonts/font12.c
        Fonts/font12CN.c
        Fonts/font16.c
        Fonts/font20.c
        Fonts/font24.c
        Fonts/font24CN.c
        Fonts/font8.c
        Fonts/fonts.h

        GUI/GUI_BMPfile.c
        GUI/GUI_BMPfile.h
        GUI/GUI_Paint.c
        GUI/GUI_Paint.h
    )

    target_include_directories(epaper PUBLIC ./Config ./epaper ./Fonts ./GUI ../../bcm2835/src)

else()
    message(FATAL_ERROR
        "The specified files for the EPD_MODEL '${EPD_MODEL}' do not exist: ${SOURCE_FILE}, ${HEADER_FILE}\n"
        "This probably means you mispelled or are using an incorrect value for EPD_MODEL. See the README for valid values."
    )
endif()