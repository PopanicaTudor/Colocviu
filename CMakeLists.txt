cmake_minimum_required(VERSION 3.10)

project(CoffeeJourney)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Găsește fișierele sursă pentru Menu
file(GLOB MENU_SOURCES src/menu/*.cpp)

# Găsește fișierele sursă pentru Employee
file(GLOB EMPLOYEE_SOURCES src/employee/*.cpp)

# Găsește fișierele sursă pentru Event
file(GLOB EVENT_SOURCES src/event/*.cpp)

# Găsește fișierele sursă pentru Product
file(GLOB PRODUCT_SOURCES src/inventory/*.cpp)

# Găsește fișierele sursă pentru Order
file(GLOB ORDER_SOURCES src/order/*.cpp)

# Găsește fișierele sursă pentru Report
file(GLOB REPORT_SOURCES src/report/*.cpp)

# Găsește fișierele sursă pentru Util
file(GLOB UTIL_SOURCES src/util/*.cpp)

# Creează executabilul
add_executable(CoffeeJourney src/main.cpp ${MENU_SOURCES} ${EMPLOYEE_SOURCES} ${EVENT_SOURCES} ${PRODUCT_SOURCES} ${ORDER_SOURCES} ${REPORT_SOURCES} ${UTIL_SOURCES})

# Include toate fișierele sursă
target_include_directories(CoffeeJourney PUBLIC src)