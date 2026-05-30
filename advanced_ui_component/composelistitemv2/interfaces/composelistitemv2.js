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
var __decorate = (this && this.__decorate) || function (v9, w9, x9, y9) {
    var z9 = arguments.length, a10 = z9 < 3 ? w9 : y9 === null ? y9 = Object.getOwnPropertyDescriptor(w9, x9) : y9, b10;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function')
        a10 = Reflect.decorate(v9, w9, x9, y9); else
        for (var c10 = v9.length - 1; c10 >= 0; c10--)
            if (b10 = v9[c10])
                a10 = (z9 < 3 ? b10(a10) : z9 > 3 ? b10(w9, x9, a10) : b10(w9, x9)) || a10;
    return z9 > 3 && a10 && Object.defineProperty(w9, x9, a10), a10;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const emitter = requireNapi('events.emitter');

export var IconTypeV2;
(function (u9) {
    u9[u9['BADGE'] = 1] = 'BADGE';
    u9[u9['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    u9[u9['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    u9[u9['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    u9[u9['APP_ICON'] = 5] = 'APP_ICON';
    u9[u9['PREVIEW'] = 6] = 'PREVIEW';
    u9[u9['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    u9[u9['VERTICAL'] = 8] = 'VERTICAL';
})(IconTypeV2 || (IconTypeV2 = {}));
var FontSizeScaleLevel;
(function (t9) {
    t9[t9['LEVEL1'] = 1.75] = 'LEVEL1';
    t9[t9['LEVEL2'] = 2] = 'LEVEL2';
    t9[t9['LEVEL3'] = 3.2] = 'LEVEL3';
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (s9) {
    s9[s9['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    s9[s9['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    s9[s9['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    s9[s9['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    s9[s9['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
})(ItemHeight || (ItemHeight = {}));
let OperateIconV2 = class OperateIconV2 {
    constructor(r9) {
        this.value = '';
        if (r9) {
            if (r9.value !== undefined) {
                this.value = r9.value;
            }
            if (r9.symbolStyle !== undefined) {
                this.symbolStyle = r9.symbolStyle;
            }
            if (r9.action !== undefined) {
                this.action = r9.action;
            }
            if (r9.accessibilityText !== undefined) {
                this.accessibilityText = r9.accessibilityText;
            }
            if (r9.accessibilityDescription !== undefined) {
                this.accessibilityDescription = r9.accessibilityDescription;
            }
            if (r9.accessibilityLevel !== undefined) {
                this.accessibilityLevel = r9.accessibilityLevel;
            }
        }
    }
};
__decorate([
    Trace
], OperateIconV2.prototype, 'value', void 0);
__decorate([
    Trace
], OperateIconV2.prototype, 'symbolStyle', void 0);
__decorate([
    Trace
], OperateIconV2.prototype, 'action', void 0);
__decorate([
    Trace
], OperateIconV2.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], OperateIconV2.prototype, 'accessibilityDescription', void 0);
__decorate([
    Trace
], OperateIconV2.prototype, 'accessibilityLevel', void 0);
OperateIconV2 = __decorate([
    ObservedV2
], OperateIconV2);

export { OperateIconV2 };
let OperateCheckV2 = class OperateCheckV2 {
    constructor(q9) {
        if (q9) {
            if (q9.isCheck !== undefined) {
                this.isCheck = q9.isCheck;
            }
            if (q9.onChange !== undefined) {
                this.onChange = q9.onChange;
            }
            if (q9.accessibilityText !== undefined) {
                this.accessibilityText = q9.accessibilityText;
            }
            if (q9.accessibilityDescription !== undefined) {
                this.accessibilityDescription = q9.accessibilityDescription;
            }
            if (q9.accessibilityLevel !== undefined) {
                this.accessibilityLevel = q9.accessibilityLevel;
            }
        }
    }
};
__decorate([
    Trace
], OperateCheckV2.prototype, 'isCheck', void 0);
__decorate([
    Trace
], OperateCheckV2.prototype, 'onChange', void 0);
__decorate([
    Trace
], OperateCheckV2.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], OperateCheckV2.prototype, 'accessibilityDescription', void 0);
__decorate([
    Trace
], OperateCheckV2.prototype, 'accessibilityLevel', void 0);
OperateCheckV2 = __decorate([
    ObservedV2
], OperateCheckV2);

export { OperateCheckV2 };
let OperateButtonV2 = class OperateButtonV2 {
    constructor(p9) {
        if (p9) {
            if (p9.text !== undefined) {
                this.text = p9.text;
            }
            if (p9.accessibilityText !== undefined) {
                this.accessibilityText = p9.accessibilityText;
            }
            if (p9.accessibilityDescription !== undefined) {
                this.accessibilityDescription = p9.accessibilityDescription;
            }
            if (p9.accessibilityLevel !== undefined) {
                this.accessibilityLevel = p9.accessibilityLevel;
            }
        }
    }
};
__decorate([
    Trace
], OperateButtonV2.prototype, 'text', void 0);
__decorate([
    Trace
], OperateButtonV2.prototype, 'accessibilityText', void 0);
__decorate([
    Trace
], OperateButtonV2.prototype, 'accessibilityDescription', void 0);
__decorate([
    Trace
], OperateButtonV2.prototype, 'accessibilityLevel', void 0);
OperateButtonV2 = __decorate([
    ObservedV2
], OperateButtonV2);

export { OperateButtonV2 };
let ContentItemV2 = class ContentItemV2 {
    constructor(o9) {
        if (o9) {
            if (o9.iconStyle !== undefined) {
                this.iconStyle = o9.iconStyle;
            }
            if (o9.icon !== undefined) {
                this.icon = o9.icon;
            }
            if (o9.symbolStyle !== undefined) {
                this.symbolStyle = o9.symbolStyle;
            }
            if (o9.primaryText !== undefined) {
                this.primaryText = o9.primaryText;
            }
            if (o9.secondaryText !== undefined) {
                this.secondaryText = o9.secondaryText;
            }
            if (o9.description !== undefined) {
                this.description = o9.description;
            }
        }
    }
};
__decorate([
    Trace
], ContentItemV2.prototype, 'iconStyle', void 0);
__decorate([
    Trace
], ContentItemV2.prototype, 'icon', void 0);
__decorate([
    Trace
], ContentItemV2.prototype, 'symbolStyle', void 0);
__decorate([
    Trace
], ContentItemV2.prototype, 'primaryText', void 0);
__decorate([
    Trace
], ContentItemV2.prototype, 'secondaryText', void 0);
__decorate([
    Trace
], ContentItemV2.prototype, 'description', void 0);
ContentItemV2 = __decorate([
    ObservedV2
], ContentItemV2);

export { ContentItemV2 };
let OperateItemV2 = class OperateItemV2 {
    constructor(n9) {
        if (n9) {
            if (n9.icon !== undefined) {
                this.icon = n9.icon;
            }
            if (n9.subIcon !== undefined) {
                this.subIcon = n9.subIcon;
            }
            if (n9.button !== undefined) {
                this.button = n9.button;
            }
            if (n9.toggle !== undefined) {
                this.toggle = n9.toggle;
            }
            if (n9.checkbox !== undefined) {
                this.checkbox = n9.checkbox;
            }
            if (n9.radio !== undefined) {
                this.radio = n9.radio;
            }
            if (n9.image !== undefined) {
                this.image = n9.image;
            }
            if (n9.symbolStyle !== undefined) {
                this.symbolStyle = n9.symbolStyle;
            }
            if (n9.text !== undefined) {
                this.text = n9.text;
            }
            if (n9.arrow !== undefined) {
                this.arrow = n9.arrow;
            }
        }
    }
};
__decorate([
    Trace
], OperateItemV2.prototype, 'icon', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'subIcon', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'button', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'toggle', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'checkbox', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'radio', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'image', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'symbolStyle', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'text', void 0);
__decorate([
    Trace
], OperateItemV2.prototype, 'arrow', void 0);
OperateItemV2 = __decorate([
    ObservedV2
], OperateItemV2);

export { OperateItemV2 };
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
    static isSymbolResource(l9) {
        if (!Util.isResourceType(l9)) {
            return false;
        }
        let m9 = l9;
        return m9.type === RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(k9) {
        if (!k9) {
            return false;
        }
        if (typeof k9 === 'string' || typeof k9 === 'undefined') {
            return false;
        }
        return true;
    }
}

class ContentItemStruct extends ViewV2 {
    constructor(e9, f9, g9, h9 = -1, i9, j9) {
        super(e9, h9, j9);
        this.initParam('iconStyle', (f9 && 'iconStyle' in f9) ? f9.iconStyle : null);
        this.initParam('icon', (f9 && 'icon' in f9) ? f9.icon : null);
        this.initParam('symbolStyle', (f9 && 'symbolStyle' in f9) ? f9.symbolStyle : null);
        this.initParam('primaryText', (f9 && 'primaryText' in f9) ? f9.primaryText : null);
        this.initParam('secondaryText', (f9 && 'secondaryText' in f9) ? f9.secondaryText : null);
        this.initParam('description', (f9 && 'description' in f9) ? f9.description : null);
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.initParam('leftWidth', (f9 && 'leftWidth' in f9) ? f9.leftWidth : LEFT_PART_WIDTH);
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
        this.initParam('fontSizeScale', (f9 && 'fontSizeScale' in f9) ? f9.fontSizeScale : 1);
        this.initParam('parentDirection', (f9 && 'parentDirection' in f9) ? f9.parentDirection : FlexDirection.Row);
        this.initParam('itemDirection', (f9 && 'itemDirection' in f9) ? f9.itemDirection : FlexDirection.Row);
        this.initParam('isFocus', (f9 && 'isFocus' in f9) ? f9.isFocus : false);
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
        this.initParam('itemHeight', (f9 && 'itemHeight' in f9) ? f9.itemHeight : null);
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

    resetStateVarsOnReuse(d9) {
        this.resetParam('iconStyle', (d9 && 'iconStyle' in d9) ? d9.iconStyle : null);
        this.resetParam('icon', (d9 && 'icon' in d9) ? d9.icon : null);
        this.resetParam('symbolStyle', (d9 && 'symbolStyle' in d9) ? d9.symbolStyle : null);
        this.resetParam('primaryText', (d9 && 'primaryText' in d9) ? d9.primaryText : null);
        this.resetParam('secondaryText', (d9 && 'secondaryText' in d9) ? d9.secondaryText : null);
        this.resetParam('description', (d9 && 'description' in d9) ? d9.description : null);
        this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        this.resetParam('leftWidth', (d9 && 'leftWidth' in d9) ? d9.leftWidth : LEFT_PART_WIDTH);
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
        this.resetParam('fontSizeScale', (d9 && 'fontSizeScale' in d9) ? d9.fontSizeScale : 1);
        this.resetParam('parentDirection', (d9 && 'parentDirection' in d9) ? d9.parentDirection : FlexDirection.Row);
        this.resetParam('itemDirection', (d9 && 'itemDirection' in d9) ? d9.itemDirection : FlexDirection.Row);
        this.resetParam('isFocus', (d9 && 'isFocus' in d9) ? d9.isFocus : false);
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
        this.resetParam('itemHeight', (d9 && 'itemHeight' in d9) ? d9.itemHeight : null);
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
        let c9 = {
            data: { isWrapText: this.isWrapText }
        };
        emitter.emit({ eventId: EVENT_IS_WRAP_TEXT_CHANGE }, c9);
    }

    onWillApplyTheme(b9) {
        this.primaryTextColor = b9.colors.fontPrimary;
        this.secondaryTextColor = b9.colors.fontSecondary;
        this.descriptionColor = b9.colors.fontTertiary;
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

    judgeIsWrap(x8, y8, z8) {
        let a9 = this.getSingleRowTextHeight(x8, y8);
        return z8 > a9;
    }

    getSingleRowTextHeight(s8, t8) {
        if (s8 && t8) {
            let u8 = measure.measureTextSize({
                textContent: s8,
                fontSize: t8,
                maxLines: TEXT_MAX_LINE
            });
            if (u8 && u8.height) {
                let v8 = 0;
                if (typeof u8.height === 'number') {
                    v8 = u8.height;
                } else if (typeof u8.height === 'string') {
                    v8 = parseFloat(u8.height);
                }
                let w8 = px2vp(v8);
                return w8;
            }
        }
        return 0;
    }

    aboutToAppear() {
        this.onPropChange();
    }

    createIcon(b8 = null) {
        this.observeComponentCreation2((c8, d8) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e8, f8) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q8, r8) => {
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
                                this.observeComponentCreation2((g8, h8) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.icon)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o8, p8) => {
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
                                            this.observeComponentCreation2((i8, j8) => {
                                                If.create();
                                                if (this.iconStyle <= IconTypeV2.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((m8, n8) => {
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
                                                        this.observeComponentCreation2((k8, l8) => {
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

    createText(f7 = null) {
        this.observeComponentCreation2((z7, a8) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((u7, v7) => {
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
            Text.onSizeChange((w7, x7) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT && x7.height) {
                    let y7 = typeof x7.height === 'number' ? x7.height : 0;
                    this.isWrapFirstText = this.judgeIsWrap(this.primaryText, this.primaryTextSize, y7);
                }
            });
        }, Text);
        Text.pop();
        this.observeComponentCreation2((n7, o7) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((p7, q7) => {
                        Text.create(this.secondaryText);
                        Text.fontSize(this.secondaryThirdTextSize);
                        Text.fontColor(this.secondaryTextColors);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                                TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((r7, s7) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT && s7.height) {
                                let t7 = typeof s7.height === 'number' ? s7.height : 0;
                                this.isWrapSecondText =
                                    this.judgeIsWrap(this.secondaryText, this.secondaryThirdTextSize, t7);
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
        this.observeComponentCreation2((g7, h7) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i7, j7) => {
                        Text.create(this.description);
                        Text.fontSize(this.secondaryThirdTextSize);
                        Text.fontColor(this.descriptionColors);
                        Text.textOverflow({
                            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
                                TextOverflow.Ellipsis
                        });
                        Text.draggable(false);
                        Text.onSizeChange((k7, l7) => {
                            if (!IS_SUPPORT_SUBCOMPONENT_EVENT && l7.height) {
                                let m7 = typeof l7.height === 'number' ? l7.height : 0;
                                this.isWrapThirdText =
                                    this.judgeIsWrap(this.description, this.secondaryThirdTextSize, m7);
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
        this.observeComponentCreation2((d7, e7) => {
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

    updateStateVars(c7) {
        if (c7 === undefined) {
            return;
        }
        if ('iconStyle' in c7) {
            this.updateParam('iconStyle', c7.iconStyle);
        }
        if ('icon' in c7) {
            this.updateParam('icon', c7.icon);
        }
        if ('symbolStyle' in c7) {
            this.updateParam('symbolStyle', c7.symbolStyle);
        }
        if ('primaryText' in c7) {
            this.updateParam('primaryText', c7.primaryText);
        }
        if ('secondaryText' in c7) {
            this.updateParam('secondaryText', c7.secondaryText);
        }
        if ('description' in c7) {
            this.updateParam('description', c7.description);
        }
        if ('leftWidth' in c7) {
            this.updateParam('leftWidth', c7.leftWidth);
        }
        if ('fontSizeScale' in c7) {
            this.updateParam('fontSizeScale', c7.fontSizeScale);
        }
        if ('parentDirection' in c7) {
            this.updateParam('parentDirection', c7.parentDirection);
        }
        if ('itemDirection' in c7) {
            this.updateParam('itemDirection', c7.itemDirection);
        }
        if ('isFocus' in c7) {
            this.updateParam('isFocus', c7.isFocus);
        }
        if ('itemHeight' in c7) {
            this.updateParam('itemHeight', c7.itemHeight);
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
        this.changeToggleState = () => {
        };
    }
}

class OperateItemStruct extends ViewV2 {
    constructor(w6, x6, y6, z6 = -1, a7, b7) {
        super(w6, z6, b7);
        this.initParam('arrow', (x6 && 'arrow' in x6) ? x6.arrow : null);
        this.initParam('icon', (x6 && 'icon' in x6) ? x6.icon : null);
        this.initParam('subIcon', (x6 && 'subIcon' in x6) ? x6.subIcon : null);
        this.initParam('button', (x6 && 'button' in x6) ? x6.button : null);
        this.initParam('toggle', (x6 && 'toggle' in x6) ? x6.toggle : null);
        this.initParam('checkBox', (x6 && 'checkBox' in x6) ? x6.checkBox : null);
        this.initParam('radio', (x6 && 'radio' in x6) ? x6.radio : null);
        this.initParam('image', (x6 && 'image' in x6) ? x6.image : null);
        this.initParam('symbolStyle', (x6 && 'symbolStyle' in x6) ? x6.symbolStyle : null);
        this.initParam('text', (x6 && 'text' in x6) ? x6.text : null);
        this.toggleState = false;
        this.radioState = false;
        this.checkBoxState = false;
        this.initParam('rightWidth', (x6 && 'rightWidth' in x6) ? x6.rightWidth : RIGHT_PART_WIDTH);
        this.secondaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.hoveringColor = '#0d000000';
        this.activedColor = '#1a0a59f7';
        this.initParam('parentCanFocus', (x6 && 'parentCanFocus' in x6) ? x6.parentCanFocus : false);
        this.initParam('parentCanTouch', (x6 && 'parentCanTouch' in x6) ? x6.parentCanTouch : true);
        this.initParam('parentIsHover', (x6 && 'parentIsHover' in x6) ? x6.parentIsHover : false);
        this.initParam('parentCanHover', (x6 && 'parentCanHover' in x6) ? x6.parentCanHover : true);
        this.initParam('parentIsActive', (x6 && 'parentIsActive' in x6) ? x6.parentIsActive : false);
        this.initParam('parentFrontColor', (x6 && 'parentFrontColor' in x6) ? x6.parentFrontColor : NORMAL_BG_COLOR);
        this.initParam('parentDirection', (x6 && 'parentDirection' in x6) ? x6.parentDirection : FlexDirection.Row);
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.initParam('isFocus', (x6 && 'isFocus' in x6) ? x6.isFocus : false);
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
        this.changeToggleState = () => {
            this.toggleState = !this.toggleState;
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(v6) {
        this.resetParam('arrow', (v6 && 'arrow' in v6) ? v6.arrow : null);
        this.resetParam('icon', (v6 && 'icon' in v6) ? v6.icon : null);
        this.resetParam('subIcon', (v6 && 'subIcon' in v6) ? v6.subIcon : null);
        this.resetParam('button', (v6 && 'button' in v6) ? v6.button : null);
        this.resetParam('toggle', (v6 && 'toggle' in v6) ? v6.toggle : null);
        this.resetParam('checkBox', (v6 && 'checkBox' in v6) ? v6.checkBox : null);
        this.resetParam('radio', (v6 && 'radio' in v6) ? v6.radio : null);
        this.resetParam('image', (v6 && 'image' in v6) ? v6.image : null);
        this.resetParam('symbolStyle', (v6 && 'symbolStyle' in v6) ? v6.symbolStyle : null);
        this.resetParam('text', (v6 && 'text' in v6) ? v6.text : null);
        this.toggleState = false;
        this.radioState = false;
        this.checkBoxState = false;
        this.resetParam('rightWidth', (v6 && 'rightWidth' in v6) ? v6.rightWidth : RIGHT_PART_WIDTH);
        this.secondaryTextColor = {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_secondary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
        this.hoveringColor = '#0d000000';
        this.activedColor = '#1a0a59f7';
        this.resetParam('parentCanFocus', (v6 && 'parentCanFocus' in v6) ? v6.parentCanFocus : false);
        this.resetParam('parentCanTouch', (v6 && 'parentCanTouch' in v6) ? v6.parentCanTouch : true);
        this.resetParam('parentIsHover', (v6 && 'parentIsHover' in v6) ? v6.parentIsHover : false);
        this.resetParam('parentCanHover', (v6 && 'parentCanHover' in v6) ? v6.parentCanHover : true);
        this.resetParam('parentIsActive', (v6 && 'parentIsActive' in v6) ? v6.parentIsActive : false);
        this.resetParam('parentFrontColor', (v6 && 'parentFrontColor' in v6) ? v6.parentFrontColor : NORMAL_BG_COLOR);
        this.resetParam('parentDirection', (v6 && 'parentDirection' in v6) ? v6.parentDirection : FlexDirection.Row);
        this.rowSpace = DEFAULT_ROW_SPACE;
        this.resetParam('isFocus', (v6 && 'isFocus' in v6) ? v6.isFocus : false);
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
        if (this.toggle != null) {
            this.toggleState = this.toggle.isCheck;
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

    onWillApplyTheme(u6) {
        this.secondaryTextColor = u6.colors.fontSecondary;
        this.hoveringColor = u6.colors.interactiveHover;
        this.activedColor = u6.colors.interactiveActive;
    }

    aboutToAppear() {
        this.onPropChange();
        this.onFocusChange();
        if (this.controller) {
            this.controller.changeRadioState = this.changeRadioState;
            this.controller.changeCheckboxState = this.changeCheckboxState;
            this.controller.changeToggleState = this.changeToggleState;
        }
    }

    createButton(m6 = null) {
        this.observeComponentCreation2((r6, s6) => {
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
            Button.onHover((t6) => {
                this.notifyParentCanHoverChange(false);
                if (t6 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!t6) {
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
        this.observeComponentCreation2((p6, q6) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((n6, o6) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }

    createIcon(x5, y5 = null) {
        this.observeComponentCreation2((j6, k6) => {
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
            Button.onHover((l6) => {
                this.notifyParentCanHoverChange(false);
                if (l6 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!l6) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
            Button.onClick(x5.icon?.action);
            Button.accessibilityLevel(getAccessibilityLevelOnAction(x5.icon?.accessibilityLevel, x5.icon?.action));
            Button.accessibilityText(getAccessibilityText(x5.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(x5.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((z5, a6) => {
            If.create();
            if (x5.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h6, i6) => {
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([this.iconColor]);
                        SymbolGlyph.attributeModifier.bind(this)(x5.icon?.symbolStyle);
                        SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((b6, c6) => {
                        If.create();
                        if (Util.isSymbolResource(x5.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f6, g6) => {
                                    SymbolGlyph.create(x5.icon?.value);
                                    SymbolGlyph.fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`);
                                    SymbolGlyph.fontColor([this.iconColor]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((d6, e6) => {
                                    Image.create(x5.icon?.value);
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

    createImage(q5 = null) {
        this.observeComponentCreation2((r5, s5) => {
            If.create();
            if (Util.isSymbolResource(this.image)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v5, w5) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((t5, u5) => {
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

    createSymbol(n5 = null) {
        this.observeComponentCreation2((o5, p5) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(this.symbolStyle);
            SymbolGlyph.fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }

    createText(k5 = null) {
        this.observeComponentCreation2((l5, m5) => {
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

    createArrow(w4 = null) {
        this.observeComponentCreation2((h5, i5) => {
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
            Button.onHover((j5) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (j5 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
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
        this.observeComponentCreation2((x4, y4) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f5, g5) => {
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
                    this.observeComponentCreation2((z4, a5) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d5, e5) => {
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
                                this.observeComponentCreation2((b5, c5) => {
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

    createRadio(r4 = null) {
        this.observeComponentCreation2((s4, t4) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.radioStyle({
                uncheckedBorderColor: DEFUALT_RADIO_CHECKBOX_BORDER_COLOR
            });
            Radio.backgroundColor(Color.Transparent);
            Radio.borderRadius(OPERATE_ITEM_RADIUS);
            Radio.onChange((v4) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.radioState = v4;
                }
                if (this.radio?.onChange) {
                    this.radio?.onChange(v4);
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
            Radio.onHover((u4) => {
                this.notifyParentCanHoverChange(false);
                if (u4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!u4) {
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

    createCheckBox(m4 = null) {
        this.observeComponentCreation2((n4, o4) => {
            Checkbox.create();
            Checkbox.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Checkbox.unselectedColor(DEFUALT_RADIO_CHECKBOX_BORDER_COLOR);
            Checkbox.backgroundColor(Color.Transparent);
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange((q4) => {
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.checkBoxState = q4;
                }
                if (this.checkBox?.onChange) {
                    this.checkBox?.onChange(q4);
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
            Checkbox.onHover((p4) => {
                this.notifyParentCanHoverChange(false);
                if (p4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!p4) {
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

    createToggle(f4 = null) {
        this.observeComponentCreation2((j4, k4) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.notifyParentCanFocusChange(false);
            });
            Row.onHover((l4) => {
                this.notifyParentCanHoverChange(false);
                if (l4 && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor :
                        Color.Transparent.toString());
                }
                if (!l4) {
                    this.notifyParentCanHoverChange(true);
                    if (this.parentIsHover) {
                        this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((g4, h4) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.toggleState });
            Toggle.borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS);
            Toggle.backgroundColor(Color.Transparent);
            Toggle.onChange((i4) => {
                this.toggleState = i4;
                if (this.toggle?.onChange) {
                    this.toggle?.onChange(i4);
                }
            });
            Toggle.onClick(() => {
                this.toggleState = !this.toggleState;
            });
            Toggle.hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None);
            Toggle.accessibilityLevel(getAccessibilityLevelOnChange(this.toggle?.accessibilityLevel,
                this.toggle?.onChange));
            Toggle.accessibilityText(getAccessibilityText(this.toggle?.accessibilityText ?? ''));
            Toggle.accessibilityDescription(getAccessibilityText(this.toggle?.accessibilityDescription ?? ''));
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }

    createTextArrow(x2 = null) {
        this.observeComponentCreation2((c4, d4) => {
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
            Button.onHover((e4) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (e4 && IS_SUPPORT_SUBCOMPONENT_EVENT) {
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
        this.observeComponentCreation2((y2, z2) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a4, b4) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((y3, z3) => {
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
                    this.observeComponentCreation2((o3, p3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((w3, x3) => {
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
                                this.observeComponentCreation2((q3, r3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((u3, v3) => {
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
                                            this.observeComponentCreation2((s3, t3) => {
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
                    this.observeComponentCreation2((m3, n3) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((k3, l3) => {
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
                    this.observeComponentCreation2((a3, b3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((i3, j3) => {
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
                                this.observeComponentCreation2((c3, d3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((g3, h3) => {
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
                                            this.observeComponentCreation2((e3, f3) => {
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
        let w2 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            w2.justifyContent = FlexAlign.SpaceBetween;
        } else {
            w2.space = { main: LengthMetrics.vp(this.rowSpace) };
            w2.justifyContent = FlexAlign.End;
        }
        return w2;
    }

    notifyParentCanFocusChange(v2) {
        emitter.emit({ eventId: EVENT_PARENT_CAN_FOCUS_CHANGE }, { data: { canFocus: v2 } });
    }

    notifyParentCanHoverChange(u2) {
        emitter.emit({ eventId: EVENT_PARENT_CAN_HOVER_CHANGE }, { data: { canHover: u2 } });
    }

    notifyParentFrontColorChange(t2) {
        emitter.emit({ eventId: EVENT_PARENT_FRONT_COLOR_CHANGE }, { data: { frontColor: t2 } });
    }

    initialRender() {
        this.observeComponentCreation2((r2, s2) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((n2, o2) => {
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
            } else if (this.toggle != null) {
                this.ifElseBranchUpdateFunction(9, () => {
                    this.createToggle.bind(this)();
                });
            } else if (this.icon != null) {
                this.ifElseBranchUpdateFunction(10, () => {
                    this.createIcon.bind(this)(makeBuilderParameterProxy('createIcon',
                        { icon: () => (this['__icon'] ? this['__icon'] : this['icon']) }));
                    this.observeComponentCreation2((p2, q2) => {
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

    updateStateVars(m2) {
        if (m2 === undefined) {
            return;
        }
        if ('arrow' in m2) {
            this.updateParam('arrow', m2.arrow);
        }
        if ('icon' in m2) {
            this.updateParam('icon', m2.icon);
        }
        if ('subIcon' in m2) {
            this.updateParam('subIcon', m2.subIcon);
        }
        if ('button' in m2) {
            this.updateParam('button', m2.button);
        }
        if ('toggle' in m2) {
            this.updateParam('toggle', m2.toggle);
        }
        if ('checkBox' in m2) {
            this.updateParam('checkBox', m2.checkBox);
        }
        if ('radio' in m2) {
            this.updateParam('radio', m2.radio);
        }
        if ('image' in m2) {
            this.updateParam('image', m2.image);
        }
        if ('symbolStyle' in m2) {
            this.updateParam('symbolStyle', m2.symbolStyle);
        }
        if ('text' in m2) {
            this.updateParam('text', m2.text);
        }
        if ('rightWidth' in m2) {
            this.updateParam('rightWidth', m2.rightWidth);
        }
        if ('parentCanFocus' in m2) {
            this.updateParam('parentCanFocus', m2.parentCanFocus);
        }
        if ('parentCanTouch' in m2) {
            this.updateParam('parentCanTouch', m2.parentCanTouch);
        }
        if ('parentIsHover' in m2) {
            this.updateParam('parentIsHover', m2.parentIsHover);
        }
        if ('parentCanHover' in m2) {
            this.updateParam('parentCanHover', m2.parentCanHover);
        }
        if ('parentIsActive' in m2) {
            this.updateParam('parentIsActive', m2.parentIsActive);
        }
        if ('parentFrontColor' in m2) {
            this.updateParam('parentFrontColor', m2.parentFrontColor);
        }
        if ('parentDirection' in m2) {
            this.updateParam('parentDirection', m2.parentDirection);
        }
        if ('isFocus' in m2) {
            this.updateParam('isFocus', m2.isFocus);
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
], OperateItemStruct.prototype, 'toggle', void 0);
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
], OperateItemStruct.prototype, 'toggleState', void 0);
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
    Monitor('arrow', 'icon', 'subIcon', 'button', 'toggle', 'checkBox', 'radio', 'image', 'symbolStyle', 'text')
], OperateItemStruct.prototype, 'onPropChange', null);
__decorate([
    Monitor('isFocus')
], OperateItemStruct.prototype, 'onFocusChange', null);

function getAccessibilityText(h2) {
    try {
        let l2 = '';
        if (typeof h2 === 'string') {
            l2 = h2;
        } else {
            l2 = getContext().resourceManager.getStringSync(h2);
        }
        return l2;
    } catch (i2) {
        let j2 = i2.code;
        let k2 = i2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${j2}, message: ${k2}`);
        return '';
    }
}

function getAccessibilityLevelOnChange(f2, g2) {
    if (f2) {
        return f2;
    }
    if (g2) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}

function getAccessibilityLevelOnAction(d2, e2) {
    if (d2) {
        return d2;
    }
    if (e2) {
        return ACCESSIBILITY_LEVEL_YES;
    }
    return ACCESSIBILITY_LEVEL_NO;
}

export class ComposeListItemV2 extends ViewV2 {
    constructor(s1, t1, u1, v1 = -1, w1, x1) {
        super(s1, v1, x1);
        this.initParam('contentItemV2', (t1 && 'contentItemV2' in t1) ? t1.contentItemV2 : null);
        this.initParam('operateItemV2', (t1 && 'operateItemV2' in t1) ? t1.operateItemV2 : null);
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
            onConfigurationUpdated: (z1) => {
                if (z1 === undefined || !this.isFollowingSystemFontScale) {
                    this.fontSizeScale = 1;
                    return;
                }
                try {
                    this.fontSizeScale = Math.min(this.maxFontScale, z1.fontSizeScale ?? 1);
                } catch (a2) {
                    let b2 = a2.code;
                    let c2 = a2.message;
                    hilog.error(0x3900, 'Ace', `ComposeListItemV2 environmentCallback error: ${b2}, ${c2}`);
                }
            },
            onMemoryLevel: (y1) => {
            }
        };
        this.finalizeConstruction();
    }

    resetStateVarsOnReuse(r1) {
        this.resetParam('contentItemV2', (r1 && 'contentItemV2' in r1) ? r1.contentItemV2 : null);
        this.resetParam('operateItemV2', (r1 && 'operateItemV2' in r1) ? r1.operateItemV2 : null);
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
                let q1 = this.contentItemV2.iconStyle ?? IconTypeV2.BADGE;
                this.itemHeight = q1 <= IconTypeV2.HEAD_SCULPTURE ?
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
            let p1 = this.contentItemV2.iconStyle ?? IconTypeV2.BADGE;
            if (this.contentItemV2.icon === undefined ||
                (this.contentItemV2.icon !== undefined && p1 <= IconTypeV2.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            } else {
                this.itemHeight = p1 === IconTypeV2.HEAD_SCULPTURE ? ItemHeight.FOURTH_HEIGHT : APPICON_ITEMLENGTH;
            }
        } else {
            this.itemHeight = ItemHeight.FIFTH_HEIGHT;
        }
        let n1 = this.contentItemV2?.iconStyle ?? IconTypeV2.BADGE;
        let o1 = ICON_SIZE_MAP.get(n1);
        if (o1 !== undefined && o1 >= this.itemHeight) {
            this.itemHeight = o1 + SAFE_LIST_PADDING;
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

    onWillApplyTheme(m1) {
        this.hoveringColor = m1.colors.interactiveHover;
        this.touchDownColor = m1.colors.interactivePressed;
        this.activedColor = m1.colors.interactiveActive;
        this.focusOutlineColor = m1.colors.interactiveFocus;
    }

    aboutToAppear() {
        this.fontSizeScale = this.decideFontSizeScale();
        this.onPropChange();
        try {
            this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
        } catch (j1) {
            let k1 = j1.code;
            let l1 = j1.message;
            hilog.error(0x3900, 'Ace', `ComposeListItemV2 Faild to get environment param error: ${k1}, ${l1}`);
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
            this.onFontSizeScaleChange();
        }
        emitter.on({ eventId: EVENT_IS_WRAP_TEXT_CHANGE }, (i1) => {
            if (i1.data && i1.data.isWrapText !== undefined) {
                this.isWrapText = i1.data.isWrapText;
            }
        });
        emitter.on({ eventId: EVENT_PARENT_CAN_FOCUS_CHANGE }, (h1) => {
            if (h1.data && h1.data.canFocus !== undefined) {
                this.canFocus = h1.data.canFocus;
            }
        });
        emitter.on({ eventId: EVENT_PARENT_CAN_HOVER_CHANGE }, (g1) => {
            if (g1.data && g1.data.canHover !== undefined) {
                this.canHover = g1.data.canHover;
            }
        });
        emitter.on({ eventId: EVENT_PARENT_FRONT_COLOR_CHANGE }, (f1) => {
            if (f1.data && f1.data.frontColor !== undefined) {
                this.frontColor = f1.data.frontColor;
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
        if (this.operateItemV2?.toggle) {
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
        let d1 = this.contentItemV2?.iconStyle ?? IconTypeV2.BADGE;
        let e1 = ICON_SIZE_MAP.get(d1);
        if (this.contentItemV2?.icon && e1 !== undefined && e1 <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(e1 + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
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
            let a1 = LengthMetrics.resource(ITEM_PADDING).value;
            let b1 = a1 > LISTITEM_PADDING;
            let c1 = b1 ? a1 - LISTITEM_PADDING : 0;
            return {
                top: this.isWrapText ? a1 : 0,
                bottom: this.isWrapText ? a1 : 0,
                left: c1,
                right: c1
            };
        } else {
            return undefined;
        }
    }

    initialRender() {
        this.observeComponentCreation2((y, z) => {
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
                if (this.operateItemV2?.toggle) {
                    this.operateItemStructRef.changeToggleState();
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
        this.observeComponentCreation2((v, w) => {
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
            Flex.onHover((x) => {
                if (this.isFocus && !IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.isHover = false;
                    return;
                }
                this.isHover = x;
                if (this.canHover) {
                    this.frontColor = x ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
                if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
                    this.frontColor = x ? FOCUSED_BG_COLOR : NORMAL_BG_COLOR;
                    x ? this.zoomIn() : this.zoomOut();
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
        this.observeComponentCreation2((p, q) => {
            If.create();
            if (this.contentItemV2 === null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((r, s) => {
                            if (s) {
                                let t = new ContentItemStruct(this, {}, undefined, r, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composelistitemv2.ets',
                                    line: 1615,
                                    col: 11
                                });
                                ViewV2.create(t);
                                let u = () => {
                                    return {};
                                };
                                t.paramsGenerator_ = u;
                            } else {
                                this.updateStateVarsOfChildByElmtId(r, {});
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
        this.observeComponentCreation2((j, k) => {
            If.create();
            if (this.contentItemV2 !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((l, m) => {
                            if (m) {
                                let n = new ContentItemStruct(this, {
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
                                }, undefined, l, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composelistitemv2.ets',
                                    line: 1618,
                                    col: 11
                                });
                                ViewV2.create(n);
                                let o = () => {
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
                                n.paramsGenerator_ = o;
                            } else {
                                this.updateStateVarsOfChildByElmtId(l, {
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
        this.observeComponentCreation2((b, c) => {
            If.create();
            if (this.operateItemV2 !== null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h, i) => {
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
                        this.observeComponentCreation2((d, e) => {
                            if (e) {
                                let f = new OperateItemStruct(this, {
                                    icon: this.operateItemV2?.icon,
                                    subIcon: this.operateItemV2?.subIcon,
                                    button: this.operateItemV2?.button,
                                    toggle: this.operateItemV2?.toggle,
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
                                }, undefined, d, () => {
                                }, {
                                    page: 'library/src/main/ets/components/composelistitemv2.ets',
                                    line: 1633,
                                    col: 11
                                });
                                ViewV2.create(f);
                                let g = () => {
                                    return {
                                        icon: this.operateItemV2?.icon,
                                        subIcon: this.operateItemV2?.subIcon,
                                        button: this.operateItemV2?.button,
                                        toggle: this.operateItemV2?.toggle,
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
                                f.paramsGenerator_ = g;
                            } else {
                                this.updateStateVarsOfChildByElmtId(d, {
                                    icon: this.operateItemV2?.icon,
                                    subIcon: this.operateItemV2?.subIcon,
                                    button: this.operateItemV2?.button,
                                    toggle: this.operateItemV2?.toggle,
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

    updateStateVars(a) {
        if (a === undefined) {
            return;
        }
        if ('contentItemV2' in a) {
            this.updateParam('contentItemV2', a.contentItemV2);
        }
        if ('operateItemV2' in a) {
            this.updateParam('operateItemV2', a.operateItemV2);
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
    IconTypeV2, ComposeListItemV2, ContentItemV2,
    OperateButtonV2, OperateCheckV2, OperateItemV2, OperateIconV2
};
