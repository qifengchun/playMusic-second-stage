cmake_minimum_required(VERSION 3.23)

project(CloudMusic VERSION 0.1 LANGUAGES CXX)
file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QRC_SOURCE_FILES Resource.qrc)

find_package(Qt6 6.2 COMPONENTS Quick Core Network Widgets Gui Qml REQUIRED)
INCLUDE_DIRECTORIES("/usr/include/taglib")
qt6_add_resources(Imag Resource.qrc)
qt_add_executable(appCloudMusic
    main.cpp
    ${QRC_FILES}
    song.cpp song.h
    lyric.cpp lyric.h
    kugousong.cpp kugousong.h ${Imag}
)

qt_add_qml_module(appCloudMusic
    URI CloudMusic
    VERSION 1.0
    QML_FILES main.qml
    Actions.qml
    Content.qml
    Dialogs.qml
    KuGou.qml
    LyricPage.qml
    SkinDialog.qml
    SongSearchDialog.qml
    TrackInformationDialog.qml
)

qt6_add_resources(QRC_FILES ${QRC_SOURCE_FILES})

SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

set_target_properties(appCloudMusic PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appCloudMusic
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appCloudMusic
    PRIVATE Qt6::Quick tag Qt6::Core Qt6::Network Qt6::Widgets Qt6::Gui Qt6::Qml)
