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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Callback_Number_Void } from "./alphabetIndexer"
import { Callback_Boolean_Void } from "./navigation"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceStr } from "./units"
import { ComponentContent } from "./arkui-custom"

export class ArkRefreshPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRefreshPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Refresh_construct(peerId, flags)
        const _peer  = new ArkRefreshPeer(_peerPtr, peerId, "Refresh", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRefreshOptionsAttribute(value: RefreshOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeRefreshOptions(value)
        ArkUIGeneratedNativeModule._RefreshInterface_setRefreshOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onStateChangeAttribute(value: ((state: RefreshStatus) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_onStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRefreshingAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_onRefreshing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    refreshOffsetAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_refreshOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pullToRefreshAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_pullToRefresh(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onOffsetChangeAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_onOffsetChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pullDownRatioAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._RefreshAttribute_pullDownRatio(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_refreshingAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._RefreshAttribute__onChangeEvent_refreshing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    offset?: number | string;
    friction?: number | string;
    promptText?: ResourceStr;
    builder?: CustomBuilder;
    refreshingContent?: ComponentContent;
}
export type RefreshInterface = (value: RefreshOptions) => RefreshAttribute;
export type Callback_RefreshStatus_Void = (state: RefreshStatus) => void;
export interface RefreshAttribute extends CommonMethod {
    onStateChange(value: ((state: RefreshStatus) => void) | undefined): this
    onRefreshing(value: (() => void) | undefined): this
    refreshOffset(value: number | undefined): this
    pullToRefresh(value: boolean | undefined): this
    onOffsetChange(value: ((index: number) => void) | undefined): this
    pullDownRatio(value: number | undefined): this
    _onChangeEvent_refreshing(callback: ((isVisible: boolean) => void)): void
}
export class ArkRefreshStyle extends ArkCommonMethodStyle implements RefreshAttribute {
    onStateChange_value?: ((state: RefreshStatus) => void) | undefined
    onRefreshing_value?: (() => void) | undefined
    refreshOffset_value?: number | undefined
    pullToRefresh_value?: boolean | undefined
    onOffsetChange_value?: ((index: number) => void) | undefined
    pullDownRatio_value?: number | undefined
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
    public onOffsetChange(value: ((index: number) => void) | undefined): this {
        return this
    }
    public pullDownRatio(value: number | undefined): this {
        return this
    }
    public _onChangeEvent_refreshing(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
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
            this.getPeer()?.onStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onRefreshing(value: (() => void) | undefined): this {
        if (this.checkPriority("onRefreshing")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onRefreshingAttribute(value_casted)
            return this
        }
        return this
    }
    public refreshOffset(value: number | undefined): this {
        if (this.checkPriority("refreshOffset")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.refreshOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public pullToRefresh(value: boolean | undefined): this {
        if (this.checkPriority("pullToRefresh")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.pullToRefreshAttribute(value_casted)
            return this
        }
        return this
    }
    public onOffsetChange(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onOffsetChange")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onOffsetChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public pullDownRatio(value: number | undefined): this {
        if (this.checkPriority("pullDownRatio")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.pullDownRatioAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_refreshing(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_refreshing")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_refreshingAttribute(callback_casted)
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
export function Refresh(
    /** @memo */
    style: ((attributes: RefreshAttribute) => void) | undefined,
    value: RefreshOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRefreshComponent()
    })
    NodeAttach<ArkRefreshPeer>((): ArkRefreshPeer => ArkRefreshPeer.create(receiver), (_: ArkRefreshPeer) => {
        receiver.setRefreshOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
