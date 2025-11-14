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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { hookToolBarItemAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { ToolBarItemModifier } from "./../ToolBarItemModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkToolBarItemPeer extends PeerNode {
    attributeSet?: ToolBarItemModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkToolBarItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ToolBarItem_construct(peerId, flags)
        const _peer  = new ArkToolBarItemPeer(_peerPtr, peerId, 'ToolBarItem', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setToolBarItemOptionsAttribute(options?: ToolBarItemOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ToolBarItemOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ToolBarItemInterface_setToolBarItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ToolBarItemPlacement {
    TOP_BAR_LEADING = 0,
    TOP_BAR_TRAILING = 1
}
export interface ToolBarItemOptions {
    placement?: ToolBarItemPlacement;
}
export interface ToolBarItemAttribute {
    setToolBarItemOptions(options?: ToolBarItemOptions): this {
        throw new Error("Unimplemented method setToolBarItemOptions")
    }
    attributeModifier(value: AttributeModifier<ToolBarItemAttribute> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkToolBarItemStyle implements ToolBarItemAttribute {
    setToolBarItemOptions(options?: ToolBarItemOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ToolBarItemAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkToolBarItemComponent extends ComponentBase implements ToolBarItemAttribute {
    getPeer(): ArkToolBarItemPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkToolBarItemPeer)
    }
    public setToolBarItemOptions(options?: ToolBarItemOptions): this {
        if (this.checkPriority("setToolBarItemOptions")) {
            const options_casted = options as (ToolBarItemOptions | undefined)
            this.getPeer()?.setToolBarItemOptionsAttribute(options_casted)
            this.applyOptionsFinish('ToolBarItemAttribute');
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ToolBarItemAttribute> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookToolBarItemAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ToolBarItemImpl(
    @memo
    style: ((attributes: ToolBarItemAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkToolBarItemComponent>((): ArkToolBarItemComponent => {
        return new ArkToolBarItemComponent()
    })
    NodeAttach<ArkToolBarItemPeer>((): ArkToolBarItemPeer => ArkToolBarItemPeer.create(receiver), (peer: ArkToolBarItemPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class ToolBarItemOptions_serializer {
    public static write(buffer: SerializerBase, value: ToolBarItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPlacement  = value.placement
        if (valueHolderForPlacement !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPlacementTmpValue  = (valueHolderForPlacement as ToolBarItemPlacement)
            valueSerializer.writeInt32(valueHolderForPlacementTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ToolBarItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const placementTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placementTmpBuf : ToolBarItemPlacement | undefined = undefined
        if ((placementTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            placementTmpBuf = ToolBarItemPlacement.fromValue(valueDeserializer.readInt32())
        }
        const placementTmpResult : ToolBarItemPlacement | undefined = placementTmpBuf
        let value : ToolBarItemOptions = ({placement: placementTmpResult} as ToolBarItemOptions)
        return value
    }
}
