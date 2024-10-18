/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "component_test/core/component_test_component_impl.h"

#include <string>

#include "component_test/core/combination_isscrollable.h"

#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_event_hub.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/marquee/marquee_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/radio/radio_event_hub.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/web/web_accessibility_property.h"

namespace OHOS::Ace::ComponentTest {
namespace {
constexpr char INSPECTOR_TYPE[] = "$type";
constexpr char INSPECTOR_ID[] = "$ID";
constexpr char INSPECTOR_RECT[] = "$rect";
constexpr char INSPECTOR_ATTRS[] = "$attrs";
constexpr char INSPECTOR_WIDTH[] = "width";
constexpr char INSPECTOR_HEIGHT[] = "height";
constexpr char INSPECTOR_RESOLUTION[] = "$resolution";
constexpr char INSPECTOR_CHILDREN[] = "$children";
constexpr char INSPECTOR_DEBUGLINE[] = "$debugLine";
constexpr char INSPECTOR_VIEW_ID[] = "$viewID";
constexpr char INSPECTOR_COMPONENT_TYPE[] = "type";
NG::RectF deviceRect;
} // namespace

void ComponentTestComponentImpl::TapImpl(ErrInfo& errInfo) const
{
    if (!GenericClick(TouchType::TAP)) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    }
}

void ComponentTestComponentImpl::DoubleTapImpl(ErrInfo& errInfo) const
{
    if (!GenericClick(TouchType::DOUBLE_TAP)) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    }
}

void ComponentTestComponentImpl::PressImpl(ErrInfo& errInfo, uint32_t duration) const
{
    if (!GenericClick(TouchType::PRESS, duration)) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    }
}

void ComponentTestComponentImpl::PinchOutImpl(float scale, ErrInfo& errInfo) const
{
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(uiNode_);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    CHECK_NULL_VOID(frameNode);
    NG::RectF rect = frameNode->GetTransformRectRelativeToWindow();
    auto viewScale = context->GetViewScale();
    float widthScale = context->GetRootWidth() * viewScale / rect.Width();
    float heightScale = context->GetRootHeight() * viewScale / rect.Height();
    float originalScale = (widthScale < heightScale) ? widthScale : heightScale;
    if (scale < 1) {
        return;
    } else if (scale > originalScale) {
        scale = originalScale;
    }
    PinchAction pinchAction(rect, scale);
    EventSequenceManager::GetInstance().Execute(&pinchAction);
}

void ComponentTestComponentImpl::PinchInImpl(float scale, ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    CHECK_NULL_VOID(uiNode_);
    CHECK_NULL_VOID(frameNode);
    NG::RectF rectBound = frameNode->GetTransformRectRelativeToWindow();
    if (scale > 1 && scale < 0) {
        return;
    }
    PinchAction pinchAction(rectBound, scale);
    EventSequenceManager::GetInstance().Execute(&pinchAction);
}

void ComponentTestComponentImpl::InputTextImpl(std::string text, ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = GetFrameNode();
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_NOT_SUPPORTED);
        return;
    }
    const RefPtr<NG::Pattern>& pattern = frameNode->GetPattern();
    if (!pattern) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return;
    }
    std::string currentText = GetTextImpl(errInfo);
    SingleKeyAction singleKeyAction(text, currentText);
    singleKeyAction.Send();
    return;
}

void ComponentTestComponentImpl::ClearTextImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return;
    }
    std::vector<OHOS::MMI::KeyCode> keyCodes;
    std::string buff = GetTextImpl(errInfo);
    keyCodes.push_back(OHOS::MMI::KeyCode::KEY_DPAD_DOWN);
    for (auto i : buff) {
        if (i == '\n') {
            keyCodes.push_back(OHOS::MMI::KeyCode::KEY_DPAD_DOWN);
        }
    }
    keyCodes.push_back(OHOS::MMI::KeyCode::KEY_DPAD_DOWN);
    keyCodes.push_back(OHOS::MMI::KeyCode::KEY_MOVE_END);
    for (size_t i = 0; i < buff.size(); i++) {
        keyCodes.push_back(OHOS::MMI::KeyCode::KEY_FORWARD_DEL);
    }
    SingleKeyAction singleKeyAction(keyCodes);
    singleKeyAction.Send();
    return;
}

