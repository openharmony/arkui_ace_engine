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
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./units"
import { FontStyle, FontWeight, BorderStyle } from "./enums"
import { Resource } from "global/resource";
export enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1
}
/** @memo:stable */
export interface SecurityComponentMethod {
    /** @memo */
    iconSize(value: Dimension): this
    /** @memo */
    layoutDirection(value: SecurityComponentLayoutDirection): this
    /** @memo */
    position(value: Position): this
    /** @memo */
    markAnchor(value: Position): this
    /** @memo */
    offset(value: Position | Edges | LocalizedEdges): this
    /** @memo */
    fontSize(value: Dimension): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    fontFamily(value: string | Resource): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    iconColor(value: ResourceColor): this
    /** @memo */
    backgroundColor(value: ResourceColor): this
    /** @memo */
    borderStyle(value: BorderStyle): this
    /** @memo */
    borderWidth(value: Dimension): this
    /** @memo */
    borderColor(value: ResourceColor): this
    /** @memo */
    borderRadius(value: Dimension): this
    /** @memo */
    padding(value: Padding | Dimension): this
    /** @memo */
    textIconSpace(value: Dimension): this
    /** @memo */
    key(value: string): this
    /** @memo */
    width(value: Length): this
    /** @memo */
    height(value: Length): this
    /** @memo */
    size(value: SizeOptions): this
    /** @memo */
    constraintSize(value: ConstraintSizeOptions): this
}
// /** @memo */
// export function SecurityComponentMethod(
//   /** @memo */
//   style: ((attributes: SecurityComponentMethodAttribute) => void) | undefined,
  
//   /** @memo */
//   content_?: () => void,
// ) {
//     const receiver = remember(() => {
//         return new ArkSecurityComponentMethodComponent()
//     })
//     NodeAttach<ArkSecurityComponentMethodPeer>((): ArkSecurityComponentMethodPeer => ArkSecurityComponentMethodPeer.create(receiver), (_: ArkSecurityComponentMethodPeer) => {
        
//         style?.(receiver)
//         content_?.()
//         receiver.applyAttributesFinish()
//     })
// }
