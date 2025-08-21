/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}

const display = requireNapi('display');
const mediaquery = requireNapi('mediaquery');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const componentUtils = requireNapi('arkui.componentUtils');
const Configuration = requireNapi('configuration');
const SystemDateTime = requireNapi('systemDateTime');

const o = 10003;
const t = 10002;
const u = 10007;
export const a1 = {
    icon: {
        size: { width: 32, height: 32 },
        margin: {
            top: LengthMetrics.vp(12),
            bottom: LengthMetrics.vp(12),
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12)
        },
        fillColor: '',
        borderRadius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_s'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
    title: {
        margin: { bottom: LengthMetrics.vp(2) },
        minFontSize: 12,
        fontWeight: FontWeight.Medium,
        fontSize: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_sub_title2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
    button: {
        margin: {
            top: LengthMetrics.vp(16),
            bottom: LengthMetrics.vp(16),
            start: LengthMetrics.vp(16),
            end: LengthMetrics.vp(16)
        },
        padding: {
            top: LengthMetrics.vp(4),
            bottom: LengthMetrics.vp(4),
            start: LengthMetrics.vp(4),
            end: LengthMetrics.vp(4)
        },
        fontSize: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_button2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        e2: {
            top: LengthMetrics.vp(8),
            bottom: LengthMetrics.vp(8),
            start: LengthMetrics.vp(8),
            end: LengthMetrics.vp(8)
        },
        minFontSize: 9,
        fontWeight: FontWeight.Medium,
        f2: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
    message: {
        fontSize: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontWeight: FontWeight.Regular,
        g2: { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
    h2: {
        padding: {
            top: LengthMetrics.vp(12),
            bottom: LengthMetrics.vp(12),
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12)
        },
    },
    i2: {
        size: { width: 22, height: 22 },
        padding: {
            top: LengthMetrics.vp(2),
            bottom: LengthMetrics.vp(2),
            start: LengthMetrics.vp(2),
            end: LengthMetrics.vp(2)
        },
        margin: {
            top: LengthMetrics.vp(12),
            bottom: LengthMetrics.vp(12),
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12)
        },
        symbolStyle: new SymbolGlyphModifier({ "id": -1, "type": 40000, params: ['sys.symbol.xmark'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        f2: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        j2: '18vp',
        l2: { "id": -1, "type": 10003, params: ['sys.string.off_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
};
const b1 = () => {
};
const c1 = 400;
export function Popup(options, parent = null) {
    const d2 = options;
    {
        (parent ? parent : this).observeComponentCreation2((elmtId, isInitialRender, options = d2) => {
            if (isInitialRender) {
                let componentCall = new d1(parent ? parent : this, {
                    icon: options.icon,
                    title: options.title,
                    message: options.message,
                    popupDirection: options.direction,
                    showClose: options.showClose,
                    onClose: options.onClose,
                    buttons: options.buttons,
                    maxWidth: options.maxWidth
                }, undefined, elmtId, () => { }, { page: "library/src/main/ets/components/MainPage.ets", line: 210, m2: 3 });
                ViewPU.create(componentCall);
                let paramsLambda = () => {
                    return {
                        icon: options.icon,
                        title: options.title,
                        message: options.message,
                        popupDirection: options.direction,
                        showClose: options.showClose,
                        onClose: options.onClose,
                        buttons: options.buttons,
                        maxWidth: options.maxWidth
                    };
                };
                componentCall.paramsGenerator_ = paramsLambda;
            }
            else {
                (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {
                    icon: options.icon,
                    title: options.title,
                    message: options.message,
                    popupDirection: options.direction,
                    showClose: options.showClose,
                    buttons: options.buttons,
                    maxWidth: options.maxWidth
                });
            }
        }, { name: "PopupComponent" });
    }
}
function i(dimension, c2) {
    const matches = dimension.match(c2);
    if (!matches || matches.length < 3) {
        return false;
    }
    const value = Number.parseFloat(matches[1]);
    return value >= 0;
}
function j(dimension) {
    return i(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}
function m(context, value) {
    const resourceManager = context?.resourceManager;
    if (value === void (0) || value === null || resourceManager === void (0)) {
        return false;
    }
    if (value.type !== o && value.type !== u &&
        value.type !== t) {
        return false;
    }
    if (value.type === u || value.type === t) {
        if (resourceManager.getNumber(value.id) >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    if (value.type === o && !j(resourceManager.getStringSync(value.id))) {
        return false;
    }
    else {
        return true;
    }
}
export class d1 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.onClose = b1;
        this.theme = a1;
        this.applycontentKey = 'applyContent' + SystemDateTime.getTime(false);
        this.__icon = new SynchedPropertyObjectOneWayPU(params.icon, this, "icon");
        this.__maxWidth = new SynchedPropertyObjectOneWayPU(params.maxWidth, this, "maxWidth");
        this.__messageMaxWidth = new SynchedPropertySimpleOneWayPU(params.messageMaxWidth, this, "messageMaxWidth");
        this.__title = new SynchedPropertyObjectOneWayPU(params.title, this, "title");
        this.__message = new SynchedPropertyObjectOneWayPU(params.message, this, "message");
        this.__popupDirection = new SynchedPropertySimpleOneWayPU(params.popupDirection, this, "popupDirection");
        this.__showClose = new SynchedPropertyObjectOneWayPU(params.showClose, this, "showClose");
        this.__buttons = new SynchedPropertyObjectOneWayPU(params.buttons, this, "buttons");
        this.textHeight = 0;
        this.__titleHeight = new ObservedPropertySimplePU(0, this, "titleHeight");
        this.__applyHeight = new ObservedPropertySimplePU(0, this, "applyHeight");
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, "buttonHeight");
        this.__messageMaxWeight = new ObservedPropertyObjectPU(0, this, "messageMaxWeight");
        this.__beforeScreenStatus = new ObservedPropertySimplePU(undefined, this, "beforeScreenStatus");
        this.__currentScreenStatus = new ObservedPropertySimplePU(true, this, "currentScreenStatus");
        this.__applySizeOptions = new ObservedPropertyObjectPU(undefined, this, "applySizeOptions");
        this.__closeButtonBackgroundColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "closeButtonBackgroundColor");
        this.__firstButtonBackgroundColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "firstButtonBackgroundColor");
        this.__secondButtonBackgroundColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "secondButtonBackgroundColor");
        this.__closeButtonFillColorWithTheme = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "closeButtonFillColorWithTheme");
        this.listener = mediaquery.matchMediaSync('(orientation: landscape)');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.onClose !== undefined) {
            this.onClose = params.onClose;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.applycontentKey !== undefined) {
            this.applycontentKey = params.applycontentKey;
        }
        if (params.icon === undefined) {
            this.__icon.set({ image: '' });
        }
        if (params.messageMaxWidth === undefined) {
            this.__messageMaxWidth.set(0);
        }
        if (params.title === undefined) {
            this.__title.set({ text: '' });
        }
        if (params.message === undefined) {
            this.__message.set({ text: '' });
        }
        if (params.popupDirection === undefined) {
            this.__popupDirection.set(Direction.Auto);
        }
        if (params.showClose === undefined) {
            this.__showClose.set(true);
        }
        if (params.buttons === undefined) {
            this.__buttons.set([{ text: '' }, { text: '' }]);
        }
        if (params.textHeight !== undefined) {
            this.textHeight = params.textHeight;
        }
        if (params.titleHeight !== undefined) {
            this.titleHeight = params.titleHeight;
        }
        if (params.applyHeight !== undefined) {
            this.applyHeight = params.applyHeight;
        }
        if (params.buttonHeight !== undefined) {
            this.buttonHeight = params.buttonHeight;
        }
        if (params.messageMaxWeight !== undefined) {
            this.messageMaxWeight = params.messageMaxWeight;
        }
        if (params.beforeScreenStatus !== undefined) {
            this.beforeScreenStatus = params.beforeScreenStatus;
        }
        if (params.currentScreenStatus !== undefined) {
            this.currentScreenStatus = params.currentScreenStatus;
        }
        if (params.applySizeOptions !== undefined) {
            this.applySizeOptions = params.applySizeOptions;
        }
        if (params.closeButtonBackgroundColor !== undefined) {
            this.closeButtonBackgroundColor = params.closeButtonBackgroundColor;
        }
        if (params.firstButtonBackgroundColor !== undefined) {
            this.firstButtonBackgroundColor = params.firstButtonBackgroundColor;
        }
        if (params.secondButtonBackgroundColor !== undefined) {
            this.secondButtonBackgroundColor = params.secondButtonBackgroundColor;
        }
        if (params.closeButtonFillColorWithTheme !== undefined) {
            this.closeButtonFillColorWithTheme = params.closeButtonFillColorWithTheme;
        }
        if (params.listener !== undefined) {
            this.listener = params.listener;
        }
    }
    updateStateVars(params) {
        this.__icon.reset(params.icon);
        this.__maxWidth.reset(params.maxWidth);
        this.__messageMaxWidth.reset(params.messageMaxWidth);
        this.__title.reset(params.title);
        this.__message.reset(params.message);
        this.__popupDirection.reset(params.popupDirection);
        this.__showClose.reset(params.showClose);
        this.__buttons.reset(params.buttons);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__icon.purgeDependencyOnElmtId(rmElmtId);
        this.__maxWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__messageMaxWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__title.purgeDependencyOnElmtId(rmElmtId);
        this.__message.purgeDependencyOnElmtId(rmElmtId);
        this.__popupDirection.purgeDependencyOnElmtId(rmElmtId);
        this.__showClose.purgeDependencyOnElmtId(rmElmtId);
        this.__buttons.purgeDependencyOnElmtId(rmElmtId);
        this.__titleHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__applyHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__buttonHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__messageMaxWeight.purgeDependencyOnElmtId(rmElmtId);
        this.__beforeScreenStatus.purgeDependencyOnElmtId(rmElmtId);
        this.__currentScreenStatus.purgeDependencyOnElmtId(rmElmtId);
        this.__applySizeOptions.purgeDependencyOnElmtId(rmElmtId);
        this.__closeButtonBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__firstButtonBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__secondButtonBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__closeButtonFillColorWithTheme.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__icon.aboutToBeDeleted();
        this.__maxWidth.aboutToBeDeleted();
        this.__messageMaxWidth.aboutToBeDeleted();
        this.__title.aboutToBeDeleted();
        this.__message.aboutToBeDeleted();
        this.__popupDirection.aboutToBeDeleted();
        this.__showClose.aboutToBeDeleted();
        this.__buttons.aboutToBeDeleted();
        this.__titleHeight.aboutToBeDeleted();
        this.__applyHeight.aboutToBeDeleted();
        this.__buttonHeight.aboutToBeDeleted();
        this.__messageMaxWeight.aboutToBeDeleted();
        this.__beforeScreenStatus.aboutToBeDeleted();
        this.__currentScreenStatus.aboutToBeDeleted();
        this.__applySizeOptions.aboutToBeDeleted();
        this.__closeButtonBackgroundColor.aboutToBeDeleted();
        this.__firstButtonBackgroundColor.aboutToBeDeleted();
        this.__secondButtonBackgroundColor.aboutToBeDeleted();
        this.__closeButtonFillColorWithTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(newValue) {
        this.__icon.set(newValue);
    }
    get maxWidth() {
        return this.__maxWidth.get();
    }
    set maxWidth(newValue) {
        this.__maxWidth.set(newValue);
    }
    get messageMaxWidth() {
        return this.__messageMaxWidth.get();
    }
    set messageMaxWidth(newValue) {
        this.__messageMaxWidth.set(newValue);
    }
    get title() {
        return this.__title.get();
    }
    set title(newValue) {
        this.__title.set(newValue);
    }
    get message() {
        return this.__message.get();
    }
    set message(newValue) {
        this.__message.set(newValue);
    }
    get popupDirection() {
        return this.__popupDirection.get();
    }
    set popupDirection(newValue) {
        this.__popupDirection.set(newValue);
    }
    get showClose() {
        return this.__showClose.get();
    }
    set showClose(newValue) {
        this.__showClose.set(newValue);
    }
    get buttons() {
        return this.__buttons.get();
    }
    set buttons(newValue) {
        this.__buttons.set(newValue);
    }
    get titleHeight() {
        return this.__titleHeight.get();
    }
    set titleHeight(newValue) {
        this.__titleHeight.set(newValue);
    }
    get applyHeight() {
        return this.__applyHeight.get();
    }
    set applyHeight(newValue) {
        this.__applyHeight.set(newValue);
    }
    get buttonHeight() {
        return this.__buttonHeight.get();
    }
    set buttonHeight(newValue) {
        this.__buttonHeight.set(newValue);
    }
    get messageMaxWeight() {
        return this.__messageMaxWeight.get();
    }
    set messageMaxWeight(newValue) {
        this.__messageMaxWeight.set(newValue);
    }
    get beforeScreenStatus() {
        return this.__beforeScreenStatus.get();
    }
    set beforeScreenStatus(newValue) {
        this.__beforeScreenStatus.set(newValue);
    }
    get currentScreenStatus() {
        return this.__currentScreenStatus.get();
    }
    set currentScreenStatus(newValue) {
        this.__currentScreenStatus.set(newValue);
    }
    get applySizeOptions() {
        return this.__applySizeOptions.get();
    }
    set applySizeOptions(newValue) {
        this.__applySizeOptions.set(newValue);
    }
    get closeButtonBackgroundColor() {
        return this.__closeButtonBackgroundColor.get();
    }
    set closeButtonBackgroundColor(newValue) {
        this.__closeButtonBackgroundColor.set(newValue);
    }
    get firstButtonBackgroundColor() {
        return this.__firstButtonBackgroundColor.get();
    }
    set firstButtonBackgroundColor(newValue) {
        this.__firstButtonBackgroundColor.set(newValue);
    }
    get secondButtonBackgroundColor() {
        return this.__secondButtonBackgroundColor.get();
    }
    set secondButtonBackgroundColor(newValue) {
        this.__secondButtonBackgroundColor.set(newValue);
    }
    get closeButtonFillColorWithTheme() {
        return this.__closeButtonFillColorWithTheme.get();
    }
    set closeButtonFillColorWithTheme(newValue) {
        this.__closeButtonFillColorWithTheme.set(newValue);
    }
    getIconWidth() {
        return this.icon?.width ?? this.theme.icon.size.width;
    }
    getIconHeight() {
        return this.icon?.height ?? this.theme.icon.size.height;
    }
    getIconFillColor() {
        return this.icon?.fillColor ?? this.theme.icon.fillColor;
    }
    getIconBorderRadius() {
        return this.icon?.borderRadius ?? this.theme.icon.borderRadius;
    }
    getIconMargin() {
        return {
            start: new LengthMetrics(this.theme.button.margin.start.value / 2, this.theme.button.margin.start.unit),
            end: new LengthMetrics(this.theme.icon.margin.start.value - (this.theme.button.margin.end.value / 2), this.theme.button.margin.start.unit)
        };
    }
    getIconImage() {
        return this.icon?.image;
    }
    getTitleText() {
        return this.title?.text;
    }
    getTitlePadding() {
        return {
            start: new LengthMetrics(this.theme.button.margin.start.value / 2, this.theme.button.margin.start.unit),
            end: this.theme.i2.margin.end
        };
    }
    getTitleMargin() {
        return this.theme.title.margin;
    }
    getTitleMinFontSize() {
        return this.theme.title.minFontSize;
    }
    getTitleFontWeight() {
        return this.title?.fontWeight ?? this.theme.title.fontWeight;
    }
    getTitleFontSize() {
        return this.title?.fontSize ?? this.theme.title.fontSize;
    }
    getTitleFontColor() {
        return this.title?.fontColor ?? this.theme.title.fontColor;
    }
    getCloseButtonWidth() {
        return this.theme.i2.size.width;
    }
    getCloseButtonHeight() {
        return this.theme.i2.size.height;
    }
    getCloseButtonFillColor() {
        return this.closeButtonFillColorWithTheme;
    }
    getCloseButtonHoverColor() {
        return this.theme.i2.f2;
    }
    getCloseButtonBackgroundColor() {
        return this.theme.i2.backgroundColor;
    }
    getCloseButtonPadding() {
        return this.theme.i2.padding;
    }
    getCloseButtonSymbolSize() {
        return this.theme.i2.j2;
    }
    getMessageText() {
        return this.message.text;
    }
    getMessageFontSize() {
        return this.message.fontSize ?? this.theme.message.fontSize;
    }
    getMessageFontColor() {
        let fontColor;
        if (this.message.fontColor) {
            fontColor = this.message.fontColor;
        }
        else {
            if (this.title.text !== '' && this.title.text !== void (0)) {
                fontColor = this.theme.message.fontColor;
            }
            else {
                fontColor = this.theme.message.g2;
            }
        }
        return fontColor;
    }
    getMessagePadding() {
        let padding;
            padding = {
                start: LengthMetrics.vp(this.theme.button.margin.start.value / 2),
                end: LengthMetrics.vp(this.theme.i2.margin.end.value)
            };
        return padding;
    }
    getMessageMaxWeight() {
        let a2 = undefined;
        let b2 = undefined;
        try {
            b2 = display.getDefaultDisplaySync();
        }
        catch (error) {
            console.error(`Ace Popup getDefaultDisplaySync, error: ${error.toString()}`);
            return a2 = 400;
        }
        if (this.showClose || this.showClose === void (0)) {
            if (this.messageMaxWidth != undefined) {
                if (this.maxWidth != undefined && this.maxWidth > px2vp(b2.width)) {
                    a2 = px2vp(b2.width);
                }
                else {
                    a2 = this.messageMaxWidth;
                }
            }
            else {
                if (b2.width != 0) {
                    a2 = px2vp(b2.width);
                }
                else {
                    a2 = -1;
                }
            }
            a2 -= (this.theme.h2.padding.start.value - (this.theme.button.margin.end.value / 2));
            a2 -= this.theme.h2.padding.end.value;
            a2 -= this.theme.button.margin.start.value / 2;
            a2 -= this.theme.i2.margin.end.value;
            a2 -= this.getCloseButtonWidth();
        }
        return a2;
    }
    getMessageFontWeight() {
        return this.theme.message.fontWeight;
    }
    getButtonMargin() {
        return {
            top: LengthMetrics.vp(this.theme.button.e2.top.value / 2 - 4),
            bottom: LengthMetrics.vp(this.theme.button.e2.bottom.value / 2 - 4),
            start: LengthMetrics.vp(this.theme.button.margin.start.value / 2 - 4),
            end: LengthMetrics.vp(this.theme.button.margin.end.value / 2 - 4)
        };
    }
    getButtonTextMargin() {
        return { top: LengthMetrics.vp(this.theme.button.e2.bottom.value) };
    }
    getButtonTextPadding() {
        return this.theme.button.padding;
    }
    getButtonHoverColor() {
        return this.theme.button.f2;
    }
    getButtonBackgroundColor() {
        return this.theme.button.backgroundColor;
    }
    getFirstButtonText() {
        return this.buttons?.[0]?.text;
    }
    getSecondButtonText() {
        return this.buttons?.[1]?.text;
    }
    getFirstButtonFontSize() {
        return this.buttons?.[0]?.fontSize ?? this.theme.button.fontSize;
    }
    getSecondButtonFontSize() {
        return this.buttons?.[1]?.fontSize ?? this.theme.button.fontSize;
    }
    getFirstButtonFontColor() {
        return this.buttons?.[0]?.fontColor ?? this.theme.button.fontColor;
    }
    getSecondButtonFontColor() {
        return this.buttons?.[1]?.fontColor ?? this.theme.button.fontColor;
    }
    getButtonMinFontSize() {
        return this.theme.button.minFontSize;
    }
    getButtonFontWeight() {
        return this.theme.button.fontWeight;
    }
    getWindowsPadding() {
        let top = this.theme.h2.padding.top;
        let bottom = LengthMetrics.vp(this.theme.h2.padding.bottom.value - (this.theme.button.e2.bottom.value / 2));
        let start = LengthMetrics.vp(this.theme.h2.padding.start.value - (this.theme.button.margin.end.value / 2));
        let end = this.theme.h2.padding.end;
        let z1 = this.toVp(this.maxWidth);
        if (z1 === 0) {
            start = LengthMetrics.vp(0);
            end = LengthMetrics.vp(0);
        }
        return {
            top: top,
            bottom: bottom,
            start: start,
            end: end
        };
    }
    onWillApplyTheme(theme) {
        this.theme.title.fontColor = theme.colors.fontPrimary;
        this.theme.button.fontColor = theme.colors.fontEmphasize;
        this.theme.message.fontColor = theme.colors.fontSecondary;
        this.theme.message.g2 = theme.colors.fontPrimary;
        this.closeButtonFillColorWithTheme = theme.colors.iconSecondary;
    }
    aboutToAppear() {
        this.listener.on("change", (w1) => {
            this.currentScreenStatus = w1.matches;
        });
    }
    aboutToDisappear() {
        this.listener.off("change");
    }
    getScrollMaxHeight() {
        let v1 = undefined;
        if (this.currentScreenStatus !== this.beforeScreenStatus) {
            this.applySizeOptions = this.getApplyMaxSize();
            this.beforeScreenStatus = this.currentScreenStatus;
            return v1;
        }
        v1 = px2vp(componentUtils.getRectangleById(this.applycontentKey).size?.height);
        v1 -= this.titleHeight;
        v1 -= this.buttonHeight;
        v1 -= this.theme.h2.padding.top.value;
        v1 -= (this.theme.button.e2.bottom.value / 2);
        v1 -= this.theme.title.margin.bottom.value;
        v1 -= (this.theme.h2.padding.bottom.value -
            (this.theme.button.e2.bottom.value / 2));
        if (Math.floor(this.textHeight) > Math.floor(v1 + 1)) {
            return v1;
        }
        else {
            v1 = undefined;
            return v1;
        }
    }
    getLayoutWeight() {
        let layoutWeight;
        if ((this.icon.image !== '' && this.icon.image !== void (0)) ||
            (this.title.text !== '' && this.title.text !== void (0)) ||
            (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
            (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
            layoutWeight = 1;
        }
        else {
            layoutWeight = 0;
        }
        return layoutWeight;
    }
    resourceToVp(value) {
        try {
            if (value.id !== -1) {
                return px2vp(getContext(this).resourceManager.getNumber(value.id));
            }
            else {
                return px2vp(getContext(this)
                    .resourceManager
                    .getNumberByName((value.params[0]).split('.')[2]));
            }
        }
        catch (error) {
            return c1;
        }
    }
    toVp(value) {
        let s1 = undefined;
        try {
            s1 = display.getDefaultDisplaySync();
        }
        catch (error) {
            console.error(`Ace Popup getDefaultDisplaySync, error: ${error.toString()}`);
            return Number.NEGATIVE_INFINITY;
        }
        if (value === void (0)) {
            return Number.NEGATIVE_INFINITY;
        }
        switch (typeof (value)) {
            case 'number':
                return value;
            case 'object':
                try {
                    let u1 = this.resourceToVp(value);
                    if (u1 === 0 &&
                        !m(getContext(this), value)) {
                        return Number.NEGATIVE_INFINITY;
                    }
                    return u1;
                }
                catch (error) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let t1 = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
                let matches = value.match(t1);
                if (!matches) {
                    return Number.NEGATIVE_INFINITY;
                }
                let length = Number(matches?.[1] ?? 0);
                let unit = matches?.[2] ?? 'vp';
                switch (unit.toLowerCase()) {
                    case 'px':
                        length = px2vp(length);
                        break;
                    case 'fp':
                        length = px2vp(fp2px(length));
                        break;
                    case 'lpx':
                        length = px2vp(lpx2px(length));
                        break;
                    case '%':
                        length = length / 100 * px2vp(s1.width);
                        break;
                    case 'vp':
                        break;
                    default:
                        break;
                }
                return length;
            default:
                return Number.NEGATIVE_INFINITY;
        }
    }
    getApplyMaxSize() {
        let m1 = undefined;
        let n1 = undefined;
        let o1 = undefined;
        let p1 = undefined;
        let q1 = 400;
        try {
            p1 = display.getDefaultDisplaySync();
        }
        catch (error) {
            console.error(`Ace Popup getDefaultDisplaySync, error: ${error.toString()}`);
            this.messageMaxWeight = 400;
            return o1 = { maxWidth: 400, maxHeight: 480 };
        }
        if (this.maxWidth !== undefined) {
            if (typeof this.maxWidth === 'number' && this.maxWidth >= 0) {
                q1 = this.maxWidth;
            }
            else if (typeof this.maxWidth === 'number' && this.maxWidth < 0) {
                q1 = c1;
            }
            else {
                q1 = this.toVp(this.maxWidth);
            }
        }
        if (px2vp(p1.width) > q1) {
            m1 = q1;
        }
        else {
            if (p1.width != 0) {
                m1 = px2vp(p1.width);
            }
            else {
                m1 = -1;
            }
        }
        if (px2vp(p1.height) > 480) {
            n1 = 480;
        }
        else {
            n1 = px2vp(p1.height) - 40 - 40;
        }
        o1 = { maxWidth: m1, maxHeight: n1 };
        this.messageMaxWidth = m1;
        this.messageMaxWeight = this.getMessageMaxWeight();
        return o1;
    }
    getTitleTextAlign() {
        let k2 = TextAlign.Start;
        if ((Configuration.getLocale().dir === 'rtl') && this.popupDirection === Direction.Auto) {
            k2 = TextAlign.End;
        }
        return k2;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.popupDirection);
            Row.alignItems(VerticalAlign.Top);
            Row.padding(this.getWindowsPadding());
            Row.constraintSize(ObservedObject.GetRawObject(this.applySizeOptions));
            Row.constraintSize(this.getApplyMaxSize());
            Row.key(this.applycontentKey);
            Row.onAreaChange((k1, rect) => {
                this.applyHeight = rect.height;
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.icon.image !== '' && this.icon.image !== void (0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.getIconImage());
                        Image.direction(this.popupDirection);
                        Image.width(this.getIconWidth());
                        Image.height(this.getIconHeight());
                        Image.margin(this.getIconMargin());
                        Image.fillColor(this.getIconFillColor());
                        Image.borderRadius(this.getIconBorderRadius());
                        Image.draggable(false);
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.title.text !== '' && this.title.text !== void (0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.direction(this.popupDirection);
                        Column.layoutWeight(this.getLayoutWeight());
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ alignItems: ItemAlign.Start });
                        Flex.direction(this.popupDirection);
                        Flex.width("100%");
                        Flex.margin(this.getTitleMargin());
                        Flex.onAreaChange((j1, rect) => {
                            this.titleHeight = rect.height;
                        });
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.getTitleText());
                        Text.direction(this.popupDirection);
                        Text.flexGrow(1);
                        Text.maxLines(2);
                        Text.align(Alignment.Start);
                        Text.padding(this.getTitlePadding());
                        Text.minFontSize(this.getTitleMinFontSize());
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.fontWeight(this.getTitleFontWeight());
                        Text.fontSize(this.getTitleFontSize());
                        Text.fontColor(this.getTitleFontColor());
                        Text.constraintSize({ minHeight: this.getCloseButtonHeight() });
                        Text.textAlign(this.getTitleTextAlign());
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.showClose || this.showClose === void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.width(this.getCloseButtonWidth());
                                    Button.height(this.getCloseButtonHeight());
                                    Button.padding(this.getCloseButtonPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.closeButtonBackgroundColor));
                                    Button.flexShrink(0);
                                    Button.accessibilityText(this.theme.i2.l2);
                                    Button.onHover((isHover) => {
                                        if (isHover) {
                                            this.closeButtonBackgroundColor = this.getCloseButtonHoverColor();
                                        }
                                        else {
                                            this.closeButtonBackgroundColor = this.getCloseButtonBackgroundColor();
                                        }
                                    });
                                    Button.onClick(() => {
                                        if (this.onClose) {
                                            this.onClose();
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([this.getCloseButtonFillColor()]);
                                    SymbolGlyph.fontSize(this.getCloseButtonSymbolSize());
                                    SymbolGlyph.direction(this.popupDirection);
                                    SymbolGlyph.attributeModifier.bind(this)(this.theme.i2.symbolStyle);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                                Button.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Scroll.create();
                        Scroll.direction(this.popupDirection);
                        Scroll.width("100%");
                        Scroll.align(Alignment.TopStart);
                        Scroll.padding(this.getMessagePadding());
                        Scroll.scrollBar(BarState.Auto);
                        Scroll.scrollable(ScrollDirection.Vertical);
                        Scroll.constraintSize({ maxHeight: this.getScrollMaxHeight() });
                        Scroll.edgeEffect(EdgeEffect.Spring, { alwaysEnabled: false });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.getMessageText());
                        Text.direction(this.popupDirection);
                        Text.fontSize(this.getMessageFontSize());
                        Text.fontColor(this.getMessageFontColor());
                        Text.fontWeight(this.getMessageFontWeight());
                        Text.constraintSize({ minHeight: this.getCloseButtonHeight() });
                        Text.onAreaChange((i1, rect) => {
                            this.textHeight = rect.height;
                        });
                    }, Text);
                    Text.pop();
                    Scroll.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ wrap: FlexWrap.Wrap });
                        Flex.direction(this.popupDirection);
                        Flex.margin(this.getButtonTextMargin());
                        Flex.flexGrow(1);
                        Flex.onAreaChange((h1, rect) => {
                            if ((this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
                                (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
                                this.buttonHeight = rect.height;
                            }
                            else {
                                this.buttonHeight = 0;
                            }
                        });
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild();
                                    Button.type(ButtonType.Normal);
                                    Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.popup_button_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.firstButtonBackgroundColor));
                                    Button.onHover((isHover) => {
                                        if (isHover) {
                                            this.firstButtonBackgroundColor = this.getButtonHoverColor();
                                        }
                                        else {
                                            this.firstButtonBackgroundColor = this.getButtonBackgroundColor();
                                        }
                                    });
                                    Button.onClick(() => {
                                        if (this.buttons?.[0]?.action) {
                                            this.buttons?.[0]?.action();
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.getFirstButtonText());
                                    Text.direction(this.popupDirection);
                                    Text.maxLines(2);
                                    Text.focusable(true);
                                    Text.fontSize(this.getFirstButtonFontSize());
                                    Text.fontColor(this.getFirstButtonFontColor());
                                    Text.fontWeight(this.getButtonFontWeight());
                                    Text.minFontSize(this.getButtonMinFontSize());
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                }, Text);
                                Text.pop();
                                Button.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild();
                                    Button.type(ButtonType.Normal);
                                    Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.popup_button_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.secondButtonBackgroundColor));
                                    Button.onHover((isHover) => {
                                        if (isHover) {
                                            this.secondButtonBackgroundColor = this.getButtonHoverColor();
                                        }
                                        else {
                                            this.secondButtonBackgroundColor = this.getButtonBackgroundColor();
                                        }
                                    });
                                    Button.onClick(() => {
                                        if (this.buttons?.[1]?.action) {
                                            this.buttons?.[1]?.action();
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.getSecondButtonText());
                                    Text.direction(this.popupDirection);
                                    Text.maxLines(2);
                                    Text.focusable(true);
                                    Text.fontSize(this.getSecondButtonFontSize());
                                    Text.fontColor(this.getSecondButtonFontColor());
                                    Text.fontWeight(this.getButtonFontWeight());
                                    Text.minFontSize(this.getButtonMinFontSize());
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                }, Text);
                                Text.pop();
                                Button.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.direction(this.popupDirection);
                        Column.layoutWeight(this.getLayoutWeight());
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create();
                        Flex.height(0);
                        Flex.onAreaChange((g1, rect) => {
                            this.titleHeight = rect.height;
                        });
                    }, Flex);
                    Flex.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.direction(this.popupDirection);
                        Row.alignItems(VerticalAlign.Top);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Scroll.create();
                        Scroll.direction(this.popupDirection);
                        Scroll.layoutWeight(this.getLayoutWeight());
                        Scroll.edgeEffect(EdgeEffect.Spring, { alwaysEnabled: false });
                        Scroll.align(Alignment.TopStart);
                        Scroll.padding(this.getMessagePadding());
                        Scroll.scrollBar(BarState.Auto);
                        Scroll.scrollable(ScrollDirection.Vertical);
                        Scroll.constraintSize({ maxHeight: this.getScrollMaxHeight() });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.getMessageText());
                        Text.direction(this.popupDirection);
                        Text.fontSize(this.getMessageFontSize());
                        Text.fontColor(this.getMessageFontColor());
                        Text.fontWeight(this.getMessageFontWeight());
                        Text.constraintSize({ maxWidth: this.messageMaxWeight, minHeight: this.getCloseButtonHeight() });
                        Text.onAreaChange((f1, rect) => {
                            this.textHeight = rect.height;
                        });
                    }, Text);
                    Text.pop();
                    Scroll.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.showClose || this.showClose === void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.width(this.getCloseButtonWidth());
                                    Button.height(this.getCloseButtonHeight());
                                    Button.padding(this.getCloseButtonPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.closeButtonBackgroundColor));
                                    Button.flexShrink(0);
                                    Button.accessibilityText(this.theme.i2.l2);
                                    Button.onHover((isHover) => {
                                        if (isHover) {
                                            this.closeButtonBackgroundColor = this.getCloseButtonHoverColor();
                                        }
                                        else {
                                            this.closeButtonBackgroundColor = this.getCloseButtonBackgroundColor();
                                        }
                                    });
                                    Button.onClick(() => {
                                        if (this.onClose) {
                                            this.onClose();
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([this.getCloseButtonFillColor()]);
                                    SymbolGlyph.fontSize(this.getCloseButtonSymbolSize());
                                    SymbolGlyph.direction(this.popupDirection);
                                    SymbolGlyph.attributeModifier.bind(this)(this.theme.i2.symbolStyle);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                                Button.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ wrap: FlexWrap.Wrap });
                        Flex.direction(this.popupDirection);
                        Flex.margin(this.getButtonTextMargin());
                        Flex.flexGrow(1);
                        Flex.onAreaChange((e1, rect) => {
                            if ((this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
                                (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
                                this.buttonHeight = rect.height;
                            }
                            else {
                                this.buttonHeight = 0;
                            }
                        });
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild();
                                    Button.type(ButtonType.Normal);
                                    Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.popup_button_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.firstButtonBackgroundColor));
                                    Button.onHover((isHover) => {
                                        if (isHover) {
                                            this.firstButtonBackgroundColor = this.getButtonHoverColor();
                                        }
                                        else {
                                            this.firstButtonBackgroundColor = this.getButtonBackgroundColor();
                                        }
                                    });
                                    Button.onClick(() => {
                                        if (this.buttons?.[0]?.action) {
                                            this.buttons?.[0]?.action();
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.getFirstButtonText());
                                    Text.direction(this.popupDirection);
                                    Text.maxLines(2);
                                    Text.focusable(true);
                                    Text.fontSize(this.getFirstButtonFontSize());
                                    Text.fontColor(this.getFirstButtonFontColor());
                                    Text.fontWeight(this.getButtonFontWeight());
                                    Text.minFontSize(this.getButtonMinFontSize());
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                }, Text);
                                Text.pop();
                                Button.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild();
                                    Button.type(ButtonType.Normal);
                                    Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.popup_button_border_radius'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.secondButtonBackgroundColor));
                                    Button.onHover((isHover) => {
                                        if (isHover) {
                                            this.secondButtonBackgroundColor = this.getButtonHoverColor();
                                        }
                                        else {
                                            this.secondButtonBackgroundColor = this.getButtonBackgroundColor();
                                        }
                                    });
                                    Button.onClick(() => {
                                        if (this.buttons?.[1]?.action) {
                                            this.buttons?.[1]?.action();
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Text.create(this.getSecondButtonText());
                                    Text.direction(this.popupDirection);
                                    Text.maxLines(2);
                                    Text.focusable(true);
                                    Text.fontSize(this.getSecondButtonFontSize());
                                    Text.fontColor(this.getSecondButtonFontColor());
                                    Text.fontWeight(this.getButtonFontWeight());
                                    Text.minFontSize(this.getButtonMinFontSize());
                                    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                }, Text);
                                Text.pop();
                                Button.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                    Column.pop();
                });
            }
        }, If);
        If.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { Popup };