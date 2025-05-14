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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
  var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
  if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') r = Reflect.decorate(decorators, target, key, desc);
  else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
  return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
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
// 'sys.float.alert_container_max_width'
const MAX_DIALOG_WIDTH = getNumberByResourceId(125831042, 400);
// 'sys.float.alert_right_padding_horizontal'
const BUTTON_HORIZONTAL_MARGIN = getNumberByResourceId(125831054, 16);
// 'sys.float.padding_level8'
const BUTTON_HORIZONTAL_PADDING = getNumberByResourceId(125830927, 16);
// 'sys.float.padding_level4'
const CHECK_BOX_MARGIN_END = getNumberByResourceId(125830923, 8);
// 'sys.float.alert_button_horizontal_space'
const BUTTON_HORIZONTAL_SPACE = getNumberByResourceId(125831051, 8);
// 'sys.float.Body_L'
const BODY_L = getNumberByResourceId(125830970, 16);
// 'sys.float.Body_M'
const BODY_M = getNumberByResourceId(125830971, 14);
// 'sys.float.Body_S'
const BODY_S = getNumberByResourceId(125830972, 12);
// 'sys.float.Title_S'
const TITLE_S = getNumberByResourceId(125830966, 20);
// 'sys.float.Subtitle_S'
const SUBTITLE_S = getNumberByResourceId(125830969, 14);
// 'sys.float.padding_level8'
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);
// 'sys.float.dialog_divider_show'
const DIALOG_DIVIDER_SHOW = getNumberByResourceId(125831202, 1, true);
// 'sys.float.alert_button_style'
const ALERT_BUTTON_STYLE = getNumberByResourceId(125831085, 2, true);
// 'sys.float.alert_title_alignment'
const ALERT_TITLE_ALIGNMENT = getEnumNumberByResourceId(125831126, 1);
const SCROLL_BAR_OFFSET = 20;
const SELECT_DIALOG_SCROLL_BAR_OFFSET = 4;
let AdvancedDialogV2Button = class AdvancedDialogV2Button {
  constructor(options) {
    this.content = '';
    this.content = options.content;
    this.action = options.action;
    this.background = options.background;
    this.fontColor = options.fontColor;
    this.buttonStyle = options.buttonStyle;
    this.role = options.role;
    this.defaultFocus = options.defaultFocus;
    this.enabled = options.enabled;
  }
  ;
};
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'content', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'action', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'background', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'fontColor', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'buttonStyle', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'role', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'defaultFocus', void 0);
__decorate([
  Trace
], AdvancedDialogV2Button.prototype, 'enabled', void 0);
AdvancedDialogV2Button = __decorate([
  ObservedV2
], AdvancedDialogV2Button);
export { AdvancedDialogV2Button };
export class TipsDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('imageRes', (params && 'imageRes' in params) ? params.imageRes : undefined);
    this.initParam('imageSize', (params && 'imageSize' in params) ? params.imageSize : { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE });
    this.initParam('imageBorderColor', (params && 'imageBorderColor' in params) ? params.imageBorderColor : undefined);
    this.initParam('imageBorderWidth', (params && 'imageBorderWidth' in params) ? params.imageBorderWidth : undefined);
    this.initParam('title', (params && 'title' in params) ? params.title : null);
    this.initParam('content', (params && 'content' in params) ? params.content : null);
    this.initParam('onCheckedChange', (params && 'onCheckedChange' in params) ? params.onCheckedChange : undefined);
    this.initParam('checkTips', (params && 'checkTips' in params) ? params.checkTips : null);
    this.initParam('checked', (params && 'checked' in params) ? params.checked : false);
    this.checkedInner = false;
    this.initParam('primaryButton', (params && 'primaryButton' in params) ? params.primaryButton : null);
    this.initParam('secondaryButton', (params && 'secondaryButton' in params) ? params.secondaryButton : null);
    this.marginOffset = 0 - PADDING_LEVEL_8;
    this.contentScroller = new Scroller();
    this.fontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.fontSizeScale = 1;
    this.minContentHeight = 160;
    this.imageIndex = 0;
    this.textIndex = 1;
    this.checkBoxIndex = 2;
    this.appMaxFontScale = 3.2;
    this.finalizeConstruction();
  }
  checkedChangeMonitor(monitor) {
    this.checkedInner = monitor.value('checked')?.now;
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let buttons = [];
    if (this.primaryButton) {
      buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      buttons.push(this.secondaryButton);
    }
    return buttons;
  }
  onWillApplyTheme(theme) {
    this.fontColorWithTheme = theme.colors.fontPrimary;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogContentComponent(this, {
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            minContentHeight: this.minContentHeight,
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 182, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
            return {
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              minContentHeight: this.minContentHeight
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            buttons: this.buttons,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    __Common__.pop();
  }
  contentBuilder(parent = null) {
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new TipsDialogContentLayout(this, {
            title: this.title,
            content: this.content,
            checkTips: this.checkTips,
            minContentHeight: this.minContentHeight,
            dialogBuilder: () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                ForEach.create();
                const forEachItemGenFunction = _item => {
                  const index = _item;
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index === this.imageIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.imagePart.bind(this)();
                      });
                    }
                    else if (index === this.textIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                          Column.create();
                          Column.padding({ top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
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
                this.forEachUpdateFunction(elmtId, [this.imageIndex, this.textIndex, this.checkBoxIndex], forEachItemGenFunction);
              }, ForEach);
              ForEach.pop();
            },
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 193, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
            return {
              title: this.title,
              content: this.content,
              checkTips: this.checkTips,
              minContentHeight: this.minContentHeight,
              dialogBuilder: () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  ForEach.create();
                  const forEachItemGenFunction = _item => {
                    const index = _item;
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (index === this.imageIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.imagePart.bind(this)();
                        });
                      }
                      else if (index === this.textIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Column.create();
                            Column.padding({ top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
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
                  this.forEachUpdateFunction(elmtId, [this.imageIndex, this.textIndex, this.checkBoxIndex], forEachItemGenFunction);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            title: this.title,
            content: this.content,
            checkTips: this.checkTips,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'TipsDialogContentLayout' });
    }
  }
  checkBoxPart(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.accessibilityGroup(true);
      Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.checkedInner));
      Row.accessibilityDescription(this.checkedInner ? { 'id': -1, 'type': 10003, params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10003, params: ['sys.string.slider_accessibility_unselectedDesc'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Row.onClick(() => {
        this.checkedInner = !this.checkedInner;
        try {
          let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.checkedInner ? getContext().resourceManager.getStringSync(125833934) :
            getContext().resourceManager.getStringSync(125833935)
          });
          accessibility.sendAccessibilityEvent(eventInfo);
        }
        catch (exception) {
          let code = exception.code;
          let message = exception.message;
          hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
        }
      });
      Row.padding({ top: 8, bottom: 8 });
      Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.checkTips !== null && this.checkTips !== undefined) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Checkbox.create({ name: '', group: 'checkboxGroup' });
            Checkbox.select(this.checkedInner);
            Checkbox.onChange((checked) => {
              this.checkedInner = checked;
              this.onCheckedChange?.(checked);
            });
            Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
          }, Checkbox);
          Checkbox.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
  imagePart(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Image.create(this.imageRes);
      Image.objectFit(ImageFit.Contain);
      Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Image.constraintSize({
        maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE,
        maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE
      });
      Image.outline({
        width: `${lengthMetricsToPX(this.imageBorderWidth)}px`,
        radius: `${lengthMetricsToPX(LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' })) +
        lengthMetricsToPX(this.imageBorderWidth)}px`,
        color: this.imageBorderColor?.color
      });
    }, Image);
    Column.pop();
  }
  textPart(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
    }, Scroll);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) });
      Column.width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`);
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.title !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.padding({ bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.content !== null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            Text.onKeyEvent((event) => {
              if (event) {
                resolveKeyEvent(event, this.contentScroller);
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
    let uiContext = this.getUIContext();
    this.appMaxFontScale = uiContext.getMaxFontScale();
    this.checkedInner = this.checked;
  }
  getContentFontSize() {
    return BODY_L + 'fp';
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('imageRes' in params) {
      this.updateParam('imageRes', params.imageRes);
    }
    if ('imageSize' in params) {
      this.updateParam('imageSize', params.imageSize);
    }
    if ('imageBorderColor' in params) {
      this.updateParam('imageBorderColor', params.imageBorderColor);
    }
    if ('imageBorderWidth' in params) {
      this.updateParam('imageBorderWidth', params.imageBorderWidth);
    }
    if ('title' in params) {
      this.updateParam('title', params.title);
    }
    if ('content' in params) {
      this.updateParam('content', params.content);
    }
    if ('onCheckedChange' in params) {
      this.updateParam('onCheckedChange', params.onCheckedChange);
    }
    if ('checkTips' in params) {
      this.updateParam('checkTips', params.checkTips);
    }
    if ('checked' in params) {
      this.updateParam('checked', params.checked);
    }
    if ('primaryButton' in params) {
      this.updateParam('primaryButton', params.primaryButton);
    }
    if ('secondaryButton' in params) {
      this.updateParam('secondaryButton', params.secondaryButton);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], TipsDialogV2.prototype, 'imageRes', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'imageSize', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'imageBorderColor', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'imageBorderWidth', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'title', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'content', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'onCheckedChange', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'checkTips', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'checked', void 0);
__decorate([
  Local
], TipsDialogV2.prototype, 'checkedInner', void 0);
__decorate([
  Monitor('checked')
], TipsDialogV2.prototype, 'checkedChangeMonitor', null);
__decorate([
  Computed
], TipsDialogV2.prototype, 'buttons', null);
__decorate([
  Param
], TipsDialogV2.prototype, 'primaryButton', void 0);
__decorate([
  Param
], TipsDialogV2.prototype, 'secondaryButton', void 0);
__decorate([
  Local
], TipsDialogV2.prototype, 'fontColorWithTheme', void 0);
__decorate([
  Provider()
], TipsDialogV2.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], TipsDialogV2.prototype, 'minContentHeight', void 0);
class TipsDialogContentLayout extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('title', (params && 'title' in params) ? params.title : null);
    this.initParam('content', (params && 'content' in params) ? params.content : null);
    this.initParam('checkTips', (params && 'checkTips' in params) ? params.checkTips : null);
    this.initParam('minContentHeight', (params && 'minContentHeight' in params) ? params.minContentHeight : 0);
    this.$minContentHeight = '$minContentHeight' in params ? params.$minContentHeight : undefined;
    this.dialogBuilder = 'dialogBuilder' in params ? params.dialogBuilder : this.doNothingBuilder;
    this.imageIndex = 0;
    this.textIndex = 1;
    this.checkBoxIndex = 2;
    this.childrenSize = 3;
    this.finalizeConstruction();
  }
  doNothingBuilder(parent = null) {
  }
  ;
  onPlaceChildren(selfLayoutInfo, children, constraint) {
    let currentX = 0;
    let currentY = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }
  onMeasureSize(selfLayoutInfo, children, constraint) {
    let sizeResult = { width: Number(constraint.maxWidth), height: 0 };
    if (children.length < this.childrenSize) {
      return sizeResult;
    }
    let height = 0;
    let checkBoxHeight = 0;
    if (this.checkTips !== null && this.checkTips !== undefined) {
      let checkboxChild = children[this.checkBoxIndex];
      let checkboxConstraint = {
        maxWidth: constraint.maxWidth,
        minHeight: CHECKBOX_CONTAINER_HEIGHT,
        maxHeight: constraint.maxHeight
      };
      let checkBoxMeasureResult = checkboxChild.measure(checkboxConstraint);
      checkBoxHeight = checkBoxMeasureResult.height;
      height += checkBoxHeight;
    }
    let imageChild = children[this.imageIndex];
    let textMinHeight = 0;
    if (this.title !== null || this.content !== null) {
      textMinHeight = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
    }
    let imageMaxHeight = Number(constraint.maxHeight) - checkBoxHeight - textMinHeight;
    let imageConstraint = {
      maxWidth: constraint.maxWidth,
      maxHeight: imageMaxHeight
    };
    let imageMeasureResult = imageChild.measure(imageConstraint);
    height += imageMeasureResult.height;
    if (this.title !== null || this.content !== null) {
      let textChild = children[this.textIndex];
      let contentMaxHeight = Number(constraint.maxHeight) - imageMeasureResult.height - checkBoxHeight;
      let contentConstraint = {
        maxWidth: constraint.maxWidth,
        maxHeight: Math.max(contentMaxHeight, TEXT_MIN_HEIGHT)
      };
      let contentMeasureResult = textChild.measure(contentConstraint);
      height += contentMeasureResult.height;
    }
    sizeResult.height = height;
    this.$minContentHeight?.(Math.max(checkBoxHeight + imageMeasureResult.height + textMinHeight, MIN_CONTENT_HEIGHT));
    return sizeResult;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('title' in params) {
      this.updateParam('title', params.title);
    }
    if ('content' in params) {
      this.updateParam('content', params.content);
    }
    if ('checkTips' in params) {
      this.updateParam('checkTips', params.checkTips);
    }
    if ('minContentHeight' in params) {
      this.updateParam('minContentHeight', params.minContentHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], TipsDialogContentLayout.prototype, 'title', void 0);
__decorate([
  Param
], TipsDialogContentLayout.prototype, 'content', void 0);
__decorate([
  Param
], TipsDialogContentLayout.prototype, 'checkTips', void 0);
__decorate([
  Param
], TipsDialogContentLayout.prototype, 'minContentHeight', void 0);
__decorate([
  Event
], TipsDialogContentLayout.prototype, '$minContentHeight', void 0);
export class SelectDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('title', (params && 'title' in params) ? params.title : '');
    this.initParam('content', (params && 'content' in params) ? params.content : '');
    this.initParam('confirm', (params && 'confirm' in params) ? params.confirm : null);
    this.initParam('radioContent', (params && 'radioContent' in params) ? params.radioContent : []);
    this.initParam('selectedIndex', (params && 'selectedIndex' in params) ? params.selectedIndex : -1);
    this.selectedIndexInner = -1;
    this.isFocus = false;
    this.currentFocusIndex = -1;
    this.radioHeight = 0;
    this.itemHeight = 0;
    this.contentBuilder = 'contentBuilder' in params ? params.contentBuilder : this.buildContent;
    this.fontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.dividerColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.comp_divider'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.contentScroller = new Scroller();
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  selectedIndexMonitor(monitor) {
    this.selectedIndexInner = monitor.value('selectedIndex')?.now;
  }
  get buttons() {
    let buttons = [];
    if (this.confirm) {
      buttons.push(this.confirm);
    }
    return buttons;
  }
  get contentPadding() {
    if (!this.title && !this.confirm) {
      return {
        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
      };
    }
    if (!this.title) {
      return {
        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
      };
    }
    else if (!this.confirm) {
      return {
        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
      };
    }
    return {
      left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level0'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
    };
  }
  buildContent(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Scroll.create(this.contentScroller);
      Scroll.scrollBar(BarState.Auto);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.onDidScroll((xOffset, yOffset) => {
        let scrollHeight = (this.itemHeight - this.radioHeight) / 2;
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
            if (yOffset > 0) {
              this.contentScroller.scrollBy(0, scrollHeight);
            }
            else if (yOffset < 0) {
              this.contentScroller.scrollBy(0, 0 - scrollHeight);
            }
          }
          this.isFocus = false;
        }
      });
      Scroll.margin({ end: LengthMetrics.vp(SELECT_DIALOG_SCROLL_BAR_OFFSET) });
    }, Scroll);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.padding({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
            });
            Row.width('100%');
          }, Row);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ForEach.create();
      const forEachItemGenFunction = (_item, index) => {
        const item = _item;
        {
          const itemCreation = (elmtId, isInitialRender) => {
            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
            itemCreation2(elmtId, isInitialRender);
            if (!isInitialRender) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const itemCreation2 = (elmtId, isInitialRender) => {
            ListItem.create(deepRenderFunction, true);
            ListItem.padding({
              left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
              right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
            });
            ListItem.onSizeChange((oldValue, newValue) => {
              this.itemHeight = Number(newValue.height);
            });
          };
          const deepRenderFunction = (elmtId, isInitialRender) => {
            itemCreation(elmtId, isInitialRender);
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Column.create();
              Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
              Column.focusBox({
                margin: { value: -2, unit: LengthUnit.VP }
              });
              Column.accessibilityText(getAccessibilityText(item.title, this.selectedIndexInner === index));
              Column.onClick(() => {
                this.selectedIndexInner = index;
                item.action && item.action();
                this.getDialogController()?.close();
              });
            }, Column);
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Button.createWithChild();
              Button.type(ButtonType.Normal);
              Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
              Button.buttonStyle(ButtonStyleMode.TEXTUAL);
              Button.padding({
                left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
              });
            }, Button);
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Row.create();
              Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
              Row.clip(false);
              Row.padding({ top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }, bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            }, Row);
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Text.create(item.title);
              Text.fontSize(`${BODY_L}fp`);
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor(this.fontColorWithTheme);
              Text.layoutWeight(1);
              Text.direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr);
            }, Text);
            Text.pop();
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
              Radio.checked(this.selectedIndexInner === index);
              Radio.hitTestBehavior(HitTestMode.None);
              Radio.id(String(index));
              Radio.focusable(false);
              Radio.accessibilityLevel('no');
              Radio.visibility(this.selectedIndex === index ? Visibility.Visible : Visibility.Hidden);
              Radio.radioStyle({ uncheckedBorderColor: Color.Transparent });
              Radio.onFocus(() => {
                this.isFocus = true;
                this.currentFocusIndex = index;
                if (index === FIRST_ITEM_INDEX) {
                  this.contentScroller.scrollEdge(Edge.Top);
                }
                else if (index === this.radioContent.length - 1) {
                  this.contentScroller.scrollEdge(Edge.Bottom);
                }
              });
              Radio.onSizeChange((oldValue, newValue) => {
                this.radioHeight = Number(newValue.height);
              });
            }, Radio);
            Row.pop();
            Button.pop();
            this.observeComponentCreation2((elmtId, isInitialRender) => {
              If.create();
              if (index < this.radioContent.length - 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Divider.create();
                    Divider.color(this.dividerColorWithTheme);
                    Divider.padding({
                      left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                      right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level6'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
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
          this.observeComponentCreation2(itemCreation2, ListItem);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(elmtId, this.radioContent, forEachItemGenFunction, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    List.pop();
    Column.pop();
    Scroll.pop();
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogContentComponent(this, {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            minContentHeight: this.minContentHeight,
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 603, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
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
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            primaryTitle: this.title,
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    __Common__.pop();
  }
  onWillApplyTheme(theme) {
    this.fontColorWithTheme = theme.colors.fontPrimary;
    this.dividerColorWithTheme = theme.colors.compDivider;
  }
  aboutToAppear() {
    this.selectedIndexInner = this.selectedIndex;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('title' in params) {
      this.updateParam('title', params.title);
    }
    if ('content' in params) {
      this.updateParam('content', params.content);
    }
    if ('confirm' in params) {
      this.updateParam('confirm', params.confirm);
    }
    if ('radioContent' in params) {
      this.updateParam('radioContent', params.radioContent);
    }
    if ('selectedIndex' in params) {
      this.updateParam('selectedIndex', params.selectedIndex);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], SelectDialogV2.prototype, 'title', void 0);
__decorate([
  Param
], SelectDialogV2.prototype, 'content', void 0);
__decorate([
  Param
], SelectDialogV2.prototype, 'confirm', void 0);
__decorate([
  Param
], SelectDialogV2.prototype, 'radioContent', void 0);
__decorate([
  Param
], SelectDialogV2.prototype, 'selectedIndex', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'selectedIndexInner', void 0);
__decorate([
  Monitor('selectedIndex')
], SelectDialogV2.prototype, 'selectedIndexMonitor', null);
__decorate([
  Local
], SelectDialogV2.prototype, 'isFocus', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'currentFocusIndex', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'radioHeight', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'itemHeight', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'fontColorWithTheme', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'dividerColorWithTheme', void 0);
__decorate([
  Provider()
], SelectDialogV2.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], SelectDialogV2.prototype, 'minContentHeight', void 0);
__decorate([
  Computed
], SelectDialogV2.prototype, 'buttons', null);
__decorate([
  Computed
], SelectDialogV2.prototype, 'contentPadding', null);
class ConfirmDialogContentLayout extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.textIndex = 0;
    this.checkboxIndex = 1;
    this.initParam('minContentHeight', (params && 'minContentHeight' in params) ? params.minContentHeight : 0);
    this.$minContentHeight = '$minContentHeight' in params ? params.$minContentHeight : undefined;
    this.dialogBuilder = 'dialogBuilder' in params ? params.dialogBuilder : this.doNothingBuilder;
    this.finalizeConstruction();
  }
  doNothingBuilder(parent = null) {
  }
  ;
  onPlaceChildren(selfLayoutInfo, children, constraint) {
    let currentX = 0;
    let currentY = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }
  onMeasureSize(selfLayoutInfo, children, constraint) {
    let sizeResult = { width: Number(constraint.maxWidth), height: 0 };
    let childrenSize = 2;
    if (children.length < childrenSize) {
      return sizeResult;
    }
    let height = 0;
    let checkboxChild = children[this.checkboxIndex];
    let checkboxConstraint = {
      maxWidth: constraint.maxWidth,
      minHeight: CHECKBOX_CONTAINER_HEIGHT,
      maxHeight: constraint.maxHeight
    };
    let checkBoxMeasureResult = checkboxChild.measure(checkboxConstraint);
    height += checkBoxMeasureResult.height;
    let textChild = children[this.textIndex];
    let textConstraint = {
      maxWidth: constraint.maxWidth,
      maxHeight: Number(constraint.maxHeight) - height
    };
    let textMeasureResult = textChild.measure(textConstraint);
    height += textMeasureResult.height;
    sizeResult.height = height;
    this.$minContentHeight?.(Math.max(checkBoxMeasureResult.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT));
    return sizeResult;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('minContentHeight' in params) {
      this.updateParam('minContentHeight', params.minContentHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ConfirmDialogContentLayout.prototype, 'minContentHeight', void 0);
__decorate([
  Event
], ConfirmDialogContentLayout.prototype, '$minContentHeight', void 0);
export class ConfirmDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('title', (params && 'title' in params) ? params.title : '');
    this.initParam('content', (params && 'content' in params) ? params.content : '');
    this.initParam('checkTips', (params && 'checkTips' in params) ? params.checkTips : '');
    this.initParam('checked', (params && 'checked' in params) ? params.checked : false);
    this.checkedInner = this.checked;
    this.initParam('primaryButton', (params && 'primaryButton' in params) ? params.primaryButton : new AdvancedDialogV2Button({ content: '' }));
    this.initParam('secondaryButton', (params && 'secondaryButton' in params) ? params.secondaryButton : new AdvancedDialogV2Button({ content: '' }));
    this.fontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.initParam('onCheckedChange', (params && 'onCheckedChange' in params) ? params.onCheckedChange : undefined);
    this.contentScroller = new Scroller();
    this.marginOffset = 0 - PADDING_LEVEL_8;
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.textIndex = 0;
    this.checkboxIndex = 1;
    this.finalizeConstruction();
  }
  checkedMonitor(monitor) {
    this.checkedInner = monitor.value('checked')?.now;
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let buttons = [];
    if (this.primaryButton) {
      buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      buttons.push(this.secondaryButton);
    }
    return buttons;
  }
  textBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
    }, Scroll);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) });
      Column.width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`);
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
      Text.onKeyEvent((event) => {
        if (event) {
          resolveKeyEvent(event, this.contentScroller);
        }
      });
      Text.width('100%');
    }, Text);
    Text.pop();
    Column.pop();
    Scroll.pop();
    Column.pop();
  }
  checkBoxBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.accessibilityGroup(true);
      Row.accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.checkedInner));
      Row.accessibilityDescription(this.checkedInner ? { 'id': -1, 'type': 10003, params: ['sys.string.advanced_dialog_accessibility_cancel_checked_desc'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10003, params: ['sys.string.slider_accessibility_unselectedDesc'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Row.onClick(() => {
        this.checkedInner = !this.checkedInner;
        try {
          let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: getContext()?.abilityInfo?.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.checkedInner ? getContext().resourceManager.getStringSync(125833934) :
            getContext().resourceManager.getStringSync(125833935)
          });
          accessibility.sendAccessibilityEvent(eventInfo);
        }
        catch (exception) {
          let code = exception.code;
          let message = exception.message;
          hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
        }
      });
      Row.width('100%');
      Row.padding({ top: 8, bottom: 8 });
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Checkbox.create({ name: '', group: 'checkboxGroup' });
      Checkbox.select(this.checkedInner);
      Checkbox.onChange((checked) => {
        this.checkedInner = checked;
        if (this.onCheckedChange) {
          this.onCheckedChange(this.checkedInner);
        }
      });
      Checkbox.hitTestBehavior(HitTestMode.Block);
      Checkbox.margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(CHECK_BOX_MARGIN_END) });
    }, Checkbox);
    Checkbox.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
  buildContent(parent = null) {
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new ConfirmDialogContentLayout(this, {
            minContentHeight: this.minContentHeight,
            dialogBuilder: () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                ForEach.create();
                const forEachItemGenFunction = _item => {
                  const index = _item;
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index === this.textIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.textBuilder.bind(this)();
                      });
                    }
                    else if (index === this.checkboxIndex) {
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
                this.forEachUpdateFunction(elmtId, [this.textIndex, this.checkboxIndex], forEachItemGenFunction);
              }, ForEach);
              ForEach.pop();
            },
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 801, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
            return {
              minContentHeight: this.minContentHeight,
              dialogBuilder: () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  ForEach.create();
                  const forEachItemGenFunction = _item => {
                    const index = _item;
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (index === this.textIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.textBuilder.bind(this)();
                        });
                      }
                      else if (index === this.checkboxIndex) {
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
                  this.forEachUpdateFunction(elmtId, [this.textIndex, this.checkboxIndex], forEachItemGenFunction);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'ConfirmDialogContentLayout' });
    }
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogContentComponent(this, {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.buildContent();
            },
            minContentHeight: this.minContentHeight,
            buttons: this.buttons,
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 813, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
            return {
              primaryTitle: this.title,
              contentBuilder: () => {
                this.buildContent();
              },
              minContentHeight: this.minContentHeight,
              buttons: this.buttons
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            primaryTitle: this.title,
            minContentHeight: this.minContentHeight,
            buttons: this.buttons
          });
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    __Common__.pop();
  }
  onWillApplyTheme(theme) {
    this.fontColorWithTheme = theme.colors.fontPrimary;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('title' in params) {
      this.updateParam('title', params.title);
    }
    if ('content' in params) {
      this.updateParam('content', params.content);
    }
    if ('checkTips' in params) {
      this.updateParam('checkTips', params.checkTips);
    }
    if ('checked' in params) {
      this.updateParam('checked', params.checked);
    }
    if ('primaryButton' in params) {
      this.updateParam('primaryButton', params.primaryButton);
    }
    if ('secondaryButton' in params) {
      this.updateParam('secondaryButton', params.secondaryButton);
    }
    if ('onCheckedChange' in params) {
      this.updateParam('onCheckedChange', params.onCheckedChange);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], ConfirmDialogV2.prototype, 'title', void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, 'content', void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, 'checkTips', void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, 'checked', void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, 'checkedInner', void 0);
