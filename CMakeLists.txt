cmake_minimum_required(VERSION 3.16)

project(CRUD LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Modules Qt requis
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql Charts QuickWidgets Positioning Quick)

# Fichiers sources et headers
set(SOURCES
    main.cpp
    mainwindow.cpp
    connexion.cpp
    client.cpp
)

set(HEADERS
    mainwindow.h
    connexion.h
    client.h
)

set(FORMS
    mainwindow.ui
)

set(QML_FILES
    MapView.qml
)

# Génération des fichiers UI
qt_wrap_ui(UI_HEADERS ${FORMS})

# Ajouter l’exécutable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_HEADERS}
    ${QML_FILES}
)

# Lier les modules Qt
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
    Qt6::Charts
    Qt6::QuickWidgets
    Qt6::Positioning
    Qt6::Quick
)

# Définir le dossier QML pour l’exécution
set_target_properties(${PROJECT_NAME} PROPERTIES
    QT_QML_IMPORT_PATH "${CMAKE_CURRENT_SOURCE_DIR}"
    AUTORCC ON
)
