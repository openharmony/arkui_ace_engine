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

var __decorate = (this && this.__decorate) || function (x11, y11, z11, a12) {
  var b12 = arguments.length, c12 = b12 < 3 ? y11 : a12 === null ? a12 = Object.getOwnPropertyDescriptor(y11, z11) : a12, d12;
  if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
    c12 = Reflect.decorate(x11, y11, z11, a12);
  else
    for (var e12 = x11.length - 1; e12 >= 0; e12--)
      if (d12 = x11[e12])
        c12 = (b12 < 3 ? d12(c12) : b12 > 3 ? d12(y11, z11, c12) : d12(y11, z11)) || c12;
  return b12 > 3 && c12 && Object.defineProperty(y11, z11, c12), c12;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const DividerModifier = requireNapi('arkui.modifier').DividerModifier;
const hilog = requireNapi('hilog');

export var ItemState;
(function (v11) {
  v11[v11["ENABLE"] = 1] = "ENABLE";
  v11[v11["DISABLE"] = 2] = "DISABLE";
  v11[v11["ACTIVATE"] = 3] = "ACTIVATE";
})(ItemState || (ItemState = {}));
const PUBLIC_MORE = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const IMAGE_SIZE = '24vp';
const DEFAULT_TOOLBAR_HEIGHT = 56;
const TOOLBAR_MAX_LENGTH = 5;
const MAX_FONT_SIZE = 3.2;
const DIALOG_IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TEXT_TOOLBAR_DIALOG = '18.3fp';
const FOCUS_BOX_MARGIN = -2;
const FOCUS_BOX_BORDER_WIDTH = 2;
class ButtonGestureModifier {
  constructor(u11) {
    this.fontSize = 1;
    this.controller = null;
    this.controller = u11;
  }
  applyGesture(r11) {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      r11.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
        .onAction(() => {
          if (r11) {
            this.controller?.open();
          }
        })
        .onActionEnd(() => {
          this.controller?.close();
        }));
    }
    else {
      r11.clearGestures();
    }
  }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
