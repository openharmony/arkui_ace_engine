/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

import { __context, StateManager } from '@koalaui/runtime';
import { int32 } from '@koalaui/common';
import { WrappedBuilder } from "./builder"
import { NavigationRouterMap, NavDestinationBuilder } from "#handwritten"
import { InteropNativeModule } from '@koalaui/interop'
import { default as uiObserver } from '@ohos/arkui/observer';
import { ArkStructBase } from '../ArkStructBase';
import { ArkUIAniModule } from 'arkui.ani';
import { ConstraintSizeOptions } from './units';
import { ContextRecord } from 'arkui/base/UIContextImpl';
import { ExtendableComponent, IExtendableComponent } from './extendableComponent';
import { CommonMethod, GeometryInfo, Layoutable, Measurable, SizeResult } from './common';
import { Theme } from '@ohos.arkui.theme';
import { LocalStorage, StateUpdateLoop } from '@ohos.arkui.stateManagement';
import { PeerNode } from '../PeerNode';
import { UIContext } from '@ohos/arkui/UIContext';
import promptAction from '@ohos/promptAction';
import { RecordData } from "@ohos.base"
import { UIContextImpl } from "arkui/base/UIContextImpl"
import { UIContextUtil } from "arkui/base/UIContextUtil"
import { ObserveSingleton } from '../stateManagement/base/observeSingleton';
import { ArkThemeScopeManager } from '../theme/ArkThemeScopeManager';
import { AccessibilityCallback, AccessibilityFocusCallback, TransitionFinishCallback, TipsMessageType, ShouldBuiltInRecognizerParallelWithCallback, OnDragEventCallback, GestureRecognizerJudgeBeginCallback, CustomProperty, MouseEvent, TouchEvent, DragEvent, ResponseType, AttributeModifier, LayoutPolicy, Length, ResourceColor, AccessibilityFocusCallback, AccessibilityOptions, AccessibilityRoleType, AccessibilitySamePageMode, Alignment, AlignRuleOption, AnimateParam, Area, AttributeModifier, Axis, AxisEvent, BackgroundBlurStyleOptions, BackgroundBrightnessOptions, BackgroundEffectOptions, BackgroundImageOptions, BackgroundOptions, BaseGestureEvent, Bindable, BlendApplyType, BlendMode, BlurOptions, BlurStyle, BorderImageOption, BorderOptions, BorderRadiuses, BorderStyle, ChainStyle, ChainWeightOptions, ClickEffect, ClickEvent, Color, ColoringStrategy, ComponentContent, ContentCoverOptions, ContextMenuOptions, CrownEvent, CustomBuilder, CustomPopupOptions, CustomProperty, Dimension, Direction, DragInteractionOptions, DragItemInfo, DragPreviewOptions, DrawModifier, DropOptions, EdgeColors, EdgeOutlineStyles, EdgeOutlineWidths, Edges, EdgeStyles, EdgeWidths, EffectType, FocusAxisEvent, FocusBoxStyle, FocusDrawLevel, FocusMovement, FocusPriority, ForegroundBlurStyleOptions, ForegroundEffectOptions, FunctionKey, GeometryTransitionOptions, GestureInfo, GestureJudgeResult, GestureMask, GestureModifier, GestureRecognizerJudgeBeginCallback, GestureType, HitTestMode, HoverEffect, HoverEvent, ImageRepeat, ImageSize, InvertOptions, ItemAlign, KeyEvent, LinearGradientBlurOptions, LinearGradientOptions, LocalizedAlignRuleOptions, LocalizedBorderRadiuses, LocalizedEdgeColors, LocalizedEdges, LocalizedEdgeWidths, LocalizedPadding, LocalizedPosition, MenuElement, MenuOptions, ModalTransition, ModifierKey, MotionBlurOptions, MotionPathOptions, ObscuredReasons, OnDragEventCallback, OutlineOptions, OutlineRadiuses, OutlineStyle, OverlayOptions, Padding, PixelRoundPolicy, PixelStretchEffectOptions, PopupOptions, Position, PreDragStatus, PreviewConfiguration, ProgressMask, RadialGradientOptions, Rectangle, RenderFit, ResizableOptions, ResourceColor, ResourceStr, ReuseOptions, RotateOptions, SafeAreaEdge, SafeAreaType, ScaleOptions, ShadowOptions, ShadowStyle, sharedTransitionOptions, SheetOptions, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SizeOptions, StateStyles, SweepGradientOptions, SystemAdaptiveOptions, TipsMessageType, TipsOptions, TouchResult, TouchTestInfo, TransitionEffect, TransitionFinishCallback, TranslateOptions, Visibility, VisibleAreaChangeCallback, VisibleAreaEventOptions, VoidCallback } from '#generated';
import { LengthMetrics } from 'arkui/Graphics';
import { default as uiEffect } from '@ohos.graphics.uiEffect';
import { Resource } from 'global.resource';
import { default as matrix4 } from '@ohos.matrix4';
import { default as uniformTypeDescriptor } from '@ohos.data.uniformTypeDescriptor';
import { CircleShape, EllipseShape, PathShape, RectShape } from '@ohos.arkui.shape';
import { default as image } from '@ohos.multimedia.image';

