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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceStr } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
import { CustomBuilder } from "./builder"
import { ComponentContent, ComponentContent_serializer } from "./../generated/arkui.ComponentContent"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRefreshPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRefreshPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Refresh_construct(peerId, flags)
        const _peer  = new ArkRefreshPeer(_peerPtr, peerId, "Refresh", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRefreshOptionsAttribute(value: RefreshOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RefreshOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RefreshInterface_setRefreshOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnStateChangeAttribute(value: ((state: RefreshStatus) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setOnStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRefreshingAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setOnRefreshing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRefreshOffsetAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setRefreshOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPullToRefreshAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setPullToRefresh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnOffsetChangeAttribute(value: ((value0: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setOnOffsetChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPullDownRatioAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_setPullDownRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_refreshingAttribute(callback_: ((refreshing: boolean) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._RefreshAttribute_set_onChangeEvent_refreshing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum RefreshStatus {
    INACTIVE = 0,
    Inactive = 0,
    DRAG = 1,
    Drag = 1,
    OVER_DRAG = 2,
    OverDrag = 2,
    REFRESH = 3,
    Refresh = 3,
    DONE = 4,
    Done = 4
}
export interface RefreshOptions {
    refreshing: boolean;
    promptText?: ResourceStr;
    builder?: CustomBuilder;
    refreshingContent?: ComponentContent;
}
export interface RefreshAttribute extends CommonMethod {
    onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        throw new Error("Unimplemented method onStateChange")
    }
    onRefreshing(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onRefreshing")
    }
    refreshOffset(value: number | undefined): this {
        throw new Error("Unimplemented method refreshOffset")
    }
    pullToRefresh(value: boolean | undefined): this {
        throw new Error("Unimplemented method pullToRefresh")
    }
    onOffsetChange(value: ((value0: number) => void) | undefined): this {
        throw new Error("Unimplemented method onOffsetChange")
    }
    pullDownRatio(value: number | undefined): this {
        throw new Error("Unimplemented method pullDownRatio")
    }
    _onChangeEvent_refreshing(callback_: ((refreshing: boolean) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_refreshing")
    }
    attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRefreshStyle extends ArkCommonMethodStyle implements RefreshAttribute {
    onStateChange_value?: ((state: RefreshStatus) => void) | undefined
    onRefreshing_value?: (() => void) | undefined
    refreshOffset_value?: number | undefined
    pullToRefresh_value?: boolean | undefined
    onOffsetChange_value?: ((value0: number) => void) | undefined
    pullDownRatio_value?: number | undefined
    attributeModifier_value?: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined
    public onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        return this
    }
    public onRefreshing(value: (() => void) | undefined): this {
        return this
    }
    public refreshOffset(value: number | undefined): this {
        return this
    }
    public pullToRefresh(value: boolean | undefined): this {
        return this
    }
    public onOffsetChange(value: ((value0: number) => void) | undefined): this {
        return this
    }
    public pullDownRatio(value: number | undefined): this {
        return this
    }
    public _onChangeEvent_refreshing(callback_: ((refreshing: boolean) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RefreshAttribute): void {
        super.apply(target)
        if (this.onStateChange_value !== undefined)
            target.onStateChange(this.onStateChange_value!)
        if (this.onRefreshing_value !== undefined)
            target.onRefreshing(this.onRefreshing_value!)
        if (this.refreshOffset_value !== undefined)
            target.refreshOffset(this.refreshOffset_value!)
        if (this.pullToRefresh_value !== undefined)
            target.pullToRefresh(this.pullToRefresh_value!)
        if (this.onOffsetChange_value !== undefined)
            target.onOffsetChange(this.onOffsetChange_value!)
        if (this.pullDownRatio_value !== undefined)
            target.pullDownRatio(this.pullDownRatio_value!)
    }
}

export class ArkRefreshComponent extends ArkCommonMethodComponent implements RefreshAttribute {
    getPeer(): ArkRefreshPeer {
        return (this.peer as ArkRefreshPeer)
    }
    public setRefreshOptions(value: RefreshOptions): this {
        if (this.checkPriority("setRefreshOptions")) {
            const value_casted = value as (RefreshOptions)
            this.getPeer()?.setRefreshOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        if (this.checkPriority("onStateChange")) {
            const value_casted = value as (((state: RefreshStatus) => void) | undefined)
            this.getPeer()?.setOnStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onRefreshing(value: (() => void) | undefined): this {
        if (this.checkPriority("onRefreshing")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnRefreshingAttribute(value_casted)
            return this
        }
        return this
    }
    public refreshOffset(value: number | undefined): this {
        if (this.checkPriority("refreshOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setRefreshOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public pullToRefresh(value: boolean | undefined): this {
        if (this.checkPriority("pullToRefresh")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPullToRefreshAttribute(value_casted)
            return this
        }
        return this
    }
    public onOffsetChange(value: ((value0: number) => void) | undefined): this {
        if (this.checkPriority("onOffsetChange")) {
            const value_casted = value as (((value0: number) => void) | undefined)
            this.getPeer()?.setOnOffsetChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public pullDownRatio(value: number | undefined): this {
        if (this.checkPriority("pullDownRatio")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setPullDownRatioAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_refreshing(callback_: ((refreshing: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_refreshing")) {
            const callback__casted = callback_ as (((refreshing: boolean) => void))
            this.getPeer()?.set_onChangeEvent_refreshingAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRefreshStyle(receiver: RefreshAttribute, modifier: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRefreshStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Refresh")
// export function Refresh(
//     value: RefreshOptions,
//     @memo
//     content_?: () => void,
// ): RefreshAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Refresh(
    @memo
    style: ((attributes: RefreshAttribute) => void) | undefined,
    value: RefreshOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRefreshComponent>((): ArkRefreshComponent => {
        return new ArkRefreshComponent()
    })
    NodeAttach<ArkRefreshPeer>((): ArkRefreshPeer => ArkRefreshPeer.create(receiver), (_: ArkRefreshPeer): void => {
        receiver.setRefreshOptions(value)
        style?.(receiver)
        withRefreshStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRefreshSet extends ArkCommonMethodSet implements RefreshAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onStateChange_flag?: boolean
    _onStateChange0_value?: ((state: RefreshStatus) => void) | undefined
    _onRefreshing_flag?: boolean
    _onRefreshing0_value?: (() => void) | undefined
    _refreshOffset_flag?: boolean
    _refreshOffset0_value?: number | undefined
    _pullToRefresh_flag?: boolean
    _pullToRefresh0_value?: boolean | undefined
    _onOffsetChange_flag?: boolean
    _onOffsetChange0_value?: ((value0: number) => void) | undefined
    _pullDownRatio_flag?: boolean
    _pullDownRatio0_value?: number | undefined
    __onChangeEvent_refreshing_flag?: boolean
    __onChangeEvent_refreshing0_value?: ((refreshing: boolean) => void)
    applyModifierPatch(component: RefreshAttribute): void {
        if (this._onStateChange_flag)
            component.onStateChange((this._onStateChange0_value as ((state: RefreshStatus) => void) | undefined))
        if (this._onRefreshing_flag)
            component.onRefreshing((this._onRefreshing0_value as (() => void) | undefined))
        if (this._refreshOffset_flag)
            component.refreshOffset((this._refreshOffset0_value as number | undefined))
        if (this._pullToRefresh_flag)
            component.pullToRefresh((this._pullToRefresh0_value as boolean | undefined))
        if (this._onOffsetChange_flag)
            component.onOffsetChange((this._onOffsetChange0_value as ((value0: number) => void) | undefined))
        if (this._pullDownRatio_flag)
            component.pullDownRatio((this._pullDownRatio0_value as number | undefined))
    }
    public onStateChange(value: ((state: RefreshStatus) => void) | undefined): this {
        this._onStateChange_flag = true
        this._onStateChange0_value = value
        return this
    }
    public onRefreshing(value: (() => void) | undefined): this {
        this._onRefreshing_flag = true
        this._onRefreshing0_value = value
        return this
    }
    public refreshOffset(value: number | undefined): this {
        this._refreshOffset_flag = true
        this._refreshOffset0_value = value
        return this
    }
    public pullToRefresh(value: boolean | undefined): this {
        this._pullToRefresh_flag = true
        this._pullToRefresh0_value = value
        return this
    }
    public onOffsetChange(value: ((value0: number) => void) | undefined): this {
        this._onOffsetChange_flag = true
        this._onOffsetChange0_value = value
        return this
    }
    public pullDownRatio(value: number | undefined): this {
        this._pullDownRatio_flag = true
        this._pullDownRatio0_value = value
        return this
    }
    public _onChangeEvent_refreshing(callback_: ((refreshing: boolean) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RefreshOptions_serializer {
    public static write(buffer: SerializerBase, value: RefreshOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_refreshing  = value.refreshing
        valueSerializer.writeBoolean(value_refreshing)
        const value_promptText  = value.promptText
        let value_promptText_type : int32 = RuntimeType.UNDEFINED
        value_promptText_type = runtimeType(value_promptText)
        valueSerializer.writeInt8((value_promptText_type).toChar())
        if ((value_promptText_type) != (RuntimeType.UNDEFINED)) {
            const value_promptText_value  = value_promptText!
            let value_promptText_value_type : int32 = RuntimeType.UNDEFINED
            value_promptText_value_type = runtimeType(value_promptText_value)
            if (RuntimeType.STRING == value_promptText_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_promptText_value_0  = value_promptText_value as string
                valueSerializer.writeString(value_promptText_value_0)
            }
            else if (RuntimeType.OBJECT == value_promptText_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_promptText_value_1  = value_promptText_value as Resource
                Resource_serializer.write(valueSerializer, value_promptText_value_1)
            }
        }
        const value_builder  = value.builder
        let value_builder_type : int32 = RuntimeType.UNDEFINED
        value_builder_type = runtimeType(value_builder)
        valueSerializer.writeInt8((value_builder_type).toChar())
        if ((value_builder_type) != (RuntimeType.UNDEFINED)) {
            const value_builder_value  = value_builder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_builder_value))
        }
        const value_refreshingContent  = value.refreshingContent
        let value_refreshingContent_type : int32 = RuntimeType.UNDEFINED
        value_refreshingContent_type = runtimeType(value_refreshingContent)
        valueSerializer.writeInt8((value_refreshingContent_type).toChar())
        if ((value_refreshingContent_type) != (RuntimeType.UNDEFINED)) {
            const value_refreshingContent_value  = value_refreshingContent!
            ComponentContent_serializer.write(valueSerializer, value_refreshingContent_value)
        }
    }
    public static read(buffer: DeserializerBase): RefreshOptions {
        let valueDeserializer : DeserializerBase = buffer
        const refreshing_result : boolean = valueDeserializer.readBoolean()
        const promptText_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let promptText_buf : ResourceStr | undefined
        if ((promptText_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const promptText_buf__selector : int32 = valueDeserializer.readInt8()
            let promptText_buf_ : string | Resource | undefined
            if (promptText_buf__selector == (0).toChar()) {
                promptText_buf_ = (valueDeserializer.readString() as string)
            }
            else if (promptText_buf__selector == (1).toChar()) {
                promptText_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for promptText_buf_ has to be chosen through deserialisation.")
            }
            promptText_buf = (promptText_buf_ as string | Resource)
        }
        const promptText_result : ResourceStr | undefined = promptText_buf
        const builder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builder_buf : CustomBuilder | undefined
        if ((builder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const builder_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const builder_buf__call : KPointer = valueDeserializer.readPointer()
            const builder_buf__callSync : KPointer = valueDeserializer.readPointer()
            builder_buf = ():void => { 
    const builder_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    builder_buf__argsSerializer.writeInt32(builder_buf__resource.resourceId);
    builder_buf__argsSerializer.writePointer(builder_buf__call);
    builder_buf__argsSerializer.writePointer(builder_buf__callSync);
    InteropNativeModule._CallCallback(737226752, builder_buf__argsSerializer.asBuffer(), builder_buf__argsSerializer.length());
    builder_buf__argsSerializer.release();
    return; }
        }
        const builder_result : CustomBuilder | undefined = builder_buf
        const refreshingContent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let refreshingContent_buf : ComponentContent | undefined
        if ((refreshingContent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            refreshingContent_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const refreshingContent_result : ComponentContent | undefined = refreshingContent_buf
        let value : RefreshOptions = ({refreshing: refreshing_result, promptText: promptText_result, builder: builder_result, refreshingContent: refreshingContent_result} as RefreshOptions)
        return value
    }
}
