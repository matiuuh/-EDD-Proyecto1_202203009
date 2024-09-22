cmake_minimum_required(VERSION 3.16)

project(Fase2EDD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        interfazprincipal.cpp
        interfazprincipal.h
        interfazprincipal.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Fase2EDD
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        usuario.h usuario.cpp
        moduloentrada.h moduloentrada.cpp moduloentrada.ui
        moduloadministrador.h moduloadministrador.cpp moduloadministrador.ui

        pila.h pila.cpp
        listasimple.h listasimple.cpp
        listadoble.h listadoble.cpp
        bstpublicaciones.h bstpublicaciones.cpp
        EstructurasAdmin/avlusuarios.h EstructurasAdmin/avlusuarios.cpp
        EstructurasAdmin/listadoblepublicacionesglobal.h EstructurasAdmin/listadoblepublicacionesglobal.cpp
        registrousuario.h registrousuario.cpp registrousuario.ui
        EstructurasUsuario/listadobleusuariosdisponibles.h EstructurasUsuario/listadobleusuariosdisponibles.cpp
        TablasModUsuario/buttondelegatesolicitudes.h TablasModUsuario/buttondelegatesolicitudes.cpp
        TablasModUsuario/buttondelegateenviadas.h TablasModUsuario/buttondelegateenviadas.cpp
        EstructurasUsuario/matrizdispersaamigos.h EstructurasUsuario/matrizdispersaamigos.cpp
        nuevapublicacion.h nuevapublicacion.cpp nuevapublicacion.ui
        Publicaciones/publicacion.h Publicaciones/publicacion.cpp
        Publicaciones/Comentarios/comentario.h Publicaciones/Comentarios/comentario.cpp
        Publicaciones/Comentarios/arbolbcomentarios.h Publicaciones/Comentarios/arbolbcomentarios.cpp
        gestorcomentarios.h gestorcomentarios.cpp gestorcomentarios.ui
        TablasAdmin/buttondelegatetablaadmin.h TablasAdmin/buttondelegatetablaadmin.cpp
        TablasModUsuario/modificarusuariodialog.h TablasModUsuario/modificarusuariodialog.cpp




        #Oficial.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Fase2EDD APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Fase2EDD SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Fase2EDD
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Fase2EDD PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Fase2EDD)
endif()
set_target_properties(Fase2EDD PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Fase2EDD
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Fase2EDD)
endif()
