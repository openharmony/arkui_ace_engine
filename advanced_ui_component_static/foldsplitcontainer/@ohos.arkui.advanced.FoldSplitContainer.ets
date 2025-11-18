/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { Column, Component, AnimateParam, BuilderParam, Stack, SizeOptions, Curve,
  Callback, LocalizedEdges, Builder, Entry, Text } from '@ohos.arkui.component';
import { State, Prop, Watch, PropRef } from '@ohos.arkui.stateManagement';
import { BusinessError } from '@ohos.base';
import { UIContext, Context } from '@ohos.arkui.UIContext';
import display from '@ohos.display';
import window from '@ohos.window';
import hilog from '@ohos.hilog';
import { LengthMetrics, NodePosition, Size } from '@ohos.arkui.node';
import curves from '@ohos.curves';
import mediaQuery from '@ohos.mediaquery';

@Builder
type FoldVoidCallback = () => void;

@Builder
function noop() {
}

class Layout {
  public size: Size = { width: 0, height: 0 };
  public position: NodePosition = { x: 0, y: 0 };
}

class RegionLayout {
  public primary: Layout = {
    size: { width: 0, height: 0 },
    position: { x: 0, y: 0 }
  };
  public secondary: Layout = {
    size: { width: 0, height: 0 },
    position: { x: 0, y: 0 }
  };
  public extra: Layout = {
    size: { width: 0, height: 0 },
    position: { x: 0, y: 0 }
  };
}

/**
 * Position enum of the extra region
 *
 * @enum { ExtraRegionPosition }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export enum ExtraRegionPosition {
  /**
   * The extra region position is in the top.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  TOP = 1,
  /**
   * The extra region position is in the bottom.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  BOTTOM = 2
}

/**
 * The layout options for the container when the foldable screen is expanded.
 *
 * @interface ExpandedRegionLayoutOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export interface ExpandedRegionLayoutOptions {
  /**
   * The ratio of the widths of two areas in the horizontal direction.
   *
   * @type { ?PresetSplitRatio }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  horizontalSplitRatio?: PresetSplitRatio;
  /**
   * The ratio of the heights of two areas in the vertical direction.
   *
   * @type { ?PresetSplitRatio }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  verticalSplitRatio?: PresetSplitRatio;
  /**
   * Does the extended area span from top to bottom within the container?
   *
   * @type { ?boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  isExtraRegionPerpendicular?: boolean;
  /**
   * Specify the position of the extra area when the extra area does not vertically span the container.
   *
   * @type { ?ExtraRegionPosition }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  extraRegionPosition?: ExtraRegionPosition;
}

/**
 * The layout options for the container when the foldable screen is in hover mode.
 *
 * @typedef HoverModeRegionLayoutOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export interface HoverModeRegionLayoutOptions {
  /**
   * The ratio of the widths of two areas in the horizontal direction.
   *
   * @type { ?PresetSplitRatio }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  horizontalSplitRatio?: PresetSplitRatio;
  /**
   * Does the foldable screen display an extra area when it's in the half-folded state?
   *
   * @type { ?boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  showExtraRegion?: boolean;
  /**
   * Specify the position of the extra area when the foldable screen is in the half-folded state.
   *
   * @type { ?ExtraRegionPosition }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  extraRegionPosition?: ExtraRegionPosition;
}

/**
 * The layout options for the container when the foldable screen is folded.
 *
 * @interface FoldedRegionLayoutOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export interface FoldedRegionLayoutOptions {
  /**
   * The ratio of the heights of two areas in the vertical direction.
   *
   * @type { ?PresetSplitRatio }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  verticalSplitRatio?: PresetSplitRatio;
}

/**
 * Preset split ratio.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export enum PresetSplitRatio {
  /**
   * 1:1
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  LAYOUT_1V1 = 1.0,
  /**
   * 2:3
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  LAYOUT_2V3 = 0.6666666666666666,
  /**
   * 3:2
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  LAYOUT_3V2 = 1.5,
}

/**
 * The status of hover mode.
 *
 * @interface HoverStatus
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export interface HoverModeStatus {
  /**
   * The fold status of devices.
   *
   * @type { display.FoldStatus }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  foldStatus: display.FoldStatus;
  /**
   * Is the app currently in hover mode?
   * In hover mode, the upper half of the screen is used for display, and the lower half is used for operation.
   *
   * @type { boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  isHoverMode: boolean;
  /**
   * The angle of rotation applied.
   *
   * @type { double }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  appRotation: double;
  /**
   * The status of window.
   *
   * @type { window.WindowStatusType }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  windowStatusType: window.WindowStatusType;
}

/**
 * The handler of onHoverStatusChange event
 *
 * @typedef { function } OnHoverStatusChangeHandler
 * @param { HoverModeStatus } status - The status of hover mode
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 22 static
 * @noninterop
 */
