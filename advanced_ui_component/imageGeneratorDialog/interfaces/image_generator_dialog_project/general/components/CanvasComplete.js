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
export class ResultImageShowArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("pixelMap", (params && "pixelMap" in params) ? params.pixelMap : undefined);
        this.imageScale = 1.0;
        this.minScale = 1.0;
        this.maxScale = 4.0;
        this.offsetX = 0;
        this.offsetY = 0;
        this.initialScale = 1.0;
        this.initialOffsetX = 0;
        this.initialOffsetY = 0;
        this.isPinching = false;
        this.focusX = 0;
        this.focusY = 0;
        this.focalPointX = 0;
        this.focalPointY = 0;
        this.imageWidth = 386;
        this.imageHeight = 386;
        this.containerWidth = 386;
        this.containerHeight = 386;
        this.imageAspectRatio = 1.0;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("pixelMap", (params && "pixelMap" in params) ? params.pixelMap : undefined);
        this.imageScale = 1.0;
        this.offsetX = 0;
        this.offsetY = 0;
        this.initialScale = 1.0;
        this.initialOffsetX = 0;
        this.initialOffsetY = 0;
        this.isPinching = false;
        this.focusX = 0;
        this.focusY = 0;
        this.focalPointX = 0;
        this.focalPointY = 0;
        this.imageWidth = 386;
        this.imageHeight = 386;
        this.containerWidth = 386;
        this.containerHeight = 386;
        this.imageAspectRatio = 1.0;
    }
    aboutToAppear() {
        this.containerWidth = 386;
        this.containerHeight = 386;
    }
    snapScaleToBounds() {
        if (this.imageScale < this.minScale) {
            this.imageScale = this.minScale;
        }
        else if (this.imageScale > this.maxScale) {
            this.imageScale = this.maxScale;
        }
    }
    snapOffsetToBounds() {
        if (this.imageWidth * this.imageScale < this.containerWidth) {
            this.offsetX = 0;
        }
        else {
            let maxOffsetX = Math.max(0, (this.imageWidth * this.imageScale) / 2 - this.containerWidth / 2);
            if (this.offsetX > maxOffsetX) {
                this.offsetX = maxOffsetX;
            }
            else if (this.offsetX < -maxOffsetX) {
                this.offsetX = -maxOffsetX;
            }
        }
        if (this.imageHeight * this.imageScale < this.containerHeight) {
            this.offsetY = 0;
        }
        else {
            let maxOffsetY = Math.max(0, (this.imageHeight * this.imageScale) / 2 - this.containerHeight / 2);
            if (this.offsetY > maxOffsetY) {
                this.offsetY = maxOffsetY;
            }
            else if (this.offsetY < -maxOffsetY) {
                this.offsetY = -maxOffsetY;
            }
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.width(this.containerWidth);
            Stack.height(this.containerHeight);
            Stack.borderRadius(24);
            Stack.clip(true);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.justifyContent(FlexAlign.Center);
            Column.alignItems(HorizontalAlign.Center);
            Column.backgroundColor('#FFFFFF');
            Column.borderRadius(24);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.pixelMap);
            Image.objectFit(ImageFit.Contain);
            Image.scale({ x: this.imageScale, y: this.imageScale });
            Image.translate({ x: this.offsetX, y: this.offsetY });
            Gesture.create(GesturePriority.Low);
            TapGesture.create({ count: 2 });
            TapGesture.onAction((event) => {
                if (event.fingerList && event.fingerList.length > 0) {
                    let tapX = event.fingerList[0].localX - this.containerWidth / 2;
                    let tapY = event.fingerList[0].localY - this.containerHeight / 2;
                    if (this.imageScale === this.minScale) {
                        let oldOffsetX = this.offsetX;
                        let oldOffsetY = this.offsetY;
                        let oldScale = this.imageScale;
                        let scaleRatio = 2.0 / oldScale;
                        this.imageScale = 2.0;
                        this.offsetX = tapX - (tapX - oldOffsetX) * scaleRatio;
                        this.offsetY = tapY - (tapY - oldOffsetY) * scaleRatio;
                        this.snapOffsetToBounds();
                    }
                    else {
                        this.imageScale = this.minScale;
                        this.offsetX = 0;
                        this.offsetY = 0;
                    }
                }
            });
            TapGesture.pop();
            Gesture.pop();
            Gesture.create(GesturePriority.Low);
            PinchGesture.create();
            PinchGesture.onActionStart((event) => {
                this.isPinching = true;
                this.initialScale = this.imageScale;
                this.initialOffsetX = this.offsetX;
                this.initialOffsetY = this.offsetY;
                if (event.fingerList && event.fingerList.length >= 2) {
                    let centerX = (event.fingerList[0].localX + event.fingerList[1].localX) / 2;
                    let centerY = (event.fingerList[0].localY + event.fingerList[1].localY) / 2;
                    this.focusX = centerX - this.containerWidth / 2;
                    this.focusY = centerY - this.containerHeight / 2;
                    this.focalPointX = (this.focusX - this.initialOffsetX) / this.initialScale;
                    this.focalPointY = (this.focusY - this.initialOffsetY) / this.initialScale;
                }
            });
            PinchGesture.onActionUpdate((event) => {
                if (event.scale) {
                    let newScale = this.initialScale * event.scale;
                    this.imageScale = newScale;
                    this.offsetX = this.focusX - this.focalPointX * this.imageScale;
                    this.offsetY = this.focusY - this.focalPointY * this.imageScale;
                }
            });
            PinchGesture.onActionEnd(() => {
                this.isPinching = false;
                this.snapScaleToBounds();
                this.snapOffsetToBounds();
                this.initialOffsetX = this.offsetX;
                this.initialOffsetY = this.offsetY;
            });
            PinchGesture.pop();
            Gesture.pop();
            Gesture.create(GesturePriority.Low);
            PanGesture.create({ direction: PanDirection.All });
            PanGesture.onActionStart(() => {
                if (!this.isPinching) {
                    this.initialOffsetX = this.offsetX;
                    this.initialOffsetY = this.offsetY;
                }
            });
            PanGesture.onActionUpdate((event) => {
                if (!this.isPinching && event.offsetX !== undefined && event.offsetY !== undefined) {
                    let adjustedOffsetX = event.offsetX * this.imageScale;
                    let adjustedOffsetY = event.offsetY * this.imageScale;
                    this.offsetX = this.initialOffsetX + adjustedOffsetX;
                    this.offsetY = this.initialOffsetY + adjustedOffsetY;
                }
            });
            PanGesture.onActionEnd(() => {
                if (!this.isPinching) {
                    this.snapOffsetToBounds();
                }
            });
            PanGesture.pop();
            Gesture.pop();
        }, Image);
        Column.pop();
        Stack.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("pixelMap" in params) {
            this.updateParam("pixelMap", params.pixelMap);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ResultImageShowArea.prototype, "pixelMap", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "imageScale", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "offsetX", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "offsetY", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "initialScale", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "initialOffsetX", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "initialOffsetY", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "isPinching", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "focusX", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "focusY", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "focalPointX", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "focalPointY", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "imageWidth", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "imageHeight", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "containerWidth", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "containerHeight", void 0);
