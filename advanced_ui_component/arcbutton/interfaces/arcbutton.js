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

let __decorate =
    (this && this.__decorate) ||
    function (decorators, target, key, desc) {
        let c = arguments.length;
        let r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc;
        let d;
        if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
            r = Reflect.decorate(decorators, target, key, desc);
        } else {
            for (let i = decorators.length - 1; i >= 0; i--) {
            d = decorators[i];
            if (d) {
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
            }
        }
    }
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {});
}

const measure = requireNapi('measure');
const Curves = globalThis.requireNativeModule('ohos.curves');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const PathShape = requireNapi('arkui.shape').PathShape;

export let ArcButtonPosition;
(function (ArcButtonPosition) {
    ArcButtonPosition[(ArcButtonPosition['TOP_EDGE'] = 0)] = 'TOP_EDGE';
    ArcButtonPosition[(ArcButtonPosition['BOTTOM_EDGE'] = 1)] = 'BOTTOM_EDGE';
})(ArcButtonPosition || (ArcButtonPosition = {}));

export let ArcButtonStyleMode;
(function (ArcButtonStyleMode) {
    ArcButtonStyleMode[(ArcButtonStyleMode['EMPHASIZED_LIGHT'] = 0)] =
      'EMPHASIZED_LIGHT';
    ArcButtonStyleMode[(ArcButtonStyleMode['EMPHASIZED_DARK'] = 1)] =
      'EMPHASIZED_DARK';
    ArcButtonStyleMode[(ArcButtonStyleMode['NORMAL_LIGHT'] = 2)] = 'NORMAL_LIGHT';
    ArcButtonStyleMode[(ArcButtonStyleMode['NORMAL_DARK'] = 3)] = 'NORMAL_DARK';
    ArcButtonStyleMode[(ArcButtonStyleMode['CUSTOM'] = 4)] = 'CUSTOM';
})(ArcButtonStyleMode || (ArcButtonStyleMode = {}));

export let ArcButtonStatus;
(function (ArcButtonStatus) {
    ArcButtonStatus[(ArcButtonStatus['NORMAL'] = 0)] = 'NORMAL';
    ArcButtonStatus[(ArcButtonStatus['PRESSED'] = 1)] = 'PRESSED';
    ArcButtonStatus[(ArcButtonStatus['DISABLED'] = 2)] = 'DISABLED';
})(ArcButtonStatus || (ArcButtonStatus = {}));

class Constants {}

/**
 * 最大文字大小
 */
Constants.MAX_FONT_SIZE = 19;
/**
 * 最小文字大小
 */
Constants.MIN_FONT_SIZE = 13;
/**
 * 阴影半径
 */
Constants.SHADOW_BLUR = 4;
/**
 * Y偏移
 */
Constants.SHADOW_OFFSET_Y = 3;
/**
 * 按钮与边框距离
 */
Constants.DISTANCE_FROM_BORDER = 1;
/**
 * 文本间距
 */
Constants.TEXT_HORIZONTAL_MARGIN = 24;
Constants.TEXT_MARGIN_TOP = 10;
Constants.TEXT_MARGIN_BOTTOM = 16;
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
Constants.EMPHASIZED_NORMAL_BTN_COLOR = {
    id: -1,
    type: 10001,
    params: ['sys.color.comp_background_emphasize'],
    bundleName: '__harDefaultBundleName__',
    moduleName: '__harDefaultModuleName__',
}

