
The SSL-enabled services are compiled with -DWITH_OPENSSL -DWITH_GZIP and
linked with -lgsoapssl -lssl -lcrypto -lz

How to generate self-signed root certificate and client.pem/server.pem with
certificates signed by the root CA for deployment in clients and servers.

Create a 'CA' directory and copy openssl.cnf, root.sh, and cert.sh to this
dir.

Change dir to 'CA'.

Modify the openssl.cnf file in the [req_distinguished_name] section for the
following items:

[ req_distinguished_name ]
countryName_default             = US
stateOrProvinceName_default     = Your-State
localityName_default            = Your-City
0.organizationName_default      = Your-Company-Name
emailAddress_default            = your-email@address

If you are going to use these settings often, add this line to your .cshrc:
setenv OPENSSL_CONF $HOME/CA/openssl.cnf

To generate the root CA:

./root.sh

When prompted, choose a passphrase to protect the CA's private key that you
are about to generate. You need the passphrase again when you sign
certificates with the CA's private key.

Save the root.pem key and the passphrase in a safe place (don't distribute!).

Now you got the root.pem with the CA's keys and the cacert.pem certificate of
the CA (for distribution).

The root.pem and cacert.pem are valid for three years. Don't repeat this step
until the certificate expires.

Next, we will generate the server.pem key file:

./cert.sh server

Enter a password when prompted and enter the host or simply "localhost" for
the domain of the server application. The password is used to lock the private
key of the server and will therefore be needed by your server application to
unlock the private key in the server.pem when needed for secure
communications. Use the root CA passphrase when prompted to sign the server
certificate.

When applicable, repeat the procedure for the client (use a fresh password and
select a host for the client application):

./cert.sh client

The client.pem and server.pem keys are valid for one year. Do not distribute
them (they include the private key, which is encrypted with the passwords
you selected which is not very secure). They are used ony locally by the SSL
application. Only distribute the CA certificate.

Required files in HOME/CA directory:

openssl.cnf
root.sh
cert.sh

Files generated:

cacert.pem      root's certificate for distribution, to verify authentication
root.pem        root CA (to sign client/server key files, do not distribute!)
rootkey.pem     private key (do not distribute!)
rootreq.pem     sign request
root.srl        serial number

client.pem      client key file (do not distribute)
clientkey.pem   private key (do not distribute)
clientreq.pem   sign request

server.pem      server key (private key and certificate, do not distribute)
serverkey.pem   private key (do not distribute)
serverreq.pem   sign request

To print the contents of a PEM file:

openssl x509 -text -in file.pem