RefPtr<NG::FrameNode> GetEndpointChildFrameNode(RefPtr<NG::UINode> parentNode, bool first)
{
    NG::UINode* node = parentNode.GetRawPtr();
    while (node && !node->IsAtomicNode()) {
        node = first ? node->GetFirstChild().GetRawPtr() : node->GetLastChild().GetRawPtr();
        if (AceType::InstanceOf<NG::FrameNode>(node)) {
            break;
        }
    }
    if (!node || !AceType::InstanceOf<NG::FrameNode>(node)) {
        node = nullptr;
    }
    return AceType::Claim<NG::FrameNode>(AceType::DynamicCast<NG::FrameNode>(node));
}

void ComponentTestComponentImpl::ScrollToBorderAsync(
    uint32_t speed, bool toTop, std::function<void(ErrInfo errInfo)>&& callback) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        callback(QueryRetMsg(ErrCode::RET_ERR_COMPONENT_NOT_SUPPORTED));
        return;
    }
    const RefPtr<NG::FrameNode>& endFrameNode = GetEndpointChildFrameNode(uiNode_, toTop);
    if (!endFrameNode) {
        callback(QueryRetMsg(ErrCode::RET_ERR_COMPONENT_NOT_SUPPORTED));
        return;
    }
    NG::RectF parentRect = frameNode->GetRectWithRender();
    NG::RectF endFrameRect = endFrameNode->GetTransformRectRelativeToWindow();
    float endY = toTop ? endFrameRect.GetY() : endFrameRect.GetY() + endFrameRect.Height();
    NG::PointF bottomPoint(parentRect.Center().GetX(), parentRect.Bottom());
    NG::PointF topPoint(parentRect.Center().GetX(), parentRect.Top());
    MoveAction* moveAction;
    if (toTop) {
        if (LessOrEqual(parentRect.GetY(), endY) && GreatNotEqual(parentRect.GetY() + parentRect.Height(), endY)) {
            callback({ ErrCode::RET_OK, "" });
            return;
        }
        MoveAction moveAction(topPoint, bottomPoint, TouchType::DRAG, speed);
        EventSequenceManager::GetInstance().Execute(&moveAction);
    } else {
        if (GreatOrEqual(parentRect.GetY() + parentRect.Height(), endY) && LessNotEqual(parentRect.GetY(), endY)) {
            callback({ ErrCode::RET_OK, "" });
            return;
        }
        MoveAction moveAction(bottomPoint, topPoint, TouchType::DRAG, speed);
        EventSequenceManager::GetInstance().Execute(&moveAction);
    }
    ComponentTestManagerProxy::PostJSTask(
        [this, speed, toTop, passedCallback = std::move(callback)](void* data) {
            ScrollToBorderAsync(speed, toTop, [passedCallback](ErrInfo errInfo) { passedCallback(errInfo); });
        },
        nullptr);
    return;
}

void ComponentTestComponentImpl::ScrollToTopImplAsync(
    uint32_t speed, std::function<void(ErrInfo errInfo)>&& callback) const
{
    ScrollToBorderAsync(speed, true, std::move(callback));
}

void ComponentTestComponentImpl::ScrollToBottomImplAsync(
    uint32_t speed, std::function<void(ErrInfo errInfo)>&& callback) const
{
    ScrollToBorderAsync(speed, false, std::move(callback));
}

std::string ComponentTestComponentImpl::GetIdImpl(ErrInfo& errInfo) const
{
    if (uiNode_) {
        const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
        if (frameNode) {
            return frameNode->GetInspectorId().value_or("");
        }
    }
    errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    return "";
}

