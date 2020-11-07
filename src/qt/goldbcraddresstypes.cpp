// Copyright (c) 2011-2018 The GoldBCR Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/goldbcraddresstypes.h>

#include <QStringList>

GoldBCRAddressTypes::GoldBCRAddressTypes(QObject *parent):
        QAbstractListModel(parent),
        addressTypeList(availableAddressTypes())
{
}

QList<GoldBCRAddressTypes::AddressType> GoldBCRAddressTypes::availableAddressTypes()
{
    QList<GoldBCRAddressTypes::AddressType> addressTypeList;
    addressTypeList.append(LEGACY);
    addressTypeList.append(NESTED_SEGWIT);
    addressTypeList.append(NATIVE_SEGWIT);
    return addressTypeList;
}

bool GoldBCRAddressTypes::valid(int addressType)
{
    switch(addressType)
    {
    case LEGACY:
    case NESTED_SEGWIT:
    case NATIVE_SEGWIT:
        return true;
    default:
        return false;
    }
}

QString GoldBCRAddressTypes::longName(int addressType)
{
    switch(addressType)
    {
    case LEGACY: return QString("Legacy");
    case NESTED_SEGWIT: return QString("Nested Segwit");
    case NATIVE_SEGWIT: return QString("Native Segwit");
    default: return QString("???");
    }
}

QString GoldBCRAddressTypes::shortName(int addressType)
{
    return longName(addressType);
}

QString GoldBCRAddressTypes::description(int addressType)
{
    switch(addressType)
    {
    case LEGACY: return QString("Legacy goldbcr address. P2PKH");
    case NESTED_SEGWIT: return QString("Nested Segwit address. P2SH");
    case NATIVE_SEGWIT: return QString("Native Segwit address. P2WPKH");
    default: return QString("???");
    }
}

int GoldBCRAddressTypes::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return addressTypeList.size();
}

QVariant GoldBCRAddressTypes::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < addressTypeList.size())
    {
        AddressType addressType = addressTypeList.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(longName(addressType));
        case Qt::ToolTipRole:
            return QVariant(description(addressType));
        case AddressTypeRole:
            return QVariant(static_cast<int>(addressType));
        }
    }
    return QVariant();
}
