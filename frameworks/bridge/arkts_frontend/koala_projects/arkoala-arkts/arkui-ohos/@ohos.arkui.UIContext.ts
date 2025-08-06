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

import { FrameNode, FrameNodeInternal, FrameNodeUtils } from "arkui/FrameNode"
import { GlobalScope_ohos_font } from "arkui/component/arkui-external"
import { GlobalScope_ohos_measure_utils } from "arkui/component/arkui-external"
import { UIContextDispatchKeyEvent, UIContextAtomicServiceBar } from "arkui/component/arkui-custom"
import { FontOptions, FontInfo } from "@ohos/font"
import { MeasureOptions } from "@ohos/measure"
import { SizeOptions } from "arkui/component/units"
import { ArkUIGeneratedNativeModule } from "#components"
import { int32 } from "@koalaui/common"
import { nullptr } from "@koalaui/interop"
import { _animateTo } from "arkui/handwritten/ArkAnimation"
import { AnimateParam } from 'arkui/component'
import { AnimatorResult, AnimatorOptions, Animator} from "@ohos/animator"
import { Context } from "#external"
import { ArkUIAniModule } from "arkui.ani"
import { Serializer } from "arkui/component/peers/Serializer"
import { componentUtils } from "@ohos/arkui/componentUtils"
import { focusController } from "@ohos/arkui/focusController"
import { Frame } from "arkui/Graphics"
import { KeyEvent } from "arkui/component/common"
import { Nullable } from "arkui/component/enums"
import { KeyProcessingMode } from "arkui/component/focus"
import { uiObserver } from "@ohos/arkui/observer"
import { AlertDialog, AlertDialogParamWithConfirm, AlertDialogParamWithButtons,
    AlertDialogParamWithOptions }from "arkui/component/alertDialog"
import inspector from "@ohos/arkui/inspector"
import router from '@ohos/router'
import promptAction from '@ohos/promptAction';
import { ContextMenu } from 'arkui/component/contextMenu';
import { Router as RouterExt } from 'arkui/handwritten';
import { ComputableState } from '@koalaui/runtime'
import { PeerNode } from 'arkui/PeerNode'

export class UIInspector {
    instanceId_: int32 = -1;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public createComponentObserver(id: string): inspector.ComponentObserver {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let componentObserver = inspector.createComponentObserver(id);
        ArkUIAniModule._Common_Restore_InstanceId();
        return componentObserver;
    }
}

export class Font {
    instanceId_: int32 = 10001;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public registerFont(options: FontOptions) : void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        GlobalScope_ohos_font.registerFont(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public getSystemFontList() : Array<string> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let arrayResult_ = GlobalScope_ohos_font.getSystemFontList();
        ArkUIAniModule._Common_Restore_InstanceId();
        return arrayResult_;
    }
    public getFontByName(fontName : string) : FontInfo {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let fontInfo : FontInfo = GlobalScope_ohos_font.getFontByName(fontName);
        ArkUIAniModule._Common_Restore_InstanceId();
        return fontInfo;
    }
}

