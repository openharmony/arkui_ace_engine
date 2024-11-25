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

export const defaultTheme = {
    icon: {
        size: { width: 32, height: 32 },
        margin: {
            top: LengthMetrics.vp(12),
            bottom: LengthMetrics.vp(12),
            start: LengthMetrics.vp(12),
            end: LengthMetrics.vp(12)
        },
        fillColor: '',
        borderRadius: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_corner_radius_default_s'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }
    },
    title: {
        margin: { bottom: LengthMetrics.vp(2) },
        minFontSize: 12,
        fontWeight: FontWeight.Medium,
        fontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_sub_title2'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_primary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }
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
        fontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_button2'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_emphasize'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        textMargin: {
            top: LengthMetrics.vp(8),
            bottom: LengthMetrics.vp(8),
            start: LengthMetrics.vp(8),
            end: LengthMetrics.vp(8)
        },
        minFontSize: 9,
        fontWeight: FontWeight.Medium,
        hoverColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_hover'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        backgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }
    },
    message: {
        fontSize: {
            "id": -1,
            "type": 10002,
            params: ['sys.float.ohos_id_text_size_body2'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fontWeight: FontWeight.Regular,
        plainFontColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.font_primary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }
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
        imageSize: { width: 18, height: 18 },
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
        image: {
            "id": -1,
            "type": 20000,
            params: ['sys.media.ohos_ic_public_cancel'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        fillColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.icon_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        hoverColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_hover'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        },
        backgroundColor: {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }
    },
};
const noop = () => {
};

export function Popup(r29, s29 = null) {
    const t29 = r29;
    {
        (s29 ? s29 : this).observeComponentCreation2((v29, w29, x29 = t29) => {
            if (w29) {
                let y29 = new PopupComponent(typeof PUV2ViewBase !== "undefined" && s29 instanceof PUV2ViewBase ? s29 : this, {
                    icon: x29.icon,
                    title: x29.title,
                    message: x29.message,
                    popupDirection: x29.direction,
                    showClose: x29.showClose,
                    onClose: x29.onClose,
                    buttons: x29.buttons
                }, undefined, v29, () => {
                }, { page: "library/src/main/ets/components/popup/popup.ets", line: 198, col: 3 });
                ViewPU.create(y29);
                let z29 = () => {
                    return {
                        icon: x29.icon,
                        title: x29.title,
                        message: x29.message,
                        popupDirection: x29.direction,
                        showClose: x29.showClose,
                        onClose: x29.onClose,
                        buttons: x29.buttons
                    };
                };
                y29.paramsGenerator_ = z29;
            }
            else {
                (s29 ? s29 : this).updateStateVarsOfChildByElmtId(v29, {
                    icon: x29.icon,
                    title: x29.title,
                    message: x29.message,
                    popupDirection: x29.direction,
                    showClose: x29.showClose,
                    buttons: x29.buttons
                });
            }
        }, { name: "PopupComponent" });
    }
}

export class PopupComponent extends ViewPU {
    constructor(l29, m29, n29, o29 = -1, p29 = undefined, q29) {
        super(l29, n29, o29, q29);
        if (typeof p29 === "function") {
            this.paramsGenerator_ = p29;
        }
        this.onClose = noop;
        this.theme = defaultTheme;
        this.__icon = new SynchedPropertyObjectOneWayPU(m29.icon, this, "icon");
        this.__title = new SynchedPropertyObjectOneWayPU(m29.title, this, "title");
        this.__message = new SynchedPropertyObjectOneWayPU(m29.message, this, "message");
        this.__popupDirection = new SynchedPropertySimpleOneWayPU(m29.popupDirection, this, "popupDirection");
        this.__showClose = new SynchedPropertyObjectOneWayPU(m29.showClose, this, "showClose");
        this.__buttons = new SynchedPropertyObjectOneWayPU(m29.buttons, this, "buttons");
        this.textHeight = 0;
        this.__titleHeight = new ObservedPropertySimplePU(0, this, "titleHeight");
        this.__applyHeight = new ObservedPropertySimplePU(0, this, "applyHeight");
        this.__buttonHeight = new ObservedPropertySimplePU(0, this, "buttonHeight");
        this.__messageMaxWeight = new ObservedPropertyObjectPU(0, this, "messageMaxWeight");
        this.__beforeScreenStatus = new ObservedPropertySimplePU(undefined, this, "beforeScreenStatus");
        this.__currentScreenStatus = new ObservedPropertySimplePU(true, this, "currentScreenStatus");
        this.__applySizeOptions = new ObservedPropertyObjectPU(undefined, this, "applySizeOptions");
        this.__closeButtonBackgroundColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "closeButtonBackgroundColor");
        this.__firstButtonBackgroundColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "firstButtonBackgroundColor");
        this.__secondButtonBackgroundColor = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "secondButtonBackgroundColor");
        this.__closeButtonFillColorWithTheme = new ObservedPropertyObjectPU({
            "id": -1,
            "type": 10001,
            params: ['sys.color.icon_secondary'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
        }, this, "closeButtonFillColorWithTheme");
        this.listener = mediaquery.matchMediaSync('(orientation: landscape)');
        this.setInitiallyProvidedValue(m29);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(k29) {
        if (k29.onClose !== undefined) {
            this.onClose = k29.onClose;
        }
        if (k29.theme !== undefined) {
            this.theme = k29.theme;
        }
        if (k29.icon === undefined) {
            this.__icon.set({ image: '' });
        }
        if (k29.title === undefined) {
            this.__title.set({ text: '' });
        }
        if (k29.message === undefined) {
            this.__message.set({ text: '' });
        }
        if (k29.popupDirection === undefined) {
            this.__popupDirection.set(Direction.Auto);
        }
        if (k29.showClose === undefined) {
            this.__showClose.set(true);
        }
        if (k29.buttons === undefined) {
            this.__buttons.set([{ text: '' }, { text: '' }]);
        }
        if (k29.textHeight !== undefined) {
            this.textHeight = k29.textHeight;
        }
        if (k29.titleHeight !== undefined) {
            this.titleHeight = k29.titleHeight;
        }
        if (k29.applyHeight !== undefined) {
            this.applyHeight = k29.applyHeight;
        }
        if (k29.buttonHeight !== undefined) {
            this.buttonHeight = k29.buttonHeight;
        }
        if (k29.messageMaxWeight !== undefined) {
            this.messageMaxWeight = k29.messageMaxWeight;
        }
        if (k29.beforeScreenStatus !== undefined) {
            this.beforeScreenStatus = k29.beforeScreenStatus;
        }
        if (k29.currentScreenStatus !== undefined) {
            this.currentScreenStatus = k29.currentScreenStatus;
        }
        if (k29.applySizeOptions !== undefined) {
            this.applySizeOptions = k29.applySizeOptions;
        }
        if (k29.closeButtonBackgroundColor !== undefined) {
            this.closeButtonBackgroundColor = k29.closeButtonBackgroundColor;
        }
        if (k29.firstButtonBackgroundColor !== undefined) {
            this.firstButtonBackgroundColor = k29.firstButtonBackgroundColor;
        }
        if (k29.secondButtonBackgroundColor !== undefined) {
            this.secondButtonBackgroundColor = k29.secondButtonBackgroundColor;
        }
        if (k29.closeButtonFillColorWithTheme !== undefined) {
            this.closeButtonFillColorWithTheme = k29.closeButtonFillColorWithTheme;
        }
        if (k29.listener !== undefined) {
            this.listener = k29.listener;
        }
    }

    updateStateVars(j29) {
        this.__icon.reset(j29.icon);
        this.__title.reset(j29.title);
        this.__message.reset(j29.message);
        this.__popupDirection.reset(j29.popupDirection);
        this.__showClose.reset(j29.showClose);
        this.__buttons.reset(j29.buttons);
    }

    purgeVariableDependenciesOnElmtId(i29) {
        this.__icon.purgeDependencyOnElmtId(i29);
        this.__title.purgeDependencyOnElmtId(i29);
        this.__message.purgeDependencyOnElmtId(i29);
        this.__popupDirection.purgeDependencyOnElmtId(i29);
        this.__showClose.purgeDependencyOnElmtId(i29);
        this.__buttons.purgeDependencyOnElmtId(i29);
        this.__titleHeight.purgeDependencyOnElmtId(i29);
        this.__applyHeight.purgeDependencyOnElmtId(i29);
        this.__buttonHeight.purgeDependencyOnElmtId(i29);
        this.__messageMaxWeight.purgeDependencyOnElmtId(i29);
        this.__beforeScreenStatus.purgeDependencyOnElmtId(i29);
        this.__currentScreenStatus.purgeDependencyOnElmtId(i29);
        this.__applySizeOptions.purgeDependencyOnElmtId(i29);
        this.__closeButtonBackgroundColor.purgeDependencyOnElmtId(i29);
        this.__firstButtonBackgroundColor.purgeDependencyOnElmtId(i29);
        this.__secondButtonBackgroundColor.purgeDependencyOnElmtId(i29);
        this.__closeButtonFillColorWithTheme.purgeDependencyOnElmtId(i29);
    }

    aboutToBeDeleted() {
        this.__icon.aboutToBeDeleted();
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

    set icon(h29) {
        this.__icon.set(h29);
    }

    get title() {
        return this.__title.get();
    }

    set title(g29) {
        this.__title.set(g29);
    }

    get message() {
        return this.__message.get();
    }

    set message(f29) {
        this.__message.set(f29);
    }

    get popupDirection() {
        return this.__popupDirection.get();
    }

    set popupDirection(e29) {
        this.__popupDirection.set(e29);
    }

    get showClose() {
        return this.__showClose.get();
    }

    set showClose(d29) {
        this.__showClose.set(d29);
    }

    get buttons() {
        return this.__buttons.get();
    }

    set buttons(c29) {
        this.__buttons.set(c29);
    }

    get titleHeight() {
        return this.__titleHeight.get();
    }

    set titleHeight(b29) {
        this.__titleHeight.set(b29);
    }

    get applyHeight() {
        return this.__applyHeight.get();
    }

    set applyHeight(a29) {
        this.__applyHeight.set(a29);
    }

    get buttonHeight() {
        return this.__buttonHeight.get();
    }

    set buttonHeight(z28) {
        this.__buttonHeight.set(z28);
    }

    get messageMaxWeight() {
        return this.__messageMaxWeight.get();
    }

    set messageMaxWeight(y28) {
        this.__messageMaxWeight.set(y28);
    }

    get beforeScreenStatus() {
        return this.__beforeScreenStatus.get();
    }

    set beforeScreenStatus(x28) {
        this.__beforeScreenStatus.set(x28);
    }

    get currentScreenStatus() {
        return this.__currentScreenStatus.get();
    }

    set currentScreenStatus(w28) {
        this.__currentScreenStatus.set(w28);
    }

    get applySizeOptions() {
        return this.__applySizeOptions.get();
    }

    set applySizeOptions(v28) {
        this.__applySizeOptions.set(v28);
    }

    get closeButtonBackgroundColor() {
        return this.__closeButtonBackgroundColor.get();
    }

    set closeButtonBackgroundColor(u28) {
        this.__closeButtonBackgroundColor.set(u28);
    }

    get firstButtonBackgroundColor() {
        return this.__firstButtonBackgroundColor.get();
    }

    set firstButtonBackgroundColor(t28) {
        this.__firstButtonBackgroundColor.set(t28);
    }

    get secondButtonBackgroundColor() {
        return this.__secondButtonBackgroundColor.get();
    }

    set secondButtonBackgroundColor(s28) {
        this.__secondButtonBackgroundColor.set(s28);
    }

    get closeButtonFillColorWithTheme() {
        return this.__closeButtonFillColorWithTheme.get();
    }

    set closeButtonFillColorWithTheme(r28) {
        this.__closeButtonFillColorWithTheme.set(r28);
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
        return this.title?.fontWeight ?? this.theme.title.fontWeight;
    }

    getTitleFontSize() {
        return this.title?.fontSize ?? this.theme.title.fontSize;
    }

    getTitleFontColor() {
        return this.title?.fontColor ?? this.theme.title.fontColor;
    }

    getCloseButtonWidth() {
        return this.theme.closeButton.size.width;
    }

    getCloseButtonHeight() {
        return this.theme.closeButton.size.height;
    }

    getCloseButtonImage() {
        return this.theme.closeButton.image;
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

    getCloseButtonImageWidth() {
        return this.theme.closeButton.imageSize.width;
    }

    getCloseButtonImageHeight() {
        return this.theme.closeButton.imageSize.height;
    }

    getMessageText() {
        return this.message.text;
    }

    getMessageFontSize() {
        return this.message.fontSize ?? this.theme.message.fontSize;
    }

    getMessageFontColor() {
        let q28;
        if (this.message.fontColor) {
            q28 = this.message.fontColor;
        }
        else {
            if (this.title.text !== '' && this.title.text !== void (0)) {
                q28 = this.theme.message.fontColor;
            }
            else {
                q28 = this.theme.message.plainFontColor;
            }
        }
        return q28;
    }

    getMessagePadding() {
        let p28;
        if (this.title.text !== '' && this.title.text !== void (0)) {
            p28 = { start: LengthMetrics.vp(this.theme.button.margin.start.value / 2) };
        }
        else {
            p28 = {
                start: LengthMetrics.vp(this.theme.button.margin.start.value / 2),
                end: LengthMetrics.vp(this.theme.closeButton.margin.end.value)
            };
        }
        return p28;
    }

    getMessageMaxWeight() {
        let n28 = undefined;
        let o28 = display.getDefaultDisplaySync();
        if (this.showClose || this.showClose === void (0)) {
            if (px2vp(o28.width) > 400) {
                n28 = 400;
            }
            else {
                if (o28.width != 0) {
                    n28 = px2vp(o28.width);
                } else {
                    // The previewer does not support the display interface to use abnormal values
                    n28 = -1;
                }
            }
            n28 -= (this.theme.windows.padding.start.value - (this.theme.button.margin.end.value / 2));
            n28 -= this.theme.windows.padding.end.value;
            n28 -= this.theme.button.margin.start.value / 2;
            n28 -= this.getCloseButtonWidth();
        }
        return n28;
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
        return { top: LengthMetrics.vp(this.theme.button.textMargin.bottom.value ) };
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
        return {
            top: this.theme.windows.padding.top,
            bottom: LengthMetrics.vp(this.theme.windows.padding.bottom.value -
                (this.theme.button.textMargin.bottom.value / 2)),
            start: LengthMetrics.vp(this.theme.windows.padding.start.value -
                (this.theme.button.margin.end.value / 2)),
            end: this.theme.windows.padding.end
        };
    }

    onWillApplyTheme(m28) {
        this.theme.title.fontColor = m28.colors.fontPrimary;
        this.theme.button.fontColor = m28.colors.fontEmphasize;
        this.theme.message.fontColor = m28.colors.fontSecondary;
        this.theme.message.plainFontColor = m28.colors.fontPrimary;
        this.closeButtonFillColorWithTheme = m28.colors.iconSecondary;
    }

    aboutToAppear() {
        this.listener.on("change", (l28) => {
            this.currentScreenStatus = l28.matches;
        });
    }

    aboutToDisappear() {
        this.listener.off("change");
    }

    getScrollMaxHeight() {
        let j28 = undefined;
        if (this.currentScreenStatus !== this.beforeScreenStatus) {
            this.applySizeOptions = this.getApplyMaxSize();
            this.beforeScreenStatus = this.currentScreenStatus;
            return j28;
        }
        j28 = this.applyHeight;
        j28 -= this.titleHeight;
        j28 -= this.buttonHeight;
        j28 -= this.theme.windows.padding.top.value;
        j28 -= (this.theme.button.textMargin.bottom.value / 2);
        j28 -= this.theme.title.margin.bottom.value;
        j28 -= (this.theme.windows.padding.bottom.value -
            (this.theme.button.textMargin.bottom.value / 2));
        if (Math.floor(this.textHeight) > Math.floor(j28 + 1)) {
            return j28;
        }
        else {
            j28 = undefined;
            return j28;
        }
    }

    getLayoutWeight() {
        let i28;
        if ((this.icon.image !== '' && this.icon.image !== void (0)) ||
            (this.title.text !== '' && this.title.text !== void (0)) ||
            (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
            (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
            i28 = 1;
        }
        else {
            i28 = 0;
        }
        return i28;
    }

    getApplyMaxSize() {
        let e28 = undefined;
        let f28 = undefined;
        let g28 = undefined;
        let h28 = display.getDefaultDisplaySync();
        if (px2vp(h28.width) > 400) {
            e28 = 400;
        }
        else {
            if (h28.width != 0) {
                e28 = px2vp(h28.width);
            } else {
                // The previewer does not support the display interface to use abnormal values
                e28 = -1;
            }
        }
        if (px2vp(h28.height) > 480) {
            f28 = 480;
        }
        else {
            f28 = px2vp(h28.height) - 40 - 40;
        }
        g28 = { maxWidth: e28, maxHeight: f28 };
        this.messageMaxWeight = this.getMessageMaxWeight();
        return g28;
    }

    initialRender() {
        this.observeComponentCreation2((z27, a28) => {
            Row.create();
            Row.direction(this.popupDirection);
            Row.alignItems(VerticalAlign.Top);
            Row.padding(this.getWindowsPadding());
            Row.constraintSize(ObservedObject.GetRawObject(this.applySizeOptions));
            Row.onAreaChange((c28, d28) => {
                this.applyHeight = d28.height;
            });
        }, Row);
        this.observeComponentCreation2((s27, t27) => {
            If.create();
            if (this.icon.image !== '' && this.icon.image !== void (0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x27, y27) => {
                        Image.create(this.getIconImage());
                        Image.direction(this.popupDirection);
                        Image.width(this.getIconWidth());
                        Image.height(this.getIconHeight());
                        Image.margin(this.getIconMargin());
                        Image.fillColor(this.getIconFillColor());
                        Image.borderRadius(this.getIconBorderRadius());
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((m22, n22) => {
            If.create();
            if (this.title.text !== '' && this.title.text !== void (0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q27, r27) => {
                        Column.create();
                        Column.direction(this.popupDirection);
                        Column.layoutWeight(this.getLayoutWeight());
                    }, Column);
                    this.observeComponentCreation2((l27, m27) => {
                        Flex.create({ alignItems: ItemAlign.Start });
                        Flex.direction(this.popupDirection);
                        Flex.width("100%");
                        Flex.margin(this.getTitleMargin());
                        Flex.onAreaChange((o27, p27) => {
                            this.titleHeight = p27.height;
                        });
                    }, Flex);
                    this.observeComponentCreation2((j27, k27) => {
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
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((w26, x26) => {
                        If.create();
                        if (this.showClose || this.showClose === void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e27, f27) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.width(this.getCloseButtonWidth());
                                    Button.height(this.getCloseButtonHeight());
                                    Button.padding(this.getCloseButtonPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.closeButtonBackgroundColor));
                                    Button.flexShrink(0);
                                    Button.onHover((i27) => {
                                        if (i27) {
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
                                this.observeComponentCreation2((c27, d27) => {
                                    Image.create(this.getCloseButtonImage());
                                    Image.direction(this.popupDirection);
                                    Image.focusable(true);
                                    Image.width(this.getCloseButtonImageWidth());
                                    Image.height(this.getCloseButtonImageHeight());
                                    Image.fillColor(this.getCloseButtonFillColor());
                                }, Image);
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
                    this.observeComponentCreation2((u26, v26) => {
                        Scroll.create();
                        Scroll.direction(this.popupDirection);
                        Scroll.width("100%");
                        Scroll.align(Alignment.TopStart);
                        Scroll.padding(this.getMessagePadding());
                        Scroll.scrollBar(BarState.Auto);
                        Scroll.edgeEffect(EdgeEffect.Spring);
                        Scroll.scrollable(ScrollDirection.Vertical);
                        Scroll.constraintSize({ maxHeight: this.getScrollMaxHeight() });
                    }, Scroll);
                    this.observeComponentCreation2((p26, q26) => {
                        Text.create(this.getMessageText());
                        Text.direction(this.popupDirection);
                        Text.fontSize(this.getMessageFontSize());
                        Text.fontColor(this.getMessageFontColor());
                        Text.fontWeight(this.getMessageFontWeight());
                        Text.constraintSize({ minHeight: this.getCloseButtonHeight() });
                        Text.onAreaChange((s26, t26) => {
                            this.textHeight = t26.height;
                        });
                    }, Text);
                    Text.pop();
                    Scroll.pop();
                    this.observeComponentCreation2((k26, l26) => {
                        Flex.create({ wrap: FlexWrap.Wrap });
                        Flex.direction(this.popupDirection);
                        Flex.margin(this.getButtonTextMargin());
                        Flex.flexGrow(1);
                        Flex.onAreaChange((n26, o26) => {
                            this.buttonHeight = o26.height;
                        });
                    }, Flex);
                    this.observeComponentCreation2((x25, y25) => {
                        If.create();
                        if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f26, g26) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.firstButtonBackgroundColor));
                                    Button.onHover((j26) => {
                                        if (j26) {
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
                                this.observeComponentCreation2((d26, e26) => {
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
                    this.observeComponentCreation2((k25, l25) => {
                        If.create();
                        if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s25, t25) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.secondButtonBackgroundColor));
                                    Button.onHover((w25) => {
                                        if (w25) {
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
                                this.observeComponentCreation2((q25, r25) => {
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
                    this.observeComponentCreation2((y24, z24) => {
                        Column.create();
                        Column.direction(this.popupDirection);
                        Column.layoutWeight(this.getLayoutWeight());
                    }, Column);
                    this.observeComponentCreation2((i3, j3) => {
                        Flex.create();
                        Flex.height(0);
                        Flex.onAreaChange((l3, m3) => {
                            this.titleHeight = m3.height;
                        });
                    }, Flex);
                    Flex.pop();
                    this.observeComponentCreation2((w24, x24) => {
                        Row.create();
                        Row.direction(this.popupDirection);
                        Row.alignItems(VerticalAlign.Top);
                    }, Row);
                    this.observeComponentCreation2((u24, v24) => {
                        Scroll.create();
                        Scroll.direction(this.popupDirection);
                        Scroll.layoutWeight(this.getLayoutWeight());
                        Scroll.align(Alignment.TopStart);
                        Scroll.padding(this.getMessagePadding());
                        Scroll.scrollBar(BarState.Auto);
                        Scroll.scrollable(ScrollDirection.Vertical);
                        Scroll.edgeEffect(EdgeEffect.Spring);
                        Scroll.constraintSize({ maxHeight: this.getScrollMaxHeight() });
                    }, Scroll);
                    this.observeComponentCreation2((p24, q24) => {
                        Text.create(this.getMessageText());
                        Text.direction(this.popupDirection);
                        Text.fontSize(this.getMessageFontSize());
                        Text.fontColor(this.getMessageFontColor());
                        Text.fontWeight(this.getMessageFontWeight());
                        Text.constraintSize({
                            maxWidth: this.messageMaxWeight,
                            minHeight: this.getCloseButtonHeight()
                        });
                        Text.onAreaChange((s24, t24) => {
                            this.textHeight = t24.height;
                        });
                    }, Text);
                    Text.pop();
                    Scroll.pop();
                    this.observeComponentCreation2((c24, d24) => {
                        If.create();
                        if (this.showClose || this.showClose === void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k24, l24) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.width(this.getCloseButtonWidth());
                                    Button.height(this.getCloseButtonHeight());
                                    Button.padding(this.getCloseButtonPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.closeButtonBackgroundColor));
                                    Button.flexShrink(0);
                                    Button.onHover((o24) => {
                                        if (o24) {
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
                                this.observeComponentCreation2((i24, j24) => {
                                    Image.create(this.getCloseButtonImage());
                                    Image.direction(this.popupDirection);
                                    Image.focusable(true);
                                    Image.width(this.getCloseButtonImageWidth());
                                    Image.height(this.getCloseButtonImageHeight());
                                    Image.fillColor(this.getCloseButtonFillColor());
                                }, Image);
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
                    this.observeComponentCreation2((x23, y23) => {
                        Flex.create({ wrap: FlexWrap.Wrap });
                        Flex.direction(this.popupDirection);
                        Flex.margin(this.getButtonTextMargin());
                        Flex.flexGrow(1);
                        Flex.onAreaChange((a24, b24) => {
                            this.buttonHeight = b24.height;
                        });
                    }, Flex);
                    this.observeComponentCreation2((k23, l23) => {
                        If.create();
                        if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s23, t23) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.firstButtonBackgroundColor));
                                    Button.onHover((w23) => {
                                        if (w23) {
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
                                this.observeComponentCreation2((q23, r23) => {
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
                    this.observeComponentCreation2((x22, y22) => {
                        If.create();
                        if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f23, g23) => {
                                    Button.createWithChild();
                                    Button.direction(this.popupDirection);
                                    Button.margin(this.getButtonMargin());
                                    Button.padding(this.getButtonTextPadding());
                                    Button.backgroundColor(ObservedObject.GetRawObject(this.secondButtonBackgroundColor));
                                    Button.onHover((j23) => {
                                        if (j23) {
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
                                this.observeComponentCreation2((d23, e23) => {
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