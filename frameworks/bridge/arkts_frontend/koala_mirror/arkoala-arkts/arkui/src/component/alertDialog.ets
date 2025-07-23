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
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { DialogButtonStyle, Color, WordBreak, BorderStyle } from "./enums"
import { ResourceStr, ResourceColor, VoidCallback, Offset, Dimension, BorderRadiuses, LocalizedBorderRadiuses, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, EdgeStyles } from "./units"
import { Resource } from "./../generated/resource"
import { DismissDialogAction } from "./actionSheet"
import { Rectangle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, TransitionEffect, ShadowOptions, ShadowStyle, HoverModeAreaType } from "./common"
import { LevelMode, ImmersiveMode, LevelOrder } from "./../generated/ohos.promptAction"
export enum DialogAlignment {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
    DEFAULT = 3,
    Default = 3,
    TOP_START = 4,
    TopStart = 4,
    TOP_END = 5,
    TopEnd = 5,
    CENTER_START = 6,
    CenterStart = 6,
    CENTER_END = 7,
    CenterEnd = 7,
    BOTTOM_START = 8,
    BottomStart = 8,
    BOTTOM_END = 9,
    BottomEnd = 9
}
export enum DialogButtonDirection {
    AUTO = 0,
    HORIZONTAL = 1,
    VERTICAL = 2
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
export interface TextStyle {
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
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    textStyle?: TextStyle;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
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
