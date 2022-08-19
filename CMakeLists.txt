cmake_minimum_required (VERSION 3.8.2)
set(PROJECT lumina-desktop)
project(${PROJECT})

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#Find pkgconfig
find_package(PkgConfig REQUIRED)

# OS-detection
#
# This ignores the actual OS and just sets FreeBSD-useful values
add_definitions(
    -DL_ETCDIR=QStringLiteral\("${CMAKE_INSTALL_PREFIX}/etc"\)
    -DL_SHAREDIR=QStringLiteral\("${CMAKE_INSTALL_DATADIR}"\)
)

# Dependencies
find_package(Qt5 REQUIRED COMPONENTS Widgets X11Extras Network Multimedia MultimediaWidgets Concurrent Svg Quick Qml)
pkg_check_modules(LUMINA REQUIRED lumina)

# Tell CMake to create the executable
add_executable(${PROJECT}
 main.cpp
 global-includes.h
 Globals.h
 JsonMenu.h
 WMProcess.cpp
 LXcbEventFilter.cpp
 LSession.cpp
 LDesktop.cpp
 LDesktopBackground.cpp
 LDesktopPluginSpace.cpp
 LPanel.cpp
 LWinInfo.cpp
 AppMenu.cpp
 SettingsMenu.cpp
 SystemWindow.cpp
 BootSplash.cpp
 
 # OS framework
 framework-interfaces/framework-OSInterface.h
 framework-interfaces/framework-OSInterface_private.cpp
 framework-interfaces/framework-OSInterface-template.cpp
 
 # Base Plugins
 plugins/plugins-base.cpp
 plugins/plugins-screensaver.cpp
 plugins/plugins-desktop.cpp

 # Screensaver
 screensaver/LLockScreen.cpp
 screensaver/LScreenSaver.cpp
 screensaver/SSBaseWidget.cpp
  
 # Screensaver animations
 screensaver/animations/BaseAnimGroup.cpp
 
 screensaver/animations/BaseAnimGroup.h
 screensaver/animations/SampleAnimation.h
 screensaver/animations/Fireflies.h
 screensaver/animations/Grav.h
 screensaver/animations/ImageSlideshow.h
 screensaver/animations/VideoSlideshow.h
 screensaver/animations/Text.h

 # Desktop plugins
 desktop-plugins/applauncher/AppLauncherPlugin.cpp
 desktop-plugins/desktopview/DesktopViewPlugin.cpp
 desktop-plugins/notepad/NotepadPlugin.cpp
 desktop-plugins/audioplayer/PlayerWidget.cpp
 desktop-plugins/systemmonitor/MonitorWidget.cpp
 desktop-plugins/rssreader/RSSFeedPlugin.cpp
 desktop-plugins/rssreader/RSSObjects.cpp
 
 desktop-plugins/calendar/CalendarPlugin.h
 desktop-plugins/applauncher/OutlineToolButton.h

 # Panel plugins
 panel-plugins/userbutton/LUserButton.cpp
 panel-plugins/userbutton/UserWidget.cpp
 panel-plugins/userbutton/UserItemWidget.cpp
 panel-plugins/desktopbar/LDeskBar.cpp
 panel-plugins/taskmanager/LTaskManagerPlugin.cpp
 panel-plugins/taskmanager/LTaskButton.cpp
 panel-plugins/systemtray/LSysTray.cpp
 panel-plugins/systemtray/TrayIcon.cpp
 panel-plugins/clock/LClock.cpp
 panel-plugins/battery/LBattery.cpp
 panel-plugins/desktopswitcher/LDesktopSwitcher.cpp
 panel-plugins/systemdashboard/LSysDashboard.cpp
 panel-plugins/systemdashboard/SysMenuQuick.cpp
 panel-plugins/showdesktop/LHomeButton.cpp
 panel-plugins/appmenu/LAppMenuPlugin.cpp
 panel-plugins/applauncher/AppLaunchButton.cpp
 panel-plugins/systemstart/LStartButton.cpp
 panel-plugins/systemstart/StartMenu.cpp
 panel-plugins/systemstart/ItemWidget.cpp
 panel-plugins/audioplayer/LPAudioPlayer.cpp
 panel-plugins/audioplayer/PPlayerWidget.cpp
 panel-plugins/jsonmenu/PPJsonMenu.cpp

 panel-plugins/RotateToolButton.h
 panel-plugins/spacer/LSpacer.h
 panel-plugins/line/LLine.h

 #Test
 desktop-plugins/LDPlugin.cpp
 panel-plugins/LPPlugin.h
 panel-plugins/NewPP.h
 panel-plugins/LTBWidget.h
 desktop-plugins/LDPlugin.h
 desktop-plugins/NewDP.h
)

# Add the dependencies for linking
target_link_libraries(${PROJECT}
 Qt5::Widgets
 Qt5::X11Extras
 Qt5::Network
 Qt5::Multimedia
 Qt5::MultimediaWidgets
 Qt5::Concurrent
 Qt5::Svg
 Qt5::Quick
 Qt5::Qml
 ${LUMINA_LIBRARIES}
)

# Include header files
include_directories(
    ${LUMINA_INCLUDE_DIRS}
)

install(TARGETS ${PROJECT} RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# XSession
install(FILES "data/Lumina-DE.desktop" DESTINATION "${CMAKE_INSTALL_DATADIR}/xsessions")
# PNG
install(FILES "data/Lumina-DE.png" DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps")

# Configuration
## Fluxbox
install(FILES "data/fluxboxconf/fluxbox-init-rc" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/fluxboxconf/fluxbox-keys" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/fluxboxconf/theme.cfg" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
## Defaults
install(FILES "data/defaults/luminaDesktop.conf" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/defaults/compton.conf" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/audiofiles/Logout.ogg" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/audiofiles/Login.ogg" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/audiofiles/low-battery.ogg" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
## Extrafiles
install(FILES "data/extrafiles/Lumina-DE.png" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(FILES "data/extrafiles/globs2" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
install(DIRECTORY "data/extrafiles/screensavers" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
## Themes
install(DIRECTORY "data/themes" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
## Menuscripts
install(DIRECTORY "data/menu-scripts" DESTINATION "${CMAKE_INSTALL_DATADIR}/lumina-desktop")
