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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';


@Component
export struct ProgressLockBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State isShow: boolean = false;
  @State enableProgressWidth: boolean = false;
  @State progressWidth: number = 100;
  @State enableProgressHeight: boolean = false;
  @State progressHeight: number = 60;
  @State enableProgressLayoutWeight: boolean = false;
  @State progressLayoutWeight: number = 0;
  @State enableProgressPadding: boolean = false;
  @State progressPadding: number = 0;
  @State enableProgressMargin: boolean = false;
  @State progressMargin: number = 0;
  @State enableProgressBorderWidth: boolean = false;
  @State progressBorderWidth: number = 0;
  @State enableProgressBorderRadius: boolean = false;
  @State progressBorderRadius: number = 0;
  @State enableProgressOpacity: boolean = false;
  @State progressOpacity: number = 0;
  @State enableProgressBorderStyle: boolean = false;
  @State progressBorderStyle: BorderStyle = BorderStyle.Dotted;
  @State enableProgressBorderColor: boolean = false;
  @State progressBorderColor: Color = Color.Transparent;
  @State enableProgressEnabled: boolean = false;
  @State progressEnabled: boolean = false;
  @State enableProgressBackgroundColor: boolean = false;
  @State progressBackgroundColor: ResourceColor = Color.White;
  @State enableProgressOptionsValue: boolean = false;
  @State progressOptionsValue: number = 0;
  @State enableProgressOptionsTotal: boolean = false;
  @State progressOptionsTotal: number = 100;
  @State enableProgressOptionsType: boolean = false;
  @State progressOptionsType: ProgressType = ProgressType.Linear;
  @State enableProgressValue: boolean = false;
  @State progressValue: number = 0;
  @State enableProgressColor: boolean = false;
  @State progressColor: ResourceColor = '#33007dff';
  @State enableCapsuleStyleOptionsBorderColor: boolean = false;
  @State capsuleStyleOptionsBorderColor: ResourceColor = '#33007dff';
  @State enableCapsuleStyleOptionsBorderWidth: boolean = false;
  @State capsuleStyleOptionsBorderWidth: number = 1;
  @State enableCapsuleStyleOptionsFont: boolean = false;
  @State capsuleStyleOptionsFont: number = 12;
  @State enableCapsuleStyleOptionsFontColor: boolean = false;
  @State capsuleStyleOptionsFontColor: ResourceColor = '#ff182431';
  @State enableCapsuleStyleOptionsScaleWidth: boolean = false;
  @State capsuleStyleOptionsScaleWidth: number = 2;
  @State enableCapsuleStyleOptionsShowDefaultPercentage: boolean = false;
  @State capsuleStyleOptionsShowDefaultPercentage: boolean = true;
  @State enableScaleRingStyleOptionsStrokeWidth: boolean = false;
  @State scaleRingStyleOptionsStrokeWidth: number = 4;
  @State enableScaleRingStyleOptionsScaleCount: boolean = false;
  @State scaleRingStyleOptionsScaleCount: number = 120;
  @State enableScaleRingStyleOptionsScaleWidth: boolean = false;
  @State scaleRingStyleOptionsScaleWidth: number = 2;
  @State enableEclipseStyleOptionsEnableSmoothEffect: boolean = false;
  @State eclipseStyleOptionsEnableSmoothEffect: boolean = true;
  @State enableRingStyleOptionsStrokeWidth: boolean = false;
  @State ringStyleOptionsStrokeWidth: number = 2;
  @State enableRingStyleOptionsShadow: boolean = false;
  @State ringStyleOptionsShadow: boolean = false;
  @State enableRingStyleOptionsStatus: boolean = false;
  @State ringStyleOptionsStatus: ProgressStatus = ProgressStatus.PROGRESSING;
  @State enableLinearStyleOptionsStrokeWidth: boolean = false;
  @State linearStyleOptionsStrokeWidth: number = 4;
  @State enableLinearStyleOptionsStrokeRadius: boolean = false;
  @State linearStyleOptionsStrokeRadius: number = 2;
  @State enableProgressStyleOptionsStrokeWidth: boolean = false;
  @State progressStyleOptionsStrokeWidth: number = 4;
  @State enableProgressStyleOptionsScaleWidth: boolean = false;
  @State progressStyleOptionsScaleWidth: number = 2;
  @State enableProgressStyleOptionsScaleCount: boolean = false;
  @State progressStyleOptionsScaleCount: number = 120;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      Progress({
        value: useEnabled(this.enableProgressOptionsValue, this.progressOptionsValue),
        type: useEnabled(this.enableProgressOptionsType, this.progressOptionsType),
        total: useEnabled(this.enableProgressOptionsTotal, this.progressOptionsTotal)
      })
        .value(useEnabled(this.enableProgressValue, this.progressValue))
        .color(useEnabled(this.enableProgressColor, this.progressColor))
        .style(this.progressOptionsType === ProgressType.Capsule ?
          {
            borderColor: useEnabled(this.enableCapsuleStyleOptionsBorderColor, this.capsuleStyleOptionsBorderColor),
            borderWidth: useEnabled(this.enableCapsuleStyleOptionsBorderWidth, this.capsuleStyleOptionsBorderWidth),
            content: 'CapsuleStyleOptions',
            font: useEnabled(this.enableCapsuleStyleOptionsFont, this.capsuleStyleOptionsFont),
            fontColor: useEnabled(this.enableCapsuleStyleOptionsFontColor, this.capsuleStyleOptionsFontColor),
            scaleWidth: useEnabled(this.enableCapsuleStyleOptionsScaleWidth, this.capsuleStyleOptionsScaleWidth),
            showDefaultPercentage: useEnabled(this.enableCapsuleStyleOptionsShowDefaultPercentage,
              this.capsuleStyleOptionsShowDefaultPercentage)
          } as CapsuleStyleOptions :
          this.progressOptionsType === ProgressType.ScaleRing ?
            {
              strokeWidth: useEnabled(this.enableScaleRingStyleOptionsStrokeWidth,
                this.scaleRingStyleOptionsStrokeWidth),
              scaleCount: useEnabled(this.enableScaleRingStyleOptionsScaleCount, this.scaleRingStyleOptionsScaleCount),
              scaleWidth: useEnabled(this.enableScaleRingStyleOptionsScaleWidth, this.scaleRingStyleOptionsScaleWidth)
            } as ScaleRingStyleOptions :
            this.progressOptionsType === ProgressType.Eclipse ? {
              enableSmoothEffect: useEnabled(this.enableEclipseStyleOptionsEnableSmoothEffect,
                this.eclipseStyleOptionsEnableSmoothEffect)
            } as EclipseStyleOptions :
              this.progressOptionsType === ProgressType.Ring ?
                {
                  strokeWidth: useEnabled(this.enableRingStyleOptionsStrokeWidth, this.ringStyleOptionsStrokeWidth),
                  shadow: useEnabled(this.enableRingStyleOptionsShadow, this.ringStyleOptionsShadow),
                  status: useEnabled(this.enableRingStyleOptionsStatus, this.ringStyleOptionsStatus)
                } as RingStyleOptions :
                this.progressOptionsType === ProgressType.Linear ?
                  {
                    strokeWidth: useEnabled(this.enableLinearStyleOptionsStrokeWidth,
                      this.linearStyleOptionsStrokeWidth),
                    strokeRadius: useEnabled(this.enableLinearStyleOptionsStrokeRadius,
                      this.linearStyleOptionsStrokeRadius)
                  } as LinearStyleOptions : {
                  strokeWidth: useEnabled(this.enableProgressStyleOptionsStrokeWidth,
                    this.progressStyleOptionsStrokeWidth),
                  scaleWidth: useEnabled(this.enableProgressStyleOptionsScaleWidth,
                    this.progressStyleOptionsScaleWidth),
                  scaleCount: useEnabled(this.enableProgressStyleOptionsScaleCount, this.progressStyleOptionsScaleCount)
                } as ProgressStyleOptions)
        .backgroundColor(useEnabled(this.enableProgressBackgroundColor, this.progressBackgroundColor))
        .width(useEnabled(this.enableProgressWidth, this.progressWidth))
        .height(useEnabled(this.enableProgressHeight, this.progressHeight))
        .layoutWeight(useEnabled(this.enableProgressLayoutWeight, this.progressLayoutWeight))
        .padding(useEnabled(this.enableProgressPadding, this.progressPadding))
        .margin(useEnabled(this.enableProgressMargin, this.progressMargin))
        .opacity(useEnabled(this.enableProgressOpacity, this.progressOpacity))
        .borderStyle(useEnabled(this.enableProgressBorderStyle, this.progressBorderStyle))
        .borderWidth(useEnabled(this.enableProgressBorderWidth, this.progressBorderWidth))
        .borderRadius(useEnabled(this.enableProgressBorderRadius, this.progressBorderRadius))
        .borderColor(useEnabled(this.enableProgressBorderColor, this.progressBorderColor))
        .enabled(useEnabled(this.enableProgressEnabled, this.progressEnabled))
    }.justifyContent(FlexAlign.Center)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        SliderBlock({
          title: 'progressOptions.value',
          isEnabled: $enableProgressOptionsValue,
          value: $progressOptionsValue,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'progressOptions.type',
          isEnabled: $enableProgressOptionsType,
          value: $progressOptionsType,
          dataSource: [
            { label: 'Linear', value: ProgressType.Linear },
            { label: 'Ring', value: ProgressType.Ring },
            { label: 'Eclipse', value: ProgressType.Eclipse },
            { label: 'ScaleRing', value: ProgressType.ScaleRing },
            { label: 'Capsule', value: ProgressType.Capsule }
          ]
        })

        SliderBlock({
          title: 'progressOptions.total',
          isEnabled: $enableProgressOptionsTotal,
          value: $progressOptionsTotal,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'value',
          isEnabled: $enableProgressValue,
          value: $progressValue,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'capsuleStyleOptions.borderColor',
          isEnabled: $enableCapsuleStyleOptionsBorderColor,
          color: $capsuleStyleOptionsBorderColor,
        })

        SliderBlock({
          title: 'capsuleStyleOptions.borderWidth',
          isEnabled: $enableCapsuleStyleOptionsBorderWidth,
          value: $capsuleStyleOptionsBorderWidth,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'capsuleStyleOptions.font',
          isEnabled: $enableCapsuleStyleOptionsFont,
          value: $capsuleStyleOptionsFont,
          min: 8,
          max: 24
        })

        ColorBlock({
          title: 'capsuleStyleOptions.fontColor',
          isEnabled: $enableCapsuleStyleOptionsFontColor,
          color: $capsuleStyleOptionsFontColor,
        })

        RadioBlock({
          title: 'capsuleStyleOptions.showDefaultPercentage',
          isEnabled: $enableCapsuleStyleOptionsShowDefaultPercentage,
          value: $capsuleStyleOptionsShowDefaultPercentage,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'scaleRingStyleOptions.strokeWidth',
          isEnabled: $enableScaleRingStyleOptionsStrokeWidth,
          value: $scaleRingStyleOptionsStrokeWidth,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'scaleRingStyleOptions.scaleWidth',
          isEnabled: $enableScaleRingStyleOptionsScaleWidth,
          value: $scaleRingStyleOptionsScaleWidth,
          min: 8,
          max: 24
        })

        SliderBlock({
          title: 'scaleRingStyleOptions.scaleCount',
          isEnabled: $enableScaleRingStyleOptionsScaleCount,
          value: $scaleRingStyleOptionsScaleCount,
          min: 100,
          max: 200
        })

        RadioBlock({
          title: 'eclipseStyleOptions.enableSmoothEffect',
          isEnabled: $enableEclipseStyleOptionsEnableSmoothEffect,
          value: $eclipseStyleOptionsEnableSmoothEffect,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'ringStyleOptions.strokeWidth',
          isEnabled: $enableRingStyleOptionsStrokeWidth,
          value: $ringStyleOptionsStrokeWidth,
          min: 0,
          max: 8
        })

        RadioBlock({
          title: 'ringStyleOptions.shadow',
          isEnabled: $enableRingStyleOptionsShadow,
          value: $ringStyleOptionsShadow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'ringStyleOptions.status',
          isEnabled: $enableRingStyleOptionsStatus,
          value: $ringStyleOptionsStatus,
          dataSource: [
            { label: 'PROGRESSING', value: ProgressStatus.PROGRESSING },
            { label: 'LOADING', value: ProgressStatus.LOADING },
          ]
        })

        SliderBlock({
          title: 'linearStyleOptions.strokeWidth',
          isEnabled: $enableLinearStyleOptionsStrokeWidth,
          value: $linearStyleOptionsStrokeWidth,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'linearStyleOptions.strokeRadius',
          isEnabled: $enableLinearStyleOptionsStrokeRadius,
          value: $linearStyleOptionsStrokeRadius,
          min: 8,
          max: 24
        })

        SliderBlock({
          title: 'progressStyleOptions.strokeWidth',
          isEnabled: $enableProgressStyleOptionsStrokeWidth,
          value: $progressStyleOptionsStrokeWidth,
          min: 0,
          max: 8
        })

        SliderBlock({
          title: 'progressStyleOptions.scaleWidth',
          isEnabled: $enableProgressStyleOptionsScaleWidth,
          value: $progressStyleOptionsScaleWidth,
          min: 8,
          max: 24
        })

        SliderBlock({
          title: 'progressStyleOptions.scaleCount',
          isEnabled: $enableProgressStyleOptionsScaleCount,
          value: $progressStyleOptionsScaleCount,
          min: 80,
          max: 200
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableProgressBackgroundColor,
          color: $progressBackgroundColor,
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableProgressWidth,
          value: $progressWidth,
          min: 50,
          max: 180
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableProgressHeight,
          value: $progressHeight,
          min: 50,
          max: 100
        })

        RadioBlock({
          title: 'layoutWeight',
          isEnabled: $enableProgressLayoutWeight,
          value: $progressLayoutWeight,
          dataSource: [
            { label: '1', value: 1 },
            { label: '0', value: 0 }
          ]
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableProgressPadding,
          value: $progressPadding,
          min: 0,
          max: 24
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableProgressMargin,
          value: $progressMargin,
          min: 0,
          max: 24
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableProgressOpacity,
          value: $progressOpacity,
          min: 0,
          step: 0.1,
          max: 1
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableProgressBorderWidth,
          value: $progressBorderWidth,
          min: 0,
          max: 6
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableProgressBorderRadius,
          value: $progressBorderRadius,
          min: 0,
          max: 24
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableProgressBorderColor,
          color: $progressBorderColor,
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableProgressBorderStyle,
          value: $progressBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid },
          ]
        })

        RadioBlock({
          title: 'enabled',
          isEnabled: $enableProgressEnabled,
          value: $progressEnabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ProgressLockPreviewer {
  build() {
    ProgressLockBootcamp({
      title: '进度条/Progress'
    })
  }
}