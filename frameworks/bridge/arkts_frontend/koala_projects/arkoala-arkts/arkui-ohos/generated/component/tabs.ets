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
import { TranslateOptions_serializer, TranslateOptions, DividerStyle_serializer, BackgroundEffectOptions_serializer, BackgroundBlurStyleOptions_serializer, ArkCommonMethodPeer, CommonMethod, DividerStyle, BlurStyle, BackgroundEffectOptions, BackgroundBlurStyleOptions, BlurStyleOptions, BlurStyleActivePolicy, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, Bindable_I32_serializer } from "./common"
import { Resource_serializer } from "./../framework/resource"
import { curves_ICurve_serializer } from "./../framework/ohos.curves"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Length, ResourceColor, Dimension } from "./units"
import { Resource } from "global.resource"
import { EdgeEffect, Color, PageFlipMode } from "./enums"
import { default as curves } from "@ohos.curves"
import { extractors, AttributeModifier, hookTabsAttributeModifier, AttributeUpdater, hookTabsApplyAttributesFinish } from "#handwritten"
import { TabsExtender } from '#generated'
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { TabsModifier } from "./../TabsModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { KInt32ArrayPtr } from "@koalaui/interop"
export interface TabContentTransitionProxy {
    from: int32
    to: int32
    finishTransition(): void
}
export class TabContentTransitionProxyInternal implements MaterializedBase,TabContentTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get from(): int32 {
        return this.getFrom()
    }
    set from(from: int32) {
        this.setFrom(from)
    }
    get to(): int32 {
        return this.getTo()
    }
    set to(to: int32) {
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
    private getFrom(): int32 {
        return this.getFrom_serialize()
    }
    private setFrom(from: int32): void {
        const from_casted = from as (int32)
        this.setFrom_serialize(from_casted)
        return
    }
    private getTo(): int32 {
        return this.getTo_serialize()
    }
    private setTo(to: int32): void {
        const to_casted = to as (int32)
        this.setTo_serialize(to_casted)
        return
    }
    finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getFrom_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFrom(this.peer!.ptr)
        return retval
    }
    private setFrom_serialize(from: int32): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setFrom(this.peer!.ptr, from)
    }
    private getTo_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getTo(this.peer!.ptr)
        return retval
    }
    private setTo_serialize(to: int32): void {
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
    public changeIndex(value: int32): void {
        const value_casted = value as (int32)
        this.changeIndex_serialize(value_casted)
        return
    }
    public preloadItems(indices: KInt32ArrayPtr | undefined): Promise<void> {
        const indices_casted = indices as (KInt32ArrayPtr | undefined)
        return this.preloadItems_serialize(indices_casted)
    }
    public setTabBarTranslate(translate: TranslateOptions): void {
        const translate_casted = translate as (TranslateOptions)
        this.setTabBarTranslate_serialize(translate_casted)
        return
    }
    public setTabBarOpacity(opacity: double): void {
        const opacity_casted = opacity as (double)
        this.setTabBarOpacity_serialize(opacity_casted)
        return
    }
    changeIndex_serialize(value: int32): void {
        ArkUIGeneratedNativeModule._TabsController_changeIndex(this.peer!.ptr, value)
    }
    preloadItems_serialize(indices: KInt32ArrayPtr | undefined): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (indices !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const indicesTmpValue  = indices!
            thisSerializer.writeInt32((indicesTmpValue.length).toInt())
            for (let indicesTmpValueCounterI = 0; indicesTmpValueCounterI < indicesTmpValue.length; indicesTmpValueCounterI++) {
                const indicesTmpValueTmpElement : int32 = indicesTmpValue[indicesTmpValueCounterI]
                thisSerializer.writeInt32(indicesTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._TabsController_preloadItems(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    setTabBarTranslate_serialize(translate: TranslateOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TranslateOptions_serializer.write(thisSerializer, translate)
        ArkUIGeneratedNativeModule._TabsController_setTabBarTranslate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTabBarOpacity_serialize(opacity: double): void {
        ArkUIGeneratedNativeModule._TabsController_setTabBarOpacity(this.peer!.ptr, opacity)
    }
}
export class ArkTabsPeer extends ArkCommonMethodPeer {
    attributeSet?: TabsModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnimationCurveAttribute(value: curves.Curve | curves.ICurve | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof curves.Curve) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as curves.Curve
                thisSerializer.writeInt32(valueTmpValueForIdx0.valueOf())
            } else if (valueTmpValue instanceof curves.ICurve) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as curves.ICurve
                curves_ICurve_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setAnimationCurve(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAnimationDurationAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: int32) => void) | undefined): void {
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
    setOnSelectedAttribute(value: ((value0: int32) => void) | undefined): void {
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
    setOnTabBarClickAttribute(value: ((value0: int32) => void) | undefined): void {
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
    setOnUnselectedAttribute(value: ((value0: int32) => void) | undefined): void {
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
    setDividerAttribute(value: DividerStyle | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setOnContentDidScrollAttribute(value: OnTabsContentDidScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setOnContentDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarModeAttribute(value: BarMode | undefined, options?: ScrollableBarModeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BarMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setBarHeightAttribute(height: Length | undefined, noMinHeightLimit: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (height !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const heightTmpValue  = height!
            if (heightTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const heightTmpValueForIdx0  = heightTmpValue as string
                thisSerializer.writeString(heightTmpValueForIdx0)
            } else if (heightTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const heightTmpValueForIdx1  = heightTmpValue as number
                thisSerializer.writeNumber(heightTmpValueForIdx1)
            } else if (heightTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const heightTmpValueForIdx2  = heightTmpValue as Resource
                Resource_serializer.write(thisSerializer, heightTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (noMinHeightLimit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const noMinHeightLimitTmpValue  = noMinHeightLimit!
            thisSerializer.writeBoolean(noMinHeightLimitTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabsAttribute_setBarHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarBackgroundBlurStyle1Attribute(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue  = (style as BlurStyle)
            thisSerializer.writeInt32(styleTmpValue.valueOf())
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
    setCachedMaxCountAttribute(count: int32 | undefined, mode: TabsCacheMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeInt32(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (mode !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const modeTmpValue  = (mode as TabsCacheMode)
            thisSerializer.writeInt32(modeTmpValue.valueOf())
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
    index?: int32 | Bindable<int32>;
    controller?: TabsController;
}
export interface TabsAnimationEvent {
    currentOffset: double;
    targetOffset: double;
    velocity: double;
}
export interface BarGridColumnOptions {
    sm?: int32;
    md?: int32;
    lg?: int32;
    margin?: Dimension;
    gutter?: Dimension;
}
export interface ScrollableBarModeOptions {
    margin?: Dimension;
    nonScrollableLayoutStyle?: LayoutStyle;
}
export type OnTabsAnimationStartCallback = (index: int32, targetIndex: int32, extraInfo: TabsAnimationEvent) => void;
export type OnTabsAnimationEndCallback = (index: int32, extraInfo: TabsAnimationEvent) => void;
export type OnTabsGestureSwipeCallback = (index: int32, extraInfo: TabsAnimationEvent) => void;
export type TabsCustomContentTransitionCallback = (from: int32, to: int32) => TabContentAnimatedTransition | undefined;
export type OnTabsContentWillChangeCallback = (currentIndex: int32, comingIndex: int32) => boolean;
export type OnTabsContentDidScrollCallback = (selectedIndex: int32, index: int32, position: double, mainAxisLength: double) => void;
export interface TabsAttribute extends CommonMethod {
    setTabsOptions(options?: TabsOptions): this {
        throw new Error("Unimplemented method setTabsOptions")
    }
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
    animationCurve(value: curves.Curve | curves.ICurve | undefined): this {
        throw new Error("Unimplemented method animationCurve")
    }
    animationDuration(value: int32 | undefined): this {
        throw new Error("Unimplemented method animationDuration")
    }
    animationMode(value: AnimationMode | undefined): this {
        throw new Error("Unimplemented method animationMode")
    }
    edgeEffect(value: EdgeEffect | undefined): this {
        throw new Error("Unimplemented method edgeEffect")
    }
    onChange(value: ((value0: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onSelected(value: ((value0: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onSelected")
    }
    onTabBarClick(value: ((value0: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onTabBarClick")
    }
    onUnselected(value: ((value0: int32) => void) | undefined): this {
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
    divider(value: DividerStyle | null | undefined): this {
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
    onContentDidScroll(value: OnTabsContentDidScrollCallback | undefined): this {
        throw new Error("Unimplemented method onContentDidScroll")
    }
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        throw new Error("Unimplemented method barMode")
    }
    barHeight(height: Length | undefined, noMinHeightLimit: boolean | undefined): this {
        throw new Error("Unimplemented method barHeight")
    }
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        throw new Error("Unimplemented method barBackgroundBlurStyle")
    }
    cachedMaxCount(count: int32 | undefined, mode: TabsCacheMode | undefined): this {
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
    animationDuration_value?: int32 | undefined
    animationMode_value?: AnimationMode | undefined
    edgeEffect_value?: EdgeEffect | undefined
    onChange_value?: ((value0: int32) => void) | undefined
    onSelected_value?: ((value0: int32) => void) | undefined
    onTabBarClick_value?: ((value0: int32) => void) | undefined
    onUnselected_value?: ((value0: int32) => void) | undefined
    onAnimationStart_value?: OnTabsAnimationStartCallback | undefined
    onAnimationEnd_value?: OnTabsAnimationEndCallback | undefined
    onGestureSwipe_value?: OnTabsGestureSwipeCallback | undefined
    fadingEdge_value?: boolean | undefined
    divider_value?: DividerStyle | null | undefined
    barOverlap_value?: boolean | undefined
    barBackgroundColor_value?: ResourceColor | undefined
    barGridAlign_value?: BarGridColumnOptions | undefined
    customContentTransition_value?: TabsCustomContentTransitionCallback | undefined
    barBackgroundBlurStyle_value?: BlurStyle | undefined
    pageFlipMode_value?: PageFlipMode | undefined
    barBackgroundEffect_value?: BackgroundEffectOptions | undefined
    onContentWillChange_value?: OnTabsContentWillChangeCallback | undefined
    attributeModifier_value?: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined
    onContentDidScroll_value?: OnTabsContentDidScrollCallback | undefined
    setTabsOptions(options?: TabsOptions): this {
        return this
    }
    vertical(value: boolean | undefined): this {
        return this
    }
    barPosition(value: BarPosition | undefined): this {
        return this
    }
    scrollable(value: boolean | undefined): this {
        return this
    }
    barWidth(value: Length | undefined): this {
        return this
    }
    animationCurve(value: curves.Curve | curves.ICurve | undefined): this {
        return this
    }
    animationDuration(value: int32 | undefined): this {
        return this
    }
    animationMode(value: AnimationMode | undefined): this {
        return this
    }
    edgeEffect(value: EdgeEffect | undefined): this {
        return this
    }
    onChange(value: ((value0: int32) => void) | undefined): this {
        return this
    }
    onSelected(value: ((value0: int32) => void) | undefined): this {
        return this
    }
    onTabBarClick(value: ((value0: int32) => void) | undefined): this {
        return this
    }
    onUnselected(value: ((value0: int32) => void) | undefined): this {
        return this
    }
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): this {
        return this
    }
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): this {
        return this
    }
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): this {
        return this
    }
    fadingEdge(value: boolean | undefined): this {
        return this
    }
    divider(value: DividerStyle | null | undefined): this {
        return this
    }
    barOverlap(value: boolean | undefined): this {
        return this
    }
    barBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    barGridAlign(value: BarGridColumnOptions | undefined): this {
        return this
    }
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): this {
        return this
    }
    barBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    pageFlipMode(value: PageFlipMode | undefined): this {
        return this
    }
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): this {
        return this
    }
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): this {
        return this
    }
    onContentDidScroll(value: OnTabsContentDidScrollCallback | undefined): this {
        return this
    }
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions): this {
        return this
    }
    barHeight(height: Length | undefined, noMinHeightLimit: boolean | undefined): this {
        return this
    }
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): this {
        return this
    }
    cachedMaxCount(count: int32 | undefined, mode: TabsCacheMode | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface TabContentAnimatedTransition {
    timeout?: int32;
    transition: ((value0: TabContentTransitionProxy) => void);
}

export class ArkTabsComponent extends ArkCommonMethodComponent implements TabsAttribute {
    getPeer(): ArkTabsPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
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
    public animationCurve(value: curves.Curve | curves.ICurve | undefined): this {
        if (this.checkPriority("animationCurve")) {
            const value_casted = value as (curves.Curve | curves.ICurve | undefined)
            this.getPeer()?.setAnimationCurveAttribute(value_casted)
            return this
        }
        return this
    }
    public animationDuration(value: int32 | undefined): this {
        if (this.checkPriority("animationDuration")) {
            const value_casted = value as (int32 | undefined)
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
    public onChange(value: ((value0: int32) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: int32) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelected(value: ((value0: int32) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((value0: int32) => void) | undefined)
            this.getPeer()?.setOnSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public onTabBarClick(value: ((value0: int32) => void) | undefined): this {
        if (this.checkPriority("onTabBarClick")) {
            const value_casted = value as (((value0: int32) => void) | undefined)
            this.getPeer()?.setOnTabBarClickAttribute(value_casted)
            return this
        }
        return this
    }
    public onUnselected(value: ((value0: int32) => void) | undefined): this {
        if (this.checkPriority("onUnselected")) {
            const value_casted = value as (((value0: int32) => void) | undefined)
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
    public divider(value: DividerStyle | null | undefined): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (DividerStyle | null | undefined)
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
    public onContentDidScroll(value: OnTabsContentDidScrollCallback | undefined): this {
        if (this.checkPriority("onContentDidScroll")) {
            const value_casted = value as (OnTabsContentDidScrollCallback | undefined)
            this.getPeer()?.setOnContentDidScrollAttribute(value_casted)
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
    public barHeight(height: Length | undefined, noMinHeightLimit: boolean | undefined): this {
        if (this.checkPriority("barHeight")) {
            const height_casted = height as (Length | undefined)
            const noMinHeightLimit_casted = noMinHeightLimit as (boolean | undefined)
            this.getPeer()?.setBarHeightAttribute(height_casted, noMinHeightLimit_casted)
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
    public cachedMaxCount(count: int32 | undefined, mode: TabsCacheMode | undefined): this {
        if (this.checkPriority("cachedMaxCount")) {
            const count_casted = count as (int32 | undefined)
            const mode_casted = mode as (TabsCacheMode | undefined)
            this.getPeer()?.setCachedMaxCountAttribute(count_casted, mode_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookTabsAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        hookTabsApplyAttributesFinish(this)
        super.applyAttributesFinish()
    }
}

@memo
export function TabsImpl(
    @memo
    style: ((attributes: TabsAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTabsComponent>((): ArkTabsComponent => {
        return new ArkTabsComponent()
    })
    NodeAttach<ArkTabsPeer>((): ArkTabsPeer => ArkTabsPeer.create(receiver), (peer: ArkTabsPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
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
        const valueHolderForCurrentOffset  = value.currentOffset
        valueSerializer.writeFloat64(valueHolderForCurrentOffset)
        const valueHolderForTargetOffset  = value.targetOffset
        valueSerializer.writeFloat64(valueHolderForTargetOffset)
        const valueHolderForVelocity  = value.velocity
        valueSerializer.writeFloat64(valueHolderForVelocity)
    }
    public static read(buffer: DeserializerBase): TabsAnimationEvent {
        let valueDeserializer : DeserializerBase = buffer
        const currentOffsetTmpResult : double = valueDeserializer.readFloat64()
        const targetOffsetTmpResult : double = valueDeserializer.readFloat64()
        const velocityTmpResult : double = valueDeserializer.readFloat64()
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
            valueSerializer.writeInt32(valueHolderForTimeoutTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        valueSerializer.holdAndWriteCallback(valueHolderForTransition)
    }
    public static read(buffer: DeserializerBase): TabContentAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const timeoutTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeoutTmpBuf : int32 | undefined = undefined
        if ((timeoutTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeoutTmpBuf = valueDeserializer.readInt32()
        }
        const timeoutTmpResult : int32 | undefined = timeoutTmpBuf
        const transitionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const transitionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const transitionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const transitionTmpResult : ((value0: TabContentTransitionProxy) => void) = (value0: TabContentTransitionProxy):void => {
            const transitionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            transitionTmpBufBufArgsSerializer.writeInt32(transitionTmpBufBufResource.resourceId);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCall);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCallSync);
            TabContentTransitionProxy_serializer.write(transitionTmpBufBufArgsSerializer, value0);
            InteropNativeModule._CallCallbackSync(10, -1223938478, transitionTmpBufBufArgsSerializer.asBuffer(), transitionTmpBufBufArgsSerializer.length());
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
            valueSerializer.writeInt32(valueHolderForBarPositionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndex  = value.index
        if (valueHolderForIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndexTmpValue  = valueHolderForIndex!
            if (valueHolderForIndexTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIndexTmpValueForIdx0  = valueHolderForIndexTmpValue as int32
                valueSerializer.writeInt32(valueHolderForIndexTmpValueForIdx0)
            } else if (valueHolderForIndexTmpValue instanceof Bindable<int32>) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIndexTmpValueForIdx1  = valueHolderForIndexTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(valueSerializer, valueHolderForIndexTmpValueForIdx1)
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
        let barPositionTmpBuf : BarPosition | undefined = undefined
        if ((barPositionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            barPositionTmpBuf = BarPosition.fromValue(valueDeserializer.readInt32())
        }
        const barPositionTmpResult : BarPosition | undefined = barPositionTmpBuf
        const indexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indexTmpBuf : int32 | Bindable<int32> | undefined = undefined
        if ((indexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indexTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let indexTmpBuf_ : int32 | Bindable<int32> | undefined
            if (indexTmpBuf_UnionSelector == (0).toChar()) {
                indexTmpBuf_ = valueDeserializer.readInt32()
            } else if (indexTmpBuf_UnionSelector == (1).toChar()) {
                indexTmpBuf_ = Bindable_I32_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for indexTmpBuf_ has to be chosen through deserialisation.")
            }
            indexTmpBuf = (indexTmpBuf_ as int32 | Bindable<int32>)
        }
        const indexTmpResult : int32 | Bindable<int32> | undefined = indexTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controllerTmpBuf : TabsController | undefined = undefined
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
            valueSerializer.writeInt32(valueHolderForSmTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMd  = value.md
        if (valueHolderForMd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMdTmpValue  = valueHolderForMd!
            valueSerializer.writeInt32(valueHolderForMdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLg  = value.lg
        if (valueHolderForLg !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLgTmpValue  = valueHolderForLg!
            valueSerializer.writeInt32(valueHolderForLgTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            if (valueHolderForMarginTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as string
                valueSerializer.writeString(valueHolderForMarginTmpValueForIdx0)
            } else if (valueHolderForMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForMarginTmpValueForIdx1)
            } else if (valueHolderForMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForGutterTmpValueForIdx0  = valueHolderForGutterTmpValue as string
                valueSerializer.writeString(valueHolderForGutterTmpValueForIdx0)
            } else if (valueHolderForGutterTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForGutterTmpValueForIdx1  = valueHolderForGutterTmpValue as number
                valueSerializer.writeNumber(valueHolderForGutterTmpValueForIdx1)
            } else if (valueHolderForGutterTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
        let smTmpBuf : int32 | undefined = undefined
        if ((smTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            smTmpBuf = valueDeserializer.readInt32()
        }
        const smTmpResult : int32 | undefined = smTmpBuf
        const mdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mdTmpBuf : int32 | undefined = undefined
        if ((mdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mdTmpBuf = valueDeserializer.readInt32()
        }
        const mdTmpResult : int32 | undefined = mdTmpBuf
        const lgTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lgTmpBuf : int32 | undefined = undefined
        if ((lgTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lgTmpBuf = valueDeserializer.readInt32()
        }
        const lgTmpResult : int32 | undefined = lgTmpBuf
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTmpBuf : Dimension | undefined = undefined
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
        let gutterTmpBuf : Dimension | undefined = undefined
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as string
                valueSerializer.writeString(valueHolderForMarginTmpValueForIdx0)
            } else if (valueHolderForMarginTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as number
                valueSerializer.writeNumber(valueHolderForMarginTmpValueForIdx1)
            } else if (valueHolderForMarginTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
            valueSerializer.writeInt32(valueHolderForNonScrollableLayoutStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollableBarModeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTmpBuf : Dimension | undefined = undefined
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
        let nonScrollableLayoutStyleTmpBuf : LayoutStyle | undefined = undefined
        if ((nonScrollableLayoutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nonScrollableLayoutStyleTmpBuf = LayoutStyle.fromValue(valueDeserializer.readInt32())
        }
        const nonScrollableLayoutStyleTmpResult : LayoutStyle | undefined = nonScrollableLayoutStyleTmpBuf
        let value : ScrollableBarModeOptions = ({margin: marginTmpResult, nonScrollableLayoutStyle: nonScrollableLayoutStyleTmpResult} as ScrollableBarModeOptions)
        return value
    }
}
