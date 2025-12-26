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

#include <cstring>

#include "core/interfaces/native/node/node_api.h"

constexpr int32_t MODIFIER_COUNTS = 9;
constexpr int32_t MODIFIER_COUNTS_CJ = 8;
constexpr int32_t BLANK_LINES = 6;
// Mock implementation for unit tests
extern "C" {
ACE_FORCE_EXPORT const ArkUINodeModifiers* GetArkUINodeModifiers()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static ArkUINodeModifiers impl = {
        .version = ARKUI_NODE_MODIFIERS_API_VERSION,
        .getCommonModifier = nullptr,
        .getCheckboxGroupModifier = nullptr,
        .getCounterModifier = nullptr,
        .getRowModifier = nullptr,
        .getRowSplitModifier = nullptr,
        .getTextModifier = nullptr,
        .getButtonModifier = nullptr,
        .getToggleModifier = nullptr,
        .getImageSpanModifier = nullptr,
        .getBlankModifier = nullptr,
        .getSearchModifier = nullptr,
        .getSelectModifier = nullptr,
        .getRadioModifier = nullptr,
        .getCheckboxModifier = nullptr,
        .getTimepickerModifier = nullptr,
        .getTextPickerModifier = nullptr,
        .getRatingModifier = nullptr,
        .getSliderModifier = nullptr,
        .getDividerModifier = nullptr,
        .getStackModifier = nullptr,
#ifndef ARKUI_WEARABLE
        .getFolderStackModifier = nullptr,
#else
        .getFolderStackModifier = nullptr,
#endif
        .getNavDestinationModifier = nullptr,
        .getGridModifier = nullptr,
        .getGridColModifier = nullptr,
        .getGridRowModifier = nullptr,
        .getPanelModifier = nullptr,
        .getTextAreaModifier = nullptr,
        .getNavigationModifier = nullptr,
        .getColumnModifier = nullptr,
        .getRichEditorModifier = nullptr,
        .getImageModifier = nullptr,
        .getVideoModifier = nullptr,
        .getVideoControllerModifier = nullptr,
        .getNavigatorModifier = nullptr,
        .getNavRouterModifier = nullptr,
        .getNodeContainerModifier = nullptr,
        .getPatternLockModifier = nullptr,
        .getColumnSplitModifier = nullptr,
        .getLineModifier = nullptr,
        .getPathModifier = nullptr,
        .getPolygonModifier = nullptr,
        .getPolylineModifier = nullptr,
        .getSpanModifier = nullptr,
        .getImageAnimatorModifier = nullptr,
        .getSideBarContainerModifier = nullptr,
#ifndef ARKUI_WEARABLE
        .getCalendarPickerModifier = nullptr,
#else
        .getCalendarPickerModifier = nullptr,
#endif
        .getTextInputModifier = nullptr,
        .getTabsModifier = nullptr,
        .getStepperItemModifier = nullptr,
        .getHyperlinkModifier = nullptr,
        .getMarqueeModifier = nullptr,
        .getMenuItemModifier = nullptr,
        .getMenuModifier = nullptr,
        .getDatePickerModifier = nullptr,
        .getWaterFlowModifier = nullptr,
        .getAlphabetIndexerModifier = nullptr,
        .getDataPanelModifier = nullptr,
        .getGaugeModifier = nullptr,
        .getScrollModifier = nullptr,
        .getScrollableModifier = nullptr,
        .getGridItemModifier = nullptr,
        .getProgressModifier = nullptr,
        .getCommonShapeModifier = nullptr,
        .getShapeModifier = nullptr,
        .getRectModifier = nullptr,
        .getSwiperModifier = nullptr,
        .getListItemModifier = nullptr,
        .getListModifier = nullptr,
        .getListItemGroupModifier = nullptr,
#ifdef QRCODEGEN_SUPPORT
        .getQRCodeModifier = nullptr,
#else
        .getQRCodeModifier = nullptr,
#endif
        .getLoadingProgressModifier = nullptr,
        .getTextClockModifier = nullptr,
        .getTextTimerModifier = nullptr,
        .getRenderNodeModifier = nullptr,
        .getFrameNodeModifier = nullptr,
#ifdef PLUGIN_COMPONENT_SUPPORTED
        .getPluginModifier = nullptr,
#else
        .getPluginModifier = nullptr,
#endif
#ifdef XCOMPONENT_SUPPORTED
        .getXComponentModifier = nullptr,
#else
        .getXComponentModifier = nullptr,
#endif
        .getUIStateModifier = nullptr,
        .getFormComponentModifier = nullptr,
        .getFlexModifier = nullptr,
        .getScrollBarModifier = nullptr,
        .getScrollerModifier = nullptr,
        .getTabContentModifier = nullptr,
        .getTabsControllerModifier = nullptr,
        .getSwiperControllerModifier = nullptr,
        .getGestureModifier = nullptr,
        .getBadgeModifier = nullptr,
#ifdef WEB_SUPPORTED
        .getWebModifier = nullptr,
#else
        .getWebModifier = nullptr, // WebModifier
#endif
        .getRefreshModifier = nullptr,
        .getMenuItemGroupModifier = nullptr,
        .getSearchControllerModifier = nullptr,
        .getSideBarModifier = nullptr,
        .getPatternLockControllerModifier = nullptr,
        .getTextTimerControllerModifier = nullptr,
        .getTextClockControllerModifier = nullptr,
        .getRichEditorControllerModifier = nullptr,
        .getTextAreaControllerModifier = nullptr,
        .getRelativeContainerModifier = nullptr,
        .getParticleModifier = nullptr,
        .getNodeContentModifier = nullptr,
        .getSymbolGlyphModifier = nullptr,
        .getSymbolSpanModifier = nullptr,
        .getComponent3DModifier = nullptr,
        .getContainerSpanModifier = nullptr,
        .getCustomNodeExtModifier = nullptr,
        .getThemeModifier = nullptr,
        .getLinearIndicatorModifier = nullptr,
        .getIndicatorComponentModifier = nullptr,
        .getLazyGridLayoutModifier = nullptr,
        .getEmbeddedComponentModifier = nullptr,
        .getCanvasModifier = nullptr,
        .getStepperModifier = nullptr,
        .getNDKRenderNodeModifier = nullptr,
        .getContainerPickerModifier = nullptr,
        .getAtomicServiceModifier = nullptr,
    };
    return &impl;
}

