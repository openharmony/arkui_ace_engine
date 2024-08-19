/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('ohos.hilog');
const DEFAULT_MARGIN = 16;
const ITEM_SPACE = 4;
const MIN_SIZE = 24;
const MID_SIZE = 40;
const MAX_SIZE = 48;
const MAX_FONT_SIZE = 2;
export class SwipeRefresher extends ViewPU {
  constructor(u11, v11, w11, x11 = -1, y11 = undefined, z11) {
    super(u11, w11, x11, z11);
    if (typeof y11 === 'function') {
      this.paramsGenerator_ = y11;
    }
    this.__content = new SynchedPropertySimpleOneWayPU(v11.content, this, 'content');
    this.__isLoading = new SynchedPropertySimpleOneWayPU(v11.isLoading, this, 'isLoading');
    this.maxAppFontScale = 1;
    this.isFollowingSystemFontScale = false;
    this.minFontSize = 1.75;
    this.maxFontSize = 2;
    this.setInitiallyProvidedValue(v11);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(t11) {
    if (t11.content === undefined) {
      this.__content.set('');
    }
    if (t11.isLoading === undefined) {
      this.__isLoading.set(false);
    }
    if (t11.maxAppFontScale !== undefined) {
      this.maxAppFontScale = t11.maxAppFontScale;
    }
    if (t11.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = t11.isFollowingSystemFontScale;
    }
    if (t11.minFontSize !== undefined) {
      this.minFontSize = t11.minFontSize;
    }
    if (t11.maxFontSize !== undefined) {
      this.maxFontSize = t11.maxFontSize;
    }
  }
  updateStateVars(s11) {
    this.__content.reset(s11.content);
    this.__isLoading.reset(s11.isLoading);
  }
  purgeVariableDependenciesOnElmtId(r11) {
    this.__content.purgeDependencyOnElmtId(r11);
    this.__isLoading.purgeDependencyOnElmtId(r11);
  }
  aboutToBeDeleted() {
    this.__content.aboutToBeDeleted();
    this.__isLoading.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get content() {
    return this.__content.get();
  }
  set content(q11) {
    this.__content.set(q11);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(p11) {
    this.__isLoading.set(p11);
  }
  aboutToAppear() {
    try {
      let o11 = this.getUIContext();
      this.isFollowingSystemFontScale = o11.isFollowingSystemFontScale();
      this.maxAppFontScale = o11.getMaxFontScale();
    }
    catch (l11) {
      let m11 = l11.code;
      let n11 = l11.message;
      hilog.error(0x3900, 'SwipeRefresher', `Failed to init fontsizescale info, cause, code: ${m11}, message: ${n11}`);
    }
  }
  updateFontScale() {
    let j11 = this.getUIContext();
    let k11 = j11.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(k11, this.maxAppFontScale);
  }
  initialRender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.observeComponentCreation((h11, i11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(h11);
      Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
      if (!i11) {
        Flex.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    this.observeComponentCreation((a11, b11) => {
      ViewStackProcessor.StartGetAccessRecordingFor(a11);
      If.create();
      if (this.isLoading) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation((f11, g11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f11);
            LoadingProgress.create();
            LoadingProgress.height(Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.maxFontSize ? MAX_SIZE :
              (Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE : MIN_SIZE));
            LoadingProgress.width(Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.maxFontSize ? MAX_SIZE :
              (Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE : MIN_SIZE));
            LoadingProgress.margin({
              end: LengthMetrics.vp(ITEM_SPACE)
            });
            if (!g11) {
              LoadingProgress.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
          });
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
      if (!b11) {
        If.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    If.pop();
    this.observeComponentCreation((y10, z10) => {
      ViewStackProcessor.StartGetAccessRecordingFor(y10);
      Text.create(this.content);
      Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Text.minFontScale(1);
      Text.maxFontScale(Math.min(this.updateFontScale(), 2));
      Text.padding({
        top: DEFAULT_MARGIN,
        bottom: DEFAULT_MARGIN
      });
      if (!z10) {
        Text.pop();
      }
      ViewStackProcessor.StopGetAccessRecording();
    });
    Text.pop();
    Flex.pop();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
  rerender() {
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
    this.updateDirtyElements();
    PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
  }
}
export default { SwipeRefresher };