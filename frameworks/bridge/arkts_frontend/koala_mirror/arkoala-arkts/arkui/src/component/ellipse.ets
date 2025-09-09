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
import { ArkCommonShapeMethodPeer, CommonShapeMethod, CommonMethod, ArkCommonShapeMethodComponent, ArkCommonShapeMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonShapeMethodSet, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkEllipsePeer extends ArkCommonShapeMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEllipsePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Ellipse_construct(peerId, flags)
        const _peer  = new ArkEllipsePeer(_peerPtr, peerId, "Ellipse", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setEllipseOptionsAttribute(options?: EllipseOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            EllipseOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._EllipseInterface_setEllipseOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface EllipseOptions {
}
export interface EllipseAttribute extends CommonShapeMethod {
    attributeModifier(value: AttributeModifier<EllipseAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkEllipseStyle extends ArkCommonShapeMethodStyle implements EllipseAttribute {
    attributeModifier_value?: AttributeModifier<EllipseAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<EllipseAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: EllipseAttribute): void {
        super.apply(target)
    }
}

export class ArkEllipseComponent extends ArkCommonShapeMethodComponent implements EllipseAttribute {
    getPeer(): ArkEllipsePeer {
        return (this.peer as ArkEllipsePeer)
    }
    public setEllipseOptions(options?: EllipseOptions): this {
        if (this.checkPriority("setEllipseOptions")) {
            const options_casted = options as (EllipseOptions | undefined)
            this.getPeer()?.setEllipseOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<EllipseAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withEllipseStyle(receiver: EllipseAttribute, modifier: AttributeModifier<EllipseAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkEllipseStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Ellipse")
// export function Ellipse(
//     options?: EllipseOptions,
//     @memo
//     content_?: () => void,
// ): EllipseAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Ellipse(
    @memo
    style: ((attributes: EllipseAttribute) => void) | undefined,
    options?: EllipseOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkEllipseComponent>((): ArkEllipseComponent => {
        return new ArkEllipseComponent()
    })
    NodeAttach<ArkEllipsePeer>((): ArkEllipsePeer => ArkEllipsePeer.create(receiver), (_: ArkEllipsePeer): void => {
        receiver.setEllipseOptions(options)
        style?.(receiver)
        withEllipseStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkEllipseSet extends ArkCommonShapeMethodSet implements EllipseAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: EllipseAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<EllipseAttribute> | AttributeModifier<CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class EllipseOptions_serializer {
    public static write(buffer: SerializerBase, value: EllipseOptions): void {
    }
    public static read(buffer: DeserializerBase): EllipseOptions {
        let value : EllipseOptions = ({} as EllipseOptions)
        return value
    }
}
