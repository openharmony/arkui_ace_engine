/*
Copyright (c) 2025 Huawei Device Co., Ltd.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_CHILDREN_MAIN_SIZE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_CHILDREN_MAIN_SIZE_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"

namespace OHOS::Ace::Framework {
using OnStateChangedFunc =  std::function<void(size_t start, size_t deleteCount, std::vector<float>&& newChildrenSize)>;
using OnDefaultSizeUpdateFunc =  std::function<void(double defaultSize)>;

class JSListChildrenMainSize : public Referenced {
public:
    JSListChildrenMainSize() = default;
    ~JSListChildrenMainSize() override = default;
    static void JSBind(BindingTarget globalObj);

    void SetOnStateChangedCallback(OnStateChangedFunc callback)
    {
        onStateChangedCallback_ = callback;
    }

    void OnStateChanged(const JSCallbackInfo& info);

    void SetOnDefaultSizeUpdate(OnDefaultSizeUpdateFunc callback)
    {
        onDefaultSizeUpdate_ = callback;
    }

    void OnDefaultSizeUpdate(const JSCallbackInfo& info);

    void SetHost(const WeakPtr<NG::FrameNode>& host)
    {
        host_ = host;
    }

    RefPtr<NG::FrameNode> GetHost()
    {
        return host_.Upgrade();
    }

    bool IsHostEqual(const NG::FrameNode* node)
    {
        auto frameNode = host_.Upgrade();
        CHECK_NULL_RETURN(frameNode, false);
        return frameNode == node;
    }

    static void SetNativeChildrenMainSize(JSRef<JSObject> jsStack, JSRef<JSObject> nativeChildrenSize);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSListChildrenMainSize);
    static void Constructor(const JSCallbackInfo& info);
    static void Destructor(JSListChildrenMainSize* mainSize);
    OnStateChangedFunc onStateChangedCallback_;
    OnDefaultSizeUpdateFunc onDefaultSizeUpdate_;
    WeakPtr<NG::FrameNode> host_;
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_CHILDREN_MAIN_SIZE_H