__decorate([
  Monitor('checked')
], ConfirmDialogV2.prototype, 'checkedMonitor', null);
__decorate([
  Param
], ConfirmDialogV2.prototype, 'primaryButton', void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, 'secondaryButton', void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, 'fontColorWithTheme', void 0);
__decorate([
  Param
], ConfirmDialogV2.prototype, 'onCheckedChange', void 0);
__decorate([
  Provider()
], ConfirmDialogV2.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], ConfirmDialogV2.prototype, 'minContentHeight', void 0);
__decorate([
  Computed
], ConfirmDialogV2.prototype, 'buttons', null);
export class AlertDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('primaryTitle', (params && 'primaryTitle' in params) ? params.primaryTitle : undefined);
    this.initParam('secondaryTitle', (params && 'secondaryTitle' in params) ? params.secondaryTitle : undefined);
    this.initParam('content', (params && 'content' in params) ? params.content : '');
    this.initParam('primaryButton', (params && 'primaryButton' in params) ? params.primaryButton : null);
    this.initParam('secondaryButton', (params && 'secondaryButton' in params) ? params.secondaryButton : null);
    this.textAlign = TextAlign.Center;
    this.contentScroller = new Scroller();
    this.fontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  get buttons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return undefined;
    }
    let buttons = [];
    if (this.primaryButton) {
      buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      buttons.push(this.secondaryButton);
    }
    return buttons;
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogContentComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
            minContentHeight: this.minContentHeight,
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 858, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
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
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            buttons: this.buttons,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    __Common__.pop();
  }
  AlertDialogContentBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) });
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Scroll.create(this.contentScroller);
      Scroll.nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL });
      Scroll.width('100%');
    }, Scroll);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
      Text.onKeyEvent((event) => {
        if (event) {
          resolveKeyEvent(event, this.contentScroller);
        }
      });
    }, Text);
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  onWillApplyTheme(theme) {
    this.fontColorWithTheme = theme.colors.fontPrimary;
  }
  getFontWeight() {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return FontWeight.Medium;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('primaryTitle' in params) {
      this.updateParam('primaryTitle', params.primaryTitle);
    }
    if ('secondaryTitle' in params) {
      this.updateParam('secondaryTitle', params.secondaryTitle);
    }
    if ('content' in params) {
      this.updateParam('content', params.content);
    }
    if ('primaryButton' in params) {
      this.updateParam('primaryButton', params.primaryButton);
    }
    if ('secondaryButton' in params) {
      this.updateParam('secondaryButton', params.secondaryButton);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], AlertDialogV2.prototype, 'primaryTitle', void 0);
