/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const hilog = requireNapi('ohos.hilog');
const DEFAULT_MARGIN = 16;
const ITEM_SPACE = 4;
const MIN_SIZE = 24;
const MID_SIZE = 40;
const MAX_SIZE = 48;
const MAX_FONT_SIZE = 2;
export class SwipeRefresher extends ViewPU {
  constructor(t, u, v, w = -1, x = undefined, y) {
    super(t, v, w, y);
    if (typeof x === 'function') {
      this.paramsGenerator_ = x;
    }
    this.__content = new SynchedPropertyObjectOneWayPU(u.content, this, 'content');
    this.__isLoading = new SynchedPropertySimpleOneWayPU(u.isLoading, this, 'isLoading');
    this.maxAppFontScale = 1;
    this.isFollowingSystemFontScale = false;
    this.minFontSize = 1.75;
    this.maxFontSize = 2;
    this.setInitiallyProvidedValue(u);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s) {
    if (s.content === undefined) {
      this.__content.set('');
    }
    if (s.isLoading === undefined) {
      this.__isLoading.set(false);
    }
    if (s.maxAppFontScale !== undefined) {
      this.maxAppFontScale = s.maxAppFontScale;
    }
    if (s.isFollowingSystemFontScale !== undefined) {
      this.isFollowingSystemFontScale = s.isFollowingSystemFontScale;
    }
    if (s.minFontSize !== undefined) {
      this.minFontSize = s.minFontSize;
    }
    if (s.maxFontSize !== undefined) {
      this.maxFontSize = s.maxFontSize;
    }
  }
  updateStateVars(r) {
    this.__content.reset(r.content);
    this.__isLoading.reset(r.isLoading);
  }
  purgeVariableDependenciesOnElmtId(q) {
    this.__content.purgeDependencyOnElmtId(q);
    this.__isLoading.purgeDependencyOnElmtId(q);
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
  set content(p) {
    this.__content.set(p);
  }
  get isLoading() {
    return this.__isLoading.get();
  }
  set isLoading(o) {
    this.__isLoading.set(o);
  }
  aboutToAppear() {
    try {
      let n = this.getUIContext();
      this.isFollowingSystemFontScale = n.isFollowingSystemFontScale();
      this.maxAppFontScale = n.getMaxFontScale();
    }
    catch (k) {
      let l = k.code;
      let m = k.message;
      hilog.error(0x3900, 'SwipeRefresher', `Failed to init fontsizescale info, cause, code: ${l}, message: ${m}`);
    }
  }
  updateFontScale() {
    let i = this.getUIContext();
    let j = i.getHostContext()?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(j, this.maxAppFontScale);
  }
  initialRender() {
    this.observeComponentCreation2((g, h) => {
      Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
    }, Flex);
    this.observeComponentCreation2((c, d) => {
      If.create();
      if (this.isLoading) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((e, f) => {
            LoadingProgress.create();
            LoadingProgress.height(Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.maxFontSize ? MAX_SIZE :
              (Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE : MIN_SIZE));
            LoadingProgress.width(Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.maxFontSize ? MAX_SIZE :
              (Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE : MIN_SIZE));
            LoadingProgress.margin({
              end: LengthMetrics.vp(ITEM_SPACE)
            });
          }, LoadingProgress);
        });
      }
      else {
        this.ifElseBranchUpdateFunction(1, () => {
        });
      }
    }, If);
    If.pop();
    this.observeComponentCreation2((a, b) => {
      Text.create(this.content);
      Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_secondary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_body2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
      Text.minFontScale(1);
      Text.maxFontScale(Math.min(this.updateFontScale(), 2));
      Text.padding({
        top: DEFAULT_MARGIN,
        bottom: DEFAULT_MARGIN
      });
    }, Text);
    Text.pop();
    Flex.pop();
  }
  rerender() {
    this.updateDirtyElements();
  }
}
export default { SwipeRefresher };