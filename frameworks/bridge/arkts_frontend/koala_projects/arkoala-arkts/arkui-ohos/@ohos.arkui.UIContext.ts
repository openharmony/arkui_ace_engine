/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { FrameNode, FrameNodeUtils } from 'arkui/FrameNode';
import { default as font } from '@ohos/font';
import { MeasureOptions } from '@ohos/measure';
import { SizeOptions, GestureEvent, GestureRecognizer, ClickEvent } from 'arkui/framework';
import { AnimateParam } from 'arkui/framework';
import { AnimatorResult, AnimatorOptions, Animator, SimpleAnimatorOptions} from '@ohos/animator';
import { Context, PointerStyle, PixelMap } from '#external';
import { UIAbilityContext, ExtensionContext } from "#external"
import { UIObserverGestureEventOps, DetachedRootEntryManager, FocusControllerImpl, ComponentUtilsImpl,
    ComponentSnapshotImpl, DragControllerImpl, AtomicServiceBarInternal, UIInspectorImpl, ContextMenuControllerImpl,
    CursorControllerImpl, OverlayManagerImpl, PromptActionImpl, FontImpl, MeasureUtilsImpl, MagnifierImpl,
    TextMenuControllerImpl, RouterImpl, MediaQueryImpl } from "arkui/base/UIContextImpl"
import { componentUtils } from '@ohos/arkui/componentUtils';
import { componentSnapshot, NodeIdentity } from '@ohos/arkui/componentSnapshot';
import { dragController } from '@ohos/arkui/dragController';
import { focusController } from '@ohos/arkui/focusController';
import { Frame } from 'arkui/Graphics';
import { KeyEvent, KeyframeAnimateParam, KeyframeState, PopupCommonOptions, MenuOptions, ExpectedFrameRateRange } from 'arkui/framework';
import { TextMenuOptions } from 'arkui/framework';
import { Nullable, WidthBreakpoint, HeightBreakpoint } from 'arkui/framework';
import { KeyProcessingMode } from 'arkui/framework';
import { default as uiObserver } from '@ohos/arkui/observer';
import { default as mediaquery } from '@ohos/mediaquery';
import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions } from 'arkui/framework';
import { ActionSheetOptions } from 'arkui/framework';
import { TimePickerDialogOptions } from 'arkui/framework';
import { TextPickerDialogOptions, TextPickerDialogOptionsExt } from 'arkui/framework';
import { DatePickerDialogOptions } from 'arkui/framework';
import { SheetOptions } from 'arkui/framework';
import inspector from '@ohos/arkui/inspector';
import router from '@ohos/router';
import { ComponentContent, ComponentContentBase } from 'arkui/ComponentContent';
import overlayManager from '@ohos/overlayManager';
import promptAction, { LevelOrder } from '@ohos/promptAction';
import { LocalStorage } from 'arkui/stateManagement/storage/localStorage';
import { CustomBuilder, CustomBuilderT, DragItemInfo, Callback } from 'arkui/framework';
import { Router as RouterExt, AsyncCallback } from 'arkui/base';
import { ComputableState, IncrementalNode, GlobalStateManager, GlobalUIStateManager } from '@koalaui/runtime';
import { PeerNode } from 'arkui/PeerNode';
import { ArkUIAniModule } from 'arkui.ani';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { int32, int64 } from "@koalaui/common";
import { KPointer, KSerializerBuffer, KBuffer, DeserializerBase, nullptr, wrapSystemCallback } from '@koalaui/interop';
import { TabsController } from 'arkui/component/tabs';
import { Scroller } from 'arkui/component/scroll';
import { TextLayoutOptions, Paragraph, StyledString, ContextMenu, FrameNodeExtender, AnimationExtender, AlertDialog, ActionSheet, DialogExtender } from 'arkui/framework';
import { InnerGestureObserverConfigs, InnerGestureTriggerInfo, IUIContext, UIContextGetInfo, SystemOps } from 'arkui/component/idlize';
import { BusinessError } from "@ohos.base"
import { ArkUIGeneratedNativeModule } from '#components';
import { GlobalScopeUicontextFontScale } from "#generated"
import { deserializeAndCallCallback } from 'arkui/framework/peers/CallbackDeserializeCall';

export const enum GestureActionPhase {
    WILL_START = 0,
    WILL_END = 1
}

export const enum  GestureListenerType {
    TAP = 0,
    LONG_PRESS = 1,
    PAN = 2,
    PINCH = 3,
    SWIPE = 4,
    ROTATION = 5
}

export interface GestureTriggerInfo {
    event: GestureEvent;
    current: GestureRecognizer;
    currentPhase: GestureActionPhase;
    node?: FrameNode;
}

export interface GestureObserverConfigs {
    actionPhases: Array<GestureActionPhase>;
}

export class UIInspector {
    public createComponentObserver(id: string | int): inspector.ComponentObserver {
        throw Error("createComponentObserver not implemented in UIInspector!")
    }
    public createComponentObserver(id: string): inspector.ComponentObserver {
        throw Error("createComponentObserver not implemented in UIInspector!")
    }
}

export interface TargetInfo {
    id: string | int32;
    componentId?: int32;
}

export class Font {
    public registerFont(options: font.FontOptions) : void {
        throw Error("registerFont not implemented in Font!")
    }
    public getSystemFontList() : Array<string> {
        throw Error("getSystemFontList not implemented in Font!")
    }
    public getFontByName(fontName : string) : font.FontInfo {
        throw Error("getFontByName not implemented in Font!")
    }
}

export class MediaQuery {
    public matchMediaSync(condition: string): mediaquery.MediaQueryListener {
        throw Error("matchMediaSync not implemented in MedaiQuery!")
    }
}

export class MeasureUtils {
    public measureText(options: MeasureOptions) : double {
        throw Error("measureText not implemented in MeasureUtils!")
    }
    public measureTextSize(options: MeasureOptions) : SizeOptions {
        throw Error("measureTextSize not implemented in MeasureUtils!")
    }
    public getParagraphs(styledString: StyledString, options?: TextLayoutOptions): Array<Paragraph> {
        throw Error("getParagraphs not implemented in MeasureUtils!")
    }
}

export class TextMenuController {
    public setMenuOptions(options: TextMenuOptions) : void {
        throw Error("setMenuOptions not implemented in TextMenuController!")
    }
}

