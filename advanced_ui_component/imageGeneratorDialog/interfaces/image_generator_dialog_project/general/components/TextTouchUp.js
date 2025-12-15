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
import { AIGenerateImpl } from '../utils/AIGenerateImpl';
export class TextTouchUpComponent extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            NavDestination.create(() => {
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new TextTouchUp(this, {}, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TextTouchUp.ets", line: 24, col: 7 });
                            ViewV2.create(componentCall);
                            let paramsLambda = () => {
                                return {};
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {});
                        }
                    }, { name: "TextTouchUp" });
                }
            }, { moduleName: "__harDefaultModuleName__", pagePath: "" });
            NavDestination.title('文本润色');
            NavDestination.backgroundImageSize({
                width: '100%',
                height: '100%'
            });
            NavDestination.onBackPressed(() => {
                AIGenerateImpl.getInstance().cancelTextGenerateTask(2);
                return false;
            });
        }, NavDestination);
        NavDestination.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class TextTouchUp extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.originText = "";
        this.uiContext = this.getUIContext();
        this.uiContextMeasure = this.uiContext.getMeasureUtils();
        this.textSize = this.uiContextMeasure.measureTextSize({
            textContent: this.originText,
            fontSize: 13
        });
        this.stack = undefined;
        this.aiThinkText = '';
        this.aiResultText = '';
        this.isDisPlayThinkProcess = true;
        this.imgOrientation = ImageRotateOrientation.UP;
        this.symbolRes = { "id": 125835549, "type": 40000, params: ['sys.symbol.chevron_up_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.taskId = -1;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.originText = "";
        this.uiContext = this.getUIContext();
        this.uiContextMeasure = this.uiContext.getMeasureUtils();
        this.aiThinkText = '';
        this.aiResultText = '';
        this.isDisPlayThinkProcess = true;
        this.imgOrientation = ImageRotateOrientation.UP;
        this.symbolRes = { "id": 125835549, "type": 40000, params: ['sys.symbol.chevron_up_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.taskId = -1;
    }
    aboutToAppear() {
        this.stack = this.queryNavigationInfo()?.pathStack;
        AIGenerateImpl.getInstance().TextAIGenerate({
            onReady: () => {
            },
            onError: () => {
            },
            onResult: (result) => {
                if (result.reasoningContent) {
                    this.aiThinkText += result.reasoningContent;
                }
                if (result.content) {
                    this.aiResultText += result.content;
                }
            },
            onComplete: (result) => {
            },
        }).then((id) => {
            this.taskId = id;
        });
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.height(382);
            Column.width('100%');
            Column.margin({
                top: 16,
                right: 8
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.constraintSize({ maxHeight: 358 });
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.padding({
                bottom: 6,
                left: 16
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({
                direction: FlexDirection.Row,
                justifyContent: FlexAlign.Start,
                alignItems: ItemAlign.Start,
            });
            Flex.width('100%');
            Flex.height(40);
            Flex.padding({
                top: 8,
                bottom: 12,
                left: 8,
                right: 8
            });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('深度思考');
            Text.width(582);
            Text.height(20);
            Text.textAlign(TextAlign.Start);
            Text.fontColor("#000000");
            Text.fontSize(14);
            Text.fontWeight(500);
            Text.lineHeight(17);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.symbolRes);
            SymbolGlyph.width(20);
            SymbolGlyph.height(20);
            SymbolGlyph.onClick(() => {
                this.isDisPlayThinkProcess = !this.isDisPlayThinkProcess;
                if (this.isDisPlayThinkProcess) {
                    this.imgOrientation = ImageRotateOrientation.UP;
                    this.symbolRes = { "id": 125835549, "type": 40000, params: ['sys.symbol.chevron_up_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
                else {
                    this.imgOrientation = ImageRotateOrientation.DOWN;
                    this.symbolRes = { "id": 125832666, "type": 40000, params: ['sys.symbol.chevron_down'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
                }
            });
        }, SymbolGlyph);
        Flex.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.aiThinkText);
            Text.fontColor({ "id": 125830984, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize(14);
            Text.fontWeight(400);
            Text.lineHeight(17);
            Text.backgroundColor(Color.Transparent);
            Text.padding({
                left: 8,
                right: 8
            });
            Text.visibility(this.imgOrientation == ImageRotateOrientation.UP ? Visibility.Visible : Visibility.None);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.padding({
                top: 8,
                bottom: 8
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Divider.create();
            Divider.strokeWidth(0.5);
            Divider.color({ "id": 125831013, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Divider);
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.height(184);
            Column.padding({
                top: 8,
                bottom: 8,
                left: 16,
                right: 16
            });
            Column.borderRadius(16);
            Column.backgroundColor("#ffffffff");
            Column.shadow({
                radius: 18,
                offsetX: 0,
                offsetY: 4,
                fill: false,
                color: '#05ffffff'
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TextArea.create({ text: { value: this.aiResultText, changeEvent: newValue => { this.aiResultText = newValue; } } });
            TextArea.placeholderFont({ size: 14 });
            TextArea.fontColor('#e6000000');
            TextArea.fontSize(16);
            TextArea.fontWeight(500);
            TextArea.lineHeight(19);
            TextArea.backgroundColor("#ffffffff");
            TextArea.padding({
                top: 0,
                bottom: 0,
                left: 0,
                right: 0
            });
            TextArea.borderRadius(0);
        }, TextArea);
        Column.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('内容由API生成');
            Text.fontColor({ "id": 125830984, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize(12);
            Text.fontWeight(400);
            Text.lineHeight(14);
            Text.textAlign(TextAlign.Center);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel('使用润色结果');
            Button.width(448);
            Button.height(40);
            Button.fontSize(16);
            Button.fontWeight(500);
            Button.margin({
                top: 20,
                bottom: 16,
                left: 101,
                right: 101
            });
            Button.onClick(() => {
                if (this.stack) {
                    this.stack.pop(this.aiResultText);
                }
            });
        }, Button);
        Button.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], TextTouchUp.prototype, "originText", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "uiContext", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "uiContextMeasure", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "aiThinkText", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "aiResultText", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "isDisPlayThinkProcess", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "imgOrientation", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "symbolRes", void 0);
__decorate([
    Local
], TextTouchUp.prototype, "taskId", void 0);
