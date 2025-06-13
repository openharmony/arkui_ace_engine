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

import { FrameNode } from "arkui/FrameNode"
import { FontOptions, FontInfo } from "@ohos/font"
import { MeasureOptions } from "@ohos/measure"
import { SizeOptions } from "arkui/component/units"
import { AnimateParam } from "arkui/component"
import { AnimatorResult, AnimatorOptions, Animator} from "@ohos/animator"
import { Context, PointerStyle, PixelMap } from "#external"
import { componentUtils } from "@ohos/arkui/componentUtils"
import { componentSnapshot } from "@ohos/arkui/componentSnapshot"
import { focusController } from "@ohos/arkui/focusController"
import { Frame } from "arkui/Graphics"
import { KeyEvent } from "arkui/component/common"
import { TextMenuOptions } from "arkui/component/textCommon"
import { Nullable } from "arkui/component/enums"
import { KeyProcessingMode } from "arkui/component/focus"
import { uiObserver } from "@ohos/arkui/observer"
import { mediaquery } from '@ohos/mediaquery'
import { AlertDialog, AlertDialogParamWithConfirm, AlertDialogParamWithButtons,
    AlertDialogParamWithOptions }from "arkui/component/alertDialog"
import inspector from "@ohos/arkui/inspector"
import router from '@ohos/router'
import promptAction from '@ohos/promptAction';
import { AsyncCallback, CustomBuilder } from 'arkui/component'

export class UIInspector {
    public createComponentObserver(id: string): inspector.ComponentObserver {
        throw Error("createComponentObserver not implemented in UIInspector!")
    }
}

export class Font {
    public registerFont(options: FontOptions) : void {
        throw Error("registerFont not implemented in Font!")
    }
    public getSystemFontList() : Array<string> {
        throw Error("getSystemFontList not implemented in Font!")
    }
    public getFontByName(fontName : string) : FontInfo {
        throw Error("getFontByName not implemented in Font!")
    }
}

export class MediaQuery {
    public matchMediaSync(condition: string): mediaquery.MediaQueryListener {
        throw Error("matchMediaSync not implemented in MedaiQuery!")
    }
}

export class MeasureUtils {
    public measureText(options: MeasureOptions) : number {
        throw Error("measureText not implemented in MeasureUtils!")
    }
    public measureTextSize(options: MeasureOptions) : SizeOptions {
        throw Error("measureTextSize not implemented in MeasureUtils!")
    }
}

export class TextMenuController {
    public setMenuOptions(options: TextMenuOptions) : void {
        throw Error("setMenuOptions not implemented in TextMenuController!")
    }
}

export class Router {
    public pushUrl(options: router.RouterOptions): Promise<void> {
        throw Error("pushUrl not implemented in Router!")
    }

    public back(options?:router.RouterOptions): void {
        throw Error("back not implemented in Router!")
    }

    public clear(): void {
        throw Error("clear not implemented in Router!")
    }
}

export interface AtomicServiceBar {
    getBarRect(): Frame;
}

export class ComponentUtils {
    public getRectangleById(id: string): componentUtils.ComponentInfo {
        throw Error("getRectangleById not implemented in ComponentUtils!")
    }
}


export class FocusController {
    public clearFocus(): void {
        throw Error("clearFocus not implemented in FocusController!")
    }

    public requestFocus(key: string): void {
        throw Error("requestFocus not implemented in FocusController!")
    }

    public activate(isActive: boolean, autoInactive?: boolean): void {
        throw Error("activate not implemented in FocusController!")
    }

    public setAutoFocusTransfer(isAutoFocusTransfer: boolean): void {
        throw Error("setAutoFocusTransfer not implemented in FocusController!")
    }
    public setKeyProcessingMode(mode: KeyProcessingMode): void {
        throw Error("setKeyProcessingMode not implemented in FocusController!")
    }
}