export class Router {
    router_: RouterExt | undefined = undefined;
    public setRouter(router: RouterExt) {
        this.router_ = router;
    }
    public getRouter(): RouterExt {
        return this.router_!;
    }
    public pushUrl(options: router.RouterOptions): Promise<void> {
        throw Error("pushUrl not implemented in Router!");
    }

    public pushUrl(options: router.RouterOptions, mode: router.RouterMode): Promise<void> {
        throw Error("pushUrl not implemented in Router!");
    }

    public pushUrl(options: router.RouterOptions, callback: AsyncCallback<void>): void {
        throw Error("pushUrl not implemented in Router!");
    }

    public pushUrl(options: router.RouterOptions, mode: router.RouterMode, callback: AsyncCallback<void>): void {
        throw Error("pushUrl not implemented in Router!");
    }

    public pushNamedRoute(options: router.NamedRouterOptions): Promise<void> {
        throw Error("pushNamedRoute not implemented in Router!");
    }

    public pushNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode): Promise<void> {
        throw Error("pushNamedRoute not implemented in Router!");
    }

    public pushNamedRoute(options: router.NamedRouterOptions, callback: AsyncCallback<void>): void {
        throw Error("pushNamedRoute not implemented in Router!");
    }

    public pushNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode, callback: AsyncCallback<void>): void {
        throw Error("pushNamedRoute not implemented in Router!");
    }

    public replaceUrl(options: router.RouterOptions): Promise<void> {
        throw Error("replaceUrl not implemented in Router!");
    }

    public replaceUrl(options: router.RouterOptions, mode: router.RouterMode): Promise<void> {
        throw Error("replaceUrl not implemented in Router!");
    }

    public replaceUrl(options: router.RouterOptions, callback: AsyncCallback<void>): void {
        throw Error("replaceUrl not implemented in Router!");
    }

    public replaceUrl(options: router.RouterOptions, mode: router.RouterMode, callback: AsyncCallback<void>): void {
        throw Error("replaceUrl not implemented in Router!");
    }

    public replaceNamedRoute(options: router.NamedRouterOptions): Promise<void> {
        throw Error("replaceNamedRoute not implemented in Router!");
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode): Promise<void> {
        throw Error("replaceNamedRoute not implemented in Router!");
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, callback: AsyncCallback<void>): void {
        throw Error("replaceNamedRoute not implemented in Router!");
    }

    public replaceNamedRoute(options: router.NamedRouterOptions, mode: router.RouterMode, callback: AsyncCallback<void>): void {
        throw Error("replaceNamedRoute not implemented in Router!");
    }

    public back(options?: router.RouterOptions): void {
        throw Error("back not implemented in Router!");
    }

    public back(index: int, params?: Object): void {
        throw Error("back not implemented in Router!");
    }

    public clear(): void {
        throw Error("clear not implemented in Router!");
    }
    public getLength(): string {
        throw Error("getLength not implemented in Router!");
    }
    public getStackSize(): int {
        throw Error("getStackSize not implemented in Router!")
    }

    public getParams(): Object {
        throw Error("getParams not implemented in Router!");
    }

    public getState(): router.RouterState {
        throw Error("getState not implemented in Router!");
    }

    public getStateByIndex(index: int): router.RouterState | undefined {
        throw Error("getStateByIndex not implemented in Router!");
    }

    public getStateByUrl(url: string): Array<router.RouterState> {
        throw Error("getStateByUrl not implemented in Router!");
    }

    public getStateRoot(): ComputableState<IncrementalNode> | undefined {
        throw Error("getStateRoot not implemented in Router!");
    }

    public getPreState(): ComputableState<IncrementalNode> | undefined {
        throw Error("getPreState not implemented in Router!");
    }

    public showAlertBeforeBackPage(options: router.EnableAlertOptions): void {
        throw Error("showAlertBeforeBackPage not implemented in Router!");
    }

    public hideAlertBeforeBackPage(): void {
        throw Error("hideAlertBeforeBackPage not implemented in Router!");
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
    public isActive(): boolean {
        throw Error('isActive not implemented in FocusController!')
    }
}