export class MeasureUtils {
    instanceId_: int32 = 10001;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public measureText(options: MeasureOptions) : number {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let width = GlobalScope_ohos_measure_utils.measureText(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return width;
    }
    public measureTextSize(options: MeasureOptions) : SizeOptions {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let sizeOptions = GlobalScope_ohos_measure_utils.measureTextSize(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return sizeOptions;
    }
}

export class Router {
    instanceId_: int32 = 100000;
    router_: RouterExt | undefined = undefined;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public setRouter(router: RouterExt) {
        this.router_ = router;
    }
    public getRouter(): RouterExt {
        return this.router_!;
    }
    public pushUrl(options: router.RouterOptions): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = new Promise<void>((resolve, reject) => {
            this.router_!.push(options);
        });
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public replaceUrl(options: router.RouterOptions): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = new Promise<void>((resolve, reject) => {
            this.router_!.replace(options);
        });
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public back(options?:router.RouterOptions): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.back(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public clear(): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.clear();
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public getLength(): string {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getLength();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getParams(): Object {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getParams();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getState(): router.RouterState {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getState();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getStateByIndex(index: number): router.RouterState | undefined {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getStateByIndex(index);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getStateByUrl(url: string): Array<router.RouterState> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getStateByUrl(url);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getStateRoot(): Array<ComputableState<PeerNode>> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getEntryRootValue();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }
}

export interface AtomicServiceBar {
    getBarRect(): Frame;
}

export class AtomicServiceBarInternal implements AtomicServiceBar {
    instanceId_: int32;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public getBarRect(): Frame {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let frame = UIContextAtomicServiceBar.getBarRect();
        ArkUIAniModule._Common_Restore_InstanceId();
        return frame;
    }
}
export class ComponentUtils {
    instanceId_: int32
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }

    public getRectangleById(id: string): componentUtils.ComponentInfo {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
       let componentInformation = componentUtils.getRectangleById(id);
       ArkUIAniModule._Common_Restore_InstanceId();
       return componentInformation;
    }
}


export class FocusController {
    instanceId_: int32
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }

    public clearFocus(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        focusController.clearFocus();
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public requestFocus(key: string): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        focusController.requestFocus(key);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public activate(isActive: boolean, autoInactive?: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        focusController.activate(isActive, autoInactive);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public setAutoFocusTransfer(isAutoFocusTransfer: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        focusController.setAutoFocusTransfer(isAutoFocusTransfer);
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public setKeyProcessingMode(mode: KeyProcessingMode): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        focusController.setKeyProcessingMode(mode);
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

class ContextMenuController {
    instanceId_: int32
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }

    public close(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ContextMenu.close();
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export class PromptAction {
    instanceId_: int32 = 100000;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }

    showToast(options: promptAction.ShowToastOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        promptAction.showToast(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export class UIContext {
    instanceId_: int32 = 100000;
    observer_ :UIObserver |null = null;
    router_: Router;
    focusController_: FocusController;
    componentUtils_: ComponentUtils;
    atomicServiceBar_: AtomicServiceBarInternal;
    uiInspector_: UIInspector | null = null;
    contextMenuController_: ContextMenuController;
    promptAction_: PromptAction | null = null;

    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
        this.focusController_ = new FocusController(instanceId);
        this.componentUtils_ = new ComponentUtils(instanceId);
        this.atomicServiceBar_ = new AtomicServiceBarInternal(instanceId);
        this.contextMenuController_ = new ContextMenuController(instanceId);
        this.router_ = new Router(instanceId);
    }
    public getFont() : Font {
        let font : Font = new Font(this.instanceId_);
        return font;
    }
    public getMeasureUtils() : MeasureUtils {
        let measureUtils : MeasureUtils = new MeasureUtils(this.instanceId_);
        return measureUtils;
    }
    public getFrameNodeById(id: string): FrameNode | null {
        const id_casted = id as (string);
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByKey(id_casted);
        if (retval === nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (!node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getAttachedFrameNodeById(id: string): FrameNode | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = ArkUIGeneratedNativeModule._FrameNode_getAttachedFrameNodeById(id);
        if (retval === nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (!node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getFrameNodeByNodeId(id: number): FrameNode | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeById(id);
        if (retval === nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (!node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getFrameNodeByUniqueId(id: number): FrameNode | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByUniqueId(id);
        if (retval === nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (!node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getHostContext(): Context | undefined {
        return ArkUIAniModule._Common_GetHostContext(this.instanceId_);
    }
    
    public getAtomicServiceBar(): Nullable<AtomicServiceBar> {
        return this.atomicServiceBar_;
    }

    public dispatchKeyEvent(node: number | string, event: KeyEvent): boolean {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = UIContextDispatchKeyEvent.dispatchKeyEvent(node, event);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getFocusController(): FocusController {
        return this.focusController_;
    }

    public getContextMenuController(): ContextMenuController {
        return this.contextMenuController_;
    }

    public getComponentUtils(): ComponentUtils {
        return this.componentUtils_;
    }

    public getRouter(): Router {
        if (this.router_ === undefined) {
            this.router_ = new Router(this.instanceId_);
        }
        return this.router_;
    }

    public setRouter(router: RouterExt): void {
        this.router_.setRouter(router);
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        _animateTo(param, event);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public createAnimator(options: AnimatorOptions): AnimatorResult {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        let animatorRet = Animator.create(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return animatorRet;
    }
    public setFrameCallback(onFrameCallback: ((index: number) => void), onIdleCallback: ((index: number) => void),
                                              delayTime: number): void {
        const onFrameCallback_casted = onFrameCallback as (((index: number) => void))
        const onIdleCallback_casted = onIdleCallback as (((index: number) => void))
        const delayTime_casted = delayTime as (number)
        this.setFrameCallback_serialize(onFrameCallback_casted, onIdleCallback_casted, delayTime_casted)
        return
    }
    private setFrameCallback_serialize(onFrameCallback: ((index: number) => void),
                                                         onIdleCallback: ((index: number) => void),
                                                         delayTime: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onFrameCallback)
        thisSerializer.holdAndWriteCallback(onIdleCallback)
        ArkUIGeneratedNativeModule._SystemOps_setFrameCallback(thisSerializer.asBuffer(),
                                                               thisSerializer.length(), delayTime)
        thisSerializer.release()
    }
    runScopedTask(callback: () => void): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        if (callback !== undefined) {
            callback()
        }
        ArkUIAniModule._Common_Restore_InstanceId()
    }
    clearResourceCache(): void {
        ArkUIGeneratedNativeModule._SystemOps_resourceManagerReset()
    }
    postFrameCallback(frameCallback: FrameCallback): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        const onFrameFunc = frameCallback.onFrame
        const onIdleFunc = frameCallback.onIdle
        this.setFrameCallback(onFrameFunc, onIdleFunc, 0)
        ArkUIAniModule._Common_Restore_InstanceId()
    }
    postDelayedFrameCallback(frameCallback: FrameCallback, delayTime: number): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        const onFrameFunc = frameCallback.onFrame
        const onIdleFunc = frameCallback.onIdle
        this.setFrameCallback(onFrameFunc, onIdleFunc, delayTime)
        ArkUIAniModule._Common_Restore_InstanceId()
    }
    public getUIInspector(): UIInspector {
        if (!this.uiInspector_) {
            this.uiInspector_ = new UIInspector(this.instanceId_);
        }
        return this.uiInspector_ as UIInspector;
    }
    public getUIObserver(): UIObserver {
        if (!this.observer_) {
            this.observer_ = new UIObserver(this.instanceId_);
        }
        return this.observer_ as UIObserver;
    }

    public getPromptAction(): PromptAction {
        if (!this.promptAction_) {
            this.promptAction_ = new PromptAction(this.instanceId_);
        }
        return this.promptAction_ as PromptAction;
    }

    public showAlertDialog(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons |
        AlertDialogParamWithOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        AlertDialog.show(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public freezeUINode(id: number, isFrozen: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        ArkUIGeneratedNativeModule._UIContextImp_freezeUINode1(id, isFrozen ? 1 : 0);
        ArkUIAniModule._Common_Restore_InstanceId()
    }

    // @ts-ignore
    public freezeUINode(id: string, isFrozen: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        ArkUIGeneratedNativeModule._UIContextImp_freezeUINode0(id, isFrozen ? 1 : 0);
        ArkUIAniModule._Common_Restore_InstanceId()
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