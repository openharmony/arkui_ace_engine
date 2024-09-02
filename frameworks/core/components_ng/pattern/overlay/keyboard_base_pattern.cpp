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

#include "core/components_ng/pattern/overlay/keyboard_base_pattern.h"

#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void KeyboardPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildAtIndex(0);
    while (child) {
        // find first framenode, filter SyntaxItem
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode) {
            auto layoutProperty = childFrameNode->GetLayoutProperty();
            if (!layoutProperty) {
                break;
            }
            // set custom keyboard view width match parent
            std::optional<CalcLength> height = std::nullopt;
            auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
            if (layoutConstraint != nullptr && layoutConstraint->selfIdealSize) {
                height = layoutConstraint->selfIdealSize->Height();
            }
            auto dimension = Dimension(1.0f, DimensionUnit::PERCENT);
            layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dimension), height));
            if (CheckChildPosition(childFrameNode)) {
                host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
            }
            break;
        }
        child = child->GetChildAtIndex(0);
    }
}

bool KeyboardPattern::CheckChildPosition(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto childRender = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(childRender, false);
    return childRender->HasPosition();
}

void KeyboardPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("TargetId: ")
                                        .append(std::to_string(targetId_)));
}

void KeyboardPattern::OnModifyDone()
{
    auto context = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddOnAreaChangeNode(GetHost()->GetId());
}

void KeyboardPattern::OnAreaChangedInner()
{
    if (!supportAvoidance_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto customHeight = GetKeyboardHeight();
    if (NearEqual(customHeight, keyboardHeight_)) {
        return;
    }
    auto boundaryHeight = 0.0f;
    // Check that the effective height of the keyboard is captured
    if (std::abs(customHeight) > boundaryHeight) {
        auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        Rect keyboardRect = Rect(0.0f, 0.0f, 0.0f, customHeight);
        TAG_LOGI(ACE_KEYBOARD, "customKeyboardHeight Change to %{public}f, safeHeight: %{public}f",
            customHeight, safeHeight_);
        pipeline->OnVirtualKeyboardAreaChange(keyboardRect, nullptr, safeHeight_, supportAvoidance_, true);
    }
    keyboardHeight_ = customHeight;
}

void KeyboardPattern::SetKeyboardAreaChange(bool keyboardAvoidance)
{
    if (keyboardAvoidance) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto keyboardHeight = GetKeyboardHeight();
        auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        Rect keyboardRect = Rect(0.0f, 0.0f, 0.0f, keyboardHeight);
        TAG_LOGI(ACE_KEYBOARD, "customKeyboardHeight Change to %{public}f, safeHeight: %{public}f",
            keyboardHeight, safeHeight_);
        pipeline->OnVirtualKeyboardAreaChange(keyboardRect, nullptr, safeHeight_, supportAvoidance_, true);
    }
}

float KeyboardPattern::GetKeyboardHeight()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto child = host->GetChildAtIndex(0);
    while (child) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (!childFrameNode) {
            child = child->GetChildAtIndex(0);
            continue;
        }
        auto hostRect = host->GetTransformRectRelativeToWindow();
        if (!CheckChildPosition(childFrameNode)) {
            return hostRect.Height();
        }
        auto childRender = childFrameNode->GetRenderContext();
        CHECK_NULL_RETURN(childRender, false);
        auto positionY = childRender->GetPositionValue({}).GetY().ConvertToPx();
        return hostRect.Height() - positionY > 0.0f ? hostRect.Height() - positionY : 0.0f;
    }
    return 0.0f;
}

void KeyboardPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveOnAreaChangeNode(node->GetId());
}

void KeyboardPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("TargetId", targetId_);
}
} // namespace OHOS::Ace::NG