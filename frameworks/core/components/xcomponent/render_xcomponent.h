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
#include "core/components/xcomponent/native_render_context.h"
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

    virtual void PluginContextInit(NativeRenderContext* context) = 0;
    virtual void PluginUpdate() = 0;
    virtual void SetTextureId(int64_t id) = 0;

    void SetXComponentSizeChange(XComponentSizeChangeEvent &&xcomponentSizeChangeEvent)
    {
        xcomponentSizeChangeEvent_ = std::move(xcomponentSizeChangeEvent);
    }

    NativeRenderContext* GetPluginContext() const
    {
        return pluginContext_;
    }

protected:
    RefPtr<XComponentDelegate> delegate_;
    RefPtr<XComponentTaskPool> pool_;
    std::list<TaskFunction> tasks_;
    NativeRenderContext* pluginContext_ = nullptr;
    XComponentSizeChangeEvent xcomponentSizeChangeEvent_;

    Offset position_;
    Size drawSize_;
    Offset prePosition_;
    Size preDrawSize_;
    int64_t textureId_ = -1;

private:
    void CreateXComponentPlatformResource();
    void UpdateXComponentLayout();
    void CallXComponentLayoutMethod();
    std::string MakeMethodHash(const std::string& method) const;
    bool isCreatePlatformResourceSuccess_ = false;
    State state_ = State::UNINITIALIZED;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_RENDER_XCOMPONENT_H
