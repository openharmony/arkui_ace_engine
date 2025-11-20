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

import { FrameNode } from 'arkui/FrameNode';
import { default as font } from '@ohos/font';
import { MeasureOptions } from '@ohos/measure';
import { SizeOptions } from 'arkui/framework';
import { AnimateParam } from 'arkui/framework';
import { AnimatorResult, AnimatorOptions, Animator, SimpleAnimatorOptions} from '@ohos/animator';
import { Context, PointerStyle, PixelMap } from '#external';
import { UIAbilityContext, ExtensionContext } from "#external"
import { UIContextImpl } from 'arkui/handwritten/UIContextImpl'
import { componentUtils } from '@ohos/arkui/componentUtils';
import { componentSnapshot } from '@ohos/arkui/componentSnapshot';
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
import { TextPickerDialogOptions } from 'arkui/framework';
import { DatePickerDialogOptions } from 'arkui/framework';
import { SheetOptions } from 'arkui/framework';
import inspector from '@ohos/arkui/inspector';
import router from '@ohos/router';
import { ComponentContent } from 'arkui/ComponentContent';
import overlayManager from '@ohos/overlayManager';
import promptAction, { LevelOrder } from '@ohos/promptAction';
import { LocalStorage } from 'arkui/stateManagement/storage/localStorage';
import { CustomBuilder, CustomBuilderT, DragItemInfo, Callback } from 'arkui/framework';
import { Router as RouterExt, AsyncCallback } from 'arkui/base';
import { ComputableState, IncrementalNode } from '@koalaui/runtime';
import { PeerNode } from 'arkui/PeerNode';
import { ArkUIAniModule } from 'arkui.ani';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { int32, int64 } from "@koalaui/common";
import { KPointer } from '@koalaui/interop';

