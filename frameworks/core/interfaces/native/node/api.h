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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_API_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_API_H

#include <cstdint>
#include "interfaces/inner_api/ace/macros.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/progress/progress_date.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/event/mouse_event.h"
#include "core/components/common/properties/decoration.h"
#include "core/interfaces/native/node/node_api.h"

struct ArkUINodeAPI {
    ArkUINodeHandle (*GetFrameNodeById)(int nodeId);
    int64_t (*GetUIState)(ArkUINodeHandle node);
    void (*SetSupportedUIState)(ArkUINodeHandle node, uint64_t state);
    ArkUICommonModifier (*GetCommonModifier)();
    ArkUICheckboxGroupModifier (*GetCheckboxGroupModifier)();
    ArkUICounterModifier (*GetCounterModifier)();
    ArkUIRowModifier (*GetRowModifier)();
    ArkUIRowSplitModifier (*GetRowSplitModifier)();
    ArkUITextModifier (*GetTextModifier)();
    ArkUIButtonModifier (*GetButtonModifier)();
    ArkUIToggleModifier (*GetToggleModifier)();
    ArkUIImageSpanModifier (*GetImageSpanModifier)();
    ArkUIBlankModifier (*GetBlankModifier)();
    ArkUISearchModifier (*GetSearchModifier)();
    ArkUISelectModifier (*GetSelectModifier)();
    ArkUIRadioModifier (*GetRadioModifier)();
    ArkUICheckboxModifier (*GetCheckboxModifier)();
    ArkUITimepickerModifier (*GetTimepickerModifier)();
    ArkUITextPickerModifier (*GetTextpickerModifier)();
    ArkUIRatingModifier (*GetRatingModifier)();
    ArkUISliderModifier (*GetSliderModifier)();
    ArkUIDividerModifier (*GetDividerModifier)();
    ArkUIStackModifier (*GetStackModifier)();
    ArkUINavDestinationModifier (*GetNavDestinationModifier)();
    ArkUIGridModifier (*GetGridModifier)();
    ArkUIGridColModifier (*GetGridColModifier)();
    ArkUIGridRowModifier (*GetGridRowModifier)();
    ArkUIPanelModifier (*GetPanelModifier)();
    ArkUITextAreaModifier (*GetTextAreaModifier)();
    ArkUINavigationModifier (*GetNavigationModifier)();
    ArkUIColumnModifier (*GetColumnModifier)();
    ArkUIRichEditorModifier (*GetRichEditorModifier)();
    ArkUIImageModifier (*GetImageModifier)();
    ArkUIVideoModifier (*GetVideoModifier)();
    ArkUINavigatorModifier (*GetNavigatorModifier)();
    ArkUINavRouterModifier (*GetNavRouterModifier)();
    ArkUINodeContainerModifier (*GetNodeContainerModifier)();
    ArkUIPatternLockModifier (*GetPatternLockModifier)();
    ArkUIColumnSplitModifier (*GetColumnSplitModifier)();
    ArkUILineModifier (*GetLineModifier)();
    ArkUIPathModifier (*GetPathModifier)();
    ArkUIPolygonModifier (*GetPolygonModifier)();
    ArkUIPolylineModifier (*GetPolylineModifier)();
    ArkUISpanModifier (*GetSpanModifier)();frameworks/core/interfaces/native/node/node_api.h
    ArkUIImageAnimatorModifier (*GetImageAnimatorModifier)();
    ArkUISideBarContainerModifier (*GetSideBarContainerModifier)();
    ArkUICalendarPickerModifier (*GetCalendarPickerModifier)();
    ArkUITextInputModifier (*GetTextInputModifier)();
    ArkUITabsModifier (*GetTabsModifier)();
    ArkUIStepperItemModifier (*GetStepperItemModifier)();
    ArkUIHyperlinkModifier (*GetHyperlinkModifier)();
    ArkUIMarqueeModifier (*GetMarqueeModifier)();
    ArkUIMenuItemModifier (*GetMenuItemModifier)();
    ArkUIMenuModifier (*GetMenuModifier)();
    ArkUIDatePickerModifier (*GetDatePickerModifier)();
    ArkUIWaterFlowModifier (*GetWaterFlowModifier)();
    ArkUIAlphabetIndexerModifier (*GetAlphabetIndexerModifier)();
    ArkUIDataPanelModifier (*GetDataPanelModifier)();
    ArkUIGaugeModifier (*GetGaugeModifier)();
    ArkUIScrollModifier (*GetScrollModifier)();
    ArkUIGridItemModifier (*GetGridItemModifier)();
    ArkUIProgressModifier (*GetProgressModifier)();
    ArkUICommonShapeModifier(*GetCommonShapeModifier)();
    ArkUIShapeModifier(*GetShapeModifier)();
    ArkUIRectModifier (*GetRectModifier)();
    ArkUISwiperModifier (*GetSwiperModifier)();
    ArkUIListItemModifier (*GetListItemModifier)();
    ArkUIListModifier (*GetListModifier)();
    ArkUIListItemGroupModifier(*GetListItemGroupModifier)();
    ArkUIQRCodeModifier (*GetQRCodeModifier)();
    ArkUILoadingProgressModifier (*GetLoadingProgressModifier)();
    ArkUITextClockModifier (*GetTextClockModifier)();
    ArkUITextTimerModifier (*GetTextTimerModifier)();
    ArkUIRenderNodeModifier (*GetRenderNodeModifier)();

#ifdef PLUGIN_COMPONENT_SUPPORTED
    ArkUIPluginModifier (*GetPluginModifier)();
#endif
#ifdef XCOMPONENT_SUPPORTED
    ArkUIXComponentModifier (*GetXComponentModifier)();
#endif
#ifdef FORM_SUPPORTED
    ArkUIFormComponentModifier (*GetFormComponentModifier)();
#endif
};
ArkUINodeAPI* GetArkUIInternalNodeAPI();
#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_API_H