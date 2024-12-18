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

import { RadioBlock, useEnabled, SliderBlock, ColorBlock } from 'common';
import { Drawer } from 'common/src/main/ets/components/Drawer';

@Component
export struct SliderBootcamp {
  @State showParameters: boolean = false;
  @Require @Prop title: ResourceStr;
  @State enableSliderStyle: boolean = false;
  @State sliderStyle: SliderStyle = SliderStyle.OutSet;
  @State enableShowSteps: boolean = false;
  @State showSteps: boolean = false;
  @State enableStep: boolean = false;
  @State step: number = 1;
  @State enableShowTips: boolean = false;
  @State showTips: boolean = false;
  @State enableDirection: boolean = false;
  @State currentDirection: Direction = Direction.Auto;
  @State sliderWidth: number = 80;
  @State enableSliderWidth: boolean = false;
  @State sliderHeight: number = 50;
  @State enableSliderHeight: boolean = false;
  @State sliderEnabled: boolean = true;
  @State enableSliderEnabled: boolean = false;
  @State sliderBorderRadius: number = 1;
  @State enableSliderBorderRadius: boolean = false;
  @State sliderBorderColor: ResourceColor = Color.Black;
  @State enableSliderBorderColor: boolean = false;
  @State sliderBorderWidth: number = 1;
  @State enableSliderBorderWidth: boolean = false;
  @State sliderBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableSliderBorderStyle: boolean = false;
  @State sliderBackgroundColor: ResourceColor = Color.White;
  @State enableSliderBackgroundColor: boolean = false;
  @State sliderOpacity: number = 1;
  @State enableSliderOpacity: boolean = false;
  @State sliderVisibility: Visibility = Visibility.Visible;
  @State enableSliderVisibility: boolean = false;
  
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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column({ space: 8 }) {
      Slider({ style: useEnabled(this.enableSliderStyle, this.sliderStyle), step: this.step })
        .showTips(useEnabled(this.enableShowTips, this.showTips))
        .showSteps(useEnabled(this.enableShowSteps, this.showSteps))
        .direction(useEnabled(this.enableDirection, this.currentDirection))
        .width(useEnabled(this.enableSliderWidth, this.sliderWidth))
        .height(useEnabled(this.enableSliderHeight, this.sliderHeight))
        .enabled(useEnabled(this.enableSliderEnabled, this.sliderEnabled))
        .borderRadius(useEnabled(this.enableSliderBorderRadius, this.sliderBorderRadius))
        .borderColor(useEnabled(this.enableSliderBorderColor, this.sliderBorderColor))
        .borderWidth(useEnabled(this.enableSliderBorderWidth, this.sliderBorderWidth))
        .borderStyle(useEnabled(this.enableSliderBorderStyle, this.sliderBorderStyle))
        .backgroundColor(useEnabled(this.enableSliderBackgroundColor, this.sliderBackgroundColor))
        .opacity(useEnabled(this.enableSliderOpacity, this.sliderOpacity))
        .visibility(useEnabled(this.enableSliderVisibility, this.sliderVisibility))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '滑块的位置',
          isEnabled: this.enableSliderStyle,
          value: this.sliderStyle,
          dataSource: [
            { label: '滑块在滑轨上', value: SliderStyle.OutSet },
            { label: '滑块在滑轨内', value: SliderStyle.InSet },
          ]
        })

        RadioBlock({
          title: '是否显示步长刻度值',
          isEnabled: this.enableShowSteps,
          value: this.showSteps,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false },
          ]
        })

        SliderBlock({
          title: '间续滑动步长',
          isEnabled: this.enableStep,
          value: this.step,
          min: 1,
          max: 20
        })

        RadioBlock({
          title: '是否显示气泡',
          isEnabled: this.enableShowTips,
          value: this.showTips,
          dataSource: [
            { label: '是', value: true },
            { label: '否', value: false },
          ]
        })

        RadioBlock({
          title: '布局方式',
          isEnabled: this.enableDirection,
          value: this.currentDirection,
          dataSource: [
            { label: '默认布局', value: Direction.Auto },
            { label: '从右到左', value: Direction.Rtl },
            { label: '从左到右', value: Direction.Ltr }
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableSliderWidth,
          value: $sliderWidth,
          min: 60,
          max: 300
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableSliderHeight,
          value: $sliderHeight,
          min: 50,
          max: 80
        })

        RadioBlock({
          title: 'enabled',
          isEnabled: $enableSliderEnabled,
          value: $sliderEnabled,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableSliderBorderWidth,
          value: $sliderBorderWidth,
          min: 1,
          max: 5
        })

        SliderBlock({
          title: 'sliderBorderRadius',
          isEnabled: $enableSliderBorderRadius,
          value: $sliderBorderRadius,
          min: 0,
          max: 24
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableSliderBorderColor,
          color: $sliderBorderColor
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableSliderBorderStyle,
          value: $sliderBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid },
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableSliderBackgroundColor,
          color: $sliderBackgroundColor
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableSliderOpacity,
          value: $sliderOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })

        RadioBlock({
          title: 'visibility',
          isEnabled: $enableSliderVisibility,
          value: $sliderVisibility,
          dataSource: [
            { label: 'Visible', value: Visibility.Visible },
            { label: 'Hidden', value: Visibility.Hidden },
          ]
        })
      }
    }.height('52%')
  }
}

@Preview
@Component
struct SliderBootcampPreviewer {
  build() {
    SliderBootcamp({ title: '滑动条/Slider' })
  }
}