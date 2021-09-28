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

#include "core/components_v2/inspector/inspector_composed_component.h"

#include <unordered_map>

#include "base/utils/string_utils.h"
#include "core/common/container.h"
#include "core/components_v2/inspector/badge_composed_element.h"
#include "core/components_v2/inspector/blank_composed_element.h"
#include "core/components_v2/inspector/button_composed_element.h"
#include "core/components_v2/inspector/calendar_composed_element.h"
#include "core/components_v2/inspector/checkbox_composed_element.h"
#include "core/components_v2/inspector/column_composed_element.h"
#include "core/components_v2/inspector/column_split_composed_element.h"
#include "core/components_v2/inspector/divider_composed_element.h"
#include "core/components_v2/inspector/flex_composed_element.h"
#include "core/components_v2/inspector/grid_composed_element.h"
#include "core/components_v2/inspector/grid_item_composed_element.h"
#include "core/components_v2/inspector/image_animator_composed_element.h"
#include "core/components_v2/inspector/image_composed_element.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/list_composed_element.h"
#include "core/components_v2/inspector/list_item_composed_element.h"
#include "core/components_v2/inspector/navigator_composed_element.h"
#include "core/components_v2/inspector/panel_composed_element.h"
#include "core/components_v2/inspector/qrcode_composed_element.h"
#include "core/components_v2/inspector/row_composed_element.h"
#include "core/components_v2/inspector/row_split_composed_element.h"
#include "core/components_v2/inspector/scroll_composed_element.h"
#include "core/components_v2/inspector/shape_composed_element.h"
#include "core/components_v2/inspector/shape_container_composed_element.h"
#include "core/components_v2/inspector/span_composed_element.h"
#include "core/components_v2/inspector/stack_composed_element.h"
#include "core/components_v2/inspector/swiper_composed_element.h"
#include "core/components_v2/inspector/switch_composed_element.h"
#include "core/components_v2/inspector/tab_content_composed_element.h"
#include "core/components_v2/inspector/tabs_composed_element.h"
#include "core/components_v2/inspector/text_composed_element.h"
#include "core/components_v2/inspector/toggle_composed_element.h"
#include "core/components_v2/inspector/wrap_composed_element.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace::V2 {

namespace {

const std::unordered_map<std::string, CreateElementFunc> CREATE_ELEMENT_MAP {
    { COLUMN_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ColumnComposedElement>(id); } },
    { COLUMN_SPLIT_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ColumnSplitComposedElement>(id); } },
    { COUNTER_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { NAVIGATION_VIEW_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::InspectorComposedElement>(id); } },
    { ROW_SPLIT_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::RowSplitComposedElement>(id); } },
    { STACK_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::StackComposedElement>(id); } },
    { SWIPER_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::SwiperComposedElement>(id); } },
    { TAB_CONTENT_ITEM_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::TabContentComposedElement>(id); } },
    { TABS_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::TabsComposedElement>(id); } },
    { TEXT_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::TextComposedElement>(id); } },
    { COLUMN_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ColumnComposedElement>(id); } },
    { FLEX_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::FlexComposedElement>(id); } },
    { WRAP_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::WrapComposedElement>(id); } },
    { GRID_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::GridComposedElement>(id); } },
    { GRID_ITEM_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::GridItemComposedElement>(id); } },
    { LIST_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ListComposedElement>(id); } },
    { LIST_ITEM_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ListItemComposedElement>(id); } },
    { NAVIGATOR_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::NavigatorComposedElement>(id); } },
    { PANEL_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::PanelComposedElement>(id); } },
    { ROW_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::RowComposedElement>(id); } },
    { SHAPE_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ShapeComposedElement>(id); } },
    { SHAPE_CONTAINER_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ShapeContainerComposedElement>(id); } },
    { IMAGE_ANIMATOR_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ImageAnimatorComposedElement>(id); } },
    { IMAGE_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::ImageComposedElement>(id); } },
    { QRCODE_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::QrcodeComposedElement>(id); } },
    { SPAN_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::SpanComposedElement>(id); } },
    { BOX_COMPONENT_TAG,
        [](const std::string& id) { return AceType::MakeRefPtr<V2::BlankComposedElement>(id); } },
    { BUTTON_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::ButtonComposedElement>(id); } },
    { DIVIDER_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::DividerComposedElement>(id); } },
    { CHECKBOX_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::CheckboxComposedElement>(id); } },
    { SWITCH_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::SwitchComposedElement>(id); } },
    { TOGGLE_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::ToggleComposedElement>(id); } },
    { SCROLL_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::ScrollComposedElement>(id); } },
    { CALENDAR_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::CalendarComposedElement>(id); } },
    { BADGE_COMPONENT_TAG,
        [](const std::string& id) {return AceType::MakeRefPtr<V2::BadgeComposedElement>(id); } }
};

