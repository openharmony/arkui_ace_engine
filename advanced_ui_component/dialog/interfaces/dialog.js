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

const display = requireNapi('display');
const hilog = requireNapi('hilog');
const measure = requireNapi('measure');
const resourceManager = requireNapi('resourceManager');

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
class CustomThemeImpl {
  constructor(d21) {
    this.colors = d21;
  }
}
const TITLE_MAX_LINES = 2;
const HORIZON_BUTTON_MAX_COUNT = 2;
const VERTICAL_BUTTON_MAX_COUNT = 4;
const BUTTON_DEFAULT_HEIGHT = 40;
const BUTTON_LAYOUT_WEIGHT = 1;
const CHECKBOX_CONTAINER_HEIGHT = 48;
const CONTENT_MAX_LINES = 2;
const DIVIDER_CONTAINER_WIDTH = 16;
const DIVIDER_HEIGHT = 24;
const DIVIDER_WIDTH = 2;
const LOADING_PROGRESS_WIDTH = 40;
const LOADING_PROGRESS_HEIGHT = 40;
const ITEM_TEXT_SIZE = 14;
const LOADING_MAX_LINES = 10;
const LOADING_TEXT_LAYOUT_WEIGHT = 1;
const LOADING_TEXT_MARGIN_LEFT = 12;
const LOADING_MIN_HEIGHT = 48;
const LIST_MIN_HEIGHT = 48;
const CHECKBOX_CONTAINER_LENGTH = 20;
const TEXT_MIN_HEIGHT = 48;
const DEFAULT_IMAGE_SIZE = 64;
const KEYCODE_UP = 2012;
const KEYCODE_DOWN = 2013;
const IGNORE_KEY_EVENT_TYPE = 1;
const FIRST_ITEM_INDEX = 0;

