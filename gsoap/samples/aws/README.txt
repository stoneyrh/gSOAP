Example AWS S3 service invocation

Lists all S3 buckets of a user

Other service invocations can be easily added

Report generated in soapReadme.md

Build steps:

$ wsdl2h -t typemap.dat -o aws-s3.h http://doc.s3.amazonaws.com/2006-03-01/AmazonS3.wsdl
$ soapcpp2 -C -j -r aws-s3.h
$ c++ -DWITH_OPENSSL -o aws-s3 aws-s3.cpp soapAmazonS3SoapBindingProxy.cpp soapC.cpp stdsoap2.cpp -lssl -lcrypto

