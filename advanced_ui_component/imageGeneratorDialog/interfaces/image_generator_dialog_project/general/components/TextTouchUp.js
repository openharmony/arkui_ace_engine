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

var __decorate = (this && this.__decorate) || function (v11, w11, x11, y11) {
    var z11 = arguments.length, a12 = z11 < 3 ? w11 : y11 === null ? y11 = Object.getOwnPropertyDescriptor(w11, x11) : y11, b12;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        a12 = Reflect.decorate(v11, w11, x11, y11);
    else
        for (var c12 = v11.length - 1; c12 >= 0; c12--)
            if (b12 = v11[c12])
                a12 = (z11 < 3 ? b12(a12) : z11 > 3 ? b12(w11, x11, a12) : b12(w11, x11)) || a12;
    return z11 > 3 && a12 && Object.defineProperty(w11, x11, a12), a12;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { LengthMetrics } from "@ohos.arkui.node";
import { AIGenerateImpl } from '../utils/AIGenerateImpl';
export class TextTouchUpComponent extends ViewV2 {
    constructor(p11, q11, r11, s11 = -1, t11, u11) {
        super(p11, s11, u11);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(o11) {
    }
    initialRender() {
        this.observeComponentCreation2((i11, j11) => {
            NavDestination.create(() => {
                {
                    this.observeComponentCreation2((k11, l11) => {
                        if (l11) {
                            let m11 = new TextTouchUp(this, {}, undefined, k11, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TextTouchUp.ets", line: 24, col: 7 });
                            ViewV2.create(m11);
                            let n11 = () => {
                                return {};
                            };
                            m11.paramsGenerator_ = n11;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(k11, {});
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
    constructor(c11, d11, e11, f11 = -1, g11, h11) {
        super(c11, f11, h11);
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
    resetStateVarsOnReuse(b11) {
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
            onResult: (a11) => {
                if (a11.reasoningContent) {
                    this.aiThinkText += a11.reasoningContent;
                }
                if (a11.content) {
                    this.aiResultText += a11.content;
                }
            },
            onComplete: (z10) => {
            },
        }).then((y10) => {
            this.taskId = y10;
        });
    }
    initialRender() {
        this.observeComponentCreation2((w10, x10) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
        }, Column);
        this.observeComponentCreation2((u10, v10) => {
            Column.create();
            Column.height(382);
            Column.width('100%');
            Column.margin({
                top: LengthMetrics.vp(16),
                end: LengthMetrics.vp(8)
            });
        }, Column);
        this.observeComponentCreation2((s10, t10) => {
            Scroll.create();
            Scroll.constraintSize({ maxHeight: 358 });
        }, Scroll);
        this.observeComponentCreation2((q10, r10) => {
            Column.create();
            Column.padding({
                bottom: LengthMetrics.vp(6),
                start: LengthMetrics.vp(16),
            });
        }, Column);
        this.observeComponentCreation2((o10, p10) => {
            Flex.create({
                direction: FlexDirection.Row,
                justifyContent: FlexAlign.Start,
                alignItems: ItemAlign.Start,
            });
            Flex.width('100%');
            Flex.height(40);
            Flex.padding({
                top: LengthMetrics.vp(8),
                bottom: LengthMetrics.vp(12),
                start: LengthMetrics.vp(8),
                end: LengthMetrics.vp(8)
            });
        }, Flex);
        this.observeComponentCreation2((m10, n10) => {
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
        this.observeComponentCreation2((k10, l10) => {
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
        this.observeComponentCreation2((i10, j10) => {
            Text.create(this.aiThinkText);
            Text.fontColor({ "id": 125830984, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize(14);
            Text.fontWeight(400);
            Text.lineHeight(17);
            Text.backgroundColor(Color.Transparent);
            Text.padding({
                start: LengthMetrics.vp(8),
                end: LengthMetrics.vp(8)
            });
            Text.visibility(this.imgOrientation == ImageRotateOrientation.UP ? Visibility.Visible : Visibility.None);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((g10, h10) => {
            Column.create();
            Column.width('100%');
            Column.padding({
                top: LengthMetrics.vp(8.5),
                bottom: LengthMetrics.vp(8)
            });
        }, Column);
        this.observeComponentCreation2((e10, f10) => {
            Divider.create();
            Divider.strokeWidth(0.5);
            Divider.color({ "id": 125831013, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        }, Divider);
        Column.pop();
        this.observeComponentCreation2((c10, d10) => {
            Column.create();
            Column.width('100%');
            Column.height(184);
            Column.padding({
                top: LengthMetrics.vp(8),
                bottom: LengthMetrics.vp(8),
                start: LengthMetrics.vp(16),
                end: LengthMetrics.vp(16)
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
        this.observeComponentCreation2((z9, a10) => {
            TextArea.create({ text: { value: this.aiResultText, changeEvent: b10 => { this.aiResultText = b10; } } });
            TextArea.placeholderFont({ size: 14 });
            TextArea.fontColor('#e6000000');
            TextArea.fontSize(16);
            TextArea.fontWeight(500);
            TextArea.lineHeight(19);
            TextArea.backgroundColor("#ffffffff");
            TextArea.padding({
                top: LengthMetrics.vp(0),
                bottom: LengthMetrics.vp(0),
                start: LengthMetrics.vp(0),
                end: LengthMetrics.vp(0)
            });
            TextArea.borderRadius(0);
        }, TextArea);
        Column.pop();
        Column.pop();
        Scroll.pop();
        Column.pop();
        this.observeComponentCreation2((x9, y9) => {
            Text.create('内容由API生成');
            Text.fontColor({ "id": 125830984, "type": 10001, params: ['sys.color.font_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontSize(12);
            Text.fontWeight(400);
            Text.lineHeight(14);
            Text.textAlign(TextAlign.Center);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((v9, w9) => {
            Button.createWithLabel('使用润色结果');
            Button.width(448);
            Button.height(40);
            Button.fontSize(16);
            Button.fontWeight(500);
            Button.margin({
                top: LengthMetrics.vp(20),
                bottom: LengthMetrics.vp(16),
                start: LengthMetrics.vp(101),
                end: LengthMetrics.vp(101)
            });
            Button.onClick(() => {
                this.stack.pop(this.aiResultText);
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