const static std::unordered_map<std::string, std::string> COMPONENT_TAG_TO_ETS_TAG_MAP {
    { COLUMN_COMPONENT_TAG, COLUMN_ETS_TAG },
    { TEXT_COMPONENT_TAG, TEXT_ETS_TAG },
    { COLUMN_SPLIT_COMPONENT_TAG, COLUMN_SPLIT_ETS_TAG },
    { COUNTER_COMPONENT_TAG, COUNTER_ETS_TAG },
    { NAVIGATION_VIEW_COMPONENT_TAG, NAVIGATION_VIEW_ETS_TAG },
    { ROW_SPLIT_COMPONENT_TAG, ROW_SPLIT_ETS_TAG },
    { STACK_COMPONENT_TAG, STACK_ETS_TAG },
    { SWIPER_COMPONENT_TAG, SWIPER_ETS_TAG },
    { TAB_CONTENT_ITEM_COMPONENT_TAG, TAB_CONTENT_ITEM_ETS_TAG },
    { TABS_COMPONENT_TAG, TABS_ETS_TAG },
    { FLEX_COMPONENT_TAG, FLEX_ETS_TAG },
    { WRAP_COMPONENT_TAG, WRAP_ETS_TAG },
    { GRID_COMPONENT_TAG, GRID_ETS_TAG },
    { GRID_ITEM_COMPONENT_TAG, GRID_ITEM_ETS_TAG },
    { LIST_COMPONENT_TAG, LIST_ETS_TAG },
    { LIST_ITEM_COMPONENT_TAG, LIST_ITEM_ETS_TAG },
    { NAVIGATOR_COMPONENT_TAG, NAVIGATOR_ETS_TAG },
    { PANEL_COMPONENT_TAG, PANEL_ETS_TAG },
    { ROW_COMPONENT_TAG, ROW_ETS_TAG },
    { IMAGE_ANIMATOR_COMPONENT_TAG, IMAGE_ANIMATOR_ETS_TAG },
    { SHAPE_CONTAINER_COMPONENT_TAG, SHAPE_CONTAINER_ETS_TAG },
    { SHAPE_COMPONENT_TAG, SHAPE_ETS_TAG },
    { IMAGE_COMPONENT_TAG, IMAGE_ETS_TAG },
    { QRCODE_COMPONENT_TAG, QRCODE_ETS_TAG },
    { SPAN_COMPONENT_TAG, SPAN_ETS_TAG },
    { BOX_COMPONENT_TAG, BLANK_ETS_TAG },
    { BUTTON_COMPONENT_TAG, BUTTON_ETS_TAG },
    { DIVIDER_COMPONENT_TAG, DIVIDER_ETS_TAG },
    { CHECKBOX_COMPONENT_TAG, CHECKBOX_ETS_TAG },
    { SWITCH_COMPONENT_TAG, SWITCH_ETS_TAG },
    { TOGGLE_COMPONENT_TAG, TOGGLE_ETS_TAG },
    { SCROLL_COMPONENT_TAG, SCROLL_ETS_TAG },
    { CALENDAR_COMPONENT_TAG, CALENDAR_ETS_TAG },
    { BADGE_COMPONENT_TAG, BADGE_ETS_TAG }
};

} // namespace

RefPtr<Element> InspectorComposedComponent::CreateElement()
{
    auto generateFunc = CREATE_ELEMENT_MAP.find(GetName());
    if (generateFunc != CREATE_ELEMENT_MAP.end()) {
        auto composedElement = generateFunc->second(GetId());
        AddElementToAccessibilityManager(composedElement);
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
        composedElement->SetDebugLine(GetDebugLine());
#endif
        return composedElement;
    }
    return nullptr;
}

RefPtr<AccessibilityManager> InspectorComposedComponent::GetAccessibilityManager()
{
    auto container = OHOS::Ace::Container::Current();
    if (!container) {
        LOGE("container is nullptr");
        return nullptr;
    }
    auto front = container->GetFrontend();
    if (!front) {
        LOGE("front is nullptr");
        return nullptr;
    }
    auto accessibilityManager = front->GetAccessibilityManager();
    return accessibilityManager;
}

bool InspectorComposedComponent::HasInspectorFinished(std::string tag)
{
    auto generateFunc = COMPONENT_TAG_TO_ETS_TAG_MAP.find(tag);
    if (generateFunc != COMPONENT_TAG_TO_ETS_TAG_MAP.end()) {
        return true;
    }
    return false;
}

RefPtr<AccessibilityNode> InspectorComposedComponent::CreateAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    auto iter = COMPONENT_TAG_TO_ETS_TAG_MAP.find(tag);
    if (iter == COMPONENT_TAG_TO_ETS_TAG_MAP.end()) {
        LOGD("can't find %{public}s component", tag.c_str());
        return nullptr;
    }
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("get AccessibilityManager failed");
        return nullptr;
    }
    auto node = accessibilityManager->CreateAccessibilityNode(iter->second, nodeId, parentNodeId, itemIndex);
    return node;
}

void InspectorComposedComponent::AddElementToAccessibilityManager(const RefPtr<ComposedElement>& composedElement)
{
    if (!composedElement) {
        LOGE("composedElement is null");
        return;
    }
    auto accessibilityManager = GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("get AccessibilityManager failed");
        return;
    }
    accessibilityManager->AddComposedElement(composedElement->GetId(), composedElement);
}

} // namespace OHOS::Ace::V2
