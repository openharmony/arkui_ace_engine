/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { IBackingValue } from '../base/iBackingValue';
import { FactoryInternal } from '../base/iFactoryInternal';
import { EnvOptions, IEnvDecoratedVariable, IVariableOwner, OBSERVE, SystemEnvKey, ReadonlyEnvKey } from '../decorator';
import { DecoratedVariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { default as uiObserver } from '@ohos/arkui/observer';
import { UIContext } from '@ohos/arkui/UIContext';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { default as window } from '@ohos.window';
import { UIObserver } from '@ohos.arkui.UIContext';
import { HeightBreakpoint, WidthBreakpoint } from '@ohos.arkui.component';
import { int32 } from '@koalaui/common';
import { WindowStaticEnv } from '@ohos.windowenv';

export interface IEnvironmentValueBase {
    onWatchFunc(): void;
    offWatchFunc(instanceId?: int32): void;
}

export interface IEnvironmentValue<T> extends IEnvironmentValueBase {
    get(): T;
    shouldAddRef(): boolean;
    reConstructor(instanceId: int32): void;
}

export interface IEnvVariable {
    registerEnv(instanceId?: int32): void;
    unRegisterEnv(instanceId?: int32): void;
}

export class WindowSizeLayoutBreakpoint implements uiObserver.WindowSizeLayoutBreakpointInfo,
    IEnvironmentValue<uiObserver.WindowSizeLayoutBreakpointInfo> {
    private widthBreakPointBackingValue: IBackingValue<WidthBreakpoint>;
    private heightBreakPointBackingValue: IBackingValue<HeightBreakpoint>;
    private uiObserver: UIObserver;
    private instanceId: int32;

    constructor(instanceId: int32) {
        this.instanceId = instanceId;
        const context: UIContext = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.uiObserver = context.getUIObserver();
        this.widthBreakPointBackingValue = FactoryInternal.mkDecoratorValue<WidthBreakpoint>('EnvWidthBreakpoint', context.getWindowWidthBreakpoint());
        this.heightBreakPointBackingValue = FactoryInternal.mkDecoratorValue<HeightBreakpoint>('EnvHeightBreakpoint', context.getWindowHeightBreakpoint());
    }

    public reConstructor(instanceId: int32): void {
        this.instanceId = instanceId;
        const context: UIContext = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.uiObserver = context.getUIObserver();
        this.widthBreakpoint = context.getWindowWidthBreakpoint();
        this.heightBreakpoint = context.getWindowHeightBreakpoint();
    }

    public onWatchFunc(): void {
        this.uiObserver.onWindowSizeLayoutBreakpointChange(this.breakPointCallback);
    }

    public breakPointCallback(breakPoint: uiObserver.WindowSizeLayoutBreakpointInfo): void {
        this.set(breakPoint);
    }

    get widthBreakpoint(): WidthBreakpoint {
        const shouldAddRef = this.shouldAddRef();
        return this.widthBreakPointBackingValue.get(shouldAddRef);
    }

    set widthBreakpoint(newValue: WidthBreakpoint) {
        const oldWidthBreakpointValue = this.widthBreakPointBackingValue.get(false);
        if (oldWidthBreakpointValue !== newValue) {
            this.widthBreakPointBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get heightBreakpoint(): HeightBreakpoint {
        const shouldAddRef = this.shouldAddRef();
        return this.heightBreakPointBackingValue.get(shouldAddRef);
    }

    set heightBreakpoint(newValue: HeightBreakpoint) {
        const oldHeightBreakpointValue = this.heightBreakPointBackingValue.get(false);
        if (oldHeightBreakpointValue !== newValue) {
            this.heightBreakPointBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    private set(newValue: uiObserver.WindowSizeLayoutBreakpointInfo): void {
        this.widthBreakpoint = newValue.widthBreakpoint;
        this.heightBreakpoint = newValue.heightBreakpoint;
    }
    
    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }

    public get(): uiObserver.WindowSizeLayoutBreakpointInfo {
        return this;
    }

    public offWatchFunc(instanceId?: int32): void {
        this.uiObserver.offWindowSizeLayoutBreakpointChange(this.breakPointCallback);
    }
}


export class WindowAvoidAreaPxEnv implements window.UIEnvWindowAvoidAreaInfoPX, IEnvironmentValue<window.UIEnvWindowAvoidAreaInfoPX> {
    private statusBarBackingValue: IBackingValue<window.AvoidArea>;
    private cutoutBackingValue: IBackingValue<window.AvoidArea>;
    private keyboardBackingValue: IBackingValue<window.AvoidArea>;
    private navigationIndicatorBackingValue: IBackingValue<window.AvoidArea>;
    private win: window.Window;
    private instanceId: int32;
    
    constructor(instanceId: int32) {
        this.instanceId = instanceId;
        const context: UIContext = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.win = window.findWindow(context.getWindowName()!);
        this.statusBarBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvStatusBar', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM));
        this.cutoutBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvCutout', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_CUTOUT));
        this.keyboardBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvKeyboard', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_KEYBOARD));
        this.navigationIndicatorBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvNavigationIndicator', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR));
    }

    public reConstructor(instanceId: int32): void {
        this.instanceId = instanceId;
        const context: UIContext = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.win = window.findWindow(context.getWindowName()!);
        this.statusBar = this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM);
        this.cutout = this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_CUTOUT);
        this.keyboard = this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_KEYBOARD);
        this.navigationIndicator = this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR);
    }

    public onWatchFunc(): void {
        this.win.onAvoidAreaChange(this.avoidAreaChangeCallback);
    }

    public avoidAreaChangeCallback(avoidArea: window.AvoidAreaOptions): void {
        this.set(avoidArea);
    }

    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }

    get statusBar(): window.AvoidArea {
        const shouldAddRef = this.shouldAddRef();
        return this.statusBarBackingValue.get(shouldAddRef);
    }

    set statusBar(newValue: window.AvoidArea) {
        const oldStatusBarValue = this.statusBarBackingValue.get(false);
        if (oldStatusBarValue !== newValue) {
            this.statusBarBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get cutout(): window.AvoidArea {
        const shouldAddRef = this.shouldAddRef();
        return this.cutoutBackingValue.get(shouldAddRef);
    }

    set cutout(newValue: window.AvoidArea) {
        const oldCutoutValue = this.cutoutBackingValue.get(false);
        if (oldCutoutValue !== newValue) {
            this.cutoutBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get keyboard(): window.AvoidArea {
        const shouldAddRef = this.shouldAddRef();
        return this.keyboardBackingValue.get(shouldAddRef);
    }

    set keyboard(newValue: window.AvoidArea) {
        const oldKeyboardValue = this.keyboardBackingValue.get(false);
        if (oldKeyboardValue !== newValue) {
            this.keyboardBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get navigationIndicator(): window.AvoidArea {
        const shouldAddRef = this.shouldAddRef();
        return this.navigationIndicatorBackingValue.get(shouldAddRef);
    }

    set navigationIndicator(newValue: window.AvoidArea) {
        const oldNavigationIndicatorValue = this.navigationIndicatorBackingValue.get(false);
        if (oldNavigationIndicatorValue !== newValue) {
            this.navigationIndicatorBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    private set(tempWindowAvoidArea: window.AvoidAreaOptions): void {
        switch (tempWindowAvoidArea.type) {
            case window.AvoidAreaType.TYPE_SYSTEM:
                this.statusBar = tempWindowAvoidArea.area;
                break;
            case window.AvoidAreaType.TYPE_CUTOUT:
                this.cutout = tempWindowAvoidArea.area;
                break;
            case window.AvoidAreaType.TYPE_KEYBOARD:
                this.keyboard = tempWindowAvoidArea.area;
                break;
            case window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR:
                this.navigationIndicator = tempWindowAvoidArea.area;
                break;
            default:
                break;
        }
    }

    public get(): window.UIEnvWindowAvoidAreaInfoPX {
        return this;
    }

    public offWatchFunc(instanceId?: int32): void {
        if (instanceId === undefined) {
            this.win.offAvoidAreaChange(this.avoidAreaChangeCallback);
        }
    }
}

export class WindowAvoidAreaVpEnv implements window.UIEnvWindowAvoidAreaInfoVP, IEnvironmentValue<window.UIEnvWindowAvoidAreaInfoVP> {
    private statusBarVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private cutoutVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private keyboardVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private navigationIndicatorVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private instanceId: int32;

    private win: window.Window;
    private context: UIContext;
    private areaInPx: Map<window.AvoidAreaType, window.AvoidArea> = new Map<window.AvoidAreaType, window.AvoidArea>();
    private uiObserver: UIObserver;

    constructor(instanceId: int32) {
        this.instanceId = instanceId;
        this.context = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.uiObserver = this.context.getUIObserver();
        this.win = window.findWindow(this.context.getWindowName()!);
        this.initAreaInPx();
        this.statusBarVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvStatusBarVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_SYSTEM)!));
        this.cutoutVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvCutoutVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_CUTOUT)!));
        this.keyboardVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvKeyboardVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_KEYBOARD)!));
        this.navigationIndicatorVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvNavigationIndicatorVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR)!));
    }

    public reConstructor(instanceId: int32): void {
        this.instanceId = instanceId;
        this.context = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.uiObserver = this.context.getUIObserver();
        this.win = window.findWindow(this.context.getWindowName()!);
        this.areaInPx.clear();
        this.initAreaInPx();
        this.statusBar = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_SYSTEM)!);
        this.cutout = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_CUTOUT)!);
        this.keyboard = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_KEYBOARD)!);
        this.navigationIndicator = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR)!);
    }

    private initAreaInPx(): void {
        for (const type of [
            window.AvoidAreaType.TYPE_SYSTEM, 
            window.AvoidAreaType.TYPE_CUTOUT, 
            window.AvoidAreaType.TYPE_KEYBOARD, 
            window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR
        ]) {
            this.areaInPx.set(type, this.win.getWindowAvoidArea(type));
        }
    }

    public onWatchFunc(): void {
        this.win.onAvoidAreaChange(this.avoidAreaChangeCallback);
        this.uiObserver.onDensityUpdate(this.densityUpdateCallback);
    }

    private translateRectToVp(rect: window.Rect): window.RectInVP {
        return {
            left: this.context?.px2vp(rect.left) ?? rect.left.toDouble(),
            top: this.context?.px2vp(rect.top) ?? rect.top.toDouble(),
            width: this.context?.px2vp(rect.width) ?? rect.width.toDouble(),
            height: this.context?.px2vp(rect.height) ?? rect.height.toDouble()
        } as window.RectInVP;
    }

    private translateAvoidAreaToVp(area: window.AvoidArea): window.UIEnvAvoidAreaVP {
        return {
            visible: area.visible,
            leftRect: this.translateRectToVp(area.leftRect),
            topRect: this.translateRectToVp(area.topRect),
            rightRect: this.translateRectToVp(area.rightRect),
            bottomRect: this.translateRectToVp(area.bottomRect)
        } as window.UIEnvAvoidAreaVP;
    }

    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }

    get statusBar(): window.UIEnvAvoidAreaVP {
        const shouldAddRef = this.shouldAddRef();
        return this.statusBarVpBackingValue.get(shouldAddRef);
    }

    set statusBar(newValue: window.UIEnvAvoidAreaVP) {
        const oldStatusBarVpValue = this.statusBarVpBackingValue.get(false);
        if (oldStatusBarVpValue !== newValue) {
            this.statusBarVpBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get cutout(): window.UIEnvAvoidAreaVP {
        const shouldAddRef = this.shouldAddRef();
        return this.cutoutVpBackingValue.get(shouldAddRef);
    }

    set cutout(newValue: window.UIEnvAvoidAreaVP) {
        const oldCutoutVpValue = this.cutoutVpBackingValue.get(false);
        if (oldCutoutVpValue !== newValue) {
            this.cutoutVpBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get keyboard(): window.UIEnvAvoidAreaVP {
        const shouldAddRef = this.shouldAddRef();
        return this.keyboardVpBackingValue.get(shouldAddRef);
    }

    set keyboard(newValue: window.UIEnvAvoidAreaVP) {
        const oldKeyboardVpValue = this.keyboardVpBackingValue.get(false);
        if (oldKeyboardVpValue !== newValue) {
            this.keyboardVpBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get navigationIndicator(): window.UIEnvAvoidAreaVP {
        const shouldAddRef = this.shouldAddRef();
        return this.navigationIndicatorVpBackingValue.get(shouldAddRef);
    }

    set navigationIndicator(newValue: window.UIEnvAvoidAreaVP) {
        const oldNavigationIndicatorVpValue = this.navigationIndicatorVpBackingValue.get(false);
        if (oldNavigationIndicatorVpValue !== newValue) {
            this.navigationIndicatorVpBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    public avoidAreaChangeCallback(avoidArea: window.AvoidAreaOptions): void {
        this.areaInPx.set(avoidArea.type, avoidArea.area);
        switch (avoidArea.type) {
            case window.AvoidAreaType.TYPE_SYSTEM:
                this.statusBar = this.translateAvoidAreaToVp(avoidArea.area);
                break;
            case window.AvoidAreaType.TYPE_CUTOUT:
                this.cutout = this.translateAvoidAreaToVp(avoidArea.area);
                break;
            case window.AvoidAreaType.TYPE_KEYBOARD:
                this.keyboard = this.translateAvoidAreaToVp(avoidArea.area);
                break;
            case window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR:
                this.navigationIndicator = this.translateAvoidAreaToVp(avoidArea.area);
                break;
            default:
                break;
        }
    }

    public densityUpdateCallback(): void {
        this.handleDensityUpdate();
    }

    private handleDensityUpdate(): void {
        if (!this.context) {
            return;
        }
        this.statusBar = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_SYSTEM)!);
        this.cutout = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_CUTOUT)!);
        this.keyboard = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_KEYBOARD)!);
        this.navigationIndicator = this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR)!);
    }

    public get(): window.UIEnvWindowAvoidAreaInfoVP {
        return this;
    }

    public offWatchFunc(instanceId?: int32): void {
        this.areaInPx.clear();
        this.uiObserver.offDensityUpdate(this.densityUpdateCallback);
        if (instanceId === undefined) {
            this.win.offAvoidAreaChange(this.avoidAreaChangeCallback);
        }
    }
}

