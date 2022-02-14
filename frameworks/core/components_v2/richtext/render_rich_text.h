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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_RICHTEXT_RENDER_RICHTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_RICHTEXT_RENDER_RICHTEXT_H

#include "core/components/common/layout/constants.h"
#include "core/components_v2/richtext/rich_text_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {
class RenderRichText : public RenderNode {
    DECLARE_ACE_TYPE(V2::RenderRichText, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    RenderRichText() : RenderNode(true) {}
    ~RenderRichText() override = default;

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void OnPaintFinish() override;

private:
    RefPtr<RichTextComponent> component_;
};
} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_RICHTEXT_RENDER_RICHTEXT_H
