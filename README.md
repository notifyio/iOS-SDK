# iOS-SDK
This document provides an overview of Notify.io’s SDK integration
#1. Quick Overview
Integration with our platform has two components:

An ingestion endpoint that you use to send us information about your items (such as your videos, articles, or products). This is the universe of items from which we recommend

Native SDKs that you use to send us user activity and that we use to deliver personalized contextual notifications.  We use activity data(including screen views, engagement, conversion, and tap activity) to build models of user behavior.  
#3. iOS SDK
##3.1. Installation

1. Download the SDK

2. Add the SDK to your project by dragging the [file a] and the [file b] you downloaded into your Xcode project folder target.  Make sure the "Copy items to destination's group folder" checkbox is checked

3. Add the dependencies. Click on Targets -> Your app name -> then the ‘Build Phases’ tab. Expand ‘Link Binary with Libraries’. Click the + button on the bottom left of the ‘Link Binary with Libraries’ section and add the following libraries:
  * Accelerate.framework
  * MediaPlayer.framework
  * Accounts.framework
  * libstdc++.dylib
  * SystemConfiguration.framework

4. Set the -objc linker flag. 

##3.2 Basic Setup (Configuration) 
The Notify.io SDK uses a .plist configuration file named NotifyConfig.plist to manage your production and development application profiles.  Once you have installed the SDK create an NotifyConfig.plist file.  

Set the following values in the config file

```XML
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>apiKey</key>
	<string>[Your API Key]</string>
</dict>
</plist>
```

In your application delagate file, add the following import to the top of the file:

Swift (AppDelegate.swift)
```swift
import NotifySDKFramework
var glance: NotifySwift?
```

ObjectiveC(AppDelegate.h)
```objectivec
#import "NotifySDKFramework/Notify.h”
@property(strong,nonatomic) Notify *notify;
```

Initialize the SDK singleton object by adding the following in your `application:didFinishLaunchingWithOptions:` function:

Swift
```swift
let config = ConfigSwift.configWithContentsOfFile("Config.plist")
self.notify = NotifySwift.initWithConfig(config)
```

ObjectiveC
```objectivec
Config *config=[Config configWithContentsOfFile:@"Config.plist"];
self.notify = [Notify initWithConfig:config];
```

##3.3 Requesting Push Permissions
We’ve designed our SDK to allow you to request push permissions at any time in your application's lifecycle.  We recommend that you request push permissions only when you believe the user will opt-in them.  This is usually after the user understands the value of push notifications.  Best practices include, after the user becomes engaged, or when the user triggers a feature that request notifications.  Please contact us to discuss optimizing your opt-in follow.  

Before requesting push permissions, you need to specify the capabilities of the notifications you’ll be delivering.  We recommend that you request permissions for sounds, alerts and badges as we do in the example below.  

When you’re ready to request push permissions make the following calls: 
Swift
```swift
let settings = UIUserNotificationSettings(forTypes: [.Alert, .Badge, .Sound], categories: nil)
NotifySwift.getInstance().requestPushPermission(settings.types)
```

ObjectiveC
```objectivec
UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:(UIUserNotificationTypeBadge | UIUserNotificationTypeSound | UIUserNotificationTypeAlert) categories:nil];
[[Notify getInstance] requestPushPermission:settings.types]
```
	
Please note that SDK is aware of different APIs needed for requesting for push across iOS7/iOS8 and automatically chooses the correct API to call at runtime.

Additionally, notification handlers are automatically set up for you during our initialization call. 

##3.4 Get the Current Push Permissions
To aid you in optimising your push opt-in workflow, we provide a simple method of getting the user’s current permission state. 

This method will return one of the following states.
* Default - The application has not yet requested push permissions.		
* Enabled - The user has enabled push notification for the application.
* Disabled - The user has disabled push notification for the application.

Swift
```swift
NotifySwift.getInstance().getDevicePushState()
```

Objective C
```objectivec
[[Notify getInstance] getDevicePushState];
```

##3.5 Track Action on an Item
The track action API is used to send us actions a user takes on an item (including screen views, engagement, conversion, and tap activity). We use activity data to build models of user behavior.

We support the following standard action types:
* __Viewed__ for a user viewing an item. This is the most standard event type. 
* __Engaged__ this action is used to indicate that the user has engaged with the item.  For a video this might mean the user has vided more than 50% of it.  For content, it can mean the user has scrolled through more than 50% of the page.  
* __Ended__ indicates that the user has completed viewing or reading the item.  For example it would indicate that the user has reached the end of the video.  
* __Purchased__ when the user has completed the purchase of an item.  If the user purchases multiple items you’ll have to make an individual call for each purchase. 
* __AddedToCart__ after a user adds an item to their cart.  

