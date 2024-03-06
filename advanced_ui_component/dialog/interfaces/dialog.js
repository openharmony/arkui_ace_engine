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

const hilog = requireNapi('hilog');
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
const LOADING_PROGRESS_HEIGHT = 48;
const ITEM_TEXT_SIZE = 14;

export class TipsDialog extends ViewPU {
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.imageRes = void 0;
    this.imageSize = { width: '100%', height: 180 };
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
    void 0 !== e.imageRes && (this.imageRes = e.imageRes);
    void 0 !== e.imageSize && (this.imageSize = e.imageSize);
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
      Row.width('100%');
      Row.padding({ left: 24, right: 24 });
      Row.margin({ top: 24 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Column.create();
      Column.layoutWeight(1);
      Column.clip(!0);
      o || Column.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Image.create(this.imageRes);
      Image.size(this.imageSize);
      Image.objectFit(ImageFit.Fill);
      o || Image.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Column.pop();
    Row.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Row.create();
      Row.padding({ left: 24, right: 24 });
      Row.margin({ top: 16 });
      o || Row.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      Text.create(this.title);
      Text.fontSize({
        id: -1,
        type: 10002,
        params: ['sys.float.ohos_id_text_size_headline8'],
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
      Text.textAlign(TextAlign.Center);
      Text.maxLines(2);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.minFontSize(15);
      Text.maxFontSize({
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_text_size_headline8"],
        bundleName: "",
        moduleName: ""
      });
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
          Text.fontWeight(FontWeight.Regular);
          Text.fontColor({
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            bundleName: '',
            moduleName: ''
          });
          Text.textAlign(TextAlign.Center);
          Text.minFontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_body3'],
            bundleName: '',
            moduleName: ''
          });
          Text.maxLines(2);
          Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
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

export class SelectDialog extends ViewPU {
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.title = '';
    this.content = '';
    this.selectedIndex = -1;
    this.confirm = { value: '' };
    this.radioContent = [];
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.title && (this.title = e.title);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.selectedIndex && (this.selectedIndex = e.selectedIndex);
    void 0 !== e.confirm && (this.confirm = e.confirm);
    void 0 !== e.radioContent && (this.radioContent = e.radioContent);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
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
          o || Row.pop();
          ViewStackProcessor.StopGetAccessRecording();
        }));
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Text.create(this.content);
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
      List.create({ space: 1 });
      List.width('100%');
      List.padding({ left: 24, right: 24, top: 8, bottom: 8 });
      List.clip(!1);
      o || List.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      ForEach.create();
      this.forEachUpdateFunction(e, this.radioContent, ((e, o) => {
        const t = e;
        {
          const e = !0;
          const r = (o, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            ListItem.create(i, e);
            t || ListItem.pop();
            ViewStackProcessor.StopGetAccessRecording();
          };
          const s = () => {
            this.observeComponentCreation(r);
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Column.create();
              o || Column.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create();
              Row.constraintSize({ minHeight: 48 });
              Row.clip(!1);
              Row.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(t.title);
              Text.fontSize(ITEM_TEXT_SIZE);
              Text.fontWeight(FontWeight.Medium);
              Text.maxLines(CONTENT_MAX_LINES);
              Text.fontColor({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                bundleName: '',
                moduleName: ''
              });
              Text.layoutWeight(1);
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Text.pop();
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: 20, height:20});
              Radio.checked(this.selectedIndex === o);
              Radio.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              r || Radio.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Row.pop();
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              o < this.radioContent.length - 1 ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, o) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Divider.create();
                  Divider.color({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_list_separator'],
                    bundleName: '',
                    moduleName: ''
                  });
                  o || Divider.pop();
                  ViewStackProcessor.StopGetAccessRecording();
                }));
              })) : If.branchId(1);
              t || If.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          const i = (e, s) => {
            r(e, s);
            this.updateFuncByElmtId.set(e, r);
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Column.create();
                o || Column.pop();
                ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Row.create();
              Row.constraintSize({ minHeight: 48 });
              Row.clip(!1);
              Row.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              o || Row.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            this.observeComponentCreation(((e, o) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Text.create(t.title);
              Text.fontSize(ITEM_TEXT_SIZE);
              Text.fontWeight(FontWeight.Regular);
              Text.maxLines(CONTENT_MAX_LINES);
              Text.fontColor({
                id: -1,
                type: 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                bundleName: '',
                moduleName: ''
              });
              Text.layoutWeight(1);
              o || Text.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Text.pop();
            this.observeComponentCreation(((e, r) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              Radio.create({ value: 'item.title', group: 'radioGroup' });
              Radio.size({ width: 20, height: 20 });
              Radio.checked(this.selectedIndex === o);
              Radio.onClick((() => {
                t.action && t.action();
                this.controller.close();
              }));
              r || Radio.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            Row.pop();
            this.observeComponentCreation(((e, t) => {
              ViewStackProcessor.StartGetAccessRecordingFor(e);
              If.create();
              o < this.radioContent.length - 1 ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, o) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Divider.create();
                  Divider.color({
                    id: -1,
                    type: 10001,
                    params: ['sys.color.ohos_id_color_list_separator'],
                    bundleName: '',
                    moduleName: ''
                  });
                  o || Divider.pop();
                  ViewStackProcessor.StopGetAccessRecording();
                }));
              })) : If.branchId(1);
              t || If.pop();
              ViewStackProcessor.StopGetAccessRecording();
            }));
            If.pop();
            Column.pop();
            ListItem.pop();
          };
          e ? (() => {
            this.observeComponentCreation(r);
            ListItem.pop();
          })() : s();
        }
      }), void 0, !0, !1);
      o || ForEach.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    ForEach.pop();
    List.pop();
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
      this.confirm.value ? this.ifElseBranchUpdateFunction(0, (() => {
        this.observeComponentCreation(((e, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Button.createWithLabel(this.confirm.value);
          Button.fontSize({
            id: -1,
            type: 10002,
            params: ['sys.float.ohos_id_text_size_button1'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontWeight(FontWeight.Medium);
          Button.layoutWeight(1);
          Button.backgroundColor(this.confirm.background ? this.confirm.background : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_background_transparent'],
            bundleName: '',
            moduleName: ''
          });
          Button.fontColor(this.confirm.fontColor ? this.confirm.fontColor : {
            id: -1,
            type: 10001,
            params: ['sys.color.ohos_id_color_text_primary_activated'],
            bundleName: '',
            moduleName: ''
          });
          Button.onClick((() => {
            this.confirm.action && this.confirm.action();
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
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.content = '';
    this.primaryButton = { value: '' };
    this.secondaryButton = { value: '' };
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.content && (this.content = e.content);
    void 0 !== e.primaryButton && (this.primaryButton = e.primaryButton);
    void 0 !== e.secondaryButton && (this.secondaryButton = e.secondaryButton);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
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
      Row.padding({
        left: 24,
        right: 24,
        top: 24,
        bottom: this.secondaryButton.value || this.primaryButton.value ? 0 : 24
      });
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

export class LoadingDialog extends ViewPU {
  constructor(e, o, t, r = -1) {
    super(e, t, r);
    this.controller = void 0;
    this.content = '';
    this.setInitiallyProvidedValue(o);
  }

  setInitiallyProvidedValue(e) {
    void 0 !== e.controller && (this.controller = e.controller);
    void 0 !== e.content && (this.content = e.content);
  }

  updateStateVars(e) {
  }

  purgeVariableDependenciesOnElmtId(e) {
  }

  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }

  setController(e) {
    this.controller = e;
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
      Row.margin({ left: 24, right: 24, top: 24, bottom: 24 });
      Row.constraintSize({ minHeight: 48 });
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
      Text.layoutWeight(1);
      o || Text.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Text.pop();
    this.observeComponentCreation(((e, o) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e);
      LoadingProgress.create();
      LoadingProgress.width(LOADING_PROGRESS_WIDTH);
      LoadingProgress.height(LOADING_PROGRESS_HEIGHT);
      LoadingProgress.margin({ left: 16 });
      o || LoadingProgress.pop();
      ViewStackProcessor.StopGetAccessRecording();
    }));
    Row.pop();
    Column.pop();
  }

  rerender() {
    this.updateDirtyElements();
  }
}

if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
export class CustomContentDialog extends ViewPU {
  constructor(a6, b6, c6, d6 = -1, e6 = undefined, f6) {
    super(a6, c6, d6, f6);
    if (typeof e6 === "function") {
      this.paramsGenerator_ = e6;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = undefined;
    this.buttons = undefined;
    this.setInitiallyProvidedValue(b6);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(z5) {
    if (z5.controller !== undefined) {
      this.controller = z5.controller;
    }
    if (z5.primaryTitle !== undefined) {
      this.primaryTitle = z5.primaryTitle;
    }
    if (z5.secondaryTitle !== undefined) {
      this.secondaryTitle = z5.secondaryTitle;
    }
    if (z5.contentBuilder !== undefined) {
      this.contentBuilder = z5.contentBuilder;
    }
    if (z5.buttons !== undefined) {
      this.buttons = z5.buttons;
    }
  }
  updateStateVars(y5) {
  }
  purgeVariableDependenciesOnElmtId(x5) {
  }
  aboutToBeDeleted() {
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  setController(w5) {
    this.controller = w5;
  }
  initialRender() {
    {
      this.observeComponentCreation((q5, r5) => {
        ViewStackProcessor.StartGetAccessRecordingFor(q5);
        if (r5) {
          let s5 = new CustomDialogContentComponent(this, {
            controller: this.controller,
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            contentBuilder: () => {
              this.contentBuilder();
            },
            buttons: this.buttons,
          }, undefined, q5, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 22 });
          ViewPU.create(s5);
          let t5 = () => {
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
          s5.paramsGenerator_ = t5;
        }
        else {
          this.updateStateVarsOfChildByElmtId(q5, {});
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
  constructor(j5, k5, l5, m5 = -1, n5 = undefined, o5) {
    super(j5, l5, m5, o5);
    if (typeof n5 === "function") {
      this.paramsGenerator_ = n5;
    }
    this.controller = undefined;
    this.primaryTitle = undefined;
    this.secondaryTitle = undefined;
    this.contentBuilder = this.defaultContentBuilder;
    this.buttons = undefined;
    this.titleHeight = 0;
    this.__contentMaxHeight = new ObservedPropertySimplePU('', this, "contentMaxHeight");
    this.setInitiallyProvidedValue(k5);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(i5) {
    if (i5.controller !== undefined) {
      this.controller = i5.controller;
    }
    if (i5.primaryTitle !== undefined) {
      this.primaryTitle = i5.primaryTitle;
    }
    if (i5.secondaryTitle !== undefined) {
      this.secondaryTitle = i5.secondaryTitle;
    }
    if (i5.contentBuilder !== undefined) {
      this.contentBuilder = i5.contentBuilder;
    }
    if (i5.buttons !== undefined) {
      this.buttons = i5.buttons;
    }
    if (i5.titleHeight !== undefined) {
      this.titleHeight = i5.titleHeight;
    }
    if (i5.contentMaxHeight !== undefined) {
      this.contentMaxHeight = i5.contentMaxHeight;
    }
  }
  updateStateVars(h5) {
  }
  purgeVariableDependenciesOnElmtId(g5) {
    this.__contentMaxHeight.purgeDependencyOnElmtId(g5);
  }
  aboutToBeDeleted() {
    this.__contentMaxHeight.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  defaultContentBuilder(f5 = null) {
  }
  get contentMaxHeight() {
    return this.__contentMaxHeight.get();
  }
  set contentMaxHeight(e5) {
    this.__contentMaxHeight.set(e5);
  }
  initialRender() {
    this.observeComponentCreation((c5, d5) => {
      ViewStackProcessor.StartGetAccessRecordingFor(c5);
      Column.create();
      Column.width('100%');
      if (!d5) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((y4, z4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y4);
      If.create();
      if (this.primaryTitle || this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.buildTitles.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!z4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((w4, x4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(w4);
      Column.create();
      Column.padding(this.getContentPadding());
      Column.constraintSize({ maxHeight: this.contentMaxHeight, });
      if (!x4) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.contentBuilder.bind(this)();
    Column.pop();
    this.observeComponentCreation((s4, t4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(s4);
      If.create();
      if (this.buttons && this.buttons.length > 0) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.buildButtons.bind(this)();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!t4) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  buildTitles(a3 = null) {
    this.observeComponentCreation((j4, k4) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j4);
      Column.create();
      Column.constraintSize({
        minHeight: this.getTitleAreaMinHeight(),
      });
      Column.justifyContent(FlexAlign.Center);
      Column.width('100%');
      Column.padding(this.getTitleAreaPadding());
      Column.onAreaChange((m4, n4) => {
        this.titleHeight = Number(n4.height);
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
      });
      if (!k4) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((o3, p3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(o3);
      If.create();
      if (this.primaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((h4, i4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h4);
            Row.create();
            Row.width('100%');
            if (!i4) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((f4, g4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f4);
            Text.create(this.primaryTitle);
            Text.fontWeight(FontWeight.Bold);
            Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_primary'], bundleName: '', moduleName: '' });
            Text.textAlign(TextAlign.Start);
            Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Title_S'], bundleName: '', moduleName: '' });
            Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_L'], bundleName: '', moduleName: '' });
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            if (!g4) {
              Text.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          Text.pop();
          Row.pop();
          this.observeComponentCreation((v3, w3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v3);
            If.create();
            if (this.secondaryTitle) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((d4, e4) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(d4);
                  Row.create();
                  if (!e4) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.observeComponentCreation((b4, c4) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(b4);
                  Divider.create();
                  Divider.margin({ id: -1, type: 10002, params: ['sys.float.padding_level1'], bundleName: '', moduleName: '' });
                  Divider.color(Color.Transparent);
                  if (!c4) {
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
            if (!w3) {
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
      if (!p3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((e3, f3) => {
      ViewStackProcessor.StartGetAccessRecordingFor(e3);
      If.create();
      if (this.secondaryTitle) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((m3, n3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(m3);
            Row.create();
            Row.width('100%');
            if (!n3) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((k3, l3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k3);
            Text.create(this.secondaryTitle);
            Text.fontWeight(FontWeight.Regular);
            Text.fontColor({ id: -1, type: 10001, params: ['sys.color.font_secondary'], bundleName: '', moduleName: '' });
            Text.textAlign(TextAlign.Start);
            Text.maxFontSize({ id: -1, type: 10002, params: ['sys.float.Subtitle_S'], bundleName: '', moduleName: '' });
            Text.minFontSize({ id: -1, type: 10002, params: ['sys.float.Body_S'], bundleName: '', moduleName: '' });
            Text.maxLines(TITLE_MAX_LINES);
            Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            if (!l3) {
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
      if (!f3) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  buildButtons(g1 = null) {
    this.observeComponentCreation((y2, z2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y2);
      Column.create();
      Column.width('100%');
      Column.padding(this.getOperationAreaPadding());
      if (!z2) {
        Column.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((j2, k2) => {
      ViewStackProcessor.StartGetAccessRecordingFor(j2);
      If.create();
      if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((w2, x2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w2);
            Row.create();
            if (!x2) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.buildSingleButton.bind(this)(this.buttons[0]);
          this.observeComponentCreation((p2, q2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p2);
            If.create();
            if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((u2, v2) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(u2);
                  Divider.create();
                  Divider.width({ id: -1, type: 10002, params: ['sys.float.alert_divider_width'], bundleName: '', moduleName: '' });
                  Divider.height({ id: -1, type: 10002, params: ['sys.float.alert_divider_height'], bundleName: '', moduleName: '' });
                  Divider.color({ id: -1, type: 10001, params: ['sys.color.alert_divider_color'], bundleName: '', moduleName: '' });
                  Divider.vertical(true);
                  Divider.margin({
                    left: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                    right: { id: -1, type: 10002, params: ['sys.float.alert_button_horizontal_space'], bundleName: '', moduleName: '' },
                  });
                  if (!v2) {
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
            if (!q2) {
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
      if (!k2) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((k1, l1) => {
      ViewStackProcessor.StartGetAccessRecordingFor(k1);
      If.create();
      if (this.isVerticalAlignButton()) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((h2, i2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h2);
            Column.create();
            if (!i2) {
              Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.observeComponentCreation((y1, z1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y1);
            ForEach.create();
            const a2 = (e2, f2) => {
              const g2 = e2;
              this.buildButtonWithDivider.bind(this)(f2);
            };
            this.forEachUpdateFunction(y1, this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT - 1), a2, (d2) => d2.value.toString(), true, false);
            if (!z1) {
              ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          ForEach.pop();
          this.observeComponentCreation((r1, s1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r1);
            If.create();
            if (this.buttons.length >= VERTICAL_BUTTON_MAX_COUNT) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((w1, x1) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(w1);
                  Row.create();
                  if (!x1) {
                    Row.pop();
                  }
                  ViewStackProcessor.StopGetAccessRecording();
                });
                this.buildSingleButton.bind(this)(this.buttons[VERTICAL_BUTTON_MAX_COUNT - 1]);
                Row.pop();
              });
            }
            else {
              this.ifElseBranchUpdateFunction(1, () => {
              });
            }
            if (!s1) {
              If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          If.pop();
          Column.pop();
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!l1) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    Column.pop();
  }
  buildSingleButton(x, y = null) {
    this.observeComponentCreation((a1, b1) => {
      var c1, d1;
      ViewStackProcessor.StartGetAccessRecordingFor(a1);
      Button.createWithLabel(x.value);
      Button.onClick(() => {
        var f1;
        if (x.action) {
          x.action();
        }
        (f1 = this.controller) === null || f1 === void 0 ? void 0 : f1.close();
      });
      Button.buttonStyle((c1 = x.buttonStyle) !== null && c1 !== void 0 ? c1 : getNumberByResource('alert_button_style'));
      Button.role((d1 = x.role) !== null && d1 !== void 0 ? d1 : ButtonRole.NORMAL);
      Button.layoutWeight(BUTTON_LAYOUT_WEIGHT);
      if (!b1) {
        Button.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Button.pop();
  }
  buildButtonWithDivider(f, g = null) {
    this.observeComponentCreation((i, j) => {
      ViewStackProcessor.StartGetAccessRecordingFor(i);
      If.create();
      if (this.buttons && this.buttons[f]) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((v, w) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v);
            Row.create();
            if (!w) {
              Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
          this.buildSingleButton.bind(this)(this.buttons[f]);
          Row.pop();
          this.observeComponentCreation((o, p) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            If.create();
            if (f < this.buttons.length - 1) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation((t, u) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(t);
                  Row.create();
                  Row.height({ id: -1, type: 10002, params: ['sys.float.alert_button_vertical_space'], bundleName: '', moduleName: '' });
                  if (!u) {
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
            if (!p) {
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
      if (!j) {
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
    let e = getNumberByResource('alert_button_top_padding');
    if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
      e += BUTTON_DEFAULT_HEIGHT
        + getNumberByResource('alert_button_bottom_padding_horizontal');
    }
    else {
      e += BUTTON_DEFAULT_HEIGHT * this.buttons.length
        + (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space')
        + getNumberByResource('alert_button_bottom_padding_vertical');
    }
    return e;
  }
  getContentPadding() {
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
    else {
      return {
        top: 0,
        right: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_right'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_title_padding_left'], bundleName: '', moduleName: '' },
        bottom: 0,
      };
    }
  }
  isVerticalAlignButton() {
    return this.buttons && this.buttons.length > HORIZON_BUTTON_MAX_COUNT;
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
    else {
      return {
        top: { id: -1, type: 10002, params: ['sys.float.alert_button_top_padding'], bundleName: '', moduleName: '' },
        right: { id: -1, type: 10002, params: ['sys.float.alert_right_padding_horizontal'], bundleName: '', moduleName: '' },
        left: { id: -1, type: 10002, params: ['sys.float.alert_left_padding_horizontal'], bundleName: '', moduleName: '' },
        bottom: { id: -1, type: 10002, params: ['sys.float.alert_button_bottom_padding_horizontal'], bundleName: '', moduleName: '' },
      };
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
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

export default { TipsDialog, ConfirmDialog, SelectDialog, AlertDialog, LoadingDialog, CustomContentDialog };