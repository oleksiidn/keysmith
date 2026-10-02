/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: 2019 Johan Ouwerkerk <jm.ouwerkerk@gmail.com>
 */

#ifndef SECRET_VALIDATOR_H
#define SECRET_VALIDATOR_H

#include <QRegularExpressionValidator>
#include <QValidator>

namespace validators
{
    class Base32Validator : public QValidator
    {
        Q_OBJECT
        Q_PROPERTY(bool allowOtpauthUri READ allowOtpauthUri WRITE setAllowOtpauthUri NOTIFY allowOtpauthUriChanged)
    public:
        explicit Base32Validator(QObject *parent = nullptr);
        QValidator::State validate(QString &input, int &pos) const override;
        void fixup(QString &input) const override;
        bool allowOtpauthUri(void) const;
        void setAllowOtpauthUri(bool allow);
        Q_SIGNALS:
            void allowOtpauthUriChanged(void);

    private:
        bool isOtpauthUri(const QString &input) const;

    private:
        const QRegularExpressionValidator m_pattern;
        bool m_allowOtpauthUri;
    };
}

#endif
