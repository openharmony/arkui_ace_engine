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
(function (c12) {
    c12[c12['BADGE'] = 1] = 'BADGE';
    c12[c12['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    c12[c12['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    c12[c12['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    c12[c12['APP_ICON'] = 5] = 'APP_ICON';
    c12[c12['PREVIEW'] = 6] = 'PREVIEW';
    c12[c12['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    c12[c12['VERTICAL'] = 8] = 'VERTICAL';
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (b12) {
    b12[b12['LEVEL1'] = 1.75] = 'LEVEL1';
    b12[b12['LEVEL2'] = 2] = 'LEVEL2';
    b12[b12['LEVEL3'] = 3.2] = 'LEVEL3';
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (a12) {
    a12[a12['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    a12[a12['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    a12[a12['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    a12[a12['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    a12[a12['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
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
const ACCESSIBILITY_LEVEL_YES = 'yes';
const ACCESSIBILITY_LEVEL_NO = 'no';
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
    static isSymbolResource(y11) {
        if (!Util.isResourceType(y11)) {
            return false;
        }
        let z11 = y11;
        return z11.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(x11) {
        if (!x11) {
            return false;
        }
        if (typeof x11 === 'string' || typeof x11 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ContentItemStruct extends ViewPU {
    constructor(r11, s11, t11, u11 = -1, v11 = undefined, w11) {
        super(r11, t11, u11, w11);
        if (typeof v11 === 'function') {
            this.paramsGenerator_ = v11;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(s11.iconStyle, this, 'iconStyle');
        this.__icon = new SynchedPropertyObjectOneWayPU(s11.icon, this, 'icon');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(s11.symbolStyle, this, 'symbolStyle');
        this.__primaryText = new SynchedPropertyObjectOneWayPU(s11.primaryText, this, 'primaryText');
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(s11.secondaryText, this, 'secondaryText');
        this.__description = new SynchedPropertyObjectOneWayPU(s11.description, this, 'description');
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, 'itemRowSpace');
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(s11.leftWidth, this, 'leftWidth');
        this.__primaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextColor');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.__descriptionColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'descriptionColor');
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(s11.fontSizeScale, this, 'fontSizeScale');
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(s11.parentDirection, this, 'parentDirection');
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(s11.itemDirection, this, 'itemDirection');
        this.__isFocus = new SynchedPropertySimpleOneWayPU(s11.isFocus, this, 'isFocus');
        this.__primaryTextSize = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextSize');
        this.__primaryTextColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextColors');
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(s11.itemHeight, this, 'itemHeight');
        this.__iconColor = new ObservedPropertyObjectPU(null, this, 'iconColor');
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColors');
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_left_secondary_tertiary_text_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryThirdTextSize');
        this.__descriptionColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_tertiary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'descriptionColors');
        this.__isWrapText = new SynchedPropertyObjectTwoWayPU(s11.isWrapText, this, 'isWrapText');
        this.__isWrapFirstText = new ObservedPropertyObjectPU(false, this, 'isWrapFirstText');
        this.__isWrapSecondText = new ObservedPropertyObjectPU(false, this, 'isWrapSecondText');
        this.__isWrapThirdText = new ObservedPropertyObjectPU(false, this, 'isWrapThirdText');
        this.setInitiallyProvidedValue(s11);
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
    setInitiallyProvidedValue(q11) {
        if (q11.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (q11.icon === undefined) {
            this.__icon.set(null);
        }
        if (q11.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (q11.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (q11.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (q11.description === undefined) {
            this.__description.set(null);
        }
        if (q11.itemRowSpace !== undefined) {
            this.itemRowSpace = q11.itemRowSpace;
        }
        if (q11.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (q11.primaryTextColor !== undefined) {
            this.primaryTextColor = q11.primaryTextColor;
        }
        if (q11.secondaryTextColor !== undefined) {
            this.secondaryTextColor = q11.secondaryTextColor;
        }
        if (q11.descriptionColor !== undefined) {
            this.descriptionColor = q11.descriptionColor;
        }
        if (q11.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (q11.primaryTextSize !== undefined) {
            this.primaryTextSize = q11.primaryTextSize;
        }
        if (q11.primaryTextColors !== undefined) {
            this.primaryTextColors = q11.primaryTextColors;
        }
        if (q11.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (q11.iconColor !== undefined) {
            this.iconColor = q11.iconColor;
        }
        if (q11.secondaryTextColors !== undefined) {
            this.secondaryTextColors = q11.secondaryTextColors;
        }
        if (q11.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = q11.secondaryThirdTextSize;
        }
        if (q11.descriptionColors !== undefined) {
            this.descriptionColors = q11.descriptionColors;
        }
        if (q11.isWrapFirstText !== undefined) {
            this.isWrapFirstText = q11.isWrapFirstText;
        }
        if (q11.isWrapSecondText !== undefined) {
            this.isWrapSecondText = q11.isWrapSecondText;
        }
        if (q11.isWrapThirdText !== undefined) {
            this.isWrapThirdText = q11.isWrapThirdText;
        }
    }
    updateStateVars(p11) {
        this.__iconStyle.reset(p11.iconStyle);
        this.__icon.reset(p11.icon);
        this.__symbolStyle.reset(p11.symbolStyle);
        this.__primaryText.reset(p11.primaryText);
        this.__secondaryText.reset(p11.secondaryText);
        this.__description.reset(p11.description);
        this.__leftWidth.reset(p11.leftWidth);
        this.__fontSizeScale.reset(p11.fontSizeScale);
        this.__parentDirection.reset(p11.parentDirection);
        this.__itemDirection.reset(p11.itemDirection);
        this.__isFocus.reset(p11.isFocus);
        this.__itemHeight.reset(p11.itemHeight);
    }
    purgeVariableDependenciesOnElmtId(o11) {
        this.__iconStyle.purgeDependencyOnElmtId(o11);
        this.__icon.purgeDependencyOnElmtId(o11);
        this.__symbolStyle.purgeDependencyOnElmtId(o11);
        this.__primaryText.purgeDependencyOnElmtId(o11);
        this.__secondaryText.purgeDependencyOnElmtId(o11);
        this.__description.purgeDependencyOnElmtId(o11);
        this.__itemRowSpace.purgeDependencyOnElmtId(o11);
        this.__leftWidth.purgeDependencyOnElmtId(o11);
        this.__primaryTextColor.purgeDependencyOnElmtId(o11);
        this.__secondaryTextColor.purgeDependencyOnElmtId(o11);
        this.__descriptionColor.purgeDependencyOnElmtId(o11);
        this.__fontSizeScale.purgeDependencyOnElmtId(o11);
        this.__parentDirection.purgeDependencyOnElmtId(o11);
        this.__itemDirection.purgeDependencyOnElmtId(o11);
        this.__isFocus.purgeDependencyOnElmtId(o11);
        this.__primaryTextSize.purgeDependencyOnElmtId(o11);
        this.__primaryTextColors.purgeDependencyOnElmtId(o11);
        this.__itemHeight.purgeDependencyOnElmtId(o11);
        this.__iconColor.purgeDependencyOnElmtId(o11);
        this.__secondaryTextColors.purgeDependencyOnElmtId(o11);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(o11);
        this.__descriptionColors.purgeDependencyOnElmtId(o11);
        this.__isWrapText.purgeDependencyOnElmtId(o11);
        this.__isWrapFirstText.purgeDependencyOnElmtId(o11);
        this.__isWrapSecondText.purgeDependencyOnElmtId(o11);
        this.__isWrapThirdText.purgeDependencyOnElmtId(o11);
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
    set iconStyle(n11) {
        this.__iconStyle.set(n11);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(m11) {
        this.__icon.set(m11);
    }
    get symbolStyle() {
        return this.__symbolStyle.get();
    }
    set symbolStyle(l11) {
        this.__symbolStyle.set(l11);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(k11) {
        this.__primaryText.set(k11);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(j11) {
        this.__secondaryText.set(j11);
    }
    get description() {
        return this.__description.get();
    }
    set description(i11) {
        this.__description.set(i11);
    }
    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }
    set itemRowSpace(h11) {
        this.__itemRowSpace.set(h11);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(g11) {
        this.__leftWidth.set(g11);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(f11) {
        this.__primaryTextColor.set(f11);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(e11) {
        this.__secondaryTextColor.set(e11);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(d11) {
        this.__descriptionColor.set(d11);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(c11) {
        this.__fontSizeScale.set(c11);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(b11) {
        this.__parentDirection.set(b11);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(a11) {
        this.__itemDirection.set(a11);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(z10) {
        this.__isFocus.set(z10);
    }
    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }
    set primaryTextSize(y10) {
        this.__primaryTextSize.set(y10);
    }
    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }
    set primaryTextColors(x10) {
        this.__primaryTextColors.set(x10);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(w10) {
        this.__itemHeight.set(w10);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(v10) {
        this.__iconColor.set(v10);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(u10) {
        this.__secondaryTextColors.set(u10);
    }
    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }
    set secondaryThirdTextSize(t10) {
        this.__secondaryThirdTextSize.set(t10);
    }
    get descriptionColors() {
        return this.__descriptionColors.get();
    }
    set descriptionColors(s10) {
        this.__descriptionColors.set(s10);
    }
    get isWrapText() {
        return this.__isWrapText.get();
    }
    set isWrapText(r10) {
        this.__isWrapText.set(r10);
    }
    get isWrapFirstText() {
        return this.__isWrapFirstText.get();
    }
    set isWrapFirstText(q10) {
        this.__isWrapFirstText.set(q10);
    }
    get isWrapSecondText() {
        return this.__isWrapSecondText.get();
    }
    set isWrapSecondText(p10) {
        this.__isWrapSecondText.set(p10);
    }
    get isWrapThirdText() {
        return this.__isWrapThirdText.get();
    }
    set isWrapThirdText(o10) {
        this.__isWrapThirdText.set(o10);
    }
    onWillApplyTheme(n10) {
        this.primaryTextColor = n10.colors.fontPrimary;
        this.secondaryTextColor = n10.colors.fontSecondary;
        this.descriptionColor = n10.colors.fontTertiary;
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
    judgeIsWrap(j10, k10, l10) {
        let m10 = this.getSingleRowTextHeight(j10, k10);
        return l10 > m10;
    }
    getSingleRowTextHeight(g10, h10) {
        if (g10 && h10) {
            let i10 = px2vp(measure.measureTextSize({
                textContent: g10,
                fontSize: h10,
                maxLines: TEXT_MAX_LINE
            }).height);
            return i10;
        }
        return 0;
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createIcon(p9 = null) {
        this.observeComponentCreation2((q9, r9) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s9, t9) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((e10, f10) => {
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
                                this.observeComponentCreation2((u9, v9) => {
                                    If.create();
                                    if (Util.isSymbolResource(ObservedObject.GetRawObject(this.icon))) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((c10, d10) => {
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
                                            this.observeComponentCreation2((w9, x9) => {
                                                If.create();
                                                if (this.iconStyle <= IconType.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((a10, b10) => {
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
                                                        this.observeComponentCreation2((y9, z9) => {
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
    createText(w8 = null) {
        this.observeComponentCreation2((n9, o9) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((j9, k9) => {
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
            Text.onSizeChange((l9, m9) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isWrapFirstText = this.judgeIsWrap(ObservedObject.GetRawObject(this.primaryText), ObservedObject.GetRawObject(this.primaryTextSize), m9.height);
                }
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((d9, e9) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f9, g9) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((h9, i9) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                                this.isWrapSecondText = this.judgeIsWrap(ObservedObject.GetRawObject(this.secondaryText), ObservedObject.GetRawObject(this.secondaryThirdTextSize), i9.height);
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
        this.observeComponentCreation2((x8, y8) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z8, a9) => {
                        Text.create(this.description);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((b9, c9) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                                this.isWrapThirdText = this.judgeIsWrap(ObservedObject.GetRawObject(this.description), ObservedObject.GetRawObject(this.secondaryThirdTextSize), c9.height);
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
        this.observeComponentCreation2((u8, v8) => {
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
    constructor(o8, p8, q8, r8 = -1, s8 = undefined, t8) {
        super(o8, q8, r8, t8);
        if (typeof s8 === 'function') {
            this.paramsGenerator_ = s8;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(p8.arrow, this, 'arrow');
        this.__icon = new SynchedPropertyObjectOneWayPU(p8.icon, this, 'icon');
        this.__subIcon = new SynchedPropertyObjectOneWayPU(p8.subIcon, this, 'subIcon');
        this.__button = new SynchedPropertyObjectOneWayPU(p8.button, this, 'button');
        this.__switch = new SynchedPropertyObjectOneWayPU(p8.switch, this, 'switch');
        this.__checkBox = new SynchedPropertyObjectOneWayPU(p8.checkBox, this, 'checkBox');
        this.__radio = new SynchedPropertyObjectOneWayPU(p8.radio, this, 'radio');
        this.__image = new SynchedPropertyObjectOneWayPU(p8.image, this, 'image');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(p8.symbolStyle, this, 'symbolStyle');
        this.__text = new SynchedPropertyObjectOneWayPU(p8.text, this, 'text');
        this.__switchState = new ObservedPropertySimplePU(false, this, 'switchState');
        this.__radioState = new ObservedPropertySimplePU(false, this, 'radioState');
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, 'checkBoxState');
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(p8.rightWidth, this, 'rightWidth');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(p8.parentCanFocus, this, 'parentCanFocus');
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(p8.parentCanTouch, this, 'parentCanTouch');
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(p8.parentIsHover, this, 'parentIsHover');
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(p8.parentCanHover, this, 'parentCanHover');
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(p8.parentIsActive, this, 'parentIsActive');
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(p8.parentFrontColor, this, 'parentFrontColor');
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(p8.parentDirection, this, 'parentDirection');
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, 'rowSpace');
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(p8.isFocus, this, 'isFocus');
        this.__secondaryTextSize = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextSize');
        this.__secondaryTextColors = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColors');
        this.__iconColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_right_icon_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'iconColor');
        this.__isChecked = new SynchedPropertySimpleTwoWayPU(p8.isChecked, this, 'isChecked');
        this.setInitiallyProvidedValue(p8);
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
    setInitiallyProvidedValue(n8) {
        if (n8.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (n8.icon === undefined) {
            this.__icon.set(null);
        }
        if (n8.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (n8.button === undefined) {
            this.__button.set(null);
        }
        if (n8.switch === undefined) {
            this.__switch.set(null);
        }
        if (n8.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (n8.radio === undefined) {
            this.__radio.set(null);
        }
        if (n8.image === undefined) {
            this.__image.set(null);
        }
        if (n8.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (n8.text === undefined) {
            this.__text.set(null);
        }
        if (n8.switchState !== undefined) {
            this.switchState = n8.switchState;
        }
        if (n8.radioState !== undefined) {
            this.radioState = n8.radioState;
        }
        if (n8.checkBoxState !== undefined) {
            this.checkBoxState = n8.checkBoxState;
        }
        if (n8.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (n8.secondaryTextColor !== undefined) {
            this.secondaryTextColor = n8.secondaryTextColor;
        }
        if (n8.hoveringColor !== undefined) {
            this.hoveringColor = n8.hoveringColor;
        }
        if (n8.activedColor !== undefined) {
            this.activedColor = n8.activedColor;
        }
        if (n8.rowSpace !== undefined) {
            this.rowSpace = n8.rowSpace;
        }
        if (n8.secondaryTextSize !== undefined) {
            this.secondaryTextSize = n8.secondaryTextSize;
        }
        if (n8.secondaryTextColors !== undefined) {
            this.secondaryTextColors = n8.secondaryTextColors;
        }
        if (n8.iconColor !== undefined) {
            this.iconColor = n8.iconColor;
        }
    }
    updateStateVars(m8) {
        this.__arrow.reset(m8.arrow);
        this.__icon.reset(m8.icon);
        this.__subIcon.reset(m8.subIcon);
        this.__button.reset(m8.button);
        this.__switch.reset(m8.switch);
        this.__checkBox.reset(m8.checkBox);
        this.__radio.reset(m8.radio);
        this.__image.reset(m8.image);
        this.__symbolStyle.reset(m8.symbolStyle);
        this.__text.reset(m8.text);
        this.__rightWidth.reset(m8.rightWidth);
    }
    purgeVariableDependenciesOnElmtId(l8) {
        this.__arrow.purgeDependencyOnElmtId(l8);
        this.__icon.purgeDependencyOnElmtId(l8);
        this.__subIcon.purgeDependencyOnElmtId(l8);
        this.__button.purgeDependencyOnElmtId(l8);
        this.__switch.purgeDependencyOnElmtId(l8);
        this.__checkBox.purgeDependencyOnElmtId(l8);
        this.__radio.purgeDependencyOnElmtId(l8);
        this.__image.purgeDependencyOnElmtId(l8);
        this.__symbolStyle.purgeDependencyOnElmtId(l8);
        this.__text.purgeDependencyOnElmtId(l8);
        this.__switchState.purgeDependencyOnElmtId(l8);
        this.__radioState.purgeDependencyOnElmtId(l8);
        this.__checkBoxState.purgeDependencyOnElmtId(l8);
        this.__rightWidth.purgeDependencyOnElmtId(l8);
        this.__secondaryTextColor.purgeDependencyOnElmtId(l8);
        this.__hoveringColor.purgeDependencyOnElmtId(l8);
        this.__activedColor.purgeDependencyOnElmtId(l8);
        this.__parentCanFocus.purgeDependencyOnElmtId(l8);
        this.__parentCanTouch.purgeDependencyOnElmtId(l8);
        this.__parentIsHover.purgeDependencyOnElmtId(l8);
        this.__parentCanHover.purgeDependencyOnElmtId(l8);
        this.__parentIsActive.purgeDependencyOnElmtId(l8);
        this.__parentFrontColor.purgeDependencyOnElmtId(l8);
        this.__parentDirection.purgeDependencyOnElmtId(l8);
        this.__rowSpace.purgeDependencyOnElmtId(l8);
        this.__isFocus.purgeDependencyOnElmtId(l8);
        this.__secondaryTextSize.purgeDependencyOnElmtId(l8);
        this.__secondaryTextColors.purgeDependencyOnElmtId(l8);
        this.__iconColor.purgeDependencyOnElmtId(l8);
        this.__isChecked.purgeDependencyOnElmtId(l8);
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
    set arrow(k8) {
        this.__arrow.set(k8);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(j8) {
        this.__icon.set(j8);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(i8) {
        this.__subIcon.set(i8);
    }
    get button() {
        return this.__button.get();
    }
    set button(h8) {
        this.__button.set(h8);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(g8) {
        this.__switch.set(g8);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(f8) {
        this.__checkBox.set(f8);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(e8) {
        this.__radio.set(e8);
    }
    get image() {
        return this.__image.get();
    }
    set image(d8) {
        this.__image.set(d8);
    }
    get symbolStyle() {
        return this.__symbolStyle.get();
    }
    set symbolStyle(c8) {
        this.__symbolStyle.set(c8);
    }
    get text() {
        return this.__text.get();
    }
    set text(b8) {
        this.__text.set(b8);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(a8) {
        this.__switchState.set(a8);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(z7) {
        this.__radioState.set(z7);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(y7) {
        this.__checkBoxState.set(y7);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(x7) {
        this.__rightWidth.set(x7);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(w7) {
        this.__secondaryTextColor.set(w7);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(v7) {
        this.__hoveringColor.set(v7);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(u7) {
        this.__activedColor.set(u7);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(t7) {
        this.__parentCanFocus.set(t7);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(s7) {
        this.__parentCanTouch.set(s7);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(r7) {
        this.__parentIsHover.set(r7);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(q7) {
        this.__parentCanHover.set(q7);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(p7) {
        this.__parentIsActive.set(p7);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(o7) {
        this.__parentFrontColor.set(o7);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(n7) {
        this.__parentDirection.set(n7);
    }
    get rowSpace() {
        return this.__rowSpace.get();
    }
    set rowSpace(m7) {
        this.__rowSpace.set(m7);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(l7) {
        this.__isFocus.set(l7);
    }
    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }
    set secondaryTextSize(k7) {
        this.__secondaryTextSize.set(k7);
    }
    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }
    set secondaryTextColors(j7) {
        this.__secondaryTextColors.set(j7);
    }
    get iconColor() {
        return this.__iconColor.get();
    }
    set iconColor(i7) {
        this.__iconColor.set(i7);
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(h7) {
        this.__isChecked.set(h7);
    }
    onWillApplyTheme(g7) {
        this.secondaryTextColor = g7.colors.fontSecondary;
        this.hoveringColor = g7.colors.interactiveHover;
        this.activedColor = g7.colors.interactiveActive;
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
    createButton(y6 = null) {
        this.observeComponentCreation2((d7, e7) => {
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
            Button.onHover((f7) => {
                this.parentCanHover = false;
                if (f7 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!f7) {
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
        this.observeComponentCreation2((b7, c7) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((z6, a7) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(j6, k6 = null) {
        this.observeComponentCreation2((v6, w6) => {
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
            Button.onHover((x6) => {
                this.parentCanHover = false;
                if (x6 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!x6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(j6.icon?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(j6.icon?.accessibilityLevel, j6.icon?.action));
            Button.accessibilityText(getAccessibilityText(j6.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(j6.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((l6, m6) => {
            If.create();
            if (j6.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t6, u6) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(j6.icon?.symbolStyle);
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
                    this.observeComponentCreation2((n6, o6) => {
                        If.create();
                        if (Util.isSymbolResource(j6.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((r6, s6) => {
                                    SymbolGlyph.create(j6.icon?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p6, q6) => {
                                    Image.create(j6.icon?.value);
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
    createImage(c6 = null) {
        this.observeComponentCreation2((d6, e6) => {
            If.create();
            if (Util.isSymbolResource(ObservedObject.GetRawObject(this.image))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h6, i6) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((f6, g6) => {
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
    createSymbol(z5 = null) {
        this.observeComponentCreation2((a6, b6) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
            SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }
    createText(w5 = null) {
        this.observeComponentCreation2((x5, y5) => {
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
    createArrow(i5 = null) {
        this.observeComponentCreation2((t5, u5) => {
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
            Button.onHover((v5) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (v5 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
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
            Button.accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel, this.arrow?.action));
            Button.accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((j5, k5) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r5, s5) => {
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
                    this.observeComponentCreation2((l5, m5) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((p5, q5) => {
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
                                this.observeComponentCreation2((n5, o5) => {
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
    createRadio(d5 = null) {
        this.observeComponentCreation2((e5, f5) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: this.getUnselectedColor()
            });
            Radio.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((h5) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.radioState = h5;
                    this.isChecked = h5;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(h5);
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
            Radio.onHover((g5) => {
                this.parentCanHover = false;
                if (g5 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!g5) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Radio.accessibilityLevel(getAccessibilityLevelOnChange(this.radio?.accessibilityLevel, this.radio?.onChange));
            Radio.accessibilityText(getAccessibilityText(this.radio?.accessibilityText ?? ''));
            Radio.accessibilityDescription(getAccessibilityText(this.radio?.accessibilityDescription ?? ''));
        }, Radio);
    }
    createCheckBox(y4 = null) {
        this.observeComponentCreation2((z4, a5) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(this.getUnselectedColor());
            Checkbox.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((c5) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.checkBoxState = c5;
                    this.isChecked = c5;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(c5);
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
            Checkbox.onHover((b5) => {
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
            Checkbox.accessibilityLevel(getAccessibilityLevelOnChange(this.checkBox?.accessibilityLevel, this.checkBox?.onChange));
            Checkbox.accessibilityText(getAccessibilityText(this.checkBox?.accessibilityText ?? ''));
            Checkbox.accessibilityDescription(getAccessibilityText(this.checkBox?.accessibilityDescription ?? ''));
        }, Checkbox);
        Checkbox.pop();
    }
    createSwitch(r4 = null) {
        this.observeComponentCreation2((v4, w4) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((x4) => {
                this.parentCanHover = false;
                if (x4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!x4) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((s4, t4) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Toggle.switchPointColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus && !this.switchState ? OPERATE_ITEM_COLOR :
                UNUSUAL);
            Toggle.onChange((u4) => {
                this.switchState = u4;
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isChecked = u4;
                }
                if (this.switch?.onChange) {
                    this.switch?.onChange(u4);
                }
            });
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Toggle.accessibilityLevel(getAccessibilityLevelOnChange(this.switch?.accessibilityLevel, this.switch?.onChange));
            Toggle.accessibilityText(getAccessibilityText(this.switch?.accessibilityText ?? ''));
            Toggle.accessibilityDescription(getAccessibilityText(this.switch?.accessibilityDescription ?? ''));
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(j3 = null) {
        this.observeComponentCreation2((o4, p4) => {
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
            Button.onHover((q4) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (q4 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
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
            Button.accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel, this.arrow?.action));
            Button.accessibilityText(`${this.text} ${getAccessibilityText(this.arrow?.accessibilityText ?? '')}`);
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((k3, l3) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m4, n4) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((k4, l4) => {
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
                    this.observeComponentCreation2((a4, b4) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((i4, j4) => {
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
                                this.observeComponentCreation2((c4, d4) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((g4, h4) => {
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
                                            this.observeComponentCreation2((e4, f4) => {
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
                    this.observeComponentCreation2((y3, z3) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((w3, x3) => {
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
                    this.observeComponentCreation2((m3, n3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u3, v3) => {
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
                                this.observeComponentCreation2((o3, p3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((s3, t3) => {
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
                                            this.observeComponentCreation2((q3, r3) => {
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
        let i3 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            i3.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            i3.space = { main: LengthMetrics.vp(this.rowSpace) };
            i3.justifyContent = FlexAlign.End;
        }
        return i3;
    }
    initialRender() {
        this.observeComponentCreation2((g3, h3) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((c3, d3) => {
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
                    this.observeComponentCreation2((e3, f3) => {
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
function getAccessibilityText(x2) {
    try {
        let b3 = '';
        if (typeof x2 === 'string') {
            b3 = x2;
        }
        else {
            b3 = getContext().resourceManager.getStringSync(x2);
        }
        return b3;
    }
    catch (y2) {
        let z2 = y2.code;
        let a3 = y2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${z2}, message: ${a3}`);
        return '';
    }
}
function getAccessibilityLevelOnChange(v2, w2) {
    if (v2) {
        return v2;
    }
    if (w2) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}
function getAccessibilityLevelOnAction(t2, u2) {
    if (t2) {
        return t2;
    }
    if (u2) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}
export class ComposeListItem extends ViewPU {
    constructor(i2, j2, k2, l2 = -1, m2 = undefined, n2) {
        super(i2, k2, l2, n2);
        if (typeof m2 === 'function') {
            this.paramsGenerator_ = m2;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(j2.contentItem, this, 'contentItem');
        this.__operateItem = new SynchedPropertyObjectOneWayPU(j2.operateItem, this, 'operateItem');
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
            onConfigurationUpdated: (p2) => {
                if (p2 === undefined || !this.isFollowingSystemFontScale) {
                    this.fontSizeScale = 1;
                    return;
                }
                try {
                    this.fontSizeScale = Math.min(this.maxFontScale, p2.fontSizeScale ?? 1);
                }
                catch (q2) {
                    let r2 = q2.code;
                    let s2 = q2.message;
                    hilog.error(0x3900, 'Ace', `ComposeListItem environmentCallback error: ${r2}, ${s2}`);
                }
            },
            onMemoryLevel: (o2) => {
            }
        };
        this.setInitiallyProvidedValue(j2);
        this.declareWatch('contentItem', this.onPropChange);
        this.declareWatch('operateItem', this.onPropChange);
        this.declareWatch('fontSizeScale', this.onFontSizeScaleChange);
        this.declareWatch('isWrapText', this.onWrapChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(h2) {
        if (h2.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (h2.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (h2.frontColor !== undefined) {
            this.frontColor = h2.frontColor;
        }
        if (h2.borderSize !== undefined) {
            this.borderSize = h2.borderSize;
        }
        if (h2.canFocus !== undefined) {
            this.canFocus = h2.canFocus;
        }
        if (h2.canTouch !== undefined) {
            this.canTouch = h2.canTouch;
        }
        if (h2.canHover !== undefined) {
            this.canHover = h2.canHover;
        }
        if (h2.isHover !== undefined) {
            this.isHover = h2.isHover;
        }
        if (h2.itemHeight !== undefined) {
            this.itemHeight = h2.itemHeight;
        }
        if (h2.isActive !== undefined) {
            this.isActive = h2.isActive;
        }
        if (h2.hoveringColor !== undefined) {
            this.hoveringColor = h2.hoveringColor;
        }
        if (h2.touchDownColor !== undefined) {
            this.touchDownColor = h2.touchDownColor;
        }
        if (h2.activedColor !== undefined) {
            this.activedColor = h2.activedColor;
        }
        if (h2.focusOutlineColor !== undefined) {
            this.focusOutlineColor = h2.focusOutlineColor;
        }
        if (h2.fontSizeScale !== undefined) {
            this.fontSizeScale = h2.fontSizeScale;
        }
        if (h2.containerDirection !== undefined) {
            this.containerDirection = h2.containerDirection;
        }
        if (h2.contentItemDirection !== undefined) {
            this.contentItemDirection = h2.contentItemDirection;
        }
        if (h2.containerPadding !== undefined) {
            this.containerPadding = h2.containerPadding;
        }
        if (h2.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = h2.textArrowLeftSafeOffset;
        }
        if (h2.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = h2.isFollowingSystemFontScale;
        }
        if (h2.maxFontScale !== undefined) {
            this.maxFontScale = h2.maxFontScale;
        }
        if (h2.callbackId !== undefined) {
            this.callbackId = h2.callbackId;
        }
        if (h2.accessibilityTextBuilder !== undefined) {
            this.accessibilityTextBuilder = h2.accessibilityTextBuilder;
        }
        if (h2.isFocus !== undefined) {
            this.isFocus = h2.isFocus;
        }
        if (h2.isChecked !== undefined) {
            this.isChecked = h2.isChecked;
        }
        if (h2.isWrapText !== undefined) {
            this.isWrapText = h2.isWrapText;
        }
        if (h2.envCallback !== undefined) {
            this.envCallback = h2.envCallback;
        }
    }
    updateStateVars(g2) {
        this.__contentItem.reset(g2.contentItem);
        this.__operateItem.reset(g2.operateItem);
    }
    purgeVariableDependenciesOnElmtId(f2) {
        this.__contentItem.purgeDependencyOnElmtId(f2);
        this.__operateItem.purgeDependencyOnElmtId(f2);
        this.__frontColor.purgeDependencyOnElmtId(f2);
        this.__borderSize.purgeDependencyOnElmtId(f2);
        this.__canFocus.purgeDependencyOnElmtId(f2);
        this.__canTouch.purgeDependencyOnElmtId(f2);
        this.__canHover.purgeDependencyOnElmtId(f2);
        this.__isHover.purgeDependencyOnElmtId(f2);
        this.__itemHeight.purgeDependencyOnElmtId(f2);
        this.__isActive.purgeDependencyOnElmtId(f2);
        this.__hoveringColor.purgeDependencyOnElmtId(f2);
        this.__touchDownColor.purgeDependencyOnElmtId(f2);
        this.__activedColor.purgeDependencyOnElmtId(f2);
        this.__focusOutlineColor.purgeDependencyOnElmtId(f2);
        this.__fontSizeScale.purgeDependencyOnElmtId(f2);
        this.__containerDirection.purgeDependencyOnElmtId(f2);
        this.__contentItemDirection.purgeDependencyOnElmtId(f2);
        this.__containerPadding.purgeDependencyOnElmtId(f2);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(f2);
        this.__accessibilityTextBuilder.purgeDependencyOnElmtId(f2);
        this.__isFocus.purgeDependencyOnElmtId(f2);
        this.__isChecked.purgeDependencyOnElmtId(f2);
        this.__isWrapText.purgeDependencyOnElmtId(f2);
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
    set contentItem(e2) {
        this.__contentItem.set(e2);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(d2) {
        this.__operateItem.set(d2);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(c2) {
        this.__frontColor.set(c2);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(b2) {
        this.__borderSize.set(b2);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(a2) {
        this.__canFocus.set(a2);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(z1) {
        this.__canTouch.set(z1);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(y1) {
        this.__canHover.set(y1);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(x1) {
        this.__isHover.set(x1);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(w1) {
        this.__itemHeight.set(w1);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(v1) {
        this.__isActive.set(v1);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(u1) {
        this.__hoveringColor.set(u1);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(t1) {
        this.__touchDownColor.set(t1);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(s1) {
        this.__activedColor.set(s1);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(r1) {
        this.__focusOutlineColor.set(r1);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(q1) {
        this.__fontSizeScale.set(q1);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(p1) {
        this.__containerDirection.set(p1);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(o1) {
        this.__contentItemDirection.set(o1);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(n1) {
        this.__containerPadding.set(n1);
    }
    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }
    set textArrowLeftSafeOffset(m1) {
        this.__textArrowLeftSafeOffset.set(m1);
    }
    get accessibilityTextBuilder() {
        return this.__accessibilityTextBuilder.get();
    }
    set accessibilityTextBuilder(l1) {
        this.__accessibilityTextBuilder.set(l1);
    }
    get isFocus() {
        return this.__isFocus.get();
    }
    set isFocus(k1) {
        this.__isFocus.set(k1);
    }
    get isChecked() {
        return this.__isChecked.get();
    }
    set isChecked(j1) {
        this.__isChecked.set(j1);
    }
    get isWrapText() {
        return this.__isWrapText.get();
    }
    set isWrapText(i1) {
        this.__isWrapText.set(i1);
    }
    onWillApplyTheme(h1) {
        this.hoveringColor = h1.colors.interactiveHover;
        this.touchDownColor = h1.colors.interactivePressed;
        this.activedColor = h1.colors.interactiveActive;
        this.focusOutlineColor = h1.colors.interactiveFocus;
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
            let g1 = this.contentItem.iconStyle;
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && g1 <= IconType.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            }
            else {
                this.itemHeight = g1 === IconType.HEAD_SCULPTURE ? ItemHeight.FOURTH_HEIGHT : APPICON_ITEMLENGTH;
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
            ViewStackProcessor.visualState('focused');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_radius'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.composeListItem_stroke_normal_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.composeListItem_stroke_normal_thickness'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
            });
            ViewStackProcessor.visualState('pressed');
            Flex.backgroundColor(ObservedObject.GetRawObject(this.touchDownColor));
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
                                }, undefined, q, () => { }, { page: 'library/src/main/ets/components/composelistitem.ets', line: 1404, col: 11 });
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
                                }, undefined, k, () => { }, { page: 'library/src/main/ets/components/composelistitem.ets', line: 1409, col: 11 });
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
                                }, undefined, c, () => { }, { page: 'library/src/main/ets/components/composelistitem.ets', line: 1425, col: 11 });
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