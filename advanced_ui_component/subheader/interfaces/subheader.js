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

var _a;
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const TextModifier = requireNapi('arkui.modifier').TextModifier;
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const resourceManager = requireNapi('resourceManager');
const hilog = requireNapi('hilog');
const INDEX_ZERO = 0;
const INDEX_ONE = 1;
const INDEX_TWO = 2;
const SINGLE_LINE_NUM = 1;
const DOUBLE_LINE_NUM = 2;
const SINGLE_LINE_HEIGHT = 56;
const DOUBLE_LINE_HEIGHT = 72;
const BORDER_WIDTH = 2;
const RESOURCE_TYPE_SYMBOL = 40000;
const LEFT_ICON_SIZE = 16;
const BUTTON_ZONE_SIZE = 32;
const BUTTON_HEIGHT = 28;
const ARROW_ICON_WIDTH = 12;
const ARROW_ICON_HEIGHT = 24;
const SINGLE_ICON_ZONE_SIZE = 28;
const RIGHT_SINGLE_ICON_SIZE = 24;
const LOADING_SIZE = 24;
const PADDING_LEVEL_2 = 4;
const MAX_RIGHT_WIDTH = '34%';

export var OperationType;
(function (q12) {
  q12[q12["TEXT_ARROW"] = 0] = "TEXT_ARROW";
  q12[q12["BUTTON"] = 1] = "BUTTON";
  q12[q12["ICON_GROUP"] = 2] = "ICON_GROUP";
  q12[q12["LOADING"] = 3] = "LOADING";
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
      "id": -1,
      "type": 10001,
      params: ['sys.color.font_primary'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.fontSecondaryColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.font_secondary'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.fontButtonColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.font_emphasize'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.iconArrowColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.icon_tertiary'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.textArrowHoverBgColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.interactive_hover'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.borderFocusColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.interactive_focus'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.leftIconColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.icon_secondary'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
    this.rightIconColor = {
      "id": -1,
      "type": 10001,
      params: ['sys.color.icon_primary'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    };
  }
}

function __Text__secondaryTitleStyles(p12) {
  Text.fontSize({
    "id": -1,
    "type": 10002,
    params: ['sys.float.Subtitle_S'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
  });
  Text.fontColor(p12?.fontColor ?? {
    "id": -1,
    "type": 10001,
    params: ['sys.color.font_secondary'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
  });
  Text.fontWeight(p12?.fontWeight);
  Text.maxLines(p12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(p12?.alignment);
}

function __Text__primaryTitleStyles(o12) {
  Text.fontSize({
    "id": -1,
    "type": 10002,
    params: ['sys.float.Subtitle_L'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
  });
  Text.fontColor(o12?.fontColor ?? {
    "id": -1,
    "type": 10001,
    params: ['sys.color.font_primary'],
    "bundleName": "__harDefaultBundleName__",
    "moduleName": "__harDefaultModuleName__"
  });
  Text.fontWeight(o12?.fontWeight);
  Text.maxLines(o12?.maxLines);
  Text.textOverflow({ overflow: TextOverflow.Ellipsis });
  Text.align(o12?.alignment);
}

export class SubHeader extends ViewPU {
  constructor(i12, j12, k12, l12 = -1, m12 = undefined, n12) {
    super(i12, k12, l12, n12);
    if (typeof m12 === "function") {
      this.paramsGenerator_ = m12;
    }
    this.__icon = new SynchedPropertyObjectOneWayPU(j12.icon, this, "icon");
    this.iconSymbolOptions = null;
    this.__primaryTitle = new SynchedPropertyObjectOneWayPU(j12.primaryTitle, this, "primaryTitle");
    this.__primaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "primaryTitleModifier");
    this.__secondaryTitle = new SynchedPropertyObjectOneWayPU(j12.secondaryTitle, this, "secondaryTitle");
    this.__secondaryTitleModifier = new ObservedPropertyObjectPU(new TextModifier(), this, "secondaryTitleModifier");
    this.select = null;
    this.__operationType = new SynchedPropertySimpleOneWayPU(j12.operationType, this, "operationType");
    this.operationItem = null;
    this.operationSymbolOptions = null;
    this.__textArrowBgColor = new ObservedPropertyObjectPU({
      "id": -1,
      "type": 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    }, this, "textArrowBgColor");
    this.__buttonBgColor = new ObservedPropertyObjectPU({
      "id": -1,
      "type": 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    }, this, "buttonBgColor");
    this.__textArrowFocus = new ObservedPropertySimplePU(false, this, "textArrowFocus");
    this.__buttonFocus = new ObservedPropertySimplePU(false, this, "buttonFocus");
    this.__textArrowStyleWidth = new ObservedPropertySimplePU(0, this, "textArrowStyleWidth");
    this.__textArrowStyleHeight = new ObservedPropertySimplePU(0, this, "textArrowStyleHeight");
    this.__buttonStyleWidth = new ObservedPropertySimplePU(0, this, "buttonStyleWidth");
    this.__buttonStyleHeight = new ObservedPropertySimplePU(0, this, "buttonStyleHeight");
    this.__iconWidth = new ObservedPropertySimplePU(0, this, "iconWidth");
    this.__selectedIndex = new ObservedPropertyObjectPU(-1, this, "selectedIndex");
    this.__selectValue = new ObservedPropertyObjectPU('', this, "selectValue");
    this.__flexAlign = new ObservedPropertySimplePU(FlexAlign.SpaceBetween, this, "flexAlign");
    this.titleBuilder = undefined;
    this.__contentMargin = new SynchedPropertyObjectOneWayPU(j12.contentMargin, this, "contentMargin");
    this.__contentPadding = new SynchedPropertyObjectOneWayPU(j12.contentPadding, this, "contentPadding");
    this.__subHeaderMargin = new ObservedPropertyObjectPU({
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0)
    }, this, "subHeaderMargin");
    this.__subHeaderTheme = new ObservedPropertyObjectPU(new SubHeaderTheme(), this, "subHeaderTheme");
    this.addProvidedVar("subHeaderTheme", this.__subHeaderTheme, false);
    this.setInitiallyProvidedValue(j12);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(h12) {
    if (h12.icon === undefined) {
      this.__icon.set(null);
    }
    if (h12.iconSymbolOptions !== undefined) {
      this.iconSymbolOptions = h12.iconSymbolOptions;
    }
    if (h12.primaryTitle === undefined) {
      this.__primaryTitle.set(null);
    }
    if (h12.primaryTitleModifier !== undefined) {
      this.primaryTitleModifier = h12.primaryTitleModifier;
    }
    if (h12.secondaryTitle === undefined) {
      this.__secondaryTitle.set(null);
    }
    if (h12.secondaryTitleModifier !== undefined) {
      this.secondaryTitleModifier = h12.secondaryTitleModifier;
    }
    if (h12.select !== undefined) {
      this.select = h12.select;
    }
    if (h12.operationType === undefined) {
      this.__operationType.set(OperationType.BUTTON);
    }
    if (h12.operationItem !== undefined) {
      this.operationItem = h12.operationItem;
    }
    if (h12.operationSymbolOptions !== undefined) {
      this.operationSymbolOptions = h12.operationSymbolOptions;
    }
    if (h12.textArrowBgColor !== undefined) {
      this.textArrowBgColor = h12.textArrowBgColor;
    }
    if (h12.buttonBgColor !== undefined) {
      this.buttonBgColor = h12.buttonBgColor;
    }
    if (h12.textArrowFocus !== undefined) {
      this.textArrowFocus = h12.textArrowFocus;
    }
    if (h12.buttonFocus !== undefined) {
      this.buttonFocus = h12.buttonFocus;
    }
    if (h12.textArrowStyleWidth !== undefined) {
      this.textArrowStyleWidth = h12.textArrowStyleWidth;
    }
    if (h12.textArrowStyleHeight !== undefined) {
      this.textArrowStyleHeight = h12.textArrowStyleHeight;
    }
    if (h12.buttonStyleWidth !== undefined) {
      this.buttonStyleWidth = h12.buttonStyleWidth;
    }
    if (h12.buttonStyleHeight !== undefined) {
      this.buttonStyleHeight = h12.buttonStyleHeight;
    }
    if (h12.iconWidth !== undefined) {
      this.iconWidth = h12.iconWidth;
    }
    if (h12.selectedIndex !== undefined) {
      this.selectedIndex = h12.selectedIndex;
    }
    if (h12.selectValue !== undefined) {
      this.selectValue = h12.selectValue;
    }
    if (h12.flexAlign !== undefined) {
      this.flexAlign = h12.flexAlign;
    }
    if (h12.titleBuilder !== undefined) {
      this.titleBuilder = h12.titleBuilder;
    }
    if (h12.subHeaderMargin !== undefined) {
      this.subHeaderMargin = h12.subHeaderMargin;
    }
    if (h12.subHeaderTheme !== undefined) {
      this.subHeaderTheme = h12.subHeaderTheme;
    }
  }

  updateStateVars(g12) {
    this.__icon.reset(g12.icon);
    this.__primaryTitle.reset(g12.primaryTitle);
    this.__secondaryTitle.reset(g12.secondaryTitle);
    this.__operationType.reset(g12.operationType);
    this.__contentMargin.reset(g12.contentMargin);
    this.__contentPadding.reset(g12.contentPadding);
  }

  purgeVariableDependenciesOnElmtId(f12) {
    this.__icon.purgeDependencyOnElmtId(f12);
    this.__primaryTitle.purgeDependencyOnElmtId(f12);
    this.__primaryTitleModifier.purgeDependencyOnElmtId(f12);
    this.__secondaryTitle.purgeDependencyOnElmtId(f12);
    this.__secondaryTitleModifier.purgeDependencyOnElmtId(f12);
    this.__operationType.purgeDependencyOnElmtId(f12);
    this.__textArrowBgColor.purgeDependencyOnElmtId(f12);
    this.__buttonBgColor.purgeDependencyOnElmtId(f12);
    this.__textArrowFocus.purgeDependencyOnElmtId(f12);
    this.__buttonFocus.purgeDependencyOnElmtId(f12);
    this.__textArrowStyleWidth.purgeDependencyOnElmtId(f12);
    this.__textArrowStyleHeight.purgeDependencyOnElmtId(f12);
    this.__buttonStyleWidth.purgeDependencyOnElmtId(f12);
    this.__buttonStyleHeight.purgeDependencyOnElmtId(f12);
    this.__iconWidth.purgeDependencyOnElmtId(f12);
    this.__selectedIndex.purgeDependencyOnElmtId(f12);
    this.__selectValue.purgeDependencyOnElmtId(f12);
    this.__flexAlign.purgeDependencyOnElmtId(f12);
    this.__contentMargin.purgeDependencyOnElmtId(f12);
    this.__contentPadding.purgeDependencyOnElmtId(f12);
    this.__subHeaderMargin.purgeDependencyOnElmtId(f12);
    this.__subHeaderTheme.purgeDependencyOnElmtId(f12);
  }

  aboutToBeDeleted() {
    this.__icon.aboutToBeDeleted();
    this.__primaryTitle.aboutToBeDeleted();
    this.__primaryTitleModifier.aboutToBeDeleted();
    this.__secondaryTitle.aboutToBeDeleted();
    this.__secondaryTitleModifier.aboutToBeDeleted();
    this.__operationType.aboutToBeDeleted();
    this.__textArrowBgColor.aboutToBeDeleted();
    this.__buttonBgColor.aboutToBeDeleted();
    this.__textArrowFocus.aboutToBeDeleted();
    this.__buttonFocus.aboutToBeDeleted();
    this.__textArrowStyleWidth.aboutToBeDeleted();
    this.__textArrowStyleHeight.aboutToBeDeleted();
    this.__buttonStyleWidth.aboutToBeDeleted();
    this.__buttonStyleHeight.aboutToBeDeleted();
    this.__iconWidth.aboutToBeDeleted();
    this.__selectedIndex.aboutToBeDeleted();
    this.__selectValue.aboutToBeDeleted();
    this.__flexAlign.aboutToBeDeleted();
    this.__contentMargin.aboutToBeDeleted();
    this.__contentPadding.aboutToBeDeleted();
    this.__subHeaderMargin.aboutToBeDeleted();
    this.__subHeaderTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  get icon() {
    return this.__icon.get();
  }

  set icon(e12) {
    this.__icon.set(e12);
  }

  get primaryTitle() {
    return this.__primaryTitle.get();
  }

  set primaryTitle(d12) {
    this.__primaryTitle.set(d12);
  }

  get primaryTitleModifier() {
    return this.__primaryTitleModifier.get();
  }

  set primaryTitleModifier(c12) {
    this.__primaryTitleModifier.set(c12);
  }

  get secondaryTitle() {
    return this.__secondaryTitle.get();
  }

  set secondaryTitle(b12) {
    this.__secondaryTitle.set(b12);
  }

  get secondaryTitleModifier() {
    return this.__secondaryTitleModifier.get();
  }

  set secondaryTitleModifier(a12) {
    this.__secondaryTitleModifier.set(a12);
  }

  get operationType() {
    return this.__operationType.get();
  }

  set operationType(z11) {
    this.__operationType.set(z11);
  }

  get textArrowBgColor() {
    return this.__textArrowBgColor.get();
  }

  set textArrowBgColor(y11) {
    this.__textArrowBgColor.set(y11);
  }

  get buttonBgColor() {
    return this.__buttonBgColor.get();
  }

  set buttonBgColor(x11) {
    this.__buttonBgColor.set(x11);
  }

  get textArrowFocus() {
    return this.__textArrowFocus.get();
  }

  set textArrowFocus(w11) {
    this.__textArrowFocus.set(w11);
  }

  get buttonFocus() {
    return this.__buttonFocus.get();
  }

  set buttonFocus(v11) {
    this.__buttonFocus.set(v11);
  }

  get textArrowStyleWidth() {
    return this.__textArrowStyleWidth.get();
  }

  set textArrowStyleWidth(u11) {
    this.__textArrowStyleWidth.set(u11);
  }

  get textArrowStyleHeight() {
    return this.__textArrowStyleHeight.get();
  }

  set textArrowStyleHeight(t11) {
    this.__textArrowStyleHeight.set(t11);
  }

  get buttonStyleWidth() {
    return this.__buttonStyleWidth.get();
  }

  set buttonStyleWidth(s11) {
    this.__buttonStyleWidth.set(s11);
  }

  get buttonStyleHeight() {
    return this.__buttonStyleHeight.get();
  }

  set buttonStyleHeight(r11) {
    this.__buttonStyleHeight.set(r11);
  }

  get iconWidth() {
    return this.__iconWidth.get();
  }

  set iconWidth(q11) {
    this.__iconWidth.set(q11);
  }

  get selectedIndex() {
    return this.__selectedIndex.get();
  }

  set selectedIndex(p11) {
    this.__selectedIndex.set(p11);
  }

  get selectValue() {
    return this.__selectValue.get();
  }

  set selectValue(o11) {
    this.__selectValue.set(o11);
  }

  get flexAlign() {
    return this.__flexAlign.get();
  }

  set flexAlign(n11) {
    this.__flexAlign.set(n11);
  }

  get contentMargin() {
    return this.__contentMargin.get();
  }

  set contentMargin(m11) {
    this.__contentMargin.set(m11);
  }

  get contentPadding() {
    return this.__contentPadding.get();
  }

  set contentPadding(l11) {
    this.__contentPadding.set(l11);
  }

  get subHeaderMargin() {
    return this.__subHeaderMargin.get();
  }

  set subHeaderMargin(k11) {
    this.__subHeaderMargin.set(k11);
  }

  get subHeaderTheme() {
    return this.__subHeaderTheme.get();
  }

  set subHeaderTheme(j11) {
    this.__subHeaderTheme.set(j11);
  }

  onWillApplyTheme(i11) {
    this.subHeaderTheme.fontPrimaryColor = i11.colors.fontPrimary;
    this.subHeaderTheme.fontSecondaryColor = i11.colors.fontSecondary;
    this.subHeaderTheme.fontButtonColor = i11.colors.fontEmphasize;
    this.subHeaderTheme.iconArrowColor = i11.colors.iconTertiary;
    this.subHeaderTheme.textArrowHoverBgColor = i11.colors.interactiveHover;
    this.subHeaderTheme.borderFocusColor = i11.colors.interactiveFocus;
    this.subHeaderTheme.leftIconColor = i11.colors.iconSecondary;
    this.subHeaderTheme.rightIconColor = i11.colors.iconPrimary;
  }

  initialRender() {
    this.observeComponentCreation2((g11, h11) => {
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.End });
      Flex.constraintSize({ minHeight: this.getMinHeight() });
      Flex.margin(this.contentMargin ?? this.subHeaderMargin);
      Flex.padding(this.getAreaPadding());
    }, Flex);
    this.observeComponentCreation2((e11, f11) => {
      Row.create();
      Row.width('100%');
      Row.flexShrink(1);
    }, Row);
    this.leftArea.bind(this)(this);
    Row.pop();
    this.observeComponentCreation2((c11, d11) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.constraintSize({ maxWidth: this.getMaxWidth() });
      Row.flexShrink(0);
    }, Row);
    this.rightArea.bind(this)(this);
    Row.pop();
    Flex.pop();
  }

  onMeasureSize(s10, t10, u10) {
    let v10 = { width: s10.width, height: s10.height };
    t10.forEach((x10) => {
      if (!this.contentMargin) {
        let y10 = Number(u10.maxWidth);
        if (y10 < Util.BREAKPOINT_S) {
          this.subHeaderMargin = {
            start: LengthMetrics.resource({
              "id": -1,
              "type": 10002,
              params: ['sys.float.padding_level8'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
              "id": -1,
              "type": 10002,
              params: ['sys.float.padding_level8'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            }),
          };
        }
        else if (y10 < Util.BREAKPOINT_M) {
          this.subHeaderMargin = {
            start: LengthMetrics.resource({
              "id": -1,
              "type": 10002,
              params: ['sys.float.padding_level12'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
              "id": -1,
              "type": 10002,
              params: ['sys.float.padding_level12'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            }),
          };
        }
        else {
          this.subHeaderMargin = {
            start: LengthMetrics.resource({
              "id": -1,
              "type": 10002,
              params: ['sys.float.padding_level16'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            }),
            end: LengthMetrics.resource({
              "id": -1,
              "type": 10002,
              params: ['sys.float.padding_level16'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            }),
          };
        }
      }
      u10.minHeight = Math.min(Number(this.getMinHeight()), Number(u10.maxHeight));
      v10.height = x10.measure(u10).height;
      v10.width = Number(u10.maxWidth);
    });
    return v10;
  }

  onPlaceChildren(n10, o10, p10) {
    o10.forEach((r10) => {
      r10.layout({ x: 0, y: 0 });
    });
  }

  getMaxWidth() {
    if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
      return '100%';
    }
    else {
      return MAX_RIGHT_WIDTH;
    }
  }

  getMinHeight() {
    if (this.secondaryTitle && this.icon) {
      return SINGLE_LINE_HEIGHT;
    }
    else if (this.secondaryTitle && this.primaryTitle) {
      return DOUBLE_LINE_HEIGHT;
    }
    return SINGLE_LINE_HEIGHT;
  }

  getTextArrowPaddingLeft() {
    if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
      return LengthMetrics.resource({
        "id": -1,
        "type": 10002,
        params: ['sys.float.padding_level1'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      });
    }
    return LengthMetrics.resource({
      "id": -1,
      "type": 10002,
      params: ['sys.float.padding_level0'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    });
  }

  getTextArrowMarginRight() {
    if (this.operationItem && this.operationItem.length > 0 && this.operationItem[0].value) {
      return LengthMetrics.vp(PADDING_LEVEL_2 + ARROW_ICON_WIDTH);
    }
    return LengthMetrics.vp(ARROW_ICON_WIDTH);
  }

  getAreaPadding() {
    if (this.contentPadding) {
      return this.contentPadding;
    }
    let m10 = {};
    if (!this.titleBuilder && ((this.secondaryTitle && this.icon) ||
      (!this.primaryTitle && this.secondaryTitle))) {
      m10 = {
        start: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level6'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        end: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level6'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        })
      };
    }
    return m10;
  }

  leftArea(b10 = null) {
    this.observeComponentCreation2((d10, e10) => {
      If.create();
      if (this.titleBuilder) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.titleBuilder.bind(this)(b10 ? b10 : this);
        });
      }
      else if (this.secondaryTitle && this.icon) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.IconSecondaryTitleStyle.bind(this)(makeBuilderParameterProxy("IconSecondaryTitleStyle", {
            content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"]),
            iconOptions: () => ({
              icon: this.icon,
              symbolicIconOption: this.iconSymbolOptions,
            })
          }), b10 ? b10 : this);
        });
      }
      else if (this.secondaryTitle && this.primaryTitle) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.SubTitleStyle.bind(this)(makeBuilderParameterProxy("SubTitleStyle", {
            content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"]),
            subContent: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"])
          }), b10 ? b10 : this);
        });
      }
      else if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(3, () => {
          this.SecondTitleStyle.bind(this)(makeBuilderParameterProxy("SecondTitleStyle", {
            content: () => (this["__secondaryTitle"] ? this["__secondaryTitle"] : this["secondaryTitle"])
          }), b10 ? b10 : this);
        });
      }
      else if (this.select) {
        this.ifElseBranchUpdateFunction(4, () => {
          this.SelectStyle.bind(this)(this.select, b10 ? b10 : this);
        });
      }
      else if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(5, () => {
          this.PrimaryTitleStyle.bind(this)(makeBuilderParameterProxy("PrimaryTitleStyle", {
            content: () => (this["__primaryTitle"] ? this["__primaryTitle"] : this["primaryTitle"])
          }), b10 ? b10 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(6, () => {
          this.dummyFunction.bind(this)(b10 ? b10 : this);
        });
      }
    }, If);
    If.pop();
  }

  rightArea(g9 = null) {
    this.observeComponentCreation2((x9, y9) => {
      If.create();
      if (this.operationType === OperationType.BUTTON && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.ButtonStyle.bind(this)(this.operationItem[0], g9 ? g9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((t9, u9) => {
      If.create();
      if (this.operationType === OperationType.TEXT_ARROW && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.TextArrowStyle.bind(this)(this.operationItem[0], g9 ? g9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((p9, q9) => {
      If.create();
      if (this.operationType === OperationType.ICON_GROUP && (this.operationItem && this.operationItem.length > 0)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.IconGroupStyle.bind(this)(this.operationItem, g9 ? g9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((l9, m9) => {
      If.create();
      if (this.operationType === OperationType.LOADING) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.LoadingProcessStyle.bind(this)(g9 ? g9 : this);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
  }

  IconSecondaryTitleStyle(m8, n8 = null) {
    this.observeComponentCreation2((d9, e9) => {
      Flex.create({ direction: FlexDirection.Row, alignItems: ItemAlign.Center });
      Flex.padding({
        end: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level6'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        top: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        bottom: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
      });
      Flex.onAppear(() => {
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Flex);
    this.observeComponentCreation2((t8, u8) => {
      If.create();
      if (Util.isSymbolResource(m8.iconOptions?.icon)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b9, c9) => {
            SymbolGlyph.create(m8.iconOptions?.icon);
            SymbolGlyph.fontSize(m8.iconOptions?.symbolicIconOption?.fontSize ?? LEFT_ICON_SIZE);
            SymbolGlyph.fontColor(m8.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.leftIconColor]);
            SymbolGlyph.fontWeight(m8.iconOptions?.symbolicIconOption?.fontWeight);
            SymbolGlyph.renderingStrategy(m8.iconOptions?.symbolicIconOption?.renderingStrategy);
            SymbolGlyph.effectStrategy(m8.iconOptions?.symbolicIconOption?.effectStrategy);
            SymbolGlyph.margin({
              end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level4'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              })
            });
            SymbolGlyph.flexShrink(0);
          }, SymbolGlyph);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((x8, y8) => {
            Image.create(m8.iconOptions?.icon);
            Image.fillColor(this.subHeaderTheme.leftIconColor);
            Image.width(LEFT_ICON_SIZE);
            Image.height(LEFT_ICON_SIZE);
            Image.margin({
              end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level4'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              })
            });
            Image.draggable(false);
            Image.flexShrink(0);
          }, Image);
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((r8, s8) => {
      Text.create(m8.content);
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

  SubTitleStyle(a8, b8 = null) {
    this.observeComponentCreation2((j8, k8) => {
      Column.create();
      Column.padding({
        end: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level0'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        top: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        bottom: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
      });
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Column);
    this.observeComponentCreation2((h8, i8) => {
      Text.create(a8.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: SINGLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontPrimaryColor,
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
      Text.width('100%');
    }, Text);
    Text.pop();
    this.observeComponentCreation2((f8, g8) => {
      Text.create(a8.subContent);
      __Text__secondaryTitleStyles({
        maxLines: SINGLE_LINE_NUM,
        fontWeight: FontWeight.Regular,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontSecondaryColor,
      });
      Text.width('100%');
      Text.margin({
        top: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level1'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
    }, Text);
    Text.pop();
    Column.pop();
  }

  SecondTitleStyle(r7, s7 = null) {
    this.observeComponentCreation2((y7, z7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        end: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level6'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        top: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        bottom: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
      });
    }, Column);
    this.observeComponentCreation2((v7, w7) => {
      Text.create(r7.content);
      __Text__secondaryTitleStyles({
        maxLines: DOUBLE_LINE_NUM,
        fontWeight: FontWeight.Medium,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontSecondaryColor,
      });
      Text.width('100%');
      Text.onAppear(() => {
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.secondaryTitleModifier));
    }, Text);
    Text.pop();
    Column.pop();
  }

  SelectStyle(f7, g7 = null) {
    this.observeComponentCreation2((o7, p7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.onAppear(() => {
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
    }, Column);
    this.observeComponentCreation2((j7, k7) => {
      Select.create(f7.options);
      Select.selected(ObservedObject.GetRawObject(this.selectedIndex));
      Select.value(ObservedObject.GetRawObject(this.selectValue));
      Select.onSelect((m7, n7) => {
        this.selectedIndex = m7;
        if (n7) {
          this.selectValue = n7;
        }
        if (f7.onSelect) {
          f7.onSelect(m7, n7);
        }
      });
      Select.font({
        size: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.Body_L'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        weight: FontWeight.Medium,
      });
    }, Select);
    Select.pop();
    Column.pop();
  }

  PrimaryTitleStyle(w6, x6 = null) {
    this.observeComponentCreation2((d7, e7) => {
      Column.create();
      Column.alignItems(HorizontalAlign.Start);
      Column.padding({
        end: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level0'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        top: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        bottom: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
      });
    }, Column);
    this.observeComponentCreation2((a7, b7) => {
      Text.create(w6.content);
      __Text__primaryTitleStyles({
        fontWeight: FontWeight.Bold,
        maxLines: DOUBLE_LINE_NUM,
        alignment: Alignment.Start,
        fontColor: this.subHeaderTheme.fontPrimaryColor,
      });
      Text.width('100%');
      Text.onAppear(() => {
        this.changeFlexAlign(FlexAlign.SpaceBetween);
      });
      Text.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.primaryTitleModifier));
    }, Text);
    Text.pop();
    Column.pop();
  }

  ButtonStyle(k5, l5 = null) {
    this.observeComponentCreation2((u6, v6) => {
      Row.create();
      Row.margin({
        start: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        })
      });
      Row.justifyContent(FlexAlign.End);
    }, Row);
    this.observeComponentCreation2((s6, t6) => {
      Stack.create();
      Stack.focusable(true);
    }, Stack);
    this.observeComponentCreation2((x5, y5) => {
      If.create();
      if (k5) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((f6, g6) => {
            Row.create();
            Row.padding({
              start: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level1'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              }),
              end: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level1'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              }),
              top: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level2'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              }),
              bottom: LengthMetrics.resource({
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level2'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              })
            });
            Row.margin({
              bottom: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level2'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              },
            });
            Row.backgroundColor(ObservedObject.GetRawObject(this.buttonBgColor));
            Row.focusable(true);
            Row.constraintSize({ minHeight: BUTTON_HEIGHT });
            Row.justifyContent(FlexAlign.End);
            Row.borderRadius({
              "id": -1,
              "type": 10002,
              params: ['sys.float.corner_radius_level4'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            });
            Row.onFocus(() => {
              this.buttonFocus = true;
            });
            Row.onBlur(() => {
              this.buttonFocus = false;
            });
            Row.onHover((r6) => {
              if (r6) {
                this.buttonBgColor = this.subHeaderTheme.textArrowHoverBgColor;
              }
              else {
                this.buttonBgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
            });
            Row.onTouch((q6) => {
              if (q6.type === TouchType.Down) {
                this.buttonBgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.interactive_pressed'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
              if (q6.type === TouchType.Up) {
                this.buttonBgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
            });
            Row.onClick((p6) => {
              if (k5.action) {
                k5.action();
              }
            });
            Row.onAreaChange((n6, o6) => {
              this.buttonStyleWidth = Number(o6.width);
              this.buttonStyleHeight = Number(o6.height);
            });
          }, Row);
          this.observeComponentCreation2((d6, e6) => {
            Text.create(k5.value);
            __Text__secondaryTitleStyles({
              fontWeight: FontWeight.Medium,
              maxLines: DOUBLE_LINE_NUM,
              fontColor: this.subHeaderTheme.fontButtonColor,
            });
            Text.focusable(true);
          }, Text);
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((q5, r5) => {
      If.create();
      if (this.buttonFocus) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((v5, w5) => {
            Row.create();
            Row.height(this.buttonStyleHeight);
            Row.width(this.buttonStyleWidth);
            Row.hitTestBehavior(HitTestMode.None);
            Row.border({
              width: BORDER_WIDTH,
              color: this.subHeaderTheme.borderFocusColor
            });
            Row.borderRadius({
              "id": -1,
              "type": 10002,
              params: ['sys.float.corner_radius_level4'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            });
          }, Row);
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    Stack.pop();
    Row.pop();
  }

  TextArrowStyle(a4, b4 = null) {
    this.observeComponentCreation2((c5, d5) => {
      Row.create();
      Row.onHover((j5) => {
        if (j5) {
          this.textArrowBgColor = this.subHeaderTheme.textArrowHoverBgColor;
        }
        else {
          this.textArrowBgColor = {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
          };
        }
      });
      Row.onTouch((i5) => {
        if (i5.type === TouchType.Down) {
          this.textArrowBgColor = {
            "id": -1,
            "type": 10001,
            params: ['sys.color.interactive_pressed'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
          };
        }
        if (i5.type === TouchType.Up) {
          this.textArrowBgColor = {
            "id": -1,
            "type": 10001,
            params: ['sys.color.ohos_id_color_sub_background_transparent'],
            "bundleName": "__harDefaultBundleName__",
            "moduleName": "__harDefaultModuleName__"
          };
        }
      });
      Row.onClick((h5) => {
        if (a4.action) {
          a4.action();
        }
      });
      Row.focusable(true);
      Row.justifyContent(FlexAlign.End);
      Row.margin({
        start: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        bottom: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level2'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
      });
    }, Row);
    this.observeComponentCreation2((a5, b5) => {
      Stack.create();
    }, Stack);
    this.observeComponentCreation2((t4, u4) => {
      Row.create();
      Row.alignItems(VerticalAlign.Center);
      Row.borderRadius({
        "id": -1,
        "type": 10002,
        params: ['sys.float.corner_radius_level4'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      });
      Row.focusable(true);
      Row.backgroundColor(ObservedObject.GetRawObject(this.textArrowBgColor));
      Row.constraintSize({ minHeight: BUTTON_ZONE_SIZE });
      Row.onFocus(() => {
        this.textArrowFocus = true;
      });
      Row.onBlur(() => {
        this.textArrowFocus = false;
      });
      Row.padding({
        start: this.getTextArrowPaddingLeft(),
        top: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level2'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
        bottom: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level2'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        }),
      });
      Row.onAreaChange((y4, z4) => {
        this.textArrowStyleWidth = Number(z4.width);
        this.textArrowStyleHeight = Number(z4.height);
      });
    }, Row);
    this.observeComponentCreation2((m4, n4) => {
      If.create();
      if (a4) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r4, s4) => {
            Text.create(a4.value);
            __Text__secondaryTitleStyles({
              maxLines: DOUBLE_LINE_NUM,
              fontWeight: FontWeight.Regular,
              alignment: Alignment.End,
              fontColor: this.subHeaderTheme.fontSecondaryColor,
            });
            Text.margin({
              end: this.getTextArrowMarginRight(), 
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
    Row.pop();
    this.observeComponentCreation2((k4, l4) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.height(this.textArrowStyleHeight);
      Row.width(this.textArrowStyleWidth);
      Row.hitTestBehavior(HitTestMode.None);
      Row.border({
        radius: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.corner_radius_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        width: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.outline_extra_larger'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        color: {
          "id": -1,
          "type": 10001,
          params: ['sys.color.interactive_focus'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
      });
      ViewStackProcessor.visualState("focused");
      Row.border({
        radius: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.corner_radius_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        width: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.outline_extra_larger'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        color: this.subHeaderTheme.borderFocusColor,
      });
      ViewStackProcessor.visualState("pressed");
      Row.backgroundColor({
        "id": -1,
        "type": 10001,
        params: ['sys.color.interactive_pressed'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      });
      ViewStackProcessor.visualState("disabled");
      Row.opacity({
        "id": -1,
        "type": 10002,
        params: ['sys.float.interactive_disable'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      });
      ViewStackProcessor.visualState("normal");
      Row.border({
        radius: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.corner_radius_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        width: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.border_none'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        color: {
          "id": -1,
          "type": 10001,
          params: ['sys.color.ohos_id_color_focused_outline_transparent'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
      });
      ViewStackProcessor.visualState();
    }, Row);
    this.observeComponentCreation2((i4, j4) => {
      Image.create({
        "id": -1,
        "type": 20000,
        params: ['sys.media.ohos_ic_public_arrow_right'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      });
      Image.fillColor(this.subHeaderTheme.iconArrowColor);
      Image.width(ARROW_ICON_WIDTH);
      Image.height(ARROW_ICON_HEIGHT);
      Image.focusable(true);
      Image.draggable(false);
      Image.matchTextDirection(true);
    }, Image);
    Row.pop();
    Stack.pop();
    Row.pop();
  }

  IconGroupStyle(l2, m2 = null) {
    this.observeComponentCreation2((y3, z3) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.focusable(true);
      Row.margin({
        start: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        })
      });
    }, Row);
    this.observeComponentCreation2((p2, q2) => {
      ForEach.create();
      const r2 = (t2, u2) => {
        const v2 = t2;
        this.observeComponentCreation2((x2, y2) => {
          If.create();
          if (Util.isResourceType(v2.value)) {
            this.ifElseBranchUpdateFunction(0, () => {
              this.observeComponentCreation2((c3, d3) => {
                If.create();
                if (u2 === INDEX_ZERO) {
                  this.ifElseBranchUpdateFunction(0, () => {
                    {
                      this.observeComponentCreation2((s3, t3) => {
                        if (t3) {
                          let u3 = new SingleIconStyle(typeof PUV2ViewBase !== "undefined" && m2 instanceof PUV2ViewBase ? m2 : this, {
                            item: {
                              iconOptions: {
                                icon: v2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > u2 ?
                                  this.operationSymbolOptions[u2] : null,
                              },
                              action: v2.action,
                            }
                          }, undefined, s3, () => {
                          }, {
                            page: "library/src/main/ets/components/mainpage/MainPage.ets",
                            line: 664,
                            col: 13
                          });
                          ViewPU.create(u3);
                          let v3 = () => {
                            return {
                              item: {
                                iconOptions: {
                                  icon: v2.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > u2 ?
                                    this.operationSymbolOptions[u2] : null,
                                },
                                action: v2.action,
                              }
                            };
                          };
                          u3.paramsGenerator_ = v3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(s3, {});
                        }
                      }, { name: "SingleIconStyle" });
                    }
                  });
                }
                else if (u2 === INDEX_ONE || u2 === INDEX_TWO) {
                  this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((o3, p3) => {
                      __Common__.create();
                      __Common__.margin({
                        start: LengthMetrics.resource({
                          "id": -1,
                          "type": 10002,
                          params: ['sys.float.padding_level4'],
                          "bundleName": "__harDefaultBundleName__",
                          "moduleName": "__harDefaultModuleName__"
                        })
                      });
                    }, __Common__);
                    {
                      this.observeComponentCreation2((i3, j3) => {
                        if (j3) {
                          let k3 = new SingleIconStyle(typeof PUV2ViewBase !== "undefined" && m2 instanceof PUV2ViewBase ? m2 : this, {
                            item: {
                              action: v2.action,
                              iconOptions: {
                                icon: v2.value,
                                symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > u2 ?
                                  this.operationSymbolOptions[u2] : null,
                              },
                            }
                          }, undefined, i3, () => {
                          }, {
                            page: "library/src/main/ets/components/mainpage/MainPage.ets",
                            line: 675,
                            col: 13
                          });
                          ViewPU.create(k3);
                          let l3 = () => {
                            return {
                              item: {
                                action: v2.action,
                                iconOptions: {
                                  icon: v2.value,
                                  symbolicIconOption: this.operationSymbolOptions && this.operationSymbolOptions.length > u2 ?
                                    this.operationSymbolOptions[u2] : null,
                                },
                              }
                            };
                          };
                          k3.paramsGenerator_ = l3;
                        }
                        else {
                          this.updateStateVarsOfChildByElmtId(i3, {});
                        }
                      }, { name: "SingleIconStyle" });
                    }
                    __Common__.pop();
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
      };
      this.forEachUpdateFunction(p2, l2, r2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    Row.pop();
  }

  LoadingProcessStyle(e2 = null) {
    this.observeComponentCreation2((j2, k2) => {
      Row.create();
      Row.justifyContent(FlexAlign.End);
      Row.padding({
        top: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level2'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
        bottom: {
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level2'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        },
      });
      Row.margin({
        start: LengthMetrics.resource({
          "id": -1,
          "type": 10002,
          params: ['sys.float.padding_level4'],
          "bundleName": "__harDefaultBundleName__",
          "moduleName": "__harDefaultModuleName__"
        })
      });
    }, Row);
    this.observeComponentCreation2((h2, i2) => {
      LoadingProgress.create();
      LoadingProgress.width(LOADING_SIZE);
      LoadingProgress.height(LOADING_SIZE);
      LoadingProgress.color({
        "id": -1,
        "type": 10001,
        params: ['sys.color.icon_secondary'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      });
    }, LoadingProgress);
    Row.pop();
  }

  dummyFunction(z1 = null) {
    this.observeComponentCreation2((b2, c2) => {
      Row.create();
      Row.onAppear(() => {
        this.changeFlexAlign(FlexAlign.End);
      });
    }, Row);
    Row.pop();
  }

  aboutToAppear() {
    if (this.select) {
      this.selectedIndex = this.select.selected;
      this.selectValue = this.select.value;
    }
  }

  changeFlexAlign(y1) {
    if (this.flexAlign === y1) {
      return;
    }
    this.flexAlign = y1;
  }

  rerender() {
    this.updateDirtyElements();
  }
}

class SingleIconStyle extends ViewPU {
  constructor(s1, t1, u1, v1 = -1, w1 = undefined, x1) {
    super(s1, u1, v1, x1);
    if (typeof w1 === "function") {
      this.paramsGenerator_ = w1;
    }
    this.__bgColor = new ObservedPropertyObjectPU({
      "id": -1,
      "type": 10001,
      params: ['sys.color.ohos_id_color_sub_background_transparent'],
      "bundleName": "__harDefaultBundleName__",
      "moduleName": "__harDefaultModuleName__"
    }, this, "bgColor");
    this.__isFocus = new ObservedPropertySimplePU(false, this, "isFocus");
    this.item = null;
    this.__subHeaderTheme = this.initializeConsume("subHeaderTheme", "subHeaderTheme");
    this.setInitiallyProvidedValue(t1);
    this.finalizeConstruction();
  }

  setInitiallyProvidedValue(r1) {
    if (r1.bgColor !== undefined) {
      this.bgColor = r1.bgColor;
    }
    if (r1.isFocus !== undefined) {
      this.isFocus = r1.isFocus;
    }
    if (r1.item !== undefined) {
      this.item = r1.item;
    }
  }

  updateStateVars(q1) {
  }

  purgeVariableDependenciesOnElmtId(p1) {
    this.__bgColor.purgeDependencyOnElmtId(p1);
    this.__isFocus.purgeDependencyOnElmtId(p1);
    this.__subHeaderTheme.purgeDependencyOnElmtId(p1);
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

  set bgColor(o1) {
    this.__bgColor.set(o1);
  }

  get isFocus() {
    return this.__isFocus.get();
  }

  set isFocus(n1) {
    this.__isFocus.set(n1);
  }

  get subHeaderTheme() {
    return this.__subHeaderTheme.get();
  }

  set subHeaderTheme(m1) {
    this.__subHeaderTheme.set(m1);
  }

  initialRender() {
    this.observeComponentCreation2((z, a1) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((e1, f1) => {
            Row.create();
            Row.focusable(true);
            Row.width(SINGLE_ICON_ZONE_SIZE);
            Row.height(SINGLE_ICON_ZONE_SIZE);
            Row.margin({
              bottom: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.padding_level2'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              },
            });
            Row.justifyContent(FlexAlign.Center);
            Row.borderRadius({
              "id": -1,
              "type": 10002,
              params: ['sys.float.corner_radius_level4'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            });
            Row.backgroundColor(ObservedObject.GetRawObject(this.bgColor));
            ViewStackProcessor.visualState("normal");
            Row.border({ width: 0 });
            Row.backgroundColor({
              "id": -1,
              "type": 10001,
              params: ['sys.color.ohos_id_color_sub_background_transparent'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            });
            ViewStackProcessor.visualState("focused");
            Row.border({
              radius: {
                "id": -1,
                "type": 10002,
                params: ['sys.float.corner_radius_level4'],
                "bundleName": "__harDefaultBundleName__",
                "moduleName": "__harDefaultModuleName__"
              },
              width: BORDER_WIDTH,
              color: this.subHeaderTheme.borderFocusColor,
              style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState("pressed");
            Row.backgroundColor({
              "id": -1,
              "type": 10001,
              params: ['sys.color.interactive_pressed'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            });
            ViewStackProcessor.visualState("disabled");
            Row.opacity({
              "id": -1,
              "type": 10002,
              params: ['sys.float.interactive_disable'],
              "bundleName": "__harDefaultBundleName__",
              "moduleName": "__harDefaultModuleName__"
            });
            ViewStackProcessor.visualState();
            Row.onTouch((l1) => {
              if (l1.type === TouchType.Down) {
                this.bgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.interactive_pressed'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
              if (l1.type === TouchType.Up) {
                this.bgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
            });
            Row.onHover((k1) => {
              if (k1) {
                this.bgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.interactive_hover'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
              else {
                this.bgColor = {
                  "id": -1,
                  "type": 10001,
                  params: ['sys.color.ohos_id_color_sub_background_transparent'],
                  "bundleName": "__harDefaultBundleName__",
                  "moduleName": "__harDefaultModuleName__"
                };
              }
            });
            Row.onClick((j1) => {
              if (this.item?.action) {
                this.item?.action();
              }
            });
          }, Row);
          this.IconZone.bind(this)(this);
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
  }

  IconZone(h = null) {
    this.observeComponentCreation2((j, k) => {
      If.create();
      if (this.item && this.item.iconOptions) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((o, p) => {
            If.create();
            if (Util.isSymbolResource(this.item.iconOptions.icon)) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((w, x) => {
                  SymbolGlyph.create(this.item.iconOptions?.icon);
                  SymbolGlyph.focusable(true);
                  SymbolGlyph.fontSize(this.item.iconOptions?.symbolicIconOption?.fontSize ?? RIGHT_SINGLE_ICON_SIZE);
                  SymbolGlyph.fontColor(this.item.iconOptions?.symbolicIconOption?.fontColor ?? [this.subHeaderTheme.rightIconColor]);
                  SymbolGlyph.fontWeight(this.item.iconOptions?.symbolicIconOption?.fontWeight);
                  SymbolGlyph.renderingStrategy(this.item.iconOptions?.symbolicIconOption?.renderingStrategy);
                  SymbolGlyph.effectStrategy(this.item.iconOptions?.symbolicIconOption?.effectStrategy);
                }, SymbolGlyph);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.observeComponentCreation2((s, t) => {
                  Image.create(this.item?.iconOptions?.icon);
                  Image.fillColor(this.subHeaderTheme.rightIconColor);
                  Image.width(RIGHT_SINGLE_ICON_SIZE);
                  Image.height(RIGHT_SINGLE_ICON_SIZE);
                  Image.focusable(true);
                  Image.draggable(false);
                }, Image);
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

  rerender() {
    this.updateDirtyElements();
  }
}

class Util {
  static isSymbolResource(f) {
    if (!Util.isResourceType(f)) {
      return false;
    }
    let g = f;
    return g.type === RESOURCE_TYPE_SYMBOL;
  }

  static isResourceType(e) {
    if (!e) {
      return false;
    }
    if (typeof e === 'string' || typeof e === 'undefined') {
      return false;
    }
    return true;
  }

  static getNumberByResource(a) {
    try {
      return resourceManager.getSystemResourceManager().getNumberByName(a);
    }
    catch (b) {
      let c = b.code;
      let d = b.message;
      hilog.error(0x3900, 'Ace', `SubHeader getNumberByResource error, code: ${c}, message: ${d}`);
      return Util.DEFAULT_VALUE;
    }
  }
}

_a = Util;
Util.DEFAULT_VALUE = 0;
Util.DEFAULT_BREAKPOINT_S = 600;
Util.DEFAULT_BREAKPOINT_M = 840;
Util.CALCULATE_BREAKPOINT_S = _a.getNumberByResource('breakpoint_horizontal_s');
Util.CALCULATE_BREAKPOINT_M = _a.getNumberByResource('breakpoint_horizontal_m');
Util.BREAKPOINT_S = _a.CALCULATE_BREAKPOINT_S === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_S : _a.CALCULATE_BREAKPOINT_S;
Util.BREAKPOINT_M = _a.CALCULATE_BREAKPOINT_M === _a.DEFAULT_VALUE ? _a.DEFAULT_BREAKPOINT_M : _a.CALCULATE_BREAKPOINT_M;

export default { OperationType, SubHeader };