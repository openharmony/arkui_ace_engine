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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_RICHTEXT_RICHTEXT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_RICHTEXT_RICHTEXT_COMPONENT_H

#include "core/components/web/web_component.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace::V2 {
// A component can show HTML rich-text.
class ACE_EXPORT RichTextComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(V2::RichTextComponent, SoleChildComponent);

public:
    RichTextComponent();
    ~RichTextComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetData(const std::string& data)
    {
        data_ = data;
        webComponent_->SetType(data);
    }

    const std::string& GetData() const
    {
        return data_;
    }

    void SetPageStartedEventId(const EventMarker& pageStartedEventId)
    {
        return webComponent_->SetPageStartedEventId(pageStartedEventId);
    }

    void SetPageFinishedEventId(const EventMarker& pageFinishedEventId)
    {
        return webComponent_->SetPageFinishedEventId(pageFinishedEventId);
    }

    RefPtr<WebController> GetController() const
    {
        if (!webComponent_) {
            return nullptr;
        }
        return webComponent_->GetController();
    }

private:
    RefPtr<WebComponent> webComponent_;
    std::string data_;

    ACE_DISALLOW_COPY_AND_MOVE(RichTextComponent);
};
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_RICHTEXT_RICHTEXT_COMPONENT_H
