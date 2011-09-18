#import <Foundation/Foundation.h>

@interface D3EmuPacket : NSObject

@property (nonatomic, readonly) NSData *data;

- (id)initWithData:(NSData *)theData;

@end
