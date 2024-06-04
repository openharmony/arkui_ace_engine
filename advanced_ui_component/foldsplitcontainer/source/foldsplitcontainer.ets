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

import display from '@ohos.display';
import window from '@ohos.window';
import hilog from '@ohos.hilog';
import { LengthMetrics, Position, Size } from '@ohos.arkui.node';
import curves from '@ohos.curves';
import { Callback } from '@ohos.base';

interface Layout {
  size: Size;
  position: Position;
}

interface RegionLayout {
  primary: Layout;
  secondary: Layout;
  extra: Layout;
}

/**
 * Position enum of the extra region
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export enum ExtraRegionPosition {
  /**
   * The extra region position is in the top.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  TOP = 1,

  /**
   * The extra region position is in the bottom.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  BOTTOM = 2,
}

/**
 * The layout options for the container when the foldable screen is expanded.
 *
 * @interface ExpandedRegionLayoutOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface ExpandedRegionLayoutOptions {
  /**
   * The ratio of the widths of two areas in the horizontal direction.
   *
   * @type { ?number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  horizontalSplitRatio?: number;

  /**
   * The ratio of the heights of two areas in the vertical direction.
   *
   * @type { ?number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  verticalSplitRatio?: number;

  /**
   * Does the extended area span from top to bottom within the container?
   *
   * @type { ?boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  isExtraRegionPerpendicular?: boolean;

  /**
   * Specify the position of the extra area when the extra area does not vertically span the container.
   *
   * @type { ?ExtraRegionPosition }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  extraRegionPosition?: ExtraRegionPosition;
}

/**
 * The layout options for the container when the foldable screen is folding.
 *
 * @interface FoldingRegionLayoutOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface FoldingRegionLayoutOptions {
  /**
   * The ratio of the widths of two areas in the horizontal direction.
   *
   * @type { ?number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  horizontalSplitRatio?: number;

  /**
   * Does the foldable screen display an extra area when it's in the half-folded state?
   *
   * @type { ?boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  showExtraRegion?: boolean;

  /**
   * Specify the position of the extra area when the foldable screen is in the half-folded state.
   *
   * @type { ?ExtraRegionPosition }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  extraRegionPosition?: ExtraRegionPosition;
}

/**
 * The layout options for the container when the foldable screen is folded.
 *
 * @interface FoldedRegionLayoutOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export interface FoldedRegionLayoutOptions {
  /**
   * The ratio of the heights of two areas in the vertical direction.
   *
   * @type { ?number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  verticalSplitRatio?: number;
}

/**
 * Preset split ratio.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
export enum PresetSplitRatio {
  /**
   * 1:1
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  LAYOUT_1V1 = 1 / 1,

  /**
   * 2:3
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  LAYOUT_2V3 = 2 / 3,

  /**
   * 3:2
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  LAYOUT_3V2 = 3 / 2,
}

function withDefaultValue<T>(value: T | undefined | null, defaultValue: T): T {
  if (value === void 0 || value === null) {
    return defaultValue;
  }
  return value;
}

function getSplitRatio(ratio: number | undefined | null, defaultRatio: number): number {
  if (ratio === void 0 || ratio === null) {
    return defaultRatio;
  }
  if (ratio <= 0) {
    return defaultRatio;
  }
  return ratio;
}

class Logger {
  static debug(format: string, ...args: ESObject[]): void {
    return hilog.debug(0x3900, 'FoldSplitContainer', format, ...args);
  }

  static info(format: string, ...args: ESObject[]): void {
    return hilog.info(0x3900, 'FoldSplitContainer', format, ...args);
  }

  static error(format: string, ...args: ESObject[]): void {
    return hilog.error(0x3900, 'FoldSplitContainer', format, ...args);
  }
}

function initLayout(): Layout {
  return {
    size: { width: 0, height: 0 },
    position: { x: 0, y: 0 },
  };
}

/**
 * Defines FoldSplitContainer container.
 *
 * @interface FoldSplitContainer
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 12
 */
