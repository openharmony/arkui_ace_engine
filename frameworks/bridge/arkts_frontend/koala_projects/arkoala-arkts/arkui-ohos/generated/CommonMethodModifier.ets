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

import { AttributeModifier, TouchTestInfo, TouchResult, extractors, hookAllowDrop, hookDragPreviewOptions, hookCommonMethodModifierCustomProperty, hookCustomPropertyImpl, hookKeyboardShortcut, hookMergeKeyboardShortcuts, KeyboardShortcut } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkCommonMethodPeer, LayoutPolicy, Rectangle, ResponseRegion, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, BorderImageOption, OutlineStyle, ClickEvent, HoverEvent, AccessibilityCallback, AccessibilityHoverEvent, AccessibilityTransparentCallback, TouchEvent, MouseEvent, KeyEvent, CrownEvent, FocusAxisEvent, AxisEvent, FocusMovement, AnimateParam, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, RotateAngleOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, DragEvent, DragItemInfo, PreDragStatus, LinearGradientOptions, SweepGradientOptions, RadialGradientOptions, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, PixelStretchEffectOptions, AccessibilitySamePageMode, AccessibilityRoleType, AccessibilityFocusCallback, AccessibilityActionInterceptCallback, AccessibilityAction, ReuseOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, CustomProperty, SafeAreaType, SafeAreaEdge, LayoutSafeAreaType, LayoutSafeAreaEdge, BackgroundOptions, BackgroundImageOptions, BlurStyle, BackgroundBlurStyleOptions, SystemAdaptiveOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, OnDragEventCallback, DropOptions, PreviewConfiguration, DragPreviewOptions, DragInteractionOptions, OverlayOptions, BlendMode, BlendApplyType, GeometryTransitionOptions, TipsMessageType, TipsOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, Bindable, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, VisibleAreaEventOptions, CommonMethod } from "./component/common"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, ResourceColor, ResourceStr, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, VoidCallback, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityActionOptions, AccessibilityOptions } from "./component/units"
import { Resource } from "global.resource"
import { HitTestMode, Color, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Visibility, ItemAlign, LocalizedAlignment, Direction, ObscuredReasons, RenderFit, FocusDrawLevel, ImageRepeat, RenderStrategy, Axis, ResponseType, FunctionKey, ModifierKey } from "./component/enums"
import { LengthMetrics, ColorMetrics } from "arkui.Graphics"
import { default as image } from "@ohos.multimedia.image"
import { ResizableOptions } from "./component/image"
import { default as uiEffect } from "@ohos.graphics.uiEffect"
import { FocusBoxStyle, FocusPriority } from "./component/focus"
import { default as matrix4 } from "@ohos.matrix4"
import { CustomBuilder, CustomBuilderT } from "./component/builder"
import { default as uniformTypeDescriptor } from "@ohos.data.uniformTypeDescriptor"
import { CircleShape, EllipseShape, PathShape, RectShape } from "@ohos.arkui.shape"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer } from "./component/gesture"
import { default as uiMaterial } from "@ohos.arkui.uiMaterial"
import { ComponentContent } from "arkui.ComponentContent"
import { StyledString } from "./component/styledString"
export class CommonMethodModifier implements CommonMethod {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    _width_0_0value?: Length | LayoutPolicy | undefined
    _height_0_0value?: Length | LayoutPolicy | undefined
    _responseRegion_0_0value?: Array<Rectangle> | Rectangle | undefined
    _mouseResponseRegion_0_0value?: Array<Rectangle> | Rectangle | undefined
    _responseRegionList_0_0value?: Array<ResponseRegion> | undefined
    _size_0_0value?: SizeOptions | undefined
    _constraintSize_0_0value?: ConstraintSizeOptions | undefined
    _hitTestBehavior_0_0value?: HitTestMode | undefined
    _onChildTouchTest_0_0value?: ((value: Array<TouchTestInfo>) => TouchResult) | undefined
    _layoutWeight_0_0value?: number | string | undefined
    _chainWeight_0_0value?: ChainWeightOptions | undefined
    _padding_0_0value?: Padding | Length | LocalizedPadding | undefined
    _safeAreaPadding_0_0value?: Padding | LengthMetrics | LocalizedPadding | undefined
    _margin_0_0value?: Padding | Length | LocalizedPadding | undefined
    _backgroundColor_0_0value?: ResourceColor | ColorMetrics | undefined
    _pixelRound_0_0value?: PixelRoundPolicy | undefined
    _backgroundImage_0_0value?: ResourceStr | image.PixelMap | undefined
    _backgroundImageSize_0_0value?: SizeOptions | ImageSize | undefined
    _backgroundImagePosition_0_0value?: Position | Alignment | undefined
    _backgroundEffect_0_0value?: BackgroundEffectOptions | undefined
    _backgroundImageResizable_0_0value?: ResizableOptions | undefined
    _foregroundEffect_0_0value?: ForegroundEffectOptions | undefined
    _visualEffect_0_0value?: uiEffect.VisualEffect | undefined
    _backgroundFilter_0_0value?: uiEffect.Filter | undefined
    _foregroundFilter_0_0value?: uiEffect.Filter | undefined
    _compositingFilter_0_0value?: uiEffect.Filter | undefined
    _materialFilter_0_0value?: uiEffect.Filter | undefined
    _opacity_0_0value?: double | Resource | undefined
    _border_0_0value?: BorderOptions | undefined
    _borderStyle_0_0value?: BorderStyle | EdgeStyles | undefined
    _borderWidth_0_0value?: Length | EdgeWidths | LocalizedEdgeWidths | undefined
    _borderColor_0_0value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
    _borderRadius_0_0value?: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined
    _borderImage_0_0value?: BorderImageOption | undefined
    _outline_0_0value?: OutlineOptions | undefined
    _outlineStyle_0_0value?: OutlineStyle | EdgeOutlineStyles | undefined
    _outlineWidth_0_0value?: Dimension | EdgeOutlineWidths | undefined
    _outlineColor_0_0value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
    _outlineRadius_0_0value?: Dimension | OutlineRadiuses | undefined
    _foregroundColor_0_0value?: ResourceColor | ColoringStrategy | undefined
    _onClick_0_0value?: ((event: ClickEvent) => void) | undefined
    _onHover_0_0value?: ((isHover: boolean,event: HoverEvent) => void) | undefined
    _onHoverMove_0_0value?: ((value0: HoverEvent) => void) | undefined
    _onAccessibilityHover_0_0value?: AccessibilityCallback | undefined
    _onAccessibilityHoverTransparent_0_0value?: AccessibilityTransparentCallback | undefined
    _hoverEffect_0_0value?: HoverEffect | undefined
    _onMouse_0_0value?: ((event: MouseEvent) => void) | undefined
    _onTouch_0_0value?: ((event: TouchEvent) => void) | undefined
    _onKeyEvent_0_0value?: ((value0: KeyEvent) => boolean) | undefined
    _onDigitalCrown_0_0value?: ((value0: CrownEvent) => void) | undefined
    _onKeyPreIme_0_0value?: ((value0: KeyEvent) => boolean) | undefined
    _onKeyEventDispatch_0_0value?: ((value0: KeyEvent) => boolean) | undefined
    _onFocusAxisEvent_0_0value?: ((value0: FocusAxisEvent) => void) | undefined
    _onAxisEvent_0_0value?: ((value0: AxisEvent) => void) | undefined
    _focusable_0_0value?: boolean | undefined
    _nextFocus_0_0value?: FocusMovement | undefined
    _tabStop_0_0value?: boolean | undefined
    _onFocus_0_0value?: (() => void) | undefined
    _onBlur_0_0value?: (() => void) | undefined
    _tabIndex_0_0value?: int32 | undefined
    _defaultFocus_0_0value?: boolean | undefined
    _groupDefaultFocus_0_0value?: boolean | undefined
    _focusOnTouch_0_0value?: boolean | undefined
    _focusBox_0_0value?: FocusBoxStyle | undefined
    _animation_0_0value?: AnimateParam | undefined
    _transition_0_0value?: TransitionEffect | undefined
    _motionBlur_0_0value?: MotionBlurOptions | undefined
    _brightness_0_0value?: double | undefined
    _contrast_0_0value?: double | undefined
    _grayscale_0_0value?: double | undefined
    _colorBlend_0_0value?: Color | string | Resource | undefined
    _saturate_0_0value?: double | undefined
    _sepia_0_0value?: double | undefined
    _invert_0_0value?: double | InvertOptions | undefined
    _hueRotate_0_0value?: double | string | undefined
    _useShadowBatching_0_0value?: boolean | undefined
    _useEffect_0_0value?: boolean | undefined
    _useUnionEffect_0_0value?: boolean | undefined
    _renderGroup_0_0value?: boolean | undefined
    _freeze_0_0value?: boolean | undefined
    _translate_0_0value?: TranslateOptions | undefined
    _scale_0_0value?: ScaleOptions | undefined
    _rotate_0_0value?: RotateOptions | RotateAngleOptions | undefined
    _transform_0_0value?: matrix4.Matrix4Transit | undefined
    _transform3D_0_0value?: matrix4.Matrix4Transit | undefined
    _onAppear_0_0value?: (() => void) | undefined
    _onDisAppear_0_0value?: (() => void) | undefined
    _onAttach_0_0value?: VoidCallback | undefined
    _onDetach_0_0value?: VoidCallback | undefined
    _onAreaChange_0_0value?: ((oldValue: Area,newValue: Area) => void) | undefined
    _visibility_0_0value?: Visibility | undefined
    _flexGrow_0_0value?: number | undefined
    _flexShrink_0_0value?: number | undefined
    _flexBasis_0_0value?: number | string | undefined
    _alignSelf_0_0value?: ItemAlign | undefined
    _layoutGravity_0_0value?: LocalizedAlignment | undefined
    _displayPriority_0_0value?: number | undefined
    _zIndex_0_0value?: int32 | undefined
    _direction_0_0value?: Direction | undefined
    _align_0_0value?: Alignment | LocalizedAlignment | undefined
    _position_0_0value?: Position | Edges | LocalizedEdges | undefined
    _markAnchor_0_0value?: Position | LocalizedPosition | undefined
    _offset_0_0value?: Position | Edges | LocalizedEdges | undefined
    _enabled_0_0value?: boolean | undefined
    _alignRules_0_0value?: AlignRuleOption | LocalizedAlignRuleOptions | undefined
    _aspectRatio_0_0value?: number | undefined
    _clickEffect_0_0value?: ClickEffect | null | undefined
    _onDragStart_0_0value?: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined
    _onDragEnter_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDragMove_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDragLeave_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDrop_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDragEnd_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _allowDrop_0_0value?: Array<uniformTypeDescriptor.UniformDataType> | Array<string> | null | undefined
    _draggable_0_0value?: boolean | undefined
    _dragPreview_0_0value?: CustomBuilder | DragItemInfo | string | undefined
    _onPreDrag_0_0value?: ((value0: PreDragStatus) => void) | undefined
    _linearGradient_0_0value?: LinearGradientOptions | undefined
    _sweepGradient_0_0value?: SweepGradientOptions | undefined
    _radialGradient_0_0value?: RadialGradientOptions | undefined
    _motionPath_0_0value?: MotionPathOptions | undefined
    _shadow_0_0value?: ShadowOptions | ShadowStyle | undefined
    _clip_0_0value?: boolean | undefined
    _clipShape_0_0value?: CircleShape | EllipseShape | PathShape | RectShape | undefined
    _mask_0_0value?: ProgressMask | undefined
    _maskShape_0_0value?: CircleShape | EllipseShape | PathShape | RectShape | undefined
    _key_0_0value?: string | undefined
    _id_0_0value?: string | undefined
    _geometryTransition_0_0value?: string | undefined
    _restoreId_0_0value?: int32 | undefined
    _sphericalEffect_0_0value?: double | undefined
    _lightUpEffect_0_0value?: double | undefined
    _pixelStretchEffect_0_0value?: PixelStretchEffectOptions | undefined
    _accessibilityGroup_0_0value?: boolean | undefined
    _accessibilityTextOfStringType_0_0value?: string | undefined
    _accessibilityNextFocusId_0_0value?: string | undefined
    _accessibilityDefaultFocus_0_0value?: boolean | undefined
    _accessibilityUseSamePage_0_0value?: AccessibilitySamePageMode | undefined
    _accessibilityScrollTriggerable_0_0value?: boolean | undefined
    _accessibilityTextOfResourceType_0_0value?: Resource | undefined
    _accessibilityRole_0_0value?: AccessibilityRoleType | undefined
    _onAccessibilityFocus_0_0value?: AccessibilityFocusCallback | undefined
    _onAccessibilityActionIntercept_0_0value?: AccessibilityActionInterceptCallback | undefined
    _accessibilityTextHint_0_0value?: string | undefined
    _accessibilityDescriptionOfStringType_0_0value?: string | undefined
    _accessibilityDescriptionOfResourceType_0_0value?: Resource | undefined
    _accessibilityLevel_0_0value?: string | undefined
    _accessibilityVirtualNode_0_0value?: CustomBuilder | undefined
    _accessibilityChecked_0_0value?: boolean | undefined
    _accessibilitySelected_0_0value?: boolean | undefined
    _obscured_0_0value?: Array<ObscuredReasons> | undefined
    _reuseId_0_0value?: string | undefined
    _reuse_0_0value?: ReuseOptions | undefined
    _renderFit_0_0value?: RenderFit | undefined
    _backgroundBrightness_0_0value?: BackgroundBrightnessOptions | undefined
    _onGestureJudgeBegin_0_0value?: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined
    _onGestureRecognizerJudgeBegin_0_0value?: GestureRecognizerJudgeBeginCallback | undefined
    _shouldBuiltInRecognizerParallelWith_0_0value?: ShouldBuiltInRecognizerParallelWithCallback | undefined
    _monopolizeEvents_0_0value?: boolean | undefined
    _onTouchIntercept_0_0value?: ((value0: TouchEvent) => HitTestMode) | undefined
    _onSizeChange_0_0value?: SizeChangeCallback | undefined
    _accessibilityFocusDrawLevel_0_0value?: FocusDrawLevel | undefined
    _systemMaterial_0_0value?: uiMaterial.Material | undefined
    _accessibilityStateDescription_0_0value?: string | Resource | undefined
    _accessibilityActionOptions_0_0value?: AccessibilityActionOptions | undefined
    _customProperty_0_0value?: string
    _customProperty_0_1value?: CustomProperty
    _expandSafeArea_0_0value?: Array<SafeAreaType> | undefined
    _expandSafeArea_0_1value?: Array<SafeAreaEdge> | undefined
    _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    _background_0_0value?: CustomBuilder | undefined
    _background_0_1value?: BackgroundOptions | undefined
    _backgroundImage_1_0value?: ResourceStr | image.PixelMap | undefined
    _backgroundImage_1_1value?: BackgroundImageOptions
    _backgroundImage_2_0value?: ResourceStr | image.PixelMap | undefined
    _backgroundImage_2_1value?: ImageRepeat
    _backgroundBlurStyle_0_0value?: BlurStyle | undefined
    _backgroundBlurStyle_0_1value?: BackgroundBlurStyleOptions | undefined
    _backgroundBlurStyle_0_2value?: SystemAdaptiveOptions | undefined
    _backgroundEffect_1_0value?: BackgroundEffectOptions | undefined
    _backgroundEffect_1_1value?: SystemAdaptiveOptions | undefined
    _foregroundBlurStyle_0_0value?: BlurStyle | undefined
    _foregroundBlurStyle_0_1value?: ForegroundBlurStyleOptions | undefined
    _foregroundBlurStyle_0_2value?: SystemAdaptiveOptions | undefined
    _borderRadius_1_0value?: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined
    _borderRadius_1_1value?: RenderStrategy | undefined
    _onClick_1_0value?: ((event: ClickEvent) => void) | undefined
    _onClick_1_1value?: double | undefined
    _focusScopeId_0_0value?: string | undefined
    _focusScopeId_0_1value?: boolean | undefined
    _focusScopeId_0_2value?: boolean | undefined
    _focusScopePriority_0_0value?: string | undefined
    _focusScopePriority_0_1value?: FocusPriority | undefined
    _transition_1_0value?: TransitionEffect | undefined
    _transition_1_1value?: TransitionFinishCallback | undefined
    _blur_0_0value?: double | undefined
    _blur_0_1value?: BlurOptions | undefined
    _blur_0_2value?: SystemAdaptiveOptions | undefined
    _linearGradientBlur_0_0value?: double | undefined
    _linearGradientBlur_0_1value?: LinearGradientBlurOptions | undefined
    _useEffect_1_0value?: boolean | undefined
    _useEffect_1_1value?: EffectType | undefined
    _backdropBlur_0_0value?: double | undefined
    _backdropBlur_0_1value?: BlurOptions | undefined
    _backdropBlur_0_2value?: SystemAdaptiveOptions | undefined
    _sharedTransition_0_0value?: string | undefined
    _sharedTransition_0_1value?: sharedTransitionOptions | undefined
    _chainMode_0_0value?: Axis | undefined
    _chainMode_0_1value?: ChainStyle | undefined
    _onDrop_1_0value?: OnDragEventCallback | undefined
    _onDrop_1_1value?: DropOptions | undefined
    _dragPreview_1_0value?: CustomBuilder | DragItemInfo | string | undefined
    _dragPreview_1_1value?: PreviewConfiguration | undefined
    _dragPreviewOptions_0_0value?: DragPreviewOptions | undefined
    _dragPreviewOptions_0_1value?: DragInteractionOptions | undefined
    _overlay_0_0value?: string | CustomBuilder | ComponentContent | undefined
    _overlay_0_1value?: OverlayOptions | undefined
    _blendMode_0_0value?: BlendMode | undefined
    _blendMode_0_1value?: BlendApplyType | undefined
    _advancedBlendMode_0_0value?: BlendMode | uiEffect.Blender | undefined
    _advancedBlendMode_0_1value?: BlendApplyType | undefined
    _geometryTransition_1_0value?: string | undefined
    _geometryTransition_1_1value?: GeometryTransitionOptions | undefined
    _bindTips_0_0value?: TipsMessageType | undefined
    _bindTips_0_1value?: TipsOptions | undefined
    _bindPopup_0_0value?: boolean | undefined
    _bindPopup_0_1value?: PopupOptions | CustomPopupOptions | undefined
    _bindMenu_0_0value?: Array<MenuElement> | CustomBuilder | undefined
    _bindMenu_0_1value?: MenuOptions | undefined
    _bindMenu_1_0value?: boolean | undefined
    _bindMenu_1_1value?: Array<MenuElement> | CustomBuilder | undefined
    _bindMenu_1_2value?: MenuOptions | undefined
    _bindContextMenu_0_0value?: CustomBuilder | undefined
    _bindContextMenu_0_1value?: ResponseType | undefined
    _bindContextMenu_0_2value?: ContextMenuOptions | undefined
    _bindContextMenuWithResponse_0_0value?: CustomBuilderT<ResponseType> | undefined
    _bindContextMenuWithResponse_0_1value?: ContextMenuOptions | undefined
    _bindContextMenu_1_0value?: boolean | undefined
    _bindContextMenu_1_1value?: CustomBuilder | undefined
    _bindContextMenu_1_2value?: ContextMenuOptions | undefined
    _bindContentCover_0_0value?: boolean | Bindable<boolean> | undefined
    _bindContentCover_0_1value?: CustomBuilder | undefined
    _bindContentCover_0_2value?: ModalTransition | undefined
    _bindContentCover_1_0value?: boolean | Bindable<boolean> | undefined
    _bindContentCover_1_1value?: CustomBuilder | undefined
    _bindContentCover_1_2value?: ContentCoverOptions | undefined
    _bindSheet_0_0value?: boolean | Bindable<boolean> | undefined
    _bindSheet_0_1value?: CustomBuilder | undefined
    _bindSheet_0_2value?: SheetOptions | undefined
    _onVisibleAreaChange_0_0value?: Array<double> | undefined
    _onVisibleAreaChange_0_1value?: VisibleAreaChangeCallback | undefined
    _onVisibleAreaApproximateChange_0_0value?: VisibleAreaEventOptions | undefined
    _onVisibleAreaApproximateChange_0_1value?: VisibleAreaChangeCallback | undefined
    _keyboardShortcut_0_0value?: string | FunctionKey | undefined
    _keyboardShortcut_0_1value?: Array<ModifierKey> | undefined
    _keyboardShortcut_0_2value?: (() => void) | undefined
    _keyboardShortcutList: Array<KeyboardShortcut> = []
    _accessibilityGroup_1_0value?: boolean | undefined
    _accessibilityGroup_1_1value?: AccessibilityOptions | undefined
    _onGestureRecognizerJudgeBegin_1_0value?: GestureRecognizerJudgeBeginCallback | undefined
    _onGestureRecognizerJudgeBegin_1_1value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        const peer = node as ArkCommonMethodPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
        this.applyModifierPatch1(peer, flagArray);
        this.applyModifierPatch2(peer, flagArray);
        this.applyModifierPatch3(peer, flagArray);
        this.applyModifierPatch4(peer, flagArray);
        this.applyModifierPatch5(peer, flagArray);
        this.applyModifierPatch6(peer, flagArray);
        this.applyModifierPatch7(peer, flagArray);
        this.applyModifierPatch8(peer, flagArray);
        this.applyModifierPatch9(peer, flagArray);
        this.applyModifierPatch10(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0)
        {
            switch (flagArray[0] as int32) {
                case 1: {
                    peer.setWidthAttribute((this._width_0_0value as Length | LayoutPolicy | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setWidthAttribute((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (flagArray[1] != 0)
        {
            switch (flagArray[1] as int32) {
                case 1: {
                    peer.setHeightAttribute((this._height_0_0value as Length | LayoutPolicy | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setHeightAttribute((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (flagArray[2] != 0)
        {
            switch (flagArray[2] as int32) {
                case 1: {
                    peer.setResponseRegionAttribute((this._responseRegion_0_0value as Array<Rectangle> | Rectangle | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setResponseRegionAttribute((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (flagArray[3] != 0)
        {
            switch (flagArray[3] as int32) {
                case 1: {
                    peer.setMouseResponseRegionAttribute((this._mouseResponseRegion_0_0value as Array<Rectangle> | Rectangle | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setMouseResponseRegionAttribute((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (flagArray[4] != 0)
        {
            switch (flagArray[4] as int32) {
                case 1: {
                    peer.setResponseRegionListAttribute((this._responseRegionList_0_0value as Array<ResponseRegion> | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setResponseRegionListAttribute((undefined as Array<ResponseRegion> | undefined));
                }
            }
        }
        if (flagArray[5] != 0)
        {
            switch (flagArray[5] as int32) {
                case 1: {
                    peer.setSizeAttribute((this._size_0_0value as SizeOptions | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (flagArray[6] != 0)
        {
            switch (flagArray[6] as int32) {
                case 1: {
                    peer.setConstraintSizeAttribute((this._constraintSize_0_0value as ConstraintSizeOptions | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setConstraintSizeAttribute((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (flagArray[7] != 0)
        {
            switch (flagArray[7] as int32) {
                case 1: {
                    peer.setHitTestBehaviorAttribute((this._hitTestBehavior_0_0value as HitTestMode | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setHitTestBehaviorAttribute((undefined as HitTestMode | undefined));
                }
            }
        }
        if (flagArray[8] != 0)
        {
            switch (flagArray[8] as int32) {
                case 1: {
                    peer.setOnChildTouchTestAttribute((this._onChildTouchTest_0_0value as ((value: Array<TouchTestInfo>) => TouchResult) | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnChildTouchTestAttribute((undefined as ((value: Array<TouchTestInfo>) => TouchResult) | undefined));
                }
            }
        }
        if (flagArray[9] != 0)
        {
            switch (flagArray[9] as int32) {
                case 1: {
                    peer.setLayoutWeightAttribute((this._layoutWeight_0_0value as number | string | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setLayoutWeightAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (flagArray[10] != 0)
        {
            switch (flagArray[10] as int32) {
                case 1: {
                    peer.setChainWeightAttribute((this._chainWeight_0_0value as ChainWeightOptions | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setChainWeightAttribute((undefined as ChainWeightOptions | undefined));
                }
            }
        }
        if (flagArray[11] != 0)
        {
            switch (flagArray[11] as int32) {
                case 1: {
                    peer.setPaddingAttribute((this._padding_0_0value as Padding | Length | LocalizedPadding | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setPaddingAttribute((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (flagArray[12] != 0)
        {
            switch (flagArray[12] as int32) {
                case 1: {
                    peer.setSafeAreaPaddingAttribute((this._safeAreaPadding_0_0value as Padding | LengthMetrics | LocalizedPadding | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setSafeAreaPaddingAttribute((undefined as Padding | LengthMetrics | LocalizedPadding | undefined));
                }
            }
        }
        if (flagArray[13] != 0)
        {
            switch (flagArray[13] as int32) {
                case 1: {
                    peer.setMarginAttribute((this._margin_0_0value as Padding | Length | LocalizedPadding | undefined));
                    flagArray[13] = 2;
                    break;
                }
                case 3: {
                    flagArray[13] = 2;
                    break;
                }
                default: {
                    flagArray[13] = 0;
                    peer.setMarginAttribute((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (flagArray[14] != 0)
        {
            switch (flagArray[14] as int32) {
                case 1: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | ColorMetrics | undefined));
                    flagArray[14] = 2;
                    break;
                }
                case 3: {
                    flagArray[14] = 2;
                    break;
                }
                default: {
                    flagArray[14] = 0;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | ColorMetrics | undefined));
                }
            }
        }
        if (flagArray[15] != 0)
        {
            switch (flagArray[15] as int32) {
                case 1: {
                    peer.setPixelRoundAttribute((this._pixelRound_0_0value as PixelRoundPolicy | undefined));
                    flagArray[15] = 2;
                    break;
                }
                case 3: {
                    flagArray[15] = 2;
                    break;
                }
                default: {
                    flagArray[15] = 0;
                    peer.setPixelRoundAttribute((undefined as PixelRoundPolicy | undefined));
                }
            }
        }
        if (flagArray[16] != 0)
        {
            switch (flagArray[16] as int32) {
                case 1: {
                    peer.setBackgroundImage0Attribute((this._backgroundImage_0_0value as ResourceStr | image.PixelMap | undefined));
                    flagArray[16] = 2;
                    break;
                }
                case 3: {
                    flagArray[16] = 2;
                    break;
                }
                default: {
                    flagArray[16] = 0;
                    peer.setBackgroundImage0Attribute((undefined as ResourceStr | image.PixelMap | undefined));
                }
            }
        }
        if (flagArray[17] != 0)
        {
            switch (flagArray[17] as int32) {
                case 1: {
                    peer.setBackgroundImageSizeAttribute((this._backgroundImageSize_0_0value as SizeOptions | ImageSize | undefined));
                    flagArray[17] = 2;
                    break;
                }
                case 3: {
                    flagArray[17] = 2;
                    break;
                }
                default: {
                    flagArray[17] = 0;
                    peer.setBackgroundImageSizeAttribute((undefined as SizeOptions | ImageSize | undefined));
                }
            }
        }
        if (flagArray[18] != 0)
        {
            switch (flagArray[18] as int32) {
                case 1: {
                    peer.setBackgroundImagePositionAttribute((this._backgroundImagePosition_0_0value as Position | Alignment | undefined));
                    flagArray[18] = 2;
                    break;
                }
                case 3: {
                    flagArray[18] = 2;
                    break;
                }
                default: {
                    flagArray[18] = 0;
                    peer.setBackgroundImagePositionAttribute((undefined as Position | Alignment | undefined));
                }
            }
        }
        if (flagArray[19] != 0)
        {
            switch (flagArray[19] as int32) {
                case 1: {
                    peer.setBackgroundEffect0Attribute((this._backgroundEffect_0_0value as BackgroundEffectOptions | undefined));
                    flagArray[19] = 2;
                    break;
                }
                case 3: {
                    flagArray[19] = 2;
                    break;
                }
                default: {
                    flagArray[19] = 0;
                    peer.setBackgroundEffect0Attribute((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
    }
    applyModifierPatch1(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[20] != 0)
        {
            switch (flagArray[20] as int32) {
                case 1: {
                    peer.setBackgroundImageResizableAttribute((this._backgroundImageResizable_0_0value as ResizableOptions | undefined));
                    flagArray[20] = 2;
                    break;
                }
                case 3: {
                    flagArray[20] = 2;
                    break;
                }
                default: {
                    flagArray[20] = 0;
                    peer.setBackgroundImageResizableAttribute((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (flagArray[21] != 0)
        {
            switch (flagArray[21] as int32) {
                case 1: {
                    peer.setForegroundEffectAttribute((this._foregroundEffect_0_0value as ForegroundEffectOptions | undefined));
                    flagArray[21] = 2;
                    break;
                }
                case 3: {
                    flagArray[21] = 2;
                    break;
                }
                default: {
                    flagArray[21] = 0;
                    peer.setForegroundEffectAttribute((undefined as ForegroundEffectOptions | undefined));
                }
            }
        }
        if (flagArray[22] != 0)
        {
            switch (flagArray[22] as int32) {
                case 1: {
                    peer.setVisualEffectAttribute((this._visualEffect_0_0value as uiEffect.VisualEffect | undefined));
                    flagArray[22] = 2;
                    break;
                }
                case 3: {
                    flagArray[22] = 2;
                    break;
                }
                default: {
                    flagArray[22] = 0;
                    peer.setVisualEffectAttribute((undefined as uiEffect.VisualEffect | undefined));
                }
            }
        }
        if (flagArray[23] != 0)
        {
            switch (flagArray[23] as int32) {
                case 1: {
                    peer.setBackgroundFilterAttribute((this._backgroundFilter_0_0value as uiEffect.Filter | undefined));
                    flagArray[23] = 2;
                    break;
                }
                case 3: {
                    flagArray[23] = 2;
                    break;
                }
                default: {
                    flagArray[23] = 0;
                    peer.setBackgroundFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (flagArray[24] != 0)
        {
            switch (flagArray[24] as int32) {
                case 1: {
                    peer.setForegroundFilterAttribute((this._foregroundFilter_0_0value as uiEffect.Filter | undefined));
                    flagArray[24] = 2;
                    break;
                }
                case 3: {
                    flagArray[24] = 2;
                    break;
                }
                default: {
                    flagArray[24] = 0;
                    peer.setForegroundFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (flagArray[25] != 0)
        {
            switch (flagArray[25] as int32) {
                case 1: {
                    peer.setCompositingFilterAttribute((this._compositingFilter_0_0value as uiEffect.Filter | undefined));
                    flagArray[25] = 2;
                    break;
                }
                case 3: {
                    flagArray[25] = 2;
                    break;
                }
                default: {
                    flagArray[25] = 0;
                    peer.setCompositingFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (flagArray[26] != 0)
        {
            switch (flagArray[26] as int32) {
                case 1: {
                    peer.setOpacityAttribute((this._opacity_0_0value as double | Resource | undefined));
                    flagArray[26] = 2;
                    break;
                }
                case 3: {
                    flagArray[26] = 2;
                    break;
                }
                default: {
                    flagArray[26] = 0;
                    peer.setOpacityAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (flagArray[27] != 0)
        {
            switch (flagArray[27] as int32) {
                case 1: {
                    peer.setBorderAttribute((this._border_0_0value as BorderOptions | undefined));
                    flagArray[27] = 2;
                    break;
                }
                case 3: {
                    flagArray[27] = 2;
                    break;
                }
                default: {
                    flagArray[27] = 0;
                    peer.setBorderAttribute((undefined as BorderOptions | undefined));
                }
            }
        }
        if (flagArray[28] != 0)
        {
            switch (flagArray[28] as int32) {
                case 1: {
                    peer.setBorderStyleAttribute((this._borderStyle_0_0value as BorderStyle | EdgeStyles | undefined));
                    flagArray[28] = 2;
                    break;
                }
                case 3: {
                    flagArray[28] = 2;
                    break;
                }
                default: {
                    flagArray[28] = 0;
                    peer.setBorderStyleAttribute((undefined as BorderStyle | EdgeStyles | undefined));
                }
            }
        }
        if (flagArray[29] != 0)
        {
            switch (flagArray[29] as int32) {
                case 1: {
                    peer.setBorderWidthAttribute((this._borderWidth_0_0value as Length | EdgeWidths | LocalizedEdgeWidths | undefined));
                    flagArray[29] = 2;
                    break;
                }
                case 3: {
                    flagArray[29] = 2;
                    break;
                }
                default: {
                    flagArray[29] = 0;
                    peer.setBorderWidthAttribute((undefined as Length | EdgeWidths | LocalizedEdgeWidths | undefined));
                }
            }
        }
        if (flagArray[30] != 0)
        {
            switch (flagArray[30] as int32) {
                case 1: {
                    peer.setBorderColorAttribute((this._borderColor_0_0value as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                    flagArray[30] = 2;
                    break;
                }
                case 3: {
                    flagArray[30] = 2;
                    break;
                }
                default: {
                    flagArray[30] = 0;
                    peer.setBorderColorAttribute((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (flagArray[31] != 0)
        {
            switch (flagArray[31] as int32) {
                case 1: {
                    peer.setBorderRadius0Attribute((this._borderRadius_0_0value as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined));
                    flagArray[31] = 2;
                    break;
                }
                case 3: {
                    flagArray[31] = 2;
                    break;
                }
                default: {
                    flagArray[31] = 0;
                    peer.setBorderRadius0Attribute((undefined as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined));
                }
            }
        }
        if (flagArray[32] != 0)
        {
            switch (flagArray[32] as int32) {
                case 1: {
                    peer.setBorderImageAttribute((this._borderImage_0_0value as BorderImageOption | undefined));
                    flagArray[32] = 2;
                    break;
                }
                case 3: {
                    flagArray[32] = 2;
                    break;
                }
                default: {
                    flagArray[32] = 0;
                    peer.setBorderImageAttribute((undefined as BorderImageOption | undefined));
                }
            }
        }
        if (flagArray[33] != 0)
        {
            switch (flagArray[33] as int32) {
                case 1: {
                    peer.setOutlineAttribute((this._outline_0_0value as OutlineOptions | undefined));
                    flagArray[33] = 2;
                    break;
                }
                case 3: {
                    flagArray[33] = 2;
                    break;
                }
                default: {
                    flagArray[33] = 0;
                    peer.setOutlineAttribute((undefined as OutlineOptions | undefined));
                }
            }
        }
        if (flagArray[34] != 0)
        {
            switch (flagArray[34] as int32) {
                case 1: {
                    peer.setOutlineStyleAttribute((this._outlineStyle_0_0value as OutlineStyle | EdgeOutlineStyles | undefined));
                    flagArray[34] = 2;
                    break;
                }
                case 3: {
                    flagArray[34] = 2;
                    break;
                }
                default: {
                    flagArray[34] = 0;
                    peer.setOutlineStyleAttribute((undefined as OutlineStyle | EdgeOutlineStyles | undefined));
                }
            }
        }
        if (flagArray[35] != 0)
        {
            switch (flagArray[35] as int32) {
                case 1: {
                    peer.setOutlineWidthAttribute((this._outlineWidth_0_0value as Dimension | EdgeOutlineWidths | undefined));
                    flagArray[35] = 2;
                    break;
                }
                case 3: {
                    flagArray[35] = 2;
                    break;
                }
                default: {
                    flagArray[35] = 0;
                    peer.setOutlineWidthAttribute((undefined as Dimension | EdgeOutlineWidths | undefined));
                }
            }
        }
        if (flagArray[36] != 0)
        {
            switch (flagArray[36] as int32) {
                case 1: {
                    peer.setOutlineColorAttribute((this._outlineColor_0_0value as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                    flagArray[36] = 2;
                    break;
                }
                case 3: {
                    flagArray[36] = 2;
                    break;
                }
                default: {
                    flagArray[36] = 0;
                    peer.setOutlineColorAttribute((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (flagArray[37] != 0)
        {
            switch (flagArray[37] as int32) {
                case 1: {
                    peer.setOutlineRadiusAttribute((this._outlineRadius_0_0value as Dimension | OutlineRadiuses | undefined));
                    flagArray[37] = 2;
                    break;
                }
                case 3: {
                    flagArray[37] = 2;
                    break;
                }
                default: {
                    flagArray[37] = 0;
                    peer.setOutlineRadiusAttribute((undefined as Dimension | OutlineRadiuses | undefined));
                }
            }
        }
        if (flagArray[38] != 0)
        {
            switch (flagArray[38] as int32) {
                case 1: {
                    peer.setForegroundColorAttribute((this._foregroundColor_0_0value as ResourceColor | ColoringStrategy | undefined));
                    flagArray[38] = 2;
                    break;
                }
                case 3: {
                    flagArray[38] = 2;
                    break;
                }
                default: {
                    flagArray[38] = 0;
                    peer.setForegroundColorAttribute((undefined as ResourceColor | ColoringStrategy | undefined));
                }
            }
        }
        if (flagArray[39] != 0)
        {
            switch (flagArray[39] as int32) {
                case 1: {
                    peer.setOnClick0Attribute((this._onClick_0_0value as ((event: ClickEvent) => void) | undefined));
                    flagArray[39] = 2;
                    break;
                }
                case 3: {
                    flagArray[39] = 2;
                    break;
                }
                default: {
                    flagArray[39] = 0;
                    peer.setOnClick0Attribute((undefined as ((event: ClickEvent) => void) | undefined));
                }
            }
        }
    }
    applyModifierPatch2(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[40] != 0)
        {
            switch (flagArray[40] as int32) {
                case 1: {
                    peer.setOnHoverAttribute((this._onHover_0_0value as ((isHover: boolean,event: HoverEvent) => void) | undefined));
                    flagArray[40] = 2;
                    break;
                }
                case 3: {
                    flagArray[40] = 2;
                    break;
                }
                default: {
                    flagArray[40] = 0;
                    peer.setOnHoverAttribute((undefined as ((isHover: boolean,event: HoverEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[41] != 0)
        {
            switch (flagArray[41] as int32) {
                case 1: {
                    peer.setOnHoverMoveAttribute((this._onHoverMove_0_0value as ((value0: HoverEvent) => void) | undefined));
                    flagArray[41] = 2;
                    break;
                }
                case 3: {
                    flagArray[41] = 2;
                    break;
                }
                default: {
                    flagArray[41] = 0;
                    peer.setOnHoverMoveAttribute((undefined as ((value0: HoverEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[42] != 0)
        {
            switch (flagArray[42] as int32) {
                case 1: {
                    peer.setOnAccessibilityHoverAttribute((this._onAccessibilityHover_0_0value as AccessibilityCallback | undefined));
                    flagArray[42] = 2;
                    break;
                }
                case 3: {
                    flagArray[42] = 2;
                    break;
                }
                default: {
                    flagArray[42] = 0;
                    peer.setOnAccessibilityHoverAttribute((undefined as AccessibilityCallback | undefined));
                }
            }
        }
        if (flagArray[43] != 0)
        {
            switch (flagArray[43] as int32) {
                case 1: {
                    peer.setOnAccessibilityHoverTransparentAttribute((this._onAccessibilityHoverTransparent_0_0value as AccessibilityTransparentCallback | undefined));
                    flagArray[43] = 2;
                    break;
                }
                case 3: {
                    flagArray[43] = 2;
                    break;
                }
                default: {
                    flagArray[43] = 0;
                    peer.setOnAccessibilityHoverTransparentAttribute((undefined as AccessibilityTransparentCallback | undefined));
                }
            }
        }
        if (flagArray[44] != 0)
        {
            switch (flagArray[44] as int32) {
                case 1: {
                    peer.setHoverEffectAttribute((this._hoverEffect_0_0value as HoverEffect | undefined));
                    flagArray[44] = 2;
                    break;
                }
                case 3: {
                    flagArray[44] = 2;
                    break;
                }
                default: {
                    flagArray[44] = 0;
                    peer.setHoverEffectAttribute((undefined as HoverEffect | undefined));
                }
            }
        }
        if (flagArray[45] != 0)
        {
            switch (flagArray[45] as int32) {
                case 1: {
                    peer.setOnMouseAttribute((this._onMouse_0_0value as ((event: MouseEvent) => void) | undefined));
                    flagArray[45] = 2;
                    break;
                }
                case 3: {
                    flagArray[45] = 2;
                    break;
                }
                default: {
                    flagArray[45] = 0;
                    peer.setOnMouseAttribute((undefined as ((event: MouseEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[46] != 0)
        {
            switch (flagArray[46] as int32) {
                case 1: {
                    peer.setOnTouchAttribute((this._onTouch_0_0value as ((event: TouchEvent) => void) | undefined));
                    flagArray[46] = 2;
                    break;
                }
                case 3: {
                    flagArray[46] = 2;
                    break;
                }
                default: {
                    flagArray[46] = 0;
                    peer.setOnTouchAttribute((undefined as ((event: TouchEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[47] != 0)
        {
            switch (flagArray[47] as int32) {
                case 1: {
                    peer.setOnKeyEventAttribute((this._onKeyEvent_0_0value as ((value0: KeyEvent) => boolean) | undefined));
                    flagArray[47] = 2;
                    break;
                }
                case 3: {
                    flagArray[47] = 2;
                    break;
                }
                default: {
                    flagArray[47] = 0;
                    peer.setOnKeyEventAttribute((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[48] != 0)
        {
            switch (flagArray[48] as int32) {
                case 1: {
                    peer.setOnDigitalCrownAttribute((this._onDigitalCrown_0_0value as ((value0: CrownEvent) => void) | undefined));
                    flagArray[48] = 2;
                    break;
                }
                case 3: {
                    flagArray[48] = 2;
                    break;
                }
                default: {
                    flagArray[48] = 0;
                    peer.setOnDigitalCrownAttribute((undefined as ((value0: CrownEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[49] != 0)
        {
            switch (flagArray[49] as int32) {
                case 1: {
                    peer.setOnKeyPreImeAttribute((this._onKeyPreIme_0_0value as ((value0: KeyEvent) => boolean) | undefined));
                    flagArray[49] = 2;
                    break;
                }
                case 3: {
                    flagArray[49] = 2;
                    break;
                }
                default: {
                    flagArray[49] = 0;
                    peer.setOnKeyPreImeAttribute((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[50] != 0)
        {
            switch (flagArray[50] as int32) {
                case 1: {
                    peer.setOnKeyEventDispatchAttribute((this._onKeyEventDispatch_0_0value as ((value0: KeyEvent) => boolean) | undefined));
                    flagArray[50] = 2;
                    break;
                }
                case 3: {
                    flagArray[50] = 2;
                    break;
                }
                default: {
                    flagArray[50] = 0;
                    peer.setOnKeyEventDispatchAttribute((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[51] != 0)
        {
            switch (flagArray[51] as int32) {
                case 1: {
                    peer.setOnFocusAxisEventAttribute((this._onFocusAxisEvent_0_0value as ((value0: FocusAxisEvent) => void) | undefined));
                    flagArray[51] = 2;
                    break;
                }
                case 3: {
                    flagArray[51] = 2;
                    break;
                }
                default: {
                    flagArray[51] = 0;
                    peer.setOnFocusAxisEventAttribute((undefined as ((value0: FocusAxisEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[52] != 0)
        {
            switch (flagArray[52] as int32) {
                case 1: {
                    peer.setOnAxisEventAttribute((this._onAxisEvent_0_0value as ((value0: AxisEvent) => void) | undefined));
                    flagArray[52] = 2;
                    break;
                }
                case 3: {
                    flagArray[52] = 2;
                    break;
                }
                default: {
                    flagArray[52] = 0;
                    peer.setOnAxisEventAttribute((undefined as ((value0: AxisEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[53] != 0)
        {
            switch (flagArray[53] as int32) {
                case 1: {
                    peer.setFocusableAttribute((this._focusable_0_0value as boolean | undefined));
                    flagArray[53] = 2;
                    break;
                }
                case 3: {
                    flagArray[53] = 2;
                    break;
                }
                default: {
                    flagArray[53] = 0;
                    peer.setFocusableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[54] != 0)
        {
            switch (flagArray[54] as int32) {
                case 1: {
                    peer.setNextFocusAttribute((this._nextFocus_0_0value as FocusMovement | undefined));
                    flagArray[54] = 2;
                    break;
                }
                case 3: {
                    flagArray[54] = 2;
                    break;
                }
                default: {
                    flagArray[54] = 0;
                    peer.setNextFocusAttribute((undefined as FocusMovement | undefined));
                }
            }
        }
        if (flagArray[55] != 0)
        {
            switch (flagArray[55] as int32) {
                case 1: {
                    peer.setTabStopAttribute((this._tabStop_0_0value as boolean | undefined));
                    flagArray[55] = 2;
                    break;
                }
                case 3: {
                    flagArray[55] = 2;
                    break;
                }
                default: {
                    flagArray[55] = 0;
                    peer.setTabStopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[56] != 0)
        {
            switch (flagArray[56] as int32) {
                case 1: {
                    peer.setOnFocusAttribute((this._onFocus_0_0value as (() => void) | undefined));
                    flagArray[56] = 2;
                    break;
                }
                case 3: {
                    flagArray[56] = 2;
                    break;
                }
                default: {
                    flagArray[56] = 0;
                    peer.setOnFocusAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[57] != 0)
        {
            switch (flagArray[57] as int32) {
                case 1: {
                    peer.setOnBlurAttribute((this._onBlur_0_0value as (() => void) | undefined));
                    flagArray[57] = 2;
                    break;
                }
                case 3: {
                    flagArray[57] = 2;
                    break;
                }
                default: {
                    flagArray[57] = 0;
                    peer.setOnBlurAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[58] != 0)
        {
            switch (flagArray[58] as int32) {
                case 1: {
                    peer.setTabIndexAttribute((this._tabIndex_0_0value as int32 | undefined));
                    flagArray[58] = 2;
                    break;
                }
                case 3: {
                    flagArray[58] = 2;
                    break;
                }
                default: {
                    flagArray[58] = 0;
                    peer.setTabIndexAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[59] != 0)
        {
            switch (flagArray[59] as int32) {
                case 1: {
                    peer.setDefaultFocusAttribute((this._defaultFocus_0_0value as boolean | undefined));
                    flagArray[59] = 2;
                    break;
                }
                case 3: {
                    flagArray[59] = 2;
                    break;
                }
                default: {
                    flagArray[59] = 0;
                    peer.setDefaultFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    applyModifierPatch3(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[60] != 0)
        {
            switch (flagArray[60] as int32) {
                case 1: {
                    peer.setGroupDefaultFocusAttribute((this._groupDefaultFocus_0_0value as boolean | undefined));
                    flagArray[60] = 2;
                    break;
                }
                case 3: {
                    flagArray[60] = 2;
                    break;
                }
                default: {
                    flagArray[60] = 0;
                    peer.setGroupDefaultFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[61] != 0)
        {
            switch (flagArray[61] as int32) {
                case 1: {
                    peer.setFocusOnTouchAttribute((this._focusOnTouch_0_0value as boolean | undefined));
                    flagArray[61] = 2;
                    break;
                }
                case 3: {
                    flagArray[61] = 2;
                    break;
                }
                default: {
                    flagArray[61] = 0;
                    peer.setFocusOnTouchAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[62] != 0)
        {
            switch (flagArray[62] as int32) {
                case 1: {
                    peer.setFocusBoxAttribute((this._focusBox_0_0value as FocusBoxStyle | undefined));
                    flagArray[62] = 2;
                    break;
                }
                case 3: {
                    flagArray[62] = 2;
                    break;
                }
                default: {
                    flagArray[62] = 0;
                    peer.setFocusBoxAttribute((undefined as FocusBoxStyle | undefined));
                }
            }
        }
        if (flagArray[63] != 0)
        {
            switch (flagArray[63] as int32) {
                case 1: {
                    peer.setAnimationAttribute((this._animation_0_0value as AnimateParam | undefined));
                    flagArray[63] = 2;
                    break;
                }
                case 3: {
                    flagArray[63] = 2;
                    break;
                }
                default: {
                    flagArray[63] = 0;
                    peer.setAnimationAttribute((undefined as AnimateParam | undefined));
                }
            }
        }
        if (flagArray[64] != 0)
        {
            switch (flagArray[64] as int32) {
                case 1: {
                    peer.setTransition0Attribute((this._transition_0_0value as TransitionEffect | undefined));
                    flagArray[64] = 2;
                    break;
                }
                case 3: {
                    flagArray[64] = 2;
                    break;
                }
                default: {
                    flagArray[64] = 0;
                    peer.setTransition0Attribute((undefined as TransitionEffect | undefined));
                }
            }
        }
        if (flagArray[65] != 0)
        {
            switch (flagArray[65] as int32) {
                case 1: {
                    peer.setMotionBlurAttribute((this._motionBlur_0_0value as MotionBlurOptions | undefined));
                    flagArray[65] = 2;
                    break;
                }
                case 3: {
                    flagArray[65] = 2;
                    break;
                }
                default: {
                    flagArray[65] = 0;
                    peer.setMotionBlurAttribute((undefined as MotionBlurOptions | undefined));
                }
            }
        }
        if (flagArray[66] != 0)
        {
            switch (flagArray[66] as int32) {
                case 1: {
                    peer.setBrightnessAttribute((this._brightness_0_0value as double | undefined));
                    flagArray[66] = 2;
                    break;
                }
                case 3: {
                    flagArray[66] = 2;
                    break;
                }
                default: {
                    flagArray[66] = 0;
                    peer.setBrightnessAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[67] != 0)
        {
            switch (flagArray[67] as int32) {
                case 1: {
                    peer.setContrastAttribute((this._contrast_0_0value as double | undefined));
                    flagArray[67] = 2;
                    break;
                }
                case 3: {
                    flagArray[67] = 2;
                    break;
                }
                default: {
                    flagArray[67] = 0;
                    peer.setContrastAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[68] != 0)
        {
            switch (flagArray[68] as int32) {
                case 1: {
                    peer.setGrayscaleAttribute((this._grayscale_0_0value as double | undefined));
                    flagArray[68] = 2;
                    break;
                }
                case 3: {
                    flagArray[68] = 2;
                    break;
                }
                default: {
                    flagArray[68] = 0;
                    peer.setGrayscaleAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[69] != 0)
        {
            switch (flagArray[69] as int32) {
                case 1: {
                    peer.setColorBlendAttribute((this._colorBlend_0_0value as Color | string | Resource | undefined));
                    flagArray[69] = 2;
                    break;
                }
                case 3: {
                    flagArray[69] = 2;
                    break;
                }
                default: {
                    flagArray[69] = 0;
                    peer.setColorBlendAttribute((undefined as Color | string | Resource | undefined));
                }
            }
        }
        if (flagArray[70] != 0)
        {
            switch (flagArray[70] as int32) {
                case 1: {
                    peer.setSaturateAttribute((this._saturate_0_0value as double | undefined));
                    flagArray[70] = 2;
                    break;
                }
                case 3: {
                    flagArray[70] = 2;
                    break;
                }
                default: {
                    flagArray[70] = 0;
                    peer.setSaturateAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[71] != 0)
        {
            switch (flagArray[71] as int32) {
                case 1: {
                    peer.setSepiaAttribute((this._sepia_0_0value as double | undefined));
                    flagArray[71] = 2;
                    break;
                }
                case 3: {
                    flagArray[71] = 2;
                    break;
                }
                default: {
                    flagArray[71] = 0;
                    peer.setSepiaAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[72] != 0)
        {
            switch (flagArray[72] as int32) {
                case 1: {
                    peer.setInvertAttribute((this._invert_0_0value as double | InvertOptions | undefined));
                    flagArray[72] = 2;
                    break;
                }
                case 3: {
                    flagArray[72] = 2;
                    break;
                }
                default: {
                    flagArray[72] = 0;
                    peer.setInvertAttribute((undefined as double | InvertOptions | undefined));
                }
            }
        }
        if (flagArray[73] != 0)
        {
            switch (flagArray[73] as int32) {
                case 1: {
                    peer.setHueRotateAttribute((this._hueRotate_0_0value as double | string | undefined));
                    flagArray[73] = 2;
                    break;
                }
                case 3: {
                    flagArray[73] = 2;
                    break;
                }
                default: {
                    flagArray[73] = 0;
                    peer.setHueRotateAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[74] != 0)
        {
            switch (flagArray[74] as int32) {
                case 1: {
                    peer.setUseShadowBatchingAttribute((this._useShadowBatching_0_0value as boolean | undefined));
                    flagArray[74] = 2;
                    break;
                }
                case 3: {
                    flagArray[74] = 2;
                    break;
                }
                default: {
                    flagArray[74] = 0;
                    peer.setUseShadowBatchingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[75] != 0)
        {
            switch (flagArray[75] as int32) {
                case 1: {
                    peer.setUseEffect0Attribute((this._useEffect_0_0value as boolean | undefined));
                    flagArray[75] = 2;
                    break;
                }
                case 3: {
                    flagArray[75] = 2;
                    break;
                }
                default: {
                    flagArray[75] = 0;
                    peer.setUseEffect0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[76] != 0)
        {
            switch (flagArray[76] as int32) {
                case 1: {
                    peer.setRenderGroupAttribute((this._renderGroup_0_0value as boolean | undefined));
                    flagArray[76] = 2;
                    break;
                }
                case 3: {
                    flagArray[76] = 2;
                    break;
                }
                default: {
                    flagArray[76] = 0;
                    peer.setRenderGroupAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[77] != 0)
        {
            switch (flagArray[77] as int32) {
                case 1: {
                    peer.setFreezeAttribute((this._freeze_0_0value as boolean | undefined));
                    flagArray[77] = 2;
                    break;
                }
                case 3: {
                    flagArray[77] = 2;
                    break;
                }
                default: {
                    flagArray[77] = 0;
                    peer.setFreezeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[78] != 0)
        {
            switch (flagArray[78] as int32) {
                case 1: {
                    peer.setTranslateAttribute((this._translate_0_0value as TranslateOptions | undefined));
                    flagArray[78] = 2;
                    break;
                }
                case 3: {
                    flagArray[78] = 2;
                    break;
                }
                default: {
                    flagArray[78] = 0;
                    peer.setTranslateAttribute((undefined as TranslateOptions | undefined));
                }
            }
        }
        if (flagArray[79] != 0)
        {
            switch (flagArray[79] as int32) {
                case 1: {
                    peer.setScaleAttribute((this._scale_0_0value as ScaleOptions | undefined));
                    flagArray[79] = 2;
                    break;
                }
                case 3: {
                    flagArray[79] = 2;
                    break;
                }
                default: {
                    flagArray[79] = 0;
                    peer.setScaleAttribute((undefined as ScaleOptions | undefined));
                }
            }
        }
    }
    applyModifierPatch4(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[80] != 0)
        {
            switch (flagArray[80] as int32) {
                case 1: {
                    peer.setRotateAttribute((this._rotate_0_0value as RotateOptions | RotateAngleOptions | undefined));
                    flagArray[80] = 2;
                    break;
                }
                case 3: {
                    flagArray[80] = 2;
                    break;
                }
                default: {
                    flagArray[80] = 0;
                    peer.setRotateAttribute((undefined as RotateOptions | RotateAngleOptions | undefined));
                }
            }
        }
        if (flagArray[81] != 0)
        {
            switch (flagArray[81] as int32) {
                case 1: {
                    peer.setTransformAttribute((this._transform_0_0value as matrix4.Matrix4Transit | undefined));
                    flagArray[81] = 2;
                    break;
                }
                case 3: {
                    flagArray[81] = 2;
                    break;
                }
                default: {
                    flagArray[81] = 0;
                    peer.setTransformAttribute((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (flagArray[82] != 0)
        {
            switch (flagArray[82] as int32) {
                case 1: {
                    peer.setTransform3DAttribute((this._transform3D_0_0value as matrix4.Matrix4Transit | undefined));
                    flagArray[82] = 2;
                    break;
                }
                case 3: {
                    flagArray[82] = 2;
                    break;
                }
                default: {
                    flagArray[82] = 0;
                    peer.setTransform3DAttribute((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (flagArray[83] != 0)
        {
            switch (flagArray[83] as int32) {
                case 1: {
                    peer.setOnAppearAttribute((this._onAppear_0_0value as (() => void) | undefined));
                    flagArray[83] = 2;
                    break;
                }
                case 3: {
                    flagArray[83] = 2;
                    break;
                }
                default: {
                    flagArray[83] = 0;
                    peer.setOnAppearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[84] != 0)
        {
            switch (flagArray[84] as int32) {
                case 1: {
                    peer.setOnDisAppearAttribute((this._onDisAppear_0_0value as (() => void) | undefined));
                    flagArray[84] = 2;
                    break;
                }
                case 3: {
                    flagArray[84] = 2;
                    break;
                }
                default: {
                    flagArray[84] = 0;
                    peer.setOnDisAppearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[85] != 0)
        {
            switch (flagArray[85] as int32) {
                case 1: {
                    peer.setOnAttachAttribute((this._onAttach_0_0value as VoidCallback | undefined));
                    flagArray[85] = 2;
                    break;
                }
                case 3: {
                    flagArray[85] = 2;
                    break;
                }
                default: {
                    flagArray[85] = 0;
                    peer.setOnAttachAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[86] != 0)
        {
            switch (flagArray[86] as int32) {
                case 1: {
                    peer.setOnDetachAttribute((this._onDetach_0_0value as VoidCallback | undefined));
                    flagArray[86] = 2;
                    break;
                }
                case 3: {
                    flagArray[86] = 2;
                    break;
                }
                default: {
                    flagArray[86] = 0;
                    peer.setOnDetachAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[87] != 0)
        {
            switch (flagArray[87] as int32) {
                case 1: {
                    peer.setOnAreaChangeAttribute((this._onAreaChange_0_0value as ((oldValue: Area,newValue: Area) => void) | undefined));
                    flagArray[87] = 2;
                    break;
                }
                case 3: {
                    flagArray[87] = 2;
                    break;
                }
                default: {
                    flagArray[87] = 0;
                    peer.setOnAreaChangeAttribute((undefined as ((oldValue: Area,newValue: Area) => void) | undefined));
                }
            }
        }
        if (flagArray[88] != 0)
        {
            switch (flagArray[88] as int32) {
                case 1: {
                    peer.setVisibilityAttribute((this._visibility_0_0value as Visibility | undefined));
                    flagArray[88] = 2;
                    break;
                }
                case 3: {
                    flagArray[88] = 2;
                    break;
                }
                default: {
                    flagArray[88] = 0;
                    peer.setVisibilityAttribute((undefined as Visibility | undefined));
                }
            }
        }
        if (flagArray[89] != 0)
        {
            switch (flagArray[89] as int32) {
                case 1: {
                    peer.setFlexGrowAttribute((this._flexGrow_0_0value as number | undefined));
                    flagArray[89] = 2;
                    break;
                }
                case 3: {
                    flagArray[89] = 2;
                    break;
                }
                default: {
                    flagArray[89] = 0;
                    peer.setFlexGrowAttribute((undefined as number | undefined));
                }
            }
        }
        if (flagArray[90] != 0)
        {
            switch (flagArray[90] as int32) {
                case 1: {
                    peer.setFlexShrinkAttribute((this._flexShrink_0_0value as number | undefined));
                    flagArray[90] = 2;
                    break;
                }
                case 3: {
                    flagArray[90] = 2;
                    break;
                }
                default: {
                    flagArray[90] = 0;
                    peer.setFlexShrinkAttribute((undefined as number | undefined));
                }
            }
        }
        if (flagArray[91] != 0)
        {
            switch (flagArray[91] as int32) {
                case 1: {
                    peer.setFlexBasisAttribute((this._flexBasis_0_0value as number | string | undefined));
                    flagArray[91] = 2;
                    break;
                }
                case 3: {
                    flagArray[91] = 2;
                    break;
                }
                default: {
                    flagArray[91] = 0;
                    peer.setFlexBasisAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (flagArray[92] != 0)
        {
            switch (flagArray[92] as int32) {
                case 1: {
                    peer.setAlignSelfAttribute((this._alignSelf_0_0value as ItemAlign | undefined));
                    flagArray[92] = 2;
                    break;
                }
                case 3: {
                    flagArray[92] = 2;
                    break;
                }
                default: {
                    flagArray[92] = 0;
                    peer.setAlignSelfAttribute((undefined as ItemAlign | undefined));
                }
            }
        }
        if (flagArray[93] != 0)
        {
            switch (flagArray[93] as int32) {
                case 1: {
                    peer.setLayoutGravityAttribute((this._layoutGravity_0_0value as LocalizedAlignment | undefined));
                    flagArray[93] = 2;
                    break;
                }
                case 3: {
                    flagArray[93] = 2;
                    break;
                }
                default: {
                    flagArray[93] = 0;
                    peer.setLayoutGravityAttribute((undefined as LocalizedAlignment | undefined));
                }
            }
        }
        if (flagArray[94] != 0)
        {
            switch (flagArray[94] as int32) {
                case 1: {
                    peer.setDisplayPriorityAttribute((this._displayPriority_0_0value as number | undefined));
                    flagArray[94] = 2;
                    break;
                }
                case 3: {
                    flagArray[94] = 2;
                    break;
                }
                default: {
                    flagArray[94] = 0;
                    peer.setDisplayPriorityAttribute((undefined as number | undefined));
                }
            }
        }
        if (flagArray[95] != 0)
        {
            switch (flagArray[95] as int32) {
                case 1: {
                    peer.setZIndexAttribute((this._zIndex_0_0value as int32 | undefined));
                    flagArray[95] = 2;
                    break;
                }
                case 3: {
                    flagArray[95] = 2;
                    break;
                }
                default: {
                    flagArray[95] = 0;
                    peer.setZIndexAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[96] != 0)
        {
            switch (flagArray[96] as int32) {
                case 1: {
                    peer.setDirectionAttribute((this._direction_0_0value as Direction | undefined));
                    flagArray[96] = 2;
                    break;
                }
                case 3: {
                    flagArray[96] = 2;
                    break;
                }
                default: {
                    flagArray[96] = 0;
                    peer.setDirectionAttribute((undefined as Direction | undefined));
                }
            }
        }
        if (flagArray[97] != 0)
        {
            switch (flagArray[97] as int32) {
                case 1: {
                    peer.setAlignAttribute((this._align_0_0value as Alignment | LocalizedAlignment | undefined));
                    flagArray[97] = 2;
                    break;
                }
                case 3: {
                    flagArray[97] = 2;
                    break;
                }
                default: {
                    flagArray[97] = 0;
                    peer.setAlignAttribute((undefined as Alignment | LocalizedAlignment | undefined));
                }
            }
        }
        if (flagArray[98] != 0)
        {
            switch (flagArray[98] as int32) {
                case 1: {
                    peer.setPositionAttribute((this._position_0_0value as Position | Edges | LocalizedEdges | undefined));
                    flagArray[98] = 2;
                    break;
                }
                case 3: {
                    flagArray[98] = 2;
                    break;
                }
                default: {
                    flagArray[98] = 0;
                    peer.setPositionAttribute((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (flagArray[99] != 0)
        {
            switch (flagArray[99] as int32) {
                case 1: {
                    peer.setMarkAnchorAttribute((this._markAnchor_0_0value as Position | LocalizedPosition | undefined));
                    flagArray[99] = 2;
                    break;
                }
                case 3: {
                    flagArray[99] = 2;
                    break;
                }
                default: {
                    flagArray[99] = 0;
                    peer.setMarkAnchorAttribute((undefined as Position | LocalizedPosition | undefined));
                }
            }
        }
    }
    applyModifierPatch5(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[100] != 0)
        {
            switch (flagArray[100] as int32) {
                case 1: {
                    peer.setOffsetAttribute((this._offset_0_0value as Position | Edges | LocalizedEdges | undefined));
                    flagArray[100] = 2;
                    break;
                }
                case 3: {
                    flagArray[100] = 2;
                    break;
                }
                default: {
                    flagArray[100] = 0;
                    peer.setOffsetAttribute((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (flagArray[101] != 0)
        {
            switch (flagArray[101] as int32) {
                case 1: {
                    peer.setEnabledAttribute((this._enabled_0_0value as boolean | undefined));
                    flagArray[101] = 2;
                    break;
                }
                case 3: {
                    flagArray[101] = 2;
                    break;
                }
                default: {
                    flagArray[101] = 0;
                    peer.setEnabledAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[102] != 0)
        {
            switch (flagArray[102] as int32) {
                case 1: {
                    peer.setAlignRulesAttribute((this._alignRules_0_0value as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                    flagArray[102] = 2;
                    break;
                }
                case 3: {
                    flagArray[102] = 2;
                    break;
                }
                default: {
                    flagArray[102] = 0;
                    peer.setAlignRulesAttribute((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (flagArray[103] != 0)
        {
            switch (flagArray[103] as int32) {
                case 1: {
                    peer.setAspectRatioAttribute((this._aspectRatio_0_0value as number | undefined));
                    flagArray[103] = 2;
                    break;
                }
                case 3: {
                    flagArray[103] = 2;
                    break;
                }
                default: {
                    flagArray[103] = 0;
                    peer.setAspectRatioAttribute((undefined as number | undefined));
                }
            }
        }
        if (flagArray[104] != 0)
        {
            switch (flagArray[104] as int32) {
                case 1: {
                    peer.setClickEffectAttribute((this._clickEffect_0_0value as ClickEffect | null | undefined));
                    flagArray[104] = 2;
                    break;
                }
                case 3: {
                    flagArray[104] = 2;
                    break;
                }
                default: {
                    flagArray[104] = 0;
                    peer.setClickEffectAttribute((undefined as ClickEffect | null | undefined));
                }
            }
        }
        if (flagArray[105] != 0)
        {
            switch (flagArray[105] as int32) {
                case 1: {
                    peer.setOnDragStartAttribute((this._onDragStart_0_0value as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined));
                    flagArray[105] = 2;
                    break;
                }
                case 3: {
                    flagArray[105] = 2;
                    break;
                }
                default: {
                    flagArray[105] = 0;
                    peer.setOnDragStartAttribute((undefined as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined));
                }
            }
        }
        if (flagArray[106] != 0)
        {
            switch (flagArray[106] as int32) {
                case 1: {
                    peer.setOnDragEnterAttribute((this._onDragEnter_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    flagArray[106] = 2;
                    break;
                }
                case 3: {
                    flagArray[106] = 2;
                    break;
                }
                default: {
                    flagArray[106] = 0;
                    peer.setOnDragEnterAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[107] != 0)
        {
            switch (flagArray[107] as int32) {
                case 1: {
                    peer.setOnDragMoveAttribute((this._onDragMove_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    flagArray[107] = 2;
                    break;
                }
                case 3: {
                    flagArray[107] = 2;
                    break;
                }
                default: {
                    flagArray[107] = 0;
                    peer.setOnDragMoveAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[108] != 0)
        {
            switch (flagArray[108] as int32) {
                case 1: {
                    peer.setOnDragLeaveAttribute((this._onDragLeave_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    flagArray[108] = 2;
                    break;
                }
                case 3: {
                    flagArray[108] = 2;
                    break;
                }
                default: {
                    flagArray[108] = 0;
                    peer.setOnDragLeaveAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[109] != 0)
        {
            switch (flagArray[109] as int32) {
                case 1: {
                    peer.setOnDrop0Attribute((this._onDrop_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    flagArray[109] = 2;
                    break;
                }
                case 3: {
                    flagArray[109] = 2;
                    break;
                }
                default: {
                    flagArray[109] = 0;
                    peer.setOnDrop0Attribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[110] != 0)
        {
            switch (flagArray[110] as int32) {
                case 1: {
                    peer.setOnDragEndAttribute((this._onDragEnd_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    flagArray[110] = 2;
                    break;
                }
                case 3: {
                    flagArray[110] = 2;
                    break;
                }
                default: {
                    flagArray[110] = 0;
                    peer.setOnDragEndAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[111] != 0)
        {
            switch (flagArray[111] as int32) {
                case 1: {
                    hookAllowDrop(peer, (this._allowDrop_0_0value as Array<uniformTypeDescriptor.UniformDataType> | Array<string> | null | undefined));
                    flagArray[111] = 2;
                    break;
                }
                case 3: {
                    flagArray[111] = 2;
                    break;
                }
                default: {
                    flagArray[111] = 0;
                    hookAllowDrop(peer, (undefined as Array<uniformTypeDescriptor.UniformDataType> | Array<string> | null | undefined));
                }
            }
        }
        if (flagArray[112] != 0)
        {
            switch (flagArray[112] as int32) {
                case 1: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    flagArray[112] = 2;
                    break;
                }
                case 3: {
                    flagArray[112] = 2;
                    break;
                }
                default: {
                    flagArray[112] = 0;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[113] != 0)
        {
            switch (flagArray[113] as int32) {
                case 1: {
                    peer.setDragPreview0Attribute((this._dragPreview_0_0value as CustomBuilder | DragItemInfo | string | undefined));
                    flagArray[113] = 2;
                    break;
                }
                case 3: {
                    flagArray[113] = 2;
                    break;
                }
                default: {
                    flagArray[113] = 0;
                    peer.setDragPreview0Attribute((undefined as CustomBuilder | DragItemInfo | string | undefined));
                }
            }
        }
        if (flagArray[114] != 0)
        {
            switch (flagArray[114] as int32) {
                case 1: {
                    peer.setOnPreDragAttribute((this._onPreDrag_0_0value as ((value0: PreDragStatus) => void) | undefined));
                    flagArray[114] = 2;
                    break;
                }
                case 3: {
                    flagArray[114] = 2;
                    break;
                }
                default: {
                    flagArray[114] = 0;
                    peer.setOnPreDragAttribute((undefined as ((value0: PreDragStatus) => void) | undefined));
                }
            }
        }
        if (flagArray[115] != 0)
        {
            switch (flagArray[115] as int32) {
                case 1: {
                    peer.setLinearGradientAttribute((this._linearGradient_0_0value as LinearGradientOptions | undefined));
                    flagArray[115] = 2;
                    break;
                }
                case 3: {
                    flagArray[115] = 2;
                    break;
                }
                default: {
                    flagArray[115] = 0;
                    peer.setLinearGradientAttribute((undefined as LinearGradientOptions | undefined));
                }
            }
        }
        if (flagArray[116] != 0)
        {
            switch (flagArray[116] as int32) {
                case 1: {
                    peer.setSweepGradientAttribute((this._sweepGradient_0_0value as SweepGradientOptions | undefined));
                    flagArray[116] = 2;
                    break;
                }
                case 3: {
                    flagArray[116] = 2;
                    break;
                }
                default: {
                    flagArray[116] = 0;
                    peer.setSweepGradientAttribute((undefined as SweepGradientOptions | undefined));
                }
            }
        }
        if (flagArray[117] != 0)
        {
            switch (flagArray[117] as int32) {
                case 1: {
                    peer.setRadialGradientAttribute((this._radialGradient_0_0value as RadialGradientOptions | undefined));
                    flagArray[117] = 2;
                    break;
                }
                case 3: {
                    flagArray[117] = 2;
                    break;
                }
                default: {
                    flagArray[117] = 0;
                    peer.setRadialGradientAttribute((undefined as RadialGradientOptions | undefined));
                }
            }
        }
        if (flagArray[118] != 0)
        {
            switch (flagArray[118] as int32) {
                case 1: {
                    peer.setMotionPathAttribute((this._motionPath_0_0value as MotionPathOptions | undefined));
                    flagArray[118] = 2;
                    break;
                }
                case 3: {
                    flagArray[118] = 2;
                    break;
                }
                default: {
                    flagArray[118] = 0;
                    peer.setMotionPathAttribute((undefined as MotionPathOptions | undefined));
                }
            }
        }
        if (flagArray[119] != 0)
        {
            switch (flagArray[119] as int32) {
                case 1: {
                    peer.setShadowAttribute((this._shadow_0_0value as ShadowOptions | ShadowStyle | undefined));
                    flagArray[119] = 2;
                    break;
                }
                case 3: {
                    flagArray[119] = 2;
                    break;
                }
                default: {
                    flagArray[119] = 0;
                    peer.setShadowAttribute((undefined as ShadowOptions | ShadowStyle | undefined));
                }
            }
        }
    }
    applyModifierPatch6(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[120] != 0)
        {
            switch (flagArray[120] as int32) {
                case 1: {
                    peer.setClipAttribute((this._clip_0_0value as boolean | undefined));
                    flagArray[120] = 2;
                    break;
                }
                case 3: {
                    flagArray[120] = 2;
                    break;
                }
                default: {
                    flagArray[120] = 0;
                    peer.setClipAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[121] != 0)
        {
            switch (flagArray[121] as int32) {
                case 1: {
                    peer.setClipShapeAttribute((this._clipShape_0_0value as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                    flagArray[121] = 2;
                    break;
                }
                case 3: {
                    flagArray[121] = 2;
                    break;
                }
                default: {
                    flagArray[121] = 0;
                    peer.setClipShapeAttribute((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (flagArray[122] != 0)
        {
            switch (flagArray[122] as int32) {
                case 1: {
                    peer.setMaskAttribute((this._mask_0_0value as ProgressMask | undefined));
                    flagArray[122] = 2;
                    break;
                }
                case 3: {
                    flagArray[122] = 2;
                    break;
                }
                default: {
                    flagArray[122] = 0;
                    peer.setMaskAttribute((undefined as ProgressMask | undefined));
                }
            }
        }
        if (flagArray[123] != 0)
        {
            switch (flagArray[123] as int32) {
                case 1: {
                    peer.setMaskShapeAttribute((this._maskShape_0_0value as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                    flagArray[123] = 2;
                    break;
                }
                case 3: {
                    flagArray[123] = 2;
                    break;
                }
                default: {
                    flagArray[123] = 0;
                    peer.setMaskShapeAttribute((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (flagArray[124] != 0)
        {
            switch (flagArray[124] as int32) {
                case 1: {
                    peer.setKeyAttribute((this._key_0_0value as string | undefined));
                    flagArray[124] = 2;
                    break;
                }
                case 3: {
                    flagArray[124] = 2;
                    break;
                }
                default: {
                    flagArray[124] = 0;
                    peer.setKeyAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[125] != 0)
        {
            switch (flagArray[125] as int32) {
                case 1: {
                    peer.setIdAttribute((this._id_0_0value as string | undefined));
                    flagArray[125] = 2;
                    break;
                }
                case 3: {
                    flagArray[125] = 2;
                    break;
                }
                default: {
                    flagArray[125] = 0;
                    peer.setIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[126] != 0)
        {
            switch (flagArray[126] as int32) {
                case 1: {
                    peer.setGeometryTransition0Attribute((this._geometryTransition_0_0value as string | undefined));
                    flagArray[126] = 2;
                    break;
                }
                case 3: {
                    flagArray[126] = 2;
                    break;
                }
                default: {
                    flagArray[126] = 0;
                    peer.setGeometryTransition0Attribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[127] != 0)
        {
            switch (flagArray[127] as int32) {
                case 1: {
                    peer.setRestoreIdAttribute((this._restoreId_0_0value as int32 | undefined));
                    flagArray[127] = 2;
                    break;
                }
                case 3: {
                    flagArray[127] = 2;
                    break;
                }
                default: {
                    flagArray[127] = 0;
                    peer.setRestoreIdAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[128] != 0)
        {
            switch (flagArray[128] as int32) {
                case 1: {
                    peer.setSphericalEffectAttribute((this._sphericalEffect_0_0value as double | undefined));
                    flagArray[128] = 2;
                    break;
                }
                case 3: {
                    flagArray[128] = 2;
                    break;
                }
                default: {
                    flagArray[128] = 0;
                    peer.setSphericalEffectAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[129] != 0)
        {
            switch (flagArray[129] as int32) {
                case 1: {
                    peer.setLightUpEffectAttribute((this._lightUpEffect_0_0value as double | undefined));
                    flagArray[129] = 2;
                    break;
                }
                case 3: {
                    flagArray[129] = 2;
                    break;
                }
                default: {
                    flagArray[129] = 0;
                    peer.setLightUpEffectAttribute((undefined as double | undefined));
                }
            }
        }
        if (flagArray[130] != 0)
        {
            switch (flagArray[130] as int32) {
                case 1: {
                    peer.setPixelStretchEffectAttribute((this._pixelStretchEffect_0_0value as PixelStretchEffectOptions | undefined));
                    flagArray[130] = 2;
                    break;
                }
                case 3: {
                    flagArray[130] = 2;
                    break;
                }
                default: {
                    flagArray[130] = 0;
                    peer.setPixelStretchEffectAttribute((undefined as PixelStretchEffectOptions | undefined));
                }
            }
        }
        if (flagArray[131] != 0)
        {
            switch (flagArray[131] as int32) {
                case 1: {
                    peer.setAccessibilityGroupWithValueAttribute((this._accessibilityGroup_0_0value as boolean | undefined));
                    flagArray[131] = 2;
                    break;
                }
                case 3: {
                    flagArray[131] = 2;
                    break;
                }
                default: {
                    flagArray[131] = 0;
                    peer.setAccessibilityGroupWithValueAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[132] != 0)
        {
            switch (flagArray[132] as int32) {
                case 1: {
                    peer.setAccessibilityTextOfStringTypeAttribute((this._accessibilityTextOfStringType_0_0value as string | undefined));
                    flagArray[132] = 2;
                    break;
                }
                case 3: {
                    flagArray[132] = 2;
                    break;
                }
                default: {
                    flagArray[132] = 0;
                    peer.setAccessibilityTextOfStringTypeAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[133] != 0)
        {
            switch (flagArray[133] as int32) {
                case 1: {
                    peer.setAccessibilityNextFocusIdAttribute((this._accessibilityNextFocusId_0_0value as string | undefined));
                    flagArray[133] = 2;
                    break;
                }
                case 3: {
                    flagArray[133] = 2;
                    break;
                }
                default: {
                    flagArray[133] = 0;
                    peer.setAccessibilityNextFocusIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[134] != 0)
        {
            switch (flagArray[134] as int32) {
                case 1: {
                    peer.setAccessibilityDefaultFocusAttribute((this._accessibilityDefaultFocus_0_0value as boolean | undefined));
                    flagArray[134] = 2;
                    break;
                }
                case 3: {
                    flagArray[134] = 2;
                    break;
                }
                default: {
                    flagArray[134] = 0;
                    peer.setAccessibilityDefaultFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[135] != 0)
        {
            switch (flagArray[135] as int32) {
                case 1: {
                    peer.setAccessibilityUseSamePageAttribute((this._accessibilityUseSamePage_0_0value as AccessibilitySamePageMode | undefined));
                    flagArray[135] = 2;
                    break;
                }
                case 3: {
                    flagArray[135] = 2;
                    break;
                }
                default: {
                    flagArray[135] = 0;
                    peer.setAccessibilityUseSamePageAttribute((undefined as AccessibilitySamePageMode | undefined));
                }
            }
        }
        if (flagArray[136] != 0)
        {
            switch (flagArray[136] as int32) {
                case 1: {
                    peer.setAccessibilityScrollTriggerableAttribute((this._accessibilityScrollTriggerable_0_0value as boolean | undefined));
                    flagArray[136] = 2;
                    break;
                }
                case 3: {
                    flagArray[136] = 2;
                    break;
                }
                default: {
                    flagArray[136] = 0;
                    peer.setAccessibilityScrollTriggerableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[137] != 0)
        {
            switch (flagArray[137] as int32) {
                case 1: {
                    peer.setAccessibilityTextOfResourceTypeAttribute((this._accessibilityTextOfResourceType_0_0value as Resource | undefined));
                    flagArray[137] = 2;
                    break;
                }
                case 3: {
                    flagArray[137] = 2;
                    break;
                }
                default: {
                    flagArray[137] = 0;
                    peer.setAccessibilityTextOfResourceTypeAttribute((undefined as Resource | undefined));
                }
            }
        }
        if (flagArray[138] != 0)
        {
            switch (flagArray[138] as int32) {
                case 1: {
                    peer.setAccessibilityRoleAttribute((this._accessibilityRole_0_0value as AccessibilityRoleType | undefined));
                    flagArray[138] = 2;
                    break;
                }
                case 3: {
                    flagArray[138] = 2;
                    break;
                }
                default: {
                    flagArray[138] = 0;
                    peer.setAccessibilityRoleAttribute((undefined as AccessibilityRoleType | undefined));
                }
            }
        }
        if (flagArray[139] != 0)
        {
            switch (flagArray[139] as int32) {
                case 1: {
                    peer.setOnAccessibilityFocusAttribute((this._onAccessibilityFocus_0_0value as AccessibilityFocusCallback | undefined));
                    flagArray[139] = 2;
                    break;
                }
                case 3: {
                    flagArray[139] = 2;
                    break;
                }
                default: {
                    flagArray[139] = 0;
                    peer.setOnAccessibilityFocusAttribute((undefined as AccessibilityFocusCallback | undefined));
                }
            }
        }
    }
    applyModifierPatch7(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[140] != 0)
        {
            switch (flagArray[140] as int32) {
                case 1: {
                    peer.setOnAccessibilityActionInterceptAttribute((this._onAccessibilityActionIntercept_0_0value as AccessibilityActionInterceptCallback | undefined));
                    flagArray[140] = 2;
                    break;
                }
                case 3: {
                    flagArray[140] = 2;
                    break;
                }
                default: {
                    flagArray[140] = 0;
                    peer.setOnAccessibilityActionInterceptAttribute((undefined as AccessibilityActionInterceptCallback | undefined));
                }
            }
        }
        if (flagArray[141] != 0)
        {
            switch (flagArray[141] as int32) {
                case 1: {
                    peer.setAccessibilityTextHintAttribute((this._accessibilityTextHint_0_0value as string | undefined));
                    flagArray[141] = 2;
                    break;
                }
                case 3: {
                    flagArray[141] = 2;
                    break;
                }
                default: {
                    flagArray[141] = 0;
                    peer.setAccessibilityTextHintAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[142] != 0)
        {
            switch (flagArray[142] as int32) {
                case 1: {
                    peer.setAccessibilityDescriptionOfStringTypeAttribute((this._accessibilityDescriptionOfStringType_0_0value as string | undefined));
                    flagArray[142] = 2;
                    break;
                }
                case 3: {
                    flagArray[142] = 2;
                    break;
                }
                default: {
                    flagArray[142] = 0;
                    peer.setAccessibilityDescriptionOfStringTypeAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[143] != 0)
        {
            switch (flagArray[143] as int32) {
                case 1: {
                    peer.setAccessibilityDescriptionOfResourceTypeAttribute((this._accessibilityDescriptionOfResourceType_0_0value as Resource | undefined));
                    flagArray[143] = 2;
                    break;
                }
                case 3: {
                    flagArray[143] = 2;
                    break;
                }
                default: {
                    flagArray[143] = 0;
                    peer.setAccessibilityDescriptionOfResourceTypeAttribute((undefined as Resource | undefined));
                }
            }
        }
        if (flagArray[144] != 0)
        {
            switch (flagArray[144] as int32) {
                case 1: {
                    peer.setAccessibilityLevelAttribute((this._accessibilityLevel_0_0value as string | undefined));
                    flagArray[144] = 2;
                    break;
                }
                case 3: {
                    flagArray[144] = 2;
                    break;
                }
                default: {
                    flagArray[144] = 0;
                    peer.setAccessibilityLevelAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[145] != 0)
        {
            switch (flagArray[145] as int32) {
                case 1: {
                    peer.setAccessibilityVirtualNodeAttribute((this._accessibilityVirtualNode_0_0value as CustomBuilder | undefined));
                    flagArray[145] = 2;
                    break;
                }
                case 3: {
                    flagArray[145] = 2;
                    break;
                }
                default: {
                    flagArray[145] = 0;
                    peer.setAccessibilityVirtualNodeAttribute((undefined as CustomBuilder | undefined));
                }
            }
        }
        if (flagArray[146] != 0)
        {
            switch (flagArray[146] as int32) {
                case 1: {
                    peer.setAccessibilityCheckedAttribute((this._accessibilityChecked_0_0value as boolean | undefined));
                    flagArray[146] = 2;
                    break;
                }
                case 3: {
                    flagArray[146] = 2;
                    break;
                }
                default: {
                    flagArray[146] = 0;
                    peer.setAccessibilityCheckedAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[147] != 0)
        {
            switch (flagArray[147] as int32) {
                case 1: {
                    peer.setAccessibilitySelectedAttribute((this._accessibilitySelected_0_0value as boolean | undefined));
                    flagArray[147] = 2;
                    break;
                }
                case 3: {
                    flagArray[147] = 2;
                    break;
                }
                default: {
                    flagArray[147] = 0;
                    peer.setAccessibilitySelectedAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[148] != 0)
        {
            switch (flagArray[148] as int32) {
                case 1: {
                    peer.setObscuredAttribute((this._obscured_0_0value as Array<ObscuredReasons> | undefined));
                    flagArray[148] = 2;
                    break;
                }
                case 3: {
                    flagArray[148] = 2;
                    break;
                }
                default: {
                    flagArray[148] = 0;
                    peer.setObscuredAttribute((undefined as Array<ObscuredReasons> | undefined));
                }
            }
        }
        if (flagArray[149] != 0)
        {
            switch (flagArray[149] as int32) {
                case 1: {
                    peer.setReuseIdAttribute((this._reuseId_0_0value as string | undefined));
                    flagArray[149] = 2;
                    break;
                }
                case 3: {
                    flagArray[149] = 2;
                    break;
                }
                default: {
                    flagArray[149] = 0;
                    peer.setReuseIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[150] != 0)
        {
            switch (flagArray[150] as int32) {
                case 1: {
                    peer.setReuseAttribute((this._reuse_0_0value as ReuseOptions | undefined));
                    flagArray[150] = 2;
                    break;
                }
                case 3: {
                    flagArray[150] = 2;
                    break;
                }
                default: {
                    flagArray[150] = 0;
                    peer.setReuseAttribute((undefined as ReuseOptions | undefined));
                }
            }
        }
        if (flagArray[151] != 0)
        {
            switch (flagArray[151] as int32) {
                case 1: {
                    peer.setRenderFitAttribute((this._renderFit_0_0value as RenderFit | undefined));
                    flagArray[151] = 2;
                    break;
                }
                case 3: {
                    flagArray[151] = 2;
                    break;
                }
                default: {
                    flagArray[151] = 0;
                    peer.setRenderFitAttribute((undefined as RenderFit | undefined));
                }
            }
        }
        if (flagArray[152] != 0)
        {
            switch (flagArray[152] as int32) {
                case 1: {
                    peer.setBackgroundBrightnessAttribute((this._backgroundBrightness_0_0value as BackgroundBrightnessOptions | undefined));
                    flagArray[152] = 2;
                    break;
                }
                case 3: {
                    flagArray[152] = 2;
                    break;
                }
                default: {
                    flagArray[152] = 0;
                    peer.setBackgroundBrightnessAttribute((undefined as BackgroundBrightnessOptions | undefined));
                }
            }
        }
        if (flagArray[153] != 0)
        {
            switch (flagArray[153] as int32) {
                case 1: {
                    peer.setOnGestureJudgeBeginAttribute((this._onGestureJudgeBegin_0_0value as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined));
                    flagArray[153] = 2;
                    break;
                }
                case 3: {
                    flagArray[153] = 2;
                    break;
                }
                default: {
                    flagArray[153] = 0;
                    peer.setOnGestureJudgeBeginAttribute((undefined as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined));
                }
            }
        }
        if (flagArray[154] != 0)
        {
            switch (flagArray[154] as int32) {
                case 1: {
                    peer.setOnGestureRecognizerJudgeBegin0Attribute((this._onGestureRecognizerJudgeBegin_0_0value as GestureRecognizerJudgeBeginCallback | undefined));
                    flagArray[154] = 2;
                    break;
                }
                case 3: {
                    flagArray[154] = 2;
                    break;
                }
                default: {
                    flagArray[154] = 0;
                    peer.setOnGestureRecognizerJudgeBegin0Attribute((undefined as GestureRecognizerJudgeBeginCallback | undefined));
                }
            }
        }
        if (flagArray[155] != 0)
        {
            switch (flagArray[155] as int32) {
                case 1: {
                    peer.setShouldBuiltInRecognizerParallelWithAttribute((this._shouldBuiltInRecognizerParallelWith_0_0value as ShouldBuiltInRecognizerParallelWithCallback | undefined));
                    flagArray[155] = 2;
                    break;
                }
                case 3: {
                    flagArray[155] = 2;
                    break;
                }
                default: {
                    flagArray[155] = 0;
                    peer.setShouldBuiltInRecognizerParallelWithAttribute((undefined as ShouldBuiltInRecognizerParallelWithCallback | undefined));
                }
            }
        }
        if (flagArray[156] != 0)
        {
            switch (flagArray[156] as int32) {
                case 1: {
                    peer.setMonopolizeEventsAttribute((this._monopolizeEvents_0_0value as boolean | undefined));
                    flagArray[156] = 2;
                    break;
                }
                case 3: {
                    flagArray[156] = 2;
                    break;
                }
                default: {
                    flagArray[156] = 0;
                    peer.setMonopolizeEventsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[157] != 0)
        {
            switch (flagArray[157] as int32) {
                case 1: {
                    peer.setOnTouchInterceptAttribute((this._onTouchIntercept_0_0value as ((value0: TouchEvent) => HitTestMode) | undefined));
                    flagArray[157] = 2;
                    break;
                }
                case 3: {
                    flagArray[157] = 2;
                    break;
                }
                default: {
                    flagArray[157] = 0;
                    peer.setOnTouchInterceptAttribute((undefined as ((value0: TouchEvent) => HitTestMode) | undefined));
                }
            }
        }
        if (flagArray[158] != 0)
        {
            switch (flagArray[158] as int32) {
                case 1: {
                    peer.setOnSizeChangeAttribute((this._onSizeChange_0_0value as SizeChangeCallback | undefined));
                    flagArray[158] = 2;
                    break;
                }
                case 3: {
                    flagArray[158] = 2;
                    break;
                }
                default: {
                    flagArray[158] = 0;
                    peer.setOnSizeChangeAttribute((undefined as SizeChangeCallback | undefined));
                }
            }
        }
        if (flagArray[159] != 0)
        {
            switch (flagArray[159] as int32) {
                case 1: {
                    peer.setAccessibilityFocusDrawLevelAttribute((this._accessibilityFocusDrawLevel_0_0value as FocusDrawLevel | undefined));
                    flagArray[159] = 2;
                    break;
                }
                case 3: {
                    flagArray[159] = 2;
                    break;
                }
                default: {
                    flagArray[159] = 0;
                    peer.setAccessibilityFocusDrawLevelAttribute((undefined as FocusDrawLevel | undefined));
                }
            }
        }
    }
    applyModifierPatch8(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[160] != 0) {
            switch (flagArray[160] as int32) {
                case 1: {
                    hookCustomPropertyImpl(peer, (this._customProperty_0_0value as string), (this._customProperty_0_1value as CustomProperty), this);
                    flagArray[160] = 2;
                    break;
                }
                case 3: {
                    flagArray[160] = 2;
                    break;
                }
                default: {
                    flagArray[160] = 0;
                }
            }
        }
        if (flagArray[161] != 0)
        {
            switch (flagArray[161] as int32) {
                case 1: {
                    peer.setExpandSafeAreaAttribute((this._expandSafeArea_0_0value as Array<SafeAreaType> | undefined | undefined), (this._expandSafeArea_0_1value as Array<SafeAreaEdge> | undefined | undefined));
                    flagArray[161] = 2;
                    break;
                }
                case 3: {
                    flagArray[161] = 2;
                    break;
                }
                default: {
                    flagArray[161] = 0;
                    peer.setExpandSafeAreaAttribute((undefined as Array<SafeAreaType> | undefined | undefined), (undefined as Array<SafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (flagArray[162] != 0)
        {
            switch (flagArray[162] as int32) {
                case 1: {
                    peer.setIgnoreLayoutSafeAreaAttribute((this._ignoreLayoutSafeArea_0_0value as Array<LayoutSafeAreaType> | undefined | undefined), (this._ignoreLayoutSafeArea_0_1value as Array<LayoutSafeAreaEdge> | undefined | undefined));
                    flagArray[162] = 2;
                    break;
                }
                case 3: {
                    flagArray[162] = 2;
                    break;
                }
                default: {
                    flagArray[162] = 0;
                    peer.setIgnoreLayoutSafeAreaAttribute((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (flagArray[163] != 0)
        {
            switch (flagArray[163] as int32) {
                case 1: {
                    peer.setBackgroundAttribute((this._background_0_0value as CustomBuilder | undefined), (this._background_0_1value as BackgroundOptions | undefined | undefined));
                    flagArray[163] = 2;
                    break;
                }
                case 3: {
                    flagArray[163] = 2;
                    break;
                }
                default: {
                    flagArray[163] = 0;
                    peer.setBackgroundAttribute((undefined as CustomBuilder | undefined), (undefined as BackgroundOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[164] != 0)
        {
            switch (flagArray[164] as int32) {
                case 1: {
                    peer.setBackgroundImage1Attribute((this._backgroundImage_1_0value as ResourceStr | image.PixelMap | undefined), (this._backgroundImage_1_1value as BackgroundImageOptions));
                    flagArray[164] = 2;
                    break;
                }
                case 3: {
                    flagArray[164] = 2;
                    break;
                }
                default: {
                    flagArray[164] = 0;
                    peer.setBackgroundImage1Attribute((undefined as ResourceStr | image.PixelMap | undefined), (undefined as BackgroundImageOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[165] != 0)
        {
            switch (flagArray[165] as int32) {
                case 1: {
                    peer.setBackgroundImage2Attribute((this._backgroundImage_2_0value as ResourceStr | image.PixelMap | undefined), (this._backgroundImage_2_1value as ImageRepeat));
                    flagArray[165] = 2;
                    break;
                }
                case 3: {
                    flagArray[165] = 2;
                    break;
                }
                default: {
                    flagArray[165] = 0;
                    peer.setBackgroundImage2Attribute((undefined as ResourceStr | image.PixelMap | undefined), (undefined as ImageRepeat | undefined | undefined));
                }
            }
        }
        if (flagArray[166] != 0)
        {
            switch (flagArray[166] as int32) {
                case 1: {
                    peer.setBackgroundBlurStyleAttribute((this._backgroundBlurStyle_0_0value as BlurStyle | undefined), (this._backgroundBlurStyle_0_1value as BackgroundBlurStyleOptions | undefined | undefined), (this._backgroundBlurStyle_0_2value as SystemAdaptiveOptions | undefined | undefined));
                    flagArray[166] = 2;
                    break;
                }
                case 3: {
                    flagArray[166] = 2;
                    break;
                }
                default: {
                    flagArray[166] = 0;
                    peer.setBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[167] != 0)
        {
            switch (flagArray[167] as int32) {
                case 1: {
                    peer.setBackgroundEffect1Attribute((this._backgroundEffect_1_0value as BackgroundEffectOptions | undefined), (this._backgroundEffect_1_1value as SystemAdaptiveOptions | undefined | undefined));
                    flagArray[167] = 2;
                    break;
                }
                case 3: {
                    flagArray[167] = 2;
                    break;
                }
                default: {
                    flagArray[167] = 0;
                    peer.setBackgroundEffect1Attribute((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[168] != 0)
        {
            switch (flagArray[168] as int32) {
                case 1: {
                    peer.setForegroundBlurStyleAttribute((this._foregroundBlurStyle_0_0value as BlurStyle | undefined), (this._foregroundBlurStyle_0_1value as ForegroundBlurStyleOptions | undefined | undefined), (this._foregroundBlurStyle_0_2value as SystemAdaptiveOptions | undefined | undefined));
                    flagArray[168] = 2;
                    break;
                }
                case 3: {
                    flagArray[168] = 2;
                    break;
                }
                default: {
                    flagArray[168] = 0;
                    peer.setForegroundBlurStyleAttribute((undefined as BlurStyle | undefined), (undefined as ForegroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[169] != 0)
        {
            switch (flagArray[169] as int32) {
                case 1: {
                    peer.setBorderRadius1Attribute((this._borderRadius_1_0value as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined), (this._borderRadius_1_1value as RenderStrategy | undefined | undefined));
                    flagArray[169] = 2;
                    break;
                }
                case 3: {
                    flagArray[169] = 2;
                    break;
                }
                default: {
                    flagArray[169] = 0;
                    peer.setBorderRadius1Attribute((undefined as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined), (undefined as RenderStrategy | undefined | undefined));
                }
            }
        }
        if (flagArray[170] != 0)
        {
            switch (flagArray[170] as int32) {
                case 1: {
                    peer.setOnClick1Attribute((this._onClick_1_0value as ((event: ClickEvent) => void) | undefined), (this._onClick_1_1value as double | undefined));
                    flagArray[170] = 2;
                    break;
                }
                case 3: {
                    flagArray[170] = 2;
                    break;
                }
                default: {
                    flagArray[170] = 0;
                    peer.setOnClick1Attribute((undefined as ((event: ClickEvent) => void) | undefined), (undefined as double | undefined));
                }
            }
        }
        if (flagArray[171] != 0)
        {
            switch (flagArray[171] as int32) {
                case 1: {
                    peer.setFocusScopeIdAttribute((this._focusScopeId_0_0value as string | undefined), (this._focusScopeId_0_1value as boolean | undefined | undefined), (this._focusScopeId_0_2value as boolean | undefined | undefined));
                    flagArray[171] = 2;
                    break;
                }
                case 3: {
                    flagArray[171] = 2;
                    break;
                }
                default: {
                    flagArray[171] = 0;
                    peer.setFocusScopeIdAttribute((undefined as string | undefined), (undefined as boolean | undefined | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[172] != 0)
        {
            switch (flagArray[172] as int32) {
                case 1: {
                    peer.setFocusScopePriorityAttribute((this._focusScopePriority_0_0value as string | undefined), (this._focusScopePriority_0_1value as FocusPriority | undefined | undefined));
                    flagArray[172] = 2;
                    break;
                }
                case 3: {
                    flagArray[172] = 2;
                    break;
                }
                default: {
                    flagArray[172] = 0;
                    peer.setFocusScopePriorityAttribute((undefined as string | undefined), (undefined as FocusPriority | undefined | undefined));
                }
            }
        }
        if (flagArray[173] != 0)
        {
            switch (flagArray[173] as int32) {
                case 1: {
                    peer.setTransition1Attribute((this._transition_1_0value as TransitionEffect | undefined), (this._transition_1_1value as TransitionFinishCallback | undefined));
                    flagArray[173] = 2;
                    break;
                }
                case 3: {
                    flagArray[173] = 2;
                    break;
                }
                default: {
                    flagArray[173] = 0;
                    peer.setTransition1Attribute((undefined as TransitionEffect | undefined), (undefined as TransitionFinishCallback | undefined));
                }
            }
        }
        if (flagArray[174] != 0)
        {
            switch (flagArray[174] as int32) {
                case 1: {
                    peer.setBlurAttribute((this._blur_0_0value as double | undefined), (this._blur_0_1value as BlurOptions | undefined), (this._blur_0_2value as SystemAdaptiveOptions | undefined));
                    flagArray[174] = 2;
                    break;
                }
                case 3: {
                    flagArray[174] = 2;
                    break;
                }
                default: {
                    flagArray[174] = 0;
                    peer.setBlurAttribute((undefined as double | undefined), (undefined as BlurOptions | undefined), (undefined as SystemAdaptiveOptions | undefined));
                }
            }
        }
        if (flagArray[175] != 0)
        {
            switch (flagArray[175] as int32) {
                case 1: {
                    peer.setLinearGradientBlurAttribute((this._linearGradientBlur_0_0value as double | undefined), (this._linearGradientBlur_0_1value as LinearGradientBlurOptions | undefined));
                    flagArray[175] = 2;
                    break;
                }
                case 3: {
                    flagArray[175] = 2;
                    break;
                }
                default: {
                    flagArray[175] = 0;
                    peer.setLinearGradientBlurAttribute((undefined as double | undefined), (undefined as LinearGradientBlurOptions | undefined));
                }
            }
        }
        if (flagArray[176] != 0)
        {
            switch (flagArray[176] as int32) {
                case 1: {
                    peer.setSystemBarEffectAttribute();
                    flagArray[176] = 2;
                    break;
                }
                case 3: {
                    flagArray[176] = 2;
                    break;
                }
                default: {
                    flagArray[176] = 0;
                    peer.setSystemBarEffectAttribute();
                }
            }
        }
        if (flagArray[177] != 0)
        {
            switch (flagArray[177] as int32) {
                case 1: {
                    peer.setUseEffect1Attribute((this._useEffect_1_0value as boolean | undefined), (this._useEffect_1_1value as EffectType | undefined));
                    flagArray[177] = 2;
                    break;
                }
                case 3: {
                    flagArray[177] = 2;
                    break;
                }
                default: {
                    flagArray[177] = 0;
                    peer.setUseEffect1Attribute((undefined as boolean | undefined), (undefined as EffectType | undefined));
                }
            }
        }
        if (flagArray[178] != 0)
        {
            switch (flagArray[178] as int32) {
                case 1: {
                    peer.setBackdropBlurAttribute((this._backdropBlur_0_0value as double | undefined), (this._backdropBlur_0_1value as BlurOptions | undefined), (this._backdropBlur_0_2value as SystemAdaptiveOptions | undefined));
                    flagArray[178] = 2;
                    break;
                }
                case 3: {
                    flagArray[178] = 2;
                    break;
                }
                default: {
                    flagArray[178] = 0;
                    peer.setBackdropBlurAttribute((undefined as number | undefined), (undefined as BlurOptions | undefined), (undefined as SystemAdaptiveOptions | undefined));
                }
            }
        }
        if (flagArray[179] != 0)
        {
            switch (flagArray[179] as int32) {
                case 1: {
                    peer.setSharedTransitionAttribute((this._sharedTransition_0_0value as string | undefined), (this._sharedTransition_0_1value as sharedTransitionOptions | undefined | undefined));
                    flagArray[179] = 2;
                    break;
                }
                case 3: {
                    flagArray[179] = 2;
                    break;
                }
                default: {
                    flagArray[179] = 0;
                    peer.setSharedTransitionAttribute((undefined as string | undefined), (undefined as sharedTransitionOptions | undefined | undefined));
                }
            }
        }
    }
    applyModifierPatch9(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[180] != 0)
        {
            switch (flagArray[180] as int32) {
                case 1: {
                    peer.setChainModeAttribute((this._chainMode_0_0value as Axis | undefined), (this._chainMode_0_1value as ChainStyle | undefined));
                    flagArray[180] = 2;
                    break;
                }
                case 3: {
                    flagArray[180] = 2;
                    break;
                }
                default: {
                    flagArray[180] = 0;
                    peer.setChainModeAttribute((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (flagArray[181] != 0)
        {
            switch (flagArray[181] as int32) {
                case 1: {
                    peer.setOnDrop1Attribute((this._onDrop_1_0value as OnDragEventCallback | undefined), (this._onDrop_1_1value as DropOptions | undefined | undefined));
                    flagArray[181] = 2;
                    break;
                }
                case 3: {
                    flagArray[181] = 2;
                    break;
                }
                default: {
                    flagArray[181] = 0;
                    peer.setOnDrop1Attribute((undefined as OnDragEventCallback | undefined), (undefined as DropOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[182] != 0)
        {
            switch (flagArray[182] as int32) {
                case 1: {
                    peer.setDragPreview1Attribute((this._dragPreview_1_0value as CustomBuilder | DragItemInfo | string | undefined), (this._dragPreview_1_1value as PreviewConfiguration | undefined | undefined));
                    flagArray[182] = 2;
                    break;
                }
                case 3: {
                    flagArray[182] = 2;
                    break;
                }
                default: {
                    flagArray[182] = 0;
                    peer.setDragPreview1Attribute((undefined as CustomBuilder | DragItemInfo | string | undefined), (undefined as PreviewConfiguration | undefined | undefined));
                }
            }
        }
        if (flagArray[183] != 0)
        {
            switch (flagArray[183] as int32) {
                case 1: {
                    hookDragPreviewOptions(peer, (this._dragPreviewOptions_0_0value as DragPreviewOptions | undefined), (this._dragPreviewOptions_0_1value as DragInteractionOptions | undefined | undefined));
                    flagArray[183] = 2;
                    break;
                }
                case 3: {
                    flagArray[183] = 2;
                    break;
                }
                default: {
                    flagArray[183] = 0;
                    hookDragPreviewOptions(peer, (undefined as DragPreviewOptions | undefined), (undefined as DragInteractionOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[184] != 0)
        {
            switch (flagArray[184] as int32) {
                case 1: {
                    peer.setOverlayAttribute((this._overlay_0_0value as string | CustomBuilder | ComponentContent | undefined), (this._overlay_0_1value as OverlayOptions | undefined | undefined));
                    flagArray[184] = 2;
                    break;
                }
                case 3: {
                    flagArray[184] = 2;
                    break;
                }
                default: {
                    flagArray[184] = 0;
                    peer.setOverlayAttribute((undefined as string | CustomBuilder | ComponentContent | undefined), (undefined as OverlayOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[185] != 0)
        {
            switch (flagArray[185] as int32) {
                case 1: {
                    peer.setBlendModeAttribute((this._blendMode_0_0value as BlendMode | undefined), (this._blendMode_0_1value as BlendApplyType | undefined | undefined));
                    flagArray[185] = 2;
                    break;
                }
                case 3: {
                    flagArray[185] = 2;
                    break;
                }
                default: {
                    flagArray[185] = 0;
                    peer.setBlendModeAttribute((undefined as BlendMode | undefined), (undefined as BlendApplyType | undefined | undefined));
                }
            }
        }
        if (flagArray[186] != 0)
        {
            switch (flagArray[186] as int32) {
                case 1: {
                    peer.setAdvancedBlendModeAttribute((this._advancedBlendMode_0_0value as BlendMode | uiEffect.Blender | undefined), (this._advancedBlendMode_0_1value as BlendApplyType | undefined));
                    flagArray[186] = 2;
                    break;
                }
                case 3: {
                    flagArray[186] = 2;
                    break;
                }
                default: {
                    flagArray[186] = 0;
                    peer.setAdvancedBlendModeAttribute((undefined as BlendMode | uiEffect.Blender | undefined), (undefined as BlendApplyType | undefined));
                }
            }
        }
        if (flagArray[187] != 0)
        {
            switch (flagArray[187] as int32) {
                case 1: {
                    peer.setGeometryTransition1Attribute((this._geometryTransition_1_0value as string | undefined), (this._geometryTransition_1_1value as GeometryTransitionOptions | undefined | undefined));
                    flagArray[187] = 2;
                    break;
                }
                case 3: {
                    flagArray[187] = 2;
                    break;
                }
                default: {
                    flagArray[187] = 0;
                    peer.setGeometryTransition1Attribute((undefined as string | undefined), (undefined as GeometryTransitionOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[188] != 0)
        {
            switch (flagArray[188] as int32) {
                case 1: {
                    peer.setBindTipsAttribute((this._bindTips_0_0value as TipsMessageType | undefined), (this._bindTips_0_1value as TipsOptions | undefined | undefined));
                    flagArray[188] = 2;
                    break;
                }
                case 3: {
                    flagArray[188] = 2;
                    break;
                }
                default: {
                    flagArray[188] = 0;
                    peer.setBindTipsAttribute((undefined as TipsMessageType | undefined), (undefined as TipsOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[189] != 0)
        {
            switch (flagArray[189] as int32) {
                case 1: {
                    peer.setBindPopupAttribute((this._bindPopup_0_0value as boolean | undefined), (this._bindPopup_0_1value as PopupOptions | CustomPopupOptions | undefined));
                    flagArray[189] = 2;
                    break;
                }
                case 3: {
                    flagArray[189] = 2;
                    break;
                }
                default: {
                    flagArray[189] = 0;
                    peer.setBindPopupAttribute((undefined as boolean | undefined), (undefined as PopupOptions | CustomPopupOptions | undefined));
                }
            }
        }
        if (flagArray[190] != 0)
        {
            switch (flagArray[190] as int32) {
                case 1: {
                    peer.setBindMenu0Attribute((this._bindMenu_0_0value as Array<MenuElement> | CustomBuilder | undefined), (this._bindMenu_0_1value as MenuOptions | undefined | undefined));
                    flagArray[190] = 2;
                    break;
                }
                case 3: {
                    flagArray[190] = 2;
                    break;
                }
                default: {
                    flagArray[190] = 0;
                    peer.setBindMenu0Attribute((undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[191] != 0)
        {
            switch (flagArray[191] as int32) {
                case 1: {
                    peer.setBindMenu1Attribute((this._bindMenu_1_0value as boolean | undefined), (this._bindMenu_1_1value as Array<MenuElement> | CustomBuilder | undefined), (this._bindMenu_1_2value as MenuOptions | undefined | undefined));
                    flagArray[191] = 2;
                    break;
                }
                case 3: {
                    flagArray[191] = 2;
                    break;
                }
                default: {
                    flagArray[191] = 0;
                    peer.setBindMenu1Attribute((undefined as boolean | undefined), (undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[192] != 0)
        {
            switch (flagArray[192] as int32) {
                case 1: {
                    peer.setBindContextMenu0Attribute((this._bindContextMenu_0_0value as CustomBuilder | undefined), (this._bindContextMenu_0_1value as ResponseType | undefined), (this._bindContextMenu_0_2value as ContextMenuOptions | undefined | undefined));
                    flagArray[192] = 2;
                    break;
                }
                case 3: {
                    flagArray[192] = 2;
                    break;
                }
                default: {
                    flagArray[192] = 0;
                    peer.setBindContextMenu0Attribute((undefined as CustomBuilder | undefined), (undefined as ResponseType | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[193] != 0)
        {
            switch (flagArray[193] as int32) {
                case 1: {
                    peer.setBindContextMenuWithResponseAttribute((this._bindContextMenuWithResponse_0_0value as CustomBuilderT<ResponseType> | undefined), (this._bindContextMenuWithResponse_0_1value as ContextMenuOptions | undefined));
                    flagArray[193] = 2;
                    break;
                }
                case 3: {
                    flagArray[193] = 2;
                    break;
                }
                default: {
                    flagArray[193] = 0;
                    peer.setBindContextMenuWithResponseAttribute((undefined as CustomBuilderT<ResponseType> | undefined), (undefined as ContextMenuOptions | undefined));
                }
            }
        }
        if (flagArray[194] != 0)
        {
            switch (flagArray[194] as int32) {
                case 1: {
                    peer.setBindContextMenu1Attribute((this._bindContextMenu_1_0value as boolean | undefined), (this._bindContextMenu_1_1value as CustomBuilder | undefined), (this._bindContextMenu_1_2value as ContextMenuOptions | undefined | undefined));
                    flagArray[194] = 2;
                    break;
                }
                case 3: {
                    flagArray[194] = 2;
                    break;
                }
                default: {
                    flagArray[194] = 0;
                    peer.setBindContextMenu1Attribute((undefined as boolean | undefined), (undefined as CustomBuilder | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[195] != 0)
        {
            switch (flagArray[195] as int32) {
                case 1: {
                    peer.setBindContentCover0Attribute((this._bindContentCover_0_0value as boolean | Bindable<boolean> | undefined), (this._bindContentCover_0_1value as CustomBuilder | undefined), (this._bindContentCover_0_2value as ModalTransition | undefined | undefined));
                    flagArray[195] = 2;
                    break;
                }
                case 3: {
                    flagArray[195] = 2;
                    break;
                }
                default: {
                    flagArray[195] = 0;
                    peer.setBindContentCover0Attribute((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ModalTransition | undefined | undefined));
                }
            }
        }
        if (flagArray[196] != 0)
        {
            switch (flagArray[196] as int32) {
                case 1: {
                    peer.setBindContentCover1Attribute((this._bindContentCover_1_0value as boolean | Bindable<boolean> | undefined), (this._bindContentCover_1_1value as CustomBuilder | undefined), (this._bindContentCover_1_2value as ContentCoverOptions | undefined | undefined));
                    flagArray[196] = 2;
                    break;
                }
                case 3: {
                    flagArray[196] = 2;
                    break;
                }
                default: {
                    flagArray[196] = 0;
                    peer.setBindContentCover1Attribute((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ContentCoverOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[197] != 0)
        {
            switch (flagArray[197] as int32) {
                case 1: {
                    peer.setBindSheetAttribute((this._bindSheet_0_0value as boolean | Bindable<boolean> | undefined), (this._bindSheet_0_1value as CustomBuilder | undefined), (this._bindSheet_0_2value as SheetOptions | undefined | undefined));
                    flagArray[197] = 2;
                    break;
                }
                case 3: {
                    flagArray[197] = 2;
                    break;
                }
                default: {
                    flagArray[197] = 0;
                    peer.setBindSheetAttribute((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as SheetOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[198] != 0)
        {
            switch (flagArray[198] as int32) {
                case 1: {
                    peer.setOnVisibleAreaChangeAttribute((this._onVisibleAreaChange_0_0value as Array<double> | undefined), (this._onVisibleAreaChange_0_1value as VisibleAreaChangeCallback | undefined));
                    flagArray[198] = 2;
                    break;
                }
                case 3: {
                    flagArray[198] = 2;
                    break;
                }
                default: {
                    flagArray[198] = 0;
                    peer.setOnVisibleAreaChangeAttribute((undefined as Array<double> | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (flagArray[199] != 0)
        {
            switch (flagArray[199] as int32) {
                case 1: {
                    peer.setOnVisibleAreaApproximateChangeAttribute((this._onVisibleAreaApproximateChange_0_0value as VisibleAreaEventOptions | undefined), (this._onVisibleAreaApproximateChange_0_1value as VisibleAreaChangeCallback | undefined));
                    flagArray[199] = 2;
                    break;
                }
                case 3: {
                    flagArray[199] = 2;
                    break;
                }
                default: {
                    flagArray[199] = 0;
                    peer.setOnVisibleAreaApproximateChangeAttribute((undefined as VisibleAreaEventOptions | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (flagArray[200] != 0)
        {
            switch (flagArray[200] as int32) {
                case 1: {
                    hookKeyboardShortcut(peer, this._keyboardShortcutList);
                    flagArray[200] = 2;
                    break;
                }
                case 3: {
                    flagArray[200] = 2;
                    break;
                }
                default: {
                    flagArray[200] = 0;
                    peer.setKeyboardShortcutAttribute((undefined as string | FunctionKey | undefined), (undefined as Array<ModifierKey> | undefined), (undefined as (() => void) | undefined | undefined));
                }
            }
        }
    }
    applyModifierPatch10(peer: ArkCommonMethodPeer, flagArray: Uint8Array): void {
        if (flagArray[201] != 0)
        {
            switch (flagArray[201] as int32) {
                case 1: {
                    peer.setAccessibilityGroupWithConfigAttribute((this._accessibilityGroup_1_0value as boolean | undefined), (this._accessibilityGroup_1_1value as AccessibilityOptions | undefined));
                    flagArray[201] = 2;
                    break;
                }
                case 3: {
                    flagArray[201] = 2;
                    break;
                }
                default: {
                    flagArray[201] = 0;
                    peer.setAccessibilityGroupWithConfigAttribute((undefined as boolean | undefined), (undefined as AccessibilityOptions | undefined));
                }
            }
        }
        if (flagArray[202] != 0)
        {
            switch (flagArray[202] as int32) {
                case 1: {
                    peer.setOnGestureRecognizerJudgeBegin1Attribute((this._onGestureRecognizerJudgeBegin_1_0value as GestureRecognizerJudgeBeginCallback | undefined), (this._onGestureRecognizerJudgeBegin_1_1value as boolean | undefined));
                    flagArray[202] = 2;
                    break;
                }
                case 3: {
                    flagArray[202] = 2;
                    break;
                }
                default: {
                    flagArray[202] = 0;
                    peer.setOnGestureRecognizerJudgeBegin1Attribute((undefined as GestureRecognizerJudgeBeginCallback | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[203] != 0)
        {
            switch (flagArray[203] as int32) {
                case 1: {
                    peer.setSystemMaterialAttribute((this._systemMaterial_0_0value as uiMaterial.Material | undefined));
                    flagArray[203] = 2;
                    break;
                }
                case 3: {
                    flagArray[203] = 2;
                    break;
                }
                default: {
                    flagArray[203] = 0;
                    peer.setSystemMaterialAttribute((undefined as uiMaterial.Material | undefined));
                }
            }
        }
        if (flagArray[204] != 0) {
            switch (flagArray[204] as int32) {
                case 1: {
                    peer.setAccessibilityStateDescriptionAttribute((this._accessibilityStateDescription_0_0value as string | Resource | undefined));
                    flagArray[204] = 2;
                    break;
                }
                case 3: {
                    flagArray[204] = 2;
                    break;
                }
                default: {
                    flagArray[204] = 0;
                    peer.setAccessibilityStateDescriptionAttribute((undefined as string | Resource | undefined));
                }
            }
        }
        if (flagArray[205] != 0)
        {
            switch (flagArray[205] as int32) {
                case 1: {
                    peer.setAccessibilityActionOptionsAttribute((this._accessibilityActionOptions_0_0value as AccessibilityActionOptions | undefined));
                    flagArray[205] = 2;
                    break;
                }
                case 3: {
                    flagArray[205] = 2;
                    break;
                }
                default: {
                    flagArray[205] = 0;
                    peer.setAccessibilityActionOptionsAttribute((undefined as AccessibilityActionOptions | undefined));
                }
            }
        }
        if (flagArray[206] != 0)
        {
            switch (flagArray[206] as int32) {
                case 1: {
                    peer.setUseUnionEffectAttribute((this._useUnionEffect_0_0value as boolean | undefined));
                    flagArray[206] = 2;
                    break;
                }
                case 3: {
                    flagArray[206] = 2;
                    break;
                }
                default: {
                    flagArray[206] = 0;
                    peer.setUseUnionEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[207] != 0)
        {
            switch (flagArray[207] as int32) {
                case 1: {
                    peer.setMaterialFilterAttribute((this._materialFilter_0_0value as uiEffect.Filter | undefined));
                    flagArray[207] = 2;
                    break;
                }
                case 3: {
                    flagArray[207] = 2;
                    break;
                }
                default: {
                    flagArray[207] = 0;
                    peer.setMaterialFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CommonMethodModifier): void {
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
        this.mergeModifier1(modifier, flagArray);
        this.mergeModifier2(modifier, flagArray);
        this.mergeModifier3(modifier, flagArray);
        this.mergeModifier4(modifier, flagArray);
        this.mergeModifier5(modifier, flagArray);
        this.mergeModifier6(modifier, flagArray);
        this.mergeModifier7(modifier, flagArray);
        this.mergeModifier8(modifier, flagArray);
        this.mergeModifier9(modifier, flagArray);
        this.mergeModifier10(modifier, flagArray);
    }
    mergeModifier0(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0)
        {
            switch (flagArray[0] as int32) {
                case 1:
                case 3: {
                    this.width(modifier._width_0_0value);
                    break;
                }
                default: {
                    this.width((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (flagArray[1] != 0)
        {
            switch (flagArray[1] as int32) {
                case 1:
                case 3: {
                    this.height(modifier._height_0_0value);
                    break;
                }
                default: {
                    this.height((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (flagArray[2] != 0)
        {
            switch (flagArray[2] as int32) {
                case 1:
                case 3: {
                    this.responseRegion(modifier._responseRegion_0_0value);
                    break;
                }
                default: {
                    this.responseRegion((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (flagArray[3] != 0)
        {
            switch (flagArray[3] as int32) {
                case 1:
                case 3: {
                    this.mouseResponseRegion(modifier._mouseResponseRegion_0_0value);
                    break;
                }
                default: {
                    this.mouseResponseRegion((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (flagArray[4] != 0)
        {
            switch (flagArray[4] as int32) {
                case 1:
                case 3: {
                    this.responseRegionList(modifier._responseRegionList_0_0value);
                    break;
                }
                default: {
                    this.responseRegionList((undefined as Array<ResponseRegion> | undefined));
                }
            }
        }
        if (flagArray[5] != 0)
        {
            switch (flagArray[5] as int32) {
                case 1:
                case 3: {
                    this.size(modifier._size_0_0value);
                    break;
                }
                default: {
                    this.size((undefined as SizeOptions | undefined));
                }
            }
        }
        if (flagArray[6] != 0)
        {
            switch (flagArray[6] as int32) {
                case 1:
                case 3: {
                    this.constraintSize(modifier._constraintSize_0_0value);
                    break;
                }
                default: {
                    this.constraintSize((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (flagArray[7] != 0)
        {
            switch (flagArray[7] as int32) {
                case 1:
                case 3: {
                    this.hitTestBehavior(modifier._hitTestBehavior_0_0value);
                    break;
                }
                default: {
                    this.hitTestBehavior((undefined as HitTestMode | undefined));
                }
            }
        }
        if (flagArray[8] != 0)
        {
            switch (flagArray[8] as int32) {
                case 1:
                case 3: {
                    this.onChildTouchTest(modifier._onChildTouchTest_0_0value);
                    break;
                }
                default: {
                    this.onChildTouchTest((undefined as ((value: Array<TouchTestInfo>) => TouchResult) | undefined));
                }
            }
        }
        if (flagArray[9] != 0)
        {
            switch (flagArray[9] as int32) {
                case 1:
                case 3: {
                    this.layoutWeight(modifier._layoutWeight_0_0value);
                    break;
                }
                default: {
                    this.layoutWeight((undefined as number | string | undefined));
                }
            }
        }
        if (flagArray[10] != 0)
        {
            switch (flagArray[10] as int32) {
                case 1:
                case 3: {
                    this.chainWeight(modifier._chainWeight_0_0value);
                    break;
                }
                default: {
                    this.chainWeight((undefined as ChainWeightOptions | undefined));
                }
            }
        }
        if (flagArray[11] != 0)
        {
            switch (flagArray[11] as int32) {
                case 1:
                case 3: {
                    this.padding(modifier._padding_0_0value);
                    break;
                }
                default: {
                    this.padding((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (flagArray[12] != 0)
        {
            switch (flagArray[12] as int32) {
                case 1:
                case 3: {
                    this.safeAreaPadding(modifier._safeAreaPadding_0_0value);
                    break;
                }
                default: {
                    this.safeAreaPadding((undefined as Padding | LengthMetrics | LocalizedPadding | undefined));
                }
            }
        }
        if (flagArray[13] != 0)
        {
            switch (flagArray[13] as int32) {
                case 1:
                case 3: {
                    this.margin(modifier._margin_0_0value);
                    break;
                }
                default: {
                    this.margin((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (flagArray[14] != 0)
        {
            switch (flagArray[14] as int32) {
                case 1:
                case 3: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | ColorMetrics | undefined));
                }
            }
        }
        if (flagArray[15] != 0)
        {
            switch (flagArray[15] as int32) {
                case 1:
                case 3: {
                    this.pixelRound(modifier._pixelRound_0_0value);
                    break;
                }
                default: {
                    this.pixelRound((undefined as PixelRoundPolicy | undefined));
                }
            }
        }
        if (flagArray[16] != 0)
        {
            switch (flagArray[16] as int32) {
                case 1:
                case 3: {
                    this.backgroundImage(modifier._backgroundImage_0_0value);
                    break;
                }
                default: {
                    this.backgroundImage((undefined as ResourceStr | image.PixelMap | undefined));
                }
            }
        }
        if (flagArray[17] != 0)
        {
            switch (flagArray[17] as int32) {
                case 1:
                case 3: {
                    this.backgroundImageSize(modifier._backgroundImageSize_0_0value);
                    break;
                }
                default: {
                    this.backgroundImageSize((undefined as SizeOptions | ImageSize | undefined));
                }
            }
        }
        if (flagArray[18] != 0)
        {
            switch (flagArray[18] as int32) {
                case 1:
                case 3: {
                    this.backgroundImagePosition(modifier._backgroundImagePosition_0_0value);
                    break;
                }
                default: {
                    this.backgroundImagePosition((undefined as Position | Alignment | undefined));
                }
            }
        }
        if (flagArray[19] != 0)
        {
            switch (flagArray[19] as int32) {
                case 1:
                case 3: {
                    this.backgroundEffect(modifier._backgroundEffect_0_0value);
                    break;
                }
                default: {
                    this.backgroundEffect((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
    }
    mergeModifier1(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[20] != 0)
        {
            switch (flagArray[20] as int32) {
                case 1:
                case 3: {
                    this.backgroundImageResizable(modifier._backgroundImageResizable_0_0value);
                    break;
                }
                default: {
                    this.backgroundImageResizable((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (flagArray[21] != 0)
        {
            switch (flagArray[21] as int32) {
                case 1:
                case 3: {
                    this.foregroundEffect(modifier._foregroundEffect_0_0value);
                    break;
                }
                default: {
                    this.foregroundEffect((undefined as ForegroundEffectOptions | undefined));
                }
            }
        }
        if (flagArray[22] != 0)
        {
            switch (flagArray[22] as int32) {
                case 1:
                case 3: {
                    this.visualEffect(modifier._visualEffect_0_0value);
                    break;
                }
                default: {
                    this.visualEffect((undefined as uiEffect.VisualEffect | undefined));
                }
            }
        }
        if (flagArray[23] != 0)
        {
            switch (flagArray[23] as int32) {
                case 1:
                case 3: {
                    this.backgroundFilter(modifier._backgroundFilter_0_0value);
                    break;
                }
                default: {
                    this.backgroundFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (flagArray[24] != 0)
        {
            switch (flagArray[24] as int32) {
                case 1:
                case 3: {
                    this.foregroundFilter(modifier._foregroundFilter_0_0value);
                    break;
                }
                default: {
                    this.foregroundFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (flagArray[25] != 0)
        {
            switch (flagArray[25] as int32) {
                case 1:
                case 3: {
                    this.compositingFilter(modifier._compositingFilter_0_0value);
                    break;
                }
                default: {
                    this.compositingFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (flagArray[26] != 0)
        {
            switch (flagArray[26] as int32) {
                case 1:
                case 3: {
                    this.opacity(modifier._opacity_0_0value);
                    break;
                }
                default: {
                    this.opacity((undefined as double | Resource | undefined));
                }
            }
        }
        if (flagArray[27] != 0)
        {
            switch (flagArray[27] as int32) {
                case 1:
                case 3: {
                    this.border(modifier._border_0_0value);
                    break;
                }
                default: {
                    this.border((undefined as BorderOptions | undefined));
                }
            }
        }
        if (flagArray[28] != 0)
        {
            switch (flagArray[28] as int32) {
                case 1:
                case 3: {
                    this.borderStyle(modifier._borderStyle_0_0value);
                    break;
                }
                default: {
                    this.borderStyle((undefined as BorderStyle | EdgeStyles | undefined));
                }
            }
        }
        if (flagArray[29] != 0)
        {
            switch (flagArray[29] as int32) {
                case 1:
                case 3: {
                    this.borderWidth(modifier._borderWidth_0_0value);
                    break;
                }
                default: {
                    this.borderWidth((undefined as Length | EdgeWidths | LocalizedEdgeWidths | undefined));
                }
            }
        }
        if (flagArray[30] != 0)
        {
            switch (flagArray[30] as int32) {
                case 1:
                case 3: {
                    this.borderColor(modifier._borderColor_0_0value);
                    break;
                }
                default: {
                    this.borderColor((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (flagArray[31] != 0)
        {
            switch (flagArray[31] as int32) {
                case 1:
                case 3: {
                    this.borderRadius(modifier._borderRadius_0_0value);
                    break;
                }
                default: {
                    this.borderRadius((undefined as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined));
                }
            }
        }
        if (flagArray[32] != 0)
        {
            switch (flagArray[32] as int32) {
                case 1:
                case 3: {
                    this.borderImage(modifier._borderImage_0_0value);
                    break;
                }
                default: {
                    this.borderImage((undefined as BorderImageOption | undefined));
                }
            }
        }
        if (flagArray[33] != 0)
        {
            switch (flagArray[33] as int32) {
                case 1:
                case 3: {
                    this.outline(modifier._outline_0_0value);
                    break;
                }
                default: {
                    this.outline((undefined as OutlineOptions | undefined));
                }
            }
        }
        if (flagArray[34] != 0)
        {
            switch (flagArray[34] as int32) {
                case 1:
                case 3: {
                    this.outlineStyle(modifier._outlineStyle_0_0value);
                    break;
                }
                default: {
                    this.outlineStyle((undefined as OutlineStyle | EdgeOutlineStyles | undefined));
                }
            }
        }
        if (flagArray[35] != 0)
        {
            switch (flagArray[35] as int32) {
                case 1:
                case 3: {
                    this.outlineWidth(modifier._outlineWidth_0_0value);
                    break;
                }
                default: {
                    this.outlineWidth((undefined as Dimension | EdgeOutlineWidths | undefined));
                }
            }
        }
        if (flagArray[36] != 0)
        {
            switch (flagArray[36] as int32) {
                case 1:
                case 3: {
                    this.outlineColor(modifier._outlineColor_0_0value);
                    break;
                }
                default: {
                    this.outlineColor((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (flagArray[37] != 0)
        {
            switch (flagArray[37] as int32) {
                case 1:
                case 3: {
                    this.outlineRadius(modifier._outlineRadius_0_0value);
                    break;
                }
                default: {
                    this.outlineRadius((undefined as Dimension | OutlineRadiuses | undefined));
                }
            }
        }
        if (flagArray[38] != 0)
        {
            switch (flagArray[38] as int32) {
                case 1:
                case 3: {
                    this.foregroundColor(modifier._foregroundColor_0_0value);
                    break;
                }
                default: {
                    this.foregroundColor((undefined as ResourceColor | ColoringStrategy | undefined));
                }
            }
        }
        if (flagArray[39] != 0)
        {
            switch (flagArray[39] as int32) {
                case 1:
                case 3: {
                    this.onClick(modifier._onClick_0_0value);
                    break;
                }
                default: {
                    this.onClick((undefined as ((event: ClickEvent) => void) | undefined));
                }
            }
        }
    }
    mergeModifier2(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[40] != 0)
        {
            switch (flagArray[40] as int32) {
                case 1:
                case 3: {
                    this.onHover(modifier._onHover_0_0value);
                    break;
                }
                default: {
                    this.onHover((undefined as ((isHover: boolean,event: HoverEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[41] != 0)
        {
            switch (flagArray[41] as int32) {
                case 1:
                case 3: {
                    this.onHoverMove(modifier._onHoverMove_0_0value);
                    break;
                }
                default: {
                    this.onHoverMove((undefined as ((value0: HoverEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[42] != 0)
        {
            switch (flagArray[42] as int32) {
                case 1:
                case 3: {
                    this.onAccessibilityHover(modifier._onAccessibilityHover_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityHover((undefined as AccessibilityCallback | undefined));
                }
            }
        }
        if (flagArray[43] != 0)
        {
            switch (flagArray[43] as int32) {
                case 1:
                case 3: {
                    this.onAccessibilityHoverTransparent(modifier._onAccessibilityHoverTransparent_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityHoverTransparent((undefined as AccessibilityTransparentCallback | undefined));
                }
            }
        }
        if (flagArray[44] != 0)
        {
            switch (flagArray[44] as int32) {
                case 1:
                case 3: {
                    this.hoverEffect(modifier._hoverEffect_0_0value);
                    break;
                }
                default: {
                    this.hoverEffect((undefined as HoverEffect | undefined));
                }
            }
        }
        if (flagArray[45] != 0)
        {
            switch (flagArray[45] as int32) {
                case 1:
                case 3: {
                    this.onMouse(modifier._onMouse_0_0value);
                    break;
                }
                default: {
                    this.onMouse((undefined as ((event: MouseEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[46] != 0)
        {
            switch (flagArray[46] as int32) {
                case 1:
                case 3: {
                    this.onTouch(modifier._onTouch_0_0value);
                    break;
                }
                default: {
                    this.onTouch((undefined as ((event: TouchEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[47] != 0)
        {
            switch (flagArray[47] as int32) {
                case 1:
                case 3: {
                    this.onKeyEvent(modifier._onKeyEvent_0_0value);
                    break;
                }
                default: {
                    this.onKeyEvent((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[48] != 0)
        {
            switch (flagArray[48] as int32) {
                case 1:
                case 3: {
                    this.onDigitalCrown(modifier._onDigitalCrown_0_0value);
                    break;
                }
                default: {
                    this.onDigitalCrown((undefined as ((value0: CrownEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[49] != 0)
        {
            switch (flagArray[49] as int32) {
                case 1:
                case 3: {
                    this.onKeyPreIme(modifier._onKeyPreIme_0_0value);
                    break;
                }
                default: {
                    this.onKeyPreIme((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[50] != 0)
        {
            switch (flagArray[50] as int32) {
                case 1:
                case 3: {
                    this.onKeyEventDispatch(modifier._onKeyEventDispatch_0_0value);
                    break;
                }
                default: {
                    this.onKeyEventDispatch((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (flagArray[51] != 0)
        {
            switch (flagArray[51] as int32) {
                case 1:
                case 3: {
                    this.onFocusAxisEvent(modifier._onFocusAxisEvent_0_0value);
                    break;
                }
                default: {
                    this.onFocusAxisEvent((undefined as ((value0: FocusAxisEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[52] != 0)
        {
            switch (flagArray[52] as int32) {
                case 1:
                case 3: {
                    this.onAxisEvent(modifier._onAxisEvent_0_0value);
                    break;
                }
                default: {
                    this.onAxisEvent((undefined as ((value0: AxisEvent) => void) | undefined));
                }
            }
        }
        if (flagArray[53] != 0)
        {
            switch (flagArray[53] as int32) {
                case 1:
                case 3: {
                    this.focusable(modifier._focusable_0_0value);
                    break;
                }
                default: {
                    this.focusable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[54] != 0)
        {
            switch (flagArray[54] as int32) {
                case 1:
                case 3: {
                    this.nextFocus(modifier._nextFocus_0_0value);
                    break;
                }
                default: {
                    this.nextFocus((undefined as FocusMovement | undefined));
                }
            }
        }
        if (flagArray[55] != 0)
        {
            switch (flagArray[55] as int32) {
                case 1:
                case 3: {
                    this.tabStop(modifier._tabStop_0_0value);
                    break;
                }
                default: {
                    this.tabStop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[56] != 0)
        {
            switch (flagArray[56] as int32) {
                case 1:
                case 3: {
                    this.onFocus(modifier._onFocus_0_0value);
                    break;
                }
                default: {
                    this.onFocus((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[57] != 0)
        {
            switch (flagArray[57] as int32) {
                case 1:
                case 3: {
                    this.onBlur(modifier._onBlur_0_0value);
                    break;
                }
                default: {
                    this.onBlur((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[58] != 0)
        {
            switch (flagArray[58] as int32) {
                case 1:
                case 3: {
                    this.tabIndex(modifier._tabIndex_0_0value);
                    break;
                }
                default: {
                    this.tabIndex((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[59] != 0)
        {
            switch (flagArray[59] as int32) {
                case 1:
                case 3: {
                    this.defaultFocus(modifier._defaultFocus_0_0value);
                    break;
                }
                default: {
                    this.defaultFocus((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier3(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[60] != 0)
        {
            switch (flagArray[60] as int32) {
                case 1:
                case 3: {
                    this.groupDefaultFocus(modifier._groupDefaultFocus_0_0value);
                    break;
                }
                default: {
                    this.groupDefaultFocus((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[61] != 0)
        {
            switch (flagArray[61] as int32) {
                case 1:
                case 3: {
                    this.focusOnTouch(modifier._focusOnTouch_0_0value);
                    break;
                }
                default: {
                    this.focusOnTouch((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[62] != 0)
        {
            switch (flagArray[62] as int32) {
                case 1:
                case 3: {
                    this.focusBox(modifier._focusBox_0_0value);
                    break;
                }
                default: {
                    this.focusBox((undefined as FocusBoxStyle | undefined));
                }
            }
        }
        if (flagArray[63] != 0)
        {
            switch (flagArray[63] as int32) {
                case 1:
                case 3: {
                    this.animation(modifier._animation_0_0value);
                    break;
                }
                default: {
                    this.animation((undefined as AnimateParam | undefined));
                }
            }
        }
        if (flagArray[64] != 0)
        {
            switch (flagArray[64] as int32) {
                case 1:
                case 3: {
                    this.transition(modifier._transition_0_0value);
                    break;
                }
                default: {
                    this.transition((undefined as TransitionEffect | undefined));
                }
            }
        }
        if (flagArray[65] != 0)
        {
            switch (flagArray[65] as int32) {
                case 1:
                case 3: {
                    this.motionBlur(modifier._motionBlur_0_0value);
                    break;
                }
                default: {
                    this.motionBlur((undefined as MotionBlurOptions | undefined));
                }
            }
        }
        if (flagArray[66] != 0)
        {
            switch (flagArray[66] as int32) {
                case 1:
                case 3: {
                    this.brightness(modifier._brightness_0_0value);
                    break;
                }
                default: {
                    this.brightness((undefined as double | undefined));
                }
            }
        }
        if (flagArray[67] != 0)
        {
            switch (flagArray[67] as int32) {
                case 1:
                case 3: {
                    this.contrast(modifier._contrast_0_0value);
                    break;
                }
                default: {
                    this.contrast((undefined as double | undefined));
                }
            }
        }
        if (flagArray[68] != 0)
        {
            switch (flagArray[68] as int32) {
                case 1:
                case 3: {
                    this.grayscale(modifier._grayscale_0_0value);
                    break;
                }
                default: {
                    this.grayscale((undefined as double | undefined));
                }
            }
        }
        if (flagArray[69] != 0)
        {
            switch (flagArray[69] as int32) {
                case 1:
                case 3: {
                    this.colorBlend(modifier._colorBlend_0_0value);
                    break;
                }
                default: {
                    this.colorBlend((undefined as Color | string | Resource | undefined));
                }
            }
        }
        if (flagArray[70] != 0)
        {
            switch (flagArray[70] as int32) {
                case 1:
                case 3: {
                    this.saturate(modifier._saturate_0_0value);
                    break;
                }
                default: {
                    this.saturate((undefined as double | undefined));
                }
            }
        }
        if (flagArray[71] != 0)
        {
            switch (flagArray[71] as int32) {
                case 1:
                case 3: {
                    this.sepia(modifier._sepia_0_0value);
                    break;
                }
                default: {
                    this.sepia((undefined as double | undefined));
                }
            }
        }
        if (flagArray[72] != 0)
        {
            switch (flagArray[72] as int32) {
                case 1:
                case 3: {
                    this.invert(modifier._invert_0_0value);
                    break;
                }
                default: {
                    this.invert((undefined as double | InvertOptions | undefined));
                }
            }
        }
        if (flagArray[73] != 0)
        {
            switch (flagArray[73] as int32) {
                case 1:
                case 3: {
                    this.hueRotate(modifier._hueRotate_0_0value);
                    break;
                }
                default: {
                    this.hueRotate((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[74] != 0)
        {
            switch (flagArray[74] as int32) {
                case 1:
                case 3: {
                    this.useShadowBatching(modifier._useShadowBatching_0_0value);
                    break;
                }
                default: {
                    this.useShadowBatching((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[75] != 0)
        {
            switch (flagArray[75] as int32) {
                case 1:
                case 3: {
                    this.useEffect(modifier._useEffect_0_0value);
                    break;
                }
                default: {
                    this.useEffect((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[76] != 0)
        {
            switch (flagArray[76] as int32) {
                case 1:
                case 3: {
                    this.renderGroup(modifier._renderGroup_0_0value);
                    break;
                }
                default: {
                    this.renderGroup((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[77] != 0)
        {
            switch (flagArray[77] as int32) {
                case 1:
                case 3: {
                    this.freeze(modifier._freeze_0_0value);
                    break;
                }
                default: {
                    this.freeze((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[78] != 0)
        {
            switch (flagArray[78] as int32) {
                case 1:
                case 3: {
                    this.translate(modifier._translate_0_0value);
                    break;
                }
                default: {
                    this.translate((undefined as TranslateOptions | undefined));
                }
            }
        }
        if (flagArray[79] != 0)
        {
            switch (flagArray[79] as int32) {
                case 1:
                case 3: {
                    this.scale(modifier._scale_0_0value);
                    break;
                }
                default: {
                    this.scale((undefined as ScaleOptions | undefined));
                }
            }
        }
    }
    mergeModifier4(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[80] != 0)
        {
            switch (flagArray[80] as int32) {
                case 1:
                case 3: {
                    this.rotate(modifier._rotate_0_0value);
                    break;
                }
                default: {
                    this.rotate((undefined as RotateOptions | RotateAngleOptions | undefined));
                }
            }
        }
        if (flagArray[81] != 0)
        {
            switch (flagArray[81] as int32) {
                case 1:
                case 3: {
                    this.transform(modifier._transform_0_0value);
                    break;
                }
                default: {
                    this.transform((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (flagArray[82] != 0)
        {
            switch (flagArray[82] as int32) {
                case 1:
                case 3: {
                    this.transform3D(modifier._transform3D_0_0value);
                    break;
                }
                default: {
                    this.transform3D((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (flagArray[83] != 0)
        {
            switch (flagArray[83] as int32) {
                case 1:
                case 3: {
                    this.onAppear(modifier._onAppear_0_0value);
                    break;
                }
                default: {
                    this.onAppear((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[84] != 0)
        {
            switch (flagArray[84] as int32) {
                case 1:
                case 3: {
                    this.onDisAppear(modifier._onDisAppear_0_0value);
                    break;
                }
                default: {
                    this.onDisAppear((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[85] != 0)
        {
            switch (flagArray[85] as int32) {
                case 1:
                case 3: {
                    this.onAttach(modifier._onAttach_0_0value);
                    break;
                }
                default: {
                    this.onAttach((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[86] != 0)
        {
            switch (flagArray[86] as int32) {
                case 1:
                case 3: {
                    this.onDetach(modifier._onDetach_0_0value);
                    break;
                }
                default: {
                    this.onDetach((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[87] != 0)
        {
            switch (flagArray[87] as int32) {
                case 1:
                case 3: {
                    this.onAreaChange(modifier._onAreaChange_0_0value);
                    break;
                }
                default: {
                    this.onAreaChange((undefined as ((oldValue: Area,newValue: Area) => void) | undefined));
                }
            }
        }
        if (flagArray[88] != 0)
        {
            switch (flagArray[88] as int32) {
                case 1:
                case 3: {
                    this.visibility(modifier._visibility_0_0value);
                    break;
                }
                default: {
                    this.visibility((undefined as Visibility | undefined));
                }
            }
        }
        if (flagArray[89] != 0)
        {
            switch (flagArray[89] as int32) {
                case 1:
                case 3: {
                    this.flexGrow(modifier._flexGrow_0_0value);
                    break;
                }
                default: {
                    this.flexGrow((undefined as number | undefined));
                }
            }
        }
        if (flagArray[90] != 0)
        {
            switch (flagArray[90] as int32) {
                case 1:
                case 3: {
                    this.flexShrink(modifier._flexShrink_0_0value);
                    break;
                }
                default: {
                    this.flexShrink((undefined as number | undefined));
                }
            }
        }
        if (flagArray[91] != 0)
        {
            switch (flagArray[91] as int32) {
                case 1:
                case 3: {
                    this.flexBasis(modifier._flexBasis_0_0value);
                    break;
                }
                default: {
                    this.flexBasis((undefined as number | string | undefined));
                }
            }
        }
        if (flagArray[92] != 0)
        {
            switch (flagArray[92] as int32) {
                case 1:
                case 3: {
                    this.alignSelf(modifier._alignSelf_0_0value);
                    break;
                }
                default: {
                    this.alignSelf((undefined as ItemAlign | undefined));
                }
            }
        }
        if (flagArray[93] != 0)
        {
            switch (flagArray[93] as int32) {
                case 1:
                case 3: {
                    this.layoutGravity(modifier._layoutGravity_0_0value);
                    break;
                }
                default: {
                    this.layoutGravity((undefined as LocalizedAlignment | undefined));
                }
            }
        }
        if (flagArray[94] != 0)
        {
            switch (flagArray[94] as int32) {
                case 1:
                case 3: {
                    this.displayPriority(modifier._displayPriority_0_0value);
                    break;
                }
                default: {
                    this.displayPriority((undefined as number | undefined));
                }
            }
        }
        if (flagArray[95] != 0)
        {
            switch (flagArray[95] as int32) {
                case 1:
                case 3: {
                    this.zIndex(modifier._zIndex_0_0value);
                    break;
                }
                default: {
                    this.zIndex((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[96] != 0)
        {
            switch (flagArray[96] as int32) {
                case 1:
                case 3: {
                    this.direction(modifier._direction_0_0value);
                    break;
                }
                default: {
                    this.direction((undefined as Direction | undefined));
                }
            }
        }
        if (flagArray[97] != 0)
        {
            switch (flagArray[97] as int32) {
                case 1:
                case 3: {
                    this.align(modifier._align_0_0value);
                    break;
                }
                default: {
                    this.align((undefined as Alignment | LocalizedAlignment | undefined));
                }
            }
        }
        if (flagArray[98] != 0)
        {
            switch (flagArray[98] as int32) {
                case 1:
                case 3: {
                    this.position(modifier._position_0_0value);
                    break;
                }
                default: {
                    this.position((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (flagArray[99] != 0)
        {
            switch (flagArray[99] as int32) {
                case 1:
                case 3: {
                    this.markAnchor(modifier._markAnchor_0_0value);
                    break;
                }
                default: {
                    this.markAnchor((undefined as Position | LocalizedPosition | undefined));
                }
            }
        }
    }
    mergeModifier5(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[100] != 0)
        {
            switch (flagArray[100] as int32) {
                case 1:
                case 3: {
                    this.offset(modifier._offset_0_0value);
                    break;
                }
                default: {
                    this.offset((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (flagArray[101] != 0)
        {
            switch (flagArray[101] as int32) {
                case 1:
                case 3: {
                    this.enabled(modifier._enabled_0_0value);
                    break;
                }
                default: {
                    this.enabled((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[102] != 0)
        {
            switch (flagArray[102] as int32) {
                case 1:
                case 3: {
                    this.alignRules(modifier._alignRules_0_0value);
                    break;
                }
                default: {
                    this.alignRules((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (flagArray[103] != 0)
        {
            switch (flagArray[103] as int32) {
                case 1:
                case 3: {
                    this.aspectRatio(modifier._aspectRatio_0_0value);
                    break;
                }
                default: {
                    this.aspectRatio((undefined as number | undefined));
                }
            }
        }
        if (flagArray[104] != 0)
        {
            switch (flagArray[104] as int32) {
                case 1:
                case 3: {
                    this.clickEffect(modifier._clickEffect_0_0value);
                    break;
                }
                default: {
                    this.clickEffect((undefined as ClickEffect | null | undefined));
                }
            }
        }
        if (flagArray[105] != 0)
        {
            switch (flagArray[105] as int32) {
                case 1:
                case 3: {
                    this.onDragStart(modifier._onDragStart_0_0value);
                    break;
                }
                default: {
                    this.onDragStart((undefined as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined));
                }
            }
        }
        if (flagArray[106] != 0)
        {
            switch (flagArray[106] as int32) {
                case 1:
                case 3: {
                    this.onDragEnter(modifier._onDragEnter_0_0value);
                    break;
                }
                default: {
                    this.onDragEnter((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[107] != 0)
        {
            switch (flagArray[107] as int32) {
                case 1:
                case 3: {
                    this.onDragMove(modifier._onDragMove_0_0value);
                    break;
                }
                default: {
                    this.onDragMove((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[108] != 0)
        {
            switch (flagArray[108] as int32) {
                case 1:
                case 3: {
                    this.onDragLeave(modifier._onDragLeave_0_0value);
                    break;
                }
                default: {
                    this.onDragLeave((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[109] != 0)
        {
            switch (flagArray[109] as int32) {
                case 1:
                case 3: {
                    this.onDrop(modifier._onDrop_0_0value);
                    break;
                }
                default: {
                    this.onDrop((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[110] != 0)
        {
            switch (flagArray[110] as int32) {
                case 1:
                case 3: {
                    this.onDragEnd(modifier._onDragEnd_0_0value);
                    break;
                }
                default: {
                    this.onDragEnd((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (flagArray[111] != 0)
        {
            switch (flagArray[111] as int32) {
                case 1:
                case 3: {
                    this.allowDrop(modifier._allowDrop_0_0value);
                    break;
                }
                default: {
                    this.allowDrop((undefined as Array<uniformTypeDescriptor.UniformDataType> | Array<string> | null | undefined));
                }
            }
        }
        if (flagArray[112] != 0)
        {
            switch (flagArray[112] as int32) {
                case 1:
                case 3: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[113] != 0)
        {
            switch (flagArray[113] as int32) {
                case 1:
                case 3: {
                    this.dragPreview(modifier._dragPreview_0_0value);
                    break;
                }
                default: {
                    this.dragPreview((undefined as CustomBuilder | DragItemInfo | string | undefined));
                }
            }
        }
        if (flagArray[114] != 0)
        {
            switch (flagArray[114] as int32) {
                case 1:
                case 3: {
                    this.onPreDrag(modifier._onPreDrag_0_0value);
                    break;
                }
                default: {
                    this.onPreDrag((undefined as ((value0: PreDragStatus) => void) | undefined));
                }
            }
        }
        if (flagArray[115] != 0)
        {
            switch (flagArray[115] as int32) {
                case 1:
                case 3: {
                    this.linearGradient(modifier._linearGradient_0_0value);
                    break;
                }
                default: {
                    this.linearGradient((undefined as LinearGradientOptions | undefined));
                }
            }
        }
        if (flagArray[116] != 0)
        {
            switch (flagArray[116] as int32) {
                case 1:
                case 3: {
                    this.sweepGradient(modifier._sweepGradient_0_0value);
                    break;
                }
                default: {
                    this.sweepGradient((undefined as SweepGradientOptions | undefined));
                }
            }
        }
        if (flagArray[117] != 0)
        {
            switch (flagArray[117] as int32) {
                case 1:
                case 3: {
                    this.radialGradient(modifier._radialGradient_0_0value);
                    break;
                }
                default: {
                    this.radialGradient((undefined as RadialGradientOptions | undefined));
                }
            }
        }
        if (flagArray[118] != 0)
        {
            switch (flagArray[118] as int32) {
                case 1:
                case 3: {
                    this.motionPath(modifier._motionPath_0_0value);
                    break;
                }
                default: {
                    this.motionPath((undefined as MotionPathOptions | undefined));
                }
            }
        }
        if (flagArray[119] != 0)
        {
            switch (flagArray[119] as int32) {
                case 1:
                case 3: {
                    this.shadow(modifier._shadow_0_0value);
                    break;
                }
                default: {
                    this.shadow((undefined as ShadowOptions | ShadowStyle | undefined));
                }
            }
        }
    }
    mergeModifier6(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[120] != 0)
        {
            switch (flagArray[120] as int32) {
                case 1:
                case 3: {
                    this.clip(modifier._clip_0_0value);
                    break;
                }
                default: {
                    this.clip((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[121] != 0)
        {
            switch (flagArray[121] as int32) {
                case 1:
                case 3: {
                    this.clipShape(modifier._clipShape_0_0value);
                    break;
                }
                default: {
                    this.clipShape((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (flagArray[122] != 0)
        {
            switch (flagArray[122] as int32) {
                case 1:
                case 3: {
                    this.mask(modifier._mask_0_0value);
                    break;
                }
                default: {
                    this.mask((undefined as ProgressMask | undefined));
                }
            }
        }
        if (flagArray[123] != 0)
        {
            switch (flagArray[123] as int32) {
                case 1:
                case 3: {
                    this.maskShape(modifier._maskShape_0_0value);
                    break;
                }
                default: {
                    this.maskShape((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (flagArray[124] != 0)
        {
            switch (flagArray[124] as int32) {
                case 1:
                case 3: {
                    this.key(modifier._key_0_0value);
                    break;
                }
                default: {
                    this.key((undefined as string | undefined));
                }
            }
        }
        if (flagArray[125] != 0)
        {
            switch (flagArray[125] as int32) {
                case 1:
                case 3: {
                    this.id(modifier._id_0_0value);
                    break;
                }
                default: {
                    this.id((undefined as string | undefined));
                }
            }
        }
        if (flagArray[126] != 0)
        {
            switch (flagArray[126] as int32) {
                case 1:
                case 3: {
                    this.geometryTransition(modifier._geometryTransition_0_0value);
                    break;
                }
                default: {
                    this.geometryTransition((undefined as string | undefined));
                }
            }
        }
        if (flagArray[127] != 0)
        {
            switch (flagArray[127] as int32) {
                case 1:
                case 3: {
                    this.restoreId(modifier._restoreId_0_0value);
                    break;
                }
                default: {
                    this.restoreId((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[128] != 0)
        {
            switch (flagArray[128] as int32) {
                case 1:
                case 3: {
                    this.sphericalEffect(modifier._sphericalEffect_0_0value);
                    break;
                }
                default: {
                    this.sphericalEffect((undefined as double | undefined));
                }
            }
        }
        if (flagArray[129] != 0)
        {
            switch (flagArray[129] as int32) {
                case 1:
                case 3: {
                    this.lightUpEffect(modifier._lightUpEffect_0_0value);
                    break;
                }
                default: {
                    this.lightUpEffect((undefined as double | undefined));
                }
            }
        }
        if (flagArray[130] != 0)
        {
            switch (flagArray[130] as int32) {
                case 1:
                case 3: {
                    this.pixelStretchEffect(modifier._pixelStretchEffect_0_0value);
                    break;
                }
                default: {
                    this.pixelStretchEffect((undefined as PixelStretchEffectOptions | undefined));
                }
            }
        }
        if (flagArray[131] != 0)
        {
            switch (flagArray[131] as int32) {
                case 1:
                case 3: {
                    this.accessibilityGroup(modifier._accessibilityGroup_0_0value);
                    break;
                }
                default: {
                    this.accessibilityGroup((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[132] != 0)
        {
            switch (flagArray[132] as int32) {
                case 1:
                case 3: {
                    this.accessibilityText(modifier._accessibilityTextOfStringType_0_0value);
                    break;
                }
                default: {
                    this.accessibilityText((undefined as string | undefined));
                }
            }
        }
        if (flagArray[133] != 0)
        {
            switch (flagArray[133] as int32) {
                case 1:
                case 3: {
                    this.accessibilityNextFocusId(modifier._accessibilityNextFocusId_0_0value);
                    break;
                }
                default: {
                    this.accessibilityNextFocusId((undefined as string | undefined));
                }
            }
        }
        if (flagArray[134] != 0)
        {
            switch (flagArray[134] as int32) {
                case 1:
                case 3: {
                    this.accessibilityDefaultFocus(modifier._accessibilityDefaultFocus_0_0value);
                    break;
                }
                default: {
                    this.accessibilityDefaultFocus((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[135] != 0)
        {
            switch (flagArray[135] as int32) {
                case 1:
                case 3: {
                    this.accessibilityUseSamePage(modifier._accessibilityUseSamePage_0_0value);
                    break;
                }
                default: {
                    this.accessibilityUseSamePage((undefined as AccessibilitySamePageMode | undefined));
                }
            }
        }
        if (flagArray[136] != 0)
        {
            switch (flagArray[136] as int32) {
                case 1:
                case 3: {
                    this.accessibilityScrollTriggerable(modifier._accessibilityScrollTriggerable_0_0value);
                    break;
                }
                default: {
                    this.accessibilityScrollTriggerable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[137] != 0)
        {
            switch (flagArray[137] as int32) {
                case 1:
                case 3: {
                    this.accessibilityText(modifier._accessibilityTextOfResourceType_0_0value);
                    break;
                }
                default: {
                    this.accessibilityText((undefined as Resource | undefined));
                }
            }
        }
        if (flagArray[138] != 0)
        {
            switch (flagArray[138] as int32) {
                case 1:
                case 3: {
                    this.accessibilityRole(modifier._accessibilityRole_0_0value);
                    break;
                }
                default: {
                    this.accessibilityRole((undefined as AccessibilityRoleType | undefined));
                }
            }
        }
        if (flagArray[139] != 0)
        {
            switch (flagArray[139] as int32) {
                case 1:
                case 3: {
                    this.onAccessibilityFocus(modifier._onAccessibilityFocus_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityFocus((undefined as AccessibilityFocusCallback | undefined));
                }
            }
        }
    }
    mergeModifier7(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[140] != 0)
        {
            switch (flagArray[140] as int32) {
                case 1:
                case 3: {
                    this.onAccessibilityActionIntercept(modifier._onAccessibilityActionIntercept_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityActionIntercept((undefined as AccessibilityActionInterceptCallback | undefined));
                }
            }
        }
        if (flagArray[141] != 0)
        {
            switch (flagArray[141] as int32) {
                case 1:
                case 3: {
                    this.accessibilityTextHint(modifier._accessibilityTextHint_0_0value);
                    break;
                }
                default: {
                    this.accessibilityTextHint((undefined as string | undefined));
                }
            }
        }
        if (flagArray[142] != 0)
        {
            switch (flagArray[142] as int32) {
                case 1:
                case 3: {
                    this.accessibilityDescription(modifier._accessibilityDescriptionOfStringType_0_0value);
                    break;
                }
                default: {
                    this.accessibilityDescription((undefined as string | undefined));
                }
            }
        }
        if (flagArray[143] != 0)
        {
            switch (flagArray[143] as int32) {
                case 1:
                case 3: {
                    this.accessibilityDescription(modifier._accessibilityDescriptionOfResourceType_0_0value);
                    break;
                }
                default: {
                    this.accessibilityDescription((undefined as Resource | undefined));
                }
            }
        }
        if (flagArray[144] != 0)
        {
            switch (flagArray[144] as int32) {
                case 1:
                case 3: {
                    this.accessibilityLevel(modifier._accessibilityLevel_0_0value);
                    break;
                }
                default: {
                    this.accessibilityLevel((undefined as string | undefined));
                }
            }
        }
        if (flagArray[145] != 0)
        {
            switch (flagArray[145] as int32) {
                case 1:
                case 3: {
                    this.accessibilityVirtualNode(modifier._accessibilityVirtualNode_0_0value);
                    break;
                }
                default: {
                    this.accessibilityVirtualNode((undefined as CustomBuilder | undefined));
                }
            }
        }
        if (flagArray[146] != 0)
        {
            switch (flagArray[146] as int32) {
                case 1:
                case 3: {
                    this.accessibilityChecked(modifier._accessibilityChecked_0_0value);
                    break;
                }
                default: {
                    this.accessibilityChecked((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[147] != 0)
        {
            switch (flagArray[147] as int32) {
                case 1:
                case 3: {
                    this.accessibilitySelected(modifier._accessibilitySelected_0_0value);
                    break;
                }
                default: {
                    this.accessibilitySelected((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[148] != 0)
        {
            switch (flagArray[148] as int32) {
                case 1:
                case 3: {
                    this.obscured(modifier._obscured_0_0value);
                    break;
                }
                default: {
                    this.obscured((undefined as Array<ObscuredReasons> | undefined));
                }
            }
        }
        if (flagArray[149] != 0)
        {
            switch (flagArray[149] as int32) {
                case 1:
                case 3: {
                    this.reuseId(modifier._reuseId_0_0value);
                    break;
                }
                default: {
                    this.reuseId((undefined as string | undefined));
                }
            }
        }
        if (flagArray[150] != 0)
        {
            switch (flagArray[150] as int32) {
                case 1:
                case 3: {
                    this.reuse(modifier._reuse_0_0value);
                    break;
                }
                default: {
                    this.reuse((undefined as ReuseOptions | undefined));
                }
            }
        }
        if (flagArray[151] != 0)
        {
            switch (flagArray[151] as int32) {
                case 1:
                case 3: {
                    this.renderFit(modifier._renderFit_0_0value);
                    break;
                }
                default: {
                    this.renderFit((undefined as RenderFit | undefined));
                }
            }
        }
        if (flagArray[152] != 0)
        {
            switch (flagArray[152] as int32) {
                case 1:
                case 3: {
                    this.backgroundBrightness(modifier._backgroundBrightness_0_0value);
                    break;
                }
                default: {
                    this.backgroundBrightness((undefined as BackgroundBrightnessOptions | undefined));
                }
            }
        }
        if (flagArray[153] != 0)
        {
            switch (flagArray[153] as int32) {
                case 1:
                case 3: {
                    this.onGestureJudgeBegin(modifier._onGestureJudgeBegin_0_0value);
                    break;
                }
                default: {
                    this.onGestureJudgeBegin((undefined as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined));
                }
            }
        }
        if (flagArray[154] != 0)
        {
            switch (flagArray[154] as int32) {
                case 1:
                case 3: {
                    this.onGestureRecognizerJudgeBegin(modifier._onGestureRecognizerJudgeBegin_0_0value);
                    break;
                }
                default: {
                    this.onGestureRecognizerJudgeBegin((undefined as GestureRecognizerJudgeBeginCallback | undefined));
                }
            }
        }
        if (flagArray[155] != 0)
        {
            switch (flagArray[155] as int32) {
                case 1:
                case 3: {
                    this.shouldBuiltInRecognizerParallelWith(modifier._shouldBuiltInRecognizerParallelWith_0_0value);
                    break;
                }
                default: {
                    this.shouldBuiltInRecognizerParallelWith((undefined as ShouldBuiltInRecognizerParallelWithCallback | undefined));
                }
            }
        }
        if (flagArray[156] != 0)
        {
            switch (flagArray[156] as int32) {
                case 1:
                case 3: {
                    this.monopolizeEvents(modifier._monopolizeEvents_0_0value);
                    break;
                }
                default: {
                    this.monopolizeEvents((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[157] != 0)
        {
            switch (flagArray[157] as int32) {
                case 1:
                case 3: {
                    this.onTouchIntercept(modifier._onTouchIntercept_0_0value);
                    break;
                }
                default: {
                    this.onTouchIntercept((undefined as ((value0: TouchEvent) => HitTestMode) | undefined));
                }
            }
        }
        if (flagArray[158] != 0)
        {
            switch (flagArray[158] as int32) {
                case 1:
                case 3: {
                    this.onSizeChange(modifier._onSizeChange_0_0value);
                    break;
                }
                default: {
                    this.onSizeChange((undefined as SizeChangeCallback | undefined));
                }
            }
        }
        if (flagArray[159] != 0)
        {
            switch (flagArray[159] as int32) {
                case 1:
                case 3: {
                    this.accessibilityFocusDrawLevel(modifier._accessibilityFocusDrawLevel_0_0value);
                    break;
                }
                default: {
                    this.accessibilityFocusDrawLevel((undefined as FocusDrawLevel | undefined));
                }
            }
        }
    }
    mergeModifier8(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[160] != 0)
        {
            switch (flagArray[160] as int32) {
                case 1:
                case 3: {
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[161] != 0)
        {
            switch (flagArray[161] as int32) {
                case 1:
                case 3: {
                    this.expandSafeArea(modifier._expandSafeArea_0_0value, modifier._expandSafeArea_0_1value);
                    break;
                }
                default: {
                    this.expandSafeArea((undefined as Array<SafeAreaType> | undefined | undefined), (undefined as Array<SafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (flagArray[162] != 0)
        {
            switch (flagArray[162] as int32) {
                case 1:
                case 3: {
                    this.ignoreLayoutSafeArea(modifier._ignoreLayoutSafeArea_0_0value, modifier._ignoreLayoutSafeArea_0_1value);
                    break;
                }
                default: {
                    this.ignoreLayoutSafeArea((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (flagArray[163] != 0)
        {
            switch (flagArray[163] as int32) {
                case 1:
                case 3: {
                    this.background(modifier._background_0_0value, modifier._background_0_1value);
                    break;
                }
                default: {
                    this.background((undefined as CustomBuilder | undefined), (undefined as BackgroundOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[164] != 0)
        {
            switch (flagArray[164] as int32) {
                case 1:
                case 3: {
                    this.backgroundImage(modifier._backgroundImage_1_0value, modifier._backgroundImage_1_1value);
                    break;
                }
                default: {
                    this.backgroundImage((undefined as ResourceStr | image.PixelMap | undefined), (undefined as BackgroundImageOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[165] != 0)
        {
            switch (flagArray[165] as int32) {
                case 1:
                case 3: {
                    this.backgroundImage(modifier._backgroundImage_2_0value, modifier._backgroundImage_2_1value);
                    break;
                }
                default: {
                    this.backgroundImage((undefined as ResourceStr | image.PixelMap | undefined), (undefined as ImageRepeat | undefined | undefined));
                }
            }
        }
        if (flagArray[166] != 0)
        {
            switch (flagArray[166] as int32) {
                case 1:
                case 3: {
                    this.backgroundBlurStyle(modifier._backgroundBlurStyle_0_0value, modifier._backgroundBlurStyle_0_1value, modifier._backgroundBlurStyle_0_2value);
                    break;
                }
                default: {
                    this.backgroundBlurStyle((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[167] != 0)
        {
            switch (flagArray[167] as int32) {
                case 1:
                case 3: {
                    this.backgroundEffect(modifier._backgroundEffect_1_0value, modifier._backgroundEffect_1_1value);
                    break;
                }
                default: {
                    this.backgroundEffect((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[168] != 0)
        {
            switch (flagArray[168] as int32) {
                case 1:
                case 3: {
                    this.foregroundBlurStyle(modifier._foregroundBlurStyle_0_0value, modifier._foregroundBlurStyle_0_1value, modifier._foregroundBlurStyle_0_2value);
                    break;
                }
                default: {
                    this.foregroundBlurStyle((undefined as BlurStyle | undefined), (undefined as ForegroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[169] != 0)
        {
            switch (flagArray[169] as int32) {
                case 1:
                case 3: {
                    this.borderRadius(modifier._borderRadius_1_0value, modifier._borderRadius_1_1value);
                    break;
                }
                default: {
                    this.borderRadius((undefined as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined), (undefined as RenderStrategy | undefined | undefined));
                }
            }
        }
        if (flagArray[170] != 0)
        {
            switch (flagArray[170] as int32) {
                case 1:
                case 3: {
                    this.onClick(modifier._onClick_1_0value, modifier._onClick_1_1value);
                    break;
                }
                default: {
                    this.onClick((undefined as ((event: ClickEvent) => void) | undefined), (undefined as double | undefined));
                }
            }
        }
        if (flagArray[171] != 0)
        {
            switch (flagArray[171] as int32) {
                case 1:
                case 3: {
                    this.focusScopeId(modifier._focusScopeId_0_0value, modifier._focusScopeId_0_1value, modifier._focusScopeId_0_2value);
                    break;
                }
                default: {
                    this.focusScopeId((undefined as string | undefined), (undefined as boolean | undefined | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (flagArray[172] != 0)
        {
            switch (flagArray[172] as int32) {
                case 1:
                case 3: {
                    this.focusScopePriority(modifier._focusScopePriority_0_0value, modifier._focusScopePriority_0_1value);
                    break;
                }
                default: {
                    this.focusScopePriority((undefined as string | undefined), (undefined as FocusPriority | undefined | undefined));
                }
            }
        }
        if (flagArray[173] != 0)
        {
            switch (flagArray[173] as int32) {
                case 1:
                case 3: {
                    this.transition(modifier._transition_1_0value, modifier._transition_1_1value);
                    break;
                }
                default: {
                    this.transition((undefined as TransitionEffect | undefined), (undefined as TransitionFinishCallback | undefined));
                }
            }
        }
        if (flagArray[174] != 0)
        {
            switch (flagArray[174] as int32) {
                case 1:
                case 3: {
                    this.blur(modifier._blur_0_0value, modifier._blur_0_1value, modifier._blur_0_2value);
                    break;
                }
                default: {
                    this.blur((undefined as double | undefined), (undefined as BlurOptions | undefined), (undefined as SystemAdaptiveOptions | undefined));
                }
            }
        }
        if (flagArray[175] != 0)
        {
            switch (flagArray[175] as int32) {
                case 1:
                case 3: {
                    this.linearGradientBlur(modifier._linearGradientBlur_0_0value, modifier._linearGradientBlur_0_1value);
                    break;
                }
                default: {
                    this.linearGradientBlur((undefined as double | undefined), (undefined as LinearGradientBlurOptions | undefined));
                }
            }
        }
        if (flagArray[176] != 0)
        {
            switch (flagArray[176] as int32) {
                case 1:
                case 3: {
                    this.systemBarEffect();
                    break;
                }
                default: {
                    this.systemBarEffect();
                }
            }
        }
        if (flagArray[177] != 0)
        {
            switch (flagArray[177] as int32) {
                case 1:
                case 3: {
                    this.useEffect(modifier._useEffect_1_0value, modifier._useEffect_1_1value);
                    break;
                }
                default: {
                    this.useEffect((undefined as boolean | undefined), (undefined as EffectType | undefined));
                }
            }
        }
        if (flagArray[178] != 0)
        {
            switch (flagArray[178] as int32) {
                case 1:
                case 3: {
                    this.backdropBlur(modifier._backdropBlur_0_0value, modifier._backdropBlur_0_1value, modifier._backdropBlur_0_2value);
                    break;
                }
                default: {
                    this.backdropBlur((undefined as double | undefined), (undefined as BlurOptions | undefined), (undefined as SystemAdaptiveOptions | undefined));
                }
            }
        }
        if (flagArray[179] != 0)
        {
            switch (flagArray[179] as int32) {
                case 1:
                case 3: {
                    this.sharedTransition(modifier._sharedTransition_0_0value, modifier._sharedTransition_0_1value);
                    break;
                }
                default: {
                    this.sharedTransition((undefined as string | undefined), (undefined as sharedTransitionOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier9(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[180] != 0)
        {
            switch (flagArray[180] as int32) {
                case 1:
                case 3: {
                    this.chainMode(modifier._chainMode_0_0value, modifier._chainMode_0_1value);
                    break;
                }
                default: {
                    this.chainMode((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (flagArray[181] != 0)
        {
            switch (flagArray[181] as int32) {
                case 1:
                case 3: {
                    this.onDrop(modifier._onDrop_1_0value, modifier._onDrop_1_1value);
                    break;
                }
                default: {
                    this.onDrop((undefined as OnDragEventCallback | undefined), (undefined as DropOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[182] != 0)
        {
            switch (flagArray[182] as int32) {
                case 1:
                case 3: {
                    this.dragPreview(modifier._dragPreview_1_0value, modifier._dragPreview_1_1value);
                    break;
                }
                default: {
                    this.dragPreview((undefined as CustomBuilder | DragItemInfo | string | undefined), (undefined as PreviewConfiguration | undefined | undefined));
                }
            }
        }
        if (flagArray[183] != 0)
        {
            switch (flagArray[183] as int32) {
                case 1:
                case 3: {
                    this.dragPreviewOptions(modifier._dragPreviewOptions_0_0value, modifier._dragPreviewOptions_0_1value);
                    break;
                }
                default: {
                    this.dragPreviewOptions((undefined as DragPreviewOptions | undefined), (undefined as DragInteractionOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[184] != 0)
        {
            switch (flagArray[184] as int32) {
                case 1:
                case 3: {
                    this.overlay(modifier._overlay_0_0value, modifier._overlay_0_1value);
                    break;
                }
                default: {
                    this.overlay((undefined as string | CustomBuilder | ComponentContent | undefined), (undefined as OverlayOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[185] != 0)
        {
            switch (flagArray[185] as int32) {
                case 1:
                case 3: {
                    this.blendMode(modifier._blendMode_0_0value, modifier._blendMode_0_1value);
                    break;
                }
                default: {
                    this.blendMode((undefined as BlendMode | undefined), (undefined as BlendApplyType | undefined | undefined));
                }
            }
        }
        if (flagArray[186] != 0)
        {
            switch (flagArray[186] as int32) {
                case 1:
                case 3: {
                    this.advancedBlendMode(modifier._advancedBlendMode_0_0value, modifier._advancedBlendMode_0_1value);
                    break;
                }
                default: {
                    this.advancedBlendMode((undefined as BlendMode | uiEffect.Blender | undefined), (undefined as BlendApplyType | undefined));
                }
            }
        }
        if (flagArray[187] != 0)
        {
            switch (flagArray[187] as int32) {
                case 1:
                case 3: {
                    this.geometryTransition(modifier._geometryTransition_1_0value, modifier._geometryTransition_1_1value);
                    break;
                }
                default: {
                    this.geometryTransition((undefined as string | undefined), (undefined as GeometryTransitionOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[188] != 0)
        {
            switch (flagArray[188] as int32) {
                case 1:
                case 3: {
                    this.bindTips(modifier._bindTips_0_0value, modifier._bindTips_0_1value);
                    break;
                }
                default: {
                    this.bindTips((undefined as TipsMessageType | undefined), (undefined as TipsOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[189] != 0)
        {
            switch (flagArray[189] as int32) {
                case 1:
                case 3: {
                    this.bindPopup(modifier._bindPopup_0_0value, modifier._bindPopup_0_1value);
                    break;
                }
                default: {
                    this.bindPopup((undefined as boolean | undefined), (undefined as PopupOptions | CustomPopupOptions | undefined));
                }
            }
        }
        if (flagArray[190] != 0)
        {
            switch (flagArray[190] as int32) {
                case 1:
                case 3: {
                    this.bindMenu(modifier._bindMenu_0_0value, modifier._bindMenu_0_1value);
                    break;
                }
                default: {
                    this.bindMenu((undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[191] != 0)
        {
            switch (flagArray[191] as int32) {
                case 1:
                case 3: {
                    this.bindMenu(modifier._bindMenu_1_0value, modifier._bindMenu_1_1value, modifier._bindMenu_1_2value);
                    break;
                }
                default: {
                    this.bindMenu((undefined as boolean | undefined), (undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[192] != 0)
        {
            switch (flagArray[192] as int32) {
                case 1:
                case 3: {
                    this.bindContextMenu(modifier._bindContextMenu_0_0value, modifier._bindContextMenu_0_1value, modifier._bindContextMenu_0_2value);
                    break;
                }
                default: {
                    this.bindContextMenu((undefined as CustomBuilder | undefined), (undefined as ResponseType | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[193] != 0)
        {
            switch (flagArray[193] as int32) {
                case 1:
                case 3: {
                    this.bindContextMenuWithResponse(modifier._bindContextMenuWithResponse_0_0value, modifier._bindContextMenuWithResponse_0_1value);
                    break;
                }
                default: {
                    this.bindContextMenuWithResponse((undefined as CustomBuilderT<ResponseType> | undefined), (undefined as ContextMenuOptions | undefined));
                }
            }
        }
        if (flagArray[194] != 0)
        {
            switch (flagArray[194] as int32) {
                case 1:
                case 3: {
                    this.bindContextMenu(modifier._bindContextMenu_1_0value, modifier._bindContextMenu_1_1value, modifier._bindContextMenu_1_2value);
                    break;
                }
                default: {
                    this.bindContextMenu((undefined as boolean | undefined), (undefined as CustomBuilder | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[195] != 0)
        {
            switch (flagArray[195] as int32) {
                case 1:
                case 3: {
                    this.bindContentCover(modifier._bindContentCover_0_0value, modifier._bindContentCover_0_1value, modifier._bindContentCover_0_2value);
                    break;
                }
                default: {
                    this.bindContentCover((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ModalTransition | undefined | undefined));
                }
            }
        }
        if (flagArray[196] != 0)
        {
            switch (flagArray[196] as int32) {
                case 1:
                case 3: {
                    this.bindContentCover(modifier._bindContentCover_1_0value, modifier._bindContentCover_1_1value, modifier._bindContentCover_1_2value);
                    break;
                }
                default: {
                    this.bindContentCover((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ContentCoverOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[197] != 0)
        {
            switch (flagArray[197] as int32) {
                case 1:
                case 3: {
                    this.bindSheet(modifier._bindSheet_0_0value, modifier._bindSheet_0_1value, modifier._bindSheet_0_2value);
                    break;
                }
                default: {
                    this.bindSheet((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as SheetOptions | undefined | undefined));
                }
            }
        }
        if (flagArray[198] != 0)
        {
            switch (flagArray[198] as int32) {
                case 1:
                case 3: {
                    this.onVisibleAreaChange(modifier._onVisibleAreaChange_0_0value, modifier._onVisibleAreaChange_0_1value);
                    break;
                }
                default: {
                    this.onVisibleAreaChange((undefined as Array<double> | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (flagArray[199] != 0)
        {
            switch (flagArray[199] as int32) {
                case 1:
                case 3: {
                    this.onVisibleAreaApproximateChange(modifier._onVisibleAreaApproximateChange_0_0value, modifier._onVisibleAreaApproximateChange_0_1value);
                    break;
                }
                default: {
                    this.onVisibleAreaApproximateChange((undefined as VisibleAreaEventOptions | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (flagArray[200] != 0)
        {
            switch (flagArray[200] as int32) {
                case 1:
                case 3: {
                    hookMergeKeyboardShortcuts(this, modifier._keyboardShortcutList);
                    break;
                }
                default: {
                    this.keyboardShortcut((undefined as string | FunctionKey | undefined), (undefined as Array<ModifierKey> | undefined), (undefined as (() => void) | undefined | undefined));
                }
            }
        }
    }
    mergeModifier10(modifier: CommonMethodModifier, flagArray: Uint8Array): void {
        if (flagArray[201] != 0)
        {
            switch (flagArray[201] as int32) {
                case 1:
                case 3: {
                    this.accessibilityGroup(modifier._accessibilityGroup_1_0value, modifier._accessibilityGroup_1_1value);
                    break;
                }
                default: {
                    this.accessibilityGroup((undefined as boolean | undefined), (undefined as AccessibilityOptions | undefined));
                }
            }
        }
        if (flagArray[202] != 0)
        {
            switch (flagArray[202] as int32) {
                case 1:
                case 3: {
                    this.onGestureRecognizerJudgeBegin(modifier._onGestureRecognizerJudgeBegin_1_0value, modifier._onGestureRecognizerJudgeBegin_1_1value);
                    break;
                }
                default: {
                    this.onGestureRecognizerJudgeBegin((undefined as GestureRecognizerJudgeBeginCallback | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[203] != 0)
        {
            switch (flagArray[203] as int32) {
                case 1:
                case 3: {
                    this.systemMaterial(modifier._systemMaterial_0_0value);
                    break;
                }
                default: {
                    this.systemMaterial((undefined as uiMaterial.Material | undefined));
                }
            }
        }
        if (flagArray[204] != 0)
        {
            switch (flagArray[204] as int32) {
                case 1:
                case 3: {
                    this.accessibilityStateDescription(modifier._accessibilityStateDescription_0_0value);
                    break;
                }
                default: {
                    this.accessibilityStateDescription((undefined as string | Resource | undefined));
                }
            }
        }
        if (flagArray[205] != 0)
        {
            switch (flagArray[205] as int32) {
                case 1:
                case 3: {
                    this.accessibilityActionOptions(modifier._accessibilityActionOptions_0_0value);
                    break;
                }
                default: {
                    this.accessibilityActionOptions((undefined as AccessibilityActionOptions | undefined));
                }
            }
        }
        if (flagArray[206] != 0)
        {
            switch (flagArray[206] as int32) {
                case 1:
                case 3: {
                    this.useUnionEffect(modifier._useUnionEffect_0_0value);
                    break;
                }
                default: {
                    this.useUnionEffect((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[207] != 0)
        {
            switch (flagArray[207] as int32) {
                case 1:
                case 3: {
                    this.materialFilter(modifier._materialFilter_0_0value);
                    break;
                }
                default: {
                    this.materialFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
    }
    width(value: Length | LayoutPolicy | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true))
        {
            this._flagArray[0] = 1
            this._width_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[0] = 3
        }
        return this
    }
    height(value: Length | LayoutPolicy | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true))
        {
            this._flagArray[1] = 1
            this._height_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[1] = 3
        }
        return this
    }
    responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true))
        {
            this._flagArray[2] = 1
            this._responseRegion_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[2] = 3
        }
        return this
    }
    mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true))
        {
            this._flagArray[3] = 1
            this._mouseResponseRegion_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[3] = 3
        }
        return this
    }
    responseRegionList(value: Array<ResponseRegion> | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true))
        {
            this._flagArray[4] = 1
            this._responseRegionList_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[4] = 3
        }
        return this
    }
    size(value: SizeOptions | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true))
        {
            this._flagArray[5] = 1
            this._size_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[5] = 3
        }
        return this
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true))
        {
            this._flagArray[6] = 1
            this._constraintSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[6] = 3
        }
        return this
    }
    hitTestBehavior(value: HitTestMode | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true))
        {
            this._flagArray[7] = 1
            this._hitTestBehavior_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[7] = 3
        }
        return this
    }
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true))
        {
            this._flagArray[8] = 1
            this._onChildTouchTest_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[8] = 3
        }
        return this
    }
    layoutWeight(value: number | string | undefined): this {
        if (((this._flagArray[9]) == (0)) || ((this._layoutWeight_0_0value) !== (value)))
        {
            this._flagArray[9] = 1
            this._layoutWeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[9] = 3
        }
        return this
    }
    chainWeight(value: ChainWeightOptions | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true))
        {
            this._flagArray[10] = 1
            this._chainWeight_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[10] = 3
        }
        return this
    }
    padding(value: Padding | Length | LocalizedPadding | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true))
        {
            this._flagArray[11] = 1
            this._padding_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[11] = 3
        }
        return this
    }
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true))
        {
            this._flagArray[12] = 1
            this._safeAreaPadding_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[12] = 3
        }
        return this
    }
    margin(value: Padding | Length | LocalizedPadding | undefined): this {
        if (((this._flagArray[13]) == (0)) || (true))
        {
            this._flagArray[13] = 1
            this._margin_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[13] = 3
        }
        return this
    }
    backgroundColor(value: ResourceColor | ColorMetrics | undefined): this {
        if (((this._flagArray[14]) == (0)) || (true))
        {
            this._flagArray[14] = 1
            this._backgroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[14] = 3
        }
        return this
    }
    pixelRound(value: PixelRoundPolicy | undefined): this {
        if (((this._flagArray[15]) == (0)) || (true))
        {
            this._flagArray[15] = 1
            this._pixelRound_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[15] = 3
        }
        return this
    }
    backgroundImage(value: ResourceStr | image.PixelMap | undefined): this {
        if (((this._flagArray[16]) == (0)) || (true))
        {
            this._flagArray[16] = 1
            this._backgroundImage_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[16] = 3
        }
        return this
    }
    backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
        if (((this._flagArray[17]) == (0)) || (true))
        {
            this._flagArray[17] = 1
            this._backgroundImageSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[17] = 3
        }
        return this
    }
    backgroundImagePosition(value: Position | Alignment | undefined): this {
        if (((this._flagArray[18]) == (0)) || (true))
        {
            this._flagArray[18] = 1
            this._backgroundImagePosition_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[18] = 3
        }
        return this
    }
    backgroundEffect(value: BackgroundEffectOptions | undefined): this {
        // instructive change start
        this.backgroundEffectClear();
        // instructive change end
        if (((this._flagArray[19]) == (0)) || (true))
        {
            this._flagArray[19] = 1
            this._backgroundEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[19] = 3
        }
        return this
    }
    backgroundImageResizable(value: ResizableOptions | undefined): this {
        if (((this._flagArray[20]) == (0)) || (true))
        {
            this._flagArray[20] = 1
            this._backgroundImageResizable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[20] = 3
        }
        return this
    }
    foregroundEffect(value: ForegroundEffectOptions | undefined): this {
        if (((this._flagArray[21]) == (0)) || (true))
        {
            this._flagArray[21] = 1
            this._foregroundEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[21] = 3
        }
        return this
    }
    visualEffect(value: uiEffect.VisualEffect | undefined): this {
        if (((this._flagArray[22]) == (0)) || (true))
        {
            this._flagArray[22] = 1
            this._visualEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[22] = 3
        }
        return this
    }
    backgroundFilter(value: uiEffect.Filter | undefined): this {
        if (((this._flagArray[23]) == (0)) || (true))
        {
            this._flagArray[23] = 1
            this._backgroundFilter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[23] = 3
        }
        return this
    }
    foregroundFilter(value: uiEffect.Filter | undefined): this {
        if (((this._flagArray[24]) == (0)) || (true))
        {
            this._flagArray[24] = 1
            this._foregroundFilter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[24] = 3
        }
        return this
    }
    compositingFilter(value: uiEffect.Filter | undefined): this {
        if (((this._flagArray[25]) == (0)) || (true))
        {
            this._flagArray[25] = 1
            this._compositingFilter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[25] = 3
        }
        return this
    }
    opacity(value: double | Resource | undefined): this {
        if (((this._flagArray[26]) == (0)) || (true))
        {
            this._flagArray[26] = 1
            this._opacity_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[26] = 3
        }
        return this
    }
    border(value: BorderOptions | undefined): this {
        if (((this._flagArray[27]) == (0)) || (true))
        {
            this._flagArray[27] = 1
            this._border_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[27] = 3
        }
        return this
    }
    borderStyle(value: BorderStyle | EdgeStyles | undefined): this {
        if (((this._flagArray[28]) == (0)) || (true))
        {
            this._flagArray[28] = 1
            this._borderStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[28] = 3
        }
        return this
    }
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this {
        if (((this._flagArray[29]) == (0)) || (true))
        {
            this._flagArray[29] = 1
            this._borderWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[29] = 3
        }
        return this
    }
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        if (((this._flagArray[30]) == (0)) || (true))
        {
            this._flagArray[30] = 1
            this._borderColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[30] = 3
        }
        return this
    }
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this {
        if (((this._flagArray[31]) == (0)) || (true))
        {
            this._flagArray[31] = 1
            this._borderRadius_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[31] = 3
        }
        return this
    }
    borderImage(value: BorderImageOption | undefined): this {
        if (((this._flagArray[32]) == (0)) || (true))
        {
            this._flagArray[32] = 1
            this._borderImage_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[32] = 3
        }
        return this
    }
    outline(value: OutlineOptions | undefined): this {
        if (((this._flagArray[33]) == (0)) || (true))
        {
            this._flagArray[33] = 1
            this._outline_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[33] = 3
        }
        return this
    }
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
        if (((this._flagArray[34]) == (0)) || (true))
        {
            this._flagArray[34] = 1
            this._outlineStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[34] = 3
        }
        return this
    }
    outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
        if (((this._flagArray[35]) == (0)) || (true))
        {
            this._flagArray[35] = 1
            this._outlineWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[35] = 3
        }
        return this
    }
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        if (((this._flagArray[36]) == (0)) || (true))
        {
            this._flagArray[36] = 1
            this._outlineColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[36] = 3
        }
        return this
    }
    outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
        if (((this._flagArray[37]) == (0)) || (true))
        {
            this._flagArray[37] = 1
            this._outlineRadius_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[37] = 3
        }
        return this
    }
    foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
        if (((this._flagArray[38]) == (0)) || (true))
        {
            this._flagArray[38] = 1
            this._foregroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[38] = 3
        }
        return this
    }
    onClick(value: ((event: ClickEvent) => void) | undefined): this {
        if (((this._flagArray[39]) == (0)) || (true))
        {
            this._flagArray[39] = 1
            this._onClick_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[39] = 3
        }
        return this
    }
    onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
        if (((this._flagArray[40]) == (0)) || (true))
        {
            this._flagArray[40] = 1
            this._onHover_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[40] = 3
        }
        return this
    }
    onHoverMove(value: ((value0: HoverEvent) => void) | undefined): this {
        if (((this._flagArray[41]) == (0)) || (true))
        {
            this._flagArray[41] = 1
            this._onHoverMove_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[41] = 3
        }
        return this
    }
    onAccessibilityHover(value: AccessibilityCallback | undefined): this {
        if (((this._flagArray[42]) == (0)) || (true))
        {
            this._flagArray[42] = 1
            this._onAccessibilityHover_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[42] = 3
        }
        return this
    }
    onAccessibilityHoverTransparent(value: AccessibilityTransparentCallback | undefined): this {
        if (((this._flagArray[43]) == (0)) || (true))
        {
            this._flagArray[43] = 1
            this._onAccessibilityHoverTransparent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[43] = 3
        }
        return this
    }
    hoverEffect(value: HoverEffect | undefined): this {
        if (((this._flagArray[44]) == (0)) || (true))
        {
            this._flagArray[44] = 1
            this._hoverEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[44] = 3
        }
        return this
    }
    onMouse(value: ((event: MouseEvent) => void) | undefined): this {
        if (((this._flagArray[45]) == (0)) || (true))
        {
            this._flagArray[45] = 1
            this._onMouse_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[45] = 3
        }
        return this
    }
    onTouch(value: ((event: TouchEvent) => void) | undefined): this {
        if (((this._flagArray[46]) == (0)) || (true))
        {
            this._flagArray[46] = 1
            this._onTouch_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[46] = 3
        }
        return this
    }
    onKeyEvent(value: ((value0: KeyEvent) => boolean) | undefined): this {
        if (((this._flagArray[47]) == (0)) || (true))
        {
            this._flagArray[47] = 1
            this._onKeyEvent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[47] = 3
        }
        return this
    }
    onDigitalCrown(value: ((value0: CrownEvent) => void) | undefined): this {
        if (((this._flagArray[48]) == (0)) || (true))
        {
            this._flagArray[48] = 1
            this._onDigitalCrown_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[48] = 3
        }
        return this
    }
    onKeyPreIme(value: ((value0: KeyEvent) => boolean) | undefined): this {
        if (((this._flagArray[49]) == (0)) || (true))
        {
            this._flagArray[49] = 1
            this._onKeyPreIme_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[49] = 3
        }
        return this
    }
    onKeyEventDispatch(value: ((value0: KeyEvent) => boolean) | undefined): this {
        if (((this._flagArray[50]) == (0)) || (true))
        {
            this._flagArray[50] = 1
            this._onKeyEventDispatch_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[50] = 3
        }
        return this
    }
    onFocusAxisEvent(value: ((value0: FocusAxisEvent) => void) | undefined): this {
        if (((this._flagArray[51]) == (0)) || (true))
        {
            this._flagArray[51] = 1
            this._onFocusAxisEvent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[51] = 3
        }
        return this
    }
    onAxisEvent(value: ((value0: AxisEvent) => void) | undefined): this {
        if (((this._flagArray[52]) == (0)) || (true))
        {
            this._flagArray[52] = 1
            this._onAxisEvent_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[52] = 3
        }
        return this
    }
    focusable(value: boolean | undefined): this {
        if (((this._flagArray[53]) == (0)) || ((this._focusable_0_0value) !== (value)))
        {
            this._flagArray[53] = 1
            this._focusable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[53] = 3
        }
        return this
    }
    nextFocus(value: FocusMovement | undefined): this {
        if (((this._flagArray[54]) == (0)) || (true))
        {
            this._flagArray[54] = 1
            this._nextFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[54] = 3
        }
        return this
    }
    tabStop(value: boolean | undefined): this {
        if (((this._flagArray[55]) == (0)) || ((this._tabStop_0_0value) !== (value)))
        {
            this._flagArray[55] = 1
            this._tabStop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[55] = 3
        }
        return this
    }
    onFocus(value: (() => void) | undefined): this {
        if (((this._flagArray[56]) == (0)) || (true))
        {
            this._flagArray[56] = 1
            this._onFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[56] = 3
        }
        return this
    }
    onBlur(value: (() => void) | undefined): this {
        if (((this._flagArray[57]) == (0)) || (true))
        {
            this._flagArray[57] = 1
            this._onBlur_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[57] = 3
        }
        return this
    }
    tabIndex(value: int32 | undefined): this {
        if (((this._flagArray[58]) == (0)) || ((this._tabIndex_0_0value) !== (value)))
        {
            this._flagArray[58] = 1
            this._tabIndex_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[58] = 3
        }
        return this
    }
    defaultFocus(value: boolean | undefined): this {
        if (((this._flagArray[59]) == (0)) || ((this._defaultFocus_0_0value) !== (value)))
        {
            this._flagArray[59] = 1
            this._defaultFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[59] = 3
        }
        return this
    }
    groupDefaultFocus(value: boolean | undefined): this {
        if (((this._flagArray[60]) == (0)) || ((this._groupDefaultFocus_0_0value) !== (value)))
        {
            this._flagArray[60] = 1
            this._groupDefaultFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[60] = 3
        }
        return this
    }
    focusOnTouch(value: boolean | undefined): this {
        if (((this._flagArray[61]) == (0)) || ((this._focusOnTouch_0_0value) !== (value)))
        {
            this._flagArray[61] = 1
            this._focusOnTouch_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[61] = 3
        }
        return this
    }
    focusBox(value: FocusBoxStyle | undefined): this {
        if (((this._flagArray[62]) == (0)) || (true))
        {
            this._flagArray[62] = 1
            this._focusBox_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[62] = 3
        }
        return this
    }
    animation(value: AnimateParam | undefined): this {
        if (((this._flagArray[63]) == (0)) || (true))
        {
            this._flagArray[63] = 1
            this._animation_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[63] = 3
        }
        return this
    }
    transition(value: TransitionEffect | undefined): this {
        if (((this._flagArray[64]) == (0)) || (true))
        {
            this._flagArray[64] = 1
            this._transition_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[64] = 3
        }
        return this
    }
    motionBlur(value: MotionBlurOptions | undefined): this {
        if (((this._flagArray[65]) == (0)) || (true))
        {
            this._flagArray[65] = 1
            this._motionBlur_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[65] = 3
        }
        return this
    }
    brightness(value: double | undefined): this {
        if (((this._flagArray[66]) == (0)) || ((this._brightness_0_0value) !== (value)))
        {
            this._flagArray[66] = 1
            this._brightness_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[66] = 3
        }
        return this
    }
    contrast(value: double | undefined): this {
        if (((this._flagArray[67]) == (0)) || ((this._contrast_0_0value) !== (value)))
        {
            this._flagArray[67] = 1
            this._contrast_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[67] = 3
        }
        return this
    }
    grayscale(value: double | undefined): this {
        if (((this._flagArray[68]) == (0)) || ((this._grayscale_0_0value) !== (value)))
        {
            this._flagArray[68] = 1
            this._grayscale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[68] = 3
        }
        return this
    }
    colorBlend(value: Color | string | Resource | undefined): this {
        if (((this._flagArray[69]) == (0)) || (true))
        {
            this._flagArray[69] = 1
            this._colorBlend_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[69] = 3
        }
        return this
    }
    saturate(value: double | undefined): this {
        if (((this._flagArray[70]) == (0)) || ((this._saturate_0_0value) !== (value)))
        {
            this._flagArray[70] = 1
            this._saturate_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[70] = 3
        }
        return this
    }
    sepia(value: double | undefined): this {
        if (((this._flagArray[71]) == (0)) || ((this._sepia_0_0value) !== (value)))
        {
            this._flagArray[71] = 1
            this._sepia_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[71] = 3
        }
        return this
    }
    invert(value: double | InvertOptions | undefined): this {
        if (((this._flagArray[72]) == (0)) || (true))
        {
            this._flagArray[72] = 1
            this._invert_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[72] = 3
        }
        return this
    }
    hueRotate(value: double | string | undefined): this {
        if (((this._flagArray[73]) == (0)) || ((this._hueRotate_0_0value) !== (value)))
        {
            this._flagArray[73] = 1
            this._hueRotate_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[73] = 3
        }
        return this
    }
    useShadowBatching(value: boolean | undefined): this {
        if (((this._flagArray[74]) == (0)) || ((this._useShadowBatching_0_0value) !== (value)))
        {
            this._flagArray[74] = 1
            this._useShadowBatching_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[74] = 3
        }
        return this
    }
    useEffect(value: boolean | undefined): this {
        if (((this._flagArray[75]) == (0)) || ((this._useEffect_0_0value) !== (value)))
        {
            this._flagArray[75] = 1
            this._useEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[75] = 3
        }
        return this
    }
    renderGroup(value: boolean | undefined): this {
        if (((this._flagArray[76]) == (0)) || ((this._renderGroup_0_0value) !== (value)))
        {
            this._flagArray[76] = 1
            this._renderGroup_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[76] = 3
        }
        return this
    }
    freeze(value: boolean | undefined): this {
        if (((this._flagArray[77]) == (0)) || ((this._freeze_0_0value) !== (value)))
        {
            this._flagArray[77] = 1
            this._freeze_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[77] = 3
        }
        return this
    }
    translate(value: TranslateOptions | undefined): this {
        if (((this._flagArray[78]) == (0)) || (true))
        {
            this._flagArray[78] = 1
            this._translate_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[78] = 3
        }
        return this
    }
    scale(value: ScaleOptions | undefined): this {
        if (((this._flagArray[79]) == (0)) || (true))
        {
            this._flagArray[79] = 1
            this._scale_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[79] = 3
        }
        return this
    }
    rotate(value: RotateOptions | RotateAngleOptions | undefined): this {
        if (((this._flagArray[80]) == (0)) || (true))
        {
            this._flagArray[80] = 1
            this._rotate_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[80] = 3
        }
        return this
    }
    transform(value: matrix4.Matrix4Transit | undefined): this {
        if (((this._flagArray[81]) == (0)) || (true))
        {
            this._flagArray[81] = 1
            this._transform_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[81] = 3
        }
        return this
    }
    transform3D(value: matrix4.Matrix4Transit | undefined): this {
        if (((this._flagArray[82]) == (0)) || (true))
        {
            this._flagArray[82] = 1
            this._transform3D_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[82] = 3
        }
        return this
    }
    onAppear(value: (() => void) | undefined): this {
        if (((this._flagArray[83]) == (0)) || (true))
        {
            this._flagArray[83] = 1
            this._onAppear_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[83] = 3
        }
        return this
    }
    onDisAppear(value: (() => void) | undefined): this {
        if (((this._flagArray[84]) == (0)) || (true))
        {
            this._flagArray[84] = 1
            this._onDisAppear_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[84] = 3
        }
        return this
    }
    onAttach(value: VoidCallback | undefined): this {
        if (((this._flagArray[85]) == (0)) || (true))
        {
            this._flagArray[85] = 1
            this._onAttach_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[85] = 3
        }
        return this
    }
    onDetach(value: VoidCallback | undefined): this {
        if (((this._flagArray[86]) == (0)) || (true))
        {
            this._flagArray[86] = 1
            this._onDetach_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[86] = 3
        }
        return this
    }
    onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
        if (((this._flagArray[87]) == (0)) || (true))
        {
            this._flagArray[87] = 1
            this._onAreaChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[87] = 3
        }
        return this
    }
    visibility(value: Visibility | undefined): this {
        if (((this._flagArray[88]) == (0)) || (true))
        {
            this._flagArray[88] = 1
            this._visibility_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[88] = 3
        }
        return this
    }
    flexGrow(value: number | undefined): this {
        if (((this._flagArray[89]) == (0)) || ((this._flexGrow_0_0value) !== (value)))
        {
            this._flagArray[89] = 1
            this._flexGrow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[89] = 3
        }
        return this
    }
    flexShrink(value: number | undefined): this {
        if (((this._flagArray[90]) == (0)) || ((this._flexShrink_0_0value) !== (value)))
        {
            this._flagArray[90] = 1
            this._flexShrink_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[90] = 3
        }
        return this
    }
    flexBasis(value: number | string | undefined): this {
        if (((this._flagArray[91]) == (0)) || ((this._flexBasis_0_0value) !== (value)))
        {
            this._flagArray[91] = 1
            this._flexBasis_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[91] = 3
        }
        return this
    }
    alignSelf(value: ItemAlign | undefined): this {
        if (((this._flagArray[92]) == (0)) || (true))
        {
            this._flagArray[92] = 1
            this._alignSelf_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[92] = 3
        }
        return this
    }
    layoutGravity(value: LocalizedAlignment | undefined): this {
        if (((this._flagArray[93]) == (0)) || (true))
        {
            this._flagArray[93] = 1
            this._layoutGravity_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[93] = 3
        }
        return this
    }
    displayPriority(value: number | undefined): this {
        if (((this._flagArray[94]) == (0)) || ((this._displayPriority_0_0value) !== (value)))
        {
            this._flagArray[94] = 1
            this._displayPriority_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[94] = 3
        }
        return this
    }
    zIndex(value: int32 | undefined): this {
        if (((this._flagArray[95]) == (0)) || ((this._zIndex_0_0value) !== (value)))
        {
            this._flagArray[95] = 1
            this._zIndex_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[95] = 3
        }
        return this
    }
    direction(value: Direction | undefined): this {
        if (((this._flagArray[96]) == (0)) || (true))
        {
            this._flagArray[96] = 1
            this._direction_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[96] = 3
        }
        return this
    }
    align(value: Alignment | LocalizedAlignment | undefined): this {
        if (((this._flagArray[97]) == (0)) || (true))
        {
            this._flagArray[97] = 1
            this._align_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[97] = 3
        }
        return this
    }
    position(value: Position | Edges | LocalizedEdges | undefined): this {
        if (((this._flagArray[98]) == (0)) || (true))
        {
            this._flagArray[98] = 1
            this._position_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[98] = 3
        }
        return this
    }
    markAnchor(value: Position | LocalizedPosition | undefined): this {
        if (((this._flagArray[99]) == (0)) || (true))
        {
            this._flagArray[99] = 1
            this._markAnchor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[99] = 3
        }
        return this
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (((this._flagArray[100]) == (0)) || (true))
        {
            this._flagArray[100] = 1
            this._offset_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[100] = 3
        }
        return this
    }
    enabled(value: boolean | undefined): this {
        if (((this._flagArray[101]) == (0)) || ((this._enabled_0_0value) !== (value)))
        {
            this._flagArray[101] = 1
            this._enabled_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[101] = 3
        }
        return this
    }
    alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        if (((this._flagArray[102]) == (0)) || (true))
        {
            this._flagArray[102] = 1
            this._alignRules_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[102] = 3
        }
        return this
    }
    aspectRatio(value: number | undefined): this {
        if (((this._flagArray[103]) == (0)) || ((this._aspectRatio_0_0value) !== (value)))
        {
            this._flagArray[103] = 1
            this._aspectRatio_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[103] = 3
        }
        return this
    }
    clickEffect(value: ClickEffect | null | undefined): this {
        if (((this._flagArray[104]) == (0)) || (true))
        {
            this._flagArray[104] = 1
            this._clickEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[104] = 3
        }
        return this
    }
    onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this {
        if (((this._flagArray[105]) == (0)) || (true))
        {
            this._flagArray[105] = 1
            this._onDragStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[105] = 3
        }
        return this
    }
    onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._flagArray[106]) == (0)) || (true))
        {
            this._flagArray[106] = 1
            this._onDragEnter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[106] = 3
        }
        return this
    }
    onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._flagArray[107]) == (0)) || (true))
        {
            this._flagArray[107] = 1
            this._onDragMove_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[107] = 3
        }
        return this
    }
    onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._flagArray[108]) == (0)) || (true))
        {
            this._flagArray[108] = 1
            this._onDragLeave_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[108] = 3
        }
        return this
    }
    onDrop(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._flagArray[109]) == (0)) || (true))
        {
            this._flagArray[109] = 1
            this._onDrop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[109] = 3
        }
        return this
    }
    onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._flagArray[110]) == (0)) || (true))
        {
            this._flagArray[110] = 1
            this._onDragEnd_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[110] = 3
        }
        return this
    }
    allowDrop(value: Array<uniformTypeDescriptor.UniformDataType> | Array<string> | null | undefined): this {
        if (((this._flagArray[111]) == (0)) || (true))
        {
            this._flagArray[111] = 1
            this._allowDrop_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[111] = 3
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._flagArray[112]) == (0)) || ((this._draggable_0_0value) !== (value)))
        {
            this._flagArray[112] = 1
            this._draggable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[112] = 3
        }
        return this
    }
    dragPreview(value: CustomBuilder | DragItemInfo | string | undefined): this {
        if (((this._flagArray[113]) == (0)) || (true))
        {
            this._flagArray[113] = 1
            this._dragPreview_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[113] = 3
        }
        return this
    }
    onPreDrag(value: ((value0: PreDragStatus) => void) | undefined): this {
        if (((this._flagArray[114]) == (0)) || (true))
        {
            this._flagArray[114] = 1
            this._onPreDrag_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[114] = 3
        }
        return this
    }
    linearGradient(value: LinearGradientOptions | undefined): this {
        if (((this._flagArray[115]) == (0)) || (true))
        {
            this._flagArray[115] = 1
            this._linearGradient_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[115] = 3
        }
        return this
    }
    sweepGradient(value: SweepGradientOptions | undefined): this {
        if (((this._flagArray[116]) == (0)) || (true))
        {
            this._flagArray[116] = 1
            this._sweepGradient_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[116] = 3
        }
        return this
    }
    radialGradient(value: RadialGradientOptions | undefined): this {
        if (((this._flagArray[117]) == (0)) || (true))
        {
            this._flagArray[117] = 1
            this._radialGradient_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[117] = 3
        }
        return this
    }
    motionPath(value: MotionPathOptions | undefined): this {
        if (((this._flagArray[118]) == (0)) || (true))
        {
            this._flagArray[118] = 1
            this._motionPath_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[118] = 3
        }
        return this
    }
    shadow(value: ShadowOptions | ShadowStyle | undefined): this {
        if (((this._flagArray[119]) == (0)) || (true))
        {
            this._flagArray[119] = 1
            this._shadow_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[119] = 3
        }
        return this
    }
    clip(value: boolean | undefined): this {
        if (((this._flagArray[120]) == (0)) || ((this._clip_0_0value) !== (value)))
        {
            this._flagArray[120] = 1
            this._clip_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[120] = 3
        }
        return this
    }
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        if (((this._flagArray[121]) == (0)) || (true))
        {
            this._flagArray[121] = 1
            this._clipShape_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[121] = 3
        }
        return this
    }
    mask(value: ProgressMask | undefined): this {
        if (((this._flagArray[122]) == (0)) || (true))
        {
            this._flagArray[122] = 1
            this._mask_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[122] = 3
        }
        return this
    }
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        if (((this._flagArray[123]) == (0)) || (true))
        {
            this._flagArray[123] = 1
            this._maskShape_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[123] = 3
        }
        return this
    }
    key(value: string | undefined): this {
        if (((this._flagArray[124]) == (0)) || ((this._key_0_0value) !== (value)))
        {
            this._flagArray[124] = 1
            this._key_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[124] = 3
        }
        return this
    }
    id(value: string | undefined): this {
        if (((this._flagArray[125]) == (0)) || ((this._id_0_0value) !== (value)))
        {
            this._flagArray[125] = 1
            this._id_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[125] = 3
        }
        return this
    }
    geometryTransition(value: string | undefined): this {
        if (((this._flagArray[126]) == (0)) || ((this._geometryTransition_0_0value) !== (value)))
        {
            this._flagArray[126] = 1
            this._geometryTransition_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[126] = 3
        }
        return this
    }
    restoreId(value: int32 | undefined): this {
        if (((this._flagArray[127]) == (0)) || ((this._restoreId_0_0value) !== (value)))
        {
            this._flagArray[127] = 1
            this._restoreId_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[127] = 3
        }
        return this
    }
    sphericalEffect(value: double | undefined): this {
        if (((this._flagArray[128]) == (0)) || ((this._sphericalEffect_0_0value) !== (value)))
        {
            this._flagArray[128] = 1
            this._sphericalEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[128] = 3
        }
        return this
    }
    lightUpEffect(value: double | undefined): this {
        if (((this._flagArray[129]) == (0)) || ((this._lightUpEffect_0_0value) !== (value)))
        {
            this._flagArray[129] = 1
            this._lightUpEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[129] = 3
        }
        return this
    }
    pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
        if (((this._flagArray[130]) == (0)) || (true))
        {
            this._flagArray[130] = 1
            this._pixelStretchEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[130] = 3
        }
        return this
    }
    accessibilityGroup(value: boolean | undefined): this {
        if (((this._flagArray[131]) == (0)) || ((this._accessibilityGroup_0_0value) !== (value)))
        {
            this._flagArray[131] = 1
            this._accessibilityGroup_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[131] = 3
        }
        return this
    }
    accessibilityText(value: Resource | undefined): this {
        if (((this._flagArray[137]) == (0)) || (true)) {
            this._flagArray[137] = 1
            this._accessibilityTextOfResourceType_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[137] = 3
        }
        return this
    }
    accessibilityText(value: string | undefined): this {
        if (((this._flagArray[132]) == (0)) || ((this._accessibilityTextOfStringType_0_0value) !== (value))) {
            this._flagArray[132] = 1
            this._accessibilityTextOfStringType_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[132] = 3
        }
        return this
    }
    accessibilityText(value: Resource | string | undefined): this {
        if (value instanceof Resource) {
            const value_casted = value as (Resource | undefined)
            this.accessibilityText(value_casted)
            this._state.fireChange()
            return this
        } else {
            const value_casted = value as (string | undefined)
            this.accessibilityText(value_casted)
            return this
        }
    }
    accessibilityNextFocusId(value: string | undefined): this {
        if (((this._flagArray[133]) == (0)) || ((this._accessibilityNextFocusId_0_0value) !== (value)))
        {
            this._flagArray[133] = 1
            this._accessibilityNextFocusId_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[133] = 3
        }
        return this
    }
    accessibilityDefaultFocus(value: boolean | undefined): this {
        if (((this._flagArray[134]) == (0)) || ((this._accessibilityDefaultFocus_0_0value) !== (value)))
        {
            this._flagArray[134] = 1
            this._accessibilityDefaultFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[134] = 3
        }
        return this
    }
    accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this {
        if (((this._flagArray[135]) == (0)) || (true))
        {
            this._flagArray[135] = 1
            this._accessibilityUseSamePage_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[135] = 3
        }
        return this
    }
    accessibilityScrollTriggerable(value: boolean | undefined): this {
        if (((this._flagArray[136]) == (0)) || ((this._accessibilityScrollTriggerable_0_0value) !== (value)))
        {
            this._flagArray[136] = 1
            this._accessibilityScrollTriggerable_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[136] = 3
        }
        return this
    }
    accessibilityTextOfResourceType(value: Resource | undefined): this {
        if (((this._flagArray[137]) == (0)) || (true))
        {
            this._flagArray[137] = 1
            this._accessibilityTextOfResourceType_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[137] = 3
        }
        return this
    }
    accessibilityRole(value: AccessibilityRoleType | undefined): this {
        if (((this._flagArray[138]) == (0)) || (true))
        {
            this._flagArray[138] = 1
            this._accessibilityRole_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[138] = 3
        }
        return this
    }
    onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this {
        if (((this._flagArray[139]) == (0)) || (true))
        {
            this._flagArray[139] = 1
            this._onAccessibilityFocus_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[139] = 3
        }
        return this
    }
    onAccessibilityActionIntercept(value: AccessibilityActionInterceptCallback | undefined): this {
        if (((this._flagArray[140]) == (0)) || (true))
        {
            this._flagArray[140] = 1
            this._onAccessibilityActionIntercept_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[140] = 3
        }
        return this
    }
    accessibilityTextHint(value: string | undefined): this {
        if (((this._flagArray[141]) == (0)) || ((this._accessibilityTextHint_0_0value) !== (value)))
        {
            this._flagArray[141] = 1
            this._accessibilityTextHint_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[141] = 3
        }
        return this
    }
    accessibilityDescription(value: string | undefined): this {
        if (((this._flagArray[142]) == (0)) || ((this._accessibilityDescriptionOfStringType_0_0value) !== (value))) {
            this._flagArray[142] = 1
            this._accessibilityDescriptionOfStringType_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[142] = 3
        }
        return this
    }
    accessibilityDescription(value: Resource | undefined): this {
        if (((this._flagArray[143]) == (0)) || (true)) {
            this._flagArray[143] = 1
            this._accessibilityDescriptionOfResourceType_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[143] = 3
        }
        return this
    }
    accessibilityDescription(value: Resource | string | undefined): this {
        if (value instanceof Resource) {
            const value_casted = value as (Resource | undefined)
            this.accessibilityDescription(value_casted)
            this._state.fireChange()
            return this
        } else {
            const value_casted = value as (string | undefined)
            this.accessibilityDescription(value_casted)
            return this
        }
    }
    accessibilityLevel(value: string | undefined): this {
        if (((this._flagArray[144]) == (0)) || ((this._accessibilityLevel_0_0value) !== (value)))
        {
            this._flagArray[144] = 1
            this._accessibilityLevel_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[144] = 3
        }
        return this
    }
    accessibilityVirtualNode(value: CustomBuilder | undefined): this {
        if (((this._flagArray[145]) == (0)) || (true))
        {
            this._flagArray[145] = 1
            this._accessibilityVirtualNode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[145] = 3
        }
        return this
    }
    accessibilityChecked(value: boolean | undefined): this {
        if (((this._flagArray[146]) == (0)) || ((this._accessibilityChecked_0_0value) !== (value)))
        {
            this._flagArray[146] = 1
            this._accessibilityChecked_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[146] = 3
        }
        return this
    }
    accessibilitySelected(value: boolean | undefined): this {
        if (((this._flagArray[147]) == (0)) || ((this._accessibilitySelected_0_0value) !== (value)))
        {
            this._flagArray[147] = 1
            this._accessibilitySelected_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[147] = 3
        }
        return this
    }
    obscured(value: Array<ObscuredReasons> | undefined): this {
        if (((this._flagArray[148]) == (0)) || (true))
        {
            this._flagArray[148] = 1
            this._obscured_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[148] = 3
        }
        return this
    }
    reuseId(value: string | undefined): this {
        if (((this._flagArray[149]) == (0)) || ((this._reuseId_0_0value) !== (value)))
        {
            this._flagArray[149] = 1
            this._reuseId_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[149] = 3
        }
        return this
    }
    reuse(value: ReuseOptions | undefined): this {
        if (((this._flagArray[150]) == (0)) || (true))
        {
            this._flagArray[150] = 1
            this._reuse_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[150] = 3
        }
        return this
    }
    renderFit(value: RenderFit | undefined): this {
        if (((this._flagArray[151]) == (0)) || (true))
        {
            this._flagArray[151] = 1
            this._renderFit_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[151] = 3
        }
        return this
    }
    backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
        if (((this._flagArray[152]) == (0)) || (true))
        {
            this._flagArray[152] = 1
            this._backgroundBrightness_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[152] = 3
        }
        return this
    }
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
        if (((this._flagArray[153]) == (0)) || (true))
        {
            this._flagArray[153] = 1
            this._onGestureJudgeBegin_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[153] = 3
        }
        return this
    }
    onGestureRecognizerJudgeBegin(value: GestureRecognizerJudgeBeginCallback | undefined): this {
        if (((this._flagArray[154]) == (0)) || (true))
        {
            this._flagArray[154] = 1
            this._onGestureRecognizerJudgeBegin_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[154] = 3
        }
        return this
    }
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
        if (((this._flagArray[155]) == (0)) || (true))
        {
            this._flagArray[155] = 1
            this._shouldBuiltInRecognizerParallelWith_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[155] = 3
        }
        return this
    }
    monopolizeEvents(value: boolean | undefined): this {
        if (((this._flagArray[156]) == (0)) || ((this._monopolizeEvents_0_0value) !== (value)))
        {
            this._flagArray[156] = 1
            this._monopolizeEvents_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[156] = 3
        }
        return this
    }
    onTouchIntercept(value: ((value0: TouchEvent) => HitTestMode) | undefined): this {
        if (((this._flagArray[157]) == (0)) || (true))
        {
            this._flagArray[157] = 1
            this._onTouchIntercept_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[157] = 3
        }
        return this
    }
    onSizeChange(value: SizeChangeCallback | undefined): this {
        if (((this._flagArray[158]) == (0)) || (true))
        {
            this._flagArray[158] = 1
            this._onSizeChange_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[158] = 3
        }
        return this
    }
    accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this {
        if (((this._flagArray[159]) == (0)) || (true))
        {
            this._flagArray[159] = 1
            this._accessibilityFocusDrawLevel_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[159] = 3
        }
        return this
    }
    customProperty(name: string, value: CustomProperty): this {
        // instructive change start
        hookCommonMethodModifierCustomProperty(this, name, value)
        // instructive change end
        if (((this._flagArray[160]) == (0)) || ((this._customProperty_0_0value) !== (name)) || (true))
        {
            this._flagArray[160] = 1
            this._customProperty_0_0value = name
            this._customProperty_0_1value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[160] = 3
        }
        return this
    }
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        if (((this._flagArray[161]) == (0)) || (true) || (true))
        {
            this._flagArray[161] = 1
            this._expandSafeArea_0_0value = types
            this._expandSafeArea_0_1value = edges
            this._state.fireChange()
        } else
        {
            this._flagArray[161] = 3
        }
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (((this._flagArray[162]) == (0)) || (true) || (true))
        {
            this._flagArray[162] = 1
            this._ignoreLayoutSafeArea_0_0value = types
            this._ignoreLayoutSafeArea_0_1value = edges
            this._state.fireChange()
        } else
        {
            this._flagArray[162] = 3
        }
        return this
    }
    background(builder: CustomBuilder | undefined, options?: BackgroundOptions): this {
        if (((this._flagArray[163]) == (0)) || (true) || (true))
        {
            this._flagArray[163] = 1
            this._background_0_0value = builder
            this._background_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[163] = 3
        }
        return this
    }
    backgroundImage(src: ResourceStr | image.PixelMap | undefined, options: BackgroundImageOptions): this {
        if (((this._flagArray[164]) == (0)) || (true) || (true))
        {
            this._flagArray[164] = 1
            this._backgroundImage_1_0value = src
            this._backgroundImage_1_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[164] = 3
        }
        return this
    }
    backgroundImage(src: ResourceStr | image.PixelMap | undefined, repeat: ImageRepeat): this {
        if (((this._flagArray[165]) == (0)) || (true) || (true))
        {
            this._flagArray[165] = 1
            this._backgroundImage_2_0value = src
            this._backgroundImage_2_1value = repeat
            this._state.fireChange()
        } else
        {
            this._flagArray[165] = 3
        }
        return this
    }

    // instructive change start
    backgroundEffectClear() {
        // backgroundBlurStyle clear
        this._flagArray[166] = 0;

        // backgroundEffect clear
        this._flagArray[167] = 0;
        this._flagArray[19] = 0;

        // backdropBlur clear
        this._flagArray[178] = 0;
    }
    // instructive change end
    backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        // instructive change start
        this.backgroundEffectClear();
        // instructive change end
        if (((this._flagArray[166]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[166] = 1
            this._backgroundBlurStyle_0_0value = style
            this._backgroundBlurStyle_0_1value = options
            this._backgroundBlurStyle_0_2value = sysOptions
            this._state.fireChange()
        } else
        {
            this._flagArray[166] = 3
        }
        return this
    }
    backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
        // instructive change start
        this.backgroundEffectClear();
        // instructive change end
        if (((this._flagArray[167]) == (0)) || (true) || (true))
        {
            this._flagArray[167] = 1
            this._backgroundEffect_1_0value = options
            this._backgroundEffect_1_1value = sysOptions
            this._state.fireChange()
        } else
        {
            this._flagArray[167] = 3
        }
        return this
    }
    foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._flagArray[168]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[168] = 1
            this._foregroundBlurStyle_0_0value = style
            this._foregroundBlurStyle_0_1value = options
            this._foregroundBlurStyle_0_2value = sysOptions
            this._state.fireChange()
        } else
        {
            this._flagArray[168] = 3
        }
        return this
    }
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined, type?: RenderStrategy): this {
        if (((this._flagArray[169]) == (0)) || (true) || (true))
        {
            this._flagArray[169] = 1
            this._borderRadius_1_0value = value
            this._borderRadius_1_1value = type
            this._state.fireChange()
        } else
        {
            this._flagArray[169] = 3
        }
        return this
    }
    onClick(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: double | undefined): this {
        if (((this._flagArray[170]) == (0)) || (true) || ((this._onClick_1_1value) !== (distanceThreshold)))
        {
            this._flagArray[170] = 1
            this._onClick_1_0value = event
            this._onClick_1_1value = distanceThreshold
            this._state.fireChange()
        } else
        {
            this._flagArray[170] = 3
        }
        return this
    }
    focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
        if (((this._flagArray[171]) == (0)) || ((this._focusScopeId_0_0value) !== (id)) || ((this._focusScopeId_0_1value) !== (isGroup)) || ((this._focusScopeId_0_2value) !== (arrowStepOut)))
        {
            this._flagArray[171] = 1
            this._focusScopeId_0_0value = id
            this._focusScopeId_0_1value = isGroup
            this._focusScopeId_0_2value = arrowStepOut
            this._state.fireChange()
        } else
        {
            this._flagArray[171] = 3
        }
        return this
    }
    focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
        if (((this._flagArray[172]) == (0)) || ((this._focusScopePriority_0_0value) !== (scopeId)) || (true))
        {
            this._flagArray[172] = 1
            this._focusScopePriority_0_0value = scopeId
            this._focusScopePriority_0_1value = priority
            this._state.fireChange()
        } else
        {
            this._flagArray[172] = 3
        }
        return this
    }
    transition(effect: TransitionEffect | undefined, onFinish: TransitionFinishCallback | undefined): this {
        if (((this._flagArray[173]) == (0)) || (true) || (true))
        {
            this._flagArray[173] = 1
            this._transition_1_0value = effect
            this._transition_1_1value = onFinish
            this._state.fireChange()
        } else
        {
            this._flagArray[173] = 3
        }
        return this
    }
    blur(blurRadius: double | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._flagArray[174]) == (0)) || ((this._blur_0_0value) !== (blurRadius)) || (true) || (true))
        {
            this._flagArray[174] = 1
            this._blur_0_0value = blurRadius
            this._blur_0_1value = options
            this._blur_0_2value = sysOptions
            this._state.fireChange()
        } else
        {
            this._flagArray[174] = 3
        }
        return this
    }
    linearGradientBlur(value: double | undefined, options: LinearGradientBlurOptions | undefined): this {
        if (((this._flagArray[175]) == (0)) || ((this._linearGradientBlur_0_0value) !== (value)) || (true))
        {
            this._flagArray[175] = 1
            this._linearGradientBlur_0_0value = value
            this._linearGradientBlur_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[175] = 3
        }
        return this
    }
    systemBarEffect(): this {
        if ((this._flagArray[176]) == (0))
        {
            this._flagArray[176] = 1
            this._state.fireChange()
        } else
        {
            this._flagArray[176] = 3
        }
        return this
    }
    useEffect(useEffect: boolean | undefined, effectType: EffectType | undefined): this {
        if (((this._flagArray[177]) == (0)) || ((this._useEffect_1_0value) !== (useEffect)) || (true))
        {
            this._flagArray[177] = 1
            this._useEffect_1_0value = useEffect
            this._useEffect_1_1value = effectType
            this._state.fireChange()
        } else
        {
            this._flagArray[177] = 3
        }
        return this
    }
    backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        // instructive change start
        this.backgroundEffectClear();
        // instructive change end
        if (((this._flagArray[178]) == (0)) || ((this._backdropBlur_0_0value) !== (radius)) || (true) || (true))
        {
            this._flagArray[178] = 1
            this._backdropBlur_0_0value = radius
            this._backdropBlur_0_1value = options
            this._backdropBlur_0_2value = sysOptions
            this._state.fireChange()
        } else
        {
            this._flagArray[178] = 3
        }
        return this
    }
    sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
        if (((this._flagArray[179]) == (0)) || ((this._sharedTransition_0_0value) !== (id)) || (true))
        {
            this._flagArray[179] = 1
            this._sharedTransition_0_0value = id
            this._sharedTransition_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[179] = 3
        }
        return this
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (((this._flagArray[180]) == (0)) || (true) || (true))
        {
            this._flagArray[180] = 1
            this._chainMode_0_0value = direction
            this._chainMode_0_1value = style
            this._state.fireChange()
        } else
        {
            this._flagArray[180] = 3
        }
        return this
    }
    onDrop(eventCallback: OnDragEventCallback | undefined, dropOptions?: DropOptions): this {
        if (((this._flagArray[181]) == (0)) || (true) || (true))
        {
            this._flagArray[181] = 1
            this._onDrop_1_0value = eventCallback
            this._onDrop_1_1value = dropOptions
            this._state.fireChange()
        } else
        {
            this._flagArray[181] = 3
        }
        return this
    }
    dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this {
        if (((this._flagArray[182]) == (0)) || (true) || (true))
        {
            this._flagArray[182] = 1
            this._dragPreview_1_0value = preview
            this._dragPreview_1_1value = config
            this._state.fireChange()
        } else
        {
            this._flagArray[182] = 3
        }
        return this
    }
    dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this {
        if (((this._flagArray[183]) == (0)) || (true) || (true))
        {
            this._flagArray[183] = 1
            this._dragPreviewOptions_0_0value = value
            this._dragPreviewOptions_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[183] = 3
        }
        return this
    }
    overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this {
        if (((this._flagArray[184]) == (0)) || (true) || (true))
        {
            this._flagArray[184] = 1
            this._overlay_0_0value = value
            this._overlay_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[184] = 3
        }
        return this
    }
    blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
        if (((this._flagArray[185]) == (0)) || (true) || (true))
        {
            this._flagArray[185] = 1
            this._blendMode_0_0value = value
            this._blendMode_0_1value = type
            this._state.fireChange()
        } else
        {
            this._flagArray[185] = 3
        }
        return this
    }
    advancedBlendMode(effect: BlendMode | uiEffect.Blender | undefined, type?: BlendApplyType): this {
        if (((this._flagArray[186]) == (0)) || (true) || (true))
        {
            this._flagArray[186] = 1
            this._advancedBlendMode_0_0value = effect
            this._advancedBlendMode_0_1value = type
            this._state.fireChange()
        } else
        {
            this._flagArray[186] = 3
        }
        return this
    }
    geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
        if (((this._flagArray[187]) == (0)) || ((this._geometryTransition_1_0value) !== (id)) || (true))
        {
            this._flagArray[187] = 1
            this._geometryTransition_1_0value = id
            this._geometryTransition_1_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[187] = 3
        }
        return this
    }
    bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this {
        if (((this._flagArray[188]) == (0)) || (true) || (true))
        {
            this._flagArray[188] = 1
            this._bindTips_0_0value = message
            this._bindTips_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[188] = 3
        }
        return this
    }
    bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this {
        if (((this._flagArray[189]) == (0)) || ((this._bindPopup_0_0value) !== (show)) || (true))
        {
            this._flagArray[189] = 1
            this._bindPopup_0_0value = show
            this._bindPopup_0_1value = popup
            this._state.fireChange()
        } else
        {
            this._flagArray[189] = 3
        }
        return this
    }
    bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this {
        if (((this._flagArray[190]) == (0)) || (true) || (true))
        {
            this._flagArray[190] = 1
            this._bindMenu_0_0value = content
            this._bindMenu_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[190] = 3
        }
        return this
    }
    bindMenu(isShow: boolean | undefined, content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this {
        if (((this._flagArray[191]) == (0)) || ((this._bindMenu_1_0value) !== (isShow)) || (true) || (true))
        {
            this._flagArray[191] = 1
            this._bindMenu_1_0value = isShow
            this._bindMenu_1_1value = content
            this._bindMenu_1_2value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[191] = 3
        }
        return this
    }
    bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions): this {
        if (((this._flagArray[192]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[192] = 1
            this._bindContextMenu_0_0value = content
            this._bindContextMenu_0_1value = responseType
            this._bindContextMenu_0_2value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[192] = 3
        }
        return this
    }
    bindContextMenuWithResponse(content: CustomBuilderT<ResponseType> | undefined, options?: ContextMenuOptions): this {
        if (((this._flagArray[193]) == (0)) || (true) || (true))
        {
            this._flagArray[193] = 1
            this._bindContextMenuWithResponse_0_0value = content
            this._bindContextMenuWithResponse_0_1value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[193] = 3
        }
        return this
    }
    bindContextMenu(isShown: boolean | undefined, content: CustomBuilder | undefined, options?: ContextMenuOptions): this {
        if (((this._flagArray[194]) == (0)) || ((this._bindContextMenu_1_0value) !== (isShown)) || (true) || (true))
        {
            this._flagArray[194] = 1
            this._bindContextMenu_1_0value = isShown
            this._bindContextMenu_1_1value = content
            this._bindContextMenu_1_2value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[194] = 3
        }
        return this
    }
    bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, type?: ModalTransition): this {
        if (((this._flagArray[195]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[195] = 1
            this._bindContentCover_0_0value = isShow
            this._bindContentCover_0_1value = builder
            this._bindContentCover_0_2value = type
            this._state.fireChange()
        } else
        {
            this._flagArray[195] = 3
        }
        return this
    }
    bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: ContentCoverOptions): this {
        if (((this._flagArray[196]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[196] = 1
            this._bindContentCover_1_0value = isShow
            this._bindContentCover_1_1value = builder
            this._bindContentCover_1_2value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[196] = 3
        }
        return this
    }
    bindSheet(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this {
        if (((this._flagArray[197]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[197] = 1
            this._bindSheet_0_0value = isShow
            this._bindSheet_0_1value = builder
            this._bindSheet_0_2value = options
            this._state.fireChange()
        } else
        {
            this._flagArray[197] = 3
        }
        return this
    }
    onVisibleAreaChange(ratios: Array<double> | undefined, event: VisibleAreaChangeCallback | undefined): this {
        if (((this._flagArray[198]) == (0)) || ((this._onVisibleAreaChange_0_0value) !== (ratios)) || (true))
        {
            this._flagArray[198] = 1
            this._onVisibleAreaChange_0_0value = ratios
            this._onVisibleAreaChange_0_1value = event
            this._state.fireChange()
        } else
        {
            this._flagArray[198] = 3
        }
        return this
    }
    onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
        if (((this._flagArray[199]) == (0)) || (true) || (true))
        {
            this._flagArray[199] = 1
            this._onVisibleAreaApproximateChange_0_0value = options
            this._onVisibleAreaApproximateChange_0_1value = event
            this._state.fireChange()
        } else
        {
            this._flagArray[199] = 3
        }
        return this
    }
    keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
        if (((this._flagArray[200]) == (0)) || (true) || (true) || (true))
        {
            this._flagArray[200] = 1
            this._keyboardShortcutList.push({value: value, keys: keys, action: action})
            this._keyboardShortcut_0_0value = value
            this._keyboardShortcut_0_1value = keys
            this._keyboardShortcut_0_2value = action
            this._state.fireChange()
        } else
        {
            this._flagArray[200] = 3
        }
        return this
    }
    accessibilityGroup(isGroup: boolean | undefined, config: AccessibilityOptions | undefined): this {
        if (((this._flagArray[201]) == (0)) || ((this._accessibilityGroup_1_0value) !== (isGroup)) || (true))
        {
            this._flagArray[201] = 1
            this._accessibilityGroup_1_0value = isGroup
            this._accessibilityGroup_1_1value = config
            this._state.fireChange()
        } else
        {
            this._flagArray[201] = 3
        }
        return this
    }
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture: boolean | undefined): this {
        if (((this._flagArray[202]) == (0)) || (true) || ((this._onGestureRecognizerJudgeBegin_1_1value) !== (exposeInnerGesture)))
        {
            this._flagArray[202] = 1
            this._onGestureRecognizerJudgeBegin_1_0value = callback_
            this._onGestureRecognizerJudgeBegin_1_1value = exposeInnerGesture
            this._state.fireChange()
        } else
        {
            this._flagArray[202] = 3
        }
        return this
    }
    systemMaterial(value: uiMaterial.Material | undefined): this {
        if (((this._flagArray[203]) == (0)) || (true))
        {
            this._flagArray[203] = 1
            this._systemMaterial_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[203] = 3
        }
        return this
    }
    accessibilityStateDescription(value: string | Resource | undefined): this {
        if (((this._flagArray[204]) == (0)) || (true))
        {
            this._flagArray[204] = 1
            this._accessibilityStateDescription_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[204] = 3
        }
        return this
    }
    accessibilityActionOptions(value: AccessibilityActionOptions | undefined): this {
        if (((this._flagArray[205]) == (0)) || (true))
        {
            this._flagArray[205] = 1
            this._accessibilityActionOptions_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[205] = 3
        }
        return this
    }
    useUnionEffect(value: boolean | undefined): this {
        if (((this._flagArray[206]) == (0)) || ((this._useUnionEffect_0_0value) !== (value)))
        {
            this._flagArray[206] = 1
            this._useUnionEffect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[206] = 3
        }
        return this
    }
    materialFilter(value: uiEffect.Filter | undefined): this {
        if (((this._flagArray[207]) == (0)) || (true))
        {
            this._flagArray[207] = 1
            this._materialFilter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._flagArray[207] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
