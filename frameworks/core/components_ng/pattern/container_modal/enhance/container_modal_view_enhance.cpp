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

#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"

#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/container_modal/container_modal_utils.h"

namespace OHOS::Ace::NG {
/**
 * The structure of container_modal enhanced is designed as follows :
 * |--container_modal(stack)
 *   |--column
 *      |--container_modal_custom_title(row)
 *          |--custom_node(js)
 *      |--stack
 *          |--container_modal_content(stage)
 *              |--page
 *          |--dialog(when show)
 *      |--gesture_row(row)
 *   |--container_modal_custom_floating_title(row)
 *          |--custom_node(js)
 *   |--container_modal_control_buttons(row)
 *          |--[maxRecover, minimize, close](button)
 */

RefPtr<FrameNode> ContainerModalViewEnhance::Create(RefPtr<FrameNode>& content)
{
    auto containerModalNode = FrameNode::CreateFrameNode("ContainerModal",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ContainerModalPatternEnhance>());
    auto stack = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto controlButtonsRow = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), MakeRefPtr<LinearLayoutPattern>(false));

    column->AddChild(BuildTitle(containerModalNode));
    stack->AddChild(content);
    column->AddChild(stack);
    column->AddChild(BuildGestureRow(containerModalNode));
    auto containerPattern = containerModalNode->GetPattern<ContainerModalPatternEnhance>();
    CHECK_NULL_RETURN(containerPattern, nullptr);
    containerModalNode->AddChild(column);
    containerModalNode->AddChild(BuildTitle(containerModalNode, true));
    containerModalNode->AddChild(BuildCustomButtonRow(controlButtonsRow));
    containerPattern->Init();
    return containerModalNode;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildCustomButtonRow(RefPtr<FrameNode>& containerRow)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalViewEnhance BuildCustomButtonRow called");
    CHECK_NULL_RETURN(containerRow, nullptr);
    auto isSucc = ExecuteCustomTitleAbc();
    if (!isSucc) {
        return nullptr;
    }
    auto customNode = NG::ViewStackProcessor::GetInstance()->GetCustomButtonNode();
    containerRow->AddChild(customNode);
    return containerRow;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalViewEnhance BuildTitle called");
    auto titleRow = BuildTitleContainer(containerNode, isFloatingTitle);
    CHECK_NULL_RETURN(titleRow, nullptr);
    return titleRow;
}

RefPtr<FrameNode> ContainerModalViewEnhance::AddControlButtons(
    RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow)
{
    WeakPtr<ContainerModalPatternEnhance> weakPattern = containerNode->GetPattern<ContainerModalPatternEnhance>();
    RefPtr<FrameNode> maximizeBtn = BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE,
        [weakPattern](GestureEvent& info) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnMaxButtonClick(info);
        });
    maximizeBtn->UpdateInspectorId("EnhanceMaximizeBtn");

    // add long press event
    WeakPtr<FrameNode> weakMaximizeBtn = maximizeBtn;
    auto longPressCallback = [weakPattern, weakMaximizeBtn](GestureEvent& info) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto maximizeBtn = weakMaximizeBtn.Upgrade();
        CHECK_NULL_VOID(maximizeBtn);
        pattern->ShowMaxMenu(maximizeBtn);
    };
    // diable mouse left!
    auto hub = maximizeBtn->GetOrCreateGestureEventHub();
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    hub->SetLongPressEvent(longPressEvent, false, true);

    auto eventHub = maximizeBtn->GetOrCreateInputEventHub();
    auto hoverMoveFuc = [weakPattern](MouseInfo& info) {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnMaxBtnInputEvent(info);
    };
    eventHub->AddOnMouseEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverMoveFuc)));

    // add hover in out event
    auto hoverEventFuc = [weakPattern, weakMaximizeBtn](bool hover) mutable {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnMaxBtnHoverEvent(hover, weakMaximizeBtn);
    };
    eventHub->AddOnHoverEvent(AceType::MakeRefPtr<InputEvent>(std::move(hoverEventFuc)));
    containerTitleRow->AddChild(maximizeBtn);

    RefPtr<FrameNode> minimizeBtn =BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE,
        [weakPattern](GestureEvent& info) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnMinButtonClick(info);
        });
    // minimizeBtn add empty panEvent to over fater container event
    minimizeBtn->UpdateInspectorId("EnhanceMinimizeBtn");
    containerTitleRow->AddChild(minimizeBtn);

    RefPtr<FrameNode> closeBtn = BuildControlButton(
        InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE,
        [weakPattern](GestureEvent& info) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnCloseButtonClick(info);
        },
        true);
    // closeBtn add empty panEvent to over fater container event
    closeBtn->UpdateInspectorId("EnhanceCloseBtn");
    containerTitleRow->AddChild(closeBtn);

    return containerTitleRow;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildMenuItemIcon(InternalResource::ResourceId resourceId)
{
    auto icon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto iconLayoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo sourceInfo;
    sourceInfo.SetResourceId(resourceId);
    auto theme = PipelineContext::GetCurrentContext()->GetTheme<AdvancedPatternTheme>();
    if (theme) {
        sourceInfo.SetFillColor(theme->GetPrimaryColor());
    } else {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "BuildMenuItemIcon AdvancedPatternTheme is null");
    }
    iconLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    iconLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TITLE_BUTTON_SIZE), CalcLength(TITLE_BUTTON_SIZE)));
    icon->MarkModifyDone();
    return icon;
}

RefPtr<FrameNode> ContainerModalViewEnhance::BuildGestureRow(RefPtr<FrameNode>& containerNode)
{
    auto pattern = containerNode->GetPattern<ContainerModalPatternEnhance>();
    auto gestureRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto renderContext = gestureRow->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    renderContext->UpdatePosition(OffsetT<Dimension>());
    auto layoutProp = gestureRow->GetLayoutProperty();
    layoutProp->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(CONTAINER_TITLE_HEIGHT)));
    return gestureRow;
}

} // namespace OHOS::Ace::NG