@Component
export struct FoldSplitContainer {
  /**
   * The builder function which will be rendered in the major region of container.
   *
   * @type { Callback<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  @BuilderParam
  primary: Callback<void>;
  /**
   * The builder function which will be rendered in the minor region of container.
   *
   * @type { Callback<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  @BuilderParam
  secondary: Callback<void>;
  /**
   * The builder function which will be rendered in the extra region of container.
   *
   * @type { ?Callback<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  @BuilderParam
  extra?: Callback<void>;
  /**
   * The layout options for the container when the foldable screen is expanded.
   *
   * @type { ExpandedRegionLayoutOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  @Prop
  @Watch('updateLayout')
  expandedLayoutOptions: ExpandedRegionLayoutOptions = {
    horizontalSplitRatio: PresetSplitRatio.LAYOUT_3V2,
    verticalSplitRatio: PresetSplitRatio.LAYOUT_1V1,
    isExtraRegionPerpendicular: true,
    extraRegionPosition: ExtraRegionPosition.TOP
  };
  /**
   * The layout options for the container when the foldable screen is folding.
   *
   * @type { FoldingRegionLayoutOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  @Prop
  @Watch('updateLayout')
  foldingLayoutOptions: FoldingRegionLayoutOptions = {
    horizontalSplitRatio: PresetSplitRatio.LAYOUT_3V2,
    showExtraRegion: true,
    extraRegionPosition: ExtraRegionPosition.TOP
  };
  /**
   * The layout options for the container when the foldable screen is folded.
   *
   * @type { FoldingRegionLayoutOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @crossplatform
   * @atomicservice
   * @since 12
   */
  @Prop
  @Watch('updateLayout')
  foldedLayoutOptions: FoldedRegionLayoutOptions = {
    verticalSplitRatio: PresetSplitRatio.LAYOUT_1V1
  };
  @State primaryLayout: Layout = initLayout();
  @State secondaryLayout: Layout = initLayout();
  @State extraLayout: Layout = initLayout();
  private foldStatus: display.FoldStatus = display.FoldStatus.FOLD_STATUS_UNKNOWN;
  private windowInstance?: window.Window;
  private containerSize: Size = { width: 0, height: 0 };
  private containerGlobalPosition: Position = { x: 0, y: 0 };

  aboutToAppear() {
    this.foldStatus = display.getFoldStatus();
    display.on('foldStatusChange', (foldStatus) => {
      this.foldStatus = foldStatus;
      this.updateLayout();
      this.updatePreferredOrientation();
    });

    window.getLastWindow(this.getUIContext().getHostContext(), (error, windowInstance) => {
      if (error && error.code) {
        Logger.error('Failed to get window instance, error code: %{public}d', error.code);
        return;
      }

      const windowId = windowInstance.getWindowProperties().id;
      if (windowId < 0) {
        Logger.error('Failed to get window instance because the window id is invalid. window id: %{public}d', windowId);
        return;
      }

      this.windowInstance = windowInstance;
      this.updatePreferredOrientation();
    });
  }

  aboutToDisappear() {
    display.off('foldStatusChange');
  }

  build() {
    Stack() {
      Column() {
        this.primary();
      }
      .size(this.primaryLayout.size)
      .position({
        start: LengthMetrics.vp(this.primaryLayout.position.x),
        top: LengthMetrics.vp(this.primaryLayout.position.y),
      })
      .clip(true)

      Column() {
        this.secondary();
      }
      .size(this.secondaryLayout.size)
      .position({
        start: LengthMetrics.vp(this.secondaryLayout.position.x),
        top: LengthMetrics.vp(this.secondaryLayout.position.y),
      })
      .clip(true)

      if (this.hasExtraRegion()) {
        if (this.extraLayout.size.width > 0 && this.extraLayout.size.height > 0) {
          Column() {
            this.extra();
          }
          .size(this.extraLayout.size)
          .position({
            start: LengthMetrics.vp(this.extraLayout.position.x),
            top: LengthMetrics.vp(this.extraLayout.position.y),
          })
          .transition(
            TransitionEffect.OPACITY.animation({ curve: Curve.Linear, duration: 250 })
          )
          .clip(true)
        }
      }
    }
    .width('100%')
    .height('100%')
    .onAreaChange((_, area) => {
      this.updateContainerArea(area);
      this.updateLayout();
    })
  }

  hasExtraRegion(): boolean {
    return !!this.extra;
  }

