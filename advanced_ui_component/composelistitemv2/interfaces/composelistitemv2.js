/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (s44, t44, u44, v44) {
    var w44 = arguments.length,
        x44 = w44 < 3 ? t44 : v44 === null ? v44 = Object.getOwnPropertyDescriptor(t44, u44) : v44, y44;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        x44 = Reflect.decorate(s44, t44, u44, v44); else
        for (var z44 = s44.length - 1; z44 >= 0; z44--)
            if (y44 = s44[z44])
                x44 = (w44 < 3 ? y44(x44) : w44 > 3 ? y44(t44, u44, x44) : y44(t44, u44)) || x44;
    return w44 > 3 && x44 && Object.defineProperty(t44, u44, x44), x44;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const LengthMetrics = arkuiNode.LengthMetrics;
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const emitter = requireNapi('events.emitter');

export var IconTypeV2;
(function (r44) {
    r44[r44['BADGE'] = 1] = 'BADGE';
    r44[r44['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    r44[r44['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    r44[r44['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    r44[r44['APP_ICON'] = 5] = 'APP_ICON';
    r44[r44['PREVIEW'] = 6] = 'PREVIEW';
    r44[r44['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    r44[r44['VERTICAL'] = 8] = 'VERTICAL';
})(IconTypeV2 || (IconTypeV2 = {}));
var FontSizeScaleLevel;
(function (q44) {
    q44[q44['LEVEL1'] = 1.75] = 'LEVEL1';
    q44[q44['LEVEL2'] = 2] = 'LEVEL2';
    q44[q44['LEVEL3'] = 3.2] = 'LEVEL3';
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (p44) {
    p44[p44['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    p44[p44['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    p44[p44['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    p44[p44['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    p44[p44['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
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
const EVENT_IS_WRAP_TEXT_CHANGE = 10001;
const EVENT_PARENT_CAN_FOCUS_CHANGE = 10002;
const EVENT_PARENT_CAN_HOVER_CHANGE = 10003;
const EVENT_PARENT_FRONT_COLOR_CHANGE = 10004;
const ICON_SIZE_MAP = new Map([
    [IconTypeV2.BADGE, BADGE_SIZE],
    [IconTypeV2.NORMAL_ICON, SMALL_ICON_SIZE],
    [IconTypeV2.SYSTEM_ICON, SYSTEM_ICON_SIZE],
    [IconTypeV2.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
    [IconTypeV2.APP_ICON, APP_ICON_SIZE],
    [IconTypeV2.PREVIEW, PREVIEW_SIZE],
    [IconTypeV2.LONGITUDINAL, LONGITUDINAL_SIZE],
    [IconTypeV2.VERTICAL, VERTICAL_SIZE]
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
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR = {
    'id': -1,
    'type': 10001,
    params: ['sys.color.ohos_id_color_switch_outline_off'],
    'bundleName': '__harDefaultBundleName__',
    'moduleName': '__harDefaultModuleName__'
};
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
    static isSymbolResource(n44) {
        if (!Util.isResourceType(n44)) {
            return false;
        }
        let o44 = n44;
        return o44.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(m44) {
        if (!m44) {
            return false;
        }
        if (typeof m44 === 'string' || typeof m44 === 'undefined') {
            return false;
        }
        return true;
    }
}

class ContentItemStruct extends ViewV2 {
    constructor(g44, h44, i44, j44 = -1, k44, l44) {
        super(g44, j44, l44);
        this.initParam('iconStyle', (h44 && 'iconStyle' in h44) ? h44.iconStyle : null);
        this.initParam('icon', (h44 && 'icon' in h44) ? h44.icon : null);
        this.initParam('symbolStyle', (h44 && 'symbolStyle' in h44) ? h44.symbolStyle : null);
        this.initParam('primaryText', (h44 && 'primaryText' in h44) ? h44.primaryText : null);
        this.initParam('secondaryText', (h44 && 'secondaryText' in h44) ? h44.secondaryText : null);
        this.initParam('description', (h44 && 'description' in h44) ? h44.description : null);
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.initParam('leftWidth', (h44 && 'leftWidth' in h44) ? h44.leftWidth : LEFT_PART_WIDTH);
        this.primaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.descriptionColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.initParam('fontSizeScale', (h44 && 'fontSizeScale' in h44) ? h44.fontSizeScale : 1);
        this.initParam('parentDirection', (h44 && 'parentDirection' in h44) ? h44.parentDirection : FlexDirection.Row);
        this.initParam('itemDirection', (h44 && 'itemDirection' in h44) ? h44.itemDirection : FlexDirection.Row);
        this.initParam('isFocus', (h44 && 'isFocus' in h44) ? h44.isFocus : false);
        this.primaryTextSize = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.primaryTextColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.initParam('itemHeight', (h44 && 'itemHeight' in h44) ? h44.itemHeight : null);
        this.iconColor = null;
        this.secondaryTextColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryThirdTextSize = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.composeListItem_left_secondary_tertiary_text_size'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.descriptionColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.isWrapText = false;
        this.isWrapFirstText = false;
        this.isWrapSecondText = false;
        this.isWrapThirdText = false;
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(f44) {
        this.resetParam('iconStyle', (f44 && 'iconStyle' in f44) ? f44.iconStyle : null);
        this.resetParam('icon', (f44 && 'icon' in f44) ? f44.icon : null);
        this.resetParam('symbolStyle', (f44 && 'symbolStyle' in f44) ? f44.symbolStyle : null);
        this.resetParam('primaryText', (f44 && 'primaryText' in f44) ? f44.primaryText : null);
        this.resetParam('secondaryText', (f44 && 'secondaryText' in f44) ? f44.secondaryText : null);
        this.resetParam('description', (f44 && 'description' in f44) ? f44.description : null);
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.resetParam('leftWidth', (f44 && 'leftWidth' in f44) ? f44.leftWidth : LEFT_PART_WIDTH);
        this.primaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.descriptionColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.resetParam('fontSizeScale', (f44 && 'fontSizeScale' in f44) ? f44.fontSizeScale : 1);
        this.resetParam('parentDirection', (f44 && 'parentDirection' in f44) ? f44.parentDirection : FlexDirection.Row);
        this.resetParam('itemDirection', (f44 && 'itemDirection' in f44) ? f44.itemDirection : FlexDirection.Row);
        this.resetParam('isFocus', (f44 && 'isFocus' in f44) ? f44.isFocus : false);
        this.primaryTextSize = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.primaryTextColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.resetParam('itemHeight', (f44 && 'itemHeight' in f44) ? f44.itemHeight : null);
        this.iconColor = null;
        this.secondaryTextColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryThirdTextSize = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.composeListItem_left_secondary_tertiary_text_size'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.descriptionColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_tertiary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.isWrapText = false;
        this.isWrapFirstText = false;
        this.isWrapSecondText = false;
        this.isWrapThirdText = false;
        this.resetMonitorsOnReuse();
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
        let e44 = {
            data: { isWrapText: this.isWrapText }
        };
        emitter.emit({ eventId: EVENT_IS_WRAP_TEXT_CHANGE }, e44);
    }

    onWillApplyTheme(d44) {
        this.primaryTextColor = d44.colors.fontPrimary;
        this.secondaryTextColor = d44.colors.fontSecondary;
        this.descriptionColor = d44.colors.fontTertiary;
    }

    getContentItemIconFillColor() {
        switch (this.iconStyle) {
            case IconTypeV2.BADGE:
                return {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.composeListItem_badge_color'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
            case IconTypeV2.SYSTEM_ICON:
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

    judgeIsWrap(z43, a44, b44) {
        let c44 = this.getSingleRowTextHeight(z43, a44);
        return b44 > c44;
    }

    getSingleRowTextHeight(u43, v43) {
        if (u43 && v43) {
            let w43 = measure.measureTextSize({
                textContent: u43,
                fontSize: v43,
                maxLines: TEXT_MAX_LINE
            });
            if (w43 && w43.height) {
                let x43 = 0;
                if (typeof w43.height === 'number') {
                    x43 = w43.height;
                } else if (typeof w43.height === 'string') {
                    x43 = parseFloat(w43.height);
                }
                let y43 = px2vp(x43);
                return y43;
            }
        }
        return 0;
    }

    aboutToAppear() {
        this.onPropChange();
    }

    createIcon(d43 = null) {
        this.observeComponentCreation2((e43, f43) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g43, h43) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((s43, t43) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([this.getContentItemIconFillColor()]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.symbolStyle);
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
                                this.observeComponentCreation2((i43, j43) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.icon)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((q43, r43) => {
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
                                            this.observeComponentCreation2((k43, l43) => {
                                                If.create();
                                                if (this.iconStyle <= IconTypeV2.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((o43, p43) => {
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
                                                        this.observeComponentCreation2((m43, n43) => {
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

    createText(h42 = null) {
        this.observeComponentCreation2((b43, c43) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((w42, x42) => {
            Text.create(this.primaryText);
            Text.fontSize(this.primaryTextSize);
            Text.fontColor(this.primaryTextColors);
            Text.textOverflow({
                overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                    TextOverflow.Ellipsis
            });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
            Text.onSizeChange((y42, z42) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT && z42.height) {
                    let a43 = typeof z42.height === 'number' ? z42.height : 0;
                    this.isWrapFirstText = this.judgeIsWrap(this.primaryText, this.primaryTextSize, a43);
                }
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((p42, q42) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r42, s42) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(this.secondaryThirdTextSize);
                        Text.fontColor(this.secondaryTextColors);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                                TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((t42, u42) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT && u42.height) {
                                let v42 = typeof u42.height === 'number' ? u42.height : 0;
                                this.isWrapSecondText =
                                    this.judgeIsWrap(this.secondaryText, this.secondaryThirdTextSize, v42);
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
        this.observeComponentCreation2((i42, j42) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k42, l42) => {
                        Text.create(this.description);
                        Text.fontSize(this.secondaryThirdTextSize);
                        Text.fontColor(this.descriptionColors);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                                TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((m42, n42) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT && n42.height) {
                                let o42 = typeof n42.height === 'number' ? n42.height : 0;
                                this.isWrapThirdText =
                                    this.judgeIsWrap(this.description, this.secondaryThirdTextSize, o42);
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
        this.observeComponentCreation2((f42, g42) => {
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

    updateStateVars(e42) {
        if (e42 === undefined) {
            return;
        }
        if ('iconStyle' in e42) {
            this.updateParam('iconStyle', e42.iconStyle);
        }
        if ('icon' in e42) {
            this.updateParam('icon', e42.icon);
        }
        if ('symbolStyle' in e42) {
            this.updateParam('symbolStyle', e42.symbolStyle);
        }
        if ('primaryText' in e42) {
            this.updateParam('primaryText', e42.primaryText);
        }
        if ('secondaryText' in e42) {
            this.updateParam('secondaryText', e42.secondaryText);
        }
        if ('description' in e42) {
            this.updateParam('description', e42.description);
        }
        if ('leftWidth' in e42) {
            this.updateParam('leftWidth', e42.leftWidth);
        }
        if ('fontSizeScale' in e42) {
            this.updateParam('fontSizeScale', e42.fontSizeScale);
        }
        if ('parentDirection' in e42) {
            this.updateParam('parentDirection', e42.parentDirection);
        }
        if ('itemDirection' in e42) {
            this.updateParam('itemDirection', e42.itemDirection);
        }
        if ('isFocus' in e42) {
            this.updateParam('isFocus', e42.isFocus);
        }
        if ('itemHeight' in e42) {
            this.updateParam('itemHeight', e42.itemHeight);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Param
], ContentItemStruct.prototype, 'iconStyle', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'icon', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'symbolStyle', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'primaryText', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'secondaryText', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'description', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'itemRowSpace', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'leftWidth', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'primaryTextColor', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'secondaryTextColor', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'descriptionColor', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'fontSizeScale', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'parentDirection', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'itemDirection', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'isFocus', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'primaryTextSize', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'primaryTextColors', void 0);
__decorate([
    Param
], ContentItemStruct.prototype, 'itemHeight', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'iconColor', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'secondaryTextColors', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'secondaryThirdTextSize', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'descriptionColors', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'isWrapText', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'isWrapFirstText', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'isWrapSecondText', void 0);
__decorate([
    Local
], ContentItemStruct.prototype, 'isWrapThirdText', void 0);
__decorate([
    Monitor('iconStyle', 'icon', 'symbolStyle', 'primaryText', 'secondaryText', 'description', 'isFocus')
], ContentItemStruct.prototype, 'onPropChange', null);
__decorate([
    Monitor('isWrapFirstText', 'isWrapSecondText', 'isWrapThirdText')
], ContentItemStruct.prototype, 'onWrapChange', null);

class CreateIconParam {
}

class OperateItemStructController {
    constructor() {
        this.changeRadioState = () => {
        };
        this.changeCheckboxState = () => {
        };
        this.changeSwitchState = () => {
        };
    }
}

class OperateItemStruct extends ViewV2 {
    constructor(y41, z41, a42, b42 = -1, c42, d42) {
        super(y41, b42, d42);
        this.initParam('arrow', (z41 && 'arrow' in z41) ? z41.arrow : null);
        this.initParam('icon', (z41 && 'icon' in z41) ? z41.icon : null);
        this.initParam('subIcon', (z41 && 'subIcon' in z41) ? z41.subIcon : null);
        this.initParam('button', (z41 && 'button' in z41) ? z41.button : null);
        this.initParam('switch', (z41 && 'switch' in z41) ? z41.switch : null);
        this.initParam('checkBox', (z41 && 'checkBox' in z41) ? z41.checkBox : null);
        this.initParam('radio', (z41 && 'radio' in z41) ? z41.radio : null);
        this.initParam('image', (z41 && 'image' in z41) ? z41.image : null);
        this.initParam('symbolStyle', (z41 && 'symbolStyle' in z41) ? z41.symbolStyle : null);
        this.initParam('text', (z41 && 'text' in z41) ? z41.text : null);
        this.switchState = false;
        this.radioState = false;
        this.checkBoxState = false;
        this.initParam('rightWidth', (z41 && 'rightWidth' in z41) ? z41.rightWidth : RIGHT_PART_WIDTH);
        this.secondaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.hoveringColor = '#0d000000';
        this.activedColor = '#1a0a59f7';
        this.initParam('parentCanFocus', (z41 && 'parentCanFocus' in z41) ? z41.parentCanFocus : false);
        this.initParam('parentCanTouch', (z41 && 'parentCanTouch' in z41) ? z41.parentCanTouch : true);
        this.initParam('parentIsHover', (z41 && 'parentIsHover' in z41) ? z41.parentIsHover : false);
        this.initParam('parentCanHover', (z41 && 'parentCanHover' in z41) ? z41.parentCanHover : true);
        this.initParam('parentIsActive', (z41 && 'parentIsActive' in z41) ? z41.parentIsActive : false);
        this.initParam('parentFrontColor', (z41 && 'parentFrontColor' in z41) ? z41.parentFrontColor : NORMAL_BG_COLOR);
        this.initParam('parentDirection', (z41 && 'parentDirection' in z41) ? z41.parentDirection : FlexDirection.Row);
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.initParam('isFocus', (z41 && 'isFocus' in z41) ? z41.isFocus : false);
        this.secondaryTextSize = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_size_body2'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryTextColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.composeListItem_right_icon_normal_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.controller = new OperateItemStructController();
        this.changeRadioState = () => {
            this.radioState = !this.radioState;
        };
        this.changeCheckboxState = () => {
            this.checkBoxState = !this.checkBoxState;
        };
        this.changeSwitchState = () => {
            this.switchState = !this.switchState;
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(x41) {
        this.resetParam('arrow', (x41 && 'arrow' in x41) ? x41.arrow : null);
        this.resetParam('icon', (x41 && 'icon' in x41) ? x41.icon : null);
        this.resetParam('subIcon', (x41 && 'subIcon' in x41) ? x41.subIcon : null);
        this.resetParam('button', (x41 && 'button' in x41) ? x41.button : null);
        this.resetParam('switch', (x41 && 'switch' in x41) ? x41.switch : null);
        this.resetParam('checkBox', (x41 && 'checkBox' in x41) ? x41.checkBox : null);
        this.resetParam('radio', (x41 && 'radio' in x41) ? x41.radio : null);
        this.resetParam('image', (x41 && 'image' in x41) ? x41.image : null);
        this.resetParam('symbolStyle', (x41 && 'symbolStyle' in x41) ? x41.symbolStyle : null);
        this.resetParam('text', (x41 && 'text' in x41) ? x41.text : null);
        this.switchState = false;
        this.radioState = false;
        this.checkBoxState = false;
        this.resetParam('rightWidth', (x41 && 'rightWidth' in x41) ? x41.rightWidth : RIGHT_PART_WIDTH);
        this.secondaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.hoveringColor = '#0d000000';
        this.activedColor = '#1a0a59f7';
        this.resetParam('parentCanFocus', (x41 && 'parentCanFocus' in x41) ? x41.parentCanFocus : false);
        this.resetParam('parentCanTouch', (x41 && 'parentCanTouch' in x41) ? x41.parentCanTouch : true);
        this.resetParam('parentIsHover', (x41 && 'parentIsHover' in x41) ? x41.parentIsHover : false);
        this.resetParam('parentCanHover', (x41 && 'parentCanHover' in x41) ? x41.parentCanHover : true);
        this.resetParam('parentIsActive', (x41 && 'parentIsActive' in x41) ? x41.parentIsActive : false);
        this.resetParam('parentFrontColor',
            (x41 && 'parentFrontColor' in x41) ? x41.parentFrontColor : NORMAL_BG_COLOR);
        this.resetParam('parentDirection', (x41 && 'parentDirection' in x41) ? x41.parentDirection : FlexDirection.Row);
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.resetParam('isFocus', (x41 && 'isFocus' in x41) ? x41.isFocus : false);
        this.secondaryTextSize = {
            'id': -1,
            'type': 10002,
            params: ['sys.float.ohos_id_text_size_body2'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.secondaryTextColors = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.font_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.iconColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.composeListItem_right_icon_normal_color'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.resetMonitorsOnReuse();
    }

    onPropChange() {
        if (this.switch != null) {
            this.switchState = this.switch.isCheck;
        }
        if (this.radio != null) {
            this.radioState = this.radio.isCheck;
        }
        if (this.checkBox != null) {
            this.checkBoxState = this.checkBox.isCheck;
        }
        if ((this.button == null && this.image == null && this.symbolStyle == null && this.text != null) &&
            ((this.icon != null) || (this.icon == null && this.arrow != null))) {
            this.rowSpace = SPECICAL_ROW_SPACE;
        } else {
            this.rowSpace = DEFAULT_ROW_SPACE;
        }
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

    onWillApplyTheme(w41) {
        this.secondaryTextColor = w41.colors.fontSecondary;
        this.hoveringColor = w41.colors.interactiveHover;
        this.activedColor = w41.colors.interactiveActive;
    }

    aboutToAppear() {
        this.onPropChange();
        this.onFocusChange();
        if (this.controller) {
            this.controller.changeRadioState = this.changeRadioState;
            this.controller.changeCheckboxState = this.changeCheckboxState;
            this.controller.changeSwitchState = this.changeSwitchState;
        }
    }

    createButton(o41 = null) {
        this.observeComponentCreation2((t41, u41) => {
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
                this.notifyParentCanFocusChange(false);
            });
            Button.onHover((v41) => {
                this.notifyParentCanHoverChange(false);
                if (v41 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!v41) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
            Button.accessibilityLevel(this.button?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(this.button?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.button?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((r41, s41) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((p41, q41) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }

    createIcon(z40, a41 = null) {
        this.observeComponentCreation2((l41, m41) => {
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
                this.notifyParentCanFocusChange(false);
            });
            Button.onHover((n41) => {
                this.notifyParentCanHoverChange(false);
                if (n41 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!n41) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
            Button.onClick(z40.icon?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(z40.icon?.accessibilityLevel, z40.icon?.action));
            Button.accessibilityText(getAccessibilityText(z40.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(z40.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((b41, c41) => {
            If.create();
            if (z40.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j41, k41) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(z40.icon?.symbolStyle);
                        SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((d41, e41) => {
                        If.create();
                        if (Util.isSymbolResource(z40.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((h41, i41) => {
                                    SymbolGlyph.create(z40.icon?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((f41, g41) => {
                                    Image.create(z40.icon?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.focusable(true);
                                    Image.fillColor(this.iconColor);
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

    createImage(s40 = null) {
        this.observeComponentCreation2((t40, u40) => {
            If.create();
            if (Util.isSymbolResource(this.image)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x40, y40) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((v40, w40) => {
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

    createSymbol(p40 = null) {
        this.observeComponentCreation2((q40, r40) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(this.symbolStyle);
            SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }

    createText(m40 = null) {
        this.observeComponentCreation2((n40, o40) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize(this.secondaryTextSize);
            Text.fontColor(this.secondaryTextColors);
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

    createArrow(y39 = null) {
        this.observeComponentCreation2((j40, k40) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.shadow(CLEAR_SHADOW);
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
                (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.notifyParentCanFocusChange(false);
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((l40) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (l40 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentCanHoverChange(false);
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                } else {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel,
                this.arrow?.action));
            Button.accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((z39, a40) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h40, i40) => {
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
                    this.observeComponentCreation2((b40, c40) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f40, g40) => {
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
                                this.observeComponentCreation2((d40, e40) => {
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

    createRadio(t39 = null) {
        this.observeComponentCreation2((u39, v39) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: DEFUALT_RADIO_CHECKBOX_BORDER_COLOR
            });
            Radio.backgroundColor(Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((x39) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.radioState = x39;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(x39);
                }
            });
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Radio.onFocus(() => {
                this.notifyParentCanFocusChange(false);
            });
            Radio.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Radio.flexShrink(0);
            Radio.onHover((w39) => {
                this.notifyParentCanHoverChange(false);
                if (w39 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!w39) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
            Radio.accessibilityLevel(getAccessibilityLevelOnChange(this.radio?.accessibilityLevel,
                this.radio?.onChange));
            Radio.accessibilityText(getAccessibilityText(this.radio?.accessibilityText ?? ''));
            Radio.accessibilityDescription(getAccessibilityText(this.radio?.accessibilityDescription ?? ''));
        }, Radio);
    }

    createCheckBox(o39 = null) {
        this.observeComponentCreation2((p39, q39) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(DEFUALT_RADIO_CHECKBOX_BORDER_COLOR);
            Checkbox.backgroundColor(Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((s39) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.checkBoxState = s39;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(s39);
                }
            });
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Checkbox.onFocus(() => {
                this.notifyParentCanFocusChange(false);
            });
            Checkbox.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Checkbox.flexShrink(0);
            Checkbox.onHover((r39) => {
                this.notifyParentCanHoverChange(false);
                if (r39 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!r39) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
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

    createSwitch(h39 = null) {
        this.observeComponentCreation2((l39, m39) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.notifyParentCanFocusChange(false);
            });
            Row.onHover((n39) => {
                this.notifyParentCanHoverChange(false);
                if (n39 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!n39) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((i39, j39) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(Color.Transparent);
            Toggle.onChange((k39) => {
                this.switchState = k39;
                if (this.switch?.onChange) {
                    this.switch?.onChange(k39);
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

    createTextArrow(z37 = null) {
        this.observeComponentCreation2((e39, f39) => {
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
                this.notifyParentCanFocusChange(false);
            });
            Button.padding({
                top: 0,
                bottom: 0,
                left: 0,
                right: 0
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((g39) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (g39 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentCanHoverChange(false);
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                } else {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
            Button.onClick(this.arrow?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel,
                this.arrow?.action));
            Button.accessibilityText(`${this.text} ${getAccessibilityText(this.arrow?.accessibilityText ?? '')}`);
            Button.accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''));
        }, Button);
        this.observeComponentCreation2((a38, b38) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c39, d39) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((a39, b39) => {
                        Text.create(this.text);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body2'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor(this.secondaryTextColor);
                        Text.focusable(true);
                        Text.draggable(false);
                        Text.constraintSize({
                            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((q38, r38) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y38, z38) => {
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
                                this.observeComponentCreation2((s38, t38) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((w38, x38) => {
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
                                            this.observeComponentCreation2((u38, v38) => {
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
                    this.observeComponentCreation2((o38, p38) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((m38, n38) => {
                        Text.create(this.text);
                        Text.fontSize(this.secondaryTextSize);
                        Text.fontColor(this.secondaryTextColors);
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
                    this.observeComponentCreation2((c38, d38) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((k38, l38) => {
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
                                this.observeComponentCreation2((e38, f38) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((i38, j38) => {
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
                                            this.observeComponentCreation2((g38, h38) => {
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
        let y37 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            y37.justifyContent = FlexAlign.SpaceBetween;
        } else {
            y37.space = { main: LengthMetrics.vp(this.rowSpace) };
            y37.justifyContent = FlexAlign.End;
        }
        return y37;
    }

    notifyParentCanFocusChange(x37) {
        emitter.emit({ eventId: EVENT_PARENT_CAN_FOCUS_CHANGE }, { data: { canFocus: x37 } });
    }

    notifyParentCanHoverChange(w37) {
        emitter.emit({ eventId: EVENT_PARENT_CAN_HOVER_CHANGE }, { data: { canHover: w37 } });
    }

    notifyParentFrontColorChange(v37) {
        emitter.emit({ eventId: EVENT_PARENT_FRONT_COLOR_CHANGE }, { data: { frontColor: v37 } });
    }

    initialRender() {
        this.observeComponentCreation2((t37, u37) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((p37, q37) => {
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
            } else if (this.arrow != null && (this.text == null || this.text == '')) {
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
                    this.observeComponentCreation2((r37, s37) => {
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

    updateStateVars(o37) {
        if (o37 === undefined) {
            return;
        }
        if ('arrow' in o37) {
            this.updateParam('arrow', o37.arrow);
        }
        if ('icon' in o37) {
            this.updateParam('icon', o37.icon);
        }
        if ('subIcon' in o37) {
            this.updateParam('subIcon', o37.subIcon);
        }
        if ('button' in o37) {
            this.updateParam('button', o37.button);
        }
        if ('switch' in o37) {
            this.updateParam('switch', o37.switch);
        }
        if ('checkBox' in o37) {
            this.updateParam('checkBox', o37.checkBox);
        }
        if ('radio' in o37) {
            this.updateParam('radio', o37.radio);
        }
        if ('image' in o37) {
            this.updateParam('image', o37.image);
        }
        if ('symbolStyle' in o37) {
            this.updateParam('symbolStyle', o37.symbolStyle);
        }
        if ('text' in o37) {
            this.updateParam('text', o37.text);
        }
        if ('rightWidth' in o37) {
            this.updateParam('rightWidth', o37.rightWidth);
        }
        if ('parentCanFocus' in o37) {
            this.updateParam('parentCanFocus', o37.parentCanFocus);
        }
        if ('parentCanTouch' in o37) {
            this.updateParam('parentCanTouch', o37.parentCanTouch);
        }
        if ('parentIsHover' in o37) {
            this.updateParam('parentIsHover', o37.parentIsHover);
        }
        if ('parentCanHover' in o37) {
            this.updateParam('parentCanHover', o37.parentCanHover);
        }
        if ('parentIsActive' in o37) {
            this.updateParam('parentIsActive', o37.parentIsActive);
        }
        if ('parentFrontColor' in o37) {
            this.updateParam('parentFrontColor', o37.parentFrontColor);
        }
        if ('parentDirection' in o37) {
            this.updateParam('parentDirection', o37.parentDirection);
        }
        if ('isFocus' in o37) {
            this.updateParam('isFocus', o37.isFocus);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}

__decorate([
    Param
], OperateItemStruct.prototype, 'arrow', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'icon', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'subIcon', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'button', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'switch', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'checkBox', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'radio', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'image', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'symbolStyle', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'text', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'switchState', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'radioState', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'checkBoxState', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'rightWidth', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'secondaryTextColor', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'hoveringColor', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'activedColor', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentCanFocus', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentCanTouch', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentIsHover', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentCanHover', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentIsActive', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentFrontColor', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'parentDirection', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'rowSpace', void 0);
__decorate([
    Param
], OperateItemStruct.prototype, 'isFocus', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'secondaryTextSize', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'secondaryTextColors', void 0);
__decorate([
    Local
], OperateItemStruct.prototype, 'iconColor', void 0);
__decorate([
    Monitor('arrow', 'icon', 'subIcon', 'button', 'switch', 'checkBox', 'radio', 'image', 'symbolStyle', 'text')
], OperateItemStruct.prototype, 'onPropChange', null);
__decorate([
    Monitor('isFocus')
], OperateItemStruct.prototype, 'onFocusChange', null);

function getAccessibilityText(j37) {
    try {
        let n37 = '';
        if (typeof j37 === 'string') {
            n37 = j37;
        } else {
            n37 = getContext().resourceManager.getStringSync(j37);
        }
        return n37;
    } catch (k37) {
        let l37 = k37.code;
        let m37 = k37.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${l37}, message: ${m37}`);
        return '';
    }
}

function getAccessibilityLevelOnChange(h37, i37) {
    if (h37) {
        return h37;
    }
    if (i37) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}

function getAccessibilityLevelOnAction(f37, g37) {
    if (f37) {
        return f37;
    }
    if (g37) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}

export class ComposeListItemV2 extends ViewV2 {
    constructor(u36, v36, w36, x36 = -1, y36, z36) {
        super(u36, x36, z36);
        this.initParam('contentItemV2', (v36 && 'contentItemV2' in v36) ? v36.contentItemV2 : null);
        this.initParam('operateItemV2', (v36 && 'operateItemV2' in v36) ? v36.operateItemV2 : null);
        this.frontColor = NORMAL_BG_COLOR;
        this.borderSize = 0;
        this.canFocus = false;
        this.canTouch = true;
        this.canHover = true;
        this.isHover = false;
        this.itemHeight = ItemHeight.FIRST_HEIGHT;
        this.isActive = false;
        this.hoveringColor = '#0d000000';
        this.touchDownColor = '#1a000000';
        this.activedColor = '#1a0a59f7';
        this.focusOutlineColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.fontSizeScale = 1;
        this.containerDirection = FlexDirection.Row;
        this.contentItemDirection = FlexDirection.Row;
        this.containerPadding = undefined;
        this.textArrowLeftSafeOffset = 0;
        this.isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
        this.maxFontScale = this.getUIContext().getMaxFontScale();
        this.callbackId = undefined;
        this.accessibilityTextBuilder = '';
        this.isFocus = false;
        this.isWrapText = false;
        this.listScale = { x: 1, y: 1 };
        this.operateItemStructRef = new OperateItemStructController();
        this.envCallback = {
            onConfigurationUpdated: (b37) => {
                if (b37 === undefined || !this.isFollowingSystemFontScale) {
                    this.fontSizeScale = 1;
                    return;
                }
                try {
                    this.fontSizeScale = Math.min(this.maxFontScale, b37.fontSizeScale ?? 1);
                } catch (c37) {
                    let d37 = c37.code;
                    let e37 = c37.message;
                    hilog.error(0x3900, 'Ace', `ComposeListItemV2 environmentCallback error: ${d37}, ${e37}`);
                }
            },
            onMemoryLevel: (a37) => {
            }
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(t36) {
        this.resetParam('contentItemV2', (t36 && 'contentItemV2' in t36) ? t36.contentItemV2 : null);
        this.resetParam('operateItemV2', (t36 && 'operateItemV2' in t36) ? t36.operateItemV2 : null);
        this.frontColor = NORMAL_BG_COLOR;
        this.borderSize = 0;
        this.canFocus = false;
        this.canTouch = true;
        this.canHover = true;
        this.isHover = false;
        this.itemHeight = ItemHeight.FIRST_HEIGHT;
        this.isActive = false;
        this.hoveringColor = '#0d000000';
        this.touchDownColor = '#1a000000';
        this.activedColor = '#1a0a59f7';
        this.focusOutlineColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_focused_outline'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.fontSizeScale = 1;
        this.containerDirection = FlexDirection.Row;
        this.contentItemDirection = FlexDirection.Row;
        this.containerPadding = undefined;
        this.textArrowLeftSafeOffset = 0;
        this.accessibilityTextBuilder = '';
        this.isFocus = false;
        this.isWrapText = false;
        this.listScale = { x: 1, y: 1 };
        this.resetMonitorsOnReuse();
    }

    onPropChange() {
        this.containerDirection = this.decideContainerDirection();
        this.contentItemDirection = this.decideContentItemDirection();
        if (this.contentItemV2 === undefined) {
            if (this.operateItemV2?.image !== undefined ||
                this.operateItemV2?.symbolStyle !== undefined ||
                this.operateItemV2?.icon !== undefined ||
                this.operateItemV2?.subIcon !== undefined) {
                this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
            }
            return;
        }
        if (this.contentItemV2?.secondaryText === undefined && this.contentItemV2?.description === undefined) {
            if (this.contentItemV2?.icon === undefined) {
                this.itemHeight = ItemHeight.FIRST_HEIGHT;
            } else {
                let s36 = this.contentItemV2.iconStyle ?? IconTypeV2.BADGE;
                this.itemHeight = s36 <= IconTypeV2.HEAD_SCULPTURE ?
                    ItemHeight.SECOND_HEIGHT :
                    (LengthMetrics.resource({
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.composeListItem_system_icon_line_height'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    }).value);
            }
        } else if (this.contentItemV2.description === undefined) {
            let r36 = this.contentItemV2.iconStyle ?? IconTypeV2.BADGE;
            if (this.contentItemV2.icon === undefined ||
                (this.contentItemV2.icon !== undefined && r36 <= IconTypeV2.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            } else {
                this.itemHeight = r36 === IconTypeV2.HEAD_SCULPTURE ? ItemHeight.FOURTH_HEIGHT : APPICON_ITEMLENGTH;
            }
        } else {
            this.itemHeight = ItemHeight.FIFTH_HEIGHT;
        }
        let p36 = this.contentItemV2?.iconStyle ?? IconTypeV2.BADGE;
        let q36 = ICON_SIZE_MAP.get(p36);
        if (q36 !== undefined && q36 >= this.itemHeight) {
            this.itemHeight = q36 + SAFE_LIST_PADDING;
        }
        if (this.operateItemV2?.arrow && this.operateItemV2?.text && this.operateItemV2?.arrow?.action) {
            this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItemV2?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.description ?? '')}
      `;
        } else {
            this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItemV2?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.description ?? '')}
        ${getAccessibilityText(this.operateItemV2?.text ?? '')}
      `;
        }
    }

    onWrapChange() {
        this.containerPadding = this.getPadding();
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

    onWillApplyTheme(o36) {
        this.hoveringColor = o36.colors.interactiveHover;
        this.touchDownColor = o36.colors.interactivePressed;
        this.activedColor = o36.colors.interactiveActive;
        this.focusOutlineColor = o36.colors.interactiveFocus;
    }

    aboutToAppear() {
        this.fontSizeScale = this.decideFontSizeScale();
        this.onPropChange();
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (l36) {
            let m36 = l36.code;
            let n36 = l36.message;
            hilog.error(0x3900, 'Ace', `ComposeListItemV2 Faild to get environment param error: ${m36}, ${n36}`);
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
            this.onFontSizeScaleChange();
        }
        emitter.on({ eventId: EVENT_IS_WRAP_TEXT_CHANGE }, (k36) => {
            if (k36.data && k36.data.isWrapText !== undefined) {
                this.isWrapText = k36.data.isWrapText;
            }
        });
        emitter.on({ eventId: EVENT_PARENT_CAN_FOCUS_CHANGE }, (j36) => {
            if (j36.data && j36.data.canFocus !== undefined) {
                this.canFocus = j36.data.canFocus;
            }
        });
        emitter.on({ eventId: EVENT_PARENT_CAN_HOVER_CHANGE }, (i36) => {
            if (i36.data && i36.data.canHover !== undefined) {
                this.canHover = i36.data.canHover;
            }
        });
        emitter.on({ eventId: EVENT_PARENT_FRONT_COLOR_CHANGE }, (h36) => {
            if (h36.data && h36.data.frontColor !== undefined) {
                this.frontColor = h36.data.frontColor;
            }
        });
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()
            ?.getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
        emitter.off(EVENT_IS_WRAP_TEXT_CHANGE);
        emitter.off(EVENT_PARENT_CAN_FOCUS_CHANGE);
        emitter.off(EVENT_PARENT_CAN_HOVER_CHANGE);
        emitter.off(EVENT_PARENT_FRONT_COLOR_CHANGE);
    }

    calculatedRightWidth() {
        if (this.operateItemV2?.text || this.operateItemV2?.button) {
            return RIGHT_PART_WIDTH;
        }
        if (this.operateItemV2?.switch) {
            return RIGHT_ONLY_SWITCH_WIDTH;
        } else if (this.operateItemV2?.checkbox) {
            return RIGHT_ONLY_CHECKBOX_WIDTH;
        } else if (this.operateItemV2?.radio) {
            return RIGHT_ONLY_RADIO_WIDTH;
        } else if (this.operateItemV2?.icon) {
            if (this.operateItemV2?.subIcon) {
                return RIGHT_ICON_SUB_ICON_WIDTH;
            }
            return RIGHT_ONLY_ICON_WIDTH;
        } else if (this.operateItemV2?.symbolStyle) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        } else if (this.operateItemV2?.image) {
            return RIGHT_ONLY_IMAGE_WIDTH;
        } else if (this.operateItemV2?.arrow) {
            return RIGHT_ONLY_ARROW_WIDTH;
        }
        return RIGHT_CONTENT_NULL_RIGHTWIDTH;
    }

    decideContentItemDirection() {
        if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 &&
            this.contentItemV2?.iconStyle && this.contentItemV2?.iconStyle > IconTypeV2.HEAD_SCULPTURE) {
            return FlexDirection.Column;
        }
        return FlexDirection.Row;
    }

    decideContainerDirection() {
        if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1 || !this.contentItemV2) {
            return FlexDirection.Row;
        }
        if (this.operateItemV2?.button) {
            return FlexDirection.Column;
        } else if (this.operateItemV2?.symbolStyle) {
            return FlexDirection.Row;
        } else if (this.operateItemV2?.image) {
            return FlexDirection.Row;
        } else if (this.operateItemV2?.icon && this.operateItemV2?.text) {
            return FlexDirection.Column;
        } else if (this.operateItemV2?.arrow) {
            if (!this.operateItemV2?.text) {
                return FlexDirection.Row;
            }
            this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
            return FlexDirection.Column;
        } else if (this.operateItemV2?.text) {
            return FlexDirection.Column;
        } else {
            return FlexDirection.Row;
        }
    }

    isSingleLine() {
        return !this.contentItemV2?.secondaryText && !this.contentItemV2?.description;
    }

    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let f36 = this.contentItemV2?.iconStyle ?? IconTypeV2.BADGE;
        let g36 = ICON_SIZE_MAP.get(f36);
        if (this.contentItemV2?.icon && g36 !== undefined && g36 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(g36 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
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
            let c36 = LengthMetrics.resource(ITEM_PADDING).value;
            let d36 = c36 > LISTITEM_PADDING;
            let e36 = d36 ? c36 - LISTITEM_PADDING : 0;
            return {
                top: this.isWrapText ? c36 : 0,
                bottom: this.isWrapText ? c36 : 0,
                left: e36,
                right: e36
            };
        } else {
            return undefined;
        }
    }

    initialRender() {
        this.observeComponentCreation2((a36, b36) => {
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
                if (this.operateItemV2?.icon && this.operateItemV2.icon?.action) {
                    this.operateItemV2.icon.action();
                }
                if (this.operateItemV2?.subIcon && this.operateItemV2.subIcon?.action) {
                    this.operateItemV2.subIcon.action();
                }
                if (this.operateItemV2?.arrow && this.operateItemV2.arrow?.action) {
                    this.operateItemV2.arrow.action();
                }
                if (this.operateItemV2?.radio) {
                    this.operateItemStructRef.changeRadioState();
                }
                if (this.operateItemV2?.checkbox) {
                    this.operateItemStructRef.changeCheckboxState();
                }
                if (this.operateItemV2?.switch) {
                    this.operateItemStructRef.changeSwitchState();
                }
            });
            Stack.scale(this.listScale);
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
        this.observeComponentCreation2((x35, y35) => {
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
            Flex.backgroundColor(this.frontColor);
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((z35) => {
                if (this.isFocus && !IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isHover = false;
                    return;
                }
                this.isHover = z35;
                if (this.canHover) {
                    this.frontColor = z35 ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.frontColor = z35 ? FOCUSED_BG_COLOR : NORMAL_BG_COLOR;
                    z35 ? this.zoomIn() : this.zoomOut();
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
            Flex.backgroundColor(this.touchDownColor);
            ViewStackProcessor.visualState();
            Flex.padding(this.containerPadding);
        }, Flex);
        this.observeComponentCreation2((r35, s35) => {
            If.create();
            if (this.contentItemV2 === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((t35, u35) => {
                            if (u35) {
                                let v35 = new ContentItemStruct(this, {}, undefined, t35, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/composelistitemv2/source/composelistitemv2.ets',
                                    line: 1454,
                                    col: 11
                                });
                                ViewV2.create(v35);
                                let w35 = () => {
                                    return {};
                                };
                                v35.paramsGenerator_ = w35;
                            } else {
                                this.updateStateVarsOfChildByElmtId(t35, {});
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
        this.observeComponentCreation2((l35, m35) => {
            If.create();
            if (this.contentItemV2 !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((n35, o35) => {
                            if (o35) {
                                let p35 = new ContentItemStruct(this, {
                                    icon: this.contentItemV2?.icon,
                                    symbolStyle: this.contentItemV2?.symbolStyle,
                                    iconStyle: this.contentItemV2?.iconStyle,
                                    primaryText: this.contentItemV2?.primaryText,
                                    secondaryText: this.contentItemV2?.secondaryText,
                                    description: this.contentItemV2?.description,
                                    fontSizeScale: this.fontSizeScale,
                                    parentDirection: this.containerDirection,
                                    itemDirection: this.contentItemDirection,
                                    isFocus: this.isFocus,
                                    itemHeight: this.itemHeight
                                }, undefined, n35, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/composelistitemv2/source/composelistitemv2.ets',
                                    line: 1457,
                                    col: 11
                                });
                                ViewV2.create(p35);
                                let q35 = () => {
                                    return {
                                        icon: this.contentItemV2?.icon,
                                        symbolStyle: this.contentItemV2?.symbolStyle,
                                        iconStyle: this.contentItemV2?.iconStyle,
                                        primaryText: this.contentItemV2?.primaryText,
                                        secondaryText: this.contentItemV2?.secondaryText,
                                        description: this.contentItemV2?.description,
                                        fontSizeScale: this.fontSizeScale,
                                        parentDirection: this.containerDirection,
                                        itemDirection: this.contentItemDirection,
                                        isFocus: this.isFocus,
                                        itemHeight: this.itemHeight
                                    };
                                };
                                p35.paramsGenerator_ = q35;
                            } else {
                                this.updateStateVarsOfChildByElmtId(n35, {
                                    icon: this.contentItemV2?.icon,
                                    symbolStyle: this.contentItemV2?.symbolStyle,
                                    iconStyle: this.contentItemV2?.iconStyle,
                                    primaryText: this.contentItemV2?.primaryText,
                                    secondaryText: this.contentItemV2?.secondaryText,
                                    description: this.contentItemV2?.description,
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
        this.observeComponentCreation2((d35, e35) => {
            If.create();
            if (this.operateItemV2 !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j35, k35) => {
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
                        this.observeComponentCreation2((f35, g35) => {
                            if (g35) {
                                let h35 = new OperateItemStruct(this, {
                                    icon: this.operateItemV2?.icon,
                                    subIcon: this.operateItemV2?.subIcon,
                                    button: this.operateItemV2?.button,
                                    switch: this.operateItemV2?.switch,
                                    checkBox: this.operateItemV2?.checkbox,
                                    radio: this.operateItemV2?.radio,
                                    image: this.operateItemV2?.image,
                                    symbolStyle: this.operateItemV2?.symbolStyle,
                                    text: this.operateItemV2?.text,
                                    arrow: this.operateItemV2?.arrow,
                                    parentCanFocus: this.canFocus,
                                    parentCanTouch: this.canTouch,
                                    parentIsHover: this.isHover,
                                    parentFrontColor: this.frontColor,
                                    parentIsActive: this.isActive,
                                    parentCanHover: this.canHover,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.containerDirection,
                                    isFocus: this.isFocus
                                }, undefined, f35, () => {
                                }, {
                                    page: 'library/src/main/ets/components/0508/composelistitemv2/source/composelistitemv2.ets',
                                    line: 1472,
                                    col: 11
                                });
                                ViewV2.create(h35);
                                let i35 = () => {
                                    return {
                                        icon: this.operateItemV2?.icon,
                                        subIcon: this.operateItemV2?.subIcon,
                                        button: this.operateItemV2?.button,
                                        switch: this.operateItemV2?.switch,
                                        checkBox: this.operateItemV2?.checkbox,
                                        radio: this.operateItemV2?.radio,
                                        image: this.operateItemV2?.image,
                                        symbolStyle: this.operateItemV2?.symbolStyle,
                                        text: this.operateItemV2?.text,
                                        arrow: this.operateItemV2?.arrow,
                                        parentCanFocus: this.canFocus,
                                        parentCanTouch: this.canTouch,
                                        parentIsHover: this.isHover,
                                        parentFrontColor: this.frontColor,
                                        parentIsActive: this.isActive,
                                        parentCanHover: this.canHover,
                                        rightWidth: this.calculatedRightWidth(),
                                        parentDirection: this.containerDirection,
                                        isFocus: this.isFocus
                                    };
                                };
                                h35.paramsGenerator_ = i35;
                            } else {
                                this.updateStateVarsOfChildByElmtId(f35, {
                                    icon: this.operateItemV2?.icon,
                                    subIcon: this.operateItemV2?.subIcon,
                                    button: this.operateItemV2?.button,
                                    switch: this.operateItemV2?.switch,
                                    checkBox: this.operateItemV2?.checkbox,
                                    radio: this.operateItemV2?.radio,
                                    image: this.operateItemV2?.image,
                                    symbolStyle: this.operateItemV2?.symbolStyle,
                                    text: this.operateItemV2?.text,
                                    arrow: this.operateItemV2?.arrow,
                                    parentCanFocus: this.canFocus,
                                    parentCanTouch: this.canTouch,
                                    parentIsHover: this.isHover,
                                    parentFrontColor: this.frontColor,
                                    parentIsActive: this.isActive,
                                    parentCanHover: this.canHover,
                                    rightWidth: this.calculatedRightWidth(),
                                    parentDirection: this.containerDirection,
                                    isFocus: this.isFocus
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

    updateStateVars(c35) {
        if (c35 === undefined) {
            return;
        }
        if ('contentItemV2' in c35) {
            this.updateParam('contentItemV2', c35.contentItemV2);
        }
        if ('operateItemV2' in c35) {
            this.updateParam('operateItemV2', c35.operateItemV2);
        }
    }

    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], ComposeListItemV2.prototype, 'contentItemV2', void 0);
__decorate([
    Param
], ComposeListItemV2.prototype, 'operateItemV2', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'frontColor', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'borderSize', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'canFocus', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'canTouch', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'canHover', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'isHover', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'itemHeight', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'isActive', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'hoveringColor', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'touchDownColor', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'activedColor', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'focusOutlineColor', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'fontSizeScale', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'containerDirection', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'contentItemDirection', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'containerPadding', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'textArrowLeftSafeOffset', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'accessibilityTextBuilder', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'isFocus', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'isWrapText', void 0);
__decorate([
    Local
], ComposeListItemV2.prototype, 'listScale', void 0);
__decorate([
    Monitor('contentItemV2', 'operateItemV2')
], ComposeListItemV2.prototype, 'onPropChange', null);
__decorate([
    Monitor('isWrapText')
], ComposeListItemV2.prototype, 'onWrapChange', null);
__decorate([
    Monitor('fontSizeScale')
], ComposeListItemV2.prototype, 'onFontSizeScaleChange', null);

export default {
    IconTypeV2, ComposeListItemV2
};