export class ComponentSnapshot {
    //@ts-ignore
    public get(id: string, callback: AsyncCallback<PixelMap>,
               options?: componentSnapshot.SnapshotOptions): void {
        throw Error("get with callback not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public get(id: string, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        throw Error("get with promise not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public createFromBuilder(builder: CustomBuilder, callback: AsyncCallback<PixelMap>,
                             delay?: number, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): void {
        throw Error("createFromBuilder with callback not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public createFromBuilder(builder: CustomBuilder, delay?: number, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        throw Error("createFromBuilder with promise not implemented in ComponentSnapshot!")
    }
    public getSync(id: string, options?: componentSnapshot.SnapshotOptions): PixelMap {
        throw Error("getSync not implemented in ComponentSnapshot!")
    }
    public getWithUniqueId(uniqueId: number, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        throw Error("getWithUniqueId not implemented in ComponentSnapshot!")
    }

    public getSyncWithUniqueId(uniqueId: number, options?: componentSnapshot.SnapshotOptions): PixelMap {
        throw Error("getSyncWithUniqueId not implemented in ComponentSnapshot!")
    }
}

export class ContextMenuController {
    public close(): void {
        throw Error("close not implemented in ContextMenuController!")
    }
}

export class PromptAction {
    showToast(options: promptAction.ShowToastOptions): void {
        throw Error("showToast not implemented in PromptAction!")
    }
}

export class CursorController {
    public restoreDefault(): void {
        throw Error("restoreDefault not implemented in CursorController!")
    }

    public setCursor(value: PointerStyle): void {
        throw Error("setCursor not implemented in CursorController!")
    }
}

export class UIContext {
    constructor() {
    }
    public getFont() : Font {
        throw Error("getFont not implemented in UIContext!")
    }

    public getMediaQuery(): MediaQuery {
        throw Error("getMediaQuery not implemented in UIContext!")
    }

    public getMeasureUtils() : MeasureUtils {
        throw Error("getMeasureUtils not implemented in UIContext!")
    }
    public getTextMenuController() : TextMenuController {
        throw Error("getTextMenuController not implemented in UIContext!")
    }
    public isFollowingSystemFontScale() : boolean {
        throw Error("isFollowingSystemFontScale not implemented in UIContext!")
    }
    public getMaxFontScale() : number {
        throw Error("getMaxFontScale not implemented in UIContext!")
    }
    public getFrameNodeById(id: string): FrameNode | null {
        throw Error("getFrameNodeById not implemented in UIContext!")
    }
    getAttachedFrameNodeById(id: string): FrameNode | null {
        throw Error("getAttachedFrameNodeById not implemented in UIContext!")
    }
    getFrameNodeByNodeId(id: number): FrameNode | null {
        throw Error("getFrameNodeByNodeId not implemented in UIContext!")
    }
    getFrameNodeByUniqueId(id: number): FrameNode | null {
        throw Error("getFrameNodeByUniqueId not implemented in UIContext!")
    }
    getHostContext(): Context | undefined {
        throw Error("getHostContext not implemented in UIContext!")
    }

    public getAtomicServiceBar(): Nullable<AtomicServiceBar> {
        throw Error("getAtomicServiceBar not implemented in UIContext!")
    }

    public dispatchKeyEvent(node: number | string, event: KeyEvent): boolean {
        throw Error("dispatchKeyEvent not implemented in UIContext!")
    }

    public getFocusController(): FocusController {
        throw Error("getFocusController not implemented in UIContext!")
    }

    public getContextMenuController(): ContextMenuController {
        throw Error("getContextMenuController not implemented in UIContext!")
    }

    public getComponentUtils(): ComponentUtils {
        throw Error("getComponentUtils not implemented in UIContext!")
    }

    public getCursorController(): CursorController {
        throw Error("getCursorController not implemented in UIContext!")
    }
    
    public getComponentSnapshot(): ComponentSnapshot {
        throw Error("getComponentSnapshot not implemented in UIContext!")
    }

    public getRouter(): Router {
        throw Error("getRouter not implemented in UIContext!")
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        throw Error("animateTo not implemented in UIContext!")
    }

    public createAnimator(options: AnimatorOptions): AnimatorResult {
        throw Error("createAnimator not implemented in UIContext!")
    }
    public setFrameCallback(onFrameCallback: ((index: number) => void), onIdleCallback: ((index: number) => void),
                                              delayTime: number): void {
        throw Error("setFrameCallback not implemented in UIContext!")
    }
    runScopedTask(callback: () => void): void {
        throw Error("runScopedTask not implemented in UIContext!")
    }
    clearResourceCache(): void {
        throw Error("clearResourceCache not implemented in UIContext!")
    }
    postFrameCallback(frameCallback: FrameCallback): void {
        throw Error("postFrameCallback not implemented in UIContext!")
    }
    postDelayedFrameCallback(frameCallback: FrameCallback, delayTime: number): void {
        throw Error("postDelayedFrameCallback not implemented in UIContext!")
    }
    public getUIInspector(): UIInspector {
        throw Error("getUIInspector not implemented in UIContext!")
    }
    public getUIObserver(): UIObserver {
        throw Error("getUIObserver not implemented in UIContext!")
    }

    public getPromptAction(): PromptAction {
        throw Error("getPromptAction not implemented in UIContext!")
    }

    public showAlertDialog(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons |
        AlertDialogParamWithOptions): void {
        throw Error("showAlertDialog not implemented in UIContext!")
    }

    // @ts-ignore
    public freezeUINode(id: number, isFrozen: boolean): void {
        throw Error("freezeUINode not implemented in UIContext!")
    }

    // @ts-ignore
    public freezeUINode(id: string, isFrozen: boolean): void {
        throw Error("freezeUINode not implemented in UIContext!")
    }
}
export abstract class FrameCallback {
    onFrame(frameTimeInNano: number): void {}
    onIdle(timeLeftInNano: number): void {}
}

export type Callback<T,V = void> = (data: T) => V
export class UIObserver {
    private instanceId_: number = 100000;
    private observerImpl: uiObserver.UIObserver | null = null;

    constructor(instanceId: number) {
        this.instanceId_ = instanceId;
        this.createUIObserver(this.instanceId_);
    }

    private createUIObserver(id: number): uiObserver.UIObserver | null {
        this.observerImpl = uiObserver.createUIObserver(id);
        return this.observerImpl;
    }

    public on(type: string, callback:Callback<uiObserver.DensityInfo>): void {
        if (type == 'densityUpdate') {
            this.observerImpl!.on('densityUpdate', callback);
        }
    }

    public off(type: string, callback?: (() => void) | undefined): void {
        if (this.observerImpl) {
            this.observerImpl!.off(type, callback);
        }
    }
}
