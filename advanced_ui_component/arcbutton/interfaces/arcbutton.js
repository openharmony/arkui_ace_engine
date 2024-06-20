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

var __decorate = this && this.__decorate || function (t, e, s, i) {
    var o, n = arguments.length, r = n < 3 ? e : null === i ? i = Object.getOwnPropertyDescriptor(e, s) : i;
    if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) r = Reflect.decorate(t, e, s, i); else for (var a = t.length - 1; a >= 0; a--) (o = t[a]) && (r = (n < 3 ? o(r) : n > 3 ? o(e, s, r) : o(e, s)) || r);
    return n > 3 && r && Object.defineProperty(e, s, r), r
};
const measure = globalThis.requireNapi("measure");
const Curves = globalThis.requireNativeModule("ohos.curves");

export var TYPE_MODE;
!function(t){
    t[t.UP_ARC=0] = "UP_ARC";
    t[t.DOWN_ARC=1] = "DOWN_ARC"
}(TYPE_MODE || (TYPE_MODE = {}));

export var ARC_BUTTON_STYLE_MODE;
!function(t){
    t[t.EMPHASIZED=0] = "EMPHASIZED";
    t[t.NORMAL01=1] = "NORMAL01";
    t[t.NORMAL02=2] = "NORMAL02";
    t[t.EMPHASIZEWARN=3] = "EMPHASIZEWARN"
}(ARC_BUTTON_STYLE_MODE || (ARC_BUTTON_STYLE_MODE = {}));

export var ARC_BUTTON_STATUS;
!function(t){
    t[t.NORMAL=0] = "NORMAL";
    t[t.PRESSED=1] = "PRESSED";
    t[t.UNAVAILABLE=2] = "UNAVAILABLE"
}(ARC_BUTTON_STATUS || (ARC_BUTTON_STATUS = {}));

export var CLICK_EFFECT_STATUS;
!function(t){
    t[t.NONE=0] = "NONE";
    t[t.LIGHT=1] = "LIGHT";
    t[t.MIDDLE=2] = "MIDDLE";
    t[t.HEAVY=3] = "HEAVY"
}(CLICK_EFFECT_STATUS || (CLICK_EFFECT_STATUS = {}));

export class Margin {
}
let ArcButtonOptions = class {
    constructor(t) {
        var e, s, i, o, n, r, a, l, h, C, _, c, p, E, R;
        this.type = null !== (e = t.type) && void 0 !== e ? e : TYPE_MODE.DOWN_ARC;
        this.width = null !== (s = t.width) && void 0 !== s ? s : Constants.UPPER_ARC_CIRCLE_R;
        this.height = null !== (i = t.height) && void 0 !== i ? i : Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R + Constants.UPPER_ARC_CIRCLE_R - Constants.UPPER_ARC_CIRCLE_CENTER_Y;
        this.styleMode = null !== (o = t.styleMode) && void 0 !== o ? o : ARC_BUTTON_STYLE_MODE.EMPHASIZED;
        this.status = null !== (n = t.status) && void 0 !== n ? n : ARC_BUTTON_STATUS.NORMAL;
        this.resourceText = null !== (r = t.resourceText) && void 0 !== r ? r : "";
        this.touchEffect = null !== (a = t.touchEffect) && void 0 !== a ? a : CLICK_EFFECT_STATUS.NONE;
        this.backgroundColor = null !== (l = t.backgroundColor) && void 0 !== l ? l : Color.Black;
        this.shadowColor = null !== (h = t.shadowColor) && void 0 !== h ? h : "#000000";
        this.shadowEnabled = null !== (C = t.shadowEnabled) && void 0 !== C && C;
        this.textSize = null !== (_ = t.textSize) && void 0 !== _ ? _ : Constants.MAX_FONT_SIZE;
        this.textColor = null !== (c = t.textColor) && void 0 !== c ? c : Color.White;
        this.pressedTextColor = null !== (p = t.pressedTextColor) && void 0 !== p ? p : Color.White;
        this.textStyle = null !== (E = t.textStyle) && void 0 !== E ? E : FontStyle.Normal;
        this.textFamily = t.textFamily;
        this.textMargin = null !== (R = t.textMargin) && void 0 !== R ? R : {
            left: Constants.TEXT_HORIZONTAL_MARGIN,
            top: Constants.TEXT_MARGIN_TOP,
            right: Constants.TEXT_HORIZONTAL_MARGIN,
            bottom: Constants.TEXT_MARGIN_BOTTOM
        }
    }
};
ArcButtonOptions = __decorate([Observed], ArcButtonOptions);

