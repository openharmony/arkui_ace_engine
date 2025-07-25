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
#include "jsc-interop.h"

#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#import <GrBackendSurface.h>
#import <GrDirectContext.h>
#import <mtl/GrMtlBackendContext.h>
#import <mtl/GrMtlTypes.h>

#include <iostream>
#include <deque>

struct IosEngine {
    RedrawerPeer* peer = nullptr;
    std::deque<std::unique_ptr<Event>> _pendingEvents;
    bool multitouchDown = false;
    CGPoint pointer = CGPointMake(0.0f, 0.0f);

    // Called by OS.
    void addTouchesEvent(NSSet<UITouch*>* touches, int kind, UIView* view, CGRect workArea);
    void onResize(int width, int height);

    // Called by JS code.
    KNativePointer getFrame(KNativePointer peerPtr, int width, int height);
    KInt getFrameWidth(UIWindow* window);
    KInt getFrameHeight(UIWindow* window);
    KFloat getContentScale(UIWindow* window);
    KInt getPhysicalWidth(UIWindow* window);
    KInt getPhysicalHeight(UIWindow* window);
    bool makeCurrent(UIWindow* window);
    void swapBuffers(UIWindow* window);
    bool checkEvents(UIWindow* window);
    SkString* getClipboard(UIWindow* window);
    void setClipboard(UIWindow* window, const SkString& str);
    void requestHaptic(int p1, int p2);
    void softKeyboard(bool show);
    void commitInput();
    void setCursor(UIWindow* window, SkoalaCursor cursor);
    void setMousePoint(CGPoint point);
    void globalPointer(int &x, int &y);
};