bool GetTextByPattern(const RefPtr<NG::FrameNode>& frameNode, std::string& text)
{
    const RefPtr<NG::Pattern>& pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    if (AceType::InstanceOf<NG::TextFieldPattern>(pattern)) {
        auto textFieldPattern = AceType::DynamicCast<NG::TextFieldPattern>(pattern);
        CHECK_NULL_RETURN(textFieldPattern, false);
        text = textFieldPattern->GetTextValue();
        return true;
    } else if (AceType::InstanceOf<NG::SearchPattern>(pattern)) {
        auto searchPattern = AceType::DynamicCast<NG::SearchPattern>(pattern);
        if (searchPattern) {
            auto textFieldFrameNode = AceType::DynamicCast<NG::FrameNode>(frameNode->GetChildAtIndex(0));
            auto textFieldPattern = textFieldFrameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_RETURN(textFieldPattern, false);
            text = textFieldPattern->GetTextValue();
            return true;
        }
    }
    return false;
}
bool GetTextByEventHub(const RefPtr<NG::FrameNode>& frameNode, std::string& text)
{
    const RefPtr<NG::EventHub>& eventHub = frameNode->GetEventHub<NG::EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (AceType::InstanceOf<NG::CheckBoxEventHub>(eventHub)) {
        auto checkBoxEventHub = AceType::DynamicCast<NG::CheckBoxEventHub>(eventHub);
        if (checkBoxEventHub) {
            text = checkBoxEventHub->GetName();
            return true;
        }
    } else if (AceType::InstanceOf<NG::RadioEventHub>(eventHub)) {
        auto radioEventHub = AceType::DynamicCast<NG::RadioEventHub>(eventHub);
        if (radioEventHub) {
            text = radioEventHub->GetValue();
            return true;
        }
    }
    return false;
}
bool GetTextByAccessibilityProperty(const RefPtr<NG::FrameNode>& frameNode, std::string& text)
{
    const RefPtr<NG::AccessibilityProperty>& accessibilityProperty =
        frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    if (AceType::InstanceOf<NG::AccessibilityProperty>(accessibilityProperty)) {
        if (accessibilityProperty) {
            text = accessibilityProperty->GetText();
            return true;
        }
    }
    return false;
}
bool GetTextByLayoutProperty(const RefPtr<NG::FrameNode>& frameNode, std::string& text)
{
    const RefPtr<NG::LayoutProperty>& layoutProperty = frameNode->GetLayoutProperty<NG::LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (AceType::InstanceOf<NG::ButtonLayoutProperty>(layoutProperty)) {
        auto buttonLayoutProperty = AceType::DynamicCast<NG::ButtonLayoutProperty>(layoutProperty);
        if (buttonLayoutProperty) {
            text = buttonLayoutProperty->GetLabelValue();
            return true;
        }
    } else if (AceType::InstanceOf<NG::TextLayoutProperty>(layoutProperty)) {
        auto textLayoutProperty = AceType::DynamicCast<NG::TextLayoutProperty>(layoutProperty);
        if (textLayoutProperty) {
            text = textLayoutProperty->GetContent().value();
            return true;
        }
    }
    return false;
}
std::string ComponentTestComponentImpl::GetTextImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = GetFrameNode();
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_NOT_SUPPORTED);
        return "";
    }
    std::string buff;
    if (OHOS::Ace::ComponentTest::GetTextByPattern(frameNode, buff)) {
        return buff;
    } else if (OHOS::Ace::ComponentTest::GetTextByEventHub(frameNode, buff)) {
        return buff;
    } else if (OHOS::Ace::ComponentTest::GetTextByAccessibilityProperty(frameNode, buff)) {
        return buff;
    } else if (OHOS::Ace::ComponentTest::GetTextByLayoutProperty(frameNode, buff)) {
        return buff;
    } else {
        return "";
    }
}

std::string ComponentTestComponentImpl::GetTypeImpl(ErrInfo& errInfo) const
{
    if (uiNode_) {
        const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
        if (frameNode) {
            return frameNode->GetTag();
        }
    }
    errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    return "";
}

bool ComponentTestComponentImpl::IsClickableImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = GetFrameNode();
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    return gesture && gesture->IsClickable();
}

