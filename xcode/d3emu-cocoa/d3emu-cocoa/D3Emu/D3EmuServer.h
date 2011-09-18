#import <Foundation/Foundation.h>

@interface D3EmuServer : NSObject {
@private
    int _socket;
    BOOL _alive;
}

@property (nonatomic, retain) NSString *host;
@property (nonatomic, retain) NSString *port;

- (id)initWithHost:(NSString *)host port:(NSString *)port;
- (void)run;

@end