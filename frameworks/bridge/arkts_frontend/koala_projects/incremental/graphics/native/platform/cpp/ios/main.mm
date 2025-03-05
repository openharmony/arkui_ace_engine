/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#import <GrBackendSurface.h>
#import <GrDirectContext.h>
#import <mtl/GrMtlBackendContext.h>
#import <mtl/GrMtlTypes.h>

#import "koala-view.h"

@interface ViewController : UIViewController

- (IBAction)startKoala;

@end

@interface ViewController ()
{
    id<MTLDevice> device;
    id<MTLCommandQueue> commandQueue;
    id<MTLLibrary> defaultLibrary;
    CAMetalLayer* metalLayer;
    id<CAMetalDrawable> currentDrawable;

    KoalaView* koalaView;
}
@end

@implementation ViewController


// TODO: hack, rework.
void setKoalaView(KoalaView* koalaView);

-(void)loadView {
    [super loadView];

    koalaView = [[KoalaView alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)];
    self.view = koalaView;
    setKoalaView((KoalaView*)self.view);
    [self startApplication];
}

-(void)startApplication {
    NSLog(@"Start app");
    const char* appJS = [self getAppJS];
    skoala_startJS((__bridge void*)self.view, appJS);
}

- (const char*)getAppJS {
    NSError* error;
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"Data/js/app" ofType:@"js"];
    if(filePath) {
        NSString *text = [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:&error];
        if(text) {
            return [text UTF8String];
        }
    }
    return "";
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator {
    const float scale = [UIScreen mainScreen].scale;
    CGRect frame = CGRectMake(0, 0, size.width, size.height);
    metalLayer.frame = frame;
    metalLayer.drawableSize = CGSizeMake(size.width * scale, size.height * scale);

    if (koalaView)
        [koalaView onResize:size.width withHeight:size.height];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    device = MTLCreateSystemDefaultDevice();

    commandQueue = [device newCommandQueue];
    defaultLibrary = [device newDefaultLibrary];

    metalLayer = [CAMetalLayer layer];
    metalLayer.device = device;
    metalLayer.opaque = NO;
    metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    metalLayer.contentsGravity = kCAGravityTopLeft;
    metalLayer.framebufferOnly = YES;
    metalLayer.frame = self.view.layer.frame;
    [metalLayer removeAllAnimations];
    [metalLayer setNeedsDisplayOnBoundsChange: YES];

    const CGSize Size = self.view.frame.size;
    const float scale = [UIScreen mainScreen].scale;
    self.view.contentScaleFactor = scale;

    CGRect frame = CGRectMake(0, 0, Size.width, Size.height);
    metalLayer.frame = frame;
    metalLayer.contentsScale = scale;
    metalLayer.drawableSize = CGSizeMake(Size.width * scale, Size.height * scale);

    extern void setMetalData(id<MTLDevice> device, CAMetalLayer* metalLayer, id<MTLCommandQueue> queue);
    setMetalData(metalLayer.device, metalLayer, commandQueue);

    [self.view.layer addSublayer: metalLayer];
   
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    CGFloat topPadding = [self view].safeAreaInsets.top;
    
    const CGSize Size = self.view.frame.size;
    CGRect frame = CGRectMake(0, topPadding, Size.width, Size.height);
    metalLayer.frame = frame;
    
    [koalaView setWorkArea:CGRectMake(0, topPadding, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ViewController *viewController;

@end

@interface AppDelegate ()
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    self.window = [[UIWindow alloc] initWithFrame:CGRectMake(0,0,[UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height)];
    self.viewController = [[ViewController alloc]initWithNibName:nil bundle:nil];
    UINavigationController *navi = [[UINavigationController alloc]initWithRootViewController:self.viewController];
    self.window.rootViewController = navi;
    self.window.backgroundColor = [UIColor blackColor];
    [self.window makeKeyAndVisible];

    extern void setUIWindow(UIWindow* window);
    setUIWindow(self.window);
 
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end


int main(int argc, char * argv[]) {
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}