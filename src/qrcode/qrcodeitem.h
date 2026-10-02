/*
* SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef QRCODE_QRCODEITEM_H
#define QRCODE_QRCODEITEM_H

#include <QByteArray>
#include <QQuickPaintedItem>
#include <QString>

namespace qrcode
{
    /*
     * Renders a QR code for the given text using libqrencode.
     *
     * The code is always painted dark-on-light (regardless of colour scheme) with a quiet zone around it,
     * because many scanners cannot cope with inverted or borderless codes.
     */
    class QrCodeItem : public QQuickPaintedItem
    {
        Q_OBJECT
        Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
        Q_PROPERTY(bool valid READ valid NOTIFY textChanged)
    public:
        explicit QrCodeItem(QQuickItem *parent = nullptr);
        ~QrCodeItem() override;

        QString text(void) const;
        void setText(const QString &text);
        bool valid(void) const;

        void paint(QPainter *painter) override;

        Q_SIGNALS:
            void textChanged(void);

    private:
        void clear(void);

    private:
        QString m_text;
        QByteArray m_modules;
        int m_width;
    };
}

#endif