let ArcButtonOptions = class ArcButtonOptions {
    constructor(options) {
        this.position = options.position ?? ArcButtonPosition.BOTTOM_EDGE;
        this.styleMode = options.styleMode ?? ArcButtonStyleMode.EMPHASIZED_LIGHT;
        this.status = options.status ?? ArcButtonStatus.NORMAL;
        this.label = options.label ?? '';
        this.backgroundBlurStyle = options.backgroundBlurStyle ?? BlurStyle.NONE;
        this.backgroundColor =
            options.backgroundColor ?? ColorMetrics.resourceColor(Color.Black);
        this.shadowColor =
            options.shadowColor ?? ColorMetrics.resourceColor('#000000');
        this.shadowEnabled = options.shadowEnabled ?? false;
        this.fontSize =
            options.fontSize ?? new LengthMetrics(Constants.MAX_FONT_SIZE);
        this.fontColor =
            options.fontColor ?? ColorMetrics.resourceColor(Color.White);
        this.pressedFontColor =
            options.pressedFontColor ?? ColorMetrics.resourceColor(Color.White);
        this.fontStyle = options.fontStyle ?? FontStyle.Normal;
        this.fontFamily = options.fontFamily ?? '';
        this.fontMargin = options.fontMargin ?? {
            start: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
            top: LengthMetrics.vp(Constants.TEXT_MARGIN_TOP),
            end: LengthMetrics.vp(Constants.TEXT_HORIZONTAL_MARGIN),
            bottom: LengthMetrics.vp(Constants.TEXT_MARGIN_BOTTOM),
        };
        this.onTouch = options.onTouch ?? (() => {});
        this.onClick = options.onClick ?? (() => {});
    }
};
__decorate([Trace], ArcButtonOptions.prototype, 'position', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'styleMode', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'status', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'label', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'backgroundBlurStyle', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'backgroundColor', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'shadowColor', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'shadowEnabled', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'fontSize', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'fontColor', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'pressedFontColor', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'fontStyle', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'fontFamily', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'fontMargin', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'onTouch', void 0);
__decorate([Trace], ArcButtonOptions.prototype, 'onClick', void 0);
ArcButtonOptions = __decorate([ObservedV2], ArcButtonOptions);

export { ArcButtonOptions };

