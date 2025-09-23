/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

@Entry
@Component
struct ProgressCapsuleStyleTest04 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Column({ space: 15 }) {
      Row() {
        Text('CapsuleStyleOptions.fontColor属性测试')
          .fontSize(16)
          .fontColor(0x000000)
          .textAlign(TextAlign.Start)
          .fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)
      .margin({ bottom: 10 })

      Row() {
        Button('ChangeDarkMode').backgroundColor(0x7B68EE).width(180).height(30)
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

      Text('fontColor不设置').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('fontColor ResourceColor:Color').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .style({
            content: 'Installing...'
          })
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .style({
            content: 'Installing...',
            fontColor: Color.Blue,
          })
      }

      Text('fontColor ResourceColor:Number').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('fontColor ResourceColor:#ffffff').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .style({
            content: 'Installing...',
            fontColor: 0xffa500,
          })
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .style({
            content: 'Installing...',
            fontColor: '#564af7',
          })
      }

      Text('fontColor ResourceColor:rgb').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('fontColor ResourceColor:rgba').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .style({
            content: 'Installing...',
            fontColor: 'rgb(255,165,0)',
          })
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .style({
            content: 'Installing...',
            fontColor: 'rgba(255,165,0,0.8)',
          })
      }

      Text('fontColor ResourceColor:$r引入应用资源$r("app.color.ColorBlue")')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('90%')
      Text('fontColor ResourceColor:$r引入系统资源$r("sys.color.ohos_id_color_component_activated")')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .style({
            content: 'Installing...',
            fontColor: $r('app.color.ColorBlue')
          })
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .style({
            content: 'Installing...',
            fontColor: $r('sys.color.ohos_id_color_component_activated')
          })
      }

      Text('fontColor undefined').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('fontColor null').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .style({
            content: 'Installing...',
            fontColor: undefined,
          })
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .style({
            content: 'Installing...',
            fontColor: null,
          })
      }
    }.width('100%').margin({ top: 30 })
  }
}