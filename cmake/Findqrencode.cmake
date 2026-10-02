#
# SPDX-License-Identifier: BSD-2-Clause
#
# Tries to find the local libqrencode installation (https://github.com/fukuchi/libqrencode).
#
# Once done the following variables will be defined:
#
# qrencode_FOUND qrencode_INCLUDE_DIR qrencode_LIBRARY qrencode_VERSION
#
# Furthermore an imported "qrencode::qrencode" target is created.
#

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_qrencode QUIET libqrencode)
endif()

find_path(qrencode_INCLUDE_DIR
        NAMES qrencode.h
        HINTS ${PC_qrencode_INCLUDEDIRS}
)

find_library(qrencode_LIBRARY
        NAMES qrencode qrencoded
        HINTS ${PC_qrencode_LIBDIR} ${PC_qrencode_LIBRARY_DIRS}
)

set(qrencode_VERSION ${PC_qrencode_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(qrencode
        REQUIRED_VARS qrencode_LIBRARY qrencode_INCLUDE_DIR
        VERSION_VAR qrencode_VERSION
)

if(qrencode_FOUND AND NOT TARGET qrencode::qrencode)
    add_library(qrencode::qrencode UNKNOWN IMPORTED)
    set_target_properties(qrencode::qrencode PROPERTIES
            IMPORTED_LOCATION "${qrencode_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${qrencode_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(qrencode_INCLUDE_DIR qrencode_LIBRARY)
