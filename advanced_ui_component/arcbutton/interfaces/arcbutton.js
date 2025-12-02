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

var __decorate = (this && this.__decorate) || function (v4, w4, x4, y4) {
    var z4 = arguments.length, a5 = z4 < 3 ? w4 : y4 === null ? y4 = Object.getOwnPropertyDescriptor(w4, x4) : y4, b5;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        a5 = Reflect.decorate(v4, w4, x4, y4);
    else
        for (var c5 = v4.length - 1; c5 >= 0; c5--)
            if (b5 = v4[c5])
                a5 = (z4 < 3 ? b5(a5) : z4 > 3 ? b5(w4, x4, a5) : b5(w4, x4)) || a5;
    return z4 > 3 && a5 && Object.defineProperty(w4, x4, a5), a5;
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
(function (u4) {
    u4[u4["TOP_EDGE"] = 0] = "TOP_EDGE";
    u4[u4["BOTTOM_EDGE"] = 1] = "BOTTOM_EDGE";
})(ArcButtonPosition || (ArcButtonPosition = {}));
export var ArcButtonStyleMode;
(function (t4) {
    t4[t4["EMPHASIZED_LIGHT"] = 0] = "EMPHASIZED_LIGHT";
    t4[t4["EMPHASIZED_DARK"] = 1] = "EMPHASIZED_DARK";
    t4[t4["NORMAL_LIGHT"] = 2] = "NORMAL_LIGHT";
    t4[t4["NORMAL_DARK"] = 3] = "NORMAL_DARK";
    t4[t4["CUSTOM"] = 4] = "CUSTOM";
})(ArcButtonStyleMode || (ArcButtonStyleMode = {}));
export var ArcButtonStatus;
(function (s4) {
    s4[s4["NORMAL"] = 0] = "NORMAL";
    s4[s4["PRESSED"] = 1] = "PRESSED";
    s4[s4["DISABLED"] = 2] = "DISABLED";
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
Constants.DEFAULT_TRANSPARENCY = 0.4;
let ArcButtonProgressConfig = class ArcButtonProgressConfig {
    constructor(d5) {
        this.value = d5.value;
        this.total = d5.total;
        this.color = d5.color;
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
    constructor(q4) {
        this.position = q4.position ?? ArcButtonPosition.BOTTOM_EDGE;
        this.styleMode = q4.styleMode ?? ArcButtonStyleMode.EMPHASIZED_LIGHT;
        this.status = q4.status ?? ArcButtonStatus.NORMAL;
        this.label = q4.label ?? '';
        this.backgroundBlurStyle = q4.backgroundBlurStyle ?? BlurStyle.NONE;
        this.backgroundColor = q4.backgroundColor ?? ColorMetrics.resourceColor(Color.Black);
        this.shadowColor = q4.shadowColor ?? ColorMetrics.resourceColor('#000000');
        this.shadowEnabled = q4.shadowEnabled ?? false;
        this.fontSize = q4.fontSize;
        this.fontColor = q4.fontColor ?? ColorMetrics.resourceColor(Color.White);
        this.pressedFontColor = q4.pressedFontColor ?? ColorMetrics.resourceColor(Color.White);
        this.fontStyle = q4.fontStyle ?? FontStyle.Normal;
        this.fontFamily = q4.fontFamily ?? '';
        this.fontMargin = q4.fontMargin ?? {
            start: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
            top: LengthMetrics.vp(Constants.TEXT_MARGIN_TOP),
            end: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
            bottom: LengthMetrics.vp(Constants.TEXT_MARGIN_BOTTOM)
        };
        this.onTouch = q4.onTouch ?? (() => {
        });
        this.onClick = q4.onClick ?? (() => {
        });
        if (q4.progressConfig) {
            this.progressConfig = new ArcButtonProgressConfig(q4.progressConfig);
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
    constructor(k4, l4, m4, n4 = -1, o4, p4) {
        super(k4, n4, p4);
        this.initParam("options", (l4 && "options" in l4) ? l4.options : undefined);
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
        this.progressColor = ColorMetrics.resourceColor(Color.White);
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
    resetStateVarsOnReuse(j4) {
        this.resetParam("options", (j4 && "options" in j4) ? j4.options : undefined);
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
        this.progressColor = ColorMetrics.resourceColor(Color.White);
        this.resetMonitorsOnReuse();
    }
    optionsChange() {
        this.fontSize = this.cover(this.options.fontSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE));
        this.judgeTextWidth();
        this.changeStatus();
    }
    progressOptionsChange() {
        if (this.options.progressConfig) {
            this.progressValue = this.options.progressConfig.value;
            if (this.options.progressConfig.color) {
                this.progressColor = this.options.progressConfig.color;
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
                this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_PRESSED_BTN_COLOR);
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZED_TEXT_COLOR);
                break;
            case ArcButtonStyleMode.NORMAL_LIGHT:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_PRESSED_BTN_COLOR);
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL_LIGHT_TEXT_COLOR);
                break;
            case ArcButtonStyleMode.NORMAL_DARK:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_PRESSED_BTN_COLOR);
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.NORMAL_DARK_TEXT_COLOR);
                break;
            case ArcButtonStyleMode.EMPHASIZED_DARK:
                this.btnNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR);
                this.textNormalColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR);
                this.btnPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR);
                this.btnDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR);
                this.textDisableColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR);
                this.textPressColor = ColorMetrics.resourceColor(Constants.EMPHASIZEWARN_TEXT_COLOR);
                break;
            default:
                this.btnNormalColor = this.options.backgroundColor;
                this.textNormalColor = this.options.fontColor;
                this.btnPressColor = this.options.backgroundColor;
                this.textPressColor = this.options.pressedFontColor;
                break;
        }
        if (this.options.status === ArcButtonStatus.DISABLED) {
            this.btnColor = this.btnDisableColor;
            this.fontColor = this.textDisableColor;
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
        this.scaleValue = 0.95;
        this.progressOptionsChange();
        this.changeStatus();
    }
    getArcButtonThemeVpValue(g4) {
        if (!g4) {
            return 0;
        }
        let h4 = LengthMetrics.resource(g4);
        let i4 = h4.value;
        switch (h4.unit) {
            case LengthUnit.PX:
                return px2vp(i4);
            case LengthUnit.LPX:
                return px2vp(lpx2px(i4));
            case LengthUnit.FP:
                return px2vp(fp2px(i4));
        }
        return i4;
    }
    judgeTextWidth() {
        const f4 = measure.measureText({
            textContent: this.options.label,
            fontStyle: this.options.fontStyle,
            fontFamily: this.options.fontFamily,
            fontWeight: FontWeight.Medium,
            maxLines: 1,
            fontSize: `${Constants.MIN_FONT_SIZE}fp`
        });
        this.isExceed = f4 > this.getUIContext().vp2px(this.textWidth);
    }
    aboutToAppear() {
        if (this.arcButtonTheme.BUTTON_HEIGHT === 0) {
            console.error("arcbutton can't obtain sys float value.");
            return;
        }
        this.initValues();
        this.dataProcessUtil.initData();
        const e4 = this.dataProcessUtil.calculate();
        this.generatePath(e4);
    }
    calculateActualPosition(a4, b4) {
        const c4 = this.getUIContext().vp2px(a4.x - b4.x);
        const d4 = this.getUIContext().vp2px(a4.y - b4.y);
        return new ArcButtonPoint(c4, d4);
    }
    generatePath(l3) {
        if (l3 === null) {
            return;
        }
        this.canvasWidth = l3.btnWidth + Constants.SHADOW_BLUR * 2;
        this.canvasHeight = l3.btnHeight + Constants.DISTANCE_FROM_BORDER * 2;
        const m3 = this.options.fontMargin;
        const n3 = m3?.start?.value ?? 0;
        const o3 = m3?.end?.value ?? 0;
        const p3 = m3?.top?.value ?? 0;
        const q3 = m3?.bottom?.value ?? 0;
        this.textWidth = l3.btnWidth - n3 - o3;
        this.textHeight = l3.btnHeight - p3 - q3;
        this.judgeTextWidth();
        const r3 = l3.canvasLeftTop;
        r3.x -= Constants.SHADOW_BLUR;
        r3.y -= Constants.DISTANCE_FROM_BORDER;
        const s3 = this.calculateActualPosition(l3.leftTopPoint, r3);
        const t3 = this.getUIContext().vp2px(this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2);
        const u3 = this.calculateActualPosition(l3.rightTopPoint, r3);
        const v3 = this.getUIContext().vp2px(this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS);
        const w3 = this.calculateActualPosition(l3.rightBottomPoint, r3);
        const x3 = this.getUIContext().vp2px(this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2);
        const y3 = this.calculateActualPosition(l3.leftBottomPoint, r3);
        const z3 = `M ${s3.x} ${s3.y} A ${t3} ${t3}, 0, 0, 0,
       ${u3.x} ${u3.y}` +
            `Q ${u3.x - v3 * 1.2} ${u3.y +
                v3 * 0.6} ${w3.x} ${w3.y}` +
            `A ${x3} ${x3}, 0, 0, 0, ${y3.x}
       ${y3.y}` +
            `Q ${s3.x + v3 * 1.2} ${s3.y +
                v3 * 0.6} ${s3.x} ${s3.y}`;
        this.pathString = z3;
    }
    TextBuilderIsExceed(i3 = null) {
        this.observeComponentCreation2((j3, k3) => {
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
    TextBuilderNormal(f3 = null) {
        this.observeComponentCreation2((g3, h3) => {
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
    cover(e3) {
        switch (e3.unit) {
            case LengthUnit.VP:
                return `${e3.value}vp`;
            case LengthUnit.PX:
                return `${e3.value}px`;
            case LengthUnit.FP:
                return `${e3.value}fp`;
            case LengthUnit.LPX:
                return `${e3.value}lpx`;
            case LengthUnit.PERCENT:
                return `${e3.value}%`;
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
        this.observeComponentCreation2((a3, b3) => {
            Stack.create({ alignContent: Alignment.Center });
            Context.animation({ curve: this.curves });
            Stack.enabled(this.options.status !== ArcButtonStatus.DISABLED);
            Stack.opacity((this.options.styleMode === ArcButtonStyleMode.EMPHASIZED_LIGHT &&
                this.options.status === ArcButtonStatus.DISABLED) ? Constants.DEFAULT_TRANSPARENCY : 1);
            Context.animation(null);
            Stack.width(this.canvasWidth);
            Stack.height(this.canvasHeight);
            Stack.scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.canvasHeight });
            Stack.onTouch((d3) => {
                this.dealTouchEvent(d3);
            });
            Stack.onClick((c3) => {
                if (this.options.onClick) {
                    this.options.onClick(c3);
                }
            });
        }, Stack);
        this.observeComponentCreation2((u2, v2) => {
            If.create();
            if (this.options.progressConfig) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y2, z2) => {
                        Progress.create({ value: this.progressValue, total: this.progressTotal, type: ProgressType.Capsule });
                        Progress.width('100%');
                        Progress.height('100%');
                        Progress.rotate({ angle: !this.isUp ? 0 : 180 });
                        Progress.clipShape(new Path({ commands: this.pathString }));
                        Progress.backgroundColor(this.btnColor.color);
                        Progress.color(this.progressColor?.color);
                        Progress.backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true });
                        Progress.shadow(this.getShadow());
                    }, Progress);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w2, x2) => {
                        Button.createWithLabel({ type: ButtonType.Normal, stateEffect: true });
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
        this.observeComponentCreation2((s2, t2) => {
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
    dealTouchEvent(p2) {
        const q2 = p2.touches[0].windowX;
        const r2 = p2.touches[0].windowY;
        if (this.options.onTouch) {
            this.options.onTouch(p2);
        }
        switch (p2.type) {
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
    updateStateVars(o2) {
        if (o2 === undefined) {
            return;
        }
        if ("options" in o2) {
            this.updateParam("options", o2.options);
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
    Monitor('options.label', 'options.type', 'options.fontSize', 'options.styleMode', 'options.status', 'options.backgroundColor', 'options.fontColor')
], ArcButton.prototype, "optionsChange", null);
__decorate([
    Monitor('options.progressConfig', 'options.progressConfig.color', 'options.progressConfig.total', 'options.progressConfig.value')
], ArcButton.prototype, "progressOptionsChange", null);
class DataProcessUtil {
    constructor(n2) {
        this.dial = new ArcButtonCircle(0, 0, 0);
        this.arc = new ArcButtonCircle(0, 0, 0);
        this.height = 0;
        this.width = 0;
        this.arcButtonTheme = undefined;
        this.arcButtonTheme = n2;
    }
    initData() {
        const j2 = this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2;
        this.dial = new ArcButtonCircle(j2, j2, j2);
        const k2 = this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2;
        this.height = this.arcButtonTheme.BUTTON_HEIGHT;
        const l2 = this.dial.center.x;
        const m2 = this.dial.center.y + j2 + k2 - this.height;
        this.arc = new ArcButtonCircle(k2, l2, m2);
    }
    calculate() {
        const a2 = this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS;
        const b2 = new ArcButtonCircle(this.dial.radius - a2, this.dial.center.x, this.dial.center.y);
        const c2 = new ArcButtonCircle(this.arc.radius - a2, this.arc.center.x, this.arc.center.y);
        const d2 = this.findCircleIntersections(c2, b2);
        const e2 = this.calculateIntersection(this.arc.center, this.arc.radius, d2[0]);
        const f2 = this.calculateIntersection(this.arc.center, this.arc.radius, d2[1]);
        const g2 = this.calculateIntersection(this.dial.center, this.dial.radius, d2[1]);
        const h2 = this.calculateIntersection(this.dial.center, this.dial.radius, d2[0]);
        this.width = this.calculateDistance(d2[0], d2[1]) + a2 * 2;
        const i2 = new ArcButtonPoint(d2[0].x - a2, this.dial.center.y +
            this.dial.radius - this.height);
        return new AllPoints(this.width, this.height, f2, e2, g2, h2, i2);
    }
    calculateDistance(y1, z1) {
        return Math.sqrt((z1.x - y1.x) ** 2 + (z1.y - y1.y) ** 2);
    }
    calculateIntersection(c1, d1, e1) {
        const f1 = c1.x;
        const g1 = c1.y;
        const h1 = e1.x;
        const i1 = e1.y;
        let j1 = 0;
        if (h1 !== f1) {
            j1 = (i1 - g1) / (h1 - f1);
        }
        else {
            j1 = -1;
        }
        let k1 = 0;
        if (j1 !== -1) {
            k1 = i1 - j1 * h1;
        }
        let l1 = [];
        if (j1 !== -1) {
            const r1 = Math.pow(j1, 2) + 1;
            const s1 = 2 * (j1 * k1 - j1 * g1 - f1);
            const t1 = g1 ** 2 - d1 ** 2 + f1 ** 2 - 2 * k1 * g1 + k1 ** 2;
            const u1 = (-s1 + (s1 ** 2 - 4 * r1 * t1) ** 0.5) / (2 * r1);
            const v1 = (-s1 - (s1 ** 2 - 4 * r1 * t1) ** 0.5) / (2 * r1);
            const w1 = j1 * u1 + k1;
            const x1 = j1 * v1 + k1;
            l1 = [new ArcButtonPoint(u1, w1), new ArcButtonPoint(v1, x1)];
        }
        else {
            const o1 = f1;
            const p1 = g1 + d1;
            const q1 = g1 - d1;
            l1 = [new ArcButtonPoint(o1, p1), new ArcButtonPoint(o1, q1)];
        }
        const m1 = this.calculateDistance(l1[0], e1);
        const n1 = this.calculateDistance(l1[1], e1);
        if (m1 < n1) {
            return l1[0];
        }
        else {
            return l1[1];
        }
    }
    findCircleIntersections(m, n) {
        const o = m.radius;
        const p = m.center.x;
        const q = m.center.y;
        const r = n.radius;
        const s = n.center.x;
        const t = n.center.y;
        const u = Math.sqrt((p - s) ** 2 + (q - t) ** 2);
        if (u > o + r) {
            return [];
        }
        else if (u < Math.abs(o - r)) {
            return [];
        }
        else if (u === 0 && o === r) {
            return [];
        }
        const v = (o ** 2 - r ** 2 + u ** 2) / (2 * u);
        const w = Math.sqrt(o ** 2 - v ** 2);
        const x = p + v * (s - p) / u;
        const y = q + v * (t - q) / u;
        let z = new ArcButtonPoint(x + w * (t - q) / u, y -
            w * (s - p) / u);
        let a1 = new ArcButtonPoint(x - w * (t - q) / u, y +
            w * (s - p) / u);
        if (z.x > a1.x) {
            const b1 = z;
            z = a1;
            a1 = b1;
        }
        return [z, a1];
    }
}
class ArcButtonCircle {
    constructor(j, k, l) {
        this.radius = j;
        this.center = new ArcButtonPoint(k, l);
    }
}
class ArcButtonPoint {
    constructor(h, i) {
        this.x = h;
        this.y = i;
    }
}
class AllPoints {
    constructor(a, b, c, d, e, f, g) {
        this.btnWidth = a;
        this.btnHeight = b;
        this.leftTopPoint = c;
        this.rightTopPoint = d;
        this.leftBottomPoint = e;
        this.rightBottomPoint = f;
        this.canvasLeftTop = g;
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
