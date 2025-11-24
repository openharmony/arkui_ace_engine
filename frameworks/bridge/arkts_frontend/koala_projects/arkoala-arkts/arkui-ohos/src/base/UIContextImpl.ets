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

import { FrameNode, FrameNodeUtils } from 'arkui/FrameNode';
import { ArkUIGeneratedNativeModule } from '#components';
import { int32, int64 } from '@koalaui/common';
import { nullptr, KPointer, KSerializerBuffer, toPeerPtr, RuntimeType,
    runtimeType, Finalizable, SerializerBase, DeserializerBase } from '@koalaui/interop';
import { _animateTo } from 'arkui/base/ArkAnimation';
import { AnimateParam, KeyframeAnimateParam, KeyframeState } from 'arkui/framework';
import { AnimatorResult , AnimatorOptions, Animator, SimpleAnimatorOptions } from '@ohos/animator';
import { UIContext, MeasureUtils, TextMenuController, Font, FocusController, ContextMenuController, ComponentUtils,
    FrameCallback, UIInspector, UIObserver, OverlayManager, PromptAction, AtomicServiceBar, Router, CursorController,
    MediaQuery, ComponentSnapshot, OverlayManagerOptions, DragController, TargetInfo, CustomBuilderWithId,
    KeyboardAvoidMode, DynamicSyncScene, SwiperDynamicSyncScene, SwiperDynamicSyncSceneType, PageInfo} from '@ohos/arkui/UIContext';
import { StateManager, ComputableState, GlobalStateManager, memoEntry, memoEntry1,
    IncrementalNode } from '@koalaui/runtime';
import { StateContext } from 'arkui.incremental.runtime.state';
import { Context, PointerStyle, PixelMap } from '#external';
import { Nullable,  WidthBreakpoint, HeightBreakpoint } from 'arkui/component/enums';
import { KeyEvent, PopupCommonOptions, MenuOptions, ExpectedFrameRateRange } from 'arkui/component/common';
import { GlobalScope_ohos_font } from '#generated';
import router from '@ohos/router';
import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons,
    AlertDialogParamWithOptions }from "arkui/component/alertDialog"
import { ActionSheetOptions } from "arkui/component/actionSheet"
import { TimePickerDialogOptions } from "arkui/component/timePicker"
import { TextPickerDialogOptions } from "arkui/component/textPicker"
import { DatePickerDialogOptions } from "arkui/component/datePicker"
import inspector from "@ohos/arkui/inspector"
import { ComponentContent } from 'arkui/ComponentContent'
import overlayManager from '@ohos/overlayManager'
import promptAction, { LevelOrder } from '@ohos/promptAction'
import { ArkUIAniModule } from "arkui.ani"
import { default as font } from "@ohos/font"
import { MeasureOptions } from "@ohos/measure"
import { GlobalScope_ohos_measure_utils } from "#generated"
import { GlobalScopeUicontextTextMenu } from "#generated"
import { GlobalScopeUicontextFontScale } from "#generated"
import { SizeOptions, ResourceColor } from "arkui/component/units"
import { Frame } from "arkui/Graphics"
import { TextMenuOptions } from "arkui/component/textCommon"
import { focusController } from "@ohos/arkui/focusController"
import { KeyProcessingMode } from "arkui/component/focus"
import { componentUtils } from "@ohos/arkui/componentUtils"
import { componentSnapshot } from "@ohos/arkui/componentSnapshot"
import { dragController } from "@ohos/arkui/dragController"
import { UIContextAtomicServiceBar, UIContextGetInfo } from "arkui/component/idlize"
import { GlobalScope } from "#generated"
import { default as mediaquery } from '@ohos/mediaquery'
import { CustomBuilder, CustomBuilderT, ArkComponentRootPeer, DragItemInfo, Callback } from 'arkui/framework'
import { AsyncCallback } from "#generated";
import { createUiDetachedRoot, createUiDetachedRootT, destroyUiDetachedRoot } from 'arkui/ArkUIEntry';
import { PeerNode, findPeerNode } from 'arkui/PeerNode';
import { KBuffer } from '@koalaui/interop';
import { deserializeAndCallCallback } from 'arkui/framework/peers/CallbackDeserializeCall';
import { InteropNativeModule } from '@koalaui/interop';
import { LocalStorage } from '../stateManagement/storage/localStorage';
import { Router as RouterExt } from 'arkui/base';
import { PromptActionExtender, FrameNodeExtender, AlertDialog, ActionSheet, AnimationExtender,
    SystemOps, DialogExtender } from '../framework';
