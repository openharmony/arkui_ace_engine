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

let TextModifier;
if (globalThis.__hasUIFramework__) {
    TextModifier = requireNapi('arkui.modifier').TextModifier;
} else {
    TextModifier = requireNapi('arkui.mock').TextModifier;
}

var _a;

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const arkuiNode = requireNapi('arkui.node');
const LengthMetrics = arkuiNode.LengthMetrics;
const ColorMetrics = arkuiNode.ColorMetrics;
const LengthUnit = arkuiNode.LengthUnit;
const resourceManager = requireNapi('resourceManager');
const BusinessError = requireNapi('base');
const common = requireNapi('app.ability.common');
const hilog = requireNapi('hilog');
const HashMap = requireNapi('util.HashMap');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;

const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const DEFAULT_FONT_SCALE = 1;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE_NUMBER = 16;
const LEFT_TEXT_NUMBER = 8;
const OPERATE_ITEM_LENGTH = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_arrow_height');
});
const ARROW_ICON_WIDTH = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_arrow_width');
});
const SINGLE_ICON_ZONE_SIZE = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_icon_zone_size');
});
const RIGHT_SINGLE_ICON_SIZE = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_icon_size') + 'vp';
});
const DEFAULT_FOCUS_STYLE = lazyInit(() => {
    return getResourceValue('sys.float.subheader_right_button_default_focus_style');
});
const PADDING_LEVEL_2 = 4;
const MAX_RIGHT_WIDTH = '34%';
const MIN_FONT_SIZE = 1.75;
const MIN_HOT_AREA_LENGTH = 40;
const MULTI_ICON_REGION_WIDTH = 37;
const ICON_REGION_X = -9;
const ICON_REGION_Y = -6;
const SINGLE_ICON_REGION_X = -12;
const SINGLE_ICON_NUMBER = 1;
const PADDING_LEFT = 2;

export var OperationType;
(function (m11) {
    m11[m11['TEXT_ARROW'] = 0] = 'TEXT_ARROW';
    m11[m11['BUTTON'] = 1] = 'BUTTON';
    m11[m11['ICON_GROUP'] = 2] = 'ICON_GROUP';
    m11[m11['LOADING'] = 3] = 'LOADING';
})(OperationType || (OperationType = {}));

class IconOptions {
}

class ContentIconOption {
}

class FontStyle {
    constructor() {
        this.maxLines = 0;
        this.fontWeight = 0;
    }
}

