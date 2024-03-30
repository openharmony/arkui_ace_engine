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
  constructor(k19, l19, m19, n19 = -1, o19 = undefined, p19) {
    super(k19, m19, n19, p19);
    if (typeof o19 === 'function') {
      this.paramsGenerator_ = o19;
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
    this.__contentScrollHeight = new ObservedPropertySimplePU("0px", this, "contentScrollHeight");
    this.contentScroller = new Scroller();
    this.setInitiallyProvidedValue(l19);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(j19) {
    if (j19.controller !== undefined) {
      this.controller = j19.controller;
    }
    if (j19.imageRes !== undefined) {
      this.imageRes = j19.imageRes;
    }
    if (j19.imageSize !== undefined) {
      this.imageSize = j19.imageSize;
    }
    if (j19.title !== undefined) {
      this.title = j19.title;
    }
    if (j19.content !== undefined) {
      this.content = j19.content;
    }
    if (j19.checkAction !== undefined) {
      this.checkAction = j19.checkAction;
    }
    if (j19.checkTips !== undefined) {
      this.checkTips = j19.checkTips;
    }
    if (j19.isChecked !== undefined) {
      this.isChecked = j19.isChecked;
    }
    if (j19.primaryButton !== undefined) {
      this.primaryButton = j19.primaryButton;
    }
    if (j19.secondaryButton !== undefined) {
      this.secondaryButton = j19.secondaryButton;
    }
    if (j19.buttons !== undefined) {
      this.buttons = j19.buttons;
    }
    if (j19.imageSizeHeight !== undefined) {
      this.imageSizeHeight = j19.imageSizeHeight;
    }
    if (j19.textAlignment !== undefined) {
      this.textAlignment = j19.textAlignment;
    }
    if (j19.marginOffset !== undefined) {
      this.marginOffset = j19.marginOffset;
    }
    if (j19.checkBoxHeight !== undefined) {
      this.checkBoxHeight = j19.checkBoxHeight;
    }
    if (j19.buttonHeight !== undefined) {
      this.buttonHeight = j19.buttonHeight;
    }
    if (j19.contentScrollHeight !== undefined) {
      this.contentScrollHeight = j19.contentScrollHeight;
    }
    if (j19.contentScroller !== undefined) {
      this.contentScroller = j19.contentScroller;
    }
  }
  updateStateVars(i19) {
  }
  purgeVariableDependenciesOnElmtId(h19) {
    this.__imageSize.purgeDependencyOnElmtId(h19);
    this.__isChecked.purgeDependencyOnElmtId(h19);
    this.__imageSizeHeight.purgeDependencyOnElmtId(h19);
    this.__textAlignment.purgeDependencyOnElmtId(h19);
    this.__checkBoxHeight.purgeDependencyOnElmtId(h19);
    this.__contentScrollHeight.purgeDependencyOnElmtId(h19);
  }
  aboutToBeDeleted() {
    this.__imageSize.aboutToBeDeleted();
    this.__isChecked.aboutToBeDeleted();
    this.__imageSizeHeight.aboutToBeDeleted();
    this.__textAlignment.aboutToBeDeleted();
    this.__checkBoxHeight.aboutToBeDeleted();
    this.__contentScrollHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(g19) {
    this.controller = g19;
  }
  get imageSize() {
    return this.__imageSize.get();
  }
  set imageSize(f19) {
    this.__imageSize.set(f19);
  }
  get isChecked() {
    return this.__isChecked.get();
  }
  set isChecked(e19) {
    this.__isChecked.set(e19);
  }
  get imageSizeHeight() {
    return this.__imageSizeHeight.get();
  }
  set imageSizeHeight(d19) {
    this.__imageSizeHeight.set(d19);
  }
  get textAlignment() {
    return this.__textAlignment.get();
  }
  set textAlignment(c19) {
    this.__textAlignment.set(c19);
  }
  get checkBoxHeight() {
    return this.__checkBoxHeight.get();
  }
  set checkBoxHeight(b19) {
    this.__checkBoxHeight.set(b19);
  }
  get contentScrollHeight() {
    return this.__contentScrollHeight.get();
  }
  set contentScrollHeight(z20) {
    this.__contentScrollHeight.set(z20);
  }
  initialRender() {
    {
      this.observeComponentCreation((v18, w18) => {
        ViewStackProcessor.StartGetAccessRecordingFor(v18);
        if (w18) {
          let x18 = new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
          }, undefined, v18, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 65 });
          ViewPU.create(x18);
          let y18 = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons
            };
          };
          x18.paramsGenerator_ = y18;
        }
        else {
          this.updateStateVarsOfChildByElmtId(v18, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
  }
  contentBuilder(d18 = null) {
    this.observeComponentCreation((s18, t18) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s18);
      Column.create();
      if (!t18) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.imagePart.bind(this)();
    this.observeComponentCreation((l18, m18) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l18);
      If.create();
      if (this.title != null || this.content != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((q18, r18) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q18);
            Column.create();
            Column.padding({ top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '', 'moduleName': '' } });
            Column.constraintSize({
              maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.imageSizeHeight}vp - ${this.buttonHeight}vp)`
            });
            if (!r18) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.textPart.bind(this)();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!m18) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((h18, i18) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h18);
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
      if (!i18) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  checkBoxPart(m17, n17 = null) {
    this.observeComponentCreation((y17, z17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y17);
      Row.create();
      Row.padding({ top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '', 'moduleName': '' } });
      Row.constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT });
      Row.width('100%');
      Row.onAreaChange((b18, c18) => {
        this.checkBoxHeight = Number(c18.height);
      });
      if (!z17) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((u17, v17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(u17);
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((x17) => {
        this.isChecked = x17;
        if (this.checkAction) {
          this.checkAction(x17);
        }
      });
      Checkbox.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '', 'moduleName': '' } });
      if (!v17) {
        Checkbox.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Checkbox.pop();
    this.observeComponentCreation((r17, s17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r17);
      Text.create(m17);
      Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Body_M'], 'bundleName': '', 'moduleName': '' });
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '', 'moduleName': '' });
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
      if (!s17) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
  }
  imagePart(c17 = null) {
    this.observeComponentCreation((h17, i17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h17);
      Column.create();
      Column.width('100%');
      Column.constraintSize({
        maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
      });
      Column.onAreaChange((k17, l17) => {
        this.imageSizeHeight = Number(l17.height);
      });
      if (!i17) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((f17, g17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f17);
      Image.create(this.imageRes);
      Image.size(this.imageSize);
      Image.objectFit(ImageFit.Contain);
      Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level6'], 'bundleName': '', 'moduleName': '' });
      Image.constraintSize({
        maxWidth: '100%',
        maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
      });
      if (!g17) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Column.pop();
  }
  textPart(w15 = null) {
    this.observeComponentCreation((a17, b17) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a17);
      Scroll.create();
      Scroll.margin({ right: `${this.marginOffset}vp` });
      if (!b17) {
        Scroll.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((y16, z16) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y16);
      Column.create();
      Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '', 'moduleName': '' } });
      if (!z16) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((o16, p16) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o16);
      If.create();
      if (this.title != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((w16, x16) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w16);
            Row.create();
            Row.padding({ bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '', 'moduleName': '' } });
            if (!x16) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((u16, v16) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u16);
            Text.create(this.title);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Title_S'], 'bundleName': '', 'moduleName': '' });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '', 'moduleName': '' });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(CONTENT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '', 'moduleName': '' });
            Text.maxFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Title_S'], 'bundleName': '', 'moduleName': '' });
            Text.width('100%');
            if (!v16) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!p16) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((b16, c16) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b16);
      If.create();
      if (this.content != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((m16, n16) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m16);
            Row.create();
            if (!n16) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((i18, j18) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i18);
            Scroll.create(this.contentScroller);
            Scroll.height(this.contentScrollHeight);
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((h16, i16) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h16);
            var c18;
            Text.create(this.content);
            Text.focusable(true);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '', 'moduleName': '' });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '', 'moduleName': '' });
            Text.textAlign(this.textAlignment);
            Text.width('100%');
            Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
            Text.onKeyEvent((h18) => {
              if (h18) {
                resolveKeyEvent(h18, this.contentScroller);
              }
            });
            Text.onSizeChange((k16, l16) => {
              if (l16 && l16.width) {
                this.getContentScrollHeight(Number(l16.width));
                this.getTextAlign(Number(l16.width));
              }
            });
            if (!i16) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Scroll.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!c16) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
    Scroll.pop();
  }
  aboutToAppear() {
    this.initButtons();
    this.initMargin();
  }

  getContentScrollHeight(j17) {
    let k17 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.Body_L'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      },
    });
    let l17 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.Body_L'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      },
      constraintWidth: j17,
    });
    let m17 = Number(k17.height);
    let n17 = Number(l17.height);
    this.contentScrollHeight = Math.min(n17, 10 * m17) + "px";
  }

  getTextAlign(t15) {
    let u15 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '', 'moduleName': '' },
      constraintWidth: t15,
    });
    let v15 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { 'id': -1, 'type': 10002, params: ['sys.float.Body_L'], 'bundleName': '', 'moduleName': '' },
    });
    if (this.getTextHeight(u15) <= this.getTextHeight(v15)) {
      this.textAlignment = TextAlign.Center;
    }
  }
  getTextHeight(s15) {
    if (s15 && s15.height !== null && s15.height !== undefined) {
      return Number(s15.height);
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
    let r15 = getNumberByResource('alert_button_top_padding');
    r15 += BUTTON_DEFAULT_HEIGHT + getNumberByResource('alert_button_bottom_padding_horizontal');
    return r15;
  }
  initMargin() {
    this.marginOffset = 0 - getNumberByResource('padding_level8');
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export class SelectDialog extends ViewPU {
  constructor(j15, k15, l15, m15 = -1, n15 = undefined, o15) {
    super(j15, l15, m15, o15);
    if (typeof n15 === 'function') {
      this.paramsGenerator_ = n15;
    }
    this.title = '';
    this.content = '';
    this.selectedIndex = -1;
    this.confirm = null;
    this.radioContent = [];
    this.buttons = [];
    this.contentPadding = undefined;
    this.contentBuilder = this.buildContent;
    this.controller = new CustomDialogController({
      builder: () => {
        let p15 = new CustomContentDialog(this, {
          primaryTitle: this.title,
          contentBuilder: () => {
            this.contentBuilder();
          },
          buttons: this.buttons,
        }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 254 });
        p15.setController(this.controller);
        ViewPU.create(p15);
        let q15 = () => {
          return {
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons
          };
        };
        p15.paramsGenerator_ = q15;
      }
    }, this);
    this.__contentListHeight = new ObservedPropertyObjectPU(undefined, this, "contentListHeight");
    this.isGetHeight = false;
    this.contentScroller = new Scroller();
    this.setInitiallyProvidedValue(k15);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(i15) {
    if (i15.title !== undefined) {
      this.title = i15.title;
    }
    if (i15.content !== undefined) {
      this.content = i15.content;
    }
    if (i15.selectedIndex !== undefined) {
      this.selectedIndex = i15.selectedIndex;
    }
    if (i15.confirm !== undefined) {
      this.confirm = i15.confirm;
    }
    if (i15.radioContent !== undefined) {
      this.radioContent = i15.radioContent;
    }
    if (i15.buttons !== undefined) {
      this.buttons = i15.buttons;
    }
    if (i15.contentPadding !== undefined) {
      this.contentPadding = i15.contentPadding;
    }
    if (i15.contentBuilder !== undefined) {
      this.contentBuilder = i15.contentBuilder;
    }
    if (i15.controller !== undefined) {
      this.controller = i15.controller;
    }
    if (i15.contentListHeight !== undefined) {
      this.contentListHeight = i15.contentListHeight;
    }
    if (i15.isGetHeight !== undefined) {
      this.isGetHeight = i15.isGetHeight;
    }
    if (i15.contentScroller !== undefined) {
      this.contentScroller = i15.contentScroller;
    }
  }
  updateStateVars(h15) {
  }
  purgeVariableDependenciesOnElmtId(g15) {
    this.__contentListHeight.purgeDependencyOnElmtId(g15);
  }
  aboutToBeDeleted() {
    this.__contentListHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(f15) {
    this.controller = f15;
  }

  get contentListHeight() {
    return this.__contentListHeight.get();
  }

  set contentListHeight(p16) {
    this.__contentListHeight.set(p16);
  }

  buildContent(s12 = null) {
    this.observeComponentCreation((d15, e15) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d15);
      Scroll.create();
      Scroll.scrollBar(BarState.Auto);
      if (!e15) {
        Scroll.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((b15, c15) => {
      ViewStackProcessor.StartGetAccessRecordingFor(b15);
      Column.create();
      if (!c15) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((r14, s14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r14);
      If.create();
      if (this.content) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((z14, a15) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z14);
            Row.create();
            Row.padding({
              left: { id: -1, type: 10002, params: ['sys.float.padding_level12'], bundleName: '', moduleName: '' },
              right: { id: -1, type: 10002, params: ['sys.float.padding_level12'], bundleName: '', moduleName: '' },
              bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' }
            });
            Row.width('100%');
            if (!a15) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((x14, y14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x14);
            Text.create(this.content);
            Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_M'], bundleName: '', moduleName: '' });
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            if (!y14) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!s14) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((p14, q14) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p14);
      var a16;
      List.create({ space: 1, scroller: this.contentScroller });
      List.width('100%');
      List.clip(false);
      List.onFocus(() => {
        this.contentScroller.scrollToIndex(FIRST_ITEM_INDEX);
        focusControl.requestFocus(String(FIRST_ITEM_INDEX));
      });
      List.defaultFocus(((a16 = this.buttons) === null || a16 === void 0 ? void 0 : a16.length) == 0 ? true : false);
      List.height(ObservedObject.GetRawObject(this.contentListHeight));
      if (!q14) {
        List.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((y12, z12) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y12);
      ForEach.create();
      const a13 = (c13, d13) => {
        const e13 = c13;
        {
          const f13 = (n14, o14) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n14);
            g13(n14, o14);
            if (!o14) {
              ListItem.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          };
          const g13 = (l14, m14) => {
            ListItem.create(h13, true);
            ListItem.onSizeChange((u15, v15) => {
              if (!this.isGetHeight && d13 == 0 && this.radioContent.length > 3) {
                this.contentListHeight = 3 * Number(v15.height);
                this.isGetHeight = true;
              }
            });
          };
          const h13 = (l13, m13) => {
            f13(l13, m13);
            this.updateFuncByElmtId.set(l13, f13);
            this.observeComponentCreation((j14, k14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(j14);
              Column.create();
              Column.padding({
                left: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
                right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' }
              });
              if (!k14) {
                Column.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            this.observeComponentCreation((g14, h14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(g14);
              Button.createWithChild();
              Button.type(ButtonType.Normal);
              Button.borderRadius({ id: -1, type: 10002, params: ['sys.float.corner_radius_level8'], bundleName: '', moduleName: '' });
              Button.buttonStyle(ButtonStyleMode.TEXTUAL);
              Button.padding({
                left: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
                right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' }
              });
              Button.onClick(() => {
                e13.action && e13.action();
                this.controller.close();
              });
              if (!h14) {
                Button.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            this.observeComponentCreation((e14, f14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e14);
              Row.create();
              Row.constraintSize({ minHeight: LIST_MIN_HEIGHT });
              Row.clip(false);
              Row.padding({
                top: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' },
                bottom: { id: -1, type: 10002, params: ['sys.float.padding_level4'], bundleName: '', moduleName: '' }
              });
              Row.onClick(() => {
                e13.action && e13.action();
                this.controller.close();
              });
              if (!f14) {
                Row.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            this.observeComponentCreation((c14, d14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(c14);
              Text.create(e13.title);
              Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
              Text.layoutWeight(1);
              if (!d14) {
                Text.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            Text.pop();
            this.observeComponentCreation((a14, b14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(a14);
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH });
              Radio.checked(this.selectedIndex === d13);
              Radio.hitTestBehavior(HitTestMode.None);
              Radio.id(String(d13));
              Radio.onFocus(() => {
                if (d13 == FIRST_ITEM_INDEX) {
                  this.contentScroller.scrollToIndex(FIRST_ITEM_INDEX);
                }
              });
              if (!b14) {
                Radio.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            Row.pop();
            Button.pop();
            this.observeComponentCreation((t13, u13) => {
              ViewStackProcessor.StartGetAccessRecordingFor(t13);
              If.create();
              if (d13 < this.radioContent.length - 1) {
                this.ifElseBranchUpdateFunction(0, () => {
                  this.observeComponentCreation((y13, z13) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(y13);
                    Divider.create();
                    Divider.color({ id: -1, type: 10001, params: ['sys.color.comp_divider'], bundleName: '', moduleName: '' });
                    Divider.padding({
                      left: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' },
                      right: { id: -1, type: 10002, params: ['sys.float.padding_level6'], bundleName: '', moduleName: '' }
                    });
                    if (!z13) {
                      Divider.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                  });
                });
              }
              else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
              }
              if (!u13) {
                If.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          this.observeComponentCreation(f13);
          ListItem.pop();
        }
      };
      this.forEachUpdateFunction(y12, this.radioContent, a13, undefined, true, false);
      if (!z12) {
        ForEach.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    ForEach.pop();
    List.pop();
    Column.pop();
    Scroll.pop();
  }
  initialRender() {
    {
      this.observeComponentCreation((m12, n12) => {
        ViewStackProcessor.StartGetAccessRecordingFor(m12);
        if (n12) {
          let o12 = new CustomDialogComponent(this, {
            controller: this.controller,
            primaryTitle: this.title,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentPadding
          }, undefined, m12, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 332 });
          ViewPU.create(o12);
          let p12 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.title,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              contentAreaPadding: this.contentPadding
            };
          };
          o12.paramsGenerator_ = p12;
        }
        else {
          this.updateStateVarsOfChildByElmtId(m12, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
  }
  aboutToAppear() {
    this.initContentPadding();
    this.initButtons();
  }
  initContentPadding() {
    this.contentPadding = {
      left: { id: -1, type: 10002, params: ['sys.float.padding_level0'], bundleName: '', moduleName: '' },
      right: { id: -1, type: 10002, params: ['sys.float.padding_level0'], bundleName: '', moduleName: '' }
    };
    if (!this.title && !this.confirm) {
      this.contentPadding = {
        top: { id: -1, type: 10002, params: ['sys.float.padding_level12'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level12'], bundleName: '', moduleName: '' }
      };
      return;
    }
    if (!this.title) {
      this.contentPadding = {
        top: { id: -1, type: 10002, params: ['sys.float.padding_level12'], bundleName: '', moduleName: '' }
      };
    }
    else if (!this.confirm) {
      this.contentPadding = {
        bottom: { id: -1, type: 10002, params: ['sys.float.padding_level12'], bundleName: '', moduleName: '' }
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
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.title = '';
    this.content = '';
    this.checkTips = '';
    this.__isChecked = new ObservedPropertySimplePU(!1, this, 'isChecked');
    this.primaryButton = { value: '' };
    this.secondaryButton = { value: '' };
    this.__contentScrollHeight = new ObservedPropertySimplePU("0px", this, "contentScrollHeight");
    this.contentScroller = new Scroller();
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.title && (this.title = e.title);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.checkTips && (this.checkTips = e.checkTips);
    void 0 !== e.isChecked && (this.isChecked = e.isChecked);
    void 0 !== e.primaryButton && (this.primaryButton = e.primaryButton);
    void 0 !== e.secondaryButton && (this.secondaryButton = e.secondaryButton);
    void 0 !== e.contentScrollHeight && (this.contentScrollHeight = e.contentScrollHeight);
    void 0 !== e.contentScroller && (this.contentScroller = e.contentScroller);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__isChecked.purgeDependencyOnElmtId(e);
    this.__contentScrollHeight.purgeDependencyOnElmtId(e);
  }

  aboutToBeDeleted() {
    this.__isChecked.aboutToBeDeleted();
    this.__contentScrollHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
  }

  get isChecked() {
    return this.__isChecked.get();
  }

  set isChecked(e) {
    this.__isChecked.set(e);
  }

  get contentScrollHeight() {
    return this.__contentScrollHeight.get();
  }

  set contentScrollHeight(e13) {
    this.__contentScrollHeight.set(e13);
  }

  getContentScrollHeight(z12) {
    let a13 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.ohos_id_text_size_body1'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      },
      fontWeight: FontWeight.Medium
    });
    let b13 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.ohos_id_text_size_body1'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      },
      constraintWidth: z12,
      fontWeight: FontWeight.Medium
    });
    let c13 = Number(a13.height);
    let d13 = Number(b13.height);
    this.contentScrollHeight = Math.min(d13, 10 * c13) + "px";
  }

  initialRender() {
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.backgroundBlurStyle(BlurStyle.Thick);
      Column.borderRadius({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_corner_radius_dialog'],
        bundleName: '',
        moduleName: ''
      });
      Column.margin({
        left: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_start'],
          bundleName: '',
          moduleName: ''
        },
        right: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_end'],
          bundleName: '',
          moduleName: ''
        },
        bottom: {
          id: -1,
          type: 10002,
          params: ['sys.float.ohos_id_dialog_margin_bottom'],
          bundleName: '',
          moduleName: ''
        }
      });
      Column.backgroundColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_dialog_bg'],
        bundleName: '',
        moduleName: ''
      });
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.padding({ left: 24, right: 24, top: 24 });
      Row.constraintSize({ minHeight: 56 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.title);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_dialog_tittle'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.maxLines(CONTENT_MAX_LINES);
      Text.minFontSize(15);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.textAlign(TextAlign.Start);
      Text.width('100%');
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.content ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
          Row.width('100%');
          Row.constraintSize({ minHeight: 36 });
          o || Row.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));

        this.observeComponentCreation((p12, q12) => {
          ViewStackProcessor.StartGetAccessRecordingFor(p12);
          Scroll.create(this.contentScroller);
          Scroll.height(this.contentScrollHeight);
          ViewStackProcessor.StopGetAccessRecording();
        });

        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          let x12, y12;
          Text.create(this.content);
          Text.focusable(true);
          Text.defaultFocus(!(((x12 = this.primaryButton) === null || x12 === void 0 ? void 0 : x12.value) || ((y12 = this.secondaryButton) === null || y12 === void 0 ? void 0 : y12.value)));
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body1'],
            bundleName: '',
            moduleName: ''
          });
          Text.fontWeight(FontWeight.Medium);
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            bundleName: '',
            moduleName: ''
          });
          Text.minFontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body3'],
            bundleName: '',
            moduleName: ''
          });
          Text.onKeyEvent((o12) => {
            if (o12) {
              resolveKeyEvent(o12, this.contentScroller);
            }
          });
          Text.onSizeChange((m12, n12) => {
            this.getContentScrollHeight(Number(n12.width));
          });
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Text.pop();
        Scroll.pop();
        Row.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.height(CHECKBOX_CONTAINER_HEIGHT);
      Row.width('100%');
      Row.padding({ left: 24, right: 24, top: 8, bottom: 8 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((e => {
        this.isChecked = e;
      }));
      Checkbox.margin({ left: 0, right: 8 });
      o || Checkbox.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Checkbox.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.checkTips);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_body2'],
        bundleName: '',
        moduleName: ''
      });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({
        id: -1,
        type: 10001,
        params: ['sys.color.ohos_id_color_text_primary'],
        bundleName: '',
        moduleName: ''
      });
      Text.maxLines(CONTENT_MAX_LINES);
      Text.layoutWeight(1);
      Text.focusable(false);
      Text.onClick((() => {
        this.isChecked = !this.isChecked;
      }));
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.width('100%');
      Row.padding({ left: 16, right: 16, top: 16, bottom: 16 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.primaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.primaryButton.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.defaultFocus(true);
          Button.backgroundColor(this.primaryButton.background ? this.primaryButton.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.primaryButton.fontColor ? this.primaryButton.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.primaryButton.action && this.primaryButton.action();
            this.controller.close();
          }));
          o || Button.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Button.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.secondaryButton.value && this.primaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Column.create();
          Column.width(DIVIDER_CONTAINER_WIDTH);
          Column.alignItems(HorizontalAlign.Center);
          o || Column.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          If.create();
          this.secondaryButton.background ? If.branchId(1) : this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Divider.create();
              Divider.width(DIVIDER_WIDTH);
              Divider.height(DIVIDER_HEIGHT);
              Divider.color({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_list_separator'],
                bundleName: '',
                moduleName: ''
              });
              Divider.vertical(!0);
              o || Divider.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
          }));
          o || If.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        If.pop();
        Column.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      If.create();
      this.secondaryButton.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.secondaryButton.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.defaultFocus(true);
          Button.layoutWeight(1);
          Button.backgroundColor(this.secondaryButton.background ? this.secondaryButton.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.secondaryButton.fontColor ? this.secondaryButton.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.secondaryButton.action && this.secondaryButton.action();
            this.controller.close();
          }));
          o || Button.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Button.pop();
      })) : If.branchId(1);
      o || If.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    If.pop();
    Row.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}

export class AlertDialog extends ViewPU {
  constructor(n9, o9, p9, q9 = -1, r9 = undefined, s9) {
    super(n9, p9, q9, s9);
    if (typeof r9 === 'function') {
      this.paramsGenerator_ = r9;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.content = '';
    this.primaryButton = null;
    this.secondaryButton = null;
    this.buttons = undefined;
    this.__textAlign = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlign');
    this.__contentScrollHeight = new ObservedPropertySimplePU("0px", this, "contentScrollHeight");
    this.contentScroller = new Scroller();
    this.setInitiallyProvidedValue(o9);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(m9) {
    if (m9.controller !== undefined) {
      this.controller = m9.controller;
    }
    if (m9.primaryTitle !== undefined) {
      this.primaryTitle = m9.primaryTitle;
    }
    if (m9.secondaryTitle !== undefined) {
      this.secondaryTitle = m9.secondaryTitle;
    }
    if (m9.content !== undefined) {
      this.content = m9.content;
    }
    if (m9.primaryButton !== undefined) {
      this.primaryButton = m9.primaryButton;
    }
    if (m9.secondaryButton !== undefined) {
      this.secondaryButton = m9.secondaryButton;
    }
    if (m9.buttons !== undefined) {
      this.buttons = m9.buttons;
    }
    if (m9.textAlign !== undefined) {
      this.textAlign = m9.textAlign;
    }
    if (m9.contentScrollHeight !== undefined) {
      this.contentScrollHeight = m9.contentScrollHeight;
    }
    if (m9.contentScroller !== undefined) {
      this.contentScroller = m9.contentScroller;
    }
  }
  updateStateVars(l9) {
  }

  purgeVariableDependenciesOnElmtId(k9) {
    this.__textAlign.purgeDependencyOnElmtId(k9);
    this.__textAlign.purgeDependencyOnElmtId(k9);
    this.__contentScrollHeight.purgeDependencyOnElmtId(k9);
  }
  aboutToBeDeleted() {
    this.__textAlign.aboutToBeDeleted();
    this.__contentScrollHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(j9) {
    this.controller = j9;
  }
  get textAlign() {
    return this.__textAlign.get();
  }
  set textAlign(i9) {
    this.__textAlign.set(i9);
  }

  get contentScrollHeight() {
    return this.__contentScrollHeight.get();
  }

  set contentScrollHeight(g9) {
    this.__contentScrollHeight.set(g9);
  }
  initialRender() {
    {
      this.observeComponentCreation2((c9, d9) => {
        if (d9) {
          let e9 = new CustomDialogComponent(this, {
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            controller: this.controller,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
          }, undefined, c9, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 57 });
          ViewPU.create(e9);
          let f9 = () => {
            return {
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              controller: this.controller,
              contentBuilder: () => {
                this.AlertDialogContentBuilder();
              },
              buttons: this.buttons
            };
          };
          e9.paramsGenerator_ = f9;
        }
        else {
          this.updateStateVarsOfChildByElmtId(c9, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
  }
  AlertDialogContentBuilder(o8 = null) {
    this.observeComponentCreation2((z8, a9) => {
      Column.create();
      Column.margin({ right: `${this.getMargin()}vp`, });
    }, Column);

    this.observeComponentCreation2((h8, i8) => {
      Scroll.create(this.contentScroller);
      Scroll.height(this.contentScrollHeight);
      Scroll.width('100%');
    }, Scroll);
    this.observeComponentCreation2((s8, t8) => {
      Text.create(this.content);
      Text.focusable(true);
      Text.defaultFocus(!(this.primaryButton || this.secondaryButton));
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level8'], bundleName: '', moduleName: '' }, });
      Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
      Text.textAlign(this.textAlign);

      Text.onSizeChange((f8, g8) => {
        this.getContentScrollHeight(Number(g8.width));
        this.getTextAlign(Number(g8.width));
      });
      Text.onKeyEvent((s8) => {
        if (s8) {
          resolveKeyEvent(s8, this.contentScroller);
        }
      });
    }, Text);
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  aboutToAppear() {
    this.initButtons();
  }

  getContentScrollHeight(f8) {
    let g8 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.Body_L'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      },
      fontWeight: FontWeight.Medium
    });
    let h8 = measure.measureTextSize({
      textContent: this.content,
      fontSize: {
        "id": -1,
        "type": 10002,
        params: ['sys.float.Body_L'],
        "bundleName": "__harDefaultBundleName__",
        "moduleName": "__harDefaultModuleName__"
      },
      constraintWidth: f8,
      fontWeight: FontWeight.Medium
    });
    let i8 = Number(g8.height);
    let j8 = Number(h8.height);
    this.contentScrollHeight = Math.min(j8, 10 * i8) + "px";
  }
  getTextAlign(l8) {
    let m8 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
      constraintWidth: l8,
    });
    let n8 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
    });
    if (this.getTextHeight(m8) <= this.getTextHeight(n8)) {
      this.textAlign = TextAlign.Center;
    }
  }
  getTextHeight(k8) {
    if (k8 && k8.height !== null && k8.height !== undefined) {
      return Number(k8.height);
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
  rerender() {
    this.updateDirtyElements();
  }
}

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
export class CustomContentDialog extends ViewPU {
  constructor(e8, f8, g8, h8 = -1, i8 = undefined, j8) {
    super(e8, g8, h8, j8);
    if (typeof i8 === 'function') {
      this.paramsGenerator_ = i8;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.contentAreaPadding = undefined;
    this.buttons = undefined;
    this.setInitiallyProvidedValue(f8);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(d8) {
    if (d8.controller !== undefined) {
      this.controller = d8.controller;
    }
    if (d8.primaryTitle !== undefined) {
      this.primaryTitle = d8.primaryTitle;
    }
    if (d8.secondaryTitle !== undefined) {
      this.secondaryTitle = d8.secondaryTitle;
    }
    if (d8.contentBuilder !== undefined) {
      this.contentBuilder = d8.contentBuilder;
    }
    if (d8.contentAreaPadding !== undefined) {
      this.contentAreaPadding = d8.contentAreaPadding;
    }
    if (d8.buttons !== undefined) {
      this.buttons = d8.buttons;
    }
  }
  updateStateVars(c8) {
  }
  purgeVariableDependenciesOnElmtId(b8) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(a8) {
    this.controller = a8;
  }
  initialRender() {
    {
      this.observeComponentCreation2((u7, v7) => {
        if (v7) {
          let w7 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            contentAreaPadding: this.contentAreaPadding,
            buttons: this.buttons,
          }, undefined, u7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 143 });
          ViewPU.create(w7);
          let x7 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              contentAreaPadding: this.contentAreaPadding,
              buttons: this.buttons
            };
          };
          w7.paramsGenerator_ = x7;
        }
        else {
          this.updateStateVarsOfChildByElmtId(u7, {});
        }
      }, { name: 'CustomDialogContentComponent' });
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class CustomDialogContentComponent extends ViewPU {
  constructor(n7, o7, p7, q7 = -1, r7 = undefined, s7) {
    super(n7, p7, q7, s7);
    if (typeof r7 === 'function') {
      this.paramsGenerator_ = r7;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = this.defaultContentBuilder;
    this.buttons = undefined;
    this.contentAreaPadding = undefined;
    this.titleHeight = 0;
    this.__contentMaxHeight = new ObservedPropertySimplePU('', this, 'contentMaxHeight');
    this.setInitiallyProvidedValue(o7);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(m7) {
    if (m7.controller !== undefined) {
      this.controller = m7.controller;
    }
    if (m7.primaryTitle !== undefined) {
      this.primaryTitle = m7.primaryTitle;
    }
    if (m7.secondaryTitle !== undefined) {
      this.secondaryTitle = m7.secondaryTitle;
    }
    if (m7.contentBuilder !== undefined) {
      this.contentBuilder = m7.contentBuilder;
    }
    if (m7.buttons !== undefined) {
      this.buttons = m7.buttons;
    }
    if (m7.contentAreaPadding !== undefined) {
      this.contentAreaPadding = m7.contentAreaPadding;
    }
    if (m7.titleHeight !== undefined) {
      this.titleHeight = m7.titleHeight;
    }
    if (m7.contentMaxHeight !== undefined) {
      this.contentMaxHeight = m7.contentMaxHeight;
    }
  }
  updateStateVars(l7) {
  }
  purgeVariableDependenciesOnElmtId(k7) {
    this.__contentMaxHeight.purgeDependencyOnElmtId(k7);
  }
  aboutToBeDeleted() {
    this.__contentMaxHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  defaultContentBuilder(j7 = null) {
  }
  get contentMaxHeight() {
    return this.__contentMaxHeight.get();
  }
  set contentMaxHeight(i7) {
    this.__contentMaxHeight.set(i7);
  }
  initialRender() {
    this.observeComponentCreation2((g7, h7) => {
      Column.create();
      Column.width('100%');
    }, Column);
    this.buildTitles.bind(this)();
    this.observeComponentCreation2((e7, f7) => {
      Column.create();
      Column.padding(this.getContentPadding());
      Column.constraintSize({ maxHeight: this.contentMaxHeight, });
    }, Column);
    this.contentBuilder.bind(this)();
    Column.pop();
    this.buildButtons.bind(this)();
    Column.pop();
  }
  buildTitles(y5 = null) {
    this.observeComponentCreation2((x6, y6) => {
      Column.create();
      Column.constraintSize({
        minHeight: this.getTitleAreaMinHeight(),
      });
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
      Column.onAreaChange((a7, b7) => {
        this.titleHeight = Number(b7.height);
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
      });
    }, Column);
    this.observeComponentCreation2((v6, w6) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((t6, u6) => {
      Text.create(this.primaryTitle);
      Text.fontWeight(FontWeight.Bold);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.textAlign(this.getTitleTextAlign());
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Title_S'], bundleName: '', moduleName: '' });
      Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    this.observeComponentCreation2((j6, k6) => {
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((r6, s6) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((p6, q6) => {
            Divider.create();
            Divider.margin({ id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' });
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
    this.observeComponentCreation2((h6, i6) => {
      Row.create();
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((f6, g6) => {
      Text.create(this.secondaryTitle);
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
      Text.textAlign(this.getTitleTextAlign());
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
      Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_S'], bundleName: '', moduleName: '' });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.width('100%');
    }, Text);
    Text.pop();
    Row.pop();
    Column.pop();
  }
  buildButtons(u5 = null) {
    this.observeComponentCreation2((w5, x5) => {
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
    }, Column);
    this.buildHorizontalAlignButtons.bind(this)();
    this.buildVerticalAlignButtons.bind(this)();
    Column.pop();
  }
  buildSingleButton(z4, a5 = null) {
    this.observeComponentCreation2((c5, d5) => {
      If.create();
      if (this.isNewPropertiesHighPriority(z4)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((s5, t5) => {
            Button.createWithLabel(z4.value);
            __Button__setButtonProperties(z4, this.controller);
            Button.role(z4.role ?? ButtonRole.NORMAL);
          }, Button);
          Button.pop();
        });
      }
      else if (z4.background !== undefined && z4.fontColor !== undefined) {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation2((o5, p5) => {
            Button.createWithLabel(z4.value);
            __Button__setButtonProperties(z4, this.controller);
            Button.backgroundColor(z4.background);
            Button.fontColor(z4.fontColor);
          }, Button);
          Button.pop();
        });
      }
      else if (z4.background !== undefined) {
        this.ifElseBranchUpdateFunction(2, () => {
          this.observeComponentCreation2((k5, l5) => {
            Button.createWithLabel(z4.value);
            __Button__setButtonProperties(z4, this.controller);
            Button.backgroundColor(z4.background);
          }, Button);
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(3, () => {
          this.observeComponentCreation2((g5, h5) => {
            Button.createWithLabel(z4.value);
            __Button__setButtonProperties(z4, this.controller);
            Button.fontColor(z4.fontColor);
          }, Button);
          Button.pop();
        });
      }
    }, If);
    If.pop();
  }
  buildHorizontalAlignButtons(i4 = null) {
    this.observeComponentCreation2((k4, l4) => {
      If.create();
      if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((x4, y4) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(this.buttons[0]);
          this.observeComponentCreation2((q4, r4) => {
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((v4, w4) => {
                  Divider.create();
                  Divider.width({ id: -1, type: 10002, params: ['sys.float.alert_divider_width'], bundleName: '', moduleName: '' });
                  Divider.height({ id: -1, type: 10002, params: ['sys.float.alert_divider_height'], bundleName: '', moduleName: '' });
                  Divider.color({ id: -1, type: 10001, params: ['sys.color.alert_divider_color'], bundleName: '', moduleName: '' });
                  Divider.vertical(true);
                  Divider.margin({
                    left: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                    right: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
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
  buildVerticalAlignButtons(p3 = null) {
    this.observeComponentCreation2((r3, s3) => {
      If.create();
      if (this.buttons && this.isVerticalAlignButton()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((g4, h4) => {
            Column.create();
          }, Column);
          this.observeComponentCreation2((x3, y3) => {
            ForEach.create();
            const z3 = (d4, e4) => {
              const f4 = d4;
              this.buildButtonWithDivider.bind(this)(e4);
            };
            this.forEachUpdateFunction(x3, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), z3, (c4) => c4.value.toString(), true, false);
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
  buildButtonWithDivider(x2, y2 = null) {
    this.observeComponentCreation2((a3, b3) => {
      If.create();
      if (this.buttons && this.buttons[x2]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((n3, o3) => {
            Row.create();
          }, Row);
          this.buildSingleButton.bind(this)(this.buttons[x2]);
          Row.pop();
          this.observeComponentCreation2((g3, h3) => {
            If.create();
            if (x2 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((l3, m3) => {
                  Row.create();
                  Row.height({ id: -1, type: 10002, params: ['sys.float.alert_button_vertical_space'], bundleName: '', moduleName: '' });
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
  }
  getButtonsHeight() {
    if (!this.buttons || this.buttons.length === 0) {
      return 0;
    }
    let w2 = getNumberByResource('alert_button_top_padding');
    if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
      w2 += BUTTON_DEFAULT_HEIGHT +
      getNumberByResource('alert_button_bottom_padding_horizontal');
    }
    else {
      w2 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
        (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
      getNumberByResource('alert_button_bottom_padding_vertical');
    }
    return w2;
  }
  getContentPadding() {
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }
    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: 0,
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
    else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
    else if (this.buttons && this.buttons.length > 0) {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: 0,
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
    else {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_content_default_padding'], bundleName: '', moduleName: '' },
      };
    }
  }
  getTitleAreaMinHeight() {
    if (this.secondaryTitle) {
      return { id: -1, type: 10002, params: ['sys.float.alert_title_secondary_height'], bundleName: '', moduleName: '' };
    }
    else if (this.primaryTitle) {
      return { id: -1, type: 10002, params: ['sys.float.alert_title_primary_height'], bundleName: '', moduleName: '' };
    }
    else {
      return 0;
    }
  }
  getTitleAreaPadding() {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_top'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_right'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_left'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_bottom'], bundleName: '', moduleName: '' },
      };
    }
    return {
      top: 0,
      right: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_right'], bundleName: '', moduleName: '' },
      left: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_left'], bundleName: '', moduleName: '' },
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
        top: { id: -1, type: 10002, params: ['sys.float.alert_button_top_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_right_padding_vertical'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_left_padding_vertical'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_button_bottom_padding_vertical'], bundleName: '', moduleName: '' },
      };
    }
    return {
      top: { id: -1, type: 10002, params: ['sys.float.alert_button_top_padding'], bundleName: '', moduleName: '' },
      right: { id: -1, type: 10002, params: ['sys.float.alert_right_padding_horizontal'], bundleName: '', moduleName: '' },
      left: { id: -1, type: 10002, params: ['sys.float.alert_left_padding_horizontal'], bundleName: '', moduleName: '' },
      bottom: { id: -1, type: 10002, params: ['sys.float.alert_button_bottom_padding_horizontal'], bundleName: '', moduleName: '' },
    };
  }
  isNewPropertiesHighPriority(v2) {
    if (v2.role === ButtonRole.ERROR) {
      return true;
    }
    if (v2.buttonStyle !== undefined &&
      v2.buttonStyle !== getNumberByResource('alert_button_style')) {
      return true;
    }
    if (v2.background === undefined && v2.fontColor === undefined) {
      return true;
    }
    return false;
  }
  getTitleTextAlign() {
    let u2 = getEnumNumberByResource('alert_title_alignment');
    if (u2 === TextAlign.Start) {
      return TextAlign.Start;
    }
    else if (u2 === TextAlign.Center) {
      return TextAlign.Center;
    }
    else if (u2 === TextAlign.End) {
      return TextAlign.End;
    }
    else if (u2 === TextAlign.JUSTIFY) {
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
  constructor(o2, p2, q2, r2 = -1, s2 = undefined, t2) {
    super(o2, q2, r2, t2);
    if (typeof s2 === 'function') {
      this.paramsGenerator_ = s2;
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
    this.setInitiallyProvidedValue(p2);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n2) {
    if (n2.controller !== undefined) {
      this.controller = n2.controller;
    }
    if (n2.primaryTitle !== undefined) {
      this.primaryTitle = n2.primaryTitle;
    }
    if (n2.secondaryTitle !== undefined) {
      this.secondaryTitle = n2.secondaryTitle;
    }
    if (n2.contentBuilder !== undefined) {
      this.contentBuilder = n2.contentBuilder;
    }
    if (n2.buttons !== undefined) {
      this.buttons = n2.buttons;
    }
    if (n2.contentAreaPadding !== undefined) {
      this.contentAreaPadding = n2.contentAreaPadding;
    }
    if (n2.screenWidth !== undefined) {
      this.screenWidth = n2.screenWidth;
    }
    if (n2.columnModifier !== undefined) {
      this.columnModifier = n2.columnModifier;
    }
    if (n2.isFirstInit !== undefined) {
      this.isFirstInit = n2.isFirstInit;
    }
  }
  updateStateVars(m2) {
  }
  purgeVariableDependenciesOnElmtId(l2) {
    this.__columnModifier.purgeDependencyOnElmtId(l2);
  }
  aboutToBeDeleted() {
    this.__columnModifier.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get columnModifier() {
    return this.__columnModifier.get();
  }
  set columnModifier(k2) {
    this.__columnModifier.set(k2);
  }
  initialRender() {
    this.observeComponentCreation2((f2, g2) => {
      Column.create();
      Column.onAreaChange((i2, j2) => {
        if (!this.isFirstInit) {
          return;
        }
        if (this.screenWidth > getNumberByResource('alert_container_max_width')) {
          this.columnModifier.customStyle = j2.width > getNumberByResource('alert_container_max_width');
        }
        else {
          this.columnModifier.customStyle = j2.width >= this.screenWidth;
        }
        this.isFirstInit = false;
      });
    }, Column);
    this.observeComponentCreation2((d2, e2) => {
      Column.create();
      Column.attributeModifier.bind(this)(ObservedObject.GetRawObject(this.columnModifier));
    }, Column);
    {
      this.observeComponentCreation2((x1, y1) => {
        if (y1) {
          let z1 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentAreaPadding,
          }, undefined, x1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 519 });
          ViewPU.create(z1);
          let a2 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons,
              contentAreaPadding: this.contentAreaPadding
            };
          };
          z1.paramsGenerator_ = a2;
        }
        else {
          this.updateStateVarsOfChildByElmtId(x1, {});
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
    catch (t1) {
      hilog.error(0x3900, 'Ace', `CustomDialogComponent getDefaultDisplaySync error: ${JSON.stringify(t1)}`);
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
  applyNormalAttribute(s1) {
    if (!this.customStyle) {
      return;
    }
    s1.backgroundBlurStyle(BlurStyle.Thick);
    s1.borderRadius({ id: -1, type: 10002, params: ['sys.float.ohos_id_corner_radius_dialog'], bundleName: '', moduleName: '' });
    s1.margin({
      left: { id: -1, type: 10002, params: ['sys.float.ohos_id_dialog_margin_start'], bundleName: '', moduleName: '' },
      right: { id: -1, type: 10002, params: ['sys.float.ohos_id_dialog_margin_end'], bundleName: '', moduleName: '' },
      bottom: { id: -1, type: 10002, params: ['sys.float.ohos_id_dialog_margin_bottom'], bundleName: '', moduleName: '' },
    });
    s1.backgroundColor({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_dialog_bg'], bundleName: '', moduleName: '' });
  }
}
function __Button__setButtonProperties(p1, q1) {
  Button.onClick(() => {
    if (p1.action) {
      p1.action();
    }
    q1?.close();
  });
  Button.buttonStyle(p1.buttonStyle ?? getNumberByResource('alert_button_style'));
  Button.defaultFocus(true);
  Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}
function getNumberByResource(l1) {
  try {
    return resourceManager.getSystemResourceManager().getNumberByName(l1);
  }
  catch (m1) {
    let n1 = m1.code;
    let o1 = m1.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${n1}, message: ${o1}`);
    return 0;
  }
}
function getEnumNumberByResource(h1) {
  try {
    return getContext().resourceManager.getNumberByName(h1);
  }
  catch (i1) {
    let j1 = i1.code;
    let k1 = i1.message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${j1}, message: ${k1}`);
    return -1;
  }
}
function resolveKeyEvent(h1, i1) {
  if (h1.type == IGNORE_KEY_EVENT_TYPE) {
    return;
  }
  if (h1.keyCode == KEYCODE_UP) {
    i1.scrollPage({ next: false });
    h1.stopPropagation();
  }
  else if (h1.keyCode == KEYCODE_DOWN) {
    if (i1.isAtEnd()) {
      return;
    }
    else {
      i1.scrollPage({ next: true });
      h1.stopPropagation();
    }
  }
}
export class LoadingDialog extends ViewPU {
  constructor(b1, c1, d1, e1 = -1, f1 = undefined, g1) {
    super(b1, d1, e1, g1);
    if (typeof f1 === 'function') {
      this.paramsGenerator_ = f1;
    }
    this.controller = undefined;
    this.content = '';
    this.setInitiallyProvidedValue(c1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(a1) {
    if (a1.controller !== undefined) {
      this.controller = a1.controller;
    }
    if (a1.content !== undefined) {
      this.content = a1.content;
    }
  }
  updateStateVars(z) {
  }
  purgeVariableDependenciesOnElmtId(y) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(x) {
    this.controller = x;
  }
  initialRender() {
    this.observeComponentCreation((v, w) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v);
      Column.create();
      if (!w) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    {
      this.observeComponentCreation((p, q) => {
        ViewStackProcessor.StartGetAccessRecordingFor(p);
        if (q) {
          let r = new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.contentBuilder();
            },
          }, undefined, p, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 758 });
          ViewPU.create(r);
          let s = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.contentBuilder();
              }
            };
          };
          r.paramsGenerator_ = s;
        }
        else {
          this.updateStateVarsOfChildByElmtId(p, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    Column.pop();
  }
  contentBuilder(a = null) {
    this.observeComponentCreation((l, m) => {
      ViewStackProcessor.StartGetAccessRecordingFor(l);
      Column.create();
      if (!m) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j, k) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j);
      Row.create();
      Row.constraintSize({ minHeight: LOADING_MIN_HEIGHT });
      if (!k) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((h, i) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h);
      Text.create(this.content);
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT);
      Text.maxLines(LOADING_MAX_LINES);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.focusable(true);
      Text.defaultFocus(true);
      if (!i) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    this.observeComponentCreation((f, g) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f);
      LoadingProgress.create();
      LoadingProgress.color({ id: -1, type: 10001, params: ['sys.color.icon_secondary'], bundleName: '', moduleName: '' });
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ left: LOADING_TEXT_MARGIN_LEFT });
      if (!g) {
        LoadingProgress.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Row.pop();
    Column.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog };
