Shared Libraries
================

## goldbcrconsensus

The purpose of this library is to make the verification functionality that is critical to Gold BCR's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `goldbcrconsensus.h` located in `src/script/goldbcrconsensus.h`.

#### Version

`goldbcrconsensus_version` returns an `unsigned int` with the API version *(currently `1`)*.

#### Script Validation

`goldbcrconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `goldbcrconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/goldbcr/bips/blob/master/bip-0016.mediawiki)) subscripts
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/goldbcr/bips/blob/master/bip-0066.mediawiki)) compliance
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/goldbcr/bips/blob/master/bip-0147.mediawiki))
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/goldbcr/bips/blob/master/bip-0065.mediawiki))
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/goldbcr/bips/blob/master/bip-0112.mediawiki))
- `goldbcrconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/goldbcr/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `goldbcrconsensus_ERR_OK` - No errors with input parameters *(see the return value of `goldbcrconsensus_verify_script` for the verification status)*
- `goldbcrconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `goldbcrconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `goldbcrconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `goldbcrconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NGold BCR](https://github.com/NicolasDorier/NGold BCR/blob/master/NGold BCR/Script.cs#L814) (.NET Bindings)
- [node-libgoldbcrconsensus](https://github.com/bitpay/node-libgoldbcrconsensus) (Node.js Bindings)
- [java-libgoldbcrconsensus](https://github.com/dexX7/java-libgoldbcrconsensus) (Java Bindings)
- [goldbcrconsensus-php](https://github.com/Bit-Wasp/goldbcrconsensus-php) (PHP Bindings)
