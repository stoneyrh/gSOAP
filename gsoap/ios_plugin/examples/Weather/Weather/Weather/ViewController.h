//
// ViewController.h
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController{
    UITextField* inputcity;
}
@property (strong, nonatomic) IBOutlet UITextField *inputcity;

- (IBAction) buttonPressed;
@end

