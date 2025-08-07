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

import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

@Entry
@Component
struct GaugeIndicatorIconTest02 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('indicator属性测试02').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Row() {
        Column({ space: 2 }) {
          Text('indicator space 不设置').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)

          Text('indicator space 10').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: 10, icon: $r('app.media.indicator') })

          Text('indicator space "10fp"').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: '10fp', icon: $r('app.media.indicator') })

          Text('indicator space "10px"').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: '10px', icon: $r('app.media.indicator') })

        }.width('50%').height('80%').alignItems(HorizontalAlign.Center)

        Column({ space: 2 }) {
          Text('indicator space "10lpx"').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: '10lpx', icon: $r('app.media.indicator') })

          Text('indicator space "10%"').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: '10%', icon: $r('app.media.indicator') })

          Text('indicator space undefined').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: undefined, icon: $r('app.media.indicator') })

          Text('indicator space null').fontSize(12).fontColor(0x696969)
          
          Gauge({ value: 50, min: 1, max: 100 })
            .colors([[new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]), 9],
              [new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]), 8],
              [new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]), 7],
              [new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]), 6],
              [new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]), 5],
              [new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]), 4],
              [new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]), 3],
              [new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]), 2],
              [new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
                1]])
            .height('20%')
            .strokeWidth(12)
            .indicator({ space: null, icon: $r('app.media.indicator') })
        }.width('50%').height('80%').alignItems(HorizontalAlign.Center)
      }
      .width('95%')
      .justifyContent(FlexAlign.Center)

      Button('ChangeDarkMode').backgroundColor(0x7B68EE).width(180).height(20)
        .onClick(() => {
          if (this.isDark) {
            this.isDark = false;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
          } else {
            this.isDark = true;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
          }
        })
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}