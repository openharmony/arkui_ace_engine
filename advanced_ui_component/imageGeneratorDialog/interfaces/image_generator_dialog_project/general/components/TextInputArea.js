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
import { CanvasLayoutDirection, ImageGenerateState } from "../types/Declaration";
import { AIGenerateOptions } from '../utils/AIGenerateOptions';
const textBaseMaxLength = 280;
export class TextInputArea extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
        this.isTextEdit = false;
        this.inputText = '';
        this.initParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
        this.inputController = new TextAreaController();
        this.setMaxLines = 7;
        this.originText = '';
        this.uiContext = this.getUIContext();
        this.uiContextMeasure = this.uiContext.getMeasureUtils();
        this.textSize = this.uiContextMeasure.measureTextSize({
            textContent: this.originText,
            fontSize: 16
        });
        this.textMaxLines = 1;
        this.textOverflow = TextOverflow.Ellipsis;
        this.patchesStr = '带白色描边的贴纸效果';
        this.keepLayoutStr = '保持输入图像的位置关系';
        this.isSelectedPatches = false;
        this.isClickKeepLayout = false;
        this.inputHeight = 40;
        this.initParam("imgCounts", (params && "imgCounts" in params) ? params.imgCounts : 0);
        this.isEnableTouchUp = false;
        this.isShowTouchUp = false;
        this.stack = undefined;
        this.updateInputText = '';
        this.textMaxLength = 280;
        this.curLayoutDirection = CanvasLayoutDirection.DEFAULT;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.changeGenerateState = "changeGenerateState" in params ? params.changeGenerateState : (state) => { };
        this.isTextEdit = false;
        this.inputText = '';
        this.resetParam("userPrompt", (params && "userPrompt" in params) ? params.userPrompt : '');
        this.inputController = new TextAreaController();
        this.originText = '';
        this.uiContext = this.getUIContext();
        this.uiContextMeasure = this.uiContext.getMeasureUtils();
        this.textMaxLines = 1;
        this.textOverflow = TextOverflow.Ellipsis;
        this.isSelectedPatches = false;
        this.isClickKeepLayout = false;
        this.inputHeight = 40;
        this.resetParam("imgCounts", (params && "imgCounts" in params) ? params.imgCounts : 0);
        this.isEnableTouchUp = false;
        this.isShowTouchUp = false;
        this.stack = undefined;
        this.updateInputText = '';
        this.textMaxLength = 280;
        this.resetConsumer("curLayoutDirection", CanvasLayoutDirection.DEFAULT);
        this.resetMonitorsOnReuse();
    }
    getTextMaxLength() {
        this.textMaxLength = textBaseMaxLength;
        if (this.inputText.includes(this.keepLayoutStr + '，')) {
            this.textMaxLength += (this.keepLayoutStr + '，').length;
        }
        else if (this.inputText.includes(this.keepLayoutStr)) {
            this.textMaxLength += this.keepLayoutStr.length;
        }
        if (this.inputText.includes(this.patchesStr + '，')) {
            this.textMaxLength += (this.patchesStr + '，').length;
        }
        else if (this.inputText.includes(this.patchesStr)) {
            this.textMaxLength += this.patchesStr.length;
        }
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
        this.getTextMaxLength();
    }
    watchUserPromptChange(monitor) {
        this.inputText = this.userPrompt;
    }
    aboutToAppear() {
        this.inputText = this.userPrompt;
        this.stack = this.queryNavigationInfo()?.pathStack;
    }
    getDataFromUdmfRetry(event, callback) {
        try {
            let data = event.getData();
            if (!data) {
                return false;
            }
            let records = data.getRecords();
            if (!records || records.length <= 0) {
                return false;
            }
            callback(event);
            return true;
        }
        catch (e) {
            return false;
        }
    }
    getDataFromUdmf(event, callback) {
        if (this.getDataFromUdmfRetry(event, callback)) {
            return;
        }
        setTimeout(() => {
            this.getDataFromUdmfRetry(event, callback);
        }, 1500);
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
            Button.createWithChild();
            Button.padding({
                top: 6,
                bottom: 6,
                left: 12,
                right: 12
            });
            Button.borderRadius(20);
            Button.backgroundColor(this.isClickKeepLayout ? { "id": 125831004, "type": 10001, params: ['sys.color.comp_background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.visibility((this.imgCounts > 1 && this.isTextEdit) ? Visibility.Visible : Visibility.None);
            Button.onClick(() => {
                this.isClickKeepLayout = !this.isClickKeepLayout;
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 4 });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({ "id": 125836321, "type": 20000, params: ['sys.media.maintain_layout'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.width('16vp');
            Image.height('16vp');
            Image.fillColor({ "id": 125830991, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Image);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('保持布局');
            Text.height('100%');
            Text.fontSize(12);
            Text.fontColor({ "id": 125830991, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.padding({
                top: 6,
                bottom: 6,
                left: 12,
                right: 12
            });
            Button.borderRadius(20);
            Button.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.enabled(this.isEnableTouchUp);
            Button.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
            Button.onClick(() => {
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
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 4 });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": 125835100, "type": 40000, params: ['sys.symbol.AI_pencil'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
            SymbolGlyph.fontColor([{ "id": 125830991, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('文本润色');
            Text.height('100%');
            Text.fontSize(12);
            Text.fontColor({ "id": 125830991, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild();
            Button.padding({
                top: 6,
                bottom: 6,
                left: 12,
                right: 12
            });
            Button.borderRadius(20);
            Button.backgroundColor(this.isSelectedPatches ? { "id": 125831004, "type": 10001, params: ['sys.color.comp_background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
            Button.onClick(() => {
                this.isSelectedPatches = !this.isSelectedPatches;
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create({ space: 4 });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({ "id": 125831455, "type": 40000, params: ['sys.symbol.stickers'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
            SymbolGlyph.fontColor([{ "id": 125830991, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
        }, SymbolGlyph);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('贴纸效果');
            Text.height('100%');
            Text.fontSize(12);
            Text.fontColor({ "id": 125830991, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
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
            Column.width(this.curLayoutDirection === CanvasLayoutDirection.HORIZONTAL ? 510 : 344);
            Column.backgroundColor('#99FFFFFF');
            Column.backdropBlur(120);
            Column.borderRadius(24);
            Column.border({ width: 1, color: '#FFFFFF' });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            TextArea.create({ placeholder: '描述你想要创作的内容', text: { value: this.inputText, changeEvent: newValue => { this.inputText = newValue; } }, controller: this.inputController });
            TextArea.margin({ top: 9.5, bottom: 9.5, left: 16, right: 16 });
            TextArea.padding(0);
            TextArea.constraintSize({
                maxHeight: this.setMaxLines * this.getUIContext().px2vp(Number(this.textSize.height))
            });
            TextArea.placeholderFont({ size: 16 });
            TextArea.placeholderColor({ "id": 125830984, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            TextArea.fontSize(16);
            TextArea.textAlign(TextAlign.Start);
            TextArea.backgroundColor(Color.Transparent);
            TextArea.maxLength(this.textMaxLength);
            TextArea.maxLines(this.textMaxLines);
            TextArea.textOverflow(this.textOverflow);
            TextArea.barState(BarState.On);
            TextArea.borderRadius(0);
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
            TextArea.onEditChange((isEditing) => {
                this.isTextEdit = isEditing;
                if (isEditing) {
                    this.textMaxLines = 0;
                    this.textOverflow = TextOverflow.None;
                    this.inputHeight = 'auto';
                    this.getUIContext().setKeyboardAvoidMode(2);
                    if (!this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                        this.inputText = this.keepLayoutStr + '，' + this.inputText;
                        this.isClickKeepLayout = true;
                    }
                }
                else {
                    this.textMaxLines = 1;
                    this.textOverflow = TextOverflow.Ellipsis;
                    this.inputHeight = 40;
                    this.getUIContext().setKeyboardAvoidMode(0);
                }
            });
            TextArea.onDrop((dragEvent) => {
                this.isTextEdit = false;
                this.getDataFromUdmf(dragEvent, (event) => {
                    let records = event.getData().getRecords();
                    let plainText = records[0];
                    this.inputController.addText(plainText.textContent, { offset: this.inputController.getCaretOffset().index });
                });
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
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("userPrompt" in params) {
            this.updateParam("userPrompt", params.userPrompt);
        }
        if ("imgCounts" in params) {
            this.updateParam("imgCounts", params.imgCounts);
        }
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
    Param
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
    Param
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
    Local
], TextInputArea.prototype, "textMaxLength", void 0);
__decorate([
    Consumer('globalLayoutDirection')
], TextInputArea.prototype, "curLayoutDirection", void 0);
__decorate([
    Monitor('imgCounts', 'isClickKeepLayout', 'updateInputText', 'isSelectedPatches')
], TextInputArea.prototype, "watchKeepLayout", null);
__decorate([
    Monitor('userPrompt')
], TextInputArea.prototype, "watchUserPromptChange", null);
