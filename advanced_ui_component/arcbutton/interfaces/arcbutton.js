/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (l5, m5, n5, o5) {
    var p5 = arguments.length, q5 = p5 < 3 ? m5 : o5 === null ? o5 = Object.getOwnPropertyDescriptor(m5, n5) : o5, r5;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        q5 = Reflect.decorate(l5, m5, n5, o5);
    else
        for (var s5 = l5.length - 1; s5 >= 0; s5--)
            if (r5 = l5[s5])
                q5 = (p5 < 3 ? r5(q5) : p5 > 3 ? r5(m5, n5, q5) : r5(m5, n5)) || q5;
    return p5 > 3 && q5 && Object.defineProperty(m5, n5, q5), q5;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}

const measure = requireNapi('measure');
const Curves = globalThis.requireNativeModule('ohos.curves');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const PathShape = requireNapi('arkui.shape').PathShape;

export var ArcButtonPosition;
(function (k5) {
    k5[k5["TOP_EDGE"] = 0] = "TOP_EDGE";
    k5[k5["BOTTOM_EDGE"] = 1] = "BOTTOM_EDGE";
})(ArcButtonPosition || (ArcButtonPosition = {}));
export var ArcButtonStyleMode;
(function (j5) {
    j5[j5["EMPHASIZED_LIGHT"] = 0] = "EMPHASIZED_LIGHT";
    j5[j5["EMPHASIZED_DARK"] = 1] = "EMPHASIZED_DARK";
    j5[j5["NORMAL_LIGHT"] = 2] = "NORMAL_LIGHT";
    j5[j5["NORMAL_DARK"] = 3] = "NORMAL_DARK";
    j5[j5["CUSTOM"] = 4] = "CUSTOM";
})(ArcButtonStyleMode || (ArcButtonStyleMode = {}));
export var ArcButtonStatus;
(function (i5) {
    i5[i5["NORMAL"] = 0] = "NORMAL";
    i5[i5["PRESSED"] = 1] = "PRESSED";
    i5[i5["DISABLED"] = 2] = "DISABLED";
})(ArcButtonStatus || (ArcButtonStatus = {}));
class Constants {
}
Constants.MAX_FONT_SIZE = 19;
Constants.MIN_FONT_SIZE = 13;
Constants.SHADOW_BLUR = 4;
Constants.SHADOW_OFFSET_Y = 3;
Constants.DISTANCE_FROM_BORDER = 1;
Constants.TEXT_HORIZONTAL_MARGIN = 24;
Constants.TEXT_MARGIN_TOP = 10;
Constants.TEXT_MARGIN_BOTTOM = 16;
Constants.EMPHASIZED_NORMAL_BTN_COLOR = { "id": -1, "type": 10001, params: ['sys.color.comp_background_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
Constants.EMPHASIZED_TEXT_COLOR = '#FFFFFF';
Constants.EMPHASIZED_PRESSED_BTN_COLOR = '#357FFF';
Constants.EMPHASIZED_DISABLE_BTN_COLOR = '#1F71FF';
Constants.EMPHASIZED_DISABLE_TEXT_COLOR = '#FFFFFF';
Constants.NORMAL_LIGHT_NORMAL_BTN_COLOR = '#17273F';
Constants.NORMAL_LIGHT_TEXT_COLOR = '#5EA1FF';
Constants.NORMAL_LIGHT_PRESSED_BTN_COLOR = '#2E3D52';
Constants.NORMAL_LIGHT_DISABLE_BTN_COLOR = '#17273F';
Constants.NORMAL_LIGHT_DISABLE_TEXT_COLOR = '#995ea1ff';
Constants.NORMAL_DARK_NORMAL_BTN_COLOR = '#252525';
Constants.NORMAL_DARK_TEXT_COLOR = '#5EA1FF';
Constants.NORMAL_DARK_PRESSED_BTN_COLOR = '#3B3B3B';
Constants.NORMAL_DARK_DISABLE_BTN_COLOR = '#262626';
Constants.NORMAL_DARK_DISABLE_TEXT_COLOR = '#995ea1ff';
Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR = '#BF2629';
Constants.EMPHASIZEWARN_TEXT_COLOR = '#FFFFFF';
Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR = '#C53C3E';
Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR = '#4C0f10';
Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR = '#99FFFFFF';
Constants.PRESS_MERGE_COLOR = '#1AFFFFFF';
Constants.DEFAULT_TRANSPARENCY = 0.4;
let ArcButtonProgressConfig = class ArcButtonProgressConfig {
    constructor(h5) {
        this.value = h5.value;
        this.total = h5.total;
        this.color = h5.color;
    }
};
__decorate([
    Trace
], ArcButtonProgressConfig.prototype, "value", void 0);
__decorate([
    Trace
], ArcButtonProgressConfig.prototype, "total", void 0);
__decorate([
    Trace
], ArcButtonProgressConfig.prototype, "color", void 0);
ArcButtonProgressConfig = __decorate([
    ObservedV2
], ArcButtonProgressConfig);
export { ArcButtonProgressConfig };
let ArcButtonOptions = class ArcButtonOptions {
    constructor(g5) {
        this.position = g5.position ?? ArcButtonPosition.BOTTOM_EDGE;
        this.styleMode = g5.styleMode ?? ArcButtonStyleMode.EMPHASIZED_LIGHT;
        this.status = g5.status ?? ArcButtonStatus.NORMAL;
        this.label = g5.label ?? '';
        this.backgroundBlurStyle = g5.backgroundBlurStyle ?? BlurStyle.NONE;
        this.backgroundColor = g5.backgroundColor ?? ColorMetrics.resourceColor(Color.Black);
        this.shadowColor = g5.shadowColor ?? ColorMetrics.resourceColor('#000000');
        this.shadowEnabled = g5.shadowEnabled ?? false;
        this.fontSize = g5.fontSize;
        this.fontColor = g5.fontColor ?? ColorMetrics.resourceColor(Color.White);
        this.pressedFontColor = g5.pressedFontColor ?? ColorMetrics.resourceColor(Color.White);
        this.fontStyle = g5.fontStyle ?? FontStyle.Normal;
        this.fontFamily = g5.fontFamily ?? '';
        this.fontMargin = g5.fontMargin ?? {
            start: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
            top: LengthMetrics.vp(Constants.TEXT_MARGIN_TOP),
            end: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
            bottom: LengthMetrics.vp(Constants.TEXT_MARGIN_BOTTOM)
        };
        this.onTouch = g5.onTouch ?? (() => {
        });
        this.onClick = g5.onClick ?? (() => {
        });
        if (g5.progressConfig) {
            this.backgroundColor = g5.backgroundColor ?? ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
            this.progressConfig = new ArcButtonProgressConfig(g5.progressConfig);
        }
        else {
            this.progressConfig = undefined;
        }
    }
};
__decorate([
    Trace
], ArcButtonOptions.prototype, "position", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "styleMode", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "status", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "label", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "backgroundBlurStyle", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "backgroundColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "shadowColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "shadowEnabled", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "fontSize", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "fontColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "pressedFontColor", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "fontStyle", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "fontFamily", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "fontMargin", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "onTouch", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "onClick", void 0);
__decorate([
    Trace
], ArcButtonOptions.prototype, "progressConfig", void 0);
ArcButtonOptions = __decorate([
    ObservedV2
], ArcButtonOptions);
export { ArcButtonOptions };
export class ArcButton extends ViewV2 {
    constructor(a5, b5, c5, d5 = -1, e5, f5) {
        super(a5, d5, f5);
        this.initParam("options", (b5 && "options" in b5) ? b5.options : undefined);
        this.canvasWidth = 0;
        this.canvasHeight = 0;
        this.scaleX = 1;
        this.scaleY = 1;
        this.btnColor = ColorMetrics.resourceColor(Color.Black);
        this.textWidth = 0;
        this.textHeight = 0;
        this.fontColor = ColorMetrics.resourceColor(Color.White);
        this.isExceed = false;
        this.pathString = '';
        this.fontSize = '';
        this.progressValue = 0;
        this.progressTotal = 100;
        this.progressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
        this.btnNormalColor = ColorMetrics.resourceColor(Color.Black);
        this.btnPressColor = ColorMetrics.resourceColor(Color.Black);
        this.btnDisableColor = ColorMetrics.resourceColor(Color.Black);
        this.textNormalColor = ColorMetrics.resourceColor(Color.White);
        this.textDisableColor = ColorMetrics.resourceColor(Color.White);
        this.isUp = false;
        this.curves = Curves.interpolatingSpring(10, 1, 350, 35);
        this.scaleValue = 1;
        this.textPressColor = ColorMetrics.resourceColor(Color.White);
        this.arcButtonTheme = {
            BUTTON_HEIGHT: this.getArcButtonThemeVpValue({ "id": -1, "type": 10002, params: ['sys.float.arc_button_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            ARC_CIRCLE_DIAMETER: this.getArcButtonThemeVpValue({ "id": -1, "type": 10002, params: ['sys.float.arc_button_auxiliary_circle_diameter'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            DIAL_CIRCLE_DIAMETER: this.getArcButtonThemeVpValue({ "id": -1, "type": 10002, params: ['sys.float.arc_button_dial_circle_diameter'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            CHAMFER_CIRCLE_RADIUS: this.getArcButtonThemeVpValue({ "id": -1, "type": 10002, params: ['sys.float.arc_button_chamfer_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
        };
        this.dataProcessUtil = new DataProcessUtil(this.arcButtonTheme);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(z4) {
        this.resetParam("options", (z4 && "options" in z4) ? z4.options : undefined);
        this.canvasWidth = 0;
        this.canvasHeight = 0;
        this.scaleX = 1;
        this.scaleY = 1;
        this.btnColor = ColorMetrics.resourceColor(Color.Black);
        this.textWidth = 0;
        this.textHeight = 0;
        this.fontColor = ColorMetrics.resourceColor(Color.White);
        this.isExceed = false;
        this.pathString = '';
        this.fontSize = '';
        this.progressValue = 0;
        this.progressTotal = 100;
        this.progressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
        this.resetMonitorsOnReuse();
    }
    optionsChange() {
        this.fontSize = this.cover(this.options.fontSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE));
        this.judgeTextWidth();
        this.changeStatus();
        this.progressOptionsChange();
    }
    progressOptionsChange() {
        if (this.options.progressConfig) {
            this.progressValue = this.options.progressConfig.value;
            if (this.options.progressConfig.color) {
                this.progressColor = ColorMetrics.resourceColor(this.options.progressConfig.color);
            }
            else if (this.options.backgroundColor !== undefined) {
                this.progressColor = this.options.backgroundColor;
            }
            else {
                this.progressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
            }
            if (this.options.progressConfig.total) {
                this.progressTotal = this.options.progressConfig.total;
            }
            else {
                this.progressTotal = 100;
            }
        }
    }
    changeStatus() {
        switch (this.options.styleMode) {
            case ArcButtonStyleMode.EMPHASIZED_LIGHT:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_NORMAL_BTN_COLOR).blendColor(ColorMetrics.resourceColor(Constants.PRESS_MERGE_COLOR));
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR);
                break;
            case ArcButtonStyleMode.NORMAL_LIGHT:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_NORMAL_BTN_COLOR).blendColor(ColorMetrics.resourceColor(Constants.PRESS_MERGE_COLOR));
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_TEXT_COLOR);
                break;
            case ArcButtonStyleMode.NORMAL_DARK:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_NORMAL_BTN_COLOR).blendColor(ColorMetrics.resourceColor(Constants.PRESS_MERGE_COLOR));
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_TEXT_COLOR);
                break;
            case ArcButtonStyleMode.EMPHASIZED_DARK:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR).blendColor(ColorMetrics.resourceColor(Constants.PRESS_MERGE_COLOR));
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR);
                break;
            default:
                this.btnNormalColor = this.options.backgroundColor;
                this.textNormalColor = this.options.fontColor;
                this.btnPressColor = this.options.backgroundColor.blendColor(ColorMetrics.resourceColor(Constants.PRESS_MERGE_COLOR));
                this.textPressColor = this.options.pressedFontColor;
                break;
        }
        if (this.options.status === ArcButtonStatus.DISABLED) {
            this.btnColor = this.btnDisableColor;
            this.fontColor = this.textDisableColor;
        }
        else if (this.options.status === ArcButtonStatus.PRESSED) {
            this.btnColor = this.btnPressColor;
            this.fontColor = this.textPressColor;
        }
        else {
            this.btnColor = this.btnNormalColor;
            this.fontColor = this.textNormalColor;
        }
    }
    initValues() {
        this.isUp = this.options.position == ArcButtonPosition.TOP_EDGE;
        this.btnColor = this.options.backgroundColor;
        this.fontColor = this.options.fontColor;
        this.curves = Curves.interpolatingSpring(10, 1, 350, 35);
        this.scaleValue = 1;
        this.progressOptionsChange();
        this.changeStatus();
    }
    getArcButtonThemeVpValue(w4) {
        if (!w4) {
            return 0;
        }
        let x4 = LengthMetrics.resource(w4);
        let y4 = x4.value;
        switch (x4.unit) {
            case LengthUnit.PX:
                return px2vp(y4);
            case LengthUnit.LPX:
                return px2vp(lpx2px(y4));
            case LengthUnit.FP:
                return px2vp(fp2px(y4));
        }
        return y4;
    }
    judgeTextWidth() {
        const v4 = measure.measureText({
            textContent: this.options.label,
            fontStyle: this.options.fontStyle,
            fontFamily: this.options.fontFamily,
            fontWeight: FontWeight.Medium,
            maxLines: 1,
            fontSize: `${Constants.MIN_FONT_SIZE}fp`
        });
        this.isExceed = v4 > this.getUIContext().vp2px(this.textWidth);
    }
    aboutToAppear() {
        if (this.arcButtonTheme.BUTTON_HEIGHT === 0) {
            console.error("arcbutton can't obtain sys float value.");
            return;
        }
        this.initValues();
        this.dataProcessUtil.initData();
        const u4 = this.dataProcessUtil.calculate();
        this.generatePath(u4);
    }
    calculateActualPosition(q4, r4) {
        const s4 = this.getUIContext().vp2px(q4.x - r4.x);
        const t4 = this.getUIContext().vp2px(q4.y - r4.y);
        return new ArcButtonPoint(s4, t4);
    }
    generatePath(b4) {
        if (b4 === null) {
            return;
        }
        this.canvasWidth = b4.btnWidth + Constants.SHADOW_BLUR * 2;
        this.canvasHeight = b4.btnHeight + Constants.DISTANCE_FROM_BORDER * 2;
        const c4 = this.options.fontMargin;
        const d4 = c4?.start?.value ?? 0;
        const e4 = c4?.end?.value ?? 0;
        const f4 = c4?.top?.value ?? 0;
        const g4 = c4?.bottom?.value ?? 0;
        this.textWidth = b4.btnWidth - d4 - e4;
        this.textHeight = b4.btnHeight - f4 - g4;
        this.judgeTextWidth();
        const h4 = b4.canvasLeftTop;
        h4.x -= Constants.SHADOW_BLUR;
        h4.y -= Constants.DISTANCE_FROM_BORDER;
        const i4 = this.calculateActualPosition(b4.leftTopPoint, h4);
        const j4 = this.getUIContext().vp2px(this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2);
        const k4 = this.calculateActualPosition(b4.rightTopPoint, h4);
        const l4 = this.getUIContext().vp2px(this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS);
        const m4 = this.calculateActualPosition(b4.rightBottomPoint, h4);
        const n4 = this.getUIContext().vp2px(this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2);
        const o4 = this.calculateActualPosition(b4.leftBottomPoint, h4);
        const p4 = `M ${i4.x} ${i4.y} A ${j4} ${j4}, 0, 0, 0,
       ${k4.x} ${k4.y}` +
            `Q ${k4.x - l4 * 1.2} ${k4.y +
                l4 * 0.6} ${m4.x} ${m4.y}` +
            `A ${n4} ${n4}, 0, 0, 0, ${o4.x}
       ${o4.y}` +
            `Q ${i4.x + l4 * 1.2} ${i4.y +
                l4 * 0.6} ${i4.x} ${i4.y}`;
        this.pathString = p4;
    }
    TextBuilderIsExceed(y3 = null) {
        this.observeComponentCreation2((z3, a4) => {
            Text.create(this.options.label);
            Text.width(this.textWidth);
            Text.height(this.textHeight);
            Text.fontColor(this.fontColor.color);
            Text.fontSize(this.fontSize);
            Text.maxLines(1);
            Text.textAlign(TextAlign.Center);
            Text.fontWeight(FontWeight.Medium);
            Text.fontStyle(this.options.fontStyle);
            Text.fontFamily(this.options.fontFamily);
            Text.backgroundColor(Color.Transparent);
            Text.textOverflow({ overflow: TextOverflow.MARQUEE });
            Text.margin({
                start: this.options.fontMargin.start,
                top: this.isUp ? this.options.fontMargin.bottom : this.options.fontMargin.top,
                end: this.options.fontMargin.end,
                bottom: this.options.fontMargin.bottom
            });
        }, Text);
        Text.pop();
    }
    TextBuilderNormal(v3 = null) {
        this.observeComponentCreation2((w3, x3) => {
            Text.create(this.options.label);
            Text.width(this.textWidth);
            Text.height(this.textHeight);
            Text.textAlign(TextAlign.Center);
            Text.fontColor(this.fontColor.color);
            Text.maxFontSize(this.options.fontSize ? undefined : `${Constants.MAX_FONT_SIZE}fp`);
            Text.minFontSize(this.options.fontSize ? undefined : `${Constants.MIN_FONT_SIZE}fp`);
            Text.fontSize(this.options.fontSize ? this.cover(this.options.fontSize) : undefined);
            Text.fontWeight(FontWeight.Medium);
            Text.fontStyle(this.options.fontStyle);
            Text.fontFamily(this.options.fontFamily);
            Text.maxLines(1);
            Text.margin({
                start: this.options.fontMargin.start,
                top: this.isUp ? this.options.fontMargin.bottom : this.options.fontMargin.top,
                end: this.options.fontMargin.end,
                bottom: this.options.fontMargin.bottom
            });
        }, Text);
        Text.pop();
    }
    cover(u3) {
        switch (u3.unit) {
            case LengthUnit.VP:
                return `${u3.value}vp`;
            case LengthUnit.PX:
                return `${u3.value}px`;
            case LengthUnit.FP:
                return `${u3.value}fp`;
            case LengthUnit.LPX:
                return `${u3.value}lpx`;
            case LengthUnit.PERCENT:
                return `${u3.value}%`;
        }
    }
    getShadow() {
        if (!this.options.shadowEnabled) {
            return undefined;
        }
        return {
            radius: Constants.SHADOW_BLUR,
            color: this.options.shadowColor.color,
            offsetY: Constants.SHADOW_OFFSET_Y
        };
    }
    initialRender() {
        this.observeComponentCreation2((q3, r3) => {
            Stack.create({ alignContent: Alignment.Center });
            Context.animation({ curve: this.curves });
            Stack.enabled(this.options.status !== ArcButtonStatus.DISABLED);
            Stack.opacity((this.options.styleMode === ArcButtonStyleMode.EMPHASIZED_LIGHT &&
                this.options.status === ArcButtonStatus.DISABLED) ? Constants.DEFAULT_TRANSPARENCY : 1);
            Context.animation(null);
            Stack.width(this.canvasWidth);
            Stack.height(this.canvasHeight);
            Stack.scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.canvasHeight });
            Stack.onTouch((t3) => {
                this.dealTouchEvent(t3);
            });
            Stack.onClick((s3) => {
                if (this.options.onClick) {
                    this.options.onClick(s3);
                }
            });
        }, Stack);
        this.observeComponentCreation2((k3, l3) => {
            If.create();
            if (this.options.progressConfig) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o3, p3) => {
                        Progress.create({ value: this.progressValue, total: this.progressTotal, type: ProgressType.Capsule });
                        Progress.width('100%');
                        Progress.height('100%');
                        Progress.rotate({ angleX: !this.isUp ? 0 : 180 });
                        Progress.clipShape(new Path({ commands: this.pathString }));
                        Progress.backgroundColor(ColorMetrics.rgba(this.progressColor.red, this.progressColor.green, this.progressColor.blue, 0.25));
                        Progress.color(this.progressColor.color);
                        Progress.backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true });
                        Progress.shadow(this.getShadow());
                    }, Progress);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m3, n3) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: false });
                        Button.width('100%');
                        Button.height('100%');
                        Button.rotate({ angle: !this.isUp ? 0 : 180 });
                        Button.clipShape(new Path({ commands: this.pathString }));
                        Button.backgroundColor(this.btnColor.color);
                        Button.backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true });
                        Button.shadow(this.getShadow());
                    }, Button);
                    Button.pop();
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((i3, j3) => {
            If.create();
            if (this.isExceed) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextBuilderIsExceed.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.TextBuilderNormal.bind(this)();
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    dealTouchEvent(f3) {
        const g3 = f3.touches[0].windowX;
        const h3 = f3.touches[0].windowY;
        if (this.options.onTouch) {
            this.options.onTouch(f3);
        }
        if (this.options.status === ArcButtonStatus.PRESSED) {
            this.scaleX = this.scaleValue;
            this.scaleY = this.scaleValue;
            this.btnColor = this.btnPressColor;
            this.fontColor = this.textPressColor;
        }
        else {
            switch (f3.type) {
                case TouchType.Down:
                    this.scaleX = this.scaleValue;
                    this.scaleY = this.scaleValue;
                    this.btnColor = this.btnPressColor;
                    this.fontColor = this.textPressColor;
                    break;
                case TouchType.Up:
                    this.scaleX = 1;
                    this.scaleY = 1;
                    this.btnColor = this.btnNormalColor;
                    this.fontColor = this.textNormalColor;
                    break;
                default:
                    break;
            }
        }
    }
    updateStateVars(e3) {
        if (e3 === undefined) {
            return;
        }
        if ("options" in e3) {
            this.updateParam("options", e3.options);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ArcButton.prototype, "options", void 0);
__decorate([
    Local
], ArcButton.prototype, "canvasWidth", void 0);
__decorate([
    Local
], ArcButton.prototype, "canvasHeight", void 0);
__decorate([
    Local
], ArcButton.prototype, "scaleX", void 0);
__decorate([
    Local
], ArcButton.prototype, "scaleY", void 0);
__decorate([
    Local
], ArcButton.prototype, "btnColor", void 0);
__decorate([
    Local
], ArcButton.prototype, "textWidth", void 0);
__decorate([
    Local
], ArcButton.prototype, "textHeight", void 0);
__decorate([
    Local
], ArcButton.prototype, "fontColor", void 0);
__decorate([
    Local
], ArcButton.prototype, "isExceed", void 0);
__decorate([
    Local
], ArcButton.prototype, "pathString", void 0);
__decorate([
    Local
], ArcButton.prototype, "fontSize", void 0);
__decorate([
    Local
], ArcButton.prototype, "progressValue", void 0);
__decorate([
    Local
], ArcButton.prototype, "progressTotal", void 0);
__decorate([
    Local
], ArcButton.prototype, "progressColor", void 0);
__decorate([
    Monitor('options.label', 'options.type', 'options.fontSize', 'options.styleMode', 'options.status', 'options.backgroundColor', 'options.fontColor', 'options.progressConfig.color', 'options.progressConfig.total', 'options.progressConfig.value')
], ArcButton.prototype, "optionsChange", null);
class DataProcessUtil {
    constructor(d3) {
        this.dial = new ArcButtonCircle(0, 0, 0);
        this.arc = new ArcButtonCircle(0, 0, 0);
        this.height = 0;
        this.width = 0;
        this.arcButtonTheme = undefined;
        this.arcButtonTheme = d3;
    }
    initData() {
        const z2 = this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2;
        this.dial = new ArcButtonCircle(z2, z2, z2);
        const a3 = this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2;
        this.height = this.arcButtonTheme.BUTTON_HEIGHT;
        const b3 = this.dial.center.x;
        const c3 = this.dial.center.y + z2 + a3 - this.height;
        this.arc = new ArcButtonCircle(a3, b3, c3);
    }
    calculate() {
        const q2 = this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS;
        const r2 = new ArcButtonCircle(this.dial.radius - q2, this.dial.center.x, this.dial.center.y);
        const s2 = new ArcButtonCircle(this.arc.radius - q2, this.arc.center.x, this.arc.center.y);
        const t2 = this.findCircleIntersections(s2, r2);
        const u2 = this.calculateIntersection(this.arc.center, this.arc.radius, t2[0]);
        const v2 = this.calculateIntersection(this.arc.center, this.arc.radius, t2[1]);
        const w2 = this.calculateIntersection(this.dial.center, this.dial.radius, t2[1]);
        const x2 = this.calculateIntersection(this.dial.center, this.dial.radius, t2[0]);
        this.width = this.calculateDistance(t2[0], t2[1]) + q2 * 2;
        const y2 = new ArcButtonPoint(t2[0].x - q2, this.dial.center.y +
            this.dial.radius - this.height);
        return new AllPoints(this.width, this.height, v2, u2, w2, x2, y2);
    }
    calculateDistance(o2, p2) {
        return Math.sqrt((p2.x - o2.x) ** 2 + (p2.y - o2.y) ** 2);
    }
    calculateIntersection(s1, t1, u1) {
        const v1 = s1.x;
        const w1 = s1.y;
        const x1 = u1.x;
        const y1 = u1.y;
        let z1 = 0;
        if (x1 !== v1) {
            z1 = (y1 - w1) / (x1 - v1);
        }
        else {
            z1 = -1;
        }
        let a2 = 0;
        if (z1 !== -1) {
            a2 = y1 - z1 * x1;
        }
        let b2 = [];
        if (z1 !== -1) {
            const h2 = Math.pow(z1, 2) + 1;
            const i2 = 2 * (z1 * a2 - z1 * w1 - v1);
            const j2 = w1 ** 2 - t1 ** 2 + v1 ** 2 - 2 * a2 * w1 + a2 ** 2;
            const k2 = (-i2 + (i2 ** 2 - 4 * h2 * j2) ** 0.5) / (2 * h2);
            const l2 = (-i2 - (i2 ** 2 - 4 * h2 * j2) ** 0.5) / (2 * h2);
            const m2 = z1 * k2 + a2;
            const n2 = z1 * l2 + a2;
            b2 = [new ArcButtonPoint(k2, m2), new ArcButtonPoint(l2, n2)];
        }
        else {
            const e2 = v1;
            const f2 = w1 + t1;
            const g2 = w1 - t1;
            b2 = [new ArcButtonPoint(e2, f2), new ArcButtonPoint(e2, g2)];
        }
        const c2 = this.calculateDistance(b2[0], u1);
        const d2 = this.calculateDistance(b2[1], u1);
        if (c2 < d2) {
            return b2[0];
        }
        else {
            return b2[1];
        }
    }
    findCircleIntersections(c1, d1) {
        const e1 = c1.radius;
        const f1 = c1.center.x;
        const g1 = c1.center.y;
        const h1 = d1.radius;
        const i1 = d1.center.x;
        const j1 = d1.center.y;
        const k1 = Math.sqrt((f1 - i1) ** 2 + (g1 - j1) ** 2);
        if (k1 > e1 + h1) {
            return [];
        }
        else if (k1 < Math.abs(e1 - h1)) {
            return [];
        }
        else if (k1 === 0 && e1 === h1) {
            return [];
        }
        const l1 = (e1 ** 2 - h1 ** 2 + k1 ** 2) / (2 * k1);
        const m1 = Math.sqrt(e1 ** 2 - l1 ** 2);
        const n1 = f1 + l1 * (i1 - f1) / k1;
        const o1 = g1 + l1 * (j1 - g1) / k1;
        let p1 = new ArcButtonPoint(n1 + m1 * (j1 - g1) / k1, o1 -
            m1 * (i1 - f1) / k1);
        let q1 = new ArcButtonPoint(n1 - m1 * (j1 - g1) / k1, o1 +
            m1 * (i1 - f1) / k1);
        if (p1.x > q1.x) {
            const r1 = p1;
            p1 = q1;
            q1 = r1;
        }
        return [p1, q1];
    }
}
class ArcButtonCircle {
    constructor(z, a1, b1) {
        this.radius = z;
        this.center = new ArcButtonPoint(a1, b1);
    }
}
class ArcButtonPoint {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}
class AllPoints {
    constructor(q, r, s, t, u, v, w) {
        this.btnWidth = q;
        this.btnHeight = r;
        this.leftTopPoint = s;
        this.rightTopPoint = t;
        this.leftBottomPoint = u;
        this.rightBottomPoint = v;
        this.canvasLeftTop = w;
    }
}

export default {
    ArcButton,
    ArcButtonOptions,
    ArcButtonPosition,
    ArcButtonStyleMode,
    ArcButtonStatus,
};
//# sourceMappingURL=ArcButton.js.map
