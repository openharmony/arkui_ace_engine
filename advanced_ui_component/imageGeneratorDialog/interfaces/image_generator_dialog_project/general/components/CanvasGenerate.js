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

var __decorate = (this && this.__decorate) || function (r5, s5, t5, u5) {
    var v5 = arguments.length, w5 = v5 < 3 ? s5 : u5 === null ? u5 = Object.getOwnPropertyDescriptor(s5, t5) : u5, x5;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        w5 = Reflect.decorate(r5, s5, t5, u5);
    else
        for (var y5 = r5.length - 1; y5 >= 0; y5--)
            if (x5 = r5[y5])
                w5 = (v5 < 3 ? x5(w5) : v5 > 3 ? x5(s5, t5, w5) : x5(s5, t5)) || w5;
    return v5 > 3 && w5 && Object.defineProperty(s5, t5, w5), w5;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { ImageGenerateState } from '../types/Declaration';

const systemDateTime = requireNapi('systemDateTime');

export class GenerateProgress extends ViewV2 {
    constructor(k5, l5, m5, n5 = -1, o5, p5) {
        super(k5, n5, p5);
        this.initParam("currentGenerateState", (l5 && "currentGenerateState" in l5) ? l5.currentGenerateState : undefined);
        this.changeCurrentState = "changeCurrentState" in l5 ? l5.changeCurrentState : (q5) => { };
        this.initParam("imageNumber", (l5 && "imageNumber" in l5) ? l5.imageNumber : 0);
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
    resetStateVarsOnReuse(i5) {
        this.resetParam("currentGenerateState", (i5 && "currentGenerateState" in i5) ? i5.currentGenerateState : undefined);
        this.changeCurrentState = "changeCurrentState" in i5 ? i5.changeCurrentState : (j5) => { };
        this.resetParam("imageNumber", (i5 && "imageNumber" in i5) ? i5.imageNumber : 0);
        this.progressValue = 0;
        this.isGenerateSuccess = false;
        this.isGenerateTimeout = false;
        this.resetMonitorsOnReuse();
    }
    currentGenerateStateChangeMonitor(h5) {
        if (this.isForeground &&
            h5.value('currentGenerateState')?.now === ImageGenerateState.BEFORE_GENERATED) {
            this.progressValue = this.total;
        }
    }
    getEstimatedTime(f5) {
        let g5 = [300, 300, 400, 500, 700];
        if (f5 < g5.length) {
            return g5[f5];
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
        let b5 = this;
        this.canvasGenerateProgressChangeCallback = {
            onApplicationForeground() {
                let c5 = systemDateTime.getTime();
                if (b5.isGenerateSuccess) {
                    this.progressValue = b5.total;
                }
                else if (b5.estimatedTime > 0) {
                    let d5 = Math.floor((c5 - b5.goToBackGroundTimeStamp) / b5.estimatedTime);
                    let e5 = b5.goToBackProgressValue + d5;
                    if (e5 >= b5.total) {
                        b5.progressValue = b5.total - 1;
                    }
                    else {
                        b5.progressValue = e5;
                    }
                    b5.timerCnt += d5;
                }
                b5.isForeground = true;
            },
            onApplicationBackground() {
                b5.goToBackGroundTimeStamp = systemDateTime.getTime();
                b5.goToBackProgressValue = b5.progressValue;
                b5.isForeground = false;
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
        this.observeComponentCreation2((z4, a5) => {
            Column.create();
            Column.width(150);
            Column.height(40);
        }, Column);
        this.observeComponentCreation2((x4, y4) => {
            Stack.create();
            Stack.height('100%');
        }, Stack);
        this.observeComponentCreation2((v4, w4) => {
            Stack.create();
            Stack.width(150);
            Stack.height(40);
            Stack.blur(20);
            Stack.borderRadius(20);
            Stack.clip(true);
        }, Stack);
        this.observeComponentCreation2((r4, s4) => {
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
        this.observeComponentCreation2((p4, q4) => {
            Row.create();
            Row.justifyContent(FlexAlign.SpaceBetween);
            Row.width('100%');
            Row.height(22);
            Row.padding({
                left: 12,
                right: 12
            });
        }, Row);
        this.observeComponentCreation2((n4, o4) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((l4, m4) => {
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
        this.observeComponentCreation2((j4, k4) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((f4, g4) => {
            If.create();
            if (!this.isGenerateSuccess) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h4, i4) => {
                        Image.create({ "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_cancel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
    updateStateVars(e4) {
        if (e4 === undefined) {
            return;
        }
        if ("currentGenerateState" in e4) {
            this.updateParam("currentGenerateState", e4.currentGenerateState);
        }
        if ("imageNumber" in e4) {
            this.updateParam("imageNumber", e4.imageNumber);
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
    constructor(y3, z3, a4, b4 = -1, c4, d4) {
        super(y3, b4, d4);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(x3) {
    }
    initialRender() {
        this.observeComponentCreation2((v3, w3) => {
            Button.createWithChild({ type: ButtonType.Circle });
            Button.backgroundColor(Color.White);
            Button.width(40);
            Button.height(40);
            Button.margin({ left: 8 });
            Button.onClick(() => {
            });
        }, Button);
        this.observeComponentCreation2((t3, u3) => {
            SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.smal_window_playback'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
    constructor(m3, n3, o3, p3 = -1, q3, r3) {
        super(m3, p3, r3);
        this.initParam("currentGenerateState", (n3 && "currentGenerateState" in n3) ? n3.currentGenerateState : undefined);
        this.changeGenerateState = "changeGenerateState" in n3 ? n3.changeGenerateState : (s3) => { };
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(k3) {
        this.resetParam("currentGenerateState", (k3 && "currentGenerateState" in k3) ? k3.currentGenerateState : undefined);
        this.changeGenerateState = "changeGenerateState" in k3 ? k3.changeGenerateState : (l3) => { };
    }
    initialRender() {
        this.observeComponentCreation2((i3, j3) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((g3, h3) => {
            Row.create();
        }, Row);
        {
            this.observeComponentCreation2((c3, d3) => {
                if (d3) {
                    let e3 = new GenerateProgress(this, {
                        currentGenerateState: this.currentGenerateState,
                        changeCurrentState: this.changeGenerateState
                    }, undefined, c3, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasGenerate.ets", line: 219, col: 9 });
                    ViewV2.create(e3);
                    let f3 = () => {
                        return {
                            currentGenerateState: this.currentGenerateState,
                            changeCurrentState: this.changeGenerateState
                        };
                    };
                    e3.paramsGenerator_ = f3;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(c3, {
                        currentGenerateState: this.currentGenerateState
                    });
                }
            }, { name: "GenerateProgress" });
        }
        {
            this.observeComponentCreation2((y2, z2) => {
                if (z2) {
                    let a3 = new MinimizeButton(this, {}, undefined, y2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasGenerate.ets", line: 223, col: 9 });
                    ViewV2.create(a3);
                    let b3 = () => {
                        return {};
                    };
                    a3.paramsGenerator_ = b3;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(y2, {});
                }
            }, { name: "MinimizeButton" });
        }
        Row.pop();
        Column.pop();
    }
    updateStateVars(x2) {
        if (x2 === undefined) {
            return;
        }
        if ("currentGenerateState" in x2) {
            this.updateParam("currentGenerateState", x2.currentGenerateState);
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
