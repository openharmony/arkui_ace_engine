/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!
 */

#include "arkoala-macros.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "node_api.h"

namespace OHOS::Ace::NG {

Ark_Float32 GetDensity(Ark_Int32 deviceId);
Ark_Float32 GetFontScale(Ark_Int32 deviceId);
Ark_Float32 GetDesignWidthScale(Ark_Int32 deviceId);

namespace ApiImpl {
    // Basic API
    Ark_NodeHandle GetNodeByViewStack();
    void DisposeNode(Ark_NodeHandle node);
    void DumpTreeNode(Ark_NodeHandle node);
    Ark_Int32 AddChild(Ark_NodeHandle parent, Ark_NodeHandle child);
    void RemoveChild(Ark_NodeHandle parent, Ark_NodeHandle child);
    Ark_Int32 InsertChildAfter(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_NodeHandle sibling);
    Ark_Int32 InsertChildBefore(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_NodeHandle sibling);
    Ark_Int32 InsertChildAt(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_Int32 position);
    void ApplyModifierFinish(Ark_NodeHandle node);
    void MarkDirty(Ark_NodeHandle node, Ark_UInt32 flag);
    Ark_Boolean IsBuilderNode(Ark_NodeHandle node);
    Ark_Float32 ConvertLengthMetricsUnit(Ark_Float32 value, Ark_Int32 originUnit, Ark_Int32 targetUnit);

