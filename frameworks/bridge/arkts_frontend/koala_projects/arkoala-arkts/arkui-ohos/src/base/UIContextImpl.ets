/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
import { ArkUINativeModule } from '#components'
import { UIAbilityContext, ExtensionContext } from "#external"
import { UIContextUtil } from "arkui/base/UIContextUtil"
import { int32, int64 } from '@koalaui/common';
import { nullptr, KPointer, KSerializerBuffer, toPeerPtr, RuntimeType,
    registerNativeModuleLibraryName, wrapSystemCallback,
    runtimeType, Finalizable, SerializerBase, DeserializerBase } from '@koalaui/interop';
import { _animateTo } from 'arkui/base/ArkAnimation';
import { AnimateParam, KeyframeAnimateParam, KeyframeState } from 'arkui/framework'
import { AnimatorResult , AnimatorOptions, Animator, SimpleAnimatorOptions } from '@ohos/animator';
import { MarqueeDynamicSyncScene, MarqueeDynamicSyncSceneType } from '@ohos/arkui/UIContext';
import { UIContext, MeasureUtils, TextMenuController, Font, FocusController, ContextMenuController, ComponentUtils,
    FrameCallback, UIInspector, UIObserver, OverlayManager, PromptAction, AtomicServiceBar, Router, CursorController,
    MediaQuery, ComponentSnapshot, NodeIdentity, OverlayManagerOptions, DragController, TargetInfo, CustomBuilderWithId,
    KeyboardAvoidMode, DynamicSyncScene, SwiperDynamicSyncScene, SwiperDynamicSyncSceneType, PageInfo,
    CustomKeyboardContinueFeature, Magnifier } from '@ohos/arkui/UIContext';
import { ComputableState, GlobalStateManager, memoEntry, memoEntry1,
    IncrementalNode, GlobalUIStateManager } from '@koalaui/runtime';
import { StateContext } from 'arkui.incremental.runtime.state';
import { Context, PointerStyle, PixelMap } from '#external';
import { Nullable,  WidthBreakpoint, HeightBreakpoint } from 'arkui/component/enums';
import { KeyEvent, PopupCommonOptions, MenuOptions, ExpectedFrameRateRange } from 'arkui/component/common';
import { GlobalScope_ohos_font } from '#generated';
import router from '@ohos/router';
import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons,
    AlertDialogParamWithOptions } from 'arkui/component/alertDialog';
import { ActionSheetOptions } from 'arkui/component/actionSheet';
import { TimePickerDialogOptions } from "arkui/component/timePicker"
import { TextPickerDialogOptions, TextPickerDialogOptionsExt } from "arkui/component/textPicker"
import { DatePickerDialogOptions } from "arkui/component/datePicker"
import inspector from '@ohos/arkui/inspector';
import { ComponentContent, ComponentContentBase } from 'arkui/ComponentContent';
import overlayManager from '@ohos/overlayManager';
import promptAction, { LevelOrder } from '@ohos/promptAction';
import { ArkUIAniModule } from 'arkui.ani';
import { default as font } from '@ohos/font';
import { MeasureOptions } from '@ohos/measure';
import { GlobalScope_ohos_measure_utils } from '#generated';
import { GlobalScopeUicontextTextMenu } from "#generated"
import { GlobalScopeUicontextFontScale } from "#generated"
import { SizeOptions, ResourceColor } from 'arkui/component/units';
import { Frame } from 'arkui/Graphics';
import { TextMenuOptions, TextLayoutOptions, Paragraph } from 'arkui/component/textCommon';
import { focusController } from '@ohos/arkui/focusController';
import { KeyProcessingMode } from 'arkui/component/focus';
import { componentUtils } from '@ohos/arkui/componentUtils';
import { componentSnapshot } from '@ohos/arkui/componentSnapshot';
import { dragController } from '@ohos/arkui/dragController';
import { UIContextAtomicServiceBar, UIContextGetInfo } from 'arkui/component/idlize';
import { SheetOptions } from '#generated';
import { GlobalScope } from './../framework/GlobalScope';
import { default as mediaquery } from '@ohos/mediaquery';
import { CustomBuilder, CustomBuilderT, ArkComponentRootPeer, DragItemInfo, Callback } from 'arkui/framework';
import { AsyncCallback } from '#external';
import { createUiDetachedRoot, createUiDetachedRootT, destroyUiDetachedRoot } from 'arkui/ArkUIEntry';
import { PeerNode, findPeerNode } from 'arkui/PeerNode';
import { KBuffer } from '@koalaui/interop';
import { deserializeAndCallCallback } from 'arkui/framework/peers/CallbackDeserializeCall';
import { InteropNativeModule } from '@koalaui/interop';
import { LocalStorage } from '../stateManagement/storage/localStorage';
import { Router as RouterExt } from 'arkui/base';
import { PromptActionExtender, FrameNodeExtender, AlertDialog, ActionSheet, AnimationExtender,
    DialogExtender, IUIContext, ContextMenu } from '../framework';
