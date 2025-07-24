/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { CommonAttribute, LayoutPolicy } from 'arkui/component/common'
import { Length } from "arkui/component/units"
import { ArkCommonMethodPeer, ClickEvent, CommonMethod, KeyEvent, Rectangle, FocusMovement, SizeChangeCallback,
  ShouldBuiltInRecognizerParallelWithCallback, GestureRecognizerJudgeBeginCallback, FocusAxisEvent, AxisEvent,
  HoverEvent, TouchEvent, MouseEvent, CustomProperty, ArkCommonMethodComponent
} from './component/common'
import { PeerNode } from './PeerNode'
import { ResourceColor, SizeOptions, Area, Position } from './component/units'
import { runtimeType, RuntimeType } from '@koalaui/interop'
import { FunctionKey, ModifierKey, ImageRepeat, ImageSize, HitTestMode, HoverEffect, Visibility, Alignment } from './component/enums'
import { FocusBoxStyle, FocusPriority } from './component/focus'
import { GestureInfo, BaseGestureEvent, GestureJudgeResult } from './component/gesture'
import { ResizableOptions } from './component/image'
import { ResourceStr } from './component/units'
import { PixelMap } from '#external'
import { hookModifierBackgroundImageImpl } from './handwritten/ArkBackgroundImageImpl'
import { hookCustomPropertyImpl } from "./handwritten/CommonHandWritten"

export enum AttributeUpdaterFlag {
    INITIAL = 0,
    UPDATE = 1,
    SKIP = 2,
    RESET = 3,
}
export class CommonMethodModifier implements CommonMethod {
   _width_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _width0_value?: Length | LayoutPolicy | undefined
  
   _backgroundColor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _backgroundColor0_value?: ResourceColor | undefined
  
   _size_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _size0_value?: SizeOptions | undefined
  
   _onClick_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onClick0_value?: ((event: ClickEvent) => void) | undefined
  
   _zIndex_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _zIndex0_value?: number | undefined
  
   _backgroundImage_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _backgroundImage_src?: ResourceStr | PixelMap | undefined
   _backgroundImage_repeat?: ImageRepeat | undefined

   _backgroundImageSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _backgroundImageSize_value?: SizeOptions | ImageSize | undefined

   _backgroundImagePosition_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _backgroundImagePosition_value?: Position | Alignment | undefined

   _backgroundImageResizable_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _backgroundImageResizable_value?: ResizableOptions | undefined

   _onHover_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onHover_value?: ((isHover: boolean,event: HoverEvent) => void) | undefined

   _onHoverMove_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onHoverMove_value?: ((parameter: HoverEvent) => void) | undefined

   _onMouse_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onMouse_value?: ((event: MouseEvent) => void) | undefined

   _onTouch_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onTouch_value?: ((event: TouchEvent) => void) | undefined

   _onFocusAxisEvent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onFocusAxisEvent_value?: ((parameter: FocusAxisEvent) => void) | undefined
   
   _onAxisEvent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onAxisEvent_value?: ((parameter: AxisEvent) => void) | undefined

   _onKeyEvent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onKeyEvent1_value?: ((event: KeyEvent) => boolean) | undefined

   _onKeyPreIme_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onKeyPreIme_value?: ((event: KeyEvent) => boolean) | undefined
   
   _onKeyEventDispatch_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onKeyEventDispatch_value?: ((event: KeyEvent) => boolean) | undefined

   _keyboardShortcut_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _keyboardShortcut_value?: string | FunctionKey | undefined
   _keyboardShortcut_keys?: Array<ModifierKey> | undefined
   _keyboardShortcut_action?: (() => void)
  
   _focusable_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _focusable_value?: boolean | undefined

   _nextFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _nextFocus_value?: FocusMovement | undefined

   _tabIndex_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _tabIndex_value?: number | undefined

   _defaultFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _defaultFocus_value?: boolean | undefined

   _groupDefaultFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _groupDefaultFocus_value?: boolean | undefined

   _focusOnTouch_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _focusOnTouch_value?: boolean | undefined

   _focusBox_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _focusBox_value?: FocusBoxStyle | undefined

   _focusScopeId_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _focusScopeId_id?: string | undefined
   _focusScopeId_isGroup?: boolean
   _focusScopeId_arrowStepOut?: boolean

   _focusScopePriority_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _focusScopePriority_scopeId?: string | undefined
   _focusScopePriority_priority?: FocusPriority

   _tabStop_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _tabStop_value?: boolean | undefined

   _onFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onFocus_value?: (() => void) | undefined

   _onBlur_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onBlur_value?: (() => void) | undefined

   _onAppear_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onAppear_value?: (() => void) | undefined

   _onDisAppear_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onDisAppear_value?: (() => void) | undefined

   _onAttach_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onAttach_value?: (() => void) | undefined

   _onDetach_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onDetach_value?: (() => void) | undefined

   _onAreaChange_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onAreaChange_value?: ((oldValue: Area,newValue: Area) => void) | undefined

   _onSizeChange_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onSizeChange_value?: SizeChangeCallback | undefined

   _onGestureJudgeBegin_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onGestureJudgeBegin_value?: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined

   _shouldBuiltInRecognizerParallelWith_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _shouldBuiltInRecognizerParallelWith_value?: ShouldBuiltInRecognizerParallelWithCallback | undefined

   _onGestureRecognizerJudgeBegin_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onGestureRecognizerJudgeBegin_callback?: GestureRecognizerJudgeBeginCallback | undefined
   _onGestureRecognizerJudgeBegin_exposeInnerGesture?: boolean

   _responseRegion_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _responseRegion_value?: Array<Rectangle> | Rectangle | undefined

   _hitTestBehavior_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _hitTestBehavior_value?: HitTestMode | undefined

   _monopolizeEvents_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _monopolizeEvents_value?: boolean | undefined

   _restoreId_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _restoreId_value?:  number | undefined
  
