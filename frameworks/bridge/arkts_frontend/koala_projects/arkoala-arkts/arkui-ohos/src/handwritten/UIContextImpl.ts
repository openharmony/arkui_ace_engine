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

import { FrameNode, FrameNodeInternal, FrameNodeUtils } from "arkui/FrameNode"
import { ArkUIGeneratedNativeModule } from "#components"
import { int32, int64 } from "@koalaui/common"
import { nullptr, KPointer, KSerializerBuffer, toPeerPtr, RuntimeType,
    runtimeType, Finalizable } from "@koalaui/interop"
import { _animateTo } from "arkui/handwritten/ArkAnimation"
import { AnimateParam, AnimationExtender, KeyframeAnimateParam, KeyframeState } from 'arkui/component'
import { AnimatorResult , AnimatorOptions, Animator, SimpleAnimatorOptions } from "@ohos/animator"
import { UIContext, MeasureUtils, Font, TextMenuController, FocusController, ContextMenuController, ComponentUtils,
    FrameCallback, UIInspector, UIObserver, OverlayManager, PromptAction, AtomicServiceBar, Router, CursorController,
    MediaQuery, ComponentSnapshot, OverlayManagerOptions, DragController, TargetInfo, CustomBuilderWithId }
    from "@ohos/arkui/UIContext"
import { StateManager, ComputableState, GlobalStateManager, StateContext, memoEntry, IncrementalNode } from '@koalaui/runtime'
import { Context, PointerStyle, PixelMap } from "#external"
import { Nullable,  WidthBreakpoint, HeightBreakpoint } from "arkui/component/enums"
import { KeyEvent, PopupCommonOptions, MenuOptions, SheetOptions } from "arkui/component/common"
import { GlobalScope_ohos_font } from "arkui/component/arkui-external"
import router from '@ohos/router'
import { AlertDialog, AlertDialogParamWithConfirm, AlertDialogParamWithButtons,
    AlertDialogParamWithOptions }from "arkui/component/alertDialog"
import { ActionSheet, ActionSheetOptions } from "arkui/component/actionSheet"
import inspector from "@ohos/arkui/inspector"
import { ComponentContent } from 'arkui/ComponentContent'
import overlayManager from '@ohos/overlayManager'
import promptAction, { LevelOrder } from '@ohos/promptAction'
import { ContextMenu } from 'arkui/component/contextMenu'
import { ArkUIAniModule } from "arkui.ani"
import { FontOptions, FontInfo } from "@ohos/font"
import { MeasureOptions } from "@ohos/measure"
import { GlobalScope_ohos_measure_utils } from "arkui/component/arkui-external"
import { SizeOptions, ResourceColor } from "arkui/component/units"
import { Frame } from "arkui/Graphics"
import { TextMenuOptions } from "arkui/component/textCommon"
import { focusController } from "@ohos/arkui/focusController"
import { KeyProcessingMode } from "arkui/component/focus"
import { componentUtils } from "@ohos/arkui/componentUtils"
import { componentSnapshot } from "@ohos/arkui/componentSnapshot"
import { dragController } from "@ohos/arkui/dragController"
import { UIContextDispatchKeyEvent, UIContextAtomicServiceBar } from "arkui/component/arkui-custom"
import { Serializer } from "arkui/component/peers/Serializer"
import { GlobalScopeUicontextFontScale, GlobalScopeUicontextTextMenu } from "arkui/component/arkui-uicontext-text-utils"
import { GlobalScope } from "arkui/component/GlobalScope"
import { mediaquery } from '@ohos/mediaquery'
import { AsyncCallback, CustomBuilder, ArkComponentRootPeer, DragItemInfo, Callback } from 'arkui/component'
import { createUiDetachedRoot, destroyUiDetachedRoot } from "arkui/ArkUIEntry"
import { PeerNode, findPeerNode } from 'arkui/PeerNode'
import { Deserializer } from "arkui/component/peers/Deserializer"
import { Serializer } from "arkui/component/peers/Serializer"
import { KBuffer } from "@koalaui/interop"
import { deserializeAndCallCallback } from "arkui/component/peers/CallbackDeserializeCall"
import { InteropNativeModule } from "@koalaui/interop"
import { LocalStorage } from '../stateManagement/storage/localStorage';
import { Router as RouterExt } from 'arkui/handwritten';
import { ComponentContent } from "arkui/ComponentContent"
import { CommonMethodHandWritten } from "./CommonHandWritten"
import { UIContextUtil } from 'arkui/handwritten/UIContextUtil'

export class ContextRecord {
    uiContext?: UIContext
}

