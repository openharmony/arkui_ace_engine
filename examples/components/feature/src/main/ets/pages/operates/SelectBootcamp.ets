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
export struct SelectBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State menuItem: SelectOption[] = [
    { value: 'Menu Item', icon: $r('sys.media.ohos_user_auth_icon_face') },
    { value: 'Menu Item', icon: $r('sys.media.ohos_user_auth_icon_face') },
    { value: 'Menu Item', icon: $r('sys.media.ohos_user_auth_icon_face') },
    { value: 'Menu Item', icon: $r('sys.media.ohos_user_auth_icon_face') }
  ];
  @State enableSelect: boolean = false;
  @State enable: boolean = true;
  @State enableBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = '#ffffff';
  @State enableControlSize: boolean = false;
  @State compControlSize: ControlSize = ControlSize.NORMAL;
  @State enableWidth: boolean = false;
  @State compWidth: number = 68;
  @State enableHeight: boolean = false;
  @State compHeight: number = 32;
  @State enableFontStyle: boolean = false;
  @State compFontStyle: FontStyle = FontStyle.Normal;
  @State enableFontSize: boolean = false;
  @State compFontSize: number = 10;
  @State enableBorderRadius: boolean = false;
  @State customBorderRadius: number = 8;
  @State enableDivider: boolean = false;
  @State dividerStrokeWidth: number = 1;
  @State dividerColor: ResourceColor = '#33182431';
  @State enableDividerColor: boolean = false;
  @State enableDividerStrokeWidth: boolean = false;
  @State dividerConfig: boolean = false;
  @State selectBorderColor: ResourceColor = Color.Black;
  @State enableSelectBorderColor: boolean = false;
  @State selectBorderWidth: number = 1;
  @State enableSelectBorderWidth: boolean = false;
  @State selectBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableSelectBorderStyle: boolean = false;
  @State selectOpacity: number = 1;
  @State enableSelectOpacity: boolean = false;
  @State selectVisibility: Visibility = Visibility.Visible;
  @State enableSelectVisibility: boolean = false;
  @State selectPadding: number = 8;
  @State enableSelectPadding: boolean = false;
  @State selectMargin: number = 8;
  @State enableSelectMargin: boolean = false;

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
    Column() {
      Select(this.menuItem)
        .value('下拉按钮')
        .backgroundColor(useEnabled(this.enableBackgroundColor, this.compBackgroundColor))
        .enabled(useEnabled(this.enableSelect, this.enable))
        .controlSize(useEnabled(this.enableControlSize, this.compControlSize))
        .width(useEnabled(this.enableWidth, this.compWidth))
        .height(useEnabled(this.enableHeight, this.compHeight))
        .divider(
          this.getDividerOptions()
        )
        .font({
          size: useEnabled(this.enableFontSize, this.compFontSize),
          style: useEnabled(this.enableFontStyle, this.compFontStyle),
        })
        .borderRadius(useEnabled(this.enableBorderRadius, this.customBorderRadius))
        .borderColor(useEnabled(this.enableSelectBorderColor, this.selectBorderColor))
        .borderWidth(useEnabled(this.enableSelectBorderWidth, this.selectBorderWidth))
        .borderStyle(useEnabled(this.enableSelectBorderStyle, this.selectBorderStyle))
        .opacity(useEnabled(this.enableSelectOpacity, this.selectOpacity))
        .visibility(useEnabled(this.enableSelectVisibility, this.selectVisibility))
        .margin(useEnabled(this.enableSelectMargin, this.selectMargin))
        .padding(useEnabled(this.enableSelectPadding, this.selectPadding))
    }
  }

  getDividerOptions(): DividerOptions | null | undefined {
    if (!this.enableDivider) {
      return null;
    }

    if (!this.dividerConfig) {
      return null;
    }

    return {
      strokeWidth: useEnabled(this.enableDividerStrokeWidth, this.dividerStrokeWidth),
      color: useEnabled(this.enableDividerColor, this.dividerColor),
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'controlSize',
          isEnabled: this.enableControlSize,
          value: this.compControlSize,
          dataSource: [
            { label: 'small', value: ControlSize.SMALL },
            { label: 'normal', value: ControlSize.NORMAL },
          ]
        })

        SliderBlock({
          title: 'fontSize',
          isEnabled: this.enableFontSize,
          value: this.compFontSize,
          min: 10,
          max: 30
        })

        SliderBlock({
          title: 'width',
          isEnabled: this.enableWidth,
          value: this.compWidth,
          min: 50,
          max: 100
        })

        SliderBlock({
          title: 'height',
          isEnabled: this.enableHeight,
          value: this.compHeight,
          min: 20,
          max: 50
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: this.enableBorderRadius,
          value: this.customBorderRadius,
          min: -5,
          max: 30
        })

        RadioBlock({
          title: 'enabled',
          isEnabled: this.enableSelect,
          value: this.enable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: this.enableBackgroundColor,
          color: this.compBackgroundColor
        })

        RadioBlock({
          title: 'fontStyle',
          isEnabled: this.enableFontStyle,
          value: this.compFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'divider',
          isEnabled: this.enableDivider,
          value: this.dividerConfig,
          dataSource: [
            { label: '显示', value: true },
            { label: '隐藏', value: false }
          ]
        })

        RadioBlock({
          title: '显隐控制',
          isEnabled: $enableSelectVisibility,
          value: $selectVisibility,
          dataSource: [
            { label: '显示', value: Visibility.Visible },
            { label: '隐藏', value: Visibility.Hidden },
          ]
        })

        SliderBlock({
          title: '边框宽度',
          isEnabled: $enableSelectBorderWidth,
          value: $selectBorderWidth,
          min: 1,
          max: 5
        })

        ColorBlock({
          title: '边框颜色',
          isEnabled: $enableSelectBorderColor,
          color: $selectBorderColor
        })

        RadioBlock({
          title: '边框样式',
          isEnabled: $enableSelectBorderStyle,
          value: $selectBorderStyle,
          dataSource: [
            { label: '原点', value: BorderStyle.Dotted },
            { label: '虚线', value: BorderStyle.Dashed },
            { label: '实线', value: BorderStyle.Solid },
          ]
        })

        SliderBlock({
          title: '透明度',
          isEnabled: $enableSelectOpacity,
          value: $selectOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })

        SliderBlock({
          title: '内边距',
          isEnabled: $enableSelectPadding,
          value: $selectPadding,
          step: 0.1,
          min: 0,
          max: 1
        })

        SliderBlock({
          title: '外边距',
          isEnabled: $enableSelectMargin,
          value: $selectMargin,
          step: 0.1,
          min: 0,
          max: 1
        })

        if (this.dividerConfig) {
          ColorBlock({
            title: 'dividercolor',
            isEnabled: this.enableDividerColor,
            color: this.dividerColor
          })

          SliderBlock({
            title: 'dividerstrokewidth',
            isEnabled: this.enableDividerStrokeWidth,
            value: this.dividerStrokeWidth,
            min: 1,
            max: 10
          })
        }
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct SelectBootcampPreviewer {
  build() {
    SelectBootcamp({
      title: '下拉按钮/Select'
    })
  }
}