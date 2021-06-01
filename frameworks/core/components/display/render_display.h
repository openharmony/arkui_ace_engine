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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_RENDER_DISPLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_RENDER_DISPLAY_H

#include "core/components/display/display_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderDisplay : public RenderNode {
    DECLARE_ACE_TYPE(RenderDisplay, RenderNode);

public:
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;

    void Dump() override;

    void UpdateVisibleType(VisibleType type)
    {
        if (visible_ != type) {
            visible_ = type;
            MarkNeedLayout();
        }
    }

    void UpdateOpacity(uint8_t opacity) override
    {
        if (disableLayer_) {
            for (auto& callback : opacityCallbacks_) {
                callback(opacity);
            }
            return;
        }
        if (opacity_ != opacity) {
            opacity_ = opacity;
            MarkNeedRender();
        }
    }

    uint8_t GetOpacity() const
    {
        return opacity_;
    }

    VisibleType GetVisibleType()
    {
        return visible_;
    }

    void GetOpacityCallbacks();

    bool GetVisible() const override;

protected:
    VisibleType visible_ = VisibleType::VISIBLE;
    bool disableLayer_ = false;
    std::list<OpacityCallback> opacityCallbacks_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DISPLAY_RENDER_DISPLAY_H