export class FontImpl extends Font {
    instanceId_: int32;
    constructor(instanceId: int32) {
        super()
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

export class MediaQueryImpl extends MediaQuery {
    instanceId_: int32 = 100000;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public matchMediaSync(condition: string): mediaquery.MediaQueryListener {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let mediaQueryListener = mediaquery.matchMediaSync(condition);
        ArkUIAniModule._Common_Restore_InstanceId();
        return mediaQueryListener;
    }
}

export class MeasureUtilsImpl extends MeasureUtils {
    instanceId_: int32;
    constructor(instanceId: int32) {
        super()
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

export class TextMenuControllerImpl extends TextMenuController {
    instanceId_: int32;
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }
    public setMenuOptions(options: TextMenuOptions) : void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        GlobalScopeUicontextTextMenu.setMenuOptions(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }
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

export class FocusControllerImpl extends FocusController {
    instanceId_: int32
    constructor(instanceId: int32) {
        super()
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

class ContextMenuControllerImpl extends ContextMenuController {
    instanceId_: int32
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    public close(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ContextMenu.close();
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export class ComponentUtilsImpl extends ComponentUtils {
    instanceId_: int32
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    public getRectangleById(id: string): componentUtils.ComponentInfo {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
       let componentInformation = componentUtils.getRectangleById(id);
       ArkUIAniModule._Common_Restore_InstanceId();
       return componentInformation;
    }
}

export class ComponentSnapshotImpl extends ComponentSnapshot {
    instanceId_: int32
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    //@ts-ignore
    public get(id: string, callback: AsyncCallback<PixelMap>, options?: componentSnapshot.SnapshotOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        componentSnapshot.get(id, callback, options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public get(id: string, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.get(id, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    // @ts-ignore
    public createFromBuilder(builder: CustomBuilder, callback: AsyncCallback<PixelMap>,
                             delay?: number, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
            return ArkComponentRootPeer.create(undefined);
        }, builder);
        let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
        const destroyCallback = (): void => {
            destroyUiDetachedRoot(rootNode, this.instanceId_);
        }
        ArkUIAniModule._ComponentSnapshot_createFromBuilderWithCallback(
            rootNode, destroyCallback, callback, delay, checkImageStatus, options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public createFromBuilder(builder: CustomBuilder, delay?: number, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
            return ArkComponentRootPeer.create(undefined);
        }, builder);
        let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
        const destroyCallback = (): void => {
            destroyUiDetachedRoot(rootNode, this.instanceId_);
        }
        let pixmap = ArkUIAniModule._ComponentSnapshot_createFromBuilderWithPromise(
            rootNode, destroyCallback, delay, checkImageStatus, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public getSync(id: string, options?: componentSnapshot.SnapshotOptions): PixelMap {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getSync(id, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }
    public getWithUniqueId(uniqueId: number, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getWithUniqueId(uniqueId, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public getSyncWithUniqueId(uniqueId: number, options?: componentSnapshot.SnapshotOptions): PixelMap {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getSyncWithUniqueId(uniqueId, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public createFromComponent<T extends Object>(content: ComponentContent<T>, delay?: number,
        checkImageStatus?: boolean, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let node = content.getFrameNode();
        if (node === undefined || node === null) {
            throw Error("The type of parameters is incorrect.");
        }
        let frameNode = node as FrameNode
        const destroyCallback = (): void => {}
        let pixmap = ArkUIAniModule._ComponentSnapshot_createFromComponentWithPromise(
            toPeerPtr(frameNode), destroyCallback, delay, checkImageStatus, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }
}

export class DragControllerImpl extends DragController {
    instanceId_: int32
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    //@ts-ignore
    public executeDrag(custom: CustomBuilder | DragItemInfo, dragInfo: dragController.DragInfo,
        callback: AsyncCallback<dragController.DragEventParam>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        if (typeof custom === "function") {
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
                return ArkComponentRootPeer.create(undefined);
            }, custom as CustomBuilder);
            let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
            const destroyCallback = (): void => {
                destroyUiDetachedRoot(rootNode, this.instanceId_);
            }
            let dragItemInfoNull: DragItemInfo = {};
            ArkUIAniModule._DragController_executeDragWithCallback(dragItemInfoNull, rootNode,
                destroyCallback, dragInfo, callback);
        } else {
            let destroyCallback = (): void => { };
            let customDragInfo = custom as DragItemInfo;

            if (customDragInfo.pixelMap !== undefined) {
                ArkUIAniModule._DragController_executeDragWithCallback(custom as DragItemInfo, nullptr,
                    destroyCallback, dragInfo, callback);
            } else {
                let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
                const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, customDragInfo.builder as CustomBuilder);
                let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
                destroyCallback = (): void => {
                    destroyUiDetachedRoot(rootNode, this.instanceId_);
                }
                let dragItemInfoNull: DragItemInfo = {};
                ArkUIAniModule._DragController_executeDragWithCallback(dragItemInfoNull, rootNode,
                    destroyCallback, dragInfo, callback);
            }
        }
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public executeDrag(custom: CustomBuilder | DragItemInfo, dragInfo: dragController.DragInfo):
        Promise<dragController.DragEventParam> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let promise = new Promise<dragController.DragEventParam>((resolve, reject) => { });
        if (typeof custom === "function") {
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
                return ArkComponentRootPeer.create(undefined);
            }, custom as CustomBuilder);
            let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
            const destroyCallback = (): void => {
                destroyUiDetachedRoot(rootNode, this.instanceId_);
            }
            let dragItemInfoNull: DragItemInfo = {};
            promise = ArkUIAniModule._DragController_executeDragWithPromise(dragItemInfoNull, rootNode,
                destroyCallback, dragInfo);
        } else {
            let destroyCallback = (): void => { };
            let customDragInfo = custom as DragItemInfo;

            if (customDragInfo.pixelMap !== undefined) {
                promise = ArkUIAniModule._DragController_executeDragWithPromise(custom as DragItemInfo,
                    nullptr, destroyCallback, dragInfo);
            } else {
                let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
                const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, customDragInfo.builder as CustomBuilder);
                let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
                destroyCallback = (): void => {
                    destroyUiDetachedRoot(rootNode, this.instanceId_);
                }
                let dragItemInfoNull: DragItemInfo = {};
                promise = ArkUIAniModule._DragController_executeDragWithPromise(dragItemInfoNull, rootNode,
                    destroyCallback, dragInfo);
            }
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return promise;
    }

    public createDragAction(customArray: Array<CustomBuilder | DragItemInfo>,
        dragInfo: dragController.DragInfo): dragController.DragAction {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);

        let rootNodeArray: Array<KPointer> = [];
        let peerNodeArray: Array<PeerNode> = [];
        let dragItemInfoArray: Array<DragItemInfo> = [];

        for (let element of customArray) {
            if (typeof element === "function") {
                let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
                const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, element as CustomBuilder);
                const rootNode = peerNode ? peerNode.peer.ptr : nullptr;
                if (peerNode && rootNode) {
                    rootNodeArray.push(rootNode);
                    peerNodeArray.push(peerNode);
                }
            } else if (element instanceof DragItemInfo) {
                const dragItemInfo = element as DragItemInfo;
                if (dragItemInfo.pixelMap !== undefined) {
                    dragItemInfoArray.push(dragItemInfo);
                } else {
                    let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
                    const peerNode = context.getDetachedRootEntryManager().createUiDetachedFreeRoot((): PeerNode => {
                        return ArkComponentRootPeer.create(undefined);
                    }, dragItemInfo.builder as CustomBuilder);
                    const rootNode = peerNode ? peerNode.peer.ptr : nullptr;
                    if (peerNode && rootNode) {
                        rootNodeArray.push(rootNode);
                        peerNodeArray.push(peerNode);
                    }
                }
            }
        }

        let destroyCallback = (): void => {
            peerNodeArray.forEach((peerNode) => {
                let rootNode = peerNode ? peerNode.peer.ptr : nullptr;
                destroyUiDetachedRoot(rootNode, this.instanceId_);
            });
            rootNodeArray.length = 0;
            peerNodeArray.length = 0;
        };
        
        let dragAction = ArkUIAniModule._DragController_createDragAction(dragItemInfoArray, rootNodeArray,
            destroyCallback, dragInfo);
        ArkUIAniModule._Common_Restore_InstanceId();
        return dragAction;
    }

    public getDragPreview(): dragController.DragPreview {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let dragPreview = ArkUIAniModule._DragController_getDragPreview();
        ArkUIAniModule._Common_Restore_InstanceId();
        return dragPreview;
    }

    public setDragEventStrictReportingEnabled(enable: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._DragController_setDragEventStrictReportingEnabled(enable);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public cancelDataLoading(key: string): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._DragController_cancelDataLoading(key);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public notifyDragStartRequest(requestStatus: dragController.DragStartRequestStatus): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._DragController_notifyDragStartReques(requestStatus);
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export class RouterImpl extends Router {
    instanceId_: int32 = -1;
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }
    public pushUrl(options: router.RouterOptions): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = new Promise<void>((resolve, reject) => {
            this.router_!.push(options)
        })
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
        this.router_!.back(options)
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

    public getStateRoot(): ComputableState<IncrementalNode> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getEntryRootValue();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public showAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.showAlertBeforeBackPage(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public hideAlertBeforeBackPage(): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.hideAlertBeforeBackPage();
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export class UIInspectorImpl extends UIInspector {
    instanceId_: int32 = -1;
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }
    public createComponentObserver(id: string): inspector.ComponentObserver {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let componentObserver = inspector.createComponentObserver(id);
        ArkUIAniModule._Common_Restore_InstanceId();
        return componentObserver;
    }
}

export class OverlayManagerImpl extends OverlayManager {
    instanceId_: int32 = -1;
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    setOverlayManagerOptions(options: OverlayManagerOptions): boolean {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = overlayManager.setOverlayManagerOptions(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    getOverlayManagerOptions(): OverlayManagerOptions {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = overlayManager.getOverlayManagerOptions();
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    addComponentContent(content: ComponentContent, index?: number): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ptr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            ptr = content.getNodePtr() as (KPointer)
        }
        let idx: number = -1
        if (index !== undefined) {
            idx = index
        }
        overlayManager.addComponentContent(ptr, idx);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    addComponentContentWithOrder(content: ComponentContent, levelOrder?: LevelOrder): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ptr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            ptr = content.getNodePtr() as (KPointer)
        }
        let order: LevelOrder = LevelOrder.clamp(0)
        if (levelOrder !== undefined) {
            order = levelOrder
        }
        overlayManager.addComponentContentWithOrder(ptr, order);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    removeComponentContent(content: ComponentContent): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ptr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            ptr = content.getNodePtr() as (KPointer)
        }
        overlayManager.removeComponentContent(ptr);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    showComponentContent(content: ComponentContent): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ptr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            ptr = content.getNodePtr() as (KPointer)
        }
        overlayManager.showComponentContent(ptr);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    hideComponentContent(content: ComponentContent): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ptr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            ptr = content.getNodePtr() as (KPointer)
        }
        overlayManager.hideComponentContent(ptr);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    showAllComponentContents(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        overlayManager.showAllComponentContents();
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    hideAllComponentContents(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        overlayManager.hideAllComponentContents();
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export class PromptActionImpl extends PromptAction {
    instanceId_: int32 = -1;
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    showToast(options: promptAction.ShowToastOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        promptAction.showToast(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    openToast(options: promptAction.ShowToastOptions): Promise<number> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let promise = promptAction.openToast(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return promise;
    }

    closeToast(toastId: number): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        promptAction.closeToast(toastId);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    //@ts-ignore
    showDialog(options: promptAction.ShowDialogOptions,
        callback: AsyncCallback<promptAction.ShowDialogSuccessResponse>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let optionsInternal: promptAction.ShowDialogOptionsInternal = {};
        const levelOrder = options?.levelOrder?.getOrder?.();
        if (levelOrder !== undefined) {
            optionsInternal.levelOrder = levelOrder as number;
        }
        promptAction.showDialog1(options, callback, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    //@ts-ignore
    showDialog(options: promptAction.ShowDialogOptions): Promise<promptAction.ShowDialogSuccessResponse> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let optionsInternal: promptAction.ShowDialogOptionsInternal = {};
        const levelOrder = options?.levelOrder?.getOrder?.();
        if (levelOrder !== undefined) {
            optionsInternal.levelOrder = levelOrder as number;
        }
        const retval = promptAction.showDialog(options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    //@ts-ignore
    showActionMenu(options: promptAction.ActionMenuOptions,
        callback: AsyncCallback<promptAction.ActionMenuSuccessResponse>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        promptAction.showActionMenu1(options, callback);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    //@ts-ignore
    showActionMenu(options: promptAction.ActionMenuOptions): Promise<promptAction.ActionMenuSuccessResponse> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = promptAction.showActionMenu(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    //@ts-ignore
    openCustomDialog(content: ComponentContent, options?: promptAction.BaseDialogOptions): Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let contentPtr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            contentPtr = content.getNodePtr() as (KPointer)
        }

        let optionsInternal: promptAction.DialogOptionsInternal = {};
        const transition = options?.transition?.getPeer?.();
        if (transition !== undefined) {
            optionsInternal.transition = transition.ptr;
        }
        const dialogTransition = options?.dialogTransition?.getPeer?.();
        if (dialogTransition !== undefined) {
            optionsInternal.dialogTransition = dialogTransition.ptr;
        }
        const maskTransition = options?.maskTransition?.getPeer?.();
        if (maskTransition !== undefined) {
            optionsInternal.maskTransition = maskTransition.ptr;
        }
        const levelOrder = options?.levelOrder?.getOrder?.();
        if (levelOrder !== undefined) {
            optionsInternal.levelOrder = levelOrder as number;
        }
        const retval = promptAction.openCustomDialog1(contentPtr, options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    //@ts-ignore
    openCustomDialog(options: promptAction.CustomDialogOptions): Promise<number> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const peerNode = createUiDetachedRoot((): PeerNode => {
            return ArkComponentRootPeer.create(undefined);
        }, options.builder, this.instanceId_);
        let builderPtr = peerNode.peer.ptr;

        let optionsInternal: promptAction.DialogOptionsInternal = {};
        const transition = options?.transition?.getPeer?.();
        if (transition !== undefined) {
            optionsInternal.transition = transition.ptr;
        }
        const dialogTransition = options?.dialogTransition?.getPeer?.();
        if (dialogTransition !== undefined) {
            optionsInternal.dialogTransition = dialogTransition.ptr;
        }
        const maskTransition = options?.maskTransition?.getPeer?.();
        if (maskTransition !== undefined) {
            optionsInternal.maskTransition = maskTransition.ptr;
        }
        const levelOrder = options?.levelOrder?.getOrder?.();
        if (levelOrder !== undefined) {
            optionsInternal.levelOrder = levelOrder as number;
        }
        const retval = promptAction.openCustomDialog(builderPtr, options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    updateCustomDialog(content: ComponentContent, options: promptAction.BaseDialogOptions): Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let contentPtr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            contentPtr = content.getNodePtr() as (KPointer)
        }
        const retval = promptAction.updateCustomDialog(contentPtr, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    //@ts-ignore
    closeCustomDialog(content: ComponentContent): Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let contentPtr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            contentPtr = content.getNodePtr() as (KPointer)
        }
        const retval = promptAction.closeCustomDialog1(contentPtr);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    //@ts-ignore
    closeCustomDialog(dialogId: number): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        promptAction.closeCustomDialog(dialogId);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    openCustomDialogWithController(content: ComponentContent, controller: promptAction.DialogController,
        options?: promptAction.BaseDialogOptions): Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let contentPtr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            contentPtr = content.getNodePtr() as (KPointer)
        }

        let optionsInternal: promptAction.DialogOptionsInternal = {};
        const transition = options?.transition?.getPeer?.();
        if (transition !== undefined) {
            optionsInternal.transition = transition.ptr;
        }
        const dialogTransition = options?.dialogTransition?.getPeer?.();
        if (dialogTransition !== undefined) {
            optionsInternal.dialogTransition = dialogTransition.ptr;
        }
        const maskTransition = options?.maskTransition?.getPeer?.();
        if (maskTransition !== undefined) {
            optionsInternal.maskTransition = maskTransition.ptr;
        }
        const levelOrder = options?.levelOrder?.getOrder?.();
        if (levelOrder !== undefined) {
            optionsInternal.levelOrder = levelOrder as number;
        }
        const retval = promptAction.openCustomDialogWithController(contentPtr, controller, options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    presentCustomDialog(builder: CustomBuilder | CustomBuilderWithId, controller?: promptAction.DialogController,
        options?: promptAction.DialogOptions): Promise<number> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let builderPtr: KPointer = 0;
        if (builder instanceof CustomBuilder) {
            const peerNode = createUiDetachedRoot((): PeerNode => {
                return ArkComponentRootPeer.create(undefined);
            }, builder, this.instanceId_);
            builderPtr = peerNode.peer.ptr;
        }

        let optionsInternal: promptAction.DialogOptionsInternal = {};
        const transition = options?.transition?.getPeer?.();
        if (transition !== undefined) {
            optionsInternal.transition = transition.ptr;
        }
        const dialogTransition = options?.dialogTransition?.getPeer?.();
        if (dialogTransition !== undefined) {
            optionsInternal.dialogTransition = dialogTransition.ptr;
        }
        const maskTransition = options?.maskTransition?.getPeer?.();
        if (maskTransition !== undefined) {
            optionsInternal.maskTransition = maskTransition.ptr;
        }
        const levelOrder = options?.levelOrder?.getOrder?.();
        if (levelOrder !== undefined) {
            optionsInternal.levelOrder = levelOrder as number;
        }
        const retval = promptAction.presentCustomDialog(builderPtr, controller, options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    getTopOrder(): LevelOrder {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let orderValue: number | undefined = promptAction.getTopOrder();
        let order: LevelOrder = LevelOrder.clamp(0);
        if (orderValue !== undefined) {
            order = LevelOrder.clamp(orderValue as number);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return order;
    }

    getBottomOrder(): LevelOrder {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let orderValue: number | undefined = promptAction.getBottomOrder();
        let order: LevelOrder = LevelOrder.clamp(0);
        if (orderValue !== undefined) {
            order = LevelOrder.clamp(orderValue as number);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return order;
    }

    openPopup(content: ComponentContent, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const content_casted = content as (ComponentContent)
        const target_casted = target as (TargetInfo)
        const options_casted = options as (PopupCommonOptions | undefined)
        return this.openPopup_serialize(content_casted, target_casted, options_casted)
    }

    updatePopup(content: ComponentContent, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const content_casted = content as (ComponentContent)
        const options_casted = options as (PopupCommonOptions)
        const partialUpdate_casted = partialUpdate as (Boolean | undefined)
        return this.updatePopup_serialize(content_casted, options_casted, partialUpdate_casted)
    }

    closePopup(content: ComponentContent): Promise<void> {
        const content_casted = content as (ComponentContent)
        return this.closePopup_serialize(content_casted)
    }

    private openPopup_serialize(content: ComponentContent, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTargetInfo(target)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writePopupCommonOptions(options_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        let ptr: KPointer = 0
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer
        }
        ArkUIGeneratedNativeModule._PromptAction_openPopup(nullptr, ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updatePopup_serialize(content: ComponentContent, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePopupCommonOptions(options)
        let partialUpdate_type : int32 = RuntimeType.UNDEFINED
        partialUpdate_type = runtimeType(partialUpdate)
        thisSerializer.writeInt8((partialUpdate_type).toChar())
        if ((RuntimeType.UNDEFINED) != (partialUpdate_type)) {
            const partialUpdate_value  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdate_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        let ptr: KPointer = 0
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer
        }
        ArkUIGeneratedNativeModule._PromptAction_updatePopup(nullptr, ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private closePopup_serialize(content: ComponentContent): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        let ptr: KPointer = 0
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer
        }
        ArkUIGeneratedNativeModule._PromptAction_closePopup(nullptr, ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }

    openMenu(content: ComponentContent, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const content_casted = content as (ComponentContent)
        const target_casted = target as (TargetInfo)
        const options_casted = options as (MenuOptions | undefined)
        return this.openMenu_serialize(content_casted, target_casted, options_casted)
    }

    updateMenu(content: ComponentContent, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const content_casted = content as (ComponentContent)
        const options_casted = options as (MenuOptions)
        const partialUpdate_casted = partialUpdate as (Boolean | undefined)
        return this.updateMenu_serialize(content_casted, options_casted, partialUpdate_casted)
    }

    closeMenu(content: ComponentContent): Promise<void> {
        const content_casted = content as (ComponentContent)
        return this.closeMenu_serialize(content_casted)
    }

    private openMenu_serialize(content: ComponentContent, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTargetInfo(target)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeMenuOptions(options_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        let ptr: KPointer = 0
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer
        }
        ArkUIGeneratedNativeModule._PromptAction_openMenu(nullptr, ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private updateMenu_serialize(content: ComponentContent, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMenuOptions(options)
        let partialUpdate_type : int32 = RuntimeType.UNDEFINED
        partialUpdate_type = runtimeType(partialUpdate)
        thisSerializer.writeInt8((partialUpdate_type).toChar())
        if ((RuntimeType.UNDEFINED) != (partialUpdate_type)) {
            const partialUpdate_value  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdate_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        let ptr: KPointer = 0
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer
        }
        ArkUIGeneratedNativeModule._PromptAction_updateMenu(nullptr, ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private closeMenu_serialize(content: ComponentContent): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        let ptr: KPointer = 0
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer
        }
        ArkUIGeneratedNativeModule._PromptAction_closeMenu(nullptr, ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}

export class CursorControllerImpl extends CursorController {
    instanceId_: int32
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }

    public restoreDefault(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        GlobalScope.cursorControl_restoreDefault()
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public setCursor(value: PointerStyle): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        GlobalScope.cursorControl_setCursor(value)
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}

export interface DetachedRootEntry {
    compute(): void;
    dispose(): void;
}

export class DetachedRootEntryImpl<T extends IncrementalNode> implements DetachedRootEntry {
    entry: ComputableState<T>;
    constructor(entry: ComputableState<T>) {
        this.entry = entry
    }

    compute(): void {
        this.entry.value;
    }

    dispose(): void {
        this.entry.dispose();
    }
}

export class DetachedRootEntryManager {
    uicontext_: UIContextImpl;
    detachedRoots_: Map<KPointer, DetachedRootEntry>;
    constructor(uicontext: UIContextImpl) {
        this.detachedRoots_ = new Map<KPointer, DetachedRootEntry>();
        this.uicontext_ = uicontext;
    }

    public getDetachedRoots() : Map<KPointer, DetachedRootEntry> {
         return this.detachedRoots_;
     }

    public createUiDetachedRoot(
        peerFactory: () => PeerNode,
        /** @memo */
        builder: () => void
    ): PeerNode {
        let manager = this.uicontext_.stateMgr;
        if (manager === undefined) {
            manager = GlobalStateManager.instance;
        }
        const node = manager.updatableNode<PeerNode>(peerFactory(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            ArkUIAniModule._Common_Sync_InstanceId(this.uicontext_.getInstanceId())
            memoEntry<void>(context, 0, builder)
            ArkUIAniModule._Common_Restore_InstanceId();
            manager.frozen = frozen
        })
        this.detachedRoots_.set(node.value.peer.ptr, new DetachedRootEntryImpl<PeerNode>(node))
        return node.value
    }

    public createUiDetachedFreeRoot(
        nodeFactory: () => IncrementalNode,
        /** @memo */
        builder: () => void
    ): PeerNode | undefined {
        let manager = this.uicontext_.stateMgr;
        if (manager === undefined) {
            manager = GlobalStateManager.instance;
        }
        const node = manager.updatableNode<IncrementalNode>(nodeFactory(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            ArkUIAniModule._Common_Sync_InstanceId(this.uicontext_.getInstanceId())
            memoEntry<void>(context, 0, builder)
            ArkUIAniModule._Common_Restore_InstanceId();
            manager.frozen = frozen
        })

        const inc = node.value;
        const peerNode = findPeerNode(inc);
        if (peerNode === undefined) {
            node.dispose()
            return undefined
        }

        this.detachedRoots_.set(peerNode.peer.ptr, new DetachedRootEntryImpl<IncrementalNode>(node))
        return peerNode
    }

    public destroyUiDetachedRoot(ptr: KPointer): boolean {
        if (!this.detachedRoots_.has(ptr)) {
            return false;
        }

        const root = this.detachedRoots_.get(ptr)!
        this.detachedRoots_.delete(ptr)
        root.dispose()
        return true;
    }
}

export class UIContextImpl extends UIContext {
    instanceId_: int32 = -1;
    stateMgr: StateManager | undefined = undefined;
    observer_ :UIObserver |null = null;
    router_: Router;
    focusController_: FocusControllerImpl;
    componentUtils_: ComponentUtilsImpl;
    componentSnapshot_: ComponentSnapshotImpl;
    dragController_: DragControllerImpl;
    atomicServiceBar_: AtomicServiceBarInternal;
    uiInspector_: UIInspectorImpl | null = null;
    contextMenuController_: ContextMenuControllerImpl;
    overlayManager_: OverlayManagerImpl | null = null;
    promptAction_: PromptActionImpl | null = null;
    cursorController_: CursorControllerImpl;
    font_: FontImpl;
    measureUtils_: MeasureUtilsImpl;
    textMenuController_: TextMenuControllerImpl;
    detachedRootEntryManager_: DetachedRootEntryManager;
    isDebugMode_: boolean = false;

    bufferSize = 4096
    buffer: KBuffer = new KBuffer(this.bufferSize)
    position: int64 = 0
    deserializer: Deserializer = new Deserializer(this.buffer.buffer, this.bufferSize)

    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
        this.focusController_ = new FocusControllerImpl(instanceId);
        this.componentUtils_ = new ComponentUtilsImpl(instanceId);
        this.componentSnapshot_ = new ComponentSnapshotImpl(instanceId);
        this.dragController_ = new DragControllerImpl(instanceId);
        this.atomicServiceBar_ = new AtomicServiceBarInternal(instanceId);
        this.contextMenuController_ = new ContextMenuControllerImpl(instanceId);
        this.cursorController_ = new CursorControllerImpl(instanceId);
        this.font_ = new FontImpl(instanceId);
        this.measureUtils_ = new MeasureUtilsImpl(instanceId);
        this.textMenuController_ = new TextMenuControllerImpl(instanceId);
        this.detachedRootEntryManager_ = new DetachedRootEntryManager(this);
        this.isDebugMode_ = ArkUIAniModule._IsDebugMode(instanceId) !== 0;
        this.router_ = new RouterImpl(instanceId);
    }
    public getInstanceId() : int32 {
        return this.instanceId_;
    }
    public getDetachedRootEntryManager() : DetachedRootEntryManager {
        return this.detachedRootEntryManager_;
    }
    dispatchCallback(buffer: KSerializerBuffer, length: int32): void {
        if (length <= 0) {
            return
        }

        if (this.position + length > this.bufferSize) {
            throw Error("Callback buffer of UIContextImpl is full!")
        }

        InteropNativeModule._CopyBuffer(this.buffer.buffer + this.position, length, buffer)
        this.position += length
    }

    callCallbacks(): void {
        if (this.position === 0) {
            return
        }
        this.deserializer.resetCurrentPosition()
        this.runScopedTask(() => {
            while (this.deserializer.currentPosition() < this.position) {
                deserializeAndCallCallback(this.deserializer)
            }
        })
        this.position = 0;
    }

    public getFont() : Font {
        return this.font_;
    }
    public getMediaQuery(): MediaQuery {
        return new MediaQueryImpl(this.instanceId_);
    }
    public getMeasureUtils() : MeasureUtils {
        return this.measureUtils_;
    }
    public getTextMenuController() : TextMenuController {
        return this.textMenuController_;
    }
    public isFollowingSystemFontScale() : boolean {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let follow = GlobalScopeUicontextFontScale.isFollowingSystemFontScale();
        ArkUIAniModule._Common_Restore_InstanceId();
        return follow;
    }
    public getMaxFontScale() : number {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let fontScale = GlobalScopeUicontextFontScale.getMaxFontScale();
        ArkUIAniModule._Common_Restore_InstanceId();
        return fontScale;
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
    public getSharedLocalStorage(): LocalStorage | undefined {
        return  ArkUIAniModule._Common_GetSharedLocalStorage();
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

    public getComponentSnapshot(): ComponentSnapshot {
        return this.componentSnapshot_;
    }

    public getDragController(): DragController {
        return this.dragController_;
    }

    public getCursorController(): CursorController {
        return this.cursorController_;
    }

    public getRouter(): Router {
        if (this.router_ === undefined) {
            this.router_ = new RouterImpl(this.instanceId_)
        }
        return this.router_
    }

    public setRouter(router: RouterExt) {
        if (this.router_ === undefined) {
            this.router_ = new RouterImpl(this.instanceId_)
        }
        this.router_.setRouter(router);
    }

    public keyframeAnimateTo(param: KeyframeAnimateParam, keyframes: Array<KeyframeState>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        AnimationExtender.KeyframeAnimationImpl(param, keyframes);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        _animateTo(param, event);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public animateToImmediately(value: AnimateParam, event: Callback<void>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        CommonMethodHandWritten.hookCommonMethodAnimateToImmediatelyImpl(value, () => {
            event(undefined);
        });
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public createAnimator(options: AnimatorOptions | SimpleAnimatorOptions): AnimatorResult {
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
      public getWindowName(): string | undefined {
        return  this.getWindowName_serialize();

    }
    public getWindowWidthBreakpoint(): WidthBreakpoint {

        return this.getWindowWidthBreakpoint_serialize() as WidthBreakpoint;

    }
    public getWindowHeightBreakpoint(): HeightBreakpoint {
      return this.getWindowHeightBreakpoint_serialize() as HeightBreakpoint;

    }
    public vp2px(value: number): number {
         return ArkUIAniModule._Common_vp2px(value, this.instanceId_);
    }
    public px2vp(value: number): number {
         return ArkUIAniModule._Common_px2vp(value, this.instanceId_);
    }
    public fp2px(value: number): number {
         return ArkUIAniModule._Common_fp2px(value, this.instanceId_);
    }
    public px2fp(value: number): number {
         return ArkUIAniModule._Common_px2fp(value, this.instanceId_);
    }
    public lpx2px(value: number): number {
          return ArkUIAniModule._Common_lpx2px(value, this.instanceId_);
    }
    public px2lpx(value: number): number {
         return ArkUIAniModule._Common_px2lpx(value, this.instanceId_);
    }

    private getWindowName_serialize(): string | undefined {
        return ArkUIGeneratedNativeModule._UIContext_getWindowName(this.instanceId_);
    }
    private getWindowWidthBreakpoint_serialize(): WidthBreakpoint {
        const widthBreakpoint = ArkUIGeneratedNativeModule._UIContext_getWindowWidthBreakpoint(this.instanceId_);
        let widthBreakpointEnum = widthBreakpoint  as int32 as WidthBreakpoint;
        return widthBreakpointEnum;

    }
    private getWindowHeightBreakpoint_serialize(): HeightBreakpoint {
        const heightBreakpoint = ArkUIGeneratedNativeModule._UIContext_getWindowHeightBreakpoint(this.instanceId_);
        let heightBreakpointEnum = heightBreakpoint as int32 as HeightBreakpoint;
        return heightBreakpointEnum;
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
            this.uiInspector_ = new UIInspectorImpl(this.instanceId_);
        }
        return this.uiInspector_ as UIInspector;
    }
    public getUIObserver(): UIObserver {
        if (!this.observer_) {
            this.observer_ = new UIObserver(this.instanceId_);
        }
        return this.observer_ as UIObserver;
    }

    public getOverlayManager(): OverlayManager {
        if (!this.overlayManager_) {
            this.overlayManager_ = new OverlayManagerImpl(this.instanceId_);
        }
        if (this.overlayManager_) {
            const options: OverlayManagerOptions = { renderRootOverlay: true, enableBackPressedEvent: false };
            this.overlayManager_!.setOverlayManagerOptions(options);
        }
        return this.overlayManager_ as OverlayManager;
    }

    public setOverlayManagerOptions(options: OverlayManagerOptions): boolean {
        if (!this.overlayManager_) {
            this.overlayManager_ = new OverlayManagerImpl(this.instanceId_);
        }
        if (this.overlayManager_) {
            return this.overlayManager_!.setOverlayManagerOptions(options);
        }
        return false;
    }

    public getOverlayManagerOptions(): OverlayManagerOptions {
        if (!this.overlayManager_) {
            this.overlayManager_ = new OverlayManagerImpl(this.instanceId_);
        }
        if (this.overlayManager_) {
            return this.overlayManager_!.getOverlayManagerOptions();
        }
        return {};
    }

    public getPromptAction(): PromptAction {
        if (!this.promptAction_) {
            this.promptAction_ = new PromptActionImpl(this.instanceId_);
        }
        return this.promptAction_ as PromptAction;
    }

    public showAlertDialog(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons |
        AlertDialogParamWithOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        AlertDialog.show(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public showActionSheet(options: ActionSheetOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ActionSheet.show(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public freezeUINode(id: number, isFrozen: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode1(id, isFrozen ? 1 : 0);
        ArkUIAniModule._Common_Restore_InstanceId()
    }

    // @ts-ignore
    public freezeUINode(id: string, isFrozen: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode0(id, isFrozen ? 1 : 0);
        ArkUIAniModule._Common_Restore_InstanceId()
    }

    public setUIStates(callback: () => void): void {
        if (this.checkThread(this.instanceId_)) {
            callback();
        } else {
            this.stateMgr?.scheduleCallback(callback);
        }
    }

    public checkThread(id: int32) : boolean {
        return ArkUIAniModule._CheckIsUIThread(id) !== 0;
    }

    public openBindSheet(content: ComponentContent, options?: SheetOptions, targetId?: number) : Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const content_component = content as ComponentContent
        let frameNode = content_component.getFrameNode()
        let contentPtr = toPeerPtr(frameNode as FrameNode) as KPointer

        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSheetOptions(options_value)
        }

        let targetId_type : int32 = RuntimeType.UNDEFINED
        targetId_type = runtimeType(targetId)
        thisSerializer.writeInt8(targetId_type as int32)
        if ((RuntimeType.UNDEFINED) != (targetId_type)) {
            const targetId_value  = targetId!
            thisSerializer.writeNumber(targetId_value)
        }
        ArkUIGeneratedNativeModule._UIContext_openBindSheet(contentPtr, thisSerializer.asBuffer(), thisSerializer.length());
        ArkUIAniModule._Common_Restore_InstanceId();
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        thisSerializer.release()
        return retval;
    }

    public updateBindSheet(content: ComponentContent, options?: SheetOptions, partialUpdate?: boolean) : Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const content_component = content as ComponentContent
        let frameNode = content_component.getFrameNode()
        let contentPtr = toPeerPtr(frameNode as FrameNode) as KPointer

        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSheetOptions(options_value)
        }

        let partialUpdate_type : int32 = RuntimeType.UNDEFINED
        partialUpdate_type = runtimeType(partialUpdate)
        thisSerializer.writeInt8(partialUpdate_type as int32)
        if ((RuntimeType.UNDEFINED) != (partialUpdate_type)) {
            const partialUpdate_value  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdate_value)
        }
        ArkUIGeneratedNativeModule._UIContext_updateBindSheet(contentPtr, thisSerializer.asBuffer(), thisSerializer.length());
        ArkUIAniModule._Common_Restore_InstanceId();
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        thisSerializer.release()
        return retval;
    }

    public closeBindSheet(content: ComponentContent) : Promise<void> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const content_component = content as ComponentContent
        let frameNode = content_component.getFrameNode()
        let contentPtr = toPeerPtr(frameNode as FrameNode) as KPointer

        ArkUIGeneratedNativeModule._UIContext_closeBindSheet(contentPtr);
        ArkUIAniModule._Common_Restore_InstanceId();
        const thisSerializer : Serializer = Serializer.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        thisSerializer.release()
        return retval;
    }
}
