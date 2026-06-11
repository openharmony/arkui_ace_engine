/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_FULL_SCREEN_VIDEO_OVERLAY_HANDLER_BRIDGE_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_FULL_SCREEN_VIDEO_OVERLAY_HANDLER_BRIDGE_H

#include <cstdint>
#include <functional>

#ifdef WEB_SUPPORTED

namespace OHOS::Ace {

class VideoOverlayHandlerTransferRefCount {
public:
    VideoOverlayHandlerTransferRefCount() = default;
    ~VideoOverlayHandlerTransferRefCount() = default;
    void IncRefCount() { referencedCount_++; }
    int32_t DecRefCount()
    {
        referencedCount_--;
        return referencedCount_;
    }
    int32_t RefCount() { return referencedCount_; }
private:
    int32_t referencedCount_ = 0;
};

struct VideoOverlayListenerCallbacks {
    std::function<void(int32_t)> OnStatusChanged;
    std::function<void(bool)> OnMutedChanged;
    std::function<void(double)> OnPlaybackRateChanged;
    std::function<void(double)> OnDurationChanged;
    std::function<void(double)> OnTimeUpdate;
    std::function<void(double)> OnBufferedEndTimeChanged;
    std::function<void()> OnEnded;
    std::function<void(int32_t, int32_t)> OnVideoSizeChanged;
};

struct FullScreenVideoOverlayHandlerBridgeVTable {
    void (*destroy)(void*);
    void (*setVideoSurface)(void*, const char*, size_t);
    void (*requestMediaControl)(void*, int32_t, const char*, size_t);
    void (*addListener)(void*, const VideoOverlayListenerCallbacks*);
};

class FullScreenVideoOverlayHandlerBridge : public VideoOverlayHandlerTransferRefCount {
public:
    explicit FullScreenVideoOverlayHandlerBridge(void* handlerPtr,
        FullScreenVideoOverlayHandlerBridgeVTable vtable)
        : handlerPtr_(handlerPtr), vtable_(vtable) {}
    ~FullScreenVideoOverlayHandlerBridge()
    {
        if (handlerPtr_ && vtable_.destroy) {
            vtable_.destroy(handlerPtr_);
            handlerPtr_ = nullptr;
        }
    }
    void* GetHandlerPtr() const { return handlerPtr_; }
private:
    void* handlerPtr_;
    FullScreenVideoOverlayHandlerBridgeVTable vtable_;
};

} // namespace OHOS::Ace

#endif // WEB_SUPPORTED

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_FULL_SCREEN_VIDEO_OVERLAY_HANDLER_BRIDGE_H
