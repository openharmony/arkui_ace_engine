/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BASE_NODE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BASE_NODE_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"

namespace OHOS::Ace::Framework {
class JSBaseNode : public AceType {
    DECLARE_ACE_TYPE(JSBaseNode, AceType);
public:
    JSBaseNode() = default;
    JSBaseNode(const NG::OptionalSizeF& size, NodeRenderType renderType, std::string surfaceId)
        : size_(size), renderType_(renderType), surfaceId_(std::move(surfaceId))
    {}
    ~JSBaseNode() override = default;

    static void JSBind(BindingTarget globalObj);
    static void ConstructorCallback(const JSCallbackInfo& info);
    static void DestructorCallback(JSBaseNode* node);
    void FinishUpdateFunc(const JSCallbackInfo& info);
    void Create(const JSCallbackInfo& info);
    void BuildNode(const JSCallbackInfo& info);
    void ProccessNode(bool isSupportExportTexture, bool isSupportLazyBuild);
    void PostTouchEvent(const JSCallbackInfo& info);
    void PostInputEvent(const JSCallbackInfo& info);
    void UpdateStart(const JSCallbackInfo& info);
    void UpdateEnd(const JSCallbackInfo& info);
    void OnRecycleWithBindThis(const JSCallbackInfo& info);
    void OnReuseWithBindThis(const JSCallbackInfo& info);
    void Dispose(const JSCallbackInfo&  /*info*/)
    {
        viewNode_.Reset();
        realNode_.Reset();
    }

private:
    bool InitTouchEvent(const JSCallbackInfo& info, TouchEvent& touchEvent, bool isPostTouchEvent);
    bool InitMouseEvent(const JSCallbackInfo& info, MouseEvent& mouseEvent);
    bool InitAxisEvent(const JSCallbackInfo& info, AxisEvent& axisEvent);
    bool GetTouches(const JSCallbackInfo& info, TouchEvent& touchEvent);
    bool GetInputTouches(const JSCallbackInfo& info, TouchEvent& touchEvent);
    bool ParamTouchEvent(const JSCallbackInfo& info, TouchEvent& touchEvent);
    bool ParamMouseEvent(const JSCallbackInfo& info, MouseEvent& mouseEvent);
    bool ParamAxisEvent(const JSCallbackInfo& info, AxisEvent& axisEvent);
    bool GetChangedTouches(const JSCallbackInfo& info, TouchEvent& touchEvent);
    RefPtr<NG::FrameNode> viewNode_;
    RefPtr<NG::UINode> realNode_;
    NG::OptionalSizeF size_;
    NodeRenderType renderType_ = NodeRenderType::RENDER_TYPE_DISPLAY;
    std::string surfaceId_;
    std::unique_ptr<NG::ScopedViewStackProcessor> scopedViewStackProcessor_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BASE_NODE_H
