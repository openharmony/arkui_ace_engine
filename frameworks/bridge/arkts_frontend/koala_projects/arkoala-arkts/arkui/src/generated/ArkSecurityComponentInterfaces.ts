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
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, BorderStyle } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
export enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1
}
export interface SecurityComponentMethod<T> {
    iconSize: Dimension;
    layoutDirection: SecurityComponentLayoutDirection;
    position: Position;
    markAnchor: Position;
    offset: Position | Edges | LocalizedEdges;
    fontSize: Dimension;
    fontStyle: FontStyle;
    fontWeight: number | FontWeight | string;
    fontFamily: string | Resource;
    fontColor: ResourceColor;
    iconColor: ResourceColor;
    backgroundColor: ResourceColor;
    borderStyle: BorderStyle;
    borderWidth: Dimension;
    borderColor: ResourceColor;
    borderRadius: Dimension;
    padding: Padding | Dimension;
    textIconSpace: Dimension;
    key: string;
    width: Length;
    height: Length;
    size: SizeOptions;
    constraintSize: ConstraintSizeOptions;
}
