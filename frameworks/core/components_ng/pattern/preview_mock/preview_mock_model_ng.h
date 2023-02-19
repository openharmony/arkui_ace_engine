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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PREVIEW_MOCK_PREVIEW_MOCK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PREVIEW_MOCK_PREVIEW_MOCK_MODEL_NG_H

#include <functional>
#include <string>

#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/components_ng/pattern/preview_mock/preview_mock_model.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension DEFAULT_FONT_SIZE = 30.0_px;
constexpr double DEFAULT_OFFSET = 25;
constexpr double DEFAULT_HEIGHT = 30;
}

class ACE_EXPORT PreviewMockModelNG : public PreviewMockModel {
public:
    void Create(const std::string& content) {
        auto* stack = NG::ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode = NG::FrameNode::GetOrCreateFrameNode(
            content, nodeId, []() { return AceType::MakeRefPtr<NG::TextPattern>(); });
        CHECK_NULL_VOID(frameNode);
        stack->Push(frameNode);
        auto textLayoutProperty = frameNode->GetLayoutProperty<NG::TextLayoutProperty>();
        if (textLayoutProperty) {
            textLayoutProperty->UpdateContent("This component is not supported on PC preview.");
            textLayoutProperty->UpdateFontSize(DEFAULT_FONT_SIZE);
        }

        auto renderContext = frameNode->GetRenderContext();
        if (renderContext) {
            renderContext->UpdateBackgroundColor(Color::FromString("#808080"));
        }
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PREVIEW_MOCK_PREVIEW_MOCK_MODEL_NG_H
