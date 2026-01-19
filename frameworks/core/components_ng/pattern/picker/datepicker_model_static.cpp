/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/picker/datepicker_model_static.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BUFFER_NODE_NUMBER = 2;
}

static RefPtr<FrameNode> CreateAndSetupColumnNode(const std::string& tag, int32_t columnId,
    uint32_t showCount, const RefPtr<FrameNode>& parent)
{
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        tag, columnId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(columnNode, nullptr);
    
    for (uint32_t index = 0; index < showCount; index++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MountToParent(columnNode);
    }
    columnNode->MarkModifyDone();
    
    return columnNode;
}

void DatePickerModelStatic::SetupDateOrder(const RefPtr<FrameNode>& dateNode, const std::string& dateOrder,
    const RefPtr<FrameNode>& yearColumnNode, const RefPtr<FrameNode>& monthColumnNode,
    const RefPtr<FrameNode>& dayColumnNode, bool hasYearNode, bool hasMonthNode, bool hasDayNode)
{
    if (dateOrder == "M-d-y") {
        if (!hasMonthNode) {
            CreateDateColumn(monthColumnNode, dateNode);
        }
        if (!hasDayNode) {
            CreateDateColumn(dayColumnNode, dateNode);
        }
        if (!hasYearNode) {
            CreateDateColumn(yearColumnNode, dateNode);
        }
    } else {
        if (!hasYearNode) {
            CreateDateColumn(yearColumnNode, dateNode);
        }
        if (!hasMonthNode) {
            CreateDateColumn(monthColumnNode, dateNode);
        }
        if (!hasDayNode) {
            CreateDateColumn(dayColumnNode, dateNode);
        }
    }
}

static void SetupColumnNode(RefPtr<DatePickerPattern>& datePickerPattern,
    const RefPtr<FrameNode>& columnNode, bool hasNode)
{
    if (!hasNode) {
        datePickerPattern->SetColumn(columnNode);
    }
}

static void ApplyCircleDialStyle(const RefPtr<FrameNode>& dateNode, const RefPtr<PickerTheme>& pickerTheme)
{
    if (pickerTheme->IsCircleDial()) {
        auto renderContext = dateNode->GetRenderContext();
        renderContext->UpdateBackgroundColor(pickerTheme->GetBackgroundColor());
    }
}

RefPtr<FrameNode> DatePickerModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, dateNode);
    datePickerPattern->SetPickerTag(true);
    datePickerPattern->UpdateDateOrder();

    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();

    auto yearId = datePickerPattern->GetYearId();
    auto monthId = datePickerPattern->GetMonthId();
    auto dayId = datePickerPattern->GetDayId();

    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, dateNode);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>(dateNode->GetThemeScopeId());
    CHECK_NULL_RETURN(pickerTheme, dateNode);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    DatePickerModelNG::SetDefaultAttributes(dateNode, pickerTheme);

    auto yearColumnNode = CreateAndSetupColumnNode(V2::COLUMN_ETS_TAG, yearId, showCount, dateNode);
    CHECK_NULL_RETURN(yearColumnNode, dateNode);

    auto monthColumnNode = CreateAndSetupColumnNode(V2::COLUMN_ETS_TAG, monthId, showCount, dateNode);
    CHECK_NULL_RETURN(monthColumnNode, dateNode);

    auto dayColumnNode = CreateAndSetupColumnNode(V2::COLUMN_ETS_TAG, dayId, showCount, dateNode);
    CHECK_NULL_RETURN(dayColumnNode, dateNode);

    SetupColumnNode(datePickerPattern, yearColumnNode, hasYearNode);
    SetupColumnNode(datePickerPattern, monthColumnNode, hasMonthNode);
    SetupColumnNode(datePickerPattern, dayColumnNode, hasDayNode);

    SetupDateOrder(dateNode, datePickerPattern->GetDateOrder(),
                   yearColumnNode, monthColumnNode, dayColumnNode,
                   hasYearNode, hasMonthNode, hasDayNode);

    ApplyCircleDialStyle(dateNode, pickerTheme);

    return dateNode;
}

void DatePickerModelStatic::CreateDateColumn(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode)
{
    auto stackNode = CreateStackNode();
    auto blendNode = CreateColumnNode();
    auto buttonNode = CreateButtonNode();
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    layoutProperty->UpdateLayoutWeight(1);
    stackNode->MountToParent(dateNode);
}

RefPtr<FrameNode> DatePickerModelStatic::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> DatePickerModelStatic::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> DatePickerModelStatic::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

void DatePickerModelStatic::SetOnChange(FrameNode* frameNode, DateChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void DatePickerModelStatic::SetChangeEvent(FrameNode* frameNode, DateChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void DatePickerModelStatic::SetSelectedDate(FrameNode* frameNode, const int64_t& value)
{
    std::time_t time = static_cast<std::time_t>(value / 1000);
    std::tm local_tm{};
#ifdef WINDOWS_PLATFORM
    errno_t err = localtime_s(&local_tm, &time);
    if (err != 0) {
        LOGE("Failed to convert time to local time, error code: %{public}d", err);
        return;
    }
#else
    localtime_r(&time, &local_tm);
#endif

    const auto year = local_tm.tm_year + 1900;
    const auto month = local_tm.tm_mon + 1;
    const auto day = local_tm.tm_mday;
    DatePickerModelNG::SetSelectedDate(frameNode, PickerDate(year, month, day));
}
} // namespace OHOS::Ace::NG
 