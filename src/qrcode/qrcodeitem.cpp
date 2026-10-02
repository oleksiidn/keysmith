/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "qrcodeitem.h"

#include <QPainter>

#include <qrencode.h>

namespace qrcode
{
// width of the quiet zone, in modules, as required by ISO/IEC 18004
static const int quietZone = 4;

QrCodeItem::QrCodeItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_width(0)
{
    setAntialiasing(false);
}

QrCodeItem::~QrCodeItem()
{
    clear();
}

QString QrCodeItem::text(void) const
{
    return m_text;
}

bool QrCodeItem::valid(void) const
{
    return m_width > 0;
}

void QrCodeItem::clear(void)
{
    // the encoded text may contain a secret: wipe it rather than leaving it around on the heap
    m_text.fill(QLatin1Char('\0'));
    m_text.clear();
    m_modules.fill('\0');
    m_modules.clear();
    m_width = 0;
}

void QrCodeItem::setText(const QString &text)
{
    if (text == m_text) {
        return;
    }

    clear();
    m_text = text;

    if (!m_text.isEmpty()) {
        QByteArray utf8 = m_text.toUtf8();
        QRcode *code = QRcode_encodeString8bit(utf8.constData(), 0, QR_ECLEVEL_M);
        utf8.fill('\0');

        if (code) {
            m_width = code->width;
            m_modules.resize(code->width * code->width);
            for (int i = 0; i < m_modules.size(); ++i) {
                // bit 0 of each byte of QRcode::data tells whether the module is dark
                m_modules[i] = code->data[i] & 1;
                code->data[i] = 0;
            }
            QRcode_free(code);
        }
    }

    Q_EMIT textChanged();
    update();
}

void QrCodeItem::paint(QPainter *painter)
{
    if (m_width <= 0) {
        return;
    }

    const int total = m_width + 2 * quietZone;
    const qreal side = qMin(width(), height());
    // integral module size keeps every module the same size, which matters for reliable scanning
    const int moduleSize = qMax(1, static_cast<int>(side) / total);
    const int codeSize = moduleSize * total;
    const int left = static_cast<int>((width() - codeSize) / 2);
    const int top = static_cast<int>((height() - codeSize) / 2);

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->fillRect(left, top, codeSize, codeSize, Qt::white);

    for (int y = 0; y < m_width; ++y) {
        for (int x = 0; x < m_width; ++x) {
            if (m_modules[y * m_width + x]) {
                painter->fillRect(left + (x + quietZone) * moduleSize, top + (y + quietZone) * moduleSize, moduleSize, moduleSize, Qt::black);
            }
        }
    }
}
}