You can also use any custom action type you would like.  However, you will need to contact us to discuss how you would like the action to effect recommendations.  

Actions are always associated with items that we have ingested.  The item parameter(itemID) specifies the unique identifier for the item and should match the unique_id specified in the ingestion API.

The item does not need to be ingested before making an action call.  If the item has not been ingested yet, we will buffer the action on our backend end till the item is ingested.  

For example when a user engages with an item
Swift
```swift
String itemId = “somesite.com/someitem”
NotifySwift.getInstance().trackAction("engaged",forItem: itemId)
```

Objective C
```objectivec
NSString *itemId = @"somesite.com/someitem";
[[Notify getInstance] trackAction:@"engaged" forItem:itemId];
```

##3.6 In app notifications 
We automatically handle displaying notifications when the user is in your app.  

You can customize the look of these notifications by calling `setInAppNotificationOptionsBackground` which takes the following parameters: 
* `background` The background color of the notification 
* `foreground` Color of the foreground text.
* `font` The font to use in the notification 
* `duration` How long in seconds the notification should stay before it goes away 
* `canBeDismissedByUser` notification stays on screen till it is dismissed by the user. 

Here is an example where we make the background white, the font black and make the notification stay till dismissed. 

Swift
```swift
var background = UIColor.whiteColor()
var foreground = UIColor.blackColor()
var font = UIFont.boldSystemFontOfSize(10.0)
var Interval = NSTimeInterval.init(-1)
NotifySwift.getInstance().setInAppNotificationOptionsBackground(redColor, foreground: redColor, font: font, duration: NSTimeInterval, canBeDismissedByUser: true)
```

Objective C
```objectivec
UIColor *foreground = [UIColor colorWithRed:0.0f/255.0f green:0.0f/255.0f blue:0.0f/255.0f alpha:1.0f];

UIColor *background = [UIColor colorWithRed:255.0f/255.0f green:255.0f/255.0f blue:255.0f/255.0f alpha:1.0f];
 
[[Notify getInstance] setInAppNotificationOptionsBackground:background
 foreground:foreground
 font:[UIFont boldSystemFontOfSize:10.0]
            	 duration:-1
            	 canBeDismissedByUser:true];
```

##3.7 Deep linking
Deep linking from a push into the app is automatically handled via our push integration.

When a user clicks on a notification with a url, we process the request and then invoke the  `application:openURL:sourceApplication:annotation:` method with the following parameters:
* `url` the url specified in the notification payload. 
* `source` com.notify.push.notification
* `annotation` a dictionary representing the notification payload

Swift
```swift
func application(application: UIApplication, openURL url: NSURL, sourceApplication: String?, annotation: AnyObject) -> Bool {
if(annotation is NSDictionary) {
   var annotation_dict = annotation  as! NSDictionary        
if annotation_dict.objectForKey("data") == nil 
    return true
 } else {
    annotation_dict = annotation_dict["data"] as! NSDictionary
}
//Use annotation_dict to do deeplink
}
```

Objective C
```objectivec
- (BOOL)application:(UIApplication *)application 
	openURL:(NSURL *)url
	sourceApplication:(NSString *)sourceApplication
	annotation:(id)annotation {
	
		NSDictionary *dict = annotation;
		NSDictionary *data_dict = nil;
	    	
	    	if (dict != nil) {
	        
		        if([dict objectForKey:@"data"] != nil) {
		        	data_dict = dict[@"data"];
		        	//Use data dictionary      
		        }
	        }
        }
```

##3.8 Icon Badging 
You can optionally have our notifications increment the user’s badge count.  You can reset the badge count to zero by making the following call: 

Swift
```swift
NotifySwift.getInstance().resetBadge()
```

Objective C
```objectivec
[[Notify getInstance] resetBadge];
```

##3.9 Login
You should call login as soon as the user is identified (generally after logging in). 

Logging in a user, allow you to track users across devices and platforms, improving the quality of recommendations. 

Before calling login, we assign a unique identifier to your users and classify them as anonymous users.  Upon calling login, the anonymous user’s activity history is transferred to the logged in user’s profile.  

Your userId should be unique and unchanging. 

Swift
```swift
NotifySwift.getInstance().loginUser(userId)
```

Objective C
```objectivec
[[Notify getInstance] loginUser:userId];
```

##3.10 Logout
You will need to tell us when the user logs out of your app.  After logout, our platform defaults to an anonymous user. 

You can do that with following: 
Swift
```swift
NotifySwift.getInstance().logoutUser()
```