export type OnHoverStatusChangeHandler = (status: HoverModeStatus) => void;

function withDefaultValue<T>(value: T | undefined | null, defaultValue: T): T {
  if (value === undefined || value === null) {
    return defaultValue;
  }
  return value as T;
}

function getPresetSplitRatio(ratio: PresetSplitRatio): number {
  if (ratio === PresetSplitRatio.LAYOUT_1V1) {
    return 1.0;
  }
  if (ratio === PresetSplitRatio.LAYOUT_2V3) {
    return 0.6666666666666666;
  }
  if (ratio === PresetSplitRatio.LAYOUT_3V2) {
    return 1.5;
  }
  return -1.0;
}

function getSplitRatio(ratio: PresetSplitRatio | undefined | null, defaultRatio: PresetSplitRatio): PresetSplitRatio {
  if (ratio === undefined || ratio === null) {
    return defaultRatio;
  }
  if (getPresetSplitRatio(ratio as PresetSplitRatio) <= 0) {
    return defaultRatio;
  }
  return ratio as PresetSplitRatio;
}

class Logger {
  static debug(format: string, ...args: (Object | undefined | null)[]): void {
    return hilog.debug(0x3900, 'FoldSplitContainer', format, ...args);
  }

  static info(format: string, ...args: (Object | undefined | null)[]): void {
    return hilog.info(0x3900, 'FoldSplitContainer', format, ...args);
  }