export class ComponentSnapshot {
    //@ts-ignore
    public get(id: string, callback: AsyncCallback<PixelMap>,
               options?: componentSnapshot.SnapshotOptions): void {
        throw Error("get with callback not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public get(id: string, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("get with promise not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public createFromBuilder(builder: CustomBuilder, callback: AsyncCallback<PixelMap>,
                             delay?: int32, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): void {
        throw Error("createFromBuilder with callback not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public createFromBuilder(builder: CustomBuilder, delay?: int32, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("createFromBuilder with promise not implemented in ComponentSnapshot!")
    }
    public getSync(id: string, options?: componentSnapshot.SnapshotOptions): PixelMap | null {
        throw Error("getSync not implemented in ComponentSnapshot!")
    }
    public getWithUniqueId(uniqueId: int32, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("getWithUniqueId not implemented in ComponentSnapshot!")
    }

    public getSyncWithUniqueId(uniqueId: int32, options?: componentSnapshot.SnapshotOptions): PixelMap {
        throw Error("getSyncWithUniqueId not implemented in ComponentSnapshot!")
    }

    public createFromComponent<T extends Object>(content: ComponentContent<T>, delay?: int32, checkImageStatus?: boolean,
        options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("getSyncWithUniqueId not implemented in ComponentSnapshot!")
    }

    public getWithRange(start: NodeIdentity, end: NodeIdentity, isStartRect: boolean,
        options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error('getWithRange not implemented in ComponentSnapshot!')
    }

    public getSizeLimitation(): componentSnapshot.SnapshotSizeLimitation {
        throw Error('getSizeLimitation not implemented in ComponentSnapshot!')
    }
}

export class DragController {
    //@ts-ignore
    public executeDrag(custom: CustomBuilder | DragItemInfo, dragInfo: dragController.DragInfo,
        callback: AsyncCallback<dragController.DragEventParam>): void {
        throw Error("executeDrag with callback not implemented in DragController!")
    }
    //@ts-ignore
    public executeDrag(custom: CustomBuilder | DragItemInfo, dragInfo: dragController.DragInfo):
        Promise<dragController.DragEventParam> | null {
        throw Error("executeDrag with promise not implemented in DragController!")
    }
    public createDragAction(customArray: Array<CustomBuilder | DragItemInfo>,
        dragInfo: dragController.DragInfo): dragController.DragAction {
        throw Error("createDragAction not implemented in DragController!")
    }
    public getDragPreview(): dragController.DragPreview {
        throw Error("getDragPreview not implemented in DragController!")
    }
    public setDragEventStrictReportingEnabled(enable: boolean): void {
        throw Error("setDragEventStrictReportingEnabled not implemented in DragController!")
    }
    public cancelDataLoading(key: string): void {
        throw Error("setDragEventStrictReportingEnabled not implemented in DragController!")
    }
    public notifyDragStartRequest(requestStatus: dragController.DragStartRequestStatus): void {
        throw Error("setDragEventStrictReportingEnabled not implemented in DragController!")
    }
    public enableDropDisallowedBadge(enabled: boolean): void {
        throw Error('enableDropDisallowedBadge not implemented in DragController!')
    }
}

export interface OverlayManagerOptions {
    renderRootOverlay?: boolean;
    enableBackPressedEvent?: boolean;
}

class OverlayManagerOptionsInner implements OverlayManagerOptions {
    renderRootOverlay?: boolean = true;
    enableBackPressedEvent?: boolean = false;
}

export class ContextMenuController {
    public close(): void {
        throw Error("close not implemented in ContextMenuController!")
    }
}

export class OverlayManager {
    setOverlayManagerOptions(options: OverlayManagerOptions): boolean {
        throw Error("setOverlayManagerOptions not implemented in OverlayManager!")
    }

    getOverlayManagerOptions(): OverlayManagerOptions {
        throw Error("getOverlayManagerOptions not implemented in OverlayManager!")
    }

    addComponentContent(content: ComponentContent, index?: int32): void {
        throw Error("addComponentContent not implemented in OverlayManager!")
    }

    addComponentContentWithOrder(content: ComponentContent, levelOrder?: LevelOrder): void {
        throw Error("addComponentContentWithOrder not implemented in OverlayManager!")
    }

    removeComponentContent(content: ComponentContent): void {
        throw Error("removeComponentContent not implemented in OverlayManager!")
    }

    showComponentContent(content: ComponentContent): void {
        throw Error("showComponentContent not implemented in OverlayManager!")
    }

    hideComponentContent(content: ComponentContent): void {
        throw Error("hideComponentContent not implemented in OverlayManager!")
    }

    showAllComponentContents(): void {
        throw Error("showAllComponentContents not implemented in OverlayManager!")
    }

    hideAllComponentContents(): void {
        throw Error("hideAllComponentContents not implemented in OverlayManager!")
    }
}

export type CustomBuilderWithId = (id: int32) => void;

export class PromptAction {
    showToast(options: promptAction.ShowToastOptions): void {
        throw Error("showToast not implemented in PromptAction!")
    }

    openToast(options: promptAction.ShowToastOptions): Promise<int32> {
        throw Error("openToast not implemented in PromptAction!")
    }

    closeToast(toastId: int32): void {
        throw Error("closeToast not implemented in PromptAction!")
    }

    //@ts-ignore
    showDialog(options: promptAction.ShowDialogOptions,
        callback: AsyncCallback<promptAction.ShowDialogSuccessResponse>): void {
        throw Error("showDialog1 not implemented in PromptAction!")
    }

    //@ts-ignore
    showDialog(options: promptAction.ShowDialogOptions): Promise<promptAction.ShowDialogSuccessResponse> {
        throw Error("showDialog not implemented in PromptAction!")
    }

    //@ts-ignore
    showActionMenu(options: promptAction.ActionMenuOptions,
        callback: AsyncCallback<promptAction.ActionMenuSuccessResponse>): void {
        throw Error("showActionMenu1 not implemented in PromptAction!")
    }

    //@ts-ignore
    showActionMenu(options: promptAction.ActionMenuOptions): Promise<promptAction.ActionMenuSuccessResponse> {
        throw Error("showActionMenu not implemented in PromptAction!")
    }

    //@ts-ignore
    openCustomDialog(content: ComponentContent, options?: promptAction.BaseDialogOptions): Promise<void> {
        throw Error("openCustomDialog1 not implemented in PromptAction!")
    }

    //@ts-ignore
    openCustomDialog(options: promptAction.CustomDialogOptions): Promise<int32> {
        throw Error("openCustomDialog not implemented in PromptAction!")
    }

    updateCustomDialog(content: ComponentContent, options: promptAction.BaseDialogOptions): Promise<void> {
        throw Error("updateCustomDialog not implemented in PromptAction!")
    }

    //@ts-ignore
    closeCustomDialog(content: ComponentContent): Promise<void> {
        throw Error("closeCustomDialog1 not implemented in PromptAction!")
    }

    //@ts-ignore
    closeCustomDialog(dialogId: int32): void {
        throw Error("closeCustomDialog not implemented in PromptAction!")
    }

    openCustomDialogWithController(content: ComponentContent, controller: promptAction.DialogController,
        options?: promptAction.BaseDialogOptions): Promise<void> {
        throw Error("openCustomDialogWithController not implemented in PromptAction!")
    }

    presentCustomDialog(builder: CustomBuilder | CustomBuilderT<int32>, controller?: promptAction.DialogController,
        options?: promptAction.DialogOptions): Promise<int32> {
        throw Error("presentCustomDialog not implemented in PromptAction!")
    }

    getTopOrder(): LevelOrder | undefined {
        throw Error("getTopOrder not implemented in PromptAction!")
    }

    getBottomOrder(): LevelOrder | undefined {
        throw Error("getBottomOrder not implemented in PromptAction!")
    }

    openPopup(content: ComponentContent, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        throw Error("openPopup not implemented in PromptAction!")
    }

    updatePopup(content: ComponentContent, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        throw Error("updatePopup not implemented in PromptAction!")
    }

    closePopup(content: ComponentContent): Promise<void> {
        throw Error("closePopup not implemented in PromptAction!")
    }

    openMenu(content: ComponentContent, target: TargetInfo, options?: MenuOptions): Promise<void> {
        throw Error("openMenu not implemented in PromptAction!")
    }

    updateMenu(content: ComponentContent, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        throw Error("updateMenu not implemented in PromptAction!")
    }

    closeMenu(content: ComponentContent): Promise<void> {
        throw Error("closeMenu not implemented in PromptAction!")
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

export const enum KeyboardAvoidMode {
    OFFSET = 0,
    RESIZE = 1,
    OFFSET_WITH_CARET = 2,
    RESIZE_WITH_CARET = 3,
    NONE = 4,
}

export class ResolvedUIContext extends UIContext {
    public strategy: ResolveStrategy = ResolveStrategy.UNDEFINED;
    constructor(instanceId: int32, strategy: ResolveStrategy) {
        super(instanceId);
        this.strategy = strategy;
    }
}

export const enum ResolveStrategy {
    CALLING_SCOPE = 0,
    LAST_FOCUS = 1,
    MAX_INSTANCE_ID = 2,
    UNIQUE = 3,
    LAST_FOREGROUND = 4,
    UNDEFINED = 5
}

export class UIContext {
    instanceId_: int32 = -1;
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
    magnifier_: MagnifierImpl;
    textMenuController_: TextMenuControllerImpl;
    detachedRootEntryManager_: DetachedRootEntryManager;
    isDebugMode_: boolean = false;
    updateParallelizeItemNodeCallback_?:() => void;
    callbacks: Array<() => void>;
    isUpdateConfiguration_ = false;
    workerThreadId_: int32  = -1;

    bufferSize = 4096
    buffer: KBuffer = new KBuffer(this.bufferSize)
    position: int64 = 0
    deserializer: DeserializerBase = new DeserializerBase(this.buffer.buffer, this.bufferSize)
    static windowFreeInstanceId: int32 = -1
    static initFlag_ = false

    constructor(instanceId: int32) {
        this.instanceId_ = instanceId;
        this.focusController_ = new FocusControllerImpl(this.instanceId_);
        this.componentUtils_ = new ComponentUtilsImpl(this.instanceId_);
        this.componentSnapshot_ = new ComponentSnapshotImpl(this.instanceId_);
        this.dragController_ = new DragControllerImpl(this.instanceId_);
        this.atomicServiceBar_ = new AtomicServiceBarInternal(this.instanceId_);
        this.contextMenuController_ = new ContextMenuControllerImpl(this.instanceId_);
        this.cursorController_ = new CursorControllerImpl(this.instanceId_);
        this.font_ = new FontImpl(this.instanceId_);
        this.measureUtils_ = new MeasureUtilsImpl(this.instanceId_);
        this.magnifier_ = new MagnifierImpl(this.instanceId_);
        this.textMenuController_ = new TextMenuControllerImpl(this.instanceId_);
        this.detachedRootEntryManager_ = new DetachedRootEntryManager(this);
        this.isDebugMode_ = ArkUIAniModule._IsDebugMode(this.instanceId_) !== 0;
        this.router_ = new RouterImpl(this.instanceId_);
        this.callbacks = new Array<() => void>();
    }
    constructor() {
        this.focusController_ = new FocusControllerImpl(this.instanceId_);
        this.componentUtils_ = new ComponentUtilsImpl(this.instanceId_);
        this.componentSnapshot_ = new ComponentSnapshotImpl(this.instanceId_);
        this.dragController_ = new DragControllerImpl(this.instanceId_);
        this.atomicServiceBar_ = new AtomicServiceBarInternal(this.instanceId_);
        this.contextMenuController_ = new ContextMenuControllerImpl(this.instanceId_);
        this.cursorController_ = new CursorControllerImpl(this.instanceId_);
        this.font_ = new FontImpl(this.instanceId_);
        this.measureUtils_ = new MeasureUtilsImpl(this.instanceId_);
        this.magnifier_ = new MagnifierImpl(this.instanceId_);
        this.textMenuController_ = new TextMenuControllerImpl(this.instanceId_);
        this.detachedRootEntryManager_ = new DetachedRootEntryManager(this);
        this.isDebugMode_ = ArkUIAniModule._IsDebugMode(this.instanceId_) !== 0;
        this.router_ = new RouterImpl(this.instanceId_);
        this.callbacks = new Array<() => void>();
    }
    
    public getInstanceId() : int32 {
        return this.instanceId_;
    }
    public getDetachedRootEntryManager() : DetachedRootEntryManager {
        return this.detachedRootEntryManager_;
    }
    dispatchCallback(buffer: KSerializerBuffer, length: int32): void {
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

    static getCallingScopeUIContext(): UIContext | undefined {
        const instanceId = ArkUIAniModule._GetCallingScopeUIContext();
        if (instanceId < 0) {
            return undefined
        }
        let uiContext = UIContextUtil.getOrCreateUIContextById(instanceId)
        return uiContext
    }

    static getLastFocusedUIContext(): UIContext | undefined {
        const instanceId = ArkUIAniModule._GetLastFocusedUIContext();
        if (instanceId < 0) {
            return undefined
        }
        let uiContext = UIContextUtil.getOrCreateUIContextById(instanceId)
        return uiContext
    }

    static getLastForegroundUIContext(): UIContext | undefined {
        const instanceId = ArkUIAniModule._GetLastForegroundUIContext();
        if (instanceId < 0) {
            return undefined
        }
        let uiContext = UIContextUtil.getOrCreateUIContextById(instanceId)
        return uiContext
    }

    static getAllUIContexts(): Array<UIContext> {
        let allContainerIds = ArkUIAniModule._GetAllUIContexts();
        let contextArray = new Array<UIContext>();
        for (let item of allContainerIds) {
            if (item >= 0) {
                contextArray.push(UIContextUtil.getOrCreateUIContextById(item));
            }
        }
        return contextArray;
    }

    static resolveUIContext(): ResolvedUIContext {
        let instance = UIContextUtil.resolveUIContext();
        return new ResolvedUIContext(instance[0] as int32, ResolveStrategy.fromValue(instance[1]));
    }
    public isAvailable() : boolean {
        return UIContextUtil.availableInstanceIds_.has(this.instanceId_);
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
    public setCustomKeyboardContinueFeature(feature: CustomKeyboardContinueFeature): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        // TODO: remove after regeneration
        // instructive change start
        // IUIContext.setCustomKeyboardContinueFeature(feature);
        // instructive change end
        ArkUIAniModule._Common_Restore_InstanceId()
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
        return ArkUIAniModule._Common_GetSharedLocalStorage();
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
    getFrameNodeByUniqueId(id: int): FrameNode | null {
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
    getNavigationInfoByUniqueId(id: int): uiObserver.NavigationInfo | undefined {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let navigationInfo = UIContextGetInfo.getNavigationInfoByUniqueId(id);
        ArkUIAniModule._Common_Restore_InstanceId();
        return navigationInfo;
    }
    getHostContext(): Context | undefined {
        return ArkUIAniModule._Common_GetHostContext(this.instanceId_);
    }

    public getKeyboardAvoidMode(): KeyboardAvoidMode {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let mode:KeyboardAvoidMode = ArkUIAniModule._GetKeyboardAvoidMode();
        ArkUIAniModule._Common_Restore_InstanceId();
        return mode;
    }

    public setKeyboardAvoidMode(mode: KeyboardAvoidMode) {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        ArkUIAniModule._SetKeyboardAvoidMode(mode);
        this.keyboardAvoidMode_ = mode;
        ArkUIAniModule._Common_Restore_InstanceId();
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

    public getCursorController(): CursorController {
        return this.cursorController_;
    }
    
    public getComponentSnapshot(): ComponentSnapshot {
        return this.componentSnapshot_;
    }

    public getDragController(): DragController {
        return this.dragController_;
    }

    public getRouter(): Router {
        if (this.router_ === undefined) {
            this.router_ = new RouterImpl(this.instanceId_)
        }
        return this.router_
    }

    public keyframeAnimateTo(param: KeyframeAnimateParam, keyframes: Array<KeyframeState>): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        AnimationExtender.KeyframeAnimationImpl(param, keyframes);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        AnimationExtender.AnimateToImmediatelyImpl(param, event, false)
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public animateToImmediately(value: AnimateParam, event: () => void): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        AnimationExtender.AnimateToImmediatelyImpl(value, () => {
            event();
        }, true);
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
        SystemOps.setFrameCallback(onFrameCallback, onIdleCallback, delayTime);
        return
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

    public getMagnifier(): Magnifier {
        return this.magnifier_;
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

    public showTextPickerDialog(options: TextPickerDialogOptions | TextPickerDialogOptionsExt): void {
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
    public freezeUINode(id: int, isFrozen: boolean): void {
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

    public enableSwipeBack(enabled: boolean | undefined): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_)
        UIContextGetInfo.enableSwipeBack(enabled);
        ArkUIAniModule._Common_Restore_InstanceId()
    }

    public getWindowName(): string | undefined {
        return ArkUIAniModule._Common_getWindowName(this.instanceId_);
    }
    public getWindowId(): int32 | undefined {
        let ret = ArkUIAniModule._Common_getWindowId(this.instanceId_);
        if (ret === -1) {
            return undefined;
        }
        return ret;
    }

    private handleBreakpointError(ret: int32, type: string) {
        if (ret === -1) {
            console.error("some error occurred while initializing the ANI environment, return default value: ${type}.");
        }
        if (ret === -2) {
            console.error("failed to retrieve the current container, return default value: ${type}.");
        }
        if (ret === -3) {
            console.error("failed to retrieve the current window, return default value: ${type}.");
        }
    }
    public getWindowWidthBreakpoint(): WidthBreakpoint {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ret = ArkUIAniModule._Common_getWindowWidthBreakpoint();
        if (ret < 0) {
            this.handleBreakpointError(ret, "WidthBreakpoint.WIDTH_XS");
            ArkUIAniModule._Common_Restore_InstanceId();
            return WidthBreakpoint.WIDTH_XS;
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return WidthBreakpoint.fromValue(ret);
    }
    public getWindowHeightBreakpoint(): HeightBreakpoint {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let ret = ArkUIAniModule._Common_getWindowHeightBreakpoint();
        if (ret < 0) {
            this.handleBreakpointError(ret, "HeightBreakpoint.HEIGHT_SM");
            ArkUIAniModule._Common_Restore_InstanceId();
            return HeightBreakpoint.HEIGHT_SM;
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return HeightBreakpoint.fromValue(ret);
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

    public getId() : int32 {
        return this.instanceId_;
    }
    public setUIStates(callback: () => void): void {
        if (this.checkThread(this.instanceId_)) {
            callback();
        } else {
            const manager = GlobalUIStateManager.getStateManagerForThread(this.workerThreadId_);
            manager.scheduleCallback(callback);
        }
    }

    public checkThread(id: int32) : boolean {
        return ArkUIAniModule._CheckIsUIThread(id) !== 0;
    }

    static createUIContextWithoutWindow(context: UIAbilityContext | ExtensionContext) : UIContext | undefined {
        if (!UIContext.initFlag_) {
            UIContext.initFlag_ = true;
            wrapSystemCallback(1, (buff : KSerializerBuffer, len : int32) => {
                deserializeAndCallCallback(new DeserializerBase(buff, len))
                return 0
            })
        }
        if (UIContext.windowFreeInstanceId > 0) {
            return UIContextUtil.getOrCreateUIContextById(UIContext.windowFreeInstanceId)
        }
        const instanceId = ArkUIAniModule._CreateWindowFreeContainer(context)
        if (instanceId < 0) {
            return undefined
        }
        UIContext.windowFreeInstanceId = instanceId;
        let uiContext = UIContextUtil.getOrCreateUIContextById(instanceId)
        return uiContext
    }
    static destroyUIContextWithoutWindow() {
        if (UIContext.windowFreeInstanceId > 0) {
            ArkUIAniModule._DestroyWindowFreeContainer(UIContext.windowFreeInstanceId)
            UIContextUtil.removeUIContext(UIContext.windowFreeInstanceId)
            UIContext.windowFreeInstanceId = -1
        }
    }
    public getPageInfoByUniqueId(id: int): PageInfo {
        const navDestinationInfo = ArkUIAniModule._CustomNode_QueryNavDestinationInfo1(id);
        const routerPageInfo = ArkUIAniModule._CustomNode_QueryRouterPageInfo1(id);
        if (routerPageInfo) {
            routerPageInfo.context = this;
        }
        let pageInfo: PageInfo = {
            navDestinationInfo: navDestinationInfo,
            routerPageInfo: routerPageInfo
        }
        return pageInfo;
    }

    public getPageInfoByUniqueId(id: number): PageInfo {
        throw Error("getPageInfoByUniqueId(number) not implemented in UIContext!")
    }

    public getPageRootNode(): FrameNode | null {
        if (!this.isAvailable()) {
            throw new BusinessError(120007, 'The UIContext is not available');
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let node: FrameNode | null = null;
        try {
            const retval = ArkUIAniModule._GetPageRootNode();
            if (retval !== nullptr && retval !== 0) {
                const peer = FrameNodeExtender.createByRawPtr(retval as KPointer);
                if (!peer) {
                    ArkUIAniModule._Common_Restore_InstanceId();
                    return null;
                }
                node = FrameNodeUtils.searchNodeInRegisterProxy(peer);
                if (!node) {
                    node = FrameNodeUtils.createFrameNode(this, peer);
                }
            }
        } catch (e) {
            ArkUIAniModule._Common_Restore_InstanceId();
            throw e;
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return node;
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
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getNodeType(nodePtr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const tag : string = (retvalDeserializer.readString() as string)
        if (tag === 'Swiper') {
            let ret: Array<SwiperDynamicSyncScene> =
                [new SwiperDynamicSyncScene(SwiperDynamicSyncSceneType.GESTURE, nodePtr),
                new SwiperDynamicSyncScene(SwiperDynamicSyncSceneType.ANIMATION, nodePtr)];
            let result: Array<DynamicSyncScene> = [ret[0], ret[1]];
            ArkUIAniModule._Common_Restore_InstanceId();
            return result;
        } else if (tag === 'Marquee') {
            let ret: MarqueeDynamicSyncScene[] = [
                new MarqueeDynamicSyncScene(MarqueeDynamicSyncSceneType.ANIMATION, nodePtr)];
            let result: DynamicSyncScene[] = [ret[0]];
            ArkUIAniModule._Common_Restore_InstanceId();
            return result;
        }
        ArkUIAniModule._Common_Restore_InstanceId();
        return [];
    }

    public openBindSheet(bindSheetContent: ComponentContentBase, sheetOptions?: SheetOptions, targetId?: int): Promise<void> {
        let ptr: KPointer = 0;
        if (bindSheetContent.getNodePtr() != undefined) {
            ptr = bindSheetContent.getNodePtr() as KPointer;
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = IUIContext.openBindSheet(ptr, sheetOptions, targetId);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public updateBindSheet(bindSheetContent: ComponentContentBase, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        let ptr: KPointer = 0;
        if (bindSheetContent.getNodePtr() != undefined) {
            ptr = bindSheetContent.getNodePtr() as KPointer;
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = IUIContext.updateBindSheet(ptr, sheetOptions, partialUpdate);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public closeBindSheet(bindSheetContent: ComponentContentBase): Promise<void> {
        let ptr: KPointer = 0;
        if (bindSheetContent.getNodePtr() != undefined) {
            ptr = bindSheetContent.getNodePtr() as KPointer;
        }
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        let result = IUIContext.closeBindSheet(ptr);
        ArkUIAniModule._Common_Restore_InstanceId();
        return result;
    }

    public recycleInvisibleImageMemory(enabled: boolean): void {
        ArkUIAniModule._Common_setIsRecycleInvisibleImageMemory(enabled ? 1 : 0, this.instanceId_);
    }

    public bindTabsToScrollable(tabsController: TabsController, scroller: Scroller): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        IUIContext.bindTabsToScrollable(tabsController, scroller);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public unbindTabsFromScrollable(tabsController: TabsController, scroller: Scroller): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        IUIContext.unbindTabsFromScrollable(tabsController, scroller);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public bindTabsToNestedScrollable(tabsController: TabsController, parentScroller: Scroller,
        childScroller: Scroller): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        IUIContext.bindTabsToNestedScrollable(tabsController, parentScroller, childScroller);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public unbindTabsFromNestedScrollable(tabsController: TabsController, parentScroller: Scroller,
        childScroller: Scroller): void {
        ArkUIAniModule._Common_Sync_InstanceId(this.instanceId_);
        IUIContext.unbindTabsFromNestedScrollable(tabsController, parentScroller, childScroller);
        ArkUIAniModule._Common_Restore_InstanceId();
    }

    public setRouter(router: RouterExt) {
        if (this.router_ === undefined) {
            this.router_ = new RouterImpl(this.instanceId_)
        }
        this.router_.setRouter(router);
    }

    public updateParallelizeItemNode() {
        this.updateParallelizeItemNodeCallback_?.()
    }
    public scheduleCallback(callback: () => void) {
        this.callbacks.push(callback)
    }
    public flushCallback() {
        for(const callback of this.callbacks ) {
            callback?.()
        }
        this.callbacks.length = 0
    }

    public isUpdateConfiguration(): boolean {
        return this.isUpdateConfiguration_;
    }

    public setUpdateConfiguration(value: boolean) {
        this.isUpdateConfiguration_ = value;
    }

    public isEasySplit(): boolean {
        return ArkUIAniModule._Common_IsEasySplit(this.instanceId_);
    }
}
export abstract class FrameCallback {
    onFrame(frameTimeInNano: long): void {}
    onIdle(timeLeftInNano: long): void {}
}

export declare type PanListenerCallback = (event: GestureEvent, current: GestureRecognizer, node?: FrameNode) => void;
export declare type ClickEventListenerCallback = (event: ClickEvent, node?: FrameNode) => void;
export declare type GestureEventListenerCallback = (event: GestureEvent, node?: FrameNode) => void;

// Global gesture listener callback type
export declare type GestureListenerCallback = (triggerInfo: GestureTriggerInfo) => void;

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

    public on(type: string, callback: ((param: object) => void)): void {
        if (this.observerImpl) {
            this.observerImpl!.on(type, callback);
        }
    }

    public off(type: string, callback?: ((param: object) => void)): void {
        if (this.observerImpl) {
            this.observerImpl!.off(type, callback);
        }
    }
    
    public on(type: string, options: uiObserver.NavDestinationSwitchObserverOptions, callback: ((param: object) => void)): void {
        if (this.observerImpl) {
            this.observerImpl!.on(type, options, callback);
        }
    }

    public off(type: string, options: uiObserver.NavDestinationSwitchObserverOptions, callback?: ((param: object) => void)): void {
        if (this.observerImpl) {
            this.observerImpl!.off(type, options, callback);
        }
    }

    public onScrollEvent(options: uiObserver.ObserverOptions, callback: Callback<uiObserver.ScrollEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onScrollEvent(options, callback);
        }
    }

    public offScrollEvent(options: uiObserver.ObserverOptions, callback: Callback<uiObserver.ScrollEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offScrollEvent(options, callback);
        }
    }

    public onScrollEvent(callback: Callback<uiObserver.ScrollEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onScrollEvent(callback);
        }
    }

    public offScrollEvent(callback: Callback<uiObserver.ScrollEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offScrollEvent(callback);
        }
    }

    public onNavDestinationUpdate(
        options: uiObserver.NavDestinationSwitchObserverOptions,
        callback: Callback<uiObserver.NavDestinationInfo>
    ): void {
        if (this.observerImpl) {
            this.observerImpl!.onNavDestinationUpdate(options, callback);
        }
    }

    public offNavDestinationUpdate(
        options: uiObserver.NavDestinationSwitchObserverOptions,
        callback?: Callback<uiObserver.NavDestinationInfo>
    ): void {
        if (this.observerImpl) {
            this.observerImpl!.offNavDestinationUpdate(options, callback);
        }
    }

    public onNavDestinationUpdate(callback: Callback<uiObserver.NavDestinationInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onNavDestinationUpdate(callback);
        }
    }

    public offNavDestinationUpdate(callback?: Callback<uiObserver.NavDestinationInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offNavDestinationUpdate(callback);
        }
    }

    public onRouterPageUpdate(callback: Callback<uiObserver.RouterPageInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onRouterPageUpdate(callback);
        }
    }

    public offRouterPageUpdate(callback?: Callback<uiObserver.RouterPageInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offRouterPageUpdate(callback);
        }
    }

    public onNavDestinationSwitch(callback: Callback<uiObserver.NavDestinationSwitchInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onNavDestinationSwitch(callback);
        }
    }

    public offNavDestinationSwitch(callback?: Callback<uiObserver.NavDestinationSwitchInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offNavDestinationSwitch(callback);
        }
    }
    public onWindowSizeLayoutBreakpointChange(callback: Callback<uiObserver.WindowSizeLayoutBreakpointInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onWindowSizeLayoutBreakpointChange(callback);
        }
    }
    public offWindowSizeLayoutBreakpointChange(callback?: Callback<uiObserver.WindowSizeLayoutBreakpointInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offWindowSizeLayoutBreakpointChange(callback);
        }
    }
    public onNavDestinationSwitch(
        observerOptions: uiObserver.NavDestinationSwitchObserverOptions,
        callback: Callback<uiObserver.NavDestinationSwitchInfo>
    ): void {
        if (this.observerImpl) {
            this.observerImpl!.onNavDestinationSwitch(observerOptions, callback);
        }
    }

    public offNavDestinationSwitch(
        observerOptions: uiObserver.NavDestinationSwitchObserverOptions,
        callback?: Callback<uiObserver.NavDestinationSwitchInfo>
    ): void {
        if (this.observerImpl) {
            this.observerImpl!.offNavDestinationSwitch(observerOptions, callback);
        }
    }

    public onTabChange(callback: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onTabChange(callback);
        }
    }

    public offTabChange(callback?: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offTabChange(callback);
        }
    }

    public onTabChange(options: uiObserver.ObserverOptions, callback: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onTabChange(options, callback);
        }
    }

    public offTabChange(options: uiObserver.ObserverOptions, callback?: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offTabChange(options, callback);
        }
    }

    public onTabContentUpdate(callback: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onTabContentUpdate(callback);
        }
    }

    public offTabContentUpdate(callback?: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offTabContentUpdate(callback);
        }
    }

    public onTabContentUpdate(options: uiObserver.ObserverOptions, callback: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onTabContentUpdate(options, callback);
        }
    }

