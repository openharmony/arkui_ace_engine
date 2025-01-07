/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to  in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

var __decorate = (this && this.__decorate) || function (m10, n10, o10, p10) {
    var q10 = arguments.length, r10 = q10 < 3 ? n10 : p10 === null ? p10 = Object.getOwnPropertyDescriptor(n10, o10) : p10, s10;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r10 = Reflect.decorate(m10, n10, o10, p10);
    else
        for (var t10 = m10.length - 1; t10 >= 0; t10--)
            if (s10 = m10[t10])
                r10 = (q10 < 3 ? s10(r10) : q10 > 3 ? s10(n10, o10, r10) : s10(n10, o10)) || r10;
    return q10 > 3 && r10 && Object.defineProperty(n10, o10, r10), r10;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}

const hilog = requireNapi('hilog');
const deviceInfo = requireNapi('deviceInfo');
const display = requireNapi('display');
const mediaquery = requireNapi('mediaquery');

const TAG = 'DeviceHelper';
export class DeviceHelper {
    static isPhone() {
        return (DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_PHONE || DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_DEFAULT);
    }
    static isTablet() {
        return DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_TABLET;
    }
    static isFold() {
        let k10 = false;
        try {
            k10 = display.isFoldable();
        }
        catch (l10) {
            hilog.error(0x0000, TAG, 'isFold -> isFoldable try error:', l10);
        }
        return k10;
    }
    static isExpanded() {
        let i10 = false;
        try {
            i10 = display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_EXPANDED;
        }
        catch (j10) {
            hilog.error(0x0000, TAG, 'isExpanded -> try error:', j10);
        }
        return i10;
    }
    static isColumn() {
        let g10 = false;
        try {
            g10 = display.isFoldable() && (display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_EXPANDED ||
                display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_HALF_FOLDED);
        }
        catch (h10) {
            hilog.error(0x0000, TAG, 'isColumn -> try error:', h10);
        }
        return g10;
    }
    static isStraightProduct() {
        return DeviceHelper.isPhone() && !DeviceHelper.isFold();
    }
}
DeviceHelper.TYPE_DEFAULT = 'default';
DeviceHelper.TYPE_PHONE = 'phone';
DeviceHelper.TYPE_TABLET = 'tablet';
DeviceHelper.DEVICE_TYPE = deviceInfo.deviceType;
export class DeviceListenerManager {
    constructor() {
        this.portraitListener = mediaquery.matchMediaSync('(orientation: portrait)');
        this.drawableWidthLargeListener = mediaquery.matchMediaSync('(width >= 600vp)');
        this.isPortrait = undefined;
        this.onOrientationChange = undefined;
        this.isLarge = undefined;
        this.onDrawableWidthChange = undefined;
    }
    static getInstance() {
        if (DeviceListenerManager.instance === undefined) {
            DeviceListenerManager.instance = new DeviceListenerManager();
        }
        return DeviceListenerManager.instance;
    }
    onPortraitChange(e10) {
        let f10 = false;
        if (DeviceListenerManager.getInstance().isPortrait === undefined) {
            DeviceListenerManager.getInstance().isPortrait = e10.matches;
            f10 = true;
        }
        else {
            if (e10.matches) {
                if (!DeviceListenerManager.getInstance().isPortrait) {
                    DeviceListenerManager.getInstance().isPortrait = true;
                    f10 = true;
                    hilog.debug(0x0000, 'MultiNavigation', 'display portrait');
                }
            }
            else {
                if (DeviceListenerManager.getInstance().isPortrait) {
                    DeviceListenerManager.getInstance().isPortrait = false;
                    f10 = true;
                    hilog.debug(0x0000, 'MultiNavigation', 'display landscape');
                }
            }
        }
        if (f10) {
            DeviceListenerManager.getInstance().notifyOrientationChange();
        }
    }
    notifyOrientationChange() {
        this.onOrientationChange && this.onOrientationChange(this.isPortrait);
    }
    onDrawableWidthLargeChange(c10) {
        let d10 = false;
        if (DeviceListenerManager.getInstance().isLarge === undefined) {
            DeviceListenerManager.getInstance().isLarge = c10.matches;
            d10 = true;
        }
        else {
            if (c10.matches) {
                if (!DeviceListenerManager.getInstance().isLarge) {
                    DeviceListenerManager.getInstance().isLarge = true;
                    d10 = true;
                    hilog.debug(0x0000, 'MultiNavigation', 'display isLarge');
                }
            }
            else {
                if (DeviceListenerManager.getInstance().isLarge) {
                    DeviceListenerManager.getInstance().isLarge = false;
                    d10 = true;
                    hilog.debug(0x0000, 'MultiNavigation', 'display not large');
                }
            }
        }
        if (d10) {
            DeviceListenerManager.getInstance().notifyWidthChange();
        }
    }
    notifyWidthChange() {
        this.onDrawableWidthChange && this.onDrawableWidthChange(this.isLarge);
    }
    registerOrientationLister(b10) {
        this.onOrientationChange = b10;
        this.onOrientationChange && this.isPortrait && this.onOrientationChange(this.isPortrait);
    }
    unregisterOrientationLister() {
        this.onOrientationChange = undefined;
    }
    registerDrawableWidthLister(a10) {
        this.onDrawableWidthChange = a10;
        this.onDrawableWidthChange && this.isLarge && this.onDrawableWidthChange(this.isLarge);
    }
    unregisterDrawableWidthLister() {
        this.onDrawableWidthChange = undefined;
    }
    initListener() {
        this.portraitListener.on('change', this.onPortraitChange);
        this.drawableWidthLargeListener.on('change', this.onDrawableWidthLargeChange);
    }
    finalizeListener() {
        this.portraitListener.off('change', this.onPortraitChange);
        this.drawableWidthLargeListener.off('change', this.onDrawableWidthLargeChange);
    }
}
let NavWidthRangeAttrModifier = class NavWidthRangeAttrModifier {
    constructor() {
        this.isApplicationSet = false;
        this.minHomeWidth = '50%';
        this.maxHomeWidth = '50%';
    }
    applyNormalAttribute(z9) {
        if (this.isApplicationSet) {
            z9.navBarWidthRange([this.minHomeWidth, this.maxHomeWidth]);
        }
    }
};
NavWidthRangeAttrModifier = __decorate([
    Observed
], NavWidthRangeAttrModifier);
export { NavWidthRangeAttrModifier };
export class SubNavigation extends ViewPU {
    constructor(s9, t9, u9, v9 = -1, w9 = undefined, x9) {
        super(s9, u9, v9, x9);
        if (typeof w9 === "function") {
            this.paramsGenerator_ = w9;
        }
        this.__isPortrait = new SynchedPropertySimpleTwoWayPU(t9.isPortrait, this, "isPortrait");
        this.__displayMode = new ObservedPropertySimplePU(0, this, "displayMode");
        this.__multiStack = new SynchedPropertyNesedObjectPU(t9.multiStack, this, "multiStack");
        this.navDestination = undefined;
        this.primaryStack = new MyNavPathStack();
        this.__secondaryStack = new ObservedPropertyObjectPU(new MyNavPathStack(), this, "secondaryStack");
        this.__primaryWidth = new ObservedPropertySimplePU('50%', this, "primaryWidth");
        this.__needRenderIsFullScreen = new SynchedPropertyNesedObjectPU(t9.needRenderIsFullScreen, this, "needRenderIsFullScreen");
        this.__needRenderLeftClickCount = new SynchedPropertyNesedObjectPU(t9.needRenderLeftClickCount, this, "needRenderLeftClickCount");
        this.__navWidthRangeModifier = new SynchedPropertyNesedObjectPU(t9.navWidthRangeModifier, this, "navWidthRangeModifier");
        this.__needRenderDisplayMode = new SynchedPropertyNesedObjectPU(t9.needRenderDisplayMode, this, "needRenderDisplayMode");
        this.onNavigationModeChange = (y9) => { };
        this.setInitiallyProvidedValue(t9);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r9) {
        if (r9.displayMode !== undefined) {
            this.displayMode = r9.displayMode;
        }
        this.__multiStack.set(r9.multiStack);
        if (r9.navDestination !== undefined) {
            this.navDestination = r9.navDestination;
        }
        if (r9.primaryStack !== undefined) {
            this.primaryStack = r9.primaryStack;
        }
        if (r9.secondaryStack !== undefined) {
            this.secondaryStack = r9.secondaryStack;
        }
        if (r9.primaryWidth !== undefined) {
            this.primaryWidth = r9.primaryWidth;
        }
        this.__needRenderIsFullScreen.set(r9.needRenderIsFullScreen);
        this.__needRenderLeftClickCount.set(r9.needRenderLeftClickCount);
        this.__navWidthRangeModifier.set(r9.navWidthRangeModifier);
        this.__needRenderDisplayMode.set(r9.needRenderDisplayMode);
        if (r9.onNavigationModeChange !== undefined) {
            this.onNavigationModeChange = r9.onNavigationModeChange;
        }
    }
    updateStateVars(q9) {
        this.__multiStack.set(q9.multiStack);
        this.__needRenderIsFullScreen.set(q9.needRenderIsFullScreen);
        this.__needRenderLeftClickCount.set(q9.needRenderLeftClickCount);
        this.__navWidthRangeModifier.set(q9.navWidthRangeModifier);
        this.__needRenderDisplayMode.set(q9.needRenderDisplayMode);
    }
    purgeVariableDependenciesOnElmtId(p9) {
        this.__isPortrait.purgeDependencyOnElmtId(p9);
        this.__displayMode.purgeDependencyOnElmtId(p9);
        this.__multiStack.purgeDependencyOnElmtId(p9);
        this.__secondaryStack.purgeDependencyOnElmtId(p9);
        this.__primaryWidth.purgeDependencyOnElmtId(p9);
        this.__needRenderIsFullScreen.purgeDependencyOnElmtId(p9);
        this.__needRenderLeftClickCount.purgeDependencyOnElmtId(p9);
        this.__navWidthRangeModifier.purgeDependencyOnElmtId(p9);
        this.__needRenderDisplayMode.purgeDependencyOnElmtId(p9);
    }
    aboutToBeDeleted() {
        this.__isPortrait.aboutToBeDeleted();
        this.__displayMode.aboutToBeDeleted();
        this.__multiStack.aboutToBeDeleted();
        this.__secondaryStack.aboutToBeDeleted();
        this.__primaryWidth.aboutToBeDeleted();
        this.__needRenderIsFullScreen.aboutToBeDeleted();
        this.__needRenderLeftClickCount.aboutToBeDeleted();
        this.__navWidthRangeModifier.aboutToBeDeleted();
        this.__needRenderDisplayMode.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isPortrait() {
        return this.__isPortrait.get();
    }
    set isPortrait(o9) {
        this.__isPortrait.set(o9);
    }
    get displayMode() {
        return this.__displayMode.get();
    }
    set displayMode(n9) {
        this.__displayMode.set(n9);
    }
    get multiStack() {
        return this.__multiStack.get();
    }
    get secondaryStack() {
        return this.__secondaryStack.get();
    }
    set secondaryStack(m9) {
        this.__secondaryStack.set(m9);
    }
    get primaryWidth() {
        return this.__primaryWidth.get();
    }
    set primaryWidth(l9) {
        this.__primaryWidth.set(l9);
    }
    get needRenderIsFullScreen() {
        return this.__needRenderIsFullScreen.get();
    }
    get needRenderLeftClickCount() {
        return this.__needRenderLeftClickCount.get();
    }
    get navWidthRangeModifier() {
        return this.__navWidthRangeModifier.get();
    }
    get needRenderDisplayMode() {
        return this.__needRenderDisplayMode.get();
    }
    SubNavDestination(i9, j9, k9 = null) {
        this.navDestination.bind(this)(i9, j9);
    }
    getMode() {
        this.displayMode = this.needRenderDisplayMode.displayMode;
        if (DeviceHelper.isPhone() && DeviceHelper.isStraightProduct()) {
            return NavigationMode.Stack;
        }
        if (this.displayMode === display.FoldStatus.FOLD_STATUS_UNKNOWN) {
            try {
                this.displayMode = display.getFoldStatus();
            } catch (err) {
                hilog.warn(0x0000, 'MultiNavigation', 'Failed to get fold status. error:' + JSON.stringify(err));
            }
        }
        if (DeviceHelper.isTablet() && this.isPortrait) {
            hilog.info(0x0000, 'MultiNavigation', 'SubNavigation getMode tablet portrait');
            return NavigationMode.Stack;
        }
        if (this.needRenderIsFullScreen.isFullScreen == undefined) {
            if (DeviceHelper.isPhone()) {
                return this.secondaryStack.size() > 0 && DeviceHelper.isColumn() ? NavigationMode.Auto : NavigationMode.Stack;
            }
            return this.secondaryStack.size() > 0 ? NavigationMode.Auto : NavigationMode.Stack;
        }
        return this.needRenderIsFullScreen.isFullScreen ? NavigationMode.Stack : NavigationMode.Auto;
    }
    aboutToAppear() {
        hilog.debug(0x0000, 'MultiNavigation', 'SubNavigation aboutToAppear param = ' + JSON.stringify(this.primaryStack));
    }
    initialRender() {
        this.observeComponentCreation2((a9, b9) => {
            NavDestination.create(() => {
                this.observeComponentCreation2((f9, g9) => {
                    Navigation.create(this.secondaryStack, { moduleName: "MultiNavigation", pagePath: "", isUserCreateStack: true });
                    Navigation.mode(this.getMode());
                    Navigation.onNavigationModeChange(this?.onNavigationModeChange);
                    Navigation.hideBackButton(true);
                    Navigation.hideTitleBar(true);
                    Navigation.navDestination({ builder: this.SubNavDestination.bind(this) });
                    Navigation.navBarWidth(this.primaryWidth);
                    Navigation.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.navWidthRangeModifier));
                    Navigation.onTouch((h9) => {
                        if (h9.type === TouchType.Down) {
                            hilog.info(0x0000, 'MultiNavigation', 'outer navigation this.outerStack.leftClickCount ' +
                                this.needRenderLeftClickCount.leftClickCount);
                            this.needRenderLeftClickCount.leftClickCount--;
                        }
                    });
                }, Navigation);
                this.observeComponentCreation2((c9, d9) => {
                    Navigation.create(this.primaryStack, { moduleName: "MultiNavigation", pagePath: "", isUserCreateStack: true });
                    Navigation.hideNavBar(true);
                    Navigation.mode(NavigationMode.Stack);
                    Navigation.navDestination({ builder: this.SubNavDestination.bind(this) });
                    Navigation.hideTitleBar(true);
                    Navigation.hideToolBar(true);
                    Navigation.hideBackButton(true);
                    Navigation.onTouch((e9) => {
                        if (e9.type === TouchType.Down) {
                            this.needRenderLeftClickCount.leftClickCount = 2;
                        }
                    });
                }, Navigation);
                Navigation.pop();
                Navigation.pop();
            }, { moduleName: "MultiNavigation", pagePath: "" });
            NavDestination.onBackPressed(() => {
                hilog.debug(0x0000, 'MultiNavigation', 'subNavigation NavDestination onBackPressed');
                if (this.multiStack && this.secondaryStack.size() === 1) {
                    hilog.info(0x0000, 'MultiNavigation', 'subNavigation NavDestination onBackPressed multiStack.pop');
                    this.multiStack.pop();
                    return true;
                }
                return false;
            });
            NavDestination.hideTitleBar(true);
        }, NavDestination);
        NavDestination.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export var SplitPolicy;
(function (z8) {
    z8[z8["HOME_PAGE"] = 0] = "HOME_PAGE";
    z8[z8["DETAIL_PAGE"] = 1] = "DETAIL_PAGE";
    z8[z8["FULL_PAGE"] = 2] = "FULL_PAGE";
    z8[z8["PlACE_HOLDER_PAGE"] = 3] = "PlACE_HOLDER_PAGE";
})(SplitPolicy || (SplitPolicy = {}));
let that;
export class MultiNavigation extends ViewPU {
    constructor(q8, r8, s8, t8 = -1, u8 = undefined, v8) {
        super(q8, s8, t8, v8);
        if (typeof u8 === "function") {
            this.paramsGenerator_ = u8;
        }
        this.foldStatusCallback = (y8) => {
            hilog.info(0x0000, 'MultiNavigation', 'foldStatusCallback data.valueOf()=' + y8.valueOf());
            this.multiStack.needRenderDisplayMode.displayMode = y8.valueOf();
            this.multiStack.handleRefreshPlaceHolderIfNeeded();
        };
        this.__multiStack = new ObservedPropertyObjectPU(new MultiNavPathStack(), this, "multiStack");
        this.navDestination = undefined;
        this.mode = undefined;
        this.onNavigationModeChangeCallback = (x8) => {
        };
        this.onHomeShowOnTop = (w8) => { };
        this.__isPortrait = new ObservedPropertySimplePU(false, this, "isPortrait");
        this.setInitiallyProvidedValue(r8);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p8) {
        if (p8.foldStatusCallback !== undefined) {
            this.foldStatusCallback = p8.foldStatusCallback;
        }
        if (p8.multiStack !== undefined) {
            this.multiStack = p8.multiStack;
        }
        if (p8.navDestination !== undefined) {
            this.navDestination = p8.navDestination;
        }
        if (p8.mode !== undefined) {
            this.mode = p8.mode;
        }
        if (p8.onNavigationModeChangeCallback !== undefined) {
            this.onNavigationModeChangeCallback = p8.onNavigationModeChangeCallback;
        }
        if (p8.onHomeShowOnTop !== undefined) {
            this.onHomeShowOnTop = p8.onHomeShowOnTop;
        }
        if (p8.isPortrait !== undefined) {
            this.isPortrait = p8.isPortrait;
        }
    }
    updateStateVars(o8) {
    }
    purgeVariableDependenciesOnElmtId(n8) {
        this.__multiStack.purgeDependencyOnElmtId(n8);
        this.__isPortrait.purgeDependencyOnElmtId(n8);
    }
    aboutToBeDeleted() {
        this.__multiStack.aboutToBeDeleted();
        this.__isPortrait.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get multiStack() {
        return this.__multiStack.get();
    }
    set multiStack(m8) {
        this.__multiStack.set(m8);
    }
    get isPortrait() {
        return this.__isPortrait.get();
    }
    set isPortrait(l8) {
        this.__isPortrait.set(l8);
    }
    MultiNavDestination(c8, d8, e8 = null) {
        this.observeComponentCreation2((f8, g8) => {
            If.create();
            if (c8 === 'SubNavigation') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((h8, i8) => {
                            if (i8) {
                                let j8 = new SubNavigation(this, {
                                    isPortrait: this.__isPortrait,
                                    multiStack: this.multiStack,
                                    navDestination: this.navDestination,
                                    primaryStack: d8.primaryStack,
                                    secondaryStack: d8.secondaryStack,
                                    needRenderIsFullScreen: d8.needRenderIsFullScreen,
                                    needRenderLeftClickCount: this.multiStack.needRenderLeftClickCount,
                                    navWidthRangeModifier: this.multiStack.navWidthRangeModifier,
                                    onNavigationModeChange: this?.callback,
                                    needRenderDisplayMode: this.multiStack.needRenderDisplayMode,
                                }, undefined, h8, () => { }, { page: "MultiNavigation/src/main/ets/components/MultiNavigation.ets", line: 333, col: 7 });
                                ViewPU.create(j8);
                                let k8 = () => {
                                    return {
                                        isPortrait: this.isPortrait,
                                        multiStack: this.multiStack,
                                        navDestination: this.navDestination,
                                        primaryStack: d8.primaryStack,
                                        secondaryStack: d8.secondaryStack,
                                        needRenderIsFullScreen: d8.needRenderIsFullScreen,
                                        needRenderLeftClickCount: this.multiStack.needRenderLeftClickCount,
                                        navWidthRangeModifier: this.multiStack.navWidthRangeModifier,
                                        onNavigationModeChange: this?.callback,
                                        needRenderDisplayMode: this.multiStack.needRenderDisplayMode
                                    };
                                };
                                j8.paramsGenerator_ = k8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(h8, {
                                    multiStack: this.multiStack,
                                    needRenderIsFullScreen: d8.needRenderIsFullScreen,
                                    needRenderLeftClickCount: this.multiStack.needRenderLeftClickCount,
                                    navWidthRangeModifier: this.multiStack.navWidthRangeModifier,
                                    needRenderDisplayMode: this.multiStack.needRenderDisplayMode
                                });
                            }
                        }, { name: "SubNavigation" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.navDestination.bind(this)(c8, d8);
                });
            }
        }, If);
        If.pop();
    }
    callback(b8) {
        if (that.onNavigationModeChangeCallback !== undefined) {
            if (b8 !== that.mode || that.mode === undefined) {
                that?.onNavigationModeChangeCallback(b8);
            }
            that.mode = b8;
        }
    }
    aboutToAppear() {
        that = this;
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavigation aboutToAppear');
        try {
            display.on('foldStatusChange', this.foldStatusCallback);
        }
        catch (a8) {
            console.error('Failed to register callback. Code: ' + JSON.stringify(a8));
        }
        DeviceListenerManager.getInstance().registerOrientationLister((z7) => {
            hilog.info(0x0000, 'MultiNavigation', 'MultiNavigation orientation change ' + z7);
            this.isPortrait = z7;
            this.multiStack.isPortrait = z7;
            this.multiStack.handleRefreshPlaceHolderIfNeeded();
        });
        DeviceListenerManager.getInstance().registerDrawableWidthLister((y7) => {
            hilog.debug(0x0000, 'MultiNavigation', 'MultiNavigation Drawable width change ' + y7);
            this.multiStack.isLarge = y7;
            this.multiStack.handleRefreshPlaceHolderIfNeeded();
        });
        try {
            this.multiStack.needRenderDisplayMode.displayMode = display.getFoldStatus();
        } catch (err) {
            hilog.warn(0x0000, 'MultiNavigation', 'Failed to get fold status. error:' + JSON.stringify(err));
        }
        DeviceListenerManager.getInstance().initListener();
        this.multiStack.registerHomeChangeListener({
            onHomeShowOnTop: (x7) => {
                this.onHomeShowOnTop?.(x7);
            },
        });
    }
    aboutToDisappear() {
        try {
            display.off('foldStatusChange');
        }
        catch (w7) {
            console.error('Failed to unregister callback. Code: ' + JSON.stringify(w7));
        }
        DeviceListenerManager.getInstance().unregisterOrientationLister();
        DeviceListenerManager.getInstance().unregisterDrawableWidthLister();
        DeviceListenerManager.getInstance().finalizeListener();
        this.multiStack.unregisterHomeChangeListener();
    }
    initialRender() {
        this.observeComponentCreation2((u7, v7) => {
            Navigation.create(this.multiStack.outerStack, { moduleName: "MultiNavigation", pagePath: "", isUserCreateStack: true });
            Navigation.mode(NavigationMode.Stack);
            Navigation.navDestination({ builder: this.MultiNavDestination.bind(this) });
            Navigation.hideBackButton(true);
            Navigation.hideTitleBar(true);
            Navigation.hideToolBar(true);
            Navigation.hideNavBar(true);
        }, Navigation);
        Navigation.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
let MultiNavPathStack = class MultiNavPathStack extends NavPathStack {
    constructor() {
        super();
        this.outerStack = new MyNavPathStack();
        this.totalStack = [];
        this.subStackList = new Array();
        this.needRenderLeftClickCount = new NeedRenderLeftClickCount();
        this.needRenderDisplayMode = new NeedRenderDisplayMode();
        this.disableAllAnimation = false;
        this.mPolicyMap = new Map();
        this.navWidthRangeModifier = new NavWidthRangeAttrModifier();
        this.homeWidthPercents = [50, 50];
        this.keepBottomPageFlag = false;
        this.homeChangeListener = undefined;
        this.placeHolderPolicyInfo = undefined;
        this.isPortrait = false;
        this.isLarge = false;
        this.navPathStackOperate = {
            onPrimaryPop: () => {
                hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack onPrimaryPop');
                this.totalStack.pop();
                this.subStackList.pop();
                this.outerStack.popInner(false);
            },
            onSecondaryPop: () => {
                hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack onSecondaryPop');
                this.totalStack.pop();
                this.checkAndNotifyHomeChange();
            }
        };
        this.outerStackOperate = {
            onSystemPop: () => {
                hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack onOuterPop');
                this.totalStack.pop();
                this.subStackList.pop();
                this.checkAndNotifyHomeChange();
            }
        };
        this.outerStack.registerStackOperateCallback(this.outerStackOperate);
    }
    pushPath(l7, m7, n7) {
        hilog.info(0x0000, 'MultiNavigation', 'pushPath policy = ' + n7 + ', info.name = ' + l7.name);
        let o7 = true;
        if (m7 !== undefined) {
            if (typeof m7 === 'boolean') {
                o7 = m7;
            }
            else if (m7.animated !== undefined) {
                o7 = m7.animated;
            }
            else {
            }
        }
        n7 = (n7 === undefined) ? SplitPolicy.DETAIL_PAGE : n7;
        const p7 = this.subStackList.length;
        const q7 = new MultiNavPolicyInfo(n7, l7);
        hilog.info(0x0000, 'MultiNavigation', 'pushPath subStackLength = ' + p7);
        if (p7 > 0) {
            hilog.info(0x0000, 'MultiNavigation', 'pushPath currentTopPrimaryPolicy = ' +
                this.subStackList[p7 - 1].getPrimaryPolicy());
        }
        if (n7 === SplitPolicy.DETAIL_PAGE && p7 > 0 &&
            this.subStackList[p7 - 1].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
            let s7 = this.subStackList[p7 - 1].getSecondaryInfoList().length;
            hilog.info(0x0000, 'MultiNavigation', 'pushPath detailSize = ' + s7);
            if (s7 === 0) {
                this.subStackList[p7 - 1].pushSecondaryPath(q7, o7);
            }
            else {
                if (this.needRenderLeftClickCount.leftClickCount > 0) {
                    if (this.placeHolderPolicyInfo === undefined) {
                        this.subStackList[p7 - 1].clearSecondary(false);
                        this.totalStack.splice(this.totalStack.length - s7);
                        this.subStackList[p7 - 1].pushSecondaryPath(q7, false);
                    }
                    else {
                        const t7 = this.subStackList[p7 - 1].getSecondaryInfoList()[0].policy;
                        if (t7 === SplitPolicy.PlACE_HOLDER_PAGE) {
                            if (s7 === 1) {
                                this.subStackList[p7 - 1].pushSecondaryPath(q7, o7);
                            }
                            else {
                                this.subStackList[p7 - 1].clearSecondaryKeepPlaceHolder(false);
                                this.totalStack.splice(this.totalStack.length - s7 + 1);
                                this.subStackList[p7 - 1].pushSecondaryPath(q7, false);
                            }
                        }
                        else {
                            this.subStackList[p7 - 1].clearSecondary(false);
                            this.totalStack.splice(this.totalStack.length - s7);
                            this.subStackList[p7 - 1].pushSecondaryPath(q7, false);
                        }
                    }
                }
                else {
                    this.subStackList[p7 - 1].pushSecondaryPath(q7, o7);
                }
            }
        }
        else {
            let r7 = new SubNavigationStack();
            r7.registerMultiStackOperateCallback(this.navPathStackOperate);
            r7.disableAnimation(this.disableAllAnimation);
            r7.pushPrimaryPath(q7, false);
            this.subStackList.push(r7);
            this.outerStack.pushPath({ name: 'SubNavigation', param: r7 }, o7);
        }
        this.totalStack.push(q7);
        if (n7 === SplitPolicy.HOME_PAGE && this.placeHolderPolicyInfo !== undefined &&
            this.needShowPlaceHolder()) {
            this.pushPlaceHolder(p7);
        }
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pushPath policy = ' + n7 +
            ' stackSize = ' + this.totalStack.length +
            ' this.leftClickCount = ' + this.needRenderLeftClickCount.leftClickCount);
        this.needRenderLeftClickCount.leftClickCount = 0;
    }
    pushPathByName(g7, h7, i7, j7, k7) {
        if (i7 !== undefined && typeof i7 !== 'boolean') {
            this.pushPath({ name: g7, param: h7, onPop: i7 }, j7, k7);
            return;
        }
        if (typeof i7 === 'boolean') {
            this.pushPath({ name: g7, param: h7 }, i7, j7);
            return;
        }
        if (j7 !== undefined && typeof j7 !== 'boolean') {
            this.pushPath({ name: g7, param: h7 }, undefined, j7);
            return;
        }
        if (typeof j7 === 'boolean') {
            this.pushPath({ name: g7, param: h7 }, j7, k7);
            return;
        }
        this.pushPath({ name: g7, param: h7 }, undefined, k7);
    }
    pushDestination(c7, d7, e7) {
        hilog.error(0x0000, 'MultiNavigation', 'pushDestination is not support');
        let f7 = Promise.reject({ message: 'not support' });
        return f7;
    }
    pushDestinationByName(w6, x6, y6, z6, a7) {
        hilog.error(0x0000, 'MultiNavigation', 'pushDestinationByName is not support');
        let b7 = Promise.reject({ message: 'not support' });
        return b7;
    }
    replacePath(p6, q6) {
        let r6 = true;
        if (q6 !== undefined) {
            if (typeof q6 === 'boolean') {
                r6 = q6;
            }
            else if (q6.animated !== undefined) {
                r6 = q6.animated;
            }
            else {
            }
        }
        let s6 = this.totalStack.length;
        let t6 = this.subStackList.length;
        if (s6 < 1 || t6 < 1) {
            hilog.error(0x0000, 'MultiNavigation', 'replacePath fail stack is empty');
            return;
        }
        let u6 = this.totalStack[s6 - 1].policy;
        if (u6 === SplitPolicy.PlACE_HOLDER_PAGE) {
            hilog.warn(0x0000, 'MultiNavigation', 'replacePath fail, not support replace placeHolder');
            return;
        }
        const v6 = new MultiNavPolicyInfo(u6, p6);
        this.subStackList[t6 - 1].replacePath(v6, r6);
        this.totalStack.pop();
        this.totalStack.push(v6);
    }
    replacePathByName(m6, n6, o6) {
        this.replacePath({ name: m6, param: n6 }, o6);
    }
    removeByIndexes(x5) {
        let y5 = x5.length;
        hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes indexesLength=' + y5);
        if (y5 <= 0) {
            return 0;
        }
        let z5 = this.totalStack.length;
        hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes oriStackSize=' + z5);
        x5.sort((k6, l6) => k6 - l6);
        let a6 = 0;
        let b6 = 0;
        let c6 = [];
        hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes this.subStackList.length=' + this.subStackList.length +
            ', oriStackSize=' + z5);
        this.subStackList.forEach((g6, h6) => {
            let i6 = b6;
            b6 += g6.getAllInfoLength();
            const j6 = [];
            for (; a6 < x5.length;) {
                if (x5[a6] < b6) {
                    j6.push(x5[a6] - i6);
                    a6++;
                }
                else {
                    break;
                }
            }
            g6.removeByIndexes(j6);
            if (!g6.hasPrimaryInfo()) {
                c6.push(h6);
            }
        });
        hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes outerIndexes.length=' + c6.length);
        this.outerStack.removeByIndexes(c6);
        this.subStackList = this.subStackList.filter((f6) => {
            return f6.hasPrimaryInfo();
        });
        this.totalStack = [];
        this.subStackList.forEach((e6) => {
            this.totalStack.push(...e6.getPrimaryInfoList());
            this.totalStack.push(...e6.getSecondaryInfoList());
        });
        this.handleRefreshPlaceHolderIfNeeded();
        this.checkAndNotifyHomeChange();
        let d6 = z5 - this.totalStack.length;
        hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes size=' + d6);
        return d6;
    }
    removeByName(p5) {
        let q5 = this.totalStack.length;
        hilog.info(0x0000, 'MultiNavigation', 'removeByName name=' + p5 + ', oriStackSize=' + q5);
        let r5 = [];
        this.subStackList.forEach((v5, w5) => {
            v5.removeByName(p5);
            if (!v5.hasPrimaryInfo()) {
                r5.push(w5);
            }
        });
        this.outerStack.removeByIndexes(r5);
        hilog.info(0x0000, 'MultiNavigation', 'removeByName outerIndexes.length=' + r5.length);
        this.subStackList = this.subStackList.filter((u5) => {
            return u5.hasPrimaryInfo();
        });
        this.totalStack = [];
        this.subStackList.forEach((t5) => {
            this.totalStack.push(...t5.getPrimaryInfoList());
            this.totalStack.push(...t5.getSecondaryInfoList());
        });
        this.handleRefreshPlaceHolderIfNeeded();
        this.checkAndNotifyHomeChange();
        let s5 = q5 - this.totalStack.length;
        hilog.info(0x0000, 'MultiNavigation', 'removeByName size=' + s5);
        return s5;
    }
    pop(f5, g5) {
        let h5 = this.totalStack.length;
        let i5 = this.subStackList.length;
        if (h5 < 1 || i5 < 1) {
            hilog.error(0x0000, 'MultiNavigation', 'MultiNavPathStack pop fail stack is empty!');
            return undefined;
        }
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop totalSize=' + h5 +
            ', subStackLength' + i5);
        if (this.keepBottomPageFlag && (h5 === 1 ||
            (this.placeHolderPolicyInfo !== undefined && h5 === 2 &&
                this.totalStack[1].policy === SplitPolicy.PlACE_HOLDER_PAGE))) {
            hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop fail for keep bottom');
            return undefined;
        }
        let j5 = this.totalStack[h5 - 1].navInfo;
        let k5 = this.subStackList[i5 - 1].getAllInfoLength();
        if (k5 < 1) {
            hilog.error(0x0000, 'MultiNavigation', 'MultiNavPathStack pop fail sub stack is empty');
            return undefined;
        }
        let l5 = undefined;
        if (k5 > 1) {
            l5 = this.subStackList[i5 - 1].getSecondaryInfoList()[0].policy;
        }
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop allInfoLength=' + k5 +
            ', secondaryStackFirstPolice' + l5);
        this.totalStack.pop();
        if (k5 === 1) {
            this.outerStack.popInner(g5);
            let o5 = this.subStackList.pop();
            setTimeout(() => {
                o5?.pop(false);
                o5 = undefined;
            }, 300);
        }
        else {
            if (k5 === 2) {
                if (this.placeHolderPolicyInfo !== undefined) {
                    if (l5 === SplitPolicy.PlACE_HOLDER_PAGE) {
                        this.outerStack.popInner(g5);
                        let n5 = this.subStackList.pop();
                        setTimeout(() => {
                            n5?.clear(false);
                            n5 = undefined;
                        }, 300);
                        j5 = this.totalStack.pop()?.navInfo;
                    }
                    else {
                        if (this.needShowPlaceHolder()) {
                            this.subStackList[i5 - 1].pop(g5);
                            this.pushPlaceHolder(i5 - 1);
                        }
                        else {
                            this.subStackList[i5 - 1].pop(g5);
                        }
                    }
                }
                else {
                    this.subStackList[i5 - 1].pop(g5);
                }
            }
            else {
                this.subStackList[i5 - 1].pop(g5);
            }
        }
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop currentPath.name = ' + j5?.name);
        if (f5 !== undefined && typeof f5 !== 'boolean' &&
            j5 !== undefined && j5.onPop !== undefined) {
            let m5 = {
                info: j5,
                result: f5,
            };
            j5.onPop(m5);
        }
        this.handleRefreshPlaceHolderIfNeeded();
        this.checkAndNotifyHomeChange();
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop stackSize = ' + this.totalStack.length);
        return j5;
    }
    popToName(r4, s4, t4) {
        let u4 = this.totalStack.findIndex((e5) => {
            return e5.navInfo?.name === r4;
        });
        let v4 = this.totalStack.length;
        let w4 = this.subStackList.length;
        if (v4 < 1 || w4 < 1) {
            hilog.error(0x0000, 'MultiNavigation', 'popToName fail stack is empty!');
            return -1;
        }
        if (u4 !== -1) {
            let x4 = this.totalStack[v4 - 1].navInfo;
            let y4 = [];
            this.subStackList.forEach((c5, d5) => {
                y4.push(this.subStackList[d5].secondaryStack.size());
            });
            let z4 = 0;
            for (let b5 = 0; b5 < w4; b5++) {
                z4++;
                if (u4 === z4 - 1) {
                    this.subStackList[b5]?.secondaryStack.clear();
                    this.subStackList[b5].secondaryStack.policyInfoList.splice(0);
                    this.totalStack.splice(u4 + 1);
                    this.clearTrashStack(b5 + 1, s4, t4);
                    break;
                }
                else if (u4 > z4 - 1 && u4 < z4 + y4[b5]) {
                    this.subStackList[b5].secondaryStack.popToIndex(u4 - z4);
                    this.subStackList[b5].secondaryStack.policyInfoList.splice(u4 - z4 + 1);
                    this.totalStack.splice(u4 + 1);
                    this.clearTrashStack(b5 + 1, s4, t4);
                }
                z4 += y4[b5];
            }
            if (s4 !== undefined && typeof s4 !== 'boolean' &&
                x4 !== undefined && x4.onPop !== undefined) {
                let a5 = {
                    info: x4,
                    result: s4,
                };
                x4.onPop(a5);
            }
        }
        this.handleRefreshPlaceHolderIfNeeded();
        this.checkAndNotifyHomeChange();
        return u4;
    }
    popToIndex(f4, g4, h4) {
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex index = ' + f4);
        if (f4 > this.totalStack.length || f4 < 0) {
            hilog.error(0x0000, 'MultiNavigation', 'popToIndex fail wrong index');
            return;
        }
        let i4 = this.totalStack.length;
        let j4 = this.subStackList.length;
        if (i4 < 1 || j4 < 1) {
            hilog.error(0x0000, 'MultiNavigation', 'popToIndex fail stack is empty!');
            return;
        }
        let k4 = this.totalStack[i4 - 1].navInfo;
        let l4 = [];
        this.subStackList.forEach((p4, q4) => {
            l4.push(this.subStackList[q4].secondaryStack.size());
        });
        let m4 = 0;
        for (let o4 = 0; o4 < j4; o4++) {
            m4++;
            if (f4 === m4 - 1) {
                hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex home' + o4);
                this.subStackList[o4]?.secondaryStack.clear();
                this.subStackList[o4].secondaryStack.policyInfoList.splice(0);
                this.totalStack.splice(f4 + 1);
                this.clearTrashStack(o4 + 1, g4, h4);
                hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex totalStack=' + this.totalStack.length);
                break;
            }
            else if (f4 > m4 - 1 && f4 < m4 + l4[o4]) {
                this.subStackList[o4].secondaryStack.popToIndex(f4 - m4);
                this.subStackList[o4].secondaryStack.policyInfoList.splice(f4 - m4 + 1);
                this.totalStack.splice(f4 + 1);
                this.clearTrashStack(o4 + 1, g4, h4);
            }
            m4 += l4[o4];
        }
        if (g4 !== undefined && typeof g4 !== 'boolean' &&
            k4 !== undefined && k4.onPop !== undefined) {
            let n4 = {
                info: k4,
                result: g4,
            };
            k4.onPop(n4);
        }
        this.handleRefreshPlaceHolderIfNeeded();
        this.checkAndNotifyHomeChange();
    }
    clearTrashStack(b4, c4, d4) {
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex clearTrashStack' + b4);
        for (let e4 = b4; e4 < this.subStackList.length; e4++) {
            hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex subStackList' + b4);
            this.subStackList[e4].primaryStack.clear();
            this.subStackList[e4].secondaryStack.clear();
            this.subStackList[e4].primaryStack.policyInfoList.splice(0);
            this.subStackList[e4].secondaryStack.policyInfoList.splice(0);
        }
        this.subStackList.splice(b4);
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex subStackList.length=' + this.subStackList.length);
        this.outerStack.popToIndex(b4 - 1, c4, d4);
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex outerStack.size=' + this.outerStack.size());
    }
    moveToTop(x3, y3) {
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack moveToTop name=' + x3);
        let z3 = this.totalStack.findIndex((a4) => {
            return a4.navInfo?.name === x3;
        });
        if (z3 !== -1) {
            this.moveIndexToTop(z3, y3);
        }
        return z3;
    }
    moveIndexToTop(m3, n3) {
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack moveIndexToTop index=' + m3);
        if (m3 < 0 || m3 > this.totalStack.length) {
            hilog.error(0x0000, 'MultiNavigation', 'MultiNavPathStack moveIndexToTop wrong index');
            return;
        }
        let o3 = this.subStackList.length;
        let p3 = 0;
        let q3 = -1;
        for (let t3 = 0; t3 < o3; t3++) {
            let u3 = p3;
            p3 += this.subStackList[t3].getAllInfoLength();
            if (m3 < p3) {
                q3 = t3;
                if (this.subStackList[t3].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
                    let v3 = m3 - u3;
                    if (v3 !== 0) {
                        this.subStackList[t3].secondaryStack.moveIndexToTop(v3 - 1, n3);
                        const w3 = this.subStackList[t3].secondaryStack.policyInfoList.splice(v3 - 1, 1);
                        this.subStackList[t3].secondaryStack.policyInfoList.push(...w3);
                    }
                }
                break;
            }
        }
        if (q3 !== -1) {
            let s3 = this.subStackList.splice(q3, 1);
            this.subStackList.push(...s3);
            this.outerStack.moveIndexToTop(q3, n3);
        }
        this.totalStack = [];
        this.subStackList.forEach((r3) => {
            this.totalStack.push(...r3.getPrimaryInfoList());
            this.totalStack.push(...r3.getSecondaryInfoList());
        });
        this.handleRefreshPlaceHolderIfNeeded();
        this.checkAndNotifyHomeChange();
    }
    clear(i3) {
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack clear animated = ' + i3 + ', keepBottomPageFlag=' +
            this.keepBottomPageFlag);
        if (this.subStackList.length === 0 || this.totalStack.length === 0) {
            hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack clear return size is 0');
            return;
        }
        if (this.keepBottomPageFlag) {
            let k3 = this.subStackList.length;
            for (let l3 = 1; l3 < k3; l3++) {
                this.subStackList[l3].clear(i3);
            }
            this.outerStack.popToIndex(0, i3);
            this.subStackList.splice(1);
            if (this.placeHolderPolicyInfo !== undefined) {
                if (this.subStackList[0].getSecondaryInfoList().length > 1 &&
                    this.subStackList[0].secondaryStack.policyInfoList[0].policy === SplitPolicy.PlACE_HOLDER_PAGE) {
                    this.subStackList[0].clearSecondaryKeepPlaceHolder(i3);
                    this.totalStack.splice(2);
                }
                else {
                    this.subStackList[0].clearSecondary(i3);
                    this.totalStack.splice(1);
                    if (this.needShowPlaceHolder()) {
                        this.subStackList[0].pushSecondaryPath(this.placeHolderPolicyInfo, i3);
                        this.totalStack.push(this.placeHolderPolicyInfo);
                    }
                }
            }
            else {
                this.subStackList[0].clearSecondary(i3);
                this.totalStack.splice(1);
            }
            this.checkAndNotifyHomeChange();
            return;
        }
        this.subStackList.forEach((j3) => {
            j3.clear(i3);
        });
        this.outerStack.clear(i3);
        this.subStackList.splice(0);
        this.totalStack.splice(0);
    }
    getAllPathName() {
        let g3 = [];
        this.totalStack.forEach((h3) => {
            if (h3.navInfo !== undefined) {
                g3.push(h3.navInfo.name);
            }
        });
        return g3;
    }
    getParamByIndex(e3) {
        let f3 = undefined;
        if (e3 >= 0 && e3 < this.totalStack.length) {
            f3 = this.totalStack[e3].navInfo?.param;
        }
        return f3;
    }
    getParamByName(b3) {
        let c3 = [];
        this.totalStack.forEach((d3) => {
            if (d3.navInfo !== undefined && d3.navInfo.name == b3) {
                c3.push(d3.navInfo.param);
            }
        });
        return c3;
    }
    getIndexByName(y2) {
        let z2 = [];
        for (let a3 = 0; a3 < this.totalStack.length; a3++) {
            if (this.totalStack[a3].navInfo?.name === y2) {
                z2.push(a3);
            }
        }
        return z2;
    }
    getParent() {
        hilog.error(0x0000, 'MultiNavigation', 'getParent is not support!');
        throw new Error('getParent is not support in multi navigation');
    }
    size() {
        return this.totalStack.length;
    }
    disableAnimation(w2) {
        for (const x2 of this.subStackList) {
            x2.disableAnimation(w2);
        }
        this.outerStack.disableAnimation(w2);
        this.disableAllAnimation = w2;
    }
    setInterception(v2) {
        hilog.error(0x0000, 'MultiNavigation', 'setInterception is not support!');
        throw new Error('setInterception is not support in multi navigation');
    }
    setPagePolicy(u2) {
        this.mPolicyMap = u2;
    }
    switchFullScreenState(r2) {
        let s2 = this.totalStack.length;
        let t2 = this.subStackList.length;
        if (t2 < 1 || s2 < 1) {
            return false;
        }
        if (this.subStackList[t2 - 1].getPrimaryPolicy() !== SplitPolicy.HOME_PAGE) {
            return false;
        }
        if (this.totalStack[s2 - 1].policy === SplitPolicy.PlACE_HOLDER_PAGE) {
            return false;
        }
        if (this.totalStack[s2 - 1].isFullScreen === r2) {
            hilog.info(0x0000, 'MultiNavigation', 'switchFullScreen is same:' + r2);
            return true;
        }
        hilog.info(0x0000, 'MultiNavigation', 'switchFullScreen name=' +
            this.totalStack[s2 - 1].navInfo?.name +
            ', from ' + this.totalStack[s2 - 1].isFullScreen + ' to ' + r2);
        this.totalStack[s2 - 1].isFullScreen = r2;
        this.subStackList[t2 - 1].refreshFullScreen();
        return true;
    }
    setHomeWidthRange(p2, q2) {
        if (!this.checkInputPercent(p2) || !this.checkInputPercent(q2)) {
            hilog.error(0x0000, 'MultiNavigation', 'setHomeWidthRange failed, wrong param:' +
                ', ' + p2 + ', ' + q2);
            return;
        }
        this.homeWidthPercents = [p2, q2];
        this.refreshHomeWidth();
    }
    keepBottomPage(o2) {
        this.keepBottomPageFlag = o2;
    }
    registerHomeChangeListener(n2) {
        if (this.homeChangeListener === undefined) {
            this.homeChangeListener = n2;
        }
    }
    unregisterHomeChangeListener() {
        this.homeChangeListener = undefined;
    }
    setPlaceholderPage(m2) {
        this.placeHolderPolicyInfo = new MultiNavPolicyInfo(SplitPolicy.PlACE_HOLDER_PAGE, m2);
    }
    handleRefreshPlaceHolderIfNeeded() {
        if (this.placeHolderPolicyInfo === undefined) {
            return;
        }
        const i2 = this.subStackList.length;
        if (i2 < 1) {
            return;
        }
        const j2 = this.subStackList[i2 - 1].getPrimaryPolicy();
        if (j2 !== SplitPolicy.HOME_PAGE) {
            return;
        }
        const k2 = this.subStackList[i2 - 1].getAllInfoLength();
        let l2 = undefined;
        if (k2 > 1) {
            l2 = this.subStackList[i2 - 1].getSecondaryInfoList()[0].policy;
        }
        if (this.needShowPlaceHolder()) {
            if (k2 === 1) {
                this.pushPlaceHolder(i2 - 1);
            }
        }
        else {
            if (l2 === SplitPolicy.PlACE_HOLDER_PAGE) {
                if (k2 === 2) {
                    this.popPlaceHolder(i2 - 1);
                }
                else {
                    this.removeFirstPlaceHolder(i2 - 1);
                }
            }
        }
    }
    removeFirstPlaceHolder(g2) {
        this.subStackList[g2].removeByIndexes([1]);
        this.totalStack = [];
        this.subStackList.forEach((h2) => {
            this.totalStack.push(...h2.getPrimaryInfoList());
            this.totalStack.push(...h2.getSecondaryInfoList());
        });
    }
    pushPlaceHolder(f2) {
        this.subStackList[f2].pushSecondaryPath(this.placeHolderPolicyInfo, false);
        this.totalStack.push(this.placeHolderPolicyInfo);
    }
    popPlaceHolder(e2) {
        this.subStackList[e2].pop(false);
        this.totalStack.pop();
        this.checkAndNotifyHomeChange();
    }
    needShowPlaceHolder() {
        if (!this.isLarge) {
            hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for drawable width is less then breakpoint');
            return false;
        }
        if (DeviceHelper.isStraightProduct()) {
            hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for straight product');
            return false;
        }
        if (DeviceHelper.isPhone() && DeviceHelper.isFold() &&
            this.needRenderDisplayMode.displayMode === display.FoldStatus.FOLD_STATUS_FOLDED) {
            hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for fold status');
            return false;
        }
        if (DeviceHelper.isTablet() && this.isPortrait) {
            hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for portrait tablet');
            return false;
        }
        return true;
    }
    checkAndNotifyHomeChange() {
        if (this.totalStack.length === 0) {
            return;
        }
        let c2 = this.totalStack[this.totalStack.length - 1];
        if (c2 === undefined) {
            return;
        }
        if (c2.policy === SplitPolicy.HOME_PAGE && c2.navInfo !== undefined) {
            this.homeChangeListener && this.homeChangeListener.onHomeShowOnTop(c2.navInfo.name);
        }
        if (this.totalStack.length <= 1) {
            return;
        }
        let d2 = this.totalStack[this.totalStack.length - 2];
        if (d2 === undefined) {
            return;
        }
        if (c2.policy === SplitPolicy.PlACE_HOLDER_PAGE &&
            d2.policy === SplitPolicy.HOME_PAGE && d2.navInfo !== undefined) {
            this.homeChangeListener && this.homeChangeListener.onHomeShowOnTop(d2.navInfo.name);
        }
    }
    refreshHomeWidth() {
        this.navWidthRangeModifier.minHomeWidth = `${this.homeWidthPercents[0]}%`;
        this.navWidthRangeModifier.maxHomeWidth = `${this.homeWidthPercents[1]}%`;
        this.navWidthRangeModifier.isApplicationSet = true;
    }
    checkInputPercent(b2) {
        return (0 <= b2 && b2 <= 100);
    }
};
MultiNavPathStack = __decorate([
    Observed
], MultiNavPathStack);
export { MultiNavPathStack };
let NeedRenderIsFullScreen = class NeedRenderIsFullScreen {
    constructor() {
        this.isFullScreen = undefined;
    }
};
NeedRenderIsFullScreen = __decorate([
    Observed
], NeedRenderIsFullScreen);
export { NeedRenderIsFullScreen };
let NeedRenderLeftClickCount = class NeedRenderLeftClickCount {
    constructor() {
        this.leftClickCount = 0;
    }
};
NeedRenderLeftClickCount = __decorate([
    Observed
], NeedRenderLeftClickCount);
export { NeedRenderLeftClickCount };
let NeedRenderDisplayMode = class NeedRenderDisplayMode {
    constructor() {
        this.displayMode = 0;
    }
};
NeedRenderDisplayMode = __decorate([
    Observed
], NeedRenderDisplayMode);
export { NeedRenderDisplayMode };
class MultiNavPolicyInfo {
    constructor(z1, a2) {
        this.policy = SplitPolicy.DETAIL_PAGE;
        this.navInfo = undefined;
        this.isFullScreen = undefined;
        this.policy = z1;
        this.navInfo = a2;
    }
}
export class MyNavPathStack extends NavPathStack {
    constructor() {
        super(...arguments);
        this.operates = [];
        this.type = 'NavPathStack';
        this.policyInfoList = [];
    }
    registerStackOperateCallback(w1) {
        let x1 = this.operates.findIndex((y1) => { return y1 === w1; });
        if (x1 === -1) {
            this.operates.push(w1);
        }
    }
    unregisterStackOperateCallback(t1) {
        let u1 = this.operates.findIndex((v1) => { return v1 === t1; });
        if (u1 !== -1) {
            this.operates.splice(u1, 1);
        }
    }
    popInner(r1, s1) {
        hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack pop from inner:');
        return super.pop(r1, s1);
    }
    pop(n1, o1) {
        hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack pop from system:');
        let p1 = undefined;
        if (typeof o1 === 'boolean') {
            p1 = super.pop(o1);
        }
        else {
            p1 = super.pop(n1, o1);
        }
        this.policyInfoList.pop();
        this.operates.forEach((q1) => {
            q1.onSystemPop?.();
        });
        return p1;
    }
}
class SubNavigationStack {
    constructor() {
        this.primaryStack = new MyNavPathStack();
        this.secondaryStack = new MyNavPathStack();
        this.needRenderIsFullScreen = new NeedRenderIsFullScreen();
        this.multiOperates = [];
        this.primaryNavPathStackOperate = {
            onSystemPop: () => {
                this.multiOperates.forEach((m1) => {
                    m1.onPrimaryPop?.();
                });
            }
        };
        this.secondaryNavPathStackOperate = {
            onSystemPop: () => {
                this.multiOperates.forEach((l1) => {
                    l1.onSecondaryPop?.();
                });
                this.refreshFullScreen();
            }
        };
        this.primaryStack.registerStackOperateCallback(this.primaryNavPathStackOperate);
        this.secondaryStack.registerStackOperateCallback(this.secondaryNavPathStackOperate);
    }
    registerMultiStackOperateCallback(i1) {
        let j1 = this.multiOperates.findIndex((k1) => { return k1 === i1; });
        if (j1 === -1) {
            this.multiOperates.push(i1);
        }
    }
    unregisterMultiStackOperateCallback(f1) {
        let g1 = this.multiOperates.findIndex((h1) => { return h1 === f1; });
        if (g1 !== -1) {
            this.multiOperates.splice(g1, 1);
        }
    }
    getPrimaryPolicy() {
        if (this.primaryStack.policyInfoList.length < 1) {
            return undefined;
        }
        return this.primaryStack.policyInfoList[0].policy;
    }
    getPrimaryInfoList() {
        return this.primaryStack.policyInfoList.slice();
    }
    getSecondaryInfoList() {
        return this.secondaryStack.policyInfoList.slice();
    }
    getAllInfoLength() {
        return this.primaryStack.size() + this.secondaryStack.size();
    }
    hasPrimaryInfo() {
        return this.primaryStack.size() !== 0;
    }
    hasSecondaryInfo() {
        return this.secondaryStack.size() !== 0;
    }
    pushPrimaryPath(d1, e1) {
        this.primaryStack.policyInfoList.push(d1);
        this.primaryStack.pushPath(d1.navInfo, e1);
        this.refreshFullScreen();
    }
    pushSecondaryPath(b1, c1) {
        this.secondaryStack.policyInfoList.push(b1);
        this.secondaryStack.pushPath(b1.navInfo, c1);
        this.refreshFullScreen();
    }
    removeByIndexes(w) {
        if (w.length < 1) {
            return;
        }
        if (w[0] === 0) {
            hilog.info(0x0000, 'MultiNavigation', 'SubNavigationStack removeByIndexes primaryStack');
            this.primaryStack.removeByIndexes([0]);
            this.primaryStack.policyInfoList.pop();
            this.clear(false);
            return;
        }
        if (w.length !== 0) {
            let x = [];
            w.forEach((a1) => {
                x.push(a1 - 1);
            });
            this.secondaryStack.removeByIndexes(x);
            this.secondaryStack.policyInfoList = this.secondaryStack.policyInfoList.filter((y, z) => {
                return y && !x.includes(z);
            });
        }
        this.refreshFullScreen();
    }
    removeByName(t) {
        this.primaryStack.removeByName(t);
        this.primaryStack.policyInfoList = this.primaryStack.policyInfoList.filter((v) => {
            return v.navInfo?.name !== t;
        });
        if (!this.hasPrimaryInfo()) {
            this.clear(false);
            return;
        }
        this.secondaryStack.removeByName(t);
        this.secondaryStack.policyInfoList = this.secondaryStack.policyInfoList.filter((u) => {
            return u.navInfo?.name !== t;
        });
        this.refreshFullScreen();
    }
    pop(q, r) {
        let s = undefined;
        if (this.secondaryStack.policyInfoList.length > 0) {
            s = this.popSecondary(q, r);
        }
        else {
            s = this.popPrimary(q, r);
        }
        this.refreshFullScreen();
        return s;
    }
    clearSecondary(p) {
        this.secondaryStack.clear(p);
        this.secondaryStack.policyInfoList.splice(0);
        this.refreshFullScreen();
    }
    clearSecondaryKeepPlaceHolder(o) {
        this.secondaryStack.popToIndex(0, o);
        this.secondaryStack.policyInfoList.splice(1);
        this.refreshFullScreen();
    }
    clear(n) {
        this.secondaryStack.clear(n);
        this.primaryStack.clear(n);
        this.secondaryStack.policyInfoList.splice(0);
        this.primaryStack.policyInfoList.splice(0);
    }
    disableAnimation(m) {
        this.primaryStack.disableAnimation(m);
        this.secondaryStack.disableAnimation(m);
    }
    replacePath(k, l) {
        if (this.secondaryStack.policyInfoList.length > 0) {
            this.replaceSecond(k, l);
        }
        else {
            this.replacePrimary(k, l);
        }
        this.refreshFullScreen();
    }
    refreshFullScreen() {
        let i = this.secondaryStack.policyInfoList.length;
        if (i > 0) {
            this.needRenderIsFullScreen.isFullScreen = this.secondaryStack.policyInfoList[i - 1].isFullScreen;
            return;
        }
        let j = this.primaryStack.policyInfoList.length;
        if (j > 0) {
            this.needRenderIsFullScreen.isFullScreen = this.primaryStack.policyInfoList[j - 1].isFullScreen;
        }
    }
    replacePrimary(g, h) {
        this.primaryStack.policyInfoList.pop();
        this.primaryStack.policyInfoList.push(g);
        return this.primaryStack.replacePath(g.navInfo, h);
    }
    replaceSecond(e, f) {
        this.secondaryStack.policyInfoList.pop();
        this.secondaryStack.policyInfoList.push(e);
        return this.secondaryStack.replacePath(e.navInfo, f);
    }
    popPrimary(c, d) {
        this.primaryStack.policyInfoList.pop();
        return this.primaryStack.popInner(c, d);
    }
    popSecondary(a, b) {
        this.secondaryStack.policyInfoList.pop();
        return this.secondaryStack.popInner(a, b);
    }
}

export default { MultiNavigation, MultiNavPathStack, SplitPolicy }