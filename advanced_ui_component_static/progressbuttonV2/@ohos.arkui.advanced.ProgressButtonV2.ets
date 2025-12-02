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

import {
  $r, Row, Area, Text, Color, Stack, Button, Length, Padding, Progress, ComponentV2, FontWeight, ButtonType, ClickEvent,
  HoverEffect, TextOverflow, ProgressType, ColorMetrics, ResourceColor, ResourceStr, ButtonOptions, ProgressOptions,
  CapsuleStyleOptions, SizeOptions
} from '@ohos.arkui.component';
import { Param, Once, Local, Monitor, Require, ObservedV2, Trace, IMonitor } from '@ohos.arkui.stateManagement';
import { LengthUnit, LengthMetrics } from '@ohos.arkui.node';
import { Theme } from '@ohos.arkui.theme';

const EMPTY_STRING: string = '';
const MAX_PROGRESS: double = 100;
const MAX_PERCENTAGE: string = '100%';
const MIN_PERCENTAGE: string = '0%';
const TEXT_OPACITY: number = 0.4;
const BUTTON_NORMARL_WIDTH: number = 44;
const BUTTON_NORMARL_HEIGHT: number = 28;
const BUTTON_BORDER_RADIUS: number = 14;
const TEXT_ENABLE: number = 1.0;


// Set the key value for the basic component of skin changing corresponding to progressButton
const PROGRESS_BUTTON_PROGRESS_KEY = 'progress_button_progress_key';
const PROGRESS_BUTTON_PRIMARY_FONT_KEY = 'progress_button_primary_font_key';
const PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY = 'progress_button_container_background_color_key';
const PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY = 'progress_button_emphasize_secondary_button_key';

@ComponentV2
export struct ProgressButtonV2 {
  @Param @Require progress: double | undefined;
  @Param content: ResourceStr | undefined = EMPTY_STRING as string;
  @Param @Once progressButtonWidth?: LengthMetrics = LengthMetrics.vp(BUTTON_NORMARL_WIDTH);
  @Param onClicked: ClickCallback = () => {};
  @Param isEnabled: boolean | undefined = true;
  @Param colorOptions?: ProgressButtonV2Color | undefined = undefined;
  @Param progressButtonRadius?: LengthMetrics | undefined = undefined;
  @Local textProgress: string = EMPTY_STRING as string;
  @Local isLoading: boolean = false;
  @Local progressColor: ResourceColor = '#330A59F7'
  @Local containerBorderColor: ResourceColor = '#330A59F7'
  @Local containerBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_foreground_contrary')
  @Local textHeight?: Length = BUTTON_NORMARL_HEIGHT as number;
  @Local buttonBorderRadius?: number = BUTTON_BORDER_RADIUS as number;

  onWillApplyTheme(theme: Theme) {
    this.progressColor = theme.colors.compEmphasizeSecondary;
    this.containerBorderColor = theme.colors.compEmphasizeSecondary;
    this.containerBackgroundColor = theme.colors.iconOnFourth;
  }

  private getButtonProgress():double {
    if (this.progress === undefined) {
      return 0.0;
    }
    const safeProgress: double = this.progress as double;
    const minValue: double = Math.min(safeProgress, MAX_PROGRESS);
    return Math.max(0.0, minValue);
  }

  @Monitor(['progress'])
  private getProgressContext(monitor: IMonitor){
    const safeProgress: double = this.progress === undefined || this.progress == null
      ? 0.0
      : this.progress as double;
    if (safeProgress < 0.0) {
      this.isLoading = false;
      this.textProgress = MIN_PERCENTAGE;
    } else if (safeProgress >= MAX_PROGRESS) {
      this.isLoading = false;
      this.textProgress = MAX_PERCENTAGE;
    } else {
      this.isLoading = true;
      const percentage: double = (safeProgress / MAX_PROGRESS) * 100.0;
      this.textProgress = `${Math.floor(percentage)}%`;
    }
  }

  @Monitor(['isLoading'])
  private getLoadingProgress(monitor: IMonitor) {
    const safeProgress: double = this.progress === undefined || this.progress == null
      ? 0.0
      : this.progress as double;
    if (this.isLoading) {
      if (safeProgress < 0.0) {
        this.textProgress = MIN_PERCENTAGE;
      } else if (safeProgress >= MAX_PROGRESS) {
        this.textProgress = MAX_PERCENTAGE;
      } else {
        this.textProgress = `${Math.floor(safeProgress / MAX_PROGRESS * MAX_PROGRESS)}%`;
      }
    }
  }

  private getProgressButtonRadius(): LengthMetrics {
    if (!this.progressButtonRadius || this.progressButtonRadius?.unit === LengthUnit.PERCENT) {
      return LengthMetrics.vp(this.buttonBorderRadius!);
    } else if ((this.progressButtonRadius?.value as number) < 0) {
      return LengthMetrics.vp(0);
    } else {
      return this.progressButtonRadius as LengthMetrics;
    }
  }

