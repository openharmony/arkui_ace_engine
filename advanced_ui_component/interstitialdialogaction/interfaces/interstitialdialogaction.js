/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to  in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
const ComponentContent = requireNapi("arkui.node").ComponentContent;
const curves = requireNativeModule('ohos.curves');
const DIALOG_BORDER_RADIUS = { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_default_m'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const DIALOG_INNER_PADDING_SIZE = 16;
const DIALOG_MAX_WIDTH = 480;
const DIALOG_OFFSET_X = 0;
const DIALOG_OFFSET_Y_FOR_BAR = -88;
const DIALOG_OFFSET_Y_FOR_NONE = -44;
const STANDARD_MIN_COMPONENT_HEIGHT = 82;
const STANDARD_MAX_COMPONENT_HEIGHT = 94;
const DIALOG_SHADOW_RADIUS = 16;
const DIALOG_SHADOW_OFFSET_Y = 10;
const DIALOG_SHADOW_COLOR = '#19000000';
const TITLE_LINE_DISTANCE = 2;
const TITLE_MAX_LINE = 2;
const SUBTITLE_MAX_LINE = 1;
const TEXT_LEFT_MARGIN_SIZE = 16;
const SUBTITLE_DEFAULT_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const TITLE_DEFAULT_COLOR = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const OPERATE_AREA_AVOID_WIDTH = 28;
const CLOSE_ICON_DARK_RESOURCE = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_tertiary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const CLOSE_ICON_LIGHT_RESOURCE = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const CLOSE_BUTTON_BORDER_RADIUS = 8;
const CLOSE_BUTTON_ICON_SIZE = 16;
const CLOSE_BUTTON_HOT_SPOT_SIZE = 32;
const CLOSE_BUTTON_MARGIN = 8;
const CLOSE_BUTTON_ICON_OPACITY = 0.6;
const CLOSE_BUTTON_RESPONSE_REGION_OFFSET_X = -8;
const CLOSE_BUTTON_RESPONSE_REGION_OFFSET_Y = -8;
const CLOSE_BUTTON_OFFSET_X = 0;
const CLOSE_BUTTON_OFFSET_Y = -50;
const FOREGROUND_IMAGE_OFFSET_X = 4;
const FOREGROUND_IMAGE_OFFSET_Y = 0;
export var IconStyle;
(function (e2) {
    e2[e2["DARK"] = 0] = "DARK";
    e2[e2["LIGHT"] = 1] = "LIGHT";
})(IconStyle || (IconStyle = {}));
export var TitlePosition;
(function (d2) {
    d2[d2["TOP"] = 0] = "TOP";
    d2[d2["BOTTOM"] = 1] = "BOTTOM";
})(TitlePosition || (TitlePosition = {}));
export var BottomOffset;
(function (c2) {
    c2[c2["OFFSET_FOR_BAR"] = 0] = "OFFSET_FOR_BAR";
    c2[c2["OFFSET_FOR_NONE"] = 1] = "OFFSET_FOR_NONE";
})(BottomOffset || (BottomOffset = {}));
class DialogParams {
    constructor(a2, b2) {
        this.options = a2;
        this.defaultCloseAction = b2;
    }
}
function dialogBuilder(k, l = null) {
    const m = k;
    (l ? l : this).observeComponentCreation2((x1, y1, z1 = m) => {
        Row.create();
        Row.backgroundColor('rgba(0,0,0,0)');
        Row.width('100%');
        Row.height(STANDARD_MAX_COMPONENT_HEIGHT);
        Row.padding({
            left: DIALOG_INNER_PADDING_SIZE,
            right: DIALOG_INNER_PADDING_SIZE
        });
        Row.constraintSize({
            minHeight: STANDARD_MIN_COMPONENT_HEIGHT,
            maxHeight: STANDARD_MAX_COMPONENT_HEIGHT,
            maxWidth: DIALOG_MAX_WIDTH
        });
    }, Row);
    (l ? l : this).observeComponentCreation2((t1, u1, v1 = m) => {
        Flex.create();
        Flex.backgroundColor(v1.options.backgroundImage === undefined ? '#EBEEF5' : 'rgba(0,0,0,0)');
        Flex.shadow({
            radius: DIALOG_SHADOW_RADIUS,
            offsetX: 0,
            offsetY: DIALOG_SHADOW_OFFSET_Y,
            color: DIALOG_SHADOW_COLOR
        });
        Flex.height(STANDARD_MIN_COMPONENT_HEIGHT);
        Flex.width('100%');
        Flex.alignSelf(ItemAlign.End);
        Flex.direction(Direction.Rtl);
        Flex.zIndex(1);
        Flex.borderRadius({
            topLeft: DIALOG_BORDER_RADIUS,
            topRight: DIALOG_BORDER_RADIUS,
            bottomLeft: DIALOG_BORDER_RADIUS,
            bottomRight: DIALOG_BORDER_RADIUS
        });
        Flex.onClick(() => {
            if (v1.options.onDialogClick !== undefined) {
                v1.options.onDialogClick();
            }
            v1.defaultCloseAction();
        });
    }, Flex);
    (l ? l : this).observeComponentCreation2((q1, r1, s1 = m) => {
        Row.create();
        Row.padding({ left: OPERATE_AREA_AVOID_WIDTH });
        Row.direction(Direction.Rtl);
        Row.defaultFocus(true);
        Row.align(Alignment.End);
        Row.alignSelf(ItemAlign.End);
        Row.constraintSize({
            maxWidth: '50%',
            minWidth: '40%'
        });
    }, Row);
    (l ? l : this).observeComponentCreation2((m1, n1, o1 = m) => {
        SymbolGlyph.create({ "id": -1, "type": 40000, params: ['sys.symbol.xmark_circle_fill'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        SymbolGlyph.fontColor([o1.options.iconStyle === IconStyle.DARK ?
                CLOSE_ICON_DARK_RESOURCE : CLOSE_ICON_LIGHT_RESOURCE]);
        SymbolGlyph.borderRadius(CLOSE_BUTTON_BORDER_RADIUS);
        SymbolGlyph.width(CLOSE_BUTTON_ICON_SIZE);
        SymbolGlyph.height(CLOSE_BUTTON_ICON_SIZE);
        SymbolGlyph.opacity(CLOSE_BUTTON_ICON_OPACITY);
        SymbolGlyph.draggable(false);
        SymbolGlyph.focusable(true);
        SymbolGlyph.responseRegion({
            x: CLOSE_BUTTON_RESPONSE_REGION_OFFSET_X,
            y: CLOSE_BUTTON_RESPONSE_REGION_OFFSET_Y,
            width: CLOSE_BUTTON_HOT_SPOT_SIZE,
            height: CLOSE_BUTTON_HOT_SPOT_SIZE
        });
        SymbolGlyph.margin(CLOSE_BUTTON_MARGIN);
        SymbolGlyph.alignSelf(ItemAlign.End);
        SymbolGlyph.offset({
            x: CLOSE_BUTTON_OFFSET_X,
            y: CLOSE_BUTTON_OFFSET_Y
        });
        SymbolGlyph.onClick(() => {
            if (o1.options.onDialogClose !== undefined) {
                o1.options.onDialogClose();
            }
            o1.defaultCloseAction();
        });
    }, SymbolGlyph);
    (l ? l : this).observeComponentCreation2((j1, k1, l1 = m) => {
        Image.create(l1.options.foregroundImage);
        Image.height(STANDARD_MAX_COMPONENT_HEIGHT);
        Image.objectFit(ImageFit.Contain);
        Image.fitOriginalSize(true);
        Image.offset({
            x: FOREGROUND_IMAGE_OFFSET_X,
            y: FOREGROUND_IMAGE_OFFSET_Y
        });
        Image.alignSelf(ItemAlign.End);
    }, Image);
    Row.pop();
    (l ? l : this).observeComponentCreation2((g1, h1, i1 = m) => {
        Flex.create({
            direction: i1.options.titlePosition === TitlePosition.BOTTOM ?
                FlexDirection.ColumnReverse : FlexDirection.Column,
            justifyContent: FlexAlign.Center
        });
        Flex.constraintSize({
            maxWidth: '60%',
            minWidth: '50%'
        });
        Flex.flexGrow(1);
        Flex.margin({ left: TEXT_LEFT_MARGIN_SIZE });
    }, Flex);
    (l ? l : this).observeComponentCreation2((d1, e1, f1 = m) => {
        Text.create(f1.options.title);
        Text.alignSelf(ItemAlign.Start);
        Text.maxFontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_sub_title1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        Text.minFontSize(16);
        Text.fontColor(f1.options.titleColor !== undefined ? f1.options.titleColor : TITLE_DEFAULT_COLOR);
        Text.fontWeight(FontWeight.Bold);
        Text.margin(f1.options.titlePosition ? { top: TITLE_LINE_DISTANCE } : { bottom: TITLE_LINE_DISTANCE });
        Text.maxLines(TITLE_MAX_LINE);
        Text.wordBreak(WordBreak.BREAK_WORD);
        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    }, Text);
    Text.pop();
    (l ? l : this).observeComponentCreation2((a1, b1, c1 = m) => {
        Text.create(c1.options.subtitle);
        Text.alignSelf(ItemAlign.Start);
        Text.maxFontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
        Text.minFontSize(9);
        Text.fontColor(c1.options.subtitleColor !== undefined ? c1.options.subtitleColor : SUBTITLE_DEFAULT_COLOR);
        Text.maxLines(SUBTITLE_MAX_LINE);
        Text.wordBreak(WordBreak.BREAK_WORD);
        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    }, Text);
    Text.pop();
    Flex.pop();
    Flex.pop();
    (l ? l : this).observeComponentCreation2((w, x, y = m) => {
        Image.create(y.options.backgroundImage);
        Image.width('100%');
        Image.height(STANDARD_MIN_COMPONENT_HEIGHT);
        Image.offset({ x: '-100%', y: 0 });
        Image.borderRadius(DIALOG_BORDER_RADIUS);
        Image.zIndex(0);
        Image.alignSelf(ItemAlign.End);
        Image.onClick(() => {
            if (y.options.onDialogClose !== undefined) {
                y.options.onDialogClose();
            }
            y.defaultCloseAction();
        });
    }, Image);
    Row.pop();
}
export class InterstitialDialogAction {
    constructor(i) {
        this.uiContext = i.uiContext;
        this.bottomOffsetType = i.bottomOffsetType;
        this.dialogParam = new DialogParams(i, () => {
            this.closeDialog();
        });
        this.contentNode = new ComponentContent(this.uiContext, wrapBuilder(dialogBuilder), this.dialogParam);
    }
    openDialog() {
        if (this.contentNode !== null) {
            this.uiContext.getPromptAction().openCustomDialog(this.contentNode, {
                isModal: false,
                autoCancel: false,
                offset: {
                    dx: DIALOG_OFFSET_X,
                    dy: this.bottomOffsetType === BottomOffset.OFFSET_FOR_BAR ?
                        DIALOG_OFFSET_Y_FOR_BAR : DIALOG_OFFSET_Y_FOR_NONE
                },
                alignment: DialogAlignment.Bottom,
                transition: TransitionEffect.asymmetric(TransitionEffect.OPACITY.animation({ duration: 150, curve: Curve.Sharp })
                    .combine(TransitionEffect.scale({ x: 0.85, y: 0.85, centerX: '50%', centerY: '85%' })
                    .animation({ curve: curves.interpolatingSpring(0, 1, 228, 24) })), TransitionEffect.OPACITY.animation({ duration: 250, curve: Curve.Sharp })
                    .combine(TransitionEffect.scale({ x: 0.85, y: 0.85, centerX: '50%', centerY: '85%' })
                    .animation({ duration: 250, curve: Curve.Friction })))
            })
                .catch((f) => {
                let g = f.message;
                let h = f.code;
                console.error(`${h}: ${g}`);
            });
        }
    }
    closeDialog() {
        if (this.contentNode !== null) {
            this.uiContext.getPromptAction().closeCustomDialog(this.contentNode)
                .catch((b) => {
                let c = b.message;
                let d = b.code;
                console.error(`${d}: ${c}`);
            });
        }
    }
}

export default { InterstitialDialogAction, IconStyle, TitlePosition, BottomOffset };