   _hoverEffect_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _hoverEffect_value?:  HoverEffect | undefined

   _enabled_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _enabled_value?:  boolean | undefined

   _visibility_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _visibility_value?:  Visibility | undefined

   _key_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _key_value?:  string | undefined

   _customProperty_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _customPropertyMap?: Map<string, CustomProperty>

   public width(value: Length | LayoutPolicy | undefined): this {
     if (this._width_flag === AttributeUpdaterFlag.INITIAL || this._width0_value !== value || !Type.of(value).isPrimitive()) {
       this._width0_value = value
       this._width_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._width_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public backgroundColor(value: ResourceColor | undefined): this {
  
     if (this._backgroundColor_flag === AttributeUpdaterFlag.INITIAL || this._backgroundColor0_value !== value || !Type.of(value).isPrimitive()) {
       this._backgroundColor0_value = value
       this._backgroundColor_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._backgroundColor_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onClick(value: ((event: ClickEvent) => void) | undefined): this {
     if (this._onClick_flag === AttributeUpdaterFlag.INITIAL || this._onClick0_value !== value || !Type.of(value).isPrimitive()) {
       this._onClick0_value = value
       this._onClick_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onClick_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public size(value: SizeOptions | undefined): this {
     if (this._size_flag === AttributeUpdaterFlag.INITIAL || this._size0_value !== value || !Type.of(value).isPrimitive()) {
       this._size0_value = value
       this._size_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._size_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public zIndex(value: number | undefined): this {
     if (this._zIndex_flag === AttributeUpdaterFlag.INITIAL || this._zIndex0_value !== value || !Type.of(value).isPrimitive()) {
       this._zIndex0_value = value
       this._zIndex_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._zIndex_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this {
     if (this._backgroundImage_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImage_src !== src || this._backgroundImage_repeat !== repeat || runtimeType(src) === RuntimeType.OBJECT) {
       this._backgroundImage_src = src
       this._backgroundImage_repeat = repeat
       this._backgroundImage_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._backgroundImage_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
     if (this._backgroundImageSize_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImageSize_value !== value || !Type.of(value).isPrimitive()) {
       this._backgroundImageSize_value = value
       this._backgroundImageSize_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._backgroundImageSize_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public backgroundImagePosition(value: Position | Alignment | undefined): this {
     if (this._backgroundImagePosition_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImagePosition_value !== value || !Type.of(value).isPrimitive()) {
       this._backgroundImagePosition_value = value
       this._backgroundImagePosition_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._backgroundImagePosition_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public backgroundImageResizable(value: ResizableOptions | undefined): this {
     if (this._backgroundImageResizable_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImageResizable_value !== value || !Type.of(value).isPrimitive()) {
       this._backgroundImageResizable_value = value
       this._backgroundImageResizable_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._backgroundImageResizable_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
     if (this._onHover_flag === AttributeUpdaterFlag.INITIAL || this._onHover_value !== value || !Type.of(value).isPrimitive()) {
       this._onHover_value = value
       this._onHover_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onHover_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this {
     if (this._onHoverMove_flag === AttributeUpdaterFlag.INITIAL || this._onHoverMove_value !== value || !Type.of(value).isPrimitive()) {
       this._onHoverMove_value = value
       this._onHoverMove_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onHoverMove_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onMouse(value: ((event: MouseEvent) => void) | undefined): this {
     if (this._onMouse_flag === AttributeUpdaterFlag.INITIAL || this._onMouse_value !== value || !Type.of(value).isPrimitive()) {
       this._onMouse_value = value
       this._onMouse_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onMouse_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onTouch(value: ((event: TouchEvent) => void) | undefined): this {
     if (this._onTouch_flag === AttributeUpdaterFlag.INITIAL || this._onTouch_value !== value || !Type.of(value).isPrimitive()) {
       this._onTouch_value = value
       this._onTouch_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onTouch_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this {
     if (this._onFocusAxisEvent_flag === AttributeUpdaterFlag.INITIAL || this._onFocusAxisEvent_value !== value || !Type.of(value).isPrimitive()) {
       this._onFocusAxisEvent_value = value
       this._onFocusAxisEvent_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onFocusAxisEvent_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this {
     if (this._onAxisEvent_flag === AttributeUpdaterFlag.INITIAL || this._onAxisEvent_value !== value || !Type.of(value).isPrimitive()) {
       this._onAxisEvent_value = value
       this._onAxisEvent_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onAxisEvent_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
     if (this._onKeyEvent_flag === AttributeUpdaterFlag.INITIAL || this._onKeyEvent1_value !== value || !Type.of(value).isPrimitive()) {
       this._onKeyEvent1_value = value
       this._onKeyEvent_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onKeyEvent_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onKeyPreIme(value: ((event: KeyEvent) => boolean) | undefined): this {
     if (this._onKeyPreIme_flag === AttributeUpdaterFlag.INITIAL || this._onKeyPreIme_value !== value || !Type.of(value).isPrimitive()) {
       this._onKeyPreIme_value = value
       this._onKeyPreIme_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onKeyPreIme_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onKeyEventDispatch(value: ((event: KeyEvent) => boolean) | undefined): this {
     if (this._onKeyEventDispatch_flag === AttributeUpdaterFlag.INITIAL || this._onKeyEventDispatch_value !== value || !Type.of(value).isPrimitive()) {
       this._onKeyEventDispatch_value = value
       this._onKeyEventDispatch_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onKeyEventDispatch_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
    if (this._keyboardShortcut_flag === AttributeUpdaterFlag.INITIAL || this._keyboardShortcut_value !== value ||
      this._keyboardShortcut_keys !== keys || this._keyboardShortcut_action !== action ||
      !Type.of(value).isPrimitive()) {
      this._keyboardShortcut_value = value
      this._keyboardShortcut_keys = keys
      this._keyboardShortcut_action = action
      this._keyboardShortcut_flag = AttributeUpdaterFlag.UPDATE
    } else {
       this._keyboardShortcut_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public focusable(value: boolean | undefined): this {
     if (this._focusable_flag === AttributeUpdaterFlag.INITIAL || this._focusable_value !== value || !Type.of(value).isPrimitive()) {
       this._focusable_value = value
       this._focusable_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._focusable_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public nextFocus(value: FocusMovement | undefined): this {
     if (this._nextFocus_flag === AttributeUpdaterFlag.INITIAL || this._nextFocus_value !== value || !Type.of(value).isPrimitive()) {
       this._nextFocus_value = value
       this._nextFocus_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._nextFocus_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public tabIndex(value: number | undefined): this {
     if (this._tabIndex_flag === AttributeUpdaterFlag.INITIAL || this._tabIndex_value !== value || !Type.of(value).isPrimitive()) {
       this._tabIndex_value = value
       this._tabIndex_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._tabIndex_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public defaultFocus(value: boolean | undefined): this {
     if (this._defaultFocus_flag === AttributeUpdaterFlag.INITIAL || this._defaultFocus_value !== value || !Type.of(value).isPrimitive()) {
       this._defaultFocus_value = value
       this._defaultFocus_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._defaultFocus_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public groupDefaultFocus(value: boolean | undefined): this {
     if (this._groupDefaultFocus_flag === AttributeUpdaterFlag.INITIAL || this._groupDefaultFocus_value !== value || !Type.of(value).isPrimitive()) {
       this._groupDefaultFocus_value = value
       this._groupDefaultFocus_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._groupDefaultFocus_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public focusOnTouch(value: boolean | undefined): this {
     if (this._focusOnTouch_flag === AttributeUpdaterFlag.INITIAL || this._focusOnTouch_value !== value) {
       this._focusOnTouch_value = value
       this._focusOnTouch_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._focusOnTouch_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public focusBox(value: FocusBoxStyle | undefined): this {
     if (this._focusBox_flag === AttributeUpdaterFlag.INITIAL || this._focusBox_value !== value || !Type.of(value).isPrimitive()) {
       this._focusBox_value = value
       this._focusBox_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._focusBox_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
     if (this._focusScopeId_flag === AttributeUpdaterFlag.INITIAL || this._focusScopeId_id !== id || this._focusScopeId_isGroup !== isGroup || this._focusScopeId_arrowStepOut !== arrowStepOut || !Type.of(id).isPrimitive()) {
       this._focusScopeId_id = id
       this._focusScopeId_isGroup = isGroup
       this._focusScopeId_arrowStepOut = arrowStepOut
       this._focusScopeId_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._focusScopeId_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
     if (this._focusScopePriority_flag === AttributeUpdaterFlag.INITIAL || this._focusScopePriority_scopeId !== scopeId || this._focusScopePriority_priority !== priority || !Type.of(scopeId).isPrimitive()) {
       this._focusScopePriority_scopeId = scopeId
       this._focusScopePriority_priority = priority
       this._focusScopePriority_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._focusScopePriority_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public tabStop(value: boolean | undefined): this {
     if (this._tabStop_flag === AttributeUpdaterFlag.INITIAL || this._tabStop_value !== value || !Type.of(value).isPrimitive()) {
       this._tabStop_value = value
       this._tabStop_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._tabStop_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onFocus(value: (() => void) | undefined): this {
     if (this._onFocus_flag === AttributeUpdaterFlag.INITIAL || this._onFocus_value !== value || !Type.of(value).isPrimitive()) {
       this._onFocus_value = value
       this._onFocus_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onFocus_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onBlur(value: (() => void) | undefined): this {
     if (this._onBlur_flag === AttributeUpdaterFlag.INITIAL || this._onBlur_value !== value || !Type.of(value).isPrimitive()) {
       this._onBlur_value = value
       this._onBlur_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onBlur_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onAppear(value: (() => void) | undefined): this {
     if (this._onAppear_flag === AttributeUpdaterFlag.INITIAL || this._onAppear_value !== value || !Type.of(value).isPrimitive()) {
       this._onAppear_value = value
       this._onAppear_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onAppear_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onDisAppear(value: (() => void) | undefined): this {
     if (this._onDisAppear_flag === AttributeUpdaterFlag.INITIAL || this._onDisAppear_value !== value || !Type.of(value).isPrimitive()) {
       this._onDisAppear_value = value
       this._onDisAppear_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onDisAppear_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onAttach(value: (() => void) | undefined): this {
     if (this._onAttach_flag === AttributeUpdaterFlag.INITIAL || this._onAttach_value !== value || !Type.of(value).isPrimitive()) {
       this._onAttach_value = value
       this._onAttach_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onAttach_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onDetach(value: (() => void) | undefined): this {
     if (this._onDetach_flag === AttributeUpdaterFlag.INITIAL || this._onDetach_value !== value || !Type.of(value).isPrimitive()) {
       this._onDetach_value = value
       this._onDetach_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onDetach_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
     if (this._onAreaChange_flag === AttributeUpdaterFlag.INITIAL || this._onAreaChange_value !== value || !Type.of(value).isPrimitive()) {
       this._onAreaChange_value = value
       this._onAreaChange_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onAreaChange_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onSizeChange(value: SizeChangeCallback | undefined): this {
     if (this._onSizeChange_flag === AttributeUpdaterFlag.INITIAL || this._onSizeChange_value !== value || !Type.of(value).isPrimitive()) {
       this._onSizeChange_value = value
       this._onSizeChange_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onSizeChange_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
     if (this._onGestureJudgeBegin_flag === AttributeUpdaterFlag.INITIAL || this._onGestureJudgeBegin_value !== value || !Type.of(value).isPrimitive()) {
       this._onGestureJudgeBegin_value = value
       this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
     if (this._shouldBuiltInRecognizerParallelWith_flag === AttributeUpdaterFlag.INITIAL || this._shouldBuiltInRecognizerParallelWith_value !== value || !Type.of(value).isPrimitive()) {
       this._shouldBuiltInRecognizerParallelWith_value = value
       this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this {
     if (this._onGestureRecognizerJudgeBegin_flag === AttributeUpdaterFlag.INITIAL || this._onGestureRecognizerJudgeBegin_callback !== callback_ || this._onGestureRecognizerJudgeBegin_exposeInnerGesture !== exposeInnerGesture || !Type.of(callback_).isPrimitive()) {
       this._onGestureRecognizerJudgeBegin_callback = callback_
       this._onGestureRecognizerJudgeBegin_exposeInnerGesture = exposeInnerGesture
       this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
     if (this._responseRegion_flag === AttributeUpdaterFlag.INITIAL || this._responseRegion_value !== value || !Type.of(value).isPrimitive()) {
       this._responseRegion_value = value
       this._responseRegion_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._responseRegion_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public hitTestBehavior(value: HitTestMode | undefined): this {
     if (this._hitTestBehavior_flag === AttributeUpdaterFlag.INITIAL || this._hitTestBehavior_value !== value) {
       this._hitTestBehavior_value = value
       this._hitTestBehavior_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._hitTestBehavior_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public monopolizeEvents(value: boolean | undefined): this {
     if (this._monopolizeEvents_flag === AttributeUpdaterFlag.INITIAL || this._monopolizeEvents_value !== value) {
       this._monopolizeEvents_value = value
       this._monopolizeEvents_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._monopolizeEvents_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public restoreId(value: number | undefined): this {
     if (this._restoreId_flag === AttributeUpdaterFlag.INITIAL || this._restoreId_value !== value || !Type.of(value).isPrimitive()) {
       this._restoreId_value = value
       this._restoreId_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._restoreId_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public hoverEffect(value: HoverEffect | undefined): this {
     if (this._hoverEffect_flag === AttributeUpdaterFlag.INITIAL || this._hoverEffect_value !== value) {
       this._hoverEffect_value = value
       this._hoverEffect_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._hoverEffect_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public enabled(value: boolean | undefined): this {
     if (this._enabled_flag === AttributeUpdaterFlag.INITIAL || this._enabled_value !== value) {
       this._enabled_value = value
       this._enabled_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._enabled_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public visibility(value: Visibility | undefined): this {
     if (this._visibility_flag === AttributeUpdaterFlag.INITIAL || this._visibility_value !== value) {
       this._visibility_value = value
       this._visibility_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._visibility_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public key(value: string | undefined): this {
     if (this._key_flag === AttributeUpdaterFlag.INITIAL || this._key_value !== value || !Type.of(value).isPrimitive()) {
       this._key_value = value
       this._key_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._key_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
  public customProperty(name: string, value: CustomProperty): this {
    if (this._customPropertyMap === undefined) {
      this._customPropertyMap = new Map<string, CustomProperty>();
    }
    this._customPropertyMap!.set(name, value);
    this._customProperty_flag = AttributeUpdaterFlag.UPDATE;
    return this;
  }
   applyModifierPatch(node: PeerNode): void {
     const peerNode: ArkCommonMethodPeer = node as ArkCommonMethodPeer
     if (this._width_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._width_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.width1Attribute((this._width0_value as Length | LayoutPolicy | undefined))
           this._width_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._width_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._width_flag = AttributeUpdaterFlag.INITIAL
           peerNode.width1Attribute(undefined)
         }
       }
     }
     if (this._backgroundColor_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._backgroundColor_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.backgroundColor0Attribute((this._backgroundColor0_value as ResourceColor | undefined))
           this._backgroundColor_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._backgroundColor_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._backgroundColor_flag = AttributeUpdaterFlag.INITIAL
           peerNode.backgroundColor0Attribute(undefined)
         }
       }
     }
     if (this._onClick_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onClick_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onClick0Attribute((this._onClick0_value as ((event: ClickEvent) => void) | undefined))
           this._onClick_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onClick_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onClick_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onClick0Attribute(undefined)
         }
       }
     }
  
     if (this._size_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._size_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.sizeAttribute(this._size0_value as (SizeOptions | undefined))
           this._size_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._size_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._size_flag = AttributeUpdaterFlag.INITIAL
           peerNode.sizeAttribute(undefined)
         }
       }
     }
     if (this._zIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._zIndex_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.zIndexAttribute(this._zIndex0_value as (number | undefined))
           this._zIndex_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._zIndex_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._zIndex_flag = AttributeUpdaterFlag.INITIAL
           peerNode.zIndexAttribute(undefined)
         }
       }
     }
     if (this._backgroundImage_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._backgroundImage_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           hookModifierBackgroundImageImpl(peerNode, (this._backgroundImage_src as ResourceStr | PixelMap | undefined), (this._backgroundImage_repeat as ImageRepeat | undefined))
           this._backgroundImage_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._backgroundImage_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._backgroundImage_flag = AttributeUpdaterFlag.INITIAL
           hookModifierBackgroundImageImpl(peerNode, undefined)
         }
       }
     }
     if (this._backgroundImageSize_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._backgroundImageSize_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.backgroundImageSizeAttribute((this._backgroundImageSize_value as SizeOptions | ImageSize | undefined))
           this._backgroundImageSize_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._backgroundImageSize_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._backgroundImageSize_flag = AttributeUpdaterFlag.INITIAL
           peerNode.backgroundImageSizeAttribute(undefined)
         }
       }
     }
     if (this._backgroundImagePosition_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._backgroundImagePosition_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.backgroundImagePositionAttribute((this._backgroundImagePosition_value as Position | Alignment | undefined))
           this._backgroundImagePosition_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._backgroundImagePosition_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._backgroundImagePosition_flag = AttributeUpdaterFlag.INITIAL
           peerNode.backgroundImagePositionAttribute(undefined)
         }
       }
     }
     if (this._backgroundImageResizable_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._backgroundImageResizable_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.backgroundImageResizableAttribute((this._backgroundImageResizable_value as ResizableOptions | undefined))
           this._backgroundImageResizable_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._backgroundImageResizable_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._backgroundImageResizable_flag = AttributeUpdaterFlag.INITIAL
           peerNode.backgroundImageResizableAttribute(undefined)
         }
       }
     }
      if (this._onHover_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onHover_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onHoverAttribute((this._onHover_value as ((isHover: boolean,event: HoverEvent) => void) | undefined))
           this._onHover_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onHover_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onHover_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onHoverAttribute(undefined)
         }
       }
     }
     if (this._onHoverMove_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onHoverMove_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onHoverMoveAttribute((this._onHoverMove_value as ((parameter: HoverEvent) => void) | undefined))
           this._onHoverMove_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onHoverMove_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onHoverMove_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onHoverMoveAttribute(undefined)
         }
       }
     }
     if (this._onMouse_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onMouse_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onMouseAttribute((this._onMouse_value as (((event: MouseEvent) => void) | undefined)))
           this._onMouse_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onMouse_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onMouse_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onMouseAttribute(undefined)
         }
       }
     }
     if (this._onTouch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onTouch_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onTouchAttribute((this._onTouch_value as (((event: TouchEvent) => void) | undefined)))
           this._onTouch_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onTouch_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onTouch_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onTouchAttribute(undefined)
         }
       }
     }
     if (this._onFocusAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onFocusAxisEvent_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onFocusAxisEventAttribute((this._onFocusAxisEvent_value as (((parameter: FocusAxisEvent) => void) | undefined)))
           this._onFocusAxisEvent_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onFocusAxisEvent_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onFocusAxisEvent_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onFocusAxisEventAttribute(undefined)
         }
       }
     }
     if (this._onAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onAxisEvent_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onAxisEventAttribute((this._onAxisEvent_value as (((parameter: AxisEvent) => void) | undefined)))
           this._onAxisEvent_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onAxisEvent_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onAxisEvent_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onAxisEventAttribute(undefined)
         }
       }
     }
     if (this._onKeyEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onKeyEvent_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onKeyEvent1Attribute((this._onKeyEvent1_value as ((event: KeyEvent) => boolean) | undefined))
           this._onKeyEvent_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onKeyEvent_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onKeyEvent_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onKeyEvent1Attribute(undefined)
         }
       }
     }
     if (this._onKeyPreIme_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onKeyPreIme_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onKeyPreImeAttribute((this._onKeyPreIme_value as ((event: KeyEvent) => boolean) | undefined))
           this._onKeyPreIme_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onKeyPreIme_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onKeyPreIme_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onKeyPreImeAttribute(undefined)
         }
       }
     }
     if (this._onKeyEventDispatch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onKeyEventDispatch_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onKeyEventDispatchAttribute((this._onKeyEventDispatch_value as ((event: KeyEvent) => boolean) | undefined))
           this._onKeyEventDispatch_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onKeyEventDispatch_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onKeyEventDispatch_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onKeyEventDispatchAttribute(undefined)
         }
       }
     }
     if (this._keyboardShortcut_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._keyboardShortcut_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.keyboardShortcutAttribute((this._keyboardShortcut_value as string | FunctionKey | undefined), (this._keyboardShortcut_keys as Array<ModifierKey> | undefined), (this._keyboardShortcut_action as (() => void)))
           this._keyboardShortcut_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._keyboardShortcut_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._keyboardShortcut_flag = AttributeUpdaterFlag.INITIAL
           peerNode.keyboardShortcutAttribute(undefined, undefined)
         }
       }
     }
     if (this._focusable_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._focusable_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.focusableAttribute((this._focusable_value as boolean | undefined))
           this._focusable_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._focusable_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._focusable_flag = AttributeUpdaterFlag.INITIAL
           peerNode.focusableAttribute(undefined)
         }
       }
     }
     if (this._nextFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._nextFocus_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.nextFocusAttribute((this._nextFocus_value as FocusMovement | undefined))
           this._nextFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._nextFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._nextFocus_flag = AttributeUpdaterFlag.INITIAL
           peerNode.nextFocusAttribute(undefined)
         }
       }
     }
     if (this._tabIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._tabIndex_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.tabIndexAttribute((this._tabIndex_value as (number | undefined)))
           this._tabIndex_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._tabIndex_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._tabIndex_flag = AttributeUpdaterFlag.INITIAL
           peerNode.tabIndexAttribute(undefined)
         }
       }
     }
     if (this._defaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._defaultFocus_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.defaultFocusAttribute((this._defaultFocus_value as (boolean | undefined)))
           this._defaultFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._defaultFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._defaultFocus_flag = AttributeUpdaterFlag.INITIAL
           peerNode.defaultFocusAttribute(undefined)
         }
       }
     }
     if (this._groupDefaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._groupDefaultFocus_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.groupDefaultFocusAttribute((this._groupDefaultFocus_value as (boolean | undefined)))
           this._groupDefaultFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._groupDefaultFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._groupDefaultFocus_flag = AttributeUpdaterFlag.INITIAL
           peerNode.groupDefaultFocusAttribute(undefined)
         }
       }
     }
     if (this._focusOnTouch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._focusOnTouch_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.focusOnTouchAttribute((this._focusOnTouch_value as (boolean | undefined)))
           this._focusOnTouch_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._focusOnTouch_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._focusOnTouch_flag = AttributeUpdaterFlag.INITIAL
           peerNode.focusOnTouchAttribute(undefined)
         }
       }
     }
     if (this._focusBox_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._focusBox_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.focusBoxAttribute((this._focusBox_value as (FocusBoxStyle | undefined)))
           this._focusBox_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._focusBox_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._focusBox_flag = AttributeUpdaterFlag.INITIAL
           peerNode.focusBoxAttribute(undefined)
         }
       }
     }
     if (this._focusScopeId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._focusScopeId_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.focusScopeId1Attribute((this._focusScopeId_id as (string | undefined)), (this._focusScopeId_isGroup as boolean), (this._focusScopeId_arrowStepOut as boolean))
           this._focusScopeId_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._focusScopeId_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._focusScopeId_flag = AttributeUpdaterFlag.INITIAL
           peerNode.focusScopeId1Attribute(undefined)
         }
       }
     }
     if (this._focusScopePriority_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._focusScopePriority_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.focusScopePriorityAttribute((this._focusScopePriority_scopeId as (string | undefined)), (this._focusScopePriority_priority as FocusPriority))
           this._focusScopePriority_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._focusScopePriority_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._focusScopePriority_flag = AttributeUpdaterFlag.INITIAL
           peerNode.focusScopePriorityAttribute(undefined)
         }
       }
     }
     if (this._tabStop_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._tabStop_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.tabStopAttribute((this._tabStop_value as (boolean | undefined)))
           this._tabStop_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._tabStop_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._tabStop_flag = AttributeUpdaterFlag.INITIAL
           peerNode.tabStopAttribute(undefined)
         }
       }
     }
     if (this._onFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onFocus_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onFocusAttribute((this._onFocus_value as ((() => void) | undefined)))
           this._onFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onFocus_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onFocus_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onFocusAttribute(undefined)
         }
       }
     }
     if (this._onBlur_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onBlur_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onBlurAttribute((this._onBlur_value as ((() => void) | undefined)))
           this._onBlur_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onBlur_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onBlur_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onBlurAttribute(undefined)
         }
       }
     }
     if (this._onAppear_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onAppear_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onAppearAttribute((this._onAppear_value as ((() => void) | undefined)))
           this._onAppear_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onAppear_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onAppear_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onAppearAttribute(undefined)
         }
       }
     }
     if (this._onDisAppear_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onDisAppear_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onDisAppearAttribute((this._onDisAppear_value as ((() => void) | undefined)))
           this._onDisAppear_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onDisAppear_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onDisAppear_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onDisAppearAttribute(undefined)
         }
       }
     }
     if (this._onAttach_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onAttach_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onAttachAttribute((this._onAttach_value as ((() => void) | undefined)))
           this._onAttach_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onAttach_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onAttach_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onAttachAttribute(undefined)
         }
       }
     }
     if (this._onDetach_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onDetach_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onDetachAttribute((this._onDetach_value as ((() => void) | undefined)))
           this._onDetach_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onDetach_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onDetach_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onDetachAttribute(undefined)
         }
       }
     }
     if (this._onAreaChange_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onAreaChange_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onAreaChangeAttribute((this._onAreaChange_value as (((oldValue: Area,newValue: Area) => void) | undefined)))
           this._onAreaChange_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onAreaChange_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onAreaChange_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onAreaChangeAttribute(undefined)
         }
       }
     }
     if (this._onSizeChange_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onSizeChange_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onSizeChangeAttribute((this._onSizeChange_value as (SizeChangeCallback | undefined)))
           this._onSizeChange_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onSizeChange_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onSizeChange_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onSizeChangeAttribute(undefined)
         }
       }
     }
     if (this._onGestureJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onGestureJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onGestureJudgeBeginAttribute((this._onGestureJudgeBegin_value as (((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined)))
           this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onGestureJudgeBeginAttribute(undefined)
         }
       }
     }
     if (this._shouldBuiltInRecognizerParallelWith_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._shouldBuiltInRecognizerParallelWith_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.shouldBuiltInRecognizerParallelWithAttribute((this._shouldBuiltInRecognizerParallelWith_value as (ShouldBuiltInRecognizerParallelWithCallback | undefined)))
           this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.INITIAL
           peerNode.shouldBuiltInRecognizerParallelWithAttribute(undefined)
         }
       }
     }
     if (this._onGestureRecognizerJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onGestureRecognizerJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           if (runtimeType(this._onGestureRecognizerJudgeBegin_exposeInnerGesture) != (RuntimeType.BOOLEAN)) {
            peerNode.onGestureRecognizerJudgeBegin0Attribute((this._onGestureRecognizerJudgeBegin_callback as (GestureRecognizerJudgeBeginCallback | undefined)))
           } else {
            peerNode.onGestureRecognizerJudgeBegin1Attribute((this._onGestureRecognizerJudgeBegin_callback as (GestureRecognizerJudgeBeginCallback | undefined)), (this._onGestureRecognizerJudgeBegin_exposeInnerGesture as boolean))
           }
           this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onGestureRecognizerJudgeBegin0Attribute(undefined)
         }
       }
     }
     if (this._responseRegion_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._responseRegion_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.responseRegionAttribute((this._responseRegion_value as (Array<Rectangle> | Rectangle | undefined)))
           this._responseRegion_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._responseRegion_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._responseRegion_flag = AttributeUpdaterFlag.INITIAL
           peerNode.responseRegionAttribute(undefined)
         }
       }
     }
     if (this._hitTestBehavior_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._hitTestBehavior_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.hitTestBehaviorAttribute((this._hitTestBehavior_value as (HitTestMode | undefined)))
           this._hitTestBehavior_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._hitTestBehavior_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._hitTestBehavior_flag = AttributeUpdaterFlag.INITIAL
           peerNode.hitTestBehaviorAttribute(undefined)
         }
       }
     }
     if (this._monopolizeEvents_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._monopolizeEvents_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.monopolizeEventsAttribute((this._monopolizeEvents_value as (boolean | undefined)))
           this._monopolizeEvents_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._monopolizeEvents_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._monopolizeEvents_flag = AttributeUpdaterFlag.INITIAL
           peerNode.monopolizeEventsAttribute(undefined)
         }
       }
     }
     if (this._restoreId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._restoreId_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.restoreIdAttribute(this._restoreId_value as (number | undefined))
           this._restoreId_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._restoreId_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._restoreId_flag = AttributeUpdaterFlag.INITIAL
           peerNode.restoreIdAttribute(undefined)
         }
       }
     }
     if (this._hoverEffect_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._hoverEffect_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.hoverEffectAttribute(this._hoverEffect_value as (HoverEffect | undefined))
           this._hoverEffect_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._hoverEffect_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._hoverEffect_flag = AttributeUpdaterFlag.INITIAL
           peerNode.hoverEffectAttribute(undefined)
         }
       }
     }
     if (this._enabled_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._enabled_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.enabledAttribute(this._enabled_value as (boolean | undefined))
           this._enabled_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._enabled_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._enabled_flag = AttributeUpdaterFlag.INITIAL
           peerNode.enabledAttribute(undefined)
         }
       }
     }
     if (this._visibility_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._visibility_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.visibilityAttribute(this._visibility_value as (Visibility | undefined))
           this._visibility_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._visibility_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._visibility_flag = AttributeUpdaterFlag.INITIAL
           peerNode.visibilityAttribute(undefined)
         }
       }
     }
     if (this._key_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._key_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.keyAttribute(this._key_value as (string | undefined))
           this._key_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._key_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._key_flag = AttributeUpdaterFlag.INITIAL
           peerNode.keyAttribute(undefined)
         }
       }
     }
     if (this._customProperty_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (this._customProperty_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           const arkCommonMethodComponent: ArkCommonMethodComponent = new ArkCommonMethodComponent();
           arkCommonMethodComponent.setPeer(peerNode);
           if (this._customPropertyMap === undefined) {
             break;
           }
           this._customPropertyMap!.forEach((value, key) => {
             hookCustomPropertyImpl(arkCommonMethodComponent, key as (string), value as (CustomProperty));
           });
           this._customProperty_flag = AttributeUpdaterFlag.RESET;
           break;
         }
         case AttributeUpdaterFlag.SKIP: {
           this._customProperty_flag = AttributeUpdaterFlag.RESET;
           break;
         }
         default: {
           this._customProperty_flag = AttributeUpdaterFlag.INITIAL;
         }
       }
     }
   }
   mergeModifier(value: CommonMethodModifier): void {
     if (value._width_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._width_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.width(value._width0_value)
           break
         }
         default: {
           this.width(undefined)
         }
       }
     }
  
     if (value._backgroundColor_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundColor_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundColor(value._backgroundColor0_value)
           break
         }
         default: {
           this.backgroundColor(undefined)
         }
       }
     }
  
     if (value._size_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._size_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.size(value._size0_value)
           break
         }
         default: {
           this.size(undefined)
         }
       }
     }
  
     if (value._onClick_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onClick_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onClick(value._onClick0_value)
           break
         }
         default: {
           this.onClick(undefined)
         }
       }
     }
     if (value._zIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._zIndex_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.zIndex(value._zIndex0_value)
           break
         }
         default: {
           this.zIndex(undefined)
         }
       }
     }