bool ComponentTestComponentImpl::IsLongPressableImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = GetFrameNode();
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    return gesture && gesture->GetLongPressRecognizer();
}

bool IsScrollableByPattern(const RefPtr<NG::FrameNode>& frameNode)
{
    const RefPtr<NG::Pattern>& pattern = frameNode->GetPattern();
    if (AceType::InstanceOf<OHOS::Ace::NG::ScrollablePattern>(pattern)) {
        auto scrollablePattern = AceType::DynamicCast<OHOS::Ace::NG::ScrollablePattern>(pattern);
        return scrollablePattern->IsScrollable();
    } else if (AceType::InstanceOf<OHOS::Ace::NG::ScrollBarPattern>(pattern)) {
        auto scrollBarPattern = frameNode->GetPattern<OHOS::Ace::NG::ScrollBarPattern>();
        CHECK_NULL_RETURN(scrollBarPattern, false);
        if (scrollBarPattern->GetAxis() != Axis::NONE && Positive(scrollBarPattern->GetControlDistance())) {
            return true;
        }
        return false;
    } else if (AceType::InstanceOf<OHOS::Ace::NG::RefreshPattern>(pattern)) {
        auto refreshPattern = frameNode->GetPattern<OHOS::Ace::NG::RefreshPattern>();
        CHECK_NULL_RETURN(refreshPattern, false);
        return !refreshPattern->IsRefreshing();
    } else if (AceType::InstanceOf<OHOS::Ace::NG::MenuPattern>(pattern)) {
        auto firstChild = AceType::DynamicCast<NG::FrameNode>(frameNode->GetChildAtIndex(0));
        if (firstChild && firstChild->GetTag() == V2::SCROLL_ETS_TAG) {
            auto scrollPattern = firstChild->GetPattern<OHOS::Ace::NG::ScrollPattern>();
            CHECK_NULL_RETURN(scrollPattern, false);
            if (scrollPattern->IsScrollable() && !NearZero(scrollPattern->GetScrollableDistance())) {
                return true;
            }
        }
    }
    return false;
}

bool ComponentTestComponentImpl::IsScrollableImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode> frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    const RefPtr<NG::Pattern>& pattern = frameNode->GetPattern();
    if (!pattern) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    OHOS::Ace::CombinationIsScrollable combinationIsscrollable(frameNode);
    if (combinationIsscrollable.IsComponentExist()) {
        return combinationIsscrollable.IsComponentScrollable();
    }
    if (IsScrollableByPattern(frameNode)) {
        return true;
    }
    if (AceType::InstanceOf<OHOS::Ace::NG::DatePickerPattern>(pattern)) {
        auto datePickerPattern = AceType::DynamicCast<OHOS::Ace::NG::DatePickerPattern>(pattern);
        CHECK_NULL_RETURN(datePickerPattern, false);
        auto options = datePickerPattern->GetOptions();
        auto it = options.find(frameNode);
        uint32_t ret = 0;
        if (it != options.end()) {
            ret = it->second.size();
        }
        return ret > 1;
    } else if (AceType::InstanceOf<OHOS::Ace::NG::TimePickerColumnPattern>(pattern)) {
        auto timePickerPattern = AceType::DynamicCast<OHOS::Ace::NG::TimePickerColumnPattern>(pattern);
        CHECK_NULL_RETURN(timePickerPattern, 0);
        auto options = timePickerPattern->GetOptions();
        CHECK_NULL_RETURN(options.find(frameNode) != options.end(), false);
        return (options[frameNode] > 1) ? true : false;
    } else if (AceType::InstanceOf<OHOS::Ace::NG::SliderPattern>(pattern)) {
        const RefPtr<NG::SliderAccessibilityProperty>& sliderAccessibilityProperty =
            frameNode->GetAccessibilityProperty<NG::SliderAccessibilityProperty>();
        return sliderAccessibilityProperty->IsScrollable();
    } else {
        return false;
    }
}

bool ComponentTestComponentImpl::IsEnabledImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = GetFrameNode();
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    return eventHub && eventHub->IsEnabled();
}

