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
import { CanvasLayoutDirection, CanvasMode, ImageGenerateState } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { SelectFuncArea } from "./UserInteractiveArea";
import { GeneratingArea } from './CanvasGenerate';
import { calcAABB } from './ImageOperate';
import { ContinueOperateArea, HistoryArea } from './CanvasComplete';
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
        this.curCanvasMode = CanvasMode.DEFAULT;
        this.curSheetType = SheetType.CONTENT_COVER;
        this.curLayoutDirection = CanvasLayoutDirection.DEFAULT;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
        this.resetParam("imageInfoArr", (params && "imageInfoArr" in params) ? params.imageInfoArr : undefined);
        this.resetParam("styles", (params && "styles" in params) ? params.styles : undefined);
        this.resetParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
        this.resetConsumer("curCanvasMode", CanvasMode.DEFAULT);
        this.resetConsumer("curSheetType", SheetType.CONTENT_COVER);
        this.resetConsumer("curLayoutDirection", CanvasLayoutDirection.DEFAULT);
    }
    homeTitleBuilder(parent = null) {
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new HomeTitle(this, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 46, col: 5 });
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
                    if (this.curLayoutDirection === CanvasLayoutDirection.HORIZONTAL) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                If.create();
                                if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new HorizontalLayout(this, {
                                                        currentGenerateState: this.currentGenerateState,
                                                        imageInfoArr: this.imageInfoArr,
                                                        styles: this.styles,
                                                        userPrompt: this.userPrompt,
                                                        $currentGenerateState: value => { this.currentGenerateState = value; }
                                                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 57, col: 11 });
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
                                            }, { name: "HorizontalLayout" });
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
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    if (isInitialRender) {
                                        let componentCall = new VerticalLayout(this, {
                                            currentGenerateState: this.currentGenerateState,
                                            imageInfoArr: this.imageInfoArr,
                                            styles: this.styles,
                                            userPrompt: this.userPrompt,
                                            $currentGenerateState: value => { this.currentGenerateState = value; }
                                        }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 67, col: 9 });
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
                                }, { name: "VerticalLayout" });
                            }
                        });
                    }
                }, If);
                If.pop();
            }, { moduleName: "__harDefaultModuleName__", pagePath: "" });
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
__decorate([
    Consumer('globalCanvasMode')
], CanvasHome.prototype, "curCanvasMode", void 0);
__decorate([
    Consumer('globalSheetType')
], CanvasHome.prototype, "curSheetType", void 0);
__decorate([
    Consumer('globalLayoutDirection')
], CanvasHome.prototype, "curLayoutDirection", void 0);
class HorizontalLayout extends ViewV2 {
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
                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 138, col: 11 });
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
                                let componentCall = new SelectFuncArea(this, {
                                    imageInfoArr: this.imageInfoArr,
                                    imageMatrixArr: this.imageMatrixArr,
                                    styles: this.styles,
                                    setImgCounts: (count) => {
                                        this.imgCounts = count;
                                    }
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 144, col: 13 });
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
                        }, { name: "SelectFuncArea" });
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
                                let componentCall = new HistoryArea(this, { resultList: this.resultList }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 155, col: 13 });
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
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 162, col: 11 });
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
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 173, col: 11 });
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
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 181, col: 11 });
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
], HorizontalLayout.prototype, "styles", void 0);
__decorate([
    Param
], HorizontalLayout.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], HorizontalLayout.prototype, "$currentGenerateState", void 0);
__decorate([
    Param
], HorizontalLayout.prototype, "imageInfoArr", void 0);
__decorate([
    Local
], HorizontalLayout.prototype, "imageMatrixArr", void 0);
__decorate([
    Local
], HorizontalLayout.prototype, "imgCounts", void 0);
__decorate([
    Param
], HorizontalLayout.prototype, "userPrompt", void 0);
__decorate([
    Local
], HorizontalLayout.prototype, "resultList", void 0);
class VerticalLayout extends ViewV2 {
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
        this.initParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
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
        this.resetParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
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
            Column.create();
            Column.height('100%');
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            __Common__.create();
            __Common__.margin({ top: 16, bottom: 20 });
        }, __Common__);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new DoodleBoardArea(this, {
                        imageInfoArr: this.imageInfoArr,
                        imageMatrixArr: this.imageMatrixArr
                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 251, col: 7 });
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
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new SelectFuncArea(this, { imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr, styles: this.styles }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 258, col: 9 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        imageInfoArr: this.imageInfoArr,
                                        imageMatrixArr: this.imageMatrixArr,
                                        styles: this.styles
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr, styles: this.styles
                                });
                            }
                        }, { name: "SelectFuncArea" });
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
                                    }
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 263, col: 9 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        changeGenerateState: (state) => {
                                            this.$currentGenerateState(state);
                                        }
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
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
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 272, col: 9 });
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
        Column.pop();
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
], VerticalLayout.prototype, "styles", void 0);
__decorate([
    Param
], VerticalLayout.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], VerticalLayout.prototype, "$currentGenerateState", void 0);
__decorate([
    Param
], VerticalLayout.prototype, "imageInfoArr", void 0);
__decorate([
    Local
], VerticalLayout.prototype, "imageMatrixArr", void 0);
__decorate([
    Param
], VerticalLayout.prototype, "userPrompt", void 0);