  build() {
    Button({ type: ButtonType.Normal } as ButtonOptions) {
      Stack() {
        Progress({
          value: this.getButtonProgress(), total: MAX_PROGRESS,
          type: ProgressType.Capsule
        }  as ProgressOptions)
          .height(this.textHeight)
          .constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT })
          .borderRadius(this.buttonBorderRadius)
          .width('100%')
          .hoverEffect(HoverEffect.None)
          .style({
            borderColor: this.colorOptions?.borderColor?.color ?
              this.colorOptions?.borderColor?.color : this.containerBorderColor,
            borderRadius: this.getProgressButtonRadius()
          } as CapsuleStyleOptions)
          .clip(false)
          .enabled(this.isEnabled)
          .key(PROGRESS_BUTTON_PROGRESS_KEY)
          .color(this.colorOptions?.progressColor?.color ? this.colorOptions?.progressColor?.color : this.progressColor)
        Row() {
          Text(this.isLoading ? this.textProgress : this.content)
            .fontSize($r('sys.float.ohos_id_text_size_button3'))
            .fontWeight(FontWeight.Medium)
            .key(PROGRESS_BUTTON_PRIMARY_FONT_KEY)
            .fontColor(this.colorOptions?.textColor?.color ? this.colorOptions?.textColor?.color : '#e6182431')
            .maxLines(1)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .padding({
              top: 4,
              left: 8,
              right: 8,
              bottom: 4
            } as Padding)
            .opacity(this.isEnabled ? TEXT_ENABLE : TEXT_OPACITY)
            .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
              if (!newValue.height || newValue.height === this.textHeight) {
                return;
              }
              this.textHeight = (newValue.height as number) > (BUTTON_NORMARL_HEIGHT as number) ?
                newValue.height as number : BUTTON_NORMARL_HEIGHT;
              this.buttonBorderRadius = (Number(this.textHeight as number) / 2) as number;
            })
        }
        .constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT })

        Row()
          .key(PROGRESS_BUTTON_CONTAINER_BACKGROUND_COLOR_KEY)
          .backgroundColor(Color.Transparent)
          .border({
            width: 1,
            color: this.colorOptions?.borderColor?.color ?
              this.colorOptions?.borderColor?.color : this.containerBorderColor
          })
          .height(this.textHeight)
          .constraintSize({ minHeight: BUTTON_NORMARL_HEIGHT })
          .borderRadius(this.progressButtonRadius ? this.toLengthString(this.getProgressButtonRadius()) :
            this.buttonBorderRadius)
          .width('100%')
      }
    }
    .borderRadius(this.progressButtonRadius ? this.toLengthString(this.getProgressButtonRadius()) :
      this.buttonBorderRadius)
    .clip(false)
    .hoverEffect(HoverEffect.None)
    .key(PROGRESS_BUTTON_EMPHASIZE_SECONDARY_BUTTON_KEY)
    .backgroundColor(
      this.colorOptions?.backgroundColor?.color
        ? this.colorOptions?.backgroundColor?.color
        : this.containerBackgroundColor)
    .padding({ top: 0, bottom: 0 } as Padding)
    .width((!this.progressButtonWidth || (this.progressButtonWidth?.value as number) < 0) ?
      BUTTON_NORMARL_WIDTH as number : this.toLengthString(this.progressButtonWidth) as string)
    .constraintSize({ minWidth: BUTTON_NORMARL_WIDTH })
    .stateEffect(this.isEnabled)
    .onClick((event?: ClickEvent):void => {
      const safeProgress: double = this.progress === undefined || this.progress == null
        ? 0.0
        : this.progress as double;
      if (this.progress === undefined) {
        return;
      }
      if (!this.isEnabled) {
        return;
      }
      if (safeProgress < MAX_PROGRESS) {
        this.isLoading = !this.isLoading;
      }
      this.onClicked();
    })
  }

  private toLengthString(value: LengthMetrics | undefined): string {
    if (value === undefined) {
      return '';
    }
    const length: number = value.value;
    let lengthString: string = '';
    switch (value.unit) {
      case LengthUnit.PX:
        lengthString = `${length}px`;
        break;
      case LengthUnit.FP:
        lengthString = `${length}fp`;
        break;
      case LengthUnit.LPX:
        lengthString = `${length}lpx`;
        break;
      case LengthUnit.PERCENT:
        lengthString = `${length * 100}%`;
        break;
      case LengthUnit.VP:
        lengthString = `${length}vp`;
        break;
      default:
        lengthString = `${length}vp`;
        break;
    }
    return lengthString;
  }
}

@ObservedV2
export class ProgressButtonV2Color {
  @Trace public progressColor?: ColorMetrics;
  @Trace public borderColor?: ColorMetrics;
  @Trace public textColor?: ColorMetrics;
  @Trace public backgroundColor?: ColorMetrics;

  constructor(options: ProgressButtonV2ColorOptions) {
    this.progressColor = options.progressColor;
    this.borderColor = options.borderColor;
    this.textColor = options.textColor;
    this.backgroundColor = options.backgroundColor;
  }
}

export type ClickCallback = () => void;

export interface ProgressButtonV2ColorOptions {
  progressColor?: ColorMetrics;
  borderColor?: ColorMetrics;
  textColor?: ColorMetrics;
  backgroundColor?: ColorMetrics;
}



