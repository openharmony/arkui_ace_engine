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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { TranslateOptions_serializer, TranslateOptions, DividerStyle_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ArkCommonMethodPeer, CommonMethod, DividerStyle, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions, BlurStyleOptions, BlurStyleActivePolicy, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource_serializer, Resource } from "./resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Length, ResourceColor, Dimension } from "./units"
import { EdgeEffect, Color, PageFlipMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { CommonModifier, CommonModifier_serializer } from "./arkui.CommonModifier"
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_ctor()
        return retval
    }
    constructor() {
        this(TabContentTransitionProxyInternal.ctor())
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
        return new TabContentTransitionProxyInternal(ptr)
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabsController_ctor()
        return retval
    }
    constructor() {
        this(TabsController.ctor())
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
        thisSerializer.writeInt8(indices_type)
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            TabsOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TabsInterface_setTabsOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    verticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_vertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barPositionAttribute(value: BarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarPosition)
            thisSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_scrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    animationDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_animationDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    animationModeAttribute(value: AnimationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as AnimationMode)
            thisSerializer.writeInt32(TypeChecker.AnimationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_animationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTabBarClickAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onTabBarClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUnselectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationStartAttribute(value: OnTabsAnimationStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnTabsAnimationEndCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnTabsGestureSwipeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fadingEdgeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_fadingEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            DividerStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barOverlapAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barOverlap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barGridAlignAttribute(value: BarGridColumnOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            BarGridColumnOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barGridAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customContentTransitionAttribute(value: TabsCustomContentTransitionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_customContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundBlurStyle0Attribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundBlurStyle1Attribute(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let style_type : int32 = RuntimeType.UNDEFINED
        style_type = runtimeType(style)
        thisSerializer.writeInt8(style_type)
        if ((RuntimeType.UNDEFINED) != (style_type)) {
            const style_value  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(style_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            BackgroundBlurStyleOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barBackgroundEffectAttribute(value: BackgroundEffectOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            BackgroundEffectOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barBackgroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_pageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentWillChangeAttribute(value: OnTabsContentWillChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_onContentWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    barModeAttribute(value: BarMode | undefined, options?: ScrollableBarModeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarMode)
            thisSerializer.writeInt32(TypeChecker.BarMode_ToNumeric(value_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            ScrollableBarModeOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_barMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedMaxCountAttribute(count: number | undefined, mode: TabsCacheMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let mode_type : int32 = RuntimeType.UNDEFINED
        mode_type = runtimeType(mode)
        thisSerializer.writeInt8(mode_type)
        if ((RuntimeType.UNDEFINED) != (mode_type)) {
            const mode_value  = (mode as TabsCacheMode)
            thisSerializer.writeInt32(TypeChecker.TabsCacheMode_ToNumeric(mode_value))
        }
        ArkUIGeneratedNativeModule._TabsAttribute_cachedMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    barModifier?: CommonModifier;
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
    vertical(value: boolean | undefined): this
    barPosition(value: BarPosition | undefined): this
    scrollable(value: boolean | undefined): this
    barWidth(value: Length | undefined): this
    barHeight(value: Length | undefined): this
    animationDuration(value: number | undefined): this
    animationMode(value: AnimationMode | undefined): this
    edgeEffect(value: EdgeEffect | undefined): this
    onChange(value: ((value0: number) => void) | undefined): this
    onSelected(value: ((value0: number) => void) | undefined): this
    onTabBarClick(value: ((value0: number) => void) | undefined): this
    onUnselected(value: ((value0: number) => void) | undefined): this
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this
    fadingEdge(value: boolean | undefined): this
    divider(value: DividerStyle | undefined): this
    barOverlap(value: boolean | undefined): this
    barBackgroundColor(value: ResourceColor | undefined): this
    barGridAlign(value: BarGridColumnOptions | undefined): this
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this
    barBackgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions): this
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this
    pageFlipMode(value: PageFlipMode | undefined): this
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this
    attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this
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
    barBackgroundEffect_value?: BackgroundEffectOptions | undefined
    pageFlipMode_value?: PageFlipMode | undefined
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
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        return this
    }
    public cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        return this
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
        if (this.barBackgroundEffect_value !== undefined)
            target.barBackgroundEffect(this.barBackgroundEffect_value!)
        if (this.pageFlipMode_value !== undefined)
            target.pageFlipMode(this.pageFlipMode_value!)
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
    public onChange(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelected(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.onSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onTabBarClick(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onTabBarClick")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.onTabBarClickAttribute(value_casted)
            return this
        }
        return this
    }
    public onUnselected(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onUnselected")) {
            const value_casted = value as (((value0: number) => void) | undefined)
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
    public divider(value: DividerStyle | undefined): this {
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
            const style_type = runtimeType(style)
            const options_type = runtimeType(options)
            if (((RuntimeType.OBJECT == style_type) || (RuntimeType.OBJECT == style_type)) && (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = style as (BlurStyle | undefined)
                this.getPeer()?.barBackgroundBlurStyle0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.OBJECT == style_type) || (RuntimeType.OBJECT == style_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const style_casted = style as (BlurStyle | undefined)
                const options_casted = options as (BackgroundBlurStyleOptions | undefined)
                this.getPeer()?.barBackgroundBlurStyle1Attribute(style_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
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
    public barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        if (this.checkPriority("barMode")) {
            const value_casted = value as (BarMode | undefined)
            const options_casted = options as (ScrollableBarModeOptions | undefined)
            this.getPeer()?.barModeAttribute(value_casted, options_casted)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("TabsImpl")
export function Tabs(
    options?: TabsOptions | undefined,
    @memo
    content_?: () => void,
): TabsAttribute {
    throw new Error("Not implemented")
}

@memo
export function TabsImpl(
    @memo
    style: ((attributes: TabsAttribute) => void) | undefined,
    options?: TabsOptions | undefined,
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
        valueSerializer.writeInt8(value_timeout_type)
        if ((RuntimeType.UNDEFINED) != (value_timeout_type)) {
            const value_timeout_value  = value_timeout!
            valueSerializer.writeNumber(value_timeout_value)
        }
        const value_transition  = value.transition
        valueSerializer.holdAndWriteCallback(value_transition)
    }
    public static read(buffer: DeserializerBase): TabContentAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const timeout_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let timeout_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (timeout_buf_runtimeType))
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
        valueSerializer.writeInt8(value_barPosition_type)
        if ((RuntimeType.UNDEFINED) != (value_barPosition_type)) {
            const value_barPosition_value  = (value_barPosition as BarPosition)
            valueSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(value_barPosition_value))
        }
        const value_index  = value.index
        let value_index_type : int32 = RuntimeType.UNDEFINED
        value_index_type = runtimeType(value_index)
        valueSerializer.writeInt8(value_index_type)
        if ((RuntimeType.UNDEFINED) != (value_index_type)) {
            const value_index_value  = value_index!
            valueSerializer.writeNumber(value_index_value)
        }
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8(value_controller_type)
        if ((RuntimeType.UNDEFINED) != (value_controller_type)) {
            const value_controller_value  = value_controller!
            TabsController_serializer.write(valueSerializer, value_controller_value)
        }
        const value_barModifier  = value.barModifier
        let value_barModifier_type : int32 = RuntimeType.UNDEFINED
        value_barModifier_type = runtimeType(value_barModifier)
        valueSerializer.writeInt8(value_barModifier_type)
        if ((RuntimeType.UNDEFINED) != (value_barModifier_type)) {
            const value_barModifier_value  = value_barModifier!
            CommonModifier_serializer.write(valueSerializer, value_barModifier_value)
        }
    }
    public static read(buffer: DeserializerBase): TabsOptions {
        let valueDeserializer : DeserializerBase = buffer
        const barPosition_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let barPosition_buf : BarPosition | undefined
        if ((RuntimeType.UNDEFINED) != (barPosition_buf_runtimeType))
        {
            barPosition_buf = TypeChecker.BarPosition_FromNumeric(valueDeserializer.readInt32())
        }
        const barPosition_result : BarPosition | undefined = barPosition_buf
        const index_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let index_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (index_buf_runtimeType))
        {
            index_buf = (valueDeserializer.readNumber() as number)
        }
        const index_result : number | undefined = index_buf
        const controller_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let controller_buf : TabsController | undefined
        if ((RuntimeType.UNDEFINED) != (controller_buf_runtimeType))
        {
            controller_buf = (TabsController_serializer.read(valueDeserializer) as TabsController)
        }
        const controller_result : TabsController | undefined = controller_buf
        const barModifier_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let barModifier_buf : CommonModifier | undefined
        if ((RuntimeType.UNDEFINED) != (barModifier_buf_runtimeType))
        {
            barModifier_buf = CommonModifier_serializer.read(valueDeserializer)
        }
        const barModifier_result : CommonModifier | undefined = barModifier_buf
        let value : TabsOptions = ({barPosition: barPosition_result, index: index_result, controller: controller_result, barModifier: barModifier_result} as TabsOptions)
        return value
    }
}
export class BarGridColumnOptions_serializer {
    public static write(buffer: SerializerBase, value: BarGridColumnOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_sm  = value.sm
        let value_sm_type : int32 = RuntimeType.UNDEFINED
        value_sm_type = runtimeType(value_sm)
        valueSerializer.writeInt8(value_sm_type)
        if ((RuntimeType.UNDEFINED) != (value_sm_type)) {
            const value_sm_value  = value_sm!
            valueSerializer.writeNumber(value_sm_value)
        }
        const value_md  = value.md
        let value_md_type : int32 = RuntimeType.UNDEFINED
        value_md_type = runtimeType(value_md)
        valueSerializer.writeInt8(value_md_type)
        if ((RuntimeType.UNDEFINED) != (value_md_type)) {
            const value_md_value  = value_md!
            valueSerializer.writeNumber(value_md_value)
        }
        const value_lg  = value.lg
        let value_lg_type : int32 = RuntimeType.UNDEFINED
        value_lg_type = runtimeType(value_lg)
        valueSerializer.writeInt8(value_lg_type)
        if ((RuntimeType.UNDEFINED) != (value_lg_type)) {
            const value_lg_value  = value_lg!
            valueSerializer.writeNumber(value_lg_value)
        }
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8(value_margin_type)
        if ((RuntimeType.UNDEFINED) != (value_margin_type)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (RuntimeType.STRING == value_margin_value_type) {
                valueSerializer.writeInt8(0)
                const value_margin_value_0  = value_margin_value as string
                valueSerializer.writeString(value_margin_value_0)
            }
            else if (RuntimeType.NUMBER == value_margin_value_type) {
                valueSerializer.writeInt8(1)
                const value_margin_value_1  = value_margin_value as number
                valueSerializer.writeNumber(value_margin_value_1)
            }
            else if (RuntimeType.OBJECT == value_margin_value_type) {
                valueSerializer.writeInt8(2)
                const value_margin_value_2  = value_margin_value as Resource
                Resource_serializer.write(valueSerializer, value_margin_value_2)
            }
        }
        const value_gutter  = value.gutter
        let value_gutter_type : int32 = RuntimeType.UNDEFINED
        value_gutter_type = runtimeType(value_gutter)
        valueSerializer.writeInt8(value_gutter_type)
        if ((RuntimeType.UNDEFINED) != (value_gutter_type)) {
            const value_gutter_value  = value_gutter!
            let value_gutter_value_type : int32 = RuntimeType.UNDEFINED
            value_gutter_value_type = runtimeType(value_gutter_value)
            if (RuntimeType.STRING == value_gutter_value_type) {
                valueSerializer.writeInt8(0)
                const value_gutter_value_0  = value_gutter_value as string
                valueSerializer.writeString(value_gutter_value_0)
            }
            else if (RuntimeType.NUMBER == value_gutter_value_type) {
                valueSerializer.writeInt8(1)
                const value_gutter_value_1  = value_gutter_value as number
                valueSerializer.writeNumber(value_gutter_value_1)
            }
            else if (RuntimeType.OBJECT == value_gutter_value_type) {
                valueSerializer.writeInt8(2)
                const value_gutter_value_2  = value_gutter_value as Resource
                Resource_serializer.write(valueSerializer, value_gutter_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): BarGridColumnOptions {
        let valueDeserializer : DeserializerBase = buffer
        const sm_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let sm_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (sm_buf_runtimeType))
        {
            sm_buf = (valueDeserializer.readNumber() as number)
        }
        const sm_result : number | undefined = sm_buf
        const md_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let md_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (md_buf_runtimeType))
        {
            md_buf = (valueDeserializer.readNumber() as number)
        }
        const md_result : number | undefined = md_buf
        const lg_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lg_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (lg_buf_runtimeType))
        {
            lg_buf = (valueDeserializer.readNumber() as number)
        }
        const lg_result : number | undefined = lg_buf
        const margin_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let margin_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (margin_buf_runtimeType))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : string | number | Resource | undefined
            if (margin_buf__selector == 0) {
                margin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (margin_buf__selector == 1) {
                margin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (margin_buf__selector == 2) {
                margin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as string | number | Resource)
        }
        const margin_result : Dimension | undefined = margin_buf
        const gutter_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let gutter_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (gutter_buf_runtimeType))
        {
            const gutter_buf__selector : int32 = valueDeserializer.readInt8()
            let gutter_buf_ : string | number | Resource | undefined
            if (gutter_buf__selector == 0) {
                gutter_buf_ = (valueDeserializer.readString() as string)
            }
            else if (gutter_buf__selector == 1) {
                gutter_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (gutter_buf__selector == 2) {
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
        valueSerializer.writeInt8(value_margin_type)
        if ((RuntimeType.UNDEFINED) != (value_margin_type)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (RuntimeType.STRING == value_margin_value_type) {
                valueSerializer.writeInt8(0)
                const value_margin_value_0  = value_margin_value as string
                valueSerializer.writeString(value_margin_value_0)
            }
            else if (RuntimeType.NUMBER == value_margin_value_type) {
                valueSerializer.writeInt8(1)
                const value_margin_value_1  = value_margin_value as number
                valueSerializer.writeNumber(value_margin_value_1)
            }
            else if (RuntimeType.OBJECT == value_margin_value_type) {
                valueSerializer.writeInt8(2)
                const value_margin_value_2  = value_margin_value as Resource
                Resource_serializer.write(valueSerializer, value_margin_value_2)
            }
        }
        const value_nonScrollableLayoutStyle  = value.nonScrollableLayoutStyle
        let value_nonScrollableLayoutStyle_type : int32 = RuntimeType.UNDEFINED
        value_nonScrollableLayoutStyle_type = runtimeType(value_nonScrollableLayoutStyle)
        valueSerializer.writeInt8(value_nonScrollableLayoutStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_nonScrollableLayoutStyle_type)) {
            const value_nonScrollableLayoutStyle_value  = (value_nonScrollableLayoutStyle as LayoutStyle)
            valueSerializer.writeInt32(TypeChecker.LayoutStyle_ToNumeric(value_nonScrollableLayoutStyle_value))
        }
    }
    public static read(buffer: DeserializerBase): ScrollableBarModeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const margin_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let margin_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (margin_buf_runtimeType))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : string | number | Resource | undefined
            if (margin_buf__selector == 0) {
                margin_buf_ = (valueDeserializer.readString() as string)
            }
            else if (margin_buf__selector == 1) {
                margin_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (margin_buf__selector == 2) {
                margin_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as string | number | Resource)
        }
        const margin_result : Dimension | undefined = margin_buf
        const nonScrollableLayoutStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let nonScrollableLayoutStyle_buf : LayoutStyle | undefined
        if ((RuntimeType.UNDEFINED) != (nonScrollableLayoutStyle_buf_runtimeType))
        {
            nonScrollableLayoutStyle_buf = TypeChecker.LayoutStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const nonScrollableLayoutStyle_result : LayoutStyle | undefined = nonScrollableLayoutStyle_buf
        let value : ScrollableBarModeOptions = ({margin: margin_result, nonScrollableLayoutStyle: nonScrollableLayoutStyle_result} as ScrollableBarModeOptions)
        return value
    }
}