export class WindowSizePxEnv implements window.Size, IEnvironmentValue<window.Size> {
    private widthBackingValue: IBackingValue<int>;
    private heightBackingValue: IBackingValue<int>;
    private win: window.Window;
    private instanceId: int32;
    
    constructor(instanceId: int32) {
        this.instanceId = instanceId;
        const context = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.win = window.findWindow(context.getWindowName()!);
        const props = this.win.getWindowProperties();
        this.widthBackingValue = FactoryInternal.mkDecoratorValue<int>('EnvWindowSizeWidth', props.windowRect.width);
        this.heightBackingValue = FactoryInternal.mkDecoratorValue<int>('EnvWindowSizeHeight', props.windowRect.height);
    }

    public reConstructor(instanceId: int32): void {
        this.instanceId = instanceId;
        const context = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.win = window.findWindow(context.getWindowName()!);
        const props = this.win.getWindowProperties();
        this.width = props.windowRect.width;
        this.height = props.windowRect.height;
    }

    public onWatchFunc(): void {
        this.win.onWindowSizeChange(this.sizeChangeCallback);
    }

    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }

    get width(): int {
        const shouldAddRef = this.shouldAddRef();
        return this.widthBackingValue.get(shouldAddRef);
    }

    set width(newValue: int) {
        const oldWidthValue = this.widthBackingValue.get(false);
        if (oldWidthValue !== newValue) {
            this.widthBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get height(): int {
        const shouldAddRef = this.shouldAddRef();
        return this.heightBackingValue.get(shouldAddRef);
    }

    set height(newValue: int) {
        const oldHeightValue = this.heightBackingValue.get(false);
        if (oldHeightValue !== newValue) {
            this.heightBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    public sizeChangeCallback(size: window.Size): void {
        this.set(size);
    }

    private set(size: window.Size): void {
        this.width = size.width;
        this.height = size.height;
    }

    public get(): window.Size {
        return this;
    }

    public offWatchFunc(instanceId?: int32): void {
        if (instanceId === undefined) {
            this.win.offWindowSizeChange(this.sizeChangeCallback);
        }
    }
}

export class WindowSizeVpEnv implements window.SizeInVP, IEnvironmentValue<window.SizeInVP> {
    private widthVpBackingValue: IBackingValue<double>;
    private heightVpBackingValue: IBackingValue<double>;
    private win: window.Window;
    private context: UIContext;
    private widthPx: int = 0;
    private heightPx: int = 0;
    private uiObserver: UIObserver;
    private instanceId: int32;
    
    constructor(instanceId: int32) {
        this.instanceId = instanceId;
        this.context = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.uiObserver = this.context.getUIObserver();
        this.win = window.findWindow(this.context.getWindowName()!);
        const props = this.win.getWindowProperties();
        this.widthPx = props.windowRect.width;
        this.heightPx = props.windowRect.height;
        this.widthVpBackingValue = FactoryInternal.mkDecoratorValue<double>('EnvWindowSizeWidthVp', this.context.px2vp(this.widthPx));
        this.heightVpBackingValue = FactoryInternal.mkDecoratorValue<double>('EnvWindowSizeHeightVp', this.context.px2vp(this.heightPx));
    }

    public reConstructor(instanceId: int32): void {
        this.instanceId = instanceId;
        this.context = UIContextUtil.getOrCreateUIContextById(this.instanceId);
        this.uiObserver = this.context.getUIObserver();
        this.win = window.findWindow(this.context.getWindowName()!);
        const props = this.win.getWindowProperties();
        this.widthPx = props.windowRect.width;
        this.heightPx = props.windowRect.height;
        this.width = this.context.px2vp(this.widthPx);
        this.height = this.context.px2vp(this.heightPx);
    }

    public onWatchFunc(): void {
        this.win.onWindowSizeChange(this.sizeChangeCallback);
        this.uiObserver.onDensityUpdate(this.densityChangeCallback);
    }

    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }

    get width(): double {
        const shouldAddRef = this.shouldAddRef();
        return this.widthVpBackingValue.get(shouldAddRef);
    }

    set width(newValue: double) {
        const oldWidthVpValue = this.widthVpBackingValue.get(false);
        if (oldWidthVpValue !== newValue) {
            this.widthVpBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    get height(): double {
        const shouldAddRef = this.shouldAddRef();
        return this.heightVpBackingValue.get(shouldAddRef);
    }

    set height(newValue: double) {
        const oldHeightVpValue = this.heightVpBackingValue.get(false);
        if (oldHeightVpValue !== newValue) {
            this.heightVpBackingValue.setNoCheck(newValue);
            EnvDecoratedVariable.instanceIdSet.add(this.instanceId);
        }
    }

    private updateVpSize(): void {
        if (!this.context) {
            return;
        }
        this.set({
            width: this.context.px2vp(this.widthPx),
            height: this.context.px2vp(this.heightPx)
        } as window.SizeInVP);
    }

    public densityChangeCallback(density: uiObserver.DensityInfo): void {
        this.updateVpSize();
    }

    public sizeChangeCallback(size: window.Size): void {
        this.widthPx = size.width;
        this.heightPx = size.height;
        this.updateVpSize();
    }

    public get(): window.SizeInVP {
        return this;
    }

    private set(size: window.SizeInVP): void {
        this.width = size.width;
        this.height = size.height;
    }

    public offWatchFunc(instanceId?: int32): void {
        this.uiObserver.offDensityUpdate(this.densityChangeCallback);
        if (instanceId === undefined) {
            this.win.offWindowSizeChange(this.sizeChangeCallback);
        }
    }
}

export class EnvUtils {
    public static windowStaticEnvMap: Map<int32, WindowStaticEnv> = new Map<int32, WindowStaticEnv>();
 
 
    public static isSimpleEnvKey(key: string): boolean {
        return key === 'system.window.focused' || key === 'system.window.highlighted' ||
               key === 'system.window.density.system' || key === 'system.window.displayid' ||
               key === 'system.window.avoidarea' || key === 'system.window.avoidarea.px' ||
               key === 'system.window.size' || key === 'system.window.size.px';
    }
 
    public static getOrCreateWindowStaticEnv(uiContext: UIContext): WindowStaticEnv {
        const instanceId: int32 = uiContext.getInstanceId();
        let env = EnvUtils.windowStaticEnvMap.get(instanceId);
        if (env === undefined) {
            env = new WindowStaticEnv(instanceId, uiContext);
            EnvUtils.windowStaticEnvMap.set(instanceId, env);
        }
        return env;
    }
 
    public static registerCallbackOnWindowStaticEnv(env: WindowStaticEnv, key: string , callback: (value: Any) => void): (() => void) | undefined {
        switch (key) {
            case 'system.window.focused':
                return env.registerFocusEnv(callback as (value: boolean) => void);
            case 'system.window.highlighted':
                return env.registerHighlightedEnv(callback as (value: boolean) => void);
            case 'system.window.density.system':
                return env.registerSystemDensityEnv(callback as (value: double) => void);
            case 'system.window.displayid':
                return env.registerDisplayIdEnv(callback as (value: long) => void);
            case 'system.window.avoidarea':
                return env.registerWindowAvoidAreaVpEnv(callback as (value: window.UIEnvWindowAvoidAreaInfoVP) => void);
            case 'system.window.avoidarea.px':
                return env.registerWindowAvoidAreaPxEnv(callback as (value: window.UIEnvWindowAvoidAreaInfoPX) => void);
            case 'system.window.size':
                return env.registerWindowSizeVpEnv(callback as (value: window.SizeInVP) => void);
            case 'system.window.size.px':
                return env.registerWindowSizePxEnv(callback as (value: window.Size) => void);
            default:
                return undefined;
        }
    }
}

export class EnvDecoratedVariable<T> extends DecoratedVariableBase implements IEnvDecoratedVariable<T>, IEnvVariable {
    private owningViewInternal: IVariableOwner;
    private envValue: string | SystemEnvKey<T>;
    private envSystemEnvString: string | undefined;
    public static instanceIdSet: Set<int32> = new Set<int32>();
    private latestInstanceId: int32 | undefined = undefined;
    private finalResultBackingValue?: IBackingValue<IEnvironmentValue<T> | undefined>;
    private systemEnvKeyBackingValue?: IBackingValue<T> | undefined;
    // need to register to view's dispatch function
    private systemEnvKeyCallback: ((value: Any) => void) | undefined;

    constructor(owningView: IVariableOwner, envValue: string | SystemEnvKey<T>, varName: string, envOptions?: EnvOptions<T>) {
        super('@Env', owningView, varName);
        this.owningViewInternal = owningView;
        this.envValue = envValue;

        const isSystemEnvKey = !(typeof envValue === 'string');

        if (isSystemEnvKey) {
            const envkey: SystemEnvKey<T> =  this.envValue as SystemEnvKey<T>;
            this.envSystemEnvString = envkey.key;
            const windowStaticEnv = EnvUtils.getOrCreateWindowStaticEnv(UIContextUtil.getOrCreateCurrentUIContext());
            this.systemEnvKeyBackingValue = FactoryInternal.mkDecoratorValue<T>(
                `SystemEnvKey`, windowStaticEnv.getEnvValueByKey(this.envSystemEnvString as string) as T
            );
        } else {
            this.finalResultBackingValue = FactoryInternal.mkDecoratorValue<IEnvironmentValue<T> | undefined>(
                'EnvFinalResult', undefined
            );
        }
        this.registerEnv();
    }

    public registerEnv(instanceId?: int32): void {
        const tempInstanceId: int32 = instanceId? instanceId : UIContextUtil.getCurrentInstanceId();

        if (this.envSystemEnvString) {
            this.registerSimpleEnv(tempInstanceId, instanceId === undefined);
            this.latestInstanceId = tempInstanceId;
            return;
        }

        const envPropertyFromUIContext: Object | undefined = UIContextUtil.getEnvContextById(tempInstanceId, this.envValue as string);
        if (envPropertyFromUIContext !== undefined) {
            this.finalResult = envPropertyFromUIContext as IEnvironmentValue<T>;
            this.finalResult!.reConstructor(tempInstanceId);
        } else {
            if (this.latestInstanceId === undefined) {
                this.finalResult = this.getEnvProperty(this.envValue as string, tempInstanceId);
            } else {
                this.finalResult = this.getEnvProperty(this.envValue as string, this.latestInstanceId!);
                this.finalResult!.reConstructor(tempInstanceId);
            }
            UIContextUtil.setEnvContextById(tempInstanceId, this.envValue as string, this.finalResult! as Object);
        }
        this.finalResult!.onWatchFunc();
        if (instanceId === undefined) {
            this.owningViewInternal.__addEnvInstance__Internal(this as IEnvVariable);
        }
        EnvDecoratedVariable.instanceIdSet.add(tempInstanceId);
        this.latestInstanceId = tempInstanceId;
    }

    private registerSimpleEnv(instanceId: int32, shouldAddToSet: boolean): void {
        this.systemEnvKeyCallback = (value: Any): void => {
            const oldValue = this.systemEnvKeyBackingValue!.get(false);
            if (oldValue !== (value as T)) {
                this.systemEnvKeyBackingValue!.setNoCheck(value as T);
                EnvDecoratedVariable.instanceIdSet.add(instanceId);
            }
        };

        const isFirst = this.owningViewInternal.__addSimpleEnvCallback__Internal(this.envSystemEnvString!, this.systemEnvKeyCallback!);

        if (isFirst) {
            const callbackSet = this.owningViewInternal.__getSimpleEnvCallbackSet__Internal(this.envSystemEnvString!);
            const dispatchFunc = (value: Any): void => {
                if (callbackSet !== undefined) {
                    for (const cb of callbackSet) {
                        cb(value);
                    }
                }
            };

            this.owningViewInternal.__setSimpleEnvDispatchFunc__Internal(this.envSystemEnvString!, dispatchFunc);

            const windowStaticEnv = EnvUtils.getOrCreateWindowStaticEnv(UIContextUtil.getOrCreateCurrentUIContext());
            const unregisterFunc = EnvUtils.registerCallbackOnWindowStaticEnv(windowStaticEnv, this.envSystemEnvString!, dispatchFunc);
            if (unregisterFunc !== undefined) {
                this.owningViewInternal.__setSimpleEnvUnregisterFunc__Internal(this.envSystemEnvString!, unregisterFunc);
            }
        }

        if (shouldAddToSet) {
            this.owningViewInternal.__addEnvInstance__Internal(this as IEnvVariable);
        }
        EnvDecoratedVariable.instanceIdSet.add(instanceId);
    }

    public unRegisterEnv(instanceId?: int32): void {
        if (this.envSystemEnvString) {
            this.unregisterSystemEnvKey();
        } else {
            this.finalResult!.offWatchFunc(instanceId);
        }
    }

    private unregisterSystemEnvKey(): void {
        if (this.systemEnvKeyCallback === undefined) {
            return;
        }

        this.owningViewInternal.__removeSimpleEnvCallback__Internal(this.envSystemEnvString!, this.systemEnvKeyCallback!);
        this.systemEnvKeyCallback = undefined;
    }

    public resetOnReuse(newValue: T): void {
        return;
    }

    public shouldAddRef(): boolean {
        return OBSERVE.renderingComponent > 0;
    }

    get finalResult(): IEnvironmentValue<T> | undefined {
        const shouldAddRef = this.shouldAddRef();
        return this.finalResultBackingValue!.get(shouldAddRef);
    }

    set finalResult(newValue: IEnvironmentValue<T> | undefined) {
        const oldFinalResultValue = this.finalResultBackingValue!.get(false);
        if (oldFinalResultValue !== newValue) {
            this.finalResultBackingValue!.setNoCheck(newValue);
        }
    }

    public info(): string {
        return this.varName;
    }

    public get(): T {
        if (this.envSystemEnvString) {
            return this.systemEnvKeyBackingValue!.get(this.shouldAddRef());
        }
        return this.finalResult!.get();
    }



    private windowSizeLayoutBreakpointActivate(instanceId: int32): IEnvironmentValue<T> {
        return new WindowSizeLayoutBreakpoint(instanceId) as IEnvironmentValue<T>;
    }

    private windowAvoidAreaPxEnvActivate(instanceId: int32): IEnvironmentValue<T> {
        return new WindowAvoidAreaPxEnv(instanceId) as IEnvironmentValue<T>;
    }

    private windowAvoidAreaVpEnvActivate(instanceId: int32): IEnvironmentValue<T> {
        return new WindowAvoidAreaVpEnv(instanceId) as IEnvironmentValue<T>;
    }

    private windowSizePxEnvActivate(instanceId: int32): IEnvironmentValue<T> {
        return new WindowSizePxEnv(instanceId) as IEnvironmentValue<T>;
    }

    private windowSizeVpEnvActivate(instanceId: int32): IEnvironmentValue<T> {
        return new WindowSizeVpEnv(instanceId) as IEnvironmentValue<T>;
    }

    private getEnvProperty(key: string, instanceId: int32): IEnvironmentValue<T> | undefined {
        let ret: IEnvironmentValue<T> | undefined = undefined;
        switch (key) {
            case 'system.arkui.breakpoint':
                ret = this.windowSizeLayoutBreakpointActivate(instanceId);
                break;
            case 'system.window.avoidarea':
                ret = this.windowAvoidAreaVpEnvActivate(instanceId);
                break;
            case 'system.window.avoidarea.px':
                ret = this.windowAvoidAreaPxEnvActivate(instanceId);
                break;
            case 'system.window.size':
                ret = this.windowSizeVpEnvActivate(instanceId);
                break;
            case 'system.window.size.px':
                ret = this.windowSizePxEnvActivate(instanceId);
                break;
            default:
                break;
        }
        return ret;
    }
}

