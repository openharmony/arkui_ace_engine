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
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ButtonType } from "./ArkButtonInterfaces"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./ArkSecurityComponentInterfaces"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions, PX, VP, FP, LPX, Percentage, Area } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, BorderStyle, Color } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
export enum SaveIconStyle {
    FULL_FILLED,
    LINES = 1,
    PICTURE = 2,
}
export enum SaveDescription {
    DOWNLOAD,
    DOWNLOAD_FILE = 1,
    SAVE = 2,
    SAVE_IMAGE = 3,
    SAVE_FILE = 4,
    DOWNLOAD_AND_SHARE = 5,
    RECEIVE = 6,
    CONTINUE_TO_RECEIVE = 7,
    SAVE_TO_GALLERY = 8,
    EXPORT_TO_GALLERY = 9,
    QUICK_SAVE_TO_GALLERY = 10,
    RESAVE_TO_GALLERY = 11,
}
export interface SaveButtonOptions {
    icon?: SaveIconStyle;
    text?: SaveDescription;
    buttonType?: ButtonType;
}
export enum SaveButtonOnClickResult {
    SUCCESS,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
export interface SaveButtonInterface {
    invoke(): SaveButtonAttribute;

}
export interface SaveButtonAttribute extends SecurityComponentMethod<SaveButtonAttribute> {
    onClick: ((event: ClickEvent, result: SaveButtonOnClickResult) => void);
}
