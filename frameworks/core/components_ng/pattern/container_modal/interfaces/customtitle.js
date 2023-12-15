/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

const LayeredDrawableDescriptor = requireNapi('arkui.drawableDescriptor').LayeredDrawableDescriptor;
const TITLE_ICON_SIZE = '20vp';
const TITLE_PADDING_START = '20vp';
const TITLE_ELEMENT_MARGIN_HORIZONTAL = '12vp';
const TITLE_TEXT_FONT_SIZE = '16fp';
const TITLE_TEXT_FONT_WEIGHT = '500px';
const TITLE_ROW_HEIGHT = '37vp'
export class Index extends ViewPU {
  constructor(parent, params, __localStorage, elmtId = -1) {
    super(parent, __localStorage, elmtId);
    this.__appLabel = new ObservedPropertySimplePU('', this, "appLabel");
    this.__appTitle = new ObservedPropertySimplePU('', this, "appTitle");
    this.__textColor = new ObservedPropertySimplePU(0xff000000, this, "textColor");
    this.__appIcon = new ObservedPropertyObjectPU(new LayeredDrawableDescriptor(), this, "appIcon");
    this.__pixelMap = new ObservedPropertyObjectPU(undefined, this, "pixelMap");
    this.setInitiallyProvidedValue(params);
  }
  setInitiallyProvidedValue(params) {
    if (params.textColor !== undefined) {
      this.textColor = params.textColor;
    }
    if (params.appLabel !== undefined) {
      this.appLabel = params.appLabel;
    }
    if (params.appTitle !== undefined) {
      this.appTitle = params.appTitle;
    }
    if (params.appIcon !== undefined) {
      this.appIcon = params.appIcon;
    }
    if (params.pixelMap !== undefined) {
      this.pixelMap = params.pixelMap;
    }
  }
  updateStateVars(params) {
  }
  purgeVariableDependenciesOnElmtId(rmElmtId) {
    this.__textColor.purgeDependencyOnElmtId(rmElmtId);
    this.__appLabel.purgeDependencyOnElmtId(rmElmtId);
    this.__appTitle.purgeDependencyOnElmtId(rmElmtId);
    this.__appIcon.purgeDependencyOnElmtId(rmElmtId);
    this.__pixelMap.purgeDependencyOnElmtId(rmElmtId);
  }
  aboutToBeDeleted() {
    this.__textColor.aboutToBeDeleted();
    this.__appLabel.aboutToBeDeleted();
    this.__appTitle.aboutToBeDeleted();
    this.__appIcon.aboutToBeDeleted();
    this.__pixelMap.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get textColor() {
    return this.__textColor.get();
  }
  set textColor(newValue) {
    this.__textColor.set(newValue);
  }
  get appLabel() {
    return this.__appLabel.get();
  }
  set appLabel(newValue) {
    this.__appLabel.set(newValue);
  }
  get appTitle() {
    return this.__appTitle.get();
  }
  set appTitle(newValue) {
      this.__appTitle.set(newValue);
  }
  get appIcon() {
    return this.__appIcon.get();
  }
  set appIcon(newValue) {
    this.__appIcon.set(newValue);
  }
  get pixelMap() {
    return this.__pixelMap.get();
  }
  set pixelMap(newValue) {
    this.__pixelMap.set(newValue);
  }
  aboutToAppear() {
    const context = getContext(this);
    try {
      this.appLabel = context.resourceManager.getStringSync(context.applicationInfo.labelId);
    }
    catch (error) {
      let code = error.code;
      let message = error.message;
      console.error(`get appLabel failed, error code: ${code}, message: ${message}.`);
    }
    try {
      this.appIcon = context.resourceManager.getDrawableDescriptor(context.applicationInfo.iconId);
    }
    catch (error) {
      let code = error.code;
      let message = error.message;
      console.error(`get appIcon failed, error code: ${code}, message: ${message}.`);
    }
  }
  onWindowFocused() {
    this.textColor = 0xff000000;
  }
  onWindowUnfocused() {
    this.textColor = 0x66000000;
  }
  setAppTitle(content) {
    this.appTitle = content;
  }
  setAppIcon(pixelMap) {
    this.pixelMap = pixelMap;
  }
  initialRender() {
    this.observeComponentCreation((elmtId, isInitialRender) => {
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      Row.create();
      Row.width('100%');
      Row.height(TITLE_ROW_HEIGHT);
      Row.justifyContent(FlexAlign.Start);
      Row.alignItems(VerticalAlign.Center);
      Row.padding({ top: 6, bottom: 6 });
      Row.clip(true);
      if (!isInitialRender) {
        Row.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((elmtId, isInitialRender) => {
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      Image.create(this.pixelMap ? this.pixelMap : this.appIcon);
      Image.id("enhanceAppIcon");
      Image.height(TITLE_ICON_SIZE);
      Image.width(TITLE_ICON_SIZE);
      Image.interpolation(ImageInterpolation.Medium);
      Image.focusable(false);
      Image.margin({ left: TITLE_PADDING_START, right: TITLE_ELEMENT_MARGIN_HORIZONTAL });
      if (!isInitialRender) {
        Image.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((elmtId, isInitialRender) => {
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      Text.create(this.appTitle ? this.appTitle : this.appLabel);
      Image.id("enhanceAppLabel");
      Text.maxLines(1);
      Text.fontSize(TITLE_TEXT_FONT_SIZE);
      Text.fontColor(this.textColor);
      Text.fontWeight(TITLE_TEXT_FONT_WEIGHT);
      Text.textOverflow({ overflow: TextOverflow.Ellipsis });
      Text.textAlign(TextAlign.Start);
      Text.layoutWeight(1.0);
      if (!isInitialRender) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Row.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
ViewStackProcessor.StartGetAccessRecordingFor(ViewStackProcessor.AllocateNewElmetIdForNextComponent());
loadCustomTitleBar(new Index(undefined, {}));
ViewStackProcessor.StopGetAccessRecording();