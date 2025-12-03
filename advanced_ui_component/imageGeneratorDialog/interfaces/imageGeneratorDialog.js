/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
const promptAction = requireNapi('promptAction');

class ImageGeneratorDialog extends ViewPU {
    constructor(s4, t4, u4, v4 = -1, w4 = undefined, x4) {
        super(s4, u4, v4, x4);
        if (typeof w4 === "function") {
            this.paramsGenerator_ = w4;
        }
        this.stack = new NavPathStack();
        this.__width_ = new ObservedPropertyObjectPU(650, this, "width_");
        this.__height_ = new ObservedPropertyObjectPU(560, this, "height_");
        this.setInitiallyProvidedValue(t4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r4) {
        if (r4.stack !== undefined) {
            this.stack = r4.stack;
        }
        if (r4.width_ !== undefined) {
            this.width_ = r4.width_;
        }
        if (r4.height_ !== undefined) {
            this.height_ = r4.height_;
        }
    }
    updateStateVars(q4) {
    }
    purgeVariableDependenciesOnElmtId(p4) {
        this.__width_.purgeDependencyOnElmtId(p4);
        this.__height_.purgeDependencyOnElmtId(p4);
    }
    aboutToBeDeleted() {
        this.__width_.aboutToBeDeleted();
        this.__height_.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get width_() {
        return this.__width_.get();
    }
    set width_(o4) {
        this.__width_.set(o4);
    }
    get height_() {
        return this.__height_.get();
    }
    set height_(n4) {
        this.__height_.set(n4);
    }
    pageMap(f4, g4 = null) {
        this.observeComponentCreation2((h4, i4) => {
            If.create();
            if (f4 === 'canvasHome') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((j4, k4) => {
                            if (k4) {
                                let l4 = new CanvasHome(this, {}, undefined, j4, () => { }, { page: "mood_canvas_factory/src/main/ets/pages/Index.ets", line: 17, col: 7 });
                                ViewPU.create(l4);
                                let m4 = () => {
                                    return {};
                                };
                                l4.paramsGenerator_ = m4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(j4, {});
                            }
                        }, { name: "CanvasHome" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    aboutToAppear() {
        this.stack.pushPath({ name: 'canvasHome' });
    }
    initialRender() {
        this.observeComponentCreation2((d4, e4) => {
            Scroll.create();
            Scroll.width('100%');
            Scroll.height('100%');
            Scroll.scrollable(ScrollDirection.FREE);
        }, Scroll);
        this.observeComponentCreation2((b4, c4) => {
            Navigation.create(this.stack, { moduleName: "mood_canvas_factory", pagePath: "", isUserCreateStack: true });
            Navigation.hideNavBar(true);
            Navigation.navDestination({ builder: this.pageMap.bind(this) });
            Navigation.height(ObservedObject.GetRawObject(this.height_));
            Navigation.width(ObservedObject.GetRawObject(this.width_));
            Navigation.borderRadius(32);
            Navigation.clip(true);
        }, Navigation);
        Navigation.pop();
        Scroll.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class CanvasHome extends ViewPU {
    constructor(v3, w3, x3, y3 = -1, z3 = undefined, a4) {
        super(v3, x3, y3, a4);
        if (typeof z3 === "function") {
            this.paramsGenerator_ = z3;
        }
        this.stack = new NavPathStack();
        this.__titleName = new ObservedPropertySimplePU('灵感画布', this, "titleName");
        this.setInitiallyProvidedValue(w3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u3) {
        if (u3.stack !== undefined) {
            this.stack = u3.stack;
        }
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
        this.observeComponentCreation2((o1, p1) => {
            NavDestination.create(() => {
                this.observeComponentCreation2((a3, b3) => {
                    Column.create();
                    Column.height('100%');
                    Column.width('100%');
                }, Column);
                this.observeComponentCreation2((y2, z2) => {
                    Row.create();
                    Row.margin({
                        top: 21,
                        bottom: 28
                    });
                }, Row);
                this.observeComponentCreation2((w2, x2) => {
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
                this.observeComponentCreation2((u2, v2) => {
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
                this.observeComponentCreation2((o2, p2) => {
                    TabContent.create(() => {
                        {
                            this.observeComponentCreation2((q2, r2) => {
                                if (r2) {
                                    let s2 = new FunctionAreaPlaceholder(this, {}, undefined, q2, () => { }, { page: "mood_canvas_factory/src/main/ets/pages/Index.ets", line: 130, col: 15 });
                                    ViewPU.create(s2);
                                    let t2 = () => {
                                        return {};
                                    };
                                    s2.paramsGenerator_ = t2;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(q2, {});
                                }
                            }, { name: "FunctionAreaPlaceholder" });
                        }
                    });
                    TabContent.tabBar({ builder: () => {
                            StyleSelectTabBarBuilder.call(this, '图像');
                        } });
                }, TabContent);
                TabContent.pop();
                this.observeComponentCreation2((i2, j2) => {
                    TabContent.create(() => {
                        {
                            this.observeComponentCreation2((k2, l2) => {
                                if (l2) {
                                    let m2 = new FunctionAreaPlaceholder(this, {}, undefined, k2, () => { }, { page: "mood_canvas_factory/src/main/ets/pages/Index.ets", line: 135, col: 15 });
                                    ViewPU.create(m2);
                                    let n2 = () => {
                                        return {};
                                    };
                                    m2.paramsGenerator_ = n2;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(k2, {});
                                }
                            }, { name: "FunctionAreaPlaceholder" });
                        }
                    });
                    TabContent.tabBar({ builder: () => {
                            StyleSelectTabBarBuilder.call(this, '风格');
                        } });
                }, TabContent);
                TabContent.pop();
                this.observeComponentCreation2((c2, d2) => {
                    TabContent.create(() => {
                        {
                            this.observeComponentCreation2((e2, f2) => {
                                if (f2) {
                                    let g2 = new FunctionAreaPlaceholder(this, {}, undefined, e2, () => { }, { page: "mood_canvas_factory/src/main/ets/pages/Index.ets", line: 141, col: 15 });
                                    ViewPU.create(g2);
                                    let h2 = () => {
                                        return {};
                                    };
                                    g2.paramsGenerator_ = h2;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(e2, {});
                                }
                            }, { name: "FunctionAreaPlaceholder" });
                        }
                    });
                    TabContent.tabBar({ builder: () => {
                            StyleSelectTabBarBuilder.call(this, '比例');
                        } });
                }, TabContent);
                TabContent.pop();
                this.observeComponentCreation2((w1, x1) => {
                    TabContent.create(() => {
                        {
                            this.observeComponentCreation2((y1, z1) => {
                                if (z1) {
                                    let a2 = new FunctionAreaPlaceholder(this, {}, undefined, y1, () => { }, { page: "mood_canvas_factory/src/main/ets/pages/Index.ets", line: 147, col: 15 });
                                    ViewPU.create(a2);
                                    let b2 = () => {
                                        return {};
                                    };
                                    a2.paramsGenerator_ = b2;
                                }
                                else {
                                    this.updateStateVarsOfChildByElmtId(y1, {});
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
                this.observeComponentCreation2((u1, v1) => {
                    Row.create();
                    Row.width('100%');
                    Row.height(45);
                    Row.margin({
                        bottom: 14
                    });
                }, Row);
                this.observeComponentCreation2((s1, t1) => {
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
                this.observeComponentCreation2((q1, r1) => {
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
            }, { moduleName: "mood_canvas_factory", pagePath: "" });
            NavDestination.title({ builder: this.homeTitleBuilder.bind(this) });
        }, NavDestination);
        NavDestination.pop();
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
                }, undefined, w, () => { }, { page: "mood_canvas_factory/src/main/ets/pages/Index.ets", line: 221, col: 3 });
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

console.info('[imageGenerator]', `end of loadImageGeneratorDialog.js, will call loadImageGeneratorDialog`);
ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadImageGeneratorDialog(new ImageGeneratorDialog(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();