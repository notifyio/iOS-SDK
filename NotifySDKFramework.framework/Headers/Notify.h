#ifndef NotifySDK_Notify_h
#define NotifySDK_Notify_h


#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>
#import "Config.h"


@interface Notify : NSObject


#pragma mark Methods

@property(nonatomic,readonly)Config *config;

typedef void (^OnGetSubsListSuccess)(NSArray*response);
typedef void (^OnGetSubsListUpdate)(NSArray*response);
typedef void (^OnGetSubsListError)(NSString*response);

+ (Notify *)initWithConfig:(Config*)config;

+ (Notify *)getInstance;

- (NSString*) getDeviceId;

- (NSString*) getPushToken;

- (NSString*) getUserId;

- (BOOL)isPushSettingsEnabled;

- (void)registerForNotifications;

- (void)resetBadge;

- (void)setBadge:(int) badge;

- (void)addToChannel:(NSString*)channel;

- (void)removeFromChannel:(NSString*)channel;

- (void)requestPushPermission:(UIUserNotificationType) notificationType;

- (void)loginUser:(NSString *)userId;

- (void)logoutUser;

- (void)trackEvent:(NSString *)event;

- (void)trackAction:(NSString *)action forItem:(NSString*)itemId;

- (void)trackAction:(NSString *)action forItem:(NSString*)itemId withMetaData:(NSDictionary*)metadata;

- (void)trackEvent:(NSString *)event withDoubleValue:(double) value;

- (void)trackEvent:(NSString *)event withStringValue:(NSString *) value;

- (void)addUserAttribute:(NSDictionary*)data;

- (NSString*)getDevicePushState;

- (void)setSubscription:(NSString*) subScriptionKey state :(BOOL) state;


-(void) registerSubscriptionListHandlers:(OnGetSubsListSuccess) success onError:(OnGetSubsListError) error onUpdate:(OnGetSubsListUpdate) update;

- (void)setInAppNotificationOptionsBackground:(UIColor *)color
                                   foreground:(UIColor*)color
                                         font:(UIFont*)font
                                duration:(NSTimeInterval)duration
                    canBeDismissedByUser:(BOOL)dismissingEnabled;

@end
#endif
