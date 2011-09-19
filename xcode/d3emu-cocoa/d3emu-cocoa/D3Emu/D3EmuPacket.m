#import "D3EmuPacket.h"

@implementation D3EmuPacket

@synthesize name;

- (id)initWithName:(NSString *)theName
{
    self = [super init];
    if (self) {
        name = [theName retain];
    }
    
    return self;
}

@end