export class ReuseObject {
    readonly _raw: RecordData;
    private _recordValue: Record<string, RecordData> = {}
    private _isRecord: boolean = false;
    constructor(value: RecordData) {
        this._raw = value;
        if (this._raw instanceof Record<string, RecordData>) {
            this._recordValue = value as Record<string, RecordData>;
            this._isRecord = true;
        }
    }

    get raw(): RecordData {
        return this._raw;
    }

    $_get(key: string): RecordData {
        if (this._raw === undefined || this._raw === null) {
            return undefined;
        }
        if (this._isRecord) {
            return this._recordValue[key];
        } else {
            return ((reflect.Value.of(this._raw) as ClassValue).getFieldByName(key).getData() as RecordData);
        }
    }

    has(key: string): boolean {
        if (this._raw === undefined || this._raw === null) {
            return false;
        }
        if (this._isRecord) {
            return this._recordValue.has(key);
        } else {
            return (Type.of(this._raw) as ClassType).hasField(key);
        }
    }

    keys(): string[] {
        if (this._raw === undefined || this._raw === null) {
            return [];
        }
        if (this._isRecord) {
            let key: string[] = [];
            for (let value of this._recordValue.keys()) {
                key.push(value);
            }
            return key;
        } else {
            return Object.getOwnPropertyNames(this._raw!);
        }
    }
}

export interface PageLifeCycle {
    onPageShow(): void {}
    onPageHide(): void {}
    onBackPress(): boolean { return false }
    pageTransition(): void {}
    onNewParam(param: object | undefined | null): void {}
}

export interface LayoutCallbacks {
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {}
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        return {width: 0, height: 0} as SizeResult
    }
}

