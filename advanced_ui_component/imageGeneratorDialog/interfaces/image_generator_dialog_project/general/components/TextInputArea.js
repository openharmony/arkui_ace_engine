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
import { ImageGenerateState } from "../types/Declaration";
import { AIGenerateOptions } from '../utils/AIGenerateOptions';
export class TextInputArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
        this.isTextEdit = false;
        this.inputText = '';
        this.userPrompt = '';
        this.inputController = new TextAreaController();
        this.textAreaPadding = 12;
        this.setMaxLines = 8;
        this.originText = "";
        this.uiContext = this.getUIContext();
        this.uiContextMeasure = this.uiContext.getMeasureUtils();
        this.textSize = this.uiContextMeasure.measureTextSize({
            textContent: this.originText,
            fontSize: 16
        });
        this.textMaxLines = 1;
        this.textOverflow = TextOverflow.Ellipsis;
        this.patchesStr = '带白色描边的贴纸效果';
        this.keepLayoutStr = '保持输入图形的位置关系';
        this.isSelectedPatches = false;
        this.isClickKeepLayout = false;
        this.inputHeight = 45;
        this.imgCounts = 2;
        this.isEnableTouchUp = false;
        this.isShowTouchUp = false;
        this.stack = undefined;
        this.updateInputText = '';
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
        this.isTextEdit = false;
        this.inputText = '';
        this.userPrompt = '';
        this.inputController = new TextAreaController();
        this.originText = "";
        this.uiContext = this.getUIContext();
        this.uiContextMeasure = this.uiContext.getMeasureUtils();
        this.textMaxLines = 1;
        this.textOverflow = TextOverflow.Ellipsis;
        this.isSelectedPatches = false;
        this.isClickKeepLayout = false;
        this.inputHeight = 45;
        this.imgCounts = 2;
        this.isEnableTouchUp = false;
        this.isShowTouchUp = false;
        this.stack = undefined;
        this.updateInputText = '';
        this.resetMonitorsOnReuse();
    }
    watchKeepLayout(monitor) {
        if (this.imgCounts <= 1) {
            this.isClickKeepLayout = false;
            if (this.inputText.includes(this.keepLayoutStr)) {
                let str = this.inputText.replace(this.keepLayoutStr + '，', "");
                this.inputText = str;
            }
        }
        if (this.isClickKeepLayout && !this.inputText.includes(this.keepLayoutStr)) {
            this.inputText = this.keepLayoutStr + '，' + this.inputText;
        }
        else if (!this.isClickKeepLayout && this.inputText.includes(this.keepLayoutStr)) {
            let replaceStr = this.inputText.includes(this.keepLayoutStr + '，') ? this.keepLayoutStr + '，' : this.keepLayoutStr;
            let str = this.inputText.replace(replaceStr, "");
            this.inputText = str;
        }
        if (this.isSelectedPatches && !this.inputText.includes(this.patchesStr)) {
            if (this.inputText.includes(this.keepLayoutStr)) {
                let index = this.inputText.indexOf(this.keepLayoutStr);
                let part1 = this.inputText.slice(0, index + this.keepLayoutStr.length);
                let part2 = this.inputText.slice(index + this.keepLayoutStr.length);
                this.inputText = part1.concat('，' + this.patchesStr).concat(part2);
            }
            else {
                this.inputText = this.patchesStr + '，' + this.inputText;
            }
        }
        else if (!this.isSelectedPatches && this.inputText.includes(this.patchesStr)) {
            let replaceStr = this.inputText.includes(this.patchesStr + '，') ? this.patchesStr + '，' : this.patchesStr;
            let str = this.inputText.replace(replaceStr, "");
            this.inputText = str;
        }
        if (this.updateInputText.length != 0) {
            this.inputText = this.updateInputText;
            this.updateInputText = '';
        }
    }
    watchUserPromptChange(monitor) {
        this.inputText = this.userPrompt;
    }
    aboutToAppear() {
        this.inputText = this.userPrompt;
        this.stack = this.queryNavigationInfo()?.pathStack;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                left: 16,
                right: 16
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 8 });
            Row.width('100%');
            Row.height(28);
            Row.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 4 });
            Row.padding({
                top: 6,
                bottom: 6,
                left: 12,
                right: 12
            });
            Row.borderRadius(20);
            Row.backgroundColor(this.isClickKeepLayout ? { "id": 125831004, "type": 10001, params: ['sys.color.comp_background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.visibility((this.imgCounts > 1 && this.isTextEdit) ? Visibility.Visible : Visibility.None);
            Row.onClick(() => {
                this.isClickKeepLayout = !this.isClickKeepLayout;
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836321, "type": 20000, params: ['sys.media.maintain_layout'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width('16vp');
            Image.height('16vp');
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('保持布局');
            Text.height('100%');
            Text.fontSize(12);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 4 });
            Row.padding({
                top: 6,
                bottom: 6,
                left: 12,
                right: 12
            });
            Row.borderRadius(20);
            Row.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.enabled(this.isEnableTouchUp);
            Row.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
            Row.onClick(() => {
                this.isShowTouchUp = true;
                this.inputController.stopEditing();
                AIGenerateOptions.getInstance().updateUserPrompt(this.inputText);
                if (this.stack) {
                    this.stack.pushPath({
                        name: 'textTouchUp', onPop: (popInfo) => {
                            this.inputText = popInfo.result.toString();
                        }
                    });
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": 125835100, "type": 40000, params: ['sys.symbol.AI_pencil'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('文本润色');
            Text.height('100%');
            Text.fontSize(12);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 4 });
            Row.padding({
                top: 6,
                bottom: 6,
                left: 12,
                right: 12
            });
            Row.borderRadius(20);
            Row.backgroundColor(this.isSelectedPatches ? { "id": 125831004, "type": 10001, params: ['sys.color.comp_background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
            Row.onClick(() => {
                this.isSelectedPatches = !this.isSelectedPatches;
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": 125831455, "type": 40000, params: ['sys.symbol.stickers'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('贴纸效果');
            Text.height('100%');
            Text.fontSize(12);
        }, Text);
        Text.pop();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 12 });
            Row.width('100%');
            Row.alignItems(VerticalAlign.Bottom);
            Row.padding({
                top: 12,
                bottom: 12
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.height(this.inputHeight);
            Column.width(510);
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TextArea.create({ placeholder: '描述你想要创作的内容', text: { value: this.inputText, changeEvent: newValue => { this.inputText = newValue; } }, controller: this.inputController });
            TextArea.padding({ top: this.textAreaPadding, bottom: this.textAreaPadding });
            TextArea.constraintSize({
                maxHeight: this.textAreaPadding * 2 +
                    this.setMaxLines * this.getUIContext().px2vp(Number(this.textSize.height))
            });
            TextArea.placeholderFont({ size: 16 });
            TextArea.textAlign(TextAlign.Start);
            TextArea.backgroundColor(Color.Transparent);
            TextArea.maxLength(600);
            TextArea.maxLines(this.textMaxLines);
            TextArea.textOverflow(this.textOverflow);
            TextArea.barState(BarState.On);
            TextArea.onChange((value) => {
                this.inputText = value;
                this.isEnableTouchUp = this.inputText.length > 0 ? true : false;
                if (!this.inputText.includes(this.keepLayoutStr)) {
                    this.isClickKeepLayout = false;
                }
                else if (this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                    this.isClickKeepLayout = true;
                }
                if (!this.inputText.includes(this.patchesStr)) {
                    this.isSelectedPatches = false;
                }
                else {
                    this.isSelectedPatches = true;
                }
            });
            TextArea.onClick((event) => {
                if (!this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                    this.inputText = this.keepLayoutStr + '，' + this.inputText;
                    this.isClickKeepLayout = true;
                }
            });
            TextArea.onEditChange((isEditing) => {
                this.isTextEdit = isEditing;
                if (isEditing) {
                    this.textMaxLines = 0;
                    this.textOverflow = TextOverflow.None;
                    this.inputHeight = 'auto';
                    this.getUIContext().setKeyboardAvoidMode(2);
                }
                else {
                    this.textMaxLines = 1;
                    this.textOverflow = TextOverflow.Ellipsis;
                    this.inputHeight = 45;
                    this.getUIContext().setKeyboardAvoidMode(0);
                }
            });
        }, TextArea);
        Column.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
            Column.height(40);
            Column.width(96);
            Column.onClick(() => {
                this.changeGenerateState(ImageGenerateState.GENERATING);
            });
        }, Column);
        Column.pop();
        Row.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Event
], TextInputArea.prototype, "changeGenerateState", void 0);
__decorate([
    Local
], TextInputArea.prototype, "isTextEdit", void 0);
__decorate([
    Local
], TextInputArea.prototype, "inputText", void 0);
__decorate([
    Local
], TextInputArea.prototype, "userPrompt", void 0);
__decorate([
    Local
], TextInputArea.prototype, "inputController", void 0);
__decorate([
    Local
], TextInputArea.prototype, "originText", void 0);
__decorate([
    Local
], TextInputArea.prototype, "uiContext", void 0);
__decorate([
    Local
], TextInputArea.prototype, "uiContextMeasure", void 0);
__decorate([
    Local
], TextInputArea.prototype, "textMaxLines", void 0);
__decorate([
    Local
], TextInputArea.prototype, "textOverflow", void 0);
__decorate([
    Local
], TextInputArea.prototype, "isSelectedPatches", void 0);
__decorate([
    Local
], TextInputArea.prototype, "isClickKeepLayout", void 0);
__decorate([
    Local
], TextInputArea.prototype, "inputHeight", void 0);
__decorate([
    Local
], TextInputArea.prototype, "imgCounts", void 0);
__decorate([
    Local
], TextInputArea.prototype, "isEnableTouchUp", void 0);
__decorate([
    Local
], TextInputArea.prototype, "isShowTouchUp", void 0);
__decorate([
    Local
], TextInputArea.prototype, "stack", void 0);
__decorate([
    Local
], TextInputArea.prototype, "updateInputText", void 0);
__decorate([
    Monitor('imgCounts', 'isClickKeepLayout', 'updateInputText', 'isSelectedPatches')
], TextInputArea.prototype, "watchKeepLayout", null);
__decorate([
    Monitor('userPrompt')
], TextInputArea.prototype, "watchUserPromptChange", null);
