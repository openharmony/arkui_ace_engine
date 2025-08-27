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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceColor, Length, Position } from "./units"
import { FontWeight } from "./enums"
export class ArkBadgePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkBadgePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Badge_construct(peerId, flags)
        const _peer  = new ArkBadgePeer(_peerPtr, peerId, "Badge", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBadgeOptions0Attribute(value: BadgeParamWithNumber): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBadgeParamWithNumber(value)
        ArkUIGeneratedNativeModule._BadgeInterface_setBadgeOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBadgeOptions1Attribute(value: BadgeParamWithString): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeBadgeParamWithString(value)
        ArkUIGeneratedNativeModule._BadgeInterface_setBadgeOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum BadgePosition {
    RIGHT_TOP = 0,
    RightTop = 0,
    RIGHT = 1,
    Right = 1,
    LEFT = 2,
    Left = 2
}
export interface BadgeStyle {
    color?: ResourceColor;
    fontSize?: number | string;
    badgeSize?: number | string;
    badgeColor?: ResourceColor;
    borderColor?: ResourceColor;
    borderWidth?: Length;
    fontWeight?: number | FontWeight | string;
}
export interface BadgeParam {
    position?: BadgePosition | Position;
    style: BadgeStyle;
}
export interface BadgeParamWithNumber extends BadgeParam {
    count: number;
    maxCount?: number;
}
export interface BadgeParamWithString extends BadgeParam {
    value: string;
}
export interface BadgeAttribute extends CommonMethod {
}
export class ArkBadgeStyle extends ArkCommonMethodStyle implements BadgeAttribute {
}
export class ArkBadgeComponent extends ArkCommonMethodComponent implements BadgeAttribute {
    getPeer(): ArkBadgePeer {
        return (this.peer as ArkBadgePeer)
    }
    public setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        if (this.checkPriority("setBadgeOptions")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isBadgeParamWithNumber(value, false, false)) {
                const value_casted = value as (BadgeParamWithNumber)
                this.getPeer()?.setBadgeOptions0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isBadgeParamWithString(value, false)) {
                const value_casted = value as (BadgeParamWithString)
                this.getPeer()?.setBadgeOptions1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Badge(
    /** @memo */
    style: ((attributes: BadgeAttribute) => void) | undefined,
    value: BadgeParamWithNumber | BadgeParamWithString,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkBadgeComponent()
    })
    NodeAttach<ArkBadgePeer>((): ArkBadgePeer => ArkBadgePeer.create(receiver), (_: ArkBadgePeer) => {
        receiver.setBadgeOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