export class CustomDelegate<T extends ExtendableComponent, T_Options> extends
    ArkStructBase<CustomDelegate<T, T_Options>, T_Options> implements IExtendableComponent {
    private uiContext: UIContext | undefined;
    private instance: ExtendableComponent;
    /** @memo */
    private styles: ((instance: T) => void) | undefined;
    private executedAboutToDisappear: boolean = false;

    constructor(
        uiContext: UIContext | undefined,
        instance: ExtendableComponent,
        /** @memo */
        styles: ((instance: T) => void) | undefined
    ) {
        super();
        this.uiContext = uiContext;
        this.instance = instance;
        this.instance.__setDelegate__Internal(this);
        this.styles = styles;
        ArkThemeScopeManager.getInstance().registerThemeScopeComponent(this);
    }
 
    /** @memo:intrinsic */
    callStyles(): void {
        this.styles?.(this.instance as T)
    }
 
 
    applyStyles(instance: CommonMethod): void {
        if (this.instance instanceof HasCommonMethod) {
            const component = this.instance as HasCommonMethod
            component.__applyStyles(instance);
        }
    }
 
    get hasCommonStyles(): boolean {
        if (this.instance instanceof HasCommonMethod) {            
            const component = this.instance as HasCommonMethod
            return component.__hasCommonMethod;
        }
        return false;
    }

    get isCustomLayout(): boolean {
        return this.instance instanceof LayoutCallbacks;
    }

    __removeChildWhenDispose__IExtendableComponent_Internal(): void {
        this.instance.__removeMeFromParent__Internal();
        this.instance.__removeAllChild__Internal();
    }

    __addMeToParent__IExtendableComponent_Internal(): void {
        this.instance.__addMeToParent__Internal();
    }

    queryNavigationInfo(): uiObserver.NavigationInfo {
        return ArkUIAniModule._CustomNode_QueryNavigationInfo(this.getPeer()!.peer.ptr);
    }

    queryRouterPageInfo(): uiObserver.RouterPageInfo {
        return ArkUIAniModule._CustomNode_QueryRouterPageInfo(this.getPeer()!.peer.ptr);
    }

    queryNavDestinationInfo(isInner:boolean): uiObserver.NavDestinationInfo {
        return ArkUIAniModule._CustomNode_QueryNavDestinationInfo0(this.getPeer()!.peer.ptr, isInner);
    }
    queryNavDestinationInfo() : uiObserver.NavDestinationInfo {
        return ArkUIAniModule._CustomNode_QueryNavDestinationInfo(this.getPeer()!.peer.ptr);
    }

    getDialogController(): promptAction.DialogController | undefined {
        return promptAction.getDialogController(this.getPeer()!.peer.ptr);
    }

    aboutToAppear(): void {
        this.instance.aboutToAppear();
    }
    aboutToDisappear(): void {
        if (!this.executedAboutToDisappear) {
            this.instance.aboutToDisappear();
            this.executedAboutToDisappear = true;
        }
    }
    onDidBuild(): void {
        this.instance.onDidBuild();
    }
    /** @memo */
    build(): void {
        const current = ExtendableComponent.current;
        ExtendableComponent.current = this.instance as object;
        this.onWillApplyTheme(ArkThemeScopeManager.getInstance().getFinalTheme(this));
        this.instance.build();
        ExtendableComponent.current = current;
    }

    onPageShow(): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.onPageShow();
        } else {
            throw new Error('not an entry custom component');
        }
    }
    onPageHide(): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.onPageHide();
        } else {
            throw new Error('not an entry custom component');
        }
    }
    onBackPress(): boolean {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            return page.onBackPress();
        } else {
            throw new Error('not an entry custom component');
        }
    }
    isValidActiveCount(): boolean {
        return this.instance.__getActive__Internal() < 2;
    }
    setActiveCount(active: boolean): void {
        let activeCount: number = this.instance.__getActive__Internal();
        activeCount += active ? 1 : -1;
        this.instance.__setActive__Internal(activeCount);
        if (!this.isValidActiveCount()) {
            console.log(`activeCount_error: ${this.instance.__getActive__Internal()}`);
        }
    }
    isViewActive(): boolean {
        return this.instance.__getActive__Internal() > 0;
    }
    setActiveInternal(active: boolean, isReuse: boolean): void {
        this.setActiveCount(active);
        if (this.isViewActive()) {
            StateUpdateLoop.consumeFreezeTasks(this.getUniqueId());
            ObserveSingleton.instance.unFreezeDelayedComputedProps();
            ObserveSingleton.instance.unFreezeDelayedMonitorPaths();
        }
        const peer = this.getPeerNode() as PeerNode | undefined;
        if (peer) {
            peer.disabledStateUpdates = !this.isViewActive();
        }
        this.instance.__propagateToChild__Internal(active, isReuse);
    }
    pageTransition(): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.pageTransition();
        } else {
            // TODO: Avoid running problem
            // throw new Error('not an entry custom component');
        }
    }
    onNewParam(param: object | undefined | null): void {
        if (this.instance instanceof PageLifeCycle) {
            const page = this.instance as PageLifeCycle;
            page.onNewParam(param);
        } else {
            throw new Error('not an entry custom component');
        }
    }

    aboutToReuse(param: RecordData, initializers?: T_Options): void {
        if (this.instance instanceof ReusableLifeCycle) {
            ArkUIAniModule._CustomNode_OnReuse(this.getPeer()!.peer.ptr);
            const reusable = this.instance as ReusableLifeCycle;
            if (param) {
                reusable.aboutToReuse(new ReuseObject(param))
                return;
            }
            if (initializers === undefined) {
                reusable.aboutToReuse(new ReuseObject({} as Record<string, RecordData> as RecordData));
            } else {
                const component = this.instance as BaseCustomComponent<T_Options>;
                const data: T_Options = initializers as T_Options;
                const params: Record<string, object> = component.__toRecord(data! as object);
                reusable.aboutToReuse(new ReuseObject(params));
            }
        } else if (this.instance instanceof ReusableV2LifeCycle) {
            ArkUIAniModule._CustomNode_OnReuse(this.getPeer()!.peer.ptr);
            const reusable = this.instance as ReusableV2LifeCycle;
            reusable.aboutToReuse();
        } else {
            throw new Error('not an custom component');
        }
    }
    aboutToRecycle(): void {
        if (this.instance instanceof BaseCustomComponent<T_Options>) {
            ArkUIAniModule._CustomNode_OnRecycle(this.getPeer()!.peer.ptr);
            const component = this.instance as BaseCustomComponent<T_Options>;
            component.aboutToRecycle()
        } else {
            throw new Error('not an custom component');
        }
    }

    // Custom layout
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
        if (this.instance instanceof LayoutCallbacks) {
            const layout = this.instance as LayoutCallbacks;
            layout.onPlaceChildren(selfLayoutInfo, children, constraint);
        } else {
            throw new Error('not a custom layout component');
        }
    }
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        if (this.instance instanceof LayoutCallbacks) {
            const layout = this.instance as LayoutCallbacks;
            return layout.onMeasureSize(selfLayoutInfo, children, constraint);
        } else {
            throw new Error('not a custom layout component');
        }
    }

    onDumpInspector(): string {
        return this.instance.__onDumpInspector__Internal();
    }

    onWillApplyTheme(theme: Theme): void {
        this.instance.onWillApplyTheme(theme);
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        if (this.instance instanceof OptionsCallback<T_Options>) {
            const optionsCallback = this.instance as OptionsCallback<T_Options>;
            optionsCallback.__initializeStruct(initializers, content);
        } else {
            throw new Error('not an options callback');
        }
    }

    public __updateStruct(
        initializers?: T_Options
    ): void {
        if (this.instance instanceof OptionsCallback<T_Options>) {
            const optionsCallback = this.instance as OptionsCallback<T_Options>;
            optionsCallback.__updateStruct(initializers);
        } else {
            throw new Error('not an options callback');
        }
    }

    getUniqueId(): int32 {
        const peer = this.getPeer();
        return peer ? peer.getId() : -1;
    }

    getUIContext(): UIContext {
        return this.uiContext!;
    }

    getPeerNode(): PeerNode | undefined {
        return this.getPeer();
    }

    isV2(): boolean {
        return this.instance instanceof CustomComponentV2;
    }

    onCleanup(): void {
        this.aboutToDisappear();
    }

    onGlobalThemeChanged(theme: Theme): void {
        this.onWillApplyTheme(theme);
    }
}

