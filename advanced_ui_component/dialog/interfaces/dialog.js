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

export class TipsDialog extends ViewPU {
  constructor(o12, p12, q12, r12 = -1, s12 = undefined, t12) {
    super(o12, q12, r12, t12);
    if (typeof s12 === 'function') {
      this.paramsGenerator_ = s12;
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
    this.checkBoxHeight = CHECKBOX_CONTAINER_HEIGHT;
    this.buttonHeight = 0;
    this.setInitiallyProvidedValue(p12);
  }
  setInitiallyProvidedValue(n12) {
    if (n12.controller !== undefined) {
      this.controller = n12.controller;
    }
    if (n12.imageRes !== undefined) {
      this.imageRes = n12.imageRes;
    }
    if (n12.imageSize !== undefined) {
      this.imageSize = n12.imageSize;
    }
    if (n12.title !== undefined) {
      this.title = n12.title;
    }
    if (n12.content !== undefined) {
      this.content = n12.content;
    }
    if (n12.checkAction !== undefined) {
      this.checkAction = n12.checkAction;
    }
    if (n12.checkTips !== undefined) {
      this.checkTips = n12.checkTips;
    }
    if (n12.isChecked !== undefined) {
      this.isChecked = n12.isChecked;
    }
    if (n12.primaryButton !== undefined) {
      this.primaryButton = n12.primaryButton;
    }
    if (n12.secondaryButton !== undefined) {
      this.secondaryButton = n12.secondaryButton;
    }
    if (n12.buttons !== undefined) {
      this.buttons = n12.buttons;
    }
    if (n12.imageSizeHeight !== undefined) {
      this.imageSizeHeight = n12.imageSizeHeight;
    }
    if (n12.textAlignment !== undefined) {
      this.textAlignment = n12.textAlignment;
    }
    if (n12.marginOffset !== undefined) {
      this.marginOffset = n12.marginOffset;
    }
    if (n12.checkBoxHeight !== undefined) {
      this.checkBoxHeight = n12.checkBoxHeight;
    }
    if (n12.buttonHeight !== undefined) {
      this.buttonHeight = n12.buttonHeight;
    }
  }
  updateStateVars(m12) {
  }
  purgeVariableDependenciesOnElmtId(l12) {
    this.__imageSize.purgeDependencyOnElmtId(l12);
    this.__isChecked.purgeDependencyOnElmtId(l12);
    this.__imageSizeHeight.purgeDependencyOnElmtId(l12);
    this.__textAlignment.purgeDependencyOnElmtId(l12);
  }
  aboutToBeDeleted() {
    this.__imageSize.aboutToBeDeleted();
    this.__isChecked.aboutToBeDeleted();
    this.__imageSizeHeight.aboutToBeDeleted();
    this.__textAlignment.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(k12) {
    this.controller = k12;
  }
  get imageSize() {
    return this.__imageSize.get();
  }
  set imageSize(j12) {
    this.__imageSize.set(j12);
  }
  get isChecked() {
    return this.__isChecked.get();
  }
  set isChecked(i12) {
    this.__isChecked.set(i12);
  }
  get imageSizeHeight() {
    return this.__imageSizeHeight.get();
  }
  set imageSizeHeight(h12) {
    this.__imageSizeHeight.set(h12);
  }
  get textAlignment() {
    return this.__textAlignment.get();
  }
  set textAlignment(g12) {
    this.__textAlignment.set(g12);
  }
  initialRender() {
    {
      this.observeComponentCreation2((c12, d12) => {
        if (d12) {
          let e12 = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons
            };
          };
          ViewPU.create(new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
          }, undefined, c12, e12, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 65 }));
        }
        else {
          this.updateStateVarsOfChildByElmtId(c12, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
  }
  contentBuilder(k11 = null) {
    this.observeComponentCreation2((z11, a12) => {
      Column.create();
    }, Column);
    this.imagePart.bind(this)();
    this.observeComponentCreation2((s11, t11) => {
      If.create();
      if (this.title != null || this.content != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((x11, y11) => {
            Column.create();
            Column.padding({ top: { id: -1, type: 10002, params: ['sys.float.padding_level8'], bundleName: '', moduleName: '' } });
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
    this.observeComponentCreation2((o11, p11) => {
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
  checkBoxPart(w10, x10 = null) {
    this.observeComponentCreation2((i11, j11) => {
      Row.create();
      Row.padding({ top: { id: -1, type: 10002, params: ['sys.float.padding_level8'], 
      bundleName: '', moduleName: '' } });
      Row.height(CHECKBOX_CONTAINER_HEIGHT);
      Row.width('100%');
    }, Row);
    this.observeComponentCreation2((e11, f11) => {
      Checkbox.create({ name: 'checkbox', group: 'checkboxGroup' });
      Checkbox.select(this.isChecked);
      Checkbox.onChange((h11) => {
        this.isChecked = h11;
        if (this.checkAction) {
          this.checkAction(h11);
        }
      });
      Checkbox.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level4'], 
      bundleName: '', moduleName: '' } });
    }, Checkbox);
    Checkbox.pop();
    this.observeComponentCreation2((b11, c11) => {
      Text.create(w10);
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_M'], bundleName: '', moduleName: '' });
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.maxLines(CONTENT_MAX_LINES);
      Text.layoutWeight(1);
      Text.focusOnTouch(true);
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
  imagePart(m10 = null) {
    this.observeComponentCreation2((r10, s10) => {
      Column.create();
      Column.width('100%');
      Column.constraintSize({
        maxHeight: 
        `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
      });
      Column.onAreaChange((u10, v10) => {
        this.imageSizeHeight = Number(v10.height);
      });
    }, Column);
    this.observeComponentCreation2((p10, q10) => {
      Image.create(this.imageRes);
      Image.size(ObservedObject.GetRawObject(this.imageSize));
      Image.objectFit(ImageFit.Contain);
      Image.constraintSize({
        maxWidth: '100%',
        maxHeight: 
        `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
      });
    }, Image);
    Column.pop();
  }
  textPart(g9 = null) {
    this.observeComponentCreation2((k10, l10) => {
      Scroll.create();
      Scroll.margin({ right: `${this.marginOffset}vp` });
    }, Scroll);
    this.observeComponentCreation2((i10, j10) => {
      Column.create();
      Column.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level8'], 
      bundleName: '', moduleName: '' } });
    }, Column);
    this.observeComponentCreation2((y9, z9) => {
      If.create();
      if (this.title != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((g10, h10) => {
            Row.create();
            Row.padding({ bottom: { id: -1, type: 10002, params: ['sys.float.padding_level8'], 
            bundleName: '', moduleName: '' } });
          }, Row);
          this.observeComponentCreation2((e10, f10) => {
            Text.create(this.title);
            Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Title_S'], bundleName: '', moduleName: '' });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
            Text.textAlign(TextAlign.Center);
            Text.maxLines(CONTENT_MAX_LINES);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
            Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Title_S'], bundleName: '', moduleName: '' });
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
    this.observeComponentCreation2((l9, m9) => {
      If.create();
      if (this.content != null) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((w9, x9) => {
            Row.create();
          }, Row);
          this.observeComponentCreation2((r9, s9) => {
            Text.create(this.content);
            Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
            Text.fontWeight(FontWeight.Medium);
            Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
            Text.textAlign(this.textAlignment);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width('100%');
            Text.onAreaChange((u9, v9) => {
              this.getTextAlign(Number(v9.width));
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
    this.initButtons();
    this.initMarginAndCheckHeight();
  }
  getTextAlign(d9) {
    let e9 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
      constraintWidth: d9,
    });
    let f9 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
    });
    if (this.getTextHeight(e9) <= this.getTextHeight(f9)) {
      this.textAlignment = TextAlign.Center;
    }
  }
  getTextHeight(c9) {
    if (c9 && c9.height !== null && c9.height !== undefined) {
      return Number(c9.height);
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
    let b9 = getNumberByResource('alert_button_top_padding');
    b9 += BUTTON_DEFAULT_HEIGHT + getNumberByResource('alert_button_bottom_padding_horizontal');
    return b9;
  }
  initMarginAndCheckHeight() {
    if (this.checkTips == null) {
      this.checkBoxHeight = 0;
    }
    this.marginOffset = 0 - getNumberByResource('padding_level8');
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export class SelectDialog extends ViewPU {
  constructor(j15, k15, l15, m15 = -1, n15 = undefined, o15) {
    super(j15, l15, m15, o15);
    if (typeof n15 === "function") {
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
        }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 254 });
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
  }
  updateStateVars(h15) {
  }
  purgeVariableDependenciesOnElmtId(g15) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(f15) {
    this.controller = f15;
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
              left: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              right: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
              bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
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
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Body_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
      List.create({ space: 1 });
      List.width('100%');
      List.clip(false);
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
          };
          const h13 = (l13, m13) => {
            f13(l13, m13);
            this.updateFuncByElmtId.set(l13, f13);
            this.observeComponentCreation((j14, k14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(j14);
              Column.create();
              Column.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
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
              Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
              Button.buttonStyle(ButtonStyleMode.TEXTUAL);
              Button.padding({
                left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
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
                top: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
              });
              if (!f14) {
                Row.pop();
              }
              ViewStackProcessor.StopGetAccessRecording();
            });
            this.observeComponentCreation((c14, d14) => {
              ViewStackProcessor.StartGetAccessRecordingFor(c14);
              Text.create(e13.title);
              Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Body_L'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
              Text.fontWeight(FontWeight.Medium);
              Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
                    Divider.color({ "id": -1, "type": 10001, params: ['sys.color.comp_divider'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    Divider.padding({
                      left: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                      right: { "id": -1, "type": 10002, params: ['sys.float.padding_level6'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
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
          }, undefined, m12, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 332 });
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
      left: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
      right: { "id": -1, "type": 10002, params: ['sys.float.padding_level0'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
    };
    if (!this.title && !this.confirm) {
      this.contentPadding = {
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
      };
      return;
    }
    if (!this.title) {
      this.contentPadding = {
        top: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
      };
    }
    else if (!this.confirm) {
      this.contentPadding = {
        bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
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
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
    this.__isChecked.purgeDependencyOnElmtId(e);
  }

  aboutToBeDeleted() {
    this.__isChecked.aboutToBeDeleted();
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
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.content);
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
          Text.maxLines(CONTENT_MAX_LINES);
          Text.textOverflow({ overflow: TextOverflow.Ellipsis });
          Text.minFontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body3'],
            bundleName: '',
            moduleName: ''
          });
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        Text.pop();
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
      Text.focusOnTouch(!0);
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
  constructor(v8, w8, x8, y8 = -1, z8 = undefined, a9) {
    super(v8, x8, y8, a9);
    if (typeof z8 === 'function') {
      this.paramsGenerator_ = z8;
    }
    this.controller = undefined;
    this.content = '';
    this.primaryButton = null;
    this.secondaryButton = null;
    this.buttons = undefined;
    this.__textAlign = new ObservedPropertySimplePU(TextAlign.Start, this, 'textAlign');
    this.setInitiallyProvidedValue(w8);
  }
  setInitiallyProvidedValue(u8) {
    if (u8.controller !== undefined) {
      this.controller = u8.controller;
    }
    if (u8.content !== undefined) {
      this.content = u8.content;
    }
    if (u8.primaryButton !== undefined) {
      this.primaryButton = u8.primaryButton;
    }
    if (u8.secondaryButton !== undefined) {
      this.secondaryButton = u8.secondaryButton;
    }
    if (u8.buttons !== undefined) {
      this.buttons = u8.buttons;
    }
    if (u8.textAlign !== undefined) {
      this.textAlign = u8.textAlign;
    }
  }
  updateStateVars(t8) {
  }
  purgeVariableDependenciesOnElmtId(s8) {
    this.__textAlign.purgeDependencyOnElmtId(s8);
  }
  aboutToBeDeleted() {
    this.__textAlign.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(r8) {
    this.controller = r8;
  }
  get textAlign() {
    return this.__textAlign.get();
  }
  set textAlign(q8) {
    this.__textAlign.set(q8);
  }
  initialRender() {
    {
      this.observeComponentCreation2((m8, n8) => {
        if (n8) {
          let o8 = () => {
            return {
              controller: this.controller,
              contentBuilder: () => {
                this.AlertDialogContentBuilder();
              },
              buttons: this.buttons
            };
          };
          ViewPU.create(new CustomDialogComponent(this, {
            controller: this.controller,
            contentBuilder: () => {
              this.AlertDialogContentBuilder();
            },
            buttons: this.buttons,
          }, undefined, m8, o8, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 254 }));
        }
        else {
          this.updateStateVarsOfChildByElmtId(m8, {});
        }
      }, { name: 'CustomDialogComponent' });
    }
  }
  AlertDialogContentBuilder(y7 = null) {
    this.observeComponentCreation2((j8, k8) => {
      Column.create();
      Column.margin({ right: `${this.getMargin()}vp`, });
    }, Column);
    this.observeComponentCreation2((h8, i8) => {
      Scroll.create();
      Scroll.width('100%');
    }, Scroll);
    this.observeComponentCreation2((c8, d8) => {
      Text.create(this.content);
      Text.fontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.fontWeight(FontWeight.Medium);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.margin({ right: { id: -1, type: 10002, params: ['sys.float.padding_level8'], 
      bundleName: '', moduleName: '' }, });
      Text.width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`);
      Text.textAlign(this.textAlign);
      Text.onAreaChange((f8, g8) => {
        this.getTextAlign(Number(g8.width));
      });
    }, Text);
    Text.pop();
    Scroll.pop();
    Column.pop();
  }
  aboutToAppear() {
    this.initButtons();
  }
  getTextAlign(v7) {
    let w7 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
      constraintWidth: v7,
    });
    let x7 = measure.measureTextSize({
      textContent: this.content,
      fontSize: { id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' },
    });
    if (this.getTextHeight(w7) <= this.getTextHeight(x7)) {
      this.textAlign = TextAlign.Center;
    }
  }
  getTextHeight(u7) {
    if (u7 && u7.height !== null && u7.height !== undefined) {
      return Number(u7.height);
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
  constructor(o6, p6, q6, r6 = -1, s6 = undefined, t6) {
    super(o6, q6, r6, t6);
    if (typeof s6 === 'function') {
      this.paramsGenerator_ = s6;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.buttons = undefined;
    this.setInitiallyProvidedValue(p6);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(n6) {
    if (n6.controller !== undefined) {
      this.controller = n6.controller;
    }
    if (n6.primaryTitle !== undefined) {
      this.primaryTitle = n6.primaryTitle;
    }
    if (n6.secondaryTitle !== undefined) {
      this.secondaryTitle = n6.secondaryTitle;
    }
    if (n6.contentBuilder !== undefined) {
      this.contentBuilder = n6.contentBuilder;
    }
    if (n6.buttons !== undefined) {
      this.buttons = n6.buttons;
    }
  }
  updateStateVars(m6) {
  }
  purgeVariableDependenciesOnElmtId(l6) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(k6) {
    this.controller = k6;
  }
  initialRender() {
    {
      this.observeComponentCreation((e6, f6) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e6);
        if (f6) {
          let g6 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
          }, undefined, e6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 22 });
          ViewPU.create(g6);
          let h6 = () => {
            return {
              controller: this.controller,
              primaryTitle: this.primaryTitle,
              secondaryTitle: this.secondaryTitle,
              contentBuilder: () => {
                this.contentBuilder();
              },
              buttons: this.buttons
            };
          };
          g6.paramsGenerator_ = h6;
        }
        else {
          this.updateStateVarsOfChildByElmtId(e6, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}
class CustomDialogContentComponent extends ViewPU {
  constructor(x5, y5, z5, a6 = -1, b6 = undefined, c6) {
    super(x5, z5, a6, c6);
    if (typeof b6 === 'function') {
      this.paramsGenerator_ = b6;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = this.defaultContentBuilder;
    this.buttons = undefined;
    this.contentAreaPadding = undefined;
    this.titleHeight = 0;
    this.__contentMaxHeight = new ObservedPropertySimplePU('', this, 'contentMaxHeight');
    this.setInitiallyProvidedValue(y5);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(w5) {
    if (w5.controller !== undefined) {
      this.controller = w5.controller;
    }
    if (w5.primaryTitle !== undefined) {
      this.primaryTitle = w5.primaryTitle;
    }
    if (w5.secondaryTitle !== undefined) {
      this.secondaryTitle = w5.secondaryTitle;
    }
    if (w5.contentBuilder !== undefined) {
      this.contentBuilder = w5.contentBuilder;
    }
    if (w5.buttons !== undefined) {
      this.buttons = w5.buttons;
    }
    if (w5.contentAreaPadding !== undefined) {
      this.contentAreaPadding = w5.contentAreaPadding;
    }
    if (w5.titleHeight !== undefined) {
      this.titleHeight = w5.titleHeight;
    }
    if (w5.contentMaxHeight !== undefined) {
      this.contentMaxHeight = w5.contentMaxHeight;
    }
  }
  updateStateVars(v5) {
  }
  purgeVariableDependenciesOnElmtId(u5) {
    this.__contentMaxHeight.purgeDependencyOnElmtId(u5);
  }
  aboutToBeDeleted() {
    this.__contentMaxHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  defaultContentBuilder(t5 = null) {
  }
  get contentMaxHeight() {
    return this.__contentMaxHeight.get();
  }
  set contentMaxHeight(s5) {
    this.__contentMaxHeight.set(s5);
  }
  initialRender() {
    this.observeComponentCreation((q5, r5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(q5);
      Column.create();
      Column.width('100%');
      if (!r5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.buildTitles.bind(this)();
    this.observeComponentCreation((o5, p5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o5);
      Column.create();
      Column.padding(this.getContentPadding());
      Column.constraintSize({ maxHeight: this.contentMaxHeight, });
      if (!p5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.contentBuilder.bind(this)();
    Column.pop();
    this.buildButtons.bind(this)();
    Column.pop();
  }
  buildTitles(i4 = null) {
    this.observeComponentCreation((h5, i5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h5);
      Column.create();
      Column.constraintSize({
        minHeight: this.getTitleAreaMinHeight(),
      });
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
      Column.onAreaChange((k5, l5) => {
        this.titleHeight = Number(l5.height);
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
      });
      if (!i5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((f5, g5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(f5);
      Row.create();
      Row.width('100%');
      if (!g5) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((d5, e5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(d5);
      Text.create(this.primaryTitle);
      Text.fontWeight(FontWeight.Bold);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
      Text.textAlign(TextAlign.Start);
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Title_S'], bundleName: '', moduleName: '' });
      Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      if (!e5) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
    this.observeComponentCreation((t4, u4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t4);
      If.create();
      if (this.primaryTitle && this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b5, c5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b5);
            Row.create();
            if (!c5) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((z4, a5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(z4);
            Divider.create();
            Divider.margin({ id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' });
            Divider.color(Color.Transparent);
            if (!a5) {
              Divider.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!u4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((r4, s4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r4);
      Row.create();
      Row.width('100%');
      if (!s4) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((p4, q4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p4);
      Text.create(this.secondaryTitle);
      Text.fontWeight(FontWeight.Regular);
      Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
      Text.textAlign(TextAlign.Start);
      Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
      Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_S'], bundleName: '', moduleName: '' });
      Text.maxLines(TITLE_MAX_LINES);
      Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      if (!q4) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
    Column.pop();
  }
  buildButtons(e4 = null) {
    this.observeComponentCreation((g4, h4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g4);
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
      if (!h4) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.buildHorizontalAlignButtons.bind(this)();
    this.buildVerticalAlignButtons.bind(this)();
    Column.pop();
  }
  buildSingleButton(o3, p3 = null) {
    this.observeComponentCreation((r3, s3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(r3);
      If.create();
      if (this.isNewPropertiesHighPriority(o3)) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((b4, c4) => {
            let d4;
            ViewStackProcessor.StartGetAccessRecordingFor(b4);
            Button.createWithLabel(o3.value);
            __Button__setButtonProperties(o3, this.controller);
            Button.role((d4 = o3.role) !== null && d4 !== void 0 ? d4 : ButtonRole.NORMAL);
            if (!c4) {
              Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Button.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
          this.observeComponentCreation((v3, w3) => {
            let x3;
            let y3;
            ViewStackProcessor.StartGetAccessRecordingFor(v3);
            Button.createWithLabel(o3.value);
            __Button__setButtonProperties(o3, this.controller);
            Button.backgroundColor((x3 = o3.background) !== null && x3 !== void 0 ? x3 : { id: -1, type: 10001, params: ['sys.color.ohos_id_color_background_transparent'], bundleName: '', moduleName: '' });
            Button.fontColor((y3 = o3.fontColor) !== null && y3 !== void 0 ? y3 : { id: -1, type: 10001, params: ['sys.color.ohos_id_color_text_primary_activated'], bundleName: '', moduleName: '' });
            if (!w3) {
              Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Button.pop();
        });
      }
      if (!s3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  buildHorizontalAlignButtons(x2 = null) {
    this.observeComponentCreation((z2, a3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(z2);
      If.create();
      if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((m3, n3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m3);
            Row.create();
            if (!n3) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.buildSingleButton.bind(this)(this.buttons[0]);
          this.observeComponentCreation((f3, g3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f3);
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((k3, l3) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(k3);
                  Divider.create();
                  Divider.width({ id: -1, type: 10002, params: ['sys.float.alert_divider_width'], bundleName: '', moduleName: '' });
                  Divider.height({ id: -1, type: 10002, params: ['sys.float.alert_divider_height'], bundleName: '', moduleName: '' });
                  Divider.color({ id: -1, type: 10001, params: ['sys.color.alert_divider_color'], bundleName: '', moduleName: '' });
                  Divider.vertical(true);
                  Divider.margin({
                    left: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                    right: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                  });
                  if (!l3) {
                    Divider.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.buildSingleButton.bind(this)(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1]);
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!g3) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
          Row.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!a3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  buildVerticalAlignButtons(e2 = null) {
    this.observeComponentCreation((g2, h2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(g2);
      If.create();
      if (this.buttons && this.isVerticalAlignButton()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((v2, w2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v2);
            Column.create();
            if (!w2) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((m2, n2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m2);
            ForEach.create();
            const o2 = (s2, t2) => {
              const u2 = s2;
              this.buildButtonWithDivider.bind(this)(t2);
            };
            this.forEachUpdateFunction(m2, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), o2, (r2) => r2.value.toString(), true, false);
            if (!n2) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!h2) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
  }
  buildButtonWithDivider(m1, n1 = null) {
    this.observeComponentCreation((p1, q1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(p1);
      If.create();
      if (this.buttons && this.buttons[m1]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((c2, d2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(c2);
            Row.create();
            if (!d2) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.buildSingleButton.bind(this)(this.buttons[m1]);
          Row.pop();
          this.observeComponentCreation((v1, w1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v1);
            If.create();
            if (m1 < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((a2, b2) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(a2);
                  Row.create();
                  Row.height({ id: -1, type: 10002, params: ['sys.float.alert_button_vertical_space'], bundleName: '', moduleName: '' });
                  if (!b2) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                Row.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!w1) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!q1) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
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
    let l1 = getNumberByResource('alert_button_top_padding');
    if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
      l1 += BUTTON_DEFAULT_HEIGHT +
        getNumberByResource('alert_button_bottom_padding_horizontal');
    }
    else {
      l1 += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
        (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
        getNumberByResource('alert_button_bottom_padding_vertical');
    }
    return l1;
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
  isNewPropertiesHighPriority(k1) {
    if (k1.role === ButtonRole.ERROR) {
      return true;
    }
    if (k1.buttonStyle !== undefined &&
      k1.buttonStyle !== getNumberByResource('alert_button_style')) {
      return true;
    }
    if (k1.background === undefined && k1.fontColor === undefined) {
      return true;
    }
    return false;
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export class CustomDialogComponent extends ViewPU {
  constructor(e1, f1, g1, h1 = -1, i1 = undefined, j1) {
    super(e1, g1, h1, j1);
    if (typeof i1 === 'function') {
      this.paramsGenerator_ = i1;
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
    this.setInitiallyProvidedValue(f1);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(d1) {
    if (d1.controller !== undefined) {
      this.controller = d1.controller;
    }
    if (d1.primaryTitle !== undefined) {
      this.primaryTitle = d1.primaryTitle;
    }
    if (d1.secondaryTitle !== undefined) {
      this.secondaryTitle = d1.secondaryTitle;
    }
    if (d1.contentBuilder !== undefined) {
      this.contentBuilder = d1.contentBuilder;
    }
    if (d1.buttons !== undefined) {
      this.buttons = d1.buttons;
    }
    if (d1.contentAreaPadding !== undefined) {
      this.contentAreaPadding = d1.contentAreaPadding;
    }
    if (d1.screenWidth !== undefined) {
      this.screenWidth = d1.screenWidth;
    }
    if (d1.columnModifier !== undefined) {
      this.columnModifier = d1.columnModifier;
    }
    if (d1.isFirstInit !== undefined) {
      this.isFirstInit = d1.isFirstInit;
    }
  }
  updateStateVars(c1) {
  }
  purgeVariableDependenciesOnElmtId(b1) {
    this.__columnModifier.purgeDependencyOnElmtId(b1);
  }
  aboutToBeDeleted() {
    this.__columnModifier.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get columnModifier() {
    return this.__columnModifier.get();
  }
  set columnModifier(a1) {
    this.__columnModifier.set(a1);
  }
  initialRender() {
    this.observeComponentCreation((v, w) => {
      ViewStackProcessor.StartGetAccessRecordingFor(v);
      Column.create();
      Column.onAreaChange((y, z) => {
        if (!this.isFirstInit) {
          return;
        }
        if (this.screenWidth > getNumberByResource('alert_container_max_width')) {
          this.columnModifier.customStyle = z.width > getNumberByResource('alert_container_max_width');
        }
        else {
          this.columnModifier.customStyle = z.width >= this.screenWidth;
        }
        this.isFirstInit = false;
      });
      if (!w) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((t, u) => {
      ViewStackProcessor.StartGetAccessRecordingFor(t);
      Column.create();
      Column.attributeModifier.bind(this)(this.columnModifier);
      if (!u) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    {
      this.observeComponentCreation((n, o) => {
        ViewStackProcessor.StartGetAccessRecordingFor(n);
        if (o) {
          let p = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
            contentAreaPadding: this.contentAreaPadding,
          }, undefined, n, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 362 });
          ViewPU.create(p);
          let q = () => {
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
          p.paramsGenerator_ = q;
        }
        else {
          this.updateStateVarsOfChildByElmtId(n, {});
        }
        ViewStackProcessor.StopGetAccessRecording();
      });
    }
    Column.pop();
    Column.pop();
  }
  aboutToAppear() {
    try {
      this.screenWidth = px2vp(display.getDefaultDisplaySync().width);
    }
    catch (j) {
      hilog.error(0x3900, 'Ace', `CustomDialogComponent getDefaultDisplaySync error: ${JSON.stringify(j)}`);
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
  applyNormalAttribute(i) {
    if (!this.customStyle) {
      return;
    }
    i.backgroundBlurStyle(BlurStyle.Thick);
    i.borderRadius({ id: -1, type: 10002, params: ['sys.float.ohos_id_corner_radius_dialog'], bundleName: '', moduleName: '' });
    i.margin({
      left: { id: -1, type: 10002, params: ['sys.float.ohos_id_dialog_margin_start'], bundleName: '', moduleName: '' },
      right: { id: -1, type: 10002, params: ['sys.float.ohos_id_dialog_margin_end'], bundleName: '', moduleName: '' },
      bottom: { id: -1, type: 10002, params: ['sys.float.ohos_id_dialog_margin_bottom'], bundleName: '', moduleName: '' },
    });
    i.backgroundColor({ id: -1, type: 10001, params: ['sys.color.ohos_id_color_dialog_bg'], bundleName: '', moduleName: '' });
  }
}
function __Button__setButtonProperties(e, f) {
  let g;
  Button.onClick(() => {
    if (e.action) {
      e.action();
    }
    f === null || f === void 0 ? void 0 : f.close();
  });
  Button.buttonStyle((g = e.buttonStyle) !== null && g !== void 0 ? g : getNumberByResource('alert_button_style'));
  Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
}
function getNumberByResource(a) {
  try {
    return resourceManager.getSystemResourceManager().getNumberByName(a);
  }
  catch (b) {
    let c = b.code;
    let d = b.message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${c}, message: ${d}`);
    return 0;
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