  async updatePreferredOrientation() {
    if (this.windowInstance) {
      try {
        if (this.foldStatus === display.FoldStatus.FOLD_STATUS_FOLDED) {
          await this.windowInstance.setPreferredOrientation(window.Orientation.AUTO_ROTATION_PORTRAIT);
        } else {
          await this.windowInstance.setPreferredOrientation(window.Orientation.AUTO_ROTATION);
        }
      } catch (err) {
        Logger.error('Failed to update preferred orientation.');
      }
    }
  }

  private updateContainerArea(area: Area) {
    this.containerSize.width = area.width as number;
    this.containerSize.height = area.height as number;
    this.containerGlobalPosition.x = area.globalPosition.x as number;
    this.containerGlobalPosition.y = area.globalPosition.y as number;
  }

  private updateLayout() {
    let regionLayout: RegionLayout;
    if (this.foldStatus === display.FoldStatus.FOLD_STATUS_EXPANDED) {
      regionLayout = this.getExpandedRegionLayouts();
    } else if (this.foldStatus === display.FoldStatus.FOLD_STATUS_HALF_FOLDED) {
      regionLayout = this.getFoldingRegionLayouts();
    } else {
      regionLayout = this.getFoldedRegionLayouts();
    }
    animateTo({ curve: curves.springMotion(0.35, 1, 0) }, () => {
      this.primaryLayout = regionLayout.primary;
      this.secondaryLayout = regionLayout.secondary;
      this.extraLayout = regionLayout.extra;
    });
  }

  private getExpandedRegionLayouts(): RegionLayout {
    const width = this.containerSize.width;
    const height = this.containerSize.height;
    const primaryLayout: Layout = initLayout();
    const secondaryLayout: Layout = initLayout();
    const extraLayout: Layout = initLayout();

    const horizontalSplitRatio =
      getSplitRatio(this.expandedLayoutOptions.horizontalSplitRatio, PresetSplitRatio.LAYOUT_3V2);
    const verticalSplitRatio =
      getSplitRatio(this.expandedLayoutOptions.verticalSplitRatio, PresetSplitRatio.LAYOUT_1V1);

    if (this.hasExtraRegion()) {
      extraLayout.size.width = width / (horizontalSplitRatio + 1);
    } else {
      extraLayout.size.width = 0;
    }
    secondaryLayout.size.height = height / (verticalSplitRatio + 1);
    primaryLayout.size.height = height - secondaryLayout.size.height;
    primaryLayout.position.x = 0;
    secondaryLayout.position.x = 0;
    primaryLayout.position.y = 0;
    secondaryLayout.position.y = primaryLayout.size.height;

    const isExtraRegionPerpendicular = withDefaultValue(this.expandedLayoutOptions.isExtraRegionPerpendicular, true);
    if (isExtraRegionPerpendicular) {
      primaryLayout.size.width = width - extraLayout.size.width;
      secondaryLayout.size.width = width - extraLayout.size.width;
      extraLayout.size.height = height;
      extraLayout.position.x = primaryLayout.size.width;
      extraLayout.position.y = 0;
    } else {
      const extraRegionPosition =
        withDefaultValue(this.expandedLayoutOptions.extraRegionPosition, ExtraRegionPosition.TOP);
      if (extraRegionPosition === ExtraRegionPosition.TOP) {
        primaryLayout.size.width = width - extraLayout.size.width;
        secondaryLayout.size.width = width;
        extraLayout.size.height = primaryLayout.size.height;
        extraLayout.position.x = primaryLayout.size.width;
        extraLayout.position.y = 0;
      } else {
        primaryLayout.size.width = width;
        secondaryLayout.size.width = width - extraLayout.size.width;
        extraLayout.size.height = secondaryLayout.size.height;
        extraLayout.position.x = secondaryLayout.size.width;
        extraLayout.position.y = primaryLayout.size.height;
      }
    }

    return { primary: primaryLayout, secondary: secondaryLayout, extra: extraLayout };
  }

