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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
export class AtomicServiceNavigation extends ViewPU {
    constructor(w, x, y, z = -1, a1 = undefined, b1) {
        super(w, y, z, b1);
        if (typeof a1 === "function") {
            this.paramsGenerator_ = a1;
        }
        this.__navPathStack = new ObservedPropertyObjectPU(new NavPathStack(), this, "navPathStack");
        this.navigationContent = undefined;
        this.__title = new SynchedPropertyObjectOneWayPU(x.title, this, "title");
        this.__titleOptions = new SynchedPropertyObjectOneWayPU(x.titleOptions, this, "titleOptions");
        this.__hideTitleBar = new SynchedPropertySimpleOneWayPU(x.hideTitleBar, this, "hideTitleBar");
        this.__navBarWidth = new SynchedPropertyObjectOneWayPU(x.navBarWidth, this, "navBarWidth");
        this.__mode = new SynchedPropertySimpleOneWayPU(x.mode, this, "mode");
        this.navDestinationBuilder = this.defaultNavDestinationBuilder;
        this.__navBarWidthRange = new SynchedPropertyObjectOneWayPU(x.navBarWidthRange, this, "navBarWidthRange");
        this.__minContentWidth = new SynchedPropertyObjectOneWayPU(x.minContentWidth, this, "minContentWidth");
        this.stateChangeCallback = undefined;
        this.modeChangeCallback = undefined;
        this.setInitiallyProvidedValue(x);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v) {
        if (v.navPathStack !== undefined) {
            this.navPathStack = v.navPathStack;
        }
        if (v.navigationContent !== undefined) {
            this.navigationContent = v.navigationContent;
        }
        if (v.titleOptions === undefined) {
            this.__titleOptions.set({ isBlurEnabled: true });
        }
        if (v.navDestinationBuilder !== undefined) {
            this.navDestinationBuilder = v.navDestinationBuilder;
        }
        if (v.stateChangeCallback !== undefined) {
            this.stateChangeCallback = v.stateChangeCallback;
        }
        if (v.modeChangeCallback !== undefined) {
            this.modeChangeCallback = v.modeChangeCallback;
        }
    }
    updateStateVars(u) {
        this.__title.reset(u.title);
        this.__titleOptions.reset(u.titleOptions);
        this.__hideTitleBar.reset(u.hideTitleBar);
        this.__navBarWidth.reset(u.navBarWidth);
        this.__mode.reset(u.mode);
        this.__navBarWidthRange.reset(u.navBarWidthRange);
        this.__minContentWidth.reset(u.minContentWidth);
    }
    purgeVariableDependenciesOnElmtId(t) {
        this.__navPathStack.purgeDependencyOnElmtId(t);
        this.__title.purgeDependencyOnElmtId(t);
        this.__titleOptions.purgeDependencyOnElmtId(t);
        this.__hideTitleBar.purgeDependencyOnElmtId(t);
        this.__navBarWidth.purgeDependencyOnElmtId(t);
        this.__mode.purgeDependencyOnElmtId(t);
        this.__navBarWidthRange.purgeDependencyOnElmtId(t);
        this.__minContentWidth.purgeDependencyOnElmtId(t);
    }
    aboutToBeDeleted() {
        this.__navPathStack.aboutToBeDeleted();
        this.__title.aboutToBeDeleted();
        this.__titleOptions.aboutToBeDeleted();
        this.__hideTitleBar.aboutToBeDeleted();
        this.__navBarWidth.aboutToBeDeleted();
        this.__mode.aboutToBeDeleted();
        this.__navBarWidthRange.aboutToBeDeleted();
        this.__minContentWidth.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get navPathStack() {
        return this.__navPathStack.get();
    }
    set navPathStack(s) {
        this.__navPathStack.set(s);
    }
    get title() {
        return this.__title.get();
    }
    set title(r) {
        this.__title.set(r);
    }
    get titleOptions() {
        return this.__titleOptions.get();
    }
    set titleOptions(q) {
        this.__titleOptions.set(q);
    }
    get hideTitleBar() {
        return this.__hideTitleBar.get();
    }
    set hideTitleBar(p) {
        this.__hideTitleBar.set(p);
    }
    get navBarWidth() {
        return this.__navBarWidth.get();
    }
    set navBarWidth(o) {
        this.__navBarWidth.set(o);
    }
    get mode() {
        return this.__mode.get();
    }
    set mode(n) {
        this.__mode.set(n);
    }
    get navBarWidthRange() {
        return this.__navBarWidthRange.get();
    }
    set navBarWidthRange(m) {
        this.__navBarWidthRange.set(m);
    }
    get minContentWidth() {
        return this.__minContentWidth.get();
    }
    set minContentWidth(l) {
        this.__minContentWidth.set(l);
    }
    defaultNavDestinationBuilder(i, j, k = null) {
    }
    initialRender() {
        this.observeComponentCreation2((g, h) => {
            Navigation.create(this.navPathStack);
            Navigation.title(ObservedObject.GetRawObject(this.title), {
                backgroundColor: this.titleOptions?.backgroundColor,
                backgroundBlurStyle: this.titleOptions?.isBlurEnabled ? BlurStyle.COMPONENT_THICK : BlurStyle.NONE,
                barStyle: this.titleOptions?.barStyle
            });
            Navigation.titleMode(NavigationTitleMode.Mini);
            Navigation.hideBackButton(true);
            Navigation.hideTitleBar(this.hideTitleBar);
            Navigation.navBarWidth(ObservedObject.GetRawObject(this.navBarWidth));
            Navigation.navBarPosition(NavBarPosition.Start);
            Navigation.mode(this.mode);
            Navigation.navDestination({ builder: this.navDestinationBuilder.bind(this) });
            Navigation.navBarWidthRange(ObservedObject.GetRawObject(this.navBarWidthRange));
            Navigation.minContentWidth(ObservedObject.GetRawObject(this.minContentWidth));
            Navigation.onNavBarStateChange(this.stateChangeCallback);
            Navigation.onNavigationModeChange(this.modeChangeCallback);
        }, Navigation);
        this.observeComponentCreation2((c, d) => {
            If.create();
            if (this.navigationContent) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.navigationContent.bind(this)(this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Navigation.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { AtomicServiceNavigation };