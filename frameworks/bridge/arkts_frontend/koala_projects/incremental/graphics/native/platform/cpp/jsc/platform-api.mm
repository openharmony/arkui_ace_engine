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

#include <iostream>
#include <vector>

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common-interop.h"
#include "jsc-interop.h"
#include "skoala.h"
#include "SkString.h"

#include <mach/mach.h>


JSValueRef Jsc_setTimeout(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef argument[], JSValueRef* exception) {
    auto* functionHolder = new JSValueHolder(ctx, function);
    auto* callbackHolder = new JSValueHolder(ctx, argument[0]);

    double ms = JSValueToNumber(ctx, argument[1], nullptr); // number of ms
    JSValueHolder* callbackArguments = nullptr;
    int callbackArgumentsCount = argumentCount - 2;
    if (argumentCount > 2) {
        callbackArguments = new JSValueHolder[callbackArgumentsCount];
        for (size_t i = 0; i < callbackArgumentsCount; i++) {
            callbackArguments[i].init(ctx, argument[i + 2]);
        }
    }

    NSTimer* timer = [NSTimer scheduledTimerWithTimeInterval:ms / 1000
        target:[NSBlockOperation blockOperationWithBlock:^{
                JSValueRef* args = new JSValueRef[callbackArgumentsCount];
                for (int i = 0; i < callbackArgumentsCount; i++) {
                    args[i] = callbackArguments[i].value;
                }
                JSObjectCallAsFunction(ctx, callbackHolder->obj(), functionHolder->obj(), callbackArgumentsCount, args, nullptr);
                if (callbackArguments) delete [] callbackArguments;
                delete callbackHolder;
                delete functionHolder;
        }]
        selector:@selector(main)
        userInfo:nil
        repeats:NO
    ];
    (void)timer;
    return JSValueMakeUndefined(ctx);
}
MAKE_JSC_EXPORT_V1(setTimeout)