bool ComponentTestComponentImpl::IsFocusedImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    auto focusHub = frameNode->GetFocusHub();
    if (!focusHub) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    return focusHub->IsDefaultFocus() && focusHub->IsFocusable();
}

bool ComponentTestComponentImpl::IsSelectedImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    const RefPtr<NG::Pattern>& pattern = frameNode->GetPattern();
    if (!pattern) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    if (AceType::InstanceOf<NG::ListItemPattern>(pattern)) {
        auto listItemPattern = AceType::DynamicCast<NG::ListItemPattern>(pattern);
        if (listItemPattern) {
            return listItemPattern->IsSelected();
        }
    } else if (AceType::InstanceOf<NG::GridItemPattern>(pattern)) {
        auto gridItemPattern = AceType::DynamicCast<NG::GridItemPattern>(pattern);
        if (gridItemPattern) {
            return gridItemPattern->IsSelected();
        }
    } else if (AceType::InstanceOf<NG::TextBase>(pattern)) {
        auto textBase = AceType::DynamicCast<NG::TextBase>(pattern);
        if (textBase) {
            return textBase->IsSelected();
        }
    } else if (AceType::InstanceOf<NG::MenuItemPattern>(pattern)) {
        auto menuItemPattern = AceType::DynamicCast<NG::MenuItemPattern>(pattern);
        if (menuItemPattern) {
            return menuItemPattern->IsSelected();
        }
    }
    return false;
}

bool ComponentTestComponentImpl::IsCheckedImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    const RefPtr<NG::AccessibilityProperty>& accessibilityProperty =
        frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    if (accessibilityProperty) {
        return accessibilityProperty->IsChecked();
    } else {
        return false;
    }
}

bool ComponentTestComponentImpl::IsCheckableImpl(ErrInfo& errInfo) const
{
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (!frameNode) {
        errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
        return false;
    }
    const RefPtr<NG::AccessibilityProperty>& accessibilityProperty =
        frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    if (accessibilityProperty) {
        return accessibilityProperty->IsCheckable();
    } else {
        return false;
    }
}

std::string ComponentTestComponentImpl::GetInspectorInfoImpl(ErrInfo& errInfo) const
{
    CHECK_NULL_RETURN(uiNode_, "");
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, uiNode_->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, uiNode_->GetInspectorId().value_or("").c_str());
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (frameNode) {
        auto rect = frameNode->GetTransformRectRelativeToWindow();
        jsonNode->Put(INSPECTOR_RECT, rect.ToBounds().c_str());
    }
    auto jsonAttrs = JsonUtil::Create(true);
    std::string debugLine = uiNode_->GetDebugLine();
    jsonNode->Put(INSPECTOR_DEBUGLINE, debugLine.c_str());
    NG::InspectorFilter filter;
    uiNode_->ToJsonValue(jsonAttrs, filter);
    jsonNode->Put(INSPECTOR_ATTRS, jsonAttrs);
    return jsonNode->ToString();
}

std::string ComponentTestComponentImpl::GetInspectorTreeImpl(ErrInfo& errInfo) const
{
    if (uiNode_) {
        auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
        auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
        auto jsonNode = JsonUtil::Create(true);
        GetContextInfo(context, jsonNode);
        std::vector<RefPtr<NG::UINode>> children;
        for (const auto& item : uiNode_->GetChildren()) {
            GetFrameNodeChildren(item, children, uiNode_->GetPageId());
        }
        return GetChildrenInspectorInfo(children, uiNode_->GetPageId(), std::move(jsonNode));
    }
    errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    return "";
}

int32_t ComponentTestComponentImpl::GetChildCountImpl(ErrInfo& errInfo) const
{
    return uiNode_->TotalChildCount();
}

NG::RectF ComponentTestComponentImpl::GetBoundsImpl(ErrInfo& errInfo) const
{
    if (uiNode_) {
        const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
        if (frameNode) {
            return frameNode->GetTransformRectRelativeToWindow();
        }
    }
    errInfo = QueryRetMsg(ErrCode::RET_ERR_COMPONENT_INVISIBLE_OR_DESTROYED);
    return NG::RectF { 0, 0, 0, 0 };
}

