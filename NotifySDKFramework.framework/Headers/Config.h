
#ifndef NotifySDK_Config_h
#define NotifySDK_Config_h

#import <Foundation/Foundation.h>



@interface Config : NSObject

@property (nonatomic,  copy) NSString *apiKey;
@property (nonatomic, assign, getter=isInProduction) BOOL inProduction;
@property (nonatomic, assign) BOOL automaticSetupEnabled;
@property (nonatomic, assign) BOOL detectProvisioningMode;


+ (Config *)configWithContentsOfFile:(NSString *)path;

+ (Config *)config;



@end
#endif