KNativePointer impl_skoala_getHomeDirectoryForCurrentUser() {
    NSString* homedir = NSHomeDirectoryForUser(NSUserName());
    const char* homedirUtf8 = homedir.UTF8String;
    const NSUInteger len = [homedir lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    return new SkString(homedirUtf8, len);
}
KOALA_INTEROP_0(skoala_getHomeDirectoryForCurrentUser, KNativePointer)

KNativePointer impl_skoala_getTemporaryDirectoryForCurrentUser() {
    NSString* tempdir = NSTemporaryDirectory();
    const char* tempdirUtf8 = tempdir.UTF8String;
    const NSUInteger len = [tempdir lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    return new SkString(tempdirUtf8, len);
}
KOALA_INTEROP_0(skoala_getTemporaryDirectoryForCurrentUser, KNativePointer)

KNativePointer impl_skoala_getBundlePath() {
    NSString* bundlePath = NSBundle.mainBundle.resourcePath;
    const char* bundlePathUtf8 = bundlePath.UTF8String;
    const NSUInteger len = [bundlePath lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    return new SkString(bundlePathUtf8, len);
}
KOALA_INTEROP_0(skoala_getBundlePath, KNativePointer)

KInt impl_skoala_createDirectory(const KStringPtr& path) {
    NSString* pathDir = [NSString stringWithUTF8String:path.c_str()];
    NSFileManager* fm = [NSFileManager defaultManager];
    NSError* error;
    if([fm createDirectoryAtPath:pathDir withIntermediateDirectories:NO attributes:nil error:&error]) {
        NSLog(@"Create Dir");
        return 0;
    } else {
        NSLog(@"Create Error: %@", error);
        return 1;
    }
}
KOALA_INTEROP_1(skoala_createDirectory, KInt, KStringPtr)

KInt impl_skoala_removeFile(const KStringPtr& path) {
    NSString* filePath = [NSString stringWithUTF8String:path.c_str()];
    NSFileManager* fm = [NSFileManager defaultManager];
    NSError* error;
    if([fm removeItemAtPath:filePath error:&error]) {
        NSLog(@"File was removed");
        return 0;
    } else {
        NSLog(@"Removed error: %@", error);
        return 1;
    }
}
KOALA_INTEROP_1(skoala_removeFile, KInt, KStringPtr)

KNativePointer impl_skoala_enumerateFiles(const KStringPtr& path) {
    DIR* dir = opendir(path.c_str());
    struct dirent* entry = nullptr;
    auto* result = new std::vector<std::string>();
    while ((entry = readdir(dir)) != nullptr) {
        result->push_back(std::string(entry->d_name));
    }
    closedir(dir);
    return result;
}
KOALA_INTEROP_1(skoala_enumerateFiles, KNativePointer, KStringPtr)

KInt impl_skoala_enumerateFilesLength(KNativePointer filesPtr) {
    auto* files = reinterpret_cast<std::vector<std::string>*>(filesPtr);
    return files->size();
}
KOALA_INTEROP_1(skoala_enumerateFilesLength, KInt, KNativePointer)

void impl_skoala_releaseEnumerator(KNativePointer files) {
    delete reinterpret_cast<std::vector<std::string>*>(files);
}
KOALA_INTEROP_V1(skoala_releaseEnumerator, KNativePointer)

KNativePointer impl_skoala_enumerateFilesElement(KNativePointer filesPtr, KInt index) {
    auto* files = reinterpret_cast<std::vector<std::string>*>(filesPtr);
    auto elememt = (*files)[index];
    return new SkString(elememt);
}
KOALA_INTEROP_2(skoala_enumerateFilesElement, KNativePointer, KNativePointer, KInt)

KInt impl_skoala_isDirectory(const KStringPtr& pathPtr) {
    struct stat statBuffer;
    if (stat(pathPtr.c_str(), &statBuffer) != 0) {
        return 0;
    }
    return S_ISDIR(statBuffer.st_mode);
}
KOALA_INTEROP_1(skoala_isDirectory, KInt, KStringPtr)

@protocol ResponseProtocol <JSExport>

@property NSString* url;
@property NSInteger status;
@property JSValue* buffer;
@property NSString* text;

- (void)initUrl:(NSString*)url;
- (void)initStatus:(NSInteger)status;
- (void)initBuffer:(JSValue*)buffer;
- (void)initText:(NSString*)text;

@end

@interface Response : NSObject<ResponseProtocol>
@end

@implementation Response

@synthesize url = _url;
@synthesize status = _status;
@synthesize buffer = _buffer;
@synthesize text = _text;

- (void)initUrl:(NSString*)url
{
    _url = [url copy];
}
- (void)initStatus:(NSInteger)status
{
    _status = status;
}
- (void)initBuffer:(JSValue*)buffer
{
    _buffer = buffer;
}
- (void)initText:(NSString*)text
{
    _text = [text copy];
}
@end

JSValueRef Jsc_skoala_fetch(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef argument[], JSValueRef* exception) {
    auto* functionHolder = new JSValueHolder(ctx, function);
    auto urlHolder = JSValueHolder(ctx, argument[0]);
    auto* callbackHolder = new JSValueHolder(ctx, argument[1]);
    auto optionsHolder = JSValueHolder(ctx, argument[2]);

    JSStringRef arg = JSValueToStringCopy(ctx, urlHolder.value, nullptr);
    NSString* url = (__bridge NSString*)JSStringCopyCFString(kCFAllocatorDefault, arg);

    NSMutableURLRequest* request = [[NSMutableURLRequest alloc] init];
    [request setURL:[NSURL URLWithString:url]];
    [request setHTTPMethod:@"GET"];

    /* request headers*/
    if(!JSValueIsUndefined(ctx, optionsHolder.value)) {
        JSValueRef headers = JSObjectGetProperty(ctx, optionsHolder.obj(), JSStringCreateWithUTF8CString("headers"), nullptr);
        JSValueRef array = JSObjectGetProperty(ctx, JSValueToObject(ctx, headers, nullptr), JSStringCreateWithUTF8CString("headers"), nullptr);
        JSValueRef lengthProperty = JSObjectGetProperty(ctx, JSValueToObject(ctx, array, nullptr), JSStringCreateWithUTF8CString("length"), nullptr);
        int length = JSValueToNumber(ctx, lengthProperty, nullptr);
        for (int i = 0; i < length; i++) {
            JSStringRef tmp = JSValueToStringCopy(ctx, JSObjectGetPropertyAtIndex(ctx, JSValueToObject(ctx, array, nullptr), i, nullptr), nullptr);
            NSString* param = (__bridge NSString*)JSStringCopyCFString(kCFAllocatorDefault, tmp);
            NSArray* listItems = [param componentsSeparatedByString:@","];
            [request setValue: [listItems objectAtIndex: 0] forHTTPHeaderField: [listItems objectAtIndex: 1]];
        }
    }

    JSContext* context = [JSContext contextWithJSGlobalContextRef:JSContextGetGlobalContext(ctx)];
    __block Response* globalResponse = [[Response alloc] init];

    /* Async */
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse* response, NSData* data, NSError* error) {
        NSHTTPURLResponse* httpResponse = (NSHTTPURLResponse*)response;

        [globalResponse initUrl:[response URL].absoluteString];
        [globalResponse initStatus:[httpResponse statusCode]];
        SkData* instance = SkData::MakeWithCopy(reinterpret_cast<const void*>(data.bytes), data.length).release();
        [globalResponse initBuffer:[JSValue valueWithJSValueRef:makePointer(ctx, reinterpret_cast<KNativePointer>(instance)) inContext:context]];
        [globalResponse initText:[[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding]];

        int callbackArgumentsCount = 2;
        JSValueHolder* callbackArguments = nullptr;
        callbackArguments = new JSValueHolder[callbackArgumentsCount];
        callbackArguments[0].init(ctx, [[JSValue valueWithObject:globalResponse inContext:context] JSValueRef]);
        callbackArguments[1].init(ctx, JSValueMakeNumber(ctx, 0));

        JSValueRef* args = new JSValueRef[callbackArgumentsCount];
        for (int i = 0; i < callbackArgumentsCount; i++) {
            args[i] = callbackArguments[i].value;
        }

        JSObjectCallAsFunction(ctx, callbackHolder->obj(), functionHolder->obj(), callbackArgumentsCount, args, nullptr);
        if (callbackArguments) delete[] callbackArguments;
        delete callbackHolder;
        delete functionHolder;
    }];

    return JSValueMakeUndefined(ctx);

}
MAKE_JSC_EXPORT(skoala_fetch)

KInt impl_skoala_jsc_memory() {
    struct task_basic_info info;
    mach_msg_type_number_t size = TASK_BASIC_INFO_COUNT;
    task_info(mach_task_self(),
                                    TASK_BASIC_INFO,
                                    (task_info_t)&info,
                                    &size);

  return static_cast<KInt>(info.resident_size / 1048576);
}
KOALA_INTEROP_0(skoala_jsc_memory, KInt)

KInt impl_skoala_jsc_cpu() {
    thread_array_t threads;
    mach_msg_type_number_t threadCount;
    if (task_threads(mach_task_self(), &threads, &threadCount) != KERN_SUCCESS) {
        return -1;
    }
    double usage = 0;
    for (int i = 0; i < threadCount; i++) {
        thread_info_data_t     threadInfo;
        mach_msg_type_number_t threadInfoCount = THREAD_INFO_MAX;
        if (thread_info(threads[i], THREAD_BASIC_INFO, (thread_info_t) threadInfo, &threadInfoCount) != KERN_SUCCESS) {
            usage = -1;
            break;
        }
        auto info = (thread_basic_info_t) threadInfo;
        if ((info->flags & TH_FLAGS_IDLE) == 0) {
            usage += double(info->cpu_usage) / TH_USAGE_SCALE;
        }
    }
    vm_deallocate(mach_task_self(), (vm_offset_t) threads, threadCount * sizeof(thread_t));
    return static_cast<KInt>(usage*100);
}
KOALA_INTEROP_0(skoala_jsc_cpu, KInt)