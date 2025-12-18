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

import { ArkUIGeneratedNativeModule } from '#components'
import { Finalizable, SerializerBase, toPeerPtr, KPointer, MaterializedBase, DeserializerBase, MaterializedBaseTag } from "@koalaui/interop"
import { ResourceColor, Offset, Dimension, EdgeStyles, EdgeColors, EdgeWidths,
    BorderRadiuses } from 'arkui/framework'
import { Callback } from '@ohos.base';
import { BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle, TransitionEffect, KeyboardAvoidMode,
    DismissReason, BackgroundBlurStyleOptions, BackgroundEffectOptions } from 'arkui/framework'
import { CustomBuilder } from 'arkui/framework'
import { DialogAlignment } from 'arkui/framework'
import { DismissDialogAction, LevelOrderExtender } from 'arkui/framework'
import { BorderStyle, Alignment } from 'arkui/framework'
import { Resource } from 'global.resource';
import { LengthMetrics } from 'arkui/Graphics';
import { AsyncCallback } from 'arkui/base';
import { int32 } from "@koalaui/compat";

export enum LevelMode {
    OVERLAY = 0,
    EMBEDDED = 1,
}

export enum ImmersiveMode {
    DEFAULT = 0,
    EXTEND = 1,
}

export class LevelOrder extends LevelOrderExtender {
    constructor(peerPtr: KPointer) {
        super(MaterializedBaseTag.NOP, peerPtr)
    }
    public static clamp(order: number): LevelOrder {
        const order_casted = order as (number)
        const retval = ArkUIGeneratedNativeModule._LevelOrderExtender_clamp(order_casted)
        return new LevelOrder(retval)
    }
}

declare namespace promptAction {
    export enum CommonState {
        UNINITIALIZED = 0,
        INITIALIZED = 1,
        APPEARING = 2,
        APPEARED = 3,
        DISAPPEARING = 4,
        DISAPPEARED = 5,
    }

    export class CommonController {
        constructor();
        close(): void;
        getState(): CommonState;
    }

    export interface ShowToastOptions {
        message: string | Resource;
        duration?: int32;
        bottom?: string | double;
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
        levelUniqueId?: int32;
        immersiveMode?: ImmersiveMode;
        levelOrder?: LevelOrder;
    }

    export interface ShowDialogOptionsInternal {
        levelOrder?: number;
    }

    export interface ShowDialogSuccessResponse {
        index: int32;
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
        levelUniqueId?: int32;
        immersiveMode?: ImmersiveMode;
    }

    export interface ActionMenuSuccessResponse {
        index: int32;
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
        levelUniqueId?: int32;
        immersiveMode?: ImmersiveMode;
        levelOrder?: LevelOrder;
        focusable?: boolean;
    }

    export interface DialogOptionsInternal {
        transition?: KPointer;
        dialogTransition?: KPointer;
        maskTransition?: KPointer;
        levelOrder?: number;
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

    export interface DialogBuilderOptions {
        builder?: KPointer;
        destroyFunc?: ((ptr: KPointer) => void);
        builderWithId?: ((dialogId: int32) => KPointer);
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

    export function openToast(options: ShowToastOptions): Promise<int32>;

    export function closeToast(toastId: int32): void;

    export function showDialog1(options: ShowDialogOptions, callback: AsyncCallback<ShowDialogSuccessResponse>,
        optionsInternal?: ShowDialogOptionsInternal): void;

    export function showDialog(options: ShowDialogOptions,
        optionsInternal?: ShowDialogOptionsInternal): Promise<ShowDialogSuccessResponse>;

    export function showActionMenu1(options: ActionMenuOptions,
        callback: AsyncCallback<ActionMenuSuccessResponse>): void;

    export function showActionMenu(options: ActionMenuOptions): Promise<ActionMenuSuccessResponse>;

    export function openCustomDialog1(content: KPointer, options?: BaseDialogOptions,
        optionsInternal?: DialogOptionsInternal): Promise<void>;

    export function openCustomDialog(builderOptions: DialogBuilderOptions, options: CustomDialogOptions,
        optionsInternal?: DialogOptionsInternal): Promise<int32>;

    export function updateCustomDialog(content: KPointer, options: BaseDialogOptions): Promise<void>;

    export function closeCustomDialog1(content: KPointer): Promise<void>;

    export function closeCustomDialog(dialogId: int32): void;

    export function openCustomDialogWithController(content: KPointer, controller: DialogController,
        options?: BaseDialogOptions, optionsInternal?: DialogOptionsInternal): Promise<void>;

    export function presentCustomDialog(builderOptions: DialogBuilderOptions, controller?: DialogController,
        options?: DialogOptions, optionsInternal?: DialogOptionsInternal): Promise<int32>;

    export function getTopOrder(): number | undefined;
    export function getBottomOrder(): number | undefined;

    export function getDialogController(content: KPointer): DialogController | undefined;
}

export default promptAction
