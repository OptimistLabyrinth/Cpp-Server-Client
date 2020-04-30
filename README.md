# Cpp-Server-Client
compiled &amp; tested on Ubuntu-18.04-LTS

## [ 1 ] create ssl certificate using openssl
here, 'root' and 'user' is just used as an identifier.

#### 1) generate private key for 'root' certificate
```shell script
openssl genrsa -out rootca.key 2048
```

#### 2) make a 'root' certificate based on the above root private key
```shell script
openssl req -x509 -new -nodes -key rootca.key -out rootca.crt
```

#### 3) generate private key for 'user' certificate
```shell script
openssl genrsa -out user.key 2048
```

#### 4) make a 'user' certificate
```shell script
openssl req -new -key user.key -out user.csr
```

#### 5) sign this 'user' certificate using 'root' certificate
```shell script
openssl x509 -req -in user.csr -CA rootca.crt -CAkey rootca.key -CAcreateserial -out user.crt
```

#### 6) verify
```shell script
openssl verify -CAfile rootca.crt rootca.crt # (OK)
openssl verify -CAfile rootca.crt user.crt # (OK)
openssl verify -CAfile user.crt user.crt # (cannot verify)
```

#### 7) generate DH parameters for Diffie-Hellman key exchange protocol
```shell script
openssl dhparam -out dh2048.pem 2048
```

#### 8) where to use which
```c++
// Server-side
use_certificate_chain_file("user.crt");
use_private_key_file("user.key");
use_tmp_dh_file("dh2048.pem");

// Client-side
load_verify_file("root.crt");
```
