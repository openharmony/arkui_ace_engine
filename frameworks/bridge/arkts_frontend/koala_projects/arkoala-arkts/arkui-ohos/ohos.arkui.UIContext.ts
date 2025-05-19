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

import { FrameNode, FrameNodeInternal, FrameNodeUtils } from "./src/FrameNode"
import { GlobalScope_ohos_font } from "./src/component/arkui-external"
import { GlobalScope_ohos_measure_utils } from "./src/component/arkui-external"
import { UIContextDispatchKeyEvent, UIContextAtomicServiceBar } from "./src/component/arkui-custom"
import { FontOptions, FontInfo } from "@ohos/font/font"
import { MeasureOptions } from "@ohos/measure"
import { SizeOptions } from "./src/component/units"
import { ArkUIGeneratedNativeModule } from "#components"
import { int32 } from "@koalaui/common"
import { nullptr } from "@koalaui/interop"
import { _animateTo } from "./src/handwritten/ArkAnimation"
import { AnimateParam } from './src/component'
import { AnimatorResult, AnimatorOptions, Animator} from "@ohos/animator"
import { Context } from "#external"
import { ArkUIAniModule } from "arkui.ani"
import { Serializer } from "./src/component/peers/Serializer"
import { componentUtils } from "@ohos/arkui/componentUtils"
import { focusController } from "@ohos/arkui/focusController"
import { Frame } from "./src/component/arkui-graphics"
import { KeyEvent } from "./src/component/common"
import { Nullable } from "./src/component/enums"
import { KeyProcessingMode } from "./src/component/focus"
import {observer} from "@ohos/observer"
import router from './ohos.router'

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
        return new Array<string>();
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
        return 0;
    }
    public measureTextSize(options: MeasureOptions) : SizeOptions {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let sizeOptions = GlobalScope_ohos_measure_utils.measureTextSize(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return {};
    }
}

export class Router {
    public pushUrl(options: router.RouterOptions): Promise<void> {
        return new Promise<void>((resolve, reject) => {
            router.pushUrl(options)
        })
    }

    public back(options?:router.RouterOptions): void {
        router.back(options)
    }

    public clear(): void {
        router.clear()
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

export class UIContext {
    instanceId_: int32 = 100000;
    observer_ :UIObserver |null = null;
    router_: Router = new Router()
    focusController_: FocusController;
    componentUtils_: ComponentUtils;
    atomicServiceBar_: AtomicServiceBarInternal;

    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
        this.focusController_ = new FocusController(instanceId);
        this.componentUtils_ = new ComponentUtils(instanceId);
        this.atomicServiceBar_ = new AtomicServiceBarInternal(instanceId);
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
        if (retval == nullptr) {
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
        if (retval == nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getFrameNodeByNodeId(id: number): FrameNode | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeById(id);
        if (retval == nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getFrameNodeByUniqueId(id: number): FrameNode | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = ArkUIGeneratedNativeModule._FrameNode_getFrameNodeByUniqueId(id);
        if (retval == nullptr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return null;
        }
        let node = FrameNodeUtils.searchNodeInRegisterProxy(retval);
        if (node) {
            node = FrameNodeUtils.createFrameNode(this, retval);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
    }
    getHostContext(): Context | undefined {
        return ArkUIAniModule._Common_GetHostContext();
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

    public getComponentUtils(): ComponentUtils {
        return this.componentUtils_;
    }

    public getRouter(): Router {
        if (this.router_ === undefined) {
            this.router_ = new Router()
        }
        return this.router_
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
    public getUIObserver(): UIObserver {
        if (!this.observer_) {
            this.observer_ = new UIObserver(this.instanceId_);
        }
        return this.observer_ as UIObserver;
    }
}
export abstract class FrameCallback {
    onFrame(frameTimeInNano: number): void {}
    onIdle(timeLeftInNano: number): void {}
}

export class UIObserver {
    private instanceId_: number = 100000;
    private observerImpl: observer.UIObserver | null = null;

    constructor(instanceId: number) {
        this.instanceId_ = instanceId;
        this.createUIObserver(this.instanceId_);
    }

    private createUIObserver(id: number): observer.UIObserver | null {
        this.observerImpl = observer.createUIObserver(id);
        return this.observerImpl;
    }

    public on(type: string, callback: () => void): void {
        if (this.observerImpl) {
            this.observerImpl!.on(type, callback);
        }
    }

    public off(type: string, callback?: (() => void) | undefined): void {
        if (this.observerImpl) {
            this.observerImpl!.off(type, callback);
        }
    }
}