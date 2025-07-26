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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { isInstanceOf } from "@koalaui/interop"
import { isResource, isPadding } from "../../utils"
import { ArkUIGeneratedNativeModule } from "../ArkUIGeneratedNativeModule"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, TextDecorationOptions, InputCounterOptions, CaretOffset, SelectionOptions, MenuPolicy } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, TextOverflow, CopyOptions, TextAlign, TextContentStyle, BarState, WordBreak, LineBreakStrategy, TextHeightAdaptivePolicy, TextDecorationType, TextDecorationStyle } from "./../ArkEnumsInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./../ArkGestureInterfaces"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./../ArkArkuiExternalInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ICurve } from "./../ArkICurveMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./../ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { GestureControl } from "./../ArkGestureControlNamespace"
import { GestureEvent } from "./../ArkGestureEventMaterialized"
import { InputType, EnterKeyType, OnSubmitCallback, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback, TextInputStyle, PasswordIcon, UnderlineColor, TextInputAttribute, TextInputOptions } from "./../ArkTextInputInterfaces"
import { ContentType } from "./../ArkTextAreaInterfaces"
import { EditableTextOnChangeCallback, CaretStyle, InsertValue, DeleteValue, TextMenuItem, TextRange, TextDeleteDirection } from "./../ArkTextCommonInterfaces"
import { CancelButtonOptions, CancelButtonSymbolOptions, CancelButtonStyle, IconOptions } from "./../ArkSearchInterfaces"
import { EditMenuOptions } from "./../ArkEditMenuOptionsMaterialized"
import { KeyboardOptions } from "./../ArkRichEditorInterfaces"
import { TextMenuItemId } from "./../ArkTextMenuItemIdMaterialized"
import { TextInputController } from "./../ArkTextInputControllerMaterialized"
import { TextContentControllerBase } from "./../ArkTextContentControllerBaseMaterialized"
import { GestureName, GestureComponent } from "./../shared/generated-utils"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { unsafeCast } from "@koalaui/common"
import { Deserializer, createDeserializer } from "./Deserializer"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkTextInputPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextInputPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._TextInput_construct(peerId, flags)
        const _peer = new ArkTextInputPeer(_peerPtr, peerId, "TextInput", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextInputOptionsAttribute(value?: TextInputOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeTextInputOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextInputInterface_setTextInputOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    typeAttribute(value: InputType): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_type(this.peer.ptr, value)
    }
    contentTypeAttribute(value: ContentType): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_contentType(this.peer.ptr, value)
    }
    placeholderColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_placeholderColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflow): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_textOverflow(this.peer.ptr, value)
    }
    textIndentAttribute(value: Dimension): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_textIndent(this.peer.ptr, value)
    }
    placeholderFontAttribute(value?: Font): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_placeholderFont(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enterKeyTypeAttribute(value: EnterKeyType): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enterKeyType(this.peer.ptr, value)
    }
    caretColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_caretColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangedAttribute(value: ((parameter: boolean) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onEditChanged(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onEditChangeAttribute(value: ((parameter: boolean) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onEditChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onSubmitAttribute(value: OnSubmitCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onSubmit(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: EditableTextOnChangeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: OnTextSelectionChangeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentScrollAttribute(value: OnContentScrollCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onContentScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLengthAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_maxLength(this.peer.ptr, value)
    }
    fontColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_fontSize(this.peer.ptr, value)
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_fontStyle(this.peer.ptr, value)
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (5))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<FontWeight>(value)
            thisSerializer.writeInt32(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontWeight(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: ResourceStr): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_fontFamily(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onCopy(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onCutAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onCut(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onPasteAttribute(value: OnPasteCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onPaste(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_copyOption(this.peer.ptr, value)
    }
    showPasswordIconAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_showPasswordIcon(this.peer.ptr, +value)
    }
    textAlignAttribute(value: TextAlign): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_textAlign(this.peer.ptr, value)
    }
    styleAttribute(value: TextInputStyle | TextContentStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (1))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<TextInputStyle>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (1))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<TextContentStyle>(value)
            thisSerializer.writeInt32(value_1)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_style(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    caretStyleAttribute(value: CaretStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCaretStyle(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_caretStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    caretPositionAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_caretPosition(this.peer.ptr, value)
    }
    enableKeyboardOnFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enableKeyboardOnFocus(this.peer.ptr, +value)
    }
    passwordIconAttribute(value: PasswordIcon): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePasswordIcon(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_passwordIcon(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    showErrorAttribute(value?: ResourceStr): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            let value_value_type: int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0 = unsafeCast<string>(value_value)
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1 = unsafeCast<Resource>(value_value)
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_showError(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    showUnitAttribute(value: CustomBuilder): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._TextInputAttribute_showUnit(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    showUnderlineAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_showUnderline(this.peer.ptr, +value)
    }
    underlineColorAttribute(value?: ResourceColor | UnderlineColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            let value_value_type: int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((((RuntimeType.NUMBER) == (value_value_type)) && ((unsafeCast<int32>(value_value)) >= (0)) && ((unsafeCast<int32>(value_value)) <= (11))) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0 = unsafeCast<ResourceColor>(value_value)
                let value_value_0_type: int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (((RuntimeType.NUMBER) == (value_value_0_type)) && ((unsafeCast<int32>(value_value_0)) >= (0)) && ((unsafeCast<int32>(value_value_0)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0 = unsafeCast<Color>(value_value_0)
                    thisSerializer.writeInt32(value_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1 = unsafeCast<number>(value_value_0)
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_0_2 = unsafeCast<string>(value_value_0)
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3)
                    const value_value_0_3 = unsafeCast<Resource>(value_value_0)
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (((value_value!.hasOwnProperty("typing")) || (value_value!.hasOwnProperty("normal")) || (value_value!.hasOwnProperty("error")) || (value_value!.hasOwnProperty("disable"))))) {
                thisSerializer.writeInt8(1)
                const value_value_1 = unsafeCast<UnderlineColor>(value_value)
                thisSerializer.writeUnderlineColor(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_underlineColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionMenuHiddenAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_selectionMenuHidden(this.peer.ptr, +value)
    }
    barStateAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_barState(this.peer.ptr, value)
    }
    maxLinesAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_maxLines(this.peer.ptr, value)
    }
    wordBreakAttribute(value: WordBreak): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_wordBreak(this.peer.ptr, value)
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_lineBreakStrategy(this.peer.ptr, value)
    }
    cancelButton0Attribute(value: CancelButtonOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCancelButtonOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_cancelButton0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    cancelButton1Attribute(value: CancelButtonSymbolOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCancelButtonSymbolOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_cancelButton1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    selectAllAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_selectAll(this.peer.ptr, +value)
    }
    minFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_minFontSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_maxFontSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_heightAdaptivePolicy(this.peer.ptr, value)
    }
    enableAutoFillAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enableAutoFill(this.peer.ptr, +value)
    }
    decorationAttribute(value: TextDecorationOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeTextDecorationOptions(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_decoration(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_letterSpacing(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    lineHeightAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_lineHeight(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    passwordRulesAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_passwordRules(this.peer.ptr, value)
    }
    fontFeatureAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_fontFeature(this.peer.ptr, value)
    }
    showPasswordAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_showPassword(this.peer.ptr, +value)
    }
    onSecurityStateChangeAttribute(value: ((parameter: boolean) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onSecurityStateChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillInsertAttribute(value: ((parameter: InsertValue) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onWillInsert(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidInsertAttribute(value: ((parameter: InsertValue) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onDidInsert(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDeleteAttribute(value: ((parameter: DeleteValue) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onWillDelete(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidDeleteAttribute(value: ((parameter: DeleteValue) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextInputAttribute_onDidDelete(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_editMenuOptions(this.peer.ptr, toPeerPtr(value))
    }
    enablePreviewTextAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enablePreviewText(this.peer.ptr, +value)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextInputAttribute_enableHapticFeedback(this.peer.ptr, +value)
    }
    inputFilterAttribute(value: ResourceStr, error?: ((breakpoints: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        let error_type: int32 = RuntimeType.UNDEFINED
        error_type = runtimeType(error)
        thisSerializer.writeInt8(error_type)
        if ((RuntimeType.UNDEFINED) != (error_type)) {
            const error_value = error!
            thisSerializer.holdAndWriteCallback(error_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_inputFilter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    customKeyboardAttribute(value: CustomBuilder, options?: KeyboardOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeKeyboardOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_customKeyboard(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    showCounterAttribute(value: boolean, options?: InputCounterOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeInputCounterOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextInputAttribute_showCounter(this.peer.ptr, +value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_textAttribute(callback: ((value: ResourceStr) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TextInputAttribute__onChangeEvent_text(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkTextInputAttributes extends ArkCommonMethodAttributes {
    type?: InputType
    contentType?: ContentType
    placeholderColor?: ResourceColor
    textOverflow?: TextOverflow
    textIndent?: Dimension
    placeholderFont?: Font
    enterKeyType?: EnterKeyType
    caretColor?: ResourceColor
    onEditChanged?: ((parameter: boolean) => void)
    onEditChange?: ((parameter: boolean) => void)
    onSubmit?: OnSubmitCallback
    onChange?: EditableTextOnChangeCallback
    onTextSelectionChange?: OnTextSelectionChangeCallback
    onContentScroll?: OnContentScrollCallback
    maxLength?: number
    fontColor?: ResourceColor
    fontSize?: Length
    fontStyle?: FontStyle
    fontWeight?: number | FontWeight | string
    fontFamily?: ResourceStr
    onCopy?: ((breakpoints: string) => void)
    onCut?: ((breakpoints: string) => void)
    onPaste?: OnPasteCallback
    copyOption?: CopyOptions
    showPasswordIcon?: boolean
    textAlign?: TextAlign
    style?: TextInputStyle | TextContentStyle
    caretStyle?: CaretStyle
    selectedBackgroundColor?: ResourceColor
    caretPosition?: number
    enableKeyboardOnFocus?: boolean
    passwordIcon?: PasswordIcon
    showError?: ResourceStr | undefined
    showUnit?: CustomBuilder
    showUnderline?: boolean
    underlineColor?: ResourceColor | UnderlineColor | undefined
    selectionMenuHidden?: boolean
    barState?: BarState
    maxLines?: number
    wordBreak?: WordBreak
    lineBreakStrategy?: LineBreakStrategy
    cancelButton?: CancelButtonOptions
    selectAll?: boolean
    minFontSize?: number | string | Resource
    maxFontSize?: number | string | Resource
    heightAdaptivePolicy?: TextHeightAdaptivePolicy
    enableAutoFill?: boolean
    decoration?: TextDecorationOptions
    letterSpacing?: number | string | Resource
    lineHeight?: number | string | Resource
    passwordRules?: string
    fontFeature?: string
    showPassword?: boolean
    onSecurityStateChange?: ((parameter: boolean) => void)
    onWillInsert?: ((parameter: InsertValue) => boolean)
    onDidInsert?: ((parameter: InsertValue) => void)
    onWillDelete?: ((parameter: DeleteValue) => boolean)
    onDidDelete?: ((parameter: DeleteValue) => void)
    editMenuOptions?: EditMenuOptions
    enablePreviewText?: boolean
    enableHapticFeedback?: boolean
}
