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
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';

@Component
export struct ToggleBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableIsOn: boolean = false;
  @State isOn: boolean = false;
  @State enableCustomEnable: boolean = false;
  @State customEnable: boolean = true;
  @State enableCompHeight: boolean = false;
  @State compHeight: number = 20;
  @State enableCustomWidth: boolean = false;
  @State customWidth: number = 21.6;
  @State enableCustomPointRadius: boolean = false;
  @State customPointRadius: number = 8;
  @State enableCustomTrackBorderRadius: boolean = false;
  @State customTrackBorderRadius: number = 10;
  @State enableCustomPointColor: boolean = false;
  @State customPointColor: ResourceColor = '#ffffffff';
  @State enableCustomUnselectedColor: boolean = false;
  @State customUnselectedColor: ResourceColor = 0x337F7F7F;
  @State enableCustomSelectedColor: boolean = false;
  @State customSelectedColor: ResourceColor = '#ff007dff';
  @State toggleType: ToggleType = ToggleType.Switch;
  @State enabledToggleType: boolean = false;

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
      Toggle({
        type: useEnabled(this.enabledToggleType, this.toggleType),
        isOn: useEnabled(this.enableIsOn, this.isOn)
      }) {
        Text('status button').fontColor('#182431').fontSize(12)
      }
      .height(useEnabled(this.enableCompHeight, this.compHeight))
      .width(useEnabled(this.enableCustomWidth, this.customWidth))
      .switchStyle({
        pointRadius: useEnabled(this.enableCustomPointRadius, this.customPointRadius),
        trackBorderRadius: useEnabled(this.enableCustomTrackBorderRadius, this.customTrackBorderRadius),
        pointColor: useEnabled(this.enableCustomPointColor, this.customPointColor),
        unselectedColor: useEnabled(this.enableCustomUnselectedColor, this.customUnselectedColor),
      })
      .enabled(useEnabled(this.enableCustomEnable, this.customEnable))
      .selectedColor(useEnabled(this.enableCustomSelectedColor, this.customSelectedColor))
      .onChange((isOn: boolean) => {
        console.info('Component status:' + isOn)
      })
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'ToggleType切换',
          isEnabled: this.enabledToggleType,
          value: this.toggleType,
          dataSource: [
            { label: 'Switch', value: ToggleType.Switch },
            { label: 'Checkbox', value: ToggleType.Checkbox },
            { label: 'Button', value: ToggleType.Button },
          ]
        })

        RadioBlock({
          title: 'Switch默认是否打开',
          isEnabled: this.enableIsOn,
          value: this.isOn,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'Switch是否可操作',
          isEnabled: this.enableCustomEnable,
          value: this.customEnable,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: '滑轨高度(vp)',
          isEnabled: this.enableCompHeight,
          value: this.compHeight,
          min: -5,
          max: 200
        })

        SliderBlock({
          title: '滑轨宽度(vp)',
          isEnabled: this.enableCustomWidth,
          value: this.customWidth,
          min: -5,
          max: 200
        })

        SliderBlock({
          title: '滑块半径(vp)',
          isEnabled: this.enableCustomPointRadius,
          value: this.customPointRadius,
          min: -5,
          max: 200
        })

        SliderBlock({
          title: '滑轨圆角(vp)',
          isEnabled: this.enableCustomTrackBorderRadius,
          value: this.customTrackBorderRadius,
          min: -5,
          max: 200
        })

        ColorBlock({
          title: '滑块颜色',
          isEnabled: this.enableCustomPointColor,
          color: this.customPointColor
        })

        ColorBlock({
          title: '未选中时滑轨颜色',
          isEnabled: this.enableCustomUnselectedColor,
          color: this.customUnselectedColor
        })

        ColorBlock({
          title: '选中时滑轨颜色',
          isEnabled: this.enableCustomSelectedColor,
          color: this.customSelectedColor
        })
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct ToggleBootcampPreviewer {
  build() {
    ToggleBootcamp({
      title: '切换按钮/Toggle'
    })
  }
}