/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');

export var IconType;
(function (x11) {
    x11[x11['BADGE'] = 1] = 'BADGE';
    x11[x11['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    x11[x11['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    x11[x11['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    x11[x11['APP_ICON'] = 5] = 'APP_ICON';
    x11[x11['PREVIEW'] = 6] = 'PREVIEW';
    x11[x11['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    x11[x11['VERTICAL'] = 8] = 'VERTICAL';
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (w11) {
    w11[w11['LEVEL1'] = 1.75] = 'LEVEL1';
    w11[w11['LEVEL2'] = 2] = 'LEVEL2';
    w11[w11['LEVEL3'] = 3.2] = 'LEVEL3';
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (v11) {
    v11[v11['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    v11[v11['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    v11[v11['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    v11[v11['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    v11[v11['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
})(ItemHeight || (ItemHeight = {}));
const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
const LISTITEM_PADDING = 6;
const SWITCH_PADDING = 4;
const STACK_PADDING = 4;
const BADGE_SIZE = 8;
const SMALL_ICON_SIZE = 16;
const SYSTEM_ICON_SIZE = 24;
const TEXT_ARROW_HEIGHT = 32;
const SAFE_LIST_PADDING = 32;
const HEADSCULPTURE_SIZE = 40;
const BUTTON_SIZE = 28;
const APP_ICON_SIZE = 64;
const PREVIEW_SIZE = 96;
const LONGITUDINAL_SIZE = 96;
const VERTICAL_SIZE = 96;
const NORMAL_ITEM_ROW_SPACE = 16;
const SPECIAL_ITEM_ROW_SPACE = 0;
const SPECIAL_ICON_SIZE = 0;
const DEFAULT_ROW_SPACE = 0;
const SPECICAL_ROW_SPACE = 4;
const OPERATEITEM_ICONLIKE_SIZE = 24;
const OPERATEITEM_SELECTIONBOX_PADDING_SIZE = 2;
const OPERATEITEM_ARROW_WIDTH = 12;
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const RIGHT_ONLY_IMAGE_WIDTH = '54vp';
const RIGHT_ONLY_ICON_WIDTH = '40vp';
const RIGHT_ICON_SUB_ICON_WIDTH = '80vp';
const RIGHT_ONLY_RADIO_WIDTH = '30vp';
const RIGHT_ONLY_CHECKBOX_WIDTH = '30vp';
const RIGHT_ONLY_SWITCH_WIDTH = '44vp';
const ACCESSIBILITY_LEVEL_AUTO = 'auto';
const RESOURCE_TYPE_SYMBOL = 40000;
const ICON_SIZE_MAP = new Map([
    [IconType.BADGE, BADGE_SIZE],
    [IconType.NORMAL_ICON, SMALL_ICON_SIZE],
    [IconType.SYSTEM_ICON, SYSTEM_ICON_SIZE],
    [IconType.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
    [IconType.APP_ICON, APP_ICON_SIZE],
    [IconType.PREVIEW, PREVIEW_SIZE],
    [IconType.LONGITUDINAL, LONGITUDINAL_SIZE],
    [IconType.VERTICAL, VERTICAL_SIZE]
]);
const IS_SUPPORT_SUBCOMPONENT_EVENT = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_focus_dynamic_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value !== 1;
const RECOVER_ITEM_SCALE = 1;
const CLEAR_SHADOW = -1;
const OPERATE_ITEM_RADIUS = 50;
const OPERATE_ITEM_BACKGROUND_COLOR = '#33000000';
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR = { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_switch_outline_off'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const OPERATE_ITEM_COLOR = '#99000000';
const TEXT_SUPPORT_MARQUEE = 1;
const IS_MARQUEE_OR_ELLIPSIS = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_right_textOverflow'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value;
const UNUSUAL = -1;
const FOCUSED_BG_COLOR = { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_container_focus_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const NORMAL_BG_COLOR = { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_container_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const FOCUSED_ITEM_SCALE = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_focus_magnification'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value;
const FOCUSED_SHADOW = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_focus_shadow_attribute'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
    .value;
const NORMAL_SHADOW = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_normal_shadow_attribute'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })
    .value;
const ITEM_PADDING = { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const OPERATEITEM_ARROW_MARGIN_WIDTH = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_arrow_margin'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value;
const APPICON_ITEMLENGTH = LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_AppIcon_ItemLength'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value;
class Util {
    static isSymbolResource(t11) {
        if (!Util.isResourceType(t11)) {
            return false;
        }
        let u11 = t11;
        return u11.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(s11) {
        if (!s11) {
            return false;
        }
        if (typeof s11 === 'string' || typeof s11 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ContentItemStruct extends ViewPU {
    constructor(m11, n11, o11, p11 = -1, q11 = undefined, r11) {
        super(m11, o11, p11, r11);
        if (typeof q11 === 'function') {
            this.paramsGenerator_ = q11;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(n11.iconStyle, this, 'iconStyle');
        this.__icon = new SynchedPropertyObjectOneWayPU(n11.icon, this, 'icon');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(n11.symbolStyle, this, 'symbolStyle');
        this.__primaryText = new SynchedPropertyObjectOneWayPU(n11.primaryText, this, 'primaryText');
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(n11.secondaryText, this, 'secondaryText');
        this.__description = new SynchedPropertyObjectOneWayPU(n11.description, this, 'description');
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, 'itemRowSpace');
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(n11.leftWidth, this, 'leftWidth');
        this.__primaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextColor');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.__descriptionColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'descriptionColor');
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(n11.fontSizeScale, this, 'fontSizeScale');
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(n11.parentDirection, this, 'parentDirection');
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(n11.itemDirection, this, 'itemDirection');
        this.__isFocus = new SynchedPropertySimpleOneWayPU(n11.isFocus, this, 'isFocus');
        this.__primaryTextSize = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextSize');
        this.__primaryTextColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextColors');
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(n11.itemHeight, this, 'itemHeight');
        this.__iconColor = new ObservedPropertyObjectPU(null, this, 'iconColor');
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColors');
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_left_secondary_tertiary_text_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryThirdTextSize');
        this.__descriptionColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'descriptionColors');
        this.__isWrapText = new SynchedPropertyObjectTwoWayPU(n11.isWrapText, this, 'isWrapText');
        this.__isWrapFirstText = new ObservedPropertyObjectPU(false, this, 'isWrapFirstText');
        this.__isWrapSecondText = new ObservedPropertyObjectPU(false, this, 'isWrapSecondText');
        this.__isWrapThirdText = new ObservedPropertyObjectPU(false, this, 'isWrapThirdText');
        this.setInitiallyProvidedValue(n11);
        this.declareWatch('iconStyle', this.onPropChange);
        this.declareWatch('icon', this.onPropChange);
        this.declareWatch('symbolStyle', this.onPropChange);
        this.declareWatch('primaryText', this.onPropChange);
        this.declareWatch('secondaryText', this.onPropChange);
        this.declareWatch('description', this.onPropChange);
        this.declareWatch('primaryTextColor', this.onPropChange);
        this.declareWatch('secondaryTextColor', this.onPropChange);
        this.declareWatch('descriptionColor', this.onPropChange);
        this.declareWatch('isFocus', this.onPropChange);
        this.declareWatch('isWrapFirstText', this.onWrapChange);
        this.declareWatch('isWrapSecondText', this.onWrapChange);
        this.declareWatch('isWrapThirdText', this.onWrapChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l11) {
        if (l11.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (l11.icon === undefined) {
            this.__icon.set(null);
        }
        if (l11.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (l11.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (l11.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (l11.description === undefined) {
            this.__description.set(null);
        }
        if (l11.itemRowSpace !== undefined) {
            this.itemRowSpace = l11.itemRowSpace;
        }
        if (l11.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (l11.primaryTextColor !== undefined) {
            this.primaryTextColor = l11.primaryTextColor;
        }
        if (l11.secondaryTextColor !== undefined) {
            this.secondaryTextColor = l11.secondaryTextColor;
        }
        if (l11.descriptionColor !== undefined) {
            this.descriptionColor = l11.descriptionColor;
        }
        if (l11.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (l11.primaryTextSize !== undefined) {
            this.primaryTextSize = l11.primaryTextSize;
        }
        if (l11.primaryTextColors !== undefined) {
            this.primaryTextColors = l11.primaryTextColors;
        }
        if (l11.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (l11.iconColor !== undefined) {
            this.iconColor = l11.iconColor;
        }
        if (l11.secondaryTextColors !== undefined) {
            this.secondaryTextColors = l11.secondaryTextColors;
        }
        if (l11.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = l11.secondaryThirdTextSize;
        }
        if (l11.descriptionColors !== undefined) {
            this.descriptionColors = l11.descriptionColors;
        }
        if (l11.isWrapFirstText !== undefined) {
            this.isWrapFirstText = l11.isWrapFirstText;
        }
        if (l11.isWrapSecondText !== undefined) {
            this.isWrapSecondText = l11.isWrapSecondText;
        }
        if (l11.isWrapThirdText !== undefined) {
            this.isWrapThirdText = l11.isWrapThirdText;
        }
    }
    updateStateVars(k11) {
        this.__iconStyle.reset(k11.iconStyle);
        this.__icon.reset(k11.icon);
        this.__symbolStyle.reset(k11.symbolStyle);
        this.__primaryText.reset(k11.primaryText);
        this.__secondaryText.reset(k11.secondaryText);
        this.__description.reset(k11.description);
        this.__leftWidth.reset(k11.leftWidth);
        this.__fontSizeScale.reset(k11.fontSizeScale);
        this.__parentDirection.reset(k11.parentDirection);
        this.__itemDirection.reset(k11.itemDirection);
        this.__isFocus.reset(k11.isFocus);
        this.__itemHeight.reset(k11.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(j11) {
        this.__iconStyle.purgeDependencyOnElmtId(j11);
        this.__icon.purgeDependencyOnElmtId(j11);
        this.__symbolStyle.purgeDependencyOnElmtId(j11);
        this.__primaryText.purgeDependencyOnElmtId(j11);
        this.__secondaryText.purgeDependencyOnElmtId(j11);
        this.__description.purgeDependencyOnElmtId(j11);
        this.__itemRowSpace.purgeDependencyOnElmtId(j11);
        this.__leftWidth.purgeDependencyOnElmtId(j11);
        this.__primaryTextColor.purgeDependencyOnElmtId(j11);
        this.__secondaryTextColor.purgeDependencyOnElmtId(j11);
        this.__descriptionColor.purgeDependencyOnElmtId(j11);
        this.__fontSizeScale.purgeDependencyOnElmtId(j11);
        this.__parentDirection.purgeDependencyOnElmtId(j11);
        this.__itemDirection.purgeDependencyOnElmtId(j11);
        this.__isFocus.purgeDependencyOnElmtId(j11);
        this.__primaryTextSize.purgeDependencyOnElmtId(j11);
        this.__primaryTextColors.purgeDependencyOnElmtId(j11);
        this.__itemHeight.purgeDependencyOnElmtId(j11);
        this.__iconColor.purgeDependencyOnElmtId(j11);
        this.__secondaryTextColors.purgeDependencyOnElmtId(j11);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(j11);
        this.__descriptionColors.purgeDependencyOnElmtId(j11);
        this.__isWrapText.purgeDependencyOnElmtId(j11);
        this.__isWrapFirstText.purgeDependencyOnElmtId(j11);
        this.__isWrapSecondText.purgeDependencyOnElmtId(j11);
        this.__isWrapThirdText.purgeDependencyOnElmtId(j11);
    }
    aboutToBeDeleted() {
        this.__iconStyle.aboutToBeDeleted();
        this.__icon.aboutToBeDeleted();
        this.__symbolStyle.aboutToBeDeleted();
        this.__primaryText.aboutToBeDeleted();
        this.__secondaryText.aboutToBeDeleted();
        this.__description.aboutToBeDeleted();
        this.__itemRowSpace.aboutToBeDeleted();
        this.__leftWidth.aboutToBeDeleted();
        this.__primaryTextColor.aboutToBeDeleted();
        this.__secondaryTextColor.aboutToBeDeleted();
        this.__descriptionColor.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__parentDirection.aboutToBeDeleted();
        this.__itemDirection.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__primaryTextSize.aboutToBeDeleted();
        this.__primaryTextColors.aboutToBeDeleted();
        this.__itemHeight.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__secondaryTextColors.aboutToBeDeleted();
        this.__secondaryThirdTextSize.aboutToBeDeleted();
        this.__descriptionColors.aboutToBeDeleted();
        this.__isWrapText.aboutToBeDeleted();
        this.__isWrapFirstText.aboutToBeDeleted();
        this.__isWrapSecondText.aboutToBeDeleted();
        this.__isWrapThirdText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.__iconStyle.get();
    }
    set iconStyle(i11) {
        this.__iconStyle.set(i11);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(h11) {
        this.__icon.set(h11);
    }
    get symbolStyle() {
        return this.__symbolStyle.get();
    }
    set symbolStyle(g11) {
        this.__symbolStyle.set(g11);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(f11) {
        this.__primaryText.set(f11);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(e11) {
        this.__secondaryText.set(e11);
    }
    get description() {
        return this.__description.get();
    }
    set description(d11) {
        this.__description.set(d11);
    }
    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }
    set itemRowSpace(c11) {
        this.__itemRowSpace.set(c11);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(b11) {
        this.__leftWidth.set(b11);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(a11) {
        this.__primaryTextColor.set(a11);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(z10) {
        this.__secondaryTextColor.set(z10);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(y10) {
        this.__descriptionColor.set(y10);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(x10) {
        this.__fontSizeScale.set(x10);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(w10) {
        this.__parentDirection.set(w10);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(v10) {
        this.__itemDirection.set(v10);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(u10) {
        this.__isFocus.set(u10);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(t10) {
        this.__primaryTextSize.set(t10);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(s10) {
        this.__primaryTextColors.set(s10);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(r10) {
        this.__itemHeight.set(r10);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(q10) {
        this.__iconColor.set(q10);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(p10) {
        this.__secondaryTextColors.set(p10);
    }
    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }
    set secondaryThirdTextSize(o10) {
        this.__secondaryThirdTextSize.set(o10);
    }
    get descriptionColors() {
        return this.__descriptionColors.get();
    }
    set descriptionColors(n10) {
        this.__descriptionColors.set(n10);
    }
    get isWrapText() {
        return this.__isWrapText.get();
    }
    set isWrapText(m10) {
        this.__isWrapText.set(m10);
    }
    get isWrapFirstText() {
        return this.__isWrapFirstText.get();
    }
    set isWrapFirstText(l10) {
        this.__isWrapFirstText.set(l10);
    }
    get isWrapSecondText() {
        return this.__isWrapSecondText.get();
    }
    set isWrapSecondText(k10) {
        this.__isWrapSecondText.set(k10);
    }
    get isWrapThirdText() {
        return this.__isWrapThirdText.get();
    }
    set isWrapThirdText(j10) {
        this.__isWrapThirdText.set(j10);
    }
    onWillApplyTheme(i10) {
        this.primaryTextColor = i10.colors.fontPrimary;
        this.secondaryTextColor = i10.colors.fontSecondary;
        this.descriptionColor = i10.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        else {
            this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
            this.primaryTextColors = { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_left_text_focus_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            this.secondaryTextColors = { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_left_secondary_text_focus_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            this.descriptionColors = { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_left_secondary_text_focus_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            this.primaryTextColors = this.primaryTextColor;
            this.secondaryTextColors = this.secondaryTextColor;
            this.descriptionColors = this.descriptionColor;
        }
    }
    onWrapChange() {
        this.isWrapText = this.isWrapFirstText || this.isWrapSecondText || this.isWrapThirdText;
    }
    getContentItemIconFillColor() {
        switch (this.iconStyle) {
            case IconType.BADGE:
                return { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_badge_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            case IconType.SYSTEM_ICON:
                return { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_icon_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
            default:
                return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
    }
    judgeIsWrap(e10, f10, g10) {
        let h10 = this.getSingleRowTextHeight(e10, f10);
        return g10 > h10;
    }
    getSingleRowTextHeight(b10, c10) {
        if (b10 && c10) {
            let d10 = px2vp(measure.measureTextSize({
                textContent: b10,
                fontSize: c10,
                maxLines: TEXT_MAX_LINE
            }).height);
            return d10;
        }
        return 0;
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createIcon(k9 = null) {
        this.observeComponentCreation2((l9, m9) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n9, o9) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((z9, a10) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([this.getContentItemIconFillColor()]);
                                    SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
                                    SymbolGlyph.fontSize(`${ICON_SIZE_MAP.get(this.iconStyle)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_Image_Radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.flexShrink(0);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.icon != null) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p9, q9) => {
                                    If.create();
                                    if (Util.isSymbolResource(ObservedObject.GetRawObject(this.icon))) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((x9, y9) => {
                                                SymbolGlyph.create(this.icon);
                                                SymbolGlyph.fontSize(`${ICON_SIZE_MAP.get(this.iconStyle)}vp`);
                                                SymbolGlyph.fontColor([this.getContentItemIconFillColor()]);
                                                SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_Image_Radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.flexShrink(0);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((r9, s9) => {
                                                If.create();
                                                if (this.iconStyle <= IconType.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((v9, w9) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_Image_Radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor(this.getContentItemIconFillColor());
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                }
                                                else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((t9, u9) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.constraintSize({
                                                                minWidth: SPECIAL_ICON_SIZE,
                                                                maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                                                minHeight: SPECIAL_ICON_SIZE,
                                                                maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                                            });
                                                            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_Image_Radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor(this.getContentItemIconFillColor());
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                }
                                            }, If);
                                            If.pop();
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    createText(r8 = null) {
        this.observeComponentCreation2((i9, j9) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((e9, f9) => {
            Text.create(this.primaryText);
            Text.fontSize(ObservedObject.GetRawObject(this.primaryTextSize));
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColors));
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                TextOverflow.Ellipsis
            });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.onSizeChange((g9, h9) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isWrapFirstText = this.judgeIsWrap(ObservedObject.GetRawObject(this.primaryText), ObservedObject.GetRawObject(this.primaryTextSize), h9.height);
                }
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((y8, z8) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a9, b9) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((c9, d9) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                                this.isWrapSecondText = this.judgeIsWrap(ObservedObject.GetRawObject(this.secondaryText), ObservedObject.GetRawObject(this.secondaryThirdTextSize), d9.height);
                            }
                        });
                    }, Text);
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((s8, t8) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u8, v8) => {
                        Text.create(this.description);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((w8, x8) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                                this.isWrapThirdText = this.judgeIsWrap(ObservedObject.GetRawObject(this.description), ObservedObject.GetRawObject(this.secondaryThirdTextSize), x8.height);
                            }
                        });
                    }, Text);
                    Text.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }
    isColumnDirection() {
        return this.itemDirection === FlexDirection.Column;
    }
    isParentColumnDirection() {
        return this.parentDirection === FlexDirection.Column;
    }
    getItemSpace() {
        if (this.isColumnDirection()) {
            return LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        return LengthMetrics.vp(this.itemRowSpace);
    }
    initialRender() {
        this.observeComponentCreation2((p8, q8) => {
            Flex.create({
                space: { main: this.getItemSpace() },
                direction: this.itemDirection,
                justifyContent: FlexAlign.Start,
                alignItems: this.isColumnDirection() ? ItemAlign.Start : ItemAlign.Center,
            });
            Flex.height(this.itemDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.margin({
                end: this.isParentColumnDirection() ?
                LengthMetrics.vp(0) :
                LengthMetrics.vp(16)
            });
            Flex.padding({ start: LengthMetrics.vp(LISTITEM_PADDING) });
            Flex.flexShrink(this.isParentColumnDirection() ? 0 : 1);
        }, Flex);
        this.createIcon.bind(this)();
        this.createText.bind(this)();
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class CreateIconParam {
}
class OperateItemStruct extends ViewPU {
    constructor(j8, k8, l8, m8 = -1, n8 = undefined, o8) {
        super(j8, l8, m8, o8);
        if (typeof n8 === 'function') {
            this.paramsGenerator_ = n8;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(k8.arrow, this, 'arrow');
        this.__icon = new SynchedPropertyObjectOneWayPU(k8.icon, this, 'icon');
        this.__subIcon = new SynchedPropertyObjectOneWayPU(k8.subIcon, this, 'subIcon');
        this.__button = new SynchedPropertyObjectOneWayPU(k8.button, this, 'button');
        this.__switch = new SynchedPropertyObjectOneWayPU(k8.switch, this, 'switch');
        this.__checkBox = new SynchedPropertyObjectOneWayPU(k8.checkBox, this, 'checkBox');
        this.__radio = new SynchedPropertyObjectOneWayPU(k8.radio, this, 'radio');
        this.__image = new SynchedPropertyObjectOneWayPU(k8.image, this, 'image');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(k8.symbolStyle, this, 'symbolStyle');
        this.__text = new SynchedPropertyObjectOneWayPU(k8.text, this, 'text');
        this.__switchState = new ObservedPropertySimplePU(false, this, 'switchState');
        this.__radioState = new ObservedPropertySimplePU(false, this, 'radioState');
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, 'checkBoxState');
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(k8.rightWidth, this, 'rightWidth');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(k8.parentCanFocus, this, 'parentCanFocus');
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(k8.parentCanTouch, this, 'parentCanTouch');
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(k8.parentIsHover, this, 'parentIsHover');
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(k8.parentCanHover, this, 'parentCanHover');
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(k8.parentIsActive, this, 'parentIsActive');
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(k8.parentFrontColor, this, 'parentFrontColor');
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(k8.parentDirection, this, 'parentDirection');
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, 'rowSpace');
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(k8.isFocus, this, 'isFocus');
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextSize');
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColors');
        this.__iconColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_right_icon_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'iconColor');
        this.__isChecked = new SynchedPropertySimpleTwoWayPU(k8.isChecked, this, 'isChecked');
        this.setInitiallyProvidedValue(k8);
        this.declareWatch('arrow', this.onPropChange);
        this.declareWatch('icon', this.onPropChange);
        this.declareWatch('subIcon', this.onPropChange);
        this.declareWatch('button', this.onPropChange);
        this.declareWatch('switch', this.onPropChange);
        this.declareWatch('checkBox', this.onPropChange);
        this.declareWatch('radio', this.onPropChange);
        this.declareWatch('image', this.onPropChange);
        this.declareWatch('symbolStyle', this.onPropChange);
        this.declareWatch('text', this.onPropChange);
        this.declareWatch('secondaryTextColor', this.onFocusChange);
        this.declareWatch('isFocus', this.onFocusChange);
        this.declareWatch('isChecked', this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i8) {
        if (i8.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (i8.icon === undefined) {
            this.__icon.set(null);
        }
        if (i8.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (i8.button === undefined) {
            this.__button.set(null);
        }
        if (i8.switch === undefined) {
            this.__switch.set(null);
        }
        if (i8.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (i8.radio === undefined) {
            this.__radio.set(null);
        }
        if (i8.image === undefined) {
            this.__image.set(null);
        }
        if (i8.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (i8.text === undefined) {
            this.__text.set(null);
        }
        if (i8.switchState !== undefined) {
            this.switchState = i8.switchState;
        }
        if (i8.radioState !== undefined) {
            this.radioState = i8.radioState;
        }
        if (i8.checkBoxState !== undefined) {
            this.checkBoxState = i8.checkBoxState;
        }
        if (i8.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (i8.secondaryTextColor !== undefined) {
            this.secondaryTextColor = i8.secondaryTextColor;
        }
        if (i8.hoveringColor !== undefined) {
            this.hoveringColor = i8.hoveringColor;
        }
        if (i8.activedColor !== undefined) {
            this.activedColor = i8.activedColor;
        }
        if (i8.rowSpace !== undefined) {
            this.rowSpace = i8.rowSpace;
        }
        if (i8.secondaryTextSize !== undefined) {
            this.secondaryTextSize = i8.secondaryTextSize;
        }
        if (i8.secondaryTextColors !== undefined) {
            this.secondaryTextColors = i8.secondaryTextColors;
        }
        if (i8.iconColor !== undefined) {
            this.iconColor = i8.iconColor;
        }
    }
    updateStateVars(h8) {
        this.__arrow.reset(h8.arrow);
        this.__icon.reset(h8.icon);
        this.__subIcon.reset(h8.subIcon);
        this.__button.reset(h8.button);
        this.__switch.reset(h8.switch);
        this.__checkBox.reset(h8.checkBox);
        this.__radio.reset(h8.radio);
        this.__image.reset(h8.image);
        this.__symbolStyle.reset(h8.symbolStyle);
        this.__text.reset(h8.text);
        this.__rightWidth.reset(h8.rightWidth);
    }
    purgeVariableDependenciesOnElmtId(g8) {
        this.__arrow.purgeDependencyOnElmtId(g8);
        this.__icon.purgeDependencyOnElmtId(g8);
        this.__subIcon.purgeDependencyOnElmtId(g8);
        this.__button.purgeDependencyOnElmtId(g8);
        this.__switch.purgeDependencyOnElmtId(g8);
        this.__checkBox.purgeDependencyOnElmtId(g8);
        this.__radio.purgeDependencyOnElmtId(g8);
        this.__image.purgeDependencyOnElmtId(g8);
        this.__symbolStyle.purgeDependencyOnElmtId(g8);
        this.__text.purgeDependencyOnElmtId(g8);
        this.__switchState.purgeDependencyOnElmtId(g8);
        this.__radioState.purgeDependencyOnElmtId(g8);
        this.__checkBoxState.purgeDependencyOnElmtId(g8);
        this.__rightWidth.purgeDependencyOnElmtId(g8);
        this.__secondaryTextColor.purgeDependencyOnElmtId(g8);
        this.__hoveringColor.purgeDependencyOnElmtId(g8);
        this.__activedColor.purgeDependencyOnElmtId(g8);
        this.__parentCanFocus.purgeDependencyOnElmtId(g8);
        this.__parentCanTouch.purgeDependencyOnElmtId(g8);
        this.__parentIsHover.purgeDependencyOnElmtId(g8);
        this.__parentCanHover.purgeDependencyOnElmtId(g8);
        this.__parentIsActive.purgeDependencyOnElmtId(g8);
        this.__parentFrontColor.purgeDependencyOnElmtId(g8);
        this.__parentDirection.purgeDependencyOnElmtId(g8);
        this.__rowSpace.purgeDependencyOnElmtId(g8);
        this.__isFocus.purgeDependencyOnElmtId(g8);
        this.__secondaryTextSize.purgeDependencyOnElmtId(g8);
        this.__secondaryTextColors.purgeDependencyOnElmtId(g8);
        this.__iconColor.purgeDependencyOnElmtId(g8);
        this.__isChecked.purgeDependencyOnElmtId(g8);
    }
    aboutToBeDeleted() {
        this.__arrow.aboutToBeDeleted();
        this.__icon.aboutToBeDeleted();
        this.__subIcon.aboutToBeDeleted();
        this.__button.aboutToBeDeleted();
        this.__switch.aboutToBeDeleted();
        this.__checkBox.aboutToBeDeleted();
        this.__radio.aboutToBeDeleted();
        this.__image.aboutToBeDeleted();
        this.__symbolStyle.aboutToBeDeleted();
        this.__text.aboutToBeDeleted();
        this.__switchState.aboutToBeDeleted();
        this.__radioState.aboutToBeDeleted();
        this.__checkBoxState.aboutToBeDeleted();
        this.__rightWidth.aboutToBeDeleted();
        this.__secondaryTextColor.aboutToBeDeleted();
        this.__hoveringColor.aboutToBeDeleted();
        this.__activedColor.aboutToBeDeleted();
        this.__parentCanFocus.aboutToBeDeleted();
        this.__parentCanTouch.aboutToBeDeleted();
        this.__parentIsHover.aboutToBeDeleted();
        this.__parentCanHover.aboutToBeDeleted();
        this.__parentIsActive.aboutToBeDeleted();
        this.__parentFrontColor.aboutToBeDeleted();
        this.__parentDirection.aboutToBeDeleted();
        this.__rowSpace.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__secondaryTextSize.aboutToBeDeleted();
        this.__secondaryTextColors.aboutToBeDeleted();
        this.__iconColor.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(f8) {
        this.__arrow.set(f8);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(e8) {
        this.__icon.set(e8);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(d8) {
        this.__subIcon.set(d8);
    }
    get button() {
        return this.__button.get();
    }
    set button(c8) {
        this.__button.set(c8);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(b8) {
        this.__switch.set(b8);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(a8) {
        this.__checkBox.set(a8);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(z7) {
        this.__radio.set(z7);
    }
    get image() {
        return this.__image.get();
    }
    set image(y7) {
        this.__image.set(y7);
    }
    get symbolStyle() {
        return this.__symbolStyle.get();
    }
    set symbolStyle(x7) {
        this.__symbolStyle.set(x7);
    }
    get text() {
        return this.__text.get();
    }
    set text(w7) {
        this.__text.set(w7);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(v7) {
        this.__switchState.set(v7);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(u7) {
        this.__radioState.set(u7);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(t7) {
        this.__checkBoxState.set(t7);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(s7) {
        this.__rightWidth.set(s7);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(r7) {
        this.__secondaryTextColor.set(r7);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(q7) {
        this.__hoveringColor.set(q7);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(p7) {
        this.__activedColor.set(p7);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(o7) {
        this.__parentCanFocus.set(o7);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(n7) {
        this.__parentCanTouch.set(n7);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(m7) {
        this.__parentIsHover.set(m7);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(l7) {
        this.__parentCanHover.set(l7);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(k7) {
        this.__parentIsActive.set(k7);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(j7) {
        this.__parentFrontColor.set(j7);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(i7) {
        this.__parentDirection.set(i7);
    }
    get rowSpace() {
        return this.__rowSpace.get();
    }
    set rowSpace(h7) {
        this.__rowSpace.set(h7);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(g7) {
        this.__isFocus.set(g7);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(f7) {
        this.__secondaryTextSize.set(f7);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(e7) {
        this.__secondaryTextColors.set(e7);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(d7) {
        this.__iconColor.set(d7);
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(c7) {
        this.__isChecked.set(c7);
    }
    onWillApplyTheme(b7) {
        this.secondaryTextColor = b7.colors.fontSecondary;
        this.hoveringColor = b7.colors.interactiveHover;
        this.activedColor = b7.colors.interactiveActive;
    }
    onFocusChange() {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
            this.secondaryTextColors = { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_right_text_focus_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            this.secondaryTextColors = this.secondaryTextColor;
        }
        this.iconColor = this.isFocus ? { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_right_icon_focus_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_right_icon_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    onPropChange() {
        if (this.switch != null) {
            this.switchState = IS_SUPPORT_SUBCOMPONENT_EVENT ? this.switch.isCheck : this.isChecked;
        }
        if (this.radio != null) {
            this.radioState = IS_SUPPORT_SUBCOMPONENT_EVENT ? this.radio.isCheck : this.isChecked;
        }
        if (this.checkBox != null) {
            this.checkBoxState = IS_SUPPORT_SUBCOMPONENT_EVENT ? this.checkBox.isCheck : this.isChecked;
        }
        if ((this.button == null && this.image == null && this.symbolStyle == null && this.text != null) &&
            ((this.icon != null) || (this.icon == null && this.arrow != null))) {
            this.rowSpace = SPECICAL_ROW_SPACE;
        }
        else {
            this.rowSpace = DEFAULT_ROW_SPACE;
        }
    }
    getUnselectedColor() {
        if (IS_SUPPORT_SUBCOMPONENT_EVENT) {
            return DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
        }
        return this.isFocus ? OPERATE_ITEM_COLOR : DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
    }
    aboutToAppear() {
        if (this.switch !== null) {
            this.isChecked = this.switch.isCheck;
        }
        if (this.radio !== null) {
            this.isChecked = this.radio.isCheck;
        }
        if (this.checkBox !== null) {
            this.isChecked = this.checkBox.isCheck;
        }
        this.onPropChange();
        this.onFocusChange();
    }
    createButton(t6 = null) {
        this.observeComponentCreation2((y6, z6) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Button.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_button3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary_activated_transparent'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.constraintSize({
                minHeight: BUTTON_SIZE
            });
            Button.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_button_normal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((a7) => {
                this.parentCanHover = false;
                if (a7 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!a7) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.accessibilityLevel(this.button?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(this.button?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.button?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((w6, x6) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((u6, v6) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(e6, f6 = null) {
        this.observeComponentCreation2((q6, r6) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((s6) => {
                this.parentCanHover = false;
                if (s6 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!s6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(e6.icon?.action);
            Button.accessibilityLevel(e6.icon?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(e6.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(e6.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((g6, h6) => {
            If.create();
            if (e6.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o6, p6) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(e6.icon?.symbolStyle);
                        SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((i6, j6) => {
                        If.create();
                        if (Util.isSymbolResource(e6.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((m6, n6) => {
                                    SymbolGlyph.create(e6.icon?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k6, l6) => {
                                    Image.create(e6.icon?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.focusable(true);
                                    Image.fillColor(ObservedObject.GetRawObject(this.iconColor));
                                    Image.draggable(false);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    createImage(x5 = null) {
        this.observeComponentCreation2((y5, z5) => {
            If.create();
            if (Util.isSymbolResource(ObservedObject.GetRawObject(this.image))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c6, d6) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((a6, b6) => {
                        Image.create(this.image);
                        Image.height(OPERATEITEM_IMAGE_SIZE);
                        Image.width(OPERATEITEM_IMAGE_SIZE);
                        Image.draggable(false);
                        Image.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, Image);
                });
            }
        }, If);
        If.pop();
    }
    createSymbol(u5 = null) {
        this.observeComponentCreation2((v5, w5) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
            SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }
    createText(r5 = null) {
        this.observeComponentCreation2((s5, t5) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize(ObservedObject.GetRawObject(this.secondaryTextSize));
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
                TextOverflow.None
            });
            Text.marqueeOptions({
                start: this.isFocus || this.parentIsHover,
                fadeout: true,
                marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
            });
            Text.maxLines(LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_maxLines_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value);
            Text.draggable(false);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
    }
    createArrow(d5 = null) {
        this.observeComponentCreation2((o5, p5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
                (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((q5) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (q5 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(this.arrow?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((e5, f5) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m5, n5) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                        SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g5, h5) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k5, l5) => {
                                    SymbolGlyph.create(this.arrow?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((i5, j5) => {
                                    Image.create(this.arrow?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ARROW_WIDTH);
                                    Image.focusable(true);
                                    Image.fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.iconColor);
                                    Image.draggable(false);
                                    Image.matchTextDirection(true);
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    createRadio(y4 = null) {
        this.observeComponentCreation2((z4, a5) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: this.getUnselectedColor()
            });
            Radio.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((c5) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.radioState = c5;
                    this.isChecked = c5;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(c5);
                }
            });
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Radio.flexShrink(0);
            Radio.onHover((b5) => {
                this.parentCanHover = false;
                if (b5 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!b5) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Radio.accessibilityLevel(this.radio?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Radio.accessibilityText(getAccessibilityText(this.radio?.accessibilityText ?? ''));
            Radio.accessibilityDescription(getAccessibilityText(this.radio?.accessibilityDescription ?? ''));
        }, Radio);
    }
    createCheckBox(t4 = null) {
        this.observeComponentCreation2((u4, v4) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(this.getUnselectedColor());
            Checkbox.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((x4) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.checkBoxState = x4;
                    this.isChecked = x4;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(x4);
                }
            });
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Checkbox.flexShrink(0);
            Checkbox.onHover((w4) => {
                this.parentCanHover = false;
                if (w4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!w4) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Checkbox.accessibilityLevel(this.checkBox?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Checkbox.accessibilityText(getAccessibilityText(this.checkBox?.accessibilityText ?? ''));
            Checkbox.accessibilityDescription(getAccessibilityText(this.checkBox?.accessibilityDescription ?? ''));
        }, Checkbox);
        Checkbox.pop();
    }
    createSwitch(m4 = null) {
        this.observeComponentCreation2((q4, r4) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((s4) => {
                this.parentCanHover = false;
                if (s4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!s4) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((n4, o4) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Toggle.switchPointColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus && !this.switchState ? OPERATE_ITEM_COLOR :
                UNUSUAL);
            Toggle.onChange((p4) => {
                this.switchState = p4;
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isChecked = p4;
                }
                if (this.switch?.onChange) {
                    this.switch?.onChange(p4);
                }
            });
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Toggle.accessibilityLevel(this.switch?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Toggle.accessibilityText(getAccessibilityText(this.switch?.accessibilityText ?? ''));
            Toggle.accessibilityDescription(getAccessibilityText(this.switch?.accessibilityDescription ?? ''));
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(e3 = null) {
        this.observeComponentCreation2((j4, k4) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
                (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None);
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.backgroundColor(Color.Transparent);
            Button.constraintSize({ minHeight: TEXT_ARROW_HEIGHT });
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.padding({
                top: 0,
                bottom: 0,
                left: 0,
                right: 0
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((l4) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (l4 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(this.arrow?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(`${this.text} ${getAccessibilityText(this.arrow?.accessibilityText ?? '')}`);
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((f3, g3) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h4, i4) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((f4, g4) => {
                        Text.create(this.text);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((v3, w3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d4, e4) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((x3, y3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((b4, c4) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((z3, a4) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                                Image.width(OPERATEITEM_ARROW_WIDTH);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                Image.focusable(false);
                                                Image.draggable(false);
                                                Image.matchTextDirection(true);
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((t3, u3) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((r3, s3) => {
                        Text.create(this.text);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
                            TextOverflow.None
                        });
                        Text.marqueeOptions({
                            start: this.isFocus || this.parentIsHover,
                            fadeout: true,
                            marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
                        });
                        Text.maxLines(LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_maxLines_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value);
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH + OPERATEITEM_ARROW_MARGIN_WIDTH}vp)`
                        });
                        Text.margin({ right: OPERATEITEM_ARROW_MARGIN_WIDTH });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((h3, i3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((p3, q3) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? { 'id': -1, 'type': 10001, params: ['sys.color.icon_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.iconColor]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((j3, k3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((n3, o3) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                                SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? { 'id': -1, 'type': 10001, params: ['sys.color.icon_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.iconColor]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((l3, m3) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                                Image.width(OPERATEITEM_ARROW_WIDTH);
                                                Image.fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? { 'id': -1, 'type': 10001, params: ['sys.color.icon_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : this.iconColor);
                                                Image.focusable(false);
                                                Image.draggable(false);
                                                Image.matchTextDirection(true);
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    getFlexOptions() {
        let d3 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            d3.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            d3.space = { main: LengthMetrics.vp(this.rowSpace) };
            d3.justifyContent = FlexAlign.End;
        }
        return d3;
    }
    initialRender() {
        this.observeComponentCreation2((b3, c3) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((x2, y2) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)();
                });
            }
            else if (this.symbolStyle != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createSymbol.bind(this)();
                });
            }
            else if (this.image != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createImage.bind(this)();
                });
            }
            else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createText.bind(this)();
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon', { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                });
            }
            else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createArrow.bind(this)();
                });
            }
            else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createTextArrow.bind(this)();
                });
            }
            else if (this.text != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createText.bind(this)();
                });
            }
            else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createRadio.bind(this)();
                });
            }
            else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createCheckBox.bind(this)();
                });
            }
            else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createSwitch.bind(this)();
                });
            }
            else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(10, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon', { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                    this.observeComponentCreation2((z2, a3) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon', { icon: () => (this['__subIcon'] ? this['__subIcon'] : this['subIcon']) }));
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(11, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
function getAccessibilityText(s2) {
    try {
        let w2 = '';
        if (typeof s2 === 'string') {
            w2 = s2;
        }
        else {
            w2 = getContext().resourceManager.getStringSync(s2);
        }
        return w2;
    }
    catch (t2) {
        let u2 = t2.code;
        let v2 = t2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${u2}, message: ${v2}`);
        return '';
    }
}
export class ComposeListItem extends ViewPU {
    constructor(h2, i2, j2, k2 = -1, l2 = undefined, m2) {
        super(h2, j2, k2, m2);
        if (typeof l2 === 'function') {
            this.paramsGenerator_ = l2;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(i2.contentItem, this, 'contentItem');
        this.__operateItem = new SynchedPropertyObjectOneWayPU(i2.operateItem, this, 'operateItem');
        this.__frontColor = new ObservedPropertyObjectPU(NORMAL_BG_COLOR, this, 'frontColor');
        this.__borderSize = new ObservedPropertySimplePU(0, this, 'borderSize');
        this.__canFocus = new ObservedPropertySimplePU(false, this, 'canFocus');
        this.__canTouch = new ObservedPropertySimplePU(true, this, 'canTouch');
        this.__canHover = new ObservedPropertySimplePU(true, this, 'canHover');
        this.__isHover = new ObservedPropertySimplePU(false, this, 'isHover');
        this.__itemHeight = new ObservedPropertySimplePU(ItemHeight.FIRST_HEIGHT, this, 'itemHeight');
        this.__isActive = new ObservedPropertySimplePU(false, this, 'isActive');
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.__touchDownColor = new ObservedPropertyObjectPU('#1a000000', this, 'touchDownColor');
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.__focusOutlineColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'focusOutlineColor');
        this.__fontSizeScale = new ObservedPropertySimplePU(1, this, 'fontSizeScale');
        this.__containerDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, 'containerDirection');
        this.__contentItemDirection = new ObservedPropertySimplePU(FlexDirection.Row, this, 'contentItemDirection');
        this.__containerPadding = new ObservedPropertyObjectPU(undefined, this, 'containerPadding');
        this.__textArrowLeftSafeOffset = new ObservedPropertySimplePU(0, this, 'textArrowLeftSafeOffset');
        this.isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
        this.maxFontScale = this.getUIContext().getMaxFontScale();
        this.callbackId = undefined;
        this.__accessibilityTextBuilder = new ObservedPropertySimplePU('', this, 'accessibilityTextBuilder');
        this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
        this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
        this.__isWrapText = new ObservedPropertySimplePU(false, this, 'isWrapText');
        this.envCallback = {
            onConfigurationUpdated: (o2) => {
                if (o2 === undefined || !this.isFollowingSystemFontScale) {
                    this.fontSizeScale = 1;
                    return;
                }
                try {
                    this.fontSizeScale = Math.min(this.maxFontScale, o2.fontSizeScale ?? 1);
                }
                catch (p2) {
                    let q2 = p2.code;
                    let r2 = p2.message;
                    hilog.error(0x3900, 'Ace', `ComposeListItem environmentCallback error: ${q2}, ${r2}`);
                }
            },
            onMemoryLevel: (n2) => {
            }
        };
        this.setInitiallyProvidedValue(i2);
        this.declareWatch('contentItem', this.onPropChange);
        this.declareWatch('operateItem', this.onPropChange);
        this.declareWatch('fontSizeScale', this.onFontSizeScaleChange);
        this.declareWatch('isWrapText', this.onWrapChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(g2) {
        if (g2.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (g2.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (g2.frontColor !== undefined) {
            this.frontColor = g2.frontColor;
        }
        if (g2.borderSize !== undefined) {
            this.borderSize = g2.borderSize;
        }
        if (g2.canFocus !== undefined) {
            this.canFocus = g2.canFocus;
        }
        if (g2.canTouch !== undefined) {
            this.canTouch = g2.canTouch;
        }
        if (g2.canHover !== undefined) {
            this.canHover = g2.canHover;
        }
        if (g2.isHover !== undefined) {
            this.isHover = g2.isHover;
        }
        if (g2.itemHeight !== undefined) {
            this.itemHeight = g2.itemHeight;
        }
        if (g2.isActive !== undefined) {
            this.isActive = g2.isActive;
        }
        if (g2.hoveringColor !== undefined) {
            this.hoveringColor = g2.hoveringColor;
        }
        if (g2.touchDownColor !== undefined) {
            this.touchDownColor = g2.touchDownColor;
        }
        if (g2.activedColor !== undefined) {
            this.activedColor = g2.activedColor;
        }
        if (g2.focusOutlineColor !== undefined) {
            this.focusOutlineColor = g2.focusOutlineColor;
        }
        if (g2.fontSizeScale !== undefined) {
            this.fontSizeScale = g2.fontSizeScale;
        }
        if (g2.containerDirection !== undefined) {
            this.containerDirection = g2.containerDirection;
        }
        if (g2.contentItemDirection !== undefined) {
            this.contentItemDirection = g2.contentItemDirection;
        }
        if (g2.containerPadding !== undefined) {
            this.containerPadding = g2.containerPadding;
        }
        if (g2.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = g2.textArrowLeftSafeOffset;
        }
        if (g2.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = g2.isFollowingSystemFontScale;
        }
        if (g2.maxFontScale !== undefined) {
            this.maxFontScale = g2.maxFontScale;
        }
        if (g2.callbackId !== undefined) {
            this.callbackId = g2.callbackId;
        }
        if (g2.accessibilityTextBuilder !== undefined) {
            this.accessibilityTextBuilder = g2.accessibilityTextBuilder;
        }
        if (g2.isFocus !== undefined) {
            this.isFocus = g2.isFocus;
        }
        if (g2.isChecked !== undefined) {
            this.isChecked = g2.isChecked;
        }
        if (g2.isWrapText !== undefined) {
            this.isWrapText = g2.isWrapText;
        }
        if (g2.envCallback !== undefined) {
            this.envCallback = g2.envCallback;
        }
    }
    updateStateVars(f2) {
        this.__contentItem.reset(f2.contentItem);
        this.__operateItem.reset(f2.operateItem);
    }
    purgeVariableDependenciesOnElmtId(e2) {
        this.__contentItem.purgeDependencyOnElmtId(e2);
        this.__operateItem.purgeDependencyOnElmtId(e2);
        this.__frontColor.purgeDependencyOnElmtId(e2);
        this.__borderSize.purgeDependencyOnElmtId(e2);
        this.__canFocus.purgeDependencyOnElmtId(e2);
        this.__canTouch.purgeDependencyOnElmtId(e2);
        this.__canHover.purgeDependencyOnElmtId(e2);
        this.__isHover.purgeDependencyOnElmtId(e2);
        this.__itemHeight.purgeDependencyOnElmtId(e2);
        this.__isActive.purgeDependencyOnElmtId(e2);
        this.__hoveringColor.purgeDependencyOnElmtId(e2);
        this.__touchDownColor.purgeDependencyOnElmtId(e2);
        this.__activedColor.purgeDependencyOnElmtId(e2);
        this.__focusOutlineColor.purgeDependencyOnElmtId(e2);
        this.__fontSizeScale.purgeDependencyOnElmtId(e2);
        this.__containerDirection.purgeDependencyOnElmtId(e2);
        this.__contentItemDirection.purgeDependencyOnElmtId(e2);
        this.__containerPadding.purgeDependencyOnElmtId(e2);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(e2);
        this.__accessibilityTextBuilder.purgeDependencyOnElmtId(e2);
        this.__isFocus.purgeDependencyOnElmtId(e2);
        this.__isChecked.purgeDependencyOnElmtId(e2);
        this.__isWrapText.purgeDependencyOnElmtId(e2);
    }
    aboutToBeDeleted() {
        this.__contentItem.aboutToBeDeleted();
        this.__operateItem.aboutToBeDeleted();
        this.__frontColor.aboutToBeDeleted();
        this.__borderSize.aboutToBeDeleted();
        this.__canFocus.aboutToBeDeleted();
        this.__canTouch.aboutToBeDeleted();
        this.__canHover.aboutToBeDeleted();
        this.__isHover.aboutToBeDeleted();
        this.__itemHeight.aboutToBeDeleted();
        this.__isActive.aboutToBeDeleted();
        this.__hoveringColor.aboutToBeDeleted();
        this.__touchDownColor.aboutToBeDeleted();
        this.__activedColor.aboutToBeDeleted();
        this.__focusOutlineColor.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__containerDirection.aboutToBeDeleted();
        this.__contentItemDirection.aboutToBeDeleted();
        this.__containerPadding.aboutToBeDeleted();
        this.__textArrowLeftSafeOffset.aboutToBeDeleted();
        this.__accessibilityTextBuilder.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__isChecked.aboutToBeDeleted();
        this.__isWrapText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(d2) {
        this.__contentItem.set(d2);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(c2) {
        this.__operateItem.set(c2);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(b2) {
        this.__frontColor.set(b2);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(a2) {
        this.__borderSize.set(a2);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(z1) {
        this.__canFocus.set(z1);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(y1) {
        this.__canTouch.set(y1);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(x1) {
        this.__canHover.set(x1);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(w1) {
        this.__isHover.set(w1);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(v1) {
        this.__itemHeight.set(v1);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(u1) {
        this.__isActive.set(u1);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(t1) {
        this.__hoveringColor.set(t1);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(s1) {
        this.__touchDownColor.set(s1);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(r1) {
        this.__activedColor.set(r1);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(q1) {
        this.__focusOutlineColor.set(q1);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(p1) {
        this.__fontSizeScale.set(p1);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(o1) {
        this.__containerDirection.set(o1);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(n1) {
        this.__contentItemDirection.set(n1);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(m1) {
        this.__containerPadding.set(m1);
    }
    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }
    set textArrowLeftSafeOffset(l1) {
        this.__textArrowLeftSafeOffset.set(l1);
    }
    get accessibilityTextBuilder() {
        return this.__accessibilityTextBuilder.get();
    }
    set accessibilityTextBuilder(k1) {
        this.__accessibilityTextBuilder.set(k1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(j1) {
        this.__isFocus.set(j1);
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(i1) {
        this.__isChecked.set(i1);
    }
    get isWrapText() {
        return this.__isWrapText.get();
    }
    set isWrapText(h1) {
        this.__isWrapText.set(h1);
    }
    onWillApplyTheme(g1) {
        this.hoveringColor = g1.colors.interactiveHover;
        this.touchDownColor = g1.colors.interactivePressed;
        this.activedColor = g1.colors.interactiveActive;
        this.focusOutlineColor = g1.colors.interactiveFocus;
    }
    onWrapChange() {
        this.containerPadding = this.getPadding();
    }
    onPropChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.contentItem === undefined) {
            if (this.operateItem?.image !== undefined ||
                this.operateItem?.symbolStyle !== undefined ||
                this.operateItem?.icon !== undefined ||
                this.operateItem?.subIcon !== undefined) {
                this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
            }
            return;
        }
        if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
            if (this.contentItem?.icon === undefined) {
                this.itemHeight = ItemHeight.FIRST_HEIGHT;
            }
            else {
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ?
                ItemHeight.SECOND_HEIGHT :
                    (LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_system_icon_line_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }).value);
            }
        }
        else if (this.contentItem.description === undefined) {
            let iconStyle = this.contentItem.iconStyle;
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && iconStyle <= IconType.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            }
            else {
                this.itemHeight = iconStyle === IconType.HEAD_SCULPTURE ? ItemHeight.FOURTH_HEIGHT : APPICON_ITEMLENGTH;
            }
        }
        else {
            this.itemHeight = ItemHeight.FIFTH_HEIGHT;
        }
        if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle) >= this.itemHeight) {
            this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle) + SAFE_LIST_PADDING;
        }
        if (this.operateItem?.arrow && this.operateItem?.text && this.operateItem?.arrow?.action) {
            this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItem?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.description ?? '')}
      `;
        }
        else {
            this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItem?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItem?.description ?? '')}
        ${getAccessibilityText(this.operateItem?.text ?? '')}
      `;
        }
    }
    aboutToAppear() {
        this.fontSizeScale = this.decideFontSizeScale();
        this.onPropChange();
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        }
        catch (d1) {
            let e1 = d1.code;
            let f1 = d1.message;
            hilog.error(0x3900, 'Ace', `ComposeListItem Faild to get environment param error: ${e1}, ${f1}`);
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
            this.onFontSizeScaleChange();
        }
    }
    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }
    calculatedRightWidth() {
        if (this.operateItem?.text || this.operateItem?.button) {
            return RIGHT_PART_WIDTH;
        }
        if (this.operateItem?.switch) {
            return RIGHT_ONLY_SWITCH_WIDTH;
        }
        else if (this.operateItem?.checkbox) {
            return RIGHT_ONLY_CHECKBOX_WIDTH;
        }
        else if (this.operateItem?.radio) {
            return RIGHT_ONLY_RADIO_WIDTH;
        }
        else if (this.operateItem?.icon) {
            if (this.operateItem?.subIcon) {
                return RIGHT_ICON_SUB_ICON_WIDTH;
            }
            return RIGHT_ONLY_ICON_WIDTH;
        }
        else if (this.operateItem?.symbolStyle) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        }
        else if (this.operateItem?.image) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        }
        else if (this.operateItem?.arrow) {
            return RIGHT_ONLY_ARROW_WIDTH;
        }
        return RIGHT_CONTENT_NULL_RIGHTWIDTH;
    }
    decideContentItemDirection() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 &&
            this.contentItem?.iconStyle && this.contentItem?.iconStyle > IconType.HEAD_SCULPTURE) {
            return FlexDirection.Column;
        }
        return FlexDirection.Row;
    }
    decideContainerDirection() {
        if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1 || !this.contentItem) {
            return FlexDirection.Row;
        }
        if (this.operateItem?.button) {
            return FlexDirection.Column;
        }
        else if (this.operateItem?.symbolStyle) {
            return FlexDirection.Row;
        }
        else if (this.operateItem?.image) {
            return FlexDirection.Row;
        }
        else if (this.operateItem?.icon && this.operateItem?.text) {
            return FlexDirection.Column;
        }
        else if (this.operateItem?.arrow) {
            if (!this.operateItem?.text) {
                return FlexDirection.Row;
            }
            this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
            return FlexDirection.Column;
        }
        else if (this.operateItem?.text) {
            return FlexDirection.Column;
        }
        else {
            return FlexDirection.Row;
        }
    }
    onFontSizeScaleChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.containerPadding = {
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.containerPadding = {
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            };
        }
        else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.containerPadding = {
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            };
        }
        else {
            this.containerPadding = this.getPadding();
        }
    }
    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }
    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let c1 = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && c1 && c1 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(c1 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
        }
        return LengthMetrics.vp(LISTITEM_PADDING - this.textArrowLeftSafeOffset);
    }
    getMainSpace() {
        if (this.containerDirection === FlexDirection.Column) {
            return LengthMetrics.resource(this.isSingleLine() ? { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        return LengthMetrics.vp(0);
    }
    getFlexOptions() {
        if (this.containerDirection === FlexDirection.Column) {
            return {
                space: { main: this.getMainSpace() },
                justifyContent: FlexAlign.Center,
                alignItems: ItemAlign.Start,
                direction: this.containerDirection,
            };
        }
        return {
            justifyContent: FlexAlign.SpaceBetween,
            alignItems: ItemAlign.Center,
            direction: this.containerDirection,
        };
    }
    decideFontSizeScale() {
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.maxFontScale, this.getUIContext().getHostContext()?.config.fontSizeScale ?? 1);
    }
    getPadding() {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
            let z = LengthMetrics.resource(ITEM_PADDING).value;
            let a1 = z > LISTITEM_PADDING;
            let b1 = a1 ? z - LISTITEM_PADDING : 0;
            return {
                top: this.isWrapText ? z : 0,
                bottom: this.isWrapText ? z : 0,
                left: b1,
                right: b1
            };
        }
        else {
            return undefined;
        }
    }
    initialRender() {
        this.observeComponentCreation2((x, y) => {
            Stack.create();
            Stack.width('100%');
            Stack.accessibilityGroup(true);
            Stack.accessibilityText(this.accessibilityTextBuilder);
            Stack.onFocus(() => {
                this.isFocus = true;
                this.frontColor = FOCUSED_BG_COLOR;
            });
            Stack.onBlur(() => {
                this.isFocus = false;
                this.frontColor = NORMAL_BG_COLOR;
            });
            Stack.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Stack.onClick(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : () => {
                this.isChecked = this.operateItem?.radio ? true : !this.isChecked;
                if (this.operateItem?.icon && this.operateItem.icon?.action) {
                    this.operateItem.icon.action();
                }
                if (this.operateItem?.subIcon && this.operateItem.subIcon?.action) {
                    this.operateItem.subIcon.action();
                }
                if (this.operateItem?.arrow && this.operateItem.arrow?.action) {
                    this.operateItem.arrow.action();
                }
            });
            Stack.scale({
                x: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : (this.isFocus ? FOCUSED_ITEM_SCALE : RECOVER_ITEM_SCALE),
                y: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : (this.isFocus ? FOCUSED_ITEM_SCALE : RECOVER_ITEM_SCALE)
            });
            Stack.shadow(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : (this.isFocus ? FOCUSED_SHADOW : NORMAL_SHADOW));
            Stack.margin({
                left: !IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : undefined,
                right: !IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : undefined
            });
            Stack.padding({
                left: IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : 0,
                right: IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : 0
            });
        }, Stack);
        this.observeComponentCreation2((u, v) => {
            Flex.create(this.getFlexOptions());
            Flex.height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.constraintSize({
                minHeight: this.itemHeight
            });
            Flex.focusable(IS_SUPPORT_SUBCOMPONENT_EVENT);
            Flex.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((w) => {
                if (this.isFocus && !IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isHover = false;
                    return;
                }
                this.isHover = w;
                if (this.canHover) {
                    this.frontColor = w ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.frontColor = w ? this.hoveringColor : NORMAL_BG_COLOR;
                }
            });
            ViewStackProcessor.visualState('pressed');
            Flex.backgroundColor(ObservedObject.GetRawObject(this.touchDownColor));
            ViewStackProcessor.visualState('normal');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_stroke_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_stroke_normal_thickness'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            ViewStackProcessor.visualState('focused');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState();
            Flex.padding(ObservedObject.GetRawObject(this.containerPadding));
        }, Flex);
        this.observeComponentCreation2((o, p) => {
            If.create();
            if (this.contentItem === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((q, r) => {
                            if (r) {
                                let s = new ContentItemStruct(this, {
                                    isWrapText: this.__isWrapText
                                }, undefined, q, () => { }, { page: 'library/src/main/ets/components/ComposeListItem.ets', line: 1367, col: 11 });
                                ViewPU.create(s);
                                let t = () => {
                                    return {
                                        isWrapText: this.isWrapText
                                    };
                                };
                                s.paramsGenerator_ = t;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q, {});
                            }
                        }, { name: 'ContentItemStruct' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((i, j) => {
            If.create();
            if (this.contentItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((k, l) => {
                            if (l) {
                                let m = new ContentItemStruct(this, {
                                    icon: this.contentItem?.icon,
                                    symbolStyle: this.contentItem?.symbolStyle,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight,
                                    isWrapText: this.__isWrapText
                                }, undefined, k, () => { }, { page: 'library/src/main/ets/components/ComposeListItem.ets', line: 1372, col: 11 });
                                ViewPU.create(m);
                                let n = () => {
                                    return {
                                        icon: this.contentItem?.icon,
                                        symbolStyle: this.contentItem?.symbolStyle,
                                        iconStyle: this.contentItem?.iconStyle,
                                        primaryText: this.contentItem?.primaryText,
                                        secondaryText: this.contentItem?.secondaryText,
                                        description: this.contentItem?.description,
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection,
                                        isFocus: this.isFocus,
                                        itemHeight: this.itemHeight,
                                        isWrapText: this.isWrapText
                                    };
                                };
                                m.paramsGenerator_ = n;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(k, {
                                    icon: this.contentItem?.icon,
                                    symbolStyle: this.contentItem?.symbolStyle,
                                    iconStyle: this.contentItem?.iconStyle,
                                    primaryText: this.contentItem?.primaryText,
                                    secondaryText: this.contentItem?.secondaryText,
                                    description: this.contentItem?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight
                                });
                            }
                        }, { name: 'ContentItemStruct' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((a, b) => {
            If.create();
            if (this.operateItem !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g, h) => {
                        __Common__.create();
                        __Common__.flexShrink(0);
                        __Common__.onFocus(() => {
                            this.canFocus = false;
                        });
                        __Common__.onBlur(() => {
                            this.canFocus = true;
                        });
                        __Common__.padding({ start: this.getOperateOffset() });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((c, d) => {
                            if (d) {
                                let e = new OperateItemStruct(this, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    symbolStyle: this.operateItem?.symbolStyle,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    parentCanFocus: this.__canFocus,
                                    parentCanTouch: this.__canTouch,
                                    parentIsHover: this.__isHover,
                                    parentFrontColor: this.__frontColor,
                                    parentIsActive: this.__isActive,
                                    parentCanHover: this.__canHover,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.__containerDirection,
                                    isFocus: this.__isFocus,
                                    isChecked: this.__isChecked,
                                }, undefined, c, () => { }, { page: 'library/src/main/ets/components/ComposeListItem.ets', line: 1388, col: 11 });
                                ViewPU.create(e);
                                let f = () => {
                                    return {
                                        icon: this.operateItem?.icon,
                                        subIcon: this.operateItem?.subIcon,
                                        button: this.operateItem?.button,
                                        switch: this.operateItem?.switch,
                                        checkBox: this.operateItem?.checkbox,
                                        radio: this.operateItem?.radio,
                                        image: this.operateItem?.image,
                                        symbolStyle: this.operateItem?.symbolStyle,
                                        text: this.operateItem?.text,
                                        arrow: this.operateItem?.arrow,
                                        parentCanFocus: this.canFocus,
                                        parentCanTouch: this.canTouch,
                                        parentIsHover: this.isHover,
                                        parentFrontColor: this.frontColor,
                                        parentIsActive: this.isActive,
                                        parentCanHover: this.canHover,
                                        rightWidth: this.calculatedRightWidth(),
                                        parentDirection: this.containerDirection,
                                        isFocus: this.isFocus,
                                        isChecked: this.isChecked
                                    };
                                };
                                e.paramsGenerator_ = f;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c, {
                                    icon: this.operateItem?.icon,
                                    subIcon: this.operateItem?.subIcon,
                                    button: this.operateItem?.button,
                                    switch: this.operateItem?.switch,
                                    checkBox: this.operateItem?.checkbox,
                                    radio: this.operateItem?.radio,
                                    image: this.operateItem?.image,
                                    symbolStyle: this.operateItem?.symbolStyle,
                                    text: this.operateItem?.text,
                                    arrow: this.operateItem?.arrow,
                                    rightWidth: this.calculatedRightWidth()
                                });
                            }
                        }, { name: 'OperateItemStruct' });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Stack.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    IconType, ComposeListItem
};