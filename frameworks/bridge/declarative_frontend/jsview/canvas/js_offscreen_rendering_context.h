/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_OFFSCREEN_RENDERING_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_OFFSCREEN_RENDERING_CONTEXT_H

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_renderer.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context_settings.h"

namespace OHOS::Ace::Framework {

class JSOffscreenRenderingContext : public JSCanvasRenderer {
public:
    JSOffscreenRenderingContext();
    ~JSOffscreenRenderingContext() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSOffscreenRenderingContext* controller);

    void JsTransferToImageBitmap(const JSCallbackInfo& info);

    static void AddOffscreenCanvasPattern(const RefPtr<AceType>& pattern)
    {
        CHECK_NULL_VOID(pattern);
        std::lock_guard<std::mutex> lock(mutex_);
        offscreenPatternMap_[offscreenPatternCount_++] = pattern;
    }

    static RefPtr<AceType> GetOffscreenPattern(int32_t id)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return offscreenPatternMap_[id];
    }

    uint32_t GetId()
    {
        return id_;
    }

    void SetWidth(double width)
    {
        width_ = width;
    }

    double GetWidth() const
    {
        return width_;
    }

    void SetHeight(double height)
    {
        height_ = height;
    }

    double GetHeight() const
    {
        return height_;
    }

    ACE_DISALLOW_COPY_AND_MOVE(JSOffscreenRenderingContext);

private:
    static std::mutex mutex_;
    uint32_t id_;
    double width_ = 0.0f;
    double height_ = 0.0f;
    static std::unordered_map<uint32_t, RefPtr<AceType>> offscreenPatternMap_;
    static uint32_t offscreenPatternCount_;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_OFFSCREEN_RENDERING_CONTEXT_H
