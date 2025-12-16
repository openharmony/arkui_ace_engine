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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { FunctionAreaPlaceholder, StyleSelectBuilder, UserInteractiveTabBarBuilder } from "./UserFunctionArea";
import { PhotoSelect } from "./PhotoSelect";
export class LandscapeSelectFuncArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.tabBarDefaultBgColor = 'rgba(0,0,0,0.05)';
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
        this.styleItems = [];
        this.initParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.initParam("imageMatrixArr", (params && "imageMatrixArr" in params) ? params.imageMatrixArr : undefined);
        this.selectedIndex = 0;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.tabBarStyleBgColor = this.tabBarDefaultBgColor;
        this.styleItems = [];
        this.resetParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.resetParam("imageMatrixArr", (params && "imageMatrixArr" in params) ? params.imageMatrixArr : undefined);
        this.selectedIndex = 0;
    }
    aboutToAppear() {
        for (let i = 0; this.styles && i < this.styles?.length; ++i) {
            this.styleItems.push({ name: this.styles[i].name, resourceAddr: this.styles[i].icon });
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Tabs.create({ index: this.selectedIndex });
            Tabs.barHeight(284);
            Tabs.scrollable(false);
            Tabs.vertical(true);
            Tabs.barPosition(BarPosition.End);
            Tabs.width(118);
            Tabs.height(386);
            Tabs.onChange((index) => {
                this.selectedIndex = index;
            });
            Tabs.onAnimationStart((index, targetIndex, event) => {
                if (index === targetIndex) {
                    return;
                }
                this.selectedIndex = targetIndex;
            });
        }, Tabs);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new PhotoSelect(this, { imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 40, col: 9 });
                            ViewV2.create(componentCall);
                            let paramsLambda = () => {
                                return {
                                    imageInfoArr: this.imageInfoArr,
                                    imageMatrixArr: this.imageMatrixArr
                                };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr
                            });
                        }
                    }, { name: "PhotoSelect" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, 0, '图像', { "id": 125836048, "type": 40000, params: ['sys.symbol.style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TabContent.create(() => {
                StyleSelectBuilder.bind(this)(this.styleItems);
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, 1, '风格', { "id": 125836048, "type": 40000, params: ['sys.media.ohos_image_style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new FunctionAreaPlaceholder(this, {}, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 50, col: 9 });
                            ViewV2.create(componentCall);
                            let paramsLambda = () => {
                                return {};
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, 2, '比例', { "id": 125836048, "type": 40000, params: ['sys.symbol.style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new FunctionAreaPlaceholder(this, {}, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 55, col: 9 });
                            ViewV2.create(componentCall);
                            let paramsLambda = () => {
                                return {};
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, 3, '清晰度', { "id": 125836048, "type": 40000, params: ['sys.symbol.style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                } });
        }, TabContent);
        TabContent.pop();
        Tabs.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("styles" in params) {
            this.updateParam("styles", params.styles);
        }
        if ("imageInfoArr" in params) {
            this.updateParam("imageInfoArr", params.imageInfoArr);
        }
        if ("imageMatrixArr" in params) {
            this.updateParam("imageMatrixArr", params.imageMatrixArr);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
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
__decorate([
    Provider('functionAreaSelectedIndex')
], LandscapeSelectFuncArea.prototype, "selectedIndex", void 0);
