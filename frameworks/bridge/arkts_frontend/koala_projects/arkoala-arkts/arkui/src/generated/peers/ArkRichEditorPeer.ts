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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "./../../ComponentBase"
import { PeerNode } from "./../../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, CopyOptions, BarState } from "./../ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_RichEditorSelection_Void, Callback_RichEditorRange_Void, Callback_RichEditorInsertValue_Boolean, Callback_RichEditorTextSpanResult_Void, Callback_TextRange_Void, Callback_RichEditorDeleteValue_Boolean, Callback_Boolean_Void, Callback_RichEditorChangeValue_Boolean, Callback_CutEvent_Void, Callback_CopyEvent_Void } from "./../SyntheticDeclarations"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./../ArkGestureInterfaces"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { RichEditorSelection, RichEditorRange, RichEditorInsertValue, RichEditorTextSpanResult, RichEditorDeleteValue, PasteEventCallback, SubmitCallback, RichEditorChangeValue, CutEvent, CopyEvent, RichEditorSpanType, RichEditorResponseType, SelectionMenuOptions, RichEditorAttribute, KeyboardOptions, PlaceholderStyle, RichEditorOptions, RichEditorStyledStringOptions } from "./../ArkRichEditorInterfaces"
import { TextRange, TextDataDetectorConfig, OnDidChangeCallback } from "./../ArkTextCommonInterfaces"
import { EnterKeyType } from "./../ArkTextInputInterfaces"
import { EditMenuOptions } from "./../ArkEditMenuOptionsMaterialized"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkRichEditorPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRichEditorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichEditor_construct(peerId, flags)
        const _peer  = new ArkRichEditorPeer(_peerPtr, peerId, "RichEditor", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichEditorOptions0Attribute(value: RichEditorOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorOptions(value)
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRichEditorOptions1Attribute(options: RichEditorStyledStringOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRichEditorStyledStringOptions(options)
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: ((parameter: RichEditorSelection) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectionChangeAttribute(value: ((parameter: RichEditorRange) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToIMEInputAttribute(value: ((parameter: RichEditorInsertValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_aboutToIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onIMEInputCompleteAttribute(value: ((parameter: RichEditorTextSpanResult) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onIMEInputComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidIMEInputAttribute(value: ((parameter: TextRange) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDidIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    aboutToDeleteAttribute(value: ((parameter: RichEditorDeleteValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_aboutToDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDeleteCompleteAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDeleteComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionsAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_copyOptions(this.peer.ptr, value.valueOf())
    }
    onPasteAttribute(value: PasteEventCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDataDetectorAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableDataDetector(this.peer.ptr, value ? 1 : 0)
    }
    enablePreviewTextAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_enablePreviewText(this.peer.ptr, value ? 1 : 0)
    }
    dataDetectorConfigAttribute(value: TextDataDetectorConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextDataDetectorConfig(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_dataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditingChangeAttribute(value: ((parameter: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onEditingChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_enterKeyType(this.peer.ptr, value.valueOf())
    }
    onSubmitAttribute(value: SubmitCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillChangeAttribute(value: ((parameter: RichEditorChangeValue) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidChangeAttribute(value: OnDidChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onDidChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((parameter: CutEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((parameter: CopyEvent) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._RichEditorAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_editMenuOptions(this.peer.ptr, toPeerPtr(value))
    }
    enableKeyboardOnFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableKeyboardOnFocus(this.peer.ptr, value ? 1 : 0)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    barStateAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._RichEditorAttribute_barState(this.peer.ptr, value.valueOf())
    }
    bindSelectionMenuAttribute(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType | RichEditorResponseType, options?: SelectionMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        if (TypeChecker.isResponseType(responseType)) {
            thisSerializer.writeInt8(0 as int32)
            const responseType_0  = responseType as ResponseType
            thisSerializer.writeInt32(responseType_0.valueOf())
        }
        else if (TypeChecker.isRichEditorResponseType(responseType)) {
            thisSerializer.writeInt8(1 as int32)
            const responseType_1  = responseType as RichEditorResponseType
            thisSerializer.writeInt32(responseType_1.valueOf())
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_bindSelectionMenu(this.peer.ptr, spanType.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customKeyboardAttribute(value: CustomBuilder, options?: KeyboardOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeKeyboardOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_customKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    placeholderAttribute(value: ResourceStr, style?: PlaceholderStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = style!
            thisSerializer.writePlaceholderStyle(style_value)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_placeholder(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkRichEditorAttributes extends ArkCommonMethodAttributes {
    onReady?: (() => void)
    onSelect?: ((parameter: RichEditorSelection) => void)
    onSelectionChange?: ((parameter: RichEditorRange) => void)
    aboutToIMEInput?: ((parameter: RichEditorInsertValue) => boolean)
    onIMEInputComplete?: ((parameter: RichEditorTextSpanResult) => void)
    onDidIMEInput?: ((parameter: TextRange) => void)
    aboutToDelete?: ((parameter: RichEditorDeleteValue) => boolean)
    onDeleteComplete?: (() => void)
    copyOptions?: CopyOptions
    onPaste?: PasteEventCallback
    enableDataDetector?: boolean
    enablePreviewText?: boolean
    dataDetectorConfig?: TextDataDetectorConfig
    caretColor?: ResourceColor
    selectedBackgroundColor?: ResourceColor
    onEditingChange?: ((parameter: boolean) => void)
    enterKeyType?: EnterKeyType
    onSubmit?: SubmitCallback
    onWillChange?: ((parameter: RichEditorChangeValue) => boolean)
    onDidChange?: OnDidChangeCallback
    onCut?: ((parameter: CutEvent) => void)
    onCopy?: ((parameter: CopyEvent) => void)
    editMenuOptions?: EditMenuOptions
    enableKeyboardOnFocus?: boolean
    enableHapticFeedback?: boolean
    barState?: BarState
}
