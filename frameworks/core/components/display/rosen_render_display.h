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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_ROSEN_RENDER_DISPLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_ROSEN_RENDER_DISPLAY_H

#include "core/components/display/render_display.h"

namespace OHOS::Ace {

class RosenRenderDisplay : public RenderDisplay {
    DECLARE_ACE_TYPE(RosenRenderDisplay, RenderDisplay);

public:
    RosenRenderDisplay() = default;
    ~RosenRenderDisplay() override = default;

    void Update(const RefPtr<Component>& component) override;
    void Paint(RenderContext& context, const Offset& offset) override;

    void OnAttachContext() override
    {
        animatableOpacity_.SetContextAndCallback(
            context_, std::bind(&RosenRenderDisplay::OnOpacityAnimationCallback, this));
    }

    void UpdateOpacity(uint8_t opacity) override
    {
        RenderNode::UpdateOpacity(opacity);
    }

    bool SupportOpacity() override
    {
        return true;
    }
    void OnRemove() override;

protected:
    void OnOpacityAnimationCallback();
    void OnVisibleChanged() override;
    virtual void ClearRenderObject() override;
    void OnRSTransition(TransitionType type, unsigned long long rsNodeId) override;

private:
    bool pendingTransitionAppearing_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_FLUTTER_RENDER_DISPLAY_H
