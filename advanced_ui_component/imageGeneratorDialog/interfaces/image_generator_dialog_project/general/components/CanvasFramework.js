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
import { CanvasMode, ImageGenerateState } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { LandscapeSelectFuncArea } from "./UserInteractiveArea";
import { ContinueOperateArea, HistoryArea } from './CanvasComplete';
import { GeneratingArea } from './CanvasGenerate';
import { calcAABB } from './ImageOperate';
export class styleItem {
    constructor() {
        this.name = 'NA';
    }
}
export class CanvasHome extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
        this.initParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.initParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.initParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
        this.resetParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.resetParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.resetParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
    }
    homeTitleBuilder(parent = null) {
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new HomeTitle(this, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 43, col: 5 });
                    ViewV2.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            titleName: this.titleName,
                            currentGenerateState: this.currentGenerateState
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    });
                }
            }, { name: "HomeTitle" });
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            NavDestination.create(() => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    if (isInitialRender) {
                                        let componentCall = new LandscapeLayout(this, {
                                            currentGenerateState: this.currentGenerateState,
                                            imageInfoArr: this.imageInfoArr,
                                            styles: this.styles,
                                            userPrompt: this.userPrompt,
                                            $currentGenerateState: value => { this.currentGenerateState = value; }
                                        }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 52, col: 9 });
                                        ViewV2.create(componentCall);
                                        let paramsLambda = () => {
                                            return {
                                                currentGenerateState: this.currentGenerateState,
                                                imageInfoArr: this.imageInfoArr,
                                                styles: this.styles,
                                                userPrompt: this.userPrompt
                                            };
                                        };
                                        componentCall.paramsGenerator_ = paramsLambda;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(elmtId, {
                                            currentGenerateState: this.currentGenerateState,
                                            imageInfoArr: this.imageInfoArr,
                                            styles: this.styles,
                                            userPrompt: this.userPrompt
                                        });
                                    }
                                }, { name: "LandscapeLayout" });
                            }
                        });
                    }
                    else if (this.currentCanvasMode === CanvasMode.DOODLE_MODE) {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(2, () => {
                        });
                    }
                }, If);
                If.pop();
            }, { moduleName: "image_generator_dialog", pagePath: "" });
            NavDestination.hideBackButton(true);
            NavDestination.title({ builder: this.homeTitleBuilder.bind(this) });
        }, NavDestination);
        NavDestination.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("imageInfoArr" in params) {
            this.updateParam("imageInfoArr", params.imageInfoArr);
        }
        if ("styles" in params) {
            this.updateParam("styles", params.styles);
        }
        if ("userPrompt" in params) {
            this.updateParam("userPrompt", params.userPrompt);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], CanvasHome.prototype, "titleName", void 0);
