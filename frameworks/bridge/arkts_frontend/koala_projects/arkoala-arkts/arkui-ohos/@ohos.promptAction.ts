/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { KPointer } from "@koalaui/interop"
import { ResourceColor, Offset, Dimension, EdgeStyles, EdgeColors, EdgeWidths,
    BorderRadiuses } from 'arkui/component/units';
import { Callback } from '@ohos.base';
import { BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle, TransitionEffect, KeyboardAvoidMode,
    DismissReason, BackgroundBlurStyleOptions, BackgroundEffectOptions } from 'arkui/component/common';
import { AsyncCallback, CustomBuilder } from 'arkui/component';
import { DialogAlignment } from 'arkui/component/alertDialog';
import { BorderStyle, Alignment } from 'arkui/component/enums';
import { Resource } from 'global.resource';
import { LengthMetrics } from 'arkui/Graphics';

export enum LevelMode {
    OVERLAY = 0,
    EMBEDDED = 1,
}

export enum ImmersiveMode {
    DEFAULT = 0,
    EXTEND = 1,
}

export interface DismissDialogAction {
    dismiss: (() => void);
    reason: DismissReason;
}

export declare class LevelOrder {
    static clamp(order: number): LevelOrder;
    getOrder(): number;
}

declare namespace promptAction {
    export interface ShowToastOptions {
        message: string | Resource;
        duration?: number;
        bottom?: string | number;
        showMode?: ToastShowMode;
        alignment?: Alignment;
        offset?: Offset;
        backgroundColor?: ResourceColor;
        textColor?: ResourceColor;
        backgroundBlurStyle?: BlurStyle;
        shadow?: ShadowOptions | ShadowStyle;
        enableHoverMode?: boolean;
        hoverModeArea?: HoverModeAreaType;
    }

    export enum ToastShowMode {
        DEFAULT = 0,
        TOP_MOST = 1,
        SYSTEM_TOP_MOST = 2
    }

    export interface Button {
        text: string | Resource;
        color: string | Resource;
        primary?: boolean;
    }

    export interface ShowDialogOptions {
        title?: string | Resource;
        message?: string | Resource;
        buttons?: Array<Button>
        maskRect?: Rectangle;
        alignment?: DialogAlignment;
        offset?: Offset;
        showInSubWindow?: boolean;
        isModal?: boolean;
        backgroundColor?: ResourceColor;
        backgroundBlurStyle?: BlurStyle;
        backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
        backgroundEffect?: BackgroundEffectOptions;
        shadow?: ShadowOptions | ShadowStyle;
        enableHoverMode?: boolean;
        hoverModeArea?: HoverModeAreaType;
        onDidAppear?: (() => void);
        onDidDisappear?: (() => void);
        onWillAppear?: (() => void);
        onWillDisappear?: (() => void);
        levelMode?: LevelMode;
        levelUniqueId?: number;
        immersiveMode?: ImmersiveMode;
    }

    export interface ShowDialogSuccessResponse {
        index: number;
    }

    export type PromptActionSingleButton = [Button];
    export type PromptActionDoubleButtons = [Button, Button | undefined];
    export type PromptActionTripleButtons = [Button, Button | undefined, Button | undefined];
    export type PromptActionQuadrupleButtons = [Button, Button | undefined, Button | undefined, Button | undefined];
    export type PromptActionQuintupleButtons = [
        Button, Button | undefined, Button | undefined, Button | undefined, Button | undefined];
    export type PromptActionSextupleButtons = [
        Button, Button | undefined, Button | undefined, Button | undefined, Button | undefined, Button | undefined];

    export interface ActionMenuOptions {
        title?: string | Resource;
        buttons: PromptActionSingleButton | PromptActionDoubleButtons | PromptActionTripleButtons |
            PromptActionQuadrupleButtons | PromptActionQuintupleButtons | PromptActionSextupleButtons;
        showInSubWindow?: boolean;
        isModal?: boolean;
        levelMode?: LevelMode;
        levelUniqueId?: number;
        immersiveMode?: ImmersiveMode;
    }

    export interface ActionMenuSuccessResponse {
        index: number;
    }

