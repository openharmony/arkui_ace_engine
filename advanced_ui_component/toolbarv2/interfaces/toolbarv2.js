/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
var __decorate = (this && this.__decorate) || function (a51, b51, c51, d51) {
  var e51 = arguments.length, f51 = e51 < 3 ? b51 : d51 === null ? d51 = Object.getOwnPropertyDescriptor(b51, c51) : d51, g51;
  if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
    f51 = Reflect.decorate(a51, b51, c51, d51);
  else
    for (var h51 = a51.length - 1; h51 >= 0; h51--)
      if (g51 = a51[h51])
        f51 = (e51 < 3 ? g51(f51) : e51 > 3 ? g51(b51, c51, f51) : g51(b51, c51)) || f51;
  return e51 > 3 && f51 && Object.defineProperty(b51, c51, f51), f51;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const DividerModifier = requireNapi('arkui.modifier').DividerModifier;
const hilog = requireNapi('hilog');
const promptAction = requireNapi('promptAction');
export var ToolBarV2ItemState;
(function (z50) {
  z50[z50["ENABLE"] = 1] = "ENABLE";
  z50[z50["DISABLE"] = 2] = "DISABLE";
  z50[z50["ACTIVATE"] = 3] = "ACTIVATE";
})(ToolBarV2ItemState || (ToolBarV2ItemState = {}));
const PUBLIC_MORE = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const IMAGE_SIZE = '24vp';
const DEFAULT_TOOLBAR_HEIGHT = 56;
const TOOLBAR_MAX_LENGTH = 5;
const MAX_FONT_SIZE = 3.2;
const DIALOG_IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TEXT_TOOLBAR_DIALOG = '18.3fp';
const SCREEN_WIDTH_BREAK_POINT = 640;
const VERTICAL_SCREEN_TEXT_MAX_LINES = 6;
const HORIZONTAL_SCREEN_TEXT_MAX_LINES = 1;
const FOCUS_BOX_MARGIN = -2;
const FOCUS_BOX_BORDER_WIDTH = 2;
let ToolBarV2SymbolGlyph = class ToolBarV2SymbolGlyph {
  constructor(y50) {
    this.normal = y50.normal;
    this.activated = y50.activated;
  }
};
__decorate([
  Trace
], ToolBarV2SymbolGlyph.prototype, "normal", void 0);
__decorate([
  Trace
], ToolBarV2SymbolGlyph.prototype, "activated", void 0);
ToolBarV2SymbolGlyph = __decorate([
  ObservedV2
], ToolBarV2SymbolGlyph);
export { ToolBarV2SymbolGlyph };
class ButtonGestureModifier {
  constructor() {
    this.gestureCallBack = undefined;
  }
  applyGesture(w50) {
    this.gestureCallBack?.(w50);
  }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
let ToolBarV2ItemText = class ToolBarV2ItemText {
  constructor(v50) {
    this.color = ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    this.activatedColor = ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    this.text = v50.text;
    this.color = v50.color;
    this.activatedColor = v50.activatedColor;
  }
};
__decorate([
  Trace
], ToolBarV2ItemText.prototype, "text", void 0);
__decorate([
  Trace
], ToolBarV2ItemText.prototype, "color", void 0);
__decorate([
  Trace
], ToolBarV2ItemText.prototype, "activatedColor", void 0);
ToolBarV2ItemText = __decorate([
  ObservedV2
], ToolBarV2ItemText);
export { ToolBarV2ItemText };
let ToolBarV2ItemImage = class ToolBarV2ItemImage {
  constructor(r) {
    this.color = undefined;
    this.activatedColor = undefined;
    this.src = r.src;
    this.color = r.color;
    this.activatedColor = r.activatedColor;
  }
};
__decorate([
  Trace
], ToolBarV2ItemImage.prototype, "src", void 0);
__decorate([
  Trace
], ToolBarV2ItemImage.prototype, "color", void 0);
__decorate([
  Trace
], ToolBarV2ItemImage.prototype, "activatedColor", void 0);
ToolBarV2ItemImage = __decorate([
  ObservedV2
], ToolBarV2ItemImage);
export { ToolBarV2ItemImage };
let ToolBarV2Item = class ToolBarV2Item {
  constructor(r50) {
    this.content = new ToolBarV2ItemText({ text: '' });
    this.action = undefined;
    this.icon = undefined;
    this.state = 1;
    this.accessibilityText = '';
    this.accessibilityDescription = '';
    this.accessibilityLevel = 'auto';
    this.backgroundColor = Color.Transparent;
    this.content = r50.content;
    this.action = r50.action;
    this.icon = r50.icon;
    this.state = r50.state;
    this.accessibilityText = r50.accessibilityText;
    this.accessibilityDescription = r50.accessibilityDescription;
    this.accessibilityLevel = r50.accessibilityLevel;
  }
  get symbol() {
    if (this.icon instanceof ToolBarV2SymbolGlyph) {
      return this.icon;
    }
    return undefined;
  }
  get image() {
    if (!(this.icon instanceof ToolBarV2SymbolGlyph)) {
      return this.icon;
    }
    return undefined;
  }
};
__decorate([
  Trace
], ToolBarV2Item.prototype, "content", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "action", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "icon", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "state", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "accessibilityText", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "accessibilityDescription", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "accessibilityLevel", void 0);
__decorate([
  Trace
], ToolBarV2Item.prototype, "backgroundColor", void 0);
__decorate([
  Computed
], ToolBarV2Item.prototype, "symbol", null);
__decorate([
  Computed
], ToolBarV2Item.prototype, "image", null);
ToolBarV2Item = __decorate([
  ObservedV2
], ToolBarV2Item);
export { ToolBarV2Item };
let ToolBarV2Modifier = class ToolBarV2Modifier {
  constructor() {
    this.backgroundColorValue = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_toolbar_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.heightValue = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
    this.stateEffectValue = true;
    this.paddingValue = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  }
  applyNormalAttribute(q50) {
    q50.backgroundColor(this.backgroundColorValue);
  }
  backgroundColor(p50) {
    this.backgroundColorValue = p50.color;
    return this;
  }
  height(o50) {
    this.heightValue = o50;
    return this;
  }
  stateEffect(n50) {
    this.stateEffectValue = n50;
    return this;
  }
  padding(m50) {
    this.paddingValue = m50;
    return this;
  }
};
__decorate([
  Trace
], ToolBarV2Modifier.prototype, "backgroundColorValue", void 0);
__decorate([
  Trace
], ToolBarV2Modifier.prototype, "heightValue", void 0);
__decorate([
  Trace
], ToolBarV2Modifier.prototype, "stateEffectValue", void 0);
__decorate([
  Trace
], ToolBarV2Modifier.prototype, "paddingValue", void 0);
ToolBarV2Modifier = __decorate([
  ObservedV2
], ToolBarV2Modifier);
export { ToolBarV2Modifier };
let ToolBarV2Theme = class ToolBarV2Theme {
  constructor() {
    this.iconPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.iconActivePrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.icon_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontActivatedPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
  }
};
__decorate([
  Trace
], ToolBarV2Theme.prototype, "iconPrimaryColor", void 0);
__decorate([
  Trace
], ToolBarV2Theme.prototype, "iconActivePrimaryColor", void 0);
__decorate([
  Trace
], ToolBarV2Theme.prototype, "fontPrimaryColor", void 0);
__decorate([
  Trace
], ToolBarV2Theme.prototype, "fontActivatedPrimaryColor", void 0);
ToolBarV2Theme = __decorate([
  ObservedV2
], ToolBarV2Theme);
export class ToolBarV2 extends ViewV2 {
  constructor(g50, h50, i50, j50 = -1, k50, l50) {
    super(g50, j50, l50);
    this.initParam("toolBarList", (h50 && "toolBarList" in h50) ? h50.toolBarList : undefined);
    this.initParam("activatedIndex", (h50 && "activatedIndex" in h50) ? h50.activatedIndex : -1);
    this.initParam("dividerModifier", (h50 && "dividerModifier" in h50) ? h50.dividerModifier : new DividerModifier());
    this.initParam("toolBarModifier", (h50 && "toolBarModifier" in h50) ? h50.toolBarModifier : new ToolBarV2Modifier()
      .padding(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }))
      .stateEffect(true)
      .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
      .backgroundColor(ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_toolbar_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })));
    this.localActivatedIndex = -1;
    this.menuContent = [];
    this.fontSize = 1;
    this.theme = new ToolBarV2Theme();
    this.itemCardTextMaxLine = 1;
    this.itemDialogId = undefined;
    this.isFollowSystem = false;
    this.maxFontSizeScale = 3.2;
    this.moreItem = new ToolBarV2Item({
      content: new ToolBarV2ItemText({
        text: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      }),
      icon: new ToolBarV2ItemImage({
        src: PUBLIC_MORE
      })
    });
    this.moreText = { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.finalizeConstruction();
  }
  onActivateIndexChange(e50) {
    this.localActivatedIndex = e50.value('activatedIndex')?.now ?? -1;
  }
  get menus() {
    this.menuContent = [];
    this.toolBarList.forEach((o, p) => {
      if (p >= TOOLBAR_MAX_LENGTH - 1) {
        this.menuContent.push({
          value: this.toolBarList[p].content.text,
          action: () => {
            let q = this.toolBarList[p].action;
            if (q) {
              q(p);
            }
          },
          enabled: this.toolBarList[p].state !== ToolBarV2ItemState.DISABLE,
        });
      }
    });
    return this.menuContent;
  }
  aboutToAppear() {
    this.localActivatedIndex = this.activatedIndex ?? -1;
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    }
    catch (b50) {
      let c50 = b50?.code;
      let d50 = b50?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBarV2 getMaxFontScale, code: ${c50}, message: ${d50}`);
    }
  }
  onWillApplyTheme(a50) {
    this.theme.iconPrimaryColor = a50.colors.iconPrimary;
    this.theme.iconActivePrimaryColor = a50.colors.iconEmphasize;
    this.theme.fontPrimaryColor = a50.colors.fontPrimary;
    this.theme.fontActivatedPrimaryColor = a50.colors.fontEmphasize;
  }
  MoreTabBuilder(r49, s49 = null) {
    this.observeComponentCreation2((x49, y49) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.padding({
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Column.accessibilityText(this.moreText);
      Column.focusable(true);
      Column.focusOnTouch(true);
      Column.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
      });
      Column.bindMenu(this.menus, { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Column.backgroundColor(this.toolBarList[r49].backgroundColor);
      Column.onHover((z49) => {
        if (z49) {
          this.toolBarList[r49].backgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.toolBarList[r49].backgroundColor = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState("pressed");
      Column.backgroundColor((!this.toolBarModifier?.stateEffectValue) ?
      this.toolBarList[r49].backgroundColor : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      ViewStackProcessor.visualState();
      Column.gestureModifier(this.getItemGestureModifier(this.moreItem, r49));
    }, Column);
    this.observeComponentCreation2((v49, w49) => {
      Image.create(PUBLIC_MORE);
      Image.width(IMAGE_SIZE);
      Image.height(IMAGE_SIZE);
      Image.fillColor(this.theme.iconPrimaryColor);
      Image.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((t49, u49) => {
      Text.create(this.moreText);
      Text.fontColor(this.theme.fontPrimaryColor);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
    }, Text);
    Text.pop();
    Column.pop();
  }
  TabBuilder(e49, f49 = null) {
    this.observeComponentCreation2((o49, p49) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Column.padding({
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
      Column.opacity(this.toolBarList[e49]?.state !== ToolBarV2ItemState.DISABLE ? 1 : 0.4);
      Column.enabled(this.toolBarList[e49]?.state !== ToolBarV2ItemState.DISABLE);
      Column.accessibilityGroup(true);
      Column.accessibilityText(this.toStringFormat(this.toolBarList[e49]?.accessibilityText) ??
      this.toStringFormat(this.toolBarList[e49]?.content?.text));
      Column.accessibilityDescription(this.toStringFormat(this.toolBarList[e49]?.accessibilityDescription) ?? '');
      Column.accessibilityLevel(this.toStringFormat(this.toolBarList[e49]?.accessibilityLevel) ?? 'auto');
      Column.focusable(!(this.toolBarList[e49]?.state === ToolBarV2ItemState.DISABLE));
      Column.focusOnTouch(!(this.toolBarList[e49]?.state === ToolBarV2ItemState.DISABLE));
      Column.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
      });
      Column.backgroundColor(this.toolBarList[e49].backgroundColor);
      Column.onHover((q49) => {
        if (q49 && this.toolBarList[e49]?.state !== ToolBarV2ItemState.DISABLE) {
          this.toolBarList[e49].backgroundColor = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.toolBarList[e49].backgroundColor = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState("pressed");
      Column.backgroundColor((this.toolBarList[e49]?.state === ToolBarV2ItemState.DISABLE) ||
        (!this.toolBarModifier?.stateEffectValue) ?
      this.toolBarList[e49].backgroundColor : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      ViewStackProcessor.visualState();
      Column.onClick(() => {
        this.clickEventAction(e49);
      });
      Column.gestureModifier(this.getItemGestureModifier(this.toolBarList[e49], e49));
    }, Column);
    this.observeComponentCreation2((i49, j49) => {
      If.create();
      if (this.toolBarList[e49]?.symbol) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((m49, n49) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(IMAGE_SIZE);
            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(e49));
            SymbolGlyph.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((k49, l49) => {
            Image.create(this.toolBarList[e49]?.image?.src);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(this.getIconColor(e49));
            Image.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((g49, h49) => {
      Text.create(this.toolBarList[e49]?.content.text);
      Text.fontColor(this.getTextColor(e49));
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.maxFontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
    }, Text);
    Text.pop();
    Column.pop();
  }
  itemCardDialogBuilder(h, i, j = null) {
    this.observeComponentCreation2((x, y) => {
      If.create();
      if (h.content && h.content.text) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r1, s1) => {
            Column.create();
            Column.constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG });
          }, Column);
          this.observeComponentCreation2((l1, m1) => {
            If.create();
            if (h.symbol) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((p1, q1) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(i));
                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                  SymbolGlyph.fontSize(DIALOG_IMAGE_SIZE);
                  SymbolGlyph.margin({
                    top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                    bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                  });
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((n1, o1) => {
                  Image.create(h.image?.src);
                  Image.width(DIALOG_IMAGE_SIZE);
                  Image.height(DIALOG_IMAGE_SIZE);
                  Image.margin({
                    top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                    bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                  });
                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                }, Image);
              });
            }
          }, If);
          If.pop();
          this.observeComponentCreation2((j1, k1) => {
            Column.create();
            Column.width('100%');
            Column.padding({
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
          }, Column);
          this.observeComponentCreation2((h1, i1) => {
            Text.create(h.content.text);
            Text.fontSize(TEXT_TOOLBAR_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.itemCardTextMaxLine);
            Text.width('100%');
            Text.textAlign(TextAlign.Center);
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
          }, Text);
          Text.pop();
          Column.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((f1, g1) => {
            Column.create();
            Column.constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG });
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((z, a1) => {
            If.create();
            if (h.symbol) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((d1, e1) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(i));
                  SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                  SymbolGlyph.fontSize(DIALOG_IMAGE_SIZE);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((b1, c1) => {
                  Image.create(h.image?.src);
                  Image.width(DIALOG_IMAGE_SIZE);
                  Image.height(DIALOG_IMAGE_SIZE);
                  Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                }, Image);
              });
            }
          }, If);
          If.pop();
          Column.pop();
        });
      }
    }, If);
    If.pop();
  }
  getFontSizeScale() {
    let c49 = this.getUIContext();
    let d49 = c49.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(d49, this.maxFontSizeScale);
    }
  }
  isItemActivating(b49) {
    return this.localActivatedIndex === b49 && (this.toolBarList[b49]?.state === ToolBarV2ItemState.ACTIVATE);
  }
  getToolBarSymbolModifier(a49) {
    if (this.isItemActivating(a49)) {
      return this.toolBarList[a49]?.symbol?.activated;
    }
    return this.toolBarList[a49]?.symbol?.normal;
  }
  getIconColor(z48) {
    if (this.isItemActivating(z48)) {
      return this.toolBarList[z48]?.image?.activatedColor?.color ?? this.theme.iconActivePrimaryColor;
    }
    return this.toolBarList[z48]?.image?.color?.color ?? this.theme.iconPrimaryColor;
  }
  getTextColor(y48) {
    if (this.isItemActivating(y48)) {
      return this.toolBarList[y48]?.content.activatedColor?.color ?? this.theme.fontActivatedPrimaryColor;
    }
    return this.toolBarList[y48]?.content.color?.color ?? this.theme.fontPrimaryColor;
  }
  toStringFormat(t48) {
    if (typeof t48 === 'string' || typeof t48 === 'undefined') {
      return t48;
    }
    let d = '';
    try {
      d = getContext()?.resourceManager?.getStringSync(t48?.id);
    }
    catch (e) {
      let f = e?.code;
      let g = e?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar toStringFormat, code: ${f}, message: ${g}`);
    }
    return d;
  }
  toLengthString(q48) {
    if (q48 === undefined) {
      return '';
    }
    const r48 = q48.value;
    let s48 = '';
    switch (q48.unit) {
      case LengthUnit.PX:
        s48 = `${r48}px`;
        break;
      case LengthUnit.FP:
        s48 = `${r48}fp`;
        break;
      case LengthUnit.LPX:
        s48 = `${r48}lpx`;
        break;
      case LengthUnit.PERCENT:
        s48 = `${r48 * 100}%`;
        break;
      case LengthUnit.VP:
        s48 = `${r48}vp`;
        break;
      default:
        s48 = `${r48}vp`;
        break;
    }
    return s48;
  }
  clickEventAction(o48) {
    let p48 = this.toolBarList[o48];
    if (p48.state === ToolBarV2ItemState.ACTIVATE) {
      if (this.localActivatedIndex === o48) {
        this.localActivatedIndex = -1;
      }
      else {
        this.localActivatedIndex = o48;
      }
    }
    if (p48.state !== ToolBarV2ItemState.DISABLE) {
      p48.action && p48.action(o48);
    }
  }
  getItemGestureModifier(j48, k48) {
    if (!j48?.icon) {
      return undefined;
    }
    let l48 = new ButtonGestureModifier();
    l48.gestureCallBack = (b) => {
      if (this.fontSize >= ButtonGestureModifier.minFontSize) {
        b.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
          .onAction(() => {
            promptAction.openCustomDialog({
              builder: () => {
                this.itemCardDialogBuilder(j48, k48);
              },
              onWillAppear: () => {
                try {
                  let u = this.getUIContext().getHostContext();
                  let v = u.windowStage.getMainWindowSync();
                  let w = v.getWindowProperties();
                  if (px2vp(w.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                    this.itemCardTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                  }
                  else {
                    this.itemCardTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                  }
                }
                catch (n) {
                  let s = n?.code;
                  let t = n?.message;
                  hilog.error(0x3900, 'Ace', `ToolBarV2 get window height failed, code: ${s}, message: ${t}`);
                }
              },
              maskColor: Color.Transparent,
              isModal: true,
              backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
              backgroundColor: Color.Transparent,
              shadow: ShadowStyle.OUTER_DEFAULT_LG,
              cornerRadius: { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              width: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG
            }).then((c) => {
              this.itemDialogId = c;
            });
          })
          .onActionEnd(() => {
            if (this.itemDialogId) {
              promptAction.closeCustomDialog(this.itemDialogId);
            }
          }));
        return;
      }
      b.clearGestures();
    };
    return l48;
  }
  onMeasureSize(b48, c48, d48) {
    this.fontSize = this.getFontSizeScale();
    let e48 = { height: 0, width: 0 };
    c48.forEach((f48) => {
      let g48 = f48.measure(d48);
      e48.width = g48.width;
      e48.height = g48.height;
    });
    return e48;
  }
  initialRender() {
    this.observeComponentCreation2((z47, a48) => {
      Column.create();
      Column.attributeModifier.bind(this)(this.toolBarModifier);
    }, Column);
    this.observeComponentCreation2((x47, y47) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(this.dividerModifier);
    }, Divider);
    this.observeComponentCreation2((v47, w47) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier?.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier?.heightValue),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier?.heightValue));
      Row.padding({
        start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
          this.toolBarModifier?.paddingValue : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
    }, Row);
    this.observeComponentCreation2((j47, k47) => {
      ForEach.create();
      const a = (o47, p47) => {
        const q47 = o47;
        this.observeComponentCreation2((r47, s47) => {
          If.create();
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || p47 < TOOLBAR_MAX_LENGTH - 1) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((t47, u47) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(p47);
              Row.pop();
            });
          }
          else {
            this.ifElseBranchUpdateFunction(1, () => {
            });
          }
        }, If);
        If.pop();
      };
      this.forEachUpdateFunction(j47, this.toolBarList, a, (m47, n47) => {
        return `${this.getUniqueId}__${n47}}`;
      }, true, true);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((f47, g47) => {
      If.create();
      if (this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((h47, i47) => {
            Row.create();
            Row.height('100%');
            Row.flexShrink(1);
          }, Row);
          this.MoreTabBuilder.bind(this)(TOOLBAR_MAX_LENGTH - 1);
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Row.pop();
    Column.pop();
  }
  updateStateVars(e47) {
    if (e47 === undefined) {
      return;
    }
    if ("toolBarList" in e47) {
      this.updateParam("toolBarList", e47.toolBarList);
    }
    if ("activatedIndex" in e47) {
      this.updateParam("activatedIndex", e47.activatedIndex);
    }
    if ("dividerModifier" in e47) {
      this.updateParam("dividerModifier", e47.dividerModifier);
    }
    if ("toolBarModifier" in e47) {
      this.updateParam("toolBarModifier", e47.toolBarModifier);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ToolBarV2.prototype, "toolBarList", void 0);
__decorate([
  Param
], ToolBarV2.prototype, "activatedIndex", void 0);
__decorate([
  Param
], ToolBarV2.prototype, "dividerModifier", void 0);
__decorate([
  Param
], ToolBarV2.prototype, "toolBarModifier", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "localActivatedIndex", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "menuContent", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "fontSize", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "theme", void 0);
__decorate([
  Monitor('activatedIndex')
], ToolBarV2.prototype, "onActivateIndexChange", null);
__decorate([
  Computed
], ToolBarV2.prototype, "menus", null);
export default { ToolBarV2Item, ToolBarV2ItemImage, ToolBarV2ItemText, ToolBarV2, ToolBarV2ItemState, ToolBarV2Modifier, ToolBarV2SymbolGlyph };