    public offTabContentUpdate(options: uiObserver.ObserverOptions, callback?: Callback<uiObserver.TabContentInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offTabContentUpdate(options, callback);
        }
    }

    public onDensityUpdate(callback: Callback<uiObserver.DensityInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onDensityUpdate(callback);
        }
    }

    public offDensityUpdate(callback?: Callback<uiObserver.DensityInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offDensityUpdate(callback);
        }
    }

    public onWillDraw(callback: Callback<void>): void {
        if (this.observerImpl) {
            this.observerImpl!.onWillDraw(callback);
        }
    }

    public offWillDraw(callback?: Callback<void>): void {
        if (this.observerImpl) {
            this.observerImpl!.offWillDraw(callback);
        }
    }

    public onDidLayout(callback: Callback<void>): void {
        if (this.observerImpl) {
            this.observerImpl!.onDidLayout(callback);
        }
    }

    public offDidLayout(callback?: Callback<void>): void {
        if (this.observerImpl) {
            this.observerImpl!.offDidLayout(callback);
        }
    }

    public onRouterPageSizeChange(callback: Callback<uiObserver.RouterPageInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onRouterPageSizeChange(callback);
        }
    }

    public offRouterPageSizeChange(callback?: Callback<uiObserver.RouterPageInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offRouterPageSizeChange(callback);
        }
    }

    public onNavDestinationSizeChange(callback: Callback<uiObserver.NavDestinationInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onNavDestinationSizeChange(callback);
        }
    }

    public offNavDestinationSizeChange(callback?: Callback<uiObserver.NavDestinationInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offNavDestinationSizeChange(callback);
        }
    }

    public onNavDestinationSizeChangeByUniqueId(
        navigationUniqueId: int, callback: Callback<uiObserver.NavDestinationInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onNavDestinationSizeChangeByUniqueId(navigationUniqueId, callback);
        }
    }

    public offNavDestinationSizeChangeByUniqueId(
        navigationUniqueId: int, callback?: Callback<uiObserver.NavDestinationInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offNavDestinationSizeChangeByUniqueId(navigationUniqueId, callback);
        }
    }

    public onTextChange(callback: Callback<uiObserver.TextChangeEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onTextChange(callback);
        }
    }
    public offTextChange(callback?: Callback<uiObserver.TextChangeEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offTextChange(callback);
        }
    }
    public onTextChange(
        identity: uiObserver.ObserverOptions, callback: Callback<uiObserver.TextChangeEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.onTextChange(identity, callback);
        }
    }
    public offTextChange(
        identity: uiObserver.ObserverOptions, callback?: Callback<uiObserver.TextChangeEventInfo>): void {
        if (this.observerImpl) {
            this.observerImpl!.offTextChange(identity, callback);
        }
    }

    public onBeforePanStart(callback: PanListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnBeforePanStart(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetPanListenerCallback(this.instanceId_.toInt(), resourceId, 'beforePanStart', callback);
 	}

    public offBeforePanStart(callback?: PanListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemovePanListenerCallback(this.instanceId_.toInt(), 'beforePanStart', callback);
    }

    public onBeforePanEnd(callback: PanListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnBeforePanEnd(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetPanListenerCallback(this.instanceId_.toInt(), resourceId, 'beforePanEnd', callback);
 	}

    public offBeforePanEnd(callback?: PanListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemovePanListenerCallback(this.instanceId_.toInt(), 'beforePanEnd', callback);
    }

    public onAfterPanStart(callback: PanListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnAfterPanStart(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetPanListenerCallback(this.instanceId_.toInt(), resourceId, 'afterPanStart', callback);
 	}

    public offAfterPanStart(callback?: PanListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemovePanListenerCallback(this.instanceId_.toInt(), 'afterPanStart', callback);
    }

    public onAfterPanEnd(callback: PanListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnAfterPanEnd(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetPanListenerCallback(this.instanceId_.toInt(), resourceId, 'afterPanEnd', callback);
 	}

    public offAfterPanEnd(callback?: PanListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemovePanListenerCallback(this.instanceId_.toInt(), 'afterPanEnd', callback);
    }

    public onWillClick(callback: ClickEventListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnWillClick(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetClickListenerCallback(this.instanceId_.toInt(), resourceId, 'willClick', callback);
 	}

    public offWillClick(callback?: ClickEventListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemoveClickListenerCallback(this.instanceId_.toInt(), 'willClick', callback);
    }

    public onDidClick(callback: ClickEventListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnDidClick(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetClickListenerCallback(this.instanceId_.toInt(), resourceId, 'didClick', callback);
 	}

    public offDidClick(callback?: ClickEventListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemoveClickListenerCallback(this.instanceId_.toInt(), 'didClick', callback);
    }

    public onWillTap(callback: GestureEventListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnWillTap(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetTapListenerCallback(this.instanceId_.toInt(), resourceId, 'willTap', callback);
 	}

    public offWillTap(callback?: GestureEventListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemoveTapListenerCallback(this.instanceId_.toInt(), 'willTap', callback);
    }

    public onDidTap(callback: GestureEventListenerCallback): void {
        let resourceId = UIObserverGestureEventOps.setOnDidTap(this.instanceId_.toInt(), callback);
        ArkUIAniModule._GestureEventUIObserver_SetTapListenerCallback(this.instanceId_.toInt(), resourceId, 'didTap', callback);
 	}

    public offDidTap(callback?: GestureEventListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemoveTapListenerCallback(this.instanceId_.toInt(), 'didTap', callback);
    }

    public addGlobalGestureListener(type: GestureListenerType, option: GestureObserverConfigs, callback: GestureListenerCallback): void
    {
        let observer_callback = (info: InnerGestureTriggerInfo,frameNode?: FrameNode) => {
            let triggerInfo : GestureTriggerInfo = {
                event: info.event,
                current: info.current,
                currentPhase: info.currentPhase,
                node: frameNode
            }
            callback(triggerInfo)
        }
        let innerConfig : InnerGestureObserverConfigs = {
            actionPhases: option.actionPhases
        }
        let resourceId = UIObserverGestureEventOps.addGlobalGestureListener(type, innerConfig, observer_callback);
        ArkUIAniModule._GestureEventUIObserver_AddGlobalGestureListener(resourceId, type, callback);
    }

    public removeGlobalGestureListener(type: GestureListenerType, callback?: GestureListenerCallback): void {
        ArkUIAniModule._GestureEventUIObserver_RemoveGlobalGestureListener(type.valueOf(), callback);
    }
}
export interface PageInfo {
        routerPageInfo?: uiObserver.RouterPageInfo;
        navDestinationInfo?: uiObserver.NavDestinationInfo;
}
export interface ContentCoverController {}

export class Magnifier {
    bind(id: string): void {}
    show(x: double, y: double): void {}
    unbind(): void {}
}
export class DynamicSyncScene {
    private range: ExpectedFrameRateRange;
    constructor(range: ExpectedFrameRateRange) {
        this.range = range;
    }

    setFrameRateRange(range: ExpectedFrameRateRange): void {
        this.range = range;
    }

    getFrameRateRange(): ExpectedFrameRateRange {
        return this.range;
    }
}

export const enum SwiperDynamicSyncSceneType {
    GESTURE = 0,
    ANIMATION = 1,
}

export class SwiperDynamicSyncScene extends DynamicSyncScene {
    readonly type: SwiperDynamicSyncSceneType;
    nodePtr: KPointer;
    constructor(type: SwiperDynamicSyncSceneType, nodePtr: KPointer) {
        super({ min: 0, max: 120, expected: 120 } as ExpectedFrameRateRange);
        this.type = type;
        this.nodePtr = nodePtr;
    }

    setFrameRateRange(range: ExpectedFrameRateRange): void {
        super.setFrameRateRange(range);
        ArkUIAniModule._Common_SetFrameRateRange(this.nodePtr, range, this.type);
    }
}

export const enum MarqueeDynamicSyncSceneType {
  ANIMATION = 1
}

export class MarqueeDynamicSyncScene extends DynamicSyncScene {
    readonly type: MarqueeDynamicSyncSceneType;
    nodePtr: KPointer;
    constructor(type: MarqueeDynamicSyncSceneType, nodePtr: KPointer) {
        super({ min: 0, max: 120, expected: 120 } as ExpectedFrameRateRange);
        this.type = type;
        this.nodePtr = nodePtr;
    }

    setFrameRateRange(range: ExpectedFrameRateRange): void {
        super.setFrameRateRange(range);
        ArkUIAniModule._Common_SetFrameRateRange(this.nodePtr, range, this.type);
    }
}

export const enum CustomKeyboardContinueFeature {
    ENABLED = 0,
    DISABLED = 1,
}
