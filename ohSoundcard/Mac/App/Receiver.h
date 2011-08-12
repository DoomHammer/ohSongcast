
#import <Cocoa/Cocoa.h>
#import "Preferences.h"


// Enum for the receiver state
typedef enum
{
    eReceiverStateOffline,
    eReceiverStateDisconnected,
    eReceiverStateConnecting,
    eReceiverStateConnected
    
} EReceiverState;


// Declaration of a class to hold receiver data
@interface Receiver : NSObject
{
    NSString* udn;
    NSString* room;
    NSString* group;
    NSString* name;
    void* iPtr;
}

@property (assign) NSString* udn;
@property (assign) NSString* room;
@property (assign) NSString* group;
@property (assign) NSString* name;

- (id) initWithPtr:(void*)aPtr;
- (id) initWithPref:(PrefReceiver*)aPref;
- (void) updateWithPtr:(void*)aPtr;
- (PrefReceiver*) convertToPref;
- (EReceiverState) status;
- (void) play;
- (void) stop;
- (void) standby;

@end


