#!/usr/bin/env bash
# Copyright (c) 2020 GBCR Developers
# Copyright (c) 2016-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

BITCOIND=${BITCOIND:-$BINDIR/goldbcrd}
BITCOINCLI=${BITCOINCLI:-$BINDIR/goldbcr-cli}
BITCOINTX=${BITCOINTX:-$BINDIR/goldbcr-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/goldbcr-wallet}
BITCOINQT=${BITCOINQT:-$BINDIR/qt/goldbcr-qt}

[ ! -x $BITCOIND ] && echo "$BITCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a GBCRVER <<< "$($BITCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for goldbcrd if --version-string is not set,
# but has different outcomes for goldbcr-qt and goldbcr-cli.
echo "[COPYRIGHT]" > footer.h2m
$BITCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $BITCOIND $BITCOINCLI $BITCOINTX $WALLET_TOOL $BITCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${GBCRVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${GBCRVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
