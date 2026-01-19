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
import { Constants } from '../common/CommonConstants';
import { CanvasHome } from "./CanvasFramework";
import { TextTouchUpComponent } from "./TextTouchUp";
import window from "@ohos.window";
import { CanvasLayoutDirection, CanvasMode, LogTag } from '../types/Declaration';
import { WinSizeChangeCallbackManager } from '../utils/CallbackManagers';
export class ImageGeneratorDialog extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.stack = new NavPathStack();
        this.initParam("options", (params && "options" in params) ? params.options : undefined);
        this.width_ = 650;
        this.height_ = 560;
        this.MAX_IMAGE_COUNT = 4;
        this.imageInfoArr = [];
        this.stylesArr = [];
        this.userPrompt = '';
        this.curWindow = undefined;
        this.curCanvasMode = CanvasMode.DEFAULT;
        this.curSheetType = SheetType.CONTENT_COVER;
        this.curLayoutDirection = CanvasLayoutDirection.DEFAULT;
        this.updateCanvasLayoutProperties = (size) => {
            let breakpointPX = this.getUIContext().vp2px(Constants.CONTENT_COVER_DISPLAY_MIN_WIDTH);
            this.curSheetType = size.width >= breakpointPX ? SheetType.CONTENT_COVER : SheetType.BOTTOM;
            this.curLayoutDirection = size.width >= size.height ? CanvasLayoutDirection.HORIZONTAL : CanvasLayoutDirection.VERTICAL;
            if (this.curSheetType === SheetType.BOTTOM) {
                this.width_ = '100%';
                this.height_ = '100%';
            }
            else {
                this.width_ = this.curLayoutDirection === CanvasLayoutDirection.HORIZONTAL ? 650 : 480;
                this.height_ = 560;
            }
        };
        this.onWinSizeChangForAll = (size) => {
            WinSizeChangeCallbackManager.getOrCreateInstance().executeCallback(size);
        };
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("options", (params && "options" in params) ? params.options : undefined);
        this.width_ = 650;
        this.height_ = 560;
        this.imageInfoArr = [];
        this.stylesArr = [];
        this.userPrompt = '';
        this.curCanvasMode = CanvasMode.DEFAULT;
        this.curSheetType = SheetType.CONTENT_COVER;
        this.curLayoutDirection = CanvasLayoutDirection.DEFAULT;
    }
    initWinSizeChangeCallback() {
        try {
            this.curWindow = window.findWindow(this.getUIContext().getWindowName());
            this.curWindow.on('windowSizeChange', this.onWinSizeChangForAll);
            WinSizeChangeCallbackManager.getOrCreateInstance().addCallback(this.updateCanvasLayoutProperties);
            0;
        }
        catch (err) {
            console.info(LogTag, `get window failed, err: ${JSON.stringify(err)}`);
        }
    }
    initLayoutProperties() {
        try {
            if (this.curWindow) {
                let winRect = this.curWindow?.getWindowProperties().windowRect;
                this.updateCanvasLayoutProperties({ width: winRect.width, height: winRect.height });
            }
        }
        catch (e) {
            console.warn(LogTag, `init layout properties failed, err: ${JSON.stringify(e)}`);
        }
    }
    pageMap(name, parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (name === 'home') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new CanvasHome(this, {
                                    imageInfoArr: this.imageInfoArr,
                                    styles: this.options?.imageGenerationModel?.getModelSupportStyles(),
                                    userPrompt: this.userPrompt
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 82, col: 7 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        imageInfoArr: this.imageInfoArr,
                                        styles: this.options?.imageGenerationModel?.getModelSupportStyles(),
                                        userPrompt: this.userPrompt
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    imageInfoArr: this.imageInfoArr,
                                    styles: this.options?.imageGenerationModel?.getModelSupportStyles(),
                                    userPrompt: this.userPrompt
                                });
                            }
                        }, { name: "CanvasHome" });
                    }
                });
            }
            else if (name === 'textTouchUp') {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new TextTouchUpComponent(this, {}, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 88, col: 7 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {};
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: "TextTouchUpComponent" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
                });
            }
        }, If);
        If.pop();
    }
    initImageInfoArr() {
        if (this.options && this.options.images) {
            let initZIndex = 1;
            for (let index = 0; index < this.options.images.length && index < this.MAX_IMAGE_COUNT; index++) {
                if (this.options.images[index].zIndex === undefined) {
                    this.options.images[index].zIndex = initZIndex;
                    initZIndex++;
                }
                this.imageInfoArr.push(this.options.images[index]);
            }
            this.imageInfoArr.sort((a, b) => {
                return (a.zIndex ?? 0) - (b.zIndex ?? 0);
            });
        }
        while (this.imageInfoArr.length < this.MAX_IMAGE_COUNT) {
            this.imageInfoArr.push({ image: undefined, url: Constants.NOT_SELECTED_NAME });
        }
    }
    initUserPrompt() {
        if (this.options && this.options.content) {
            this.userPrompt = this.options.content.toString();
        }
    }
    aboutToAppear() {
        this.initImageInfoArr();
        this.initUserPrompt();
        for (let i = 0; i < this.MAX_IMAGE_COUNT; ++i) {
            this.stylesArr.push({ name: '' + i, icon: { "id": 125836048, "type": 40000, params: ['sys.symbol.style'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
        }
        this.initWinSizeChangeCallback();
        this.initLayoutProperties();
        this.stack.pushPath({ name: 'home' });
    }
    aboutToDisappear() {
        this.curWindow?.off('windowSizeChange', this.onWinSizeChangForAll);
        WinSizeChangeCallbackManager.getOrCreateInstance().destroy();
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Navigation.create(this.stack, { moduleName: "image_generator_dialog", pagePath: "", isUserCreateStack: true });
            Navigation.navDestination({ builder: this.pageMap.bind(this) });
            Navigation.hideNavBar(true);
            Navigation.height(this.height_);
            Navigation.width(this.width_);
            Navigation.borderRadius(32);
            Navigation.mode(NavigationMode.Stack);
            Navigation.clip(true);
            Navigation.alignSelf(ItemAlign.Center);
        }, Navigation);
        Navigation.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("options" in params) {
            this.updateParam("options", params.options);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ImageGeneratorDialog.prototype, "options", void 0);
__decorate([
    Local
], ImageGeneratorDialog.prototype, "width_", void 0);
__decorate([
    Local
], ImageGeneratorDialog.prototype, "height_", void 0);
__decorate([
    Local
], ImageGeneratorDialog.prototype, "imageInfoArr", void 0);
__decorate([
    Local
], ImageGeneratorDialog.prototype, "stylesArr", void 0);
__decorate([
    Local
], ImageGeneratorDialog.prototype, "userPrompt", void 0);
__decorate([
    Provider('globalCanvasMode')
], ImageGeneratorDialog.prototype, "curCanvasMode", void 0);
__decorate([
    Provider('globalSheetType')
], ImageGeneratorDialog.prototype, "curSheetType", void 0);
__decorate([
    Provider('globalLayoutDirection')
], ImageGeneratorDialog.prototype, "curLayoutDirection", void 0);
