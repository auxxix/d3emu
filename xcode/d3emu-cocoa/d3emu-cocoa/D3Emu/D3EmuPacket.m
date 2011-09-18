#import "D3EmuPacket.h"

@implementation D3EmuPacket

@synthesize data;

- (id)initWithData:(NSData *)theData
{
    self = [super init];
    if (self) {
        data = [theData retain];
    }
    return self;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@ Length=0", [self className]];
}

@end
