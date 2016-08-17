//
// ViewController.mm
//

#import "ViewController.h"
#include "soapGlobalWeatherSoapProxy.h"
#import "soapStub.h"
#import "gsoapios.h"
#include <sstream>

typedef struct _ns__GetWeather RequestStruct;
typedef struct _ns__GetWeatherResponse ResponseStruct;

@implementation ViewController
@synthesize inputcity;

- (IBAction)buttonPressed:(id)sender {
    RequestStruct sending;
    ResponseStruct receiving;
    std::string result = "";
    
    GlobalWeatherSoapProxy service;
    soap_init(service.soap);
    
    // ----- register plugin for callbacks ------
    soap_register_plugin(service.soap, soap_ios);
    
    std::string cname= std::string((char *)[inputcity.text UTF8String]);
    sending.CityName = &cname;
    std::string USA = "United States";
    sending.CountryName = &USA;
    
    if(service.GetWeather(&sending, receiving)==SOAP_OK)
    {
        std::stringstream xmlmessage;
        
        xmlmessage << *(receiving.GetWeatherResult);
            
        struct soap *ctx = soap_new1(SOAP_C_UTFSTRING | SOAP_XML_INDENT | SOAP_DOM_TREE);
        ctx->double_format = "%lG";
            
        xsd__anyType dom(ctx);
        xmlmessage >> dom;
        if (dom.soap->error)
            result = "Error: Try a different city";
            
        xsd__anyType *elt;
        #define USE_ATT(path, text) std::cout << path << " = " << text << std::endl
        #define USE_ELT(path, text) std::cout << path << " = " << text << std::endl
                
        if ((elt = dom.elt_get("Wind")))
        {
            xsd__anyType& dom_Wind = *elt;
            if (dom_Wind.get_text())
            {
                result += "Wind = ";
                result += dom_Wind.get_text();
            }
        }
        if ((elt = dom.elt_get("Visibility")))
        {
            xsd__anyType& dom_Visibility = *elt;
            if(dom_Visibility.get_text())
            {
                result += "\nVisibility = ";
                result += dom_Visibility.get_text();
            }
        }
        if ((elt = dom.elt_get("SkyConditions")))
        {
            xsd__anyType& dom_SkyConditions = *elt;
            if (dom_SkyConditions.get_text())
            {
                result += "\nSky Conditions = ";
                result += dom_SkyConditions.get_text();
            }
        }
        if ((elt = dom.elt_get("Temperature")))
        {
            xsd__anyType& dom_Temperature = *elt;
            if (dom_Temperature.get_text())
            {
                result += "\nTemperature = ";
                result += dom_Temperature.get_text();
            }
        }
        if ((elt = dom.elt_get("DewPoint")))
        {
            xsd__anyType& dom_DewPoint = *elt;
            if (dom_DewPoint.get_text())
            {
                result += "\nDew Point = ";
                result += dom_DewPoint.get_text();
            }
        }
        if ((elt = dom.elt_get("RelativeHumidity")))
        {
            xsd__anyType& dom_RelativeHumidity = *elt;
            if (dom_RelativeHumidity.get_text())
            {
                result += "\nRelative Humidity = ";
                result += dom_RelativeHumidity.get_text();
            }
        }
        if ((elt = dom.elt_get("Pressure")))
        {
            xsd__anyType& dom_Pressure = *elt;
            if (dom_Pressure.get_text())
            {
                result += "\nPressure = ";
                result += dom_Pressure.get_text();
            }
        }
            
        soap_destroy(ctx); // delete objects
        soap_end(ctx);     // delete DOM data
        soap_free(ctx);    // free context
        
    }
    
    NSString *titleMsg;
    NSString *Weather;
    titleMsg = [NSString stringWithFormat: @"%@", @"Weather Results"];
    Weather = [NSString stringWithUTF8String:result.c_str()];
    
    //show result as an alert
    UIAlertController * alert = [UIAlertController
                                 alertControllerWithTitle:titleMsg
                                 message:Weather
                                 preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction* cancelButton = [UIAlertAction
                                   actionWithTitle:@"OK"
                                   style:UIAlertActionStyleDefault
                                   handler:^(UIAlertAction * action){}];
    
    [alert addAction: cancelButton];
    [self presentViewController:alert animated:YES completion:nil];
    
    
    
    service.destroy();
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