  getFoldingRegionLayouts(): RegionLayout {
    const width = this.containerSize.width;
    const height = this.containerSize.height;
    const primaryLayout: Layout = initLayout();
    const secondaryLayout: Layout = initLayout();
    const extraLayout: Layout = initLayout();

    if (this.isPortraitOrientation()) {
      return this.getExpandedRegionLayouts();
    }

    const creaseRegionRect = this.getCreaseRegionRect();
    primaryLayout.position.x = 0;
    primaryLayout.position.y = 0;
    secondaryLayout.position.x = 0;
    secondaryLayout.position.y = creaseRegionRect.top + creaseRegionRect.height;
    secondaryLayout.size.height = height - secondaryLayout.position.y;
    primaryLayout.size.height = creaseRegionRect.top;

    const showExtraRegion = withDefaultValue(this.foldingLayoutOptions.showExtraRegion, false);

    if (!showExtraRegion) {
      primaryLayout.size.width = width;
      secondaryLayout.size.width = width;
      extraLayout.position.x = width;
      if (!this.expandedLayoutOptions.isExtraRegionPerpendicular &&
        this.expandedLayoutOptions.extraRegionPosition === ExtraRegionPosition.BOTTOM) {
        extraLayout.position.y = primaryLayout.size.height;
      } else {
        extraLayout.position.y = 0;
      }
    } else {
      const horizontalSplitRatio =
        getSplitRatio(this.foldingLayoutOptions.horizontalSplitRatio, PresetSplitRatio.LAYOUT_3V2);
      const extraRegionPosition =
        withDefaultValue(this.foldingLayoutOptions.extraRegionPosition, ExtraRegionPosition.TOP);
      if (this.hasExtraRegion()) {
        extraLayout.size.width = width / (horizontalSplitRatio + 1);
      } else {
        extraLayout.size.width = 0;
      }
      if (extraRegionPosition === ExtraRegionPosition.TOP) {
        extraLayout.size.height = primaryLayout.size.height;
        primaryLayout.size.width = width - extraLayout.size.width;
        secondaryLayout.size.width = width;
        extraLayout.position.x = primaryLayout.position.x + primaryLayout.size.width;
        extraLayout.position.y = 0;
      } else {
        primaryLayout.size.width = width;
        secondaryLayout.size.width = width - extraLayout.size.width;
        extraLayout.size.height = secondaryLayout.size.height;
        extraLayout.position.x = secondaryLayout.size.width;
        extraLayout.position.y = secondaryLayout.position.y;
      }
    }

    return { primary: primaryLayout, secondary: secondaryLayout, extra: extraLayout };
  }

  getFoldedRegionLayouts(): RegionLayout {
    const width = this.containerSize.width;
    const height = this.containerSize.height;
    const primaryLayout: Layout = initLayout();
    const secondaryLayout: Layout = initLayout();
    const extraLayout: Layout = initLayout();

    const verticalSplitRatio =
      getSplitRatio(this.foldedLayoutOptions.verticalSplitRatio, PresetSplitRatio.LAYOUT_1V1);

    secondaryLayout.size.height = height / (verticalSplitRatio + 1);
    primaryLayout.size.height = height - secondaryLayout.size.height;
    extraLayout.size.height = 0;
    primaryLayout.size.width = width;
    secondaryLayout.size.width = width;
    extraLayout.size.width = 0;
    primaryLayout.position.x = 0;
    secondaryLayout.position.x = 0;
    extraLayout.position.x = width;
    primaryLayout.position.y = 0;
    secondaryLayout.position.y = primaryLayout.size.height;
    extraLayout.position.y = 0;

    return { primary: primaryLayout, secondary: secondaryLayout, extra: extraLayout };
  }

  getCreaseRegionRect(): display.Rect {
    const creaseRegion = display.getCurrentFoldCreaseRegion();
    const rects = creaseRegion.creaseRects;
    let left: number = 0;
    let top: number = 0;
    let width: number = 0;
    let height: number = 0;
    if (rects && rects.length) {
      const rect = rects[0];
      left = px2vp(rect.left) - this.containerGlobalPosition.x;
      top = px2vp(rect.top) - this.containerGlobalPosition.y;
      width = px2vp(rect.width);
      height = px2vp(rect.height);
    }

    return { left, top, width, height };
  }

  isPortraitOrientation() {
    const defaultDisplay = display.getDefaultDisplaySync();
    switch (defaultDisplay.orientation) {
      case display.Orientation.PORTRAIT:
      case display.Orientation.PORTRAIT_INVERTED:
        return true;
      case display.Orientation.LANDSCAPE:
      case display.Orientation.LANDSCAPE_INVERTED:
      default:
        return false;
    }
  }
}
