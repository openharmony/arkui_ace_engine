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

var __decorate = (this && this.__decorate) || function (r15, s15, t15, u15) {
    var v15 = arguments.length, w15 = v15 < 3 ? s15 : u15 === null ? u15 = Object.getOwnPropertyDescriptor(s15, t15) : u15, x15;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        w15 = Reflect.decorate(r15, s15, t15, u15);
    else
        for (var y15 = r15.length - 1; y15 >= 0; y15--)
            if (x15 = r15[y15])
                w15 = (v15 < 3 ? x15(w15) : v15 > 3 ? x15(s15, t15, w15) : x15(s15, t15)) || w15;
    return v15 > 3 && w15 && Object.defineProperty(s15, t15, w15), w15;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { FunctionAreaPlaceholder, StyleSelectBuilder, StyleSelectTabBarBuilder, UserInteractiveTabBarBuilder } from "./UserFunctionArea";
export class LandscapeSelectFuncArea extends ViewV2 {
    constructor(l15, m15, n15, o15 = -1, p15, q15) {
        super(l15, o15, q15);
        this.styles = undefined;
        this.tabBarDefaultBgColor = 'rgba(0,0,0,0.05)';
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
        this.styleItems = [];
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(k15) {
        this.styles = undefined;
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
        this.styleItems = [];
    }
    aboutToAppear() {
        for (let j15 = 0; this.styles && j15 < this.styles?.length; ++j15) {
            this.styleItems.push({ name: this.styles[j15].name, resourceAddr: this.styles[j15].icon });
        }
    }
    initialRender() {
        this.observeComponentCreation2((h15, i15) => {
            Tabs.create();
            Tabs.barHeight(284);
            Tabs.scrollable(false);
            Tabs.vertical(true);
            Tabs.barPosition(BarPosition.End);
            Tabs.width(118);
            Tabs.height(386);
        }, Tabs);
        this.observeComponentCreation2((b15, c15) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((d15, e15) => {
                        if (e15) {
                            let f15 = new FunctionAreaPlaceholder(this, {}, undefined, d15, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 36, col: 9 });
                            ViewV2.create(f15);
                            let g15 = () => {
                                return {};
                            };
                            f15.paramsGenerator_ = g15;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(d15, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '图像');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((z14, a15) => {
            TabContent.create(() => {
                StyleSelectBuilder.bind(this)(this.styleItems);
            });
            TabContent.tabBar({ builder: () => {
                    StyleSelectTabBarBuilder.call(this, makeBuilderParameterProxy("StyleSelectTabBarBuilder", { name: () => '风格', icon: () => ({ bundleName: "", moduleName: "", id: 0 }), bgColor: () => (this["__tabBarStyleBgColor"] ? this["__tabBarStyleBgColor"] : this["tabBarStyleBgColor"]) }));
                } });
            TabContent.onWillShow(() => {
                this.tabBarStyleBgColor = Color.White;
            });
            TabContent.onWillHide(() => {
                this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
            });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((t14, u14) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((v14, w14) => {
                        if (w14) {
                            let x14 = new FunctionAreaPlaceholder(this, {}, undefined, v14, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 52, col: 9 });
                            ViewV2.create(x14);
                            let y14 = () => {
                                return {};
                            };
                            x14.paramsGenerator_ = y14;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(v14, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '比例');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((n14, o14) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((p14, q14) => {
                        if (q14) {
                            let r14 = new FunctionAreaPlaceholder(this, {}, undefined, p14, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 57, col: 9 });
                            ViewV2.create(r14);
                            let s14 = () => {
                                return {};
                            };
                            r14.paramsGenerator_ = s14;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(p14, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '清晰度');
                } });
        }, TabContent);
        TabContent.pop();
        Tabs.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], LandscapeSelectFuncArea.prototype, "styles", void 0);
__decorate([
    Local
], LandscapeSelectFuncArea.prototype, "tabBarStyleBgColor", void 0);
__decorate([
    Local
], LandscapeSelectFuncArea.prototype, "styleItems", void 0);
