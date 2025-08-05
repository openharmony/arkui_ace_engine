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

#import "engine.h"
#import "koala-view.h"

struct MetalData {
    id<MTLDevice> device;
    id<CAMetalDrawable> currentDrawable;
    CAMetalLayer* metalLayer;
    id<MTLCommandQueue> queue;
    UIWindow* window;
    void* pool;

    MetalData() : device(nullptr), currentDrawable(nullptr), metalLayer(nullptr), queue(nullptr), pool(nullptr) {}

};

UIWindow* window = nullptr;
MetalData* data = nullptr;
CGPoint* pointer = nullptr;

void setUIWindow(UIWindow* _window) {
    ::window = _window;
}

void setMetalData(id<MTLDevice> device, CAMetalLayer* metalLayer, id<MTLCommandQueue> queue) {
    MetalData* data = new MetalData();
    data->device = device;
    data->metalLayer = metalLayer;
    data->queue = queue;
    data->window = window;
    ::data = data;
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
        id<CAMetalDrawable> currentDrawable = [metal->metalLayer nextDrawable];
        if (!currentDrawable) {
            assert(false);
            return nullptr;
        }
        metal->currentDrawable = currentDrawable;
        info.fTexture.retain((__bridge GrMTLHandle)currentDrawable.texture);
        return new GrBackendRenderTarget(physicalWidth, physicalHeight, info);
    }
}

MetalData* getMetalData() {
    return ::data;
}

extern "C" void* objc_autoreleasePoolPush(void);
extern "C" void objc_autoreleasePoolPop(void*);
void metalMakeCurrent(UIWindow* window) {
    if (window) {
        MetalData* metal = getMetalData();
        metal->pool = objc_autoreleasePoolPush();
    }
}

void metalSwapBuffers() {
    void* pool = nullptr;
    @autoreleasepool {
        MetalData* metal = getMetalData();
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

static JscScopedState* theJscState = nullptr;
// TODO: get rid of theKoalaView.
static KoalaView* theKoalaView = nullptr;

void setKoalaView(KoalaView* koalaView) {
    theKoalaView = koalaView;
}

KNativePointer IosEngine::getFrame(KNativePointer peerPtr, int width, int height) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    peer->userData = ::data;
    return (__bridge KNativePointer)window;
}

KInt IosEngine::getFrameWidth(UIWindow* window) {
    KInt width = window.windowScene.screen.bounds.size.width;
    return width;
}

KInt IosEngine::getFrameHeight(UIWindow* window) {
    KInt height = window.windowScene.screen.bounds.size.height;
    return height;
}

KInt IosEngine::getPhysicalWidth(UIWindow* window) {
    // TODO: is it correct?
    KInt width = window.windowScene.screen.bounds.size.width * window.windowScene.screen.scale;
    return width;
}

KInt IosEngine::getPhysicalHeight(UIWindow* window) {
    // TODO: is it correct?
    KInt height = window.windowScene.screen.bounds.size.height * window.windowScene.screen.scale;
    return height;
}

KFloat IosEngine::getContentScale(UIWindow* window) {
    return window.windowScene.screen.scale;
}

bool IosEngine::makeCurrent(UIWindow* window) {
    metalMakeCurrent(window);
    return true;
}

void IosEngine::swapBuffers(UIWindow* window) {
    metalSwapBuffers();
    return;
}

bool IosEngine::checkEvents(UIWindow* window) {
    if(peer) {
        while(!_pendingEvents.empty()) {
            auto e = std::move(_pendingEvents.front());
            _pendingEvents.pop_front();
            switch(e->kind) {
                case Kind::TAP:
                    peer->callOnTap(e->count, e->args1, e->args2, e->arg3, e->target, 0);
                    break;
                case Kind::MOVE:
                    peer->callOnMove(e->count, e->args1, e->args2);
                    break;
                case Kind::RESIZE:
                    peer->callOnResize(e->args1[0], e->args2[0]);
                    break;
                default:
                    // lifecircle events
                    break;
            }
        }
    }
    return true;
}

void IosEngine::addTouchesEvent(NSSet<UITouch*>* touches, int kind, UIView* view, CGRect workArea) {
    int countFinger = touches.count;
    auto pointerEvent = std::make_unique<Event>(Kind::TAP, countFinger);
    int index = 0;
    for (UITouch* touch in touches) {
        auto location = [touch locationInView:view];
        pointerEvent->args1[index] = location.x;
        pointerEvent->args2[index] = location.y - workArea.origin.y;
        index++;
    }
    if (kind == 1 && countFinger > 1) {
        multitouchDown = true;
    }

    if (kind == 3 && countFinger > 1 && !multitouchDown) {
        // Simulate multitouch down event, if we discovered tap by another finger during move.
        auto pointerEventSim = std::make_unique<Event>(Kind::TAP, countFinger);
        pointerEventSim->arg3 = 1;
        pointerEventSim->target = 0;
        memcpy_s(pointerEventSim->args1, sizeof(pointerEventSim->args1), pointerEvent->args1, countFinger * 4);
        memcpy_s(pointerEventSim->args2, sizeof(pointerEventSim->args2), pointerEvent->args2, countFinger * 4);
        _pendingEvents.emplace_back(std::forward<std::unique_ptr<Event>>(pointerEventSim));
        multitouchDown = true;
    }

    if (kind == 2 && multitouchDown) {
        // Ensure we send multitouch up for multitouch down.
        multitouchDown = false;
        if (countFinger == 1) {
            pointerEvent->count++;
            pointerEvent->args1[countFinger] = pointerEvent->args1[countFinger - 1];
            pointerEvent->args2[countFinger] = pointerEvent->args2[countFinger - 1];
        }
    }
    pointerEvent->target = 0;
    if (kind == 3) {
        pointerEvent->kind = Kind::MOVE;
        pointerEvent->arg3 = 0;
    } else {
        pointerEvent->arg3 = (kind == 1) ? 1 : 0;
    }
    _pendingEvents.emplace_back(std::forward<std::unique_ptr<Event>>(pointerEvent));
}

void IosEngine::onResize(int width, int height) {
    _pendingEvents.emplace_back(std::make_unique<Event>(Kind::RESIZE, width, height));
}

SkString* IosEngine::getClipboard(UIWindow* window) {
    SkString* result = nullptr;
    return result;
}

void IosEngine::setClipboard(UIWindow* window, const SkString& str) {
    return;
}

void IosEngine::requestHaptic(int p1, int p2) {
    return;
}

void IosEngine::softKeyboard(bool show) {
    (show) ? [theKoalaView showScreenKeyboard] : [theKoalaView hideScreenKeyboard];
    return;
}

void IosEngine::setMousePoint(CGPoint point) {
    pointer.x = point.x;
    pointer.y = point.y;
}

void IosEngine::globalPointer(int &x, int &y) {
    x = pointer.x;
    y = pointer.y;
}

void IosEngine::commitInput() {
    [theKoalaView cleanEnteredText];
}

void IosEngine::setCursor(UIWindow* window, SkoalaCursor cursor) {
    return;
}

static KNativePointer get_frame(void* enginePtr, void* peerPtr, int width, int height, int flags, int placement, int x, int y) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    return engine->getFrame(peerPtr, width, height);
}