export class ArcButton extends ViewV2 {
    constructor(
        parent,
        params,
        __localStorage,
        elmtId = -1,
        paramsLambda,
        extraInfo
    ) {
        super(parent, elmtId, extraInfo);
        this.initParam(
            'options',
            params && 'options' in params ? params.options : undefined
        );
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
            BUTTON_HEIGHT: this.getArcButtonThemeVpValue({
                id: -1,
                type: 10002,
                params: ['sys.float.arc_button_height'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
            }),
            ARC_CIRCLE_DIAMETER: this.getArcButtonThemeVpValue({
                id: -1,
                type: 10002,
                params: ['sys.float.arc_button_auxiliary_circle_diameter'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
            }),
            DIAL_CIRCLE_DIAMETER: this.getArcButtonThemeVpValue({
                id: -1,
                type: 10002,
                params: ['sys.float.arc_button_dial_circle_diameter'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
            }),
            CHAMFER_CIRCLE_RADIUS: this.getArcButtonThemeVpValue({
                id: -1,
                type: 10002,
                params: ['sys.float.arc_button_chamfer_radius'],
                bundleName: '__harDefaultBundleName__',
                moduleName: '__harDefaultModuleName__',
            }),
        };
        this.dataProcessUtil = new DataProcessUtil(this.arcButtonTheme);
        this.finalizeConstruction();
    }

    optionsChange() {
        this.fontSize = this.cover(this.options.fontSize);
        this.judgeTextWidth();
        this.changeStatus();
    }

    changeStatus() {
        switch (this.options.styleMode) {
            case ArcButtonStyleMode.EMPHASIZED_LIGHT:
                this.btnNormalColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZED_NORMAL_BTN_COLOR
                );
                this.textNormalColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZED_TEXT_COLOR
                );
                this.btnPressColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZED_PRESSED_BTN_COLOR
                );
                this.btnDisableColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZED_DISABLE_BTN_COLOR
                );
                this.textDisableColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZED_DISABLE_TEXT_COLOR
                );
                this.textPressColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZED_TEXT_COLOR
                );
                break;
            case ArcButtonStyleMode.NORMAL_LIGHT:
                this.btnNormalColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_LIGHT_NORMAL_BTN_COLOR
                );
                this.textNormalColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_LIGHT_TEXT_COLOR
                );
                this.btnPressColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_LIGHT_PRESSED_BTN_COLOR
                );
                this.btnDisableColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_LIGHT_DISABLE_BTN_COLOR
                );
                this.textDisableColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_LIGHT_DISABLE_TEXT_COLOR
                );
                this.textPressColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_LIGHT_TEXT_COLOR
                );
                break;
            case ArcButtonStyleMode.NORMAL_DARK:
                this.btnNormalColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_DARK_NORMAL_BTN_COLOR
                );
                this.textNormalColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_DARK_TEXT_COLOR
                );
                this.btnPressColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_DARK_PRESSED_BTN_COLOR
                );
                this.btnDisableColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_DARK_DISABLE_BTN_COLOR
                );
                this.textDisableColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_DARK_DISABLE_TEXT_COLOR
                );
                this.textPressColor = ColorMetrics.resourceColor(
                    Constants.NORMAL_DARK_TEXT_COLOR
                );
                break;
            case ArcButtonStyleMode.EMPHASIZED_DARK:
                this.btnNormalColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR
                );
                this.textNormalColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZEWARN_TEXT_COLOR
                );
                this.btnPressColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR
                );
                this.btnDisableColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR
                );
                this.textDisableColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR
                );
                this.textPressColor = ColorMetrics.resourceColor(
                    Constants.EMPHASIZEWARN_TEXT_COLOR
                );
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
        } else {
            this.btnColor = this.btnNormalColor;
            this.fontColor = this.textNormalColor;
        }
    }

    /**
     * 初始化数据
     */
    initValues() {
        this.isUp = this.options.position == ArcButtonPosition.TOP_EDGE;
        this.btnColor = this.options.backgroundColor;
        this.fontColor = this.options.fontColor;
        this.curves = Curves.interpolatingSpring(10, 1, 350, 35);
        this.scaleValue = 0.95;
        this.changeStatus();
    }

    getArcButtonThemeVpValue(res) {
        if (!res) {
        return 0;
        }
        let metrics = LengthMetrics.resource(res);
        let value = metrics.value;
        switch (metrics.unit) {
        case LengthUnit.PX:
            return px2vp(value);
        case LengthUnit.LPX:
            return px2vp(lpx2px(value));
        case LengthUnit.FP:
            return px2vp(fp2px(value));
        }
        return value;
    }

    /**
     * 判断是否超出文本框宽度
     */
    judgeTextWidth() {
        const measureTextWidth = measure.measureText({
            textContent: this.options.label,
            fontStyle: this.options.fontStyle,
            fontFamily: this.options.fontFamily,
            fontWeight: FontWeight.Medium,
            maxLines: 1,
            fontSize: `${Constants.MIN_FONT_SIZE}fp`,
        });
        this.isExceed =
            measureTextWidth > this.getUIContext().vp2px(this.textWidth);
    }

    aboutToAppear() {
        if (this.arcButtonTheme.BUTTON_HEIGHT === 0) {
            console.error("arcbutton can't obtain sys float value.");
            return;
        }
        this.initValues();
        this.dataProcessUtil.initData();
        const pathData = this.dataProcessUtil.calculate();
        this.generatePath(pathData);
    }

    calculateActualPosition(pos, canvasTopPos) {
        const x = this.getUIContext().vp2px(pos.x - canvasTopPos.x);
        const y = this.getUIContext().vp2px(pos.y - canvasTopPos.y);
        return new ArcButtonPoint(x, y);
    }

    generatePath(data) {
        if (data == null) {
            return;
        }
        this.canvasWidth = data.btnWidth + Constants.SHADOW_BLUR * 2;
        this.canvasHeight = data.btnHeight + Constants.DISTANCE_FROM_BORDER * 2;
        const margin = this.options.fontMargin;
        const start = margin?.start?.value ?? 0;
        const end = margin?.end?.value ?? 0;
        const top = margin?.top?.value ?? 0;
        const bottom = margin?.bottom?.value ?? 0;
        this.textWidth = data.btnWidth - start - end;
        this.textHeight = data.btnHeight - top - bottom;
        this.judgeTextWidth();
        const canvasLeftTopPoint = data.canvasLeftTop;
        canvasLeftTopPoint.x -= Constants.SHADOW_BLUR;
        canvasLeftTopPoint.y -= Constants.DISTANCE_FROM_BORDER;
        const leftTopPoint = this.calculateActualPosition(
            data.leftTopPoint,
            canvasLeftTopPoint
        );
        const upperArcCircleR = this.getUIContext().vp2px(
            this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2
        );
        const rightTopPoint = this.calculateActualPosition(
            data.rightTopPoint,
            canvasLeftTopPoint
        );
        const chamferCircleR = this.getUIContext().vp2px(
            this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS
        );
        const rightBottomPoint = this.calculateActualPosition(
            data.rightBottomPoint,
            canvasLeftTopPoint
        );
        const lowerArcCircleR = this.getUIContext().vp2px(
            this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2
        );
        const leftBottomPoint = this.calculateActualPosition(
            data.leftBottomPoint,
            canvasLeftTopPoint
        );
        const pathStr =
            `M ${leftTopPoint.x} ${leftTopPoint.y} A ${upperArcCircleR} ${upperArcCircleR}, 0, 0, 0,
            ${rightTopPoint.x} ${rightTopPoint.y}` +
            `Q ${rightTopPoint.x - chamferCircleR * 1.2} ${
            rightTopPoint.y + chamferCircleR * 0.6
            } ${rightBottomPoint.x} ${rightBottomPoint.y}` +
            `A ${lowerArcCircleR} ${lowerArcCircleR}, 0, 0, 0, ${leftBottomPoint.x}
            ${leftBottomPoint.y}` +
            `Q ${leftTopPoint.x + chamferCircleR * 1.2} ${
            leftTopPoint.y + chamferCircleR * 0.6
            } ${leftTopPoint.x} ${leftTopPoint.y}`;
        this.pathString = pathStr;
    }

    TextBuilderIsExceed(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                top: this.isUp
                    ? this.options.fontMargin.bottom
                    : this.options.fontMargin.top,
                end: this.options.fontMargin.end,
                bottom: this.options.fontMargin.bottom,
            });
        }, Text);
        Text.pop();
    }

    TextBuilderNormal(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.options.label);
            Text.width(this.textWidth);
            Text.height(this.textHeight);
            Text.textAlign(TextAlign.Center);
            Text.fontColor(this.fontColor.color);
            Text.maxFontSize(`${Constants.MAX_FONT_SIZE}fp`);
            Text.minFontSize(`${Constants.MIN_FONT_SIZE}fp`);
            Text.fontWeight(FontWeight.Medium);
            Text.fontStyle(this.options.fontStyle);
            Text.fontFamily(this.options.fontFamily);
            Text.maxLines(1);
            Text.margin({
                start: this.options.fontMargin.start,
                top: this.isUp
                    ? this.options.fontMargin.bottom
                    : this.options.fontMargin.top,
                end: this.options.fontMargin.end,
                bottom: this.options.fontMargin.bottom,
            });
        }, Text);
        Text.pop();
    }

    cover(params) {
        switch (params.unit) {
            case LengthUnit.VP:
                return `${params.value}vp`;
            case LengthUnit.PX:
                return `${params.value}px`;
            case LengthUnit.FP:
                return `${params.value}fp`;
            case LengthUnit.LPX:
                return `${params.value}lpx`;
            case LengthUnit.PERCENT:
                return `${params.value}%`;
        }
    }

    getShadow() {
        if (!this.options.shadowEnabled) {
            return undefined;
        }
        return {
            radius: Constants.SHADOW_BLUR,
            color: this.options.shadowColor.color,
            offsetY: Constants.SHADOW_OFFSET_Y,
        };
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Center });
            Context.animation({ curve: this.curves });
            Stack.enabled(this.options.status !== ArcButtonStatus.DISABLED);
            Stack.opacity(
                this.options.styleMode === ArcButtonStyleMode.EMPHASIZED_LIGHT &&
                    this.options.status === ArcButtonStatus.DISABLED
                    ? Constants.DEFAULT_TRANSPARENCY
                    : 1
            );
            Context.animation(null);
            Stack.width(this.canvasWidth);
            Stack.height(this.canvasHeight);
            Stack.scale({
                x: this.scaleX,
                y: this.scaleY,
                centerY: this.isUp ? 0 : this.canvasHeight,
            });
            Stack.onTouch((event) => {
                this.dealTouchEvent(event);
            });
            Stack.onClick((event) => {
                if (this.options.onClick) {
                    this.options.onClick(event);
                }
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.isExceed) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextBuilderIsExceed.bind(this)(this);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.TextBuilderNormal.bind(this)(this);
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }

    dealTouchEvent(event) {
        const x = event.touches[0].windowX;
        const y = event.touches[0].windowY;
        if (this.options.onTouch) {
            this.options.onTouch(event);
        }
        switch (event.type) {
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

    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ('options' in params) {
            this.updateParam('options', params.options);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([Param], ArcButton.prototype, 'options', void 0);
__decorate([Local], ArcButton.prototype, 'canvasWidth', void 0);
__decorate([Local], ArcButton.prototype, 'canvasHeight', void 0);
__decorate([Local], ArcButton.prototype, 'scaleX', void 0);
__decorate([Local], ArcButton.prototype, 'scaleY', void 0);
__decorate([Local], ArcButton.prototype, 'btnColor', void 0);
__decorate([Local], ArcButton.prototype, 'textWidth', void 0);
__decorate([Local], ArcButton.prototype, 'textHeight', void 0);
__decorate([Local], ArcButton.prototype, 'fontColor', void 0);
__decorate([Local], ArcButton.prototype, 'isExceed', void 0);
__decorate([Local], ArcButton.prototype, 'pathString', void 0);
__decorate([Local], ArcButton.prototype, 'fontSize', void 0);
__decorate(
    [
        Monitor(
        'options.label',
        'options.type',
        'options.fontSize',
        'options.styleMode',
        'options.status',
        'options.backgroundColor',
        'options.fontColor'
        ),
    ],
    ArcButton.prototype,
    'optionsChange',
    null
);

class DataProcessUtil {
    constructor(theme) {
        this.dial = new ArcButtonCircle(0, 0, 0);
        this.arc = new ArcButtonCircle(0, 0, 0);
        this.height = 0;
        this.width = 0;
        this.arcButtonTheme = undefined;
        this.arcButtonTheme = theme;
    }

    initData() {
        const dialRadius = this.arcButtonTheme.DIAL_CIRCLE_DIAMETER / 2;
        this.dial = new ArcButtonCircle(dialRadius, dialRadius, dialRadius);
        const arcRadius = this.arcButtonTheme.ARC_CIRCLE_DIAMETER / 2;
        this.height = this.arcButtonTheme.BUTTON_HEIGHT;
        const arcX = this.dial.center.x;
        const arcY = this.dial.center.y + dialRadius + arcRadius - this.height;
        this.arc = new ArcButtonCircle(arcRadius, arcX, arcY);
    }

    calculate() {
        const chamferCircleR = this.arcButtonTheme.CHAMFER_CIRCLE_RADIUS;
        const innerDial = new ArcButtonCircle(
            this.dial.radius - chamferCircleR,
            this.dial.center.x,
            this.dial.center.y
        );
        const innerArc = new ArcButtonCircle(
            this.arc.radius - chamferCircleR,
            this.arc.center.x,
            this.arc.center.y
        );
        const intersections = this.findCircleIntersections(innerArc, innerDial);
        const tp1 = this.calculateIntersection(
            this.arc.center,
            this.arc.radius,
            intersections[0]
        );
        const tp2 = this.calculateIntersection(
            this.arc.center,
            this.arc.radius,
            intersections[1]
        );
        const tp3 = this.calculateIntersection(
            this.dial.center,
            this.dial.radius,
            intersections[1]
        );
        const tp4 = this.calculateIntersection(
            this.dial.center,
            this.dial.radius,
            intersections[0]
        );
        this.width =
        this.calculateDistance(intersections[0], intersections[1]) +
            chamferCircleR * 2;
        const canvasLeftTop = new ArcButtonPoint(
            intersections[0].x - chamferCircleR,
            this.dial.center.y + this.dial.radius - this.height
        );
        return new AllPoints(
            this.width,
            this.height,
            tp2,
            tp1,
            tp3,
            tp4,
            canvasLeftTop
        );
    }

    /**
     * 计算两点间距离
     * @param point1 点1
     * @param point2 点2
     * @returns 距离
     */
    calculateDistance(point1, point2) {
        return Math.sqrt((point2.x - point1.x) ** 2 + (point2.y - point1.y) ** 2);
    }

    calculateIntersection(circleCenter, circleRadius, point) {
        const h = circleCenter.x;
        const k = circleCenter.y;
        const x = point.x;
        const y = point.y;
        //计算直线斜率
        let m = 0;
        if (x != h) {
            m = (y - k) / (x - h);
        } else {
            m = -1;
        }
        //计算截距
        let intercept = 0;
        if (m != -1) {
            intercept = y - m * x;
        }
        //保存焦点位置
        let resultPoint = [];
        //判断斜率
        if (m != -1) {
            const a = Math.pow(m, 2) + 1;
            const b = 2 * (m * intercept - m * k - h);
            const c =
                k ** 2 -
                circleRadius ** 2 +
                h ** 2 -
                2 * intercept * k +
                intercept ** 2;
            const x1 = (-b + (b ** 2 - 4 * a * c) ** 0.5) / (2 * a);
            const x2 = (-b - (b ** 2 - 4 * a * c) ** 0.5) / (2 * a);
            const y1 = m * x1 + intercept;
            const y2 = m * x2 + intercept;
            resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x2, y2)];
        } else {
            const x1 = h;
            const y1 = k + circleRadius;
            const y2 = k - circleRadius;
            resultPoint = [new ArcButtonPoint(x1, y1), new ArcButtonPoint(x1, y2)];
        }
        const d1 = this.calculateDistance(resultPoint[0], point);
        const d2 = this.calculateDistance(resultPoint[1], point);
        if (d1 < d2) {
            return resultPoint[0];
        } else {
            return resultPoint[1];
        }
    }

    /**
     * 查找两圆的交点
     * @param C1 第一个圆
     * @param c2 第二个圆
     * @returns 两圆相交的点的数组
     */
    findCircleIntersections(firstCircus, secondCircus) {
        const firstCircusR = firstCircus.radius;
        const firstCircusCenterX = firstCircus.center.x;
        const firstCircusCenterY = firstCircus.center.y;
        const secondCircusR = secondCircus.radius;
        const secondCircusCenterX = secondCircus.center.x;
        const secondCircusCenterY = secondCircus.center.y;
        // 计算两个圆心之间的距离
        const distance = Math.sqrt(
            (firstCircusCenterX - secondCircusCenterX) ** 2 +
            (firstCircusCenterY - secondCircusCenterY) ** 2
        );
        // 检查异常情况
        if (distance > firstCircusR + secondCircusR) {
            //两个圆分离，不相交
            return [];
        } else if (distance < Math.abs(firstCircusR - secondCircusR)) {
            //一个圆包含在另一个圆内，不相交
            return [];
        } else if (distance === 0 && firstCircusR === secondCircusR) {
            //两个圆完全重合，具有无穷多交点
            return [];
        }
        // 计算交点
        const a =
            (firstCircusR ** 2 - secondCircusR ** 2 + distance ** 2) / (2 * distance);
        const h = Math.sqrt(firstCircusR ** 2 - a ** 2);
        // 中间变量
        const x2 =
            firstCircusCenterX +
            (a * (secondCircusCenterX - firstCircusCenterX)) / distance;
        const y2 =
            firstCircusCenterY +
            (a * (secondCircusCenterY - firstCircusCenterY)) / distance;
        // 交点
        let intersection1 = new ArcButtonPoint(
            x2 + (h * (secondCircusCenterY - firstCircusCenterY)) / distance,
            y2 - (h * (secondCircusCenterX - firstCircusCenterX)) / distance
        );
        let intersection2 = new ArcButtonPoint(
            x2 - (h * (secondCircusCenterY - firstCircusCenterY)) / distance,
            y2 + (h * (secondCircusCenterX - firstCircusCenterX)) / distance
        );
        if (intersection1.x > intersection2.x) {
            const mid = intersection1;
            intersection1 = intersection2;
            intersection2 = mid;
        }
        return [intersection1, intersection2];
    }
}

class ArcButtonCircle {
    constructor(radius, x, y) {
        this.radius = radius;
        this.center = new ArcButtonPoint(x, y);
    }
}

class ArcButtonPoint {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

class AllPoints {
    constructor(
        btnWidth,
        btnHeight,
        leftTopPoint,
        rightTopPoint,
        leftBottomPoint,
        rightBottomPoint,
        canvasLeftTop
    ) {
        this.btnWidth = btnWidth;
        this.btnHeight = btnHeight;
        this.leftTopPoint = leftTopPoint;
        this.rightTopPoint = rightTopPoint;
        this.leftBottomPoint = leftBottomPoint;
        this.rightBottomPoint = rightBottomPoint;
        this.canvasLeftTop = canvasLeftTop;
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
