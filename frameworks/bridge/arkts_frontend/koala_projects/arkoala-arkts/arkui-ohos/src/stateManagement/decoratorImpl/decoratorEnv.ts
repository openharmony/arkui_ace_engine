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
import { EnvOptions, IEnvDecoratedVariable, IVariableOwner, OBSERVE } from '../decorator';
import { DecoratedVariableBase } from './decoratorBase';
import { uiUtils } from '../base/uiUtilsImpl';
import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { default as uiObserver } from '@ohos/arkui/observer';
import { UIContext } from '@ohos/arkui/UIContext';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { default as window } from '@ohos.window';
import { UIObserver } from '@ohos.arkui.UIContext';
import { HeightBreakpoint, WidthBreakpoint } from '@ohos.arkui.component';

export interface IEnvironmentValueBase {
    destroy(): void;
}

export interface IEnvironmentValue<T> extends IEnvironmentValueBase {
    get(): T;
    shouldAddRef(): boolean;
}

export class WindowSizeLayoutBreakpoint implements uiObserver.WindowSizeLayoutBreakpointInfo,
    IEnvironmentValue<uiObserver.WindowSizeLayoutBreakpointInfo> {
    private widthBreakPointBackingValue: IBackingValue<WidthBreakpoint>;
    private heightBreakPointBackingValue: IBackingValue<HeightBreakpoint>;
    private uiObserver: UIObserver;

    constructor(context: UIContext) {
        this.uiObserver = context.getUIObserver();
        this.widthBreakPointBackingValue = FactoryInternal.mkDecoratorValue<WidthBreakpoint>('EnvWidthBreakpoint', context.getWindowWidthBreakpoint());
        this.heightBreakPointBackingValue = FactoryInternal.mkDecoratorValue<HeightBreakpoint>('EnvHeightBreakpoint', context.getWindowHeightBreakpoint());
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

    public destroy(): void {
        this.uiObserver.offWindowSizeLayoutBreakpointChange(this.breakPointCallback);
    }
}


export class WindowAvoidAreaPxEnv implements window.UIEnvWindowAvoidAreaInfoPX, IEnvironmentValue<window.UIEnvWindowAvoidAreaInfoPX> {
    private statusBarBackingValue: IBackingValue<window.AvoidArea>;
    private cutoutBackingValue: IBackingValue<window.AvoidArea>;
    private keyboardBackingValue: IBackingValue<window.AvoidArea>;
    private navigationIndicatorBackingValue: IBackingValue<window.AvoidArea>;
    private win: window.Window;
    
    constructor(context: UIContext) {
        this.win = window.findWindow(context.getWindowName()!);
        this.statusBarBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvStatusBar', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM));
        this.cutoutBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvCutout', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_CUTOUT));
        this.keyboardBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvKeyboard', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_KEYBOARD));
        this.navigationIndicatorBackingValue = FactoryInternal.mkDecoratorValue<window.AvoidArea>('EnvNavigationIndicator', this.win.getWindowAvoidArea(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR));
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

    public destroy(): void {
        this.win.offAvoidAreaChange(this.avoidAreaChangeCallback);
    }
}

export class WindowAvoidAreaVpEnv implements window.UIEnvWindowAvoidAreaInfoVP, IEnvironmentValue<window.UIEnvWindowAvoidAreaInfoVP> {
    private statusBarVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private cutoutVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private keyboardVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;
    private navigationIndicatorVpBackingValue: IBackingValue<window.UIEnvAvoidAreaVP>;

    private win: window.Window;
    private context: UIContext;
    private areaInPx: Map<window.AvoidAreaType, window.AvoidArea> = new Map<window.AvoidAreaType, window.AvoidArea>();
    private uiObserver: UIObserver;

    constructor(context: UIContext) {
        this.context = context;
        this.uiObserver = this.context.getUIObserver();
        this.win = window.findWindow(this.context.getWindowName()!);
        for (const type of [
            window.AvoidAreaType.TYPE_SYSTEM, 
            window.AvoidAreaType.TYPE_CUTOUT, 
            window.AvoidAreaType.TYPE_KEYBOARD, 
            window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR
        ]) {
            this.areaInPx.set(type, this.win.getWindowAvoidArea(type));
        }
        this.statusBarVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvStatusBarVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_SYSTEM)!));
        this.cutoutVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvCutoutVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_CUTOUT)!));
        this.keyboardVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvKeyboardVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_KEYBOARD)!));
        this.navigationIndicatorVpBackingValue = FactoryInternal.mkDecoratorValue<window.UIEnvAvoidAreaVP>('EnvNavigationIndicatorVp', this.translateAvoidAreaToVp(this.areaInPx.get(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR)!));
        this.win.onAvoidAreaChange(this.avoidAreaChangeCallback);
        this.uiObserver.onDensityUpdate(this.densityUpdateCallback);
    }

    private translateRectToVp(rect: window.Rect): window.RectInVP {
        return {
            left: this.context?.px2vp(rect.left) ?? rect.left as double,
            top: this.context?.px2vp(rect.top) ?? rect.top as double,
            width: this.context?.px2vp(rect.width) ?? rect.width as double,
            height: this.context?.px2vp(rect.height) ?? rect.height as double
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

    public destroy(): void {
        this.areaInPx.clear();
        this.uiObserver.offDensityUpdate(this.densityUpdateCallback);
        this.win.offAvoidAreaChange(this.avoidAreaChangeCallback);
    }
}

export class WindowSizePxEnv implements window.Size, IEnvironmentValue<window.Size> {
    private widthBackingValue: IBackingValue<int>;
    private heightBackingValue: IBackingValue<int>;
    private win: window.Window;
    
    constructor(context: UIContext) {
        this.win = window.findWindow(context.getWindowName()!);
        const props = this.win.getWindowProperties();
        this.widthBackingValue = FactoryInternal.mkDecoratorValue<int>('EnvWindowSizeWidth', props.windowRect.width);
        this.heightBackingValue = FactoryInternal.mkDecoratorValue<int>('EnvWindowSizeHeight', props.windowRect.height);
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

    public destroy(): void {
        this.win.offWindowSizeChange(this.sizeChangeCallback);
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
    
    constructor(context: UIContext) {
        this.context = context;
        this.uiObserver = this.context.getUIObserver();
        this.win = window.findWindow(this.context.getWindowName()!);
        const props = this.win.getWindowProperties();
        this.widthPx = props.windowRect.width;
        this.heightPx = props.windowRect.height;
        this.widthVpBackingValue = FactoryInternal.mkDecoratorValue<double>('EnvWindowSizeWidthVp', this.context.px2vp(this.widthPx));
        this.heightVpBackingValue = FactoryInternal.mkDecoratorValue<double>('EnvWindowSizeHeightVp', this.context.px2vp(this.heightPx));
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

    public destroy(): void {
        this.win.offWindowSizeChange(this.sizeChangeCallback);
        this.uiObserver.offDensityUpdate(this.densityChangeCallback);
    }
}

export class EnvDecoratedVariable<T> extends DecoratedVariableBase implements IEnvDecoratedVariable<T> {
    private finalResult: IEnvironmentValue<T> | undefined;

    constructor(owningView: IVariableOwner, envValue: string, varName: string, envOptions?: EnvOptions<T>) {
        super('@Env', owningView, varName);
        const context = UIContextUtil.getOrCreateCurrentUIContext();
        if (!context) {
            StateMgmtConsole.error('current context is unavailable!');
            throw new Error('current context is unavailable!');
        }
        const findInternalEnv = owningView.__findEnv__Internal(envValue);
        if (findInternalEnv !== undefined) {
            this.finalResult = findInternalEnv as IEnvironmentValue<T>;
        } else {
            this.finalResult = this.registerEnv(envValue, context);
            if (this.finalResult === undefined) {
                StateMgmtConsole.error('final result is undefined!');
                throw new Error('final result is undefined!');
            }
            owningView.__addEnv__Internal(envValue, this.finalResult! as Object);
        }
    }

    public resetOnReuse(newValue: T): void {
        return;
    }

    public info(): string {
        return this.varName;
    }

    public get(): T {
        return this.finalResult!.get();
    }

    private windowSizeLayoutBreakpointActivate(context: UIContext): IEnvironmentValue<T> {
        return new WindowSizeLayoutBreakpoint(context) as IEnvironmentValue<T>;
    }

    private windowAvoidAreaPxEnvActivate(context: UIContext): IEnvironmentValue<T> {
        return new WindowAvoidAreaPxEnv(context) as IEnvironmentValue<T>;
    }

    private windowAvoidAreaVpEnvActivate(context: UIContext): IEnvironmentValue<T> {
        return new WindowAvoidAreaVpEnv(context) as IEnvironmentValue<T>;
    }

    private windowSizePxEnvActivate(context: UIContext): IEnvironmentValue<T> {
        return new WindowSizePxEnv(context) as IEnvironmentValue<T>;
    }

    private windowSizeVpEnvActivate(context: UIContext): IEnvironmentValue<T> {
        return new WindowSizeVpEnv(context) as IEnvironmentValue<T>;
    }

    private registerEnv(key: string, context: UIContext): IEnvironmentValue<T> | undefined {
        let ret: IEnvironmentValue<T> | undefined = undefined;
        switch (key) {
            case 'system.arkui.breakpoint':
                ret = this.windowSizeLayoutBreakpointActivate(context);
                break;
            case 'system.window.avoidarea':
                ret = this.windowAvoidAreaVpEnvActivate(context);
                break;
            case 'system.window.avoidarea.px':
                ret = this.windowAvoidAreaPxEnvActivate(context);
                break;
            case 'system.window.size':
                ret = this.windowSizeVpEnvActivate(context);
                break;
            case 'system.window.size.px':
                ret = this.windowSizePxEnvActivate(context);
                break;
            default:
                break;
        }
        return ret;
    }
}

