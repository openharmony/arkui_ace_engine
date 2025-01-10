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

var __decorate = (this && this.__decorate) || function (b21, c21, d21, e21) {
  var f21 = arguments.length, g21 = f21 < 3 ? c21 : e21 === null ? e21 = Object.getOwnPropertyDescriptor(c21, d21) : e21, h21;
  if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
    g21 = Reflect.decorate(b21, c21, d21, e21);
  else
    for (var i21 = b21.length - 1; i21 >= 0; i21--)
      if (h21 = b21[i21])
        g21 = (f21 < 3 ? h21(g21) : f21 > 3 ? h21(c21, d21, g21) : h21(c21, d21)) || g21;
  return f21 > 3 && g21 && Object.defineProperty(c21, d21, g21), g21;
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
  constructor(a21) {
    this.content = '';
    this.content = a21.content;
    this.action = a21.action;
    this.background = a21.background;
    this.fontColor = a21.fontColor;
    this.buttonStyle = a21.buttonStyle;
    this.role = a21.role;
    this.defaultFocus = a21.defaultFocus;
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
AdvancedDialogV2Button = __decorate([
  ObservedV2
], AdvancedDialogV2Button);
export { AdvancedDialogV2Button };
export class TipsDialogV2 extends ViewV2 {
  constructor(u20, v20, w20, x20 = -1, y20, z20) {
    super(u20, x20, z20);
    this.initParam("imageRes", (v20 && "imageRes" in v20) ? v20.imageRes : undefined);
    this.initParam("imageSize", (v20 && "imageSize" in v20) ? v20.imageSize : { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE });
    this.initParam("title", (v20 && "title" in v20) ? v20.title : null);
    this.initParam("content", (v20 && "content" in v20) ? v20.content : null);
    this.initParam("onCheckedChange", (v20 && "onCheckedChange" in v20) ? v20.onCheckedChange : undefined);
    this.initParam("checkTips", (v20 && "checkTips" in v20) ? v20.checkTips : null);
    this.initParam("isChecked", (v20 && "isChecked" in v20) ? v20.isChecked : false);
    this.isCheckedInner = false;
    this.initParam("primaryButton", (v20 && "primaryButton" in v20) ? v20.primaryButton : null);
    this.initParam("secondaryButton", (v20 && "secondaryButton" in v20) ? v20.secondaryButton : null);
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
  resetStateVarsOnReuse(l22) {
    this.resetParam("imageRes", (l22 && "imageRes" in l22) ? l22.imageRes : undefined);
    this.resetParam("imageSize", (l22 && "imageSize" in l22) ? l22.imageSize : { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE });
    this.resetParam("title", (l22 && "title" in l22) ? l22.title : null);
    this.resetParam("content", (l22 && "content" in l22) ? l22.content : null);
    this.resetParam("onCheckedChange", (l22 && "onCheckedChange" in l22) ? l22.onCheckedChange : undefined);
    this.resetParam("checkTips", (l22 && "checkTips" in l22) ? l22.checkTips : null);
    this.resetParam("isChecked", (l22 && "isChecked" in l22) ? l22.isChecked : false);
    this.isCheckedInner = false;
    this.resetComputed("buttons");
    this.resetParam("primaryButton", (l22 && "primaryButton" in l22) ? l22.primaryButton : null);
    this.resetParam("secondaryButton", (l22 && "secondaryButton" in l22) ? l22.secondaryButton : null);
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = 160;
    this.resetMonitorsOnReuse();
  }
  isCheckedChangeMonitor(t20) {
    this.isCheckedInner = t20.value('isChecked')?.now;
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let s20 = [];
    if (this.primaryButton) {
      s20.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      s20.push(this.secondaryButton);
    }
    return s20;
  }
  onWillApplyTheme(r20) {
    this.fontColorWithTheme = r20.colors.fontPrimary;
  }
  initialRender() {
    this.observeComponentCreation2((p20, q20) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((j20, k20) => {
        if (k20) {
          let l20 = new CustomDialogContentComponent(this, {
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight,
            $fontSizeScale: o20 => { this.fontSizeScale = o20; },
            $minContentHeight: n20 => { this.minContentHeight = n20; }
          }, undefined, j20, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 175, col: 5 });
          ViewV2.create(l20);
          let m21 = () => {
            return {
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              fontSizeScale: this.fontSizeScale,
              minContentHeight: this.minContentHeight
            };
          };
          l20.paramsGenerator_ = m21;
        }
        else {
          this.updateStateVarsOfChildByElmtId(j20, {
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  contentBuilder(l19 = null) {
    {
      this.observeComponentCreation2((m19, n19) => {
        if (n19) {
          let o19 = new TipsDialogContentLayout(this, {
            title: this.title,
            content: this.content,
            checkTips: this.checkTips,
            minContentHeight: this.minContentHeight,
            dialogBuilder: () => {
              this.observeComponentCreation2((a20, b20) => {
                ForEach.create();
                const l21 = d20 => {
                  const e20 = d20;
                  this.observeComponentCreation2((f20, g20) => {
                    If.create();
                    if (e20 === this.imageIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.imagePart.bind(this)();
                      });
                    }
                    else if (e20 === this.textIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.observeComponentCreation2((h20, i20) => {
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
                this.forEachUpdateFunction(a20, [this.imageIndex, this.textIndex, this.checkBoxIndex], l21);
              }, ForEach);
              ForEach.pop();
            },
            $minContentHeight: z19 => { this.minContentHeight = z19; }
          }, undefined, m19, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 187, col: 5 });
          ViewV2.create(o19);
          let j21 = () => {
            return {
              title: this.title,
              content: this.content,
              checkTips: this.checkTips,
              minContentHeight: this.minContentHeight,
              dialogBuilder: () => {
                this.observeComponentCreation2((q19, r19) => {
                  ForEach.create();
                  const k21 = t19 => {
                    const u19 = t19;
                    this.observeComponentCreation2((v19, w19) => {
                      If.create();
                      if (u19 === this.imageIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.imagePart.bind(this)();
                        });
                      }
                      else if (u19 === this.textIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.observeComponentCreation2((x19, y19) => {
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
                  this.forEachUpdateFunction(q19, [this.imageIndex, this.textIndex, this.checkBoxIndex], k21);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          o19.paramsGenerator_ = j21;
        }
        else {
          this.updateStateVarsOfChildByElmtId(m19, {
            title: this.title,
            content: this.content,
            checkTips: this.checkTips,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "TipsDialogContentLayout" });
    }
  }
  checkBoxPart(a19 = null) {
    this.observeComponentCreation2((i19, j19) => {
      Row.create();
      Row.accessibilityGroup(true);
      Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isCheckedInner));
      Row.accessibilityDescription(this.isCheckedInner ? { "id": -1, "type": 10003, params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10003, params: ['sys.string.slider_accessibility_unselectedDesc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Row.onClick(() => {
        this.isCheckedInner = !this.isCheckedInner;
        try {
          let s19 = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.isChecked ? getContext().resourceManager.getStringSync(125833934) :
            getContext().resourceManager.getStringSync(125833935)
          });
          accessibility.sendAccessibilityEvent(s19);
        }
        catch (h2) {
          let l7 = h2.code;
          let b10 = h2.message;
          hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${l7}, message: ${b10}`);
        }
      });
      Row.padding({ top: 8, bottom: 8 });
      Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((b19, c19) => {
      If.create();
      if (this.checkTips !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((f19, g19) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.isCheckedInner);
            Checkbox.onChange((h19) => {
              this.isCheckedInner = h19;
              this.onCheckedChange?.(h19);
            });
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
          }, Checkbox);
          Checkbox.pop();
          this.observeComponentCreation2((d19, e19) => {
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
  imagePart(v18 = null) {
    this.observeComponentCreation2((y18, z18) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((w18, x18) => {
      Image.create(this.imageRes);
      Image.objectFit(ImageFit.Contain);
      Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Image.constraintSize({
        maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE,
        maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE
      });
    }, Image);
    Column.pop();
  }
  textPart(d18 = null) {
    this.observeComponentCreation2((t18, u18) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
    }, Scroll);
    this.observeComponentCreation2((r18, s18) => {
      Column.create();
      Column.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
    }, Column);
    this.observeComponentCreation2((l18, m18) => {
      If.create();
      if (this.title !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((p18, q18) => {
            Row.create();
            Row.padding({ bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
          }, Row);
          this.observeComponentCreation2((n18, o18) => {
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
    this.observeComponentCreation2((e18, f18) => {
      If.create();
      if (this.content !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((j18, k18) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((g18, h18) => {
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
            Text.onKeyEvent((i18) => {
              if (i18) {
                resolveKeyEvent(i18, this.contentScroller);
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
    let c18 = this.getUIContext();
    this.appMaxFontScale = c18.getMaxFontScale();
    this.isCheckedInner = this.isChecked;
  }
  getContentFontSize() {
    return BODY_L + 'fp';
  }
  updateStateVars(b18) {
    if (b18 === undefined) {
      return;
    }
    if ("imageRes" in b18) {
      this.updateParam("imageRes", b18.imageRes);
    }
    if ("imageSize" in b18) {
      this.updateParam("imageSize", b18.imageSize);
    }
    if ("title" in b18) {
      this.updateParam("title", b18.title);
    }
    if ("content" in b18) {
      this.updateParam("content", b18.content);
    }
    if ("onCheckedChange" in b18) {
      this.updateParam("onCheckedChange", b18.onCheckedChange);
    }
    if ("checkTips" in b18) {
      this.updateParam("checkTips", b18.checkTips);
    }
    if ("isChecked" in b18) {
      this.updateParam("isChecked", b18.isChecked);
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
], TipsDialogV2.prototype, "imageRes", void 0);
__decorate([
  Param
], TipsDialogV2.prototype, "imageSize", void 0);
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
], TipsDialogV2.prototype, "isChecked", void 0);
__decorate([
  Local
], TipsDialogV2.prototype, "isCheckedInner", void 0);
__decorate([
  Monitor('isChecked')
], TipsDialogV2.prototype, "isCheckedChangeMonitor", null);
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
  Local
], TipsDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], TipsDialogV2.prototype, "minContentHeight", void 0);
class TipsDialogContentLayout extends ViewV2 {
  constructor(v17, w17, x17, y17 = -1, z17, a18) {
    super(v17, y17, a18);
    this.initParam("title", (w17 && "title" in w17) ? w17.title : null);
    this.initParam("content", (w17 && "content" in w17) ? w17.content : null);
    this.initParam("checkTips", (w17 && "checkTips" in w17) ? w17.checkTips : null);
    this.initParam("minContentHeight", (w17 && "minContentHeight" in w17) ? w17.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in w17 ? w17.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in w17 ? w17.dialogBuilder : this.doNothingBuilder;
    this.imageIndex = 0;
    this.textIndex = 1;
    this.checkBoxIndex = 2;
    this.childrenSize = 3;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(g22) {
    this.resetParam("title", (g22 && "title" in g22) ? g22.title : null);
    this.resetParam("content", (g22 && "content" in g22) ? g22.content : null);
    this.resetParam("checkTips", (g22 && "checkTips" in g22) ? g22.checkTips : null);
    this.resetParam("minContentHeight", (g22 && "minContentHeight" in g22) ? g22.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in g22 ? g22.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in g22 ? g22.dialogBuilder : this.doNothingBuilder;
  }
  doNothingBuilder(u17 = null) {
  }
  ;
  onPlaceChildren(n17, o17, p17) {
    let q17 = 0;
    let r17 = 0;
    for (let s17 = 0; s17 < o17.length; s17++) {
      let t17 = o17[s17];
      t17.layout({ x: q17, y: r17 });
      r17 += t17.measureResult.height;
    }
  }
  onMeasureSize(v16, w16, x16) {
    let y16 = { width: Number(x16.maxWidth), height: 0 };
    if (w16.length < this.childrenSize) {
      return y16;
    }
    let z16 = 0;
    let a17 = 0;
    if (this.checkTips !== null) {
      let k17 = w16[this.checkBoxIndex];
      let l17 = {
        maxWidth: x16.maxWidth,
        minHeight: CHECKBOX_CONTAINER_HEIGHT,
        maxHeight: x16.maxHeight
      };
      let m17 = k17.measure(l17);
      a17 = m17.height;
      z16 += a17;
    }
    let b17 = w16[this.imageIndex];
    let c17 = 0;
    if (this.title !== null || this.content !== null) {
      c17 = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
    }
    let d17 = Number(x16.maxHeight) - a17 - c17;
    let e17 = {
      maxWidth: x16.maxWidth,
      maxHeight: d17
    };
    let f17 = b17.measure(e17);
    z16 += f17.height;
    if (this.title !== null || this.content !== null) {
      let g17 = w16[this.textIndex];
      let h17 = Number(x16.maxHeight) - f17.height - a17;
      let i17 = {
        maxWidth: x16.maxWidth,
        maxHeight: Math.max(h17, TEXT_MIN_HEIGHT)
      };
      let j17 = g17.measure(i17);
      z16 += j17.height;
    }
    y16.height = z16;
    this.$minContentHeight?.(Math.max(a17 + f17.height + c17, MIN_CONTENT_HEIGHT));
    return y16;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(u16) {
    if (u16 === undefined) {
      return;
    }
    if ("title" in u16) {
      this.updateParam("title", u16.title);
    }
    if ("content" in u16) {
      this.updateParam("content", u16.content);
    }
    if ("checkTips" in u16) {
      this.updateParam("checkTips", u16.checkTips);
    }
    if ("minContentHeight" in u16) {
      this.updateParam("minContentHeight", u16.minContentHeight);
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
  constructor(o16, p16, q16, r16 = -1, s16, t16) {
    super(o16, r16, t16);
    this.initParam("title", (p16 && "title" in p16) ? p16.title : '');
    this.initParam("content", (p16 && "content" in p16) ? p16.content : '');
    this.initParam("confirm", (p16 && "confirm" in p16) ? p16.confirm : null);
    this.initParam("radioContent", (p16 && "radioContent" in p16) ? p16.radioContent : []);
    this.initParam("selectedIndex", (p16 && "selectedIndex" in p16) ? p16.selectedIndex : -1);
    this.selectedIndexInner = -1;
    this.isFocus = false;
    this.currentFocusIndex = -1;
    this.radioHeight = 0;
    this.itemHeight = 0;
    this.contentBuilder = "contentBuilder" in p16 ? p16.contentBuilder : this.buildContent;
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.dividerColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.contentScroller = new Scroller();
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(f22) {
    this.resetParam("title", (f22 && "title" in f22) ? f22.title : '');
    this.resetParam("content", (f22 && "content" in f22) ? f22.content : '');
    this.resetParam("confirm", (f22 && "confirm" in f22) ? f22.confirm : null);
    this.resetParam("radioContent", (f22 && "radioContent" in f22) ? f22.radioContent : []);
    this.resetParam("selectedIndex", (f22 && "selectedIndex" in f22) ? f22.selectedIndex : -1);
    this.selectedIndexInner = -1;
    this.isFocus = false;
    this.currentFocusIndex = -1;
    this.radioHeight = 0;
    this.itemHeight = 0;
    this.contentBuilder = "contentBuilder" in f22 ? f22.contentBuilder : this.buildContent;
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.dividerColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.resetComputed("buttons");
    this.resetComputed("contentPadding");
    this.resetMonitorsOnReuse();
  }
  selectedIndexMonitor(n16) {
    this.selectedIndexInner = n16.value('selectedIndex')?.now;
  }
  get buttons() {
    let m16 = [];
    if (this.confirm) {
      m16.push(this.confirm);
    }
    return m16;
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
  buildContent(p14 = null) {
    this.observeComponentCreation2((h16, i16) => {
      Scroll.create(this.contentScroller);
      Scroll.scrollBar(BarState.Auto);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.onDidScroll((j16, k16) => {
        let l16 = (this.itemHeight - this.radioHeight) / 2;
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
            if (k16 > 0) {
              this.contentScroller.scrollBy(0, l16);
            }
            else if (k16 < 0) {
              this.contentScroller.scrollBy(0, 0 - l16);
            }
          }
          this.isFocus = false;
        }
      });
    }, Scroll);
    this.observeComponentCreation2((f16, g16) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((z15, a16) => {
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((d16, e16) => {
            Row.create();
            Row.padding({
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            Row.width('100%');
          }, Row);
          this.observeComponentCreation2((b16, c16) => {
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
    this.observeComponentCreation2((x15, y15) => {
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
    this.observeComponentCreation2((q14, r14) => {
      ForEach.create();
      const d2 = (t14, u14) => {
        const v14 = t14;
        {
          const e2 = (v15, w15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v15);
            f2(v15, w15);
            if (!w15) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const f2 = (r15, s15) => {
            ListItem.create(g2, true);
            ListItem.padding({
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
            });
            ListItem.onSizeChange((t15, u15) => {
              this.itemHeight = Number(u15.height);
            });
          };
          const g2 = (z14, a15) => {
            e2(z14, a15);
            this.observeComponentCreation2((p15, q15) => {
              Column.create();
              Column.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
              Column.focusBox({
                margin: { value: -2, unit: LengthUnit.VP }
              });
              Column.accessibilityText(getAccessibilityText(v14.title, this.selectedIndexInner === u14));
              Column.onClick(() => {
                this.selectedIndexInner = u14;
                v14.action && v14.action();
                this.getDialogController()?.close();
              });
            }, Column);
            this.observeComponentCreation2((n15, o15) => {
              Button.createWithChild();
              Button.type(ButtonType.Normal);
              Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
              Button.buttonStyle(ButtonStyleMode.TEXTUAL);
              Button.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
              });
            }, Button);
            this.observeComponentCreation2((l15, m15) => {
              Row.create();
              Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
              Row.clip(false);
              Row.padding({ top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }, bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } });
            }, Row);
            this.observeComponentCreation2((j15, k15) => {
              Text.create(v14.title);
              Text.fontSize(`${BODY_L}fp`);
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor(this.fontColorWithTheme);
              Text.layoutWeight(1);
            }, Text);
            Text.pop();
            this.observeComponentCreation2((f15, g15) => {
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
              Radio.checked(this.selectedIndexInner === u14);
              Radio.hitTestBehavior(HitTestMode.None);
              Radio.id(String(u14));
              Radio.focusable(false);
              Radio.accessibilityLevel('no');
              Radio.visibility(this.selectedIndex === u14 ? Visibility.Visible : Visibility.Hidden);
              Radio.onFocus(() => {
                this.isFocus = true;
                this.currentFocusIndex = u14;
                if (u14 === FIRST_ITEM_INDEX) {
                  this.contentScroller.scrollEdge(Edge.Top);
                }
                else if (u14 === this.radioContent.length - 1) {
                  this.contentScroller.scrollEdge(Edge.Bottom);
                }
              });
              Radio.onSizeChange((h15, i15) => {
                this.radioHeight = Number(i15.height);
              });
            }, Radio);
            Row.pop();
            Button.pop();
            this.observeComponentCreation2((b15, c15) => {
              If.create();
              if (u14 < this.radioContent.length - 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((d15, e15) => {
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
          this.observeComponentCreation2(f2, ListItem);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(q14, this.radioContent, d2, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    List.pop();
    Column.pop();
    Scroll.pop();
  }
  initialRender() {
    this.observeComponentCreation2((n14, o14) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((h14, i14) => {
        if (i14) {
          let j14 = new CustomDialogContentComponent(this, {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight,
            $fontSizeScale: m14 => { this.fontSizeScale = m14; },
            $minContentHeight: l14 => { this.minContentHeight = l14; }
          }, undefined, h14, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 586, col: 5 });
          ViewV2.create(j14);
          let p = () => {
            return {
              primaryTitle: this.title,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              contentAreaPadding: this.contentPadding,
              fontSizeScale: this.fontSizeScale,
              minContentHeight: this.minContentHeight
            };
          };
          j14.paramsGenerator_ = p;
        }
        else {
          this.updateStateVarsOfChildByElmtId(h14, {
            primaryTitle: this.title,
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  onWillApplyTheme(g14) {
    this.fontColorWithTheme = g14.colors.fontPrimary;
    this.dividerColorWithTheme = g14.colors.compDivider;
  }
  aboutToAppear() {
    this.selectedIndexInner = this.selectedIndex;
  }
  updateStateVars(f14) {
    if (f14 === undefined) {
      return;
    }
    if ("title" in f14) {
      this.updateParam("title", f14.title);
    }
    if ("content" in f14) {
      this.updateParam("content", f14.content);
    }
    if ("confirm" in f14) {
      this.updateParam("confirm", f14.confirm);
    }
    if ("radioContent" in f14) {
      this.updateParam("radioContent", f14.radioContent);
    }
    if ("selectedIndex" in f14) {
      this.updateParam("selectedIndex", f14.selectedIndex);
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
  Local
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
  constructor(z13, a14, b14, c14 = -1, d14, e14) {
    super(z13, c14, e14);
    this.textIndex = 0;
    this.checkboxIndex = 1;
    this.initParam("minContentHeight", (a14 && "minContentHeight" in a14) ? a14.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in a14 ? a14.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in a14 ? a14.dialogBuilder : this.doNothingBuilder;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(z21) {
    this.resetParam("minContentHeight", (z21 && "minContentHeight" in z21) ? z21.minContentHeight : 0);
    this.$minContentHeight = "$minContentHeight" in z21 ? z21.$minContentHeight : undefined;
    this.dialogBuilder = "dialogBuilder" in z21 ? z21.dialogBuilder : this.doNothingBuilder;
  }
  doNothingBuilder(y13 = null) {
  }
  ;
  onPlaceChildren(r13, s13, t13) {
    let u13 = 0;
    let v13 = 0;
    for (let w13 = 0; w13 < s13.length; w13++) {
      let x13 = s13[w13];
      x13.layout({ x: u13, y: v13 });
      v13 += x13.measureResult.height;
    }
  }
  onMeasureSize(f13, g13, h13) {
    let i13 = { width: Number(h13.maxWidth), height: 0 };
    let j13 = 2;
    if (g13.length < j13) {
      return i13;
    }
    let k13 = 0;
    let l13 = g13[this.checkboxIndex];
    let m13 = {
      maxWidth: h13.maxWidth,
      minHeight: CHECKBOX_CONTAINER_HEIGHT,
      maxHeight: h13.maxHeight
    };
    let n13 = l13.measure(m13);
    k13 += n13.height;
    let o13 = g13[this.textIndex];
    let p13 = {
      maxWidth: h13.maxWidth,
      maxHeight: Number(h13.maxHeight) - k13
    };
    let q13 = o13.measure(p13);
    k13 += q13.height;
    i13.height = k13;
    this.$minContentHeight?.(Math.max(n13.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT));
    return i13;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(e13) {
    if (e13 === undefined) {
      return;
    }
    if ("minContentHeight" in e13) {
      this.updateParam("minContentHeight", e13.minContentHeight);
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
  constructor(y12, z12, a13, b13 = -1, c13, d13) {
    super(y12, b13, d13);
    this.initParam("title", (z12 && "title" in z12) ? z12.title : '');
    this.initParam("content", (z12 && "content" in z12) ? z12.content : '');
    this.initParam("checkTips", (z12 && "checkTips" in z12) ? z12.checkTips : '');
    this.initParam("isChecked", (z12 && "isChecked" in z12) ? z12.isChecked : false);
    this.isCheckedInner = this.isChecked;
    this.initParam("primaryButton", (z12 && "primaryButton" in z12) ? z12.primaryButton : new AdvancedDialogV2Button({ content: "" }));
    this.initParam("secondaryButton", (z12 && "secondaryButton" in z12) ? z12.secondaryButton : new AdvancedDialogV2Button({ content: "" }));
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.initParam("onCheckedChange", (z12 && "onCheckedChange" in z12) ? z12.onCheckedChange : undefined);
    this.contentScroller = new Scroller();
    this.textAlign = TextAlign.Start;
    this.marginOffset = 0 - PADDING_LEVEL_8;
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.textIndex = 0;
    this.checkboxIndex = 1;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(y21) {
    this.resetParam("title", (y21 && "title" in y21) ? y21.title : '');
    this.resetParam("content", (y21 && "content" in y21) ? y21.content : '');
    this.resetParam("checkTips", (y21 && "checkTips" in y21) ? y21.checkTips : '');
    this.resetParam("isChecked", (y21 && "isChecked" in y21) ? y21.isChecked : false);
    this.isCheckedInner = this.isChecked;
    this.resetParam("primaryButton", (y21 && "primaryButton" in y21) ? y21.primaryButton : new AdvancedDialogV2Button({ content: "" }));
    this.resetParam("secondaryButton", (y21 && "secondaryButton" in y21) ? y21.secondaryButton : new AdvancedDialogV2Button({ content: "" }));
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.resetParam("onCheckedChange", (y21 && "onCheckedChange" in y21) ? y21.onCheckedChange : undefined);
    this.textAlign = TextAlign.Start;
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.resetComputed("buttons");
    this.resetMonitorsOnReuse();
  }
  isCheckedMonitor(x12) {
    this.isCheckedInner = x12.value('isChecked')?.now;
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let w12 = [];
    if (this.primaryButton) {
      w12.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      w12.push(this.secondaryButton);
    }
    return w12;
  }
  textBuilder(m12 = null) {
    this.observeComponentCreation2((u12, v12) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((s12, t12) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.margin({ end: LengthMetrics.vp(this.marginOffset) });
    }, Scroll);
    this.observeComponentCreation2((q12, r12) => {
      Column.create();
      Column.margin({ end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }) });
    }, Column);
    this.observeComponentCreation2((n12, o12) => {
      Text.create(this.content);
      Text.focusable(true);
      Text.defaultFocus(!(this.primaryButton?.content || this.secondaryButton?.content));
      Text.focusBox({
        strokeWidth: LengthMetrics.px(0)
      });
      Text.fontSize(`${BODY_L}fp`);
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor(this.fontColorWithTheme);
      Text.textAlign(this.textAlign);
      Text.onKeyEvent((p12) => {
        if (p12) {
          resolveKeyEvent(p12, this.contentScroller);
        }
      });
      Text.width('100%');
    }, Text);
    Text.pop();
    Column.pop();
    Scroll.pop();
    Column.pop();
  }
  checkBoxBuilder(d12 = null) {
    this.observeComponentCreation2((j12, k12) => {
      Row.create();
      Row.accessibilityGroup(true);
      Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isCheckedInner));
      Row.accessibilityDescription(this.isCheckedInner ? { "id": -1, "type": 10003, params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : { "id": -1, "type": 10003, params: ['sys.string.slider_accessibility_unselectedDesc'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
      Row.onClick(() => {
        this.isCheckedInner = !this.isCheckedInner;
        try {
          let o = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.isChecked ? getContext().resourceManager.getStringSync(125833934) :
            getContext().resourceManager.getStringSync(125833935)
          });
          accessibility.sendAccessibilityEvent(o);
        }
        catch (l) {
          let m = l.code;
          let n = l.message;
          hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${m}, message: ${n}`);
        }
      });
      Row.width('100%');
      Row.padding({ top: 8, bottom: 8 });
    }, Row);
    this.observeComponentCreation2((g12, h12) => {
      Checkbox.create({ name: '', group: 'checkboxGroup' });
      Checkbox.select(this.isCheckedInner);
      Checkbox.onChange((i12) => {
        this.isCheckedInner = i12;
        if (this.onCheckedChange) {
          this.onCheckedChange(this.isCheckedInner);
        }
      });
      Checkbox.hitTestBehavior(HitTestMode.Block);
      Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
    }, Checkbox);
    Checkbox.pop();
    this.observeComponentCreation2((e12, f12) => {
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
  buildContent(j11 = null) {
    {
      this.observeComponentCreation2((k11, l11) => {
        if (l11) {
          let m11 = new ConfirmDialogContentLayout(this, {
            minContentHeight: this.minContentHeight,
            dialogBuilder: () => {
              this.observeComponentCreation2((w11, x11) => {
                ForEach.create();
                const k = z11 => {
                  const a12 = z11;
                  this.observeComponentCreation2((b12, c12) => {
                    If.create();
                    if (a12 === this.textIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.textBuilder.bind(this)();
                      });
                    }
                    else if (a12 === this.checkboxIndex) {
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
                this.forEachUpdateFunction(w11, [this.textIndex, this.checkboxIndex], k);
              }, ForEach);
              ForEach.pop();
            },
            $minContentHeight: v11 => { this.minContentHeight = v11; }
          }, undefined, k11, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 782, col: 5 });
          ViewV2.create(m11);
          let i = () => {
            return {
              minContentHeight: this.minContentHeight,
              dialogBuilder: () => {
                this.observeComponentCreation2((o11, p11) => {
                  ForEach.create();
                  const j = r11 => {
                    const s11 = r11;
                    this.observeComponentCreation2((t11, u11) => {
                      If.create();
                      if (s11 === this.textIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.textBuilder.bind(this)();
                        });
                      }
                      else if (s11 === this.checkboxIndex) {
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
                  this.forEachUpdateFunction(o11, [this.textIndex, this.checkboxIndex], j);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          m11.paramsGenerator_ = i;
        }
        else {
          this.updateStateVarsOfChildByElmtId(k11, {
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "ConfirmDialogContentLayout" });
    }
  }
  initialRender() {
    this.observeComponentCreation2((h11, i11) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((b11, c11) => {
        if (c11) {
          let d11 = new CustomDialogContentComponent(this, {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.buildContent();
            },
            minContentHeight: this.minContentHeight,
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            $minContentHeight: g11 => { this.minContentHeight = g11; },
            $fontSizeScale: f11 => { this.fontSizeScale = f11; }
          }, undefined, b11, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 794, col: 5 });
          ViewV2.create(d11);
          let h = () => {
            return {
              primaryTitle: this.title,
              contentBuilder: () => {
                this.buildContent();
              },
              minContentHeight: this.minContentHeight,
              buttons: this.buttons,
              fontSizeScale: this.fontSizeScale
            };
          };
          d11.paramsGenerator_ = h;
        }
        else {
          this.updateStateVarsOfChildByElmtId(b11, {
            primaryTitle: this.title,
            minContentHeight: this.minContentHeight,
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  onWillApplyTheme(a11) {
    this.fontColorWithTheme = a11.colors.fontPrimary;
  }
  updateStateVars(z10) {
    if (z10 === undefined) {
      return;
    }
    if ("title" in z10) {
      this.updateParam("title", z10.title);
    }
    if ("content" in z10) {
      this.updateParam("content", z10.content);
    }
    if ("checkTips" in z10) {
      this.updateParam("checkTips", z10.checkTips);
    }
    if ("isChecked" in z10) {
      this.updateParam("isChecked", z10.isChecked);
    }
    if ("primaryButton" in z10) {
      this.updateParam("primaryButton", z10.primaryButton);
    }
    if ("secondaryButton" in z10) {
      this.updateParam("secondaryButton", z10.secondaryButton);
    }
    if ("onCheckedChange" in z10) {
      this.updateParam("onCheckedChange", z10.onCheckedChange);
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
], ConfirmDialogV2.prototype, "isChecked", void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, "isCheckedInner", void 0);
__decorate([
  Monitor('isChecked')
], ConfirmDialogV2.prototype, "isCheckedMonitor", null);
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
  Local
], ConfirmDialogV2.prototype, "textAlign", void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, "minContentHeight", void 0);
__decorate([
  Computed
], ConfirmDialogV2.prototype, "buttons", null);
export class AlertDialogV2 extends ViewV2 {
  constructor(t10, u10, v10, w10 = -1, x10, y10) {
    super(t10, w10, y10);
    this.initParam("primaryTitle", (u10 && "primaryTitle" in u10) ? u10.primaryTitle : undefined);
    this.initParam("secondaryTitle", (u10 && "secondaryTitle" in u10) ? u10.secondaryTitle : undefined);
    this.initParam("content", (u10 && "content" in u10) ? u10.content : '');
    this.initParam("primaryButton", (u10 && "primaryButton" in u10) ? u10.primaryButton : null);
    this.initParam("secondaryButton", (u10 && "secondaryButton" in u10) ? u10.secondaryButton : null);
    this.textAlign = TextAlign.Center;
    this.contentScroller = new Scroller();
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(t21) {
    this.resetParam("primaryTitle", (t21 && "primaryTitle" in t21) ? t21.primaryTitle : undefined);
    this.resetParam("secondaryTitle", (t21 && "secondaryTitle" in t21) ? t21.secondaryTitle : undefined);
    this.resetParam("content", (t21 && "content" in t21) ? t21.content : '');
    this.resetParam("primaryButton", (t21 && "primaryButton" in t21) ? t21.primaryButton : null);
    this.resetParam("secondaryButton", (t21 && "secondaryButton" in t21) ? t21.secondaryButton : null);
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.resetComputed("buttons");
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let s21 = [];
    if (this.primaryButton) {
      s21.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      s21.push(this.secondaryButton);
    }
    return s21;
  }
  initialRender() {
    this.observeComponentCreation2((r10, s10) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((l10, m10) => {
        if (m10) {
          let n10 = new CustomDialogContentComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight,
            $fontSizeScale: q10 => { this.fontSizeScale = q10; },
            $minContentHeight: p10 => { this.minContentHeight = p10; }
          }, undefined, l10, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 838, col: 5 });
          ViewV2.create(n10);
          let g = () => {
            return {
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.AlertDialogContentBuilder();
              },
              buttons: this.buttons,
              fontSizeScale: this.fontSizeScale,
              minContentHeight: this.minContentHeight
            };
          };
          n10.paramsGenerator_ = g;
        }
        else {
          this.updateStateVarsOfChildByElmtId(l10, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  AlertDialogContentBuilder(d10 = null) {
    this.observeComponentCreation2((j10, k10) => {
      Column.create();
      Column.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
    }, Column);
    this.observeComponentCreation2((h10, i10) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.width('100%');
    }, Scroll);
    this.observeComponentCreation2((e10, f10) => {
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
      Text.onKeyEvent((g10) => {
        if (g10) {
          resolveKeyEvent(g10, this.contentScroller);
        }
      });
    }, Text);
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  onWillApplyTheme(c10) {
    this.fontColorWithTheme = c10.colors.fontPrimary;
  }
  getFontWeight() {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return FontWeight.Medium;
  }
  updateStateVars(a10) {
    if (a10 === undefined) {
      return;
    }
    if ("primaryTitle" in a10) {
      this.updateParam("primaryTitle", a10.primaryTitle);
    }
    if ("secondaryTitle" in a10) {
      this.updateParam("secondaryTitle", a10.secondaryTitle);
    }
    if ("content" in a10) {
      this.updateParam("content", a10.content);
    }
    if ("primaryButton" in a10) {
      this.updateParam("primaryButton", a10.primaryButton);
    }
    if ("secondaryButton" in a10) {
      this.updateParam("secondaryButton", a10.secondaryButton);
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
  Local
], AlertDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], AlertDialogV2.prototype, "minContentHeight", void 0);
__decorate([
  Computed
], AlertDialogV2.prototype, "buttons", null);
export class CustomContentDialogV2 extends ViewV2 {
  constructor(u9, v9, w9, x9 = -1, y9, z9) {
    super(u9, x9, z9);
    this.initParam("primaryTitle", (v9 && "primaryTitle" in v9) ? v9.primaryTitle : undefined);
    this.initParam("secondaryTitle", (v9 && "secondaryTitle" in v9) ? v9.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in v9 ? v9.contentBuilder : undefined;
    this.initParam("contentAreaPadding", (v9 && "contentAreaPadding" in v9) ? v9.contentAreaPadding : undefined);
    this.initParam("buttons", (v9 && "buttons" in v9) ? v9.buttons : undefined);
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(q21) {
    this.resetParam("primaryTitle", (q21 && "primaryTitle" in q21) ? q21.primaryTitle : undefined);
    this.resetParam("secondaryTitle", (q21 && "secondaryTitle" in q21) ? q21.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in q21 ? q21.contentBuilder : undefined;
    this.resetParam("contentAreaPadding", (q21 && "contentAreaPadding" in q21) ? q21.contentAreaPadding : undefined);
    this.resetParam("buttons", (q21 && "buttons" in q21) ? q21.buttons : undefined);
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
  }
  initialRender() {
    this.observeComponentCreation2((s9, t9) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((m9, n9) => {
        if (n9) {
          let o9 = new CustomDialogContentComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              if (typeof this.contentBuilder === 'function') {
                this.contentBuilder();
              }
            },
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight,
            $fontSizeScale: r9 => { this.fontSizeScale = r9; },
            $minContentHeight: q9 => { this.minContentHeight = q9; }
          }, undefined, m9, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 901, col: 5 });
          ViewV2.create(o9);
          let f = () => {
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
              fontSizeScale: this.fontSizeScale,
              minContentHeight: this.minContentHeight
            };
          };
          o9.paramsGenerator_ = f;
        }
        else {
          this.updateStateVarsOfChildByElmtId(m9, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
  }
  updateStateVars(l9) {
    if (l9 === undefined) {
      return;
    }
    if ("primaryTitle" in l9) {
      this.updateParam("primaryTitle", l9.primaryTitle);
    }
    if ("secondaryTitle" in l9) {
      this.updateParam("secondaryTitle", l9.secondaryTitle);
    }
    if ("contentAreaPadding" in l9) {
      this.updateParam("contentAreaPadding", l9.contentAreaPadding);
    }
    if ("buttons" in l9) {
      this.updateParam("buttons", l9.buttons);
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
  Local
], CustomContentDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], CustomContentDialogV2.prototype, "minContentHeight", void 0);
class CustomDialogLayout extends ViewV2 {
  constructor(f9, g9, h9, i9 = -1, j9, k9) {
    super(f9, i9, k9);
    this.initParam("titleHeight", (g9 && "titleHeight" in g9) ? g9.titleHeight : 0);
    this.$titleHeight = "$titleHeight" in g9 ? g9.$titleHeight : undefined;
    this.initParam("buttonHeight", (g9 && "buttonHeight" in g9) ? g9.buttonHeight : 0);
    this.$buttonHeight = "$buttonHeight" in g9 ? g9.$buttonHeight : undefined;
    this.initParam("titleMinHeight", (g9 && "titleMinHeight" in g9) ? g9.titleMinHeight : 0);
    this.dialogBuilder = "dialogBuilder" in g9 ? g9.dialogBuilder : this.doNothingBuilder;
    this.titleIndex = 0;
    this.contentIndex = 1;
    this.buttonIndex = 2;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(o21) {
    this.resetParam("titleHeight", (o21 && "titleHeight" in o21) ? o21.titleHeight : 0);
    this.$titleHeight = "$titleHeight" in o21 ? o21.$titleHeight : undefined;
    this.resetParam("buttonHeight", (o21 && "buttonHeight" in o21) ? o21.buttonHeight : 0);
    this.$buttonHeight = "$buttonHeight" in o21 ? o21.$buttonHeight : undefined;
    this.resetParam("titleMinHeight", (o21 && "titleMinHeight" in o21) ? o21.titleMinHeight : 0);
    this.dialogBuilder = "dialogBuilder" in o21 ? o21.dialogBuilder : this.doNothingBuilder;
  }
  doNothingBuilder(e9 = null) {
  }
  ;
  onPlaceChildren(x8, y8, z8) {
    let a9 = 0;
    let b9 = 0;
    for (let c9 = 0; c9 < y8.length; c9++) {
      let d9 = y8[c9];
      d9.layout({ x: a9, y: b9 });
      b9 += d9.measureResult.height;
    }
  }
  onMeasureSize(j8, k8, l8) {
    let m8 = { width: Number(l8.maxWidth), height: 0 };
    let n8 = 3;
    if (k8.length < n8) {
      return m8;
    }
    let o8 = 0;
    let p8 = k8[this.titleIndex];
    let q8 = {
      maxWidth: l8.maxWidth,
      minHeight: this.titleMinHeight,
      maxHeight: l8.maxHeight
    };
    let r8 = p8.measure(q8);
    this.$titleHeight?.(r8.height);
    o8 += r8.height;
    let s8 = k8[this.buttonIndex];
    let t8 = s8.measure(l8);
    this.$buttonHeight?.(t8.height);
    o8 += t8.height;
    let u8 = k8[this.contentIndex];
    let v8 = {
      maxWidth: l8.maxWidth,
      maxHeight: Number(l8.maxHeight) - o8
    };
    let w8 = u8.measure(v8);
    o8 += w8.height;
    m8.height = o8;
    return m8;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(i8) {
    if (i8 === undefined) {
      return;
    }
    if ("titleHeight" in i8) {
      this.updateParam("titleHeight", i8.titleHeight);
    }
    if ("buttonHeight" in i8) {
      this.updateParam("buttonHeight", i8.buttonHeight);
    }
    if ("titleMinHeight" in i8) {
      this.updateParam("titleMinHeight", i8.titleMinHeight);
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
  constructor(c8, d8, e8, f8 = -1, g8, h8) {
    super(c8, f8, h8);
    this.initParam("primaryTitle", (d8 && "primaryTitle" in d8) ? d8.primaryTitle : undefined);
    this.initParam("secondaryTitle", (d8 && "secondaryTitle" in d8) ? d8.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in d8 ? d8.contentBuilder : this.defaultContentBuilder;
    this.initParam("buttons", (d8 && "buttons" in d8) ? d8.buttons : undefined);
    this.initParam("contentAreaPadding", (d8 && "contentAreaPadding" in d8) ? d8.contentAreaPadding : undefined);
    this.initParam("minContentHeight", (d8 && "minContentHeight" in d8) ? d8.minContentHeight : undefined);
    this.$minContentHeight = "$minContentHeight" in d8 ? d8.$minContentHeight : undefined;
    this.keyIndex = 0;
    this.titleHeight = 0;
    this.buttonHeight = 0;
    this.contentMaxHeight = '100%';
    this.initParam("fontSizeScale", (d8 && "fontSizeScale" in d8) ? d8.fontSizeScale : -1);
    this.$fontSizeScale = "$fontSizeScale" in d8 ? d8.$fontSizeScale : undefined;
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
  resetStateVarsOnReuse(n21) {
    this.resetParam("primaryTitle", (n21 && "primaryTitle" in n21) ? n21.primaryTitle : undefined);
    this.resetParam("secondaryTitle", (n21 && "secondaryTitle" in n21) ? n21.secondaryTitle : undefined);
    this.contentBuilder = "contentBuilder" in n21 ? n21.contentBuilder : this.defaultContentBuilder;
    this.resetParam("buttons", (n21 && "buttons" in n21) ? n21.buttons : undefined);
    this.resetParam("contentAreaPadding", (n21 && "contentAreaPadding" in n21) ? n21.contentAreaPadding : undefined);
    this.resetParam("minContentHeight", (n21 && "minContentHeight" in n21) ? n21.minContentHeight : undefined);
    this.$minContentHeight = "$minContentHeight" in n21 ? n21.$minContentHeight : undefined;
    this.titleHeight = 0;
    this.buttonHeight = 0;
    this.contentMaxHeight = '100%';
    this.resetParam("fontSizeScale", (n21 && "fontSizeScale" in n21) ? n21.fontSizeScale : -1);
    this.$fontSizeScale = "$fontSizeScale" in n21 ? n21.$fontSizeScale : undefined;
    this.customStyle = undefined;
    this.buttonMaxFontSize = `${BODY_L}fp`;
    this.buttonMinFontSize = 9;
    this.primaryTitleFontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.secondaryTitleFontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.titleTextAlign = TextAlign.Center;
    this.isButtonVertical = false;
  }
  defaultContentBuilder(b8 = null) {
  }
  initialRender() {
    this.observeComponentCreation2((z7, a8) => {
      Scroll.create();
      Scroll.backgroundColor(Color.Transparent);
    }, Scroll);
    this.observeComponentCreation2((x7, y7) => {
      Column.create();
      Column.constraintSize({ maxHeight: this.contentMaxHeight });
      Column.backgroundBlurStyle(this.customStyle ? BlurStyle.Thick : BlurStyle.NONE);
      Column.borderRadius(this.customStyle ? { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_dialog'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : 0);
      Column.margin(this.customStyle ? {
        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_dialog_margin_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_dialog_margin_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
        bottom: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.ohos_id_dialog_margin_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
      } : { left: 0, right: 0, bottom: 0 });
      Column.backgroundColor(this.customStyle ? { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_dialog_bg'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" } : Color.Transparent);
    }, Column);
    {
      this.observeComponentCreation2((y6, z6) => {
        if (z6) {
          let a7 = new CustomDialogLayout(this, {
            buttonHeight: this.buttonHeight,
            titleHeight: this.titleHeight,
            titleMinHeight: this.getTitleAreaMinHeight(),
            dialogBuilder: () => {
              this.observeComponentCreation2((o7, p7) => {
                ForEach.create();
                const e = r7 => {
                  const s7 = r7;
                  this.observeComponentCreation2((t7, u7) => {
                    If.create();
                    if (s7 === this.titleIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.titleBuilder.bind(this)();
                      });
                    }
                    else if (s7 === this.contentIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.observeComponentCreation2((v7, w7) => {
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
                this.forEachUpdateFunction(o7, [this.titleIndex, this.contentIndex, this.buttonIndex], e);
              }, ForEach);
              ForEach.pop();
            },
            $buttonHeight: n7 => { this.buttonHeight = n7; },
            $titleHeight: m7 => { this.titleHeight = m7; }
          }, undefined, y6, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 1038, col: 9 });
          ViewV2.create(a7);
          let c = () => {
            return {
              buttonHeight: this.buttonHeight,
              titleHeight: this.titleHeight,
              titleMinHeight: this.getTitleAreaMinHeight(),
              dialogBuilder: () => {
                this.observeComponentCreation2((c7, d7) => {
                  ForEach.create();
                  const d = f7 => {
                    const g7 = f7;
                    this.observeComponentCreation2((h7, i7) => {
                      If.create();
                      if (g7 === this.titleIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.titleBuilder.bind(this)();
                        });
                      }
                      else if (g7 === this.contentIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.observeComponentCreation2((j7, k7) => {
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
                  this.forEachUpdateFunction(c7, [this.titleIndex, this.contentIndex, this.buttonIndex], d);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          a7.paramsGenerator_ = c;
        }
        else {
          this.updateStateVarsOfChildByElmtId(y6, {
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
  onMeasureSize(p6, q6, r6) {
    let s6 = { width: p6.width, height: p6.height };
    let t6 = Number(r6.maxWidth);
    let u6 = Number(r6.maxHeight);
    this.$fontSizeScale?.(this.updateFontScale());
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(t6 - BUTTON_HORIZONTAL_MARGIN * 2);
    let v6 = 0;
    q6.forEach((w6) => {
      this.contentMaxHeight = '100%';
      let x6 = w6.measure(r6);
      if (u6 - this.buttonHeight - this.titleHeight < this.minContentHeight) {
        this.contentMaxHeight = MAX_CONTENT_HEIGHT;
        x6 = w6.measure(r6);
      }
      v6 += x6.height;
    });
    s6.height = v6;
    s6.width = t6;
    return s6;
  }
  onWillApplyTheme(o6) {
    this.primaryTitleFontColorWithTheme = o6.colors.fontPrimary;
    this.secondaryTitleFontColorWithTheme = o6.colors.fontSecondary;
  }
  aboutToAppear() {
    let n6 = this.getUIContext();
    this.isFollowingSystemFontScale = n6.isFollowingSystemFontScale();
    this.appMaxFontScale = n6.getMaxFontScale();
    this.$fontSizeScale?.(this.updateFontScale());
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
      let l6 = this.getUIContext();
      let m6 = l6.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(m6, this.appMaxFontScale);
    }
    catch (i6) {
      let j6 = i6.code;
      let k6 = i6.message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${j6}, message: ${k6}`);
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
  titleBuilder(t5 = null) {
    this.observeComponentCreation2((g6, h6) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
    }, Column);
    this.observeComponentCreation2((e6, f6) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((c6, d6) => {
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
    this.observeComponentCreation2((y5, z5) => {
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a6, b6) => {
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
    this.observeComponentCreation2((w5, x5) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((u5, v5) => {
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
    let s5 = ALERT_TITLE_ALIGNMENT;
    if (s5 === TextAlign.Start) {
      this.titleTextAlign = TextAlign.Start;
    }
    else if (s5 === TextAlign.Center) {
      this.titleTextAlign = TextAlign.Center;
    }
    else if (s5 === TextAlign.End) {
      this.titleTextAlign = TextAlign.End;
    }
    else if (s5 === TextAlign.JUSTIFY) {
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
  ButtonBuilder(l5 = null) {
    this.observeComponentCreation2((q5, r5) => {
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
    }, Column);
    this.observeComponentCreation2((m5, n5) => {
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((o5, p5) => {
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
  buildSingleButton(z4, a5 = null) {
    this.observeComponentCreation2((b5, c5) => {
      If.create();
      if (this.isNewPropertiesHighPriority(z4)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((j5, k5) => {
            Button.createWithLabel(z4.content);
            __Button__setButtonProperties(z4, this.buttons, this.getDialogController());
            Button.role(z4.role ?? ButtonRole.NORMAL);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else if (z4.background !== undefined && z4.fontColor !== undefined) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((h5, i5) => {
            Button.createWithLabel(z4.content);
            __Button__setButtonProperties(z4, this.buttons, this.getDialogController());
            Button.backgroundColor(z4.background.color);
            Button.fontColor(z4.fontColor.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else if (z4.background !== undefined) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((f5, g5) => {
            Button.createWithLabel(z4.content);
            __Button__setButtonProperties(z4, this.buttons, this.getDialogController());
            Button.backgroundColor(z4.background.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(3, () => {
          this.observeComponentCreation2((d5, e5) => {
            Button.createWithLabel(z4.content);
            __Button__setButtonProperties(z4, this.buttons, this.getDialogController());
            Button.fontColor(z4?.fontColor?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
    }, If);
    If.pop();
  }
  buildHorizontalAlignButtons(o4 = null) {
    this.observeComponentCreation2((p4, q4) => {
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((x4, y4) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(this.buttons[0]);
          this.observeComponentCreation2((r4, s4) => {
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((v4, w4) => {
                  Row.create();
                  Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                  Row.justifyContent(FlexAlign.Center);
                }, Row);
                this.observeComponentCreation2((t4, u4) => {
                  Divider.create();
                  Divider.width({ "id": -1, "type": 10002, params: ['sys.float.alert_divider_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Divider.height({ "id": -1, "type": 10002, params: ['sys.float.alert_divider_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                  Divider.color(this.getDividerColor());
                  Divider.vertical(true);
                }, Divider);
                Row.pop();
                this.buildSingleButton.bind(this)(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1]);
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
  buildVerticalAlignButtons(c4 = null) {
    this.observeComponentCreation2((d4, e4) => {
      If.create();
      if (this.buttons) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((m4, n4) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((f4, g4) => {
            ForEach.create();
            const b = (j4, k4) => {
              const l4 = j4;
              this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                HORIZON_BUTTON_MAX_COUNT - k4 - 1 : k4);
            };
            this.forEachUpdateFunction(f4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), b, (i4) => i4.content.toString(), true, false);
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
  isNewPropertiesHighPriority(b4) {
    if (b4.role === ButtonRole.ERROR) {
      return true;
    }
    if (b4.buttonStyle !== undefined &&
      b4.buttonStyle !== ALERT_BUTTON_STYLE) {
      return true;
    }
    if (b4.background === undefined && b4.fontColor === undefined) {
      return true;
    }
    return false;
  }
  buildButtonWithDivider(r3, s3 = null) {
    this.observeComponentCreation2((t3, u3) => {
      If.create();
      if (this.buttons && this.buttons[r3]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((z3, a4) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(this.buttons[r3]);
          Row.pop();
          this.observeComponentCreation2((v3, w3) => {
            If.create();
            if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - r3 - 1 : r3) <
              Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((x3, y3) => {
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
  isVerticalAlignButton(m3) {
    if (this.buttons) {
      if (this.buttons.length === 1) {
        return false;
      }
      if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
        return true;
      }
      let n3 = false;
      let o3 = vp2px(m3 / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
        BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
      this.buttons.forEach((p3) => {
        let q3 = measure.measureTextSize({
          textContent: p3.content,
          fontSize: this.buttonMaxFontSize
        });
        if (Number(q3.width) > o3) {
          n3 = true;
        }
      });
      return n3;
    }
    return false;
  }
  updateStateVars(l3) {
    if (l3 === undefined) {
      return;
    }
    if ("primaryTitle" in l3) {
      this.updateParam("primaryTitle", l3.primaryTitle);
    }
    if ("secondaryTitle" in l3) {
      this.updateParam("secondaryTitle", l3.secondaryTitle);
    }
    if ("buttons" in l3) {
      this.updateParam("buttons", l3.buttons);
    }
    if ("contentAreaPadding" in l3) {
      this.updateParam("contentAreaPadding", l3.contentAreaPadding);
    }
    if ("minContentHeight" in l3) {
      this.updateParam("minContentHeight", l3.minContentHeight);
    }
    if ("fontSizeScale" in l3) {
      this.updateParam("fontSizeScale", l3.fontSizeScale);
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
  Param
], CustomDialogContentComponent.prototype, "fontSizeScale", void 0);
__decorate([
  Event
], CustomDialogContentComponent.prototype, "$fontSizeScale", void 0);
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
function __Button__setButtonProperties(i3, j3, m20) {
  Button.onKeyEvent((k3) => {
    if (!k3) {
      return;
    }
    if ((k3.keyCode === KeyCode.KEYCODE_SPACE || k3.keyCode === KeyCode.KEYCODE_ENTER) &&
      k3.type === KeyType.Down) {
      if (i3.action) {
        i3.action();
      }
      m20?.close();
      k3.stopPropagation();
    }
  });
  Button.onClick(() => {
    if (i3.action) {
      i3.action();
    }
    m20?.close();
  });
  Button.defaultFocus(i3.defaultFocus ? true : isHasDefaultFocus(j3) ? false : true);
  Button.buttonStyle(i3.buttonStyle ?? ALERT_BUTTON_STYLE);
  Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
  Button.type(ButtonType.ROUNDED_RECTANGLE);
}
function isHasDefaultFocus(c3) {
  try {
    let g3 = false;
    c3?.forEach((h3) => {
      if (h3.defaultFocus) {
        g3 = true;
      }
    });
    return g3;
  }
  catch (d3) {
    let e3 = d3.code;
    let f3 = d3.message;
    hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${e3}, message: ${f3}`);
    return false;
  }
}
function getNumberByResourceId(v2, w2, x2) {
  try {
    let b3 = resourceManager.getSystemResourceManager().getNumber(v2);
    if (b3 > 0 || x2) {
      return b3;
    }
    else {
      return w2;
    }
  }
  catch (y2) {
    let z2 = y2.code;
    let a3 = y2.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${z2}, message: ${a3}`);
    return w2;
  }
}
function getEnumNumberByResourceId(p2, q2) {
  try {
    let u2 = getContext().resourceManager.getNumber(p2);
    if (u2 > 0) {
      return u2;
    }
    else {
      return q2;
    }
  }
  catch (r2) {
    let s2 = r2.code;
    let t2 = r2.message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${s2}, message: ${t2}`);
    return q2;
  }
}
function getAccessibilityText(i2, j2) {
  try {
    let n2 = getContext().resourceManager.getStringSync(125833934);
    let o2 = '';
    if (typeof i2 === 'string') {
      o2 = i2;
    }
    else {
      o2 = getContext().resourceManager.getStringSync(i2);
    }
    return j2 ? `${n2},${o2}` : o2;
  }
  catch (k2) {
    let l2 = k2.code;
    let m2 = k2.message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${l2}, message: ${m2}`);
    return '';
  }
}
function resolveKeyEvent(a2, b2) {
  if (a2.type === IGNORE_KEY_EVENT_TYPE) {
    return;
  }
  if (a2.keyCode === KEYCODE_UP) {
    b2.scrollPage({ next: false });
    a2.stopPropagation();
  }
  else if (a2.keyCode === KEYCODE_DOWN) {
    if (b2.isAtEnd()) {
      return;
    }
    else {
      b2.scrollPage({ next: true });
      a2.stopPropagation();
    }
  }
}
function getCheckTipsAccessibilityText(r1, s1) {
  try {
    let w1 = getContext().resourceManager.getStringSync(125833934);
    let x1 = getContext().resourceManager.getStringSync(125833935);
    let y1 = getContext().resourceManager.getStringSync(125834354);
    let z1 = '';
    if (typeof r1 === 'string') {
      z1 = r1;
    }
    else {
      z1 = getContext().resourceManager.getStringSync(r1);
    }
    return s1 ? `${w1},${z1},${y1}` :
      `${x1},${z1},${y1}`;
  }
  catch (t1) {
    let u1 = t1.code;
    let v1 = t1.message;
    hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${u1}, message: ${v1}`);
    return '';
  }
}
export class LoadingDialogV2 extends ViewV2 {
  constructor(l1, m1, n1, o1 = -1, p1, q1) {
    super(l1, o1, q1);
    this.initParam("content", (m1 && "content" in m1) ? m1.content : '');
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.loadingProgressIconColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(c20) {
    this.resetParam("content", (c20 && "content" in c20) ? c20.content : '');
    this.fontColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.loadingProgressIconColorWithTheme = { "id": -1, "type": 10001, params: ['sys.color.icon_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
  }
  initialRender() {
    this.observeComponentCreation2((j1, k1) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((h1, i1) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((b1, c1) => {
        if (c1) {
          let d1 = new CustomDialogContentComponent(this, {
            contentBuilder: () => {
              this.contentBuilder();
            },
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight,
            $fontSizeScale: g1 => { this.fontSizeScale = g1; },
            $minContentHeight: f1 => { this.minContentHeight = f1; }
          }, undefined, b1, () => { }, { page: "library/src/main/ets/components/dialog.ets", line: 1641, col: 7 });
          ViewV2.create(d1);
          let a = () => {
            return {
              contentBuilder: () => {
                this.contentBuilder();
              },
              fontSizeScale: this.fontSizeScale,
              minContentHeight: this.minContentHeight
            };
          };
          d1.paramsGenerator_ = a;
        }
        else {
          this.updateStateVarsOfChildByElmtId(b1, {
            fontSizeScale: this.fontSizeScale,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: "CustomDialogContentComponent" });
    }
    __Common__.pop();
    Column.pop();
  }
  contentBuilder(s = null) {
    this.observeComponentCreation2((z, a1) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((x, y) => {
      Row.create();
      Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
    }, Row);
    this.observeComponentCreation2((v, w) => {
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
    this.observeComponentCreation2((t, u) => {
      LoadingProgress.create();
      LoadingProgress.color(this.loadingProgressIconColorWithTheme);
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) });
    }, LoadingProgress);
    Row.pop();
    Column.pop();
  }
  onWillApplyTheme(r) {
    this.fontColorWithTheme = r.colors.fontPrimary;
    this.loadingProgressIconColorWithTheme = r.colors.iconSecondary;
  }
  updateStateVars(q) {
    if (q === undefined) {
      return;
    }
    if ("content" in q) {
      this.updateParam("content", q.content);
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
  Local
], LoadingDialogV2.prototype, "fontSizeScale", void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, "minContentHeight", void 0);
export class PopoverDialogV2 extends ViewV2 {
  constructor(k14, s14, w14, x14 = -1, y14, p19) {
    super(k14, x14, p19);
    this.initParam("visible", (s14 && "visible" in s14) ? s14.visible : false);
    this.$visible = "$visible" in s14 ? s14.$visible : () => { };
    this.initParam("popover", (s14 && "popover" in s14) ? s14.popover : {
      builder: undefined
    });
    this.targetBuilder = "targetBuilder" in s14 ? s14.targetBuilder : undefined;
    this.dialogWidth = this.popover?.width;
    this.finalizeConstruction();
  }
  resetStateVarsOnReuse(y11) {
    this.resetParam("visible", (y11 && "visible" in y11) ? y11.visible : false);
    this.$visible = "$visible" in y11 ? y11.$visible : () => { };
    this.resetParam("popover", (y11 && "popover" in y11) ? y11.popover : {
      builder: undefined
    });
    this.targetBuilder = "targetBuilder" in y11 ? y11.targetBuilder : undefined;
    this.dialogWidth = this.popover?.width;
  }
  emptyBuilder(q11 = null) {
  }
  aboutToAppear() {
    if (this.targetBuilder === undefined || this.targetBuilder === null) {
      this.targetBuilder = this.emptyBuilder;
    }
  }
  initialRender() {
    this.observeComponentCreation2((h4, b7) => {
      Column.create();
      Column.onClick(() => {
        try {
          let e11 = display.getDefaultDisplaySync();
          let n11 = px2vp(e11.width);
          if (n11 - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
            this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
          }
          else {
            this.popover.width = this.dialogWidth;
          }
          this.$visible?.(!this.visible);
        }
        catch (q7) {
          let p9 = q7.code;
          let o10 = q7.message;
          hilog.error(0x3900, 'Ace', `dialog popup error, code: ${p9}, message: ${o10}`);
        }
      });
      Column.bindPopup(this.visible, {
        builder: this.popover?.builder,
        placement: this.popover?.placement ?? Placement.Bottom,
        popupColor: this.popover?.popupColor,
        enableArrow: this.popover?.enableArrow ?? true,
        autoCancel: this.popover?.autoCancel,
        onStateChange: this.popover?.onStateChange ?? ((e7) => {
          if (!e7.isVisible) {
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
  updateStateVars(e1) {
    if (e1 === undefined) {
      return;
    }
    if ("visible" in e1) {
      this.updateParam("visible", e1.visible);
    }
    if ("popover" in e1) {
      this.updateParam("popover", e1.popover);
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
export default { TipsDialogV2, ConfirmDialogV2, SelectDialogV2, AlertDialogV2, LoadingDialogV2, CustomContentDialogV2, PopoverDialogV2, AdvancedDialogV2Button };