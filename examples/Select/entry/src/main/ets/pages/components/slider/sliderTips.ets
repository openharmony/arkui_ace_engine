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

import { ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);

@Builder
export function SliderTipsBuilder(name: string, param: Object) {
  SliderTipsExample()
}

@Entry
@Component
struct SliderTipsExample {
  pathStack: NavPathStack = new NavPathStack()
  
  // 基础滑动条状态变量
  @State sliderValue1: number = 50
  @State sliderValue2: number = 40
  @State sliderValue3: number = 60
  @State sliderValue4: number = 30
  @State sliderValue5: number = 70
  @State sliderValue6: number = 25
  @State sliderValue7: number = 75
  @State sliderValue8: number = 45
  @State sliderValue9: number = 55
  @State sliderValue10: number = 35
  @State sliderValue11: number = 65
  @State sliderValue12: number = 20
  @State sliderValue13: number = 80
  @State sliderValue14: number = 40
  @State sliderValue15: number = 60
  @State sliderValue16: number = 50
  @State sliderValue17: number = 50
  @State sliderValue18: number = 50
  @State sliderValue19: number = 50
  @State sliderValue20: number = 50
  
  // 垂直滑动条状态变量
  @State vSliderValue1: number = 50
  @State vSliderValue2: number = 40
  @State vSliderValue3: number = 30
  @State vSliderValue4: number = 60
  
