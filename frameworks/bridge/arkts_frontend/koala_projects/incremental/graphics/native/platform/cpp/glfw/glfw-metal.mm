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

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#import <GrBackendSurface.h>
#import <GrDirectContext.h>
#import <mtl/GrMtlBackendContext.h>
#import <mtl/GrMtlTypes.h>

#include "skoala-interop.h"

void globalPointer(int &x, int &y) {
    NSPoint p = [NSEvent mouseLocation];
    CGFloat height = [[NSScreen mainScreen] frame].size.height;
    x = (int)p.x;
    y = (int)(height - p.y);
}

struct MetalData {
    id<MTLDevice> device;
    id<CAMetalDrawable> currentDrawable;
    CAMetalLayer* layer;
    id<MTLCommandQueue> queue;
    NSWindow* nswindow;
    void* pool;

    MetalData() : device(nullptr), currentDrawable(nullptr), layer(nullptr), queue(nullptr), pool(nullptr) {}
};

void initMetalLayer(CAMetalLayer* layer, int width, int height, int physicalWidth, int physicalHeight) {
    CGRect frame = CGRectMake(0, 0, width, height);
    layer.frame = frame;
    // to avoid warning in console:
    // CAMetalLayer ignoring invalid setDrawableSize width=0.000000 height=0.000000
    if (physicalWidth > 0 && physicalHeight > 0) {
        CGSize drawableSize = CGSizeMake(physicalWidth, physicalHeight);
        layer.drawableSize = drawableSize;
        layer.contentsScale = (float)physicalWidth / width;
    }
    layer.opaque = NO;
}

GLFWwindow* createMetalWindow(int width, int height, const char* title) {
    MetalData* data = new MetalData();

    CAMetalLayer* layer = [CAMetalLayer layer];
    const id<MTLDevice> gpu = layer.preferredDevice;
    const id<MTLCommandQueue> queue = [gpu newCommandQueue];
    layer.device = gpu;
    layer.opaque = NO;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.contentsGravity = kCAGravityTopLeft;
    // TODO: rethink those props.
    layer.displaySyncEnabled = YES;
    layer.presentsWithTransaction = NO;
    layer.allowsNextDrawableTimeout = NO;
    layer.backgroundColor = CGColorCreateSRGB(0.0f, 0.0f, 0.0f, 0.0f);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    NSWindow *nswindow = glfwGetCocoaWindow(window);
    nswindow.contentView.layer = layer;
    nswindow.contentView.wantsLayer = YES;
    nswindow.contentView.canDrawConcurrently = YES;
    nswindow.contentView.layerContentsRedrawPolicy = NSViewLayerContentsRedrawOnSetNeedsDisplay;

    int physicalWidth = 0, physicalHeight = 0;
    glfwGetFramebufferSize(window, &physicalWidth, &physicalHeight);

    [layer removeAllAnimations];
    [layer setAutoresizingMask: (kCALayerWidthSizable|kCALayerHeightSizable)];
    [layer setNeedsDisplayOnBoundsChange: YES];

    initMetalLayer(layer, width, height, physicalWidth, physicalHeight);

    data->layer = layer;
    data->device = gpu;
    data->queue = queue;
    data->nswindow = nswindow;

    glfwSetWindowUserPointer(window, data);

    return window;
}

MetalData* getMetalData(GLFWwindow* window) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    return peer ? reinterpret_cast<MetalData*>(peer->userData) : nullptr;
}

void resizeMetalWindow(GLFWwindow* window, int width, int height, int physicalWidth, int physicalHeight) {
    @autoreleasepool {
        MetalData* metal = getMetalData(window);
        initMetalLayer(metal->layer, width, height, physicalWidth, physicalHeight);
    }
}

sk_sp<GrDirectContext> makeMetalContext(RedrawerPeerBase* peer) {
    GrMtlBackendContext backendContext = {};
    MetalData* metal = reinterpret_cast<MetalData*>(peer->userData);
    backendContext.fDevice.retain((__bridge GrMTLHandle)metal->device);
    backendContext.fQueue.retain((__bridge GrMTLHandle)metal->queue);
    return GrDirectContext::MakeMetal(backendContext);
}

GrBackendRenderTarget* makeMetalRenderTarget(RedrawerPeerBase* peer, int physicalWidth, int physicalHeight) {
    @autoreleasepool {
        MetalData* metal = reinterpret_cast<MetalData*>(peer->userData);
        GrMtlTextureInfo info;
        id<CAMetalDrawable> currentDrawable = [metal->layer nextDrawable];
        if (!currentDrawable) {
            assert(false);
            return nullptr;
        }
        metal->currentDrawable = currentDrawable;
        info.fTexture.retain((__bridge GrMTLHandle)currentDrawable.texture);
        return new GrBackendRenderTarget(physicalWidth, physicalHeight, info);
    }
}

extern "C" void* objc_autoreleasePoolPush(void);
extern "C" void objc_autoreleasePoolPop(void*);
void metalMakeCurrent(GLFWwindow* window) {
    if (window) {
        MetalData* metal = getMetalData(window);
        if (metal)
            metal->pool = objc_autoreleasePoolPush();
    }
}

void metalSwapBuffers(GLFWwindow* window) {
    void* pool = nullptr;
    @autoreleasepool {
        MetalData* metal = getMetalData(window);
        if (metal->currentDrawable) {
            id<MTLCommandBuffer> commandBuffer = [metal->queue commandBuffer];
            commandBuffer.label = @"Present";
            [commandBuffer presentDrawable:metal->currentDrawable];
            [commandBuffer commit];
            [commandBuffer waitUntilCompleted];
            metal->currentDrawable = nil;
        }
        pool = metal->pool;
    }
    if (pool) {
        objc_autoreleasePoolPop(pool);
    }
}