/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

"use strict";
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const i = '80vp';
const j = '40vp';
const m = '36vp';
const o = '20vp';
const t = '20vp';
const u = '16vp';
const a1 = '1px';
const b1 = '10vp';
const c1 = '16vp';
const g1 = '#182431';
const h1 = '#33000000';
const t1 = '#99FFFFFF';
const i1 = "arkui_app_bar_color_configuration";
const j1 = "arkui_app_bar_menu_safe_area";
const l1 = "arkui_app_bar_content_safe_area";
const m1 = "arkui_app_bar_info";
const n1 = "arkui_app_bar_screen";
const e2 = "arkui_custom_app_bar_menu_click";
const f2 = "arkui_custom_app_bar_close_click";
const g2 = "arkui_custom_app_bar_did_build";
const h2 = 10;
class o1 {
    constructor(a2, b2) {
        this.c2 = '#000000';
        this.d2 = '#FFFFFF';
        this.c2 = a2;
        this.d2 = b2;
    }
}
const q1 = new Map([
    [g1, new o1('#182431', '#e5ffffff')],
    [h1, new o1('#33182431', '#4Dffffff')],
    [t1, new o1('#99FFFFFF', '#33000000')],
]);
class e1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__menuResource = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125830217,
            type: 20000
        }, this, "menuResource");
        this.__closeResource = new ObservedPropertyObjectPU({
            bundleName: '',
            moduleName: '',
            params: [],
            id: 125831084,
            type: 20000
        }, this, "closeResource");
        this.__menuFillColor = new ObservedPropertySimplePU(this.getResourceColor(g1), this, "menuFillColor");
        this.__closeFillColor = new ObservedPropertySimplePU(this.getResourceColor(g1), this, "closeFillColor");
        this.__menubarBorderColor = new ObservedPropertySimplePU(this.getResourceColor(h1), this, "menubarBorderColor");
        this.__menubarBackColor = new ObservedPropertySimplePU(this.getResourceColor(t1), this, "menubarBackColor");
        this.__dividerBackgroundColor = new ObservedPropertySimplePU(this.getResourceColor(h1), this, "dividerBackgroundColor");
        this.__contentMarginTop = new ObservedPropertySimplePU('0vp', this, "contentMarginTop");
        this.__contentMarginLeft = new ObservedPropertySimplePU('0vp', this, "contentMarginLeft");
        this.__contentMarginRight = new ObservedPropertySimplePU('0vp', this, "contentMarginRight");
        this.__contentMarginBottom = new ObservedPropertySimplePU('0vp', this, "contentMarginBottom");
        this.__menuMarginTop = new ObservedPropertySimplePU('10vp', this, "menuMarginTop");
        this.isDark = true;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.menuResource !== undefined) {
            this.menuResource = params.menuResource;
        }
        if (params.closeResource !== undefined) {
            this.closeResource = params.closeResource;
        }
        if (params.menuFillColor !== undefined) {
            this.menuFillColor = params.menuFillColor;
        }
        if (params.closeFillColor !== undefined) {
            this.closeFillColor = params.closeFillColor;
        }
        if (params.menubarBorderColor !== undefined) {
            this.menubarBorderColor = params.menubarBorderColor;
        }
        if (params.menubarBackColor !== undefined) {
            this.menubarBackColor = params.menubarBackColor;
        }
        if (params.dividerBackgroundColor !== undefined) {
            this.dividerBackgroundColor = params.dividerBackgroundColor;
        }
        if (params.contentMarginTop !== undefined) {
            this.contentMarginTop = params.contentMarginTop;
        }
        if (params.contentMarginLeft !== undefined) {
            this.contentMarginLeft = params.contentMarginLeft;
        }
        if (params.contentMarginRight !== undefined) {
            this.contentMarginRight = params.contentMarginRight;
        }
        if (params.contentMarginBottom !== undefined) {
            this.contentMarginBottom = params.contentMarginBottom;
        }
        if (params.menuMarginTop !== undefined) {
            this.menuMarginTop = params.menuMarginTop;
        }
        if (params.isDark !== undefined) {
            this.isDark = params.isDark;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__menuResource.purgeDependencyOnElmtId(rmElmtId);
        this.__closeResource.purgeDependencyOnElmtId(rmElmtId);
        this.__menuFillColor.purgeDependencyOnElmtId(rmElmtId);
        this.__closeFillColor.purgeDependencyOnElmtId(rmElmtId);
        this.__menubarBorderColor.purgeDependencyOnElmtId(rmElmtId);
        this.__menubarBackColor.purgeDependencyOnElmtId(rmElmtId);
        this.__dividerBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMarginTop.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMarginLeft.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMarginRight.purgeDependencyOnElmtId(rmElmtId);
        this.__contentMarginBottom.purgeDependencyOnElmtId(rmElmtId);
        this.__menuMarginTop.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__menuResource.aboutToBeDeleted();
        this.__closeResource.aboutToBeDeleted();
        this.__menuFillColor.aboutToBeDeleted();
        this.__closeFillColor.aboutToBeDeleted();
        this.__menubarBorderColor.aboutToBeDeleted();
        this.__menubarBackColor.aboutToBeDeleted();
        this.__dividerBackgroundColor.aboutToBeDeleted();
        this.__contentMarginTop.aboutToBeDeleted();
        this.__contentMarginLeft.aboutToBeDeleted();
        this.__contentMarginRight.aboutToBeDeleted();
        this.__contentMarginBottom.aboutToBeDeleted();
        this.__menuMarginTop.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get menuResource() {
        return this.__menuResource.get();
    }
    set menuResource(newValue) {
        this.__menuResource.set(newValue);
    }
    get closeResource() {
        return this.__closeResource.get();
    }
    set closeResource(newValue) {
        this.__closeResource.set(newValue);
    }
    get menuFillColor() {
        return this.__menuFillColor.get();
    }
    set menuFillColor(newValue) {
        this.__menuFillColor.set(newValue);
    }
    get closeFillColor() {
        return this.__closeFillColor.get();
    }
    set closeFillColor(newValue) {
        this.__closeFillColor.set(newValue);
    }
    get menubarBorderColor() {
        return this.__menubarBorderColor.get();
    }
    set menubarBorderColor(newValue) {
        this.__menubarBorderColor.set(newValue);
    }
    get menubarBackColor() {
        return this.__menubarBackColor.get();
    }
    set menubarBackColor(newValue) {
        this.__menubarBackColor.set(newValue);
    }
    get dividerBackgroundColor() {
        return this.__dividerBackgroundColor.get();
    }
    set dividerBackgroundColor(newValue) {
        this.__dividerBackgroundColor.set(newValue);
    }
    get contentMarginTop() {
        return this.__contentMarginTop.get();
    }
    set contentMarginTop(newValue) {
        this.__contentMarginTop.set(newValue);
    }
    get contentMarginLeft() {
        return this.__contentMarginLeft.get();
    }
    set contentMarginLeft(newValue) {
        this.__contentMarginLeft.set(newValue);
    }
    get contentMarginRight() {
        return this.__contentMarginRight.get();
    }
    set contentMarginRight(newValue) {
        this.__contentMarginRight.set(newValue);
    }
    get contentMarginBottom() {
        return this.__contentMarginBottom.get();
    }
    set contentMarginBottom(newValue) {
        this.__contentMarginBottom.set(newValue);
    }
    get menuMarginTop() {
        return this.__menuMarginTop.get();
    }
    set menuMarginTop(newValue) {
        this.__menuMarginTop.set(newValue);
    }
    parseBoolean(value) {
        if (value === 'true') {
            return true;
        }
        return false;
    }
    getResourceColor(w1) {
        if (q1.has(w1)) {
            const z1 = q1.get(w1);
            if (z1) {
                return this.isDark ? z1.d2 : z1.c2;
            }
        }
        return w1;
    }
    setCustomCallback(eventName, param) {
        if (eventName === i1) {
            this.onColorConfigurationUpdate(this.parseBoolean(param));
        }
        else if (eventName === j1) {
            let value = Number(param) + h2;
            this.menuMarginTop = value.toString();
        }
        else if (eventName === l1) {
            let v1 = param.split('|');
            if (v1.length < 4) {
                return;
            }
            this.contentMarginTop = v1[0];
            this.contentMarginLeft = v1[1];
            this.contentMarginRight = v1[2];
            this.contentMarginBottom = v1[3];
        }
        else if (eventName === m1) {
            let u1 = param.split('|');
        }
        else if (eventName === n1) {
        }
    }
    onColorConfigurationUpdate(s1) {
        this.isDark = s1;
        this.menuFillColor = this.getResourceColor(g1);
        this.closeFillColor = this.getResourceColor(g1);
        this.menubarBorderColor = this.getResourceColor(h1);
        this.dividerBackgroundColor = this.getResourceColor(h1);
        this.menubarBackColor = this.getResourceColor(t1);
    }
    onMenuButtonClick() {
        ContainerAppBar.callNative(e2);
    }
    onCloseButtonClick() {
        ContainerAppBar.callNative(f2);
    }
    onDidBuild() {
        ContainerAppBar.callNative(g2);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.height('100%');
            Column.width('100%');
            Column.justifyContent(FlexAlign.End);
            Column.backgroundColor(Color.Transparent);
            Column.hitTestBehavior(HitTestMode.Transparent);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.TopEnd });
            Stack.id('AtomicServiceContainerId');
            Stack.height('100%');
            Stack.width('100%');
            Stack.backgroundColor(Color.Transparent);
            Stack.hitTestBehavior(HitTestMode.Transparent);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.padding({
                top: this.contentMarginTop,
                left: this.contentMarginLeft,
                right: this.contentMarginRight,
                bottom: this.contentMarginBottom
            });
            Row.height('100%');
            Row.width('100%');
            Row.id('AtomicServiceStageId');
        }, Row);
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.id('AtomicServiceMenubarRowId');
            Row.justifyContent(FlexAlign.End);
            Row.margin({ top: this.menuMarginTop, left: c1, right: c1 });
            Row.height(m);
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.borderRadius(t);
            Row.borderWidth(a1);
            Row.borderColor(this.menubarBorderColor);
            Row.backgroundColor(this.menubarBackColor);
            Row.height(m);
            Row.width(i);
            Row.align(Alignment.Top);
            Row.draggable(false);
            Row.hitTestBehavior(HitTestMode.Transparent);
            Row.id('AtomicServiceMenubarId');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.id('AtomicServiceMenuId');
            Button.type(ButtonType.Normal);
            Button.borderRadius({ topLeft: t, bottomLeft: t });
            Button.backgroundColor(Color.Transparent);
            Button.width(j);
            Button.height(m);
            Gesture.create(GesturePriority.Low);
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onMenuButtonClick();
            });
            TapGesture.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.menuResource);
            Image.id('AtomicServiceMenuIconId');
            Image.width(o);
            Image.height(o);
            Image.fillColor(this.menuFillColor);
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
        }, Image);
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Divider.create();
            Divider.id('AtomicServiceDividerId');
            Divider.vertical(true);
            Divider.color(this.dividerBackgroundColor);
            Divider.lineCap(LineCapStyle.Round);
            Divider.strokeWidth(a1);
            Divider.height(u);
        }, Divider);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.id('AtomicServiceCloseId');
            Button.type(ButtonType.Normal);
            Button.backgroundColor(Color.Transparent);
            Button.borderRadius({ topRight: t, bottomRight: t });
            Button.width(j);
            Button.height(m);
            Gesture.create(GesturePriority.Low);
            TapGesture.create();
            TapGesture.onAction(() => {
                this.onCloseButtonClick();
            });
            TapGesture.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.closeResource);
            Image.id('AtomicServiceCloseIconId');
            Image.width(o);
            Image.height(o);
            Image.fillColor(this.closeFillColor);
            Image.draggable(false);
            Image.interpolation(ImageInterpolation.High);
        }, Image);
        Button.pop();
        Row.pop();
        Row.pop();
        Stack.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
    static getEntryName() {
        return "Index";
    }
}

ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadCustomAppbar(new e1(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();