export class UIInspector {
    public createComponentObserver(id: string): inspector.ComponentObserver | undefined {
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

    public back(options?:router.RouterOptions): void {
        throw Error("back not implemented in Router!");
    }

    public clear(): void {
        throw Error("clear not implemented in Router!");
    }
    public getLength(): string {
        throw Error("getLength not implemented in Router!");
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
                             delay?: number, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): void {
        throw Error("createFromBuilder with callback not implemented in ComponentSnapshot!")
    }
    //@ts-ignore
    public createFromBuilder(builder: CustomBuilder, delay?: number, checkImageStatus?: boolean,
                             options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("createFromBuilder with promise not implemented in ComponentSnapshot!")
    }
    public getSync(id: string, options?: componentSnapshot.SnapshotOptions): PixelMap | null {
        throw Error("getSync not implemented in ComponentSnapshot!")
    }
    public getWithUniqueId(uniqueId: number, options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("getWithUniqueId not implemented in ComponentSnapshot!")
    }

    public getSyncWithUniqueId(uniqueId: number, options?: componentSnapshot.SnapshotOptions): PixelMap {
        throw Error("getSyncWithUniqueId not implemented in ComponentSnapshot!")
    }

    public createFromComponent<T extends Object>(content: ComponentContent<T>, delay?: number, checkImageStatus?: boolean,
        options?: componentSnapshot.SnapshotOptions): Promise<PixelMap> | null {
        throw Error("getSyncWithUniqueId not implemented in ComponentSnapshot!")
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

export class UIContext {
    constructor() {
    }
    static getFocusedUIContext(): UIContext | undefined {
        const instanceId = ArkUIAniModule._Common_GetFocused_InstanceId();
        if (instanceId === -1) {
            return undefined;
        }
        return UIContextUtil.getOrCreateUIContextById(instanceId);
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
    public getSharedLocalStorage(): LocalStorage | undefined {
        throw Error('getFrameNodeById not implemented in UIContext!');
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
    getNavigationInfoByUniqueId(id: int64): uiObserver.NavigationInfo | undefined {
        throw Error("getNavigationInfoByUniqueId not implemented in UIContext!")
    }
    getHostContext(): Context | undefined {
        throw Error("getHostContext not implemented in UIContext!")
    }

    public getKeyboardAvoidMode(): KeyboardAvoidMode {
        throw Error("getKeyboardAvoidMode not implemented in UIContext!")
    }

    public setKeyboardAvoidMode(mode: KeyboardAvoidMode) {
        throw Error("setKeyboardAvoidMode not implemented in UIContext!")
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

    public getDragController(): DragController {
        throw Error("getDragController not implemented in UIContext!")
    }

    public getRouter(): Router {
        throw Error("getRouter not implemented in UIContext!")
    }

    public keyframeAnimateTo(param: KeyframeAnimateParam, keyframes: Array<KeyframeState>): void {
        throw Error("animateTo not implemented in UIContext!")
    }

    public animateTo(param: AnimateParam, event: (() => void)): void {
        throw Error("animateTo not implemented in UIContext!")
    }

    public animateToImmediately(value: AnimateParam, event: Callback<void>): void {
        throw Error("animateToImmediately not implemented in UIContext!")
    }

    public createAnimator(options: AnimatorOptions | SimpleAnimatorOptions): AnimatorResult {
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

    public getOverlayManager(): OverlayManager {
        throw Error("getOverlayManager not implemented in UIContext!")
    }

    public setOverlayManagerOptions(options: OverlayManagerOptions): boolean {
        throw Error("setOverlayManagerOptions not implemented in UIContext!")
    }

    public getOverlayManagerOptions(): OverlayManagerOptions {
        throw Error("getOverlayManagerOptions not implemented in UIContext!")
    }

    public getPromptAction(): PromptAction {
        throw Error("getPromptAction not implemented in UIContext!")
    }

    public showAlertDialog(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons |
        AlertDialogParamWithOptions): void {
        throw Error("showAlertDialog not implemented in UIContext!")
    }

    public showActionSheet(options: ActionSheetOptions): void {
        throw Error("showActionSheet not implemented in UIContext!")
    }

    public showTimePickerDialog(options: TimePickerDialogOptions): void {
        throw Error("showTimePickerDialog not implemented in UIContext!")
    }

    public showTextPickerDialog(options: TextPickerDialogOptions): void {
        throw Error("showTextPickerDialog not implemented in UIContext!")
    }

    public showDatePickerDialog(options: DatePickerDialogOptions): void {
        throw Error("showDatePickerDialog not implemented in UIContext!")
    }
    // @ts-ignore
    public freezeUINode(id: number, isFrozen: boolean): void {
        throw Error("freezeUINode not implemented in UIContext!")
    }

    // @ts-ignore
    public freezeUINode(id: string, isFrozen: boolean): void {
        throw Error("freezeUINode not implemented in UIContext!")
    }

    public enableSwipeBack(enabled: boolean | undefined): void {
        throw Error("enableSwipeBack not implemented in UIContext!")
    }

    public getWindowName(): string | undefined {
        throw Error("getWindowName not implemented in UIContext!")
    }
    public getWindowWidthBreakpoint(): WidthBreakpoint {
        throw Error("getWindowWidthBreakpoint not implemented in UIContext!")
    }
    public getWindowHeightBreakpoint(): HeightBreakpoint {
        throw Error("getWindowHeightBreakpoint not implemented in UIContext!")
    }
    public vp2px(value: number): number {
        throw Error("vp2px not implemented in UIContext!")
    }
    public px2vp(value: number): number {
        throw Error("px2vp not implemented in UIContext!")
    }
    public fp2px(value: number): number {
        throw Error("fp2px not implemented in UIContext!")
    }
    public px2fp(value: number): number {
        throw Error("px2fp not implemented in UIContext!")
    }
    public lpx2px(value: number): number {
        throw Error("lpx2px not implemented in UIContext!")
    }
    public px2lpx(value: number): number {
        throw Error("px2lpx not implemented in UIContext!")
    }

    public getId() : int32 {
        throw Error("getId not implemented in UIContext!")
    }
    public setUIStates(callback: () => void): void {
        throw Error("setUIStates not implemented in UIContext!")
    }
    static createUIContextWithoutWindow(context: UIAbilityContext | ExtensionContext) : UIContext | undefined {
        return UIContextImpl.createUIContextWithoutWindow(context)
    }
    static destroyUIContextWithoutWindow() {
        UIContextImpl.destroyUIContextWithoutWindow()
    }
    public getFilteredInspectorTree(filters?: Array<string>): string {
        throw Error("getFilteredInspectorTree not implemented in UIContext!")
    }
 
    public getFilteredInspectorTreeById(id: string, depth: int, filters?: Array<string>): string {
        throw Error("getFilteredInspectorTreeById not implemented in UIContext!")
    }
    public setImageCacheCount(value: int): void {
        throw Error("setImageCacheCount not implemented in UIContext!")
    }

    public setImageRawDataCacheSize(value: int): void {
        throw Error("setImageRawDataCacheSize not implemented in UIContext!")
    }

    public requireDynamicSyncScene(id: string): Array<DynamicSyncScene> {
        throw Error("requireDynamicSyncScene not implemented in UIContext!");
    }

    public openBindSheet(bindSheetContent: ComponentContent, sheetOptions?: SheetOptions, targetId?: int): Promise<void> {
        throw Error("openBindSheet not implemented in UIContext!")
    }

    public updateBindSheet(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        throw Error("updateBindSheet not implemented in UIContext!")
    }

    public closeBindSheet(bindSheetContent: ComponentContent): Promise<void> {
        throw Error("closeBindSheet not implemented in UIContext!")
    }
}
export abstract class FrameCallback {
    onFrame(frameTimeInNano: number): void {}
    onIdle(timeLeftInNano: number): void {}
}

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
}
export interface PageInfo {}
export interface ContentCoverController {}
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