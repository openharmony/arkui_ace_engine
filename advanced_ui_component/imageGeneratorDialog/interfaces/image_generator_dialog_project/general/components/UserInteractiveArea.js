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

var __decorate = (this && this.__decorate) || function (s30, t30, u30, v30) {
    var w30 = arguments.length, x30 = w30 < 3 ? t30 : v30 === null ? v30 = Object.getOwnPropertyDescriptor(t30, u30) : v30, y30;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        x30 = Reflect.decorate(s30, t30, u30, v30);
    else
        for (var z30 = s30.length - 1; z30 >= 0; z30--)
            if (y30 = s30[z30])
                x30 = (w30 < 3 ? y30(x30) : w30 > 3 ? y30(t30, u30, x30) : y30(t30, u30)) || x30;
    return w30 > 3 && x30 && Object.defineProperty(t30, u30, x30), x30;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { FunctionAreaPlaceholder, StyleSelectBuilder, StyleSelectTabBarBuilder, UserInteractiveTabBarBuilder } from "./UserFunctionArea";
import { PhotoSelect } from "./PhotoSelect";
export class LandscapeSelectFuncArea extends ViewV2 {
    constructor(m30, n30, o30, p30 = -1, q30, r30) {
        super(m30, p30, r30);
        this.styles = undefined;
        this.tabBarDefaultBgColor = 'rgba(0,0,0,0.05)';
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
        this.styleItems = [];
        this.initParam("imageInfoArr", (n30 && "imageInfoArr" in n30) ? n30.imageInfoArr : undefined);
        this.initParam("imageMatrixArr", (n30 && "imageMatrixArr" in n30) ? n30.imageMatrixArr : undefined);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(l30) {
        this.styles = undefined;
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
        this.styleItems = [];
        this.resetParam("imageInfoArr", (l30 && "imageInfoArr" in l30) ? l30.imageInfoArr : undefined);
        this.resetParam("imageMatrixArr", (l30 && "imageMatrixArr" in l30) ? l30.imageMatrixArr : undefined);
    }
    aboutToAppear() {
        for (let q6 = 0; this.styles && q6 < this.styles?.length; ++q6) {
            this.styleItems.push({ name: this.styles[q6].name, resourceAddr: this.styles[q6].icon });
        }
    }
    initialRender() {
        this.observeComponentCreation2((j30, k30) => {
            Tabs.create();
            Tabs.barHeight(284);
            Tabs.scrollable(false);
            Tabs.vertical(true);
            Tabs.barPosition(BarPosition.End);
            Tabs.width(118);
            Tabs.height(386);
        }, Tabs);
        this.observeComponentCreation2((d30, e30) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((f30, g30) => {
                        if (g30) {
                            let h30 = new PhotoSelect(this, { imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr }, undefined, f30, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 38, col: 9 });
                            ViewV2.create(h30);
                            let i30 = () => {
                                return {
                                    imageInfoArr: this.imageInfoArr,
                                    imageMatrixArr: this.imageMatrixArr
                                };
                            };
                            h30.paramsGenerator_ = i30;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(f30, {
                                imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr
                            });
                        }
                    }, { name: "PhotoSelect" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '图像');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((x29, y29) => {
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
        this.observeComponentCreation2((r29, s29) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((t29, u29) => {
                        if (u29) {
                            let v29 = new FunctionAreaPlaceholder(this, {}, undefined, t29, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 54, col: 9 });
                            ViewV2.create(v29);
                            let w29 = () => {
                                return {};
                            };
                            v29.paramsGenerator_ = w29;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(t29, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '比例');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((l29, m29) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((n29, o29) => {
                        if (o29) {
                            let p29 = new FunctionAreaPlaceholder(this, {}, undefined, n29, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 59, col: 9 });
                            ViewV2.create(p29);
                            let q29 = () => {
                                return {};
                            };
                            p29.paramsGenerator_ = q29;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(n29, {});
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
    updateStateVars(k29) {
        if (k29 === undefined) {
            return;
        }
        if ("imageInfoArr" in k29) {
            this.updateParam("imageInfoArr", k29.imageInfoArr);
        }
        if ("imageMatrixArr" in k29) {
            this.updateParam("imageMatrixArr", k29.imageMatrixArr);
        }
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
__decorate([
    Param
], LandscapeSelectFuncArea.prototype, "imageInfoArr", void 0);
__decorate([
    Param
], LandscapeSelectFuncArea.prototype, "imageMatrixArr", void 0);
