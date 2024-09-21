add_library(bcm2835 STATIC src/bcm2835.c src/bcm2835.h)
target_include_directories(bcm2835 PUBLIC ./src)