function createInstance<T extends ExtendableComponent, T_Options>(
    uiContext: UIContext | undefined,
    factory: () => T,
    initializers?: () => T_Options,
    /** @memo */
    style?: (instance: T) => void
): CustomDelegate<T, T_Options> {
    return new CustomDelegate<T, T_Options>(uiContext, factory(), style);
}

interface OptionsCallback<T_Options> {
    __initializeStruct(
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {}

    __updateStruct(
        initializers?: T_Options
    ): void {}
}

interface HasCommonMethod {
    __applyStyles(instance: CommonMethod): void;
    readonly __hasCommonMethod: boolean;
}

export abstract class BaseCustomDialog<T extends BaseCustomDialog<T, T_Options>, T_Options> extends ExtendableComponent implements OptionsCallback<T_Options> {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    /** @memo */
    static _invokeImpl<S extends BaseCustomDialog<S, S_Options>, S_Options>(
        factory: () => S,
        initializers?: () => S_Options,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers), content, initializers);
    }
}

export abstract class BaseCustomComponent<T_Options> extends ExtendableComponent implements OptionsCallback<T_Options>, HasCommonMethod, CommonMethod {
    private __commonStyles = new Array<(instance: CommonMethod) => void>();
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }

    /** @memo */
    static _invokeImpl<S extends BaseCustomComponent<S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: () => S_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers, style), content, initializers, reuseKey);
    }

    aboutToRecycle(): void {}

    __toRecord(param: object): Record<string, object> { return {} }
 
    __applyStyles(instance: CommonMethod): void {
        if (this.__hasCommonMethod) {            
            for (let func of this.__commonStyles) {
                func(instance);
            }
            this.__commonStyles = new Array<(instance: CommonMethod) => void>();
        }
    }

    get __hasCommonMethod(): boolean {
        return this.__commonStyles.length > 0;
    }

    width(value: Length | LayoutPolicy | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.width(value));
        return this;
    }
    height(value: Length | LayoutPolicy | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.height(value));
        return this
    }
    drawModifier(value: DrawModifier | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.drawModifier(value));
        return this
    }
    responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.responseRegion(value));
        return this
    }
    mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.mouseResponseRegion(value));
        return this
    }
    size(value: SizeOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.size(value));
        return this
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.constraintSize(value));
        return this
    }
    hitTestBehavior(value: HitTestMode | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.hitTestBehavior(value));
        return this
    }
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onChildTouchTest(value));
        return this
    }
    layoutWeight(value: number | string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.layoutWeight(value));
        return this
    }
    chainWeight(value: ChainWeightOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.chainWeight(value));
        return this
    }
    padding(value: Padding | Length | LocalizedPadding | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.padding(value));
        return this
    }
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.safeAreaPadding(value));
        return this
    }
    margin(value: Padding | Length | LocalizedPadding | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.margin(value));
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundColor(value));
        return this
    }
    pixelRound(value: PixelRoundPolicy | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.pixelRound(value));
        return this
    }
    backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundImageSize(value));
        return this
    }
    backgroundImagePosition(value: Position | Alignment | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundImagePosition(value));
        return this
    }
    backgroundEffect(value: BackgroundEffectOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundEffect(value));
        return this
    }
    backgroundImageResizable(value: ResizableOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundImageResizable(value));
        return this
    }
    foregroundEffect(value: ForegroundEffectOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.foregroundEffect(value));
        return this
    }
    visualEffect(value: uiEffect.VisualEffect | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.visualEffect(value));
        return this
    }
    backgroundFilter(value: uiEffect.Filter | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundFilter(value));
        return this
    }
    foregroundFilter(value: uiEffect.Filter | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.foregroundFilter(value));
        return this
    }
    compositingFilter(value: uiEffect.Filter | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.compositingFilter(value));
        return this
    }
    opacity(value: number | Resource | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.opacity(value));
        return this
    }
    border(value: BorderOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.border(value));
        return this
    }
    borderStyle(value: BorderStyle | EdgeStyles | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.borderStyle(value));
        return this
    }
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.borderWidth(value));
        return this
    }
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.borderColor(value));
        return this
    }
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.borderRadius(value));
        return this
    }
    borderImage(value: BorderImageOption | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.borderImage(value));
        return this
    }
    outline(value: OutlineOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.outline(value));
        return this
    }
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.outlineStyle(value));
        return this
    }
    outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.outlineWidth(value));
        return this
    }
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.outlineColor(value));
        return this
    }
    outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.outlineRadius(value));
        return this
    }
    foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.foregroundColor(value));
        return this
    }
    onClick(value: ((event: ClickEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onClick(value));
        return this
    }
    onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onHover(value));
        return this
    }
    onHoverMove(value: ((value0: HoverEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onHoverMove(value));
        return this
    }
    onAccessibilityHover(value: AccessibilityCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onAccessibilityHover(value));
        return this
    }
    hoverEffect(value: HoverEffect | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.hoverEffect(value));
        return this
    }
    onMouse(value: ((event: MouseEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onMouse(value));
        return this
    }
    onTouch(value: ((event: TouchEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onTouch(value));
        return this
    }
    onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onKeyEvent(value));
        return this
    }
    onDigitalCrown(value: ((value0: CrownEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDigitalCrown(value));
        return this
    }
    onKeyPreIme(value: ((value0: KeyEvent) => boolean) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onKeyPreIme(value));
        return this
    }
    onKeyEventDispatch(value: ((value0: KeyEvent) => boolean) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onKeyEventDispatch(value));
        return this
    }
    onFocusAxisEvent(value: ((value0: FocusAxisEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onFocusAxisEvent(value));
        return this
    }
    onAxisEvent(value: ((value0: AxisEvent) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onAxisEvent(value));
        return this
    }
    focusable(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.focusable(value));
        return this
    }
    nextFocus(value: FocusMovement | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.nextFocus(value));
        return this
    }
    tabStop(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.tabStop(value));
        return this
    }
    onFocus(value: (() => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onFocus(value));
        return this
    }
    onBlur(value: (() => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onBlur(value));
        return this
    }
    tabIndex(value: int32 | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.tabIndex(value));
        return this
    }
    defaultFocus(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.defaultFocus(value));
        return this
    }
    groupDefaultFocus(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.groupDefaultFocus(value));
        return this
    }
    focusOnTouch(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.focusOnTouch(value));
        return this
    }
    focusBox(value: FocusBoxStyle | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.focusBox(value));
        return this
    }
 
    // instructive change start
    public animationStart(value: AnimateParam | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.animationStart(value));
        return this
    }
    public animationStop(value: AnimateParam | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.animationStop(value));
        return this
    }
    // instructive change end
 
    transition(value: TransitionEffect | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.transition(value));
        return this
    }
    motionBlur(value: MotionBlurOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.motionBlur(value));
        return this
    }
    brightness(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.brightness(value));
        return this
    }
    contrast(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.contrast(value));
        return this
    }
    grayscale(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.grayscale(value));
        return this
    }
    colorBlend(value: Color | string | Resource | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.colorBlend(value));
        return this
    }
    saturate(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.saturate(value));
        return this
    }
    sepia(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.sepia(value));
        return this
    }
    invert(value: number | InvertOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.invert(value));
        return this
    }
    hueRotate(value: number | string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.hueRotate(value));
        return this
    }
    useShadowBatching(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.useShadowBatching(value));
        return this
    }
    useEffect(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.useEffect(value));
        return this
    }
    renderGroup(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.renderGroup(value));
        return this
    }
    freeze(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.freeze(value));
        return this
    }
    translate(value: TranslateOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.translate(value));
        return this
    }
    scale(value: ScaleOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.scale(value));
        return this
    }
    rotate(value: RotateOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.rotate(value));
        return this
    }
    transform(value: matrix4.Matrix4Transit | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.transform(value));
        return this
    }
    onAppear(value: (() => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onAppear(value));
        return this
    }
    onDisAppear(value: (() => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDisAppear(value));
        return this
    }
    onAttach(value: VoidCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onAttach(value));
        return this
    }
    onDetach(value: VoidCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDetach(value));
        return this
    }
    onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onAreaChange(value));
        return this
    }
    visibility(value: Visibility | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.visibility(value));
        return this
    }
    flexGrow(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.flexGrow(value));
        return this
    }
    flexShrink(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.flexShrink(value));
        return this
    }
    flexBasis(value: number | string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.flexBasis(value));
        return this
    }
    alignSelf(value: ItemAlign | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.alignSelf(value));
        return this
    }
    displayPriority(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.displayPriority(value));
        return this
    }
    zIndex(value: int32 | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.zIndex(value));
        return this
    }
    direction(value: Direction | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.direction(value));
        return this
    }
    align(value: Alignment | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.align(value));
        return this
    }
    position(value: Position | Edges | LocalizedEdges | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.position(value));
        return this
    }
    markAnchor(value: Position | LocalizedPosition | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.markAnchor(value));
        return this
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.offset(value));
        return this
    }
    enabled(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.enabled(value));
        return this
    }
    alignRules(value: AlignRuleOption | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.alignRules(value));
        return this
    }
    alignRules(value: LocalizedAlignRuleOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.alignRules(value));
        return this
    }
    aspectRatio(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.aspectRatio(value));
        return this
    }
    clickEffect(value: ClickEffect | null | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.clickEffect(value));
        return this
    }
    onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDragStart(value));
        return this
    }
    onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDragEnter(value));
        return this
    }
    onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDragMove(value));
        return this
    }
    onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDragLeave(value));
        return this
    }
    onDrop(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDrop(value));
        return this
    }
    onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDragEnd(value));
        return this
    }
    allowDrop(value: Array<uniformTypeDescriptor.UniformDataType> | null | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.allowDrop(value));
        return this
    }
    draggable(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.draggable(value));
        return this
    }
    dragPreview(value: CustomBuilder | DragItemInfo | string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.dragPreview(value));
        return this
    }
    onPreDrag(value: ((value0: PreDragStatus) => void) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onPreDrag(value));
        return this
    }
    linearGradient(value: LinearGradientOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.linearGradient(value));
        return this
    }
    sweepGradient(value: SweepGradientOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.sweepGradient(value));
        return this
    }
    radialGradient(value: RadialGradientOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.radialGradient(value));
        return this
    }
    motionPath(value: MotionPathOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.motionPath(value));
        return this
    }
    shadow(value: ShadowOptions | ShadowStyle | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.shadow(value));
        return this
    }
    clip(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.clip(value));
        return this
    }
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.clipShape(value));
        return this
    }
    mask(value: ProgressMask | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.mask(value));
        return this
    }
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.maskShape(value));
        return this
    }
    key(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.key(value));
        return this
    }
    id(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.id(value));
        return this
    }
    geometryTransition(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.geometryTransition(value));
        return this
    }
    stateStyles(value: StateStyles | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.stateStyles(value));
        return this
    }
    restoreId(value: int32 | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.restoreId(value));
        return this
    }
    sphericalEffect(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.sphericalEffect(value));
        return this
    }
    lightUpEffect(value: number | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.lightUpEffect(value));
        return this
    }
    pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.pixelStretchEffect(value));
        return this
    }
    accessibilityGroup(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityGroup(value));
        return this
    }
    accessibilityText(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityText(value));
        return this
    }
    accessibilityNextFocusId(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityNextFocusId(value));
        return this
    }
    accessibilityDefaultFocus(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityDefaultFocus(value));
        return this
    }
    accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityUseSamePage(value));
        return this
    }
    accessibilityScrollTriggerable(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityScrollTriggerable(value));
        return this
    }
    accessibilityText(value: Resource | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityText(value));
        return this
    }
    accessibilityRole(value: AccessibilityRoleType | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityRole(value));
        return this
    }
    onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onAccessibilityFocus(value));
        return this
    }
    accessibilityTextHint(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityTextHint(value));
        return this
    }
    accessibilityDescription(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityDescription(value));
        return this
    }
    accessibilityDescription(value: Resource | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityDescription(value));
        return this
    }
    accessibilityLevel(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityLevel(value));
        return this
    }
    accessibilityVirtualNode(value: CustomBuilder | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityVirtualNode(value));
        return this
    }
    accessibilityChecked(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityChecked(value));
        return this
    }
    accessibilitySelected(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilitySelected(value));
        return this
    }
    obscured(value: Array<ObscuredReasons> | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.obscured(value));
        return this
    }
    reuseId(value: string | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.reuseId(value));
        return this
    }
    reuse(value: ReuseOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.reuse(value));
        return this
    }
    renderFit(value: RenderFit | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.renderFit(value));
        return this
    }
    gestureModifier(value: GestureModifier | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.gestureModifier(value));
        return this
    }
    backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundBrightness(value));
        return this
    }
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onGestureJudgeBegin(value));
        return this
    }
    onGestureRecognizerJudgeBegin(value: GestureRecognizerJudgeBeginCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onGestureRecognizerJudgeBegin(value));
        return this
    }
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.shouldBuiltInRecognizerParallelWith(value));
        return this
    }
    monopolizeEvents(value: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.monopolizeEvents(value));
        return this
    }
    onTouchIntercept(value: ((value0: TouchEvent) => HitTestMode) | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onTouchIntercept(value));
        return this
    }
    onSizeChange(value: SizeChangeCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onSizeChange(value));
        return this
    }
    accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityFocusDrawLevel(value));
        return this
    }
    customProperty(name: string, value: CustomProperty): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.customProperty(name, value));
        return this
    }
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.expandSafeArea(types, edges));
        return this
    }
    background(builder: CustomBuilder | undefined, options?: BackgroundOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.background(builder, options));
        return this
    }
    backgroundImage(src: ResourceStr | image.PixelMap | undefined, repeat?: ImageRepeat): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundImage(src, repeat));
        return this
    }
    backgroundImage(src: ResourceStr | image.PixelMap | undefined, options?: BackgroundImageOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundImage(src, options));
        return this
    }
 
    backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundBlurStyle(style, options, sysOptions));
        return this
    }
    backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backgroundEffect(options, sysOptions));
        return this
    }
    foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.foregroundBlurStyle(style, options, sysOptions));
        return this
    }
    onClick(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: double | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onClick(event, distanceThreshold));
        return this
    }
    focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.focusScopeId(id, isGroup, arrowStepOut));
        return this
    }
    focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.focusScopePriority(scopeId, priority));
        return this
    }
    transition(effect: TransitionEffect | undefined, onFinish: TransitionFinishCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.transition(effect, onFinish));
        return this
    }
    gesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.gesture(gesture, mask));
        return this
    }
    priorityGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.priorityGesture(gesture, mask));
        return this
    }
    parallelGesture(gesture: GestureType | undefined, mask?: GestureMask): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.parallelGesture(gesture, mask));
        return this
    }
    blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.blur(blurRadius, options, sysOptions));
        return this
    }
    linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.linearGradientBlur(value, options));
        return this
    }
    systemBarEffect(): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.systemBarEffect());
        return this
    }
    useEffect(useEffect: boolean | undefined, effectType: EffectType | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.useEffect(useEffect, effectType));
        return this
    }
    backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.backdropBlur(radius, options, sysOptions));
        return this
    }
    sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.sharedTransition(id, options));
        return this
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.chainMode(direction, style));
        return this
    }
    onDrop(eventCallback: OnDragEventCallback | undefined, dropOptions?: DropOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onDrop(eventCallback, dropOptions));
        return this
    }
    dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.dragPreview(preview, config));
        return this
    }
    dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.dragPreviewOptions(value, options));
        return this
    }
    overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.overlay(value, options));
        return this
    }
    blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.blendMode(value, type));
        return this
    }
    advancedBlendMode(effect: BlendMode | uiEffect.Blender, type?: BlendApplyType): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.advancedBlendMode(effect, type));
        return this
    }
    geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.geometryTransition(id, options));
        return this
    }
    bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindTips(message, options));
        return this
    }
    bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindPopup(show, popup));
        return this
    }
    bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindMenu(content, options));
        return this
    }
    bindMenu(isShow: boolean | undefined, content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindMenu(isShow, content, options));
        return this
    }
    bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindContextMenu(content, responseType, options));
        return this
    }
    bindContextMenu(isShown: boolean | undefined, content: CustomBuilder | undefined, options?: ContextMenuOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindContextMenu(isShown, content, options));
        return this
    }
    bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, type?: ModalTransition): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindContentCover(isShow, builder, type));
        return this
    }
    bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: ContentCoverOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindContentCover(isShow, builder, options));
        return this
    }
    bindSheet(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.bindSheet(isShow, builder, options));
        return this
    }
    onVisibleAreaChange(ratios: Array<double> | undefined, event: VisibleAreaChangeCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onVisibleAreaChange(ratios, event));
        return this
    }
    onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onVisibleAreaApproximateChange(options, event));
        return this
    }
    keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.keyboardShortcut(value, keys, action));
        return this
    }
    accessibilityGroup(isGroup: boolean | undefined, config: AccessibilityOptions | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.accessibilityGroup(isGroup, config));
        return this
    }
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture: boolean | undefined): this {
        this.__commonStyles.push((instance: CommonMethod): void => instance.onGestureRecognizerJudgeBegin(callback_, exposeInnerGesture));
        return this
    }
}