void ComponentTestComponentImpl::SetUiNode(const RefPtr<NG::UINode> uiNode)
{
    uiNode_ = uiNode;
}

void ComponentTestComponentImpl::SetEffective()
{
    auto container = AceEngine::Get().GetContainer(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(context);
    auto scale = context->GetViewScale();
    NG::RectF screenRect(0, 0, context->GetRootWidth() * scale, context->GetRootHeight() * scale);
    CHECK_NULL_VOID(uiNode_);
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    if (frameNode) {
        NG::RectF rect = frameNode->GetTransformRectRelativeToWindow();
        effective_ = screenRect.IntersectRectT(rect);
    } else {
        effective_ = NG::RectF();
    }
}

void ComponentTestComponentImpl::GetContextInfo(
    const RefPtr<NG::PipelineContext>& context, std::unique_ptr<JsonValue>& jsonRoot) const
{
    auto scale = context->GetViewScale();
    auto rootHeight = context->GetRootHeight();
    auto rootWidth = context->GetRootWidth();
    deviceRect.SetRect(0, 0, rootWidth * scale, rootHeight * scale);
    jsonRoot->Put(INSPECTOR_WIDTH, std::to_string(rootWidth * scale).c_str());
    jsonRoot->Put(INSPECTOR_HEIGHT, std::to_string(rootHeight * scale).c_str());
    jsonRoot->Put(INSPECTOR_RESOLUTION, std::to_string(PipelineBase::GetCurrentDensity()).c_str());
}

void ComponentTestComponentImpl::GetFrameNodeChildren(
    const RefPtr<NG::UINode>& uiNode, std::vector<RefPtr<NG::UINode>>& children, int32_t pageId) const
{
    if (AceType::InstanceOf<NG::FrameNode>(uiNode) || AceType::InstanceOf<NG::SpanNode>(uiNode)) {
        if (uiNode->GetTag() == "stage") {
        } else if (uiNode->GetTag() == "page") {
            if (uiNode->GetPageId() != pageId) {
                return;
            }
        } else {
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
            auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
            if ((frameNode && !frameNode->IsInternal()) || spanNode) {
                children.emplace_back(uiNode);
                return;
            }
        }
    }
    for (const auto& frameChild : uiNode->GetChildren()) {
        GetFrameNodeChildren(frameChild, children, pageId);
    }
}

std::string ComponentTestComponentImpl::GetChildrenInspectorInfo(
    std::vector<RefPtr<NG::UINode>> children, int32_t pageId, std::unique_ptr<JsonValue> jsonNode) const
{
    auto jsonNodeArray = JsonUtil::CreateArray(true);
    for (auto& uiNode : children) {
        GetInspectorChildren(uiNode, jsonNodeArray, pageId);
    }
    if (jsonNodeArray->GetArraySize()) {
        jsonNode->PutRef(INSPECTOR_CHILDREN, std::move(jsonNodeArray));
    }

    return jsonNode->ToString();
}

std::string NodeRectToString(RefPtr<NG::FrameNode> node)
{
    NG::RectF rect;
    bool isActive = node->IsActive();
    if (isActive) {
        rect = node->GetTransformRectRelativeToWindow();
    }
    rect = rect.Constrain(deviceRect);
    if (rect.IsEmpty()) {
        rect.SetRect(0, 0, 0, 0);
    }
    return std::to_string(rect.Left())
        .append(",")
        .append(std::to_string(rect.Top()))
        .append(",")
        .append(std::to_string(rect.Width()))
        .append(",")
        .append(std::to_string(rect.Height()));
}

void ComponentTestComponentImpl::GetInspectorChildren(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<JsonValue>& jsonNodeArray, int pageId) const
{
    // Span is a special case in Inspector since span inherits from UINode
    if (AceType::InstanceOf<NG::SpanNode>(parent)) {
        GetSpanInspector(parent, jsonNodeArray, pageId);
        return;
    }
    auto jsonNode = JsonUtil::Create(true);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetInspectorId().value_or("").c_str());
    if (parent->GetTag() == "__Common__") {
        jsonNode->Put(INSPECTOR_COMPONENT_TYPE, "custom");
    } else {
        jsonNode->Put(INSPECTOR_COMPONENT_TYPE, "build-in");
    }
    auto node = AceType::DynamicCast<NG::FrameNode>(parent);
    if (node) {
        std::string strRec = NodeRectToString(node);
        jsonNode->Put(INSPECTOR_RECT, strRec.c_str());
        jsonNode->Put(INSPECTOR_DEBUGLINE, node->GetDebugLine().c_str());
        jsonNode->Put(INSPECTOR_VIEW_ID, node->GetViewId().c_str());
        auto jsonObject = JsonUtil::Create(true);
        parent->ToJsonValue(jsonObject, NG::InspectorFilter());
        jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    }

    std::vector<RefPtr<NG::UINode>> children;
    for (const auto& item : parent->GetChildren()) {
        GetFrameNodeChildren(item, children, pageId);
    }
    if (node != nullptr) {
        auto overlayNode = node->GetOverlayNode();
        if (overlayNode != nullptr) {
            GetFrameNodeChildren(overlayNode, children, pageId);
        }
    }
    auto jsonChildrenArray = JsonUtil::CreateArray(true);
    for (auto uiNode : children) {
        GetInspectorChildren(uiNode, jsonChildrenArray, pageId);
    }
    if (jsonChildrenArray->GetArraySize()) {
        jsonNode->Put(INSPECTOR_CHILDREN, jsonChildrenArray);
    }
    jsonNodeArray->PutRef(std::move(jsonNode));
}

