/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ResourceColor, Offset, Dimension, EdgeStyles, EdgeColors, EdgeWidths,
    BorderRadiuses } from 'arkui.component.units'
import { AsyncCallback, Callback } from '@ohos.base'
import { BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle, TransitionEffect, KeyboardAvoidMode,
    DismissReason, BackgroundBlurStyleOptions, BackgroundEffectOptions } from 'arkui.component.common'
import { CustomBuilder } from 'arkui.component.builder'
import { DialogAlignment } from 'arkui.component.alertDialog'
import { DismissDialogAction } from 'arkui.component.actionSheet'
import { BorderStyle, Alignment } from 'arkui.component.enums'
import { Resource } from 'global.resource'
import { LengthMetrics } from 'arkui.Graphics'

export enum LevelMode {
    OVERLAY = 0,
    EMBEDDED = 1,
}

export enum ImmersiveMode {
    DEFAULT = 0,
    EXTEND = 1,
}

class DismissDialogActionInner implements DismissDialogAction {
    nativePtr: long = 0;
    constructor(nativePtr: long) {
        if (this.nativePtr == 0) {
            this.nativePtr = nativePtr;
        }
    }

    native dismiss(): void;
    reason: DismissReason = DismissReason.PRESS_BACK;
}

export default namespace promptAction {
    static { loadLibrary("promptAction_ani"); }

    export enum CommonState {
        UNINITIALIZED = 0,
        INITIALIZED = 1,
        APPEARING = 2,
        APPEARED = 3,
        DISAPPEARING = 4,
        DISAPPEARED = 5,
    }

    export class CommonController {
        static { loadLibrary("promptAction_ani"); }
        public native constructor();
        public native close(): void;
        public native getState(): CommonState;
    }

    export enum ToastShowMode {
        DEFAULT = 0,
        TOP_MOST = 1,
        SYSTEM_TOP_MOST = 2
    }

    export default interface ShowToastOptions
    {
        message: string | Resource;
        duration?: int;
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
        levelUniqueId?: int;
        immersiveMode?: ImmersiveMode;
    }

    export interface ShowDialogOptionsInternal {
        levelOrder?: number;
    }

    export interface ShowDialogSuccessResponse {
        index: int;
    }

    class ShowDialogSuccessResponseInner implements ShowDialogSuccessResponse {
        index: int = 0;
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
        showInSubwindow?: boolean;
        isModal?: boolean;
        levelMode?: LevelMode;
        levelUniqueId?: int;
        immersiveMode?: ImmersiveMode;
    }

    export interface ActionMenuSuccessResponse {
        index: int;
    }

    class ActionMenuSuccessResponseInner implements ActionMenuSuccessResponse {
        index: int = 0;
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
        levelUniqueId?: int;
        immersiveMode?: ImmersiveMode;
        focusable?: boolean;
    }

    export interface DialogOptionsInternal {
        transition?: long;
        dialogTransition?: long;
        maskTransition?: long;
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
        builder?: long;
        destroyFunc?: ((ptr: long) => void);
        builderWithId?: ((dialogId: int) => long);
    }

    class Cleaner {
        private ptr: long = 0
        constructor(ptr: long) {
            this.ptr = ptr
        }
        native clean(): void
    }

    export function callback(cleaner: Cleaner): void {
        cleaner.clean()
    }

    let destroyRegister = new FinalizationRegistry<Cleaner>(callback)
    let unregisterToken = new object()

    export class DialogController extends CommonController {
        static { loadLibrary("promptAction_ani"); }

        private nativePtr: long = 0;
        private cleaner: Cleaner | null = null;

        constructor() {
            if (this.nativePtr == 0) {
                this.nativePtr = this.createPtr();
            }
            this.registerCleaner(this.nativePtr);
        }

        registerCleaner(ptr: long): void {
            this.cleaner = new Cleaner(ptr);
            destroyRegister.register(this, this.cleaner!, unregisterToken);
        }

        unregisterCleaner(): void {
            destroyRegister.unregister(unregisterToken);
        }

        native createPtr(): long;
        native close(): void;
    }

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

    export native function showToast(options: ShowToastOptions): void;

    export native function openToast(options: ShowToastOptions): Promise<int>;

    export native function closeToast(toastId: int): void;

    export native function showDialog1(options: ShowDialogOptions,
        callback: AsyncCallback<ShowDialogSuccessResponse>, optionsInternal?: ShowDialogOptionsInternal): void;

    export native function showDialog(options: ShowDialogOptions,
        optionsInternal?: ShowDialogOptionsInternal): Promise<ShowDialogSuccessResponse>;

    export native function showActionMenu1(options: ActionMenuOptions,
        callback: AsyncCallback<ActionMenuSuccessResponse>): void;

    export native function showActionMenu(options: ActionMenuOptions): Promise<ActionMenuSuccessResponse>;

    export native function openCustomDialog1(content: long, options?: BaseDialogOptions,
        optionsInternal?: DialogOptionsInternal): Promise<void>;

    export native function openCustomDialog(builderOptions: DialogBuilderOptions, options: CustomDialogOptions,
        optionsInternal?: DialogOptionsInternal): Promise<int>;

    export native function updateCustomDialog(content: long, options: BaseDialogOptions): Promise<void>;

    export native function closeCustomDialog1(content: long): Promise<void>;

    export native function closeCustomDialog(dialogId: int): void;

    export native function openCustomDialogWithController(content: long, controller: DialogController,
        options?: BaseDialogOptions, optionsInternal?: DialogOptionsInternal): Promise<void>;

    export native function presentCustomDialog(builderOptions: DialogBuilderOptions, controller?: DialogController,
        options?: DialogOptions, optionsInternal?: DialogOptionsInternal): Promise<int>;

    export native function getTopOrder(): number | undefined;
    export native function getBottomOrder(): number | undefined;

    export native function getDialogNode(content: long): long | undefined;
    export native function setDialogController(dialog: long, controller: DialogController): boolean;
    export function getDialogController(content: long): DialogController | undefined {
        let dialog = getDialogNode(content);
        if (dialog === undefined) {
            return undefined;
        }

        let controller = new DialogController();
        if (setDialogController(dialog, controller)) {
            return controller;
        }
        return undefined;
    }
}