interface ReusableLifeCycle {
    aboutToReuse(params: ReuseObject): void;
}

export abstract class CustomComponent<T extends CustomComponent<T, T_Options>, T_Options> extends BaseCustomComponent<T_Options> implements ReusableLifeCycle {
    constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
        super(useSharedStorage, storage);
    }
    /** @memo */
    static _invokeImpl<S extends CustomComponent<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: () => S_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers, style), content, initializers, reuseKey);
    }

     aboutToReuse(params: ReuseObject): void {}
}

interface ReusableV2LifeCycle {
    aboutToReuse(): void;
}

export abstract class CustomComponentV2<T extends CustomComponentV2<T, T_Options>, T_Options> extends BaseCustomComponent<T_Options> implements ReusableV2LifeCycle {
    /** @memo */
    static _invokeImpl<S extends CustomComponentV2<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: () => S_Options,
        reuseKey?: string,
        /** @memo */
        content?: () => void
    ): void {
        const context: StateManager = __context() as StateManager;
        const data: ContextRecord | undefined = context.contextData ? context.contextData as ContextRecord : undefined
        const uiContext = data?.uiContext;
        CustomDelegate._instantiate(
            () => createInstance(uiContext, factory, initializers, style), content, initializers, reuseKey);
    }

    aboutToReuse(): void {}
}

export class EntryPoint {
    public static NavigationBuilderRegister(name: string, builder: WrappedBuilder<NavDestinationBuilder>) {
        InteropNativeModule._NativeLog(`AceNavigation: NavigationBuilderRegister for name: ${name}`)
        NavigationRouterMap.RegisterNavDestinationBuilder(name, builder)
    }

    constructor() {}
    /** @memo */
    entry(): void {
    }

    public static RegisterNamedRouter(routerName: string, instance: EntryPoint, param: NavInterface) {
        let uiContext : UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImpl = uiContext.getRouter().getRouter();
        globalRouterImpl.registerNamedRouter(routerName, instance, param);
    }
}

export interface NavInterface {
    bundleName: string;
    moduleName: string;
    pagePath: string;
    pageFullPath: string;
    integratedHsp: string;
}