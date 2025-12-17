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
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
        this.limit = false;
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