__decorate([
  Param
], AlertDialogV2.prototype, 'secondaryTitle', void 0);
__decorate([
  Param
], AlertDialogV2.prototype, 'content', void 0);
__decorate([
  Param
], AlertDialogV2.prototype, 'primaryButton', void 0);
__decorate([
  Param
], AlertDialogV2.prototype, 'secondaryButton', void 0);
__decorate([
  Local
], AlertDialogV2.prototype, 'fontColorWithTheme', void 0);
__decorate([
  Provider()
], AlertDialogV2.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], AlertDialogV2.prototype, 'minContentHeight', void 0);
__decorate([
  Computed
], AlertDialogV2.prototype, 'buttons', null);
export class CustomContentDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('primaryTitle', (params && 'primaryTitle' in params) ? params.primaryTitle : undefined);
    this.initParam('secondaryTitle', (params && 'secondaryTitle' in params) ? params.secondaryTitle : undefined);
    this.contentBuilder = 'contentBuilder' in params ? params.contentBuilder : undefined;
    this.initParam('contentAreaPadding', (params && 'contentAreaPadding' in params) ? params.contentAreaPadding : undefined);
    this.initParam('buttons', (params && 'buttons' in params) ? params.buttons : undefined);
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogContentComponent(this, {
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
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 920, col: 5 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
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
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    __Common__.pop();
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('primaryTitle' in params) {
      this.updateParam('primaryTitle', params.primaryTitle);
    }
    if ('secondaryTitle' in params) {
      this.updateParam('secondaryTitle', params.secondaryTitle);
    }
    if ('contentAreaPadding' in params) {
      this.updateParam('contentAreaPadding', params.contentAreaPadding);
    }
    if ('buttons' in params) {
      this.updateParam('buttons', params.buttons);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], CustomContentDialogV2.prototype, 'primaryTitle', void 0);
__decorate([
  Param
], CustomContentDialogV2.prototype, 'secondaryTitle', void 0);
__decorate([
  Param
], CustomContentDialogV2.prototype, 'contentAreaPadding', void 0);
__decorate([
  Param
], CustomContentDialogV2.prototype, 'buttons', void 0);
__decorate([
  Provider()
], CustomContentDialogV2.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], CustomContentDialogV2.prototype, 'minContentHeight', void 0);
class CustomDialogLayout extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('titleHeight', (params && 'titleHeight' in params) ? params.titleHeight : 0);
    this.$titleHeight = '$titleHeight' in params ? params.$titleHeight : undefined;
    this.initParam('buttonHeight', (params && 'buttonHeight' in params) ? params.buttonHeight : 0);
    this.$buttonHeight = '$buttonHeight' in params ? params.$buttonHeight : undefined;
    this.initParam('titleMinHeight', (params && 'titleMinHeight' in params) ? params.titleMinHeight : 0);
    this.dialogBuilder = 'dialogBuilder' in params ? params.dialogBuilder : this.doNothingBuilder;
    this.titleIndex = 0;
    this.contentIndex = 1;
    this.buttonIndex = 2;
    this.finalizeConstruction();
  }
  doNothingBuilder(parent = null) {
  }
  ;
  onPlaceChildren(selfLayoutInfo, children, constraint) {
    let currentX = 0;
    let currentY = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }
  onMeasureSize(selfLayoutInfo, children, constraint) {
    let sizeResult = { width: Number(constraint.maxWidth), height: 0 };
    let childrenSize = 3;
    if (children.length < childrenSize) {
      return sizeResult;
    }
    let height = 0;
    let titleChild = children[this.titleIndex];
    let titleConstraint = {
      maxWidth: constraint.maxWidth,
      minHeight: this.titleMinHeight,
      maxHeight: constraint.maxHeight
    };
    let titleMeasureResult = titleChild.measure(titleConstraint);
    this.$titleHeight?.(titleMeasureResult.height);
    height += titleMeasureResult.height;
    let buttonChild = children[this.buttonIndex];
    let buttonMeasureResult = buttonChild.measure(constraint);
    this.$buttonHeight?.(buttonMeasureResult.height);
    height += buttonMeasureResult.height;
    let contentChild = children[this.contentIndex];
    let contentConstraint = {
      maxWidth: constraint.maxWidth,
      maxHeight: Number(constraint.maxHeight) - height
    };
    let contentMeasureResult = contentChild.measure(contentConstraint);
    height += contentMeasureResult.height;
    sizeResult.height = height;
    return sizeResult;
  }
  initialRender() {
    this.dialogBuilder.bind(this)();
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('titleHeight' in params) {
      this.updateParam('titleHeight', params.titleHeight);
    }
    if ('buttonHeight' in params) {
      this.updateParam('buttonHeight', params.buttonHeight);
    }
    if ('titleMinHeight' in params) {
      this.updateParam('titleMinHeight', params.titleMinHeight);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], CustomDialogLayout.prototype, 'titleHeight', void 0);
