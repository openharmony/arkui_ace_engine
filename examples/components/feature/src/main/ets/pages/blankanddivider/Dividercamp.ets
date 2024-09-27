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
import { ColorBlock, RadioBlock, SliderBlock, SliderOpacityBlock } from 'common';
import { promptAction } from '@kit.ArkUI';

@Component
export struct DividerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State dividerBackgroundColor: Color = 0xFF000000;
  @State dividerMargin: number = 0;
  @State dividerPadding: number = 0;
  @State dividerStrokeWidth: number = 3;
  @State enableDividerBackgroundColor: boolean = false;
  @State enableDividerMargin: boolean = false;
  @State enableDividerPadding: boolean = false;
  @State max: number = 10;
  @State dividerWidth: number = 20;
  @State enableDividerWidth: boolean = false;
  @State dividerWidthMax: number = 100;
  @State dividerStrokeWidthMax: number = 8;
  @State enableDividerStrokeWidth: boolean = false;
  @State vertical: boolean = false;
  @State enableVertical: boolean = false;
  @State lineCapStyle: LineCapStyle = LineCapStyle.Butt;
  @State enableLineCapStyle: boolean = false;
  @State dividerVisibility: Visibility = Visibility.Visible;
  @State enableDividerVisibility: boolean = false;
  @State dividerEnabled: boolean = true;
  @State enableEnabled: boolean = false;
  @State enableOpacity: boolean = false;
  @State dividerOpacity: number = 1;
  @State opacityMax: number = 1;

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
      Row() {
        Text('Hello')
          .fontSize(18)
        Divider()
          .color(this.enableDividerBackgroundColor ? this.dividerBackgroundColor : undefined)
          .margin(this.enableDividerMargin ? this.dividerMargin : undefined)
          .padding(this.enableDividerPadding ? this.dividerPadding : undefined)
          .strokeWidth(this.enableDividerStrokeWidth ? this.dividerStrokeWidth : undefined)
          .width(this.enableDividerWidth ? this.dividerWidth : 20)
          .vertical(this.enableVertical ? this.vertical : undefined)
          .lineCap(this.enableLineCapStyle ? this.lineCapStyle : undefined)
          .visibility(this.enableDividerVisibility ? this.dividerVisibility : undefined)
          .enabled(this.enableEnabled ? this.dividerEnabled : undefined)
          .opacity(this.enableOpacity ? this.dividerOpacity : undefined)
          .onClick(() => {
            promptAction.showToast({
              message: '分割线被点击！'
            });
          })
        Text('world')
          .fontSize(18)
      }
      .justifyContent(FlexAlign.Center)
      .width(300)
      .height(150)
      .backgroundColor(0xEFEFEF)
      .borderRadius(15)
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 0 }) {
        SliderBlock({
          title: '分割线当前宽度',
          isEnabled: $enableDividerWidth,
          value: $dividerWidth,
          min: 0,
          max: this.dividerWidthMax
        })

        SliderOpacityBlock({
          title: '透明度设置',
          isEnabled: $enableOpacity,
          value: $dividerOpacity,
          min: 0,
          max: this.opacityMax
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
          max: this.max
        })

        SliderBlock({
          title: '当前内边距',
          isEnabled: $enableDividerPadding,
          value: $dividerPadding,
          min: 0,
          max: this.max
        })

        SliderBlock({
          title: '分割线宽',
          isEnabled: $enableDividerStrokeWidth,
          value: $dividerStrokeWidth,
          min: 0,
          max: this.dividerStrokeWidthMax
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
          isEnabled: $enableEnabled,
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
    .onDisAppear(()=>{
      AppStorage.setOrCreate('Block', []);
    })
  }
}


