#!/bin/sh

if [ "$#" = 1 ]
then

  echo "* Create certificate ${1}.pem signed by the root CA"
  echo "* Store the ${1}.pem key file locally with your client/server application"
  echo "* Enter a secret pass phrase when requested"
  echo "* The pass phrase is used to access ${1}.pem in your application"
  echo "* Enter the application's host name as the Common Name when requested"
  echo "* Enter the root CA pass phrase (Getting CA Private Key) to sign the key file"
  echo "* The key file will expire after one year or sooner when the root CA expires"

  # Create a certificate and signing request

  openssl req -newkey rsa:1024 -sha1 -keyout ${1}key.pem -out ${1}req.pem

  # Sign the certificate with the root CA

  openssl x509 -req -in ${1}req.pem -sha1 -extfile openssl.cnf -extensions usr_cert -CA root.pem -CAkey root.pem -CAcreateserial -out ${1}cert.pem -days 1095

  cat ${1}cert.pem ${1}key.pem cacert.pem > ${1}.pem

  openssl x509 -subject -issuer -dates -noout -in ${1}.pem

else

  echo "Usage: cert.sh <certname>"
  exit 1

fi