class SubHeaderTheme {
    constructor() {
        this.fontPrimaryColor = {
            'id': 125830982,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.fontSecondaryColor = {
            'id': 125830983,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.fontButtonColor = {
            'id': 125830986,
            'type': 10001,
            params: ['sys.color.font_emphasize'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.iconArrowColor = {
            'id': 125830993,
            'type': 10001,
            params: ['sys.color.icon_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.textArrowHoverBgColor = {
            'id': 125831019,
            'type': 10001,
            params: ['sys.color.interactive_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.borderFocusColor = {
            'id': 125831021,
            'type': 10001,
            params: ['sys.color.interactive_focus'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.leftIconColor = {
            'id': 125830992,
            'type': 10001,
            params: ['sys.color.icon_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
        this.rightIconColor = {
            'id': 125830991,
            'type': 10001,
            params: ['sys.color.icon_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        };
    }
}

function __Text__secondaryTitleStyles(l11) {
    Text.fontSize(`${getResourceValue('sys.float.Subtitle_S')}fp`);
    Text.fontColor(l11?.fontColor ?? {
        'id': 125830983,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
    });
    Text.fontWeight(l11?.fontWeight);
    Text.maxLines(l11?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(l11?.alignment);
}

function __Text__primaryTitleStyles(k11) {
    Text.fontSize(`${getResourceValue('sys.float.subheader_title_font_size')}fp`);
    Text.fontColor(k11?.fontColor ?? {
        'id': 125830982,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
    });
    Text.fontWeight(k11?.fontWeight);
    Text.maxLines(k11?.maxLines);
    Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    Text.align(k11?.alignment);
}

class SubHeaderModifier {
    constructor() {
        this.isAgeing = false;
    }

    applyNormalAttribute(j11) {
        if (this.isAgeing) {
            j11.width('100%');
        } else {
        }
    }
}

const RESOURCE_CACHE_MAP = new HashMap();
RESOURCE_CACHE_MAP.set('sys.float.padding_level0', { resourceId: 125830919, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level1', { resourceId: 125830920, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level2', { resourceId: 125830921, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level3', { resourceId: 125830922, defaultValue: 6 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level4', { resourceId: 125830923, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level6', { resourceId: 125830925, defaultValue: 12 });
RESOURCE_CACHE_MAP.set('sys.float.padding_level8', { resourceId: 125830927, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.margin_left', { resourceId: 125830936, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.margin_right', { resourceId: 125830937, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.outline_extra_larger', { resourceId: 125830951, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.corner_radius_level4', { resourceId: 125830909, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.Subtitle_S', { resourceId: 125830969, defaultValue: 14 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_size', { resourceId: 125834265, defaultValue: 18 });
RESOURCE_CACHE_MAP.set('sys.float.Body_L', { resourceId: 125830970, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.interactive_disable', { resourceId: 125831067, defaultValue: 0.4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_title_height', { resourceId: 125834252, defaultValue: 56 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_subtitle_height', { resourceId: 125834253, defaultValue: 56 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_double_height', { resourceId: 125834254, defaultValue: 72 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_title_font_weight', { resourceId: 125834255, defaultValue: 700 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_left_icon_size', { resourceId: 125835678, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_content_margin_start', { resourceId: 125835679, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_content_margin_end', { resourceId: 125835680, defaultValue: 16 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_content_padding', { resourceId: 125835681, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_subtitle_padding', { resourceId: 125835682, defaultValue: 12 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_select_padding', { resourceId: 125835683, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_left_icon_end_margin', { resourceId: 125835684, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_subtitle_font_weight', { resourceId: 125835685, defaultValue: 400 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_titles_space', { resourceId: 125835686, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_padding_horizontal',
    { resourceId: 125835784, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_padding_vertical', { resourceId: 125835785, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_x_offset', { resourceId: 125835786, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_radius', { resourceId: 125835787, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_default_focus_style',
    { resourceId: 125835788, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_margin_start', { resourceId: 125835789, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_button_margin_bottom', { resourceId: 125835790, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_button_margin_bottom',
    { resourceId: 125835791, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_padding_vertical', { resourceId: 125835792, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_padding_start', { resourceId: 125835793, defaultValue: 2 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_font_arrow_space', { resourceId: 125835794, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_padding_horizontal',
    { resourceId: 125835795, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_x_offset', { resourceId: 125835796, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_margin_start', { resourceId: 125835797, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_arrow_height', { resourceId: 125835798, defaultValue: 24 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_arrow_width', { resourceId: 125835799, defaultValue: 12 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_margin_bottom',
    { resourceId: 125835800, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_text_arrow_margin_bottom',
    { resourceId: 125835801, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_text_arrow_radius', { resourceId: 125835802, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_only_arrow_margin_bottom',
    { resourceId: 125835803, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_group_padding_start',
    { resourceId: 125835804, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_group_margin_bottom',
    { resourceId: 125835805, defaultValue: 6 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_icon_group_margin_bottom',
    { resourceId: 125835806, defaultValue: 6 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_group_x_offset', { resourceId: 125835807, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_radius', { resourceId: 125835808, defaultValue: 8 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_image_radius', { resourceId: 125835809, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_image_padding', { resourceId: 125835810, defaultValue: 0 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_zone_size', { resourceId: 125835811, defaultValue: 28 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_icon_size', { resourceId: 125835812, defaultValue: 24 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_loading_padding_bottom', { resourceId: 125835813, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_single_right_loading_padding_bottom',
    { resourceId: 125835814, defaultValue: 4 });
RESOURCE_CACHE_MAP.set('sys.float.subheader_right_loading_margin_start', { resourceId: 125835815, defaultValue: 8 });

export class SubHeader extends ViewPU {
    constructor(d11, e11, f11, g11 = -1, h11 = undefined, i11) {
        super(d11, f11, g11, i11);
        if (typeof h11 === 'function') {
            this.paramsGenerator_ = h11;
        }
        this.__icon = new SynchedPropertyObjectOneWayPU(e11.icon, this, 'icon');
        this.iconSymbolOptions = null;
        this.__primaryTitle = new SynchedPropertyObjectOneWayPU(e11.primaryTitle, this, 'primaryTitle');
        this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, 'primaryTitleModifier');
        this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(e11.secondaryTitle, this, 'secondaryTitle');
        this.__secondaryTitleModifier =
            new ObservedPropertyObjectPU(new TextModifier(), this, 'secondaryTitleModifier');
        this.__subHeaderModifier = new ObservedPropertyObjectPU(new SubHeaderModifier(), this, 'subHeaderModifier');
        this.select = null;
        this.__operationType = new SynchedPropertySimpleOneWayPU(e11.operationType, this, 'operationType');
        this.operationItem = null;
        this.operationSymbolOptions = null;
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__ageing = new ObservedPropertySimplePU(true, this, 'ageing');
        this.__textArrowBgColor = new ObservedPropertyObjectPU({
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, this, 'textArrowBgColor');
        this.__buttonBgColor = new ObservedPropertyObjectPU({
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, this, 'buttonBgColor');
        this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, 'selectedIndex');
        this.__selectValue = new ObservedPropertyObjectPU('', this, 'selectValue');
        this.titleBuilder = undefined;
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(e11.contentMargin, this, 'contentMargin');
        this.__contentPadding = new SynchedPropertyObjectOneWayPU(e11.contentPadding, this, 'contentPadding');
        this.__titleAccessibilityText =
            new SynchedPropertyObjectOneWayPU(e11.titleAccessibilityText, this, 'titleAccessibilityText');
        this.subHeaderMargin = {
            start: LengthMetrics.vp(getResourceValue('sys.float.subheader_content_margin_start')),
            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_content_margin_end')),
        };
        this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, 'subHeaderTheme');
        this.addProvidedVar('subHeaderTheme', this.__subHeaderTheme, false);
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
        this.setInitiallyProvidedValue(e11);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(c11) {
        if (c11.icon === undefined) {
            this.__icon.set(null);
        }
        if (c11.iconSymbolOptions !== undefined) {
            this.iconSymbolOptions = c11.iconSymbolOptions;
        }
        if (c11.primaryTitle === undefined) {
            this.__primaryTitle.set(null);
        }
        if (c11.primaryTitleModifier !== undefined) {
            this.primaryTitleModifier = c11.primaryTitleModifier;
        }
        if (c11.secondaryTitle === undefined) {
            this.__secondaryTitle.set(null);
        }
        if (c11.secondaryTitleModifier !== undefined) {
            this.secondaryTitleModifier = c11.secondaryTitleModifier;
        }
        if (c11.subHeaderModifier !== undefined) {
            this.subHeaderModifier = c11.subHeaderModifier;
        }
        if (c11.select !== undefined) {
            this.select = c11.select;
        }
        if (c11.operationType === undefined) {
            this.__operationType.set(OperationType.BUTTON);
        }
        if (c11.operationItem !== undefined) {
            this.operationItem = c11.operationItem;
        }
        if (c11.operationSymbolOptions !== undefined) {
            this.operationSymbolOptions = c11.operationSymbolOptions;
        }
        if (c11.fontSize !== undefined) {
            this.fontSize = c11.fontSize;
        }
        if (c11.ageing !== undefined) {
            this.ageing = c11.ageing;
        }
        if (c11.textArrowBgColor !== undefined) {
            this.textArrowBgColor = c11.textArrowBgColor;
        }
        if (c11.buttonBgColor !== undefined) {
            this.buttonBgColor = c11.buttonBgColor;
        }
        if (c11.selectedIndex !== undefined) {
            this.selectedIndex = c11.selectedIndex;
        }
        if (c11.selectValue !== undefined) {
            this.selectValue = c11.selectValue;
        }
        if (c11.titleBuilder !== undefined) {
            this.titleBuilder = c11.titleBuilder;
        }
        if (c11.subHeaderMargin !== undefined) {
            this.subHeaderMargin = c11.subHeaderMargin;
        }
        if (c11.subHeaderTheme !== undefined) {
            this.subHeaderTheme = c11.subHeaderTheme;
        }
        if (c11.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c11.isFollowingSystemFontScale;
        }
        if (c11.appMaxFontScale !== undefined) {
            this.appMaxFontScale = c11.appMaxFontScale;
        }
    }

    updateStateVars(b11) {
        this.__icon.reset(b11.icon);
        this.__primaryTitle.reset(b11.primaryTitle);
        this.__secondaryTitle.reset(b11.secondaryTitle);
        this.__operationType.reset(b11.operationType);
        this.__contentMargin.reset(b11.contentMargin);
        this.__contentPadding.reset(b11.contentPadding);
        this.__titleAccessibilityText.reset(b11.titleAccessibilityText);
    }

    purgeVariableDependenciesOnElmtId(a11) {
        this.__icon.purgeDependencyOnElmtId(a11);
        this.__primaryTitle.purgeDependencyOnElmtId(a11);
        this.__primaryTitleModifier.purgeDependencyOnElmtId(a11);
        this.__secondaryTitle.purgeDependencyOnElmtId(a11);
        this.__secondaryTitleModifier.purgeDependencyOnElmtId(a11);
        this.__subHeaderModifier.purgeDependencyOnElmtId(a11);
        this.__operationType.purgeDependencyOnElmtId(a11);
        this.__fontSize.purgeDependencyOnElmtId(a11);
        this.__ageing.purgeDependencyOnElmtId(a11);
        this.__textArrowBgColor.purgeDependencyOnElmtId(a11);
        this.__buttonBgColor.purgeDependencyOnElmtId(a11);
        this.__selectedIndex.purgeDependencyOnElmtId(a11);
        this.__selectValue.purgeDependencyOnElmtId(a11);
        this.__contentMargin.purgeDependencyOnElmtId(a11);
        this.__contentPadding.purgeDependencyOnElmtId(a11);
        this.__titleAccessibilityText.purgeDependencyOnElmtId(a11);
        this.__subHeaderTheme.purgeDependencyOnElmtId(a11);
    }

    aboutToBeDeleted() {
        this.__icon.aboutToBeDeleted();
        this.__primaryTitle.aboutToBeDeleted();
        this.__primaryTitleModifier.aboutToBeDeleted();
        this.__secondaryTitle.aboutToBeDeleted();
        this.__secondaryTitleModifier.aboutToBeDeleted();
        this.__subHeaderModifier.aboutToBeDeleted();
        this.__operationType.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__ageing.aboutToBeDeleted();
        this.__textArrowBgColor.aboutToBeDeleted();
        this.__buttonBgColor.aboutToBeDeleted();
        this.__selectedIndex.aboutToBeDeleted();
        this.__selectValue.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__contentPadding.aboutToBeDeleted();
        this.__titleAccessibilityText.aboutToBeDeleted();
        this.__subHeaderTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get icon() {
        return this.__icon.get();
    }

    set icon(z10) {
        this.__icon.set(z10);
    }

    get primaryTitle() {
        return this.__primaryTitle.get();
    }

    set primaryTitle(y10) {
        this.__primaryTitle.set(y10);
    }

    get primaryTitleModifier() {
        return this.__primaryTitleModifier.get();
    }

    set primaryTitleModifier(x10) {
        this.__primaryTitleModifier.set(x10);
    }

    get secondaryTitle() {
        return this.__secondaryTitle.get();
    }

    set secondaryTitle(w10) {
        this.__secondaryTitle.set(w10);
    }

    get secondaryTitleModifier() {
        return this.__secondaryTitleModifier.get();
    }

    set secondaryTitleModifier(v10) {
        this.__secondaryTitleModifier.set(v10);
    }

    get subHeaderModifier() {
        return this.__subHeaderModifier.get();
    }

    set subHeaderModifier(u10) {
        this.__subHeaderModifier.set(u10);
    }

    get operationType() {
        return this.__operationType.get();
    }

    set operationType(t10) {
        this.__operationType.set(t10);
    }

    get fontSize() {
        return this.__fontSize.get();
    }

    set fontSize(s10) {
        this.__fontSize.set(s10);
    }

    get ageing() {
        return this.__ageing.get();
    }

    set ageing(r10) {
        this.__ageing.set(r10);
    }

    get textArrowBgColor() {
        return this.__textArrowBgColor.get();
    }

    set textArrowBgColor(q10) {
        this.__textArrowBgColor.set(q10);
    }

    get buttonBgColor() {
        return this.__buttonBgColor.get();
    }

    set buttonBgColor(p10) {
        this.__buttonBgColor.set(p10);
    }

    get selectedIndex() {
        return this.__selectedIndex.get();
    }

    set selectedIndex(o10) {
        this.__selectedIndex.set(o10);
    }

    get selectValue() {
        return this.__selectValue.get();
    }

    set selectValue(n10) {
        this.__selectValue.set(n10);
    }

    get contentMargin() {
        return this.__contentMargin.get();
    }

    set contentMargin(m10) {
        this.__contentMargin.set(m10);
    }

    get contentPadding() {
        return this.__contentPadding.get();
    }

    set contentPadding(l10) {
        this.__contentPadding.set(l10);
    }

    get titleAccessibilityText() {
        return this.__titleAccessibilityText.get();
    }

    set titleAccessibilityText(k10) {
        this.__titleAccessibilityText.set(k10);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(j10) {
        this.__subHeaderTheme.set(j10);
    }

    onWillApplyTheme(i10) {
        this.subHeaderTheme.fontPrimaryColor = i10.colors.fontPrimary;
        this.subHeaderTheme.fontSecondaryColor = i10.colors.fontSecondary;
        this.subHeaderTheme.fontButtonColor = i10.colors.fontEmphasize;
        this.subHeaderTheme.iconArrowColor = i10.colors.iconTertiary;
        this.subHeaderTheme.textArrowHoverBgColor = i10.colors.interactiveHover;
        this.subHeaderTheme.borderFocusColor = i10.colors.interactiveFocus;
        this.subHeaderTheme.leftIconColor = i10.colors.iconSecondary;
        this.subHeaderTheme.rightIconColor = i10.colors.iconPrimary;
    }

    updateFontScale() {
        try {
            let g10 = this.getUIContext();
            let h10 = g10?.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(h10, this.appMaxFontScale);
        } catch (d10) {
            let e10 = d10.code;
            let f10 = d10.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${e10}, message: ${f10}`);
            return 1;
        }
    }

    async aboutToAppear() {
        let c10 = this.getUIContext();
        this.isFollowingSystemFontScale = c10.isFollowingSystemFontScale();
        this.appMaxFontScale = c10.getMaxFontScale();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        if (this.select) {
            this.selectedIndex = this.select.selected;
            this.selectValue = this.select.value;
        }
    }

    isSuitableAging() {
        return (this.fontSize >= MIN_FONT_SIZE) && ((this.operationType === OperationType.TEXT_ARROW) ||
            this.operationType === OperationType.BUTTON) && this.operationItem &&
            (this.operationItem?.length > 0) && this.operationItem[0].value !== '';
    }

    isLeftAreaAccessibilityGroup() {
        if (this.titleBuilder || this.secondaryTitle) {
            return true;
        }
        if (this.select) {
            return false;
        }
        return true;
    }

    getTitleAccessibilityText() {
        if (!this.select && this.titleAccessibilityText) {
            return this.titleAccessibilityText;
        }
        return '';
    }

    initialRender() {
        this.observeComponentCreation2((o9, p9) => {
            If.create();
            if (this.isSuitableAging()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a10, b10) => {
                        Column.create();
                        Column.constraintSize({ minHeight: this.getMinHeight() });
                        Column.padding(this.getAreaPadding());
                        Column.alignItems(HorizontalAlign.Start);
                    }, Column);
                    this.observeComponentCreation2((y9, z9) => {
                        Row.create();
                        Row.margin({
                            top: LengthMetrics.vp(getResourceValue('sys.float.padding_level8')),
                            bottom: LengthMetrics.vp(getResourceValue('sys.float.padding_level1')),
                        });
                        Row.padding({
                            start: this.contentMargin ? this.contentMargin.start :
                                LengthMetrics.vp(getResourceValue('sys.float.margin_left')),
                            end: this.contentMargin ? this.contentMargin.end :
                                LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Row.width('100%');
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                        Row.accessibilityText(this.getTitleAccessibilityText());
                        Row.accessibilityRole(this.primaryTitle || this.secondaryTitle ?
                            AccessibilityRoleType.TITLE_BAR : undefined);
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((w9, x9) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParentAging.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((u9, v9) => {
                        Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
                        Flex.constraintSize({ minHeight: this.getMinHeight() });
                        Flex.margin(this.contentMargin ?? this.subHeaderMargin);
                        Flex.padding(this.getAreaPadding());
                    }, Flex);
                    this.observeComponentCreation2((s9, t9) => {
                        Row.create();
                        Row.margin({
                            top: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level8') : '',
                            bottom: this.fontSize >= MIN_FONT_SIZE ? getResourceValue('sys.float.padding_level4') : '',
                        });
                        Row.width('100%');
                        Row.flexShrink(1);
                        Row.accessibilityGroup(this.isLeftAreaAccessibilityGroup());
                        Row.accessibilityText(this.getTitleAccessibilityText());
                        Row.accessibilityRole(this.primaryTitle || this.secondaryTitle ?
                            AccessibilityRoleType.TITLE_BAR : undefined);
                    }, Row);
                    this.leftArea.bind(this)();
                    Row.pop();
                    this.observeComponentCreation2((q9, r9) => {
                        If.create();
                        if (this.isRightAreaExists()) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.rightAreaParent.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Flex.pop();
                });
            }
        }, If);
        If.pop();
    }

    isRightAreaExists() {
        if (this.operationItem && this.operationItem.length > 0) {
            return true;
        }
        if (this.operationType === OperationType.LOADING) {
            return true;
        }
        return false;
    }

    getRightAreaAccessibilityLevel() {
        if (this.operationItem[0].accessibilityLevel && this.operationItem[0].accessibilityLevel !== '') {
            return this.operationItem[0].accessibilityLevel;
        }
        return 'yes';
    }

    getRightAreaAccessibilityText() {
        if (!this.operationItem || this.operationItem.length <= 0) {
            return '';
        }
        if (this.operationItem[0].accessibilityText && this.operationItem[0].accessibilityText !== '') {
            return this.operationItem[0].accessibilityText;
        } else {
            if (this.operationType === OperationType.TEXT_ARROW && this.operationItem[0].value.toString().length <= 0) {
                return Util.getStringByResource(125833704, '');
            }
        }
        return '';
    }

    getAccessibilityDescription() {
        if (!this.operationItem || this.operationItem.length <= 0) {
            return '';
        }
        if (this.operationItem[0].accessibilityDescription && this.operationItem[0].accessibilityDescription !== '') {
            return this.operationItem[0].accessibilityDescription;
        }
        return '';
    }

    rightAreaParentAging(d9 = null) {
        this.observeComponentCreation2((e9, f9) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k9, l9) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(this.operationItem ? true : false);
                        Button.align(Alignment.Start);
                        Button.onKeyEvent((n9) => {
                            if (!n9) {
                                return;
                            }
                            if ((n9.keyCode === KeyCode.KEYCODE_SPACE || n9.keyCode === KeyCode.KEYCODE_ENTER) &&
                                n9.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                n9.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((m9) => {
                            if (m9.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (m9.type === TouchType.Up || m9.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                        });
                        Button.margin({
                            bottom: getResourceValue('sys.float.padding_level4'),
                        });
                        Button.padding({
                            start: LengthMetrics.vp((this.contentMargin ?
                                (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                                getResourceValue('sys.float.margin_left')) - PADDING_LEFT),
                            end: this.contentMargin ? this.contentMargin.end :
                                LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Button.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                            this.getRightAreaAccessibilityLevel() : 'no');
                        Button.backgroundColor({
                            'id': 125829134,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Button.hoverEffect(HoverEffect.None);
                        Button.accessibilityGroup(true);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((g9, h9) => {
                        Row.create();
                        Row.focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true :
                            false);
                        Row.justifyContent(FlexAlign.Start);
                        Row.onKeyEvent((j9) => {
                            if (!j9) {
                                return;
                            }
                            if ((j9.keyCode === KeyCode.KEYCODE_SPACE || j9.keyCode === KeyCode.KEYCODE_ENTER) &&
                                j9.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                j9.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((i9) => {
                            if (i9.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (i9.type === TouchType.Up || i9.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                        });
                        Row.margin({
                            bottom: getResourceValue('sys.float.padding_level4'),
                        });
                        Row.padding({
                            start: LengthMetrics.vp((this.contentMargin ?
                                (this.contentMargin.start ? this.contentMargin.start.value : 0) :
                                getResourceValue('sys.float.margin_left')) - PADDING_LEFT),
                            end: this.contentMargin ? this.contentMargin.end :
                                LengthMetrics.vp(getResourceValue('sys.float.margin_right')),
                        });
                        Row.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                            this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    rightAreaParent(s8 = null) {
        this.observeComponentCreation2((t8, u8) => {
            If.create();
            if (this.operationType === OperationType.BUTTON || this.operationType === OperationType.TEXT_ARROW) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z8, a9) => {
                        Button.createWithChild({
                            type: ButtonType.Normal,
                            buttonStyle: ButtonStyleMode.TEXTUAL,
                            stateEffect: false
                        });
                        Button.focusable(this.operationItem ? true : false);
                        Button.margin(INDEX_ZERO);
                        Button.padding(INDEX_ZERO);
                        Button.align(Alignment.BottomEnd);
                        Button.onKeyEvent((c9) => {
                            if (!c9) {
                                return;
                            }
                            if ((c9.keyCode === KeyCode.KEYCODE_SPACE || c9.keyCode === KeyCode.KEYCODE_ENTER) &&
                                c9.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                c9.stopPropagation();
                            }
                        });
                        Button.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Button.onTouch((b9) => {
                            if (b9.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (b9.type === TouchType.Up || b9.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                        });
                        Button.constraintSize({
                            maxWidth: this.getRightAreaMaxWidth(),
                            minWidth: this.getRightAreaMinWidth(),
                            minHeight: MIN_HOT_AREA_LENGTH,
                        });
                        Button.flexShrink(0);
                        Button.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                            this.getRightAreaAccessibilityLevel() : 'no');
                        Button.hoverEffect(HoverEffect.None);
                        Button.backgroundColor({
                            'id': 125829134,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_sub_background_transparent'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        Button.accessibilityGroup(true);
                        Button.accessibilityText(this.getRightAreaAccessibilityText());
                        Button.accessibilityDescription(this.getAccessibilityDescription());
                    }, Button);
                    this.rightArea.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((v8, w8) => {
                        Row.create();
                        Row.focusable(this.operationItem && this.operationType !== OperationType.LOADING ? true :
                            false);
                        Row.justifyContent(FlexAlign.End);
                        Row.alignItems(VerticalAlign.Bottom);
                        Row.onKeyEvent((y8) => {
                            if (!y8) {
                                return;
                            }
                            if ((y8.keyCode === KeyCode.KEYCODE_SPACE || y8.keyCode === KeyCode.KEYCODE_ENTER) &&
                                y8.type === KeyType.Down) {
                                if ((this.operationType === OperationType.TEXT_ARROW ||
                                    this.operationType === OperationType.BUTTON) &&
                                this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                    this.operationItem[0].action();
                                }
                                y8.stopPropagation();
                            }
                        });
                        Row.onClick(() => {
                            if ((this.operationType === OperationType.TEXT_ARROW ||
                                this.operationType === OperationType.BUTTON) &&
                            this.operationItem && this.operationItem.length > 0 && this.operationItem[0].action) {
                                this.operationItem[0].action();
                            }
                        });
                        Row.onTouch((x8) => {
                            if (x8.type === TouchType.Down) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125831020,
                                        'type': 10001,
                                        params: ['sys.color.interactive_pressed'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                            if (x8.type === TouchType.Up || x8.type === TouchType.Cancel) {
                                if (this.operationType === OperationType.TEXT_ARROW) {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                                if (this.operationType === OperationType.BUTTON) {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }
                        });
                        Row.constraintSize({
                            maxWidth: this.getRightAreaMaxWidth(),
                            minWidth: this.getRightAreaMinWidth(),
                            minHeight: MIN_HOT_AREA_LENGTH,
                        });
                        Row.flexShrink(0);
                        Row.accessibilityLevel(this.operationType === OperationType.BUTTON ||
                            this.operationType === OperationType.TEXT_ARROW ?
                            this.getRightAreaAccessibilityLevel() : 'no');
                    }, Row);
                    this.rightArea.bind(this)();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    onMeasureSize(m8, n8, o8) {
        let p8 = { width: m8?.width ?? 0, height: m8?.height ?? 0 };
        let q8 = this.getUIContext()?.getHostContext();
        this.fontSize = this.updateFontScale();
        if (this.isSuitableAging()) {
            this.ageing = true;
            this.subHeaderModifier.isAgeing = this.ageing;
        } else {
            this.ageing = false;
            this.subHeaderModifier.isAgeing = this.ageing;
        }
        n8.forEach((r8) => {
            o8.minHeight = Math.min(Number(this.getMinHeight()), Number(o8?.maxHeight ?? 0));
            p8.height = r8?.measure(o8)?.height ?? 0;
            p8.width = Number(o8?.maxWidth ?? 0);
        });
        return p8;
    }

    onPlaceChildren(i8, j8, k8) {
        j8.forEach((l8) => {
            l8?.layout({ x: 0, y: 0 });
        });
    }

    getRightAreaMaxWidth() {
        if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
            return '100%';
        }
        return MAX_RIGHT_WIDTH;
    }

    getRightAreaMinWidth() {
        if (this.operationItem && this.operationItem.length > 0) {
            return MIN_HOT_AREA_LENGTH;
        }
        return 0;
    }

    getMinHeight() {
        if (this.secondaryTitle && this.icon) {
            return getResourceValue('sys.float.subheader_single_subtitle_height');
        } else if (this.secondaryTitle && this.primaryTitle) {
            return getResourceValue('sys.float.subheader_double_height');
        } else if (this.primaryTitle || this.select) {
            return getResourceValue('sys.float.subheader_single_title_height');
        }
        return getResourceValue('sys.float.subheader_single_subtitle_height');
    }

    getTextArrowPaddingLeft() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.vp(getResourceValue('sys.float.subheader_right_text_padding_start'));
        }
        return LengthMetrics.vp(getResourceValue('sys.float.padding_level0'));
    }

    getTextArrowMarginRight() {
        if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
            return LengthMetrics.vp(getResourceValue('sys.float.subheader_right_font_arrow_space') +
            ARROW_ICON_WIDTH());
        }
        return LengthMetrics.vp(ARROW_ICON_WIDTH());
    }

    getAreaPadding() {
        if (this.contentPadding) {
            return this.contentPadding;
        }
        let h8 = {};
        if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
            (!this.primaryTitle && this.secondaryTitle))) {
            h8 = {
                start: LengthMetrics.vp(getResourceValue('sys.float.subheader_single_subtitle_padding')),
                end: LengthMetrics.vp(getResourceValue('sys.float.subheader_single_subtitle_padding')),
            };
        } else if (this.select) {
            h8 = {
                top: LengthMetrics.vp(getResourceValue('sys.float.subheader_select_padding')),
                bottom: LengthMetrics.vp(getResourceValue('sys.float.subheader_select_padding')),
            };
        }
        return h8;
    }

    leftArea(e8 = null) {
        this.observeComponentCreation2((f8, g8) => {
            If.create();
            if (this.titleBuilder) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.titleBuilder.bind(this)();
                });
            } else if (this.secondaryTitle && this.icon) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy('IconSecondaryTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle']),
                        iconOptions: () => ({
                            icon: this.icon,
                            symbolicIconOption: this.iconSymbolOptions,
                        })
                    }));
                });
            } else if (this.secondaryTitle && this.primaryTitle) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.SubTitleStyle.bind(this)(makeBuilderParameterProxy('SubTitleStyle', {
                        content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']),
                        subContent: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
                    }));
                });
            } else if (this.secondaryTitle) {
                this.ifElseBranchUpdateFunction(3, () => {
                    this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy('SecondTitleStyle', {
                        content: () => (this['__secondaryTitle'] ? this['__secondaryTitle'] : this['secondaryTitle'])
                    }));
                });
            } else if (this.select) {
                this.ifElseBranchUpdateFunction(4, () => {
                    this.SelectStyle.bind(this)(this.select);
                });
            } else if (this.primaryTitle) {
                this.ifElseBranchUpdateFunction(5, () => {
                    this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy('PrimaryTitleStyle',
                        { content: () => (this['__primaryTitle'] ? this['__primaryTitle'] : this['primaryTitle']) }));
                });
            } else {
                this.ifElseBranchUpdateFunction(6, () => {
                    this.dummyFunction.bind(this)();
                });
            }
        }, If);
        If.pop();
    }

    rightArea(t7 = null) {
        this.observeComponentCreation2((c8, d8) => {
            If.create();
            if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0]);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((a8, b8) => {
            If.create();
            if (this.operationType === OperationType.TEXT_ARROW &&
                (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.TextArrowStyle.bind(this)(this.operationItem[0]);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((y7, z7) => {
            If.create();
            if (this.operationType === OperationType.ICON_GROUP &&
                (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconGroupStyle.bind(this)(this.operationItem);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((w7, x7) => {
            If.create();
            if (this.operationType === OperationType.LOADING) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.LoadingProcessStyle.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((u7, v7) => {
            If.create();
            if (this.operationType === undefined && (this.operationItem && this.operationItem.length > 0)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ButtonStyle.bind(this)(this.operationItem[0]);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    IconSecondaryTitleStyle(h7, i7 = null) {
        this.observeComponentCreation2((r7, s7) => {
            Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
            Flex.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
        }, Flex);
        this.observeComponentCreation2((l7, m7) => {
            If.create();
            if (Util.isSymbolResource(h7.iconOptions?.icon)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p7, q7) => {
                        SymbolGlyph.create(h7.iconOptions?.icon);
                        SymbolGlyph.fontSize(h7.iconOptions?.symbolicIconOption?.fontSize ?
                            Util.symbolFontSize(h7.iconOptions?.symbolicIconOption?.fontSize) :
                            getResourceValue('sys.float.subheader_left_icon_size') + 'vp');
                        SymbolGlyph.fontColor(h7.iconOptions?.symbolicIconOption?.fontColor ??
                            [this.subHeaderTheme.leftIconColor]);
                        SymbolGlyph.fontWeight(h7.iconOptions?.symbolicIconOption?.fontWeight);
                        SymbolGlyph.renderingStrategy(h7.iconOptions?.symbolicIconOption?.renderingStrategy);
                        SymbolGlyph.effectStrategy(h7.iconOptions?.symbolicIconOption?.effectStrategy);
                        SymbolGlyph.margin({
                            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_left_icon_end_margin'))
                        });
                        SymbolGlyph.flexShrink(0);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((n7, o7) => {
                        Image.create(h7.iconOptions?.icon);
                        Image.fillColor(this.subHeaderTheme.leftIconColor);
                        Image.width(getResourceValue('sys.float.subheader_left_icon_size') + 'vp');
                        Image.height(getResourceValue('sys.float.subheader_left_icon_size') + 'vp');
                        Image.margin({
                            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_left_icon_end_margin'))
                        });
                        Image.draggable(false);
                        Image.flexShrink(0);
                    }, Image);
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((j7, k7) => {
            Text.create(h7.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.flexShrink(1);
        }, Text);
        Text.pop();
        Flex.pop();
    }

    SubTitleStyle(z6, a7 = null) {
        this.observeComponentCreation2((f7, g7) => {
            Column.create();
            Column.width('100%');
            Column.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((d7, e7) => {
            Text.create(z6.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
        }, Text);
        Text.pop();
        this.observeComponentCreation2((b7, c7) => {
            Text.create(z6.subContent);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: getResourceValue('sys.float.subheader_subtitle_font_weight'),
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.margin({
                top: getResourceValue('sys.float.subheader_titles_space'),
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
        }, Text);
        Text.pop();
        Column.pop();
    }

    SecondTitleStyle(v6, w6 = null) {
        this.observeComponentCreation2((x6, y6) => {
            Text.create(v6.content);
            __Text__secondaryTitleStyles({
                maxLines: DOUBLE_LINE_NUM,
                fontWeight: FontWeight.Medium,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
            Text.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level6')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
        }, Text);
        Text.pop();
    }

    SelectStyle(p6, q6 = null) {
        this.observeComponentCreation2((r6, s6) => {
            Select.create(p6.options);
            Select.height('auto');
            Select.width('auto');
            Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
            Select.value(ObservedObject.GetRawObject(this.selectValue));
            Select.defaultFocus(p6.defaultFocus);
            Select.onSelect((t6, u6) => {
                this.selectedIndex = t6;
                if (u6) {
                    this.selectValue = u6;
                }
                if (p6.onSelect) {
                    p6.onSelect(t6, u6);
                }
            });
            Select.font({
                size: `${getResourceValue('sys.float.Body_L')}fp`,
                weight: FontWeight.Medium,
            });
        }, Select);
        Select.pop();
    }

    PrimaryTitleStyle(l6, m6 = null) {
        this.observeComponentCreation2((n6, o6) => {
            Text.create(l6.content);
            __Text__primaryTitleStyles({
                fontWeight: getResourceValue('sys.float.subheader_title_font_weight'),
                maxLines: DOUBLE_LINE_NUM,
                alignment: Alignment.Start,
                fontColor: this.subHeaderTheme.fontPrimaryColor,
            });
            Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
            Text.padding({
                end: LengthMetrics.vp(getResourceValue('sys.float.padding_level0')),
                top: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
                bottom: this.fontSize >= MIN_FONT_SIZE ? LengthMetrics.vp(getResourceValue('sys.float.padding_level0'))
                    : LengthMetrics.vp(getResourceValue('sys.float.subheader_content_padding')),
            });
        }, Text);
        Text.pop();
    }

    ButtonStyle(b6, c6 = null) {
        this.observeComponentCreation2((d6, e6) => {
            If.create();
            if (b6) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h6, i6) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.padding({
                            start: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_horizontal')),
                            end: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_horizontal')),
                            top: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_vertical')),
                            bottom: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_padding_vertical')),
                        });
                        Button.margin({
                            start: this.ageing ?
                                LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.padding_level0')).value +
                                this.leftIconMargin().value) :
                                LengthMetrics.vp(LengthMetrics.vp(getResourceValue('sys.float.subheader_right_button_margin_start'))
                                    .value +
                                this.leftIconMargin().value),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                (this.secondaryTitle && this.primaryTitle ?
                                    getResourceValue('sys.float.subheader_right_button_margin_bottom') :
                                    getResourceValue('sys.float.subheader_single_right_button_margin_bottom'))),
                        });
                        Button.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
                        Button.constraintSize({ minHeight: OPERATE_ITEM_LENGTH() });
                        Button.align(Alignment.End);
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_button_radius'));
                        Button.offset({ x: getResourceValue('sys.float.subheader_right_button_x_offset') });
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((k6) => {
                                if (k6) {
                                    this.buttonBgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.buttonBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        Button.onHover((j6) => {
                            if (j6) {
                                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            } else {
                                this.buttonBgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState();
                    }, Button);
                    this.observeComponentCreation2((f6, g6) => {
                        Text.create(b6.value);
                        __Text__secondaryTitleStyles({
                            fontWeight: FontWeight.Medium,
                            maxLines: DOUBLE_LINE_NUM,
                            fontColor: this.subHeaderTheme.fontButtonColor,
                        });
                        Text.defaultFocus(b6.defaultFocus);
                        Text.focusable(true);
                    }, Text);
                    Text.pop();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    leftIconMargin() {
        if (this.titleBuilder) {
            return LengthMetrics.vp(0);
        }
        if (this.icon && Util.isSymbolResource(this.icon)) {
            return this.ageing ? LengthMetrics.vp((this.iconSymbolOptions?.fontSize ?
                Util.numberToSize(this.iconSymbolOptions?.fontSize) : LEFT_ICON_SIZE_NUMBER) +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        } else {
            return (this.ageing && this.icon) ? LengthMetrics.vp(LEFT_ICON_SIZE_NUMBER +
                LEFT_TEXT_NUMBER) : LengthMetrics.vp(0);
        }
    }

    TextStyle(t5, u5 = null) {
        this.observeComponentCreation2((z5, a6) => {
            Row.create();
            Row.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.subHeaderModifier));
            Row.alignItems(VerticalAlign.Center);
            Row.focusable(true);
            Row.constraintSize({ minHeight: OPERATE_ITEM_LENGTH() });
            Row.padding({
                start: this.getTextArrowPaddingLeft(),
                top: this.ageing ? LengthMetrics.vp(0) :
                    LengthMetrics.vp(getResourceValue('sys.float.subheader_right_text_padding_vertical')),
                bottom: this.ageing ? LengthMetrics.vp(0) :
                    LengthMetrics.vp(getResourceValue('sys.float.subheader_right_text_padding_vertical')),
            });
        }, Row);
        this.observeComponentCreation2((v5, w5) => {
            If.create();
            if (t5) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x5, y5) => {
                        Text.create(t5.value);
                        __Text__secondaryTitleStyles({
                            maxLines: DOUBLE_LINE_NUM,
                            fontWeight: FontWeight.Regular,
                            alignment: Alignment.End,
                            fontColor: this.subHeaderTheme.fontSecondaryColor,
                        });
                        Text.focusable(true);
                        Text.defaultFocus(t5.defaultFocus);
                        Text.margin({
                            end: this.getTextArrowMarginRight(),
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
        Row.pop();
    }

    ArrowStyle(o5 = null) {
        this.observeComponentCreation2((r5, s5) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
        }, Row);
        this.observeComponentCreation2((p5, q5) => {
            SymbolGlyph.create({
                'id': 125832664,
                'type': 40000,
                params: ['sys.symbol.chevron_right'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
            SymbolGlyph.fontSize(OPERATE_ITEM_LENGTH() + 'vp');
            SymbolGlyph.fontColor([this.subHeaderTheme.iconArrowColor]);
            SymbolGlyph.draggable(false);
            SymbolGlyph.width(ARROW_ICON_WIDTH());
            SymbolGlyph.height(OPERATE_ITEM_LENGTH());
        }, SymbolGlyph);
        Row.pop();
    }

    TextArrowStyle(e4, f4 = null) {
        this.observeComponentCreation2((g4, h4) => {
            If.create();
            if (e4 && e4.value && e4.value.toString().length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m5, n5) => {
                        Stack.create();
                        Stack.focusable(true);
                        Stack.align(this.ageing ? Alignment.Start : Alignment.End);
                        Stack.margin({
                            start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                getResourceValue('sys.float.subheader_right_text_arrow_margin_start')),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                (this.secondaryTitle && this.primaryTitle ?
                                    getResourceValue('sys.float.subheader_right_text_arrow_margin_bottom') :
                                    getResourceValue('sys.float.subheader_single_right_text_arrow_margin_bottom'))),
                        });
                    }, Stack);
                    this.observeComponentCreation2((i5, j5) => {
                        Button.createWithChild({
                            type: ButtonType.Normal,
                            buttonStyle: ButtonStyleMode.TEXTUAL,
                            stateEffect: false
                        });
                        Button.padding({
                            top: INDEX_ZERO,
                            bottom: INDEX_ZERO,
                            left: getResourceValue('sys.float.subheader_right_text_arrow_padding_horizontal'),
                            right: getResourceValue('sys.float.subheader_right_text_arrow_padding_horizontal'),
                        });
                        Button.margin({ start: this.leftIconMargin() });
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_text_arrow_radius'));
                        Button.offset({ x: getResourceValue('sys.float.subheader_right_text_arrow_x_offset') });
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((l5) => {
                                if (l5) {
                                    this.textArrowBgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState();
                        Button.onHover((k5) => {
                            if (k5) {
                                this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            } else {
                                this.textArrowBgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                    }, Button);
                    {
                        this.observeComponentCreation2((q4, r4) => {
                            if (r4) {
                                let s4 = new TextArrowLayout(this, {
                                    textArrowBuilder: () => {
                                        this.observeComponentCreation2((b5, c5) => {
                                            ForEach.create();
                                            const d5 = e5 => {
                                                const f5 = e5;
                                                this.observeComponentCreation2((g5, h5) => {
                                                    If.create();
                                                    if (f5 === INDEX_ZERO) {
                                                        this.ifElseBranchUpdateFunction(0, () => {
                                                            this.TextStyle.bind(this)(e4);
                                                        });
                                                    } else {
                                                        this.ifElseBranchUpdateFunction(1, () => {
                                                            this.ArrowStyle.bind(this)();
                                                        });
                                                    }
                                                }, If);
                                                If.pop();
                                            };
                                            this.forEachUpdateFunction(b5, [INDEX_ZERO, INDEX_ONE], d5);
                                        }, ForEach);
                                        ForEach.pop();
                                    }
                                }, undefined, q4, () => {
                                }, { page: 'library/src/main/ets/components/subheader.ets', line: 979, col: 11 });
                                ViewPU.create(s4);
                                let t4 = () => {
                                    return {
                                        textArrowBuilder: () => {
                                            this.observeComponentCreation2((u4, v4) => {
                                                ForEach.create();
                                                const w4 = x4 => {
                                                    const y4 = x4;
                                                    this.observeComponentCreation2((z4, a5) => {
                                                        If.create();
                                                        if (y4 === INDEX_ZERO) {
                                                            this.ifElseBranchUpdateFunction(0, () => {
                                                                this.TextStyle.bind(this)(e4);
                                                            });
                                                        } else {
                                                            this.ifElseBranchUpdateFunction(1, () => {
                                                                this.ArrowStyle.bind(this)();
                                                            });
                                                        }
                                                    }, If);
                                                    If.pop();
                                                };
                                                this.forEachUpdateFunction(u4, [INDEX_ZERO, INDEX_ONE], w4);
                                            }, ForEach);
                                            ForEach.pop();
                                        }
                                    };
                                };
                                s4.paramsGenerator_ = t4;
                            } else {
                                this.updateStateVarsOfChildByElmtId(q4, {});
                            }
                        }, { name: 'TextArrowLayout' });
                    }
                    Button.pop();
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o4, p4) => {
                        Row.create();
                        Row.margin({ bottom: getResourceValue('sys.float.subheader_right_only_arrow_margin_bottom') });
                        Row.focusable(true);
                        Row.constraintSize({ minWidth: this.getRightAreaMinWidth() });
                        Row.justifyContent(FlexAlign.End);
                    }, Row);
                    this.observeComponentCreation2((k4, l4) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.width(ARROW_ICON_WIDTH());
                        Button.height(OPERATE_ITEM_LENGTH());
                        Button.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_text_arrow_radius'));
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((n4) => {
                                if (n4) {
                                    this.textArrowBgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.textArrowBgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState();
                        Button.onHover((m4) => {
                            if (m4) {
                                this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
                            } else {
                                this.textArrowBgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        Button.focusable(true);
                        Button.margin({
                            start: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                getResourceValue('sys.float.subheader_right_text_arrow_margin_start')),
                            bottom: LengthMetrics.vp(this.ageing ? getResourceValue('sys.float.padding_level0') :
                                (this.secondaryTitle && this.primaryTitle ?
                                    getResourceValue('sys.float.subheader_right_text_arrow_margin_bottom') :
                                    getResourceValue('sys.float.subheader_single_right_text_arrow_margin_bottom'))),
                        });
                    }, Button);
                    this.observeComponentCreation2((i4, j4) => {
                        SymbolGlyph.create({
                            'id': 125832664,
                            'type': 40000,
                            params: ['sys.symbol.chevron_right'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        SymbolGlyph.fontSize(OPERATE_ITEM_LENGTH() + 'vp');
                        SymbolGlyph.fontColor([this.subHeaderTheme.iconArrowColor]);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.width(ARROW_ICON_WIDTH());
                        SymbolGlyph.height(OPERATE_ITEM_LENGTH());
                    }, SymbolGlyph);
                    Button.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
    }

    IconGroupStyle(m3, n3 = null) {
        this.observeComponentCreation2((c4, d4) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((o3, p3) => {
            ForEach.create();
            const q3 = (r3, s3) => {
                const t3 = r3;
                this.observeComponentCreation2((u3, v3) => {
                    If.create();
                    if (s3 <= INDEX_TWO) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((a4, b4) => {
                                __Common__.create();
                                __Common__.margin({
                                    start: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_icon_group_padding_start')),
                                    bottom: LengthMetrics.vp(this.secondaryTitle && this.primaryTitle ?
                                        getResourceValue('sys.float.subheader_right_icon_group_margin_bottom') :
                                        getResourceValue('sys.float.subheader_single_right_icon_group_margin_bottom')),
                                });
                                __Common__.offset({
                                    x: getResourceValue('sys.float.subheader_right_icon_group_x_offset')
                                });
                            }, __Common__);
                            {
                                this.observeComponentCreation2((w3, x3) => {
                                    if (x3) {
                                        let y3 = new SingleIconStyle(this, {
                                            item: {
                                                iconOptions: {
                                                    icon: t3.value,
                                                    symbolicIconOption: this.operationSymbolOptions &&
                                                        this.operationSymbolOptions.length > s3 ?
                                                        this.operationSymbolOptions[s3] : null,
                                                },
                                                action: t3.action,
                                                defaultFocus: t3.defaultFocus,
                                                accessibilityLevel: t3.accessibilityLevel,
                                                accessibilityText: t3.accessibilityText,
                                                accessibilityDescription: t3.accessibilityDescription,
                                            },
                                            isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER,
                                        }, undefined, w3, () => {
                                        }, {
                                            page: 'library/src/main/ets/components/subheader.ets',
                                            line: 1095,
                                            col: 11
                                        });
                                        ViewPU.create(y3);
                                        let z3 = () => {
                                            return {
                                                item: {
                                                    iconOptions: {
                                                        icon: t3.value,
                                                        symbolicIconOption: this.operationSymbolOptions &&
                                                            this.operationSymbolOptions.length > s3 ?
                                                            this.operationSymbolOptions[s3] : null,
                                                    },
                                                    action: t3.action,
                                                    defaultFocus: t3.defaultFocus,
                                                    accessibilityLevel: t3.accessibilityLevel,
                                                    accessibilityText: t3.accessibilityText,
                                                    accessibilityDescription: t3.accessibilityDescription,
                                                },
                                                isSingleIcon: this.operationItem?.length === SINGLE_ICON_NUMBER
                                            };
                                        };
                                        y3.paramsGenerator_ = z3;
                                    } else {
                                        this.updateStateVarsOfChildByElmtId(w3, {});
                                    }
                                }, { name: 'SingleIconStyle' });
                            }
                            __Common__.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(o3, m3, q3, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }

    LoadingProcessStyle(h3 = null) {
        this.observeComponentCreation2((k3, l3) => {
            Row.create();
            Row.justifyContent(FlexAlign.End);
            Row.padding({
                top: getResourceValue('sys.float.padding_level2'),
                bottom: this.secondaryTitle && this.primaryTitle ?
                    getResourceValue('sys.float.subheader_right_loading_padding_bottom') :
                    getResourceValue('sys.float.subheader_single_right_loading_padding_bottom'),
            });
            Row.margin({
                start: LengthMetrics.vp(getResourceValue('sys.float.subheader_right_loading_margin_start')),
            });
        }, Row);
        this.observeComponentCreation2((i3, j3) => {
            LoadingProgress.create();
            LoadingProgress.width(OPERATE_ITEM_LENGTH());
            LoadingProgress.height(OPERATE_ITEM_LENGTH());
            LoadingProgress.color({
                'id': 125830992,
                'type': 10001,
                params: ['sys.color.icon_secondary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
            });
        }, LoadingProgress);
        Row.pop();
    }

    dummyFunction(e3 = null) {
        this.observeComponentCreation2((f3, g3) => {
            Row.create();
        }, Row);
        Row.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class SingleIconStyle extends ViewPU {
    constructor(y2, z2, a3, b3 = -1, c3 = undefined, d3) {
        super(y2, a3, b3, d3);
        if (typeof c3 === 'function') {
            this.paramsGenerator_ = c3;
        }
        this.__bgColor = new ObservedPropertyObjectPU({
            'id': 125829134,
            'type': 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__',
        }, this, 'bgColor');
        this.__isFocus = new ObservedPropertySimplePU(false, this, 'isFocus');
        this.item = null;
        this.__subHeaderTheme = this.initializeConsume('subHeaderTheme', 'subHeaderTheme');
        this.isSingleIcon = true;
        this.setInitiallyProvidedValue(z2);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(x2) {
        if (x2.bgColor !== undefined) {
            this.bgColor = x2.bgColor;
        }
        if (x2.isFocus !== undefined) {
            this.isFocus = x2.isFocus;
        }
        if (x2.item !== undefined) {
            this.item = x2.item;
        }
        if (x2.isSingleIcon !== undefined) {
            this.isSingleIcon = x2.isSingleIcon;
        }
    }

    updateStateVars(w2) {
    }

    purgeVariableDependenciesOnElmtId(v2) {
        this.__bgColor.purgeDependencyOnElmtId(v2);
        this.__isFocus.purgeDependencyOnElmtId(v2);
        this.__subHeaderTheme.purgeDependencyOnElmtId(v2);
    }

    aboutToBeDeleted() {
        this.__bgColor.aboutToBeDeleted();
        this.__isFocus.aboutToBeDeleted();
        this.__subHeaderTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get bgColor() {
        return this.__bgColor.get();
    }

    set bgColor(u2) {
        this.__bgColor.set(u2);
    }

    get isFocus() {
        return this.__isFocus.get();
    }

    set isFocus(t2) {
        this.__isFocus.set(t2);
    }

    get subHeaderTheme() {
        return this.__subHeaderTheme.get();
    }

    set subHeaderTheme(s2) {
        this.__subHeaderTheme.set(s2);
    }

    getRightIconAccessibilityText() {
        if (this.item?.accessibilityText) {
            return this.item.accessibilityText;
        }
        return '';
    }

    getRightIconAccessibilityLevel() {
        if (this.item?.accessibilityLevel && this.item?.accessibilityLevel !== '') {
            return this.item.accessibilityLevel;
        }
        return 'auto';
    }

    getRightIconAccessibilityDescription() {
        if (this.item?.accessibilityDescription && this.item?.accessibilityDescription !== '') {
            return this.item?.accessibilityDescription;
        }
        return '';
    }

    initialRender() {
        this.observeComponentCreation2((k2, l2) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m2, n2) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
                        Button.focusable(true);
                        Button.defaultFocus(this.item.defaultFocus);
                        Button.width(SINGLE_ICON_ZONE_SIZE());
                        Button.height(SINGLE_ICON_ZONE_SIZE());
                        Button.align(Alignment.Center);
                        Button.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
                        Button.borderRadius(getResourceValue('sys.float.subheader_right_icon_radius'));
                        Button.accessibilityLevel(this.getRightIconAccessibilityLevel());
                        Button.accessibilityText(this.getRightIconAccessibilityText());
                        Button.accessibilityDescription(this.getRightIconAccessibilityDescription());
                        Button.focusBox({
                            margin: { value: INDEX_ZERO, unit: LengthUnit.VP },
                            strokeColor: ColorMetrics.resourceColor(this.subHeaderTheme.borderFocusColor),
                            strokeWidth: LengthMetrics.vp(getResourceValue('sys.float.outline_extra_larger')),
                        });
                        ViewStackProcessor.visualState('disabled');
                        Button.opacity(getResourceValue('sys.float.interactive_disable'));
                        ViewStackProcessor.visualState('pressed');
                        Button.backgroundColor({
                            'id': 125831020,
                            'type': 10001,
                            params: ['sys.color.interactive_pressed'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__',
                        });
                        ViewStackProcessor.visualState();
                        Button.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                            new DefaultFocusStyleModifier((r2) => {
                                if (r2) {
                                    this.bgColor = {
                                        'id': 125831015,
                                        'type': 10001,
                                        params: ['sys.color.comp_background_focus'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                } else {
                                    this.bgColor = {
                                        'id': 125829134,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__',
                                    };
                                }
                            }));
                        Button.onTouch((q2) => {
                            if (q2.type === TouchType.Down || TouchType.Cancel) {
                                this.bgColor = {
                                    'id': 125831020,
                                    'type': 10001,
                                    params: ['sys.color.interactive_pressed'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                            if (q2.type === TouchType.Up) {
                                this.bgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        Button.onHover((p2) => {
                            if (p2) {
                                this.bgColor = {
                                    'id': 125831019,
                                    'type': 10001,
                                    params: ['sys.color.interactive_hover'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            } else {
                                this.bgColor = {
                                    'id': 125829134,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_sub_background_transparent'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__',
                                };
                            }
                        });
                        Button.responseRegion(this.iconResponseRegion());
                        Button.onClick((o2) => {
                            if (this.item?.action) {
                                this.item?.action();
                            }
                        });
                    }, Button);
                    this.IconZone.bind(this)();
                    Button.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    iconResponseRegion() {
        if (this.isSingleIcon) {
            return {
                x: SINGLE_ICON_REGION_X,
                y: ICON_REGION_Y,
                width: MIN_HOT_AREA_LENGTH,
                height: MIN_HOT_AREA_LENGTH,
            };
        }
        return {
            x: ICON_REGION_X,
            y: ICON_REGION_Y,
            width: MULTI_ICON_REGION_WIDTH,
            height: MIN_HOT_AREA_LENGTH,
        };
    }

    fontSizeValue(j2) {
        return j2.iconOptions?.symbolicIconOption?.fontSize ?
            Util.symbolFontSize(j2.iconOptions?.symbolicIconOption?.fontSize) : RIGHT_SINGLE_ICON_SIZE();
    }

    IconZone(a2 = null) {
        this.observeComponentCreation2((b2, c2) => {
            If.create();
            if (this.item && this.item.iconOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d2, e2) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.iconOptions.icon)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((h2, i2) => {
                                    SymbolGlyph.create(this.item.iconOptions?.icon);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.fontSize(this.fontSizeValue(this.item));
                                    SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ??
                                        [this.subHeaderTheme.rightIconColor]);
                                    SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                                    SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                                    SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                                    SymbolGlyph.borderRadius(getResourceValue('sys.float.subheader_right_image_radius'));
                                    SymbolGlyph.padding(getResourceValue('sys.float.subheader_right_image_padding'));
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((f2, g2) => {
                                    Image.create(this.item?.iconOptions?.icon);
                                    Image.fillColor(this.subHeaderTheme.rightIconColor);
                                    Image.width(RIGHT_SINGLE_ICON_SIZE());
                                    Image.height(RIGHT_SINGLE_ICON_SIZE());
                                    Image.focusable(true);
                                    Image.draggable(false);
                                    Image.borderRadius(getResourceValue('sys.float.subheader_right_image_radius'));
                                    Image.padding(getResourceValue('sys.float.subheader_right_image_padding'));
                                    Image.attributeModifier.bind(this)(!DEFAULT_FOCUS_STYLE() ? undefined :
                                        new DefaultImageButtonFocusStyle());
                                }, Image);
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

    rerender() {
        this.updateDirtyElements();
    }
}

class Util {
    static isSymbolResource(y1) {
        if (!Util.isResourceType(y1)) {
            return false;
        }
        let z1 = y1;
        return z1?.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(x1) {
        if (!x1) {
            return false;
        }
        if (typeof x1 === 'string' || typeof x1 === 'undefined') {
            return false;
        }
        return true;
    }

    static getNumberByResource(r1, s1) {
        try {
            let w1 = resourceManager.getSystemResourceManager().getNumber(r1);
            if (w1 === 0) {
                return s1;
            } else {
                return w1;
            }
        } catch (t1) {
            let u1 = t1.code;
            let v1 = t1.message;
            hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${u1}, message: ${v1}`);
            return s1;
        }
    }

    static getStringByResource(l1, m1) {
        try {
            let q1 = getContext().resourceManager.getStringSync(l1);
            if (q1 === '') {
                return m1;
            } else {
                return q1;
            }
        } catch (n1) {
            let o1 = n1.code;
            let p1 = n1.message;
            hilog.error(0x3900, 'Ace', `SubHeader getStringByResource error, code: ${o1}, message: ${p1}`);
            return '';
        }
    }

    static numberToSize(j1) {
        if (typeof j1 === 'string') {
            const k1 = parseInt(j1);
            return k1;
        } else if (typeof j1 === 'number') {
            return j1;
        } else {
            return getContext().resourceManager.getNumber(j1);
        }
    }

    static symbolFontSize(i1) {
        return Util.numberToSize(i1) + 'vp';
    }
}

function getResourceValue(g1) {
    if (RESOURCE_CACHE_MAP.hasKey(g1)) {
        let h1 = RESOURCE_CACHE_MAP.get(g1).resourceValue;
        if (typeof h1 === 'number') {
            return h1;
        } else {
            h1 = Util.getNumberByResource(RESOURCE_CACHE_MAP.get(g1).resourceId,
                RESOURCE_CACHE_MAP.get(g1).defaultValue);
            RESOURCE_CACHE_MAP.get(g1).resourceValue = h1;
            return h1;
        }
    }
    return 0;
}

class TextArrowLayout extends ViewPU {
    constructor(a1, b1, c1, d1 = -1, e1 = undefined, f1) {
        super(a1, c1, d1, f1);
        if (typeof e1 === 'function') {
            this.paramsGenerator_ = e1;
        }
        this.textArrowBuilder = this.doNothingBuilder;
        this.setInitiallyProvidedValue(b1);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z) {
        if (z.textArrowBuilder !== undefined) {
            this.textArrowBuilder = z.textArrowBuilder;
        }
    }

    updateStateVars(y) {
    }

    purgeVariableDependenciesOnElmtId(x) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    doNothingBuilder(w = null) {
    }

    onPlaceChildren(p, q, r) {
        let s = 0;
        let t = 0;
        for (let u = 0; u < q.length; u++) {
            let v = q[u];
            v?.layout({ x: s, y: t });
        }
    }

    onMeasureSize(f, g, h) {
        let i = ARROW_ICON_WIDTH();
        let j = OPERATE_ITEM_LENGTH();
        let k = g[INDEX_ZERO];
        let l = {
            minWidth: Math.max(i, Number(h?.minWidth ?? 0)),
            maxWidth: h?.maxWidth ?? 0,
            minHeight: Math.max(j, Number(h?.minHeight ?? 0)),
            maxHeight: h?.maxHeight ?? 0,
        };
        let m = k?.measure(l);
        i = Math.max(i, m?.width ?? 0);
        j = Math.max(j, m?.height ?? 0);
        let n = g[INDEX_ONE];
        let o = {
            minWidth: i,
            maxWidth: i,
            minHeight: j,
            maxHeight: j,
        };
        n?.measure(o);
        return { width: i, height: j };
    }

    initialRender() {
        this.textArrowBuilder.bind(this)();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

function lazyInit(d) {
    let e = null;
    return () => {
        if (e === null) {
            e = d();
        }
        return e;
    };
}

class DefaultFocusStyleModifier {
    constructor(c) {
        this.stateStyleAction = c;
    }

    applyNormalAttribute(b) {
        if (!b) {
            return;
        }
        b.focusBox(undefined)
            .scale(undefined)
            .onFocus(() => {
                this.stateStyleAction && this.stateStyleAction(true);
            })
            .onBlur(() => {
                this.stateStyleAction && this.stateStyleAction(false);
            });
    }
}

class DefaultImageButtonFocusStyle {
    applyNormalAttribute(a) {
        if (!a) {
            return;
        }
        a.borderRadius(getResourceValue('sys.float.padding_level2'))
            .focusBox({ margin: LengthMetrics.vp(getResourceValue('sys.float.padding_level4')) });
    }
}

export default {
    OperationType, SubHeader
};