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

var __decorate = (this && this.__decorate) || function (n9, o9, p9, q9) {
    var r9 = arguments.length, s9 = r9 < 3 ? o9 : q9 === null ? q9 = Object.getOwnPropertyDescriptor(o9, p9) : q9, t9;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        s9 = Reflect.decorate(n9, o9, p9, q9);
    else
        for (var u9 = n9.length - 1; u9 >= 0; u9--)
            if (t9 = n9[u9])
                s9 = (r9 < 3 ? t9(s9) : r9 > 3 ? t9(o9, p9, s9) : t9(o9, p9)) || s9;
    return r9 > 3 && s9 && Object.defineProperty(o9, p9, s9), s9;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { ImageGenerateState } from "../types/Declaration";
import { LengthMetrics } from "@ohos.arkui.node";
import { AIGenerateOptions } from '../utils/AIGenerateOptions';
export class TextInputArea extends ViewV2 {
    constructor(g9, h9, i9, j9 = -1, k9, l9) {
        super(g9, j9, l9);
        this.changeGenerateState = "changeGenerateState" in h9 ? h9.changeGenerateState : (m9) => { };
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
    resetStateVarsOnReuse(e9) {
        this.changeGenerateState = "changeGenerateState" in e9 ? e9.changeGenerateState : (f9) => { };
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
    watchKeepLayout(v8) {
        if (this.imgCounts <= 1) {
            this.isClickKeepLayout = false;
            if (this.inputText.includes(this.keepLayoutStr)) {
                let d9 = this.inputText.replace(this.keepLayoutStr + '，', "");
                this.inputText = d9;
            }
        }
        if (this.isClickKeepLayout && !this.inputText.includes(this.keepLayoutStr)) {
            this.inputText = this.keepLayoutStr + '，' + this.inputText;
        }
        else if (!this.isClickKeepLayout && this.inputText.includes(this.keepLayoutStr)) {
            let b9 = this.inputText.includes(this.keepLayoutStr + '，') ? this.keepLayoutStr + '，' : this.keepLayoutStr;
            let c9 = this.inputText.replace(b9, "");
            this.inputText = c9;
        }
        if (this.isSelectedPatches && !this.inputText.includes(this.patchesStr)) {
            if (this.inputText.includes(this.keepLayoutStr)) {
                let y8 = this.inputText.indexOf(this.keepLayoutStr);
                let z8 = this.inputText.slice(0, y8 + this.keepLayoutStr.length);
                let a9 = this.inputText.slice(y8 + this.keepLayoutStr.length);
                this.inputText = z8.concat('，' + this.patchesStr).concat(a9);
            }
            else {
                this.inputText = this.patchesStr + '，' + this.inputText;
            }
        }
        else if (!this.isSelectedPatches && this.inputText.includes(this.patchesStr)) {
            let w8 = this.inputText.includes(this.patchesStr + '，') ? this.patchesStr + '，' : this.patchesStr;
            let x8 = this.inputText.replace(w8, "");
            this.inputText = x8;
        }
        if (this.updateInputText.length != 0) {
            this.inputText = this.updateInputText;
            this.inputText = this.updateInputText;
            this.updateInputText = '';
        }
    }
    watchUserPromptChange(u8) {
        this.inputText = this.userPrompt;
    }
    aboutToAppear() {
        this.inputText = this.userPrompt;
        this.stack = this.queryNavigationInfo()?.pathStack;
    }
    initialRender() {
        this.observeComponentCreation2((s8, t8) => {
            Column.create();
            Column.alignItems(HorizontalAlign.Start);
            Column.padding({
                start: LengthMetrics.vp(16),
                end: LengthMetrics.vp(16)
            });
        }, Column);
        this.observeComponentCreation2((q8, r8) => {
            Row.create({ space: 8 });
            Row.width('100%');
            Row.height(28);
            Row.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
        }, Row);
        this.observeComponentCreation2((o8, p8) => {
            Row.create({ space: 4 });
            Row.padding({
                top: LengthMetrics.vp(6),
                bottom: LengthMetrics.vp(6),
                start: LengthMetrics.vp(12),
                end: LengthMetrics.vp(12)
            });
            Row.borderRadius(20);
            Row.backgroundColor(this.isClickKeepLayout ? { "id": 125831004, "type": 10001, params: ['sys.color.comp_background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.visibility((this.imgCounts > 1 && this.isTextEdit) ? Visibility.Visible : Visibility.None);
            Row.onClick(() => {
                this.isClickKeepLayout = !this.isClickKeepLayout;
            });
        }, Row);
        this.observeComponentCreation2((m8, n8) => {
            SymbolGlyph.create({ "id": 125835100, "type": 40000, params: ['sys.symbol.AI_pencil'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
        }, SymbolGlyph);
        this.observeComponentCreation2((k8, l8) => {
            Text.create('保持布局');
            Text.height('100%');
            Text.fontSize(12);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((h8, i8) => {
            Row.create({ space: 4 });
            Row.padding({
                top: LengthMetrics.vp(6),
                bottom: LengthMetrics.vp(6),
                start: LengthMetrics.vp(12),
                end: LengthMetrics.vp(12)
            });
            Row.borderRadius(20);
            Row.backgroundColor({ "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.enabled(this.isEnableTouchUp);
            Row.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
            Row.onClick(() => {
                this.isShowTouchUp = true;
                this.inputController.stopEditing();
                AIGenerateOptions.getInstance().updateUserPrompt(this.inputText);
                this.stack.pushPath({
                    name: 'textTouchUp',
                    onPop: (j8) => {
                        this.inputText = j8.result.toString();
                    }
                });
            });
        }, Row);
        this.observeComponentCreation2((f8, g8) => {
            SymbolGlyph.create({ "id": 125835100, "type": 40000, params: ['sys.symbol.AI_pencil'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
        }, SymbolGlyph);
        this.observeComponentCreation2((d8, e8) => {
            Text.create('文本润色');
            Text.height('100%');
            Text.fontSize(12);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((b8, c8) => {
            Row.create({ space: 4 });
            Row.padding({
                top: LengthMetrics.vp(6),
                bottom: LengthMetrics.vp(6),
                start: LengthMetrics.vp(12),
                end: LengthMetrics.vp(12)
            });
            Row.borderRadius(20);
            Row.backgroundColor(this.isSelectedPatches ? { "id": 125831004, "type": 10001, params: ['sys.color.comp_background_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": 125831008, "type": 10001, params: ['sys.color.comp_background_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Row.visibility(this.isTextEdit ? Visibility.Visible : Visibility.None);
            Row.onClick(() => {
                this.isSelectedPatches = !this.isSelectedPatches;
            });
        }, Row);
        this.observeComponentCreation2((z7, a8) => {
            SymbolGlyph.create({ "id": 125831455, "type": 40000, params: ['sys.symbol.stickers'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            SymbolGlyph.width('16vp');
            SymbolGlyph.height('16vp');
        }, SymbolGlyph);
        this.observeComponentCreation2((x7, y7) => {
            Text.create('贴纸效果');
            Text.height('100%');
            Text.fontSize(12);
        }, Text);
        Text.pop();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((v7, w7) => {
            Row.create({ space: 12 });
            Row.width('100%');
            Row.alignItems(VerticalAlign.Bottom);
            Row.padding({
                top: LengthMetrics.vp(12),
                bottom: LengthMetrics.vp(12)
            });
        }, Row);
        this.observeComponentCreation2((t7, u7) => {
            Column.create();
            Column.height(this.inputHeight);
            Column.width(510);
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
        }, Column);
        this.observeComponentCreation2((n7, o7) => {
            TextArea.create({ placeholder: '描述你想要创作的内容', text: { value: this.inputText, changeEvent: s7 => { this.inputText = s7; } }, controller: this.inputController });
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
            TextArea.onChange((r7) => {
                this.inputText = r7;
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
            TextArea.onClick((q7) => {
                if (!this.inputText.includes(this.keepLayoutStr) && this.imgCounts > 1) {
                    this.inputText = this.keepLayoutStr + '，' + this.inputText;
                    this.isClickKeepLayout = true;
                }
            });
            TextArea.onEditChange((p7) => {
                this.isTextEdit = p7;
                if (p7) {
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
        this.observeComponentCreation2((l7, m7) => {
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
