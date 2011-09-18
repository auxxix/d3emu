#import "D3EmuPacket.h"

@implementation D3EmuPacket

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@ Length=0", [self className]];
}

- (NSInteger)length
{
    return 0;
}

@end
