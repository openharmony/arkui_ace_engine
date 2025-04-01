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
import { ButtonType } from "./button"
import { ClickEvent } from "./common"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./securityComponent"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./units"
import { FontStyle, FontWeight, BorderStyle } from "./enums"
import { Resource } from "global/resource";
import { ArkPasteButtonComponent } from "./../generated/ArkPasteButton"
import { ArkPasteButtonPeer } from "./../generated/peers/ArkPasteButtonPeer"
export enum PasteIconStyle {
    LINES = 0
}
export enum PasteDescription {
    PASTE = 0
}
export interface PasteButtonOptions {
    icon?: PasteIconStyle;
    text?: PasteDescription;
    buttonType?: ButtonType;
}
export enum PasteButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export type Callback_ClickEvent_PasteButtonOnClickResult_Void = (event: ClickEvent, result: PasteButtonOnClickResult) => void;
/** @memo:stable */
export interface PasteButtonAttribute extends SecurityComponentMethod {
    /** @memo */
    setPasteButtonOptions(options?: PasteButtonOptions): this
    /** @memo */
    onClick(value: ((event: ClickEvent,result: PasteButtonOnClickResult) => void)): this
}
/** @memo */
export function PasteButton(
  /** @memo */
  style: ((attributes: PasteButtonAttribute) => void) | undefined,
  options?: PasteButtonOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkPasteButtonComponent()
    })
    NodeAttach<ArkPasteButtonPeer>((): ArkPasteButtonPeer => ArkPasteButtonPeer.create(receiver), (_: ArkPasteButtonPeer) => {
        receiver.setPasteButtonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
