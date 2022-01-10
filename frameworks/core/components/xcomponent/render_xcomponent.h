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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_RENDER_XCOMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_RENDER_XCOMPONENT_H

#include "core/components/common/layout/constants.h"
#include "core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "core/components/xcomponent/resource/xcomponent_delegate.h"
#include "core/components/xcomponent/xcomponent_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
class RenderXComponent : public RenderNode {
    DECLARE_ACE_TYPE(RenderXComponent, RenderNode);

public:
    using XComponentSizeChangeEvent = std::function<void(int64_t, int32_t, int32_t)>;
    static RefPtr<RenderNode> Create();

    ~RenderXComponent() override = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnPaintFinish() override;

#ifdef OHOS_STANDARD_SYSTEM
    using XComponentHiddenChangeEvent = std::function<void(bool)>;

    void SetHidden(bool hidden, bool inRecursion) override;

    void OnAppShow() override
    {
        LOGI("RenderXComponent: window OnAppShow.");
        RenderNode::OnAppShow();
        if (xcomponentHiddenChangeEvent_) {
            xcomponentHiddenChangeEvent_(false);
        }
    }

    void OnAppHide() override
    {
        LOGI("RenderXComponent: window OnAppHidden.");
        RenderNode::OnAppHide();
        if (xcomponentHiddenChangeEvent_) {
            xcomponentHiddenChangeEvent_(true);
        }
    }

    void SetXComponentHiddenChange(XComponentHiddenChangeEvent &&xcomponentHiddenChangeEvent)
    {
        xcomponentHiddenChangeEvent_ = std::move(xcomponentHiddenChangeEvent);
    }
#endif

    void PushTask(const TaskFunction& func);

    void SetDelegate(const RefPtr<XComponentDelegate>& delegate)
    {
        delegate_ = delegate;
    }

    enum class State: char {
        UNINITIALIZED,
        RESIZING,
        READY,
    };

    void NativeXComponentInit(
        NativeXComponent* nativeXComponent,
        WeakPtr<NativeXComponentImpl> nativeXComponentImpl);

    void NativeXComponentDestroy();

    void SetXComponentSizeChange(XComponentSizeChangeEvent &&xcomponentSizeChangeEvent)
    {
        xcomponentSizeChangeEvent_ = std::move(xcomponentSizeChangeEvent);
    }

    void NativeXComponentDispatchTouchEvent(const TouchInfo& touchInfo);

protected:
    RefPtr<XComponentDelegate> delegate_;
    RefPtr<XComponentTaskPool> pool_;
    std::list<TaskFunction> tasks_;
    NativeXComponent* nativeXComponent_ = nullptr;
    WeakPtr<NativeXComponentImpl> nativeXComponentImpl_;
    XComponentSizeChangeEvent xcomponentSizeChangeEvent_;
#ifdef OHOS_STANDARD_SYSTEM
    XComponentHiddenChangeEvent xcomponentHiddenChangeEvent_;
#endif

    Offset position_;
    Size drawSize_;
    Offset prePosition_;
    Size preDrawSize_;
    int64_t textureId_ = -1;

private:
    void CreateXComponentPlatformResource();
    void UpdateXComponentLayout();
    void CallXComponentLayoutMethod();
    void NativeXComponentOffset(const double& x, const double& y);
    std::string MakeMethodHash(const std::string& method) const;
    bool isCreatePlatformResourceSuccess_ = false;
    State state_ = State::UNINITIALIZED;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_RENDER_XCOMPONENT_H
