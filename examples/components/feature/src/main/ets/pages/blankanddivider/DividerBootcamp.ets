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
export struct DividerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State dividerBackgroundColor: Color = 0xFF000000;
  @State enableDividerBackgroundColor: boolean = false;
  @State dividerMargin: number = 0;
  @State enableDividerMargin: boolean = false;
  @State dividerPadding: number = 0;
  @State enableDividerPadding: boolean = false;
  @State dividerWidth: number = 1;
  @State enableDividerWidth: boolean = false;
  @State dividerHeight: number = 1;
  @State enableDividerHeight: boolean = false;
  @State dividerOpacity: number = 1;
  @State enableDividerOpacity: boolean = false;
  @State dividerStrokeWidth: number = 1;
  @State enableDividerStrokeWidth: boolean = false;
  @State vertical: boolean = false;
  @State enableVertical: boolean = false;
  @State lineCapStyle: LineCapStyle = LineCapStyle.Butt;
  @State enableLineCapStyle: boolean = false;
  @State dividerVisibility: Visibility = Visibility.Visible;
  @State enableDividerVisibility: boolean = false;
  @State dividerEnabled: boolean = true;
  @State enableDividerEnabled: boolean = false;

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
    Column() {
      Divider()
        .color(useEnabled(this.enableDividerBackgroundColor, this.dividerBackgroundColor))
        .margin(useEnabled(this.enableDividerMargin, this.dividerMargin))
        .padding(useEnabled(this.enableDividerPadding, this.dividerPadding))
        .strokeWidth(useEnabled(this.enableDividerStrokeWidth, this.dividerStrokeWidth))
        .width(useEnabled(this.enableDividerWidth, this.dividerWidth))
        .height(useEnabled(this.enableDividerHeight, this.dividerHeight))
        .vertical(useEnabled(this.enableVertical, this.vertical))
        .lineCap(useEnabled(this.enableLineCapStyle, this.lineCapStyle))
        .visibility(useEnabled(this.enableDividerVisibility, this.dividerVisibility))
        .enabled(useEnabled(this.enableDividerEnabled, this.dividerEnabled))
        .opacity(useEnabled(this.enableDividerOpacity, this.dividerOpacity))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column() {
        SliderBlock({
          title: '水平分割线长度',
          isEnabled: $enableDividerWidth,
          value: $dividerWidth,
          min: 50,
          max: 100
        })

        SliderBlock({
          title: '垂直分割线高度',
          isEnabled: $enableDividerHeight,
          value: $dividerHeight,
          min: 50,
          max: 100
        })

        SliderBlock({
          title: '透明度设置',
          isEnabled: $enableDividerOpacity,
          value: $dividerOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableDividerBackgroundColor,
          color: $dividerBackgroundColor
        })

        SliderBlock({
          title: '当前外边距',
          isEnabled: $enableDividerMargin,
          value: $dividerMargin,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: '当前内边距',
          isEnabled: $enableDividerPadding,
          value: $dividerPadding,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: '分割线宽',
          isEnabled: $enableDividerStrokeWidth,
          value: $dividerStrokeWidth,
          min: 0,
          max: 8
        })

        RadioBlock({
          title: '分割线方向',
          isEnabled: $enableVertical,
          value: $vertical,
          dataSource: [
            { label: '水平方向', value: false },
            { label: '垂直方向', value: true }
          ]
        })

        RadioBlock({
          title: '组件显隐',
          isEnabled: $enableDividerVisibility,
          value: $dividerVisibility,
          dataSource: [
            { label: '组件显示', value: Visibility.Visible },
            { label: '组件隐藏', value: Visibility.Hidden }
          ]
        })

        RadioBlock({
          title: '禁用控制',
          isEnabled: $enableDividerEnabled,
          value: $dividerEnabled,
          dataSource: [
            { label: '组件可交互', value: true },
            { label: '组件不可交互', value: false }
          ]
        })

        RadioBlock({
          title: '分割线端点样式',
          isEnabled: $enableLineCapStyle,
          value: $lineCapStyle,
          dataSource: [
            { label: '两端为平行线', value: LineCapStyle.Butt },
            { label: '两端为半圆', value: LineCapStyle.Round },
            { label: '两端为矩形', value: LineCapStyle.Square }
          ]
        })

      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct DividerBootcampPreviewer {
  build() {
    DividerBootcamp({
      title: '分割/divider'
    })
  }
}