import { EntryPoint, NavInterface } from "../component/customComponent"
import { AsyncCallback as routerAsyncCallback, BusinessError } from "@ohos.base"
import { IUIContext, SystemOps, UIObserverGestureEventOps, MagnifierExtender } from 'arkui/component/idlize';
import { default as uiObserver } from '@ohos/arkui/observer';
import { TabsController } from 'arkui/component/tabs';
import { Scroller } from 'arkui/component/scroll';
import { FreeRootNode } from '../CallbackTransformer';
import { StyledString } from "arkui/component/styledString"
import { default as text } from "@ohos.graphics.text"

export class ContextRecord {
    uiContext?: UIContext
}

export { UIObserverGestureEventOps };

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
    public getParagraphs(styledString: StyledString, options?: TextLayoutOptions): Array<text.Paragraph> {
        const impl: GetParagraphsImpl = new GetParagraphsImpl(this.instanceId_);
        return impl.getParagraphsImpl(styledString, options);
    }
}

class GetParagraphsImpl {
    static { loadLibrary('text_engine_ani.z') }
    instanceId_: int32;
    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
    }
    public getParagraphsImpl(styledString: StyledString, options?: TextLayoutOptions): Array<text.Paragraph> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let paragraphs = GlobalScope_ohos_measure_utils.getParagraphs(styledString, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return paragraphs;
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
    public isActive(): boolean {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = focusController.isActive();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }
}

