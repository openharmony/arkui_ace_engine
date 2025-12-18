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
import { ImageGenerateState } from '../types/Declaration';
import systemDateTime from "@ohos.systemDateTime";
export class GenerateProgress extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : undefined);
        this.changeCurrentState = "changeCurrentState" in params ? params.changeCurrentState : (state) => { };
        this.initParam("imageNumber", (params && "imageNumber" in params) ? params.imageNumber : 0);
        this.progressValue = 0;
        this.isGenerateSuccess = false;
        this.isGenerateTimeout = false;
        this.total = 100;
        this.timerCnt = 0;
        this.timerId = -1;
        this.goToBackGroundTimeStamp = 0;
        this.goToBackProgressValue = 0;
        this.estimatedTime = 0;
        this.isForeground = true;
        this.canvasGenerateProgressChangeCallback = undefined;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : undefined);
        this.changeCurrentState = "changeCurrentState" in params ? params.changeCurrentState : (state) => { };
        this.resetParam("imageNumber", (params && "imageNumber" in params) ? params.imageNumber : 0);
        this.progressValue = 0;
        this.isGenerateSuccess = false;
        this.isGenerateTimeout = false;
        this.resetMonitorsOnReuse();
    }
    currentGenerateStateChangeMonitor(monitor) {
        if (this.isForeground &&
            monitor.value('currentGenerateState')?.now === ImageGenerateState.BEFORE_GENERATED) {
            this.progressValue = this.total;
        }
    }
    getEstimatedTime(imageNumber) {
        let timeCntRet = [300, 300, 400, 500, 700];
        if (imageNumber < timeCntRet.length) {
            return timeCntRet[imageNumber];
        }
        return 300;
    }
    aboutToAppear() {
        this.createApplicationListener();
        this.createTimer();
    }
    aboutToDisappear() {
        this.clearApplicationListener();
        this.clearTimer();
    }
    createApplicationListener() {
        let that = this;
        this.canvasGenerateProgressChangeCallback = {
            onApplicationForeground() {
                let currentTimeStamp = systemDateTime.getTime();
                if (that.isGenerateSuccess) {
                    this.progressValue = that.total;
                }
                else if (that.estimatedTime > 0) {
                    let timeDiff = Math.floor((currentTimeStamp - that.goToBackGroundTimeStamp) / that.estimatedTime);
                    let progressValue = that.goToBackProgressValue + timeDiff;
                    if (progressValue >= that.total) {
                        that.progressValue = that.total - 1;
                    }
                    else {
                        that.progressValue = progressValue;
                    }
                    that.timerCnt += timeDiff;
                }
                that.isForeground = true;
            },
            onApplicationBackground() {
                that.goToBackGroundTimeStamp = systemDateTime.getTime();
                that.goToBackProgressValue = that.progressValue;
                that.isForeground = false;
            }
        };
        this.getUIContext()?.getHostContext()?.getApplicationContext()
            ?.on('applicationStateChange', this.canvasGenerateProgressChangeCallback);
    }
    clearApplicationListener() {
        if (this.canvasGenerateProgressChangeCallback) {
            this.getUIContext()?.getHostContext()?.getApplicationContext()
                ?.off('applicationStateChange', this.canvasGenerateProgressChangeCallback);
            this.canvasGenerateProgressChangeCallback = undefined;
        }
    }
    createTimer() {
        this.timerCnt = 0;
        this.estimatedTime = this.getEstimatedTime(this.imageNumber);
        this.timerId = setInterval(() => {
            if (this.isForeground) {
                if (this.progressValue == this.total) {
                    this.onSuccess();
                }
                else if (this.timerCnt >= 200) {
                    this.onTimeOut();
                }
                else if (this.progressValue < this.total - 1) {
                    this.progressValue++;
                }
                this.timerCnt++;
            }
        }, this.estimatedTime);
    }
    clearTimer() {
        if (this.timerId >= 0) {
            clearInterval((this.timerId));
        }
    }
    onSuccess() {
        this.clearTimer();
        this.clearApplicationListener();
        this.isGenerateSuccess = true;
        setTimeout(() => {
            this.changeCurrentState(ImageGenerateState.GENERATED);
        }, 300);
    }
    onTimeOut() {
        this.clearTimer();
        this.clearApplicationListener();
        this.isGenerateTimeout = true;
        this.progressValue = 0;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(150);
            Column.height(40);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.height('100%');
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(150);
            Stack.height(40);
            Stack.blur(20);
            Stack.borderRadius(20);
            Stack.clip(true);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Context.animation({
                duration: this.progressValue == this.total ? 400 : 150,
                curve: Curve.EaseOut,
                playMode: PlayMode.Normal
            });
            Stack.backgroundColor(Color.White);
            Stack.width((100 - this.progressValue) * 1.5);
            Stack.position({ right: 0 });
            Stack.height(40);
            Context.animation(null);
        }, Stack);
        Stack.pop();
        Stack.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.SpaceBetween);
            Row.width('100%');
            Row.height(22);
            Row.padding({
                left: 12,
                right: 12
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.isGenerateSuccess ? '已完成' : this.isGenerateTimeout ? `生成失败`
                : `AI生成中  ${this.progressValue} %`);
            Text.fontSize(14);
            Text.fontFamily("HarmonyHeiTi");
            Text.maxLines(1);
            Text.textOverflow({ overflow: TextOverflow.MARQUEE });
            Text.width(100);
        }, Text);
        Text.pop();
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (!this.isGenerateSuccess) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create({ "id": 125830347, "type": 20000, params: ['sys.media.ohos_ic_public_cancel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Image.width(22);
                        Image.height(22);
                        Image.onClick(() => {
                            if (!this.isGenerateSuccess) {
                                this.changeCurrentState(ImageGenerateState.CONFIGURATION);
                            }
                        });
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
        Row.pop();
        Stack.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("currentGenerateState" in params) {
            this.updateParam("currentGenerateState", params.currentGenerateState);
        }
        if ("imageNumber" in params) {
            this.updateParam("imageNumber", params.imageNumber);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], GenerateProgress.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], GenerateProgress.prototype, "changeCurrentState", void 0);
__decorate([
    Param
], GenerateProgress.prototype, "imageNumber", void 0);
__decorate([
    Local
], GenerateProgress.prototype, "progressValue", void 0);
__decorate([
    Local
], GenerateProgress.prototype, "isGenerateSuccess", void 0);
__decorate([
    Local
], GenerateProgress.prototype, "isGenerateTimeout", void 0);
__decorate([
    Monitor('currentGenerateState')
], GenerateProgress.prototype, "currentGenerateStateChangeMonitor", null);
export class MinimizeButton extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Circle });
            Button.backgroundColor(Color.White);
            Button.width(40);
            Button.height(40);
            Button.margin({ left: 8 });
            Button.onClick(() => {
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": 125832922, "type": 40000, params: ['sys.symbol.smal_window_playback'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.fontSize(21.62);
            SymbolGlyph.fontWeight(400);
        }, SymbolGlyph);
        Button.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class GeneratingArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : undefined);
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : undefined);
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
        }, Row);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new GenerateProgress(this, {
                        currentGenerateState: this.currentGenerateState,
                        changeCurrentState: this.changeGenerateState
                    }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasGenerate.ets", line: 211, col: 9 });
                    ViewV2.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            currentGenerateState: this.currentGenerateState,
                            changeCurrentState: this.changeGenerateState
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        currentGenerateState: this.currentGenerateState
                    });
                }
            }, { name: "GenerateProgress" });
        }
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new MinimizeButton(this, {}, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasGenerate.ets", line: 215, col: 9 });
                    ViewV2.create(componentCall);
                    let paramsLambda = () => {
                        return {};
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: "MinimizeButton" });
        }
        Row.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("currentGenerateState" in params) {
            this.updateParam("currentGenerateState", params.currentGenerateState);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], GeneratingArea.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], GeneratingArea.prototype, "changeGenerateState", void 0);