export class TipsDialog extends ViewPU {
  constructor(x20, y20, z20, a21 = -1, b21 = undefined, c21) {
    super(x20, z20, a21, c21);
    if (typeof b21 === 'function') {
      this.paramsGenerator_ = b21;
    }
    this.controller = undefined;
    this.imageRes = null;
    this.__imageSize = new ObservedPropertyObjectPU({ width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE }, this, 'imageSize');
    this.title = null;
    this.content = null;
    this.checkAction = undefined;
    this.checkTips = null;
    this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
    this.primaryButton = null;
    this.secondaryButton = null;
    this.buttons = undefined;
    this.__imageSizeHeight = new ObservedPropertySimplePU(0, this, 'imageSizeHeight');
    this.__textAlignment = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlignment');
    this.marginOffset = 0;
    this.__checkBoxHeight = new ObservedPropertySimplePU(0, this, 'checkBoxHeight');
    this.buttonHeight = 0;
    this.contentScroller = new Scroller();
    this.__fontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'fontColorWithTheme');
    this.theme = new CustomThemeImpl({});
    this.setInitiallyProvidedValue(y20);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(w20) {
    if (w20.controller !== undefined) {
      this.controller = w20.controller;
    }
    if (w20.imageRes !== undefined) {
      this.imageRes = w20.imageRes;
    }
    if (w20.imageSize !== undefined) {
      this.imageSize = w20.imageSize;
    }
    if (w20.title !== undefined) {
      this.title = w20.title;
    }
    if (w20.content !== undefined) {
      this.content = w20.content;
    }
    if (w20.checkAction !== undefined) {
      this.checkAction = w20.checkAction;
    }
    if (w20.checkTips !== undefined) {
      this.checkTips = w20.checkTips;
    }
    if (w20.isChecked !== undefined) {
      this.isChecked = w20.isChecked;
    }
    if (w20.primaryButton !== undefined) {
      this.primaryButton = w20.primaryButton;
    }
    if (w20.secondaryButton !== undefined) {
      this.secondaryButton = w20.secondaryButton;
    }
    if (w20.buttons !== undefined) {
      this.buttons = w20.buttons;
    }
    if (w20.imageSizeHeight !== undefined) {
      this.imageSizeHeight = w20.imageSizeHeight;
    }
    if (w20.textAlignment !== undefined) {
      this.textAlignment = w20.textAlignment;
    }
    if (w20.marginOffset !== undefined) {
      this.marginOffset = w20.marginOffset;
    }
    if (w20.checkBoxHeight !== undefined) {
      this.checkBoxHeight = w20.checkBoxHeight;
    }
    if (w20.buttonHeight !== undefined) {
      this.buttonHeight = w20.buttonHeight;
    }
    if (w20.contentScroller !== undefined) {
      this.contentScroller = w20.contentScroller;
    }
    if (w20.fontColorWithTheme !== undefined) {
      this.fontColorWithTheme = w20.fontColorWithTheme;
    }
    if (w20.theme !== undefined) {
      this.theme = w20.theme;
    }
  }
  updateStateVars(v20) {
  }
  purgeVariableDependenciesOnElmtId(u20) {
    this.__imageSize.purgeDependencyOnElmtId(u20);
    this.__isChecked.purgeDependencyOnElmtId(u20);
    this.__imageSizeHeight.purgeDependencyOnElmtId(u20);
    this.__textAlignment.purgeDependencyOnElmtId(u20);
    this.__checkBoxHeight.purgeDependencyOnElmtId(u20);
    this.__fontColorWithTheme.purgeDependencyOnElmtId(u20);
  }
  aboutToBeDeleted() {
    this.__imageSize.aboutToBeDeleted();
    this.__isChecked.aboutToBeDeleted();
    this.__imageSizeHeight.aboutToBeDeleted();
    this.__textAlignment.aboutToBeDeleted();
    this.__checkBoxHeight.aboutToBeDeleted();
    this.__fontColorWithTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(t20) {
    this.controller = t20;
  }
  get imageSize() {
    return this.__imageSize.get();
  }
  set imageSize(s20) {
    this.__imageSize.set(s20);
  }
  get isChecked() {
    return this.__isChecked.get();
  }
  set isChecked(r20) {
    this.__isChecked.set(r20);
  }
  get imageSizeHeight() {
    return this.__imageSizeHeight.get();
  }
  set imageSizeHeight(q20) {
    this.__imageSizeHeight.set(q20);
  }
  get textAlignment() {
    return this.__textAlignment.get();
  }
  set textAlignment(p20) {
    this.__textAlignment.set(p20);
  }
  get checkBoxHeight() {
    return this.__checkBoxHeight.get();
  }
  set checkBoxHeight(o20) {
    this.__checkBoxHeight.set(o20);
  }
  get fontColorWithTheme() {
    return this.__fontColorWithTheme.get();
  }
  set fontColorWithTheme(n20) {
    this.__fontColorWithTheme.set(n20);
  }
  initialRender() {
    {
      this.observeComponentCreation2((h20, i20) => {
        if (i20) {
          let j20 = new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            theme: this.theme,
          }, undefined, h20, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 82, col: 5 });
          ViewPU.create(j20);
          let k20 = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              theme: this.theme,
            };
          };
          j20.paramsGenerator_ = k20;
        }
        else {
          this.updateStateVarsOfChildByElmtId(h20, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
  }
  contentBuilder(p19 = null) {
    this.observeComponentCreation2((e20, f20) => {
      Column.create();
    }, Column);
    this.imagePart.bind(this)();
    this.observeComponentCreation2((x19, y19) => {
      If.create();
      if (this.title != null || this.content != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((c20, d20) => {
            Column.create();
            Column.padding({
              top: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level8'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              }
            });
            Column.constraintSize({
              maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.imageSizeHeight}vp - ${this.buttonHeight}vp)`
            });
          }, Column);
          this.textPart.bind(this)();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((t19, u19) => {
      If.create();
      if (this.checkTips != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.checkBoxPart.bind(this)(this.checkTips);
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
  checkBoxPart(y18, z18 = null) {
    this.observeComponentCreation2((k19, l19) => {
      Row.create();
      Row.padding({
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level8'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      });
      Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
      Row.width('100%');
      Row.onAreaChange((n19, o19) => {
        this.checkBoxHeight = Number(o19.height);
      });
    }, Row);
    this.observeComponentCreation2((g19, h19) => {
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((j19) => {
        this.isChecked = j19;
        if (this.checkAction) {
          this.checkAction(j19);
        }
      });
      Checkbox.margin({
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level4'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      });
    }, Checkbox);
    Checkbox.pop();
    this.observeComponentCreation2((d19, e19) => {
      Text.create(y18);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_M'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
      Text.maxLines(CONTENT_MAX_LINES);
      Text.layoutWeight(1);
      Text.focusable(false);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.onClick(() => {
        this.isChecked = !this.isChecked;
        if (this.checkAction) {
          this.checkAction(this.isChecked);
        }
      });
    }, Text);
    Text.pop();
    Row.pop();
  }
  imagePart(o18 = null) {
    this.observeComponentCreation2((t18, u18) => {
      Column.create();
      Column.width('100%');
      Column.constraintSize({
        maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
      });
      Column.onAreaChange((w18, x18) => {
        this.imageSizeHeight = Number(x18.height);
      });
    }, Column);
    this.observeComponentCreation2((r18, s18) => {
      Image.create(this.imageRes);
      Image.size(ObservedObject.GetRawObject(this.imageSize));
      Image.objectFit(ImageFit.Contain);
      Image.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.corner_radius_level6'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Image.constraintSize({
        maxWidth: '100%',
        maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
      });
    }, Image);
    Column.pop();
  }
  textPart(g17 = null) {
    this.observeComponentCreation2((m18, n18) => {
      Scroll.create(this.contentScroller);
      Scroll.margin({ right: `${this.marginOffset}vp` });
    }, Scroll);
    this.observeComponentCreation2((k18, l18) => {
      Column.create();
      Column.margin({
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level8'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      });
    }, Column);
    this.observeComponentCreation2((a18, b18) => {
      If.create();
      if (this.title != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((i18, j18) => {
            Row.create();
            Row.padding({
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level8'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              }
            });
          }, Row);
          this.observeComponentCreation2((g18, h18) => {
            Text.create(this.title);
            Text.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.Title_S'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(TextAlign.Center);
            Text.maxLines(CONTENT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.Body_L'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Text.maxFontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.Title_S'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
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
    this.observeComponentCreation2((l17, m17) => {
      If.create();
      if (this.content != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y17, z17) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((r17, s17) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.Body_L'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.textAlign(this.textAlignment);
            Text.width('100%');
            Text.onKeyEvent((x17) => {
              if (x17) {
                resolveKeyEvent(x17, this.contentScroller);
              }
            });
            Text.onAreaChange((v17, w17) => {
              this.getTextAlign(Number(w17.width));
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
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
      this.theme.colors.fontPrimary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.initButtons();
    this.initMargin();
  }
  getTextAlign(d17) {
    let e17 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      constraintWidth: d17,
    });
    let f17 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
    });
    if (this.getTextHeight(e17) <= this.getTextHeight(f17)) {
      this.textAlignment = TextAlign.Center;
    }
  }
  getTextHeight(c17) {
    if (c17 && c17.height !== null && c17.height !== undefined) {
      return Number(c17.height);
    }
    return 0;
  }
  initButtons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
    this.buttonHeight = this.getButtonsHeight();
  }
  getButtonsHeight() {
    if (!this.buttons || this.buttons.length === 0) {
      return 0;
    }
    let b17 = getNumberByResource('alert_button_top_padding');
    b17 += BUTTON_DEFAULT_HEIGHT + getNumberByResource('alert_button_bottom_padding_horizontal');
    return b17;
  }
  initMargin() {
    this.marginOffset = 0 - getNumberByResource('padding_level8');
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class SelectDialog extends ViewPU {
  constructor(r16, s16, t16, u16 = -1, v16 = undefined, w16) {
    super(r16, t16, u16, w16);
    if (typeof v16 === 'function') {
      this.paramsGenerator_ = v16;
    }
    this.title = '';
    this.content = '';
    this.selectedIndex = -1;
    this.confirm = null;
    this.radioContent = [];
    this.buttons = [];
    this.contentPadding = undefined;
    this.contentBuilder = this.buildContent;
    this.__fontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'fontColorWithTheme');
    this.__dividerColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.comp_divider'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'dividerColorWithTheme');
    this.theme = new CustomThemeImpl({});
    this.controller = new CustomDialogController({
      builder: () => {
        let x16 = new CustomContentDialog(this, {
          primaryTitle: this.title,
          contentBuilder: () => {
            this.contentBuilder();
          },
          buttons: this.buttons,
        }, undefined, -1, () => {
        }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 287, col: 14 });
        x16.setController(this.controller);
        ViewPU.create(x16);
        let y16 = () => {
          return {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons
          };
        };
        x16.paramsGenerator_ = y16;
      }
    }, this);
    this.contentScroller = new Scroller();
    this.setInitiallyProvidedValue(s16);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(q16) {
    if (q16.title !== undefined) {
      this.title = q16.title;
    }
    if (q16.content !== undefined) {
      this.content = q16.content;
    }
    if (q16.selectedIndex !== undefined) {
      this.selectedIndex = q16.selectedIndex;
    }
    if (q16.confirm !== undefined) {
      this.confirm = q16.confirm;
    }
    if (q16.radioContent !== undefined) {
      this.radioContent = q16.radioContent;
    }
    if (q16.buttons !== undefined) {
      this.buttons = q16.buttons;
    }
    if (q16.contentPadding !== undefined) {
      this.contentPadding = q16.contentPadding;
    }
    if (q16.contentBuilder !== undefined) {
      this.contentBuilder = q16.contentBuilder;
    }
    if (q16.fontColorWithTheme !== undefined) {
      this.fontColorWithTheme = q16.fontColorWithTheme;
    }
    if (q16.dividerColorWithTheme !== undefined) {
      this.dividerColorWithTheme = q16.dividerColorWithTheme;
    }
    if (q16.theme !== undefined) {
      this.theme = q16.theme;
    }
    if (q16.controller !== undefined) {
      this.controller = q16.controller;
    }
    if (q16.contentScroller !== undefined) {
      this.contentScroller = q16.contentScroller;
    }
  }
  updateStateVars(p16) {
  }
  purgeVariableDependenciesOnElmtId(o16) {
    this.__fontColorWithTheme.purgeDependencyOnElmtId(o16);
    this.__dividerColorWithTheme.purgeDependencyOnElmtId(o16);
  }
  aboutToBeDeleted() {
    this.__fontColorWithTheme.aboutToBeDeleted();
    this.__dividerColorWithTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get fontColorWithTheme() {
    return this.__fontColorWithTheme.get();
  }
  set fontColorWithTheme(n16) {
    this.__fontColorWithTheme.set(n16);
  }
  get dividerColorWithTheme() {
    return this.__dividerColorWithTheme.get();
  }
  set dividerColorWithTheme(m16) {
    this.__dividerColorWithTheme.set(m16);
  }
  setController(l16) {
    this.controller = l16;
  }
  buildContent(w13 = null) {
    this.observeComponentCreation2((j16, k16) => {
      Scroll.create(this.contentScroller);
      Scroll.scrollBar(BarState.Auto);
    }, Scroll);
    this.observeComponentCreation2((h16, i16) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((x15, y15) => {
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((f16, g16) => {
            Row.create();
            Row.padding({
              left: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level12'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              right: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level12'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
              bottom: {
                'id': -1,
                'type': 10002,
                params: ['sys.float.padding_level4'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              },
            });
            Row.width('100%');
          }, Row);
          this.observeComponentCreation2((d16, e16) => {
            Text.create(this.content);
            Text.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.Body_M'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
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
    this.observeComponentCreation2((u15, v15) => {
      List.create({ space: 1 });
      List.width('100%');
      List.clip(false);
      List.onFocus(() => {
        if (!this.contentScroller.isAtEnd()) {
          this.contentScroller.scrollEdge(Edge.Top);
          focusControl.requestFocus(String(FIRST_ITEM_INDEX));
        }
      });
      List.defaultFocus(this.buttons?.length == 0 ? true : false);
    }, List);
    this.observeComponentCreation2((c14, d14) => {
      ForEach.create();
      const e14 = (g14, h14) => {
        const i14 = g14;
        {
          const j14 = (s15, t15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s15);
            k14(s15, t15);
            if (!t15) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const k14 = (q15, r15) => {
            ListItem.create(l14, true);
          };
          const l14 = (p14, q14) => {
            j14(p14, q14);
            this.observeComponentCreation2((o15, p15) => {
              Column.create();
              Column.padding({
                left: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.padding_level6'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                },
                right: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.padding_level6'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                },
              });
            }, Column);
            this.observeComponentCreation2((l15, m15) => {
              Button.createWithChild();
              Button.type(ButtonType.Normal);
              Button.borderRadius({
                'id': -1,
                'type': 10002,
                params: ['sys.float.corner_radius_level8'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              });
              Button.buttonStyle(ButtonStyleMode.TEXTUAL);
              Button.padding({
                left: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.padding_level6'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                },
                right: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.padding_level6'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                },
              });
              Button.onClick(() => {
                i14.action && i14.action();
                this.controller.close();
              });
            }, Button);
            this.observeComponentCreation2((j15, k15) => {
              Row.create();
              Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
              Row.clip(false);
              Row.padding({
                top: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.padding_level4'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                },
                bottom: {
                  'id': -1,
                  'type': 10002,
                  params: ['sys.float.padding_level4'],
                  'bundleName': '__harDefaultBundleName__',
                  'moduleName': '__harDefaultModuleName__',
                }
              });
            }, Row);
            this.observeComponentCreation2((h15, i15) => {
              Text.create(i14.title);
              Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.Body_L'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__',
              });
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
              Text.layoutWeight(1);
            }, Text);
            Text.pop();
            this.observeComponentCreation2((e15, f15) => {
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
              Radio.checked(this.selectedIndex === h14);
              Radio.hitTestBehavior(HitTestMode.None);
              Radio.id(String(h14));
              Radio.onFocus(() => {
                if (h14 == FIRST_ITEM_INDEX) {
                  this.contentScroller.scrollEdge(Edge.Top);
                }
                else if (h14 == this.radioContent.length - 1) {
                  this.contentScroller.scrollEdge(Edge.Bottom);
                }
              });
            }, Radio);
            Row.pop();
            Button.pop();
            this.observeComponentCreation2((x14, y14) => {
              If.create();
              if (h14 && h14 < this.radioContent.length - 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation2((c15, d15) => {
                    Divider.create();
                    Divider.color(ObservedObject.GetRawObject(this.dividerColorWithTheme));
                    Divider.padding({
                      left: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.padding_level6'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                      },
                      right: {
                        'id': -1,
                        'type': 10002,
                        params: ['sys.float.padding_level6'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__',
                      },
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
          this.observeComponentCreation2(k14, ListItem);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(c14, this.radioContent, e14, undefined, true, false);
    }, ForEach);
    ForEach.pop();
    List.pop();
    Column.pop();
    Scroll.pop();
  }
  initialRender() {
    {
      this.observeComponentCreation2((q13, r13) => {
        if (r13) {
          let s13 = new CustomDialogComponent(this, {
            controller: this.controller,
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding,
            theme: this.theme,
          }, undefined, q13, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 376, col: 5 });
          ViewPU.create(s13);
          let t13 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.title,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              contentAreaPadding: this.contentPadding,
              theme: this.theme,
            };
          };
          s13.paramsGenerator_ = t13;
        }
        else {
          this.updateStateVarsOfChildByElmtId(q13, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
  }
  aboutToAppear() {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
      this.theme.colors.fontPrimary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.dividerColorWithTheme = this.theme?.colors?.compDivider ?
      this.theme.colors.compDivider : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.comp_divider'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.initContentPadding();
    this.initButtons();
  }
  initContentPadding() {
    this.contentPadding = {
      left: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level0'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      right: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level0'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
    };
    if (!this.title && !this.confirm) {
      this.contentPadding = {
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
      return;
    }
    if (!this.title) {
      this.contentPadding = {
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      };
    }
    else if (!this.confirm) {
      this.contentPadding = {
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level12'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        }
      };
    }
  }
  initButtons() {
    this.buttons = [];
    if (this.confirm) {
      this.buttons.push(this.confirm);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export class ConfirmDialog extends ViewPU {
  constructor(j13, k13, l13, m13 = -1, n13 = undefined, o13) {
    super(j13, l13, m13, o13);
    if (typeof n13 === 'function') {
      this.paramsGenerator_ = n13;
    }
    this.controller = undefined;
    this.title = '';
    this.content = '';
    this.checkTips = '';
    this.__isChecked = new ObservedPropertySimplePU(false, this, 'isChecked');
    this.primaryButton = { value: '' };
    this.secondaryButton = { value: '' };
    this.__fontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'fontColorWithTheme');
    this.__buttonFontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_emphasize'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'buttonFontColorWithTheme');
    this.theme = new CustomThemeImpl({});
    this.setInitiallyProvidedValue(k13);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(i13) {
    if (i13.controller !== undefined) {
      this.controller = i13.controller;
    }
    if (i13.title !== undefined) {
      this.title = i13.title;
    }
    if (i13.content !== undefined) {
      this.content = i13.content;
    }
    if (i13.checkTips !== undefined) {
      this.checkTips = i13.checkTips;
    }
    if (i13.isChecked !== undefined) {
      this.isChecked = i13.isChecked;
    }
    if (i13.primaryButton !== undefined) {
      this.primaryButton = i13.primaryButton;
    }
    if (i13.secondaryButton !== undefined) {
      this.secondaryButton = i13.secondaryButton;
    }
    if (i13.fontColorWithTheme !== undefined) {
      this.fontColorWithTheme = i13.fontColorWithTheme;
    }
    if (i13.buttonFontColorWithTheme !== undefined) {
      this.buttonFontColorWithTheme = i13.buttonFontColorWithTheme;
    }
    if (i13.theme !== undefined) {
      this.theme = i13.theme;
    }
  }
  updateStateVars(h13) {
  }
  purgeVariableDependenciesOnElmtId(g13) {
    this.__isChecked.purgeDependencyOnElmtId(g13);
    this.__fontColorWithTheme.purgeDependencyOnElmtId(g13);
    this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(g13);
  }
  aboutToBeDeleted() {
    this.__isChecked.aboutToBeDeleted();
    this.__fontColorWithTheme.aboutToBeDeleted();
    this.__buttonFontColorWithTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(f13) {
    this.controller = f13;
  }
  get isChecked() {
    return this.__isChecked.get();
  }
  set isChecked(e13) {
    this.__isChecked.set(e13);
  }
  get fontColorWithTheme() {
    return this.__fontColorWithTheme.get();
  }
  set fontColorWithTheme(d13) {
    this.__fontColorWithTheme.set(d13);
  }
  get buttonFontColorWithTheme() {
    return this.__buttonFontColorWithTheme.get();
  }
  set buttonFontColorWithTheme(c13) {
    this.__buttonFontColorWithTheme.set(c13);
  }
  initialRender() {
    this.observeComponentCreation2((a13, b13) => {
      Column.create();
      Column.backgroundBlurStyle(BlurStyle.Thick);
      Column.borderRadius({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_dialog'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Column.margin({
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_dialog_margin_start'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_dialog_margin_end'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.ohos_id_dialog_margin_bottom'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      });
      Column.backgroundColor({
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_dialog_bg'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
    }, Column);
    this.observeComponentCreation2((y12, z12) => {
      Row.create();
      Row.padding({ left: 24, right: 24, top: 24 });
      Row.constraintSize({ minHeight: 56 });
    }, Row);
    this.observeComponentCreation2((w12, x12) => {
      Text.create(this.title);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_dialog_tittle'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(CONTENT_MAX_LINES);
      Text.minFontSize(15);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
      Text.textAlign(TextAlign.Start);
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((m12, n12) => {
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((u12, v12) => {
            Row.create();
            Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
            Row.width('100%');
            Row.constraintSize({ minHeight: 36 });
          }, Row);
          this.observeComponentCreation2((s12, t12) => {
            Text.create(this.content);
            Text.focusable(true);
            Text.defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value));
            Text.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.ohos_id_text_size_body1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
            Text.maxLines(CONTENT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.ohos_id_text_size_body3'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
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
    this.observeComponentCreation2((k12, l12) => {
      Row.create();
      Row.height(CHECKBOX_CONTAINER_HEIGHT);
      Row.width('100%');
      Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
    }, Row);
    this.observeComponentCreation2((g12, h12) => {
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((j12) => {
        this.isChecked = j12;
      });
      Checkbox.margin({ left: 0, right: 8 });
    }, Checkbox);
    Checkbox.pop();
    this.observeComponentCreation2((d12, e12) => {
      Text.create(this.checkTips);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
      Text.maxLines(CONTENT_MAX_LINES);
      Text.layoutWeight(1);
      Text.focusable(false);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.onClick(() => {
        this.isChecked = !this.isChecked;
      });
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((b12, c12) => {
      Row.create();
      Row.width('100%');
      Row.padding({ left: 16, right: 16, top: 16, bottom: 16 });
    }, Row);
    this.observeComponentCreation2((t11, u11) => {
      If.create();
      if (this.primaryButton?.value) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((y11, z11) => {
            Button.createWithLabel(this.primaryButton.value);
            Button.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.ohos_id_text_size_button1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Button.fontWeight(FontWeight.Medium);
            Button.layoutWeight(1);
            Button.defaultFocus(true);
            Button.backgroundColor(this.primaryButton.background ? this.primaryButton.background : {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_background_transparent'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Button.fontColor(this.primaryButton.fontColor ? this.primaryButton.fontColor : this.buttonFontColorWithTheme);
            Button.onClick(() => {
              if (this.primaryButton?.action)
                this.primaryButton.action();
              this.controller.close();
            });
          }, Button);
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((e11, f11) => {
      If.create();
      if (this.secondaryButton?.value && this.primaryButton?.value) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r11, s11) => {
            Column.create();
            Column.width(DIVIDER_CONTAINER_WIDTH);
            Column.alignItems(HorizontalAlign.Center);
          }, Column);
          this.observeComponentCreation2((k11, l11) => {
            If.create();
            if (!this.secondaryButton.background) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((p11, q11) => {
                  Divider.create();
                  Divider.width(DIVIDER_WIDTH);
                  Divider.height(DIVIDER_HEIGHT);
                  Divider.color({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_list_separator'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  });
                  Divider.vertical(true);
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
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((w10, x10) => {
      If.create();
      if (this.secondaryButton?.value) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b11, c11) => {
            Button.createWithLabel(this.secondaryButton.value);
            Button.fontSize({
              'id': -1,
              'type': 10002,
              params: ['sys.float.ohos_id_text_size_button1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Button.fontWeight(FontWeight.Medium);
            Button.layoutWeight(1);
            Button.defaultFocus(true);
            Button.backgroundColor(this.secondaryButton.background ? this.secondaryButton.background : {
              'id': -1,
              'type': 10001,
              params: ['sys.color.ohos_id_color_background_transparent'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Button.fontColor(this.secondaryButton.fontColor ?
            this.secondaryButton.fontColor : this.buttonFontColorWithTheme);
            Button.onClick(() => {
              if (this.secondaryButton?.action)
                this.secondaryButton.action();
              this.controller.close();
            });
          }, Button);
          Button.pop();
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
  aboutToAppear() {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
      this.theme.colors.fontPrimary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.buttonFontColorWithTheme = this.theme?.colors?.fontEmphasize ?
      this.theme.colors.fontEmphasize : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_emphasize'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export class AlertDialog extends ViewPU {
  constructor(f10, g10, h10, i10 = -1, j10 = undefined, k10) {
    super(f10, h10, i10, k10);
    if (typeof j10 === 'function') {
      this.paramsGenerator_ = j10;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.content = '';
    this.primaryButton = null;
    this.secondaryButton = null;
    this.buttons = undefined;
    this.__textAlign = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlign');
    this.contentScroller = new Scroller();
    this.__fontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'fontColorWithTheme');
    this.theme = new CustomThemeImpl({});
    this.setInitiallyProvidedValue(g10);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(e10) {
    if (e10.controller !== undefined) {
      this.controller = e10.controller;
    }
    if (e10.primaryTitle !== undefined) {
      this.primaryTitle = e10.primaryTitle;
    }
    if (e10.secondaryTitle !== undefined) {
      this.secondaryTitle = e10.secondaryTitle;
    }
    if (e10.content !== undefined) {
      this.content = e10.content;
    }
    if (e10.primaryButton !== undefined) {
      this.primaryButton = e10.primaryButton;
    }
    if (e10.secondaryButton !== undefined) {
      this.secondaryButton = e10.secondaryButton;
    }
    if (e10.buttons !== undefined) {
      this.buttons = e10.buttons;
    }
    if (e10.textAlign !== undefined) {
      this.textAlign = e10.textAlign;
    }
    if (e10.contentScroller !== undefined) {
      this.contentScroller = e10.contentScroller;
    }
    if (e10.fontColorWithTheme !== undefined) {
      this.fontColorWithTheme = e10.fontColorWithTheme;
    }
    if (e10.theme !== undefined) {
      this.theme = e10.theme;
    }
  }
  updateStateVars(d10) {
  }
  purgeVariableDependenciesOnElmtId(c10) {
    this.__textAlign.purgeDependencyOnElmtId(c10);
    this.__fontColorWithTheme.purgeDependencyOnElmtId(c10);
  }
  aboutToBeDeleted() {
    this.__textAlign.aboutToBeDeleted();
    this.__fontColorWithTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(b10) {
    this.controller = b10;
  }
  get textAlign() {
    return this.__textAlign.get();
  }
  set textAlign(a10) {
    this.__textAlign.set(a10);
  }
  get fontColorWithTheme() {
    return this.__fontColorWithTheme.get();
  }
  set fontColorWithTheme(z9) {
    this.__fontColorWithTheme.set(z9);
  }
  initialRender() {
    {
      this.observeComponentCreation2((t9, u9) => {
        if (u9) {
          let v9 = new CustomDialogComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            controller: this.controller,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
            theme: this.theme,
          }, undefined, t9, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 565, col: 5 });
          ViewPU.create(v9);
          let w9 = () => {
            return {
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              controller: this.controller,
              contentBuilder: () => {
                this.AlertDialogContentBuilder();
              },
              buttons: this.buttons,
              theme: this.theme,
            };
          };
          v9.paramsGenerator_ = w9;
        }
        else {
          this.updateStateVarsOfChildByElmtId(t9, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
  }
  AlertDialogContentBuilder(d9 = null) {
    this.observeComponentCreation2((q9, r9) => {
      Column.create();
      Column.margin({ right: `${this.getMargin()}vp`, });
    }, Column);
    this.observeComponentCreation2((o9, p9) => {
      Scroll.create(this.contentScroller);
      Scroll.width('100%');
    }, Scroll);
    this.observeComponentCreation2((h9, i9) => {
      Text.create(this.content);
      Text.focusable(true);
      Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.fontWeight(this.getFontWeight());
      Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
      Text.margin({
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.padding_level8'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      });
      Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
      Text.textAlign(this.textAlign);
      Text.onAreaChange((m9, n9) => {
        this.getTextAlign(Number(n9.width));
      });
      Text.onKeyEvent((l9) => {
        if (l9) {
          resolveKeyEvent(l9, this.contentScroller);
        }
      });
    }, Text);
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  aboutToAppear() {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
      this.theme.colors.fontPrimary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.initButtons();
  }
  getTextAlign(a9) {
    let b9 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      constraintWidth: a9,
    });
    let c9 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
    });
    if (this.getTextHeight(b9) <= this.getTextHeight(c9)) {
      this.textAlign = TextAlign.Center;
    }
  }
  getTextHeight(z8) {
    if (z8 && z8.height !== null && z8.height !== undefined) {
      return Number(z8.height);
    }
    return 0;
  }
  initButtons() {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }
  getMargin() {
    return 0 - getNumberByResource('padding_level8');
  }
  getFontWeight() {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return FontWeight.Medium;
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class CustomContentDialog extends ViewPU {
  constructor(t8, u8, v8, w8 = -1, x8 = undefined, y8) {
    super(t8, v8, w8, y8);
    if (typeof x8 === 'function') {
      this.paramsGenerator_ = x8;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.contentAreaPadding = undefined;
    this.buttons = undefined;
    this.theme = new CustomThemeImpl({});
    this.setInitiallyProvidedValue(u8);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s8) {
    if (s8.controller !== undefined) {
      this.controller = s8.controller;
    }
    if (s8.primaryTitle !== undefined) {
      this.primaryTitle = s8.primaryTitle;
    }
    if (s8.secondaryTitle !== undefined) {
      this.secondaryTitle = s8.secondaryTitle;
    }
    if (s8.contentBuilder !== undefined) {
      this.contentBuilder = s8.contentBuilder;
    }
    if (s8.contentAreaPadding !== undefined) {
      this.contentAreaPadding = s8.contentAreaPadding;
    }
    if (s8.buttons !== undefined) {
      this.buttons = s8.buttons;
    }
    if (s8.theme !== undefined) {
      this.theme = s8.theme;
    }
  }
  updateStateVars(r8) {
  }
  purgeVariableDependenciesOnElmtId(q8) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(p8) {
    this.controller = p8;
  }
  initialRender() {
    {
      this.observeComponentCreation2((j8, k8) => {
        if (k8) {
          let l8 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
            theme: this.theme,
          }, undefined, j8, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 669, col: 5 });
          ViewPU.create(l8);
          let m8 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              contentAreaPadding: this.contentAreaPadding,
              buttons: this.buttons,
              theme: this.theme,
            };
          };
          l8.paramsGenerator_ = m8;
        }
        else {
          this.updateStateVarsOfChildByElmtId(j8, {});
        }
      }, { name: 'CustomDialogContentComponent' });
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class CustomDialogContentComponent extends ViewPU {
  constructor(c8, d8, e8, f8 = -1, g8 = undefined, h8) {
    super(c8, e8, f8, h8);
    if (typeof g8 === 'function') {
      this.paramsGenerator_ = g8;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = this.defaultContentBuilder;
    this.buttons = undefined;
    this.contentAreaPadding = undefined;
    this.keyIndex = 0;
    this.__primaryTitleFontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'primaryTitleFontColorWithTheme');
    this.__secondaryTitleFontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_secondary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'secondaryTitleFontColorWithTheme');
    this.__buttonFontColorWithTheme = new ObservedPropertyObjectPU('', this, 'buttonFontColorWithTheme');
    this.__errorButtonFontColorWithTheme = new ObservedPropertyObjectPU('', this, 'errorButtonFontColorWithTheme');
    this.theme = new CustomThemeImpl({});
    this.titleHeight = 0;
    this.__contentMaxHeight = new ObservedPropertySimplePU('', this, 'contentMaxHeight');
    this.setInitiallyProvidedValue(d8);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(b8) {
    if (b8.controller !== undefined) {
      this.controller = b8.controller;
    }
    if (b8.primaryTitle !== undefined) {
      this.primaryTitle = b8.primaryTitle;
    }
    if (b8.secondaryTitle !== undefined) {
      this.secondaryTitle = b8.secondaryTitle;
    }
    if (b8.contentBuilder !== undefined) {
      this.contentBuilder = b8.contentBuilder;
    }
    if (b8.buttons !== undefined) {
      this.buttons = b8.buttons;
    }
    if (b8.contentAreaPadding !== undefined) {
      this.contentAreaPadding = b8.contentAreaPadding;
    }
    if (b8.keyIndex !== undefined) {
      this.keyIndex = b8.keyIndex;
    }
    if (b8.primaryTitleFontColorWithTheme !== undefined) {
      this.primaryTitleFontColorWithTheme = b8.primaryTitleFontColorWithTheme;
    }
    if (b8.secondaryTitleFontColorWithTheme !== undefined) {
      this.secondaryTitleFontColorWithTheme = b8.secondaryTitleFontColorWithTheme;
    }
    if (b8.buttonFontColorWithTheme !== undefined) {
      this.buttonFontColorWithTheme = b8.buttonFontColorWithTheme;
    }
    if (b8.errorButtonFontColorWithTheme !== undefined) {
      this.errorButtonFontColorWithTheme = b8.errorButtonFontColorWithTheme;
    }
    if (b8.theme !== undefined) {
      this.theme = b8.theme;
    }
    if (b8.titleHeight !== undefined) {
      this.titleHeight = b8.titleHeight;
    }
    if (b8.contentMaxHeight !== undefined) {
      this.contentMaxHeight = b8.contentMaxHeight;
    }
  }
  updateStateVars(a8) {
  }
  purgeVariableDependenciesOnElmtId(z7) {
    this.__primaryTitleFontColorWithTheme.purgeDependencyOnElmtId(z7);
    this.__secondaryTitleFontColorWithTheme.purgeDependencyOnElmtId(z7);
    this.__buttonFontColorWithTheme.purgeDependencyOnElmtId(z7);
    this.__errorButtonFontColorWithTheme.purgeDependencyOnElmtId(z7);
    this.__contentMaxHeight.purgeDependencyOnElmtId(z7);
  }
  aboutToBeDeleted() {
    this.__primaryTitleFontColorWithTheme.aboutToBeDeleted();
    this.__secondaryTitleFontColorWithTheme.aboutToBeDeleted();
    this.__buttonFontColorWithTheme.aboutToBeDeleted();
    this.__errorButtonFontColorWithTheme.aboutToBeDeleted();
    this.__contentMaxHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get primaryTitleFontColorWithTheme() {
    return this.__primaryTitleFontColorWithTheme.get();
  }
  set primaryTitleFontColorWithTheme(y7) {
    this.__primaryTitleFontColorWithTheme.set(y7);
  }
  get secondaryTitleFontColorWithTheme() {
    return this.__secondaryTitleFontColorWithTheme.get();
  }
  set secondaryTitleFontColorWithTheme(x7) {
    this.__secondaryTitleFontColorWithTheme.set(x7);
  }
  get buttonFontColorWithTheme() {
    return this.__buttonFontColorWithTheme.get();
  }
  set buttonFontColorWithTheme(w7) {
    this.__buttonFontColorWithTheme.set(w7);
  }
  get errorButtonFontColorWithTheme() {
    return this.__errorButtonFontColorWithTheme.get();
  }
  set errorButtonFontColorWithTheme(v7) {
    this.__errorButtonFontColorWithTheme.set(v7);
  }
  defaultContentBuilder(u7 = null) {
  }
  get contentMaxHeight() {
    return this.__contentMaxHeight.get();
  }
  set contentMaxHeight(t7) {
    this.__contentMaxHeight.set(t7);
  }
  initialRender() {
    this.observeComponentCreation2((r7, s7) => {
      WithTheme.create({ theme: this.theme });
    }, WithTheme);
    this.observeComponentCreation2((p7, q7) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.buildTitles.bind(this)();
    this.observeComponentCreation2((n7, o7) => {
      Column.create();
      Column.padding(this.getContentPadding());
      Column.constraintSize({ maxHeight: this.contentMaxHeight });
    }, Column);
    this.contentBuilder.bind(this)();
    Column.pop();
    this.buildButtons.bind(this)();
    Column.pop();
    WithTheme.pop();
  }
  buildTitles(g6 = null) {
    this.observeComponentCreation2((f7, g7) => {
      Column.create();
      Column.constraintSize({
        minHeight: this.getTitleAreaMinHeight(),
      });
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
      Column.onAreaChange((i7, j7) => {
        this.titleHeight = Number(j7.height);
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
      });
    }, Column);
    this.observeComponentCreation2((d7, e7) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((b7, c7) => {
      Text.create(this.primaryTitle);
      Text.fontWeight(FontWeight.Bold);
      Text.fontColor(ObservedObject.GetRawObject(this.primaryTitleFontColorWithTheme));
      Text.textAlign(this.getTitleTextAlign());
      Text.maxFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Title_S'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.minFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((r6, s6) => {
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((z6, a7) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((x6, y6) => {
            Divider.create();
            Divider.margin({
              'id': -1,
              'type': 10002,
              params: ['sys.float.padding_level1'],
              'bundleName': '__harDefaultBundleName__',
              'moduleName': '__harDefaultModuleName__',
            });
            Divider.color(Color.Transparent);
          }, Divider);
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((p6, q6) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((n6, o6) => {
      Text.create(this.secondaryTitle);
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor(ObservedObject.GetRawObject(this.secondaryTitleFontColorWithTheme));
      Text.textAlign(this.getTitleTextAlign());
      Text.maxFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Subtitle_S'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.minFontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_S'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    Column.pop();
  }
  buildButtons(c6 = null) {
    this.observeComponentCreation2((e6, f6) => {
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
    }, Column);
    this.buildHorizontalAlignButtons.bind(this)();
    this.buildVerticalAlignButtons.bind(this)();
    Column.pop();
  }
  buildSingleButton(d5, e5 = null) {
    this.observeComponentCreation2((g5, h5) => {
      If.create();
      if (this.isNewPropertiesHighPriority(d5)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((a6, b6) => {
            Button.createWithLabel(d5.value);
            __Button__setButtonProperties(d5, this.controller);
            Button.role(d5.role ?? ButtonRole.NORMAL);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
          }, Button);
          Button.pop();
        });
      }
      else if (d5.background !== undefined && d5.fontColor !== undefined) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((w5, x5) => {
            Button.createWithLabel(d5.value);
            __Button__setButtonProperties(d5, this.controller);
            Button.backgroundColor(d5.background);
            Button.fontColor(d5.fontColor);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
          }, Button);
          Button.pop();
        });
      }
      else if (d5.background !== undefined) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((s5, t5) => {
            Button.createWithLabel(d5.value);
            __Button__setButtonProperties(d5, this.controller);
            Button.backgroundColor(d5.background);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
          }, Button);
          Button.pop();
        });
      }
      else if (d5.background !== undefined && d5.fontColor === undefined || '') {
        this.ifElseBranchUpdateFunction(3, () => {
          this.observeComponentCreation2((o5, p5) => {
            Button.createWithLabel(d5.value);
            __Button__setButtonProperties(d5, this.controller);
            Button.backgroundColor(d5.background);
            Button.fontColor(d5.role === ButtonRole.ERROR ?
            this.errorButtonFontColorWithTheme : this.buttonFontColorWithTheme);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
          }, Button);
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(4, () => {
          this.observeComponentCreation2((k5, l5) => {
            Button.createWithLabel(d5.value);
            __Button__setButtonProperties(d5, this.controller);
            Button.fontColor(d5.fontColor);
            Button.key(`advanced_dialog_button_${this.keyIndex++}`);
          }, Button);
          Button.pop();
        });
      }
    }, If);
    If.pop();
  }
  buildHorizontalAlignButtons(m4 = null) {
    this.observeComponentCreation2((o4, p4) => {
      If.create();
      if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((b5, c5) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(this.buttons[0]);
          this.observeComponentCreation2((u4, v4) => {
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((z4, a5) => {
                  Divider.create();
                  Divider.width({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_divider_width'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  });
                  Divider.height({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_divider_height'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                  });
                  Divider.color(this.getDividerColor());
                  Divider.vertical(true);
                  Divider.margin({
                    left: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.alert_button_horizontal_space'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__',
                    },
                    right: {
                      'id': -1,
                      'type': 10002,
                      params: ['sys.float.alert_button_horizontal_space'],
                      'bundleName': '__harDefaultBundleName__',
                      'moduleName': '__harDefaultModuleName__',
                    },
                  });
                }, Divider);
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
  buildVerticalAlignButtons(t3 = null) {
    this.observeComponentCreation2((v3, w3) => {
      If.create();
      if (this.buttons && this.isVerticalAlignButton()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((k4, l4) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((b4, c4) => {
            ForEach.create();
            const d4 = (h4, i4) => {
              const j4 = h4;
              this.buildButtonWithDivider.bind(this)(i4);
            };
            this.forEachUpdateFunction(b4, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), d4,
              (g4) => g4.value.toString(), true, false);
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
  buildButtonWithDivider(b3, c3 = null) {
    this.observeComponentCreation2((e3, f3) => {
      If.create();
      if (this.buttons && this.buttons[b3]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r3, s3) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(this.buttons[b3]);
          Row.pop();
          this.observeComponentCreation2((k3, l3) => {
            If.create();
            if (b3 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((p3, q3) => {
                  Row.create();
                  Row.height({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.alert_button_vertical_space'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
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
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
  }
  aboutToAppear() {
    if (this.primaryTitle) {
      this.titleHeight = getNumberByResource('alert_title_primary_height');
    }
    if (this.secondaryTitle) {
      this.titleHeight = getNumberByResource('alert_title_secondary_height');
    }
    this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
    this.primaryTitleFontColorWithTheme = this.theme?.colors?.fontPrimary ?
      this.theme.colors.fontPrimary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.secondaryTitleFontColorWithTheme = this.theme?.colors?.fontSecondary ?
      this.theme.colors.fontSecondary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.buttonFontColorWithTheme = this.theme?.colors?.fontEmphasize ?
      this.theme.colors.fontEmphasize : '';
    this.errorButtonFontColorWithTheme = this.theme?.colors?.warning ?
      this.theme.colors.warning : '';
  }
  getDividerColor() {
    if (!this.buttons || this.buttons.length === 0 || !getNumberByResource('dialog_divider_show')) {
      return Color.Transparent;
    }
    if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
      if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
        this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
        return {
          'id': -1,
          'type': 10001,
          params: ['sys.color.alert_divider_color'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        };
      }
    }
    return Color.Transparent;
  }
  getButtonsHeight() {
    if (!this.buttons || this.buttons.length === 0) {
      return 0;
    }
    let a3 = getNumberByResource('alert_button_top_padding');
    if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
      a3 += BUTTON_DEFAULT_HEIGHT +
      getNumberByResource('alert_button_bottom_padding_horizontal');
    }
    else {
      a3 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
        (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
      getNumberByResource('alert_button_bottom_padding_vertical');
    }
    return a3;
  }
  getContentPadding() {
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }
    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: 0,
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
    }
    else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
    }
    else if (this.buttons && this.buttons.length > 0) {
      return {
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: 0,
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
    }
    else {
      return {
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_content_default_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
    }
  }
  getTitleAreaMinHeight() {
    if (this.secondaryTitle) {
      return {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_title_secondary_height'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    }
    else if (this.primaryTitle) {
      return {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_title_primary_height'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    }
    else {
      return 0;
    }
  }
  getTitleAreaPadding() {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_title_padding_top'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_title_padding_right'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_title_padding_left'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_title_padding_bottom'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
    }
    return {
      top: 0,
      right: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_title_padding_right'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      left: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_title_padding_left'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      bottom: 0,
    };
  }
  isVerticalAlignButton() {
    if (this.buttons) {
      return this.buttons.length > HORIZON_BUTTON_MAX_COUNT;
    }
    return false;
  }
  getOperationAreaPadding() {
    if (this.isVerticalAlignButton()) {
      return {
        top: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_button_top_padding'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        right: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_right_padding_vertical'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        left: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_left_padding_vertical'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
        bottom: {
          'id': -1,
          'type': 10002,
          params: ['sys.float.alert_button_bottom_padding_vertical'],
          'bundleName': '__harDefaultBundleName__',
          'moduleName': '__harDefaultModuleName__',
        },
      };
    }
    return {
      top: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_button_top_padding'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      right: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_right_padding_horizontal'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      left: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_left_padding_horizontal'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      bottom: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.alert_button_bottom_padding_horizontal'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
    };
  }
  isNewPropertiesHighPriority(z2) {
    if (z2.role === ButtonRole.ERROR) {
      return true;
    }
    if (z2.buttonStyle !== undefined &&
      z2.buttonStyle !== getNumberByResource('alert_button_style')) {
      return true;
    }
    if (z2.background === undefined && z2.fontColor === undefined) {
      return true;
    }
    return false;
  }
  getTitleTextAlign() {
    let y2 = getEnumNumberByResource('alert_title_alignment');
    if (y2 === TextAlign.Start) {
      return TextAlign.Start;
    }
    else if (y2 === TextAlign.Center) {
      return TextAlign.Center;
    }
    else if (y2 === TextAlign.End) {
      return TextAlign.End;
    }
    else if (y2 === TextAlign.JUSTIFY) {
      return TextAlign.JUSTIFY;
    }
    else {
      return TextAlign.Center;
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class CustomDialogComponent extends ViewPU {
  constructor(s2, t2, u2, v2 = -1, w2 = undefined, x2) {
    super(s2, u2, v2, x2);
    if (typeof w2 === 'function') {
      this.paramsGenerator_ = w2;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.buttons = undefined;
    this.contentAreaPadding = undefined;
    this.screenWidth = 0;
    this.__columnModifier = new ObservedPropertyObjectPU(new ColumnModifier(), this, 'columnModifier');
    this.isFirstInit = true;
    this.theme = new CustomThemeImpl({});
    this.setInitiallyProvidedValue(t2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(r2) {
    if (r2.controller !== undefined) {
      this.controller = r2.controller;
    }
    if (r2.primaryTitle !== undefined) {
      this.primaryTitle = r2.primaryTitle;
    }
    if (r2.secondaryTitle !== undefined) {
      this.secondaryTitle = r2.secondaryTitle;
    }
    if (r2.contentBuilder !== undefined) {
      this.contentBuilder = r2.contentBuilder;
    }
    if (r2.buttons !== undefined) {
      this.buttons = r2.buttons;
    }
    if (r2.contentAreaPadding !== undefined) {
      this.contentAreaPadding = r2.contentAreaPadding;
    }
    if (r2.screenWidth !== undefined) {
      this.screenWidth = r2.screenWidth;
    }
    if (r2.columnModifier !== undefined) {
      this.columnModifier = r2.columnModifier;
    }
    if (r2.isFirstInit !== undefined) {
      this.isFirstInit = r2.isFirstInit;
    }
    if (r2.theme !== undefined) {
      this.theme = r2.theme;
    }
  }
  updateStateVars(q2) {
  }
  purgeVariableDependenciesOnElmtId(p2) {
    this.__columnModifier.purgeDependencyOnElmtId(p2);
  }
  aboutToBeDeleted() {
    this.__columnModifier.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get columnModifier() {
    return this.__columnModifier.get();
  }
  set columnModifier(o2) {
    this.__columnModifier.set(o2);
  }
  initialRender() {
    this.observeComponentCreation2((j2, k2) => {
      Column.create();
      Column.onAreaChange((m2, n2) => {
        if (!this.isFirstInit) {
          return;
        }
        if (this.screenWidth > getNumberByResource('alert_container_max_width')) {
          this.columnModifier.customStyle = n2.width > getNumberByResource('alert_container_max_width');
        }
        else {
          this.columnModifier.customStyle = n2.width >= this.screenWidth;
        }
        this.isFirstInit = false;
      });
    }, Column);
    this.observeComponentCreation2((h2, i2) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.columnModifier));
    }, Column);
    {
      this.observeComponentCreation2((b2, c2) => {
        if (c2) {
          let d2 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentAreaPadding,
            theme: this.theme,
          }, undefined, b2, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1093, col: 9 });
          ViewPU.create(d2);
          let e2 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              contentAreaPadding: this.contentAreaPadding,
              theme: this.theme,
            };
          };
          d2.paramsGenerator_ = e2;
        }
        else {
          this.updateStateVarsOfChildByElmtId(b2, {});
        }
      }, { name: 'CustomDialogContentComponent' });
    }
    Column.pop();
    Column.pop();
  }
  aboutToAppear() {
    try {
      this.screenWidth = px2vp(display.getDefaultDisplaySync().width);
    }
    catch (x1) {
      hilog.error(0x3900, 'Ace', `CustomDialogComponent getDefaultDisplaySync error: ${JSON.stringify(x1)}`);
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class ColumnModifier {
  constructor() {
    this.customStyle = false;
  }
  applyNormalAttribute(w1) {
    if (!this.customStyle) {
      return;
    }
    w1.backgroundBlurStyle(BlurStyle.Thick);
    w1.borderRadius({
      'id': -1,
      'type': 10002,
      params: ['sys.float.ohos_id_corner_radius_dialog'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    });
    w1.margin({
      left: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_dialog_margin_start'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      right: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_dialog_margin_end'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
      bottom: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_dialog_margin_bottom'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      },
    });
    w1.backgroundColor({
      'id': -1,
      'type': 10001,
      params: ['sys.color.ohos_id_color_dialog_bg'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    });
  }
}
function __Button__setButtonProperties(t1, u1) {
  Button.onClick(() => {
    if (t1.action) {
      t1.action();
    }
    u1?.close();
  });
  Button.defaultFocus(true);
  Button.buttonStyle(t1.buttonStyle ?? getNumberByResource('alert_button_style'));
  Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}
function getNumberByResource(p1) {
  try {
    return resourceManager.getSystemResourceManager().getNumberByName(p1);
  }
  catch (q1) {
    let r1 = q1.code;
    let s1 = q1.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${r1}, message: ${s1}`);
    return 0;
  }
}
function getEnumNumberByResource(l1) {
  try {
    return getContext().resourceManager.getNumberByName(l1);
  }
  catch (m1) {
    let n1 = m1.code;
    let o1 = m1.message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${n1}, message: ${o1}`);
    return -1;
  }
}
function resolveKeyEvent(j1, k1) {
  if (j1.type == IGNORE_KEY_EVENT_TYPE) {
    return;
  }
  if (j1.keyCode == KEYCODE_UP) {
    k1.scrollPage({ next: false });
    j1.stopPropagation();
  }
  else if (j1.keyCode == KEYCODE_DOWN) {
    if (k1.isAtEnd()) {
      return;
    }
    else {
      k1.scrollPage({ next: true });
      j1.stopPropagation();
    }
  }
}
export class LoadingDialog extends ViewPU {
  constructor(d1, e1, f1, g1 = -1, h1 = undefined, i1) {
    super(d1, f1, g1, i1);
    if (typeof h1 === 'function') {
      this.paramsGenerator_ = h1;
    }
    this.controller = undefined;
    this.content = '';
    this.__fontColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.font_primary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'fontColorWithTheme');
    this.__loadingProgressIconColorWithTheme = new ObservedPropertyObjectPU({
      'id': -1,
      'type': 10001,
      params: ['sys.color.icon_secondary'],
      'bundleName': '__harDefaultBundleName__',
      'moduleName': '__harDefaultModuleName__',
    }, this, 'loadingProgressIconColorWithTheme');
    this.theme = new CustomThemeImpl({});
    this.setInitiallyProvidedValue(e1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(c1) {
    if (c1.controller !== undefined) {
      this.controller = c1.controller;
    }
    if (c1.content !== undefined) {
      this.content = c1.content;
    }
    if (c1.fontColorWithTheme !== undefined) {
      this.fontColorWithTheme = c1.fontColorWithTheme;
    }
    if (c1.loadingProgressIconColorWithTheme !== undefined) {
      this.loadingProgressIconColorWithTheme = c1.loadingProgressIconColorWithTheme;
    }
    if (c1.theme !== undefined) {
      this.theme = c1.theme;
    }
  }
  updateStateVars(b1) {
  }
  purgeVariableDependenciesOnElmtId(a1) {
    this.__fontColorWithTheme.purgeDependencyOnElmtId(a1);
    this.__loadingProgressIconColorWithTheme.purgeDependencyOnElmtId(a1);
  }
  aboutToBeDeleted() {
    this.__fontColorWithTheme.aboutToBeDeleted();
    this.__loadingProgressIconColorWithTheme.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(z) {
    this.controller = z;
  }
  get fontColorWithTheme() {
    return this.__fontColorWithTheme.get();
  }
  set fontColorWithTheme(y) {
    this.__fontColorWithTheme.set(y);
  }
  get loadingProgressIconColorWithTheme() {
    return this.__loadingProgressIconColorWithTheme.get();
  }
  set loadingProgressIconColorWithTheme(x) {
    this.__loadingProgressIconColorWithTheme.set(x);
  }
  initialRender() {
    this.observeComponentCreation2((v, w) => {
      Column.create();
    }, Column);
    {
      this.observeComponentCreation2((p, q) => {
        if (q) {
          let r = new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.contentBuilder();
            },
            theme: this.theme,
          }, undefined, p, () => {
          }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 1229, col: 7 });
          ViewPU.create(r);
          let s = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.contentBuilder();
              },
              theme: this.theme,
            };
          };
          r.paramsGenerator_ = s;
        }
        else {
          this.updateStateVarsOfChildByElmtId(p, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
    Column.pop();
  }
  contentBuilder(a = null) {
    this.observeComponentCreation2((l, m) => {
      Column.create();
    }, Column);
    this.observeComponentCreation2((j, k) => {
      Row.create();
      Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
    }, Row);
    this.observeComponentCreation2((h, i) => {
      Text.create(this.content);
      Text.fontSize({
        'id': -1,
        'type': 10002,
        params: ['sys.float.Body_L'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      });
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor(ObservedObject.GetRawObject(this.fontColorWithTheme));
      Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
      Text.maxLines(LOADING_MAX_LINES);
      Text.focusable(true);
      Text.defaultFocus(true);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
    }, Text);
    Text.pop();
    this.observeComponentCreation2((f, g) => {
      LoadingProgress.create();
      LoadingProgress.color(ObservedObject.GetRawObject(this.loadingProgressIconColorWithTheme));
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ left: LOADING_TEXT_MARGIN_LEFT });
    }, LoadingProgress);
    Row.pop();
    Column.pop();
  }
  aboutToAppear() {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
      this.theme.colors.fontPrimary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.font_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
    this.loadingProgressIconColorWithTheme = this.theme?.colors?.iconSecondary ?
      this.theme.colors.iconSecondary : {
        'id': -1,
        'type': 10001,
        params: ['sys.color.icon_secondary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__',
      };
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog };
