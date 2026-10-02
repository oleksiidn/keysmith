#
# SPDX-License-Identifier: BSD-2-Clause
#

set(qrcode_SRCS
        qrcodeitem.cpp
)

add_library(qrcode_lib STATIC ${qrcode_SRCS})
target_link_libraries(qrcode_lib PUBLIC Qt::Core Qt::Gui Qt::Quick PRIVATE qrencode::qrencode)