__decorate([
    Local
], CanvasHome.prototype, "currentCanvasMode", void 0);
__decorate([
    Local
], CanvasHome.prototype, "currentGenerateState", void 0);
__decorate([
    Param
], CanvasHome.prototype, "imageInfoArr", void 0);
__decorate([
    Param
], CanvasHome.prototype, "styles", void 0);
__decorate([
    Param
], CanvasHome.prototype, "userPrompt", void 0);
class LandscapeLayout extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.initParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.$currentGenerateState = "$currentGenerateState" in params ? params.$currentGenerateState : (state) => {
        };
        this.initParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.imageMatrixArr = [[
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ]];
        this.imgCounts = 0;
        this.initParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
        this.resultList = [];
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.resetParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.$currentGenerateState = "$currentGenerateState" in params ? params.$currentGenerateState : (state) => {
        };
        this.resetParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.imageMatrixArr = [[
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ]];
        this.imgCounts = 0;
        this.resetParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
        this.resultList = [];
    }
    initImageMatrix() {
        let input = [];
        for (let i = 0; i < this.imageInfoArr.length; i++) {
            if (this.imageInfoArr[i].rect) {
                input.push(this.imageInfoArr[i]);
            }
        }
        let res = calcAABB(input, this.getUIContext().vp2px(386), this.getUIContext().vp2px(386));
        for (let i = 0; i < res.length; i++) {
            this.imageMatrixArr[i] = res[i];
        }
    }
    aboutToAppear() {
        this.initImageMatrix();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.scrollBar(BarState.Off);
            Scroll.height('100%');
            Scroll.width('100%');
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.margin({ top: 21, bottom: 28 });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.margin({ left: 69, right: 54 });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new DoodleBoardArea(this, {
                        imageInfoArr: this.imageInfoArr,
                        imageMatrixArr: this.imageMatrixArr
                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 125, col: 11 });
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
                        imageInfoArr: this.imageInfoArr,
                        imageMatrixArr: this.imageMatrixArr
                    });
                }
            }, { name: "DoodleBoardArea" });
        }
        __Common__.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ right: 16 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new LandscapeSelectFuncArea(this, {
                                    imageInfoArr: this.imageInfoArr,
                                    imageMatrixArr: this.imageMatrixArr,
                                    styles: this.styles,
                                    setImgCounts: (count) => {
                                        this.imgCounts = count;
                                    }
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 131, col: 13 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        imageInfoArr: this.imageInfoArr,
                                        imageMatrixArr: this.imageMatrixArr,
                                        styles: this.styles,
                                        setImgCounts: (count) => {
                                            this.imgCounts = count;
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    imageInfoArr: this.imageInfoArr,
                                    imageMatrixArr: this.imageMatrixArr,
                                    styles: this.styles
                                });
                            }
                        }, { name: "LandscapeSelectFuncArea" });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.GENERATED) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ right: 16 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new HistoryArea(this, { resultList: this.resultList }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 142, col: 13 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        resultList: this.resultList
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    resultList: this.resultList
                                });
                            }
                        }, { name: "HistoryArea" });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ bottom: 14 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new TextInputArea(this, {
                                    changeGenerateState: (state) => {
                                        this.$currentGenerateState(state);
                                    },
                                    imgCounts: this.imgCounts,
                                    userPrompt: this.userPrompt
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 149, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        changeGenerateState: (state) => {
                                            this.$currentGenerateState(state);
                                        },
                                        imgCounts: this.imgCounts,
                                        userPrompt: this.userPrompt
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    imgCounts: this.imgCounts,
                                    userPrompt: this.userPrompt
                                });
                            }
                        }, { name: "TextInputArea" });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.GENERATING ||
                this.currentGenerateState === ImageGenerateState.BEFORE_GENERATED) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new GeneratingArea(this, {
                                    currentGenerateState: this.currentGenerateState,
                                    changeGenerateState: (state) => {
                                        this.$currentGenerateState(state);
                                    }
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 160, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        currentGenerateState: this.currentGenerateState,
                                        changeGenerateState: (state) => {
                                            this.$currentGenerateState(state);
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    currentGenerateState: this.currentGenerateState
                                });
                            }
                        }, { name: "GeneratingArea" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.GENERATED) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ bottom: 14 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new ContinueOperateArea(this, {
                                    currentGenerateState: this.currentGenerateState,
                                    changeGenerateState: (state) => {
                                        this.$currentGenerateState(state);
                                    }
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 168, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        currentGenerateState: this.currentGenerateState,
                                        changeGenerateState: (state) => {
                                            this.$currentGenerateState(state);
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    currentGenerateState: this.currentGenerateState
                                });
                            }
                        }, { name: "ContinueOperateArea" });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
        Scroll.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("styles" in params) {
            this.updateParam("styles", params.styles);
        }
        if ("currentGenerateState" in params) {
            this.updateParam("currentGenerateState", params.currentGenerateState);
        }
        if ("imageInfoArr" in params) {
            this.updateParam("imageInfoArr", params.imageInfoArr);
        }
        if ("userPrompt" in params) {
            this.updateParam("userPrompt", params.userPrompt);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], LandscapeLayout.prototype, "styles", void 0);
__decorate([
    Param
], LandscapeLayout.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], LandscapeLayout.prototype, "$currentGenerateState", void 0);
__decorate([
    Param
], LandscapeLayout.prototype, "imageInfoArr", void 0);
__decorate([
    Local
], LandscapeLayout.prototype, "imageMatrixArr", void 0);
__decorate([
    Local
], LandscapeLayout.prototype, "imgCounts", void 0);
__decorate([
    Param
], LandscapeLayout.prototype, "userPrompt", void 0);
__decorate([
    Local
], LandscapeLayout.prototype, "resultList", void 0);
