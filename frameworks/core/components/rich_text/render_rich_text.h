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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICHTEXT_RENDER_RICHTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICHTEXT_RENDER_RICHTEXT_H

#include "core/components/common/layout/constants.h"
#include "core/components/rich_text/resource/rich_text_delegate.h"
#include "core/components/rich_text/rich_text_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderRichText : public RenderNode {
    DECLARE_ACE_TYPE(RenderRichText, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    RenderRichText() : RenderNode(true) {}
    ~RenderRichText() override = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void MarkNeedRender(bool overlay = false);
    void OnGlobalPositionChanged() override;

    void UpdateLayoutParams(const int32_t width, const int32_t height);
    void SetDelegate(const RefPtr<RichTextDelegate>& delegate)
    {
        delegate_ = delegate;
    }

private:
    void CreateRealWeb(int32_t top, int32_t left, bool visible, bool reCreate = false);

protected:
    RefPtr<RichTextDelegate> delegate_;

private:
    Size drawSize_;
    int32_t webContentWidth_ = 0;
    int32_t webContentHeight_ = 0;
    bool hasCreateWeb_ = false;
    bool isVisible_ = true;
    bool initPositionSet_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICHTEXT_RENDER_RICHTEXT_H
