/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "arkoala_api_generated.h"
#include "node_api.h"

namespace OHOS::Ace::NG {
namespace GeneratedApiImpl {
    Ark_Float32 GetDensity(Ark_Int32 deviceId);
    Ark_Float32 GetFontScale(Ark_Int32 deviceId);
    Ark_Float32 GetDesignWidthScale(Ark_Int32 deviceId);

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
    void SetCustomNodeDestroyCallback(void (*destroy)(Ark_NodeHandle nodeId));
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
    void SetCallbackMethod(GENERATED_Ark_APICallbackMethod* method);
} // namespace OHOS::Ace::NG::GeneratedApiImpl

namespace GeneratedBridge {
    Ark_NodeHandle CreateNode(GENERATED_Ark_NodeType type, Ark_Int32 id, Ark_Int32 flags);
}


}

namespace OHOS::Ace::NG::GeneratedModifier {

void SetAppendGroupedLog(void* pFunc) {}

const GENERATED_ArkUIRootModifier* GetRootModifier();
const GENERATED_ArkUIComponentRootModifier* GetComponentRootModifier();
const GENERATED_ArkUIAbilityComponentModifier* GetAbilityComponentModifier();
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier();
const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier();
const GENERATED_ArkUIBadgeModifier* GetBadgeModifier();
const GENERATED_ArkUIBlankModifier* GetBlankModifier();
const GENERATED_ArkUIButtonModifier* GetButtonModifier();
const GENERATED_ArkUICalendarModifier* GetCalendarModifier();
const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier();
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier();
const GENERATED_ArkUICommonModifier* GetCommonModifier();
const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier();
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier();
const GENERATED_ArkUINavigationModifier* GetNavigationModifier();
const GENERATED_ArkUICanvasModifier* GetCanvasModifier();
const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier();
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier();
const GENERATED_ArkUICircleModifier* GetCircleModifier();
const GENERATED_ArkUIColumnModifier* GetColumnModifier();
const GENERATED_ArkUIColumnSplitModifier* GetColumnSplitModifier();
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
#ifndef ARKUI_WEARABLE
const GENERATED_ArkUIFolderStackModifier* GetFolderStackModifier();
#endif
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
const GENERATED_ArkUILazyGridLayoutModifier* GetLazyGridLayoutModifier();
const GENERATED_ArkUILazyVGridLayoutModifier* GetLazyVGridLayoutModifier();
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
const GENERATED_ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier();
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
const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor();
const GENERATED_ArkUIBaseContextAccessor* GetBaseContextAccessor();
const GENERATED_ArkUIContextAccessor* GetContextAccessor();
const GENERATED_ArkUIUnifiedDataAccessor* GetUnifiedDataAccessor();
const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor();
const GENERATED_ArkUISystemOpsAccessor* GetSystemOpsAccessor();
const GENERATED_ArkUIGestureOpsAccessor* GetGestureOpsAccessor();
const GENERATED_ArkUIFocusControllerAccessor* GetFocusControllerAccessor();
const GENERATED_ArkUIComponentContentAccessor* GetComponentContentAccessor();
const GENERATED_ArkUISceneAccessor* GetSceneAccessor();
const GENERATED_ArkUIWorkerEventListenerAccessor* GetWorkerEventListenerAccessor();
const GENERATED_ArkUIRestrictedWorkerAccessor* GetRestrictedWorkerAccessor();
const GENERATED_ArkUIUIContextAccessor* GetUIContextAccessor();
const GENERATED_ArkUIStateStylesOpsAccessor* GetStateStylesOpsAccessor();
const GENERATED_ArkUIUIContextAtomicServiceBarAccessor* GetUIContextAtomicServiceBarAccessor();
const GENERATED_ArkUIUIContextDispatchKeyEventAccessor* GetUIContextDispatchKeyEventAccessor();
const GENERATED_ArkUIDrawableDescriptorAccessor* GetDrawableDescriptorAccessor();
const GENERATED_ArkUILayeredDrawableDescriptorAccessor* GetLayeredDrawableDescriptorAccessor();
const GENERATED_ArkUIPixelMapDrawableDescriptorAccessor* GetPixelMapDrawableDescriptorAccessor();
const GENERATED_ArkUIAnimatedDrawableDescriptorAccessor* GetAnimatedDrawableDescriptorAccessor();
const GENERATED_ArkUIDrawingColorFilterAccessor* GetDrawingColorFilterAccessor();
const GENERATED_ArkUIDrawingLatticeAccessor* GetDrawingLatticeAccessor();
const GENERATED_ArkUIDrawingCanvasAccessor* GetDrawingCanvasAccessor();
const GENERATED_ArkUIColorMetricsAccessor* GetColorMetricsAccessor();
const GENERATED_ArkUIWebviewControllerAccessor* GetWebviewControllerAccessor();
const GENERATED_ArkUIGlobalScope_ohos_arkui_componentSnapshotAccessor* GetGlobalScope_ohos_arkui_componentSnapshotAccessor();
const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor* GetGlobalScope_ohos_arkui_performanceMonitorAccessor();
const GENERATED_ArkUICommonShapeAccessor* GetCommonShapeAccessor();
const GENERATED_ArkUIBaseShapeAccessor* GetBaseShapeAccessor();
const GENERATED_ArkUIRectShapeAccessor* GetRectShapeAccessor();
const GENERATED_ArkUICircleShapeAccessor* GetCircleShapeAccessor();
const GENERATED_ArkUIEllipseShapeAccessor* GetEllipseShapeAccessor();
const GENERATED_ArkUIPathShapeAccessor* GetPathShapeAccessor();
const GENERATED_ArkUIGlobalScope_ohos_fontAccessor* GetGlobalScope_ohos_fontAccessor();
const GENERATED_ArkUIGlobalScope_ohos_measure_utilsAccessor* GetGlobalScope_ohos_measure_utilsAccessor();
const GENERATED_ArkUISymbolEffectAccessor* GetSymbolEffectAccessor();
const GENERATED_ArkUIScaleSymbolEffectAccessor* GetScaleSymbolEffectAccessor();
const GENERATED_ArkUIReplaceSymbolEffectAccessor* GetReplaceSymbolEffectAccessor();
const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor();
const GENERATED_ArkUILengthMetricsAccessor* GetLengthMetricsAccessor();
const GENERATED_ArkUIShapeMaskAccessor* GetShapeMaskAccessor();
const GENERATED_ArkUIShapeClipAccessor* GetShapeClipAccessor();
const GENERATED_ArkUIMatrix4TransitAccessor* GetMatrix4TransitAccessor();
const GENERATED_ArkUINodeContentAccessor* GetNodeContentAccessor();
const GENERATED_ArkUIPixelMapAccessor* GetPixelMapAccessor();
const GENERATED_ArkUIRenderNodeAccessor* GetRenderNodeAccessor();
const GENERATED_ArkUITabsOpsAccessor* GetTabsOpsAccessor();
const GENERATED_ArkUIUIContextImpAccessor* GetUIContextImpAccessor();
const GENERATED_ArkUIGridItemOpsAccessor* GetGridItemOpsAccessor();
const GENERATED_ArkUIFilterAccessor* GetFilterAccessor();
const GENERATED_ArkUIVisualEffectAccessor* GetVisualEffectAccessor();
const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor();
const GENERATED_ArkUIStepperOpsAccessor* GetStepperOpsAccessor();
const GENERATED_ArkUISearchOpsAccessor* GetSearchOpsAccessor();
const GENERATED_ArkUIEventEmulatorAccessor* GetEventEmulatorAccessor();
const GENERATED_ArkUITextFieldOpsAccessor* GetTextFieldOpsAccessor();
const GENERATED_ArkUIActionSheetAccessor* GetActionSheetAccessor();
const GENERATED_ArkUIAlertDialogAccessor* GetAlertDialogAccessor();
const GENERATED_ArkUISpringPropAccessor* GetSpringPropAccessor();
const GENERATED_ArkUISpringMotionAccessor* GetSpringMotionAccessor();
const GENERATED_ArkUIFrictionMotionAccessor* GetFrictionMotionAccessor();
const GENERATED_ArkUIScrollMotionAccessor* GetScrollMotionAccessor();
const GENERATED_ArkUICalendarControllerAccessor* GetCalendarControllerAccessor();
const GENERATED_ArkUICalendarPickerDialogAccessor* GetCalendarPickerDialogAccessor();
const GENERATED_ArkUIICurveAccessor* GetICurveAccessor();
const GENERATED_ArkUIDrawModifierAccessor* GetDrawModifierAccessor();
const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor();
const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor();
const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor();
const GENERATED_ArkUIHoverEventAccessor* GetHoverEventAccessor();
const GENERATED_ArkUIMouseEventAccessor* GetMouseEventAccessor();
const GENERATED_ArkUIAccessibilityHoverEventAccessor* GetAccessibilityHoverEventAccessor();
const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor();
const GENERATED_ArkUIAxisEventAccessor* GetAxisEventAccessor();
const GENERATED_ArkUIPixelMapMockAccessor* GetPixelMapMockAccessor();
const GENERATED_ArkUIDragEventAccessor* GetDragEventAccessor();
const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor();
const GENERATED_ArkUIFocusAxisEventAccessor* GetFocusAxisEventAccessor();
const GENERATED_ArkUIProgressMaskAccessor* GetProgressMaskAccessor();
const GENERATED_ArkUIMeasurableAccessor* GetMeasurableAccessor();
const GENERATED_ArkUIViewAccessor* GetViewAccessor();
const GENERATED_ArkUITextContentControllerBaseAccessor* GetTextContentControllerBaseAccessor();
const GENERATED_ArkUIChildrenMainSizeAccessor* GetChildrenMainSizeAccessor();
const GENERATED_ArkUIUICommonEventAccessor* GetUICommonEventAccessor();
const GENERATED_ArkUIGestureModifierAccessor* GetGestureModifierAccessor();
const GENERATED_ArkUINavPathInfoAccessor* GetNavPathInfoAccessor();
const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor();
const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor();
const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor();
const GENERATED_ArkUICanvasPathAccessor* GetCanvasPathAccessor();
const GENERATED_ArkUIPath2DAccessor* GetPath2DAccessor();
const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor();
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor();
const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor();
const GENERATED_ArkUIRenderingContextSettingsAccessor* GetRenderingContextSettingsAccessor();
const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor();
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor();
const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor* GetOffscreenCanvasRenderingContext2DAccessor();
const GENERATED_ArkUIOffscreenCanvasAccessor* GetOffscreenCanvasAccessor();
const GENERATED_ArkUIDrawingRenderingContextAccessor* GetDrawingRenderingContextAccessor();
const GENERATED_ArkUIContextMenuAccessor* GetContextMenuAccessor();
const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor();
const GENERATED_ArkUILinearGradientAccessor* GetLinearGradientAccessor();
const GENERATED_ArkUIDatePickerDialogAccessor* GetDatePickerDialogAccessor();
const GENERATED_ArkUIBaseGestureEventAccessor* GetBaseGestureEventAccessor();
const GENERATED_ArkUITapGestureEventAccessor* GetTapGestureEventAccessor();
const GENERATED_ArkUILongPressGestureEventAccessor* GetLongPressGestureEventAccessor();
const GENERATED_ArkUIPanGestureEventAccessor* GetPanGestureEventAccessor();
const GENERATED_ArkUIPinchGestureEventAccessor* GetPinchGestureEventAccessor();
const GENERATED_ArkUIRotationGestureEventAccessor* GetRotationGestureEventAccessor();
const GENERATED_ArkUISwipeGestureEventAccessor* GetSwipeGestureEventAccessor();
const GENERATED_ArkUIGestureEventAccessor* GetGestureEventAccessor();
const GENERATED_ArkUITapGestureInterfaceAccessor* GetTapGestureInterfaceAccessor();
const GENERATED_ArkUILongPressGestureInterfaceAccessor* GetLongPressGestureInterfaceAccessor();
const GENERATED_ArkUIPanGestureOptionsAccessor* GetPanGestureOptionsAccessor();
const GENERATED_ArkUIPanGestureInterfaceAccessor* GetPanGestureInterfaceAccessor();
const GENERATED_ArkUISwipeGestureInterfaceAccessor* GetSwipeGestureInterfaceAccessor();
const GENERATED_ArkUIPinchGestureInterfaceAccessor* GetPinchGestureInterfaceAccessor();
const GENERATED_ArkUIRotationGestureInterfaceAccessor* GetRotationGestureInterfaceAccessor();
const GENERATED_ArkUIGestureGroupInterfaceAccessor* GetGestureGroupInterfaceAccessor();
const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor();
const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor();
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor();
const GENERATED_ArkUITapRecognizerAccessor* GetTapRecognizerAccessor();
const GENERATED_ArkUILongPressRecognizerAccessor* GetLongPressRecognizerAccessor();
const GENERATED_ArkUISwipeRecognizerAccessor* GetSwipeRecognizerAccessor();
const GENERATED_ArkUIPinchRecognizerAccessor* GetPinchRecognizerAccessor();
const GENERATED_ArkUIRotationRecognizerAccessor* GetRotationRecognizerAccessor();
const GENERATED_ArkUIPanRecognizerAccessor* GetPanRecognizerAccessor();
const GENERATED_ArkUIImageAnalyzerControllerAccessor* GetImageAnalyzerControllerAccessor();
const GENERATED_ArkUIListScrollerAccessor* GetListScrollerAccessor();
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor();
const GENERATED_ArkUINavDestinationContextAccessor* GetNavDestinationContextAccessor();
const GENERATED_ArkUIPatternLockControllerAccessor* GetPatternLockControllerAccessor();
const GENERATED_ArkUIVirtualScrollOptionsAccessor* GetVirtualScrollOptionsAccessor();
const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor();
const GENERATED_ArkUIRichEditorControllerAccessor* GetRichEditorControllerAccessor();
const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* GetRichEditorStyledStringControllerAccessor();
const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor();
const GENERATED_ArkUISearchControllerAccessor* GetSearchControllerAccessor();
const GENERATED_ArkUIMenuItemConfigurationAccessor* GetMenuItemConfigurationAccessor();
const GENERATED_ArkUISwiperControllerAccessor* GetSwiperControllerAccessor();
const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor();
const GENERATED_ArkUIIndicatorComponentControllerAccessor* GetIndicatorComponentControllerAccessor();
const GENERATED_ArkUIHierarchicalSymbolEffectAccessor* GetHierarchicalSymbolEffectAccessor();
const GENERATED_ArkUIAppearSymbolEffectAccessor* GetAppearSymbolEffectAccessor();
const GENERATED_ArkUIDisappearSymbolEffectAccessor* GetDisappearSymbolEffectAccessor();
const GENERATED_ArkUIBounceSymbolEffectAccessor* GetBounceSymbolEffectAccessor();
const GENERATED_ArkUIPulseSymbolEffectAccessor* GetPulseSymbolEffectAccessor();
const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor();
const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor();
const GENERATED_ArkUITextControllerAccessor* GetTextControllerAccessor();
const GENERATED_ArkUITextAreaControllerAccessor* GetTextAreaControllerAccessor();
const GENERATED_ArkUITextClockControllerAccessor* GetTextClockControllerAccessor();
const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor();
const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor();
const GENERATED_ArkUIStyledStringControllerAccessor* GetStyledStringControllerAccessor();
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor();
const GENERATED_ArkUITextMenuItemIdAccessor* GetTextMenuItemIdAccessor();
const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor();
const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor();
const GENERATED_ArkUITextPickerDialogAccessor* GetTextPickerDialogAccessor();
const GENERATED_ArkUITextTimerControllerAccessor* GetTextTimerControllerAccessor();
const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor();
const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor();
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
const GENERATED_ArkUITextStyle_styled_stringAccessor* GetTextStyle_styled_stringAccessor();
const GENERATED_ArkUIDecorationStyleAccessor* GetDecorationStyleAccessor();
const GENERATED_ArkUIBaselineOffsetStyleAccessor* GetBaselineOffsetStyleAccessor();
const GENERATED_ArkUILetterSpacingStyleAccessor* GetLetterSpacingStyleAccessor();
const GENERATED_ArkUITextShadowStyleAccessor* GetTextShadowStyleAccessor();
const GENERATED_ArkUIBackgroundColorStyleAccessor* GetBackgroundColorStyleAccessor();
const GENERATED_ArkUIGestureStyleAccessor* GetGestureStyleAccessor();
const GENERATED_ArkUIParagraphStyleAccessor* GetParagraphStyleAccessor();
const GENERATED_ArkUILineHeightStyleAccessor* GetLineHeightStyleAccessor();
const GENERATED_ArkUIUrlStyleAccessor* GetUrlStyleAccessor();
const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor();
const GENERATED_ArkUIImageAttachmentAccessor* GetImageAttachmentAccessor();
const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor();
const GENERATED_ArkUILinearIndicatorControllerAccessor* GetLinearIndicatorControllerAccessor();
const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor();
const GENERATED_ArkUIPromptActionAccessor* GetPromptActionAccessor();
const GENERATED_ArkUIRouterExtenderAccessor* GetRouterExtenderAccessor();
const GENERATED_ArkUIStateModifier* GetUIStateModifier();
const GENERATED_ArkUINodeModifiers* GENERATED_GetArkUINodeModifiers()
{
    static const GENERATED_ArkUINodeModifiers modifiersImpl = {
        GetRootModifier,
        GetComponentRootModifier,
        GetAbilityComponentModifier,
        GetAlphabetIndexerModifier,
        GetAnimatorModifier,
        GetBadgeModifier,
        GetBlankModifier,
        GetButtonModifier,
        GetCalendarModifier,
        GetCalendarPickerModifier,
        GetCommonMethodModifier,
        GetCommonModifier,
        GetCommonShapeMethodModifier,
        GetScrollableCommonMethodModifier,
        GetNavigationModifier,
        GetCanvasModifier,
        GetCheckboxModifier,
        GetCheckboxGroupModifier,
        GetCircleModifier,
        GetColumnModifier,
        GetColumnSplitModifier,
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
    #ifndef ARKUI_WEARABLE
        GetFolderStackModifier,
    #endif
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
        GetLazyGridLayoutModifier,
        GetLazyVGridLayoutModifier,
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
        GetIndicatorComponentModifier,
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
        GetUIStateModifier,
    };
    return &modifiersImpl;
}
const GENERATED_ArkUIAccessors* GENERATED_GetArkUIAccessors()
{
    static const GENERATED_ArkUIAccessors accessorsImpl = {
        GetAnimationExtenderAccessor,
        GetBaseContextAccessor,
        GetContextAccessor,
        GetUnifiedDataAccessor,
        GetLazyForEachOpsAccessor,
        GetSystemOpsAccessor,
        GetGestureOpsAccessor,
        GetFocusControllerAccessor,
        GetComponentContentAccessor,
        GetSceneAccessor,
        GetWorkerEventListenerAccessor,
        GetRestrictedWorkerAccessor,
        GetUIContextAccessor,
        GetStateStylesOpsAccessor,
        GetUIContextAtomicServiceBarAccessor,
        GetUIContextDispatchKeyEventAccessor,
        GetDrawableDescriptorAccessor,
        GetLayeredDrawableDescriptorAccessor,
        GetPixelMapDrawableDescriptorAccessor,
        GetAnimatedDrawableDescriptorAccessor,
        GetDrawingColorFilterAccessor,
        GetDrawingLatticeAccessor,
        GetDrawingCanvasAccessor,
        GetColorMetricsAccessor,
        GetWebviewControllerAccessor,
        GetGlobalScope_ohos_arkui_componentSnapshotAccessor,
        GetGlobalScope_ohos_arkui_performanceMonitorAccessor,
        GetCommonShapeAccessor,
        GetBaseShapeAccessor,
        GetRectShapeAccessor,
        GetCircleShapeAccessor,
        GetEllipseShapeAccessor,
        GetPathShapeAccessor,
        GetGlobalScope_ohos_fontAccessor,
        GetGlobalScope_ohos_measure_utilsAccessor,
        GetSymbolEffectAccessor,
        GetScaleSymbolEffectAccessor,
        GetReplaceSymbolEffectAccessor,
        GetFrameNodeAccessor,
        GetLengthMetricsAccessor,
        GetShapeMaskAccessor,
        GetShapeClipAccessor,
        GetMatrix4TransitAccessor,
        GetNodeContentAccessor,
        GetPixelMapAccessor,
        GetRenderNodeAccessor,
        GetTabsOpsAccessor,
        GetUIContextImpAccessor,
        GetGridItemOpsAccessor,
        GetFilterAccessor,
        GetVisualEffectAccessor,
        GetNavExtenderAccessor,
        GetStepperOpsAccessor,
        GetSearchOpsAccessor,
        GetEventEmulatorAccessor,
        GetTextFieldOpsAccessor,
        GetActionSheetAccessor,
        GetAlertDialogAccessor,
        GetSpringPropAccessor,
        GetSpringMotionAccessor,
        GetFrictionMotionAccessor,
        GetScrollMotionAccessor,
        GetCalendarControllerAccessor,
        GetCalendarPickerDialogAccessor,
        GetICurveAccessor,
        GetDrawModifierAccessor,
        GetTransitionEffectAccessor,
        GetBaseEventAccessor,
        GetClickEventAccessor,
        GetHoverEventAccessor,
        GetMouseEventAccessor,
        GetAccessibilityHoverEventAccessor,
        GetTouchEventAccessor,
        GetAxisEventAccessor,
        GetPixelMapMockAccessor,
        GetDragEventAccessor,
        GetKeyEventAccessor,
        GetFocusAxisEventAccessor,
        GetProgressMaskAccessor,
        GetMeasurableAccessor,
        GetViewAccessor,
        GetTextContentControllerBaseAccessor,
        GetChildrenMainSizeAccessor,
        GetUICommonEventAccessor,
        GetGestureModifierAccessor,
        GetNavPathInfoAccessor,
        GetNavPathStackAccessor,
        GetNavigationTransitionProxyAccessor,
        GetCanvasGradientAccessor,
        GetCanvasPathAccessor,
        GetPath2DAccessor,
        GetCanvasPatternAccessor,
        GetImageBitmapAccessor,
        GetImageDataAccessor,
        GetRenderingContextSettingsAccessor,
        GetCanvasRendererAccessor,
        GetCanvasRenderingContext2DAccessor,
        GetOffscreenCanvasRenderingContext2DAccessor,
        GetOffscreenCanvasAccessor,
        GetDrawingRenderingContextAccessor,
        GetContextMenuAccessor,
        GetCustomDialogControllerAccessor,
        GetLinearGradientAccessor,
        GetDatePickerDialogAccessor,
        GetBaseGestureEventAccessor,
        GetTapGestureEventAccessor,
        GetLongPressGestureEventAccessor,
        GetPanGestureEventAccessor,
        GetPinchGestureEventAccessor,
        GetRotationGestureEventAccessor,
        GetSwipeGestureEventAccessor,
        GetGestureEventAccessor,
        GetTapGestureInterfaceAccessor,
        GetLongPressGestureInterfaceAccessor,
        GetPanGestureOptionsAccessor,
        GetPanGestureInterfaceAccessor,
        GetSwipeGestureInterfaceAccessor,
        GetPinchGestureInterfaceAccessor,
        GetRotationGestureInterfaceAccessor,
        GetGestureGroupInterfaceAccessor,
        GetScrollableTargetInfoAccessor,
        GetEventTargetInfoAccessor,
        GetGestureRecognizerAccessor,
        GetTapRecognizerAccessor,
        GetLongPressRecognizerAccessor,
        GetSwipeRecognizerAccessor,
        GetPinchRecognizerAccessor,
        GetRotationRecognizerAccessor,
        GetPanRecognizerAccessor,
        GetImageAnalyzerControllerAccessor,
        GetListScrollerAccessor,
        GetMatrix2DAccessor,
        GetNavDestinationContextAccessor,
        GetPatternLockControllerAccessor,
        GetVirtualScrollOptionsAccessor,
        GetRichEditorBaseControllerAccessor,
        GetRichEditorControllerAccessor,
        GetRichEditorStyledStringControllerAccessor,
        GetScrollerAccessor,
        GetSearchControllerAccessor,
        GetMenuItemConfigurationAccessor,
        GetSwiperControllerAccessor,
        GetSwiperContentTransitionProxyAccessor,
        GetIndicatorComponentControllerAccessor,
        GetHierarchicalSymbolEffectAccessor,
        GetAppearSymbolEffectAccessor,
        GetDisappearSymbolEffectAccessor,
        GetBounceSymbolEffectAccessor,
        GetPulseSymbolEffectAccessor,
        GetTabsControllerAccessor,
        GetTabContentTransitionProxyAccessor,
        GetTextControllerAccessor,
        GetTextAreaControllerAccessor,
        GetTextClockControllerAccessor,
        GetTextBaseControllerAccessor,
        GetTextEditControllerExAccessor,
        GetStyledStringControllerAccessor,
        GetLayoutManagerAccessor,
        GetTextMenuItemIdAccessor,
        GetSubmitEventAccessor,
        GetTextInputControllerAccessor,
        GetTextPickerDialogAccessor,
        GetTextTimerControllerAccessor,
        GetTimePickerDialogAccessor,
        GetColorFilterAccessor,
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
        GetTextStyle_styled_stringAccessor,
        GetDecorationStyleAccessor,
        GetBaselineOffsetStyleAccessor,
        GetLetterSpacingStyleAccessor,
        GetTextShadowStyleAccessor,
        GetBackgroundColorStyleAccessor,
        GetGestureStyleAccessor,
        GetParagraphStyleAccessor,
        GetLineHeightStyleAccessor,
        GetUrlStyleAccessor,
        GetMutableStyledStringAccessor,
        GetImageAttachmentAccessor,
        GetCustomSpanAccessor,
        GetLinearIndicatorControllerAccessor,
        GetGlobalScopeAccessor,
        GetPromptActionAccessor,
        GetRouterExtenderAccessor,
    };
    return &accessorsImpl;
}
const GENERATED_ArkUIBasicNodeAPI* GENERATED_GetBasicAPI()
{
    static const GENERATED_ArkUIBasicNodeAPI basicNodeAPIImpl = {
        GENERATED_ARKUI_BASIC_NODE_API_VERSION, // version
        OHOS::Ace::NG::GeneratedBridge::CreateNode,
        OHOS::Ace::NG::GeneratedApiImpl::GetNodeByViewStack,
        OHOS::Ace::NG::GeneratedApiImpl::DisposeNode,
        OHOS::Ace::NG::GeneratedApiImpl::DumpTreeNode,
        OHOS::Ace::NG::GeneratedApiImpl::AddChild,
        OHOS::Ace::NG::GeneratedApiImpl::RemoveChild,
        OHOS::Ace::NG::GeneratedApiImpl::InsertChildAfter,
        OHOS::Ace::NG::GeneratedApiImpl::InsertChildBefore,
        OHOS::Ace::NG::GeneratedApiImpl::InsertChildAt,
        OHOS::Ace::NG::GeneratedApiImpl::ApplyModifierFinish,
        OHOS::Ace::NG::GeneratedApiImpl::MarkDirty,
        OHOS::Ace::NG::GeneratedApiImpl::IsBuilderNode,
        OHOS::Ace::NG::GeneratedApiImpl::ConvertLengthMetricsUnit
    };
    return &basicNodeAPIImpl;
}

const GENERATED_ArkUIExtendedNodeAPI* GENERATED_GetExtendedAPI()
{
    static const GENERATED_ArkUIExtendedNodeAPI extendedNodeAPIImpl = {
        GENERATED_ARKUI_EXTENDED_NODE_API_VERSION, // version
        OHOS::Ace::NG::GeneratedApiImpl::GetDensity,
        OHOS::Ace::NG::GeneratedApiImpl::GetFontScale,
        OHOS::Ace::NG::GeneratedApiImpl::GetDesignWidthScale,
        OHOS::Ace::NG::GeneratedApiImpl::SetCallbackMethod,
        OHOS::Ace::NG::GeneratedApiImpl::SetCustomMethodFlag,
        OHOS::Ace::NG::GeneratedApiImpl::GetCustomMethodFlag,
        OHOS::Ace::NG::GeneratedApiImpl::SetCustomCallback,
        OHOS::Ace::NG::GeneratedApiImpl::SetCustomNodeDestroyCallback,
        OHOS::Ace::NG::GeneratedApiImpl::MeasureLayoutAndDraw,
        OHOS::Ace::NG::GeneratedApiImpl::MeasureNode,
        OHOS::Ace::NG::GeneratedApiImpl::LayoutNode,
        OHOS::Ace::NG::GeneratedApiImpl::DrawNode,
        OHOS::Ace::NG::GeneratedApiImpl::SetAttachNodePtr,
        OHOS::Ace::NG::GeneratedApiImpl::GetAttachNodePtr,
        OHOS::Ace::NG::GeneratedApiImpl::SetMeasureWidth,
        OHOS::Ace::NG::GeneratedApiImpl::GetMeasureWidth,
        OHOS::Ace::NG::GeneratedApiImpl::SetMeasureHeight,
        OHOS::Ace::NG::GeneratedApiImpl::GetMeasureHeight,
        OHOS::Ace::NG::GeneratedApiImpl::SetX,
        OHOS::Ace::NG::GeneratedApiImpl::GetX,
        OHOS::Ace::NG::GeneratedApiImpl::SetY,
        OHOS::Ace::NG::GeneratedApiImpl::GetY,
        OHOS::Ace::NG::GeneratedApiImpl::GetLayoutConstraint,
        OHOS::Ace::NG::GeneratedApiImpl::SetAlignment,
        OHOS::Ace::NG::GeneratedApiImpl::GetAlignment,
        OHOS::Ace::NG::GeneratedApiImpl::IndexerChecker,
        OHOS::Ace::NG::GeneratedApiImpl::SetRangeUpdater,
        OHOS::Ace::NG::GeneratedApiImpl::SetLazyItemIndexer,
        OHOS::Ace::NG::GeneratedApiImpl::GetPipelineContext,
        OHOS::Ace::NG::GeneratedApiImpl::SetVsyncCallback,
        OHOS::Ace::NG::GeneratedApiImpl::SetChildTotalCount,
        OHOS::Ace::NG::GeneratedApiImpl::ShowCrash
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

EXTERN_C IDLIZE_API_EXPORT const OH_AnyAPI* GENERATED_GetArkAnyAPI(
    GENERATED_Ark_APIVariantKind kind, int version)
{
    switch (static_cast<int>(kind)) {
        case GENERATED_FULL:
            if (version == GENERATED_ARKUI_FULL_API_VERSION)   {
                return reinterpret_cast<const OH_AnyAPI*>(GENERATED_GetFullAPI());
            }
            break;
        case GENERATED_BASIC:
            if (version == GENERATED_ARKUI_BASIC_NODE_API_VERSION)   {
                return reinterpret_cast<const OH_AnyAPI*>(GENERATED_GetBasicAPI());
            }
            break;
        case GENERATED_EXTENDED:
            if (version == GENERATED_ARKUI_EXTENDED_NODE_API_VERSION)   {
                return reinterpret_cast<const OH_AnyAPI*>(GENERATED_GetExtendedAPI());
            }
            break;
        case GENERIC_SERVICE_API_KIND:
            if (version == GENERIC_SERVICE_API_VERSION)   {
                return reinterpret_cast<const OH_AnyAPI*>(GetServiceAPI());
            }
            break;
        default:
            break;
    }
    return nullptr;
}

}
