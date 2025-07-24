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

import { TranslateOptions, ArkCommonMethodPeer, CommonMethod, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, DividerStyle } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Length, ResourceColor, Dimension } from "./units"
import { EdgeEffect, PageFlipMode, Color } from "./enums"
import { Callback_Number_Void } from "./alphabetIndexer"
import { Resource } from "global/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { TabsOpsHandWritten } from "./../handwritten"

export class TabsControllerInternal {
    public static fromPtr(ptr: KPointer): TabsController {
        const obj : TabsController = new TabsController()
        obj.peer = new Finalizable(ptr, TabsController.getFinalizer())
        return obj
    }
}
export class TabsController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_tabscontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabsController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TabsController.ctor_tabscontroller()
        this.peer = new Finalizable(ctorPtr, TabsController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabsController_getFinalizer()
    }
    public changeIndex(value: number): void {
        const value_casted = value as (number)
        this.changeIndex_serialize(value_casted)
        return
    }
    public preloadItems(indices: Array<number> | undefined): Promise<void> {
        const indices_casted = indices as (Array<number> | undefined)
        return this.preloadItems_serialize(indices_casted)
    }
    public setTabBarTranslate(translate: TranslateOptions): void {
        const translate_casted = translate as (TranslateOptions)
        this.setTabBarTranslate_serialize(translate_casted)
        return
    }
    public setTabBarOpacity(opacity: number): void {
        const opacity_casted = opacity as (number)
        this.setTabBarOpacity_serialize(opacity_casted)
        return
    }
    private changeIndex_serialize(value: number): void {
        ArkUIGeneratedNativeModule._TabsController_changeIndex(this.peer!.ptr, value)
    }
    private preloadItems_serialize(indices: Array<number> | undefined): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let indices_type : int32 = RuntimeType.UNDEFINED
        indices_type = runtimeType(indices)
        thisSerializer.writeInt8(indices_type as int32)
        if ((RuntimeType.UNDEFINED) != (indices_type)) {
            const indices_value  = indices!
            thisSerializer.writeInt32(indices_value.length as int32)
            for (let i = 0; i < indices_value.length; i++) {
                const indices_value_element : number = indices_value[i]
                thisSerializer.writeNumber(indices_value_element)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._TabsController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private setTabBarTranslate_serialize(translate: TranslateOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(translate)
        ArkUIGeneratedNativeModule._TabsController_setTabBarTranslate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setTabBarOpacity_serialize(opacity: number): void {
        ArkUIGeneratedNativeModule._TabsController_setTabBarOpacity(this.peer!.ptr, opacity)
    }
}
export interface TabContentTransitionProxy {
    from: number
    to: number
    finishTransition(): void
}
export class TabContentTransitionProxyInternal implements MaterializedBase,TabContentTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get from(): number {
        return this.getFrom()
    }
    set from(from: number) {
        this.setFrom(from)
    }
    get to(): number {
        return this.getTo()
    }
    set to(to: number) {
        this.setTo(to)
    }
    static ctor_tabcontenttransitionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TabContentTransitionProxyInternal.ctor_tabcontenttransitionproxy()
        this.peer = new Finalizable(ctorPtr, TabContentTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    private getFrom(): number {
        return this.getFrom_serialize()
    }
    private setFrom(from: number): void {
        const from_casted = from as (number)
        this.setFrom_serialize(from_casted)
        return
    }
    private getTo(): number {
        return this.getTo_serialize()
    }
    private setTo(to: number): void {
        const to_casted = to as (number)
        this.setTo_serialize(to_casted)
        return
    }
    private finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getFrom_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFrom(this.peer!.ptr)
        return retval
    }
    private setFrom_serialize(from: number): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setFrom(this.peer!.ptr, from)
    }
    private getTo_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getTo(this.peer!.ptr)
        return retval
    }
    private setTo_serialize(to: number): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setTo(this.peer!.ptr, to)
    }
    public static fromPtr(ptr: KPointer): TabContentTransitionProxyInternal {
        const obj : TabContentTransitionProxyInternal = new TabContentTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, TabContentTransitionProxyInternal.getFinalizer())
        return obj
    }
}
export class ArkTabsPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkTabsPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Tabs_construct(peerId, flags)
        const _peer  = new ArkTabsPeer(_peerPtr, peerId, "Tabs", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabsOptionsAttribute(options?: TabsOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeTabsOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TabsInterface_setTabsOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_vertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barPositionAttribute(value: BarPosition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarPosition)
            thisSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_scrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barMode0Attribute(value: BarMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarMode)
            thisSerializer.writeInt32(TypeChecker.BarMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barMode0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barMode1Attribute(value: BarMode | undefined, options?: ScrollableBarModeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarMode)
            thisSerializer.writeInt32(TypeChecker.BarMode_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollableBarModeOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barMode1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barWidthAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barHeightAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    animationDurationAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_animationDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    animationModeAttribute(value: AnimationMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AnimationMode)
            thisSerializer.writeInt32(TypeChecker.AnimationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_animationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectedAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTabBarClickAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onTabBarClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUnselectedAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationStartAttribute(value: OnTabsAnimationStartCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnTabsAnimationEndCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnTabsGestureSwipeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fadingEdgeAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_fadingEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDividerStyle(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barOverlapAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barOverlap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barGridAlignAttribute(value: BarGridColumnOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBarGridColumnOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barGridAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customContentTransitionAttribute(value: TabsCustomContentTransitionCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_customContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundBlurStyle0Attribute(value: BlurStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundBlurStyle1Attribute(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type as int32)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(style_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeBackgroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundEffectAttribute(value: BackgroundEffectOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBackgroundEffectOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_pageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentWillChangeAttribute(value: OnTabsContentWillChangeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onContentWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barModeScrollableAttribute(options: ScrollableBarModeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollableBarModeOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barModeScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedMaxCountAttribute(count: number | undefined, mode: TabsCacheMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type as int32)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let mode_type : int32 = RuntimeType.UNDEFINED
        mode_type = runtimeType(mode)
        thisSerializer.writeInt8(mode_type as int32)
        if ((RuntimeType.UNDEFINED) != (mode_type)) {
            const mode_value  = (mode as TabsCacheMode)
            thisSerializer.writeInt32(TypeChecker.TabsCacheMode_ToNumeric(mode_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_cachedMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_indexAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._TabsAttribute__onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface CommonModifier {
    _CommonModifierStub: string;
}
export enum BarMode {
    SCROLLABLE = 0,
    Scrollable = 0,
    FIXED = 1,
    Fixed = 1
}
export enum AnimationMode {
    CONTENT_FIRST = 0,
    ACTION_FIRST = 1,
    NO_ANIMATION = 2,
    CONTENT_FIRST_WITH_JUMP = 3,
    ACTION_FIRST_WITH_JUMP = 4
}
export enum BarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum LayoutStyle {
    ALWAYS_CENTER = 0,
    ALWAYS_AVERAGE_SPLIT = 1,
    SPACE_BETWEEN_OR_CENTER = 2
}
export enum TabsCacheMode {
    CACHE_BOTH_SIDE = 0,
    CACHE_LATEST_SWITCHED = 1
}
export interface TabsOptions {
    barPosition?: BarPosition;
    index?: number;
    controller?: TabsController;
    barModifier?: CommonModifier;
}
export type TabsInterface = (options?: TabsOptions) => TabsAttribute;
export interface TabsAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
export interface BarGridColumnOptions {
    sm?: number;
    md?: number;
    lg?: number;
    margin?: Dimension;
    gutter?: Dimension;
}
export interface ScrollableBarModeOptions {
    margin?: Dimension;
    nonScrollableLayoutStyle?: LayoutStyle;
}
export type OnTabsAnimationStartCallback = (index: number, targetIndex: number, extraInfo: TabsAnimationEvent) => void;
export type OnTabsAnimationEndCallback = (index: number, extraInfo: TabsAnimationEvent) => void;
export type OnTabsGestureSwipeCallback = (index: number, extraInfo: TabsAnimationEvent) => void;
export type TabsCustomContentTransitionCallback = (from: number, to: number) => TabContentAnimatedTransition | undefined;
export type OnTabsContentWillChangeCallback = (currentIndex: number, comingIndex: number) => boolean;
export interface TabsAttribute extends CommonMethod {
    vertical(value: boolean | undefined): this
    barPosition(value: BarPosition | undefined): this
    scrollable(value: boolean | undefined): this
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this
    barWidth(value: Length | undefined): this
    barHeight(value: Length | undefined): this
    animationDuration(value: number | undefined): this
    animationMode(value: AnimationMode | undefined): this
    edgeEffect(value: EdgeEffect | undefined): this
    onChange(value: ((index: number) => void) | undefined): this
    onSelected(value: ((index: number) => void) | undefined): this
    onTabBarClick(value: ((index: number) => void) | undefined): this
    onUnselected(value: ((index: number) => void) | undefined): this
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this
    fadingEdge(value: boolean | undefined): this
    divider(value: DividerStyle | null | undefined): this
    barOverlap(value: boolean | undefined): this
    barBackgroundColor(value: ResourceColor | undefined): this
    barGridAlign(value: BarGridColumnOptions | undefined): this
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this
    barBackgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): this
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this
    pageFlipMode(value: PageFlipMode | undefined): this
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this
    barModeScrollable(options: ScrollableBarModeOptions | undefined): this
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this
    _onChangeEvent_index(callback: ((index: number) => void)): void
}
export class ArkTabsStyle extends ArkCommonMethodStyle implements TabsAttribute {
    vertical_value?: boolean | undefined
    barPosition_value?: BarPosition | undefined
    scrollable_value?: boolean | undefined
    barMode_value?: BarMode | undefined
    barWidth_value?: Length | undefined
    barHeight_value?: Length | undefined
    animationDuration_value?: number | undefined
    animationMode_value?: AnimationMode | undefined
    edgeEffect_value?: EdgeEffect | undefined
    onChange_value?: ((index: number) => void) | undefined
    onSelected_value?: ((index: number) => void) | undefined
    onTabBarClick_value?: ((index: number) => void) | undefined
    onUnselected_value?: ((index: number) => void) | undefined
    onAnimationStart_value?: OnTabsAnimationStartCallback | undefined
    onAnimationEnd_value?: OnTabsAnimationEndCallback | undefined
    onGestureSwipe_value?: OnTabsGestureSwipeCallback | undefined
    fadingEdge_value?: boolean | undefined
    divider_value?: DividerStyle | undefined
    barOverlap_value?: boolean | undefined
    barBackgroundColor_value?: ResourceColor | undefined
    barGridAlign_value?: BarGridColumnOptions | undefined
    customContentTransition_value?: TabsCustomContentTransitionCallback | undefined
    barBackgroundBlurStyle_value?: BlurStyle | undefined
    barBackgroundEffect_value?: BackgroundEffectOptions | undefined
    pageFlipMode_value?: PageFlipMode | undefined
    onContentWillChange_value?: OnTabsContentWillChangeCallback | undefined
    public vertical(value: boolean | undefined): this {
        return this
    }
    public barPosition(value: BarPosition | undefined): this {
        return this
    }
    public scrollable(value: boolean | undefined): this {
        return this
    }
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        return this
    }
    public barWidth(value: Length | undefined): this {
        return this
    }
    public barHeight(value: Length | undefined): this {
        return this
    }
    public animationDuration(value: number | undefined): this {
        return this
    }
    public animationMode(value: AnimationMode | undefined): this {
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined): this {
        return this
    }
    public onChange(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onSelected(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onTabBarClick(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onUnselected(value: ((index: number) => void) | undefined): this {
        return this
    }
    public onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        return this
    }
    public onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        return this
    }
    public onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        return this
    }
    public fadingEdge(value: boolean | undefined): this {
        return this
    }
    public divider(value: DividerStyle | null | undefined): this {
        return this
    }
    public barOverlap(value: boolean | undefined): this {
        return this
    }
    public barBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public barGridAlign(value: BarGridColumnOptions | undefined): this {
        return this
    }
    public customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        return this
    }
    public barBackgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): this {
        return this
    }
    public barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        return this
    }
    public onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        return this
    }
    public barModeScrollable(options: ScrollableBarModeOptions | undefined): this {
        return this
    }
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        return this
    }
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        throw new Error("Unimplmented")
        }
}
export type Callback_TabContentTransitionProxy_Void = (parameter: TabContentTransitionProxy) => void;
export interface TabContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: TabContentTransitionProxy) => void);
}
export class ArkTabsComponent extends ArkCommonMethodComponent implements TabsAttribute {
    getPeer(): ArkTabsPeer {
        return (this.peer as ArkTabsPeer)
    }
    public setTabsOptions(options?: TabsOptions): this {
        if (this.checkPriority("setTabsOptions")) {
            const options_casted = options as (TabsOptions | undefined)
            this.getPeer()?.setTabsOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public vertical(value: boolean | undefined): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.verticalAttribute(value_casted)
            return this
        }
        return this
    }
    public barPosition(value: BarPosition | undefined): this {
        if (this.checkPriority("barPosition")) {
            const value_casted = value as (BarPosition | undefined)
            this.getPeer()?.barPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollable(value: boolean | undefined): this {
        if (this.checkPriority("scrollable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.scrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        if (this.checkPriority("barMode")) {
            TabsOpsHandWritten.hookTabsAttributeBarModeImpl(this.getPeer().peer.ptr,
                value, options);
        }
        return this
    }
    public barWidth(value: Length | undefined): this {
        if (this.checkPriority("barWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.barWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public barHeight(value: Length | undefined): this {
        if (this.checkPriority("barHeight")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.barHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public animationDuration(value: number | undefined): this {
        if (this.checkPriority("animationDuration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.animationDurationAttribute(value_casted)
            return this
        }
        return this
    }
    public animationMode(value: AnimationMode | undefined): this {
        if (this.checkPriority("animationMode")) {
            const value_casted = value as (AnimationMode | undefined)
            this.getPeer()?.animationModeAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            this.getPeer()?.edgeEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelected(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onTabBarClick(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onTabBarClick")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onTabBarClickAttribute(value_casted)
            return this
        }
        return this
    }
    public onUnselected(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onUnselected")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onUnselectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (OnTabsAnimationStartCallback | undefined)
            this.getPeer()?.onAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (OnTabsAnimationEndCallback | undefined)
            this.getPeer()?.onAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (OnTabsGestureSwipeCallback | undefined)
            this.getPeer()?.onGestureSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public fadingEdge(value: boolean | undefined): this {
        if (this.checkPriority("fadingEdge")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.fadingEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerStyle | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    public barOverlap(value: boolean | undefined): this {
        if (this.checkPriority("barOverlap")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.barOverlapAttribute(value_casted)
            return this
        }
        return this
    }
    public barBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("barBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.barBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public barGridAlign(value: BarGridColumnOptions | undefined): this {
        if (this.checkPriority("barGridAlign")) {
            const value_casted = value as (BarGridColumnOptions | undefined)
            this.getPeer()?.barGridAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (TabsCustomContentTransitionCallback | undefined)
            this.getPeer()?.customContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public barBackgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): this {
        if (this.checkPriority("barBackgroundBlurStyle")) {
            TabsOpsHandWritten.hookTabsAttributeBarBackgroundBlurStyleImpl(this.getPeer().peer.ptr,
            style, options);
        }
        return this
    }
    public barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        if (this.checkPriority("barBackgroundEffect")) {
            const value_casted = value as (BackgroundEffectOptions | undefined)
            this.getPeer()?.barBackgroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        if (this.checkPriority("pageFlipMode")) {
            const value_casted = value as (PageFlipMode | undefined)
            this.getPeer()?.pageFlipModeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        if (this.checkPriority("onContentWillChange")) {
            const value_casted = value as (OnTabsContentWillChangeCallback | undefined)
            this.getPeer()?.onContentWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public barModeScrollable(options: ScrollableBarModeOptions | undefined): this {
        if (this.checkPriority("barModeScrollable")) {
            const options_casted = options as (ScrollableBarModeOptions | undefined)
            this.getPeer()?.barModeScrollableAttribute(options_casted)
            return this
        }
        return this
    }
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        if (this.checkPriority("cachedMaxCount")) {
            const count_casted = count as (number | undefined)
            const mode_casted = mode as (TabsCacheMode | undefined)
            this.getPeer()?.cachedMaxCountAttribute(count_casted, mode_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_index(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_indexAttribute(callback_casted)
            return
        }
        return
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Tabs(
    /** @memo */
    style: ((attributes: TabsAttribute) => void) | undefined,
    options?: TabsOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkTabsComponent()
    })
    NodeAttach<ArkTabsPeer>((): ArkTabsPeer => ArkTabsPeer.create(receiver), (_: ArkTabsPeer) => {
        receiver.setTabsOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