  // 提示内容状态
  @State tipContent: string = '当前值'

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          // 标题部分
          Text('Slider ShowTips 综合示例')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })
            .width('100%')
            .textAlign(TextAlign.Center)

          Text('showTips API 用于显示滑动时的气泡提示，支持自定义内容')
            .fontSize(12)
            .fontColor(0x666666)
            .width('90%')
            .margin({ bottom: 10 })

          // ==================== 第一部分：基础用法 ====================
          Divider()
          Text('一、基础用法')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          // 示例1：不显示提示
          Column({ space: 10 }) {
            Text('示例1：不显示提示 (showTips: false)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('默认情况下不显示气泡提示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue1,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockColor('#4169E1')
              .selectedColor('#4169E1')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue1 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue1.toFixed(0))
                .fontSize(12)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF8F9FA)
          .borderRadius(10)

          // 示例2：显示默认提示
          Column({ space: 10 }) {
            Text('示例2：显示默认提示 (showTips: true)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('显示当前百分比的气泡提示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue2,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockColor('#32CD32')
              .selectedColor('#32CD32')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue2 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue2.toFixed(0))
                .fontSize(12)
                .fontColor('#32CD32')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // 示例3：显示自定义提示
          Column({ space: 10 }) {
            Text('示例3：显示自定义提示')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('使用content参数设置自定义提示内容')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue3,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockColor('#FF1493')
              .selectedColor('#FF1493')
              .showTips(true, '音量: ' + this.sliderValue3.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue3 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue3.toFixed(0))
                .fontSize(12)
                .fontColor('#FF1493')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF0F5)
          .borderRadius(10)

          // ==================== 第二部分：与blockColor组合 ====================
          Divider()
          Text('二、与blockColor属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例4：showTips + blockColor')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('气泡提示配合自定义滑块颜色')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue4,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockColor('#FFD700')
              .selectedColor('#FFD700')
              .showTips(true, '亮度: ' + this.sliderValue4.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue4 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue4.toFixed(0))
                .fontSize(12)
                .fontColor('#FFD700')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第三部分：与blockSize组合 ====================
          Divider()
          Text('三、与blockSize属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例5：showTips + blockSize')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('气泡提示配合自定义滑块大小')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue5,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockSize({ width: 24, height: 24 })
              .blockColor('#9370DB')
              .selectedColor('#9370DB')
              .showTips(true, '饱和度: ' + this.sliderValue5.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue5 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue5.toFixed(0))
                .fontSize(12)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第四部分：与blockBorder组合 ====================
          Divider()
          Text('四、与blockBorderWidth/blockBorderColor组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例6：showTips + blockBorder')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('气泡提示配合滑块边框')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue6,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#20B2AA')
              .blockBorderWidth(2)
              .selectedColor('#20B2AA')
              .showTips(true, '对比度: ' + this.sliderValue6.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue6 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue6.toFixed(0))
                .fontSize(12)
                .fontColor('#20B2AA')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第五部分：与trackThickness组合 ====================
          Divider()
          Text('五、与trackThickness属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例7：showTips + trackThickness')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('气泡提示配合自定义滑轨粗细')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue7,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(12)
              .blockColor('#FF6347')
              .selectedColor('#FF6347')
              .showTips(true, '温度: ' + this.sliderValue7.toFixed(0) + '°C')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue7 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue7.toFixed(0))
                .fontSize(12)
                .fontColor('#FF6347')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第六部分：与showSteps组合 ====================
          Divider()
          Text('六、与showSteps属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例8：showTips + showSteps')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('气泡提示配合刻度显示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue8,
              min: 0,
              max: 100,
              step: 10,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockColor('#00CED1')
              .selectedColor('#00CED1')
              .showSteps(true)
              .stepSize(8)
              .stepColor('#00CED1')
              .showTips(true, '速度: ' + this.sliderValue8.toFixed(0) + ' km/h')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue8 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue8.toFixed(0))
                .fontSize(12)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第七部分：与direction组合 ====================
          Divider()
          Text('七、与direction属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例9：showTips + direction (垂直)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('垂直滑动条配合气泡提示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 20 }) {
              Slider({
                style: SliderStyle.OutSet,
                value: this.vSliderValue1,
                min: 0,
                max: 100,
                direction: Axis.Vertical
              })
                .height(200)
                .blockColor('#FF69B4')
                .selectedColor('#FF69B4')
                .showTips(true, '音量: ' + this.vSliderValue1.toFixed(0) + '%')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue1 = value
                })

              Slider({
                style: SliderStyle.InSet,
                value: this.vSliderValue2,
                min: 0,
                max: 100,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(200)
                .blockColor('#32CD32')
                .selectedColor('#32CD32')
                .showTips(true, '亮度: ' + this.vSliderValue2.toFixed(0) + '%')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue2 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF0F5)
          .borderRadius(10)

          // ==================== 第八部分：与trackColor/selectedColor组合 ====================
          Divider()
          Text('八、与trackColor/selectedColor组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例10：showTips + trackColor + selectedColor')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('气泡提示配合自定义滑轨颜色')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue9,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackColor('#E0E0E0')
              .selectedColor('#FF4500')
              .blockColor('#FF4500')
              .showTips(true, '饱和度: ' + this.sliderValue9.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue9 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue9.toFixed(0))
                .fontSize(12)
                .fontColor('#FF4500')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFE4)
          .borderRadius(10)

          // ==================== 第九部分：综合示例1 - 音量调节 ====================
          Divider()
          Text('九、综合示例 - 音量调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例11：音量调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟音量调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('🔊')
                .fontSize(20)
              Slider({
                style: SliderStyle.OutSet,
                value: this.sliderValue10,
                min: 0,
                max: 100,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#32CD32')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#32CD32')
                .showTips(true, '音量: ' + this.sliderValue10.toFixed(0) + '%')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue10 = value
                })
              Text(this.sliderValue10.toFixed(0) + '%')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#32CD32')
                .width(50)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // ==================== 第十部分：综合示例2 - 亮度调节 ====================
          Divider()
          Text('十、综合示例 - 亮度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例12：亮度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟亮度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('☀️')
                .fontSize(20)
              Slider({
                style: SliderStyle.InSet,
                value: this.sliderValue11,
                min: 0,
                max: 100,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(36)
                .trackBorderRadius(18)
                .selectedBorderRadius(18)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FFD700')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FFD700')
                .showTips(true, '亮度: ' + this.sliderValue11.toFixed(0) + '%')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue11 = value
                })
              Text(this.sliderValue11.toFixed(0) + '%')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FFD700')
                .width(50)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第十一部分：综合示例3 - 温度调节 ====================
          Divider()
          Text('十一、综合示例 - 温度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例13：温度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟温度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('❄️')
                .fontSize(20)
              Slider({
                style: SliderStyle.OutSet,
                value: this.sliderValue12,
                min: 0,
                max: 100,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 22, height: 22 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#00CED1')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#00CED1')
                .showTips(true, '温度: ' + this.sliderValue12.toFixed(0) + '°C')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue12 = value
                })
              Text('🔥')
                .fontSize(20)
            }
            .width('100%')

            Row() {
              Text('温度: ')
                .fontSize(12)
              Text(this.sliderValue12.toFixed(0) + '°C')
                .fontSize(14)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第十二部分：综合示例4 - 速度控制 ====================
          Divider()
          Text('十二、综合示例 - 速度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例14：速度控制滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟速度控制场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('🚀')
                .fontSize(20)
              Slider({
                style: SliderStyle.InSet,
                value: this.sliderValue13,
                min: 0,
                max: 100,
                step: 5,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(36)
                .trackBorderRadius(18)
                .selectedBorderRadius(18)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF6347')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF6347')
                .showSteps(true)
                .stepSize(6)
                .stepColor('#FF6347')
                .showTips(true, '速度: ' + this.sliderValue13.toFixed(0) + ' km/h')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue13 = value
                })
              Text(this.sliderValue13.toFixed(0) + ' km/h')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FF6347')
                .width(80)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第十三部分：综合示例5 - 饱和度调节 ====================
          Divider()
          Text('十三、综合示例 - 饱和度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例15：饱和度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟饱和度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue14,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 24, height: 24 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#9370DB')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#9370DB')
              .showTips(true, '饱和度: ' + this.sliderValue14.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue14 = value
              })

            Row() {
              Text('饱和度: ')
                .fontSize(12)
              Text(this.sliderValue14.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第十四部分：综合示例6 - 对比度调节 ====================
          Divider()
          Text('十四、综合示例 - 对比度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例16：对比度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟对比度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue15,
              min: 0,
              max: 100,
              step: 10,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(36)
              .trackBorderRadius(18)
              .selectedBorderRadius(18)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#4169E1')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#4169E1')
              .showSteps(true)
              .stepSize(8)
              .stepColor('#4169E1')
              .showTips(true, '对比度: ' + this.sliderValue15.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue15 = value
              })

            Row() {
              Text('对比度: ')
                .fontSize(12)
              Text(this.sliderValue15.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // ==================== 第十五部分：综合示例7 - 缩放控制 ====================
          Divider()
          Text('十五、综合示例 - 缩放控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例17：缩放控制滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟缩放控制场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('🔍')
                .fontSize(20)
              Slider({
                style: SliderStyle.OutSet,
                value: this.sliderValue16,
                min: 0,
                max: 100,
                step: 25,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 18, height: 18 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF69B4')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF69B4')
                .showSteps(true)
                .stepSize(6)
                .stepColor('#FF69B4')
                .showTips(true, '缩放: ' + this.getZoomText())
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue16 = value
                })
              Text(this.getZoomText())
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FF69B4')
                .width(60)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF0F5)
          .borderRadius(10)

          // ==================== 第十六部分：综合示例8 - 透明度调节 ====================
          Divider()
          Text('十六、综合示例 - 透明度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例18：透明度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟透明度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue17,
              min: 0,
              max: 100,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(36)
              .trackBorderRadius(18)
              .selectedBorderRadius(18)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#FFD700')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#FFD700')
              .showTips(true, '透明度: ' + this.sliderValue17.toFixed(0) + '%')
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue17 = value
              })

            Row() {
              Text('透明度: ')
                .fontSize(12)
              Text(this.sliderValue17.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#FFD700')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第十七部分：综合示例9 - 垂直进度条 ====================
          Divider()
          Text('十七、综合示例 - 垂直进度条')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例19：垂直进度条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，垂直进度条场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 30 }) {
              Slider({
                style: SliderStyle.OutSet,
                value: this.vSliderValue3,
                min: 0,
                max: 100,
                step: 10,
                direction: Axis.Vertical
              })
                .height(180)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#32CD32')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#32CD32')
                .showSteps(true)
                .stepSize(8)
                .stepColor('#32CD32')
                .showTips(true, '进度: ' + this.vSliderValue3.toFixed(0) + '%')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue3 = value
                })

              Slider({
                style: SliderStyle.InSet,
                value: this.vSliderValue4,
                min: 0,
                max: 100,
                step: 10,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(180)
                .trackThickness(36)
                .trackBorderRadius(18)
                .selectedBorderRadius(18)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF6347')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF6347')
                .showSteps(true)
                .stepSize(8)
                .stepColor('#FF6347')
                .showTips(true, '进度: ' + this.vSliderValue4.toFixed(0) + '%')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue4 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // ==================== 第十八部分：综合示例10 - 频率调节 ====================
          Divider()
          Text('十八、综合示例 - 频率调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例20：频率调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟频率调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('🎵')
                .fontSize(20)
              Slider({
                style: SliderStyle.OutSet,
                value: this.sliderValue18,
                min: 0,
                max: 100,
                step: 10,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#9370DB')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#9370DB')
                .showSteps(true)
                .stepSize(8)
                .stepColor('#9370DB')
                .showTips(true, '频率: ' + this.sliderValue18.toFixed(0) + 'Hz')
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue18 = value
                })
              Text(this.sliderValue18.toFixed(0) + 'Hz')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#9370DB')
                .width(60)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第十九部分：综合示例11 - 增益调节 ====================
          Divider()
          Text('十九、综合示例 - 增益调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例21：增益调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟增益调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('📊')
                .fontSize(20)
              Slider({
                style: SliderStyle.InSet,
                value: this.sliderValue19,
                min: 0,
                max: 100,
                step: 10,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(36)
                .trackBorderRadius(18)
                .selectedBorderRadius(18)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#00CED1')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#00CED1')
                .showSteps(true)
                .stepSize(8)
                .stepColor('#00CED1')
                .showTips(true, '增益: ' + this.getGainText())
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue19 = value
                })
              Text(this.getGainText())
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#00CED1')
                .width(60)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第二十部分：综合示例12 - 平衡调节 ====================
          Divider()
          Text('二十、综合示例 - 平衡调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例22：平衡调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟平衡调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue20,
              min: 0,
              max: 100,
              step: 10,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#FF69B4')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#FF69B4')
              .showSteps(true)
              .stepSize(8)
              .stepColor('#FF69B4')
              .showTips(true, '平衡: ' + this.getBalanceText())
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue20 = value
              })

            Row() {
              Text('平衡: ')
                .fontSize(12)
              Text(this.getBalanceText())
                .fontSize(14)
                .fontColor('#FF69B4')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF0F5)
          .borderRadius(10)

          // 底部说明
          Divider()
          Text('说明')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 8 }) {
            Text('• showTips用于控制是否显示气泡提示')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• content参数可设置自定义提示内容')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 水平滑动条时，tip显示在滑块上方')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 垂直滑动条时，tip显示在滑块左边')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 可与其他Slider属性组合使用')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 支持水平、垂直滑动条')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 增强用户体验和交互反馈')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF8F8F8)
          .borderRadius(10)
          .margin({ bottom: 20 })
        }
        .width('100%')
        .padding({ left: 15, right: 15 })
      }
    }
    .title('SliderTips')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }

  // 获取缩放文本
  getZoomText(): string {
    if (this.sliderValue16 <= 25) {
      return '25%'
    } else if (this.sliderValue16 <= 50) {
      return '50%'
    } else if (this.sliderValue16 <= 75) {
      return '75%'
    } else {
      return '125%'
    }
  }

  // 获取增益文本
  getGainText(): string {
    let gain = (this.sliderValue19 - 50) * 0.24
    return gain.toFixed(1) + 'dB'
  }

  // 获取平衡文本
  getBalanceText(): string {
    let balance = (this.sliderValue20 - 50) * 2
    if (balance === 0) {
      return 'C'
    } else if (balance > 0) {
      return 'R' + balance.toFixed(0)
    } else {
      return 'L' + Math.abs(balance).toFixed(0)
    }
  }
}

export { SliderTipsExample };