const CJUINodeModifiers* GetCJUINodeModifiers()
{
    static CJUINodeModifiers modifiers {
        .version = ARKUI_NODE_MODIFIERS_API_VERSION,
        .getCommonModifier = nullptr,
        .getCheckboxGroupModifier = nullptr,
        .getCounterModifier = nullptr,
        .getRowModifier = nullptr,
        .getRowSplitModifier = nullptr,
        .getTextModifier = nullptr,
        .getButtonModifier = nullptr,
        .getToggleModifier = nullptr,
        .getImageSpanModifier = nullptr,
        .getBlankModifier = nullptr,
        .getSearchModifier = nullptr,
        .getSelectModifier = nullptr,
        .getRadioModifier = nullptr,
        .getCheckboxModifier = nullptr,
        .getTimepickerModifier = nullptr,
        .getTextPickerModifier = nullptr,
        .getRatingModifier = nullptr,
        .getSliderModifier = nullptr,
        .getDividerModifier = nullptr,
        .getStackModifier = nullptr,
        .getFolderStackModifier = nullptr,
        .getNavDestinationModifier = nullptr,
        .getGridModifier = nullptr,
        .getGridColModifier = nullptr,
        .getGridRowModifier = nullptr,
        .getPanelModifier = nullptr,
        .getTextAreaModifier = nullptr,
        .getNavigationModifier = nullptr,
        .getColumnModifier = nullptr,
        .getRichEditorModifier = nullptr,
        .getImageModifier = nullptr,
        .getVideoModifier = nullptr,
        .getVideoControllerModifier = nullptr,
        .getNavigatorModifier = nullptr,
        .getNavRouterModifier = nullptr,
        .getNodeContainerModifier = nullptr,
        .getPatternLockModifier = nullptr,
        .getColumnSplitModifier = nullptr,
        .getLineModifier = nullptr,
        .getPathModifier = nullptr,
        .getPolygonModifier = nullptr,
        .getPolylineModifier = nullptr,
        .getSpanModifier = nullptr,
        .getImageAnimatorModifier = nullptr,
        .getSideBarContainerModifier = nullptr,
        .getCalendarPickerModifier = nullptr,
        .getTextInputModifier = nullptr,
        .getTabsModifier = nullptr,
        .getStepperItemModifier = nullptr,
        .getHyperlinkModifier = nullptr,
        .getMarqueeModifier = nullptr,
        .getMenuItemModifier = nullptr,
        .getMenuModifier = nullptr,
        .getDatePickerModifier = nullptr,
        .getWaterFlowModifier = nullptr,
        .getAlphabetIndexerModifier = nullptr,
        .getDataPanelModifier = nullptr,
        .getGaugeModifier = nullptr,
        .getScrollModifier = nullptr,
        .getGridItemModifier = nullptr,
        .getProgressModifier = nullptr,
        .getCommonShapeModifier = nullptr,
        .getShapeModifier = nullptr,
        .getRectModifier = nullptr,
        .getSwiperModifier = nullptr,
        .getListItemModifier = nullptr,
        .getListModifier = nullptr,
        .getListItemGroupModifier = nullptr,
        .getQRCodeModifier = nullptr,
        .getLoadingProgressModifier = nullptr,
        .getTextClockModifier = nullptr,
        .getTextTimerModifier = nullptr,
        .getRenderNodeModifier = nullptr,
        .getFrameNodeModifier = nullptr,
        .getPluginModifier = nullptr,
        .getXComponentModifier = nullptr,

        .getUIStateModifier = nullptr,

        .getFormComponentModifier = nullptr,
        .getFlexModifier = nullptr,
        .getScrollBarModifier = nullptr,
        .getScrollerModifier = nullptr,
        .getTabContentModifier = nullptr,
        .getTabsControllerModifier = nullptr,
        .getSwiperControllerModifier = nullptr,
        .getGestureModifier = nullptr,
        .getBadgeModifier = nullptr,
        .getWebModifier = nullptr,
        .getRefreshModifier = nullptr,
        .getMenuItemGroupModifier = nullptr,
        .getSearchControllerModifier = nullptr,
        .getSideBarModifier = nullptr,
        .getPatternLockControllerModifier = nullptr,
        .getTextTimerControllerModifier = nullptr,
        .getTextClockControllerModifier = nullptr,
        .getRichEditorControllerModifier = nullptr,
        .getTextAreaControllerModifier = nullptr,
        .getRelativeContainerModifier = nullptr,
        .getNodeContentModifier = nullptr,
        .getParticleModifier = nullptr,
        .getSymbolGlyphModifier = nullptr,
        .getSymbolSpanModifier = nullptr,

        .getComponent3DModifier = nullptr,

        .getContainerSpanModifier = nullptr,
    };
    return &modifiers;
}
}