export { ArcButtonOptions };

export class ArcButton extends ViewPU {
    constructor(t, e, s, i = -1, o = void 0) {
        super(t, s, i);
        "function" == typeof o && (this.paramsGenerator_ = o);
        this.__options = new SynchedPropertyNesedObjectPU(e.options, this, "options");
        this.__btnColor = new ObservedPropertySimplePU(Color.Black, this, "btnColor");
        this.btnNormalColor = Color.Black;
        this.btnPressColor = Color.Black;
        this.btnDisableColor = Color.Black;
        this.textNormalColor = Color.White;
        this.textDisableColor = Color.White;
        this.__pathStr = new ObservedPropertySimplePU("", this, "pathStr");
        this.__btnWidth = new ObservedPropertySimplePU(0, this, "btnWidth");
        this.__btnHeight = new ObservedPropertySimplePU(0, this, "btnHeight");
        this.__scaleX = new ObservedPropertySimplePU(1, this, "scaleX");
        this.__scaleY = new ObservedPropertySimplePU(1, this, "scaleY");
        this.__translateY = new ObservedPropertySimplePU(0, this, "translateY");
        this.isUp = !1;
        this.__textWidth = new ObservedPropertySimplePU(0, this, "textWidth");
        this.__textHeight = new ObservedPropertySimplePU(0, this, "textHeight");
        this.__textColor = new ObservedPropertySimplePU(Color.White, this, "textColor");
        this.__isExceed = new ObservedPropertySimplePU(!1, this, "isExceed");
        this.settings = new RenderingContextSettings(!0);
        this.context = new CanvasRenderingContext2D(this.settings);
        this.__isReady = new ObservedPropertySimplePU(!1, this, "isReady");
        this.curves = {};
        this.scaleValue = 1;
        this.startTime = 0;
        this.calStartTime = 0;
        this.path2D = void 0;
        this.circularCrossPointUtil = void 0;
        this.upperArcCircleR = 0;
        this.upperArcCircleY = 0;
        this.setInitiallyProvidedValue(e);
        this.declareWatch("options", this.optionsChange);
        this.declareWatch("btnColor", this.doDraw);
        this.declareWatch("pathStr", this.doDraw);
        this.declareWatch("isReady", this.doDraw)
    }

    setInitiallyProvidedValue(t) {
        this.__options.set(t.options);
        void 0 !== t.btnColor && (this.btnColor = t.btnColor);
        void 0 !== t.btnNormalColor && (this.btnNormalColor = t.btnNormalColor);
        void 0 !== t.btnPressColor && (this.btnPressColor = t.btnPressColor);
        void 0 !== t.btnDisableColor && (this.btnDisableColor = t.btnDisableColor);
        void 0 !== t.textNormalColor && (this.textNormalColor = t.textNormalColor);
        void 0 !== t.textDisableColor && (this.textDisableColor = t.textDisableColor);
        void 0 !== t.pathStr && (this.pathStr = t.pathStr);
        void 0 !== t.btnWidth && (this.btnWidth = t.btnWidth);
        void 0 !== t.btnHeight && (this.btnHeight = t.btnHeight);
        void 0 !== t.scaleX && (this.scaleX = t.scaleX);
        void 0 !== t.scaleY && (this.scaleY = t.scaleY);
        void 0 !== t.translateY && (this.translateY = t.translateY);
        void 0 !== t.isUp && (this.isUp = t.isUp);
        void 0 !== t.textWidth && (this.textWidth = t.textWidth);
        void 0 !== t.textHeight && (this.textHeight = t.textHeight);
        void 0 !== t.textColor && (this.textColor = t.textColor);
        void 0 !== t.isExceed && (this.isExceed = t.isExceed);
        void 0 !== t.settings && (this.settings = t.settings);
        void 0 !== t.context && (this.context = t.context);
        void 0 !== t.isReady && (this.isReady = t.isReady);
        void 0 !== t.curves && (this.curves = t.curves);
        void 0 !== t.scaleValue && (this.scaleValue = t.scaleValue);
        void 0 !== t.startTime && (this.startTime = t.startTime);
        void 0 !== t.calStartTime && (this.calStartTime = t.calStartTime);
        void 0 !== t.path2D && (this.path2D = t.path2D);
        void 0 !== t.circularCrossPointUtil && (this.circularCrossPointUtil = t.circularCrossPointUtil);
        void 0 !== t.upperArcCircleR && (this.upperArcCircleR = t.upperArcCircleR);
        void 0 !== t.upperArcCircleY && (this.upperArcCircleY = t.upperArcCircleY)
    }

