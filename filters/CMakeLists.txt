add_subdirectory(bugzilla)
add_subdirectory(emoticons)
add_subdirectory(formatting)
add_subdirectory(images)
add_subdirectory(latex)
add_subdirectory(searchexpansion)
add_subdirectory(youtube)
add_subdirectory(highlight)
add_subdirectory(urlexpansion)

IF (EXISTS "${KDE4_DBUS_INTERFACES_DIR}/org.kde.KSpeech.xml")
    set (HAS_KTTS TRUE)
ENDIF (EXISTS "${KDE4_DBUS_INTERFACES_DIR}/org.kde.KSpeech.xml")

if(HAS_KTTS)
    add_subdirectory(texttospeech)
endif(HAS_KTTS)

macro_log_feature(HAS_KTTS "KTTSD" "KDE Text to Speech Deamon" "" FALSE "" "Needed for optional tts message plugin")