let ToolBarOption = class ToolBarOption {
  constructor() {
    this.content = '';
    this.action = undefined;
    this.icon = undefined;
    this.state = 1;
    this.iconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.activatedIconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.textColor = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.activatedTextColor = { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.toolBarSymbolOptions = undefined;
  }
};
ToolBarOption = __decorate([
  Observed
], ToolBarOption);
export { ToolBarOption };
let ToolBarOptions = class ToolBarOptions extends Array {
};
ToolBarOptions = __decorate([
  Observed
], ToolBarOptions);
export { ToolBarOptions };
export class ToolBarModifier {
  constructor() {
    this.backgroundColorValue = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_toolbar_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.heightValue = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
    this.stateEffectValue = true;
    this.paddingValue = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  }
  applyNormalAttribute(q11) {
    q11.backgroundColor(this.backgroundColorValue);
  }
  backgroundColor(p11) {
    this.backgroundColorValue = p11;
    return this;
  }
  height(o11) {
    this.heightValue = o11;
    return this;
  }
  stateEffect(n11) {
    this.stateEffectValue = n11;
    return this;
  }
  padding(m11) {
    this.paddingValue = m11;
    return this;
  }
}
export class ToolBar extends ViewPU {
  constructor(g11, h11, i11, j11 = -1, k11 = undefined, l11) {
    super(g11, i11, j11, l11);
    if (typeof k11 === "function") {
      this.paramsGenerator_ = k11;
    }
    this.__toolBarList = new SynchedPropertyNesedObjectPU(h11.toolBarList, this, "toolBarList");
    this.controller = new TabsController();
    this.__activateIndex = new SynchedPropertySimpleOneWayPU(h11.activateIndex, this, "activateIndex");
    this.__dividerModifier = new SynchedPropertyObjectOneWayPU(h11.dividerModifier, this, "dividerModifier");
    this.__toolBarModifier = new SynchedPropertyObjectOneWayPU(h11.toolBarModifier, this, "toolBarModifier");
    this.__moreText = new SynchedPropertyObjectOneWayPU(h11.moreText, this, "moreText");
    this.__menuContent = new ObservedPropertyObjectPU([], this, "menuContent");
    this.__toolBarItemBackground = new ObservedPropertyObjectPU([], this, "toolBarItemBackground");
    this.__iconPrimaryColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconPrimaryColor");
    this.__iconActivePrimaryColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.icon_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "iconActivePrimaryColor");
    this.__fontPrimaryColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "fontPrimaryColor");
    this.__fontActivatedPrimaryColor = new ObservedPropertyObjectPU({ "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, this, "fontActivatedPrimaryColor");
    this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, "symbolEffect");
    this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
    this.isFollowSystem = false;
    this.maxFontSizeScale = 3.2;
    this.moreIndex = 4;
    this.moreItem = {
      content: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      icon: PUBLIC_MORE,
    };
    this.setInitiallyProvidedValue(h11);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(f11) {
    this.__toolBarList.set(f11.toolBarList);
    if (f11.controller !== undefined) {
      this.controller = f11.controller;
    }
    if (f11.activateIndex === undefined) {
      this.__activateIndex.set(-1);
    }
    if (f11.dividerModifier === undefined) {
      this.__dividerModifier.set(new DividerModifier());
    }
    if (f11.toolBarModifier === undefined) {
      this.__toolBarModifier.set(new ToolBarModifier()
        .padding(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }))
        .stateEffect(true)
        .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
        .backgroundColor('sys.color.ohos_id_color_toolbar_bg'));
    }
    if (f11.moreText === undefined) {
      this.__moreText.set({ "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    }
    if (f11.menuContent !== undefined) {
      this.menuContent = f11.menuContent;
    }
    if (f11.toolBarItemBackground !== undefined) {
      this.toolBarItemBackground = f11.toolBarItemBackground;
    }
    if (f11.iconPrimaryColor !== undefined) {
      this.iconPrimaryColor = f11.iconPrimaryColor;
    }
    if (f11.iconActivePrimaryColor !== undefined) {
      this.iconActivePrimaryColor = f11.iconActivePrimaryColor;
    }
    if (f11.fontPrimaryColor !== undefined) {
      this.fontPrimaryColor = f11.fontPrimaryColor;
    }
    if (f11.fontActivatedPrimaryColor !== undefined) {
      this.fontActivatedPrimaryColor = f11.fontActivatedPrimaryColor;
    }
    if (f11.symbolEffect !== undefined) {
      this.symbolEffect = f11.symbolEffect;
    }
    if (f11.fontSize !== undefined) {
      this.fontSize = f11.fontSize;
    }
    if (f11.isFollowSystem !== undefined) {
      this.isFollowSystem = f11.isFollowSystem;
    }
    if (f11.maxFontSizeScale !== undefined) {
      this.maxFontSizeScale = f11.maxFontSizeScale;
    }
    if (f11.moreIndex !== undefined) {
      this.moreIndex = f11.moreIndex;
    }
    if (f11.moreItem !== undefined) {
      this.moreItem = f11.moreItem;
    }
  }
  updateStateVars(e11) {
    this.__toolBarList.set(e11.toolBarList);
    this.__activateIndex.reset(e11.activateIndex);
    this.__dividerModifier.reset(e11.dividerModifier);
    this.__toolBarModifier.reset(e11.toolBarModifier);
    this.__moreText.reset(e11.moreText);
  }
  purgeVariableDependenciesOnElmtId(d11) {
    this.__toolBarList.purgeDependencyOnElmtId(d11);
    this.__activateIndex.purgeDependencyOnElmtId(d11);
    this.__dividerModifier.purgeDependencyOnElmtId(d11);
    this.__toolBarModifier.purgeDependencyOnElmtId(d11);
    this.__moreText.purgeDependencyOnElmtId(d11);
    this.__menuContent.purgeDependencyOnElmtId(d11);
    this.__toolBarItemBackground.purgeDependencyOnElmtId(d11);
    this.__iconPrimaryColor.purgeDependencyOnElmtId(d11);
    this.__iconActivePrimaryColor.purgeDependencyOnElmtId(d11);
    this.__fontPrimaryColor.purgeDependencyOnElmtId(d11);
    this.__fontActivatedPrimaryColor.purgeDependencyOnElmtId(d11);
    this.__symbolEffect.purgeDependencyOnElmtId(d11);
    this.__fontSize.purgeDependencyOnElmtId(d11);
  }
  aboutToBeDeleted() {
    this.__toolBarList.aboutToBeDeleted();
    this.__activateIndex.aboutToBeDeleted();
    this.__dividerModifier.aboutToBeDeleted();
    this.__toolBarModifier.aboutToBeDeleted();
    this.__moreText.aboutToBeDeleted();
    this.__menuContent.aboutToBeDeleted();
    this.__toolBarItemBackground.aboutToBeDeleted();
    this.__iconPrimaryColor.aboutToBeDeleted();
    this.__iconActivePrimaryColor.aboutToBeDeleted();
    this.__fontPrimaryColor.aboutToBeDeleted();
    this.__fontActivatedPrimaryColor.aboutToBeDeleted();
    this.__symbolEffect.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get toolBarList() {
    return this.__toolBarList.get();
  }
  get activateIndex() {
    return this.__activateIndex.get();
  }
  set activateIndex(c11) {
    this.__activateIndex.set(c11);
  }
  get dividerModifier() {
    return this.__dividerModifier.get();
  }
  set dividerModifier(b11) {
    this.__dividerModifier.set(b11);
  }
  get toolBarModifier() {
    return this.__toolBarModifier.get();
  }
  set toolBarModifier(a11) {
    this.__toolBarModifier.set(a11);
  }
  get moreText() {
    return this.__moreText.get();
  }
  set moreText(z10) {
    this.__moreText.set(z10);
  }
  get menuContent() {
    return this.__menuContent.get();
  }
  set menuContent(y10) {
    this.__menuContent.set(y10);
  }
  get toolBarItemBackground() {
    return this.__toolBarItemBackground.get();
  }
  set toolBarItemBackground(x10) {
    this.__toolBarItemBackground.set(x10);
  }
  get iconPrimaryColor() {
    return this.__iconPrimaryColor.get();
  }
  set iconPrimaryColor(w10) {
    this.__iconPrimaryColor.set(w10);
  }
  get iconActivePrimaryColor() {
    return this.__iconActivePrimaryColor.get();
  }
  set iconActivePrimaryColor(v10) {
    this.__iconActivePrimaryColor.set(v10);
  }
  get fontPrimaryColor() {
    return this.__fontPrimaryColor.get();
  }
  set fontPrimaryColor(u10) {
    this.__fontPrimaryColor.set(u10);
  }
  get fontActivatedPrimaryColor() {
    return this.__fontActivatedPrimaryColor.get();
  }
  set fontActivatedPrimaryColor(t10) {
    this.__fontActivatedPrimaryColor.set(t10);
  }
  get symbolEffect() {
    return this.__symbolEffect.get();
  }
  set symbolEffect(s10) {
    this.__symbolEffect.set(s10);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(r10) {
    this.__fontSize.set(r10);
  }
  onWillApplyTheme(q10) {
    this.iconPrimaryColor = q10.colors.iconPrimary;
    this.iconActivePrimaryColor = q10.colors.iconEmphasize;
    this.fontPrimaryColor = q10.colors.fontPrimary;
    this.fontActivatedPrimaryColor = q10.colors.fontEmphasize;
  }
  MoreTabBuilder(a10, b10 = null) {
    this.observeComponentCreation2((m10, n10) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.focusable(true);
      Button.focusOnTouch(true);
      Button.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
      });
      Button.width('100%');
      Button.height('100%');
      Button.bindMenu(ObservedObject.GetRawObject(this.menuContent), { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.backgroundColor(this.toolBarItemBackground[a10]);
      Button.onHover((p10) => {
        if (p10) {
          this.toolBarItemBackground[a10] = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.toolBarItemBackground[a10] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState("pressed");
      Button.backgroundColor((!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[a10] : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      ViewStackProcessor.visualState();
      Button.gestureModifier(this.getItemGestureModifier(this.moreItem, a10));
    }, Button);
    this.observeComponentCreation2((k10, l10) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.padding({
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    }, Column);
    this.observeComponentCreation2((i10, j10) => {
      Image.create(PUBLIC_MORE);
      Image.width(IMAGE_SIZE);
      Image.height(IMAGE_SIZE);
      Image.fillColor(ObservedObject.GetRawObject(this.iconPrimaryColor));
      Image.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((g10, h10) => {
      Text.create(this.moreText);
      Text.fontColor(ObservedObject.GetRawObject(this.fontPrimaryColor));
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.focusable(true);
      Text.focusOnTouch(true);
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }
  TabBuilder(b9, c9 = null) {
    this.observeComponentCreation2((v9, w9) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.enabled(this.toolBarList[b9]?.state !== ItemState.DISABLE);
      Button.width('100%');
      Button.height('100%');
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.focusable(!(this.toolBarList[b9]?.state === ItemState.DISABLE));
      Button.focusOnTouch(!(this.toolBarList[b9]?.state === ItemState.DISABLE));
      Button.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
      });
      Button.backgroundColor(this.toolBarItemBackground[b9]);
      Button.onHover((z9) => {
        if (z9 && this.toolBarList[b9]?.state !== ItemState.DISABLE) {
          this.toolBarItemBackground[b9] = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.toolBarItemBackground[b9] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState("pressed");
      Button.backgroundColor((this.toolBarList[b9]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[b9] : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      ViewStackProcessor.visualState();
      Button.onClick(() => {
        this.clickEventAction(b9);
      });
      Button.gestureModifier(this.getItemGestureModifier(this.toolBarList[b9], b9));
    }, Button);
    this.observeComponentCreation2((t9, u9) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Column.padding({
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
    }, Column);
    this.observeComponentCreation2((j9, k9) => {
      If.create();
      if (this.toolBarList[b9]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[b9]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r9, s9) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(IMAGE_SIZE);
            SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(b9));
            SymbolGlyph.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((n9, o9) => {
            Image.create(this.toolBarList[b9]?.icon);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(this.getIconColor(b9));
            Image.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((h9, i9) => {
      Text.create(this.toolBarList[b9]?.content);
      Text.fontColor(this.getTextColor(b9));
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.maxFontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.focusable(!(this.toolBarList[b9]?.state === ItemState.DISABLE));
      Text.focusOnTouch(!(this.toolBarList[b9]?.state === ItemState.DISABLE));
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }
  getFontSizeScale() {
    let z8 = this.getUIContext();
    let a9 = z8.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(a9, this.maxFontSizeScale);
    }
  }
  getToolBarSymbolModifier(y8) {
    if ((!this.toolBarList[y8]?.toolBarSymbolOptions?.activated) &&
      (!this.toolBarList[y8]?.toolBarSymbolOptions?.normal)) {
      return undefined;
    }
    if (this.activateIndex === y8 && (this.toolBarList[y8]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[y8]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[y8]?.toolBarSymbolOptions?.normal;
  }
  getIconColor(x8) {
    if (this.activateIndex === x8 && (this.toolBarList[x8]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[x8]?.activatedIconColor ?? this.iconActivePrimaryColor;
    }
    return this.toolBarList[x8]?.iconColor ?? this.iconPrimaryColor;
  }
  getTextColor(w8) {
    if (this.activateIndex === w8 && (this.toolBarList[w8]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[w8]?.activatedTextColor ?? this.fontActivatedPrimaryColor;
    }
    return this.toolBarList[w8]?.textColor ?? this.fontPrimaryColor;
  }
  toLengthString(t8) {
    if (t8 === void (0)) {
      return '';
    }
    const u8 = t8.value;
    let v8 = '';
    switch (t8.unit) {
      case LengthUnit.PX:
        v8 = `${u8}px`;
        break;
      case LengthUnit.FP:
        v8 = `${u8}fp`;
        break;
      case LengthUnit.LPX:
        v8 = `${u8}lpx`;
        break;
      case LengthUnit.PERCENT:
        v8 = `${u8 * 100}%`;
        break;
      case LengthUnit.VP:
        v8 = `${u8}vp`;
        break;
      default:
        v8 = `${u8}vp`;
        break;
    }
    return v8;
  }
  clickEventAction(r8) {
    let s8 = this.toolBarList[r8];
    if (s8.state === ItemState.ACTIVATE) {
      if (this.activateIndex === r8) {
        this.activateIndex = -1;
      }
      else {
        this.activateIndex = r8;
      }
    }
    if (!(s8.state === ItemState.DISABLE)) {
      s8.action && s8.action();
    }
  }
  getItemGestureModifier(k8, l8) {
    let m8 = new ButtonGestureModifier(null);
    if (k8?.icon || k8?.toolBarSymbolOptions?.activated || k8?.toolBarSymbolOptions?.normal) {
      m8 = new ButtonGestureModifier(new CustomDialogController({
        builder: () => {
          let n8 = new ToolBarDialog(this, {
            itemDialog: k8,
            fontSize: this.fontSize,
            itemSymbolModifier: this.getToolBarSymbolModifier(l8),
          }, undefined, -1, () => { }, { page: "library/src/main/ets/components/toolbar.ets", line: 380, col: 18 });
          n8.setController();
          ViewPU.create(n8);
          let o37 = () => {
            return {
              itemDialog: k8,
              fontSize: this.fontSize,
              itemSymbolModifier: this.getToolBarSymbolModifier(l8)
            };
          };
          n8.paramsGenerator_ = o37;
        },
        maskColor: Color.Transparent,
        isModal: true,
        customStyle: true
      }, this));
      m8.fontSize = this.fontSize;
    }
    return m8;
  }
  refreshData() {
    this.menuContent = [];
    for (let j8 = 0; j8 < this.toolBarList.length; j8++) {
      if (j8 >= this.moreIndex && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.menuContent[j8 - this.moreIndex] = {
          value: this.toolBarList[j8].content,
          action: this.toolBarList[j8].action,
          enabled: this.toolBarList[j8].state !== ItemState.DISABLE,
        };
      }
      else {
        this.menuContent = [];
      }
      this.toolBarItemBackground[j8] = this.toolBarItemBackground[j8] ?? Color.Transparent;
    }
    return true;
  }
  onMeasureSize(c8, d8, e8) {
    this.fontSize = this.getFontSizeScale();
    let f8 = { height: 0, width: 0 };
    d8.forEach((h8) => {
      let i8 = h8.measure(e8);
      f8.width = i8.width;
      f8.height = i8.height;
    });
    return f8;
  }
  aboutToAppear() {
    this.refreshData();
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    }
    catch (z7) {
      let a8 = z7?.code;
      let b8 = z7?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getMaxFontScale, code: ${a8}, message: ${b8}`);
    }
  }
  initialRender() {
    this.observeComponentCreation2((x7, y7) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.toolBarModifier));
    }, Column);
    this.observeComponentCreation2((v7, w7) => {
      Tabs.create({ controller: this.controller });
      Tabs.visibility(Visibility.None);
    }, Tabs);
    Tabs.pop();
    this.observeComponentCreation2((t7, u7) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.dividerModifier));
    }, Divider);
    this.observeComponentCreation2((r7, s7) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier.heightValue));
      Row.padding({
        start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
        this.toolBarModifier.paddingValue : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
        this.toolBarModifier.paddingValue : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
    }, Row);
    this.observeComponentCreation2((c7, d7) => {
      ForEach.create();
      const n37 = (g7, h7) => {
        const i7 = g7;
        this.observeComponentCreation2((k7, l7) => {
          If.create();
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || h7 < this.moreIndex) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((p7, q7) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(h7);
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
      this.forEachUpdateFunction(c7, this.toolBarList, n37, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((v6, w6) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a7, b7) => {
            Row.create();
            Row.height('100%');
            Row.flexShrink(1);
          }, Row);
          this.MoreTabBuilder.bind(this)(this.moreIndex);
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
  rerender() {
    this.updateDirtyElements();
  }
}
class ToolBarDialog extends ViewPU {
  constructor(h6, i6, j6, k6 = -1, l6 = undefined, m6) {
    super(h6, j6, k6, m6);
    if (typeof l6 === "function") {
      this.paramsGenerator_ = l6;
    }
    this.itemDialog = {
      icon: undefined,
      content: '',
    };
    this.itemSymbolModifier = undefined;
    this.mainWindowStage = undefined;
    this.controller = undefined;
    this.screenWidth = 640;
    this.verticalScreenLines = 6;
    this.horizontalsScreenLines = 1;
    this.cancel = () => {
    };
    this.confirm = () => {
    };
    this.__mainWindow = this.createStorageLink('mainWindow', undefined, "mainWindow");
    this.__fontSize = new SynchedPropertySimpleOneWayPU(i6.fontSize, this, "fontSize");
    this.__maxLines = new ObservedPropertySimplePU(1, this, "maxLines");
    this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, "windowStandardHeight");
    this.__symbolEffect = new ObservedPropertyObjectPU(new SymbolEffect(), this, "symbolEffect");
    this.setInitiallyProvidedValue(i6);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(g6) {
    if (g6.itemDialog !== undefined) {
      this.itemDialog = g6.itemDialog;
    }
    if (g6.itemSymbolModifier !== undefined) {
      this.itemSymbolModifier = g6.itemSymbolModifier;
    }
    if (g6.mainWindowStage !== undefined) {
      this.mainWindowStage = g6.mainWindowStage;
    }
    if (g6.controller !== undefined) {
      this.controller = g6.controller;
    }
    if (g6.screenWidth !== undefined) {
      this.screenWidth = g6.screenWidth;
    }
    if (g6.verticalScreenLines !== undefined) {
      this.verticalScreenLines = g6.verticalScreenLines;
    }
    if (g6.horizontalsScreenLines !== undefined) {
      this.horizontalsScreenLines = g6.horizontalsScreenLines;
    }
    if (g6.cancel !== undefined) {
      this.cancel = g6.cancel;
    }
    if (g6.confirm !== undefined) {
      this.confirm = g6.confirm;
    }
    if (g6.fontSize === undefined) {
      this.__fontSize.set(1);
    }
    if (g6.maxLines !== undefined) {
      this.maxLines = g6.maxLines;
    }
    if (g6.symbolEffect !== undefined) {
      this.symbolEffect = g6.symbolEffect;
    }
  }
  updateStateVars(f6) {
    this.__fontSize.reset(f6.fontSize);
  }
  purgeVariableDependenciesOnElmtId(e6) {
    this.__mainWindow.purgeDependencyOnElmtId(e6);
    this.__fontSize.purgeDependencyOnElmtId(e6);
    this.__maxLines.purgeDependencyOnElmtId(e6);
    this.__windowStandardHeight.purgeDependencyOnElmtId(e6);
    this.__symbolEffect.purgeDependencyOnElmtId(e6);
  }
  aboutToBeDeleted() {
    this.__mainWindow.aboutToBeDeleted();
    this.__fontSize.aboutToBeDeleted();
    this.__maxLines.aboutToBeDeleted();
    this.__windowStandardHeight.aboutToBeDeleted();
    this.__symbolEffect.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(d6) {
    this.controller = d6;
  }
  get mainWindow() {
    return this.__mainWindow.get();
  }
  set mainWindow(c6) {
    this.__mainWindow.set(c6);
  }
  get fontSize() {
    return this.__fontSize.get();
  }
  set fontSize(b6) {
    this.__fontSize.set(b6);
  }
  get maxLines() {
    return this.__maxLines.get();
  }
  set maxLines(a6) {
    this.__maxLines.set(a6);
  }
  get windowStandardHeight() {
    return this.__windowStandardHeight.get();
  }
  set windowStandardHeight(z5) {
    this.__windowStandardHeight.set(z5);
  }
  get symbolEffect() {
    return this.__symbolEffect.get();
  }
  set symbolEffect(y5) {
    this.__symbolEffect.set(y5);
  }
  initialRender() {
    this.observeComponentCreation2((m4, n4) => {
      If.create();
      if (this.itemDialog.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((w5, x5) => {
            Column.create();
            Column.width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius(({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }));
          }, Column);
          this.observeComponentCreation2((m5, n5) => {
            If.create();
            if (this.itemDialog.toolBarSymbolOptions?.normal ||
              this.itemDialog.toolBarSymbolOptions?.activated) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((u5, v5) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.itemSymbolModifier);
                  SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
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
                this.observeComponentCreation2((q5, r5) => {
                  Image.create(this.itemDialog.icon);
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
          this.observeComponentCreation2((k5, l5) => {
            Column.create();
            Column.width('100%');
            Column.padding({
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
          }, Column);
          this.observeComponentCreation2((i5, j5) => {
            Text.create(this.itemDialog.content);
            Text.fontSize(TEXT_TOOLBAR_DIALOG);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(this.maxLines);
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
          this.observeComponentCreation2((b5, c5) => {
            Column.create();
            Column.width(this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG);
            Column.constraintSize({ minHeight: this.fontSize === MAX_FONT_SIZE ? MAX_DIALOG : MIN_DIALOG });
            Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
            Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
            Column.borderRadius(({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }));
            Column.justifyContent(FlexAlign.Center);
          }, Column);
          this.observeComponentCreation2((r4, s4) => {
            If.create();
            if (this.itemDialog.toolBarSymbolOptions?.normal ||
              this.itemDialog.toolBarSymbolOptions?.activated) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((z4, a5) => {
                  SymbolGlyph.create();
                  SymbolGlyph.attributeModifier.bind(this)(this.itemSymbolModifier);
                  SymbolGlyph.symbolEffect(ObservedObject.GetRawObject(this.symbolEffect), false);
                  SymbolGlyph.fontColor([{ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }]);
                  SymbolGlyph.fontSize(DIALOG_IMAGE_SIZE);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((v4, w4) => {
                  Image.create(this.itemDialog.icon);
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
  async aboutToAppear() {
    let i4 = this.getUIContext().getHostContext();
    this.mainWindowStage = i4.windowStage.getMainWindowSync();
    let j4 = this.mainWindowStage.getWindowProperties();
    let k4 = j4.windowRect;
    if (px2vp(k4.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    }
    else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
let ToolBarV2SymbolGlyphOptions = class ToolBarV2SymbolGlyphOptions {
};
__decorate([
  Trace
], ToolBarV2SymbolGlyphOptions.prototype, "normal", void 0);
__decorate([
  Trace
], ToolBarV2SymbolGlyphOptions.prototype, "activated", void 0);
ToolBarV2SymbolGlyphOptions = __decorate([
  ObservedV2
], ToolBarV2SymbolGlyphOptions);
export { ToolBarV2SymbolGlyphOptions };
let ToolBarV2Option = class ToolBarV2Option {
  constructor() {
    this.content = '';
    this.action = undefined;
    this.icon = undefined;
    this.state = 1;
    this.iconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.activatedIconColor = { "id": -1, "type": 10001, params: ['sys.color.icon_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.textColor = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.activatedTextColor = { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.toolBarSymbolOptions = undefined;
  }
};
__decorate([
  Trace
], ToolBarV2Option.prototype, "content", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "action", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "icon", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "state", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "iconColor", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "activatedIconColor", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "textColor", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "activatedTextColor", void 0);
__decorate([
  Trace
], ToolBarV2Option.prototype, "toolBarSymbolOptions", void 0);
ToolBarV2Option = __decorate([
  ObservedV2
], ToolBarV2Option);
export { ToolBarV2Option };
let ToolbarTheme = class ToolbarTheme {
  constructor() {
    this.iconPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.iconActivePrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.icon_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontActivatedPrimaryColor = { "id": -1, "type": 10001, params: ['sys.color.font_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
  }
};
__decorate([
  Trace
], ToolbarTheme.prototype, "iconPrimaryColor", void 0);
__decorate([
  Trace
], ToolbarTheme.prototype, "iconActivePrimaryColor", void 0);
__decorate([
  Trace
], ToolbarTheme.prototype, "fontPrimaryColor", void 0);
__decorate([
  Trace
], ToolbarTheme.prototype, "fontActivatedPrimaryColor", void 0);
ToolbarTheme = __decorate([
  ObservedV2
], ToolbarTheme);
let ToolBarV2Modifier = class ToolBarV2Modifier {
  constructor() {
    this.backgroundColorValue = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_toolbar_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.heightValue = LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT);
    this.stateEffectValue = true;
    this.paddingValue = LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
  }
  applyNormalAttribute(y1) {
    y1.backgroundColor(this.backgroundColorValue);
  }
  backgroundColor(x1) {
    this.backgroundColorValue = x1;
    return this;
  }
  height(p) {
    this.heightValue = p;
    return this;
  }
  stateEffect(e) {
    this.stateEffectValue = e;
    return this;
  }
  padding(d) {
    this.paddingValue = d;
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
export class ToolBarV2 extends ViewV2 {
  constructor(a4, b4, c4, d4 = -1, e4, f4) {
    super(a4, d4, f4);
    this.initParam("toolBarList", (b4 && "toolBarList" in b4) ? b4.toolBarList : undefined);
    this.initParam("activateIndex", (b4 && "activateIndex" in b4) ? b4.activateIndex : -1);
    this.$activateIndex = "$activateIndex" in b4 ? b4.$activateIndex : (h4) => { };
    this.initParam("dividerModifier", (b4 && "dividerModifier" in b4) ? b4.dividerModifier : new DividerModifier());
    this.initParam("toolBarModifier", (b4 && "toolBarModifier" in b4) ? b4.toolBarModifier : new ToolBarV2Modifier()
      .padding(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }))
      .stateEffect(true)
      .height(LengthMetrics.vp(DEFAULT_TOOLBAR_HEIGHT))
      .backgroundColor('sys.color.ohos_id_color_toolbar_bg'));
    this.moreText = { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.menuContent = [];
    this.toolBarItemBackground = [];
    this.toolBarTheme = new ToolbarTheme();
    this.symbolEffect = new SymbolEffect();
    this.fontSize = 1;
    this.isFollowSystem = false;
    this.maxFontSizeScale = 3.2;
    this.moreIndex = 4;
    this.moreItem = {
      content: { "id": -1, "type": 10003, params: ['sys.string.ohos_toolbar_more'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      icon: PUBLIC_MORE,
    };
    this.finalizeConstruction();
  }
  onWillApplyTheme(z3) {
    this.toolBarTheme.iconPrimaryColor = z3.colors.iconPrimary;
    this.toolBarTheme.iconActivePrimaryColor = z3.colors.iconEmphasize;
    this.toolBarTheme.fontPrimaryColor = z3.colors.fontPrimary;
    this.toolBarTheme.fontActivatedPrimaryColor = z3.colors.fontEmphasize;
  }
  MoreTabBuilder(j3, k3 = null) {
    this.observeComponentCreation2((v3, w3) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.focusable(true);
      Button.focusOnTouch(true);
      Button.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
      });
      Button.width('100%');
      Button.height('100%');
      Button.bindMenu(this.menuContent, { placement: Placement.TopRight, offset: { x: -12, y: -10 } });
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.backgroundColor(this.toolBarItemBackground[j3]);
      Button.onHover((y3) => {
        if (y3) {
          this.toolBarItemBackground[j3] = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.toolBarItemBackground[j3] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState("pressed");
      Button.backgroundColor((!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[j3] : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      ViewStackProcessor.visualState();
      Button.gestureModifier(this.getItemGestureModifier(this.moreItem, j3));
    }, Button);
    this.observeComponentCreation2((t3, u3) => {
      Column.create();
      Column.width('100%');
      Column.height('100%');
      Column.justifyContent(FlexAlign.Center);
      Column.padding({
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
    }, Column);
    this.observeComponentCreation2((r3, s3) => {
      Image.create(PUBLIC_MORE);
      Image.width(IMAGE_SIZE);
      Image.height(IMAGE_SIZE);
      Image.fillColor(this.toolBarTheme.iconPrimaryColor);
      Image.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
      Image.objectFit(ImageFit.Contain);
      Image.draggable(false);
    }, Image);
    this.observeComponentCreation2((p3, q3) => {
      Text.create(this.moreText);
      Text.fontColor(this.toolBarTheme.fontPrimaryColor);
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.focusable(true);
      Text.focusOnTouch(true);
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }
  TabBuilder(k2, l2 = null) {
    this.observeComponentCreation2((e3, f3) => {
      Button.createWithChild({ type: ButtonType.Normal, stateEffect: false });
      Button.enabled(this.toolBarList[k2]?.state !== ItemState.DISABLE);
      Button.width('100%');
      Button.height('100%');
      Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Button.focusable(!(this.toolBarList[k2]?.state === ItemState.DISABLE));
      Button.focusOnTouch(!(this.toolBarList[k2]?.state === ItemState.DISABLE));
      Button.focusBox({
        margin: LengthMetrics.vp(FOCUS_BOX_MARGIN),
        strokeWidth: LengthMetrics.vp(FOCUS_BOX_BORDER_WIDTH),
        strokeColor: ColorMetrics.resourceColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_focused_outline'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })
      });
      Button.backgroundColor(this.toolBarItemBackground[k2]);
      Button.onHover((i3) => {
        if (i3 && this.toolBarList[k2]?.state !== ItemState.DISABLE) {
          this.toolBarItemBackground[k2] = { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_hover'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
          this.toolBarItemBackground[k2] = Color.Transparent;
        }
      });
      ViewStackProcessor.visualState("pressed");
      Button.backgroundColor((this.toolBarList[k2]?.state === ItemState.DISABLE) ||
        (!this.toolBarModifier.stateEffectValue) ?
      this.toolBarItemBackground[k2] : { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_click_effect'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      ViewStackProcessor.visualState();
      Button.onClick(() => {
        this.clickEventAction(k2);
      });
      Button.gestureModifier(this.getItemGestureModifier(this.toolBarList[k2], k2));
    }, Button);
    this.observeComponentCreation2((c3, d3) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.height('100%');
      Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Column.padding({
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
    }, Column);
    this.observeComponentCreation2((s2, t2) => {
      If.create();
      if (this.toolBarList[k2]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[k2]?.toolBarSymbolOptions?.activated) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a3, b3) => {
            SymbolGlyph.create();
            SymbolGlyph.fontSize(IMAGE_SIZE);
            SymbolGlyph.symbolEffect(this.symbolEffect, false);
            SymbolGlyph.attributeModifier.bind(this)(this.getToolBarSymbolModifier(k2));
            SymbolGlyph.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((w2, x2) => {
            Image.create(this.toolBarList[k2]?.icon);
            Image.width(IMAGE_SIZE);
            Image.height(IMAGE_SIZE);
            Image.fillColor(this.getIconColor(k2));
            Image.margin({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            Image.objectFit(ImageFit.Contain);
            Image.draggable(false);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((q2, r2) => {
      Text.create(this.toolBarList[k2]?.content);
      Text.fontColor(this.getTextColor(k2));
      Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.maxFontSize({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_text_size_caption'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Text.minFontSize(9);
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Center);
      Text.focusable(!(this.toolBarList[k2]?.state === ItemState.DISABLE));
      Text.focusOnTouch(!(this.toolBarList[k2]?.state === ItemState.DISABLE));
    }, Text);
    Text.pop();
    Column.pop();
    Button.pop();
  }
  getFontSizeScale() {
    let i2 = this.getUIContext();
    let j2 = i2.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowSystem) {
      return 1;
    }
    else {
      return Math.min(j2, this.maxFontSizeScale);
    }
  }
  getToolBarSymbolModifier(h2) {
    if (this.activateIndex === h2 && (this.toolBarList[h2]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[h2]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[h2]?.toolBarSymbolOptions?.normal;
  }
  getIconColor(g2) {
    if (this.activateIndex === g2 && (this.toolBarList[g2]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[g2]?.activatedIconColor ?? this.toolBarTheme.iconActivePrimaryColor;
    }
    return this.toolBarList[g2]?.iconColor ?? this.toolBarTheme.iconPrimaryColor;
  }
  getTextColor(f2) {
    if (this.activateIndex === f2 && (this.toolBarList[f2]?.state === ItemState.ACTIVATE)) {
      return this.toolBarList[f2]?.activatedTextColor ?? this.toolBarTheme.fontActivatedPrimaryColor;
    }
    return this.toolBarList[f2]?.textColor ?? this.toolBarTheme.fontPrimaryColor;
  }
  toLengthString(c2) {
    if (c2 === void (0)) {
      return '';
    }
    const d2 = c2.value;
    let e2 = '';
    switch (c2.unit) {
      case LengthUnit.PX:
        e2 = `${d2}px`;
        break;
      case LengthUnit.FP:
        e2 = `${d2}fp`;
        break;
      case LengthUnit.LPX:
        e2 = `${d2}lpx`;
        break;
      case LengthUnit.PERCENT:
        e2 = `${d2 * 100}%`;
        break;
      case LengthUnit.VP:
        e2 = `${d2}vp`;
        break;
      default:
        e2 = `${d2}vp`;
        break;
    }
    return e2;
  }
  clickEventAction(a2) {
    let b2 = this.toolBarList[a2];
    if (b2.state === ItemState.ACTIVATE) {
      if (this.activateIndex === a2) {
        this.$activateIndex(-1);
      }
      else {
        this.$activateIndex(a2);
      }
    }
    if (!(b2.state === ItemState.DISABLE)) {
      b2.action && b2.action();
    }
  }
  getItemGestureModifier(t1, u1) {
    let v1 = new ButtonGestureModifier(null);
    if (t1?.icon || t1?.toolBarSymbolOptions?.activated || t1?.toolBarSymbolOptions?.normal) {
      v1 = new ButtonGestureModifier(new CustomDialogController({
        builder: () => {
          let w1 = new ToolBarDialog(this, {
            itemDialog: t1,
            fontSize: this.fontSize,
            itemSymbolModifier: this.getToolBarSymbolModifier(u1),
          }, undefined, -1, () => { }, { page: "library/src/main/ets/components/toolbar.ets", line: 888, col: 18 });
          w1.setController();
          ViewPU.create(w1);
          let m37 = () => {
            return {
              itemDialog: t1,
              fontSize: this.fontSize,
              itemSymbolModifier: this.getToolBarSymbolModifier(u1)
            };
          };
          w1.paramsGenerator_ = m37;
        },
        maskColor: Color.Transparent,
        isModal: true,
        customStyle: true
      }, this));
      v1.fontSize = this.fontSize;
    }
    return v1;
  }
  refreshData() {
    this.menuContent = [];
    for (let s1 = 0; s1 < this.toolBarList.length; s1++) {
      if (s1 >= this.moreIndex && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.menuContent[s1 - this.moreIndex] = {
          value: this.toolBarList[s1].content,
          action: this.toolBarList[s1].action,
          enabled: this.toolBarList[s1].state !== ItemState.DISABLE,
        };
      }
      else {
        this.menuContent = [];
      }
      this.toolBarItemBackground[s1] = this.toolBarItemBackground[s1] ?? Color.Transparent;
    }
    return true;
  }
  onMeasureSize(l1, m1, n1) {
    this.fontSize = this.getFontSizeScale();
    let o1 = { height: 0, width: 0 };
    m1.forEach((q1) => {
      let r1 = q1.measure(n1);
      o1.width = r1.width;
      o1.height = r1.height;
    });
    return o1;
  }
  aboutToAppear() {
    this.refreshData();
    try {
      this.isFollowSystem = this.getUIContext()?.isFollowingSystemFontScale();
      this.maxFontSizeScale = this.getUIContext()?.getMaxFontScale();
    }
    catch (i1) {
      let j1 = i1?.code;
      let k1 = i1?.message;
      hilog.error(0x3900, 'Ace', `Faild to toolBar getMaxFontScale, code: ${j1}, message: ${k1}`);
    }
  }
  initialRender() {
    this.observeComponentCreation2((g1, h1) => {
      Column.create();
      Column.attributeModifier.bind(this)(this.toolBarModifier);
    }, Column);
    this.observeComponentCreation2((e1, f1) => {
      Divider.create();
      Divider.width('100%');
      Divider.height(1);
      Divider.attributeModifier.bind(this)(this.dividerModifier);
    }, Divider);
    this.observeComponentCreation2((c1, d1) => {
      Row.create();
      Row.justifyContent(FlexAlign.Center);
      Row.constraintSize({
        minHeight: this.toLengthString(this.toolBarModifier.heightValue),
        maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
      });
      Row.width('100%');
      Row.height(this.toLengthString(this.toolBarModifier.heightValue));
      Row.padding({
        start: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
        this.toolBarModifier.paddingValue : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: this.toolBarList.length < TOOLBAR_MAX_LENGTH ?
        this.toolBarModifier.paddingValue : LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      });
    }, Row);
    this.observeComponentCreation2((n, o) => {
      ForEach.create();
      const l37 = (r, s) => {
        const t = r;
        this.observeComponentCreation2((v, w) => {
          If.create();
          if (this.toolBarList.length <= TOOLBAR_MAX_LENGTH || s < this.moreIndex) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((a1, b1) => {
                Row.create();
                Row.height('100%');
                Row.flexShrink(1);
              }, Row);
              this.TabBuilder.bind(this)(s);
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
      this.forEachUpdateFunction(n, this.toolBarList, l37, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    this.observeComponentCreation2((g, h) => {
      If.create();
      if (this.refreshData() && this.toolBarList.length > TOOLBAR_MAX_LENGTH) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((l, m) => {
            Row.create();
            Row.height('100%');
            Row.flexShrink(1);
          }, Row);
          this.MoreTabBuilder.bind(this)(this.moreIndex);
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
  updateStateVars(a) {
    if (a === undefined) {
      return;
    }
    if ("toolBarList" in a) {
      this.updateParam("toolBarList", a.toolBarList);
    }
    if ("activateIndex" in a) {
      this.updateParam("activateIndex", a.activateIndex);
    }
    if ("dividerModifier" in a) {
      this.updateParam("dividerModifier", a.dividerModifier);
    }
    if ("toolBarModifier" in a) {
      this.updateParam("toolBarModifier", a.toolBarModifier);
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
], ToolBarV2.prototype, "activateIndex", void 0);
__decorate([
  Event
], ToolBarV2.prototype, "$activateIndex", void 0);
__decorate([
  Param
], ToolBarV2.prototype, "dividerModifier", void 0);
__decorate([
  Param
], ToolBarV2.prototype, "toolBarModifier", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "menuContent", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "toolBarItemBackground", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "toolBarTheme", void 0);
__decorate([
  Local
], ToolBarV2.prototype, "fontSize", void 0);

export default { ToolBarOptions, ToolBar, ItemState, ToolBarOption, ToolBarModifier, ToolBarV2, ToolBarV2Option, ToolBarV2Modifier };