  static error(format: string, ...args: (Object | undefined | null)[]): void {
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
 * @since 22 static
 * @noninterop
 */
@Component
export struct FoldSplitContainer {
  /**
   * The builder function which will be rendered in the major region of container.
   *
   * @type { Callback<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @BuilderParam
  primary: FoldVoidCallback = noop;
  /**
   * The builder function which will be rendered in the minor region of container.
   *
   * @type { Callback<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @BuilderParam
  secondary: FoldVoidCallback = noop;
  /**
   * The builder function which will be rendered in the extra region of container.
   *
   * @type { ?Callback<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @BuilderParam
  extra?: FoldVoidCallback;
  /**
   * The layout options for the container when the foldable screen is expanded.
   *
   * @type { ExpandedRegionLayoutOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @PropRef
  @Watch('updateLayout')
  expandedLayoutOptions: ExpandedRegionLayoutOptions = {
    horizontalSplitRatio: PresetSplitRatio.LAYOUT_3V2,
    verticalSplitRatio: PresetSplitRatio.LAYOUT_1V1,
    isExtraRegionPerpendicular: true,
    extraRegionPosition: ExtraRegionPosition.TOP
  } as ExpandedRegionLayoutOptions;
  /**
   * The layout options for the container when the foldable screen is in hover mode.
   *
   * @type { HoverModeRegionLayoutOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @PropRef
  @Watch('updateLayout')
  hoverModeLayoutOptions: HoverModeRegionLayoutOptions = {
    horizontalSplitRatio: PresetSplitRatio.LAYOUT_3V2,
    showExtraRegion: false,
    extraRegionPosition: ExtraRegionPosition.TOP
  } as HoverModeRegionLayoutOptions;
  /**
   * The layout options for the container when the foldable screen is folded.
   *
   * @type { FoldedRegionLayoutOptions }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @PropRef
  @Watch('updateLayout')
  foldedLayoutOptions: FoldedRegionLayoutOptions = {
    verticalSplitRatio: PresetSplitRatio.LAYOUT_1V1
  } as FoldedRegionLayoutOptions;
  /**
   * The animation options of layout
   *
   * @type { ?AnimateParam }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  @PropRef
  animationOptions?: AnimateParam | null = undefined;
  /**
   * The callback function that is triggered when the foldable screen enters or exits hover mode.
   * In hover mode, the upper half of the screen is used for display, and the lower half is used for operation.
   *
   * @type { ?OnHoverStatusChangeHandler }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 22 static
   */
  public onHoverStatusChange?: OnHoverStatusChangeHandler = () => {
  };
  @State primaryLayout: Layout = initLayout();
  @State secondaryLayout: Layout = initLayout();
  @State extraLayout: Layout = initLayout();
  @State extraOpacity: number = 1;
  private windowStatusType: window.WindowStatusType = window.WindowStatusType.UNDEFINED;
  private foldStatus: display.FoldStatus = display.FoldStatus.FOLD_STATUS_UNKNOWN;
  private windowInstance?: window.Window;
  private containerSize: Size = { width: 0, height: 0 } as Size;
  private containerGlobalPosition: NodePosition = { x: 0, y: 0 } as NodePosition;
  private listener?: mediaQuery.MediaQueryListener = this.getUIContext().getMediaQuery().matchMediaSync('(width<=600vp)');
  private isSmallScreen: boolean = false;
  private isHoverMode: boolean | undefined = undefined;

  aboutToAppear() {
    this.listener?.on('change', (result) => {
      this.isSmallScreen = result.matches;
    });

    try {
      this.foldStatus = display.getFoldStatus();
    } catch (err : BusinessError<void>) {
      Logger.error('Failed to get foldStatus. code:%{public}d, message:%{public}s', err.code, err.message);
    }
    try {
      display.on('foldStatusChange', (foldStatus) => {
        if (this.foldStatus !== foldStatus) {
          this.foldStatus = foldStatus;
          this.updateLayout('');
          this.updatePreferredOrientation();
        }
      });
    } catch (err : BusinessError<void>) {
      Logger.error('Failed display.on foldStatusChange. code:%{public}d, message:%{public}s', err.code, err.message);
    }

    try {
      if (!!this.getUIContext().getHostContext()) {
        window.getLastWindow(this.getUIContext().getHostContext()!,
          (error: BusinessError<void> | null, windowInstance: window.Window | undefined) => {
            if (error && error.code) {
              Logger.error('Failed to get window instance, error code: %{public}d', error.code);
              return;
            }

            const windowId = windowInstance?.getWindowProperties().id;
            if (windowId && windowId < 0) {
              Logger.error('Failed to get window instance because the window id is invalid. window id: %{public}d',
                windowId);
              return;
            }

            this.windowInstance = windowInstance;
            this.updatePreferredOrientation();
            this.dealWindowStatusChange();
          });
      }
    } catch (err : BusinessError<void>) {
      Logger.error('Failed getLastWindow. code:%{public}d, message:%{public}s', err.code, err.message);
    }
  }

  dealWindowStatusChange() {
    try {
      this.windowInstance?.on('windowStatusChange', (status) => {
        this.windowStatusType = status;
      });
    } catch (err : BusinessError<void>) {
      Logger.error('Failed windowInstance.on windowStatusChange. code:%{public}d, message:%{public}s',
        err.code, err.message);
    }
  }

  aboutToDisappear() {
    if (this.listener) {
      this.listener?.off('change');
      this.listener = undefined;
    }
    try {
      display.off('foldStatusChange');
    } catch (err : BusinessError<void>) {
      Logger.error('Failed display.off foldStatusChange. code:%{public}d, message:%{public}s', err.code, err.message);
    }
    if (this.windowInstance) {
      this.windowInstance?.off('windowStatusChange');
    }
  }

  build() {
    Stack() {
      Column() {
        if (this.primary) {
          this.primary();
        }
      }
      .height(this.primaryLayout.size.height)
      .width(this.primaryLayout.size.width)
      .position({
        start: LengthMetrics.vp(this.primaryLayout.position.x),
        top: LengthMetrics.vp(this.primaryLayout.position.y),
      }  as LocalizedEdges)
      .clip(true)

      Column() {
        if (this.secondary) {
          this.secondary();
        }
      }
      .height(this.secondaryLayout.size.height)
      .width(this.secondaryLayout.size.width)
      .position({
        start: LengthMetrics.vp(this.secondaryLayout.position.x),
        top: LengthMetrics.vp(this.secondaryLayout.position.y),
      } as LocalizedEdges)
      .clip(true)

      if (this.extra) {
        Column() {
          this.extra?.();
        }
        .opacity(this.extraOpacity)
        .animation({ curve: Curve.Linear, duration: 250 })
        .height(this.extraLayout.size.height)
        .width(this.extraLayout.size.width)
        .position({
          start: LengthMetrics.vp(this.extraLayout.position.x),
          top: LengthMetrics.vp(this.extraLayout.position.y),
        } as LocalizedEdges)
        .clip(true)
      }
    }
    .id('$$FoldSplitContainer$Stack$$')
    .width('100%')
    .height('100%')
    .onSizeChange((_, size) => {
      this.updateContainerSize(size);
      this.updateContainerPosition();
      this.updateLayout('');
    })
  }

  private dispatchHoverStatusChange(isHoverMode: boolean) {
    if (this.onHoverStatusChange) {
      let rotation: number = 0;
      try {
        rotation = display.getDefaultDisplaySync().rotation;
      } catch (err : BusinessError<void>) {
        Logger.error('Failed display.getDefaultDisplaySync(). code:%{public}d, message:%{public}s',
          err.code, err.message);
      }
      this.onHoverStatusChange?.({
        foldStatus: this.foldStatus,
        isHoverMode: isHoverMode,
        appRotation: rotation,
        windowStatusType: this.windowStatusType,
      });
    }
  }

  private hasExtraRegion(): boolean {
    return !!this.extra;
  }

  private async updatePreferredOrientation() {
    if (this.windowInstance) {
      try {
        if (this.foldStatus === display.FoldStatus.FOLD_STATUS_FOLDED) {
          this.windowInstance?.setPreferredOrientation(window.Orientation.AUTO_ROTATION_PORTRAIT);
        } else {
          this.windowInstance?.setPreferredOrientation(window.Orientation.AUTO_ROTATION);
        }
      } catch (err) {
        Logger.error('Failed to update preferred orientation.');
      }
    }
  }

  private updateContainerSize(size: SizeOptions) {
    this.containerSize.width = size.width as number;
    this.containerSize.height = size.height as number;
  }

  private updateContainerPosition() {
    const context = this.getUIContext();
    const frameNode = context.getFrameNodeById('$$FoldSplitContainer$Stack$$');
    if (frameNode) {
      this.containerGlobalPosition = frameNode.getPositionToWindow();
    }
  }

  private updateLayout(propName: string) {
    let isHoverMode: boolean = false;
    let regionLayout: RegionLayout;
    if (this.isSmallScreen) {
      regionLayout = this.getFoldedRegionLayouts();
    } else {
      if (this.foldStatus === display.FoldStatus.FOLD_STATUS_EXPANDED) {
        regionLayout = this.getExpandedRegionLayouts();
      } else if (this.foldStatus === display.FoldStatus.FOLD_STATUS_HALF_FOLDED) {
        if (this.isPortraitOrientation()) {
          regionLayout = this.getExpandedRegionLayouts();
        } else {
          regionLayout = this.getHoverModeRegionLayouts();
          isHoverMode = true;
        }
      } else if (this.foldStatus === display.FoldStatus.FOLD_STATUS_FOLDED) {
        regionLayout = this.getFoldedRegionLayouts();
      } else {
        regionLayout = this.getExpandedRegionLayouts();
      }
    }

    if (this.animationOptions === null) {
      this.primaryLayout = regionLayout.primary;
      this.secondaryLayout = regionLayout.secondary;
      this.extraLayout = regionLayout.extra;
    } else if (this.animationOptions === undefined) {
      this.getUIContext()?.animateTo({ curve: curves.springMotion(0.35, 1, 0) }, () => {
        this.primaryLayout = regionLayout.primary;
        this.secondaryLayout = regionLayout.secondary;
        this.extraLayout = regionLayout.extra;
      });
    } else {
      this.getUIContext()?.animateTo(this.animationOptions as AnimateParam, () => {
        this.primaryLayout = regionLayout.primary;
        this.secondaryLayout = regionLayout.secondary;
        this.extraLayout = regionLayout.extra;
      });
    }

    if (this.isHoverMode !== isHoverMode) {
      this.dispatchHoverStatusChange(isHoverMode);
      this.isHoverMode = isHoverMode;
    }

    if (isHoverMode && !this.hoverModeLayoutOptions.showExtraRegion) {
      this.extraOpacity = 0;
    } else {
      this.extraOpacity = 1;
    }
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
      extraLayout.size.width = width / (getPresetSplitRatio(horizontalSplitRatio) + 1);
    } else {
      extraLayout.size.width = 0;
    }
    secondaryLayout.size.height = height / (getPresetSplitRatio(verticalSplitRatio) + 1);
    primaryLayout.size.height = height - secondaryLayout.size.height;
    primaryLayout.position.x = 0;
    secondaryLayout.position.x = 0;
    primaryLayout.position.y = 0;
    secondaryLayout.position.y = primaryLayout.size.height;

    const isExtraRegionPerpendicular =
      withDefaultValue<Boolean>(this.expandedLayoutOptions.isExtraRegionPerpendicular as Boolean | undefined | null,
      true);
    if (isExtraRegionPerpendicular) {
      primaryLayout.size.width = width - extraLayout.size.width;
      secondaryLayout.size.width = width - extraLayout.size.width;
      extraLayout.size.height = height;
      extraLayout.position.x = primaryLayout.size.width;
      extraLayout.position.y = 0;
    } else {
      const extraRegionPosition = withDefaultValue<ExtraRegionPosition>(
        this.expandedLayoutOptions.extraRegionPosition as ExtraRegionPosition | undefined | null,
        ExtraRegionPosition.TOP);
      if (extraRegionPosition === ExtraRegionPosition.BOTTOM) {
        primaryLayout.size.width = width;
        secondaryLayout.size.width = width - extraLayout.size.width;
        extraLayout.size.height = secondaryLayout.size.height;
        extraLayout.position.x = secondaryLayout.size.width;
        extraLayout.position.y = primaryLayout.size.height;
      } else {
        primaryLayout.size.width = width - extraLayout.size.width;
        secondaryLayout.size.width = width;
        extraLayout.size.height = primaryLayout.size.height;
        extraLayout.position.x = primaryLayout.size.width;
        extraLayout.position.y = 0;
      }
    }

    return { primary: primaryLayout, secondary: secondaryLayout, extra: extraLayout };
  }

  private getHoverModeRegionLayouts(): RegionLayout {
    const width = this.containerSize.width;
    const height = this.containerSize.height;
    const primaryLayout: Layout = initLayout();
    const secondaryLayout: Layout = initLayout();
    const extraLayout: Layout = initLayout();
    const creaseRegionRect = this.getCreaseRegionRect();
    primaryLayout.position.x = 0;
    primaryLayout.position.y = 0;
    secondaryLayout.position.x = 0;
    secondaryLayout.position.y = creaseRegionRect.top + creaseRegionRect.height;
    secondaryLayout.size.height = height - secondaryLayout.position.y;
    primaryLayout.size.height = creaseRegionRect.top;

    const showExtraRegion = withDefaultValue<Boolean>(
      this.hoverModeLayoutOptions.showExtraRegion as Boolean | undefined | null, false);

    if (!showExtraRegion) {
      primaryLayout.size.width = width;
      secondaryLayout.size.width = width;
      extraLayout.position.x = width;
      const isExpandedExtraRegionPerpendicular =
        withDefaultValue<Boolean>(this.expandedLayoutOptions.isExtraRegionPerpendicular as Boolean | undefined | null,
        true);
      if (isExpandedExtraRegionPerpendicular) {
        extraLayout.size.height = this.extraLayout.size.height;
      } else {
        const expandedExtraRegionPosition = withDefaultValue<ExtraRegionPosition>(
          this.expandedLayoutOptions.extraRegionPosition as ExtraRegionPosition | undefined | null,
          ExtraRegionPosition.TOP);
        if (expandedExtraRegionPosition === ExtraRegionPosition.BOTTOM) {
          extraLayout.size.height = secondaryLayout.size.height;
          extraLayout.position.y = secondaryLayout.position.y;
        } else {
          extraLayout.size.height = primaryLayout.size.height;
          extraLayout.position.y = 0;
        }
      }
    } else {
      const horizontalSplitRatio =
        getSplitRatio(this.hoverModeLayoutOptions.horizontalSplitRatio, PresetSplitRatio.LAYOUT_3V2);
      const extraRegionPosition = withDefaultValue<ExtraRegionPosition>(
        this.hoverModeLayoutOptions.extraRegionPosition as ExtraRegionPosition | undefined | null,
        ExtraRegionPosition.TOP);
      if (this.hasExtraRegion()) {
        extraLayout.size.width = width / (getPresetSplitRatio(horizontalSplitRatio) + 1);
      } else {
        extraLayout.size.width = 0;
      }
      if (extraRegionPosition === ExtraRegionPosition.BOTTOM) {
        primaryLayout.size.width = width;
        secondaryLayout.size.width = width - extraLayout.size.width;
        extraLayout.size.height = secondaryLayout.size.height;
        extraLayout.position.x = secondaryLayout.size.width;
        extraLayout.position.y = secondaryLayout.position.y;
      } else {
        extraLayout.size.height = primaryLayout.size.height;
        primaryLayout.size.width = width - extraLayout.size.width;
        secondaryLayout.size.width = width;
        extraLayout.position.x = primaryLayout.position.x + primaryLayout.size.width;
        extraLayout.position.y = 0;
      }
    }

    return { primary: primaryLayout, secondary: secondaryLayout, extra: extraLayout };
  }

  private getFoldedRegionLayouts(): RegionLayout {
    const width = this.containerSize.width;
    const height = this.containerSize.height;
    const primaryLayout: Layout = initLayout();
    const secondaryLayout: Layout = initLayout();
    const extraLayout: Layout = initLayout();

    const verticalSplitRatio =
      getSplitRatio(this.foldedLayoutOptions.verticalSplitRatio, PresetSplitRatio.LAYOUT_1V1);

    secondaryLayout.size.height = height / (getPresetSplitRatio(verticalSplitRatio) + 1);
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

  private getCreaseRegionRect(): display.Rect {
    const creaseRegion = display.getCurrentFoldCreaseRegion();
    const rects = creaseRegion.creaseRects;
    let left: Long = 0;
    let top: Long = 0;
    let width: Long = 0;
    let height: Long = 0;
    if (rects && rects.length) {
      const rect = rects[0];
      left = (this.getUIContext().px2vp(rect.left) - this.containerGlobalPosition.x) as Long;
      top = (this.getUIContext().px2vp(rect.top) - this.containerGlobalPosition.y) as Long;
      width = this.getUIContext().px2vp(rect.width) as Long;
      height = this.getUIContext().px2vp(rect.height) as Long;
    }

    return { left, top, width, height };
  }

  private isPortraitOrientation() {
    let orientation : display.Orientation = display.Orientation.PORTRAIT;
    try {
      orientation = display.getDefaultDisplaySync().orientation;
    } catch (err : BusinessError<void>) {
      Logger.error('Failed display.getDefaultDisplaySync(). code:%{public}d, message:%{public}s',
        err.code, err.message);
    }
    switch (orientation) {
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