__decorate([
    Local
], ResultImageShowArea.prototype, "imageAspectRatio", void 0);
function __Text__iconFontStyle() {
    Text.fontFamily("HarmonyHeiTi");
    Text.fontColor("#000000");
    Text.fontSize(10);
    Text.fontWeight(400);
    Text.lineHeight(12);
    Text.textAlign(TextAlign.Center);
}
export class ContinueOperateArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : undefined);
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => {
        };
        this.limit = false;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : undefined);
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => {
        };
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.SpaceBetween);
            Row.width(618);
            Row.height(58);
            Row.margin({
                top: 18
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(123);
            Column.height(42);
            Column.alignItems(HorizontalAlign.Center);
            Column.onClick(() => {
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836326, "type": 20000, params: ['sys.media.reset_light'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(24);
            Image.height(24);
            Image.opacity(this.limit ? 0.3 : 1);
            Image.margin({
                bottom: 4
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('重新编辑');
            __Text__iconFontStyle();
            Text.fontColor(this.limit ? "#808080" : "#000000");
        }, Text);
        Text.pop();
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(123);
            Column.height(42);
            Column.alignItems(HorizontalAlign.Center);
            Column.onClick(() => {
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836317, "type": 20000, params: ['sys.media.creat_light'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(24);
            Image.height(24);
            Image.opacity(this.limit ? 0.3 : 1);
            Image.margin({
                bottom: 4
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('继续创作');
            __Text__iconFontStyle();
            Text.fontColor(this.limit ? "#808080" : "#000000");
        }, Text);
        Text.pop();
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(123);
            Column.height(42);
            Column.alignItems(HorizontalAlign.Center);
            Column.onClick(() => {
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836320, "type": 20000, params: ['sys.media.download_light'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(24);
            Image.height(24);
            Image.margin({
                bottom: 4
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('下载');
            __Text__iconFontStyle();
        }, Text);
        Text.pop();
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(123);
            Column.height(42);
            Column.alignItems(HorizontalAlign.Center);
            Column.onClick(() => {
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836330, "type": 20000, params: ['sys.media.stickers_light'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(24);
            Image.height(24);
            Image.margin({
                bottom: 4
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('添加至贴纸');
            __Text__iconFontStyle();
        }, Text);
        Text.pop();
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(123);
            Column.height(42);
            Column.alignItems(HorizontalAlign.Center);
            Column.onClick(() => {
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836314, "type": 20000, params: ['sys.media.add_to_text_light'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width(24);
            Image.height(24);
            Image.margin({
                bottom: 4
            });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('插入笔记');
            __Text__iconFontStyle();
        }, Text);
        Text.pop();
        Column.pop();
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
], ContinueOperateArea.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], ContinueOperateArea.prototype, "changeGenerateState", void 0);
export class HistoryArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("resultList", (params && "resultList" in params) ? params.resultList : []);
        this.selectIndex = 0;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("resultList", (params && "resultList" in params) ? params.resultList : []);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.scrollBar(BarState.Off);
            Scroll.scrollable(ScrollDirection.Vertical);
            Scroll.width(79);
            Scroll.height(386);
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: 12 });
            Column.width(79);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
                const item = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Column.create();
                    Column.width(60);
                    Column.height(60);
                    Column.padding(2);
                    Column.borderRadius(11);
                    Column.clip(true);
                    Column.linearGradient(this.selectIndex == index ? {
                        angle: 90,
                        direction: GradientDirection.Left,
                        colors: [['#44D1FF', 0.0], ['#A479FF', 0.52], ['#FF678C', 1.0]],
                    } : undefined);
                    Column.onClick(() => {
                        this.selectIndex = index;
                    });
                }, Column);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Image.create(item);
                    Image.id('resultImage' + index);
                    Image.width(56);
                    Image.height(56);
                    Image.borderRadius(10);
                }, Image);
                Column.pop();
            };
            this.forEachUpdateFunction(elmtId, this.resultList, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("resultList" in params) {
            this.updateParam("resultList", params.resultList);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], HistoryArea.prototype, "resultList", void 0);
