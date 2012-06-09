INSTRUCTIONS

Install the WCF samples.

You should have:

  C:\WF_WCF_Samples\WCF\Basic\Binding\WS\DualHttp\CS

Open the WS DualHttp WCF C# example client and service.

Note:

  C:> denotes the Windows command line

  $ denotes the Unix/Linux command line

To enable gSOAP to use WS-ReliableMessaging for wsDualHttp interop, add to the
.h file to be processed by soapcpp2:

  #import "wsrm5.h"

See doc/wsrm for instructions.

To connect a WCF client to a gSOAP service
------------------------------------------

In App.config set the endpoint to the server endpoint, say "10.0.1.5" over
wifi, with Message Security disabled, and clientBase (for callback calls) to
the current machine, say 192.168.2.2:

<client>
  <endpoint address="http://10.0.1.5:8000" ... />
</client>
<bindings>
  <wsDualHttpBinding>
    <binding clientBaseAddress="http://192.168.2.2:8000/MyClient/" ...>
      <security mode="None"/>

Edit calculator.cpp to change the URIs:

Compile and run the gSOAP server on port 8000 on machine "10.0.1.5":

  $ ./calculator 8000

Compile and run the WCF client:

  C:\WF_WCF_Samples\WCF\Basic\Binding\WS\DualHttp\CS\client> bin\client.exe

To self-host a WCF service
--------------------------

Obtain the machine name or IP

  C:> ipconfig /all

say it is 192.168.2.2.

Add a Main() to self-host by adding a Program class in the WCF sample

  C:\WF_WCF_Samples\WCF\Basic\Binding\Basic\Http\CS\service

using System;
using System.ServiceModel;
using System.Configuration;
using System.ServiceModel.Description;

namespace ...
{
  ...
  public class Program
  {
    public static void Main()
    {
      Uri httpUrl = new Uri("http://192.168.2.2:8000/ServiceModelSamples/service");
      using (ServiceHost serviceHost = new ServiceHost(typeof(CalculatorService), httpUrl))
      {
        WSDualHttpBinding dhb = new WSDualHttpBinding();
	dhb.Security.Mode = WSDualHttpSecurityMode.None;
        serviceHost.AddServiceEndpoint(typeof(ICalculatorDuplex), dhb, "");
  
        ServiceMetadataBehavior smb = new ServiceMetadataBehavior();
        smb.HttpGetEnabled = true;
        serviceHost.Description.Behaviors.Add(smb);
  
        servicehost.Open();
      }
    }
  }

Under Project Properties change the Output type to Console Application to
generate a service.exe.

Use a web browser to access the service at
  http://192.168.2.2:8000/ServiceModelSamples/service
and access the WSDL at
  http://192.168.2.2:8000/ServiceModelSamples/service?wsdl

To run wsdl2h to generate C++ code:

  $ wsdl2h -t ../../../../typemap.dat -o calculator.h 'http://192.168.2.2:8000/ServiceModelSamples/service?wsdl'

This may take some time, since the self-hosted service is an iterative web
server that allows only one open connection.

A pre-generated calculator.h file is included in the build directory.

Two problems were addressed:

1. Change #import "wsrm.h" to "wsrm5.h" to support WS-ReliableMessaging 1.0
   (2005 version)

2. Because wsdl2h 2.8.9 is not updated yet to generate output-only methods, we
need to add to calculator.h:

--------------------------------------------------------------------------------
class _mssadh__Result
{ public:
    double*                              result                         0;
    struct soap                         *soap                          ;
};

class _mssadh__Equation
{ public:
    std::string*                         eqn                            0;	
    struct soap                         *soap                          ;
};

//gsoap tempuri service method-style:	Result document
//gsoap tempuri service method-encoding:	Result literal
//gsoap tempuri service method-action:	Result http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Result
int __tempuri__Result(
    _mssadh__Result*                     mssadh__Result,	///< Request parameter
    void	///< One-way message: no response parameter
);

//gsoap tempuri service method-style:	Equation document
//gsoap tempuri service method-encoding:	Equation literal
//gsoap tempuri service method-action:	Equation http://Microsoft.Samples.DualHttp/ICalculatorDuplex/Equation
int __tempuri__Equation(
    _mssadh__Equation*                     mssadh__Equation,	///< Request parameter
    void	///< One-way message: no response parameter
);
--------------------------------------------------------------------------------

To connect a gSOAP client to a WCF self-hosted service
------------------------------------------------------

In the gSOAP calculator.cpp, change the hosts to the WCF server host URI and
the client host URI and port number:

const char *serverURI = "http://192.168.2.2:8000/ServiceModelSamples/service";

const char *clientURI = "http://10.0.1.5:8001";
int clientPort = 8001;

Compile and run:

  C:\WF_WCF_Samples\WCF\Basic\Binding\WS\DualHttp\CS\service> bin\service.exe

  $ ./calculator