    // Extended API
    void SetCustomMethodFlag(Ark_NodeHandle node, Ark_Int32 flag);
    Ark_Int32 GetCustomMethodFlag(Ark_NodeHandle node);
    void RegisterCustomNodeAsyncEvent(Ark_NodeHandle node, Ark_Int32 eventType, void* extraParam);
    Ark_Int32 UnregisterCustomNodeEvent(Ark_NodeHandle node, Ark_Int32 eventType);
    void SetCustomCallback(Ark_VMContext context, Ark_NodeHandle node, Ark_Int32 callback);
    Ark_Int32 MeasureLayoutAndDraw(Ark_VMContext vmContext, Ark_NodeHandle rootPtr);
    Ark_Int32 MeasureNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32* data);
    Ark_Int32 LayoutNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32 (*data)[2]);
    Ark_Int32 DrawNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32* data);
    void SetAttachNodePtr(Ark_NodeHandle node, void* value);
    void* GetAttachNodePtr(Ark_NodeHandle node);
    void SetMeasureWidth(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 GetMeasureWidth(Ark_NodeHandle node);
    void SetMeasureHeight(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 GetMeasureHeight(Ark_NodeHandle node);
    void SetX(Ark_NodeHandle node, Ark_Int32 value);
    void SetY(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 GetX(Ark_NodeHandle node);
    Ark_Int32 GetY(Ark_NodeHandle node);
    void SetAlignment(Ark_NodeHandle node, Ark_Int32 value);
    Ark_Int32 GetAlignment(Ark_NodeHandle node);
    void GetLayoutConstraint(Ark_NodeHandle node, Ark_Int32* value);
    Ark_Int32 IndexerChecker(Ark_VMContext vmContext, Ark_NodeHandle nodePtr);
    void SetRangeUpdater(Ark_NodeHandle nodePtr, Ark_Int32 updaterId);
    void SetLazyItemIndexer(Ark_VMContext vmContext, Ark_NodeHandle nodePtr, Ark_Int32 indexerId);
    Ark_PipelineContext GetPipelineContext(Ark_NodeHandle node);
    void SetVsyncCallback(Ark_PipelineContext pipelineContext, Ark_VsyncCallback callback);
    void SetChildTotalCount(Ark_NodeHandle node, Ark_Int32 totalCount);
    void ShowCrash(Ark_CharPtr message);
} // namespace OHOS::Ace::NG::ApiImpl

namespace Bridge {
    Ark_NodeHandle CreateNode(GENERATED_Ark_NodeType type, Ark_Int32 id, Ark_Int32 flags);
    void SetCallbackMethod(GENERATED_Ark_APICallbackMethod* method);
}

namespace GeneratedEvents {
    const GENERATED_ArkUIEventsAPI* GENERATED_GetArkUiEventsAPI();
    void GENERATED_SetArkUiEventsAPI(const GENERATED_ArkUIEventsAPI* api);
}

}

namespace OHOS::Ace::NG::GeneratedModifier {

void SetAppendGroupedLog(void* pFunc) {}

const GENERATED_ArkUIAbilityComponentModifier* GetAbilityComponentModifier();
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier();
const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier();
const GENERATED_ArkUIBadgeModifier* GetBadgeModifier();
const GENERATED_ArkUIBlankModifier* GetBlankModifier();
const GENERATED_ArkUIButtonModifier* GetButtonModifier();
const GENERATED_ArkUICalendarModifier* GetCalendarModifier();
const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier();
const GENERATED_ArkUICanvasModifier* GetCanvasModifier();
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier();
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier();
const GENERATED_ArkUICircleModifier* GetCircleModifier();
const GENERATED_ArkUIColumnModifier* GetColumnModifier();
const GENERATED_ArkUIColumnSplitModifier* GetColumnSplitModifier();
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier();
const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier();
const GENERATED_ArkUICommonModifier* GetCommonModifier();
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier();
const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier();
const GENERATED_ArkUIContainerSpanModifier* GetContainerSpanModifier();
const GENERATED_ArkUICounterModifier* GetCounterModifier();
const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier();
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier();
const GENERATED_ArkUIDividerModifier* GetDividerModifier();
const GENERATED_ArkUIEffectComponentModifier* GetEffectComponentModifier();
const GENERATED_ArkUIEllipseModifier* GetEllipseModifier();
const GENERATED_ArkUIEmbeddedComponentModifier* GetEmbeddedComponentModifier();
const GENERATED_ArkUIFlexModifier* GetFlexModifier();
const GENERATED_ArkUIFlowItemModifier* GetFlowItemModifier();
const GENERATED_ArkUIFolderStackModifier* GetFolderStackModifier();
const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier();
const GENERATED_ArkUIFormLinkModifier* GetFormLinkModifier();
const GENERATED_ArkUIGaugeModifier* GetGaugeModifier();
const GENERATED_ArkUIGridModifier* GetGridModifier();
const GENERATED_ArkUIGridItemModifier* GetGridItemModifier();
const GENERATED_ArkUIGridColModifier* GetGridColModifier();
const GENERATED_ArkUIGridContainerModifier* GetGridContainerModifier();
const GENERATED_ArkUIGridRowModifier* GetGridRowModifier();
const GENERATED_ArkUIHyperlinkModifier* GetHyperlinkModifier();
const GENERATED_ArkUIImageModifier* GetImageModifier();
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier();
const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier();
const GENERATED_ArkUILineModifier* GetLineModifier();
const GENERATED_ArkUIListModifier* GetListModifier();
const GENERATED_ArkUIListItemModifier* GetListItemModifier();
const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier();
const GENERATED_ArkUILoadingProgressModifier* GetLoadingProgressModifier();
const GENERATED_ArkUILocationButtonModifier* GetLocationButtonModifier();
const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier();
const GENERATED_ArkUIMediaCachedImageModifier* GetMediaCachedImageModifier();
const GENERATED_ArkUIMenuModifier* GetMenuModifier();
const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier();
const GENERATED_ArkUIMenuItemGroupModifier* GetMenuItemGroupModifier();
const GENERATED_ArkUINavDestinationModifier* GetNavDestinationModifier();
const GENERATED_ArkUINavRouterModifier* GetNavRouterModifier();
const GENERATED_ArkUINavigationModifier* GetNavigationModifier();
const GENERATED_ArkUINavigatorModifier* GetNavigatorModifier();
const GENERATED_ArkUINodeContainerModifier* GetNodeContainerModifier();
const GENERATED_ArkUIPanelModifier* GetPanelModifier();
const GENERATED_ArkUIPasteButtonModifier* GetPasteButtonModifier();
const GENERATED_ArkUIPathModifier* GetPathModifier();
const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier();
const GENERATED_ArkUIPluginComponentModifier* GetPluginComponentModifier();
const GENERATED_ArkUIPolygonModifier* GetPolygonModifier();
const GENERATED_ArkUIPolylineModifier* GetPolylineModifier();
const GENERATED_ArkUIProgressModifier* GetProgressModifier();
const GENERATED_ArkUIQRCodeModifier* GetQRCodeModifier();
const GENERATED_ArkUIRadioModifier* GetRadioModifier();
const GENERATED_ArkUIRatingModifier* GetRatingModifier();
const GENERATED_ArkUIRectModifier* GetRectModifier();
const GENERATED_ArkUIRefreshModifier* GetRefreshModifier();
const GENERATED_ArkUIRelativeContainerModifier* GetRelativeContainerModifier();
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier();
const GENERATED_ArkUIRichTextModifier* GetRichTextModifier();
const GENERATED_ArkUIRootSceneModifier* GetRootSceneModifier();
const GENERATED_ArkUIRowModifier* GetRowModifier();
const GENERATED_ArkUIRowSplitModifier* GetRowSplitModifier();
const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier();
const GENERATED_ArkUIScreenModifier* GetScreenModifier();
const GENERATED_ArkUIScrollModifier* GetScrollModifier();
const GENERATED_ArkUIScrollBarModifier* GetScrollBarModifier();
const GENERATED_ArkUISearchModifier* GetSearchModifier();
const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier();
const GENERATED_ArkUISelectModifier* GetSelectModifier();
const GENERATED_ArkUIShapeModifier* GetShapeModifier();
const GENERATED_ArkUISliderModifier* GetSliderModifier();
const GENERATED_ArkUIBaseSpanModifier* GetBaseSpanModifier();
const GENERATED_ArkUISpanModifier* GetSpanModifier();
const GENERATED_ArkUIStackModifier* GetStackModifier();
const GENERATED_ArkUIStepperModifier* GetStepperModifier();
const GENERATED_ArkUIStepperItemModifier* GetStepperItemModifier();
const GENERATED_ArkUISwiperModifier* GetSwiperModifier();
const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphModifier();
const GENERATED_ArkUISymbolSpanModifier* GetSymbolSpanModifier();
const GENERATED_ArkUITabsModifier* GetTabsModifier();
const GENERATED_ArkUITabContentModifier* GetTabContentModifier();
const GENERATED_ArkUITextModifier* GetTextModifier();
const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier();
const GENERATED_ArkUITextClockModifier* GetTextClockModifier();
const GENERATED_ArkUITextInputModifier* GetTextInputModifier();
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier();
const GENERATED_ArkUITextTimerModifier* GetTextTimerModifier();
const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier();
const GENERATED_ArkUIToggleModifier* GetToggleModifier();
const GENERATED_ArkUIVideoModifier* GetVideoModifier();
const GENERATED_ArkUIWebModifier* GetWebModifier();
const GENERATED_ArkUIWindowSceneModifier* GetWindowSceneModifier();
const GENERATED_ArkUIXComponentModifier* GetXComponentModifier();
const GENERATED_ArkUISideBarContainerModifier* GetSideBarContainerModifier();
const GENERATED_ArkUIRemoteWindowModifier* GetRemoteWindowModifier();
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier();
const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier();
const GENERATED_ArkUILinearIndicatorModifier* GetLinearIndicatorModifier();
const GENERATED_ArkUIActionSheetAccessor* GetActionSheetAccessor();
const GENERATED_ArkUIAlertDialogAccessor* GetAlertDialogAccessor();
const GENERATED_ArkUICalendarControllerAccessor* GetCalendarControllerAccessor();
const GENERATED_ArkUICalendarPickerDialogAccessor* GetCalendarPickerDialogAccessor();
const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor();
const GENERATED_ArkUICanvasPathAccessor* GetCanvasPathAccessor();
const GENERATED_ArkUIPath2DAccessor* GetPath2DAccessor();
const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor();
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor();
const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor();
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor();
const GENERATED_ArkUIDrawingRenderingContextAccessor* GetDrawingRenderingContextAccessor();
const GENERATED_ArkUIIMonitorAccessor* GetIMonitorAccessor();
const GENERATED_ArkUIICurveAccessor* GetICurveAccessor();
const GENERATED_ArkUIDrawModifierAccessor* GetDrawModifierAccessor();
const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor();
const GENERATED_ArkUIPixelMapMockAccessor* GetPixelMapMockAccessor();
const GENERATED_ArkUIProgressMaskAccessor* GetProgressMaskAccessor();
const GENERATED_ArkUIAttributeModifierAccessor* GetAttributeModifierAccessor();
const GENERATED_ArkUIContentModifierAccessor* GetContentModifierAccessor();
const GENERATED_ArkUIMeasurableAccessor* GetMeasurableAccessor();
const GENERATED_ArkUIViewAccessor* GetViewAccessor();
const GENERATED_ArkUITextContentControllerBaseAccessor* GetTextContentControllerBaseAccessor();
const GENERATED_ArkUIDynamicNodeAccessor* GetDynamicNodeAccessor();
const GENERATED_ArkUIChildrenMainSizeAccessor* GetChildrenMainSizeAccessor();
const GENERATED_ArkUIGestureModifierAccessor* GetGestureModifierAccessor();
const GENERATED_ArkUIAbstractPropertyAccessor* GetAbstractPropertyAccessor();
const GENERATED_ArkUIIPropertySubscriberAccessor* GetIPropertySubscriberAccessor();
const GENERATED_ArkUIISinglePropertyChangeSubscriberAccessor* GetISinglePropertyChangeSubscriberAccessor();
const GENERATED_ArkUISubscribaleAbstractAccessor* GetSubscribaleAbstractAccessor();
const GENERATED_ArkUIContextMenuAccessor* GetContextMenuAccessor();
const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor();
const GENERATED_ArkUIDatePickerDialogAccessor* GetDatePickerDialogAccessor();
const GENERATED_ArkUIPanGestureOptionsAccessor* GetPanGestureOptionsAccessor();
const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor();
const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor();
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor();
const GENERATED_ArkUIPanRecognizerAccessor* GetPanRecognizerAccessor();
const GENERATED_ArkUIImageAnalyzerControllerAccessor* GetImageAnalyzerControllerAccessor();
const GENERATED_ArkUIListScrollerAccessor* GetListScrollerAccessor();
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor();
const GENERATED_ArkUINavDestinationContextAccessor* GetNavDestinationContextAccessor();
const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor();
const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor();
const GENERATED_ArkUIPatternLockControllerAccessor* GetPatternLockControllerAccessor();
const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor();
const GENERATED_ArkUIRichEditorControllerAccessor* GetRichEditorControllerAccessor();
const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* GetRichEditorStyledStringControllerAccessor();
const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor();
const GENERATED_ArkUISearchControllerAccessor* GetSearchControllerAccessor();
const GENERATED_ArkUISwiperControllerAccessor* GetSwiperControllerAccessor();
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor();
const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor();
const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor();
const GENERATED_ArkUITextControllerAccessor* GetTextControllerAccessor();
const GENERATED_ArkUITextAreaControllerAccessor* GetTextAreaControllerAccessor();
const GENERATED_ArkUITextClockControllerAccessor* GetTextClockControllerAccessor();
const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor();
const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor();
const GENERATED_ArkUIStyledStringControllerAccessor* GetStyledStringControllerAccessor();
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor();
const GENERATED_ArkUIEditMenuOptionsAccessor* GetEditMenuOptionsAccessor();
const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor();
const GENERATED_ArkUITextPickerDialogAccessor* GetTextPickerDialogAccessor();
const GENERATED_ArkUITextTimerControllerAccessor* GetTextTimerControllerAccessor();
const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor();
const GENERATED_ArkUIVideoControllerAccessor* GetVideoControllerAccessor();
const GENERATED_ArkUIWebKeyboardControllerAccessor* GetWebKeyboardControllerAccessor();
const GENERATED_ArkUIFullScreenExitHandlerAccessor* GetFullScreenExitHandlerAccessor();
const GENERATED_ArkUIFileSelectorParamAccessor* GetFileSelectorParamAccessor();
const GENERATED_ArkUIJsResultAccessor* GetJsResultAccessor();
const GENERATED_ArkUIFileSelectorResultAccessor* GetFileSelectorResultAccessor();
const GENERATED_ArkUIHttpAuthHandlerAccessor* GetHttpAuthHandlerAccessor();
const GENERATED_ArkUISslErrorHandlerAccessor* GetSslErrorHandlerAccessor();
const GENERATED_ArkUIClientAuthenticationHandlerAccessor* GetClientAuthenticationHandlerAccessor();
const GENERATED_ArkUIPermissionRequestAccessor* GetPermissionRequestAccessor();
const GENERATED_ArkUIScreenCaptureHandlerAccessor* GetScreenCaptureHandlerAccessor();
const GENERATED_ArkUIDataResubmissionHandlerAccessor* GetDataResubmissionHandlerAccessor();
const GENERATED_ArkUIControllerHandlerAccessor* GetControllerHandlerAccessor();
const GENERATED_ArkUIWebContextMenuParamAccessor* GetWebContextMenuParamAccessor();
const GENERATED_ArkUIWebContextMenuResultAccessor* GetWebContextMenuResultAccessor();
const GENERATED_ArkUIConsoleMessageAccessor* GetConsoleMessageAccessor();
const GENERATED_ArkUIWebResourceRequestAccessor* GetWebResourceRequestAccessor();
const GENERATED_ArkUIWebResourceResponseAccessor* GetWebResourceResponseAccessor();
const GENERATED_ArkUIWebResourceErrorAccessor* GetWebResourceErrorAccessor();
const GENERATED_ArkUIJsGeolocationAccessor* GetJsGeolocationAccessor();
const GENERATED_ArkUIWebCookieAccessor* GetWebCookieAccessor();
const GENERATED_ArkUIEventResultAccessor* GetEventResultAccessor();
const GENERATED_ArkUIWebControllerAccessor* GetWebControllerAccessor();
const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor();
const GENERATED_ArkUIWaterFlowSectionsAccessor* GetWaterFlowSectionsAccessor();
const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor();
const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor();
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor();
const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor();
const GENERATED_ArkUILinearIndicatorControllerAccessor* GetLinearIndicatorControllerAccessor();
const GENERATED_ArkUINodeModifiers* GENERATED_GetArkUINodeModifiers()
{
    static const GENERATED_ArkUINodeModifiers modifiersImpl = {
        GetAbilityComponentModifier,
        GetAlphabetIndexerModifier,
        GetAnimatorModifier,
        GetBadgeModifier,
        GetBlankModifier,
        GetButtonModifier,
        GetCalendarModifier,
        GetCalendarPickerModifier,
        GetCanvasModifier,
        GetCheckboxModifier,
        GetCheckboxGroupModifier,
        GetCircleModifier,
        GetColumnModifier,
        GetColumnSplitModifier,
        GetCommonMethodModifier,
        GetCommonShapeMethodModifier,
        GetCommonModifier,
        GetScrollableCommonMethodModifier,
        GetComponent3DModifier,
        GetContainerSpanModifier,
        GetCounterModifier,
        GetDataPanelModifier,
        GetDatePickerModifier,
        GetDividerModifier,
        GetEffectComponentModifier,
        GetEllipseModifier,
        GetEmbeddedComponentModifier,
        GetFlexModifier,
        GetFlowItemModifier,
        GetFolderStackModifier,
        GetFormComponentModifier,
        GetFormLinkModifier,
        GetGaugeModifier,
        GetGridModifier,
        GetGridItemModifier,
        GetGridColModifier,
        GetGridContainerModifier,
        GetGridRowModifier,
        GetHyperlinkModifier,
        GetImageModifier,
        GetImageAnimatorModifier,
        GetImageSpanModifier,
        GetLineModifier,
        GetListModifier,
        GetListItemModifier,
        GetListItemGroupModifier,
        GetLoadingProgressModifier,
        GetLocationButtonModifier,
        GetMarqueeModifier,
        GetMediaCachedImageModifier,
        GetMenuModifier,
        GetMenuItemModifier,
        GetMenuItemGroupModifier,
        GetNavDestinationModifier,
        GetNavRouterModifier,
        GetNavigationModifier,
        GetNavigatorModifier,
        GetNodeContainerModifier,
        GetPanelModifier,
        GetPasteButtonModifier,
        GetPathModifier,
        GetPatternLockModifier,
        GetPluginComponentModifier,
        GetPolygonModifier,
        GetPolylineModifier,
        GetProgressModifier,
        GetQRCodeModifier,
        GetRadioModifier,
        GetRatingModifier,
        GetRectModifier,
        GetRefreshModifier,
        GetRelativeContainerModifier,
        GetRichEditorModifier,
        GetRichTextModifier,
        GetRootSceneModifier,
        GetRowModifier,
        GetRowSplitModifier,
        GetSaveButtonModifier,
        GetScreenModifier,
        GetScrollModifier,
        GetScrollBarModifier,
        GetSearchModifier,
        GetSecurityComponentMethodModifier,
        GetSelectModifier,
        GetShapeModifier,
        GetSliderModifier,
        GetBaseSpanModifier,
        GetSpanModifier,
        GetStackModifier,
        GetStepperModifier,
        GetStepperItemModifier,
        GetSwiperModifier,
        GetSymbolGlyphModifier,
        GetSymbolSpanModifier,
        GetTabsModifier,
        GetTabContentModifier,
        GetTextModifier,
        GetTextAreaModifier,
        GetTextClockModifier,
        GetTextInputModifier,
        GetTextPickerModifier,
        GetTextTimerModifier,
        GetTimePickerModifier,
        GetToggleModifier,
        GetVideoModifier,
        GetWebModifier,
        GetWindowSceneModifier,
        GetXComponentModifier,
        GetSideBarContainerModifier,
        GetRemoteWindowModifier,
        GetWaterFlowModifier,
        GetUIExtensionComponentModifier,
        GetLinearIndicatorModifier,
    };
    return &modifiersImpl;
}
const GENERATED_ArkUIAccessors* GENERATED_GetArkUIAccessors()
{
    static const GENERATED_ArkUIAccessors accessorsImpl = {
        GetActionSheetAccessor,
        GetAlertDialogAccessor,
        GetCalendarControllerAccessor,
        GetCalendarPickerDialogAccessor,
        GetCanvasGradientAccessor,
        GetCanvasPathAccessor,
        GetPath2DAccessor,
        GetCanvasPatternAccessor,
        GetImageBitmapAccessor,
        GetCanvasRendererAccessor,
        GetCanvasRenderingContext2DAccessor,
        GetDrawingRenderingContextAccessor,
        GetIMonitorAccessor,
        GetICurveAccessor,
        GetDrawModifierAccessor,
        GetTransitionEffectAccessor,
        GetPixelMapMockAccessor,
        GetProgressMaskAccessor,
        GetAttributeModifierAccessor,
        GetContentModifierAccessor,
        GetMeasurableAccessor,
        GetViewAccessor,
        GetTextContentControllerBaseAccessor,
        GetDynamicNodeAccessor,
        GetChildrenMainSizeAccessor,
        GetGestureModifierAccessor,
        GetAbstractPropertyAccessor,
        GetIPropertySubscriberAccessor,
        GetISinglePropertyChangeSubscriberAccessor,
        GetSubscribaleAbstractAccessor,
        GetContextMenuAccessor,
        GetCustomDialogControllerAccessor,
        GetDatePickerDialogAccessor,
        GetPanGestureOptionsAccessor,
        GetScrollableTargetInfoAccessor,
        GetEventTargetInfoAccessor,
        GetGestureRecognizerAccessor,
        GetPanRecognizerAccessor,
        GetImageAnalyzerControllerAccessor,
        GetListScrollerAccessor,
        GetMatrix2DAccessor,
        GetNavDestinationContextAccessor,
        GetNavPathStackAccessor,
        GetNavigationTransitionProxyAccessor,
        GetPatternLockControllerAccessor,
        GetRichEditorBaseControllerAccessor,
        GetRichEditorControllerAccessor,
        GetRichEditorStyledStringControllerAccessor,
        GetScrollerAccessor,
        GetSearchControllerAccessor,
        GetSwiperControllerAccessor,
        GetSwiperContentTransitionProxyAccessor,
        GetTabsControllerAccessor,
        GetTabContentTransitionProxyAccessor,
        GetTextControllerAccessor,
        GetTextAreaControllerAccessor,
        GetTextClockControllerAccessor,
        GetTextBaseControllerAccessor,
        GetTextEditControllerExAccessor,
        GetStyledStringControllerAccessor,
        GetLayoutManagerAccessor,
        GetEditMenuOptionsAccessor,
        GetTextInputControllerAccessor,
        GetTextPickerDialogAccessor,
        GetTextTimerControllerAccessor,
        GetTimePickerDialogAccessor,
        GetVideoControllerAccessor,
        GetWebKeyboardControllerAccessor,
        GetFullScreenExitHandlerAccessor,
        GetFileSelectorParamAccessor,
        GetJsResultAccessor,
        GetFileSelectorResultAccessor,
        GetHttpAuthHandlerAccessor,
        GetSslErrorHandlerAccessor,
        GetClientAuthenticationHandlerAccessor,
        GetPermissionRequestAccessor,
        GetScreenCaptureHandlerAccessor,
        GetDataResubmissionHandlerAccessor,
        GetControllerHandlerAccessor,
        GetWebContextMenuParamAccessor,
        GetWebContextMenuResultAccessor,
        GetConsoleMessageAccessor,
        GetWebResourceRequestAccessor,
        GetWebResourceResponseAccessor,
        GetWebResourceErrorAccessor,
        GetJsGeolocationAccessor,
        GetWebCookieAccessor,
        GetEventResultAccessor,
        GetWebControllerAccessor,
        GetXComponentControllerAccessor,
        GetWaterFlowSectionsAccessor,
        GetUIExtensionProxyAccessor,
        GetStyledStringAccessor,
        GetMutableStyledStringAccessor,
        GetCustomSpanAccessor,
        GetLinearIndicatorControllerAccessor,
    };
    return &accessorsImpl;
}
const GENERATED_ArkUIBasicNodeAPI* GENERATED_GetBasicAPI()
{
    static const GENERATED_ArkUIBasicNodeAPI basicNodeAPIImpl = {
        GENERATED_ARKUI_BASIC_NODE_API_VERSION, // version
        OHOS::Ace::NG::Bridge::CreateNode,
        OHOS::Ace::NG::ApiImpl::GetNodeByViewStack,
        OHOS::Ace::NG::ApiImpl::DisposeNode,
        OHOS::Ace::NG::ApiImpl::DumpTreeNode,
        OHOS::Ace::NG::ApiImpl::AddChild,
        OHOS::Ace::NG::ApiImpl::RemoveChild,
        OHOS::Ace::NG::ApiImpl::InsertChildAfter,
        OHOS::Ace::NG::ApiImpl::InsertChildBefore,
        OHOS::Ace::NG::ApiImpl::InsertChildAt,
        OHOS::Ace::NG::ApiImpl::ApplyModifierFinish,
        OHOS::Ace::NG::ApiImpl::MarkDirty,
        OHOS::Ace::NG::ApiImpl::IsBuilderNode,
        OHOS::Ace::NG::ApiImpl::ConvertLengthMetricsUnit
    };
    return &basicNodeAPIImpl;
}

const GENERATED_ArkUIExtendedNodeAPI* GENERATED_GetExtendedAPI()
{
    static const GENERATED_ArkUIExtendedNodeAPI extendedNodeAPIImpl = {
        GENERATED_ARKUI_EXTENDED_NODE_API_VERSION, // version
        OHOS::Ace::NG::GetDensity,
        OHOS::Ace::NG::GetFontScale,
        OHOS::Ace::NG::GetDesignWidthScale,
        OHOS::Ace::NG::Bridge::SetCallbackMethod,
        OHOS::Ace::NG::ApiImpl::SetCustomMethodFlag,
        OHOS::Ace::NG::ApiImpl::GetCustomMethodFlag,
        OHOS::Ace::NG::ApiImpl::SetCustomCallback,
        OHOS::Ace::NG::ApiImpl::MeasureLayoutAndDraw,
        OHOS::Ace::NG::ApiImpl::MeasureNode,
        OHOS::Ace::NG::ApiImpl::LayoutNode,
        OHOS::Ace::NG::ApiImpl::DrawNode,
        OHOS::Ace::NG::ApiImpl::SetAttachNodePtr,
        OHOS::Ace::NG::ApiImpl::GetAttachNodePtr,
        OHOS::Ace::NG::ApiImpl::SetMeasureWidth,
        OHOS::Ace::NG::ApiImpl::GetMeasureWidth,
        OHOS::Ace::NG::ApiImpl::SetMeasureHeight,
        OHOS::Ace::NG::ApiImpl::GetMeasureHeight,
        OHOS::Ace::NG::ApiImpl::SetX,
        OHOS::Ace::NG::ApiImpl::GetX,
        OHOS::Ace::NG::ApiImpl::SetY,
        OHOS::Ace::NG::ApiImpl::GetY,
        OHOS::Ace::NG::ApiImpl::GetLayoutConstraint,
        OHOS::Ace::NG::ApiImpl::SetAlignment,
        OHOS::Ace::NG::ApiImpl::GetAlignment,
        OHOS::Ace::NG::ApiImpl::IndexerChecker,
        OHOS::Ace::NG::ApiImpl::SetRangeUpdater,
        OHOS::Ace::NG::ApiImpl::SetLazyItemIndexer,
        OHOS::Ace::NG::ApiImpl::GetPipelineContext,
        OHOS::Ace::NG::ApiImpl::SetVsyncCallback,
        OHOS::Ace::NG::ApiImpl::SetChildTotalCount,
        OHOS::Ace::NG::ApiImpl::ShowCrash
    };
    return &extendedNodeAPIImpl;
}

// TODO: remove me!
const GENERATED_ArkUIFullNodeAPI* GENERATED_GetFullAPI()
{
    static const GENERATED_ArkUIFullNodeAPI fullAPIImpl = {
        GENERATED_ARKUI_FULL_API_VERSION, // version
        GENERATED_GetArkUINodeModifiers,
        GENERATED_GetArkUIAccessors,
        nullptr,
        OHOS::Ace::NG::GeneratedEvents::GENERATED_GetArkUiEventsAPI,
        OHOS::Ace::NG::GeneratedEvents::GENERATED_SetArkUiEventsAPI
    };
    return &fullAPIImpl;
}

void setLogger(const ServiceLogger* logger) {
}

const GenericServiceAPI* GetServiceAPI()
{
    static const GenericServiceAPI serviceAPIImpl = {
        GENERIC_SERVICE_API_VERSION, // version
        setLogger
    };
    return &serviceAPIImpl;
}

EXTERN_C IDLIZE_API_EXPORT const GENERATED_ArkUIAnyAPI* GENERATED_GetArkAnyAPI(
    GENERATED_Ark_APIVariantKind kind, int version)
{
    switch (kind) {
        case GENERATED_FULL:
            if (version == GENERATED_ARKUI_FULL_API_VERSION)   {
                return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GENERATED_GetFullAPI());
            }
            break;
        case GENERATED_BASIC:
            if (version == GENERATED_ARKUI_BASIC_NODE_API_VERSION)   {
                return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GENERATED_GetBasicAPI());
            }
            break;
        case GENERATED_EXTENDED:
            if (version == GENERATED_ARKUI_EXTENDED_NODE_API_VERSION)   {
                return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GENERATED_GetExtendedAPI());
            }
            break;
        case GENERIC_SERVICE:
            if (version == GENERIC_SERVICE_API_VERSION)   {
                return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GetServiceAPI());
            }
            break;
        default:
            break;
    }
    return nullptr;
}

}