void ComponentTestComponentImpl::GetSpanInspector(
    const RefPtr<NG::UINode>& parent, std::unique_ptr<JsonValue>& jsonNodeArray, int pageId) const
{
    // span rect follows parent text size
    auto spanParentNode = parent->GetParent();
    while (spanParentNode != nullptr) {
        if (AceType::InstanceOf<NG::FrameNode>(spanParentNode)) {
            break;
        }
        spanParentNode = spanParentNode->GetParent();
    }
    CHECK_NULL_VOID(spanParentNode);
    auto node = AceType::DynamicCast<NG::FrameNode>(spanParentNode);
    auto jsonNode = JsonUtil::Create(true);
    auto jsonObject = JsonUtil::Create(true);
    NG::InspectorFilter filter;
    parent->ToJsonValue(jsonObject, filter);
    jsonNode->Put(INSPECTOR_ATTRS, jsonObject);
    jsonNode->Put(INSPECTOR_TYPE, parent->GetTag().c_str());
    jsonNode->Put(INSPECTOR_ID, parent->GetInspectorId().value_or("").c_str());
    std::string strRec = NodeRectToString(node);
    jsonNode->Put(INSPECTOR_RECT, strRec.c_str());
    jsonNode->Put(INSPECTOR_DEBUGLINE, parent->GetDebugLine().c_str());
    jsonNode->Put(INSPECTOR_VIEW_ID, parent->GetViewId().c_str());
    jsonNodeArray->PutRef(std::move(jsonNode));
}

bool ComponentTestComponentImpl::GenericClick(const TouchType touchType, uint32_t duration) const
{
    CHECK_NULL_RETURN(uiNode_, false);
    NG::OffsetF center = effective_.Center();
    NG::PointF point(center.GetX(), center.GetY());
    ClickAction clickAction(point, touchType, duration);
    EventSequenceManager::GetInstance().Execute(&clickAction);
    return true;
}

RefPtr<NG::FrameNode> ComponentTestComponentImpl::GetFrameNode() const
{
    CHECK_NULL_RETURN(uiNode_, nullptr);
    const RefPtr<NG::FrameNode>& frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode_);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

} // namespace OHOS::Ace::ComponentTest
