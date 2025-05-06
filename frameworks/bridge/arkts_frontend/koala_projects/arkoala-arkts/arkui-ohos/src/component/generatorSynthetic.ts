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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { GestureJudgeResult, GestureRecognizer } from "./gesture"
import { TouchResult, CustomBuilder, DragItemInfo, ScrollResult } from "./common"
import { HitTestMode } from "./enums"
import { NavigationAnimatedTransition } from "./navigation"
import { Tuple_Number_Number } from "./arkui-synthetics"
import { Tuple_Number_Number_Number_Number, ComputedBarAttribute, Literal_Number_offsetRemain } from "./grid"
import { NavDestinationTransition } from "./navDestination"
import { OnScrollFrameBeginHandlerResult, OffsetResult } from "./scroll"
import { TabContentAnimatedTransition } from "./tabs"
import { TextMenuItem } from "./textCommon"
import { WithThemeAttribute } from "./withTheme"
import { WebKeyboardOptions, WebResourceResponse } from "./web"
import { UserDataSpan, StyledString } from "./styledString"
export type Callback_Pointer_Void = (value: KPointer) => void;
export type Callback_Array_String_Void = (value: Array<string>) => void;
export type Callback_GestureJudgeResult_Void = (value: GestureJudgeResult) => void;
export type Callback_GestureRecognizer_Void = (value: GestureRecognizer) => void;
export type Callback_TouchResult_Void = (value: TouchResult) => void;
export type Callback_Union_CustomBuilder_DragItemInfo_Void = (value: CustomBuilder | DragItemInfo) => void;
export type Callback_HitTestMode_Void = (value: HitTestMode) => void;
export type Callback_Opt_Array_String_Void = (error?: Array<string> | undefined) => void;
export type Callback_Opt_NavigationAnimatedTransition_Void = (value: NavigationAnimatedTransition | undefined) => void;
export type Callback_Tuple_Number_Number_Void = (value: [ number, number ]) => void;
export type Callback_Tuple_Number_Number_Number_Number_Void = (value: [ number, number, number, number ]) => void;
export type Callback_ComputedBarAttribute_Void = (value: ComputedBarAttribute) => void;
export type Callback_CustomBuilder_Void = (value: CustomBuilder) => void;
export type Callback_Literal_Number_offsetRemain_Void = (value: Literal_Number_offsetRemain) => void;
export type Callback_Opt_Array_NavDestinationTransition_Void = (value: Array<NavDestinationTransition> | undefined) => void;
export type Callback_OnScrollFrameBeginHandlerResult_Void = (value: OnScrollFrameBeginHandlerResult) => void;
export type Callback_OffsetResult_Void = (value: OffsetResult) => void;
export type Callback_ScrollResult_Void = (value: ScrollResult) => void;
export type Callback_Opt_TabContentAnimatedTransition_Void = (value: TabContentAnimatedTransition | undefined) => void;
export type Callback_Array_TextMenuItem_Void = (value: Array<TextMenuItem>) => void;
export type Callback_WithThemeAttribute_Void = (value: WithThemeAttribute) => void;
export type Callback_WebKeyboardOptions_Void = (value: WebKeyboardOptions) => void;
export type Callback_WebResourceResponse_Void = (value: WebResourceResponse) => void;
export type Callback_Buffer_Void = (value: NativeBuffer) => void;
export type Callback_StyledStringMarshallingValue_Void = (value: UserDataSpan) => void;
export type Callback_Opt_StyledString_Opt_Array_String_Void = (value?: StyledString | undefined, error?: Array<string> | undefined) => void;