if (value._backgroundImage_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImage_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImage(value._backgroundImage_src, this._backgroundImage_repeat)
           break
         }
         default: {
           this.backgroundImage(undefined)
         }
       }
     }
     if (value._backgroundImagePosition_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImagePosition_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImagePosition(value._backgroundImagePosition_value)
           break
         }
         default: {
           this.backgroundImagePosition(undefined)
         }
       }
     }
     if (value._backgroundImageSize_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImageSize_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImageSize(value._backgroundImageSize_value)
           break
         }
         default: {
           this.backgroundImageSize(undefined)
         }
       }
     }
     if (value._backgroundImagePosition_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImagePosition_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImagePosition(value._backgroundImagePosition_value)
           break
         }
         default: {
           this.backgroundImagePosition(undefined)
         }
       }
     }
     if (value._backgroundImageResizable_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImageResizable_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImageResizable(value._backgroundImageResizable_value)
           break
         }
         default: {
           this.backgroundImageResizable(undefined)
         }
       }
     }
     if (value._onHover_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onHover_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onHover(value._onHover_value)
           break
         }
         default: {
           this.onHover(undefined)
         }
       }
     }
     if (value._onHoverMove_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onHoverMove_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onHoverMove(value._onHoverMove_value)
           break
         }
         default: {
           this.onHoverMove(undefined)
         }
       }
     }
     if (value._onMouse_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onMouse_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onMouse(value._onMouse_value)
           break
         }
         default: {
           this.onMouse(undefined)
         }
       }
     }
     if (value._onTouch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onTouch_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onTouch(value._onTouch_value)
           break
         }
         default: {
           this.onTouch(undefined)
         }
       }
     }
     if (value._onFocusAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onFocusAxisEvent_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onFocusAxisEvent(value._onFocusAxisEvent_value)
           break
         }
         default: {
           this.onFocusAxisEvent(undefined)
         }
       }
     }
     if (value._onAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAxisEvent_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAxisEvent(value._onAxisEvent_value)
           break
         }
         default: {
           this.onAxisEvent(undefined)
         }
       }
     }
     if (value._onKeyEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onKeyEvent_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onKeyEvent(value._onKeyEvent1_value)
           break
         }
         default: {
           this.onKeyEvent(undefined)
         }
       }
     }
     if (value._onKeyPreIme_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onKeyPreIme_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onKeyPreIme(value._onKeyPreIme_value)
           break
         }
         default: {
           this.onKeyPreIme(undefined)
         }
       }
     }
     if (value._onKeyEventDispatch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onKeyEventDispatch_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onKeyEventDispatch(value._onKeyEventDispatch_value)
           break
         }
         default: {
           this.onKeyEventDispatch(undefined)
         }
       }
     }
     if (value._keyboardShortcut_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._keyboardShortcut_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.keyboardShortcut((this._keyboardShortcut_value as (string | FunctionKey | undefined)), (this._keyboardShortcut_keys as (Array<ModifierKey> | undefined)), (this._keyboardShortcut_action as (() => void)))
           break
         }
         default: {
           this.keyboardShortcut(undefined, undefined)
         }
       }
     }
     if (value._focusable_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusable_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusable(value._focusable_value)
           break
         }
         default: {
           this.focusable(undefined)
         }
       }
     }
     if (value._nextFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._nextFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.nextFocus(value._nextFocus_value)
           break
         }
         default: {
           this.nextFocus(undefined)
         }
       }
     }
     if (value._tabIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._tabIndex_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.tabIndex(value._tabIndex_value)
           break
         }
         default: {
           this.tabIndex(undefined)
         }
       }
     }
     if (value._defaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._defaultFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.defaultFocus(value._defaultFocus_value)
           break
         }
         default: {
           this.defaultFocus(undefined)
         }
       }
     }
     if (value._groupDefaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._groupDefaultFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.groupDefaultFocus(value._groupDefaultFocus_value)
           break
         }
         default: {
           this.groupDefaultFocus(undefined)
         }
       }
     }
     if (value._focusOnTouch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusOnTouch_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusOnTouch(value._focusOnTouch_value)
           break
         }
         default: {
           this.focusOnTouch(undefined)
         }
       }
     }
     if (value._focusBox_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusBox_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusBox(value._focusBox_value)
           break
         }
         default: {
           this.focusBox(undefined)
         }
       }
     }
     if (value._focusScopeId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusScopeId_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusScopeId(value._focusScopeId_id, value._focusScopeId_isGroup, value._focusScopeId_arrowStepOut)
           break
         }
         default: {
           this.focusScopeId(undefined)
         }
       }
     }
     if (value._focusScopePriority_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusScopePriority_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusScopePriority(value._focusScopePriority_scopeId, value._focusScopePriority_priority)
           break
         }
         default: {
           this.focusScopePriority(undefined)
         }
       }
     }
     if (value._tabStop_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._tabStop_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.tabStop(value._tabStop_value)
           break
         }
         default: {
           this.tabStop(undefined)
         }
       }
     }
     if (value._onFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onFocus(value._onFocus_value)
           break
         }
         default: {
           this.onFocus(undefined)
         }
       }
     }
     if (value._onBlur_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onBlur_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onBlur(value._onBlur_value)
           break
         }
         default: {
           this.onBlur(undefined)
         }
       }
     }
     if (value._onAppear_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAppear_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAppear(value._onAppear_value)
           break
         }
         default: {
           this.onAppear(undefined)
         }
       }
     }
     if (value._onDisAppear_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onDisAppear_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onDisAppear(value._onDisAppear_value)
           break
         }
         default: {
           this.onDisAppear(undefined)
         }
       }
     }
     if (value._onAttach_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAttach_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAttach(value._onAttach_value)
           break
         }
         default: {
           this.onAttach(undefined)
         }
       }
     }
     if (value._onDetach_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onDetach_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onDetach(value._onDetach_value)
           break
         }
         default: {
           this.onDetach(undefined)
         }
       }
     }
     if (value._onAreaChange_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAreaChange_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAreaChange(value._onAreaChange_value)
           break
         }
         default: {
           this.onAreaChange(undefined)
         }
       }
     }
     if (value._onSizeChange_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onSizeChange_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onSizeChange(value._onSizeChange_value)
           break
         }
         default: {
           this.onSizeChange(undefined)
         }
       }
     }
     if (value._onGestureJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onGestureJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onGestureJudgeBegin(value._onGestureJudgeBegin_value)
           break
         }
         default: {
           this.onGestureJudgeBegin(undefined)
         }
       }
     }
     if (value._shouldBuiltInRecognizerParallelWith_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._shouldBuiltInRecognizerParallelWith_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.shouldBuiltInRecognizerParallelWith(value._shouldBuiltInRecognizerParallelWith_value)
           break
         }
         default: {
           this.shouldBuiltInRecognizerParallelWith(undefined)
         }
       }
     }
     if (value._onGestureRecognizerJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onGestureRecognizerJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onGestureRecognizerJudgeBegin(value._onGestureRecognizerJudgeBegin_callback, value._onGestureRecognizerJudgeBegin_exposeInnerGesture)
           break
         }
         default: {
           this.onGestureRecognizerJudgeBegin(undefined)
         }
       }
     }
     if (value._responseRegion_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._responseRegion_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.responseRegion(value._responseRegion_value)
           break
         }
         default: {
           this.responseRegion(undefined)
         }
       }
     }
     if (value._hitTestBehavior_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._hitTestBehavior_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.hitTestBehavior(value._hitTestBehavior_value)
           break
         }
         default: {
           this.hitTestBehavior(undefined)
         }
       }
     }
     if (value._monopolizeEvents_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._monopolizeEvents_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.monopolizeEvents(value._monopolizeEvents_value)
           break
         }
         default: {
           this.monopolizeEvents(undefined)
         }
       }
     }
     if (value._restoreId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._restoreId_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.restoreId(value._restoreId_value)
           break
         }
         default: {
           this.restoreId(undefined)
         }
       }
     }
     if (value._hoverEffect_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._hoverEffect_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.hoverEffect(value._hoverEffect_value)
           break
         }
         default: {
           this.hoverEffect(undefined)
         }
       }
     }
     if (value._enabled_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._enabled_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.enabled(value._enabled_value)
           break
         }
         default: {
           this.enabled(undefined)
         }
       }
     }
     if (value._visibility_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._visibility_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.visibility(value._visibility_value)
           break
         }
         default: {
           this.visibility(undefined)
         }
       }
     }
     if (value._key_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._key_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.key(value._key_value)
           break
         }
         default: {
           this.key(undefined)
         }
       }
     }
     if (value._customProperty_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._customProperty_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           if (this._customPropertyMap === undefined) {
             break;
           }
           this._customPropertyMap!.forEach((value, key) => {
             this.customProperty(key as (string), value);
           });
           break;
         }
         default: {
         }
       }
     }
   }
}