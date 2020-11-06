// Copyright (c) 2011-2014 The GoldBCR Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
#define BITCOIN_QT_BITCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class GoldBCRAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GoldBCRAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** GoldBCR address widget validator, checks for a valid goldbcr address.
 */
class GoldBCRAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GoldBCRAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOIN_QT_BITCOINADDRESSVALIDATOR_H
