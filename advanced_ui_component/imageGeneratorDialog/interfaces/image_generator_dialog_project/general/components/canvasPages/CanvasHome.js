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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import promptAction from "@ohos.promptAction";
export class CanvasHome extends ViewPU {
    constructor(v3, w3, x3, y3 = -1, z3 = undefined, a4) {
        super(v3, x3, y3, a4);
        if (typeof z3 === "function") {
            this.paramsGenerator_ = z3;
        }
        this.__titleName = new ObservedPropertySimplePU('灵感画布', this, "titleName");
        this.setInitiallyProvidedValue(w3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u3) {
        if (u3.titleName !== undefined) {
            this.titleName = u3.titleName;
        }
    }
    updateStateVars(t3) {
    }
    purgeVariableDependenciesOnElmtId(s3) {
        this.__titleName.purgeDependencyOnElmtId(s3);
    }
    aboutToBeDeleted() {
        this.__titleName.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleName() {
        return this.__titleName.get();
    }
    set titleName(r3) {
        this.__titleName.set(r3);
    }
    homeTitleBuilder(c3 = null) {
        this.observeComponentCreation2((p3, q3) => {
            Column.create();
            Column.height(64);
            Column.width('100%');
            Column.padding({
                left: 16,
                right: 16,
                top: 8
            });
        }, Column);
        this.observeComponentCreation2((n3, o3) => {
            Row.create();
            Row.height(56);
            Row.width(618);
        }, Row);
        this.observeComponentCreation2((l3, m3) => {
            Row.create();
            Row.height('100%');
            Row.width('50%');
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((j3, k3) => {
            Text.create(this.titleName);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(20);
            Text.fontWeight(700);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((h3, i3) => {
            Row.create();
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.End);
            Row.height('100%');
            Row.width('50%');
        }, Row);
        this.observeComponentCreation2((f3, g3) => {
            Image.create('');
            Image.width({ "id": -1, "type": 10002, params: ['app.float.home_title_menu_icon_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.height({ "id": -1, "type": 10002, params: ['app.float.home_title_menu_icon_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.borderRadius({ "id": -1, "type": 10002, params: ['app.float.home_title_menu_icon_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.backgroundColor({ "id": -1, "type": 10003, params: ['app.string.home_title_menu_icon_background_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.onClick(() => {
                promptAction.openToast({ message: 'full_screen clicked' })
                    .then(() => { })
                    .catch(() => { });
            });
            Image.margin({ right: 8 });
        }, Image);
        this.observeComponentCreation2((d3, e3) => {
            Image.create('');
            Image.width({ "id": -1, "type": 10002, params: ['app.float.home_title_menu_icon_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.height({ "id": -1, "type": 10002, params: ['app.float.home_title_menu_icon_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.borderRadius({ "id": -1, "type": 10002, params: ['app.float.home_title_menu_icon_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.backgroundColor({ "id": -1, "type": 10003, params: ['app.string.home_title_menu_icon_background_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.onClick(() => {
                promptAction.openToast({ message: 'x_icon clicked' })
                    .then(() => { })
                    .catch(() => { });
            });
        }, Image);
        Row.pop();
        Row.pop();
        Column.pop();
    }
    initialRender() {
        this.observeComponentCreation2((a3, b3) => {
            Navigation.create(new NavPathStack(), { moduleName: "image_generator_dialog", pagePath: "", isUserCreateStack: false });
            Navigation.mode(NavigationMode.Stack);
            Navigation.titleMode(NavigationTitleMode.Mini);
            Navigation.hideBackButton(true);
            Navigation.title({ builder: this.homeTitleBuilder.bind(this) });
        }, Navigation);
        this.observeComponentCreation2((y2, z2) => {
            Column.create();
            Column.height('100%');
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((w2, x2) => {
            Row.create();
            Row.margin({
                top: 21,
                bottom: 28
            });
        }, Row);
        this.observeComponentCreation2((u2, v2) => {
            Column.create();
            Column.width(386);
            Column.height(386);
            Column.margin({
                left: 69,
                right: 54
            });
            Column.borderRadius(24);
            Column.borderWidth(2);
            Column.borderColor('#ffffff');
            Column.shadow({
                radius: 10,
            });
        }, Column);
        Column.pop();
        this.observeComponentCreation2((s2, t2) => {
            Tabs.create();
            Tabs.barHeight(284);
            Tabs.scrollable(false);
            Tabs.vertical(true);
            Tabs.barPosition(BarPosition.End);
            Tabs.width(118);
            Tabs.height(386);
            Tabs.margin({
                right: 16
            });
        }, Tabs);
        this.observeComponentCreation2((m2, n2) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((o2, p2) => {
                        if (p2) {
                            let q2 = new FunctionAreaPlaceholder(this, {}, undefined, o2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/canvasPages/CanvasHome.ets", line: 89, col: 15 });
                            ViewPU.create(q2);
                            let r2 = () => {
                                return {};
                            };
                            q2.paramsGenerator_ = r2;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(o2, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    StyleSelectTabBarBuilder.call(this, '图像');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((g2, h2) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((i2, j2) => {
                        if (j2) {
                            let k2 = new FunctionAreaPlaceholder(this, {}, undefined, i2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/canvasPages/CanvasHome.ets", line: 94, col: 15 });
                            ViewPU.create(k2);
                            let l2 = () => {
                                return {};
                            };
                            k2.paramsGenerator_ = l2;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(i2, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    StyleSelectTabBarBuilder.call(this, '风格');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((a2, b2) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((c2, d2) => {
                        if (d2) {
                            let e2 = new FunctionAreaPlaceholder(this, {}, undefined, c2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/canvasPages/CanvasHome.ets", line: 99, col: 15 });
                            ViewPU.create(e2);
                            let f2 = () => {
                                return {};
                            };
                            e2.paramsGenerator_ = f2;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(c2, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    StyleSelectTabBarBuilder.call(this, '比例');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((u1, v1) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((w1, x1) => {
                        if (x1) {
                            let y1 = new FunctionAreaPlaceholder(this, {}, undefined, w1, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/canvasPages/CanvasHome.ets", line: 104, col: 15 });
                            ViewPU.create(y1);
                            let z1 = () => {
                                return {};
                            };
                            y1.paramsGenerator_ = z1;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(w1, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    StyleSelectTabBarBuilder.call(this, '清晰度');
                } });
        }, TabContent);
        TabContent.pop();
        Tabs.pop();
        Row.pop();
        this.observeComponentCreation2((s1, t1) => {
            Row.create();
            Row.width('100%');
            Row.height(45);
            Row.margin({
                bottom: 14
            });
        }, Row);
        this.observeComponentCreation2((q1, r1) => {
            Column.create();
            Column.height(40);
            Column.width(510);
            Column.margin({
                top: 3,
                bottom: 2,
                left: 16,
                right: 12
            });
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
        }, Column);
        Column.pop();
        this.observeComponentCreation2((o1, p1) => {
            Column.create();
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
            Column.height(40);
            Column.width(96);
            Column.margin({
                top: 3,
                bottom: 2,
                right: 16
            });
        }, Column);
        Column.pop();
        Row.pop();
        Column.pop();
        Navigation.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class FunctionAreaPlaceholder extends ViewPU {
    constructor(i1, j1, k1, l1 = -1, m1 = undefined, n1) {
        super(i1, k1, l1, n1);
        if (typeof m1 === "function") {
            this.paramsGenerator_ = m1;
        }
        this.setInitiallyProvidedValue(j1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(h1) {
    }
    updateStateVars(g1) {
    }
    purgeVariableDependenciesOnElmtId(f1) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    initialRender() {
        this.observeComponentCreation2((d1, e1) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.padding({
                right: 14
            });
        }, Column);
        this.observeComponentCreation2((b1, c1) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.border({ width: 0.5 });
        }, Column);
        Column.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
function StyleSelectTabBarBuilder(t, u = null) {
    const v = t;
    {
        (u ? u : this).observeComponentCreation2((w, x, y = v) => {
            if (x) {
                let z = new UserFunctionAreaTabBar(u ? u : this, {
                    name: y,
                }, undefined, w, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/canvasPages/CanvasHome.ets", line: 181, col: 3 });
                ViewPU.create(z);
                let a1 = () => {
                    return {
                        name: y
                    };
                };
                z.paramsGenerator_ = a1;
            }
            else {
                (u ? u : this).updateStateVarsOfChildByElmtId(w, {});
            }
        }, { name: "UserFunctionAreaTabBar" });
    }
}
class UserFunctionAreaTabBar extends ViewPU {
    constructor(n, o, p, q = -1, r = undefined, s) {
        super(n, p, q, s);
        if (typeof r === "function") {
            this.paramsGenerator_ = r;
        }
        this.name = '__NA__';
        this.setInitiallyProvidedValue(o);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m) {
        if (m.name !== undefined) {
            this.name = m.name;
        }
    }
    updateStateVars(l) {
    }
    purgeVariableDependenciesOnElmtId(k) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    initialRender() {
        this.observeComponentCreation2((i, j) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((g, h) => {
            Column.create();
            Column.padding(12);
            Column.width(48);
            Column.height(48);
            Column.margin({ bottom: 4 });
            Column.borderRadius(24);
            Column.backgroundColor('rgba(0,0,0,0.05)');
        }, Column);
        this.observeComponentCreation2((e, f) => {
            Image.create('');
            Image.width(24);
            Image.height(24);
        }, Image);
        Column.pop();
        this.observeComponentCreation2((c, d) => {
            Column.create();
            Column.height(10);
        }, Column);
        this.observeComponentCreation2((a, b) => {
            Text.create(this.name);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(10);
            Text.fontWeight(500);
        }, Text);
        Text.pop();
        Column.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