static int get_frame_width(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->getFrameWidth(window);
}

static int get_frame_height(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->getFrameHeight(window);
}

static int get_physical_width(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->getPhysicalWidth(window);
}

static int get_physical_height(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->getPhysicalHeight(window);
}

static float get_content_scale(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->getContentScale(window);
}

static bool make_current(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->makeCurrent(window);
}

static void swap_buffers(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    engine->swapBuffers(window);
}

static bool check_events(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->checkEvents(window);
}

static void request_haptic(void* enginePtr, int p1, int p2) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    return engine->requestHaptic(p1, p2);
}

static void soft_keyboard(void* enginePtr, bool show) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    return engine->softKeyboard(show);
}

static void commit_input(void* enginePtr) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    return engine->commitInput();
}

static void set_cursor(void* enginePtr, void* context, SkoalaCursor cursor) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->setCursor(window, cursor);
}

static SkString* get_clipboard(void* enginePtr, void* context) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->getClipboard(window);
}

static void set_clipboard(void* enginePtr, void* context, const SkString& str) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    UIWindow* window = (__bridge UIWindow*)context;
    return engine->setClipboard(window, str);
}

static void get_global_pointer(void* enginePtr, KInt* pointer) {
    IosEngine* engine = reinterpret_cast<IosEngine*>(enginePtr);
    engine->globalPointer(pointer[0], pointer[1]);
}


RedrawerPeer* iosPeerFactory(void* arg, JSObjectRef redrawer) {
    RedrawerPeer* peer = new RedrawerPeer(theJscState, redrawer);
    IosEngine* engine = reinterpret_cast<IosEngine*>(arg);
    engine->peer = peer;
    peer->engine = engine;
    peer->getFrame = get_frame;
    peer->getFrameWidth = get_frame_width;
    peer->getFrameHeight = get_frame_height;
    peer->getPhysicalWidth = get_physical_width;
    peer->getPhysicalHeight = get_physical_height;
    peer->getContentScale = get_content_scale;
    peer->makeCurrent = make_current;
    peer->swapBuffers = swap_buffers;
    peer->checkEvents = check_events;
    peer->requestHaptic = request_haptic;
    peer->softKeyboard = soft_keyboard;
    peer->commitInput = commit_input;
    peer->setCursor = set_cursor;
    peer->readFromClipboard = get_clipboard;
    peer->writeToClipboard = set_clipboard;
    peer->getGlobalPointer = get_global_pointer;

    if (theKoalaView) {
        [theKoalaView setEngine:engine];
    }

    return peer;
}

peerFactory_t getIosPeerFactory(JscScopedState* jscState) {
    theJscState = jscState;
    return iosPeerFactory;
}

void* getIosPeerFactoryArg() {
    return new IosEngine();
}