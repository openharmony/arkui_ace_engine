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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { TranslateOptions_serializer, TranslateOptions, DividerStyle_serializer, BackgroundEffectOptions_serializer, BackgroundBlurStyleOptions_serializer, ArkCommonMethodPeer, CommonMethod, DividerStyle, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions, BlurStyleOptions, BlurStyleActivePolicy, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Length, ResourceColor, Dimension } from "./units"
import { EdgeEffect, Color, PageFlipMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TabContentTransitionProxyInternal.getFinalizer())
    }
    constructor() {
        this(TabContentTransitionProxyInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TabContentTransitionProxyInternal {
        return new TabContentTransitionProxyInternal(ptr)
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
}
export class TabsControllerInternal {
    public static fromPtr(ptr: KPointer): TabsController {
        return new TabsController(ptr)
    }
}
export class TabsController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TabsController.getFinalizer())
    }
    constructor() {
        this(TabsController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabsController_construct()
        return retval
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let indices_type : int32 = RuntimeType.UNDEFINED
        indices_type = runtimeType(indices)
        thisSerializer.writeInt8((indices_type).toChar())
        if ((indices_type) != (RuntimeType.UNDEFINED)) {
            const indices_value  = indices!
            thisSerializer.writeInt32((indices_value.length).toInt())
            for (let indices_value_counter_i = 0; indices_value_counter_i < indices_value.length; indices_value_counter_i++) {
                const indices_value_element : number = indices_value[indices_value_counter_i]
                thisSerializer.writeNumber(indices_value_element)
            }
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._TabsController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private setTabBarTranslate_serialize(translate: TranslateOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TranslateOptions_serializer.write(thisSerializer, translate)
        ArkUIGeneratedNativeModule._TabsController_setTabBarTranslate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setTabBarOpacity_serialize(opacity: number): void {
        ArkUIGeneratedNativeModule._TabsController_setTabBarOpacity(this.peer!.ptr, opacity)
    }
}
export class ArkTabsPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTabsPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Tabs_construct(peerId, flags)
        const _peer  = new ArkTabsPeer(_peerPtr, peerId, "Tabs", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabsOptionsAttribute(options?: TabsOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            TabsOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TabsInterface_setTabsOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setVertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarPositionAttribute(value: BarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BarPosition)
            thisSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnimationDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setAnimationDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnimationModeAttribute(value: AnimationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as AnimationMode)
            thisSerializer.writeInt32(TypeChecker.AnimationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setAnimationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeEffectAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTabBarClickAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnTabBarClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUnselectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationStartAttribute(value: OnTabsAnimationStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationEndAttribute(value: OnTabsAnimationEndCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGestureSwipeAttribute(value: OnTabsGestureSwipeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFadingEdgeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setFadingEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DividerStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarOverlapAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarOverlap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarGridAlignAttribute(value: BarGridColumnOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            BarGridColumnOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarGridAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomContentTransitionAttribute(value: TabsCustomContentTransitionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setCustomContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundBlurStyle0Attribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setPageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundEffectAttribute(value: BackgroundEffectOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            BackgroundEffectOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentWillChangeAttribute(value: OnTabsContentWillChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnContentWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarModeAttribute(value: BarMode | undefined, options?: ScrollableBarModeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BarMode)
            thisSerializer.writeInt32(TypeChecker.BarMode_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ScrollableBarModeOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundBlurStyle1Attribute(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8((style_type).toChar())
        if ((style_type) != (RuntimeType.UNDEFINED)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(style_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            BackgroundBlurStyleOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedMaxCountAttribute(count: number | undefined, mode: TabsCacheMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8((count_type).toChar())
        if ((count_type) != (RuntimeType.UNDEFINED)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let mode_type : int32 = RuntimeType.UNDEFINED
        mode_type = runtimeType(mode)
        thisSerializer.writeInt8((mode_type).toChar())
        if ((mode_type) != (RuntimeType.UNDEFINED)) {
            const mode_value  = (mode as TabsCacheMode)
            thisSerializer.writeInt32(TypeChecker.TabsCacheMode_ToNumeric(mode_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setCachedMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_indexAttribute(callback_: ((value0: number) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._TabsAttribute_set_onChangeEvent_index(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
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
}
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
    vertical(value: boolean | undefined): this {
        throw new Error("Unimplemented method vertical")
    }
    barPosition(value: BarPosition | undefined): this {
        throw new Error("Unimplemented method barPosition")
    }
    scrollable(value: boolean | undefined): this {
        throw new Error("Unimplemented method scrollable")
    }
    barWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method barWidth")
    }
    barHeight(value: Length | undefined): this {
        throw new Error("Unimplemented method barHeight")
    }
    animationDuration(value: number | undefined): this {
        throw new Error("Unimplemented method animationDuration")
    }
    animationMode(value: AnimationMode | undefined): this {
        throw new Error("Unimplemented method animationMode")
    }
    edgeEffect(value: EdgeEffect | undefined): this {
        throw new Error("Unimplemented method edgeEffect")
    }
    onChange(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onSelected(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onSelected")
    }
    onTabBarClick(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onTabBarClick")
    }
    onUnselected(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onUnselected")
    }
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        throw new Error("Unimplemented method onAnimationStart")
    }
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        throw new Error("Unimplemented method onAnimationEnd")
    }
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        throw new Error("Unimplemented method onGestureSwipe")
    }
    fadingEdge(value: boolean | undefined): this {
        throw new Error("Unimplemented method fadingEdge")
    }
    divider(value: DividerStyle | undefined): this {
        throw new Error("Unimplemented method divider")
    }
    barOverlap(value: boolean | undefined): this {
        throw new Error("Unimplemented method barOverlap")
    }
    barBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method barBackgroundColor")
    }
    barGridAlign(value: BarGridColumnOptions | undefined): this {
        throw new Error("Unimplemented method barGridAlign")
    }
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        throw new Error("Unimplemented method customContentTransition")
    }
    barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        throw new Error("Unimplemented method barBackgroundBlurStyle")
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        throw new Error("Unimplemented method pageFlipMode")
    }
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        throw new Error("Unimplemented method barBackgroundEffect")
    }
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        throw new Error("Unimplemented method onContentWillChange")
    }
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        throw new Error("Unimplemented method barMode")
    }
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        throw new Error("Unimplemented method barBackgroundBlurStyle")
    }
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        throw new Error("Unimplemented method cachedMaxCount")
    }
    _onChangeEvent_index(callback_: ((value0: number) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_index")
    }
    attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTabsStyle extends ArkCommonMethodStyle implements TabsAttribute {
    vertical_value?: boolean | undefined
    barPosition_value?: BarPosition | undefined
    scrollable_value?: boolean | undefined
    barWidth_value?: Length | undefined
    barHeight_value?: Length | undefined
    animationDuration_value?: number | undefined
    animationMode_value?: AnimationMode | undefined
    edgeEffect_value?: EdgeEffect | undefined
    onChange_value?: ((value0: number) => void) | undefined
    onSelected_value?: ((value0: number) => void) | undefined
    onTabBarClick_value?: ((value0: number) => void) | undefined
    onUnselected_value?: ((value0: number) => void) | undefined
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
    pageFlipMode_value?: PageFlipMode | undefined
    barBackgroundEffect_value?: BackgroundEffectOptions | undefined
    onContentWillChange_value?: OnTabsContentWillChangeCallback | undefined
    attributeModifier_value?: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined
    public vertical(value: boolean | undefined): this {
        return this
    }
    public barPosition(value: BarPosition | undefined): this {
        return this
    }
    public scrollable(value: boolean | undefined): this {
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
    public onChange(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public onSelected(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public onTabBarClick(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
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
    public divider(value: DividerStyle | undefined): this {
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
    public barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        return this
    }
    public barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        return this
    }
    public onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        return this
    }
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        return this
    }
    public barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        return this
    }
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        return this
    }
    public _onChangeEvent_index(callback_: ((value0: number) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TabsAttribute): void {
        super.apply(target)
        if (this.vertical_value !== undefined)
            target.vertical(this.vertical_value!)
        if (this.barPosition_value !== undefined)
            target.barPosition(this.barPosition_value!)
        if (this.scrollable_value !== undefined)
            target.scrollable(this.scrollable_value!)
        if (this.barWidth_value !== undefined)
            target.barWidth(this.barWidth_value!)
        if (this.barHeight_value !== undefined)
            target.barHeight(this.barHeight_value!)
        if (this.animationDuration_value !== undefined)
            target.animationDuration(this.animationDuration_value!)
        if (this.animationMode_value !== undefined)
            target.animationMode(this.animationMode_value!)
        if (this.edgeEffect_value !== undefined)
            target.edgeEffect(this.edgeEffect_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.onSelected_value !== undefined)
            target.onSelected(this.onSelected_value!)
        if (this.onTabBarClick_value !== undefined)
            target.onTabBarClick(this.onTabBarClick_value!)
        if (this.onUnselected_value !== undefined)
            target.onUnselected(this.onUnselected_value!)
        if (this.onAnimationStart_value !== undefined)
            target.onAnimationStart(this.onAnimationStart_value!)
        if (this.onAnimationEnd_value !== undefined)
            target.onAnimationEnd(this.onAnimationEnd_value!)
        if (this.onGestureSwipe_value !== undefined)
            target.onGestureSwipe(this.onGestureSwipe_value!)
        if (this.fadingEdge_value !== undefined)
            target.fadingEdge(this.fadingEdge_value!)
        if (this.divider_value !== undefined)
            target.divider(this.divider_value!)
        if (this.barOverlap_value !== undefined)
            target.barOverlap(this.barOverlap_value!)
        if (this.barBackgroundColor_value !== undefined)
            target.barBackgroundColor(this.barBackgroundColor_value!)
        if (this.barGridAlign_value !== undefined)
            target.barGridAlign(this.barGridAlign_value!)
        if (this.customContentTransition_value !== undefined)
            target.customContentTransition(this.customContentTransition_value!)
        if (this.barBackgroundBlurStyle_value !== undefined)
            target.barBackgroundBlurStyle(this.barBackgroundBlurStyle_value!)
        if (this.pageFlipMode_value !== undefined)
            target.pageFlipMode(this.pageFlipMode_value!)
        if (this.barBackgroundEffect_value !== undefined)
            target.barBackgroundEffect(this.barBackgroundEffect_value!)
        if (this.onContentWillChange_value !== undefined)
            target.onContentWillChange(this.onContentWillChange_value!)
    }
}
export interface TabContentAnimatedTransition {
    timeout?: number;
    transition: ((value0: TabContentTransitionProxy) => void);
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
            this.getPeer()?.setVerticalAttribute(value_casted)
            return this
        }
        return this
    }
    public barPosition(value: BarPosition | undefined): this {
        if (this.checkPriority("barPosition")) {
            const value_casted = value as (BarPosition | undefined)
            this.getPeer()?.setBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollable(value: boolean | undefined): this {
        if (this.checkPriority("scrollable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public barWidth(value: Length | undefined): this {
        if (this.checkPriority("barWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public barHeight(value: Length | undefined): this {
        if (this.checkPriority("barHeight")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setBarHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public animationDuration(value: number | undefined): this {
        if (this.checkPriority("animationDuration")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setAnimationDurationAttribute(value_casted)
            return this
        }
        return this
    }
    public animationMode(value: AnimationMode | undefined): this {
        if (this.checkPriority("animationMode")) {
            const value_casted = value as (AnimationMode | undefined)
            this.getPeer()?.setAnimationModeAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect | undefined)
            this.getPeer()?.setEdgeEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelected(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onTabBarClick(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onTabBarClick")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnTabBarClickAttribute(value_casted)
            return this
        }
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onUnselected")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnUnselectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        if (this.checkPriority("onAnimationStart")) {
            const value_casted = value as (OnTabsAnimationStartCallback | undefined)
            this.getPeer()?.setOnAnimationStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        if (this.checkPriority("onAnimationEnd")) {
            const value_casted = value as (OnTabsAnimationEndCallback | undefined)
            this.getPeer()?.setOnAnimationEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        if (this.checkPriority("onGestureSwipe")) {
            const value_casted = value as (OnTabsGestureSwipeCallback | undefined)
            this.getPeer()?.setOnGestureSwipeAttribute(value_casted)
            return this
        }
        return this
    }
    public fadingEdge(value: boolean | undefined): this {
        if (this.checkPriority("fadingEdge")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setFadingEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    public divider(value: DividerStyle | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | undefined)
            this.getPeer()?.setDividerAttribute(value_casted)
            return this
        }
        return this
    }
    public barOverlap(value: boolean | undefined): this {
        if (this.checkPriority("barOverlap")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setBarOverlapAttribute(value_casted)
            return this
        }
        return this
    }
    public barBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("barBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBarBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public barGridAlign(value: BarGridColumnOptions | undefined): this {
        if (this.checkPriority("barGridAlign")) {
            const value_casted = value as (BarGridColumnOptions | undefined)
            this.getPeer()?.setBarGridAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        if (this.checkPriority("customContentTransition")) {
            const value_casted = value as (TabsCustomContentTransitionCallback | undefined)
            this.getPeer()?.setCustomContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("barBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.setBarBackgroundBlurStyle0Attribute(value_casted)
            return this
        }
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        if (this.checkPriority("pageFlipMode")) {
            const value_casted = value as (PageFlipMode | undefined)
            this.getPeer()?.setPageFlipModeAttribute(value_casted)
            return this
        }
        return this
    }
    public barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        if (this.checkPriority("barBackgroundEffect")) {
            const value_casted = value as (BackgroundEffectOptions | undefined)
            this.getPeer()?.setBarBackgroundEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        if (this.checkPriority("onContentWillChange")) {
            const value_casted = value as (OnTabsContentWillChangeCallback | undefined)
            this.getPeer()?.setOnContentWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        if (this.checkPriority("barMode")) {
            const value_casted = value as (BarMode | undefined)
            const options_casted = options as (ScrollableBarModeOptions | undefined)
            this.getPeer()?.setBarModeAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        if (this.checkPriority("barBackgroundBlurStyle")) {
            const style_casted = style as (BlurStyle | undefined)
            const options_casted = options as (BackgroundBlurStyleOptions | undefined)
            this.getPeer()?.setBarBackgroundBlurStyle1Attribute(style_casted, options_casted)
            return this
        }
        return this
    }
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        if (this.checkPriority("cachedMaxCount")) {
            const count_casted = count as (number | undefined)
            const mode_casted = mode as (TabsCacheMode | undefined)
            this.getPeer()?.setCachedMaxCountAttribute(count_casted, mode_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_index(callback_: ((value0: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_index")) {
            const callback__casted = callback_ as (((value0: number) => void))
            this.getPeer()?.set_onChangeEvent_indexAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTabsStyle(receiver: TabsAttribute, modifier: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTabsStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Tabs")
// export function Tabs(
//     options?: TabsOptions,
//     @memo
//     content_?: () => void,
// ): TabsAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Tabs(
    @memo
    style: ((attributes: TabsAttribute) => void) | undefined,
    options?: TabsOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTabsComponent>((): ArkTabsComponent => {
        return new ArkTabsComponent()
    })
    NodeAttach<ArkTabsPeer>((): ArkTabsPeer => ArkTabsPeer.create(receiver), (_: ArkTabsPeer): void => {
        receiver.setTabsOptions(options)
        style?.(receiver)
        withTabsStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTabsSet extends ArkCommonMethodSet implements TabsAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _vertical_flag?: boolean
    _vertical0_value?: boolean | undefined
    _barPosition_flag?: boolean
    _barPosition0_value?: BarPosition | undefined
    _scrollable_flag?: boolean
    _scrollable0_value?: boolean | undefined
    _barWidth_flag?: boolean
    _barWidth0_value?: Length | undefined
    _barHeight_flag?: boolean
    _barHeight0_value?: Length | undefined
    _animationDuration_flag?: boolean
    _animationDuration0_value?: number | undefined
    _animationMode_flag?: boolean
    _animationMode0_value?: AnimationMode | undefined
    _edgeEffect_flag?: boolean
    _edgeEffect0_value?: EdgeEffect | undefined
    _onChange_flag?: boolean
    _onChange0_value?: ((value0: number) => void) | undefined
    _onSelected_flag?: boolean
    _onSelected0_value?: ((value0: number) => void) | undefined
    _onTabBarClick_flag?: boolean
    _onTabBarClick0_value?: ((value0: number) => void) | undefined
    _onUnselected_flag?: boolean
    _onUnselected0_value?: ((value0: number) => void) | undefined
    _onAnimationStart_flag?: boolean
    _onAnimationStart0_value?: OnTabsAnimationStartCallback | undefined
    _onAnimationEnd_flag?: boolean
    _onAnimationEnd0_value?: OnTabsAnimationEndCallback | undefined
    _onGestureSwipe_flag?: boolean
    _onGestureSwipe0_value?: OnTabsGestureSwipeCallback | undefined
    _fadingEdge_flag?: boolean
    _fadingEdge0_value?: boolean | undefined
    _divider_flag?: boolean
    _divider0_value?: DividerStyle | undefined
    _barOverlap_flag?: boolean
    _barOverlap0_value?: boolean | undefined
    _barBackgroundColor_flag?: boolean
    _barBackgroundColor0_value?: ResourceColor | undefined
    _barGridAlign_flag?: boolean
    _barGridAlign0_value?: BarGridColumnOptions | undefined
    _customContentTransition_flag?: boolean
    _customContentTransition0_value?: TabsCustomContentTransitionCallback | undefined
    _barBackgroundBlurStyle_flag?: boolean
    _barBackgroundBlurStyle0_value?: BlurStyle | undefined
    _barBackgroundBlurStyle1_value?: BackgroundBlurStyleOptions | undefined
    _pageFlipMode_flag?: boolean
    _pageFlipMode0_value?: PageFlipMode | undefined
    _barBackgroundEffect_flag?: boolean
    _barBackgroundEffect0_value?: BackgroundEffectOptions | undefined
    _onContentWillChange_flag?: boolean
    _onContentWillChange0_value?: OnTabsContentWillChangeCallback | undefined
    _barMode_flag?: boolean
    _barMode0_value?: BarMode | undefined
    _barMode1_value?: ScrollableBarModeOptions | undefined
    _cachedMaxCount_flag?: boolean
    _cachedMaxCount0_value?: number | undefined
    _cachedMaxCount1_value?: TabsCacheMode | undefined
    __onChangeEvent_index_flag?: boolean
    __onChangeEvent_index0_value?: ((value0: number) => void)
    applyModifierPatch(component: TabsAttribute): void {
        if (this._vertical_flag)
            component.vertical((this._vertical0_value as boolean | undefined))
        if (this._barPosition_flag)
            component.barPosition((this._barPosition0_value as BarPosition | undefined))
        if (this._scrollable_flag)
            component.scrollable((this._scrollable0_value as boolean | undefined))
        if (this._barWidth_flag)
            component.barWidth((this._barWidth0_value as Length | undefined))
        if (this._barHeight_flag)
            component.barHeight((this._barHeight0_value as Length | undefined))
        if (this._animationDuration_flag)
            component.animationDuration((this._animationDuration0_value as number | undefined))
        if (this._animationMode_flag)
            component.animationMode((this._animationMode0_value as AnimationMode | undefined))
        if (this._edgeEffect_flag)
            component.edgeEffect((this._edgeEffect0_value as EdgeEffect | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((value0: number) => void) | undefined))
        if (this._onSelected_flag)
            component.onSelected((this._onSelected0_value as ((value0: number) => void) | undefined))
        if (this._onTabBarClick_flag)
            component.onTabBarClick((this._onTabBarClick0_value as ((value0: number) => void) | undefined))
        if (this._onUnselected_flag)
            component.onUnselected((this._onUnselected0_value as ((value0: number) => void) | undefined))
        if (this._onAnimationStart_flag)
            component.onAnimationStart((this._onAnimationStart0_value as OnTabsAnimationStartCallback | undefined))
        if (this._onAnimationEnd_flag)
            component.onAnimationEnd((this._onAnimationEnd0_value as OnTabsAnimationEndCallback | undefined))
        if (this._onGestureSwipe_flag)
            component.onGestureSwipe((this._onGestureSwipe0_value as OnTabsGestureSwipeCallback | undefined))
        if (this._fadingEdge_flag)
            component.fadingEdge((this._fadingEdge0_value as boolean | undefined))
        if (this._divider_flag)
            component.divider((this._divider0_value as DividerStyle | undefined))
        if (this._barOverlap_flag)
            component.barOverlap((this._barOverlap0_value as boolean | undefined))
        if (this._barBackgroundColor_flag)
            component.barBackgroundColor((this._barBackgroundColor0_value as ResourceColor | undefined))
        if (this._barGridAlign_flag)
            component.barGridAlign((this._barGridAlign0_value as BarGridColumnOptions | undefined))
        if (this._customContentTransition_flag)
            component.customContentTransition((this._customContentTransition0_value as TabsCustomContentTransitionCallback | undefined))
        if (this._barBackgroundBlurStyle_flag)
            component.barBackgroundBlurStyle((this._barBackgroundBlurStyle0_value as BlurStyle | undefined), (this._barBackgroundBlurStyle1_value as BackgroundBlurStyleOptions | undefined))
        if (this._pageFlipMode_flag)
            component.pageFlipMode((this._pageFlipMode0_value as PageFlipMode | undefined))
        if (this._barBackgroundEffect_flag)
            component.barBackgroundEffect((this._barBackgroundEffect0_value as BackgroundEffectOptions | undefined))
        if (this._onContentWillChange_flag)
            component.onContentWillChange((this._onContentWillChange0_value as OnTabsContentWillChangeCallback | undefined))
        if (this._barMode_flag)
            component.barMode((this._barMode0_value as BarMode | undefined), (this._barMode1_value as ScrollableBarModeOptions | undefined))
        if (this._cachedMaxCount_flag)
            component.cachedMaxCount((this._cachedMaxCount0_value as number | undefined), (this._cachedMaxCount1_value as TabsCacheMode | undefined))
    }
    public vertical(value: boolean | undefined): this {
        this._vertical_flag = true
        this._vertical0_value = value
        return this
    }
    public barPosition(value: BarPosition | undefined): this {
        this._barPosition_flag = true
        this._barPosition0_value = value
        return this
    }
    public scrollable(value: boolean | undefined): this {
        this._scrollable_flag = true
        this._scrollable0_value = value
        return this
    }
    public barWidth(value: Length | undefined): this {
        this._barWidth_flag = true
        this._barWidth0_value = value
        return this
    }
    public barHeight(value: Length | undefined): this {
        this._barHeight_flag = true
        this._barHeight0_value = value
        return this
    }
    public animationDuration(value: number | undefined): this {
        this._animationDuration_flag = true
        this._animationDuration0_value = value
        return this
    }
    public animationMode(value: AnimationMode | undefined): this {
        this._animationMode_flag = true
        this._animationMode0_value = value
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined): this {
        this._edgeEffect_flag = true
        this._edgeEffect0_value = value
        return this
    }
    public onChange(value: ((value0: number) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public onSelected(value: ((value0: number) => void) | undefined): this {
        this._onSelected_flag = true
        this._onSelected0_value = value
        return this
    }
    public onTabBarClick(value: ((value0: number) => void) | undefined): this {
        this._onTabBarClick_flag = true
        this._onTabBarClick0_value = value
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
        this._onUnselected_flag = true
        this._onUnselected0_value = value
        return this
    }
    public onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        this._onAnimationStart_flag = true
        this._onAnimationStart0_value = value
        return this
    }
    public onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        this._onAnimationEnd_flag = true
        this._onAnimationEnd0_value = value
        return this
    }
    public onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        this._onGestureSwipe_flag = true
        this._onGestureSwipe0_value = value
        return this
    }
    public fadingEdge(value: boolean | undefined): this {
        this._fadingEdge_flag = true
        this._fadingEdge0_value = value
        return this
    }
    public divider(value: DividerStyle | undefined): this {
        this._divider_flag = true
        this._divider0_value = value
        return this
    }
    public barOverlap(value: boolean | undefined): this {
        this._barOverlap_flag = true
        this._barOverlap0_value = value
        return this
    }
    public barBackgroundColor(value: ResourceColor | undefined): this {
        this._barBackgroundColor_flag = true
        this._barBackgroundColor0_value = value
        return this
    }
    public barGridAlign(value: BarGridColumnOptions | undefined): this {
        this._barGridAlign_flag = true
        this._barGridAlign0_value = value
        return this
    }
    public customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        this._customContentTransition_flag = true
        this._customContentTransition0_value = value
        return this
    }
    public barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        this._barBackgroundBlurStyle_flag = true
        this._barBackgroundBlurStyle0_value = style
        this._barBackgroundBlurStyle1_value = options
        return this
    }
    public pageFlipMode(value: PageFlipMode | undefined): this {
        this._pageFlipMode_flag = true
        this._pageFlipMode0_value = value
        return this
    }
    public barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        this._barBackgroundEffect_flag = true
        this._barBackgroundEffect0_value = value
        return this
    }
    public onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        this._onContentWillChange_flag = true
        this._onContentWillChange0_value = value
        return this
    }
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        this._barMode_flag = true
        this._barMode0_value = value
        this._barMode1_value = options
        return this
    }
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        this._cachedMaxCount_flag = true
        this._cachedMaxCount0_value = count
        this._cachedMaxCount1_value = mode
        return this
    }
    public _onChangeEvent_index(callback_: ((value0: number) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TabContentTransitionProxy_serializer {
    public static write(buffer: SerializerBase, value: TabContentTransitionProxy): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TabContentTransitionProxy {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TabContentTransitionProxyInternal.fromPtr(ptr)
    }
}
export class TabsAnimationEvent_serializer {
    public static write(buffer: SerializerBase, value: TabsAnimationEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_currentOffset  = value.currentOffset
        valueSerializer.writeNumber(value_currentOffset)
        const value_targetOffset  = value.targetOffset
        valueSerializer.writeNumber(value_targetOffset)
        const value_velocity  = value.velocity
        valueSerializer.writeNumber(value_velocity)
    }
    public static read(buffer: DeserializerBase): TabsAnimationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const currentOffset_result : number = (valueDeserializer.readNumber() as number)
        const targetOffset_result : number = (valueDeserializer.readNumber() as number)
        const velocity_result : number = (valueDeserializer.readNumber() as number)
        let value : TabsAnimationEvent = ({currentOffset: currentOffset_result, targetOffset: targetOffset_result, velocity: velocity_result} as TabsAnimationEvent)
        return value
    }
}
export class TabsController_serializer {
    public static write(buffer: SerializerBase, value: TabsController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TabsController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TabsControllerInternal.fromPtr(ptr)
    }
}
export class TabContentAnimatedTransition_serializer {
    public static write(buffer: SerializerBase, value: TabContentAnimatedTransition): void {
        let valueSerializer : SerializerBase = buffer
        const value_timeout  = value.timeout
        let value_timeout_type : int32 = RuntimeType.UNDEFINED
        value_timeout_type = runtimeType(value_timeout)
        valueSerializer.writeInt8((value_timeout_type).toChar())
        if ((value_timeout_type) != (RuntimeType.UNDEFINED)) {
            const value_timeout_value  = value_timeout!
            valueSerializer.writeNumber(value_timeout_value)
        }
        const value_transition  = value.transition
        valueSerializer.holdAndWriteCallback(value_transition)
    }
    public static read(buffer: DeserializerBase): TabContentAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const timeout_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeout_buf : number | undefined
        if ((timeout_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeout_buf = (valueDeserializer.readNumber() as number)
        }
        const timeout_result : number | undefined = timeout_buf
        const transition_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const transition_buf_call : KPointer = valueDeserializer.readPointer()
        const transition_buf_callSync : KPointer = valueDeserializer.readPointer()
        const transition_result : ((value0: TabContentTransitionProxy) => void) = (value0: TabContentTransitionProxy):void => { 
    const transition_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    transition_buf_argsSerializer.writeInt32(transition_buf_resource.resourceId);
    transition_buf_argsSerializer.writePointer(transition_buf_call);
    transition_buf_argsSerializer.writePointer(transition_buf_callSync);
    TabContentTransitionProxy_serializer.write(transition_buf_argsSerializer, value0);
    InteropNativeModule._CallCallback(-1223938478, transition_buf_argsSerializer.asBuffer(), transition_buf_argsSerializer.length());
    transition_buf_argsSerializer.release();
    return; }
        let value : TabContentAnimatedTransition = ({timeout: timeout_result, transition: transition_result} as TabContentAnimatedTransition)
        return value
    }
}
export class TabsOptions_serializer {
    public static write(buffer: SerializerBase, value: TabsOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_barPosition  = value.barPosition
        let value_barPosition_type : int32 = RuntimeType.UNDEFINED
        value_barPosition_type = runtimeType(value_barPosition)
        valueSerializer.writeInt8((value_barPosition_type).toChar())
        if ((value_barPosition_type) != (RuntimeType.UNDEFINED)) {
            const value_barPosition_value  = (value_barPosition as BarPosition)
            valueSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(value_barPosition_value))
        }
        const value_index  = value.index
        let value_index_type : int32 = RuntimeType.UNDEFINED
        value_index_type = runtimeType(value_index)
        valueSerializer.writeInt8((value_index_type).toChar())
        if ((value_index_type) != (RuntimeType.UNDEFINED)) {
            const value_index_value  = value_index!
            valueSerializer.writeNumber(value_index_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
            const value_controller_value  = value_controller!
            TabsController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): TabsOptions {
        let valueDeserializer : DeserializerBase = buffer
        const barPosition_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let barPosition_buf : BarPosition | undefined
        if ((barPosition_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            barPosition_buf = TypeChecker.BarPosition_FromNumeric(valueDeserializer.readInt32())
        }
        const barPosition_result : BarPosition | undefined = barPosition_buf
        const index_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let index_buf : number | undefined
        if ((index_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            index_buf = (valueDeserializer.readNumber() as number)
        }
        const index_result : number | undefined = index_buf
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : TabsController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            controller_buf = (TabsController_serializer.read(valueDeserializer) as TabsController)
        }
        const controller_result : TabsController | undefined = controller_buf
        let value : TabsOptions = ({barPosition: barPosition_result, index: index_result, controller: controller_result} as TabsOptions)
        return value
    }
}
export class BarGridColumnOptions_serializer {
    public static write(buffer: SerializerBase, value: BarGridColumnOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_sm  = value.sm
        let value_sm_type : int32 = RuntimeType.UNDEFINED
        value_sm_type = runtimeType(value_sm)
        valueSerializer.writeInt8((value_sm_type).toChar())
        if ((value_sm_type) != (RuntimeType.UNDEFINED)) {
            const value_sm_value  = value_sm!
            valueSerializer.writeNumber(value_sm_value)
        }
        const value_md  = value.md
        let value_md_type : int32 = RuntimeType.UNDEFINED
        value_md_type = runtimeType(value_md)
        valueSerializer.writeInt8((value_md_type).toChar())
        if ((value_md_type) != (RuntimeType.UNDEFINED)) {
            const value_md_value  = value_md!
            valueSerializer.writeNumber(value_md_value)
        }
        const value_lg  = value.lg
        let value_lg_type : int32 = RuntimeType.UNDEFINED
        value_lg_type = runtimeType(value_lg)
        valueSerializer.writeInt8((value_lg_type).toChar())
        if ((value_lg_type) != (RuntimeType.UNDEFINED)) {
            const value_lg_value  = value_lg!
            valueSerializer.writeNumber(value_lg_value)
        }
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8((value_margin_type).toChar())
        if ((value_margin_type) != (RuntimeType.UNDEFINED)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (RuntimeType.STRING == value_margin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_margin_value_0  = value_margin_value as string
                valueSerializer.writeString(value_margin_value_0)
            }
            else if (RuntimeType.NUMBER == value_margin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_margin_value_1  = value_margin_value as number
                valueSerializer.writeNumber(value_margin_value_1)
            }
            else if (RuntimeType.OBJECT == value_margin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_margin_value_2  = value_margin_value as Resource
                Resource_serializer.write(valueSerializer, value_margin_value_2)
            }
        }
        const value_gutter  = value.gutter
        let value_gutter_type : int32 = RuntimeType.UNDEFINED
        value_gutter_type = runtimeType(value_gutter)
        valueSerializer.writeInt8((value_gutter_type).toChar())
        if ((value_gutter_type) != (RuntimeType.UNDEFINED)) {
            const value_gutter_value  = value_gutter!
            let value_gutter_value_type : int32 = RuntimeType.UNDEFINED
            value_gutter_value_type = runtimeType(value_gutter_value)
            if (RuntimeType.STRING == value_gutter_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_gutter_value_0  = value_gutter_value as string
                valueSerializer.writeString(value_gutter_value_0)
            }
            else if (RuntimeType.NUMBER == value_gutter_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_gutter_value_1  = value_gutter_value as number
                valueSerializer.writeNumber(value_gutter_value_1)
            }
            else if (RuntimeType.OBJECT == value_gutter_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_gutter_value_2  = value_gutter_value as Resource
                Resource_serializer.write(valueSerializer, value_gutter_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): BarGridColumnOptions {
        let valueDeserializer : DeserializerBase = buffer
        const sm_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sm_buf : number | undefined
        if ((sm_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            sm_buf = (valueDeserializer.readNumber() as number)
        }
        const sm_result : number | undefined = sm_buf
        const md_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let md_buf : number | undefined
        if ((md_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            md_buf = (valueDeserializer.readNumber() as number)
        }
        const md_result : number | undefined = md_buf
        const lg_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lg_buf : number | undefined
        if ((lg_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            lg_buf = (valueDeserializer.readNumber() as number)
        }
        const lg_result : number | undefined = lg_buf
        const margin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let margin_buf : Dimension | undefined
        if ((margin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : string | number | Resource | undefined
            if (margin_buf__selector == (0).toChar()) {
                margin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (margin_buf__selector == (1).toChar()) {
                margin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (margin_buf__selector == (2).toChar()) {
                margin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as string | number | Resource)
        }
        const margin_result : Dimension | undefined = margin_buf
        const gutter_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gutter_buf : Dimension | undefined
        if ((gutter_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const gutter_buf__selector : int32 = valueDeserializer.readInt8()
            let gutter_buf_ : string | number | Resource | undefined
            if (gutter_buf__selector == (0).toChar()) {
                gutter_buf_ = (valueDeserializer.readString() as string)
            }
            else if (gutter_buf__selector == (1).toChar()) {
                gutter_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (gutter_buf__selector == (2).toChar()) {
                gutter_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for gutter_buf_ has to be chosen through deserialisation.")
            }
            gutter_buf = (gutter_buf_ as string | number | Resource)
        }
        const gutter_result : Dimension | undefined = gutter_buf
        let value : BarGridColumnOptions = ({sm: sm_result, md: md_result, lg: lg_result, margin: margin_result, gutter: gutter_result} as BarGridColumnOptions)
        return value
    }
}
export class ScrollableBarModeOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollableBarModeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8((value_margin_type).toChar())
        if ((value_margin_type) != (RuntimeType.UNDEFINED)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (RuntimeType.STRING == value_margin_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_margin_value_0  = value_margin_value as string
                valueSerializer.writeString(value_margin_value_0)
            }
            else if (RuntimeType.NUMBER == value_margin_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_margin_value_1  = value_margin_value as number
                valueSerializer.writeNumber(value_margin_value_1)
            }
            else if (RuntimeType.OBJECT == value_margin_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_margin_value_2  = value_margin_value as Resource
                Resource_serializer.write(valueSerializer, value_margin_value_2)
            }
        }
        const value_nonScrollableLayoutStyle  = value.nonScrollableLayoutStyle
        let value_nonScrollableLayoutStyle_type : int32 = RuntimeType.UNDEFINED
        value_nonScrollableLayoutStyle_type = runtimeType(value_nonScrollableLayoutStyle)
        valueSerializer.writeInt8((value_nonScrollableLayoutStyle_type).toChar())
        if ((value_nonScrollableLayoutStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_nonScrollableLayoutStyle_value  = (value_nonScrollableLayoutStyle as LayoutStyle)
            valueSerializer.writeInt32(TypeChecker.LayoutStyle_ToNumeric(value_nonScrollableLayoutStyle_value))
        }
    }
    public static read(buffer: DeserializerBase): ScrollableBarModeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const margin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let margin_buf : Dimension | undefined
        if ((margin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : string | number | Resource | undefined
            if (margin_buf__selector == (0).toChar()) {
                margin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (margin_buf__selector == (1).toChar()) {
                margin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (margin_buf__selector == (2).toChar()) {
                margin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as string | number | Resource)
        }
        const margin_result : Dimension | undefined = margin_buf
        const nonScrollableLayoutStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nonScrollableLayoutStyle_buf : LayoutStyle | undefined
        if ((nonScrollableLayoutStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            nonScrollableLayoutStyle_buf = TypeChecker.LayoutStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const nonScrollableLayoutStyle_result : LayoutStyle | undefined = nonScrollableLayoutStyle_buf
        let value : ScrollableBarModeOptions = ({margin: margin_result, nonScrollableLayoutStyle: nonScrollableLayoutStyle_result} as ScrollableBarModeOptions)
        return value
    }
}
