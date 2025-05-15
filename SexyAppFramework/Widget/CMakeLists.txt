# CMakeLists.txt
target_include_directories(${PROJECT_NAME} PUBLIC
	../
)

target_sources(${PROJECT_NAME} PRIVATE
    buttonlistener.h
    buttonwidget.h
    checkbox.h
    checkboxlistener.h
    dialog.h
    dialogbutton.h
    dialoglistener.h
    editlistener.h
    editwidget.h
    hyperlinkwidget.h
    insets.h
    listlistener.h
    listwidget.h
    scrollbarwidget.h
    scrollbuttonwidget.h
    scrolllistener.h
    slider.h
    sliderlistener.h
    textwidget.h
    flashwidget.h
    widget.h
    widgetcontainer.h
    widgetmanager.h
    buttonwidget.cpp
    checkbox.cpp
    dialog.cpp
    dialogbutton.cpp
    editwidget.cpp
    hyperlinkwidget.cpp
    insets.cpp
    listwidget.cpp
    scrollbarwidget.cpp
    scrollbuttonwidget.cpp
    slider.cpp
    textwidget.cpp
    flashwidget.cpp
    widget.cpp
    widgetcontainer.cpp
    widgetmanager.cpp
)