__decorate([
  Event
], CustomDialogLayout.prototype, '$titleHeight', void 0);
__decorate([
  Param
], CustomDialogLayout.prototype, 'buttonHeight', void 0);
__decorate([
  Event
], CustomDialogLayout.prototype, '$buttonHeight', void 0);
__decorate([
  Param
], CustomDialogLayout.prototype, 'titleMinHeight', void 0);
class CustomDialogContentComponent extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('primaryTitle', (params && 'primaryTitle' in params) ? params.primaryTitle : undefined);
    this.initParam('secondaryTitle', (params && 'secondaryTitle' in params) ? params.secondaryTitle : undefined);
    this.contentBuilder = 'contentBuilder' in params ? params.contentBuilder : this.defaultContentBuilder;
    this.initParam('buttons', (params && 'buttons' in params) ? params.buttons : undefined);
    this.initParam('contentAreaPadding', (params && 'contentAreaPadding' in params) ? params.contentAreaPadding : undefined);
    this.initParam('minContentHeight', (params && 'minContentHeight' in params) ? params.minContentHeight : undefined);
    this.$minContentHeight = '$minContentHeight' in params ? params.$minContentHeight : undefined;
    this.keyIndex = 0;
    this.titleHeight = 0;
    this.buttonHeight = 0;
    this.contentMaxHeight = '100%';
    this.fontSizeScale = -1;
    this.customStyle = undefined;
    this.buttonMaxFontSize = `${BODY_L}fp`;
    this.buttonMinFontSize = 9;
    this.primaryTitleFontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.secondaryTitleFontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
    this.scroller = new Scroller();
    this.initParam('isHasDefaultFocus', (params && 'isHasDefaultFocus' in params) ? params.isHasDefaultFocus : false);
    this.initParam('isAllFocusFalse', (params && 'isAllFocusFalse' in params) ? params.isAllFocusFalse : false);
    this.finalizeConstruction();
  }
  defaultContentBuilder(parent = null) {
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      RelativeContainer.create();
      RelativeContainer.height('auto');
    } , RelativeContainer);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Scroll.create(this.scroller);
      Scroll.edgeEffect(EdgeEffect.None, { alwaysEnabled: false });
      Scroll.backgroundColor(Color.Transparent);
      Scroll.scrollBar(BarState.Off);
      Scroll.id('CustomDialogContentComponent');
    }, Scroll);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.constraintSize({ maxHeight: this.contentMaxHeight });
      Column.backgroundBlurStyle(this.customStyle ?
      BlurStyle.Thick : BlurStyle.NONE, undefined, { disableSystemAdaptation: true });
      Column.borderRadius(this.customStyle ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_dialog'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : 0);
      Column.margin(this.customStyle ? {
        start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_dialog_margin_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_dialog_margin_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        bottom: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_dialog_margin_bottom'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
      } : { left: 0, right: 0, bottom: 0 });
      Column.backgroundColor(this.customStyle ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_dialog_bg'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : Color.Transparent);
    }, Column);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogLayout(this, {
            buttonHeight: this.buttonHeight,
            titleHeight: this.titleHeight,
            titleMinHeight: this.getTitleAreaMinHeight(),
            dialogBuilder: () => {
              this.observeComponentCreation2((elmtId, isInitialRender) => {
                ForEach.create();
                const forEachItemGenFunction = _item => {
                  const index = _item;
                  this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (index === this.titleIndex) {
                      this.ifElseBranchUpdateFunction(0, () => {
                        this.titleBuilder.bind(this)();
                      });
                    }
                    else if (index === this.contentIndex) {
                      this.ifElseBranchUpdateFunction(1, () => {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                this.forEachUpdateFunction(elmtId, [this.titleIndex, this.contentIndex, this.buttonIndex], forEachItemGenFunction);
              }, ForEach);
              ForEach.pop();
            },
            $buttonHeight: value => { this.buttonHeight = value; },
            $titleHeight: value => { this.titleHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 1057, col: 9 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
            return {
              buttonHeight: this.buttonHeight,
              titleHeight: this.titleHeight,
              titleMinHeight: this.getTitleAreaMinHeight(),
              dialogBuilder: () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  ForEach.create();
                  const forEachItemGenFunction = _item => {
                    const index = _item;
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                      If.create();
                      if (index === this.titleIndex) {
                        this.ifElseBranchUpdateFunction(0, () => {
                          this.titleBuilder.bind(this)();
                        });
                      }
                      else if (index === this.contentIndex) {
                        this.ifElseBranchUpdateFunction(1, () => {
                          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
                  this.forEachUpdateFunction(elmtId, [this.titleIndex, this.contentIndex, this.buttonIndex], forEachItemGenFunction);
                }, ForEach);
                ForEach.pop();
              }
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            buttonHeight: this.buttonHeight,
            titleHeight: this.titleHeight,
            titleMinHeight: this.getTitleAreaMinHeight()
          });
        }
      }, { name: 'CustomDialogLayout' });
    }
    Column.pop();
    Scroll.pop();
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      ScrollBar.create({ scroller: this.scroller });
      ScrollBar.alignRules({
        top: { anchor: 'CustomDialogContentComponent', align: VerticalAlign.Top },
        bottom: { anchor: 'CustomDialogContentComponent', align: VerticalAlign.Bottom },
        end: { anchor: 'CustomDialogContentComponent', align: HorizontalAlign.End }
      });
      ScrollBar.margin({
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_container_shape'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_container_shape'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__'
        }
      });
      ScrollBar.enableNestedScroll(true);
      ScrollBar.hitTestBehavior(HitTestMode.Transparent);
      ScrollBar.onGestureRecognizerJudgeBegin((event, current, others) => {
        if (current) {
          if (current.getType() == GestureControl.GestureType.LONG_PRESS_GESTURE) {
            return GestureJudgeResult.REJECT;
          }
        }
        return GestureJudgeResult.CONTINUE;
      });
    }, ScrollBar);
    ScrollBar.pop();
    RelativeContainer.pop();
  }
  onMeasureSize(selfLayoutInfo, children, constraint) {
    let sizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    let maxWidth = Number(constraint.maxWidth);
    let maxHeight = Number(constraint.maxHeight);
    this.fontSizeScale = this.updateFontScale();
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(maxWidth - BUTTON_HORIZONTAL_MARGIN * 2);
    let height = 0;
    children.forEach((child) => {
      this.contentMaxHeight = '100%';
      let measureResult = child.measure(constraint);
      if (maxHeight - this.buttonHeight - this.titleHeight < this.minContentHeight) {
        this.contentMaxHeight = MAX_CONTENT_HEIGHT;
        measureResult = child.measure(constraint);
      }
      height += measureResult.height;
    });
    sizeResult.height = height;
    sizeResult.width = maxWidth;
    return sizeResult;
  }
  onWillApplyTheme(theme) {
    this.primaryTitleFontColorWithTheme = theme.colors.fontPrimary;
    this.secondaryTitleFontColorWithTheme = theme.colors.fontSecondary;
  }
  aboutToAppear() {
    try {
      let uiContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContext?.isFollowingSystemFontScale();
      this.appMaxFontScale = uiContext?.getMaxFontScale();
    }
    catch (err) {
      let code = err?.code;
      let message = err?.message;
      hilog.error(0x3900, 'Ace', `Faild to dialog getUIContext, code: ${code}, message: ${message}`);
    }
    this.fontSizeScale = this.updateFontScale();
    this.initTitleTextAlign();
    this.setDefaultFocusState(this.buttons);
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
      let uiContext = this.getUIContext();
      let systemFontScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(systemFontScale, this.appMaxFontScale);
    }
    catch (exception) {
      let code = exception.code;
      let message = exception.message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }
  /**
   * set state of button focus
   */
  setDefaultFocusState(buttonList) {
    if (!buttonList) {
      return;
    }
    let falseNum = 0;
    buttonList.forEach((button) => {
      // 遍历查询按钮中存在是否存在默认按钮
      if (button.defaultFocus) {
        this.isHasDefaultFocus = true;
      }
      if (button.defaultFocus === false) {
        falseNum++;
      }
    });
    // 所有按钮defaultFocus都设置为false
    if (falseNum === buttonList.length) {
      this.isAllFocusFalse = true;
    }
  }
  /**
   * get dialog content padding
   *
   * @returns content padding
   */
  getContentPadding() {
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }
    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: 0,
        left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      };
    }
    else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      };
    }
    else if (this.buttons && this.buttons.length > 0) {
      return {
        top: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: 0,
        left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      };
    }
    else {
      return {
        top: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_content_default_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      };
    }
  }
  titleBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height({ 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
  /**
   * get title area padding
   *
   * @returns padding
   */
  getTitleAreaPadding() {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_padding_top'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_padding_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_padding_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_padding_bottom'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      };
    }
    return {
      top: 0,
      right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_padding_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_padding_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      bottom: 0,
    };
  }
  /**
   * get tile TextAlign
   * @returns TextAlign
   */
  initTitleTextAlign() {
    let textAlign = ALERT_TITLE_ALIGNMENT;
    if (textAlign === TextAlign.Start) {
      this.titleTextAlign = TextAlign.Start;
    }
    else if (textAlign === TextAlign.Center) {
      this.titleTextAlign = TextAlign.Center;
    }
    else if (textAlign === TextAlign.End) {
      this.titleTextAlign = TextAlign.End;
    }
    else if (textAlign === TextAlign.JUSTIFY) {
      this.titleTextAlign = TextAlign.JUSTIFY;
    }
    else {
      this.titleTextAlign = TextAlign.Center;
    }
  }
  /**
   * get title area min height
   *
   * @returns min height
   */
  getTitleAreaMinHeight() {
    if (this.secondaryTitle) {
      return { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_secondary_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else if (this.primaryTitle) {
      return { 'id': -1, 'type': 10002, params: ['sys.float.alert_title_primary_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    else {
      return 0;
    }
  }
  ButtonBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
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
  /**
   * get operation area padding
   *
   * @returns padding
   */
  getOperationAreaPadding() {
    if (this.isButtonVertical) {
      return {
        top: { 'id': -1, 'type': 10002, params: ['sys.float.alert_button_top_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_right_padding_vertical'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_left_padding_vertical'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.alert_button_bottom_padding_vertical'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      };
    }
    return {
      top: { 'id': -1, 'type': 10002, params: ['sys.float.alert_button_top_padding'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      right: { 'id': -1, 'type': 10002, params: ['sys.float.alert_right_padding_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      left: { 'id': -1, 'type': 10002, params: ['sys.float.alert_left_padding_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
      bottom: { 'id': -1, 'type': 10002, params: ['sys.float.alert_button_bottom_padding_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
    };
  }
  buildSingleButton(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.isNewPropertiesHighPriority(index)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel(this.buttons?.[index].content);
            __Button__setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, this.isAllFocusFalse, this.getDialogController());
            Button.role(this.buttons?.[index].role ?? ButtonRole.NORMAL);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else if (this.buttons?.[index].background !== undefined && this.buttons?.[index].fontColor !== undefined) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel(this.buttons?.[index].content);
            __Button__setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, this.isAllFocusFalse, this.getDialogController());
            Button.backgroundColor(this.buttons?.[index].background?.color);
            Button.fontColor(this.buttons?.[index].fontColor?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else if (this.buttons?.[index].background !== undefined) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel(this.buttons?.[index].content);
            __Button__setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, this.isAllFocusFalse, this.getDialogController());
            Button.backgroundColor(this.buttons?.[index].background?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(3, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithLabel(this.buttons?.[index].content);
            __Button__setButtonProperties(this.buttons?.[index], this.isHasDefaultFocus, this.isAllFocusFalse, this.getDialogController());
            Button.fontColor(this.buttons?.[index]?.fontColor?.color);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
            Button.labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize });
          }, Button);
          Button.pop();
        });
      }
    }, If);
    If.pop();
  }
  buildHorizontalAlignButtons(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(0);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Row.create();
                  Row.width(BUTTON_HORIZONTAL_SPACE * 2);
                  Row.justifyContent(FlexAlign.Center);
                }, Row);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Divider.create();
                  Divider.width({ 'id': -1, 'type': 10002, params: ['sys.float.alert_divider_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                  Divider.height({ 'id': -1, 'type': 10002, params: ['sys.float.alert_divider_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
  buildVerticalAlignButtons(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.buttons) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, index) => {
              const item = _item;
              this.buildButtonWithDivider.bind(this)(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
                HORIZON_BUTTON_MAX_COUNT - index - 1 : index);
            };
            this.forEachUpdateFunction(elmtId, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), forEachItemGenFunction, (item) => item.content.toString(), true, false);
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
  /**
   * get divider color
   *
   * @returns divider color
   */
  getDividerColor() {
    if (!this.buttons || this.buttons.length === 0 || !DIALOG_DIVIDER_SHOW) {
      return Color.Transparent;
    }
    if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
      if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
        this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
        return { 'id': -1, 'type': 10001, params: ['sys.color.alert_divider_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
      }
    }
    return Color.Transparent;
  }
  /**
   * is button buttonStyle and role properties high priority
   *
   * @param buttonOptions button properties
   * @returns check result
   */
  isNewPropertiesHighPriority(index) {
    if (this.buttons?.[index].role === ButtonRole.ERROR) {
      return true;
    }
    if (this.buttons?.[index].buttonStyle !== undefined &&
      this.buttons?.[index].buttonStyle !== ALERT_BUTTON_STYLE) {
      return true;
    }
    if (this.buttons?.[index].background === undefined && this.buttons?.[index].fontColor === undefined) {
      return true;
    }
    return false;
  }
  buildButtonWithDivider(index, parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      If.create();
      if (this.buttons && this.buttons[index]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(index);
          Row.pop();
          this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - index - 1 : index) <
              Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                  Row.create();
                  Row.height({ 'id': -1, 'type': 10002, params: ['sys.float.alert_button_vertical_space'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
  isVerticalAlignButton(width) {
    if (this.buttons) {
      if (this.buttons.length === 1) {
        return false;
      }
      if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
        return true;
      }
      let isVertical = false;
      let maxButtonTextSize = vp2px(width / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
        BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
      this.buttons.forEach((button) => {
        let contentSize = measure.measureTextSize({
          textContent: button.content,
          fontSize: this.buttonMaxFontSize
        });
        if (Number(contentSize.width) > maxButtonTextSize) {
          isVertical = true;
        }
      });
      return isVertical;
    }
    return false;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('primaryTitle' in params) {
      this.updateParam('primaryTitle', params.primaryTitle);
    }
    if ('secondaryTitle' in params) {
      this.updateParam('secondaryTitle', params.secondaryTitle);
    }
    if ('buttons' in params) {
      this.updateParam('buttons', params.buttons);
    }
    if ('contentAreaPadding' in params) {
      this.updateParam('contentAreaPadding', params.contentAreaPadding);
    }
    if ('minContentHeight' in params) {
      this.updateParam('minContentHeight', params.minContentHeight);
    }
    if ('isHasDefaultFocus' in params) {
      this.updateParam('isHasDefaultFocus', params.isHasDefaultFocus);
    }
    if ('isAllFocusFalse' in params) {
      this.updateParam('isAllFocusFalse', params.isAllFocusFalse);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], CustomDialogContentComponent.prototype, 'primaryTitle', void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, 'secondaryTitle', void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, 'buttons', void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, 'contentAreaPadding', void 0);
__decorate([
  Param
], CustomDialogContentComponent.prototype, 'minContentHeight', void 0);
__decorate([
  Event
], CustomDialogContentComponent.prototype, '$minContentHeight', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'titleHeight', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'buttonHeight', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'contentMaxHeight', void 0);
__decorate([
  Consumer()
], CustomDialogContentComponent.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'customStyle', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'buttonMaxFontSize', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'buttonMinFontSize', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'primaryTitleFontColorWithTheme', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'secondaryTitleFontColorWithTheme', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'titleTextAlign', void 0);
__decorate([
  Local
], CustomDialogContentComponent.prototype, 'isButtonVertical', void 0);
__decorate([
  Param,
  Once
], CustomDialogContentComponent.prototype, 'isHasDefaultFocus', void 0);
__decorate([
  Param,
  Once
], CustomDialogContentComponent.prototype, 'isAllFocusFalse', void 0);
function __Button__setButtonProperties(buttonOptions, isHasDefaultFocus, isAllFocusFalse, controller) {
  Button.onKeyEvent((event) => {
    if (!event) {
      return;
    }
    if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
      event.type === KeyType.Down) {
      if (buttonOptions?.action) {
        buttonOptions.action();
      }
      controller?.close();
      event.stopPropagation();
    }
  });
  Button.onClick(() => {
    if (buttonOptions?.action) {
      buttonOptions.action();
    }
    controller?.close();
  });
  Button.defaultFocus(isDefaultFocus(buttonOptions, isHasDefaultFocus, isAllFocusFalse));
  Button.buttonStyle(buttonOptions?.buttonStyle ?? ALERT_BUTTON_STYLE);
  Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
  Button.type(ButtonType.ROUNDED_RECTANGLE);
  Button.enabled(buttonOptions?.enabled ?? true);
}
/**
 * is button set default focus
 *
 * @param singleButton button options
 * @param isHasDefaultFocus is button list has default focus button
 * @param isAllFocusFalse is all button in button list default focus false
 * @returns boolean
 */
function isDefaultFocus(singleButton, isHasDefaultFocus, isAllFocusFalse) {
  try {
    // 当前按钮为默认按钮
    if (singleButton?.defaultFocus) {
      return true;
    }
    let isDefaultFocus = false;
    if (isHasDefaultFocus || isAllFocusFalse) {
      isDefaultFocus = false; // 存在默认按钮或者所有按钮的defaultFocus都为false
    }
    else {
      isDefaultFocus = true; // 默认第一个按钮获焦
    }
    return isDefaultFocus;
  }
  catch (error) {
    let code = error.code;
    let message = error.message;
    hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${code}, message: ${message}`);
    return true;
  }
}
/**
 * get resource size
 *
 * @param resourceId resource id
 * @param defaultValue default value
 * @returns resource size
 */
function getNumberByResourceId(resourceId, defaultValue, allowZero) {
  try {
    let sourceValue = resourceManager.getSystemResourceManager().getNumber(resourceId);
    if (sourceValue > 0 || allowZero) {
      return sourceValue;
    }
    else {
      return defaultValue;
    }
  }
  catch (error) {
    let code = error.code;
    let message = error.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${code}, message: ${message}`);
    return defaultValue;
  }
}
/**
 * get enum number
 *
 * @param resourceId resource id
 * @param defaultValue default value
 * @returns number
 */
function getEnumNumberByResourceId(resourceId, defaultValue) {
  try {
    let sourceValue = getContext().resourceManager.getNumber(resourceId);
    if (sourceValue > 0) {
      return sourceValue;
    }
    else {
      return defaultValue;
    }
  }
  catch (error) {
    let code = error.code;
    let message = error.message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResourceId error, code: ${code}, message: ${message}`);
    return defaultValue;
  }
}
/**
 * 获取SelectDialog无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getAccessibilityText(resource, selected) {
  try {
    let selectText = getContext().resourceManager.getStringSync(125833934);
    let resourceString = '';
    if (typeof resource === 'string') {
      resourceString = resource;
    }
    else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return selected ? `${selectText},${resourceString}` : resourceString;
  }
  catch (error) {
    let code = error.code;
    let message = error.message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}
/**
 * resolve content area keyEvent
 *
 * @param event keyEvent
 * @param controller the controller of content area
 * @returns undefined
 */
function resolveKeyEvent(event, controller) {
  if (event.type === IGNORE_KEY_EVENT_TYPE) {
    return;
  }
  if (event.keyCode === KEYCODE_UP) {
    controller.scrollPage({ next: false });
    event.stopPropagation();
  }
  else if (event.keyCode === KEYCODE_DOWN) {
    if (controller.isAtEnd()) {
      return;
    }
    else {
      controller.scrollPage({ next: true });
      event.stopPropagation();
    }
  }
}
/**
 * 获取checkTips无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getCheckTipsAccessibilityText(resource, selected) {
  try {
    // 'sys.string.slider_accessibility_selected'
    let selectText = getContext().resourceManager.getStringSync(125833934);
    // 'sys.string.slider_accessibility_unselected'
    let unselectText = getContext().resourceManager.getStringSync(125833935);
    // 'sys.string.advanced_dialog_accessibility_checkbox'
    let checkBoxText = getContext().resourceManager.getStringSync(125834354);
    let resourceString = '';
    if (typeof resource === 'string') {
      resourceString = resource;
    }
    else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return selected ? `${selectText},${resourceString},${checkBoxText}` :
      `${unselectText},${resourceString},${checkBoxText}`;
  }
  catch (error) {
    let code = error.code;
    let message = error.message;
    hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}
export class LoadingDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('content', (params && 'content' in params) ? params.content : '');
    this.fontColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.loadingProgressIconColorWithTheme = { 'id': -1, 'type': 10001, params: ['sys.color.icon_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    this.fontSizeScale = 1;
    this.minContentHeight = MIN_CONTENT_HEIGHT;
    this.finalizeConstruction();
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      __Common__.create();
      __Common__.constraintSize({ maxHeight: '100%' });
    }, __Common__);
    {
      this.observeComponentCreation2((elmtId, isInitialRender) => {
        if (isInitialRender) {
          let componentCall = new CustomDialogContentComponent(this, {
            contentBuilder: () => {
              this.contentBuilder();
            },
            minContentHeight: this.minContentHeight,
            $minContentHeight: value => { this.minContentHeight = value; }
          }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/dialog.ets', line: 1707, col: 7 });
          ViewV2.create(componentCall);
          let paramsLambda = () => {
            return {
              contentBuilder: () => {
                this.contentBuilder();
              },
              minContentHeight: this.minContentHeight
            };
          };
          componentCall.paramsGenerator_ = paramsLambda;
        }
        else {
          this.updateStateVarsOfChildByElmtId(elmtId, {
            minContentHeight: this.minContentHeight
          });
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    __Common__.pop();
    Column.pop();
  }
  contentBuilder(parent = null) {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Row.create();
      Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
    }, Row);
    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      LoadingProgress.create();
      LoadingProgress.color(this.loadingProgressIconColorWithTheme);
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) });
    }, LoadingProgress);
    Row.pop();
    Column.pop();
  }
  onWillApplyTheme(theme) {
    this.fontColorWithTheme = theme.colors.fontPrimary;
    this.loadingProgressIconColorWithTheme = theme.colors.iconSecondary;
  }
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('content' in params) {
      this.updateParam('content', params.content);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], LoadingDialogV2.prototype, 'content', void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, 'fontColorWithTheme', void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, 'loadingProgressIconColorWithTheme', void 0);
__decorate([
  Provider()
], LoadingDialogV2.prototype, 'fontSizeScale', void 0);
__decorate([
  Local
], LoadingDialogV2.prototype, 'minContentHeight', void 0);
export class PopoverDialogV2 extends ViewV2 {
  constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
    super(parent, elmtId, extraInfo);
    this.initParam('visible', (params && 'visible' in params) ? params.visible : false);
    this.$visible = '$visible' in params ? params.$visible : () => { };
    this.initParam('popover', (params && 'popover' in params) ? params.popover : {
      builder: undefined
    });
    this.targetBuilder = 'targetBuilder' in params ? params.targetBuilder : undefined;
    this.dialogWidth = this.popover?.width;
    this.finalizeConstruction();
  }
  emptyBuilder(parent = null) {
  }
  aboutToAppear() {
    if (this.targetBuilder === undefined || this.targetBuilder === null) {
      this.targetBuilder = this.emptyBuilder;
    }
  }
  initialRender() {
    this.observeComponentCreation2((elmtId, isInitialRender) => {
      Column.create();
      Column.onClick(() => {
        try {
          let screenSize = display.getDefaultDisplaySync();
          let screenWidth = px2vp(screenSize.width);
          if (screenWidth - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
            this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
          }
          else {
            this.popover.width = this.dialogWidth;
          }
          this.$visible?.(!this.visible);
        }
        catch (error) {
          let code = error.code;
          let message = error.message;
          hilog.error(0x3900, 'Ace', `dialog popup error, code: ${code}, message: ${message}`);
        }
      });
      Column.bindPopup(this.visible, {
        builder: this.popover?.builder,
        placement: this.popover?.placement ?? Placement.Bottom,
        popupColor: this.popover?.popupColor,
        enableArrow: this.popover?.enableArrow ?? true,
        autoCancel: this.popover?.autoCancel,
        onStateChange: this.popover?.onStateChange ?? ((e) => {
          if (!e.isVisible) {
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
        radius: this.popover?.radius ?? { 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level16'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
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
  updateStateVars(params) {
    if (params === undefined) {
      return;
    }
    if ('visible' in params) {
      this.updateParam('visible', params.visible);
    }
    if ('popover' in params) {
      this.updateParam('popover', params.popover);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
__decorate([
  Param
], PopoverDialogV2.prototype, 'visible', void 0);
__decorate([
  Event
], PopoverDialogV2.prototype, '$visible', void 0);
__decorate([
  Param
], PopoverDialogV2.prototype, 'popover', void 0);
__decorate([
  Local
], PopoverDialogV2.prototype, 'dialogWidth', void 0);
function toLengthString(value) {
  if (!value) {
    return undefined;
  }
  const length = value.value;
  let lengthString = '';
  switch (value.unit) {
    case LengthUnit.PX:
      lengthString = `${length}px`;
      break;
    case LengthUnit.FP:
      lengthString = `${length}fp`;
      break;
    case LengthUnit.LPX:
      lengthString = `${length}lpx`;
      break;
    case LengthUnit.PERCENT:
      lengthString = `${length * 100}%`;
      break;
    case LengthUnit.VP:
      lengthString = `${length}vp`;
      break;
    default:
      lengthString = `${length}vp`;
      break;
  }
  return lengthString;
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