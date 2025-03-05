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
import { DialogButtonStyle, WordBreak, BorderStyle, Color, ColoringStrategy, Curve, PlayMode } from "./ArkEnumsInterfaces"
import { ResourceStr, ResourceColor, VoidCallback, Offset, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles, Length } from "./ArkUnitsInterfaces"
import { Rectangle, BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, DismissReason, TransitionEffects, TranslateOptions, RotateOptions, ScaleOptions, TransitionEdge, AnimateParam, ShadowType, FinishCallbackType, ExpectedFrameRateRange } from "./ArkCommonInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DismissDialogAction } from "./ArkActionSheetInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { ICurve } from "./ArkICurveMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
export enum DialogAlignment {
    TOP,
    Top = TOP,
    CENTER = 1,
    Center = CENTER,
    BOTTOM = 2,
    Bottom = BOTTOM,
    DEFAULT = 3,
    Default = DEFAULT,
    TOP_START = 4,
    TopStart = TOP_START,
    TOP_END = 5,
    TopEnd = TOP_END,
    CENTER_START = 6,
    CenterStart = CENTER_START,
    CENTER_END = 7,
    CenterEnd = CENTER_END,
    BOTTOM_START = 8,
    BottomStart = BOTTOM_START,
    BOTTOM_END = 9,
    BottomEnd = BOTTOM_END,
}
export enum DialogButtonDirection {
    AUTO,
    HORIZONTAL = 1,
    VERTICAL = 2,
}
export interface AlertDialogButtonBaseOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: ResourceStr;
    fontColor?: ResourceColor;
    backgroundColor?: ResourceColor;
    action: VoidCallback;
}
export interface AlertDialogButtonOptions extends AlertDialogButtonBaseOptions {
    primary?: boolean;
}
export interface TextStyle_alert_dialog {
    wordBreak?: WordBreak;
}
export interface AlertDialogParam {
    title?: ResourceStr;
    subtitle?: ResourceStr;
    message: ResourceStr;
    autoCancel?: boolean;
    cancel?: VoidCallback;
    alignment?: DialogAlignment;
    offset?: Offset;
    gridCount?: number;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onWillDismiss?: ((parameter: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    textStyle?: TextStyle_alert_dialog;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
export interface AlertDialogParamWithConfirm extends AlertDialogParam {
    confirm?: AlertDialogButtonBaseOptions;
}
export interface AlertDialogParamWithButtons extends AlertDialogParam {
    primaryButton: AlertDialogButtonBaseOptions;
    secondaryButton: AlertDialogButtonBaseOptions;
}
export interface AlertDialogParamWithOptions extends AlertDialogParam {
    buttons: Array<AlertDialogButtonOptions>;
    buttonDirection?: DialogButtonDirection;
}
