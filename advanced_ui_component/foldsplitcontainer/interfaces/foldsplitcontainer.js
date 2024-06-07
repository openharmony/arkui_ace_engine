/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

if (!("finalizeConstruction" in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {});
}
const display = globalThis.requireNapi("display");
const window = globalThis.requireNapi("window");
const hilog = globalThis.requireNapi("hilog");
const LengthMetrics = globalThis.requireNapi("arkui.node").LengthMetrics;
const curves = globalThis.requireNativeModule("ohos.curves");
const mediaQuery = requireNapi("mediaquery");
export var ExtraRegionPosition;
(function (k3) {
  k3[(k3["TOP"] = 1)] = "TOP";
  k3[(k3["BOTTOM"] = 2)] = "BOTTOM";
})(ExtraRegionPosition || (ExtraRegionPosition = {}));
export var PresetSplitRatio;
(function (j3) {
  j3[(j3["LAYOUT_1V1"] = 1)] = "LAYOUT_1V1";
  j3[(j3["LAYOUT_2V3"] = 0.6666666666666666)] = "LAYOUT_2V3";
  j3[(j3["LAYOUT_3V2"] = 1.5)] = "LAYOUT_3V2";
})(PresetSplitRatio || (PresetSplitRatio = {}));
function withDefaultValue(h3, i3) {
  if (h3 === void 0 || h3 === null) {
    return i3;
  }
  return h3;
}
function getSplitRatio(f3, g3) {
  if (f3 === void 0 || f3 === null) {
    return g3;
  }
  if (f3 <= 0) {
    return g3;
  }
  return f3;
}
class Logger {
  static debug(d3, ...e3) {
    return hilog.debug(0x3900, "FoldSplitContainer", d3, ...e3);
  }
  static info(b3, ...c3) {
    return hilog.info(0x3900, "FoldSplitContainer", b3, ...c3);
  }
  static error(z2, ...a3) {
    return hilog.error(0x3900, "FoldSplitContainer", z2, ...a3);
  }
}
function initLayout() {
  return {
    size: { width: 0, height: 0 },
    position: { x: 0, y: 0 },
  };
}
export class FoldSplitContainer extends ViewPU {
  constructor(t2, u2, v2, w2 = -1, x2 = undefined, y2) {
    super(t2, v2, w2, y2);
    if (typeof x2 === "function") {
      this.paramsGenerator_ = x2;
    }
    this.primary = undefined;
    this.secondary = undefined;
    this.extra = undefined;
    this.__expandedLayoutOptions = new SynchedPropertyObjectOneWayPU(
      u2.expandedLayoutOptions,
      this,
      "expandedLayoutOptions"
    );
    this.__semiFoldedLayoutOptions = new SynchedPropertyObjectOneWayPU(
      u2.semiFoldedLayoutOptions,
      this,
      "semiFoldedLayoutOptions"
    );
    this.__foldedLayoutOptions = new SynchedPropertyObjectOneWayPU(
      u2.foldedLayoutOptions,
      this,
      "foldedLayoutOptions"
    );
    this.__animationOptions = new SynchedPropertyObjectOneWayPU(
      u2.animationOptions,
      this,
      "animationOptions"
    );
    this.onHoverStatusChange = () => {};
    this.__primaryLayout = new ObservedPropertyObjectPU(
      initLayout(),
      this,
      "primaryLayout"
    );
    this.__secondaryLayout = new ObservedPropertyObjectPU(
      initLayout(),
      this,
      "secondaryLayout"
    );
    this.__extraLayout = new ObservedPropertyObjectPU(
      initLayout(),
      this,
      "extraLayout"
    );
    this.windowStatusType = window.WindowStatusType.UNDEFINED;
    this.foldStatus = display.FoldStatus.FOLD_STATUS_UNKNOWN;
    this.windowInstance = undefined;
    this.containerSize = { width: 0, height: 0 };
    this.containerGlobalPosition = { x: 0, y: 0 };
    this.listener = undefined;
    this.isSmallScreen = false;
    this.setInitiallyProvidedValue(u2);
    this.declareWatch("expandedLayoutOptions", this.updateLayout);
    this.declareWatch("semiFoldedLayoutOptions", this.updateLayout);
    this.declareWatch("foldedLayoutOptions", this.updateLayout);
    this.finalizeConstruction();
  }
  setInitiallyProvidedValue(s2) {
    if (s2.primary !== undefined) {
      this.primary = s2.primary;
    }
    if (s2.secondary !== undefined) {
      this.secondary = s2.secondary;
    }
    if (s2.extra !== undefined) {
      this.extra = s2.extra;
    }
    if (s2.expandedLayoutOptions === undefined) {
      this.__expandedLayoutOptions.set({
        horizontalSplitRatio: PresetSplitRatio.LAYOUT_3V2,
        verticalSplitRatio: PresetSplitRatio.LAYOUT_1V1,
        isExtraRegionPerpendicular: true,
        extraRegionPosition: ExtraRegionPosition.TOP,
      });
    }
    if (s2.semiFoldedLayoutOptions === undefined) {
      this.__semiFoldedLayoutOptions.set({
        horizontalSplitRatio: PresetSplitRatio.LAYOUT_3V2,
        showExtraRegion: true,
        extraRegionPosition: ExtraRegionPosition.TOP,
      });
    }
    if (s2.foldedLayoutOptions === undefined) {
      this.__foldedLayoutOptions.set({
        verticalSplitRatio: PresetSplitRatio.LAYOUT_1V1,
      });
    }
    if (s2.animationOptions === undefined) {
      this.__animationOptions.set(undefined);
    }
    if (s2.onHoverStatusChange !== undefined) {
      this.onHoverStatusChange = s2.onHoverStatusChange;
    }
    if (s2.primaryLayout !== undefined) {
      this.primaryLayout = s2.primaryLayout;
    }
    if (s2.secondaryLayout !== undefined) {
      this.secondaryLayout = s2.secondaryLayout;
    }
    if (s2.extraLayout !== undefined) {
      this.extraLayout = s2.extraLayout;
    }
    if (s2.windowStatusType !== undefined) {
      this.windowStatusType = s2.windowStatusType;
    }
    if (s2.foldStatus !== undefined) {
      this.foldStatus = s2.foldStatus;
    }
    if (s2.windowInstance !== undefined) {
      this.windowInstance = s2.windowInstance;
    }
    if (s2.containerSize !== undefined) {
      this.containerSize = s2.containerSize;
    }
    if (s2.containerGlobalPosition !== undefined) {
      this.containerGlobalPosition = s2.containerGlobalPosition;
    }
    if (s2.listener !== undefined) {
      this.listener = s2.listener;
    }
    if (s2.isSmallScreen !== undefined) {
      this.isSmallScreen = s2.isSmallScreen;
    }
  }
  updateStateVars(r2) {
    this.__expandedLayoutOptions.reset(r2.expandedLayoutOptions);
    this.__semiFoldedLayoutOptions.reset(r2.semiFoldedLayoutOptions);
    this.__foldedLayoutOptions.reset(r2.foldedLayoutOptions);
    this.__animationOptions.reset(r2.animationOptions);
  }
  purgeVariableDependenciesOnElmtId(q2) {
    this.__expandedLayoutOptions.purgeDependencyOnElmtId(q2);
    this.__semiFoldedLayoutOptions.purgeDependencyOnElmtId(q2);
    this.__foldedLayoutOptions.purgeDependencyOnElmtId(q2);
    this.__animationOptions.purgeDependencyOnElmtId(q2);
    this.__primaryLayout.purgeDependencyOnElmtId(q2);
    this.__secondaryLayout.purgeDependencyOnElmtId(q2);
    this.__extraLayout.purgeDependencyOnElmtId(q2);
  }
  aboutToBeDeleted() {
    this.__expandedLayoutOptions.aboutToBeDeleted();
    this.__semiFoldedLayoutOptions.aboutToBeDeleted();
    this.__foldedLayoutOptions.aboutToBeDeleted();
    this.__animationOptions.aboutToBeDeleted();
    this.__primaryLayout.aboutToBeDeleted();
    this.__secondaryLayout.aboutToBeDeleted();
    this.__extraLayout.aboutToBeDeleted();
    SubscriberManager.Get().delete(this.id__());
    this.aboutToBeDeletedInternal();
  }
  get expandedLayoutOptions() {
    return this.__expandedLayoutOptions.get();
  }
  set expandedLayoutOptions(p2) {
    this.__expandedLayoutOptions.set(p2);
  }
  get semiFoldedLayoutOptions() {
    return this.__semiFoldedLayoutOptions.get();
  }
  set semiFoldedLayoutOptions(o4) {
    this.__semiFoldedLayoutOptions.set(o4);
  }
  get foldedLayoutOptions() {
    return this.__foldedLayoutOptions.get();
  }
  set foldedLayoutOptions(n2) {
    this.__foldedLayoutOptions.set(n2);
  }
  get animationOptions() {
    return this.__animationOptions.get();
  }
  set animationOptions(n4) {
    this.__animationOptions.set(n4);
  }
  get primaryLayout() {
    return this.__primaryLayout.get();
  }
  set primaryLayout(m2) {
    this.__primaryLayout.set(m2);
  }
  get secondaryLayout() {
    return this.__secondaryLayout.get();
  }
  set secondaryLayout(l2) {
    this.__secondaryLayout.set(l2);
  }
  get extraLayout() {
    return this.__extraLayout.get();
  }
  set extraLayout(k2) {
    this.__extraLayout.set(k2);
  }
  aboutToAppear() {
    this.listener = mediaQuery.matchMediaSync("(width<=600vp)");
    this.isSmallScreen = this.listener.matches;
    this.listener.on("change", (m4) => {
      this.isSmallScreen = m4.matches;
    });
    this.foldStatus = display.getFoldStatus();
    display.on("foldStatusChange", (j4) => {
      if (this.foldStatus !== j4) {
        const k4 = this.isHoverMode();
        this.foldStatus = j4;
        this.updateLayout();
        const l4 = this.isHoverMode();
        if (k4 !== l4) {
          this.dispatchHoverStatusChange(l4);
        }
        this.updatePreferredOrientation();
      }
    });
    window.getLastWindow(this.getUIContext().getHostContext(), (e4, f4) => {
      if (e4 && e4.code) {
        Logger.error(
          "Failed to get window instance, error code: %{public}d",
          e4.code
        );
        return;
      }
      const g4 = f4.getWindowProperties().id;
      if (g4 < 0) {
        Logger.error(
          "Failed to get window instance because the window id is invalid. window id: %{public}d",
          g4
        );
        return;
      }
      this.windowInstance = f4;
      this.updatePreferredOrientation();
      this.windowInstance.on("windowStatusChange", (i4) => {
        this.windowStatusType = i4;
      });
    });
  }
  aboutToDisappear() {
    if (this.listener) {
      this.listener.off("change");
      this.listener = undefined;
    }
    display.off("foldStatusChange");
    if (this.windowInstance) {
      this.windowInstance.off("windowStatusChange");
    }
  }
  initialRender() {
    this.observeComponentCreation2((y1, z1) => {
      Stack.create();
      Stack.id("$$FoldSplitContainer$Stack$$");
      Stack.width("100%");
      Stack.height("100%");
      Stack.onSizeChange((b2, d4) => {
        this.updateContainerSize(d4);
        this.updateContainerPosition();
        this.updateLayout();
      });
    }, Stack);
    this.observeComponentCreation2((w1, x1) => {
      Column.create();
      Column.size(this.primaryLayout.size);
      Column.position({
        start: LengthMetrics.vp(this.primaryLayout.position.x),
        top: LengthMetrics.vp(this.primaryLayout.position.y),
      });
      Column.clip(true);
    }, Column);
    this.primary.bind(this)(this);
    Column.pop();
    this.observeComponentCreation2((u1, v1) => {
      Column.create();
      Column.size(this.secondaryLayout.size);
      Column.position({
        start: LengthMetrics.vp(this.secondaryLayout.position.x),
        top: LengthMetrics.vp(this.secondaryLayout.position.y),
      });
      Column.clip(true);
    }, Column);
    this.secondary.bind(this)(this);
    Column.pop();
    this.observeComponentCreation2((n1, o1) => {
      If.create();
      if (this.extra) {
        this.ifElseBranchUpdateFunction(0, () => {
          this.observeComponentCreation2((s1, t1) => {
            If.create();
            if (
              this.extraLayout.size.width > 0 &&
              this.extraLayout.size.height > 0
            ) {
              this.ifElseBranchUpdateFunction(0, () => {
                this.observeComponentCreation2((m3, n3) => {
                  Column.create();
                  Column.size(this.extraLayout.size);
                  Column.position({
                    start: LengthMetrics.vp(this.extraLayout.position.x),
                    top: LengthMetrics.vp(this.extraLayout.position.y),
                  });
                  Column.transition(
                    TransitionEffect.OPACITY.animation({
                      curve: Curve.Linear,
                      duration: 250,
                    })
                  );
                  Column.clip(true);
                }, Column);
                this.extra.bind(this)(this);
                Column.pop();
              });
            } else {
              this.ifElseBranchUpdateFunction(1, () => {});
            }
          }, If);
          If.pop();
        });
      } else {
        this.ifElseBranchUpdateFunction(1, () => {});
      }
    }, If);
    If.pop();
    Stack.pop();
  }
  dispatchHoverStatusChange(b4) {
    const c4 = {
      foldStatus: this.foldStatus,
      isHoverMode: b4,
      appRotation: display.getDefaultDisplaySync().rotation,
      windowStatusType: this.windowStatusType,
    };
    this.onHoverStatusChange?.(c4);
  }
  hasExtraRegion() {
    return !!this.extra;
  }
  async updatePreferredOrientation() {
    if (this.windowInstance) {
      try {
        if (this.foldStatus === display.FoldStatus.FOLD_STATUS_FOLDED) {
          await this.windowInstance.setPreferredOrientation(
            window.Orientation.AUTO_ROTATION_PORTRAIT
          );
        } else {
          await this.windowInstance.setPreferredOrientation(
            window.Orientation.AUTO_ROTATION
          );
        }
      } catch (i1) {
        Logger.error("Failed to update preferred orientation.");
      }
    }
  }
  updateContainerSize(a4) {
    this.containerSize.width = a4.width;
    this.containerSize.height = a4.height;
  }
  updateContainerPosition() {
    const y3 = this.getUIContext();
    const z3 = y3.getFrameNodeById("$$FoldSplitContainer$Stack$$");
    if (z3) {
      this.containerGlobalPosition = z3.getPositionToWindow();
    }
  }
  updateLayout() {
    let g1;
    if (this.isSmallScreen) {
      g1 = this.getFoldedRegionLayouts();
    } else {
      if (this.foldStatus === display.FoldStatus.FOLD_STATUS_EXPANDED) {
        g1 = this.getExpandedRegionLayouts();
      } else if (
        this.foldStatus === display.FoldStatus.FOLD_STATUS_HALF_FOLDED
      ) {
        g1 = this.getSemiFoldedRegionLayouts();
      } else if (this.foldStatus === display.FoldStatus.FOLD_STATUS_FOLDED) {
        g1 = this.getFoldedRegionLayouts();
      } else {
        g1 = this.getExpandedRegionLayouts();
      }
    }
    if (this.animationOptions === null) {
      this.primaryLayout = g1.primary;
      this.secondaryLayout = g1.secondary;
      this.extraLayout = g1.extra;
    } else if (this.animationOptions === undefined) {
      Context.animateTo({ curve: curves.springMotion(0.35, 1, 0) }, () => {
        this.primaryLayout = g1.primary;
        this.secondaryLayout = g1.secondary;
        this.extraLayout = g1.extra;
      });
    } else {
      Context.animateTo(this.animationOptions, () => {
        this.primaryLayout = g1.primary;
        this.secondaryLayout = g1.secondary;
        this.extraLayout = g1.extra;
      });
    }
  }
  getExpandedRegionLayouts() {
    const x = this.containerSize.width;
    const y = this.containerSize.height;
    const z = initLayout();
    const a1 = initLayout();
    const b1 = initLayout();
    const c1 = getSplitRatio(
      this.expandedLayoutOptions.horizontalSplitRatio,
      PresetSplitRatio.LAYOUT_3V2
    );
    const d1 = getSplitRatio(
      this.expandedLayoutOptions.verticalSplitRatio,
      PresetSplitRatio.LAYOUT_1V1
    );
    if (this.hasExtraRegion()) {
      b1.size.width = x / (c1 + 1);
    } else {
      b1.size.width = 0;
    }
    a1.size.height = y / (d1 + 1);
    z.size.height = y - a1.size.height;
    z.position.x = 0;
    a1.position.x = 0;
    z.position.y = 0;
    a1.position.y = z.size.height;
    const e1 = withDefaultValue(
      this.expandedLayoutOptions.isExtraRegionPerpendicular,
      true
    );
    if (e1) {
      z.size.width = x - b1.size.width;
      a1.size.width = x - b1.size.width;
      b1.size.height = y;
      b1.position.x = z.size.width;
      b1.position.y = 0;
    } else {
      const j1 = withDefaultValue(
        this.expandedLayoutOptions.extraRegionPosition,
        ExtraRegionPosition.TOP
      );
      if (j1 === ExtraRegionPosition.TOP) {
        z.size.width = x - b1.size.width;
        a1.size.width = x;
        b1.size.height = z.size.height;
        b1.position.x = z.size.width;
        b1.position.y = 0;
      } else {
        z.size.width = x;
        a1.size.width = x - b1.size.width;
        b1.size.height = a1.size.height;
        b1.position.x = a1.size.width;
        b1.position.y = z.size.height;
      }
    }
    return { primary: z, secondary: a1, extra: b1 };
  }
  getSemiFoldedRegionLayouts() {
    const j2 = this.containerSize.width;
    const o3 = this.containerSize.height;
    const p3 = initLayout();
    const q3 = initLayout();
    const r3 = initLayout();
    if (this.isPortraitOrientation()) {
      return this.getExpandedRegionLayouts();
    }
    const s3 = this.getCreaseRegionRect();
    p3.position.x = 0;
    p3.position.y = 0;
    q3.position.x = 0;
    q3.position.y = s3.top + s3.height;
    q3.size.height = o3 - q3.position.y;
    p3.size.height = s3.top;
    const t3 = withDefaultValue(
      this.semiFoldedLayoutOptions.showExtraRegion,
      false
    );
    if (!t3) {
      p3.size.width = j2;
      q3.size.width = j2;
      r3.position.x = j2;
      if (
        !this.expandedLayoutOptions.isExtraRegionPerpendicular &&
        this.expandedLayoutOptions.extraRegionPosition ===
          ExtraRegionPosition.BOTTOM
      ) {
        r3.position.y = p3.size.height;
      } else {
        r3.position.y = 0;
      }
    } else {
      const u3 = getSplitRatio(
        this.semiFoldedLayoutOptions.horizontalSplitRatio,
        PresetSplitRatio.LAYOUT_3V2
      );
      const v3 = withDefaultValue(
        this.semiFoldedLayoutOptions.extraRegionPosition,
        ExtraRegionPosition.TOP
      );
      if (this.hasExtraRegion()) {
        r3.size.width = j2 / (u3 + 1);
      } else {
        r3.size.width = 0;
      }
      if (v3 === ExtraRegionPosition.TOP) {
        r3.size.height = p3.size.height;
        p3.size.width = j2 - r3.size.width;
        q3.size.width = j2;
        r3.position.x = p3.position.x + p3.size.width;
        r3.position.y = 0;
      } else {
        p3.size.width = j2;
        q3.size.width = j2 - r3.size.width;
        r3.size.height = q3.size.height;
        r3.position.x = q3.size.width;
        r3.position.y = q3.position.y;
      }
    }
    return { primary: p3, secondary: q3, extra: r3 };
  }
  getFoldedRegionLayouts() {
    const i = this.containerSize.width;
    const j = this.containerSize.height;
    const k = initLayout();
    const l = initLayout();
    const m = initLayout();
    const n = getSplitRatio(
      this.foldedLayoutOptions.verticalSplitRatio,
      PresetSplitRatio.LAYOUT_1V1
    );
    l.size.height = j / (n + 1);
    k.size.height = j - l.size.height;
    m.size.height = 0;
    k.size.width = i;
    l.size.width = i;
    m.size.width = 0;
    k.position.x = 0;
    l.position.x = 0;
    m.position.x = i;
    k.position.y = 0;
    l.position.y = k.size.height;
    m.position.y = 0;
    return { primary: k, secondary: l, extra: m };
  }
  getCreaseRegionRect() {
    const b = display.getCurrentFoldCreaseRegion();
    const c = b.creaseRects;
    let d = 0;
    let e = 0;
    let f = 0;
    let g = 0;
    if (c && c.length) {
      const h = c[0];
      d = px2vp(h.left) - this.containerGlobalPosition.x;
      e = px2vp(h.top) - this.containerGlobalPosition.y;
      f = px2vp(h.width);
      g = px2vp(h.height);
    }
    return { left: d, top: e, width: f, height: g };
  }
  isHoverMode() {
    return (
      this.foldStatus === display.FoldStatus.FOLD_STATUS_HALF_FOLDED &&
      !this.isPortraitOrientation()
    );
  }
  isPortraitOrientation() {
    const a = display.getDefaultDisplaySync();
    switch (a.orientation) {
      case display.Orientation.PORTRAIT:
      case display.Orientation.PORTRAIT_INVERTED:
        return true;
      case display.Orientation.LANDSCAPE:
      case display.Orientation.LANDSCAPE_INVERTED:
      default:
        return false;
    }
  }
  rerender() {
    this.updateDirtyElements();
  }
}

export default { ExtraRegionPosition, PresetSplitRatio, FoldSplitContainer };
