//
//  OptinworkflowManager.h
//  NotifySDK
//
//  Created by Manish on 7/30/15.
//  Copyright (c) 2015 Socialscope, Inc.. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum  {
    OnlyOnce=0,
    Auto=1,
    RepeatAlways=2
} ShowType;

@interface OptInWorkflowManager : NSObject

typedef void (^OnGetSubsListSuccess)(NSArray*response);
typedef void (^OnGetSubsListError)(NSString*response);
@property (nonatomic, copy) IBOutlet NSString *optInPromptMainText;
@property (nonatomic, copy) IBOutlet NSString *optInPromptTitleText;
@property (nonatomic, strong) IBOutlet UIImage *optInPromptBgImage;
@property (nonatomic, strong) IBOutlet UIFont *optInPromptMessageFont;
@property (nonatomic) UIUserNotificationType types;

@property (nonatomic, copy) IBOutlet NSString *optOutPromptMainText;
@property (nonatomic, copy) IBOutlet NSString *optOutPromptTitleText;
@property (nonatomic, strong) IBOutlet UIImage *optOutPromptBgImage;
@property (nonatomic, strong) IBOutlet UIFont *optOutPromptMessageFont;


@property (nonatomic, strong) UIViewController *customSubscriptionViewController;

-(void) showNotificationExplanationPromptOnScreenVisit:(ShowType) type withMinDelay:(NSTimeInterval) delay withRepeats:(NSUInteger) numRepeats;
-(void) showNotificationExplanationPromptOnToggleEnabled;
-(void) showNotificationOptOutPrompt;

-(void) setSubscription:(NSString*) subScriptionKey state :(BOOL) state;


+(OptInWorkflowManager *) getInstance;
@end