import { default as uiObserver } from '@ohos/arkui/observer';
import { EntryPoint, NavInterface } from "../component/customComponent"
import { AsyncCallback as routerAsyncCallback } from "@ohos.base"
import { IUIContext } from "arkui/component/idlize"
  import { PathStackUtils } from './ArkNavPathStack';

export class ContextRecord {
    uiContext?: UIContext
}

export class FontImpl extends Font {
    instanceId_: int32;
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }
    public registerFont(options: font.FontOptions) : void {
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
    public getFontByName(fontName : string) : font.FontInfo {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let fontInfo : font.FontInfo = GlobalScope_ohos_font.getFontByName(fontName);
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
    public measureText(options: MeasureOptions) : double {
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
        // ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        // ArkUIAniModule._Common_Restore_InstanceId();
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
    public get(id: string, callback: routerAsyncCallback<PixelMap>, options?: componentSnapshot.SnapshotOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        componentSnapshot.get(id, callback, options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public get(id: string, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.get(id, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    // @ts-ignore
    public createFromBuilder(builder: CustomBuilder, callback: AsyncCallback<PixelMap>,
                             delay?: int, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const peerNode = createUiDetachedRoot((): PeerNode => {
            return ArkComponentRootPeer.create(undefined);
        }, builder, this.instanceId_);
        let rootNode = peerNode.peer.ptr;
        const destroyCallback = (): void => {
            destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
        }
        ArkUIAniModule._ComponentSnapshot_createFromBuilderWithCallback(
            rootNode, destroyCallback, callback, delay, checkImageStatus, options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public createFromBuilder(builder: CustomBuilder, delay?: int, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const peerNode = createUiDetachedRoot((): PeerNode => {
            return ArkComponentRootPeer.create(undefined);
        }, builder, this.instanceId_);
        let rootNode = peerNode.peer.ptr;
        const destroyCallback = (): void => {
            destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
        }
        let pixmap = ArkUIAniModule._ComponentSnapshot_createFromBuilderWithPromise(
            rootNode, destroyCallback, delay, checkImageStatus, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public getSync(id: string, options?: componentSnapshot.SnapshotOptions): PixelMap | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getSync(id, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }
    public getWithUniqueId(uniqueId: int, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getWithUniqueId(uniqueId, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public getSyncWithUniqueId(uniqueId: int, options?: componentSnapshot.SnapshotOptions): PixelMap {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getSyncWithUniqueId(uniqueId, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public createFromComponent<T extends Object>(content: ComponentContent<T>, delay?: int,
        checkImageStatus?: boolean, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
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
            const peerNode = createUiDetachedRoot((): PeerNode => {
                return ArkComponentRootPeer.create(undefined);
            }, custom as CustomBuilder);
            let rootNode = peerNode.peer.ptr;
            const destroyCallback = (): void => {
                destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
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
                const peerNode = createUiDetachedRoot((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, customDragInfo.builder as CustomBuilder);
                let rootNode = peerNode.peer.ptr;
                destroyCallback = (): void => {
                    destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
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
        Promise<dragController.DragEventParam> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let promise = new Promise<dragController.DragEventParam>((resolve, reject) => { });
        if (typeof custom === "function") {
            const peerNode = createUiDetachedRoot((): PeerNode => {
                return ArkComponentRootPeer.create(undefined);
            }, custom as CustomBuilder);
            let rootNode = peerNode.peer.ptr;
            const destroyCallback = (): void => {
                destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
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
                const peerNode = createUiDetachedRoot((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, customDragInfo.builder as CustomBuilder);
                let rootNode = peerNode.peer.ptr;
                destroyCallback = (): void => {
                    destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
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
                const builder = element as CustomBuilder;
                const peerNode = createUiDetachedRoot((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, builder);
                const rootNode = peerNode.peer.ptr;
                rootNodeArray.push(rootNode);
                peerNodeArray.push(peerNode);
            } else if (element instanceof DragItemInfo) {
                const dragItemInfo = element as DragItemInfo;
                if (dragItemInfo.pixelMap !== undefined) {
                    dragItemInfoArray.push(dragItemInfo);
                } else {
                    const peerNode = createUiDetachedRoot((): PeerNode => {
                        return ArkComponentRootPeer.create(undefined);
                    }, dragItemInfo.builder as CustomBuilder);
                    const rootNode = peerNode.peer.ptr;
                    rootNodeArray.push(rootNode);
                    peerNodeArray.push(peerNode);
                }
            }
        }

        let destroyCallback = (): void => {
            peerNodeArray.forEach((peerNode) => {
                destroyUiDetachedRoot(peerNode.peer.ptr, this.instanceId_);
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
        let result = this.router_!.push(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public pushUrl(options: router.RouterOptions, mode: router.RouterMode): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.push(options, mode);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public pushUrl(options: router.RouterOptions, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public pushUrl(options: router.RouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public pushNamedRoute(options: router.NamedRouterOptions): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.pushNamedRoute(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public pushNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.pushNamedRoute(options, mode);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public pushNamedRoute(options: router.NamedRouterOptions, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public pushNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public replaceUrl(options: router.RouterOptions): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.replace(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public replaceUrl(options: router.RouterOptions, mode: router.RouterMode): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.replace(options, mode);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public replaceUrl(options: router.RouterOptions, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public replaceUrl(options: router.RouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public replaceNamedRoute(options: router.NamedRouterOptions): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.replaceNamedRoute(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode): Promise<void> {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.replaceNamedRoute(options, mode);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public back(options?:router.RouterOptions): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.back(options)
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public back(index: int, params?: Object): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.back(index, params);
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

    public getStateByIndex(index: int): router.RouterState | undefined {
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

    public getStateRoot(): ComputableState<IncrementalNode> | undefined {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getEntryRootValue();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getPreState(): ComputableState<IncrementalNode> | undefined {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getPreState();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public registerNamedRouter(routerName: string, instance: EntryPoint, param: NavInterface): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.registerNamedRouter(routerName, instance, param);
        ArkUIAniModule._Common_Restore_InstanceId();
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
    public createComponentObserver(id: string): inspector.ComponentObserver | undefined {
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

    addComponentContent(content: ComponentContent, index?: int32): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ptr: KPointer = 0
        if (content.getNodePtr() !== undefined) {
            ptr = content.getNodePtr() as (KPointer)
        }
        let idx: int32 = -1
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

    openToast(options: promptAction.ShowToastOptions): Promise<int32> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let promise = promptAction.openToast(options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return promise;
    }

    closeToast(toastId: int32): void {
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
    openCustomDialog(options: promptAction.CustomDialogOptions): Promise<int32> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let builderOptions: promptAction.DialogBuilderOptions = {};
        const peerNode = createUiDetachedRoot((): PeerNode => {
            return ArkComponentRootPeer.create(undefined);
        }, options.builder, this.instanceId_);
        builderOptions.builder = peerNode.peer.ptr;
        builderOptions.destroyFunc = (ptr: KPointer): void => {
            destroyUiDetachedRoot(ptr, this.instanceId_);
        };

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
        const retval = promptAction.openCustomDialog(builderOptions, options, optionsInternal);
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
    closeCustomDialog(dialogId: int32): void {
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

    presentCustomDialog(builder: CustomBuilder | CustomBuilderT<int32>, controller?: promptAction.DialogController,
        options?: promptAction.DialogOptions): Promise<int32> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let builderOptions: promptAction.DialogBuilderOptions = {};
        if (builder instanceof CustomBuilder) {
            const peerNode = createUiDetachedRoot((): PeerNode => {
                return ArkComponentRootPeer.create(undefined);
            }, builder as CustomBuilder, this.instanceId_);
            builderOptions.builder = peerNode.peer.ptr;
        } else {
            builderOptions.builderWithId = (dialogId: int32): KPointer => {
                const peerNode = createUiDetachedRootT<int32>((): PeerNode => {
                    return ArkComponentRootPeer.create(undefined);
                }, builder as CustomBuilderT<int32>, dialogId, this.instanceId_);
                return peerNode.peer.ptr;
            };
        }
        builderOptions.destroyFunc = (ptr: KPointer): void => {
            destroyUiDetachedRoot(ptr, this.instanceId_);
        };

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
        const retval = promptAction.presentCustomDialog(builderOptions, controller, options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    getTopOrder(): LevelOrder | undefined {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let orderValue: number | undefined = promptAction.getTopOrder();
        let order: LevelOrder | undefined = undefined;
        if (orderValue !== undefined) {
            order = LevelOrder.clamp(orderValue as number);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return order;
    }

    getBottomOrder(): LevelOrder | undefined {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let orderValue: number | undefined = promptAction.getBottomOrder();
        let order: LevelOrder | undefined = undefined;
        if (orderValue !== undefined) {
            order = LevelOrder.clamp(orderValue as number);
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return order;
    }

    openPopup(content: ComponentContent, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        let ptr: KPointer = 0;
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer;
        }
        return PromptActionExtender.openPopup(ptr, target, options);
    }

    updatePopup(content: ComponentContent, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        let ptr: KPointer = 0;
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer;
        }
        return PromptActionExtender.updatePopup(ptr, options, partialUpdate);
    }

    closePopup(content: ComponentContent): Promise<void> {
        let ptr: KPointer = 0;
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer;
        }
        return PromptActionExtender.closePopup(ptr);
    }

    openMenu(content: ComponentContent, target: TargetInfo, options?: MenuOptions): Promise<void> {
        let ptr: KPointer = 0;
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer;
        }
        return PromptActionExtender.openMenu(ptr, target, options);
    }

    updateMenu(content: ComponentContent, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        let ptr: KPointer = 0;
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer;
        }
        return PromptActionExtender.updateMenu(ptr, options, partialUpdate);
    }

    closeMenu(content: ComponentContent): Promise<void> {
        let ptr: KPointer = 0;
        if (content.getNodePtr() != undefined) {
            ptr = content.getNodePtr() as KPointer;
        }
        return PromptActionExtender.closeMenu(ptr);
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

    public setDetachedRootNode(nativeNode: KPointer, rootNode: ComputableState<IncrementalNode>): void {
        this.detachedRoots_.set(nativeNode, new DetachedRootEntryImpl<IncrementalNode>(rootNode));
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
        const node = manager.updatableNodeEx<PeerNode>(peerFactory(), (context: StateContext) => {
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

    public createUiDetachedRootT<T>(
        peerFactory: () => PeerNode,
        /** @memo */
        builder: (arg: T) => void,
        arg: T
    ): PeerNode {
        let manager = this.uicontext_.stateMgr;
        if (manager === undefined) {
            manager = GlobalStateManager.instance;
        }
        const node = manager.updatableNodeEx<PeerNode>(peerFactory(), (context: StateContext) => {
            const frozen = manager.frozen
            manager.frozen = true
            ArkUIAniModule._Common_Sync_InstanceId(this.uicontext_.getInstanceId())
            memoEntry1<T, void>(context, 0, builder, arg)
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
        const node = manager.updatableNodeEx<IncrementalNode>(nodeFactory(), (context: StateContext) => {
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
    keyboardAvoidMode_: KeyboardAvoidMode = KeyboardAvoidMode.OFFSET;
    cursorController_: CursorControllerImpl;
    font_: FontImpl;
    measureUtils_: MeasureUtilsImpl;
    textMenuController_: TextMenuControllerImpl;
    detachedRootEntryManager_: DetachedRootEntryManager;
    isDebugMode_: boolean = false;

    bufferSize = 4096
    buffer: KBuffer = new KBuffer(this.bufferSize)
    position: int64 = 0
    deserializer: DeserializerBase = new DeserializerBase(this.buffer.buffer, this.bufferSize)

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
        // if (length <= 0) {
        //     return
        // }

        // if (this.position + length > this.bufferSize) {
        // }

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
        const retval = FrameNodeExtender.getFrameNodeByKey(id_casted);
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
        const retval = FrameNodeExtender.getAttachedFrameNodeById(id);
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
        const retval = FrameNodeExtender.getFrameNodeById(id);
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
    public getFrameNodeByUniqueId(id: int): FrameNode | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        const retval = FrameNodeExtender.getFrameNodeByUniqueId(id);
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
     public getPageInfoByUniqueId(id: int): PageInfo {
        const navDestinationInfo = ArkUIAniModule._CustomNode_QueryNavDestinationInfo1(id);
        const routerPageInfo = ArkUIAniModule._CustomNode_QueryRouterPageInfo1(id);
        if (navDestinationInfo) {
            let param = PathStackUtils.getParamByNavDestinationId(navDestinationInfo.navDestinationId);
            navDestinationInfo.param = param ? param! : undefined;
        }
        if (routerPageInfo) {
            routerPageInfo.context = this;
        }
        let pageInfo: PageInfo = {
            navDestinationInfo: navDestinationInfo,
            routerPageInfo: routerPageInfo
        }
        return pageInfo;
    }
    public getNavigationInfoByUniqueId(id: int): uiObserver.NavigationInfo | undefined {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        let navigationInfo = UIContextGetInfo.getNavigationInfoByUniqueId(id);
        ArkUIAniModule._Common_Restore_InstanceId()
        return navigationInfo;
    }
    getHostContext(): Context | undefined {
        return ArkUIAniModule._Common_GetHostContext(this.instanceId_);
    }

    setKeyboardAvoidMode(mode: KeyboardAvoidMode): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._SetKeyboardAvoidMode(mode);
        this.keyboardAvoidMode_ = mode;
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    getKeyboardAvoidMode(): KeyboardAvoidMode {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let mode:KeyboardAvoidMode = ArkUIAniModule._GetKeyboardAvoidMode();
        ArkUIAniModule._Common_Restore_InstanceId();
        return mode;
    }

    public getAtomicServiceBar(): Nullable<AtomicServiceBar> {
        return this.atomicServiceBar_;
    }

    public dispatchKeyEvent(node: int | string, event: KeyEvent): boolean {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = IUIContext.dispatchKeyEvent(node, event);
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
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        AnimationExtender.AnimateToImmediatelyImpl(value, () => {
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
    public setFrameCallback(onFrameCallback: ((index: long) => void), onIdleCallback: ((index: long) => void),
                                              delayTime: long): void {
        const onFrameCallback_casted = onFrameCallback as object as (((index: number) => void))
        const onIdleCallback_casted = onIdleCallback as object as (((index: number) => void))
        const delayTime_casted = delayTime as (number)
        SystemOps.setFrameCallback(onFrameCallback_casted, onIdleCallback_casted, delayTime_casted);
        return
    }
      public getWindowName(): string | undefined {
        return ArkUIAniModule._Common_getWindowName(this.instanceId_);
    }
    public getWindowWidthBreakpoint(): WidthBreakpoint {
        let ret = ArkUIAniModule._Common_getWindowWidthBreakpoint();
        return ret as WidthBreakpoint;
    }
    public getWindowHeightBreakpoint(): HeightBreakpoint {
        let ret = ArkUIAniModule._Common_getWindowHeightBreakpoint();
        return ret as HeightBreakpoint;
    }
    public vp2px(value: double): double {
         return ArkUIAniModule._Common_vp2px(value, this.instanceId_);
    }
    public px2vp(value: double): double {
         return ArkUIAniModule._Common_px2vp(value, this.instanceId_);
    }
    public fp2px(value: double): double {
         return ArkUIAniModule._Common_fp2px(value, this.instanceId_);
    }
    public px2fp(value: double): double {
         return ArkUIAniModule._Common_px2fp(value, this.instanceId_);
    }
    public lpx2px(value: double): double {
          return ArkUIAniModule._Common_lpx2px(value, this.instanceId_);
    }
    public px2lpx(value: double): double {
         return ArkUIAniModule._Common_px2lpx(value, this.instanceId_);
    }
    private getWindowWidthBreakpoint_serialize(): WidthBreakpoint {
        throw new Error("no impl");
    }
    private getWindowHeightBreakpoint_serialize(): HeightBreakpoint {
        throw new Error("no impl");
    }
    runScopedTask(callback: () => void): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        if (callback !== undefined) {
            callback()
        }
        ArkUIAniModule._Common_Restore_InstanceId()
    }
    clearResourceCache(): void {
    }
    postFrameCallback(frameCallback: FrameCallback): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        const onFrameFunc = frameCallback.onFrame
        const onIdleFunc = frameCallback.onIdle
        this.setFrameCallback(onFrameFunc, onIdleFunc, 0)
        ArkUIAniModule._Common_Restore_InstanceId()
    }
    postDelayedFrameCallback(frameCallback: FrameCallback, delayTime: long): void {
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

    public showTimePickerDialog(options: TimePickerDialogOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        DialogExtender.showTimePickerDialog(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public showTextPickerDialog(options: TextPickerDialogOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        DialogExtender.showTextPickerDialog(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public showDatePickerDialog(options: DatePickerDialogOptions): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        DialogExtender.showDatePickerDialog(options);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public freezeUINode(id: long, isFrozen: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        IUIContext.freezeUINode(id, isFrozen);
        ArkUIAniModule._Common_Restore_InstanceId()
    }

    // @ts-ignore
    public freezeUINode(id: string, isFrozen: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        IUIContext.freezeUINode(id, isFrozen);
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
    
    public getFilteredInspectorTree(filters?: Array<string>): string {
        return inspector.getFilteredInspectorTree(filters);
    }
 
    public getFilteredInspectorTreeById(id: string, depth: int, filters?: Array<string>): string {
        return inspector.getFilteredInspectorTreeById(id, depth, filters);
    }

    public setImageCacheCount(value: int): void {
        ArkUIAniModule._Common_SetImageCacheCount(value, this.instanceId_);
    }

    public setImageRawDataCacheSize(value: int): void {
        ArkUIAniModule._Common_SetImageRawDataCacheSize(value, this.instanceId_);
    }

    public requireDynamicSyncScene(id: string): Array<DynamicSyncScene> {
        const id_casted = id as (string);
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let nodePtr = FrameNodeExtender.getFrameNodeByKey(id_casted);
        if (!nodePtr) {
            ArkUIAniModule._Common_Restore_InstanceId();
            return [];
        }
        let tag = ArkUIGeneratedNativeModule._FrameNodeExtender_getNodeType(nodePtr);
        if (tag === 'Swiper') {
            let ret: Array<SwiperDynamicSyncScene> =
                [new SwiperDynamicSyncScene(SwiperDynamicSyncSceneType.GESTURE, nodePtr),
                new SwiperDynamicSyncScene(SwiperDynamicSyncSceneType.ANIMATION, nodePtr)];
            let result: Array<DynamicSyncScene> = [ret[0], ret[1]];
            ArkUIAniModule._Common_Restore_InstanceId();
            return result;
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return [];
    }
}
