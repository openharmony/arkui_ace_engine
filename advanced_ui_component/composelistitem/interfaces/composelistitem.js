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
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');

export var IconType;
(function (d12) {
    d12[d12['BADGE'] = 1] = 'BADGE';
    d12[d12['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    d12[d12['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    d12[d12['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    d12[d12['APP_ICON'] = 5] = 'APP_ICON';
    d12[d12['PREVIEW'] = 6] = 'PREVIEW';
    d12[d12['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    d12[d12['VERTICAL'] = 8] = 'VERTICAL';
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (c12) {
    c12[c12['LEVEL1'] = 1.75] = 'LEVEL1';
    c12[c12['LEVEL2'] = 2] = 'LEVEL2';
    c12[c12['LEVEL3'] = 3.2] = 'LEVEL3';
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (b12) {
    b12[b12['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    b12[b12['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    b12[b12['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    b12[b12['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    b12[b12['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
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
const IS_SUPPORT_SUBCOMPONENT_EVENT = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_focus_dynamic_effect'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
}).value !== 1;
const RECOVER_ITEM_SCALE = 1;
const CLEAR_SHADOW = -1;
const OPERATE_ITEM_RADIUS = 50;
const OPERATE_ITEM_BACKGROUND_COLOR = '#33000000';
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR = {
    'id': -1,
    'type': 10001,
    params: ['sys.color.ohos_id_color_switch_outline_off'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const OPERATE_ITEM_COLOR = '#99000000';
const TEXT_SUPPORT_MARQUEE = 1;
const IS_MARQUEE_OR_ELLIPSIS = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_right_textOverflow'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
}).value;
const UNUSUAL = -1;
const FOCUSED_BG_COLOR = {
    'id': -1,
    'type': 10001,
    params: ['sys.color.composeListItem_container_focus_color'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const NORMAL_BG_COLOR = {
    'id': -1,
    'type': 10001,
    params: ['sys.color.composeListItem_container_normal_color'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const FOCUSED_ITEM_SCALE = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_focus_magnification'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
}).value;
const FOCUSED_SHADOW = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_focus_shadow_attribute'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
})
    .value;
const NORMAL_SHADOW = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_normal_shadow_attribute'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
})
    .value;
const ITEM_PADDING = {
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_padding'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
const OPERATEITEM_ARROW_MARGIN_WIDTH = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_arrow_margin'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
}).value;
const APPICON_ITEMLENGTH = LengthMetrics.resource({
    'id': -1,
    'type': 10002,
    params: ['sys.float.composeListItem_AppIcon_ItemLength'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
}).value;

class Util {
    static isSymbolResource(z11) {
        if (!Util.isResourceType(z11)) {
            return false;
        }
        let a12 = z11;
        return a12.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(y11) {
        if (!y11) {
            return false;
        }
        if (typeof y11 === 'string' || typeof y11 === 'undefined') {
            return false;
        }
        return true;
    }
}

class ContentItemStruct extends ViewPU {
    constructor(s11, t11, u11, v11 = -1, w11 = undefined, x11) {
        super(s11, u11, v11, x11);
        if (typeof w11 === 'function') {
            this.paramsGenerator_ = w11;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(t11.iconStyle, this, 'iconStyle');
        this.__icon = new SynchedPropertyObjectOneWayPU(t11.icon, this, 'icon');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(t11.symbolStyle, this, 'symbolStyle');
        this.__primaryText = new SynchedPropertyObjectOneWayPU(t11.primaryText, this, 'primaryText');
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(t11.secondaryText, this, 'secondaryText');
        this.__description = new SynchedPropertyObjectOneWayPU(t11.description, this, 'description');
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, 'itemRowSpace');
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(t11.leftWidth, this, 'leftWidth');
        this.__primaryTextColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'primaryTextColor');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTextColor');
        this.__descriptionColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'descriptionColor');
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(t11.fontSizeScale, this, 'fontSizeScale');
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(t11.parentDirection, this, 'parentDirection');
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(t11.itemDirection, this, 'itemDirection');
        this.__isFocus = new SynchedPropertySimpleOneWayPU(t11.isFocus, this, 'isFocus');
        this.__primaryTextSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'primaryTextSize');
        this.__primaryTextColors = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'primaryTextColors');
        this.__itemHeight = new SynchedPropertyObjectOneWayPU(t11.itemHeight, this, 'itemHeight');
        this.__iconColor = new ObservedPropertyObjectPU(null, this, 'iconColor');
        this.__secondaryTextColors = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTextColors');
        this.__secondaryThirdTextSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.composeListItem_left_secondary_tertiary_text_size'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryThirdTextSize');
        this.__descriptionColors = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'descriptionColors');
        this.__isWrapText = new SynchedPropertyObjectTwoWayPU(t11.isWrapText, this, 'isWrapText');
        this.__isWrapFirstText = new ObservedPropertyObjectPU(false, this, 'isWrapFirstText');
        this.__isWrapSecondText = new ObservedPropertyObjectPU(false, this, 'isWrapSecondText');
        this.__isWrapThirdText = new ObservedPropertyObjectPU(false, this, 'isWrapThirdText');
        this.setInitiallyProvidedValue(t11);
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

    setInitiallyProvidedValue(r11) {
        if (r11.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (r11.icon === undefined) {
            this.__icon.set(null);
        }
        if (r11.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (r11.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (r11.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (r11.description === undefined) {
            this.__description.set(null);
        }
        if (r11.itemRowSpace !== undefined) {
            this.itemRowSpace = r11.itemRowSpace;
        }
        if (r11.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (r11.primaryTextColor !== undefined) {
            this.primaryTextColor = r11.primaryTextColor;
        }
        if (r11.secondaryTextColor !== undefined) {
            this.secondaryTextColor = r11.secondaryTextColor;
        }
        if (r11.descriptionColor !== undefined) {
            this.descriptionColor = r11.descriptionColor;
        }
        if (r11.isFocus === undefined) {
            this.__isFocus.set(false);
        }
        if (r11.primaryTextSize !== undefined) {
            this.primaryTextSize = r11.primaryTextSize;
        }
        if (r11.primaryTextColors !== undefined) {
            this.primaryTextColors = r11.primaryTextColors;
        }
        if (r11.itemHeight === undefined) {
            this.__itemHeight.set(null);
        }
        if (r11.iconColor !== undefined) {
            this.iconColor = r11.iconColor;
        }
        if (r11.secondaryTextColors !== undefined) {
            this.secondaryTextColors = r11.secondaryTextColors;
        }
        if (r11.secondaryThirdTextSize !== undefined) {
            this.secondaryThirdTextSize = r11.secondaryThirdTextSize;
        }
        if (r11.descriptionColors !== undefined) {
            this.descriptionColors = r11.descriptionColors;
        }
        if (r11.isWrapFirstText !== undefined) {
            this.isWrapFirstText = r11.isWrapFirstText;
        }
        if (r11.isWrapSecondText !== undefined) {
            this.isWrapSecondText = r11.isWrapSecondText;
        }
        if (r11.isWrapThirdText !== undefined) {
            this.isWrapThirdText = r11.isWrapThirdText;
        }
    }

    updateStateVars(q11) {
        this.__iconStyle.reset(q11.iconStyle);
        this.__icon.reset(q11.icon);
        this.__symbolStyle.reset(q11.symbolStyle);
        this.__primaryText.reset(q11.primaryText);
        this.__secondaryText.reset(q11.secondaryText);
        this.__description.reset(q11.description);
        this.__leftWidth.reset(q11.leftWidth);
        this.__fontSizeScale.reset(q11.fontSizeScale);
        this.__parentDirection.reset(q11.parentDirection);
        this.__itemDirection.reset(q11.itemDirection);
        this.__isFocus.reset(q11.isFocus);
        this.__itemHeight.reset(q11.itemHeight);
    }

    purgeVariableDependenciesOnElmtId(p11) {
        this.__iconStyle.purgeDependencyOnElmtId(p11);
        this.__icon.purgeDependencyOnElmtId(p11);
        this.__symbolStyle.purgeDependencyOnElmtId(p11);
        this.__primaryText.purgeDependencyOnElmtId(p11);
        this.__secondaryText.purgeDependencyOnElmtId(p11);
        this.__description.purgeDependencyOnElmtId(p11);
        this.__itemRowSpace.purgeDependencyOnElmtId(p11);
        this.__leftWidth.purgeDependencyOnElmtId(p11);
        this.__primaryTextColor.purgeDependencyOnElmtId(p11);
        this.__secondaryTextColor.purgeDependencyOnElmtId(p11);
        this.__descriptionColor.purgeDependencyOnElmtId(p11);
        this.__fontSizeScale.purgeDependencyOnElmtId(p11);
        this.__parentDirection.purgeDependencyOnElmtId(p11);
        this.__itemDirection.purgeDependencyOnElmtId(p11);
        this.__isFocus.purgeDependencyOnElmtId(p11);
        this.__primaryTextSize.purgeDependencyOnElmtId(p11);
        this.__primaryTextColors.purgeDependencyOnElmtId(p11);
        this.__itemHeight.purgeDependencyOnElmtId(p11);
        this.__iconColor.purgeDependencyOnElmtId(p11);
        this.__secondaryTextColors.purgeDependencyOnElmtId(p11);
        this.__secondaryThirdTextSize.purgeDependencyOnElmtId(p11);
        this.__descriptionColors.purgeDependencyOnElmtId(p11);
        this.__isWrapText.purgeDependencyOnElmtId(p11);
        this.__isWrapFirstText.purgeDependencyOnElmtId(p11);
        this.__isWrapSecondText.purgeDependencyOnElmtId(p11);
        this.__isWrapThirdText.purgeDependencyOnElmtId(p11);
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

    set iconStyle(o11) {
        this.__iconStyle.set(o11);
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(n11) {
        this.__icon.set(n11);
    }

    get symbolStyle() {
        return this.__symbolStyle.get();
    }

    set symbolStyle(m11) {
        this.__symbolStyle.set(m11);
    }

    get primaryText() {
        return this.__primaryText.get();
    }

    set primaryText(l11) {
        this.__primaryText.set(l11);
    }

    get secondaryText() {
        return this.__secondaryText.get();
    }

    set secondaryText(k11) {
        this.__secondaryText.set(k11);
    }

    get description() {
        return this.__description.get();
    }

    set description(j11) {
        this.__description.set(j11);
    }

    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }

    set itemRowSpace(i11) {
        this.__itemRowSpace.set(i11);
    }

    get leftWidth() {
        return this.__leftWidth.get();
    }

    set leftWidth(h11) {
        this.__leftWidth.set(h11);
    }

    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }

    set primaryTextColor(g11) {
        this.__primaryTextColor.set(g11);
    }

    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }

    set secondaryTextColor(f11) {
        this.__secondaryTextColor.set(f11);
    }

    get descriptionColor() {
        return this.__descriptionColor.get();
    }

    set descriptionColor(e11) {
        this.__descriptionColor.set(e11);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(d11) {
        this.__fontSizeScale.set(d11);
    }

    get parentDirection() {
        return this.__parentDirection.get();
    }

    set parentDirection(c11) {
        this.__parentDirection.set(c11);
    }

    get itemDirection() {
        return this.__itemDirection.get();
    }

    set itemDirection(b11) {
        this.__itemDirection.set(b11);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(a11) {
        this.__isFocus.set(a11);
    }

    get primaryTextSize() {
        return this.__primaryTextSize.get();
    }

    set primaryTextSize(z10) {
        this.__primaryTextSize.set(z10);
    }

    get primaryTextColors() {
        return this.__primaryTextColors.get();
    }

    set primaryTextColors(y10) {
        this.__primaryTextColors.set(y10);
    }

    get itemHeight() {
        return this.__itemHeight.get();
    }

    set itemHeight(x10) {
        this.__itemHeight.set(x10);
    }

    get iconColor() {
        return this.__iconColor.get();
    }

    set iconColor(w10) {
        this.__iconColor.set(w10);
    }

    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }

    set secondaryTextColors(v10) {
        this.__secondaryTextColors.set(v10);
    }

    get secondaryThirdTextSize() {
        return this.__secondaryThirdTextSize.get();
    }

    set secondaryThirdTextSize(u10) {
        this.__secondaryThirdTextSize.set(u10);
    }

    get descriptionColors() {
        return this.__descriptionColors.get();
    }

    set descriptionColors(t10) {
        this.__descriptionColors.set(t10);
    }

    get isWrapText() {
        return this.__isWrapText.get();
    }

    set isWrapText(s10) {
        this.__isWrapText.set(s10);
    }

    get isWrapFirstText() {
        return this.__isWrapFirstText.get();
    }

    set isWrapFirstText(r10) {
        this.__isWrapFirstText.set(r10);
    }

    get isWrapSecondText() {
        return this.__isWrapSecondText.get();
    }

    set isWrapSecondText(q10) {
        this.__isWrapSecondText.set(q10);
    }

    get isWrapThirdText() {
        return this.__isWrapThirdText.get();
    }

    set isWrapThirdText(p10) {
        this.__isWrapThirdText.set(p10);
    }

    onWillApplyTheme(o10) {
        this.primaryTextColor = o10.colors.fontPrimary;
        this.secondaryTextColor = o10.colors.fontSecondary;
        this.descriptionColor = o10.colors.fontTertiary;
    }

    onPropChange() {
        if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        } else {
            this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
            this.primaryTextColors = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.composeListItem_left_text_focus_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
            this.secondaryTextColors = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.composeListItem_left_secondary_text_focus_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
            this.descriptionColors = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.composeListItem_left_secondary_text_focus_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
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
                return {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.composeListItem_badge_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
            case IconType.SYSTEM_ICON:
                return {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.composeListItem_icon_normal_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
            default:
                return {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_secondary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
        }
    }

    judgeIsWrap(k10, l10, m10) {
        let n10 = this.getSingleRowTextHeight(k10, l10);
        return m10 > n10;
    }

    getSingleRowTextHeight(h10, i10) {
        if (h10 && i10) {
            let j10 = px2vp(measure.measureTextSize({
                textContent: h10,
                fontSize: i10,
                maxLines: TEXT_MAX_LINE
            }).height);
            return j10;
        }
        return 0;
    }

    aboutToAppear() {
        this.onPropChange();
    }

    createIcon(q9 = null) {
        this.observeComponentCreation2((r9, s9) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t9, u9) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f10, g10) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([this.getContentItemIconFillColor()]);
                                    SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
                                    SymbolGlyph.fontSize(`${ICON_SIZE_MAP.get(this.iconStyle)}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.borderRadius({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.composeListItem_Image_Radius'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.flexShrink(0);
                                }, SymbolGlyph);
                            });
                        } else if (this.icon != null) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((v9, w9) => {
                                    If.create();
                                    if (Util.isSymbolResource(ObservedObject.GetRawObject(this.icon))) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((d10, e10) => {
                                                SymbolGlyph.create(this.icon);
                                                SymbolGlyph.fontSize(`${ICON_SIZE_MAP.get(this.iconStyle)}vp`);
                                                SymbolGlyph.fontColor([this.getContentItemIconFillColor()]);
                                                SymbolGlyph.borderRadius({
                                                    'id': -1,
                                                    'type': 10002,
                                                    params: ['sys.float.composeListItem_Image_Radius'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                });
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.flexShrink(0);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((x9, y9) => {
                                                If.create();
                                                if (this.iconStyle <= IconType.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((b10, c10) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.borderRadius({
                                                                'id': -1,
                                                                'type': 10002,
                                                                params: ['sys.float.composeListItem_Image_Radius'],
                                                                'bundleName': '__harDefaultBundleName__',
                                                                'moduleName': '__harDefaultModuleName__'
                                                            });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor(this.getContentItemIconFillColor());
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                } else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((z9, a10) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.constraintSize({
                                                                minWidth: SPECIAL_ICON_SIZE,
                                                                maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                                                minHeight: SPECIAL_ICON_SIZE,
                                                                maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                                            });
                                                            Image.borderRadius({
                                                                'id': -1,
                                                                'type': 10002,
                                                                params: ['sys.float.composeListItem_Image_Radius'],
                                                                'bundleName': '__harDefaultBundleName__',
                                                                'moduleName': '__harDefaultModuleName__'
                                                            });
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
                        } else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    createText(x8 = null) {
        this.observeComponentCreation2((o9, p9) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((k9, l9) => {
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
            Text.onSizeChange((m9, n9) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isWrapFirstText = this.judgeIsWrap(ObservedObject.GetRawObject(this.primaryText),
                        ObservedObject.GetRawObject(this.primaryTextSize), n9.height);
                }
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((e9, f9) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g9, h9) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((i9, j9) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                                this.isWrapSecondText =
                                    this.judgeIsWrap(ObservedObject.GetRawObject(this.secondaryText),
                                        ObservedObject.GetRawObject(this.secondaryThirdTextSize), j9.height);
                            }
                        });
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((y8, z8) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a9, b9) => {
                        Text.create(this.description);
                        Text.fontSize(ObservedObject.GetRawObject(this.secondaryThirdTextSize));
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColors));
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                            TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((c9, d9) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                                this.isWrapThirdText = this.judgeIsWrap(ObservedObject.GetRawObject(this.description),
                                    ObservedObject.GetRawObject(this.secondaryThirdTextSize), d9.height);
                            }
                        });
                    }, Text);
                    Text.pop();
                });
            } else {
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
            return LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }
        return LengthMetrics.vp(this.itemRowSpace);
    }

    initialRender() {
        this.observeComponentCreation2((v8, w8) => {
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
    constructor(p8, q8, r8, s8 = -1, t8 = undefined, u8) {
        super(p8, r8, s8, u8);
        if (typeof t8 === 'function') {
            this.paramsGenerator_ = t8;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(q8.arrow, this, 'arrow');
        this.__icon = new SynchedPropertyObjectOneWayPU(q8.icon, this, 'icon');
        this.__subIcon = new SynchedPropertyObjectOneWayPU(q8.subIcon, this, 'subIcon');
        this.__button = new SynchedPropertyObjectOneWayPU(q8.button, this, 'button');
        this.__switch = new SynchedPropertyObjectOneWayPU(q8.switch, this, 'switch');
        this.__checkBox = new SynchedPropertyObjectOneWayPU(q8.checkBox, this, 'checkBox');
        this.__radio = new SynchedPropertyObjectOneWayPU(q8.radio, this, 'radio');
        this.__image = new SynchedPropertyObjectOneWayPU(q8.image, this, 'image');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(q8.symbolStyle, this, 'symbolStyle');
        this.__text = new SynchedPropertyObjectOneWayPU(q8.text, this, 'text');
        this.__switchState = new ObservedPropertySimplePU(false, this, 'switchState');
        this.__radioState = new ObservedPropertySimplePU(false, this, 'radioState');
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, 'checkBoxState');
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(q8.rightWidth, this, 'rightWidth');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTextColor');
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(q8.parentCanFocus, this, 'parentCanFocus');
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(q8.parentCanTouch, this, 'parentCanTouch');
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(q8.parentIsHover, this, 'parentIsHover');
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(q8.parentCanHover, this, 'parentCanHover');
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(q8.parentIsActive, this, 'parentIsActive');
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(q8.parentFrontColor, this, 'parentFrontColor');
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(q8.parentDirection, this, 'parentDirection');
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, 'rowSpace');
        this.__isFocus = new SynchedPropertySimpleTwoWayPU(q8.isFocus, this, 'isFocus');
        this.__secondaryTextSize = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_size_body2'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTextSize');
        this.__secondaryTextColors = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'secondaryTextColors');
        this.__iconColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.composeListItem_right_icon_normal_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'iconColor');
        this.__isChecked = new SynchedPropertySimpleTwoWayPU(q8.isChecked, this, 'isChecked');
        this.setInitiallyProvidedValue(q8);
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

    setInitiallyProvidedValue(o8) {
        if (o8.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (o8.icon === undefined) {
            this.__icon.set(null);
        }
        if (o8.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (o8.button === undefined) {
            this.__button.set(null);
        }
        if (o8.switch === undefined) {
            this.__switch.set(null);
        }
        if (o8.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (o8.radio === undefined) {
            this.__radio.set(null);
        }
        if (o8.image === undefined) {
            this.__image.set(null);
        }
        if (o8.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (o8.text === undefined) {
            this.__text.set(null);
        }
        if (o8.switchState !== undefined) {
            this.switchState = o8.switchState;
        }
        if (o8.radioState !== undefined) {
            this.radioState = o8.radioState;
        }
        if (o8.checkBoxState !== undefined) {
            this.checkBoxState = o8.checkBoxState;
        }
        if (o8.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (o8.secondaryTextColor !== undefined) {
            this.secondaryTextColor = o8.secondaryTextColor;
        }
        if (o8.hoveringColor !== undefined) {
            this.hoveringColor = o8.hoveringColor;
        }
        if (o8.activedColor !== undefined) {
            this.activedColor = o8.activedColor;
        }
        if (o8.rowSpace !== undefined) {
            this.rowSpace = o8.rowSpace;
        }
        if (o8.secondaryTextSize !== undefined) {
            this.secondaryTextSize = o8.secondaryTextSize;
        }
        if (o8.secondaryTextColors !== undefined) {
            this.secondaryTextColors = o8.secondaryTextColors;
        }
        if (o8.iconColor !== undefined) {
            this.iconColor = o8.iconColor;
        }
    }

    updateStateVars(n8) {
        this.__arrow.reset(n8.arrow);
        this.__icon.reset(n8.icon);
        this.__subIcon.reset(n8.subIcon);
        this.__button.reset(n8.button);
        this.__switch.reset(n8.switch);
        this.__checkBox.reset(n8.checkBox);
        this.__radio.reset(n8.radio);
        this.__image.reset(n8.image);
        this.__symbolStyle.reset(n8.symbolStyle);
        this.__text.reset(n8.text);
        this.__rightWidth.reset(n8.rightWidth);
    }

    purgeVariableDependenciesOnElmtId(m8) {
        this.__arrow.purgeDependencyOnElmtId(m8);
        this.__icon.purgeDependencyOnElmtId(m8);
        this.__subIcon.purgeDependencyOnElmtId(m8);
        this.__button.purgeDependencyOnElmtId(m8);
        this.__switch.purgeDependencyOnElmtId(m8);
        this.__checkBox.purgeDependencyOnElmtId(m8);
        this.__radio.purgeDependencyOnElmtId(m8);
        this.__image.purgeDependencyOnElmtId(m8);
        this.__symbolStyle.purgeDependencyOnElmtId(m8);
        this.__text.purgeDependencyOnElmtId(m8);
        this.__switchState.purgeDependencyOnElmtId(m8);
        this.__radioState.purgeDependencyOnElmtId(m8);
        this.__checkBoxState.purgeDependencyOnElmtId(m8);
        this.__rightWidth.purgeDependencyOnElmtId(m8);
        this.__secondaryTextColor.purgeDependencyOnElmtId(m8);
        this.__hoveringColor.purgeDependencyOnElmtId(m8);
        this.__activedColor.purgeDependencyOnElmtId(m8);
        this.__parentCanFocus.purgeDependencyOnElmtId(m8);
        this.__parentCanTouch.purgeDependencyOnElmtId(m8);
        this.__parentIsHover.purgeDependencyOnElmtId(m8);
        this.__parentCanHover.purgeDependencyOnElmtId(m8);
        this.__parentIsActive.purgeDependencyOnElmtId(m8);
        this.__parentFrontColor.purgeDependencyOnElmtId(m8);
        this.__parentDirection.purgeDependencyOnElmtId(m8);
        this.__rowSpace.purgeDependencyOnElmtId(m8);
        this.__isFocus.purgeDependencyOnElmtId(m8);
        this.__secondaryTextSize.purgeDependencyOnElmtId(m8);
        this.__secondaryTextColors.purgeDependencyOnElmtId(m8);
        this.__iconColor.purgeDependencyOnElmtId(m8);
        this.__isChecked.purgeDependencyOnElmtId(m8);
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

    set arrow(l8) {
        this.__arrow.set(l8);
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(k8) {
        this.__icon.set(k8);
    }

    get subIcon() {
        return this.__subIcon.get();
    }

    set subIcon(j8) {
        this.__subIcon.set(j8);
    }

    get button() {
        return this.__button.get();
    }

    set button(i8) {
        this.__button.set(i8);
    }

    get switch() {
        return this.__switch.get();
    }

    set switch(h8) {
        this.__switch.set(h8);
    }

    get checkBox() {
        return this.__checkBox.get();
    }

    set checkBox(g8) {
        this.__checkBox.set(g8);
    }

    get radio() {
        return this.__radio.get();
    }

    set radio(f8) {
        this.__radio.set(f8);
    }

    get image() {
        return this.__image.get();
    }

    set image(e8) {
        this.__image.set(e8);
    }

    get symbolStyle() {
        return this.__symbolStyle.get();
    }

    set symbolStyle(d8) {
        this.__symbolStyle.set(d8);
    }

    get text() {
        return this.__text.get();
    }

    set text(c8) {
        this.__text.set(c8);
    }

    get switchState() {
        return this.__switchState.get();
    }

    set switchState(b8) {
        this.__switchState.set(b8);
    }

    get radioState() {
        return this.__radioState.get();
    }

    set radioState(a8) {
        this.__radioState.set(a8);
    }

    get checkBoxState() {
        return this.__checkBoxState.get();
    }

    set checkBoxState(z7) {
        this.__checkBoxState.set(z7);
    }

    get rightWidth() {
        return this.__rightWidth.get();
    }

    set rightWidth(y7) {
        this.__rightWidth.set(y7);
    }

    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }

    set secondaryTextColor(x7) {
        this.__secondaryTextColor.set(x7);
    }

    get hoveringColor() {
        return this.__hoveringColor.get();
    }

    set hoveringColor(w7) {
        this.__hoveringColor.set(w7);
    }

    get activedColor() {
        return this.__activedColor.get();
    }

    set activedColor(v7) {
        this.__activedColor.set(v7);
    }

    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }

    set parentCanFocus(u7) {
        this.__parentCanFocus.set(u7);
    }

    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }

    set parentCanTouch(t7) {
        this.__parentCanTouch.set(t7);
    }

    get parentIsHover() {
        return this.__parentIsHover.get();
    }

    set parentIsHover(s7) {
        this.__parentIsHover.set(s7);
    }

    get parentCanHover() {
        return this.__parentCanHover.get();
    }

    set parentCanHover(r7) {
        this.__parentCanHover.set(r7);
    }

    get parentIsActive() {
        return this.__parentIsActive.get();
    }

    set parentIsActive(q7) {
        this.__parentIsActive.set(q7);
    }

    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }

    set parentFrontColor(p7) {
        this.__parentFrontColor.set(p7);
    }

    get parentDirection() {
        return this.__parentDirection.get();
    }

    set parentDirection(o7) {
        this.__parentDirection.set(o7);
    }

    get rowSpace() {
        return this.__rowSpace.get();
    }

    set rowSpace(n7) {
        this.__rowSpace.set(n7);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(m7) {
        this.__isFocus.set(m7);
    }

    get secondaryTextSize() {
        return this.__secondaryTextSize.get();
    }

    set secondaryTextSize(l7) {
        this.__secondaryTextSize.set(l7);
    }

    get secondaryTextColors() {
        return this.__secondaryTextColors.get();
    }

    set secondaryTextColors(k7) {
        this.__secondaryTextColors.set(k7);
    }

    get iconColor() {
        return this.__iconColor.get();
    }

    set iconColor(j7) {
        this.__iconColor.set(j7);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(i7) {
        this.__isChecked.set(i7);
    }

    onWillApplyTheme(h7) {
        this.secondaryTextColor = h7.colors.fontSecondary;
        this.hoveringColor = h7.colors.interactiveHover;
        this.activedColor = h7.colors.interactiveActive;
    }

    onFocusChange() {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
            this.secondaryTextColors = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.composeListItem_right_text_focus_color'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        } else {
            this.secondaryTextColors = this.secondaryTextColor;
        }
        this.iconColor = this.isFocus ? {
            'id': -1,
            'type': 10001,
            params: ['sys.color.composeListItem_right_icon_focus_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        } : {
            'id': -1,
            'type': 10001,
            params: ['sys.color.composeListItem_right_icon_normal_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
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
        } else {
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

    createButton(z6 = null) {
        this.observeComponentCreation2((e7, f7) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Button.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_button3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated_transparent'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.constraintSize({
                minHeight: BUTTON_SIZE
            });
            Button.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_button_normal'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((g7) => {
                this.parentCanHover = false;
                if (g7 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!g7) {
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
        this.observeComponentCreation2((c7, d7) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((a7, b7) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }

    createIcon(k6, l6 = null) {
        this.observeComponentCreation2((w6, x6) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((y6) => {
                this.parentCanHover = false;
                if (y6 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!y6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(k6.icon?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(k6.icon?.accessibilityLevel, k6.icon?.action));
            Button.accessibilityText(getAccessibilityText(k6.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(k6.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((m6, n6) => {
            If.create();
            if (k6.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u6, v6) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(k6.icon?.symbolStyle);
                        SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o6, p6) => {
                        If.create();
                        if (Util.isSymbolResource(k6.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s6, t6) => {
                                    SymbolGlyph.create(k6.icon?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q6, r6) => {
                                    Image.create(k6.icon?.value);
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

    createImage(d6 = null) {
        this.observeComponentCreation2((e6, f6) => {
            If.create();
            if (Util.isSymbolResource(ObservedObject.GetRawObject(this.image))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i6, j6) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g6, h6) => {
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

    createSymbol(a6 = null) {
        this.observeComponentCreation2((b6, c6) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
            SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }

    createText(x5 = null) {
        this.observeComponentCreation2((y5, z5) => {
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
            Text.maxLines(LengthMetrics.resource({
                'id': -1,
                'type': 10002,
                params: ['sys.float.composeListItem_maxLines_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }).value);
            Text.draggable(false);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
    }

    createArrow(j5 = null) {
        this.observeComponentCreation2((u5, v5) => {
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
            Button.onHover((w5) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (w5 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                } else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel,
                this.arrow?.action));
            Button.accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((k5, l5) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s5, t5) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_fourth'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        } : this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                        SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m5, n5) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q5, r5) => {
                                    SymbolGlyph.create(this.arrow?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_fourth'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    } : this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((o5, p5) => {
                                    Image.create(this.arrow?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ARROW_WIDTH);
                                    Image.focusable(true);
                                    Image.fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_fourth'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    } : this.iconColor);
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

    createRadio(e5 = null) {
        this.observeComponentCreation2((f5, g5) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: this.getUnselectedColor()
            });
            Radio.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((i5) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.radioState = i5;
                    this.isChecked = i5;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(i5);
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
            Radio.onHover((h5) => {
                this.parentCanHover = false;
                if (h5 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!h5) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Radio.accessibilityLevel(getAccessibilityLevelOnChange(this.radio?.accessibilityLevel,
                this.radio?.onChange));
            Radio.accessibilityText(getAccessibilityText(this.radio?.accessibilityText ?? ''));
            Radio.accessibilityDescription(getAccessibilityText(this.radio?.accessibilityDescription ?? ''));
        }, Radio);
    }

    createCheckBox(z4 = null) {
        this.observeComponentCreation2((a5, b5) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(this.getUnselectedColor());
            Checkbox.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((d5) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.checkBoxState = d5;
                    this.isChecked = d5;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(d5);
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
            Checkbox.onHover((c5) => {
                this.parentCanHover = false;
                if (c5 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!c5) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Checkbox.accessibilityLevel(getAccessibilityLevelOnChange(this.checkBox?.accessibilityLevel,
                this.checkBox?.onChange));
            Checkbox.accessibilityText(getAccessibilityText(this.checkBox?.accessibilityText ?? ''));
            Checkbox.accessibilityDescription(getAccessibilityText(this.checkBox?.accessibilityDescription ?? ''));
        }, Checkbox);
        Checkbox.pop();
    }

    createSwitch(s4 = null) {
        this.observeComponentCreation2((w4, x4) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((y4) => {
                this.parentCanHover = false;
                if (y4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!y4) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((t4, u4) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR :
            Color.Transparent);
            Toggle.switchPointColor(!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus && !this.switchState ?
                OPERATE_ITEM_COLOR :
                UNUSUAL);
            Toggle.onChange((v4) => {
                this.switchState = v4;
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isChecked = v4;
                }
                if (this.switch?.onChange) {
                    this.switch?.onChange(v4);
                }
            });
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Toggle.accessibilityLevel(getAccessibilityLevelOnChange(this.switch?.accessibilityLevel,
                this.switch?.onChange));
            Toggle.accessibilityText(getAccessibilityText(this.switch?.accessibilityText ?? ''));
            Toggle.accessibilityDescription(getAccessibilityText(this.switch?.accessibilityDescription ?? ''));
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }

    createTextArrow(k3 = null) {
        this.observeComponentCreation2((p4, q4) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
                (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None);
            Button.labelStyle({
                maxLines: TEXT_MAX_LINE
            });
            Button.backgroundColor(Color.Transparent);
            Button.constraintSize({ minHeight: TEXT_ARROW_HEIGHT });
            Button.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_corner_radius_clicked'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
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
            Button.onHover((r4) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (r4 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.parentCanHover = false;
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                } else {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel,
                this.arrow?.action));
            Button.accessibilityText(`${this.text} ${getAccessibilityText(this.arrow?.accessibilityText ?? '')}`);
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((l3, m3) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((n4, o4) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((l4, m4) => {
                        Text.create(this.text);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body2'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((b4, c4) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((j4, k4) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_fourth'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((d4, e4) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((h4, i4) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                                SymbolGlyph.fontColor([{
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.ohos_id_color_fourth'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                }]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((f4, g4) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                                Image.width(OPERATEITEM_ARROW_WIDTH);
                                                Image.fillColor({
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.ohos_id_color_fourth'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                });
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((z3, a4) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((x3, y3) => {
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
                        Text.maxLines(LengthMetrics.resource({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.composeListItem_maxLines_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        }).value);
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH + OPERATEITEM_ARROW_MARGIN_WIDTH}vp)`
                        });
                        Text.margin({ right: OPERATEITEM_ARROW_MARGIN_WIDTH });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((n3, o3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((v3, w3) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.icon_fourth'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    } : this.iconColor]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((p3, q3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((t3, u3) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                                SymbolGlyph.fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_fourth'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                } : this.iconColor]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    } else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((r3, s3) => {
                                                Image.create(this.arrow?.value);
                                                Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                                Image.width(OPERATEITEM_ARROW_WIDTH);
                                                Image.fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? {
                                                    'id': -1,
                                                    'type': 10001,
                                                    params: ['sys.color.icon_fourth'],
                                                    'bundleName': '__harDefaultBundleName__',
                                                    'moduleName': '__harDefaultModuleName__'
                                                } : this.iconColor);
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
        let j3 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            j3.justifyContent = FlexAlign.SpaceBetween;
        } else {
            j3.space = { main: LengthMetrics.vp(this.rowSpace) };
            j3.justifyContent = FlexAlign.End;
        }
        return j3;
    }

    initialRender() {
        this.observeComponentCreation2((h3, i3) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((d3, e3) => {
            If.create();
            if (this.button != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.createButton.bind(this)();
                });
            } else if (this.symbolStyle != null) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.createSymbol.bind(this)();
                });
            } else if (this.image != null) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.createImage.bind(this)();
                });
            } else if (this.icon != null && this.text != null) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.createText.bind(this)();
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon',
                        { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                });
            } else if (this.arrow != null && this.text == null) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.createArrow.bind(this)();
                });
            } else if (this.arrow != null && this.text != null) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.createTextArrow.bind(this)();
                });
            } else if (this.text != null) {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.createText.bind(this)();
                });
            } else if (this.radio != null) {
                this.ifElseBranchUpdateFunction(7, () => {
                    this.createRadio.bind(this)();
                });
            } else if (this.checkBox != null) {
                this.ifElseBranchUpdateFunction(8, () => {
                    this.createCheckBox.bind(this)();
                });
            } else if (this.switch != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createSwitch.bind(this)();
                });
            } else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(10, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon',
                        { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                    this.observeComponentCreation2((f3, g3) => {
                        If.create();
                        if (this.subIcon != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon',
                                    { icon: () => (this['__subIcon'] ? this['__subIcon'] : this['subIcon']) }));
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            } else {
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

function getAccessibilityText(y2) {
    try {
        let c3 = '';
        if (typeof y2 === 'string') {
            c3 = y2;
        } else {
            c3 = getContext().resourceManager.getStringSync(y2);
        }
        return c3;
    } catch (z2) {
        let a3 = z2.code;
        let b3 = z2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${a3}, message: ${b3}`);
        return '';
    }
}

function getAccessibilityLevelOnChange(w2, x2) {
    if (w2) {
        return w2;
    }
    if (x2) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}

function getAccessibilityLevelOnAction(u2, v2) {
    if (u2) {
        return u2;
    }
    if (v2) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}

export class ComposeListItem extends ViewPU {
    constructor(j2, k2, l2, m2 = -1, n2 = undefined, o2) {
        super(j2, l2, m2, o2);
        if (typeof n2 === 'function') {
            this.paramsGenerator_ = n2;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(k2.contentItem, this, 'contentItem');
        this.__operateItem = new SynchedPropertyObjectOneWayPU(k2.operateItem, this, 'operateItem');
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
        this.__focusOutlineColor = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'focusOutlineColor');
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
        this.__listScale = new ObservedPropertyObjectPU({ x: 1, y: 1 }, this, 'listScale');
        this.envCallback = {
            onConfigurationUpdated: (q2) => {
                if (q2 === undefined || !this.isFollowingSystemFontScale) {
                    this.fontSizeScale = 1;
                    return;
                }
                try {
                    this.fontSizeScale = Math.min(this.maxFontScale, q2.fontSizeScale ?? 1);
                } catch (r2) {
                    let s2 = r2.code;
                    let t2 = r2.message;
                    hilog.error(0x3900, 'Ace', `ComposeListItem environmentCallback error: ${s2}, ${t2}`);
                }
            },
            onMemoryLevel: (p2) => {
            }
        };
        this.setInitiallyProvidedValue(k2);
        this.declareWatch('contentItem', this.onPropChange);
        this.declareWatch('operateItem', this.onPropChange);
        this.declareWatch('fontSizeScale', this.onFontSizeScaleChange);
        this.declareWatch('isWrapText', this.onWrapChange);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(i2) {
        if (i2.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (i2.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (i2.frontColor !== undefined) {
            this.frontColor = i2.frontColor;
        }
        if (i2.borderSize !== undefined) {
            this.borderSize = i2.borderSize;
        }
        if (i2.canFocus !== undefined) {
            this.canFocus = i2.canFocus;
        }
        if (i2.canTouch !== undefined) {
            this.canTouch = i2.canTouch;
        }
        if (i2.canHover !== undefined) {
            this.canHover = i2.canHover;
        }
        if (i2.isHover !== undefined) {
            this.isHover = i2.isHover;
        }
        if (i2.itemHeight !== undefined) {
            this.itemHeight = i2.itemHeight;
        }
        if (i2.isActive !== undefined) {
            this.isActive = i2.isActive;
        }
        if (i2.hoveringColor !== undefined) {
            this.hoveringColor = i2.hoveringColor;
        }
        if (i2.touchDownColor !== undefined) {
            this.touchDownColor = i2.touchDownColor;
        }
        if (i2.activedColor !== undefined) {
            this.activedColor = i2.activedColor;
        }
        if (i2.focusOutlineColor !== undefined) {
            this.focusOutlineColor = i2.focusOutlineColor;
        }
        if (i2.fontSizeScale !== undefined) {
            this.fontSizeScale = i2.fontSizeScale;
        }
        if (i2.containerDirection !== undefined) {
            this.containerDirection = i2.containerDirection;
        }
        if (i2.contentItemDirection !== undefined) {
            this.contentItemDirection = i2.contentItemDirection;
        }
        if (i2.containerPadding !== undefined) {
            this.containerPadding = i2.containerPadding;
        }
        if (i2.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = i2.textArrowLeftSafeOffset;
        }
        if (i2.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = i2.isFollowingSystemFontScale;
        }
        if (i2.maxFontScale !== undefined) {
            this.maxFontScale = i2.maxFontScale;
        }
        if (i2.callbackId !== undefined) {
            this.callbackId = i2.callbackId;
        }
        if (i2.accessibilityTextBuilder !== undefined) {
            this.accessibilityTextBuilder = i2.accessibilityTextBuilder;
        }
        if (i2.isFocus !== undefined) {
            this.isFocus = i2.isFocus;
        }
        if (i2.isChecked !== undefined) {
            this.isChecked = i2.isChecked;
        }
        if (i2.isWrapText !== undefined) {
            this.isWrapText = i2.isWrapText;
        }
        if (i2.listScale !== undefined) {
            this.listScale = i2.listScale;
        }
        if (i2.envCallback !== undefined) {
            this.envCallback = i2.envCallback;
        }
    }

    updateStateVars(h2) {
        this.__contentItem.reset(h2.contentItem);
        this.__operateItem.reset(h2.operateItem);
    }

    purgeVariableDependenciesOnElmtId(g2) {
        this.__contentItem.purgeDependencyOnElmtId(g2);
        this.__operateItem.purgeDependencyOnElmtId(g2);
        this.__frontColor.purgeDependencyOnElmtId(g2);
        this.__borderSize.purgeDependencyOnElmtId(g2);
        this.__canFocus.purgeDependencyOnElmtId(g2);
        this.__canTouch.purgeDependencyOnElmtId(g2);
        this.__canHover.purgeDependencyOnElmtId(g2);
        this.__isHover.purgeDependencyOnElmtId(g2);
        this.__itemHeight.purgeDependencyOnElmtId(g2);
        this.__isActive.purgeDependencyOnElmtId(g2);
        this.__hoveringColor.purgeDependencyOnElmtId(g2);
        this.__touchDownColor.purgeDependencyOnElmtId(g2);
        this.__activedColor.purgeDependencyOnElmtId(g2);
        this.__focusOutlineColor.purgeDependencyOnElmtId(g2);
        this.__fontSizeScale.purgeDependencyOnElmtId(g2);
        this.__containerDirection.purgeDependencyOnElmtId(g2);
        this.__contentItemDirection.purgeDependencyOnElmtId(g2);
        this.__containerPadding.purgeDependencyOnElmtId(g2);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(g2);
        this.__accessibilityTextBuilder.purgeDependencyOnElmtId(g2);
        this.__isFocus.purgeDependencyOnElmtId(g2);
        this.__isChecked.purgeDependencyOnElmtId(g2);
        this.__isWrapText.purgeDependencyOnElmtId(g2);
        this.__listScale.purgeDependencyOnElmtId(g2);
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
        this.__listScale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get contentItem() {
        return this.__contentItem.get();
    }

    set contentItem(f2) {
        this.__contentItem.set(f2);
    }

    get operateItem() {
        return this.__operateItem.get();
    }

    set operateItem(e2) {
        this.__operateItem.set(e2);
    }

    get frontColor() {
        return this.__frontColor.get();
    }

    set frontColor(d2) {
        this.__frontColor.set(d2);
    }

    get borderSize() {
        return this.__borderSize.get();
    }

    set borderSize(c2) {
        this.__borderSize.set(c2);
    }

    get canFocus() {
        return this.__canFocus.get();
    }

    set canFocus(b2) {
        this.__canFocus.set(b2);
    }

    get canTouch() {
        return this.__canTouch.get();
    }

    set canTouch(a2) {
        this.__canTouch.set(a2);
    }

    get canHover() {
        return this.__canHover.get();
    }

    set canHover(z1) {
        this.__canHover.set(z1);
    }

    get isHover() {
        return this.__isHover.get();
    }

    set isHover(y1) {
        this.__isHover.set(y1);
    }

    get itemHeight() {
        return this.__itemHeight.get();
    }

    set itemHeight(x1) {
        this.__itemHeight.set(x1);
    }

    get isActive() {
        return this.__isActive.get();
    }

    set isActive(w1) {
        this.__isActive.set(w1);
    }

    get hoveringColor() {
        return this.__hoveringColor.get();
    }

    set hoveringColor(v1) {
        this.__hoveringColor.set(v1);
    }

    get touchDownColor() {
        return this.__touchDownColor.get();
    }

    set touchDownColor(u1) {
        this.__touchDownColor.set(u1);
    }

    get activedColor() {
        return this.__activedColor.get();
    }

    set activedColor(t1) {
        this.__activedColor.set(t1);
    }

    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }

    set focusOutlineColor(s1) {
        this.__focusOutlineColor.set(s1);
    }

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(r1) {
        this.__fontSizeScale.set(r1);
    }

    get containerDirection() {
        return this.__containerDirection.get();
    }

    set containerDirection(q1) {
        this.__containerDirection.set(q1);
    }

    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }

    set contentItemDirection(p1) {
        this.__contentItemDirection.set(p1);
    }

    get containerPadding() {
        return this.__containerPadding.get();
    }

    set containerPadding(o1) {
        this.__containerPadding.set(o1);
    }

    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }

    set textArrowLeftSafeOffset(n1) {
        this.__textArrowLeftSafeOffset.set(n1);
    }

    get accessibilityTextBuilder() {
        return this.__accessibilityTextBuilder.get();
    }

    set accessibilityTextBuilder(m1) {
        this.__accessibilityTextBuilder.set(m1);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(l1) {
        this.__isFocus.set(l1);
    }

    get isChecked() {
        return this.__isChecked.get();
    }

    set isChecked(k1) {
        this.__isChecked.set(k1);
    }

    get isWrapText() {
        return this.__isWrapText.get();
    }

    set isWrapText(j1) {
        this.__isWrapText.set(j1);
    }

    get listScale() {
        return this.__listScale.get();
    }

    set listScale(i1) {
        this.__listScale.set(i1);
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
            } else {
                this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ?
                ItemHeight.SECOND_HEIGHT :
                    (LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.composeListItem_system_icon_line_height'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }).value);
            }
        } else if (this.contentItem.description === undefined) {
            let g1 = this.contentItem.iconStyle;
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && g1 <= IconType.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            } else {
                this.itemHeight = g1 === IconType.HEAD_SCULPTURE ? ItemHeight.FOURTH_HEIGHT : APPICON_ITEMLENGTH;
            }
        } else {
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
        } else {
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
        } catch (d1) {
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
        } else if (this.operateItem?.checkbox) {
            return RIGHT_ONLY_CHECKBOX_WIDTH;
        } else if (this.operateItem?.radio) {
            return RIGHT_ONLY_RADIO_WIDTH;
        } else if (this.operateItem?.icon) {
            if (this.operateItem?.subIcon) {
                return RIGHT_ICON_SUB_ICON_WIDTH;
            }
            return RIGHT_ONLY_ICON_WIDTH;
        } else if (this.operateItem?.symbolStyle) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        } else if (this.operateItem?.image) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        } else if (this.operateItem?.arrow) {
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
        } else if (this.operateItem?.symbolStyle) {
            return FlexDirection.Row;
        } else if (this.operateItem?.image) {
            return FlexDirection.Row;
        } else if (this.operateItem?.icon && this.operateItem?.text) {
            return FlexDirection.Column;
        } else if (this.operateItem?.arrow) {
            if (!this.operateItem?.text) {
                return FlexDirection.Row;
            }
            this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
            return FlexDirection.Column;
        } else if (this.operateItem?.text) {
            return FlexDirection.Column;
        } else {
            return FlexDirection.Row;
        }
    }

    onFontSizeScaleChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
            this.containerPadding = {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level12'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
            this.containerPadding = {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level10'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level10'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
            this.containerPadding = {
                top: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                bottom: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.padding_level8'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
            };
        } else {
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
            return LengthMetrics.resource(this.isSingleLine() ? {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level1'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level8'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
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
        } else {
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
                this.zoomIn();
            });
            Stack.onBlur(() => {
                this.isFocus = false;
                this.frontColor = NORMAL_BG_COLOR;
                this.zoomOut();
            });
            Stack.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : {
                'id': -1,
                'type': 10002,
                params: ['sys.float.composeListItem_radius'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
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
            Stack.scale(ObservedObject.GetRawObject(this.listScale));
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
            Flex.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.composeListItem_radius'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
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
                    this.frontColor = w ? FOCUSED_BG_COLOR : NORMAL_BG_COLOR;
                    w ? this.zoomIn() : this.zoomOut();
                }
            });
            ViewStackProcessor.visualState('focused');
            Flex.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.composeListItem_radius'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Flex.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.composeListItem_radius'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.composeListItem_stroke_normal_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.composeListItem_stroke_normal_thickness'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
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
                                }, undefined, q, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composelistitem.ets',
                                    line: 1405,
                                    col: 11
                                });
                                ViewPU.create(s);
                                let t = () => {
                                    return {
                                        isWrapText: this.isWrapText
                                    };
                                };
                                s.paramsGenerator_ = t;
                            } else {
                                this.updateStateVarsOfChildByElmtId(q, {});
                            }
                        }, { name: 'ContentItemStruct' });
                    }
                });
            } else {
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
                                }, undefined, k, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composelistitem.ets',
                                    line: 1410,
                                    col: 11
                                });
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
                            } else {
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
            } else {
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
                                }, undefined, c, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composelistitem.ets',
                                    line: 1426,
                                    col: 11
                                });
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
                            } else {
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
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Stack.pop();
    }

    zoomIn() {
        this.listScale = {
            x: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : FOCUSED_ITEM_SCALE,
            y: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : FOCUSED_ITEM_SCALE
        };
    }

    zoomOut() {
        this.listScale = {
            x: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : RECOVER_ITEM_SCALE,
            y: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : RECOVER_ITEM_SCALE
        };
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    IconType, ComposeListItem
};