    export interface BaseDialogOptions {
        maskRect?: Rectangle;
        alignment?: DialogAlignment;
        offset?: Offset;
        showInSubWindow?: boolean;
        isModal?: boolean;
        autoCancel?: boolean;
        transition?: TransitionEffect;
        dialogTransition?: TransitionEffect;
        maskTransition?: TransitionEffect;
        maskColor?: ResourceColor;
        onWillDismiss?: Callback<DismissDialogAction>;
        onDidAppear?: (() => void);
        onDidDisappear?: (() => void);
        onWillAppear?: (() => void);
        onWillDisappear?: (() => void);
        keyboardAvoidMode?: KeyboardAvoidMode;
        enableHoverMode?: boolean;
        hoverModeArea?: HoverModeAreaType;
        backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
        backgroundEffect?: BackgroundEffectOptions;
        keyboardAvoidDistance?: LengthMetrics;
        levelMode?: LevelMode;
        levelUniqueId?: number;
        immersiveMode?: ImmersiveMode;
        focusable?: boolean;
    }

    export interface DialogOptionsInternal {
        transition?: KPointer;
        dialogTransition?: KPointer;
        maskTransition?: KPointer;
    }

    export interface CustomDialogOptions extends BaseDialogOptions {
        builder: CustomBuilder;
        backgroundColor?: ResourceColor;
        cornerRadius?: Dimension | BorderRadiuses;
        width?: Dimension;
        height?: Dimension;
        borderWidth?: Dimension | EdgeWidths;
        borderColor?: ResourceColor | EdgeColors;
        borderStyle?: BorderStyle | EdgeStyles;
        backgroundBlurStyle?: BlurStyle;
        shadow?: ShadowOptions | ShadowStyle;
    }

    export class CommonController {
        constructor();
        close(): void;
    }

    export class DialogController extends CommonController {}

    export type DialogOptionsCornerRadius = Dimension | BorderRadiuses;
    export type DialogOptionsBorderWidth = Dimension | EdgeWidths;
    export type DialogOptionsBorderColor = ResourceColor | EdgeColors;
    export type DialogOptionsBorderStyle = BorderStyle | EdgeStyles;
    export type DialogOptionsShadow = ShadowOptions | ShadowStyle;

    export interface DialogOptions extends BaseDialogOptions {
        backgroundColor?: ResourceColor;
        cornerRadius?: DialogOptionsCornerRadius;
        width?: Dimension;
        height?: Dimension;
        borderWidth?: DialogOptionsBorderWidth;
        borderColor?: DialogOptionsBorderColor;
        borderStyle?: DialogOptionsBorderStyle;
        backgroundBlurStyle?: BlurStyle;
        shadow?: DialogOptionsShadow;
    }

    export function showToast(options: ShowToastOptions): void;

    export function openToast(options: ShowToastOptions): Promise<number>;

    export function closeToast(toastId: number): void;

    export function showDialog1(options: ShowDialogOptions, callback: AsyncCallback<ShowDialogSuccessResponse>): void;

    export function showDialog(options: ShowDialogOptions): Promise<ShowDialogSuccessResponse>;

    export function showActionMenu1(options: ActionMenuOptions,
        callback: AsyncCallback<ActionMenuSuccessResponse>): void;

    export function showActionMenu(options: ActionMenuOptions): Promise<ActionMenuSuccessResponse>;

    export function openCustomDialog1(content: KPointer, options?: BaseDialogOptions,
        optionsInternal?: DialogOptionsInternal): Promise<void>;

    export function openCustomDialog(builder: KPointer, options: CustomDialogOptions,
        optionsInternal?: DialogOptionsInternal): Promise<number>;

    export function updateCustomDialog(content: KPointer, options: BaseDialogOptions): Promise<void>;

    export function closeCustomDialog1(content: KPointer): Promise<void>;

    export function closeCustomDialog(dialogId: number): void;

    export function openCustomDialogWithController(content: KPointer, controller: DialogController,
        options?: BaseDialogOptions, optionsInternal?: DialogOptionsInternal): Promise<void>;

    export function presentCustomDialog(builder: KPointer, controller?: DialogController,
        options?: DialogOptions, optionsInternal?: DialogOptionsInternal): Promise<number>;
}

export default promptAction