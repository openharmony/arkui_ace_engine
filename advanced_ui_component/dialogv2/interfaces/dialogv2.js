/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

var __decorate = (this && this.__decorate) || function (o29, p29, q29, r29) {
  var s29 = arguments.length, t29 = s29 < 3 ? p29 : r29 === null ? r29 = Object.getOwnPropertyDescriptor(p29, q29) : r29, u29;
  if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
    t29 = Reflect.decorate(o29, p29, q29, r29);
  else
    for (var v29 = o29.length - 1; v29 >= 0; v29--)
      if (u29 = o29[v29])
        t29 = (s29 < 3 ? u29(t29) : s29 > 3 ? u29(p29, q29, t29) : u29(p29, q29)) || t29;
  return s29 > 3 && t29 && Object.defineProperty(p29, q29, t29), t29;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const display = requireNapi('display');
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
const accessibility = requireNapi('accessibility');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const i18n = requireNapi('i18n');
const TITLE_MAX_LINES = 2;
const HORIZON_BUTTON_MAX_COUNT = 2;
const VERTICAL_BUTTON_MAX_COUNT = 4;
const BUTTON_LAYOUT_WEIGHT = 1;
const CHECKBOX_CONTAINER_HEIGHT = 48;
const CONTENT_MAX_LINES = 2;
const LOADING_PROGRESS_WIDTH = 40;
const LOADING_PROGRESS_HEIGHT = 40;
const LOADING_MAX_LINES = 10;
const LOADING_MAX_LINES_BIG_FONT = 4;
const LOADING_TEXT_LAYOUT_WEIGHT = 1;
const LOADING_TEXT_MARGIN_LEFT = 12;
const LOADING_MIN_HEIGHT = 48;
const LIST_MIN_HEIGHT = 48;
const CHECKBOX_CONTAINER_LENGTH = 20;
const TEXT_MIN_HEIGHT = 48;
const DEFAULT_IMAGE_SIZE = 64;
const MIN_CONTENT_HEIGHT = 100;
const MAX_CONTENT_HEIGHT = 30000;
const KEYCODE_UP = 2012;
const KEYCODE_DOWN = 2013;
const IGNORE_KEY_EVENT_TYPE = 1;
const FIRST_ITEM_INDEX = 0;
const VERSION_TWELVE = 50000012;
const BUTTON_MIN_FONT_SIZE = 9;
const MAX_FONT_SCALE = 2;
const MAX_DIALOG_WIDTH = getNumberByResourceId(125831042, 400);
const BUTTON_HORIZONTAL_MARGIN = getNumberByResourceId(125831054, 16);
const BUTTON_HORIZONTAL_PADDING = getNumberByResourceId(125830927, 16);
const CHECK_BOX_MARGIN_END = getNumberByResourceId(125830923, 8);
const BUTTON_HORIZONTAL_SPACE = getNumberByResourceId(125831051, 8);
const BODY_L = getNumberByResourceId(125830970, 16);
const BODY_M = getNumberByResourceId(125830971, 14);
const BODY_S = getNumberByResourceId(125830972, 12);
const TITLE_S = getNumberByResourceId(125830966, 20);
const SUBTITLE_S = getNumberByResourceId(125830969, 14);
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);
const DIALOG_DIVIDER_SHOW = getNumberByResourceId(125831202, 1, true);
const ALERT_BUTTON_STYLE = getNumberByResourceId(125831085, 2, true);
const ALERT_TITLE_ALIGNMENT = getEnumNumberByResourceId(125831126, 1);
const SCROLL_BAR_OFFSET = 20;
let AdvancedDialogV2Button = class AdvancedDialogV2Button {
  constructor(n29) {
    this.content = '';
    this.content = n29.content;
    this.action = n29.action;
    this.background = n29.background;
    this.fontColor = n29.fontColor;
    this.buttonStyle = n29.buttonStyle;
    this.role = n29.role;
    this.defaultFocus = n29.defaultFocus;
    this.enabled = n29.enabled;
  }
  ;
};
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "content", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "action", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "background", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "fontColor", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "buttonStyle", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "role", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "defaultFocus", void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, "enabled", void 0);
AdvancedDialogV2Button = __decorate([
  ObservedV2
], AdvancedDialogV2Button);
export { AdvancedDialogV2Button };
export class TipsDialogV2 extends ViewV2 {
  constructor(h29, i29, j29, k29 = -1, l29, m29) {
    super(h29, k29, m29);
    this.initParam("imageRes", (i29 && "imageRes" in i29) ? i29.imageRes : undefined);
    this.initParam("imageSize", (i29 && "imageSize" in i29) ? i29.imageSize : { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE });
    this.initParam("imageBorderColor", (i29 && "imageBorderColor" in i29) ? i29.imageBorderColor : undefined);
    this.initParam("imageBorderWidth", (i29 && "imageBorderWidth" in i29) ? i29.imageBorderWidth : undefined);
    this.initParam("title", (i29 && "title" in i29) ? i29.title : null);
    this.initParam("content", (i29 && "content" in i29) ? i29.content : null);
    this.initParam("onCheckedChange", (i29 && "onCheckedChange" in i29) ? i29.onCheckedChange : undefined);
    this.initParam("checkTips", (i29 && "checkTips" in i29) ? i29.checkTips : null);
    this.initParam("checked", (i29 && "checked" in i29) ? i29.checked : false);
    this.checkedInner = false;
    this.initParam("primaryButton", (i29 && "primaryButton" in i29) ? i29.primaryButton : null);
    this.initParam("secondaryButton", (i29 && "secondaryButton" in i29) ? i29.secondaryButton : null);
    this.marginOffset = 0 - PADDING_LEVEL_8;
    this.contentScroller = new Scroller();
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = 160;
    this.imageIndex = 0;
    this.textIndex = 1;
    this.checkBoxIndex = 2;
    this.appMaxFontScale = 3.2;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(g29) {
    this.resetParam("imageRes", (g29 && "imageRes" in g29) ? g29.imageRes : undefined);
    this.resetParam("imageSize", (g29 && "imageSize" in g29) ? g29.imageSize : { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE });
    this.resetParam("imageBorderColor", (g29 && "imageBorderColor" in g29) ? g29.imageBorderColor : undefined);
    this.resetParam("imageBorderWidth", (g29 && "imageBorderWidth" in g29) ? g29.imageBorderWidth : undefined);
    this.resetParam("title", (g29 && "title" in g29) ? g29.title : null);
    this.resetParam("content", (g29 && "content" in g29) ? g29.content : null);
    this.resetParam("onCheckedChange", (g29 && "onCheckedChange" in g29) ? g29.onCheckedChange : undefined);
    this.resetParam("checkTips", (g29 && "checkTips" in g29) ? g29.checkTips : null);
    this.resetParam("checked", (g29 && "checked" in g29) ? g29.checked : false);
    this.checkedInner = false;
    this.resetComputed("buttons");
    this.resetParam("primaryButton", (g29 && "primaryButton" in g29) ? g29.primaryButton : null);
    this.resetParam("secondaryButton", (g29 && "secondaryButton" in g29) ? g29.secondaryButton : null);
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = 160;
    this.resetMonitorsOnReuse();
  }
  checkedChangeMonitor(f29) {
    this.checkedInner = f29.value('checked')?.now;
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let e29 = [];
    if (this.primaryButton) {
      e29.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      e29.push(this.secondaryButton);
    }
    return e29;
  }
  onWillApplyTheme(d29) {
    this.fontColorWithTheme = d29.colors.fontPrimary;
  }
  initialRender() {
    this.observeComponentCreation2((b29, c29) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((v28, w28) => {
        if (w28) {
          let x28 = new CustomDialogContentComponent(this, {
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            minContentHeight: this.minContentHeight,
            $minContentHeight: u1 => { this.minContentHeight = u1; }
          }, undefined, v28, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 180, col: 5 });
          ViewV2.create(x28);
          let y = () => {
            return {
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              minContentHeight: this.minContentHeight
            };
          };
          x28.paramsGenerator_ = y;
        }
        else {
          this.updateStateVarsOfChildByElmtId(v28, {
            buttons: this.buttons,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  contentBuilder(x27 = null) {
    {
      this.observeComponentCreation2((y27, z27) => {
        if (z27) {
          let a28 = new TipsDialogContentLayout(this, {
            title: this.title,
            content: this.content,
            checkTips: this.checkTips,
            minContentHeight: this.minContentHeight,
            dialogBuilder: () => {
              this.observeComponentCreation2((m28, n28) => {
                ForEach.create();
                const x = p28 => {
                  const q28 = p28;
                  this.observeComponentCreation2((r28, s28) => {
                    If.create();
                    if (q28 === this.imageIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.imagePart.bind(this)();
                      });
                    }
                    else if (q28 === this.textIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.observeComponentCreation2((t28, u28) => {
                          Column.create();
                          Column.padding({ top: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                        }, Column);
                        this.textPart.bind(this)();
                        Column.pop();
                      });
                    }
                    else {
                      this.ifElseBranchUpdateFunction(2, () => {
                        this.checkBoxPart.bind(this)();
                      });
                    }
                  }, If);
                  If.pop();
                };
                this.forEachUpdateFunction(m28, [this.imageIndex, this.textIndex, this.checkBoxIndex], x);
              }, ForEach);
              ForEach.pop();
            },
            $minContentHeight: l28 => { this.minContentHeight = l28; }
          }, undefined, y27, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 191, col: 5 });
          ViewV2.create(a28);
          let u = () => {
            return {
              title: this.title,
              content: this.content,
              checkTips: this.checkTips,
              minContentHeight: this.minContentHeight,
              dialogBuilder: () => {
                this.observeComponentCreation2((c28, d28) => {
                  ForEach.create();
                  const v = f28 => {
                    const g28 = f28;
                    this.observeComponentCreation2((h28, i28) => {
                      If.create();
                      if (g28 === this.imageIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.imagePart.bind(this)();
                        });
                      }
                      else if (g28 === this.textIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.observeComponentCreation2((j28, k28) => {
                            Column.create();
                            Column.padding({ top: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
                          }, Column);
                          this.textPart.bind(this)();
                          Column.pop();
                        });
                      }
                      else {
                        this.ifElseBranchUpdateFunction(2, () => {
                          this.checkBoxPart.bind(this)();
                        });
                      }
                    }, If);
                    If.pop();
                  };
                  this.forEachUpdateFunction(c28, [this.imageIndex, this.textIndex, this.checkBoxIndex], v);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          a28.paramsGenerator_ = u;
        }
        else {
          this.updateStateVarsOfChildByElmtId(y27, {
            title: this.title,
            content: this.content,
            checkTips: this.checkTips,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "TipsDialogContentLayout" });
    }
  }
  checkBoxPart(j27 = null) {
    this.observeComponentCreation2((r27, s27) => {
      Row.create();
      Row.accessibilityGroup(true);
      Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.checkedInner));
      Row.accessibilityDescription(this.checkedInner ? { "id": -1, "type": 10003, params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10003, params: ['sys.string.slider_accessibility_unselectedDesc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Row.onClick(() => {
        this.checkedInner = !this.checkedInner;
        try {
          let w27 = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.checkedInner ? getContext().resourceManager.getStringSync(125833934) :
            getContext().resourceManager.getStringSync(125833935)
          });
          accessibility.sendAccessibilityEvent(w27);
        }
        catch (t27) {
          let u27 = t27.code;
          let v27 = t27.message;
          hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${u27}, message: ${v27}`);
        }
      });
      Row.padding({ top: 8, bottom: 8 });
      Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((k27, l27) => {
      If.create();
      if (this.checkTips !== null && this.checkTips !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((o27, p27) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.checkedInner);
            Checkbox.onChange((q27) => {
              this.checkedInner = q27;
              this.onCheckedChange?.(q27);
            });
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
          }, Checkbox);
          Checkbox.pop();
          this.observeComponentCreation2((m27, n27) => {
            Text.create(this.checkTips);
            Text.fontSize(`${BODY_L}fp`);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(this.fontColorWithTheme);
            Text.maxLines(CONTENT_MAX_LINES);
            Text.layoutWeight(1);
            Text.focusable(false);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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
  }
  imagePart(e27 = null) {
    this.observeComponentCreation2((h27, i27) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((f27, g27) => {
      Image.create(this.imageRes);
      Image.objectFit(ImageFit.Contain);
      Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.constraintSize({
        maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE,
        maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE
      });
      Image.outline({
        width: `${lengthMetricsToPX(this.imageBorderWidth)}px`,
        radius: `${lengthMetricsToPX(LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" })) +
        lengthMetricsToPX(this.imageBorderWidth)}px`,
        color: this.imageBorderColor?.color
      });
    }, Image);
    Column.pop();
  }
  textPart(m26 = null) {
    this.observeComponentCreation2((c27, d27) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
    }, Scroll);
    this.observeComponentCreation2((a27, b27) => {
      Column.create();
      Column.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
    }, Column);
    this.observeComponentCreation2((u26, v26) => {
      If.create();
      if (this.title !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y26, z26) => {
            Row.create();
            Row.padding({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          }, Row);
          this.observeComponentCreation2((w26, x26) => {
            Text.create(this.title);
            Text.fontSize(`${TITLE_S}fp`);
            Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
            Text.fontWeight(FontWeight.Bold);
            Text.fontColor(this.fontColorWithTheme);
            Text.textAlign(TextAlign.Center);
            Text.maxLines(CONTENT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
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
    this.observeComponentCreation2((n26, o26) => {
      If.create();
      if (this.content !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((s26, t26) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((p26, q26) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.focusBox({
              strokeWidth: LengthMetrics.px(0)
            });
            Text.fontSize(this.getContentFontSize());
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(this.fontColorWithTheme);
            Text.textAlign(TextAlign.Center);
            Text.width('100%');
            Text.onKeyEvent((r26) => {
              if (r26) {
                resolveKeyEvent(r26, this.contentScroller);
              }
            });
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
    Column.pop();
    Scroll.pop();
  }
  aboutToAppear() {
    let l26 = this.getUIContext();
    this.appMaxFontScale = l26.getMaxFontScale();
    this.checkedInner = this.checked;
  }
  getContentFontSize() {
    return BODY_L + 'fp';
  }
  updateStateVars(k26) {
    if (k26 === undefined) {
      return;
    }
    if ("imageRes" in k26) {
      this.updateParam("imageRes", k26.imageRes);
    }
    if ("imageSize" in k26) {
      this.updateParam("imageSize", k26.imageSize);
    }
    if ("imageBorderColor" in k26) {
      this.updateParam("imageBorderColor", k26.imageBorderColor);
    }
    if ("imageBorderWidth" in k26) {
      this.updateParam("imageBorderWidth", k26.imageBorderWidth);
    }
    if ("title" in k26) {
      this.updateParam("title", k26.title);
    }
    if ("content" in k26) {
      this.updateParam("content", k26.content);
    }
    if ("onCheckedChange" in k26) {
      this.updateParam("onCheckedChange", k26.onCheckedChange);
    }
    if ("checkTips" in k26) {
      this.updateParam("checkTips", k26.checkTips);
    }
    if ("checked" in k26) {
      this.updateParam("checked", k26.checked);
    }
    if ("primaryButton" in k26) {
      this.updateParam("primaryButton", k26.primaryButton);
    }
    if ("secondaryButton" in k26) {
      this.updateParam("secondaryButton", k26.secondaryButton);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], TipsDialogV2.prototype, "imageRes", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "imageSize", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "imageBorderColor", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "imageBorderWidth", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "title", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "content", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "onCheckedChange", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "checkTips", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "checked", void 0);
__decorate([
  Local
], TipsDialogV2.prototype, "checkedInner", void 0);
__decorate([
  Monitor('checked')
], TipsDialogV2.prototype, "checkedChangeMonitor", null);
__decorate([
  Computed
], TipsDialogV2.prototype, "buttons", null);
__decorate([
  Param
], TipsDialogV2.prototype, "primaryButton", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "secondaryButton", void 0);
__decorate([
  Local
], TipsDialogV2.prototype, "fontColorWithTheme", void 0);
__decorate([
  Provider()
], TipsDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], TipsDialogV2.prototype, "minContentHeight", void 0);
class TipsDialogContentLayout extends ViewV2 {
  constructor(e26, f26, g26, h26 = -1, i26, j26) {
    super(e26, h26, j26);
    this.initParam("title", (f26 && "title" in f26) ? f26.title : null);
    this.initParam("content", (f26 && "content" in f26) ? f26.content : null);
    this.initParam("checkTips", (f26 && "checkTips" in f26) ? f26.checkTips : null);
    this.initParam("minContentHeight", (f26 && "minContentHeight" in f26) ? f26.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in f26 ? f26.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in f26 ? f26.dialogBuilder : this.doNothingBuilder;
    this.imageIndex = 0;
    this.textIndex = 1;
    this.checkBoxIndex = 2;
    this.childrenSize = 3;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(d26) {
    this.resetParam("title", (d26 && "title" in d26) ? d26.title : null);
    this.resetParam("content", (d26 && "content" in d26) ? d26.content : null);
    this.resetParam("checkTips", (d26 && "checkTips" in d26) ? d26.checkTips : null);
    this.resetParam("minContentHeight", (d26 && "minContentHeight" in d26) ? d26.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in d26 ? d26.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in d26 ? d26.dialogBuilder : this.doNothingBuilder;
  }
  doNothingBuilder(c26 = null) {
  }
  ;
  onPlaceChildren(v25, w25, x25) {
    let y25 = 0;
    let z25 = 0;
    for (let a26 = 0; a26 < w25.length; a26++) {
      let b26 = w25[a26];
      b26.layout({ x: y25, y: z25 });
      z25 += b26.measureResult.height;
    }
  }
  onMeasureSize(d25, e25, f25) {
    let g25 = { width: Number(f25.maxWidth), height: 0 };
    if (e25.length < this.childrenSize) {
      return g25;
    }
    let h25 = 0;
    let i25 = 0;
    if (this.checkTips !== null && this.checkTips !== undefined) {
      let s25 = e25[this.checkBoxIndex];
      let t25 = {
        maxWidth: f25.maxWidth,
        minHeight: CHECKBOX_CONTAINER_HEIGHT,
        maxHeight: f25.maxHeight
      };
      let u25 = s25.measure(t25);
      i25 = u25.height;
      h25 += i25;
    }
    let j25 = e25[this.imageIndex];
    let k25 = 0;
    if (this.title !== null || this.content !== null) {
      k25 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
    }
    let l25 = Number(f25.maxHeight) - i25 - k25;
    let m25 = {
      maxWidth: f25.maxWidth,
      maxHeight: l25
    };
    let n25 = j25.measure(m25);
    h25 += n25.height;
    if (this.title !== null || this.content !== null) {
      let o25 = e25[this.textIndex];
      let p25 = Number(f25.maxHeight) - n25.height - i25;
      let q25 = {
        maxWidth: f25.maxWidth,
        maxHeight: Math.max(p25, TEXT_MIN_HEIGHT)
      };
      let r25 = o25.measure(q25);
      h25 += r25.height;
    }
    g25.height = h25;
    this.$minContentHeight?.(Math.max(i25 + n25.height + k25, MIN_CONTENT_HEIGHT));
    return g25;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(c25) {
    if (c25 === undefined) {
      return;
    }
    if ("title" in c25) {
      this.updateParam("title", c25.title);
    }
    if ("content" in c25) {
      this.updateParam("content", c25.content);
    }
    if ("checkTips" in c25) {
      this.updateParam("checkTips", c25.checkTips);
    }
    if ("minContentHeight" in c25) {
      this.updateParam("minContentHeight", c25.minContentHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], TipsDialogContentLayout.prototype, "title", void 0);
__decorate([
  Param
], TipsDialogContentLayout.prototype, "content", void 0);
__decorate([
  Param
], TipsDialogContentLayout.prototype, "checkTips", void 0);
__decorate([
  Param
], TipsDialogContentLayout.prototype, "minContentHeight", void 0);
__decorate([
  Event
], TipsDialogContentLayout.prototype, "$minContentHeight", void 0);
export class SelectDialogV2 extends ViewV2 {
  constructor(w24, x24, y24, z24 = -1, a25, b25) {
    super(w24, z24, b25);
    this.initParam("title", (x24 && "title" in x24) ? x24.title : '');
    this.initParam("content", (x24 && "content" in x24) ? x24.content : '');
    this.initParam("confirm", (x24 && "confirm" in x24) ? x24.confirm : null);
    this.initParam("radioContent", (x24 && "radioContent" in x24) ? x24.radioContent : []);
    this.initParam("selectedIndex", (x24 && "selectedIndex" in x24) ? x24.selectedIndex : -1);
    this.selectedIndexInner = -1;
    this.isFocus = false;
    this.currentFocusIndex = -1;
    this.radioHeight = 0;
    this.itemHeight = 0;
    this.contentBuilder = "contentBuilder" in x24 ? x24.contentBuilder : this.buildContent;
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.dividerColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.contentScroller = new Scroller();
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(v24) {
    this.resetParam("title", (v24 && "title" in v24) ? v24.title : '');
    this.resetParam("content", (v24 && "content" in v24) ? v24.content : '');
    this.resetParam("confirm", (v24 && "confirm" in v24) ? v24.confirm : null);
    this.resetParam("radioContent", (v24 && "radioContent" in v24) ? v24.radioContent : []);
    this.resetParam("selectedIndex", (v24 && "selectedIndex" in v24) ? v24.selectedIndex : -1);
    this.selectedIndexInner = -1;
    this.isFocus = false;
    this.currentFocusIndex = -1;
    this.radioHeight = 0;
    this.itemHeight = 0;
    this.contentBuilder = "contentBuilder" in v24 ? v24.contentBuilder : this.buildContent;
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.dividerColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.resetComputed("buttons");
    this.resetComputed("contentPadding");
    this.resetMonitorsOnReuse();
  }
  selectedIndexMonitor(u24) {
    this.selectedIndexInner = u24.value('selectedIndex')?.now;
  }
  get buttons() {
    let t24 = [];
    if (this.confirm) {
      t24.push(this.confirm);
    }
    return t24;
  }
  get contentPadding() {
    if (!this.title && !this.confirm) {
      return {
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
      };
    }
    if (!this.title) {
      return {
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
      };
    }
    else if (!this.confirm) {
      return {
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
      };
    }
    return {
      left: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      right: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    };
  }
  buildContent(w22 = null) {
    this.observeComponentCreation2((o24, p24) => {
      Scroll.create(this.contentScroller);
      Scroll.scrollBar(BarState.Auto);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.onDidScroll((q24, r24) => {
        let s24 = (this.itemHeight - this.radioHeight) / 2;
        if (this.isFocus) {
          if (this.currentFocusIndex === this.radioContent.length - 1) {
            this.contentScroller.scrollEdge(Edge.Bottom);
            this.currentFocusIndex = -1;
          }
          else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
            this.contentScroller.scrollEdge(Edge.Top);
            this.currentFocusIndex = -1;
          }
          else {
            if (r24 > 0) {
              this.contentScroller.scrollBy(0, s24);
            }
            else if (r24 < 0) {
              this.contentScroller.scrollBy(0, 0 - s24);
            }
          }
          this.isFocus = false;
        }
      });
    }, Scroll);
    this.observeComponentCreation2((m24, n24) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((g24, h24) => {
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((k24, l24) => {
            Row.create();
            Row.padding({
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            Row.width('100%');
          }, Row);
          this.observeComponentCreation2((i24, j24) => {
            Text.create(this.content);
            Text.fontSize(`${BODY_M}fp`);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(this.fontColorWithTheme);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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
    this.observeComponentCreation2((e24, f24) => {
      List.create();
      List.width('100%');
      List.clip(false);
      List.onFocus(() => {
        if (!this.contentScroller.isAtEnd()) {
          this.contentScroller.scrollEdge(Edge.Top);
          focusControl.requestFocus(String(FIRST_ITEM_INDEX));
        }
      });
      List.defaultFocus(this.buttons?.length === 0 ? true : false);
    }, List);
    this.observeComponentCreation2((x22, y22) => {
      ForEach.create();
      const q = (a23, b23) => {
        const c23 = a23;
        {
          const r = (c24, d24) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c24);
            s(c24, d24);
            if (!d24) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const s = (y23, z23) => {
            ListItem.create(t, true);
            ListItem.padding({
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            ListItem.onSizeChange((a24, b24) => {
              this.itemHeight = Number(b24.height);
            });
          };
          const t = (g23, h23) => {
            r(g23, h23);
            this.observeComponentCreation2((w23, x23) => {
              Column.create();
              Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
              Column.focusBox({
                margin: { value: -2, unit: LengthUnit.VP }
              });
              Column.accessibilityText(getAccessibilityText(c23.title, this.selectedIndexInner === b23));
              Column.onClick(() => {
                this.selectedIndexInner = b23;
                c23.action && c23.action();
                this.getDialogController()?.close();
              });
            }, Column);
            this.observeComponentCreation2((u23, v23) => {
              Button.createWithChild();
              Button.type(ButtonType.Normal);
              Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
              Button.buttonStyle(ButtonStyleMode.TEXTUAL);
              Button.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
              });
            }, Button);
            this.observeComponentCreation2((s23, t23) => {
              Row.create();
              Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
              Row.clip(false);
              Row.padding({ top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            }, Row);
            this.observeComponentCreation2((q23, r23) => {
              Text.create(c23.title);
              Text.fontSize(`${BODY_L}fp`);
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor(this.fontColorWithTheme);
              Text.layoutWeight(1);
              Text.direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr);
            }, Text);
            Text.pop();
            this.observeComponentCreation2((m23, n23) => {
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
              Radio.checked(this.selectedIndexInner === b23);
              Radio.hitTestBehavior(HitTestMode.None);
              Radio.id(String(b23));
              Radio.focusable(false);
              Radio.accessibilityLevel('no');
              Radio.visibility(this.selectedIndex === b23 ? Visibility.Visible : Visibility.Hidden);
              Radio.radioStyle({ uncheckedBorderColor: Color.Transparent });
              Radio.onFocus(() => {
                this.isFocus = true;
                this.currentFocusIndex = b23;
                if (b23 === FIRST_ITEM_INDEX) {
                  this.contentScroller.scrollEdge(Edge.Top);
                }
                else if (b23 === this.radioContent.length - 1) {
                  this.contentScroller.scrollEdge(Edge.Bottom);
                }
              });
              Radio.onSizeChange((o23, p23) => {
                this.radioHeight = Number(p23.height);
              });
            }, Radio);
            Row.pop();
            Button.pop();
            this.observeComponentCreation2((i23, j23) => {
              If.create();
              if (b23 < this.radioContent.length - 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((k23, l23) => {
                    Divider.create();
                    Divider.color(this.dividerColorWithTheme);
                    Divider.padding({
                      left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                      right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
                    });
                  }, Divider);
                });
              }
              else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
              }
            }, If);
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          this.observeComponentCreation2(s, ListItem);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(x22, this.radioContent, q, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    List.pop();
    Column.pop();
    Scroll.pop();
  }
  initialRender() {
    this.observeComponentCreation2((u22, v22) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((o22, p22) => {
        if (p22) {
          let q22 = new CustomDialogContentComponent(this, {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            minContentHeight: this.minContentHeight,
            $minContentHeight: k1 => { this.minContentHeight = k1; }
          }, undefined, o22, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 593, col: 5 });
          ViewV2.create(q22);
          let p = () => {
            return {
              primaryTitle: this.title,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              contentAreaPadding: this.contentPadding,
              minContentHeight: this.minContentHeight
            };
          };
          q22.paramsGenerator_ = p;
        }
        else {
          this.updateStateVarsOfChildByElmtId(o22, {
            primaryTitle: this.title,
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  onWillApplyTheme(n22) {
    this.fontColorWithTheme = n22.colors.fontPrimary;
    this.dividerColorWithTheme = n22.colors.compDivider;
  }
  aboutToAppear() {
    this.selectedIndexInner = this.selectedIndex;
  }
  updateStateVars(m22) {
    if (m22 === undefined) {
      return;
    }
    if ("title" in m22) {
      this.updateParam("title", m22.title);
    }
    if ("content" in m22) {
      this.updateParam("content", m22.content);
    }
    if ("confirm" in m22) {
      this.updateParam("confirm", m22.confirm);
    }
    if ("radioContent" in m22) {
      this.updateParam("radioContent", m22.radioContent);
    }
    if ("selectedIndex" in m22) {
      this.updateParam("selectedIndex", m22.selectedIndex);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], SelectDialogV2.prototype, "title", void 0);
__decorate([
  Param
], SelectDialogV2.prototype, "content", void 0);
__decorate([
  Param
], SelectDialogV2.prototype, "confirm", void 0);
__decorate([
  Param
], SelectDialogV2.prototype, "radioContent", void 0);
__decorate([
  Param
], SelectDialogV2.prototype, "selectedIndex", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "selectedIndexInner", void 0);
__decorate([
  Monitor('selectedIndex')
], SelectDialogV2.prototype, "selectedIndexMonitor", null);
__decorate([
  Local
], SelectDialogV2.prototype, "isFocus", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "currentFocusIndex", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "radioHeight", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "itemHeight", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "fontColorWithTheme", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "dividerColorWithTheme", void 0);
__decorate([
  Provider()
], SelectDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], SelectDialogV2.prototype, "minContentHeight", void 0);
__decorate([
  Computed
], SelectDialogV2.prototype, "buttons", null);
__decorate([
  Computed
], SelectDialogV2.prototype, "contentPadding", null);
class ConfirmDialogContentLayout extends ViewV2 {
  constructor(g22, h22, i22, j22 = -1, k22, l22) {
    super(g22, j22, l22);
    this.textIndex = 0;
    this.checkboxIndex = 1;
    this.initParam("minContentHeight", (h22 && "minContentHeight" in h22) ? h22.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in h22 ? h22.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in h22 ? h22.dialogBuilder : this.doNothingBuilder;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(f22) {
    this.resetParam("minContentHeight", (f22 && "minContentHeight" in f22) ? f22.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in f22 ? f22.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in f22 ? f22.dialogBuilder : this.doNothingBuilder;
  }
  doNothingBuilder(e22 = null) {
  }
  ;
  onPlaceChildren(x21, y21, z21) {
    let a22 = 0;
    let b22 = 0;
    for (let c22 = 0; c22 < y21.length; c22++) {
      let d22 = y21[c22];
      d22.layout({ x: a22, y: b22 });
      b22 += d22.measureResult.height;
    }
  }
  onMeasureSize(l21, m21, n21) {
    let o21 = { width: Number(n21.maxWidth), height: 0 };
    let p21 = 2;
    if (m21.length < p21) {
      return o21;
    }
    let q21 = 0;
    let r21 = m21[this.checkboxIndex];
    let s21 = {
      maxWidth: n21.maxWidth,
      minHeight: CHECKBOX_CONTAINER_HEIGHT,
      maxHeight: n21.maxHeight
    };
    let t21 = r21.measure(s21);
    q21 += t21.height;
    let u21 = m21[this.textIndex];
    let v21 = {
      maxWidth: n21.maxWidth,
      maxHeight: Number(n21.maxHeight) - q21
    };
    let w21 = u21.measure(v21);
    q21 += w21.height;
    o21.height = q21;
    this.$minContentHeight?.(Math.max(t21.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT));
    return o21;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(k21) {
    if (k21 === undefined) {
      return;
    }
    if ("minContentHeight" in k21) {
      this.updateParam("minContentHeight", k21.minContentHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ConfirmDialogContentLayout.prototype, "minContentHeight", void 0);
__decorate([
  Event
], ConfirmDialogContentLayout.prototype, "$minContentHeight", void 0);
export class ConfirmDialogV2 extends ViewV2 {
  constructor(e21, f21, g21, h21 = -1, i21, j21) {
    super(e21, h21, j21);
    this.initParam("title", (f21 && "title" in f21) ? f21.title : '');
    this.initParam("content", (f21 && "content" in f21) ? f21.content : '');
    this.initParam("checkTips", (f21 && "checkTips" in f21) ? f21.checkTips : '');
    this.initParam("checked", (f21 && "checked" in f21) ? f21.checked : false);
    this.checkedInner = this.checked;
    this.initParam("primaryButton", (f21 && "primaryButton" in f21) ? f21.primaryButton : new AdvancedDialogV2Button({ content: '' }));
    this.initParam("secondaryButton", (f21 && "secondaryButton" in f21) ? f21.secondaryButton : new AdvancedDialogV2Button({ content: '' }));
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.initParam("onCheckedChange", (f21 && "onCheckedChange" in f21) ? f21.onCheckedChange : undefined);
    this.contentScroller = new Scroller();
    this.marginOffset = 0 - PADDING_LEVEL_8;
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.textIndex = 0;
    this.checkboxIndex = 1;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(d21) {
    this.resetParam("title", (d21 && "title" in d21) ? d21.title : '');
    this.resetParam("content", (d21 && "content" in d21) ? d21.content : '');
    this.resetParam("checkTips", (d21 && "checkTips" in d21) ? d21.checkTips : '');
    this.resetParam("checked", (d21 && "checked" in d21) ? d21.checked : false);
    this.checkedInner = this.checked;
    this.resetParam("primaryButton", (d21 && "primaryButton" in d21) ? d21.primaryButton : new AdvancedDialogV2Button({ content: '' }));
    this.resetParam("secondaryButton", (d21 && "secondaryButton" in d21) ? d21.secondaryButton : new AdvancedDialogV2Button({ content: '' }));
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.resetParam("onCheckedChange", (d21 && "onCheckedChange" in d21) ? d21.onCheckedChange : undefined);
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.resetComputed("buttons");
    this.resetMonitorsOnReuse();
  }
  checkedMonitor(c21) {
    this.checkedInner = c21.value('checked')?.now;
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let b21 = [];
    if (this.primaryButton) {
      b21.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      b21.push(this.secondaryButton);
    }
    return b21;
  }
  textBuilder(r20 = null) {
    this.observeComponentCreation2((z20, a21) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((x20, y20) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
    }, Scroll);
    this.observeComponentCreation2((v20, w20) => {
      Column.create();
      Column.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
    }, Column);
    this.observeComponentCreation2((s20, t20) => {
      Text.create(this.content);
      Text.focusable(true);
      Text.defaultFocus(!(this.primaryButton?.content || this.secondaryButton?.content));
      Text.focusBox({
        strokeWidth: LengthMetrics.px(0)
      });
      Text.fontSize(`${BODY_L}fp`);
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor(this.fontColorWithTheme);
      Text.textAlign(TextAlign.Center);
      Text.onKeyEvent((u20) => {
        if (u20) {
          resolveKeyEvent(u20, this.contentScroller);
        }
      });
      Text.width('100%');
    }, Text);
    Text.pop();
    Column.pop();
    Scroll.pop();
    Column.pop();
  }
  checkBoxBuilder(f20 = null) {
    this.observeComponentCreation2((l20, m20) => {
      Row.create();
      Row.accessibilityGroup(true);
      Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.checkedInner));
      Row.accessibilityDescription(this.checkedInner ? { "id": -1, "type": 10003, params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10003, params: ['sys.string.slider_accessibility_unselectedDesc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Row.onClick(() => {
        this.checkedInner = !this.checkedInner;
        try {
          let q20 = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.checkedInner ? getContext().resourceManager.getStringSync(125833934) :
            getContext().resourceManager.getStringSync(125833935)
          });
          accessibility.sendAccessibilityEvent(q20);
        }
        catch (n20) {
          let o20 = n20.code;
          let p20 = n20.message;
          hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${o20}, message: ${p20}`);
        }
      });
      Row.width('100%');
      Row.padding({ top: 8, bottom: 8 });
    }, Row);
    this.observeComponentCreation2((i20, j20) => {
      Checkbox.create({ name: '', group: 'checkboxGroup' });
      Checkbox.select(this.checkedInner);
      Checkbox.onChange((k20) => {
        this.checkedInner = k20;
        if (this.onCheckedChange) {
          this.onCheckedChange(this.checkedInner);
        }
      });
      Checkbox.hitTestBehavior(HitTestMode.Block);
      Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
    }, Checkbox);
    Checkbox.pop();
    this.observeComponentCreation2((g20, h20) => {
      Text.create(this.checkTips);
      Text.fontSize(`${BODY_M}fp`);
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor(this.fontColorWithTheme);
      Text.maxLines(CONTENT_MAX_LINES);
      Text.focusable(false);
      Text.layoutWeight(1);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    }, Text);
    Text.pop();
    Row.pop();
  }
  buildContent(l19 = null) {
    {
      this.observeComponentCreation2((m19, n19) => {
        if (n19) {
          let o19 = new ConfirmDialogContentLayout(this, {
            minContentHeight: this.minContentHeight,
            dialogBuilder: () => {
              this.observeComponentCreation2((y19, z19) => {
                ForEach.create();
                const o = b20 => {
                  const c20 = b20;
                  this.observeComponentCreation2((d20, e20) => {
                    If.create();
                    if (c20 === this.textIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.textBuilder.bind(this)();
                      });
                    }
                    else if (c20 === this.checkboxIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.checkBoxBuilder.bind(this)();
                      });
                    }
                    else {
                      this.ifElseBranchUpdateFunction(2, () => {
                      });
                    }
                  }, If);
                  If.pop();
                };
                this.forEachUpdateFunction(y19, [this.textIndex, this.checkboxIndex], o);
              }, ForEach);
              ForEach.pop();
            },
            $minContentHeight: x19 => { this.minContentHeight = x19; }
          }, undefined, m19, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 790, col: 5 });
          ViewV2.create(o19);
          let m = () => {
            return {
              minContentHeight: this.minContentHeight,
              dialogBuilder: () => {
                this.observeComponentCreation2((q19, r19) => {
                  ForEach.create();
                  const n = t19 => {
                    const u19 = t19;
                    this.observeComponentCreation2((v19, w19) => {
                      If.create();
                      if (u19 === this.textIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.textBuilder.bind(this)();
                        });
                      }
                      else if (u19 === this.checkboxIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.checkBoxBuilder.bind(this)();
                        });
                      }
                      else {
                        this.ifElseBranchUpdateFunction(2, () => {
                        });
                      }
                    }, If);
                    If.pop();
                  };
                  this.forEachUpdateFunction(q19, [this.textIndex, this.checkboxIndex], n);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          o19.paramsGenerator_ = m;
        }
        else {
          this.updateStateVarsOfChildByElmtId(m19, {
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "ConfirmDialogContentLayout" });
    }
  }
  initialRender() {
    this.observeComponentCreation2((j19, k19) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((d19, e19) => {
        if (e19) {
          let f19 = new CustomDialogContentComponent(this, {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.buildContent();
            },
            minContentHeight: this.minContentHeight,
            buttons: this.buttons,
            $minContentHeight: d1 => { this.minContentHeight = d1; }
          }, undefined, d19, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 802, col: 5 });
          ViewV2.create(f19);
          let l = () => {
            return {
              primaryTitle: this.title,
              contentBuilder: () => {
                this.buildContent();
              },
              minContentHeight: this.minContentHeight,
              buttons: this.buttons
            };
          };
          f19.paramsGenerator_ = l;
        }
        else {
          this.updateStateVarsOfChildByElmtId(d19, {
            primaryTitle: this.title,
            minContentHeight: this.minContentHeight,
            buttons: this.buttons
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  onWillApplyTheme(c19) {
    this.fontColorWithTheme = c19.colors.fontPrimary;
  }
  updateStateVars(b19) {
    if (b19 === undefined) {
      return;
    }
    if ("title" in b19) {
      this.updateParam("title", b19.title);
    }
    if ("content" in b19) {
      this.updateParam("content", b19.content);
    }
    if ("checkTips" in b19) {
      this.updateParam("checkTips", b19.checkTips);
    }
    if ("checked" in b19) {
      this.updateParam("checked", b19.checked);
    }
    if ("primaryButton" in b19) {
      this.updateParam("primaryButton", b19.primaryButton);
    }
    if ("secondaryButton" in b19) {
      this.updateParam("secondaryButton", b19.secondaryButton);
    }
    if ("onCheckedChange" in b19) {
      this.updateParam("onCheckedChange", b19.onCheckedChange);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ConfirmDialogV2.prototype, "title", void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, "content", void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, "checkTips", void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, "checked", void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, "checkedInner", void 0);
__decorate([
  Monitor('checked')
], ConfirmDialogV2.prototype, "checkedMonitor", null);
__decorate([
  Param
], ConfirmDialogV2.prototype, "primaryButton", void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, "secondaryButton", void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, "fontColorWithTheme", void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, "onCheckedChange", void 0);
__decorate([
  Provider()
], ConfirmDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, "minContentHeight", void 0);
__decorate([
  Computed
], ConfirmDialogV2.prototype, "buttons", null);
export class AlertDialogV2 extends ViewV2 {
  constructor(v18, w18, x18, y18 = -1, z18, a19) {
    super(v18, y18, a19);
    this.initParam("primaryTitle", (w18 && "primaryTitle" in w18) ? w18.primaryTitle : undefined);
    this.initParam("secondaryTitle", (w18 && "secondaryTitle" in w18) ? w18.secondaryTitle : undefined);
    this.initParam("content", (w18 && "content" in w18) ? w18.content : '');
    this.initParam("primaryButton", (w18 && "primaryButton" in w18) ? w18.primaryButton : null);
    this.initParam("secondaryButton", (w18 && "secondaryButton" in w18) ? w18.secondaryButton : null);
    this.textAlign = TextAlign.Center;
    this.contentScroller = new Scroller();
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(u18) {
    this.resetParam("primaryTitle", (u18 && "primaryTitle" in u18) ? u18.primaryTitle : undefined);
    this.resetParam("secondaryTitle", (u18 && "secondaryTitle" in u18) ? u18.secondaryTitle : undefined);
    this.resetParam("content", (u18 && "content" in u18) ? u18.content : '');
    this.resetParam("primaryButton", (u18 && "primaryButton" in u18) ? u18.primaryButton : null);
    this.resetParam("secondaryButton", (u18 && "secondaryButton" in u18) ? u18.secondaryButton : null);
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.resetComputed("buttons");
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let t18 = [];
    if (this.primaryButton) {
      t18.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      t18.push(this.secondaryButton);
    }
    return t18;
  }
  initialRender() {
    this.observeComponentCreation2((r18, s18) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((l18, m18) => {
        if (m18) {
          let n18 = new CustomDialogContentComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
            minContentHeight: this.minContentHeight,
            $minContentHeight: a1 => { this.minContentHeight = a1; }
          }, undefined, l18, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 847, col: 5 });
          ViewV2.create(n18);
          let k = () => {
            return {
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.AlertDialogContentBuilder();
              },
              buttons: this.buttons,
              minContentHeight: this.minContentHeight
            };
          };
          n18.paramsGenerator_ = k;
        }
        else {
          this.updateStateVarsOfChildByElmtId(l18, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            buttons: this.buttons,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  AlertDialogContentBuilder(d18 = null) {
    this.observeComponentCreation2((j18, k18) => {
      Column.create();
      Column.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
    }, Column);
    this.observeComponentCreation2((h18, i18) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.width('100%');
    }, Scroll);
    this.observeComponentCreation2((e18, f18) => {
      Text.create(this.content);
      Text.focusable(true);
      Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
      Text.focusBox({
        strokeWidth: LengthMetrics.px(0)
      });
      Text.fontSize(`${BODY_L}fp`);
      Text.fontWeight(this.getFontWeight());
      Text.fontColor(this.fontColorWithTheme);
      Text.margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) });
      Text.width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`);
      Text.textAlign(this.textAlign);
      Text.onKeyEvent((g18) => {
        if (g18) {
          resolveKeyEvent(g18, this.contentScroller);
        }
      });
    }, Text);
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  onWillApplyTheme(c18) {
    this.fontColorWithTheme = c18.colors.fontPrimary;
  }
  getFontWeight() {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return FontWeight.Medium;
  }
  updateStateVars(b18) {
    if (b18 === undefined) {
      return;
    }
    if ("primaryTitle" in b18) {
      this.updateParam("primaryTitle", b18.primaryTitle);
    }
    if ("secondaryTitle" in b18) {
      this.updateParam("secondaryTitle", b18.secondaryTitle);
    }
    if ("content" in b18) {
      this.updateParam("content", b18.content);
    }
    if ("primaryButton" in b18) {
      this.updateParam("primaryButton", b18.primaryButton);
    }
    if ("secondaryButton" in b18) {
      this.updateParam("secondaryButton", b18.secondaryButton);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], AlertDialogV2.prototype, "primaryTitle", void 0);
__decorate([
  Param
], AlertDialogV2.prototype, "secondaryTitle", void 0);
__decorate([
  Param
], AlertDialogV2.prototype, "content", void 0);
__decorate([
  Param
], AlertDialogV2.prototype, "primaryButton", void 0);
__decorate([
  Param
], AlertDialogV2.prototype, "secondaryButton", void 0);
__decorate([
  Local
], AlertDialogV2.prototype, "fontColorWithTheme", void 0);
__decorate([
  Provider()
], AlertDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], AlertDialogV2.prototype, "minContentHeight", void 0);
__decorate([
  Computed
], AlertDialogV2.prototype, "buttons", null);
export class CustomContentDialogV2 extends ViewV2 {
  constructor(v17, w17, x17, y17 = -1, z17, a18) {
    super(v17, y17, a18);
    this.initParam("primaryTitle", (w17 && "primaryTitle" in w17) ? w17.primaryTitle : undefined);
    this.initParam("secondaryTitle", (w17 && "secondaryTitle" in w17) ? w17.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in w17 ? w17.contentBuilder : undefined;
    this.initParam("contentAreaPadding", (w17 && "contentAreaPadding" in w17) ? w17.contentAreaPadding : undefined);
    this.initParam("buttons", (w17 && "buttons" in w17) ? w17.buttons : undefined);
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(u17) {
    this.resetParam("primaryTitle", (u17 && "primaryTitle" in u17) ? u17.primaryTitle : undefined);
    this.resetParam("secondaryTitle", (u17 && "secondaryTitle" in u17) ? u17.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in u17 ? u17.contentBuilder : undefined;
    this.resetParam("contentAreaPadding", (u17 && "contentAreaPadding" in u17) ? u17.contentAreaPadding : undefined);
    this.resetParam("buttons", (u17 && "buttons" in u17) ? u17.buttons : undefined);
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
  }
  initialRender() {
    this.observeComponentCreation2((s17, t17) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((m17, n17) => {
        if (n17) {
          let o17 = new CustomDialogContentComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              if (typeof this.contentBuilder === 'function') {
                this.contentBuilder();
              }
            },
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
            minContentHeight: this.minContentHeight,
            $minContentHeight: w => { this.minContentHeight = w; }
          }, undefined, m17, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 909, col: 5 });
          ViewV2.create(o17);
          let j = () => {
            return {
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                if (typeof this.contentBuilder === 'function') {
                  this.contentBuilder();
                }
              },
              contentAreaPadding: this.contentAreaPadding,
              buttons: this.buttons,
              minContentHeight: this.minContentHeight
            };
          };
          o17.paramsGenerator_ = j;
        }
        else {
          this.updateStateVarsOfChildByElmtId(m17, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  updateStateVars(l17) {
    if (l17 === undefined) {
      return;
    }
    if ("primaryTitle" in l17) {
      this.updateParam("primaryTitle", l17.primaryTitle);
    }
    if ("secondaryTitle" in l17) {
      this.updateParam("secondaryTitle", l17.secondaryTitle);
    }
    if ("contentAreaPadding" in l17) {
      this.updateParam("contentAreaPadding", l17.contentAreaPadding);
    }
    if ("buttons" in l17) {
      this.updateParam("buttons", l17.buttons);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], CustomContentDialogV2.prototype, "primaryTitle", void 0);
__decorate([
  Param
], CustomContentDialogV2.prototype, "secondaryTitle", void 0);
__decorate([
  Param
], CustomContentDialogV2.prototype, "contentAreaPadding", void 0);
__decorate([
  Param
], CustomContentDialogV2.prototype, "buttons", void 0);
__decorate([
  Provider()
], CustomContentDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], CustomContentDialogV2.prototype, "minContentHeight", void 0);
class CustomDialogLayout extends ViewV2 {
  constructor(f17, g17, h17, i17 = -1, j17, k17) {
    super(f17, i17, k17);
    this.initParam("titleHeight", (g17 && "titleHeight" in g17) ? g17.titleHeight : 0);
    this.$titleHeight = "$titleHeight" in g17 ? g17.$titleHeight : undefined;
    this.initParam("buttonHeight", (g17 && "buttonHeight" in g17) ? g17.buttonHeight : 0);
    this.$buttonHeight = "$buttonHeight" in g17 ? g17.$buttonHeight : undefined;
    this.initParam("titleMinHeight", (g17 && "titleMinHeight" in g17) ? g17.titleMinHeight : 0);
    this.dialogBuilder = "dialogBuilder" in g17 ? g17.dialogBuilder : this.doNothingBuilder;
    this.titleIndex = 0;
    this.contentIndex = 1;
    this.buttonIndex = 2;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(e17) {
    this.resetParam("titleHeight", (e17 && "titleHeight" in e17) ? e17.titleHeight : 0);
    this.$titleHeight = "$titleHeight" in e17 ? e17.$titleHeight : undefined;
    this.resetParam("buttonHeight", (e17 && "buttonHeight" in e17) ? e17.buttonHeight : 0);
    this.$buttonHeight = "$buttonHeight" in e17 ? e17.$buttonHeight : undefined;
    this.resetParam("titleMinHeight", (e17 && "titleMinHeight" in e17) ? e17.titleMinHeight : 0);
    this.dialogBuilder = "dialogBuilder" in e17 ? e17.dialogBuilder : this.doNothingBuilder;
  }
  doNothingBuilder(d17 = null) {
  }
  ;
  onPlaceChildren(w16, x16, y16) {
    let z16 = 0;
    let a17 = 0;
    for (let b17 = 0; b17 < x16.length; b17++) {
      let c17 = x16[b17];
      c17.layout({ x: z16, y: a17 });
      a17 += c17.measureResult.height;
    }
  }
  onMeasureSize(i16, j16, k16) {
    let l16 = { width: Number(k16.maxWidth), height: 0 };
    let m16 = 3;
    if (j16.length < m16) {
      return l16;
    }
    let n16 = 0;
    let o16 = j16[this.titleIndex];
    let p16 = {
      maxWidth: k16.maxWidth,
      minHeight: this.titleMinHeight,
      maxHeight: k16.maxHeight
    };
    let q16 = o16.measure(p16);
    this.$titleHeight?.(q16.height);
    n16 += q16.height;
    let r16 = j16[this.buttonIndex];
    let s16 = r16.measure(k16);
    this.$buttonHeight?.(s16.height);
    n16 += s16.height;
    let t16 = j16[this.contentIndex];
    let u16 = {
      maxWidth: k16.maxWidth,
      maxHeight: Number(k16.maxHeight) - n16
    };
    let v16 = t16.measure(u16);
    n16 += v16.height;
    l16.height = n16;
    return l16;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(h16) {
    if (h16 === undefined) {
      return;
    }
    if ("titleHeight" in h16) {
      this.updateParam("titleHeight", h16.titleHeight);
    }
    if ("buttonHeight" in h16) {
      this.updateParam("buttonHeight", h16.buttonHeight);
    }
    if ("titleMinHeight" in h16) {
      this.updateParam("titleMinHeight", h16.titleMinHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], CustomDialogLayout.prototype, "titleHeight", void 0);
__decorate([
  Event
], CustomDialogLayout.prototype, "$titleHeight", void 0);
__decorate([
  Param
], CustomDialogLayout.prototype, "buttonHeight", void 0);
__decorate([
  Event
], CustomDialogLayout.prototype, "$buttonHeight", void 0);
__decorate([
  Param
], CustomDialogLayout.prototype, "titleMinHeight", void 0);
class CustomDialogContentComponent extends ViewV2 {
  constructor(b16, c16, d16, e16 = -1, f16, g16) {
    super(b16, e16, g16);
    this.initParam("primaryTitle", (c16 && "primaryTitle" in c16) ? c16.primaryTitle : undefined);
    this.initParam("secondaryTitle", (c16 && "secondaryTitle" in c16) ? c16.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in c16 ? c16.contentBuilder : this.defaultContentBuilder;
    this.initParam("buttons", (c16 && "buttons" in c16) ? c16.buttons : undefined);
    this.initParam("contentAreaPadding", (c16 && "contentAreaPadding" in c16) ? c16.contentAreaPadding : undefined);
    this.initParam("minContentHeight", (c16 && "minContentHeight" in c16) ? c16.minContentHeight : undefined);
    this.$minContentHeight = "$minContentHeight" in c16 ? c16.$minContentHeight : undefined;
    this.keyIndex = 0;
    this.titleHeight = 0;
    this.buttonHeight = 0;
    this.contentMaxHeight = '100%';
    this.fontSizeScale = -1;
    this.customStyle = undefined;
    this.buttonMaxFontSize = `${BODY_L}fp`;
    this.buttonMinFontSize = 9;
    this.primaryTitleFontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.secondaryTitleFontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.titleTextAlign = TextAlign.Center;
    this.isButtonVertical = false;
    this.isFollowingSystemFontScale = false;
    this.appMaxFontScale = 3.2;
    this.titleIndex = 0;
    this.contentIndex = 1;
    this.buttonIndex = 2;
    this.primaryTitleMaxFontSize = `${TITLE_S}fp`;
    this.primaryTitleMinFontSize = `${BODY_L}fp`;
    this.secondaryTitleMaxFontSize = `${SUBTITLE_S}fp`;
    this.secondaryTitleMinFontSize = `${BODY_S}fp`;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(a16) {
    this.resetParam("primaryTitle", (a16 && "primaryTitle" in a16) ? a16.primaryTitle : undefined);
    this.resetParam("secondaryTitle", (a16 && "secondaryTitle" in a16) ? a16.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in a16 ? a16.contentBuilder : this.defaultContentBuilder;
    this.resetParam("buttons", (a16 && "buttons" in a16) ? a16.buttons : undefined);
    this.resetParam("contentAreaPadding", (a16 && "contentAreaPadding" in a16) ? a16.contentAreaPadding : undefined);
    this.resetParam("minContentHeight", (a16 && "minContentHeight" in a16) ? a16.minContentHeight : undefined);
    this.$minContentHeight = "$minContentHeight" in a16 ? a16.$minContentHeight : undefined;
    this.titleHeight = 0;
    this.buttonHeight = 0;
    this.contentMaxHeight = '100%';
    this.resetConsumer("fontSizeScale", -1);
    this.customStyle = undefined;
    this.buttonMaxFontSize = `${BODY_L}fp`;
    this.buttonMinFontSize = 9;
    this.primaryTitleFontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.secondaryTitleFontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.titleTextAlign = TextAlign.Center;
    this.isButtonVertical = false;
  }
  defaultContentBuilder(z15 = null) {
  }
  initialRender() {
    this.observeComponentCreation2((x15, y15) => {
      Scroll.create();
      Scroll.backgroundColor(Color.Transparent);
    }, Scroll);
    this.observeComponentCreation2((v15, w15) => {
      Column.create();
      Column.constraintSize({ maxHeight: this.contentMaxHeight });
      Column.backgroundBlurStyle(this.customStyle ?
        BlurStyle.Thick : BlurStyle.NONE, undefined, { disableSystemAdaptation: true });
      Column.borderRadius(this.customStyle ? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_dialog'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : 0);
      Column.margin(this.customStyle ? {
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_dialog_margin_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_dialog_margin_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_dialog_margin_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      } : { left: 0, right: 0, bottom: 0 });
      Column.backgroundColor(this.customStyle ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_dialog_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : Color.Transparent);
    }, Column);
    {
      this.observeComponentCreation2((x14, y14) => {
        if (y14) {
          let z14 = new CustomDialogLayout(this, {
            buttonHeight: this.buttonHeight,
            titleHeight: this.titleHeight,
            titleMinHeight: this.getTitleAreaMinHeight(),
            dialogBuilder: () => {
              this.observeComponentCreation2((m15, n15) => {
                ForEach.create();
                const i = p15 => {
                  const q15 = p15;
                  this.observeComponentCreation2((r15, s15) => {
                    If.create();
                    if (q15 === this.titleIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.titleBuilder.bind(this)();
                      });
                    }
                    else if (q15 === this.contentIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.observeComponentCreation2((t15, u15) => {
                          Column.create();
                          Column.padding(this.getContentPadding());
                        }, Column);
                        this.contentBuilder.bind(this)();
                        Column.pop();
                      });
                    }
                    else {
                      this.ifElseBranchUpdateFunction(2, () => {
                        this.ButtonBuilder.bind(this)();
                      });
                    }
                  }, If);
                  If.pop();
                };
                this.forEachUpdateFunction(m15, [this.titleIndex, this.contentIndex, this.buttonIndex], i);
              }, ForEach);
              ForEach.pop();
            },
            $buttonHeight: l15 => { this.buttonHeight = l15; },
            $titleHeight: k15 => { this.titleHeight = k15; }
          }, undefined, x14, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 1044, col: 9 });
          ViewV2.create(z14);
          let f = () => {
            return {
              buttonHeight: this.buttonHeight,
              titleHeight: this.titleHeight,
              titleMinHeight: this.getTitleAreaMinHeight(),
              dialogBuilder: () => {
                this.observeComponentCreation2((b15, c15) => {
                  ForEach.create();
                  const g = e15 => {
                    const f15 = e15;
                    this.observeComponentCreation2((g15, h15) => {
                      If.create();
                      if (f15 === this.titleIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.titleBuilder.bind(this)();
                        });
                      }
                      else if (f15 === this.contentIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.observeComponentCreation2((i15, j15) => {
                            Column.create();
                            Column.padding(this.getContentPadding());
                          }, Column);
                          this.contentBuilder.bind(this)();
                          Column.pop();
                        });
                      }
                      else {
                        this.ifElseBranchUpdateFunction(2, () => {
                          this.ButtonBuilder.bind(this)();
                        });
                      }
                    }, If);
                    If.pop();
                  };
                  this.forEachUpdateFunction(b15, [this.titleIndex, this.contentIndex, this.buttonIndex], g);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          z14.paramsGenerator_ = f;
        }
        else {
          this.updateStateVarsOfChildByElmtId(x14, {
            buttonHeight: this.buttonHeight,
            titleHeight: this.titleHeight,
            titleMinHeight: this.getTitleAreaMinHeight()
          });
        }
      }, { name: "CustomDialogLayout" });
    }
    Column.pop();
    Scroll.pop();
  }
  onMeasureSize(o14, p14, q14) {
    let r14 = { width: o14.width, height: o14.height };
    let s14 = Number(q14.maxWidth);
    let t14 = Number(q14.maxHeight);
    this.fontSizeScale = this.updateFontScale();
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(s14 - BUTTON_HORIZONTAL_MARGIN * 2);
    let u14 = 0;
    p14.forEach((v14) => {
      this.contentMaxHeight = '100%';
      let w14 = v14.measure(q14);
      if (t14 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
        this.contentMaxHeight = MAX_CONTENT_HEIGHT;
        w14 = v14.measure(q14);
      }
      u14 += w14.height;
    });
    r14.height = u14;
    r14.width = s14;
    return r14;
  }
  onWillApplyTheme(n14) {
    this.primaryTitleFontColorWithTheme = n14.colors.fontPrimary;
    this.secondaryTitleFontColorWithTheme = n14.colors.fontSecondary;
  }
  aboutToAppear() {
    try {
      let m14 = this.getUIContext();
      this.isFollowingSystemFontScale = m14?.isFollowingSystemFontScale();
      this.appMaxFontScale = m14?.getMaxFontScale();
    }
    catch (err) {
      let code = err?.code;
      let message = err?.message;
      hilog.error(0x3900, 'Ace', `Faild to dialog getUIContext, code: ${code}, message: ${message}`);
    }
    this.fontSizeScale = this.updateFontScale();
    this.initTitleTextAlign();
  }
  updateFontSize() {
    if (this.fontSizeScale > MAX_FONT_SCALE) {
      this.buttonMaxFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE * MAX_FONT_SCALE + 'vp';
    }
    else {
      this.buttonMaxFontSize = BODY_L + 'fp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'fp';
    }
  }
  updateFontScale() {
    try {
      let k14 = this.getUIContext();
      let l14 = k14.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(l14, this.appMaxFontScale);
    }
    catch (h14) {
      let i14 = h14.code;
      let j14 = h14.message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${i14}, message: ${j14}`);
      return 1;
    }
  }
  getContentPadding() {
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }
    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: 0,
        left: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
    }
    else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        left: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
    }
    else if (this.buttons && this.buttons.length > 0) {
      return {
        top: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: 0,
        left: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
    }
    else {
      return {
        top: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        left: { "id": -1, "type": 10002, params: ['sys.float.alert_content_default_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
    }
  }
  titleBuilder(s13 = null) {
    this.observeComponentCreation2((f14, g14) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
    }, Column);
    this.observeComponentCreation2((d14, e14) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((b14, c14) => {
      Text.create(this.primaryTitle);
      Text.fontWeight(FontWeight.Bold);
      Text.fontColor(this.primaryTitleFontColorWithTheme);
      Text.textAlign(this.titleTextAlign);
      Text.maxFontSize(this.primaryTitleMaxFontSize);
      Text.minFontSize(this.primaryTitleMinFontSize);
      Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((x13, y13) => {
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((z13, a14) => {
            Row.create();
            Row.height({ "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
    this.observeComponentCreation2((v13, w13) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((t13, u13) => {
      Text.create(this.secondaryTitle);
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor(this.secondaryTitleFontColorWithTheme);
      Text.textAlign(this.titleTextAlign);
      Text.maxFontSize(this.secondaryTitleMaxFontSize);
      Text.minFontSize(this.secondaryTitleMinFontSize);
      Text.maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE));
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    Column.pop();
  }
  getTitleAreaPadding() {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: { "id": -1, "type": 10002, params: ['sys.float.alert_title_padding_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.alert_title_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        left: { "id": -1, "type": 10002, params: ['sys.float.alert_title_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.alert_title_padding_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
    }
    return {
      top: 0,
      right: { "id": -1, "type": 10002, params: ['sys.float.alert_title_padding_right'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      left: { "id": -1, "type": 10002, params: ['sys.float.alert_title_padding_left'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      bottom: 0,
    };
  }
  initTitleTextAlign() {
    let r13 = ALERT_TITLE_ALIGNMENT;
    if (r13 === TextAlign.Start) {
      this.titleTextAlign = TextAlign.Start;
    }
    else if (r13 === TextAlign.Center) {
      this.titleTextAlign = TextAlign.Center;
    }
    else if (r13 === TextAlign.End) {
      this.titleTextAlign = TextAlign.End;
    }
    else if (r13 === TextAlign.JUSTIFY) {
      this.titleTextAlign = TextAlign.JUSTIFY;
    }
    else {
      this.titleTextAlign = TextAlign.Center;
    }
  }
  getTitleAreaMinHeight() {
    if (this.secondaryTitle) {
      return { "id": -1, "type": 10002, params: ['sys.float.alert_title_secondary_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    else if (this.primaryTitle) {
      return { "id": -1, "type": 10002, params: ['sys.float.alert_title_primary_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
    else {
      return 0;
    }
  }
  ButtonBuilder(k13 = null) {
    this.observeComponentCreation2((p13, q13) => {
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
    }, Column);
    this.observeComponentCreation2((l13, m13) => {
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((n13, o13) => {
            If.create();
            if (this.isButtonVertical) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.buildVerticalAlignButtons.bind(this)();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
                this.buildHorizontalAlignButtons.bind(this)();
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
    Column.pop();
  }
  getOperationAreaPadding() {
    if (this.isButtonVertical) {
      return {
        top: { "id": -1, "type": 10002, params: ['sys.float.alert_button_top_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        right: { "id": -1, "type": 10002, params: ['sys.float.alert_right_padding_vertical'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        left: { "id": -1, "type": 10002, params: ['sys.float.alert_left_padding_vertical'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.alert_button_bottom_padding_vertical'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      };
    }
    return {
      top: { "id": -1, "type": 10002, params: ['sys.float.alert_button_top_padding'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      right: { "id": -1, "type": 10002, params: ['sys.float.alert_right_padding_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      left: { "id": -1, "type": 10002, params: ['sys.float.alert_left_padding_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      bottom: { "id": -1, "type": 10002, params: ['sys.float.alert_button_bottom_padding_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    };
  }
  buildSingleButton(y12, z12 = null) {
    this.observeComponentCreation2((a13, b13) => {
      If.create();
      if (this.isNewPropertiesHighPriority(y12)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((i13, j13) => {
            Button.createWithLabel(this.buttons?.[y12].content);
            __Button__setButtonProperties(this.buttons?.[y12], this.buttons, this.getDialogController());
            Button.role(this.buttons?.[y12].role ?? ButtonRole.NORMAL);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else if (this.buttons?.[y12].background !== undefined && this.buttons?.[y12].fontColor !== undefined) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((g13, h13) => {
            Button.createWithLabel(this.buttons?.[y12].content);
            __Button__setButtonProperties(this.buttons?.[y12], this.buttons, this.getDialogController());
            Button.backgroundColor(this.buttons?.[y12].background?.color);
            Button.fontColor(this.buttons?.[y12].fontColor?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else if (this.buttons?.[y12].background !== undefined) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((e13, f13) => {
            Button.createWithLabel(this.buttons?.[y12].content);
            __Button__setButtonProperties(this.buttons?.[y12], this.buttons, this.getDialogController());
            Button.backgroundColor(this.buttons?.[y12].background?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(3, () => {
          this.observeComponentCreation2((c13, d13) => {
            Button.createWithLabel(this.buttons?.[y12].content);
            __Button__setButtonProperties(this.buttons?.[y12], this.buttons, this.getDialogController());
            Button.fontColor(this.buttons?.[y12]?.fontColor?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
    }, If);
    If.pop();
  }
  buildHorizontalAlignButtons(n12 = null) {
    this.observeComponentCreation2((o12, p12) => {
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((w12, x12) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(0);
          this.observeComponentCreation2((q12, r12) => {
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((u12, v12) => {
                  Row.create();
                  Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                  Row.justifyContent(FlexAlign.Center);
                }, Row);
                this.observeComponentCreation2((s12, t12) => {
                  Divider.create();
                  Divider.width({ "id": -1, "type": 10002, params: ['sys.float.alert_divider_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Divider.height({ "id": -1, "type": 10002, params: ['sys.float.alert_divider_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Divider.color(this.getDividerColor());
                  Divider.vertical(true);
                }, Divider);
                Row.pop();
                this.buildSingleButton.bind(this)(HORIZON_BUTTON_MAX_COUNT - 1);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
          }, If);
          If.pop();
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
  buildVerticalAlignButtons(b12 = null) {
    this.observeComponentCreation2((c12, d12) => {
      If.create();
      if (this.buttons) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((l12, m12) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((e12, f12) => {
            ForEach.create();
            const e = (i12, j12) => {
              const k12 = i12;
              this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                HORIZON_BUTTON_MAX_COUNT - j12 - 1 : j12);
            };
            this.forEachUpdateFunction(e12, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), e, (h12) => h12.content.toString(), true, false);
          }, ForEach);
          ForEach.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
  }
  getDividerColor() {
    if (!this.buttons || this.buttons.length === 0 || !DIALOG_DIVIDER_SHOW) {
      return Color.Transparent;
    }
    if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
      if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
        this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
        return { "id": -1, "type": 10001, params: ['sys.color.alert_divider_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
      }
    }
    return Color.Transparent;
  }
  isNewPropertiesHighPriority(a12) {
    if (this.buttons?.[a12].role === ButtonRole.ERROR) {
      return true;
    }
    if (this.buttons?.[a12].buttonStyle !== undefined &&
      this.buttons?.[a12].buttonStyle !== ALERT_BUTTON_STYLE) {
      return true;
    }
    if (this.buttons?.[a12].background === undefined && this.buttons?.[a12].fontColor === undefined) {
      return true;
    }
    return false;
  }
  buildButtonWithDivider(q11, r11 = null) {
    this.observeComponentCreation2((s11, t11) => {
      If.create();
      if (this.buttons && this.buttons[q11]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y11, z11) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(q11);
          Row.pop();
          this.observeComponentCreation2((u11, v11) => {
            If.create();
            if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - q11 - 1 : q11) <
              Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((w11, x11) => {
                  Row.create();
                  Row.height({ "id": -1, "type": 10002, params: ['sys.float.alert_button_vertical_space'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
  }
  isVerticalAlignButton(l11) {
    if (this.buttons) {
      if (this.buttons.length === 1) {
        return false;
      }
      if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
        return true;
      }
      let m11 = false;
      let n11 = vp2px(l11 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
        BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
      this.buttons.forEach((o11) => {
        let p11 = measure.measureTextSize({
          textContent: o11.content,
          fontSize: this.buttonMaxFontSize
        });
        if (Number(p11.width) > n11) {
          m11 = true;
        }
      });
      return m11;
    }
    return false;
  }
  updateStateVars(k11) {
    if (k11 === undefined) {
      return;
    }
    if ("primaryTitle" in k11) {
      this.updateParam("primaryTitle", k11.primaryTitle);
    }
    if ("secondaryTitle" in k11) {
      this.updateParam("secondaryTitle", k11.secondaryTitle);
    }
    if ("buttons" in k11) {
      this.updateParam("buttons", k11.buttons);
    }
    if ("contentAreaPadding" in k11) {
      this.updateParam("contentAreaPadding", k11.contentAreaPadding);
    }
    if ("minContentHeight" in k11) {
      this.updateParam("minContentHeight", k11.minContentHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], CustomDialogContentComponent.prototype, "primaryTitle", void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, "secondaryTitle", void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, "buttons", void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, "contentAreaPadding", void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, "minContentHeight", void 0);
__decorate([
  Event
], CustomDialogContentComponent.prototype, "$minContentHeight", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "titleHeight", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "buttonHeight", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "contentMaxHeight", void 0);
__decorate([
  Consumer()
], CustomDialogContentComponent.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "customStyle", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "buttonMaxFontSize", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "buttonMinFontSize", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "primaryTitleFontColorWithTheme", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "secondaryTitleFontColorWithTheme", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "titleTextAlign", void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, "isButtonVertical", void 0);
function __Button__setButtonProperties(g11, h11, i11) {
  Button.onKeyEvent((j11) => {
    if (!j11) {
      return;
    }
    if ((j11.keyCode === KeyCode.KEYCODE_SPACE || j11.keyCode === KeyCode.KEYCODE_ENTER) &&
      j11.type === KeyType.Down) {
      if (g11?.action) {
        g11.action();
      }
      i11?.close();
      j11.stopPropagation();
    }
  });
  Button.onClick(() => {
    if (g11?.action) {
      g11.action();
    }
    i11?.close();
  });
  Button.defaultFocus(g11?.defaultFocus ? true : isHasDefaultFocus(h11) ? false : true);
  Button.buttonStyle(g11?.buttonStyle ?? ALERT_BUTTON_STYLE);
  Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
  Button.type(ButtonType.ROUNDED_RECTANGLE);
  Button.enabled(g11?.enabled ?? true);
}
function isHasDefaultFocus(a11) {
  try {
    let e11 = false;
    a11?.forEach((f11) => {
      if (f11.defaultFocus) {
        e11 = true;
      }
    });
    return e11;
  }
  catch (b11) {
    let c11 = b11.code;
    let d11 = b11.message;
    hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${c11}, message: ${d11}`);
    return false;
  }
}
function getNumberByResourceId(t10, u10, v10) {
  try {
    let z10 = resourceManager.getSystemResourceManager().getNumber(t10);
    if (z10 > 0 || v10) {
      return z10;
    }
    else {
      return u10;
    }
  }
  catch (w10) {
    let x10 = w10.code;
    let y10 = w10.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${x10}, message: ${y10}`);
    return u10;
  }
}
function getEnumNumberByResourceId(n10, o10) {
  try {
    let s10 = getContext().resourceManager.getNumber(n10);
    if (s10 > 0) {
      return s10;
    }
    else {
      return o10;
    }
  }
  catch (p10) {
    let q10 = p10.code;
    let r10 = p10.message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${q10}, message: ${r10}`);
    return o10;
  }
}
function getAccessibilityText(g10, h10) {
  try {
    let l10 = getContext().resourceManager.getStringSync(125833934);
    let m10 = '';
    if (typeof g10 === 'string') {
      m10 = g10;
    }
    else {
      m10 = getContext().resourceManager.getStringSync(g10);
    }
    return h10 ? `${l10},${m10}` : m10;
  }
  catch (i10) {
    let j10 = i10.code;
    let k10 = i10.message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${j10}, message: ${k10}`);
    return '';
  }
}
function resolveKeyEvent(e10, f10) {
  if (e10.type === IGNORE_KEY_EVENT_TYPE) {
    return;
  }
  if (e10.keyCode === KEYCODE_UP) {
    f10.scrollPage({ next: false });
    e10.stopPropagation();
  }
  else if (e10.keyCode === KEYCODE_DOWN) {
    if (f10.isAtEnd()) {
      return;
    }
    else {
      f10.scrollPage({ next: true });
      e10.stopPropagation();
    }
  }
}
function getCheckTipsAccessibilityText(v9, w9) {
  try {
    let a10 = getContext().resourceManager.getStringSync(125833934);
    let b10 = getContext().resourceManager.getStringSync(125833935);
    let c10 = getContext().resourceManager.getStringSync(125834354);
    let d10 = '';
    if (typeof v9 === 'string') {
      d10 = v9;
    }
    else {
      d10 = getContext().resourceManager.getStringSync(v9);
    }
    return w9 ? `${a10},${d10},${c10}` :
      `${b10},${d10},${c10}`;
  }
  catch (x9) {
    let y9 = x9.code;
    let z9 = x9.message;
    hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${y9}, message: ${z9}`);
    return '';
  }
}
export class LoadingDialogV2 extends ViewV2 {
  constructor(p9, q9, r9, s9 = -1, t9, u9) {
    super(p9, s9, u9);
    this.initParam("content", (q9 && "content" in q9) ? q9.content : '');
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.loadingProgressIconColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(o9) {
    this.resetParam("content", (o9 && "content" in o9) ? o9.content : '');
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.loadingProgressIconColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
  }
  initialRender() {
    this.observeComponentCreation2((m9, n9) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((k9, l9) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((e9, f9) => {
        if (f9) {
          let g9 = new CustomDialogContentComponent(this, {
            contentBuilder: () => {
              this.contentBuilder();
            },
            minContentHeight: this.minContentHeight,
            $minContentHeight: h => { this.minContentHeight = h; }
          }, undefined, e9, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 1651, col: 7 });
          ViewV2.create(g9);
          let d = () => {
            return {
              contentBuilder: () => {
                this.contentBuilder();
              },
              minContentHeight: this.minContentHeight
            };
          };
          g9.paramsGenerator_ = d;
        }
        else {
          this.updateStateVarsOfChildByElmtId(e9, {
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
    Column.pop();
  }
  contentBuilder(v8 = null) {
    this.observeComponentCreation2((c9, d9) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((a9, b9) => {
      Row.create();
      Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
    }, Row);
    this.observeComponentCreation2((y8, z8) => {
      Text.create(this.content);
      Text.fontSize(`${BODY_L}fp`);
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor(this.fontColorWithTheme);
      Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
      Text.maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES);
      Text.focusable(true);
      Text.defaultFocus(true);
      Text.focusBox({
        strokeWidth: LengthMetrics.px(0)
      });
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    }, Text);
    Text.pop();
    this.observeComponentCreation2((w8, x8) => {
      LoadingProgress.create();
      LoadingProgress.color(this.loadingProgressIconColorWithTheme);
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) });
    }, LoadingProgress);
    Row.pop();
    Column.pop();
  }
  onWillApplyTheme(u8) {
    this.fontColorWithTheme = u8.colors.fontPrimary;
    this.loadingProgressIconColorWithTheme = u8.colors.iconSecondary;
  }
  updateStateVars(t8) {
    if (t8 === undefined) {
      return;
    }
    if ("content" in t8) {
      this.updateParam("content", t8.content);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], LoadingDialogV2.prototype, "content", void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, "fontColorWithTheme", void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, "loadingProgressIconColorWithTheme", void 0);
__decorate([
  Provider()
], LoadingDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, "minContentHeight", void 0);
export class PopoverDialogV2 extends ViewV2 {
  constructor(n8, o8, p8, q8 = -1, r8, s8) {
    super(n8, q8, s8);
    this.initParam("visible", (o8 && "visible" in o8) ? o8.visible : false);
    this.$visible = "$visible" in o8 ? o8.$visible : () => { };
    this.initParam("popover", (o8 && "popover" in o8) ? o8.popover : {
      builder: undefined
    });
    this.targetBuilder = "targetBuilder" in o8 ? o8.targetBuilder : undefined;
    this.dialogWidth = this.popover?.width;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(m8) {
    this.resetParam("visible", (m8 && "visible" in m8) ? m8.visible : false);
    this.$visible = "$visible" in m8 ? m8.$visible : () => { };
    this.resetParam("popover", (m8 && "popover" in m8) ? m8.popover : {
      builder: undefined
    });
    this.targetBuilder = "targetBuilder" in m8 ? m8.targetBuilder : undefined;
    this.dialogWidth = this.popover?.width;
  }
  emptyBuilder(l8 = null) {
  }
  aboutToAppear() {
    if (this.targetBuilder === undefined || this.targetBuilder === null) {
      this.targetBuilder = this.emptyBuilder;
    }
  }
  initialRender() {
    this.observeComponentCreation2((d8, e8) => {
      Column.create();
      Column.onClick(() => {
        try {
          let j8 = display.getDefaultDisplaySync();
          let k8 = px2vp(j8.width);
          if (k8 - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
            this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
          }
          else {
            this.popover.width = this.dialogWidth;
          }
          this.$visible?.(!this.visible);
        }
        catch (g8) {
          let h8 = g8.code;
          let i8 = g8.message;
          hilog.error(0x3900, 'Ace', `dialog popup error, code: ${h8}, message: ${i8}`);
        }
      });
      Column.bindPopup(this.visible, {
        builder: this.popover?.builder,
        placement: this.popover?.placement ?? Placement.Bottom,
        popupColor: this.popover?.popupColor,
        enableArrow: this.popover?.enableArrow ?? true,
        autoCancel: this.popover?.autoCancel,
        onStateChange: this.popover?.onStateChange ?? ((f8) => {
          if (!f8.isVisible) {
            this.$visible?.(false);
          }
        }),
        arrowOffset: this.popover?.arrowOffset,
        showInSubWindow: this.popover?.showInSubWindow,
        mask: this.popover?.mask,
        targetSpace: this.popover?.targetSpace,
        offset: this.popover?.offset,
        width: this.popover?.width,
        arrowPointPosition: this.popover?.arrowPointPosition,
        arrowWidth: this.popover?.arrowWidth,
        arrowHeight: this.popover?.arrowHeight,
        radius: this.popover?.radius ?? { "id": -1, "type": 10002, params: ['sys.float.corner_radius_level16'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        shadow: this.popover?.shadow ?? ShadowStyle.OUTER_DEFAULT_MD,
        backgroundBlurStyle: this.popover?.backgroundBlurStyle ?? BlurStyle.COMPONENT_ULTRA_THICK,
        focusable: this.popover?.focusable,
        transition: this.popover?.transition,
        onWillDismiss: this.popover?.onWillDismiss
      });
    }, Column);
    this.targetBuilder.bind(this)();
    Column.pop();
  }
  updateStateVars(c8) {
    if (c8 === undefined) {
      return;
    }
    if ("visible" in c8) {
      this.updateParam("visible", c8.visible);
    }
    if ("popover" in c8) {
      this.updateParam("popover", c8.popover);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], PopoverDialogV2.prototype, "visible", void 0);
__decorate([
  Event
], PopoverDialogV2.prototype, "$visible", void 0);
__decorate([
  Param
], PopoverDialogV2.prototype, "popover", void 0);
__decorate([
  Local
], PopoverDialogV2.prototype, "dialogWidth", void 0);
function toLengthString(a) {
  if (!a) {
    return undefined;
  }
  const b = a.value;
  let c = '';
  switch (a.unit) {
    case LengthUnit.PX:
      c = `${b}px`;
      break;
    case LengthUnit.FP:
      c = `${b}fp`;
      break;
    case LengthUnit.LPX:
      c = `${b}lpx`;
      break;
    case LengthUnit.PERCENT:
      c = `${b * 100}%`;
      break;
    case LengthUnit.VP:
      c = `${b}vp`;
      break;
    default:
      c = `${b}vp`;
      break;
  }
  return c;
}
function lengthMetricsToPX(value) {
  if (!value) {
    return 0;
  }
  const length = value.value;
  switch (value.unit) {
    case LengthUnit.PX:
      return length;
    case LengthUnit.FP:
      return fp2px(length);
    case LengthUnit.LPX:
      return lpx2px(length);
    case LengthUnit.VP:
      return vp2px(length);
    default:
      return 0;
  }
}
export default { TipsDialogV2, ConfirmDialogV2, SelectDialogV2, AlertDialogV2, LoadingDialogV2, CustomContentDialogV2, PopoverDialogV2, AdvancedDialogV2Button };