Objective C
```objectivec
[[Notify getInstance] logoutUser];
```

##3.11 Adding User Attributes 
Our platform gives you the ability to target users based on attributes and uses attributes to improve recommendations.  It is important to keep attributes up-to-date.  

Attributes include, but are not limited to email, gender, telephone number and other demographic information.  User attributes can be set using the `addUserAttribute` API. 

Attributes you should supply, include the following:
* Email
* Username
* Gender
* TwitterID
* FacebookID

Note: We currently do not merge user attributes on login.  If you set attributes for an anonymous user, you will have to set them again after calling login. 

Here is an example of setting the user’s email address and gender. 

Swift
```swift
let test_dic: [String:String] = ["email":"somename@somedomain.com,”gender”:”female”]
NotifySwift.getInstance().addUserAttribute(test_dic)
```

Objective C
```objectivec
[[Notify getInstance] addUserAttribute:@{@"email":@"somename@somedomain.com,@”gender”:@”female”}];
```

##3.12 The user id of the Currently Logged in User

You can get the userID of the currently logged in user by making the following call:

Swift
```swift
NotifySwift.getInstance().getUserId()
```

Objective C
```objectivec
[[Notify getInstance] getUserId];
```

##3.13 How to get your push token

You can retrieve the device’s current push token by making the following call:

Swift
```swift
NotifySwift.getInstance().getPushToken()
```

Objective C
```objectivec
[[Notify getInstance] getUserId];
```

##3.14 How to get the device id
We generate a DeviceId to uniquely identify each device. To the extent possible, we keep this ID the same through application upgrades. 

Swift
```swift
NotifySwift.getInstance().getDeviceId()
```

Objective C
```objectivec
[[Notify getInstance] getDeviceId];
```

##3.17 Notification Subscription Management 
We provide advanced subscription management for users allowing them to opt-in or opt-out of individual types of notification.  You determing notification types and can include things like product recommendations or trending content. 

Each user’s subscription state is synced to our backend.  To get a list of notification types and the user’s current subscription state you register handlers with the `registerSubscriptionListHandlers`.  The use of these handlers is explained below. 

* `OnGetSubsListSuccess` is called when the list of notification types has been successfully synced to the device.  The list of notification types is passed to the handler as an array.  Each entry in the array is a dictionary that defines a particular notification type.  The following keys that are defined in the dictionary :
* `subscription_id` The ID of this notification type
* `display` The display name of this notification type
* `desc` The display description of this notification type
* `value` The user’s subscription state for this notification. true = subscribed, false = unsubscribed 
* `type` This is for future use, we currently only one type ‘sub’

For example a notification type called “Recommended Items” that the user is currently subscribed to would be represented by:
```
{
    “subscription_id” = “recommended_items”;
    “display” = “Recommended Items”;
    “desc” = "Personalized recommendations for you";
    “value” = true;
    “type” = “sub”;
}
```

Note: We sync notifications during SDK initialization which will result in the invocation of this handler.  If there was a network error during initialization we’ll continue retrying and this handler will be called as soon as the list is ready. 

* `OnGetSubsListError` is called when due to network issue or if the notification types have not completed syncing yet.  If this is called we recommend displaying an error message to the user.  We will continue retrying to sync will call the OnSuccess once the sync is complete.  

* `OnGetSubsListUpdate` is called when list is updated for example when a user unsubscribes from a notification type. 

Following code snippet shows OnSuccess and OnError handlers.

Swift
```swift
Notify?.registerSubscriptionListHandlers(OnSuccess, onError: OnError, onUpdate: OnUpdate)

func OnSuccess(subsList:[AnyObject]!) -> Void {     
	NSLog("%@",subsList as NSArray)       
}

func OnUpdate(arr:[AnyObject]!) -> Void {
	NSLog("%@",arr as NSArray)
}

func OnError(str:String!) -> Void  {
	NSLog("%@",str)
}
```

Objective C
```objectivec
[[Notify getInstance] registerSubscriptionListHandlers:onSuccess onError: OnError onUpdate: onUpdate];

void onSuccess(NSArray * subsList) {
	NSLog(@”%@”,subsList);
}

void OnError(NSString *error) {  
	NSLog(@”Error occurred  %@”,error);
}

void onUpdate(NSArray * subsList) {
	NSLog(@”%@”,subsList);
}
```

You can update an individual subscription setting by calling the setSubscription method, which will also result in the invocation of your onupdate handler.

Swift
```swift
NotifySwift.getInstance().setSubscription(“key1”, state: true)
```

Objective C
```objectivec
[[Notify getInstance] setSubscription:@”key1” state:true];
```