    updateStateVars(t) {
        this.__options.set(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__options.purgeDependencyOnElmtId(t);
        this.__btnColor.purgeDependencyOnElmtId(t);
        this.__pathStr.purgeDependencyOnElmtId(t);
        this.__btnWidth.purgeDependencyOnElmtId(t);
        this.__btnHeight.purgeDependencyOnElmtId(t);
        this.__scaleX.purgeDependencyOnElmtId(t);
        this.__scaleY.purgeDependencyOnElmtId(t);
        this.__translateY.purgeDependencyOnElmtId(t);
        this.__textWidth.purgeDependencyOnElmtId(t);
        this.__textHeight.purgeDependencyOnElmtId(t);
        this.__textColor.purgeDependencyOnElmtId(t);
        this.__isExceed.purgeDependencyOnElmtId(t);
        this.__isReady.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__btnColor.aboutToBeDeleted();
        this.__pathStr.aboutToBeDeleted();
        this.__btnWidth.aboutToBeDeleted();
        this.__btnHeight.aboutToBeDeleted();
        this.__scaleX.aboutToBeDeleted();
        this.__scaleY.aboutToBeDeleted();
        this.__translateY.aboutToBeDeleted();
        this.__textWidth.aboutToBeDeleted();
        this.__textHeight.aboutToBeDeleted();
        this.__textColor.aboutToBeDeleted();
        this.__isExceed.aboutToBeDeleted();
        this.__isReady.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    get btnColor() {
        return this.__btnColor.get()
    }

    set btnColor(t) {
        this.__btnColor.set(t)
    }

    get pathStr() {
        return this.__pathStr.get()
    }

    set pathStr(t) {
        this.__pathStr.set(t)
    }

    get btnWidth() {
        return this.__btnWidth.get()
    }

    set btnWidth(t) {
        this.__btnWidth.set(t)
    }

    get btnHeight() {
        return this.__btnHeight.get()
    }

    set btnHeight(t) {
        this.__btnHeight.set(t)
    }

    get scaleX() {
        return this.__scaleX.get()
    }

    set scaleX(t) {
        this.__scaleX.set(t)
    }

    get scaleY() {
        return this.__scaleY.get()
    }

    set scaleY(t) {
        this.__scaleY.set(t)
    }

    get translateY() {
        return this.__translateY.get()
    }

    set translateY(t) {
        this.__translateY.set(t)
    }

    get textWidth() {
        return this.__textWidth.get()
    }

    set textWidth(t) {
        this.__textWidth.set(t)
    }

    get textHeight() {
        return this.__textHeight.get()
    }

    set textHeight(t) {
        this.__textHeight.set(t)
    }

    get textColor() {
        return this.__textColor.get()
    }

    set textColor(t) {
        this.__textColor.set(t)
    }

    get isExceed() {
        return this.__isExceed.get()
    }

    set isExceed(t) {
        this.__isExceed.set(t)
    }

    get isReady() {
        return this.__isReady.get()
    }

    set isReady(t) {
        this.__isReady.set(t)
    }

    optionsChange() {
        this.judgeTextWidth();
        this.btnColor = this.options.backgroundColor;
        this.textColor = this.options.textColor;
        this.changeStatus()
    }

    changeStatus() {
        switch (this.options.styleMode) {
            case ARC_BUTTON_STYLE_MODE.EMPHASIZED:
                this.btnNormalColor = Constants.EMPHASIZED_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.EMPHASIZED_TEXT_COLOR;
                this.btnPressColor = Constants.EMPHASIZED_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.EMPHASIZED_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.EMPHASIZED_DISABLE_TEXT_COLOR;
                break;
            case ARC_BUTTON_STYLE_MODE.NORMAL01:
                this.btnNormalColor = Constants.NORMAL01_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.NORMAL01_TEXT_COLOR;
                this.btnPressColor = Constants.NORMAL01_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.NORMAL01_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.NORMAL01_DISABLE_TEXT_COLOR;
                break;
            case ARC_BUTTON_STYLE_MODE.NORMAL02:
                this.btnNormalColor = Constants.NORMAL02_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.NORMAL02_TEXT_COLOR;
                this.btnPressColor = Constants.NORMAL02_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.NORMAL02_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.NORMAL02_DISABLE_TEXT_COLOR;
                break;
            case ARC_BUTTON_STYLE_MODE.EMPHASIZEWARN:
                this.btnNormalColor = Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR;
                this.textNormalColor = Constants.EMPHASIZEWARN_TEXT_COLOR;
                this.btnPressColor = Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR;
                this.btnDisableColor = Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR;
                this.textDisableColor = Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR
        }
        if (this.options.status === ARC_BUTTON_STATUS.UNAVAILABLE) {
            this.btnColor = this.btnDisableColor;
            this.textColor = this.textDisableColor
        } else {
            this.btnColor = this.btnNormalColor;
            this.textColor = this.textNormalColor
        }
    }

    initValues() {
        this.isUp = this.options.type == TYPE_MODE.UP_ARC;
        this.btnColor = this.options.backgroundColor;
        this.textColor = this.options.textColor;
        switch (this.options.touchEffect) {
            case CLICK_EFFECT_STATUS.LIGHT:
                this.curves = Curves.interpolatingSpring(10, 1, 410, 38);
                this.scaleValue = .9;
                break;
            case CLICK_EFFECT_STATUS.MIDDLE:
                this.curves = Curves.interpolatingSpring(10, 1, 350, 35);
                this.scaleValue = .95;
                break;
            case CLICK_EFFECT_STATUS.HEAVY:
                this.curves = Curves.interpolatingSpring(0, 1, 240, 28);
                this.scaleValue = .95
        }
        this.changeStatus()
    }

    judgeTextWidth() {
        let t = measure.measureText({ textContent: this.options.resourceText, fontSize: this.options.textSize });
        console.info("mitang measureTextWidth = " + JSON.stringify(t));
        this.isExceed = t > vp2px(this.textWidth)
    }

    aboutToAppear() {
        this.startTime = (new Date).getTime();
        console.info("mitang aboutToAppear start time = " + this.startTime);
        this.initValues();
        this.calStartTime = (new Date).getTime();
        console.info("mitang calculate start time = " + this.calStartTime);
        this.upperArcCircleR = this.options.width;
        this.upperArcCircleY = Constants.LOWER_ARC_CIRCLE_CENTER_Y + Constants.LOWER_ARC_CIRCLE_R + this.upperArcCircleR - this.options.height;
        this.circularCrossPointUtil = new CircularCrossPointUtil(this.upperArcCircleR, this.upperArcCircleY);
        this.circularCrossPointUtil.calculate().then((t => {
            console.info("mitang calculate end time = " + ((new Date).getTime() - this.calStartTime));
            console.info("mitang data = " + JSON.stringify(t));
            this.btnWidth = t.width + 2 * Constants.SHADOW_BLUR;
            this.isUp ? this.btnHeight = t.height + Constants.SHADOW_BLUR + Constants.SHADOW_OFFSET_Y : this.btnHeight = t.height + 2 * Constants.DISTANCE_FROM_BORDER;
            this.textWidth = t.width - this.options.textMargin.left - this.options.textMargin.right;
            console.info("mitang judgeTextWidth start time = " + (new Date).getTime());
            this.judgeTextWidth();
            console.info("mitang judgeTextWidth end time = " + (new Date).getTime());
            this.textHeight = t.height - this.options.textMargin.top - this.options.textMargin.bottom;
            let e = t.leftTopPoint;
            let s = t.rightTopPoint;
            let i = t.leftBottomPoint;
            let o = t.rightBottomPoint;
            let n = t.canvasLeftTop;
            n.x -= Constants.SHADOW_BLUR;
            n.y -= Constants.DISTANCE_FROM_BORDER;
            let r = `M ${vp2px(e.x - n.x)} ${vp2px(e.y - n.y)}\n        A ${vp2px(Constants.UPPER_ARC_CIRCLE_R)} ${vp2px(Constants.UPPER_ARC_CIRCLE_R)},\n        0, 0, 0, ${vp2px(s.x - n.x)} ${vp2px(s.y - n.y)} M ${vp2px(s.x - n.x)} ${vp2px(s.y - n.y)}\n          A ${vp2px(Constants.CHAMFER_CIRCLE_R)} ${vp2px(Constants.CHAMFER_CIRCLE_R)}, 0, 0, 0,\n          ${vp2px(o.x - n.x)} ${vp2px(o.y - n.y)} M ${vp2px(o.x - n.x)} ${vp2px(o.y - n.y)}\n          A ${vp2px(Constants.LOWER_ARC_CIRCLE_R)} ${vp2px(Constants.LOWER_ARC_CIRCLE_R)},\n          0, 0, 0, ${vp2px(i.x - n.x)} ${vp2px(i.y - n.y)} M ${vp2px(i.x - n.x)} ${vp2px(i.y - n.y)}\n          A ${vp2px(Constants.CHAMFER_CIRCLE_R)} ${vp2px(Constants.CHAMFER_CIRCLE_R)}, 0, 0, 0,\n          ${vp2px(e.x - n.x)} ${vp2px(e.y - n.y)} M ${vp2px(e.x - n.x)} ${vp2px(e.y - n.y)}\n          L ${vp2px(s.x - n.x)} ${vp2px(s.y - n.y)}\n          L ${vp2px(o.x - n.x)} ${vp2px(o.y - n.y)}\n          L ${vp2px(i.x - n.x)} ${vp2px(i.y - n.y)}\n          L ${vp2px(e.x - n.x)} ${vp2px(e.y - n.y)}`;
            this.path2D = new Path2D(r);
            console.info("mitang calculate pathStr end time = " + ((new Date).getTime() - this.calStartTime))
        }));
        console.info("mitang aboutToAppear end time = " + (new Date).getTime())
    }

    doDraw() {
        if (!this.isReady || void 0 === this.path2D) return;
        let t = (new Date).getTime();
        console.info("mitang doDraw start time = " + t);
        if (this.options.shadowEnabled) {
            this.context.shadowBlur = Constants.SHADOW_BLUR;
            this.context.shadowOffsetY = -Constants.SHADOW_OFFSET_Y;
            this.context.shadowColor = this.options.shadowColor
        }
        this.context.beginPath();
        this.context.fillStyle = this.btnColor;
        this.context.fill(this.path2D);
        console.info("mitang doDraw end time = " + (new Date).getTime())
    }

    buildLog() {
        console.info("mitang buildLog time = " + (new Date).getTime());
        return !0
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create({ alignContent: Alignment.Top });
            Context.animation(null);
            Stack.width(this.btnWidth);
            Stack.height(this.btnHeight);
            Stack.enabled(this.options.status !== ARC_BUTTON_STATUS.UNAVAILABLE);
            Stack.opacity(this.options.status === ARC_BUTTON_STATUS.UNAVAILABLE ? .4 : 1);
            Stack.scale({ x: this.scaleX, y: this.scaleY, centerY: this.isUp ? 0 : this.btnHeight });
            Stack.translate({ y: this.translateY });
            Stack.onTouch((t => {
                console.info(`mitang onTouch event = ${JSON.stringify(t)}`);
                let e = t.touches[0].windowX;
                let s = t.touches[0].windowY;
                console.info(`mitang onTouch x = ${e}, y = ${s}`);
                switch (t.type) {
                    case TouchType.Down:
                        let t = this.circularCrossPointUtil.isPointInPath(e, s, this.isUp);
                        console.info(`mitang onTouch isInPath = ${t}`);
                        if (!t) return;
                        this.scaleX = this.scaleValue;
                        this.scaleY = this.scaleValue;
                        this.btnColor = this.btnPressColor;
                        break;
                    case TouchType.Up:
                        this.scaleX = 1;
                        this.scaleY = 1;
                        this.btnColor = this.btnNormalColor
                }
            }));
            Stack.onClick((t => {
                console.info(`mitang onClick x = ${t.x}, y = ${t.y}`)
            }));
            e || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.buildLog() ? this.ifElseBranchUpdateFunction(0, (() => {
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Canvas.create(this.context);
            Canvas.onReady((() => {
                console.info("mitang isReady time = " + (new Date).getTime());
                this.isReady = !0
            }));
            Canvas.width(this.btnWidth);
            Canvas.height(this.btnHeight);
            Canvas.rotate({ angle: this.isUp ? 0 : 180 });
            e || Canvas.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Canvas.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.isExceed ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(this.options.resourceText);
                    Text.width(this.textWidth);
                    Text.height(this.textHeight);
                    Text.fontColor(this.textColor);
                    Text.fontSize(this.options.textSize);
                    Text.fontWeight(FontWeight.Medium);
                    Text.fontStyle(this.options.textStyle);
                    Text.fontFamily(this.options.textFamily);
                    Text.maxLines(1);
                    Text.textOverflow({ overflow: TextOverflow.MARQUEE });
                    Text.margin({ top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top });
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(this.options.resourceText);
                    Text.width(this.textWidth);
                    Text.height(this.textHeight);
                    Text.textAlign(TextAlign.Center);
                    Text.fontColor(this.textColor);
                    Text.maxFontSize(this.options.textSize);
                    Text.minFontSize(Constants.MIN_FONT_SIZE);
                    Text.fontWeight(FontWeight.Medium);
                    Text.fontStyle(this.options.textStyle);
                    Text.fontFamily(this.options.textFamily);
                    Text.maxLines(1);
                    Text.margin({ top: this.isUp ? this.options.textMargin.bottom : this.options.textMargin.top });
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop()
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Stack.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

class CircularCrossPointUtil {
    constructor(t, e) {
        this.mirrorUpperArcCircleY = 0;
        this.upperArcCircleY = 0;
        this.upperArcCircleR = 0;
        this.upperArcCircleR = t;
        this.upperArcCircleY = e;
        this.mirrorUpperArcCircleY = Constants.LOWER_ARC_CIRCLE_CENTER_Y - this.calculateDistance(Constants.LOWER_ARC_CIRCLE_CENTER_X, Constants.LOWER_ARC_CIRCLE_CENTER_Y, Constants.UPPER_ARC_CIRCLE_CENTER_X, this.upperArcCircleY);
        console.info(`mitang mirrorUpperArcCircleY : ${JSON.stringify(this.mirrorUpperArcCircleY)}`)
    }

    async calculate() {
        let t = new AllPoints;
        let e = Constants.LOWER_ARC_CIRCLE_R;
        let s = Constants.LOWER_ARC_CIRCLE_CENTER_X;
        let i = Constants.LOWER_ARC_CIRCLE_CENTER_Y;
        let o = Constants.UPPER_ARC_CIRCLE_CENTER_X;
        let n = Constants.CHAMFER_CIRCLE_R;
        let r = new Circle(this.upperArcCircleR, s, i);
        let a = new Circle(e, o, this.upperArcCircleY);
        let l = this.findCircleIntersections(r, a);
        if (l.length > 1) {
            let r = l[0];
            let a = l[1];
            console.info("mitang 外圆交点");
            console.info(`mitang 交点1:${JSON.stringify(r)}`);
            console.info(`mitang 交点2:${JSON.stringify(a)}`);
            let h = this.findCircleIntersections(new Circle(this.upperArcCircleR - n, s, i), new Circle(e - n, o, this.upperArcCircleY));
            if (h.length > 1) {
                r = h[0];
                a = h[1];
                console.info("mitang 内圆交点-倒角圆圆心");
                if (r.x > a.x) {
                    let t = r;
                    r = a;
                    a = t
                }
                console.info(`mitang 交点1:${JSON.stringify(r)}`);
                console.info(`mitang 交点2:${JSON.stringify(a)}`);
                let l = this.calculateIntersection(new Point(s, i), this.upperArcCircleR, new Point(r.x, r.y));
                let C = this.calculateIntersection(new Point(s, i), this.upperArcCircleR, new Point(a.x, a.y));
                let _ = this.calculateIntersection(new Point(o, this.upperArcCircleY), e, new Point(a.x, a.y));
                let c = this.calculateIntersection(new Point(o, this.upperArcCircleY), e, new Point(r.x, r.y));
                console.info(`mitang tp1 = ${JSON.stringify(l)}`);
                console.info(`mitang tp2 = ${JSON.stringify(C)}`);
                console.info(`mitang tp3 = ${JSON.stringify(_)}`);
                console.info(`mitang tp4 = ${JSON.stringify(c)}`);
                t.leftTopPoint = l;
                t.rightTopPoint = C;
                t.rightBottomPoint = _;
                t.leftBottomPoint = c;
                let p = this.calculateDistance(r.x, r.y, a.x, a.y) + 2 * n;
                t.width = p;
                console.info(`mitang width = ${p}`);
                let E = this.upperArcCircleR + e - this.calculateDistance(s, i, o, this.upperArcCircleY);
                t.height = E;
                console.info(`mitang height = ${E}`);
                let R = new Point(r.x - n, this.upperArcCircleY - e);
                t.canvasLeftTop = R
            }
        }
        return t
    }

    isPointInPath(t, e, s) {
        return this.calculateDistance(t, e, Constants.UPPER_ARC_CIRCLE_CENTER_X, s ? this.mirrorUpperArcCircleY : this.upperArcCircleY) <= Constants.UPPER_ARC_CIRCLE_R
    }

    calculateDistance(t, e, s, i) {
        return Math.sqrt((s - t)**2 + (i - e)**2)
    }

    calculateIntersection(t, e, s) {
        let i = t.x;
        let o = t.y;
        let n = s.x;
        let r = s.y;
        let a;
        a = n != i ? (r - o) / (n - i) : void 0;
        let l;
        l = isNaN(a) ? void 0 : r - a * n;
        let h = [];
        if (isNaN(a)) {
            let t = i;
            let s = o - (e**2 - (t - i)**2)**.5;
            h = [new Point(t, o + (e**2 - (t - i)**2)**.5), new Point(t, s)]
        } else {
            let t = Math.pow(a, 2) + 1;
            let s = 2 * (a * l - a * o - i);
            let n = o**2 - e**2 + i**2 - 2 * l * o + l**2;
            let r = (-s + (s**2 - 4 * t * n)**.5) / (2 * t);
            let C = (-s - (s**2 - 4 * t * n)**.5) / (2 * t);
            let _ = a * C + l;
            h = [new Point(r, a * r + l), new Point(C, _)]
        }
        return this.calculateDistance(h[0].x, h[0].y, s.x, s.y) < this.calculateDistance(h[1].x, h[1].y, s.x, s.y) ? h[0] : h[1]
    }

    findCircleIntersections(t, e) {
        let s = t.radius;
        let i = t.x;
        let o = t.y;
        let n = e.radius;
        let r = e.x;
        let a = e.y;
        let l = Math.sqrt((i - r)**2 + (o - a)**2);
        if (l > s + n) return [];
        if (l < Math.abs(s - n)) return [];
        if (0 === l && s === n) return [];
        let h = (s**2 - n**2 + l**2) / (2 * l);
        let C = Math.sqrt(s**2 - h**2);
        let _ = i + h * (r - i) / l;
        let c = o + h * (a - o) / l;
        return [new Point(_ + C * (a - o) / l, c - C * (r - i) / l), new Point(_ - C * (a - o) / l, c + C * (r - i) / l)]
    }
}

class Circle {
    constructor(t, e, s) {
        this.radius = t;
        this.x = e;
        this.y = s
    }
}

class Point {
    constructor(t, e) {
        this.x = t;
        this.y = e
    }
}

class AllPoints {
}

class Constants {
}

Constants.UPPER_ARC_CIRCLE_CENTER_X = 116.5;
Constants.UPPER_ARC_CIRCLE_CENTER_Y = 514;
Constants.UPPER_ARC_CIRCLE_R = 330;
Constants.LOWER_ARC_CIRCLE_CENTER_X = 116.5;
Constants.LOWER_ARC_CIRCLE_CENTER_Y = 116.5;
Constants.LOWER_ARC_CIRCLE_R = 115.5;
Constants.CHAMFER_CIRCLE_R = 8;
Constants.MAX_FONT_SIZE = "19fp";
Constants.MIN_FONT_SIZE = "13fp";
Constants.SHADOW_BLUR = 4;
Constants.SHADOW_OFFSET_Y = 3;
Constants.DISTANCE_FROM_BORDER = 1;
Constants.TEXT_HORIZONTAL_MARGIN = 24;
Constants.TEXT_MARGIN_TOP = 10;
Constants.TEXT_MARGIN_BOTTOM = 16;
Constants.EMPHASIZED_NORMAL_BTN_COLOR = "#1F71FF";
Constants.EMPHASIZED_TEXT_COLOR = "#FFFFFF";
Constants.EMPHASIZED_PRESSED_BTN_COLOR = "#2B6EC2";
Constants.EMPHASIZED_DISABLE_BTN_COLOR = "#991F71FF";
Constants.EMPHASIZED_DISABLE_TEXT_COLOR = "#99FFFFFF";
Constants.NORMAL01_NORMAL_BTN_COLOR = "#132230";
Constants.NORMAL01_TEXT_COLOR = "#5EA1FF";
Constants.NORMAL01_PRESSED_BTN_COLOR = "#25353E";
Constants.NORMAL01_DISABLE_BTN_COLOR = "#132230";
Constants.NORMAL01_DISABLE_TEXT_COLOR = "#995ea1ff";
Constants.NORMAL02_NORMAL_BTN_COLOR = "#1D201C";
Constants.NORMAL02_TEXT_COLOR = "#5EA1FF";
Constants.NORMAL02_PRESSED_BTN_COLOR = "#30342D";
Constants.NORMAL02_DISABLE_BTN_COLOR = "#1E211D";
Constants.NORMAL02_DISABLE_TEXT_COLOR = "#995ea1ff";
Constants.EMPHASIZEWARN_NORMAL_BTN_COLOR = "#BF2629";
Constants.EMPHASIZEWARN_TEXT_COLOR = "#FFFFFF";
Constants.EMPHASIZEWARN_PRESSED_BTN_COLOR = "#9E342F";
Constants.EMPHASIZEWARN_DISABLE_BTN_COLOR = "#3E0d0c";
Constants.EMPHASIZEWARN_DISABLE_TEXT_COLOR = "#99FFFFFF";

export default { ArcButton, ArcButtonOptions, TYPE_MODE, ARC_BUTTON_STYLE_MODE, ARC_BUTTON_STATUS, CLICK_EFFECT_STATUS }