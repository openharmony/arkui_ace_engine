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
export var IconType;
(function (h10) {
    h10[h10['BADGE'] = 1] = 'BADGE';
    h10[h10['NORMAL_ICON'] = 2] = 'NORMAL_ICON';
    h10[h10['SYSTEM_ICON'] = 3] = 'SYSTEM_ICON';
    h10[h10['HEAD_SCULPTURE'] = 4] = 'HEAD_SCULPTURE';
    h10[h10['APP_ICON'] = 5] = 'APP_ICON';
    h10[h10['PREVIEW'] = 6] = 'PREVIEW';
    h10[h10['LONGITUDINAL'] = 7] = 'LONGITUDINAL';
    h10[h10['VERTICAL'] = 8] = 'VERTICAL';
})(IconType || (IconType = {}));
var FontSizeScaleLevel;
(function (g10) {
    g10[g10['LEVEL1'] = 1.75] = 'LEVEL1';
    g10[g10['LEVEL2'] = 2] = 'LEVEL2';
    g10[g10['LEVEL3'] = 3.2] = 'LEVEL3';
})(FontSizeScaleLevel || (FontSizeScaleLevel = {}));
var ItemHeight;
(function (f10) {
    f10[f10['FIRST_HEIGHT'] = 48] = 'FIRST_HEIGHT';
    f10[f10['SECOND_HEIGHT'] = 56] = 'SECOND_HEIGHT';
    f10[f10['THIRD_HEIGHT'] = 64] = 'THIRD_HEIGHT';
    f10[f10['FOURTH_HEIGHT'] = 72] = 'FOURTH_HEIGHT';
    f10[f10['FIFTH_HEIGHT'] = 96] = 'FIFTH_HEIGHT';
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
class Util {
    static isSymbolResource(d10) {
        if (!Util.isResourceType(d10)) {
            return false;
        }
        let e10 = d10;
        return e10.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(c10) {
        if (!c10) {
            return false;
        }
        if (typeof c10 === 'string' || typeof c10 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ContentItemStruct extends ViewPU {
    constructor(w9, x9, y9, z9 = -1, a10 = undefined, b10) {
        super(w9, y9, z9, b10);
        if (typeof a10 === 'function') {
            this.paramsGenerator_ = a10;
        }
        this.__iconStyle = new SynchedPropertySimpleOneWayPU(x9.iconStyle, this, 'iconStyle');
        this.__icon = new SynchedPropertyObjectOneWayPU(x9.icon, this, 'icon');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(x9.symbolStyle, this, 'symbolStyle');
        this.__primaryText = new SynchedPropertyObjectOneWayPU(x9.primaryText, this, 'primaryText');
        this.__secondaryText = new SynchedPropertyObjectOneWayPU(x9.secondaryText, this, 'secondaryText');
        this.__description = new SynchedPropertyObjectOneWayPU(x9.description, this, 'description');
        this.__itemRowSpace = new ObservedPropertySimplePU(NORMAL_ITEM_ROW_SPACE, this, 'itemRowSpace');
        this.__leftWidth = new SynchedPropertySimpleOneWayPU(x9.leftWidth, this, 'leftWidth');
        this.__primaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'primaryTextColor');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.__descriptionColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'descriptionColor');
        this.__fontSizeScale = new SynchedPropertySimpleOneWayPU(x9.fontSizeScale, this, 'fontSizeScale');
        this.__parentDirection = new SynchedPropertySimpleOneWayPU(x9.parentDirection, this, 'parentDirection');
        this.__itemDirection = new SynchedPropertySimpleOneWayPU(x9.itemDirection, this, 'itemDirection');
        this.setInitiallyProvidedValue(x9);
        this.declareWatch('iconStyle', this.onPropChange);
        this.declareWatch('icon', this.onPropChange);
        this.declareWatch('symbolStyle', this.onPropChange);
        this.declareWatch('primaryText', this.onPropChange);
        this.declareWatch('secondaryText', this.onPropChange);
        this.declareWatch('description', this.onPropChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v9) {
        if (v9.iconStyle === undefined) {
            this.__iconStyle.set(null);
        }
        if (v9.icon === undefined) {
            this.__icon.set(null);
        }
        if (v9.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (v9.primaryText === undefined) {
            this.__primaryText.set(null);
        }
        if (v9.secondaryText === undefined) {
            this.__secondaryText.set(null);
        }
        if (v9.description === undefined) {
            this.__description.set(null);
        }
        if (v9.itemRowSpace !== undefined) {
            this.itemRowSpace = v9.itemRowSpace;
        }
        if (v9.leftWidth === undefined) {
            this.__leftWidth.set(LEFT_PART_WIDTH);
        }
        if (v9.primaryTextColor !== undefined) {
            this.primaryTextColor = v9.primaryTextColor;
        }
        if (v9.secondaryTextColor !== undefined) {
            this.secondaryTextColor = v9.secondaryTextColor;
        }
        if (v9.descriptionColor !== undefined) {
            this.descriptionColor = v9.descriptionColor;
        }
    }
    updateStateVars(u9) {
        this.__iconStyle.reset(u9.iconStyle);
        this.__icon.reset(u9.icon);
        this.__symbolStyle.reset(u9.symbolStyle);
        this.__primaryText.reset(u9.primaryText);
        this.__secondaryText.reset(u9.secondaryText);
        this.__description.reset(u9.description);
        this.__leftWidth.reset(u9.leftWidth);
        this.__fontSizeScale.reset(u9.fontSizeScale);
        this.__parentDirection.reset(u9.parentDirection);
        this.__itemDirection.reset(u9.itemDirection);
    }
    purgeVariableDependenciesOnElmtId(t9) {
        this.__iconStyle.purgeDependencyOnElmtId(t9);
        this.__icon.purgeDependencyOnElmtId(t9);
        this.__symbolStyle.purgeDependencyOnElmtId(t9);
        this.__primaryText.purgeDependencyOnElmtId(t9);
        this.__secondaryText.purgeDependencyOnElmtId(t9);
        this.__description.purgeDependencyOnElmtId(t9);
        this.__itemRowSpace.purgeDependencyOnElmtId(t9);
        this.__leftWidth.purgeDependencyOnElmtId(t9);
        this.__primaryTextColor.purgeDependencyOnElmtId(t9);
        this.__secondaryTextColor.purgeDependencyOnElmtId(t9);
        this.__descriptionColor.purgeDependencyOnElmtId(t9);
        this.__fontSizeScale.purgeDependencyOnElmtId(t9);
        this.__parentDirection.purgeDependencyOnElmtId(t9);
        this.__itemDirection.purgeDependencyOnElmtId(t9);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get iconStyle() {
        return this.__iconStyle.get();
    }
    set iconStyle(s9) {
        this.__iconStyle.set(s9);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(r9) {
        this.__icon.set(r9);
    }
    get symbolStyle() {
        return this.__symbolStyle.get();
    }
    set symbolStyle(q9) {
        this.__symbolStyle.set(q9);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(p9) {
        this.__primaryText.set(p9);
    }
    get secondaryText() {
        return this.__secondaryText.get();
    }
    set secondaryText(o9) {
        this.__secondaryText.set(o9);
    }
    get description() {
        return this.__description.get();
    }
    set description(n9) {
        this.__description.set(n9);
    }
    get itemRowSpace() {
        return this.__itemRowSpace.get();
    }
    set itemRowSpace(m9) {
        this.__itemRowSpace.set(m9);
    }
    get leftWidth() {
        return this.__leftWidth.get();
    }
    set leftWidth(l9) {
        this.__leftWidth.set(l9);
    }
    get primaryTextColor() {
        return this.__primaryTextColor.get();
    }
    set primaryTextColor(k9) {
        this.__primaryTextColor.set(k9);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(j9) {
        this.__secondaryTextColor.set(j9);
    }
    get descriptionColor() {
        return this.__descriptionColor.get();
    }
    set descriptionColor(i9) {
        this.__descriptionColor.set(i9);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(h9) {
        this.__fontSizeScale.set(h9);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(g9) {
        this.__parentDirection.set(g9);
    }
    get itemDirection() {
        return this.__itemDirection.get();
    }
    set itemDirection(f9) {
        this.__itemDirection.set(f9);
    }
    onWillApplyTheme(e9) {
        this.primaryTextColor = e9.colors.fontPrimary;
        this.secondaryTextColor = e9.colors.fontSecondary;
        this.descriptionColor = e9.colors.fontTertiary;
    }
    onPropChange() {
        if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
            this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
        }
        else {
            this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createIcon(n8 = null) {
        this.observeComponentCreation2((o8, p8) => {
            If.create();
            if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q8, r8) => {
                        If.create();
                        if (this.symbolStyle != null) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((c9, d9) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
                                    SymbolGlyph.fontSize(ICON_SIZE_MAP.get(this.iconStyle));
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.flexShrink(0);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.icon != null) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((s8, t8) => {
                                    If.create();
                                    if (Util.isSymbolResource(ObservedObject.GetRawObject(this.icon))) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((a9, b9) => {
                                                SymbolGlyph.create(this.icon);
                                                SymbolGlyph.fontSize(ICON_SIZE_MAP.get(this.iconStyle));
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.flexShrink(0);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((u8, v8) => {
                                                If.create();
                                                if (this.iconStyle <= IconType.PREVIEW) {
                                                    this.ifElseBranchUpdateFunction(0, () => {
                                                        this.observeComponentCreation2((y8, z8) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.width(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.height(ICON_SIZE_MAP.get(this.iconStyle));
                                                            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.flexShrink(0);
                                                        }, Image);
                                                    });
                                                }
                                                else {
                                                    this.ifElseBranchUpdateFunction(1, () => {
                                                        this.observeComponentCreation2((w8, x8) => {
                                                            Image.create(this.icon);
                                                            Image.objectFit(ImageFit.Contain);
                                                            Image.constraintSize({
                                                                minWidth: SPECIAL_ICON_SIZE,
                                                                maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
                                                                minHeight: SPECIAL_ICON_SIZE,
                                                                maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
                                                            });
                                                            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                            Image.focusable(false);
                                                            Image.draggable(false);
                                                            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
    createText(a8 = null) {
        this.observeComponentCreation2((l8, m8) => {
            Column.create({ space: TEXT_COLUMN_SPACE });
            Column.flexShrink(1);
            Column.margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
                top: TEXT_SAFE_MARGIN,
                bottom: TEXT_SAFE_MARGIN
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((j8, k8) => {
            Text.create(this.primaryText);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor(ObservedObject.GetRawObject(this.primaryTextColor));
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontWeight(FontWeight.Medium);
            Text.focusable(true);
            Text.draggable(false);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((f8, g8) => {
            If.create();
            if (this.secondaryText != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h8, i8) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.draggable(false);
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
        this.observeComponentCreation2((b8, c8) => {
            If.create();
            if (this.description != null) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d8, e8) => {
                        Text.create(this.description);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(ObservedObject.GetRawObject(this.descriptionColor));
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.draggable(false);
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
        this.observeComponentCreation2((y7, z7) => {
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
    constructor(s7, t7, u7, v7 = -1, w7 = undefined, x7) {
        super(s7, u7, v7, x7);
        if (typeof w7 === 'function') {
            this.paramsGenerator_ = w7;
        }
        this.__arrow = new SynchedPropertyObjectOneWayPU(t7.arrow, this, 'arrow');
        this.__icon = new SynchedPropertyObjectOneWayPU(t7.icon, this, 'icon');
        this.__subIcon = new SynchedPropertyObjectOneWayPU(t7.subIcon, this, 'subIcon');
        this.__button = new SynchedPropertyObjectOneWayPU(t7.button, this, 'button');
        this.__switch = new SynchedPropertyObjectOneWayPU(t7.switch, this, 'switch');
        this.__checkBox = new SynchedPropertyObjectOneWayPU(t7.checkBox, this, 'checkBox');
        this.__radio = new SynchedPropertyObjectOneWayPU(t7.radio, this, 'radio');
        this.__image = new SynchedPropertyObjectOneWayPU(t7.image, this, 'image');
        this.__symbolStyle = new SynchedPropertyObjectOneWayPU(t7.symbolStyle, this, 'symbolStyle');
        this.__text = new SynchedPropertyObjectOneWayPU(t7.text, this, 'text');
        this.__switchState = new ObservedPropertySimplePU(false, this, 'switchState');
        this.__radioState = new ObservedPropertySimplePU(false, this, 'radioState');
        this.__checkBoxState = new ObservedPropertySimplePU(false, this, 'checkBoxState');
        this.__rightWidth = new SynchedPropertySimpleOneWayPU(t7.rightWidth, this, 'rightWidth');
        this.__secondaryTextColor = new ObservedPropertyObjectPU({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, this, 'secondaryTextColor');
        this.__hoveringColor = new ObservedPropertyObjectPU('#0d000000', this, 'hoveringColor');
        this.__activedColor = new ObservedPropertyObjectPU('#1a0a59f7', this, 'activedColor');
        this.__parentCanFocus = new SynchedPropertySimpleTwoWayPU(t7.parentCanFocus, this, 'parentCanFocus');
        this.__parentCanTouch = new SynchedPropertySimpleTwoWayPU(t7.parentCanTouch, this, 'parentCanTouch');
        this.__parentIsHover = new SynchedPropertySimpleTwoWayPU(t7.parentIsHover, this, 'parentIsHover');
        this.__parentCanHover = new SynchedPropertySimpleTwoWayPU(t7.parentCanHover, this, 'parentCanHover');
        this.__parentIsActive = new SynchedPropertySimpleTwoWayPU(t7.parentIsActive, this, 'parentIsActive');
        this.__parentFrontColor = new SynchedPropertyObjectTwoWayPU(t7.parentFrontColor, this, 'parentFrontColor');
        this.__parentDirection = new SynchedPropertySimpleTwoWayPU(t7.parentDirection, this, 'parentDirection');
        this.__rowSpace = new ObservedPropertySimplePU(DEFAULT_ROW_SPACE, this, 'rowSpace');
        this.setInitiallyProvidedValue(t7);
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
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r7) {
        if (r7.arrow === undefined) {
            this.__arrow.set(null);
        }
        if (r7.icon === undefined) {
            this.__icon.set(null);
        }
        if (r7.subIcon === undefined) {
            this.__subIcon.set(null);
        }
        if (r7.button === undefined) {
            this.__button.set(null);
        }
        if (r7.switch === undefined) {
            this.__switch.set(null);
        }
        if (r7.checkBox === undefined) {
            this.__checkBox.set(null);
        }
        if (r7.radio === undefined) {
            this.__radio.set(null);
        }
        if (r7.image === undefined) {
            this.__image.set(null);
        }
        if (r7.symbolStyle === undefined) {
            this.__symbolStyle.set(null);
        }
        if (r7.text === undefined) {
            this.__text.set(null);
        }
        if (r7.switchState !== undefined) {
            this.switchState = r7.switchState;
        }
        if (r7.radioState !== undefined) {
            this.radioState = r7.radioState;
        }
        if (r7.checkBoxState !== undefined) {
            this.checkBoxState = r7.checkBoxState;
        }
        if (r7.rightWidth === undefined) {
            this.__rightWidth.set(RIGHT_PART_WIDTH);
        }
        if (r7.secondaryTextColor !== undefined) {
            this.secondaryTextColor = r7.secondaryTextColor;
        }
        if (r7.hoveringColor !== undefined) {
            this.hoveringColor = r7.hoveringColor;
        }
        if (r7.activedColor !== undefined) {
            this.activedColor = r7.activedColor;
        }
        if (r7.rowSpace !== undefined) {
            this.rowSpace = r7.rowSpace;
        }
    }
    updateStateVars(q7) {
        this.__arrow.reset(q7.arrow);
        this.__icon.reset(q7.icon);
        this.__subIcon.reset(q7.subIcon);
        this.__button.reset(q7.button);
        this.__switch.reset(q7.switch);
        this.__checkBox.reset(q7.checkBox);
        this.__radio.reset(q7.radio);
        this.__image.reset(q7.image);
        this.__symbolStyle.reset(q7.symbolStyle);
        this.__text.reset(q7.text);
        this.__rightWidth.reset(q7.rightWidth);
    }
    purgeVariableDependenciesOnElmtId(p7) {
        this.__arrow.purgeDependencyOnElmtId(p7);
        this.__icon.purgeDependencyOnElmtId(p7);
        this.__subIcon.purgeDependencyOnElmtId(p7);
        this.__button.purgeDependencyOnElmtId(p7);
        this.__switch.purgeDependencyOnElmtId(p7);
        this.__checkBox.purgeDependencyOnElmtId(p7);
        this.__radio.purgeDependencyOnElmtId(p7);
        this.__image.purgeDependencyOnElmtId(p7);
        this.__symbolStyle.purgeDependencyOnElmtId(p7);
        this.__text.purgeDependencyOnElmtId(p7);
        this.__switchState.purgeDependencyOnElmtId(p7);
        this.__radioState.purgeDependencyOnElmtId(p7);
        this.__checkBoxState.purgeDependencyOnElmtId(p7);
        this.__rightWidth.purgeDependencyOnElmtId(p7);
        this.__secondaryTextColor.purgeDependencyOnElmtId(p7);
        this.__hoveringColor.purgeDependencyOnElmtId(p7);
        this.__activedColor.purgeDependencyOnElmtId(p7);
        this.__parentCanFocus.purgeDependencyOnElmtId(p7);
        this.__parentCanTouch.purgeDependencyOnElmtId(p7);
        this.__parentIsHover.purgeDependencyOnElmtId(p7);
        this.__parentCanHover.purgeDependencyOnElmtId(p7);
        this.__parentIsActive.purgeDependencyOnElmtId(p7);
        this.__parentFrontColor.purgeDependencyOnElmtId(p7);
        this.__parentDirection.purgeDependencyOnElmtId(p7);
        this.__rowSpace.purgeDependencyOnElmtId(p7);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get arrow() {
        return this.__arrow.get();
    }
    set arrow(o7) {
        this.__arrow.set(o7);
    }
    get icon() {
        return this.__icon.get();
    }
    set icon(n7) {
        this.__icon.set(n7);
    }
    get subIcon() {
        return this.__subIcon.get();
    }
    set subIcon(m7) {
        this.__subIcon.set(m7);
    }
    get button() {
        return this.__button.get();
    }
    set button(l7) {
        this.__button.set(l7);
    }
    get switch() {
        return this.__switch.get();
    }
    set switch(k7) {
        this.__switch.set(k7);
    }
    get checkBox() {
        return this.__checkBox.get();
    }
    set checkBox(j7) {
        this.__checkBox.set(j7);
    }
    get radio() {
        return this.__radio.get();
    }
    set radio(i7) {
        this.__radio.set(i7);
    }
    get image() {
        return this.__image.get();
    }
    set image(h7) {
        this.__image.set(h7);
    }
    get symbolStyle() {
        return this.__symbolStyle.get();
    }
    set symbolStyle(g7) {
        this.__symbolStyle.set(g7);
    }
    get text() {
        return this.__text.get();
    }
    set text(f7) {
        this.__text.set(f7);
    }
    get switchState() {
        return this.__switchState.get();
    }
    set switchState(e7) {
        this.__switchState.set(e7);
    }
    get radioState() {
        return this.__radioState.get();
    }
    set radioState(d7) {
        this.__radioState.set(d7);
    }
    get checkBoxState() {
        return this.__checkBoxState.get();
    }
    set checkBoxState(c7) {
        this.__checkBoxState.set(c7);
    }
    get rightWidth() {
        return this.__rightWidth.get();
    }
    set rightWidth(b7) {
        this.__rightWidth.set(b7);
    }
    get secondaryTextColor() {
        return this.__secondaryTextColor.get();
    }
    set secondaryTextColor(a7) {
        this.__secondaryTextColor.set(a7);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(z6) {
        this.__hoveringColor.set(z6);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(y6) {
        this.__activedColor.set(y6);
    }
    get parentCanFocus() {
        return this.__parentCanFocus.get();
    }
    set parentCanFocus(x6) {
        this.__parentCanFocus.set(x6);
    }
    get parentCanTouch() {
        return this.__parentCanTouch.get();
    }
    set parentCanTouch(w6) {
        this.__parentCanTouch.set(w6);
    }
    get parentIsHover() {
        return this.__parentIsHover.get();
    }
    set parentIsHover(v6) {
        this.__parentIsHover.set(v6);
    }
    get parentCanHover() {
        return this.__parentCanHover.get();
    }
    set parentCanHover(u6) {
        this.__parentCanHover.set(u6);
    }
    get parentIsActive() {
        return this.__parentIsActive.get();
    }
    set parentIsActive(t6) {
        this.__parentIsActive.set(t6);
    }
    get parentFrontColor() {
        return this.__parentFrontColor.get();
    }
    set parentFrontColor(s6) {
        this.__parentFrontColor.set(s6);
    }
    get parentDirection() {
        return this.__parentDirection.get();
    }
    set parentDirection(r6) {
        this.__parentDirection.set(r6);
    }
    get rowSpace() {
        return this.__rowSpace.get();
    }
    set rowSpace(q6) {
        this.__rowSpace.set(q6);
    }
    onWillApplyTheme(p6) {
        this.secondaryTextColor = p6.colors.fontSecondary;
        this.hoveringColor = p6.colors.interactiveHover;
        this.activedColor = p6.colors.interactiveActive;
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
        }
        else {
            this.rowSpace = DEFAULT_ROW_SPACE;
        }
    }
    aboutToAppear() {
        this.onPropChange();
    }
    createButton(h6 = null) {
        this.observeComponentCreation2((m6, n6) => {
            Button.createWithChild();
            Button.padding({ top: 0, bottom: 0 });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(HitTestMode.Block);
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
            Button.onHover((o6) => {
                this.parentCanHover = false;
                if (o6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!o6) {
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
        this.observeComponentCreation2((k6, l6) => {
            Row.create();
            Row.padding({
                left: TEXT_SAFE_MARGIN,
                right: TEXT_SAFE_MARGIN
            });
        }, Row);
        this.observeComponentCreation2((i6, j6) => {
            Text.create(this.button?.text);
            Text.focusable(true);
        }, Text);
        Text.pop();
        Row.pop();
        Button.pop();
    }
    createIcon(s5, t5 = null) {
        this.observeComponentCreation2((e6, f6) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(HitTestMode.Block);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.onHover((g6) => {
                this.parentCanHover = false;
                if (g6 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!g6) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
            Button.onClick(s5.icon?.action);
            Button.accessibilityLevel(s5.icon?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Button.accessibilityText(getAccessibilityText(s5.icon?.accessibilityText ?? ''));
            Button.accessibilityDescription(getAccessibilityText(s5.icon?.accessibilityDescription ?? ''));
            Button.flexShrink(0);
        }, Button);
        this.observeComponentCreation2((u5, v5) => {
            If.create();
            if (s5.icon?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c6, d6) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(s5.icon?.symbolStyle);
                        SymbolGlyph.fontSize(OPERATEITEM_ICONLIKE_SIZE);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w5, x5) => {
                        If.create();
                        if (Util.isSymbolResource(s5.icon?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a6, b6) => {
                                    SymbolGlyph.create(s5.icon?.value);
                                    SymbolGlyph.fontSize(OPERATEITEM_ICONLIKE_SIZE);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((y5, z5) => {
                                    Image.create(s5.icon?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.focusable(true);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
    createImage(l5 = null) {
        this.observeComponentCreation2((m5, n5) => {
            If.create();
            if (Util.isSymbolResource(ObservedObject.GetRawObject(this.image))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q5, r5) => {
                        SymbolGlyph.create(this.image);
                        SymbolGlyph.fontSize(OPERATEITEM_IMAGE_SIZE);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o5, p5) => {
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
    createSymbol(i5 = null) {
        this.observeComponentCreation2((j5, k5) => {
            SymbolGlyph.create();
            SymbolGlyph.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.symbolStyle));
            SymbolGlyph.fontSize(OPERATEITEM_IMAGE_SIZE);
            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.draggable(false);
            SymbolGlyph.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
        }, SymbolGlyph);
    }
    createText(f5 = null) {
        this.observeComponentCreation2((g5, h5) => {
            Text.create(this.text);
            Text.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor(ObservedObject.GetRawObject(this.secondaryTextColor));
            Text.draggable(false);
            Text.flexShrink(1);
        }, Text);
        Text.pop();
    }
    createArrow(r4 = null) {
        this.observeComponentCreation2((c5, d5) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Button.hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent);
            Button.backgroundColor(Color.Transparent);
            Button.height(OPERATEITEM_ICONLIKE_SIZE);
            Button.width(OPERATEITEM_ARROW_WIDTH);
            Button.onFocus(() => {
                this.parentCanFocus = false;
            });
            Button.stateEffect(this.arrow?.action !== undefined);
            Button.hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None);
            Button.onHover((e5) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (e5) {
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
        this.observeComponentCreation2((s4, t4) => {
            If.create();
            if (this.arrow?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((a5, b5) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                        SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.focusable(true);
                        SymbolGlyph.draggable(false);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((u4, v4) => {
                        If.create();
                        if (Util.isSymbolResource(this.arrow?.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y4, z4) => {
                                    SymbolGlyph.create(this.arrow?.value);
                                    SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.focusable(true);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((w4, x4) => {
                                    Image.create(this.arrow?.value);
                                    Image.height(OPERATEITEM_ICONLIKE_SIZE);
                                    Image.width(OPERATEITEM_ARROW_WIDTH);
                                    Image.focusable(true);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
    createRadio(n4 = null) {
        this.observeComponentCreation2((o4, p4) => {
            Radio.create({ value: '', group: '' });
            Radio.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Radio.checked(this.radioState);
            Radio.onChange(this.radio?.onChange);
            Radio.height(OPERATEITEM_ICONLIKE_SIZE);
            Radio.width(OPERATEITEM_ICONLIKE_SIZE);
            Radio.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Radio.onFocus(() => {
                this.parentCanFocus = false;
            });
            Radio.hitTestBehavior(HitTestMode.Block);
            Radio.flexShrink(0);
            Radio.onHover((q4) => {
                this.parentCanHover = false;
                if (q4 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!q4) {
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
    createCheckBox(j4 = null) {
        this.observeComponentCreation2((k4, l4) => {
            Checkbox.create();
            Checkbox.margin({ end: LengthMetrics.vp(LISTITEM_PADDING) });
            Checkbox.select(this.checkBoxState);
            Checkbox.onChange(this.checkBox?.onChange);
            Checkbox.height(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.width(OPERATEITEM_ICONLIKE_SIZE);
            Checkbox.padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE);
            Checkbox.onFocus(() => {
                this.parentCanFocus = false;
            });
            Checkbox.hitTestBehavior(HitTestMode.Block);
            Checkbox.flexShrink(0);
            Checkbox.onHover((m4) => {
                this.parentCanHover = false;
                if (m4 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!m4) {
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
    createSwitch(d4 = null) {
        this.observeComponentCreation2((g4, h4) => {
            Row.create();
            Row.margin({ end: LengthMetrics.vp(SWITCH_PADDING) });
            Row.height(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.width(OPERATEITEM_ICON_CLICKABLE_SIZE);
            Row.justifyContent(FlexAlign.Center);
            Row.onFocus(() => {
                this.parentCanFocus = false;
            });
            Row.onHover((i4) => {
                this.parentCanHover = false;
                if (i4 && this.parentFrontColor === this.hoveringColor) {
                    this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
                }
                if (!i4) {
                    this.parentCanHover = true;
                    if (this.parentIsHover) {
                        this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
                            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
                    }
                }
            });
        }, Row);
        this.observeComponentCreation2((e4, f4) => {
            Toggle.create({ type: ToggleType.Switch, isOn: this.switchState });
            Toggle.onChange(this.switch?.onChange);
            Toggle.onClick(() => {
                this.switchState = !this.switchState;
            });
            Toggle.hitTestBehavior(HitTestMode.Block);
            Toggle.accessibilityLevel(this.switch?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO);
            Toggle.accessibilityText(getAccessibilityText(this.switch?.accessibilityText ?? ''));
            Toggle.accessibilityDescription(getAccessibilityText(this.switch?.accessibilityDescription ?? ''));
        }, Toggle);
        Toggle.pop();
        Row.pop();
    }
    createTextArrow(v2 = null) {
        this.observeComponentCreation2((a4, b4) => {
            Button.createWithChild({ type: ButtonType.Normal });
            Button.hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent);
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
            Button.onHover((c4) => {
                if (this.arrow?.action === undefined) {
                    return;
                }
                if (c4) {
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
        this.observeComponentCreation2((w2, x2) => {
            If.create();
            if (this.parentDirection === FlexDirection.Column) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y3, z3) => {
                        Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
                        Flex.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Flex);
                    this.observeComponentCreation2((w3, x3) => {
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
                    this.observeComponentCreation2((m3, n3) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((u3, v3) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
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
                                                SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
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
                    this.observeComponentCreation2((k3, l3) => {
                        Row.create({ space: SPECICAL_ROW_SPACE });
                        Row.padding({
                            start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
                            end: LengthMetrics.vp(LISTITEM_PADDING)
                        });
                    }, Row);
                    this.observeComponentCreation2((i3, j3) => {
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
                    this.observeComponentCreation2((y2, z2) => {
                        If.create();
                        if (this.arrow?.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((g3, h3) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.arrow?.symbolStyle);
                                    SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.focusable(false);
                                    SymbolGlyph.draggable(false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((a3, b3) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.arrow?.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((e3, f3) => {
                                                SymbolGlyph.create(this.arrow?.value);
                                                SymbolGlyph.fontSize(OPERATEITEM_ARROW_WIDTH);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_fourth'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.focusable(false);
                                                SymbolGlyph.draggable(false);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((c3, d3) => {
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
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    getFlexOptions() {
        let u2 = { alignItems: ItemAlign.Center };
        if (this.parentDirection === FlexDirection.Column) {
            u2.justifyContent = FlexAlign.SpaceBetween;
        }
        else {
            u2.space = { main: LengthMetrics.vp(this.rowSpace) };
            u2.justifyContent = FlexAlign.End;
        }
        return u2;
    }
    initialRender() {
        this.observeComponentCreation2((s2, t2) => {
            Flex.create(this.getFlexOptions());
            Flex.width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth);
        }, Flex);
        this.observeComponentCreation2((o2, p2) => {
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
                    this.observeComponentCreation2((q2, r2) => {
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
function getAccessibilityText(j2) {
    try {
        let n2 = '';
        if (typeof j2 === 'string') {
            n2 = j2;
        }
        else {
            n2 = getContext().resourceManager.getStringSync(j2);
        }
        return n2;
    }
    catch (k2) {
        let l2 = k2.code;
        let m2 = k2.message;
        hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${l2}, message: ${m2}`);
        return '';
    }
}
export class ComposeListItem extends ViewPU {
    constructor(b2, c2, d2, e2 = -1, f2 = undefined, g2) {
        super(b2, d2, e2, g2);
        if (typeof f2 === 'function') {
            this.paramsGenerator_ = f2;
        }
        this.__contentItem = new SynchedPropertyObjectOneWayPU(c2.contentItem, this, 'contentItem');
        this.__operateItem = new SynchedPropertyObjectOneWayPU(c2.operateItem, this, 'operateItem');
        this.__frontColor = new ObservedPropertyObjectPU(Color.Transparent.toString(), this, 'frontColor');
        this.__borderSize = new ObservedPropertySimplePU(0, this, 'borderSize');
        this.__canFocus = new ObservedPropertySimplePU(false, this, 'canFocus');
        this.__canTouch = new ObservedPropertySimplePU(true, this, 'canTouch');
        this.__canHover = new ObservedPropertySimplePU(true, this, 'canHover');
        this.__isHover = new ObservedPropertySimplePU(true, this, 'isHover');
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
        this.envCallback = {
            onConfigurationUpdated: (i2) => {
                this.fontSizeScale = this.decideFontSizeScale();
            },
            onMemoryLevel: (h2) => {
            }
        };
        this.setInitiallyProvidedValue(c2);
        this.declareWatch('contentItem', this.onPropChange);
        this.declareWatch('operateItem', this.onPropChange);
        this.declareWatch('fontSizeScale', this.onFontSizeScaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a2) {
        if (a2.contentItem === undefined) {
            this.__contentItem.set(null);
        }
        if (a2.operateItem === undefined) {
            this.__operateItem.set(null);
        }
        if (a2.frontColor !== undefined) {
            this.frontColor = a2.frontColor;
        }
        if (a2.borderSize !== undefined) {
            this.borderSize = a2.borderSize;
        }
        if (a2.canFocus !== undefined) {
            this.canFocus = a2.canFocus;
        }
        if (a2.canTouch !== undefined) {
            this.canTouch = a2.canTouch;
        }
        if (a2.canHover !== undefined) {
            this.canHover = a2.canHover;
        }
        if (a2.isHover !== undefined) {
            this.isHover = a2.isHover;
        }
        if (a2.itemHeight !== undefined) {
            this.itemHeight = a2.itemHeight;
        }
        if (a2.isActive !== undefined) {
            this.isActive = a2.isActive;
        }
        if (a2.hoveringColor !== undefined) {
            this.hoveringColor = a2.hoveringColor;
        }
        if (a2.touchDownColor !== undefined) {
            this.touchDownColor = a2.touchDownColor;
        }
        if (a2.activedColor !== undefined) {
            this.activedColor = a2.activedColor;
        }
        if (a2.focusOutlineColor !== undefined) {
            this.focusOutlineColor = a2.focusOutlineColor;
        }
        if (a2.fontSizeScale !== undefined) {
            this.fontSizeScale = a2.fontSizeScale;
        }
        if (a2.containerDirection !== undefined) {
            this.containerDirection = a2.containerDirection;
        }
        if (a2.contentItemDirection !== undefined) {
            this.contentItemDirection = a2.contentItemDirection;
        }
        if (a2.containerPadding !== undefined) {
            this.containerPadding = a2.containerPadding;
        }
        if (a2.textArrowLeftSafeOffset !== undefined) {
            this.textArrowLeftSafeOffset = a2.textArrowLeftSafeOffset;
        }
        if (a2.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a2.isFollowingSystemFontScale;
        }
        if (a2.maxFontScale !== undefined) {
            this.maxFontScale = a2.maxFontScale;
        }
        if (a2.callbackId !== undefined) {
            this.callbackId = a2.callbackId;
        }
        if (a2.accessibilityTextBuilder !== undefined) {
            this.accessibilityTextBuilder = a2.accessibilityTextBuilder;
        }
        if (a2.envCallback !== undefined) {
            this.envCallback = a2.envCallback;
        }
    }
    updateStateVars(z1) {
        this.__contentItem.reset(z1.contentItem);
        this.__operateItem.reset(z1.operateItem);
    }
    purgeVariableDependenciesOnElmtId(y1) {
        this.__contentItem.purgeDependencyOnElmtId(y1);
        this.__operateItem.purgeDependencyOnElmtId(y1);
        this.__frontColor.purgeDependencyOnElmtId(y1);
        this.__borderSize.purgeDependencyOnElmtId(y1);
        this.__canFocus.purgeDependencyOnElmtId(y1);
        this.__canTouch.purgeDependencyOnElmtId(y1);
        this.__canHover.purgeDependencyOnElmtId(y1);
        this.__isHover.purgeDependencyOnElmtId(y1);
        this.__itemHeight.purgeDependencyOnElmtId(y1);
        this.__isActive.purgeDependencyOnElmtId(y1);
        this.__hoveringColor.purgeDependencyOnElmtId(y1);
        this.__touchDownColor.purgeDependencyOnElmtId(y1);
        this.__activedColor.purgeDependencyOnElmtId(y1);
        this.__focusOutlineColor.purgeDependencyOnElmtId(y1);
        this.__fontSizeScale.purgeDependencyOnElmtId(y1);
        this.__containerDirection.purgeDependencyOnElmtId(y1);
        this.__contentItemDirection.purgeDependencyOnElmtId(y1);
        this.__containerPadding.purgeDependencyOnElmtId(y1);
        this.__textArrowLeftSafeOffset.purgeDependencyOnElmtId(y1);
        this.__accessibilityTextBuilder.purgeDependencyOnElmtId(y1);
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
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentItem() {
        return this.__contentItem.get();
    }
    set contentItem(x1) {
        this.__contentItem.set(x1);
    }
    get operateItem() {
        return this.__operateItem.get();
    }
    set operateItem(w1) {
        this.__operateItem.set(w1);
    }
    get frontColor() {
        return this.__frontColor.get();
    }
    set frontColor(v1) {
        this.__frontColor.set(v1);
    }
    get borderSize() {
        return this.__borderSize.get();
    }
    set borderSize(u1) {
        this.__borderSize.set(u1);
    }
    get canFocus() {
        return this.__canFocus.get();
    }
    set canFocus(t1) {
        this.__canFocus.set(t1);
    }
    get canTouch() {
        return this.__canTouch.get();
    }
    set canTouch(s1) {
        this.__canTouch.set(s1);
    }
    get canHover() {
        return this.__canHover.get();
    }
    set canHover(r1) {
        this.__canHover.set(r1);
    }
    get isHover() {
        return this.__isHover.get();
    }
    set isHover(q1) {
        this.__isHover.set(q1);
    }
    get itemHeight() {
        return this.__itemHeight.get();
    }
    set itemHeight(p1) {
        this.__itemHeight.set(p1);
    }
    get isActive() {
        return this.__isActive.get();
    }
    set isActive(o1) {
        this.__isActive.set(o1);
    }
    get hoveringColor() {
        return this.__hoveringColor.get();
    }
    set hoveringColor(n1) {
        this.__hoveringColor.set(n1);
    }
    get touchDownColor() {
        return this.__touchDownColor.get();
    }
    set touchDownColor(m1) {
        this.__touchDownColor.set(m1);
    }
    get activedColor() {
        return this.__activedColor.get();
    }
    set activedColor(l1) {
        this.__activedColor.set(l1);
    }
    get focusOutlineColor() {
        return this.__focusOutlineColor.get();
    }
    set focusOutlineColor(k1) {
        this.__focusOutlineColor.set(k1);
    }
    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }
    set fontSizeScale(j1) {
        this.__fontSizeScale.set(j1);
    }
    get containerDirection() {
        return this.__containerDirection.get();
    }
    set containerDirection(i1) {
        this.__containerDirection.set(i1);
    }
    get contentItemDirection() {
        return this.__contentItemDirection.get();
    }
    set contentItemDirection(h1) {
        this.__contentItemDirection.set(h1);
    }
    get containerPadding() {
        return this.__containerPadding.get();
    }
    set containerPadding(g1) {
        this.__containerPadding.set(g1);
    }
    get textArrowLeftSafeOffset() {
        return this.__textArrowLeftSafeOffset.get();
    }
    set textArrowLeftSafeOffset(f1) {
        this.__textArrowLeftSafeOffset.set(f1);
    }
    get accessibilityTextBuilder() {
        return this.__accessibilityTextBuilder.get();
    }
    set accessibilityTextBuilder(e1) {
        this.__accessibilityTextBuilder.set(e1);
    }
    onWillApplyTheme(d1) {
        this.hoveringColor = d1.colors.interactiveHover;
        this.touchDownColor = d1.colors.interactivePressed;
        this.activedColor = d1.colors.interactiveActive;
        this.focusOutlineColor = d1.colors.interactiveFocus;
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
                ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
            }
        }
        else if (this.contentItem.description === undefined) {
            if (this.contentItem.icon === undefined ||
                (this.contentItem.icon !== undefined && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
                this.itemHeight = ItemHeight.THIRD_HEIGHT;
            }
            else {
                this.itemHeight = ItemHeight.FOURTH_HEIGHT;
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
        catch (a1) {
            let b1 = a1.code;
            let c1 = a1.message;
            hilog.error(0x3900, 'Ace', `ComposeListItem Faild to get environment param error: ${b1}, ${c1}`);
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
            this.containerPadding = undefined;
        }
    }
    isSingleLine() {
        return !this.contentItem?.secondaryText && !this.contentItem?.description;
    }
    getOperateOffset() {
        if (this.containerDirection === FlexDirection.Row) {
            return LengthMetrics.vp(0);
        }
        let z = ICON_SIZE_MAP.get(this.contentItem?.iconStyle);
        if (this.contentItem?.icon && z && z <= HEADSCULPTURE_SIZE) {
            return LengthMetrics.vp(z + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
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
    initialRender() {
        this.observeComponentCreation2((x, y) => {
            Stack.create();
            Stack.width('100%');
            Stack.accessibilityGroup(true);
            Stack.accessibilityText(this.accessibilityTextBuilder);
            Stack.padding({
                left: STACK_PADDING,
                right: STACK_PADDING
            });
        }, Stack);
        this.observeComponentCreation2((u, v) => {
            Flex.create(this.getFlexOptions());
            Flex.height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined);
            Flex.constraintSize({
                minHeight: this.itemHeight
            });
            Flex.focusable(true);
            Flex.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.backgroundColor(ObservedObject.GetRawObject(this.frontColor));
            Flex.onFocus(() => {
                this.canFocus = true;
            });
            Flex.onBlur(() => {
                this.canFocus = false;
            });
            Flex.onHover((w) => {
                this.isHover = w;
                if (this.canHover) {
                    this.frontColor = w ? this.hoveringColor :
                        (this.isActive ? this.activedColor : Color.Transparent.toString());
                }
            });
            ViewStackProcessor.visualState('focused');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: ITEM_BORDER_SHOWN,
                color: this.focusOutlineColor,
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Flex.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: ITEM_BORDER_SHOWN,
                color: Color.Transparent
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
                                let s = new ContentItemStruct(this, {}, undefined, q, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1122, col: 11 });
                                ViewPU.create(s);
                                let t = () => {
                                    return {};
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
                                }, undefined, k, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1125, col: 11 });
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
                                        itemDirection: this.contentItemDirection
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
                                    itemDirection: this.contentItemDirection
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
                                }, undefined, c, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 1138, col: 11 });
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
                                        parentDirection: this.containerDirection
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

export default { IconType, ComposeListItem };