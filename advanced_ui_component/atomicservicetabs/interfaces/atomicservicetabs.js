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
const DEFAULT_BAR_WIDTH = 96;
const DEFAULT_BAR_HEIGHT = 52;
export class AtomicServiceTabs extends ViewPU {
    constructor(m1, n1, o1, p1 = -1, q1 = undefined, r1) {
        super(m1, o1, p1, r1);
        if (typeof q1 === "function") {
            this.paramsGenerator_ = q1;
        }
        this.tabContents = undefined;
        this.__tabBarOptionsArray = new SynchedPropertyObjectOneWayPU(n1.tabBarOptionsArray, this, "tabBarOptionsArray");
        this.__tabBarPosition = new SynchedPropertySimpleOneWayPU(n1.tabBarPosition, this, "tabBarPosition");
        this.__barBackgroundColor = new SynchedPropertyObjectOneWayPU(n1.barBackgroundColor, this, "barBackgroundColor");
        this.__index = new SynchedPropertyObjectOneWayPU(n1.index, this, "index");
        this.__barOverlap = new SynchedPropertySimpleOneWayPU(n1.barOverlap, this, "barOverlap");
        this.controller = new TabsController();
        this.onChange = undefined;
        this.onTabBarClick = undefined;
        this.onContentWillChange = undefined;
        this.setInitiallyProvidedValue(n1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l1) {
        if (l1.tabContents !== undefined) {
            this.tabContents = l1.tabContents;
        }
        if (l1.tabBarPosition === undefined) {
            this.__tabBarPosition.set(TabBarPosition.BOTTOM);
        }
        if (l1.barBackgroundColor === undefined) {
            this.__barBackgroundColor.set(Color.Transparent);
        }
        if (l1.index === undefined) {
            this.__index.set(0);
        }
        if (l1.barOverlap === undefined) {
            this.__barOverlap.set(true);
        }
        if (l1.controller !== undefined) {
            this.controller = l1.controller;
        }
        if (l1.onChange !== undefined) {
            this.onChange = l1.onChange;
        }
        if (l1.onTabBarClick !== undefined) {
            this.onTabBarClick = l1.onTabBarClick;
        }
        if (l1.onContentWillChange !== undefined) {
            this.onContentWillChange = l1.onContentWillChange;
        }
    }
    updateStateVars(k1) {
        this.__tabBarOptionsArray.reset(k1.tabBarOptionsArray);
        this.__tabBarPosition.reset(k1.tabBarPosition);
        this.__barBackgroundColor.reset(k1.barBackgroundColor);
        this.__index.reset(k1.index);
        this.__barOverlap.reset(k1.barOverlap);
    }
    purgeVariableDependenciesOnElmtId(j1) {
        this.__tabBarOptionsArray.purgeDependencyOnElmtId(j1);
        this.__tabBarPosition.purgeDependencyOnElmtId(j1);
        this.__barBackgroundColor.purgeDependencyOnElmtId(j1);
        this.__index.purgeDependencyOnElmtId(j1);
        this.__barOverlap.purgeDependencyOnElmtId(j1);
    }
    aboutToBeDeleted() {
        this.__tabBarOptionsArray.aboutToBeDeleted();
        this.__tabBarPosition.aboutToBeDeleted();
        this.__barBackgroundColor.aboutToBeDeleted();
        this.__index.aboutToBeDeleted();
        this.__barOverlap.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get tabBarOptionsArray() {
        return this.__tabBarOptionsArray.get();
    }
    set tabBarOptionsArray(i1) {
        this.__tabBarOptionsArray.set(i1);
    }
    get tabBarPosition() {
        return this.__tabBarPosition.get();
    }
    set tabBarPosition(h1) {
        this.__tabBarPosition.set(h1);
    }
    get barBackgroundColor() {
        return this.__barBackgroundColor.get();
    }
    set barBackgroundColor(g1) {
        this.__barBackgroundColor.set(g1);
    }
    get index() {
        return this.__index.get();
    }
    set index(f1) {
        this.__index.set(f1);
    }
    get barOverlap() {
        return this.__barOverlap.get();
    }
    set barOverlap(e1) {
        this.__barOverlap.set(e1);
    }
    initialRender() {
        this.observeComponentCreation2((c1, d1) => {
            Tabs.create({
                barPosition: this.tabBarPosition === TabBarPosition.LEFT ? BarPosition.Start : BarPosition.End,
                index: this.index,
                controller: this.controller
            });
            Tabs.barBackgroundColor(ObservedObject.GetRawObject(this.barBackgroundColor));
            Tabs.divider(null);
            Tabs.vertical(this.tabBarPosition === TabBarPosition.LEFT ? true : false);
            Tabs.scrollable(false);
            Tabs.barOverlap(this.barOverlap);
            Tabs.barBackgroundBlurStyle(BlurStyle.COMPONENT_THICK);
            Tabs.onChange(this.onChange);
            Tabs.onTabBarClick(this.onTabBarClick);
            Tabs.onContentWillChange(this.onContentWillChange);
            Tabs.width((!this.tabContents && this.tabBarPosition === TabBarPosition.LEFT) ? DEFAULT_BAR_WIDTH : '100%');
            Tabs.height((!this.tabContents && this.tabBarPosition === TabBarPosition.BOTTOM) ? DEFAULT_BAR_HEIGHT : '100%');
        }, Tabs);
        this.observeComponentCreation2((h, i) => {
            ForEach.create();
            const j = (l, m) => {
                const n = l;
                this.observeComponentCreation2((p, q) => {
                    If.create();
                    if (n) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((u, v) => {
                                TabContent.create(() => {
                                    this.observeComponentCreation2((y, z) => {
                                        If.create();
                                        if (this.tabContents && this.tabContents[m]) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.tabContents[m]?.bind(this)?.(this);
                                            });
                                        }
                                        else {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                            });
                                        }
                                    }, If);
                                    If.pop();
                                });
                                TabContent.tabBar(BottomTabBarStyle.of(n.icon, n.text)
                                    .labelStyle({ unselectedColor: n.unselectedColor, selectedColor: n.selectedColor })
                                    .iconStyle({ unselectedColor: n.unselectedColor, selectedColor: n.selectedColor }));
                                TabContent.width((!this.tabContents && this.tabBarPosition === TabBarPosition.LEFT) ? DEFAULT_BAR_WIDTH : '100%');
                                TabContent.height((!this.tabContents && this.tabBarPosition === TabBarPosition.BOTTOM) ? DEFAULT_BAR_HEIGHT : '100%');
                            }, TabContent);
                            TabContent.pop();
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(h, this.tabBarOptionsArray, j, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Tabs.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class TabBarOptions {
    constructor(b, c, d, e) {
        this.icon = b;
        this.text = c;
        this.unselectedColor = d;
        this.selectedColor = e;
    }
}

export var TabBarPosition;
(function (a) {
    a[a["LEFT"] = 0] = "LEFT";
    a[a["BOTTOM"] = 1] = "BOTTOM";
})(TabBarPosition || (TabBarPosition = {}));

export default { AtomicServiceTabs, TabBarOptions, TabBarPosition};