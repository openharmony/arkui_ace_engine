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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { TranslateOptions_serializer, TranslateOptions, DividerStyle_serializer, BackgroundEffectOptions_serializer, BackgroundBlurStyleOptions_serializer, ArkCommonMethodPeer, CommonMethod, DividerStyle, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions, BlurStyleOptions, BlurStyleActivePolicy, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, Bindable_Number_serializer } from "./common"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Length, ResourceColor, Dimension } from "./units"
import { EdgeEffect, Color, PageFlipMode } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        if (indices !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const indicesTmpValue  = indices!
            thisSerializer.writeInt32((indicesTmpValue.length).toInt())
            for (let indicesTmpValueCounterI = 0; indicesTmpValueCounterI < indicesTmpValue.length; indicesTmpValueCounterI++) {
                const indicesTmpValueTmpElement : number = indicesTmpValue[indicesTmpValueCounterI]
                thisSerializer.writeNumber(indicesTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const _peer  = new ArkTabsPeer(_peerPtr, peerId, 'Tabs', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabsOptionsAttribute(options?: TabsOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            TabsOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsInterface_setTabsOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVerticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setVertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarPositionAttribute(value: BarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BarPosition)
            thisSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnimationDurationAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setAnimationDuration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnimationModeAttribute(value: AnimationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as AnimationMode)
            thisSerializer.writeInt32(TypeChecker.AnimationMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setAnimationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeEffectAttribute(value: EdgeEffect | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTabBarClickAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnTabBarClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUnselectedAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnUnselected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationStartAttribute(value: OnTabsAnimationStartCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnAnimationStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAnimationEndAttribute(value: OnTabsAnimationEndCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnAnimationEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnGestureSwipeAttribute(value: OnTabsGestureSwipeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnGestureSwipe(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFadingEdgeAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setFadingEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDividerAttribute(value: DividerStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DividerStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setDivider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarOverlapAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarOverlap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarGridAlignAttribute(value: BarGridColumnOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            BarGridColumnOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarGridAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomContentTransitionAttribute(value: TabsCustomContentTransitionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setCustomContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundBlurStyle0Attribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundBlurStyle0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPageFlipModeAttribute(value: PageFlipMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as PageFlipMode)
            thisSerializer.writeInt32(TypeChecker.PageFlipMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setPageFlipMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundEffectAttribute(value: BackgroundEffectOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            BackgroundEffectOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentWillChangeAttribute(value: OnTabsContentWillChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnContentWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarModeAttribute(value: BarMode | undefined, options?: ScrollableBarModeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BarMode)
            thisSerializer.writeInt32(TypeChecker.BarMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ScrollableBarModeOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundBlurStyle1Attribute(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue  = (style as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(styleTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            BackgroundBlurStyleOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarBackgroundBlurStyle1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedMaxCountAttribute(count: number | undefined, mode: TabsCacheMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeNumber(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (mode !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const modeTmpValue  = (mode as TabsCacheMode)
            thisSerializer.writeInt32(TypeChecker.TabsCacheMode_ToNumeric(modeTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setCachedMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    index?: number | Bindable<number>;
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
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class TabsModifier extends CommonMethodModifier implements TabsAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _vertical_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _vertical_0_0value?: boolean | undefined
    _barPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barPosition_0_0value?: BarPosition | undefined
    _scrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scrollable_0_0value?: boolean | undefined
    _barWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barWidth_0_0value?: Length | undefined
    _barHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barHeight_0_0value?: Length | undefined
    _animationDuration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _animationDuration_0_0value?: number | undefined
    _animationMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _animationMode_0_0value?: AnimationMode | undefined
    _edgeEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _edgeEffect_0_0value?: EdgeEffect | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: ((value0: number) => void) | undefined
    _onSelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelected_0_0value?: ((value0: number) => void) | undefined
    _onTabBarClick_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTabBarClick_0_0value?: ((value0: number) => void) | undefined
    _onUnselected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUnselected_0_0value?: ((value0: number) => void) | undefined
    _onAnimationStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationStart_0_0value?: OnTabsAnimationStartCallback | undefined
    _onAnimationEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAnimationEnd_0_0value?: OnTabsAnimationEndCallback | undefined
    _onGestureSwipe_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureSwipe_0_0value?: OnTabsGestureSwipeCallback | undefined
    _fadingEdge_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fadingEdge_0_0value?: boolean | undefined
    _divider_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _divider_0_0value?: DividerStyle | undefined
    _barOverlap_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barOverlap_0_0value?: boolean | undefined
    _barBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundColor_0_0value?: ResourceColor | undefined
    _barGridAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barGridAlign_0_0value?: BarGridColumnOptions | undefined
    _customContentTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customContentTransition_0_0value?: TabsCustomContentTransitionCallback | undefined
    _barBackgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    _pageFlipMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pageFlipMode_0_0value?: PageFlipMode | undefined
    _barBackgroundEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundEffect_0_0value?: BackgroundEffectOptions | undefined
    _onContentWillChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentWillChange_0_0value?: OnTabsContentWillChangeCallback | undefined
    _barMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barMode_0_0value?: BarMode | undefined
    _barMode_0_1value?: ScrollableBarModeOptions | undefined
    _barBackgroundBlurStyle_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _barBackgroundBlurStyle_1_0value?: BlurStyle | undefined
    _barBackgroundBlurStyle_1_1value?: BackgroundBlurStyleOptions | undefined
    _cachedMaxCount_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cachedMaxCount_0_0value?: number | undefined
    _cachedMaxCount_0_1value?: TabsCacheMode | undefined
    applyModifierPatch(peer: ArkTabsPeer): void {
        super.applyModifierPatch(peer)
        if (this._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._vertical_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._vertical_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._barPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarPositionAttribute((this._barPosition_0_0value as BarPosition | undefined));
                    this._barPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarPositionAttribute((undefined as BarPosition | undefined));
                }
            }
        }
        if (this._scrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScrollableAttribute((this._scrollable_0_0value as boolean | undefined));
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScrollableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._barWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarWidthAttribute((this._barWidth_0_0value as Length | undefined));
                    this._barWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._barHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarHeightAttribute((this._barHeight_0_0value as Length | undefined));
                    this._barHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarHeightAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._animationDuration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._animationDuration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAnimationDurationAttribute((this._animationDuration_0_0value as number | undefined));
                    this._animationDuration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._animationDuration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._animationDuration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAnimationDurationAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._animationMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._animationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAnimationModeAttribute((this._animationMode_0_0value as AnimationMode | undefined));
                    this._animationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._animationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._animationMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAnimationModeAttribute((undefined as AnimationMode | undefined));
                }
            }
        }
        if (this._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEdgeEffectAttribute((this._edgeEffect_0_0value as EdgeEffect | undefined));
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._edgeEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEdgeEffectAttribute((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((value0: number) => void) | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSelectedAttribute((this._onSelected_0_0value as ((value0: number) => void) | undefined));
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSelectedAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onTabBarClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTabBarClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTabBarClickAttribute((this._onTabBarClick_0_0value as ((value0: number) => void) | undefined));
                    this._onTabBarClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTabBarClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTabBarClick_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTabBarClickAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUnselectedAttribute((this._onUnselected_0_0value as ((value0: number) => void) | undefined));
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUnselected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUnselectedAttribute((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (this._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAnimationStartAttribute((this._onAnimationStart_0_0value as OnTabsAnimationStartCallback | undefined));
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAnimationStartAttribute((undefined as OnTabsAnimationStartCallback | undefined));
                }
            }
        }
        if (this._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAnimationEndAttribute((this._onAnimationEnd_0_0value as OnTabsAnimationEndCallback | undefined));
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAnimationEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAnimationEndAttribute((undefined as OnTabsAnimationEndCallback | undefined));
                }
            }
        }
        if (this._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGestureSwipeAttribute((this._onGestureSwipe_0_0value as OnTabsGestureSwipeCallback | undefined));
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureSwipe_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGestureSwipeAttribute((undefined as OnTabsGestureSwipeCallback | undefined));
                }
            }
        }
        if (this._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFadingEdgeAttribute((this._fadingEdge_0_0value as boolean | undefined));
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fadingEdge_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFadingEdgeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDividerAttribute((this._divider_0_0value as DividerStyle | undefined));
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._divider_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._divider_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDividerAttribute((undefined as DividerStyle | undefined));
                }
            }
        }
        if (this._barOverlap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barOverlap_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarOverlapAttribute((this._barOverlap_0_0value as boolean | undefined));
                    this._barOverlap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barOverlap_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barOverlap_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarOverlapAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._barBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarBackgroundColorAttribute((this._barBackgroundColor_0_0value as ResourceColor | undefined));
                    this._barBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._barGridAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barGridAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarGridAlignAttribute((this._barGridAlign_0_0value as BarGridColumnOptions | undefined));
                    this._barGridAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barGridAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barGridAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarGridAlignAttribute((undefined as BarGridColumnOptions | undefined));
                }
            }
        }
        if (this._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomContentTransitionAttribute((this._customContentTransition_0_0value as TabsCustomContentTransitionCallback | undefined));
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customContentTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomContentTransitionAttribute((undefined as TabsCustomContentTransitionCallback | undefined));
                }
            }
        }
        if (this._barBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarBackgroundBlurStyle0Attribute((this._barBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarBackgroundBlurStyle0Attribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (this._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPageFlipModeAttribute((this._pageFlipMode_0_0value as PageFlipMode | undefined));
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pageFlipMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPageFlipModeAttribute((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (this._barBackgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barBackgroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarBackgroundEffectAttribute((this._barBackgroundEffect_0_0value as BackgroundEffectOptions | undefined));
                    this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarBackgroundEffectAttribute((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (this._onContentWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentWillChangeAttribute((this._onContentWillChange_0_0value as OnTabsContentWillChangeCallback | undefined));
                    this._onContentWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentWillChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentWillChangeAttribute((undefined as OnTabsContentWillChangeCallback | undefined));
                }
            }
        }
        if (this._barMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarModeAttribute((this._barMode_0_0value as BarMode | undefined), (this._barMode_0_1value as ScrollableBarModeOptions | undefined));
                    this._barMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarModeAttribute((undefined as BarMode | undefined), (undefined as ScrollableBarModeOptions | undefined | undefined));
                }
            }
        }
        if (this._barBackgroundBlurStyle_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._barBackgroundBlurStyle_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBarBackgroundBlurStyle1Attribute((this._barBackgroundBlurStyle_1_0value as BlurStyle | undefined), (this._barBackgroundBlurStyle_1_1value as BackgroundBlurStyleOptions | undefined));
                    this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBarBackgroundBlurStyle1Attribute((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined));
                }
            }
        }
        if (this._cachedMaxCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cachedMaxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCachedMaxCountAttribute((this._cachedMaxCount_0_0value as number | undefined), (this._cachedMaxCount_0_1value as TabsCacheMode | undefined));
                    this._cachedMaxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cachedMaxCount_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cachedMaxCount_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCachedMaxCountAttribute((undefined as number | undefined), (undefined as TabsCacheMode | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: TabsModifier): void {
        super.mergeModifier(modifier)
        if (modifier._vertical_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._vertical_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._barPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barPosition(modifier._barPosition_0_0value);
                    break;
                }
                default: {
                    this.barPosition((undefined as BarPosition | undefined));
                }
            }
        }
        if (modifier._scrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scrollable(modifier._scrollable_0_0value);
                    break;
                }
                default: {
                    this.scrollable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._barWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barWidth(modifier._barWidth_0_0value);
                    break;
                }
                default: {
                    this.barWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._barHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barHeight(modifier._barHeight_0_0value);
                    break;
                }
                default: {
                    this.barHeight((undefined as Length | undefined));
                }
            }
        }
        if (modifier._animationDuration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._animationDuration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.animationDuration(modifier._animationDuration_0_0value);
                    break;
                }
                default: {
                    this.animationDuration((undefined as number | undefined));
                }
            }
        }
        if (modifier._animationMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._animationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.animationMode(modifier._animationMode_0_0value);
                    break;
                }
                default: {
                    this.animationMode((undefined as AnimationMode | undefined));
                }
            }
        }
        if (modifier._edgeEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._edgeEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.edgeEffect(modifier._edgeEffect_0_0value);
                    break;
                }
                default: {
                    this.edgeEffect((undefined as EdgeEffect | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onSelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelected(modifier._onSelected_0_0value);
                    break;
                }
                default: {
                    this.onSelected((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onTabBarClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTabBarClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTabBarClick(modifier._onTabBarClick_0_0value);
                    break;
                }
                default: {
                    this.onTabBarClick((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onUnselected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUnselected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUnselected(modifier._onUnselected_0_0value);
                    break;
                }
                default: {
                    this.onUnselected((undefined as ((value0: number) => void) | undefined));
                }
            }
        }
        if (modifier._onAnimationStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAnimationStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationStart(modifier._onAnimationStart_0_0value);
                    break;
                }
                default: {
                    this.onAnimationStart((undefined as OnTabsAnimationStartCallback | undefined));
                }
            }
        }
        if (modifier._onAnimationEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAnimationEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAnimationEnd(modifier._onAnimationEnd_0_0value);
                    break;
                }
                default: {
                    this.onAnimationEnd((undefined as OnTabsAnimationEndCallback | undefined));
                }
            }
        }
        if (modifier._onGestureSwipe_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGestureSwipe_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureSwipe(modifier._onGestureSwipe_0_0value);
                    break;
                }
                default: {
                    this.onGestureSwipe((undefined as OnTabsGestureSwipeCallback | undefined));
                }
            }
        }
        if (modifier._fadingEdge_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fadingEdge_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fadingEdge(modifier._fadingEdge_0_0value);
                    break;
                }
                default: {
                    this.fadingEdge((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._divider_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._divider_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.divider(modifier._divider_0_0value);
                    break;
                }
                default: {
                    this.divider((undefined as DividerStyle | undefined));
                }
            }
        }
        if (modifier._barOverlap_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barOverlap_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barOverlap(modifier._barOverlap_0_0value);
                    break;
                }
                default: {
                    this.barOverlap((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._barBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundColor(modifier._barBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._barGridAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barGridAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barGridAlign(modifier._barGridAlign_0_0value);
                    break;
                }
                default: {
                    this.barGridAlign((undefined as BarGridColumnOptions | undefined));
                }
            }
        }
        if (modifier._customContentTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customContentTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customContentTransition(modifier._customContentTransition_0_0value);
                    break;
                }
                default: {
                    this.customContentTransition((undefined as TabsCustomContentTransitionCallback | undefined));
                }
            }
        }
        if (modifier._barBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundBlurStyle(modifier._barBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (modifier._pageFlipMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pageFlipMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pageFlipMode(modifier._pageFlipMode_0_0value);
                    break;
                }
                default: {
                    this.pageFlipMode((undefined as PageFlipMode | undefined));
                }
            }
        }
        if (modifier._barBackgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barBackgroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundEffect(modifier._barBackgroundEffect_0_0value);
                    break;
                }
                default: {
                    this.barBackgroundEffect((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (modifier._onContentWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentWillChange(modifier._onContentWillChange_0_0value);
                    break;
                }
                default: {
                    this.onContentWillChange((undefined as OnTabsContentWillChangeCallback | undefined));
                }
            }
        }
        if (modifier._barMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barMode(modifier._barMode_0_0value, modifier._barMode_0_1value);
                    break;
                }
                default: {
                    this.barMode((undefined as BarMode | undefined), (undefined as ScrollableBarModeOptions | undefined | undefined));
                }
            }
        }
        if (modifier._barBackgroundBlurStyle_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._barBackgroundBlurStyle_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.barBackgroundBlurStyle(modifier._barBackgroundBlurStyle_1_0value, modifier._barBackgroundBlurStyle_1_1value);
                    break;
                }
                default: {
                    this.barBackgroundBlurStyle((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined));
                }
            }
        }
        if (modifier._cachedMaxCount_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cachedMaxCount_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cachedMaxCount(modifier._cachedMaxCount_0_0value, modifier._cachedMaxCount_0_1value);
                    break;
                }
                default: {
                    this.cachedMaxCount((undefined as number | undefined), (undefined as TabsCacheMode | undefined));
                }
            }
        }
    }
    vertical(value: boolean | undefined): this {
        if (((this._vertical_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._vertical_0_0value) !== (value)))
        {
            this._vertical_0_flag = AttributeUpdaterFlag.UPDATE
            this._vertical_0_0value = value
        } else
        {
            this._vertical_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barPosition(value: BarPosition | undefined): this {
        if (((this._barPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._barPosition_0_0value = value
        } else
        {
            this._barPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scrollable(value: boolean | undefined): this {
        if (((this._scrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._scrollable_0_0value) !== (value)))
        {
            this._scrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._scrollable_0_0value = value
        } else
        {
            this._scrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barWidth(value: Length | undefined): this {
        if (((this._barWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._barWidth_0_0value = value
        } else
        {
            this._barWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barHeight(value: Length | undefined): this {
        if (((this._barHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._barHeight_0_0value = value
        } else
        {
            this._barHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    animationDuration(value: number | undefined): this {
        if (((this._animationDuration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._animationDuration_0_0value) !== (value)))
        {
            this._animationDuration_0_flag = AttributeUpdaterFlag.UPDATE
            this._animationDuration_0_0value = value
        } else
        {
            this._animationDuration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    animationMode(value: AnimationMode | undefined): this {
        if (((this._animationMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._animationMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._animationMode_0_0value = value
        } else
        {
            this._animationMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    edgeEffect(value: EdgeEffect | undefined): this {
        if (((this._edgeEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._edgeEffect_0_0value = value
        } else
        {
            this._edgeEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: ((value0: number) => void) | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelected(value: ((value0: number) => void) | undefined): this {
        if (((this._onSelected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelected_0_0value = value
        } else
        {
            this._onSelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTabBarClick(value: ((value0: number) => void) | undefined): this {
        if (((this._onTabBarClick_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTabBarClick_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTabBarClick_0_0value = value
        } else
        {
            this._onTabBarClick_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUnselected(value: ((value0: number) => void) | undefined): this {
        if (((this._onUnselected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUnselected_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUnselected_0_0value = value
        } else
        {
            this._onUnselected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        if (((this._onAnimationStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationStart_0_0value = value
        } else
        {
            this._onAnimationStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        if (((this._onAnimationEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAnimationEnd_0_0value = value
        } else
        {
            this._onAnimationEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        if (((this._onGestureSwipe_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureSwipe_0_0value = value
        } else
        {
            this._onGestureSwipe_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fadingEdge(value: boolean | undefined): this {
        if (((this._fadingEdge_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fadingEdge_0_0value) !== (value)))
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.UPDATE
            this._fadingEdge_0_0value = value
        } else
        {
            this._fadingEdge_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    divider(value: DividerStyle | undefined): this {
        if (((this._divider_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._divider_0_flag = AttributeUpdaterFlag.UPDATE
            this._divider_0_0value = value
        } else
        {
            this._divider_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barOverlap(value: boolean | undefined): this {
        if (((this._barOverlap_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._barOverlap_0_0value) !== (value)))
        {
            this._barOverlap_0_flag = AttributeUpdaterFlag.UPDATE
            this._barOverlap_0_0value = value
        } else
        {
            this._barOverlap_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._barBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundColor_0_0value = value
        } else
        {
            this._barBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barGridAlign(value: BarGridColumnOptions | undefined): this {
        if (((this._barGridAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barGridAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._barGridAlign_0_0value = value
        } else
        {
            this._barGridAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        if (((this._customContentTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customContentTransition_0_0value = value
        } else
        {
            this._customContentTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._barBackgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundBlurStyle_0_0value = value
        } else
        {
            this._barBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        if (((this._pageFlipMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._pageFlipMode_0_0value = value
        } else
        {
            this._pageFlipMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        if (((this._barBackgroundEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundEffect_0_0value = value
        } else
        {
            this._barBackgroundEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        if (((this._onContentWillChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentWillChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentWillChange_0_0value = value
        } else
        {
            this._onContentWillChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        if (((this._barMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._barMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._barMode_0_0value = value
            this._barMode_0_1value = options
        } else
        {
            this._barMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        if (((this._barBackgroundBlurStyle_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.UPDATE
            this._barBackgroundBlurStyle_1_0value = style
            this._barBackgroundBlurStyle_1_1value = options
        } else
        {
            this._barBackgroundBlurStyle_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): this {
        if (((this._cachedMaxCount_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._cachedMaxCount_0_0value) !== (count)) || (true))
        {
            this._cachedMaxCount_0_flag = AttributeUpdaterFlag.UPDATE
            this._cachedMaxCount_0_0value = count
            this._cachedMaxCount_0_1value = mode
        } else
        {
            this._cachedMaxCount_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
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
        const valueHolderForCurrentOffset  = value.currentOffset
        valueSerializer.writeNumber(valueHolderForCurrentOffset)
        const valueHolderForTargetOffset  = value.targetOffset
        valueSerializer.writeNumber(valueHolderForTargetOffset)
        const valueHolderForVelocity  = value.velocity
        valueSerializer.writeNumber(valueHolderForVelocity)
    }
    public static read(buffer: DeserializerBase): TabsAnimationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const currentOffsetTmpResult : number = (valueDeserializer.readNumber() as number)
        const targetOffsetTmpResult : number = (valueDeserializer.readNumber() as number)
        const velocityTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : TabsAnimationEvent = ({currentOffset: currentOffsetTmpResult, targetOffset: targetOffsetTmpResult, velocity: velocityTmpResult} as TabsAnimationEvent)
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
        const valueHolderForTimeout  = value.timeout
        if (valueHolderForTimeout !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeoutTmpValue  = valueHolderForTimeout!
            valueSerializer.writeNumber(valueHolderForTimeoutTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        valueSerializer.holdAndWriteCallback(valueHolderForTransition)
    }
    public static read(buffer: DeserializerBase): TabContentAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const timeoutTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeoutTmpBuf : number | undefined
        if ((timeoutTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeoutTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const timeoutTmpResult : number | undefined = timeoutTmpBuf
        const transitionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const transitionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const transitionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const transitionTmpResult : ((value0: TabContentTransitionProxy) => void) = (value0: TabContentTransitionProxy):void => {
            const transitionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            transitionTmpBufBufArgsSerializer.writeInt32(transitionTmpBufBufResource.resourceId);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCall);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCallSync);
            TabContentTransitionProxy_serializer.write(transitionTmpBufBufArgsSerializer, value0);
            InteropNativeModule._CallCallback(-1223938478, transitionTmpBufBufArgsSerializer.asBuffer(), transitionTmpBufBufArgsSerializer.length());
            transitionTmpBufBufArgsSerializer.release();
            return;
        }
        let value : TabContentAnimatedTransition = ({timeout: timeoutTmpResult, transition: transitionTmpResult} as TabContentAnimatedTransition)
        return value
    }
}
export class TabsOptions_serializer {
    public static write(buffer: SerializerBase, value: TabsOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBarPosition  = value.barPosition
        if (valueHolderForBarPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBarPositionTmpValue  = (valueHolderForBarPosition as BarPosition)
            valueSerializer.writeInt32(TypeChecker.BarPosition_ToNumeric(valueHolderForBarPositionTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndex  = value.index
        if (valueHolderForIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndexTmpValue  = valueHolderForIndex!
            if (valueHolderForIndexTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForIndexTmpValueForIdx0  = valueHolderForIndexTmpValue as number
                valueSerializer.writeNumber(valueHolderForIndexTmpValueForIdx0)
            } else if (valueHolderForIndexTmpValue instanceof Bindable<number>) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForIndexTmpValueForIdx1  = valueHolderForIndexTmpValue as Bindable<number>
                Bindable_Number_serializer.write(valueSerializer, valueHolderForIndexTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            TabsController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabsOptions {
        let valueDeserializer : DeserializerBase = buffer
        const barPositionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let barPositionTmpBuf : BarPosition | undefined
        if ((barPositionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            barPositionTmpBuf = TypeChecker.BarPosition_FromNumeric(valueDeserializer.readInt32())
        }
        const barPositionTmpResult : BarPosition | undefined = barPositionTmpBuf
        const indexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indexTmpBuf : number | Bindable<number> | undefined
        if ((indexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indexTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let indexTmpBuf_ : number | Bindable<number> | undefined
            if (indexTmpBuf_UnionSelector == (0).toChar()) {
                indexTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (indexTmpBuf_UnionSelector == (1).toChar()) {
                indexTmpBuf_ = Bindable_Number_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for indexTmpBuf_ has to be chosen through deserialisation.")
            }
            indexTmpBuf = (indexTmpBuf_ as number | Bindable<number>)
        }
        const indexTmpResult : number | Bindable<number> | undefined = indexTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controllerTmpBuf : TabsController | undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (TabsController_serializer.read(valueDeserializer) as TabsController)
        }
        const controllerTmpResult : TabsController | undefined = controllerTmpBuf
        let value : TabsOptions = ({barPosition: barPositionTmpResult, index: indexTmpResult, controller: controllerTmpResult} as TabsOptions)
        return value
    }
}
export class BarGridColumnOptions_serializer {
    public static write(buffer: SerializerBase, value: BarGridColumnOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSm  = value.sm
        if (valueHolderForSm !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSmTmpValue  = valueHolderForSm!
            valueSerializer.writeNumber(valueHolderForSmTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMd  = value.md
        if (valueHolderForMd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMdTmpValue  = valueHolderForMd!
            valueSerializer.writeNumber(valueHolderForMdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLg  = value.lg
        if (valueHolderForLg !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLgTmpValue  = valueHolderForLg!
            valueSerializer.writeNumber(valueHolderForLgTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            if (valueHolderForMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as string
                valueSerializer.writeString(valueHolderForMarginTmpValueForIdx0)
            } else if (valueHolderForMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForMarginTmpValueForIdx1)
            } else if (valueHolderForMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForMarginTmpValueForIdx2  = valueHolderForMarginTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGutter  = value.gutter
        if (valueHolderForGutter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGutterTmpValue  = valueHolderForGutter!
            if (valueHolderForGutterTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForGutterTmpValueForIdx0  = valueHolderForGutterTmpValue as string
                valueSerializer.writeString(valueHolderForGutterTmpValueForIdx0)
            } else if (valueHolderForGutterTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForGutterTmpValueForIdx1  = valueHolderForGutterTmpValue as number
                valueSerializer.writeNumber(valueHolderForGutterTmpValueForIdx1)
            } else if (valueHolderForGutterTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForGutterTmpValueForIdx2  = valueHolderForGutterTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForGutterTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BarGridColumnOptions {
        let valueDeserializer : DeserializerBase = buffer
        const smTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let smTmpBuf : number | undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            smTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const smTmpResult : number | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mdTmpBuf : number | undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mdTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const mdTmpResult : number | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lgTmpBuf : number | undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lgTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const lgTmpResult : number | undefined = lgTmpBuf
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTmpBuf : Dimension | undefined
        if ((marginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let marginTmpBuf_ : string | number | Resource | undefined
            if (marginTmpBuf_UnionSelector == (0).toChar()) {
                marginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (marginTmpBuf_UnionSelector == (1).toChar()) {
                marginTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (marginTmpBuf_UnionSelector == (2).toChar()) {
                marginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for marginTmpBuf_ has to be chosen through deserialisation.")
            }
            marginTmpBuf = (marginTmpBuf_ as string | number | Resource)
        }
        const marginTmpResult : Dimension | undefined = marginTmpBuf
        const gutterTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gutterTmpBuf : Dimension | undefined
        if ((gutterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const gutterTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let gutterTmpBuf_ : string | number | Resource | undefined
            if (gutterTmpBuf_UnionSelector == (0).toChar()) {
                gutterTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (gutterTmpBuf_UnionSelector == (1).toChar()) {
                gutterTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (gutterTmpBuf_UnionSelector == (2).toChar()) {
                gutterTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for gutterTmpBuf_ has to be chosen through deserialisation.")
            }
            gutterTmpBuf = (gutterTmpBuf_ as string | number | Resource)
        }
        const gutterTmpResult : Dimension | undefined = gutterTmpBuf
        let value : BarGridColumnOptions = ({sm: smTmpResult, md: mdTmpResult, lg: lgTmpResult, margin: marginTmpResult, gutter: gutterTmpResult} as BarGridColumnOptions)
        return value
    }
}
export class ScrollableBarModeOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollableBarModeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            if (valueHolderForMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as string
                valueSerializer.writeString(valueHolderForMarginTmpValueForIdx0)
            } else if (valueHolderForMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForMarginTmpValueForIdx1)
            } else if (valueHolderForMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForMarginTmpValueForIdx2  = valueHolderForMarginTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNonScrollableLayoutStyle  = value.nonScrollableLayoutStyle
        if (valueHolderForNonScrollableLayoutStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNonScrollableLayoutStyleTmpValue  = (valueHolderForNonScrollableLayoutStyle as LayoutStyle)
            valueSerializer.writeInt32(TypeChecker.LayoutStyle_ToNumeric(valueHolderForNonScrollableLayoutStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollableBarModeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTmpBuf : Dimension | undefined
        if ((marginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let marginTmpBuf_ : string | number | Resource | undefined
            if (marginTmpBuf_UnionSelector == (0).toChar()) {
                marginTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (marginTmpBuf_UnionSelector == (1).toChar()) {
                marginTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (marginTmpBuf_UnionSelector == (2).toChar()) {
                marginTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for marginTmpBuf_ has to be chosen through deserialisation.")
            }
            marginTmpBuf = (marginTmpBuf_ as string | number | Resource)
        }
        const marginTmpResult : Dimension | undefined = marginTmpBuf
        const nonScrollableLayoutStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nonScrollableLayoutStyleTmpBuf : LayoutStyle | undefined
        if ((nonScrollableLayoutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nonScrollableLayoutStyleTmpBuf = TypeChecker.LayoutStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const nonScrollableLayoutStyleTmpResult : LayoutStyle | undefined = nonScrollableLayoutStyleTmpBuf
        let value : ScrollableBarModeOptions = ({margin: marginTmpResult, nonScrollableLayoutStyle: nonScrollableLayoutStyleTmpResult} as ScrollableBarModeOptions)
        return value
    }
}
