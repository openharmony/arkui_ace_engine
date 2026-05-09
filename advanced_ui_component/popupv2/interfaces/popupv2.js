/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
const display = requireNapi('display');
const mediaquery = requireNapi('mediaquery');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const Configuration = requireNapi('configuration');
const SystemDateTime = requireNapi('systemDateTime');

const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
export const defaultTheme = {
    icon: {
        size: { width: 32, height: 32 },
        margin: {
            top: LengthMetrics.vp(12),
            bottom: LengthMetrics.vp(12),
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12)
        },
        fillColor: ColorContent.ORIGIN,
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
        textMargin: {
            top: LengthMetrics.vp(8),
            bottom: LengthMetrics.vp(8),
            start: LengthMetrics.vp(8),
            end: LengthMetrics.vp(8)
        },
        minFontSize: 9,
        fontWeight: FontWeight.Medium,
        hoverColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        responseRegion: { "id": -1, "type": 10002, params: ['sys.float.popup_button_response_region'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
    message: {
        fontSize: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_body2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontWeight: FontWeight.Regular,
        plainFontColor: { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
    windows: {
        padding: {
            top: LengthMetrics.vp(12),
            bottom: LengthMetrics.vp(12),
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12)
        },
    },
    closeButton: {
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
        hoverColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        symbolSize: '18vp',
        accessibilityMessage: { "id": -1, "type": 10003, params: ['sys.string.off_used_for_accessibility_text'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        responseRegion: { "id": -1, "type": 10002, params: ['sys.float.popup_close_button_response_region'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    },
};
const noop = () => {
};
const POPUP_DEFAULT_MAXWIDTH = 400;
const MAX_FONT_SCALE = 2;
export function PopupV2(options, parent = null) {
    const __options__ = options;
    {
        (parent ? parent : this).observeComponentCreation2((elmtId, isInitialRender, options = __options__) => {
            if (isInitialRender) {
                let componentCall = new PopupV2ComponentV2(parent ? parent : this, {
                    icon: options.icon,
                    title: options.title,
                    iconModifier: options.iconModifier,
                    titleModifier: options.titleModifier,
                    messageModifier: options.messageModifier,
                    message: options.message,
                    popupDirection: options.direction,
                    showClose: options.showClose,
                    onClose: options.onClose,
                    buttons: options.buttons,
                    maxWidth: options.maxWidth
                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/common/utils/popupv2.ets", line: 202, col: 3 });
                ViewV2.create(componentCall);
                let paramsLambda = () => {
                    return {
                        icon: options.icon,
                        title: options.title,
                        iconModifier: options.iconModifier,
                        titleModifier: options.titleModifier,
                        messageModifier: options.messageModifier,
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
                    iconModifier: options.iconModifier,
                    titleModifier: options.titleModifier,
                    messageModifier: options.messageModifier,
                    message: options.message,
                    popupDirection: options.direction,
                    showClose: options.showClose,
                    onClose: options.onClose,
                    buttons: options.buttons,
                    maxWidth: options.maxWidth
                });
            }
        }, { name: "PopupV2ComponentV2" });
    }
}
function isValidString(dimension, regex) {
    const matches = dimension.match(regex);
    if (!matches || matches.length < 3) {
        return false;
    }
    const value = Number.parseFloat(matches[1]);
    return value >= 0;
}
function isValidDimensionString(dimension) {
    return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}
function isValidResource(context, value) {
    const resourceManager = context?.resourceManager;
    if (value === void (0) || value === null || resourceManager === void (0)) {
        return false;
    }
    if (value.type !== RESOURCE_TYPE_STRING && value.type !== RESOURCE_TYPE_INTEGER &&
        value.type !== RESOURCE_TYPE_FLOAT) {
        return false;
    }
    if (value.type === RESOURCE_TYPE_INTEGER || value.type === RESOURCE_TYPE_FLOAT) {
        if (resourceManager.getNumber(value.id) >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    if (value.type === RESOURCE_TYPE_STRING && !isValidDimensionString(resourceManager.getStringSync(value.id))) {
        return false;
    }
    else {
        return true;
    }
}
export class PopupV2ComponentV2 extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("onClose", (params && "onClose" in params) ? params.onClose : noop);
        this.initParam("theme", (params && "theme" in params) ? params.theme : defaultTheme);
        this.applycontentKey = 'applyContent' + SystemDateTime.getTime(false);
        this.initParam("icon", (params && "icon" in params) ? params.icon : '');
        this.initParam("maxWidth", (params && "maxWidth" in params) ? params.maxWidth : undefined);
        this.messageMaxWidth = 0;
        this.initParam("title", (params && "title" in params) ? params.title : '');
        this.initParam("message", (params && "message" in params) ? params.message : '');
        this.initParam("iconModifier", (params && "iconModifier" in params) ? params.iconModifier : undefined);
        this.initParam("titleModifier", (params && "titleModifier" in params) ? params.titleModifier : undefined);
        this.initParam("messageModifier", (params && "messageModifier" in params) ? params.messageModifier : undefined);
        this.initParam("popupDirection", (params && "popupDirection" in params) ? params.popupDirection : Direction.Auto);
        this.initParam("showClose", (params && "showClose" in params) ? params.showClose : true);
        this.initParam("buttons", (params && "buttons" in params) ? params.buttons : [{ text: '' }, { text: '' }]);
        this.textHeight = 0;
        this.titleHeight = 0;
        this.applyHeight = 0;
        this.buttonHeight = 0;
        this.messageMaxWeight = 0;
        this.beforeScreenStatus = undefined;
        this.currentScreenStatus = undefined;
        this.applySizeOptions = undefined;
        this.closeButtonBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.firstButtonBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondButtonBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.closeButtonFillColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.scrollMaxHeight = undefined;
        this.firstButtonHeight = 0;
        this.secondButtonHeight = 0;
        this.appMaxFontScale = MAX_FONT_SCALE;
        this.listener = mediaquery.matchMediaSync('(orientation: landscape)');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("onClose", (params && "onClose" in params) ? params.onClose : noop);
        this.resetParam("theme", (params && "theme" in params) ? params.theme : defaultTheme);
        this.resetParam("icon", (params && "icon" in params) ? params.icon : '');
        this.resetParam("maxWidth", (params && "maxWidth" in params) ? params.maxWidth : undefined);
        this.messageMaxWidth = 0;
        this.resetParam("title", (params && "title" in params) ? params.title : '');
        this.resetParam("message", (params && "message" in params) ? params.message : '');
        this.resetParam("iconModifier", (params && "iconModifier" in params) ? params.iconModifier : undefined);
        this.resetParam("titleModifier", (params && "titleModifier" in params) ? params.titleModifier : undefined);
        this.resetParam("messageModifier", (params && "messageModifier" in params) ? params.messageModifier : undefined);
        this.resetParam("popupDirection", (params && "popupDirection" in params) ? params.popupDirection : Direction.Auto);
        this.resetParam("showClose", (params && "showClose" in params) ? params.showClose : true);
        this.resetParam("buttons", (params && "buttons" in params) ? params.buttons : [{ text: '' }, { text: '' }]);
        this.titleHeight = 0;
        this.applyHeight = 0;
        this.buttonHeight = 0;
        this.messageMaxWeight = 0;
        this.beforeScreenStatus = undefined;
        this.currentScreenStatus = undefined;
        this.applySizeOptions = undefined;
        this.closeButtonBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.firstButtonBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.secondButtonBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_background_transparent'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.closeButtonFillColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.scrollMaxHeight = undefined;
        this.firstButtonHeight = 0;
        this.secondButtonHeight = 0;
        this.appMaxFontScale = MAX_FONT_SCALE;
    }
    getIconWidth() {
        return this.theme.icon.size.width;
    }
    getIconHeight() {
        return this.theme.icon.size.height;
    }
    getIconFillColor() {
        return this.theme.icon.fillColor;
    }
    getIconBorderRadius() {
        return this.theme.icon.borderRadius;
    }
    getIconMargin() {
        return {
            start: new LengthMetrics(this.theme.button.margin.start.value / 2, this.theme.button.margin.start.unit),
            end: new LengthMetrics(this.theme.icon.margin.start.value - (this.theme.button.margin.end.value / 2), this.theme.button.margin.start.unit)
        };
    }
    getIconImage() {
        return this.icon;
    }
    getTitleText() {
        return this.title;
    }
    getTitlePadding() {
        return {
            start: new LengthMetrics(this.theme.button.margin.start.value / 2, this.theme.button.margin.start.unit),
            end: this.theme.closeButton.margin.end
        };
    }
    getTitleMargin() {
        return this.theme.title.margin;
    }
    getTitleMinFontSize() {
        return this.theme.title.minFontSize;
    }
    getTitleFontWeight() {
        return this.theme.title.fontWeight;
    }
    getTitleFontSize() {
        return this.theme.title.fontSize;
    }
    getTitleFontColor() {
        return this.theme.title.fontColor;
    }
    getCloseButtonWidth() {
        return this.theme.closeButton.size.width;
    }
    getCloseButtonHeight() {
        return this.theme.closeButton.size.height;
    }
    getCloseButtonFillColor() {
        return this.closeButtonFillColorWithTheme;
    }
    getCloseButtonHoverColor() {
        return this.theme.closeButton.hoverColor;
    }
    getCloseButtonBackgroundColor() {
        return this.theme.closeButton.backgroundColor;
    }
    getCloseButtonPadding() {
        return this.theme.closeButton.padding;
    }
    getCloseButtonSymbolSize() {
        return this.theme.closeButton.symbolSize;
    }
    getMessageText() {
        return this.message;
    }
    getMessageFontSize() {
        return this.theme.message.fontSize;
    }
    getMessageFontColor() {
        let fontColor;
        if (this.title !== '' && this.title !== void (0)) {
            fontColor = this.theme.message.fontColor;
        }
        else {
            fontColor = this.theme.message.plainFontColor;
        }
        return fontColor;
    }
    getMessagePadding() {
        let padding;
        padding = {
            start: LengthMetrics.vp((this.theme.button.margin.start?.value || 0) / 2),
            end: LengthMetrics.vp(this.theme.closeButton.margin.end?.value || 0)
        };
        return padding;
    }
    getMessageMaxWeight() {
        let textMaxWeight = undefined;
        let defaultDisplaySync = undefined;
        try {
            defaultDisplaySync = display.getDefaultDisplaySync();
        }
        catch (error) {
            console.error(`Ace PopupV2 getDefaultDisplaySync, error: ${error.toString()}`);
            return textMaxWeight = 400;
        }
        if (this.showClose || this.showClose === void (0)) {
            if (this.messageMaxWidth != undefined) {
                if (this.maxWidth != undefined && this.maxWidth > px2vp(defaultDisplaySync.width)) {
                    textMaxWeight = px2vp(defaultDisplaySync.width);
                }
                else {
                    textMaxWeight = this.messageMaxWidth;
                }
            }
            else {
                if (defaultDisplaySync.width != 0) {
                    textMaxWeight = px2vp(defaultDisplaySync.width);
                }
                else {
                    textMaxWeight = -1;
                }
            }
            textMaxWeight -= (this.theme.windows.padding.start.value - (this.theme.button.margin.end.value / 2));
            textMaxWeight -= this.theme.windows.padding.end.value;
            textMaxWeight -= this.theme.button.margin.start.value / 2;
            textMaxWeight -= this.theme.closeButton.margin.end.value;
            textMaxWeight -= this.getCloseButtonWidth();
        }
        return textMaxWeight;
    }
    getMessageFontWeight() {
        return this.theme.message.fontWeight;
    }
    getButtonMargin() {
        return {
            top: LengthMetrics.vp(this.theme.button.textMargin.top.value / 2 - 4),
            bottom: LengthMetrics.vp(this.theme.button.textMargin.bottom.value / 2 - 4),
            start: LengthMetrics.vp(this.theme.button.margin.start.value / 2 - 4),
            end: LengthMetrics.vp(this.theme.button.margin.end.value / 2 - 4)
        };
    }
    getButtonTextMargin() {
        return { top: LengthMetrics.vp(this.theme.button.textMargin.bottom.value) };
    }
    getButtonTextPadding() {
        return this.theme.button.padding;
    }
    getButtonHoverColor() {
        return this.theme.button.hoverColor;
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
        return this.theme.button.fontSize;
    }
    getSecondButtonFontSize() {
        return this.theme.button.fontSize;
    }
    getFirstButtonFontColor() {
        return this.theme.button.fontColor;
    }
    getSecondButtonFontColor() {
        return this.theme.button.fontColor;
    }
    getButtonMinFontSize() {
        return this.theme.button.minFontSize;
    }
    getButtonFontWeight() {
        return this.theme.button.fontWeight;
    }
    getBtnResponseRegion(actualWidth, actualHeight, minSizeVp) {
        if (actualWidth === 0 || actualHeight === 0 || minSizeVp <= 0) {
            return undefined;
        }
        let needExpandWidth = actualWidth === -1 ? false : (actualWidth < minSizeVp);
        let needExpandHeight = actualHeight < minSizeVp;
        if (!needExpandWidth && !needExpandHeight) {
            return undefined;
        }
        let regionWidth = needExpandWidth ? minSizeVp : '100%';
        let regionHeight = needExpandHeight ? minSizeVp : '100%';
        let offsetX = needExpandWidth ? (minSizeVp - actualWidth) / 2 : 0;
        let offsetY = needExpandHeight ? (minSizeVp - actualHeight) / 2 : 0;
        return {
            x: -offsetX,
            y: -offsetY,
            width: regionWidth,
            height: regionHeight
        };
    }
    getCloseBtnResponseRegion() {
        let responseRegionValue = this.toVp(this.theme.closeButton.responseRegion);
        return this.getBtnResponseRegion(this.theme.closeButton.size.width, this.theme.closeButton.size.height, responseRegionValue);
    }
    getNormalBtnResponseRegion(height) {
        let responseRegionValue = this.toVp(this.theme.button.responseRegion);
        return this.getBtnResponseRegion(-1, height, responseRegionValue);
    }
    getWindowsPadding() {
        let top = this.theme.windows.padding.top;
        let bottom = LengthMetrics.vp(this.theme.windows.padding.bottom.value - (this.theme.button.textMargin.bottom.value / 2));
        let start = LengthMetrics.vp(this.theme.windows.padding.start.value - (this.theme.button.margin.end.value / 2));
        let end = this.theme.windows.padding.end;
        let resolvedMaxWidth = this.toVp(this.maxWidth);
        if (resolvedMaxWidth === 0) {
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
        this.theme.message.plainFontColor = theme.colors.fontPrimary;
        this.closeButtonFillColorWithTheme = theme.colors.iconSecondary;
    }
    aboutToAppear() {
        let uiContext = this.getUIContext();
        this.appMaxFontScale = uiContext.getMaxFontScale();
        this.listener.on('change', (mediaQueryResult) => {
            setTimeout(() => {
                this.currentScreenStatus = mediaQueryResult.matches;
                this.setScrollMaxHeight(undefined, true);
            }, 10);
        });
    }
    aboutToDisappear() {
        this.listener.off('change');
    }
    setScrollMaxHeight(maxHeight, forceChange = false) {
        let scrollMaxHeight = undefined;
        if (maxHeight) {
            scrollMaxHeight = maxHeight;
        }
        else {
            this.applySizeOptions = this.getApplyMaxSize();
            let maxHeightInDisplay = this.applySizeOptions?.maxHeight;
            if (this.applyHeight && !forceChange) {
                scrollMaxHeight = Math.min(this.applyHeight, maxHeightInDisplay);
            }
            else {
                scrollMaxHeight = maxHeightInDisplay;
            }
        }
        scrollMaxHeight -= this.titleHeight;
        scrollMaxHeight -= this.buttonHeight;
        scrollMaxHeight -= this.theme.windows.padding.top.value;
        scrollMaxHeight -= (this.theme.button.textMargin.bottom.value / 2);
        scrollMaxHeight -= this.theme.title.margin.bottom.value;
        scrollMaxHeight -= (this.theme.windows.padding.bottom.value -
            (this.theme.button.textMargin.bottom.value / 2));
        if (Math.floor(this.textHeight) > Math.floor(scrollMaxHeight + 1)) {
            this.scrollMaxHeight = scrollMaxHeight;
        }
        else {
            this.scrollMaxHeight = undefined;
        }
    }
    getLayoutWeight() {
        let layoutWeight;
        if ((this.icon !== '' && this.icon !== void (0)) ||
            (this.title !== '' && this.title !== void (0)) ||
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
            return POPUP_DEFAULT_MAXWIDTH;
        }
    }
    toVp(value) {
        let defaultDisplaySync = undefined;
        try {
            defaultDisplaySync = display.getDefaultDisplaySync();
        }
        catch (error) {
            console.error(`Ace PopupV2 getDefaultDisplaySync, error: ${error.toString()}`);
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
                    let returnValue = this.resourceToVp(value);
                    if (returnValue === 0 &&
                        !isValidResource(getContext(this), value)) {
                        return Number.NEGATIVE_INFINITY;
                    }
                    return returnValue;
                }
                catch (error) {
                    return Number.NEGATIVE_INFINITY;
                }
            case 'string':
                let regex = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
                let matches = value.match(regex);
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
                        length = length / 100 * px2vp(defaultDisplaySync.width);
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
        let applyMaxWidth = undefined;
        let applyMaxHeight = undefined;
        let applyMaxSize = undefined;
        let defaultDisplaySync = undefined;
        let maxWidthSize = 400;
        try {
            defaultDisplaySync = display.getDefaultDisplaySync();
        }
        catch (error) {
            console.error(`Ace PopupV2 getDefaultDisplaySync, error: ${error.toString()}`);
            this.messageMaxWeight = 400;
            return applyMaxSize = { maxWidth: 400, maxHeight: 480 };
        }
        if (this.maxWidth !== undefined) {
            if (typeof this.maxWidth === 'number' && this.maxWidth >= 0) {
                maxWidthSize = this.maxWidth;
            }
            else if (typeof this.maxWidth === 'number' && this.maxWidth < 0) {
                maxWidthSize = POPUP_DEFAULT_MAXWIDTH;
            }
            else {
                maxWidthSize = this.toVp(this.maxWidth);
            }
        }
        if (px2vp(defaultDisplaySync.width) > maxWidthSize) {
            applyMaxWidth = maxWidthSize;
        }
        else {
            if (defaultDisplaySync.width != 0) {
                applyMaxWidth = px2vp(defaultDisplaySync.width);
            }
            else {
                applyMaxWidth = -1;
            }
        }
        if (px2vp(defaultDisplaySync.height) > 480) {
            applyMaxHeight = 480;
        }
        else {
            applyMaxHeight = px2vp(defaultDisplaySync.height) - 40 - 40;
        }
        applyMaxSize = { maxWidth: applyMaxWidth, maxHeight: applyMaxHeight };
        this.messageMaxWidth = applyMaxWidth;
        this.messageMaxWeight = this.getMessageMaxWeight();
        return applyMaxSize;
    }
    getTitleTextAlign() {
        let titleAlign = TextAlign.Start;
        if ((Configuration.getLocale().dir === 'rtl') &&
            (this.popupDirection === Direction.Auto || this.popupDirection === undefined)) {
            titleAlign = TextAlign.End;
        }
        return titleAlign;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.direction(this.popupDirection);
            Row.alignItems(VerticalAlign.Top);
            Row.padding(this.getWindowsPadding());
            Row.constraintSize(this.applySizeOptions);
            Row.constraintSize(this.getApplyMaxSize());
            Row.key(this.applycontentKey);
            Row.onAreaChange((_, rect) => {
                this.applyHeight = rect.height;
                this.setScrollMaxHeight(this.applyHeight);
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.icon !== '' && this.icon !== void (0)) {
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
                        Image.attributeModifier.bind(this)(this.iconModifier);
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
            if (this.title !== '' && this.title !== void (0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.direction(this.popupDirection);
                        Column.layoutWeight(this.getLayoutWeight());
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ alignItems: ItemAlign.Start });
                        Flex.direction(this.popupDirection);
                        Flex.width('100%');
                        Flex.margin(this.getTitleMargin());
                        Flex.onAreaChange((_, rect) => {
                            this.titleHeight = rect.height;
                            this.setScrollMaxHeight(undefined);
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
                        Text.attributeModifier.bind(this)(this.titleModifier);
                        Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
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
                                    Button.backgroundColor(this.closeButtonBackgroundColor);
                                    Button.flexShrink(0);
                                    Button.accessibilityText(this.theme.closeButton.accessibilityMessage);
                                    Button.responseRegion(this.getCloseBtnResponseRegion());
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
                                    SymbolGlyph.attributeModifier.bind(this)(this.theme.closeButton.symbolStyle);
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
                        Scroll.width('100%');
                        Scroll.align(Alignment.TopStart);
                        Scroll.padding(this.getMessagePadding());
                        Scroll.scrollBar(BarState.Auto);
                        Scroll.scrollable(ScrollDirection.Vertical);
                        Scroll.constraintSize({ maxHeight: this.scrollMaxHeight });
                        Scroll.edgeEffect(EdgeEffect.Spring, { alwaysEnabled: false });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.getMessageText());
                        Text.direction(this.popupDirection);
                        Text.fontSize(this.getMessageFontSize());
                        Text.fontColor(this.getMessageFontColor());
                        Text.fontWeight(this.getMessageFontWeight());
                        Text.constraintSize({ minHeight: this.getCloseButtonHeight() });
                        Text.textAlign(this.getTitleTextAlign());
                        Text.attributeModifier.bind(this)(this.messageModifier);
                        Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
                        Text.onAreaChange((_, rect) => {
                            this.textHeight = rect.height;
                            this.setScrollMaxHeight(undefined);
                        });
                    }, Text);
                    Text.pop();
                    Scroll.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({ wrap: FlexWrap.Wrap });
                        Flex.direction(this.popupDirection);
                        Flex.margin(this.getButtonTextMargin());
                        Flex.flexGrow(1);
                        Flex.onAreaChange((_, rect) => {
                            if ((this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
                                (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
                                this.buttonHeight = rect.height;
                            }
                            else {
                                this.buttonHeight = 0;
                            }
                            this.setScrollMaxHeight(undefined);
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
                                    Button.backgroundColor(this.firstButtonBackgroundColor);
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
                                    Button.onAreaChange((_, rect) => {
                                        this.firstButtonHeight = rect.height;
                                    });
                                    Button.responseRegion(this.getNormalBtnResponseRegion(this.firstButtonHeight));
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
                                    Text.attributeModifier.bind(this)(this.buttons?.[0]?.buttonTextModifier);
                                    Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
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
                                    Button.backgroundColor(this.secondButtonBackgroundColor);
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
                                    Button.onAreaChange((_, rect) => {
                                        this.secondButtonHeight = rect.height;
                                    });
                                    Button.responseRegion(this.getNormalBtnResponseRegion(this.secondButtonHeight));
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
                                    Text.attributeModifier.bind(this)(this.buttons?.[1]?.buttonTextModifier);
                                    Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
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
                        Flex.onAreaChange((_, rect) => {
                            this.titleHeight = rect.height;
                            this.setScrollMaxHeight(undefined);
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
                        Scroll.constraintSize({ maxHeight: this.scrollMaxHeight });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.getMessageText());
                        Text.direction(this.popupDirection);
                        Text.fontSize(this.getMessageFontSize());
                        Text.fontColor(this.getMessageFontColor());
                        Text.fontWeight(this.getMessageFontWeight());
                        Text.constraintSize({ maxWidth: this.messageMaxWeight, minHeight: this.getCloseButtonHeight() });
                        Text.textAlign(this.getTitleTextAlign());
                        Text.attributeModifier.bind(this)(this.messageModifier);
                        Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
                        Text.onAreaChange((_, rect) => {
                            this.textHeight = rect.height;
                            this.setScrollMaxHeight(undefined);
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
                                    Button.backgroundColor(this.closeButtonBackgroundColor);
                                    Button.flexShrink(0);
                                    Button.accessibilityText(this.theme.closeButton.accessibilityMessage);
                                    Button.responseRegion(this.getCloseBtnResponseRegion());
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
                                    SymbolGlyph.attributeModifier.bind(this)(this.theme.closeButton.symbolStyle);
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
                        Flex.onAreaChange((_, rect) => {
                            if ((this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
                                (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
                                this.buttonHeight = rect.height;
                            }
                            else {
                                this.buttonHeight = 0;
                            }
                            this.setScrollMaxHeight(undefined);
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
                                    Button.backgroundColor(this.firstButtonBackgroundColor);
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
                                    Button.onAreaChange((_, rect) => {
                                        this.firstButtonHeight = Number(rect.height);
                                    });
                                    Button.responseRegion(this.getNormalBtnResponseRegion(this.firstButtonHeight));
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
                                    Text.attributeModifier.bind(this)(this.buttons?.[0]?.buttonTextModifier);
                                    Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
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
                                    Button.backgroundColor(this.secondButtonBackgroundColor);
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
                                    Button.onAreaChange((_, rect) => {
                                        this.secondButtonHeight = rect.height;
                                    });
                                    Button.responseRegion(this.getNormalBtnResponseRegion(this.secondButtonHeight));
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
                                    Text.attributeModifier.bind(this)(this.buttons?.[1]?.buttonTextModifier);
                                    Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
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
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("onClose" in params) {
            this.updateParam("onClose", params.onClose);
        }
        if ("theme" in params) {
            this.updateParam("theme", params.theme);
        }
        if ("icon" in params) {
            this.updateParam("icon", params.icon);
        }
        if ("maxWidth" in params) {
            this.updateParam("maxWidth", params.maxWidth);
        }
        if ("title" in params) {
            this.updateParam("title", params.title);
        }
        if ("message" in params) {
            this.updateParam("message", params.message);
        }
        if ("iconModifier" in params) {
            this.updateParam("iconModifier", params.iconModifier);
        }
        if ("titleModifier" in params) {
            this.updateParam("titleModifier", params.titleModifier);
        }
        if ("messageModifier" in params) {
            this.updateParam("messageModifier", params.messageModifier);
        }
        if ("popupDirection" in params) {
            this.updateParam("popupDirection", params.popupDirection);
        }
        if ("showClose" in params) {
            this.updateParam("showClose", params.showClose);
        }
        if ("buttons" in params) {
            this.updateParam("buttons", params.buttons);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], PopupV2ComponentV2.prototype, "onClose", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "theme", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "icon", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "maxWidth", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "messageMaxWidth", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "title", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "message", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "iconModifier", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "titleModifier", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "messageModifier", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "popupDirection", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "showClose", void 0);
__decorate([
    Param
], PopupV2ComponentV2.prototype, "buttons", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "titleHeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "applyHeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "buttonHeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "messageMaxWeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "beforeScreenStatus", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "currentScreenStatus", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "applySizeOptions", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "closeButtonBackgroundColor", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "firstButtonBackgroundColor", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "secondButtonBackgroundColor", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "closeButtonFillColorWithTheme", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "scrollMaxHeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "firstButtonHeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "secondButtonHeight", void 0);
__decorate([
    Local
], PopupV2ComponentV2.prototype, "appMaxFontScale", void 0);
export default { PopupV2 };