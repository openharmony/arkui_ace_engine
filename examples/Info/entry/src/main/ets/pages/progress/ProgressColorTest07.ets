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
struct ProgressColorTest07 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  public color01: LinearGradient =
    new LinearGradient([{ color: Color.Green, offset: 0 }, { color: Color.Orange, offset: 0.5 },
      { color: Color.Pink, offset: 1 }])
  public color02: LinearGradient = new LinearGradient([{ color: 0x008000, offset: 0 }, { color: 0xffa500, offset: 0.5 },
    { color: 0xffc0cb, offset: 1 }])
  public color03: LinearGradient =
    new LinearGradient([{ color: '#008000', offset: 0 }, { color: '#ffa500', offset: 0.5 },
      { color: '#ffc0cb', offset: 1 }])
  public color04: LinearGradient =
    new LinearGradient([{ color: '#ff008000', offset: 0 }, { color: '#ffffa500', offset: 0.5 },
      { color: '#ffffc0cb', offset: 1 }])
  public color05: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,128,0)', offset: 0 }, { color: 'rgb(255,165,0)', offset: 0.5 },
      { color: 'rgb(255,192,203)', offset: 1 }])
  public color06: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,128,0,1)', offset: 0 }, { color: 'rgba(255,165,0,1)', offset: 0.5 },
      { color: 'rgba(255,192,203,1)', offset: 1 }])
  public color07: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorGreen'), offset: 0 },
    { color: $r('app.color.ColorOrange'), offset: 0.5 }, { color: $r('app.color.ColorPink'), offset: 1 }])

  build() {
    Column({ space: 10 }) {
      Row() {
        Text('color属性测试07').fontSize(22).fontColor(0x000000).textAlign(TextAlign.Start).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)
      .margin({ bottom: 10 })

      Row() {
        Text('RingProgressLinearGradient').fontSize(9).fontColor(0xCCCCCC).width('45%')
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
      }

      Text('#ffffff/#ffffffff').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 50, type: ProgressType.Ring }).width(100).color(this.color03).style({ strokeWidth: 20 })
        Progress({ value: 50, type: ProgressType.Ring }).width(100).color(this.color04).style({ strokeWidth: 20 })
      }

      Text('rgb/rgba').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 50, type: ProgressType.Ring }).width(100).color(this.color05).style({ strokeWidth: 20 })
        Progress({ value: 50, type: ProgressType.Ring }).width(100).color(this.color06).style({ strokeWidth: 20 })
      }

      Text('$r').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 50, type: ProgressType.Ring }).width(100).color(this.color07).style({ strokeWidth: 20 })
      }
    }.width('100%').margin({ top: 30 })
  }
}