export class ContextMenuControllerImpl extends ContextMenuController {
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
                             delay?: int32, checkImageStatus?: boolean,
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
    public createFromBuilder(builder: CustomBuilder, delay?: int32, checkImageStatus?: boolean,
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
    public getWithUniqueId(uniqueId: int32, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getWithUniqueId(uniqueId, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public getSyncWithUniqueId(uniqueId: int32, options?: componentSnapshot.SnapshotOptions): PixelMap {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getSyncWithUniqueId(uniqueId, options);
        ArkUIAniModule._Common_Restore_InstanceId();
        return pixmap;
    }

    public createFromComponent<T extends Object>(content: ComponentContent<T>, delay?: int32,
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

    public getWithRange(start: NodeIdentity, end: NodeIdentity, isStartRect: boolean,
        options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let pixmap = componentSnapshot.getWithRange(start, end, isStartRect, options);
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
    public executeDrag(custom: CustomBuilder | DragItemInfo | undefined, dragInfo: dragController.DragInfo,
        callback: AsyncCallback<dragController.DragEventParam>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        if (custom === undefined) {
            let destroyCallback = (): void => {}
            let dragItemInfoNull: DragItemInfo = {};
            ArkUIAniModule._DragController_executeDragWithCallback(dragItemInfoNull, nullptr,
                destroyCallback, dragInfo, callback);
        } else if (typeof custom === "function") {
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
            } else if (customDragInfo.builder !== undefined) {
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
            } else {
                destroyCallback = (): void => {}
                let dragItemInfoNull: DragItemInfo = {};
                ArkUIAniModule._DragController_executeDragWithCallback(dragItemInfoNull, nullptr,
                    destroyCallback, dragInfo, callback);
            }
        }
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    // @ts-ignore
    public executeDrag(custom: CustomBuilder | DragItemInfo | undefined, dragInfo: dragController.DragInfo):
        Promise<dragController.DragEventParam> | null {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let promise = new Promise<dragController.DragEventParam>((resolve, reject) => { });
        if (custom === undefined) {
            let destroyCallback = (): void => {}
            let dragItemInfoNull: DragItemInfo = {};
            ArkUIAniModule._DragController_executeDragWithPromise(dragItemInfoNull, nullptr,
                destroyCallback, dragInfo);
        } else if (typeof custom === "function") {
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
            } else if (customDragInfo.builder !== undefined) {
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
            } else {
                destroyCallback = (): void => {}
                let dragItemInfoNull: DragItemInfo = {};
                ArkUIAniModule._DragController_executeDragWithPromise(dragItemInfoNull, nullptr,
                    destroyCallback, dragInfo);
            }
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return promise;
    }

    public createDragAction(customArray: Array<CustomBuilder | DragItemInfo> | undefined,
        dragInfo: dragController.DragInfo): dragController.DragAction {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);

        let rootNodeArray: Array<KPointer> = [];
        let peerNodeArray: Array<PeerNode> = [];
        let dragItemInfoArray: Array<DragItemInfo> = [];
        
        if (customArray !== undefined) {
            let arrayData = customArray as Array<CustomBuilder | DragItemInfo>
            for (let element of arrayData) {
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
                    } else if (dragItemInfo.builder !== undefined) {
                        const peerNode = createUiDetachedRoot((): PeerNode => {
                            return ArkComponentRootPeer.create(undefined);
                        }, dragItemInfo.builder as CustomBuilder);
                        const rootNode = peerNode.peer.ptr;
                        rootNodeArray.push(rootNode);
                        peerNodeArray.push(peerNode);
                    }
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

    public enableDropDisallowedBadge(enabled: boolean): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._DragController_enableDropDisallowedBadge(enabled);
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
        this.router_!.pushAsync(options, callback);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public pushUrl(options: router.RouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.pushAsync(options, callback, mode);
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
        this.router_!.pushNamedRouteAsync(options, callback);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public pushNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.pushNamedRouteAsync(options, callback, mode);
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
        this.router_!.replaceAsync(options, callback);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public replaceUrl(options: router.RouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.replaceAsync(options, callback, mode);
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
        this.router_!.replaceNamedRouteAsync(options, callback);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode, callback: routerAsyncCallback<void>): void {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        this.router_!.replaceNamedRouteAsync(options, callback, mode);
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

    public getStackSize(): int {
        if (this.router_ === undefined) {
            throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getStackSize();
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
            return undefined
            // throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getEntryRootValue();
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public getPreState(): ComputableState<IncrementalNode> | undefined {
        if (this.router_ === undefined) {
            return undefined;
            // throw Error("router set in uiContext is empty");
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = this.router_!.getPreState();
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
    public createComponentObserver(id: string | int): inspector.ComponentObserver {
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
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
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
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
        }
        const retval = promptAction.showDialog(options, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
        return retval;
    }

    //@ts-ignore
    showActionMenu(options: promptAction.ActionMenuOptions,
        callback: AsyncCallback<promptAction.ActionMenuSuccessResponse>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let optionsInternal: promptAction.ActionMenuOptionsInternal = {};
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
        }
        promptAction.showActionMenu1(options, callback, optionsInternal);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    //@ts-ignore
    showActionMenu(options: promptAction.ActionMenuOptions): Promise<promptAction.ActionMenuSuccessResponse> {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let optionsInternal: promptAction.ActionMenuOptionsInternal = {};
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
        }
        const retval = promptAction.showActionMenu(options, optionsInternal);
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
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
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
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
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
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
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
        const materialPtr = options?.systemMaterial?.getNativeObject();
        if (materialPtr !== undefined) {
            optionsInternal.systemMaterial = materialPtr as KPointer;
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
    forceCompleteRerender(): void;
}

export class DetachedRootEntryImpl<T extends IncrementalNode> implements DetachedRootEntry {
    private entry?: ComputableState<T>;
    constructor(entry: ComputableState<T>) {
        this.entry = entry
    }

    compute(): void {
        this.entry?.value;
    }

    dispose(): void {
        this.entry?.dispose();
        this.entry = undefined;
    }

    forceCompleteRerender(): void {
        this.entry?.forceCompleteRerender();
    }
}

export class DetachedRootEntryManager {
    uicontext_: UIContext;
    detachedRoots_: Map<KPointer, DetachedRootEntry>;
    private freezedRoots_: Map<KPointer, DetachedRootEntry>;
    constructor(uicontext: UIContext) {
        this.detachedRoots_ = new Map<KPointer, DetachedRootEntry>();
        this.freezedRoots_ = new Map<KPointer, DetachedRootEntry>();
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
        const manager = GlobalStateManager.instance;
        const node = manager.updatableNodeEx<PeerNode>(peerFactory(), (context: StateContext) => {
            ArkUIAniModule._Common_Sync_InstanceId(this.uicontext_.getInstanceId())
            memoEntry<void>(context, 0, builder)
            ArkUIAniModule._Common_Restore_InstanceId();
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
        const manager = GlobalStateManager.instance;
        const node = manager.updatableNodeEx<PeerNode>(peerFactory(), (context: StateContext) => {
            ArkUIAniModule._Common_Sync_InstanceId(this.uicontext_.getInstanceId())
            memoEntry1<T, void>(context, 0, builder, arg)
            ArkUIAniModule._Common_Restore_InstanceId();
        })
        this.detachedRoots_.set(node.value.peer.ptr, new DetachedRootEntryImpl<PeerNode>(node))
        return node.value
    }

    public createUiDetachedFreeRoot(
        nodeFactory: () => IncrementalNode,
        /** @memo */
        builder: () => void
    ): PeerNode | undefined {
        const manager = GlobalStateManager.instance;
        const freeRoot = nodeFactory();
        const node = manager.updatableNodeEx<IncrementalNode>(freeRoot, (context: StateContext) => {
            ArkUIAniModule._Common_Sync_InstanceId(this.uicontext_.getInstanceId())
            const lastFreezeNode = FreeRootNode.current;
            FreeRootNode.current = freeRoot as FreeRootNode;
            memoEntry<void>(context, 0, builder)
            FreeRootNode.current = lastFreezeNode;
            ArkUIAniModule._Common_Restore_InstanceId();
        })

        const inc = node.value;
        const peerNode = findPeerNode(inc);
        if (peerNode === undefined) {
            node.dispose()
            return undefined
        }
        (freeRoot as FreeRootNode).setPtr(peerNode.peer.ptr);
        this.detachedRoots_.set(peerNode.peer.ptr, new DetachedRootEntryImpl<IncrementalNode>(node));
        return peerNode;
    }

    public freezeDetachedFreeRoot(ptr: KPointer): void {
        if (!this.detachedRoots_.has(ptr)) {
            return;
        }
        const node = this.detachedRoots_.get(ptr) as DetachedRootEntry;
        this.freezedRoots_.set(ptr, node);
        this.detachedRoots_.delete(ptr);
    }

    public unfreezeDetachedFreeRoot(ptr: KPointer): void {
        if (!this.freezedRoots_.has(ptr)) {
            return;
        }
        const node = this.freezedRoots_.get(ptr) as DetachedRootEntry;
        this.detachedRoots_.set(ptr, node);
        this.freezedRoots_.delete(ptr);
    }

    public destroyUiDetachedRoot(ptr: KPointer): boolean {
        if (!this.detachedRoots_.has(ptr) && !this.freezedRoots_.has(ptr)) {
            return false;
        }
        if (this.detachedRoots_.has(ptr)) {
            const root = this.detachedRoots_.get(ptr)!;
            this.detachedRoots_.delete(ptr);
            root.dispose();
        } else if (this.freezedRoots_.has(ptr)) {
            const root = this.freezedRoots_.get(ptr)!;
            this.freezedRoots_.delete(ptr);
            root.dispose();
        } else {
            return false;
        }
        return true;
    }
}

export class MagnifierImpl extends Magnifier {
    instanceId_: int32;
    constructor(instanceId: int32) {
        super()
        this.instanceId_ = instanceId;
    }
    public bind(id: string): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        MagnifierExtender.bind(id)
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public show(x: double, y: double): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        MagnifierExtender.show(x, y)
        ArkUIAniModule._Common_Restore_InstanceId();
    }
    public unbind(): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        MagnifierExtender.unbind()
        ArkUIAniModule._Common_Restore_InstanceId();
    }
}