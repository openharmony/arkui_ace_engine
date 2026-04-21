/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with License.
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

import { ColorMetrics, ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);

@Builder
export function SliderTrackColorMetricsBuilder(name: string, param: Object) {
  SliderTrackColorMetricsExample()
}

@Entry
@Component
struct SliderTrackColorMetricsExample {
  pathStack: NavPathStack = new NavPathStack()
  
  // 基础滑动条状态变量
  @State sliderValue1: number = 50
  @State sliderValue2: number = 30
  @State sliderValue3: number = 70
  @State sliderValue4: number = 60
  @State sliderValue5: number = 40
  @State sliderValue6: number = 80
  @State sliderValue7: number = 20
  @State sliderValue8: number = 90
  @State sliderValue9: number = 55
  @State sliderValue10: number = 35
  @State sliderValue11: number = 65
  @State sliderValue12: number = 45
  @State sliderValue13: number = 75
  @State sliderValue14: number = 25
  @State sliderValue15: number = 85
  @State sliderValue16: number = 15
  @State sliderValue17: number = 95
  @State sliderValue18: number = 50
  @State sliderValue19: number = 50
  @State sliderValue20: number = 50
  
  // 垂直滑动条状态变量
  @State vSliderValue1: number = 50
  @State vSliderValue2: number = 30
  @State vSliderValue3: number = 70
  @State vSliderValue4: number = 60
  
  // 交互模式状态变量
  @State interactionMode: SliderInteraction = SliderInteraction.SLIDE_AND_CLICK
  @State minDistance: number = 0
  @State hapticEnabled: boolean = true
  
  // 滑动范围状态变量
  @State slideFrom: number = 20
  @State slideTo: number = 80

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          // 标题部分
          Text('API 23 Slider TrackColorMetrics 综合示例')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })
            .width('100%')
            .textAlign(TextAlign.Center)

          Text('trackColorMetrics API 23 新增功能，支持设置滑轨轨道的线性渐变背景颜色')
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

          // 示例1：双色渐变
          Column({ space: 10 }) {
            Text('示例1：双色线性渐变 (蓝色到紫色)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('使用ColorMetrics.numeric()创建颜色，offset范围0-1')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue1,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x0000FF), offset: 0 },    // 蓝色
                { color: ColorMetrics.numeric(0x800080), offset: 1 }     // 紫色
              ]))
              .selectedColor('#FF6B6B')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue1 = value
                console.info('slider1 value:' + value + ' mode:' + mode.toString())
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue1.toFixed(0))
                .fontSize(12)
                .fontColor('#FF6B6B')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF8F9FA)
          .borderRadius(10)

          // 示例2：多色渐变
          Column({ space: 10 }) {
            Text('示例2：多色线性渐变 (红-黄-绿)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('支持多个颜色断点，创建平滑的多色渐变效果')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue2,
              min: 0,
              max: 100,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0xFF6B6B), offset: 0 },    // 红色
                { color: ColorMetrics.numeric(0xFFD93D), offset: 0.5 },  // 黄色
                { color: ColorMetrics.numeric(0x6BCB77), offset: 1 }     // 绿色
              ]))
              .selectedColor('#4169E1')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue2 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue2.toFixed(0))
                .fontSize(12)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF8F9FA)
          .borderRadius(10)

          // ==================== 第二部分：与blockColor组合 ====================
          Divider()
          Text('二、与blockColor属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例3：trackColorMetrics + blockColor')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('渐变滑轨配合自定义滑块颜色，增强视觉效果')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue3,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x00CED1), offset: 0 },    // 青色
                { color: ColorMetrics.numeric(0x191970), offset: 1 }     // 深蓝色
              ]))
              .blockColor('#FF1493')                                      // 粉红色滑块
              .selectedColor('#FF69B4')
              .showTips(true)
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

          // ==================== 第三部分：与blockSize组合 ====================
          Divider()
          Text('三、与blockSize属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例4：trackColorMetrics + blockSize')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('自定义滑块大小，配合渐变滑轨')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue4,
              min: 0,
              max: 100,
              step: 20,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x32CD32), offset: 0 },    // 绿色
                { color: ColorMetrics.numeric(0xFFD700), offset: 0.6 },  // 金色
                { color: ColorMetrics.numeric(0xFF4500), offset: 1 }     // 橙红色

              ]))
              .blockSize({ width: 30, height: 30 })                        // 自定义滑块大小
              .blockColor('#9370DB')
              .selectedColor('#9370DB')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue4 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue4.toFixed(0))
                .fontSize(12)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // ==================== 第四部分：与blockBorder组合 ====================
          Divider()
          Text('四、与blockBorderWidth/blockBorderColor组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例5：trackColorMetrics + blockBorder')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('滑块边框颜色和粗细，配合渐变滑轨')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue5,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x4169E1), offset: 0 },    // 蓝色
                { color: ColorMetrics.numeric(0xFF6347), offset: 1 }     // 番茄色
              ]))
              .blockSize({ width: 24, height: 24 })
              .blockColor('#FFFFFF')                                      // 白色滑块
              .blockBorderColor('#FF4500')                                // 橙红色边框
              .blockBorderWidth(3)                                        // 边框粗细
              .selectedColor('#FF6347')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue5 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue5.toFixed(0))
                .fontSize(12)
                .fontColor('#FF4500')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第五部分：与trackThickness组合 ====================
          Divider()
          Text('五、与trackThickness属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例6：trackColorMetrics + trackThickness')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('自定义滑轨粗细，配合渐变背景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue6,
              min: 0,
              max: 100,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(8)                                            // 滑轨粗细
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x20B2AA), offset: 0 },    // 深青色
                { color: ColorMetrics.numeric(0xFF1493), offset: 1 }     // 深粉色
              ]))
              .blockColor('#FFD700')
              .selectedColor('#FF1493')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue6 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue6.toFixed(0))
                .fontSize(12)
                .fontColor('#FF1493')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第六部分：与trackBorderRadius组合 ====================
          Divider()
          Text('六、与trackBorderRadius/selectedBorderRadius组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例7：trackColorMetrics + borderRadius')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('滑轨和已滑动部分的圆角设置')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue7,
              min: 0,
              max: 100,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(12)
              .trackBorderRadius(6)                                      // 滑轨圆角
              .selectedBorderRadius(6)                                   // 已滑动部分圆角
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x9370DB), offset: 0 },    // 紫色
                { color: ColorMetrics.numeric(0x00CED1), offset: 1 }     // 青色
              ]))
              .blockColor('#FF6347')
              .selectedColor('#00CED1')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue7 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue7.toFixed(0))
                .fontSize(12)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // ==================== 第七部分：与step相关属性组合 ====================
          Divider()
          Text('七、与step/stepColor/stepSize组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例8：trackColorMetrics + step属性')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('步长、刻度颜色和刻度大小配合渐变滑轨')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue8,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0xFF8C00), offset: 0 },    // 深橙色
                { color: ColorMetrics.numeric(0x32CD32), offset: 1 }     // 绿色
              ]))
              .blockColor('#FF4500')
              .selectedColor('#32CD32')
              .showSteps(true)
              .stepColor('#FFD700')                                     // 刻度颜色
              .stepSize(6)                                               // 刻度大小
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue8 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue8.toFixed(0))
                .fontSize(12)
                .fontColor('#32CD32')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFE4)
          .borderRadius(10)

          // ==================== 第八部分：与direction组合 ====================
          Divider()
          Text('八、与direction属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例9：trackColorMetrics + direction (垂直)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('垂直滑动条配合渐变滑轨')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 20 }) {
              Slider({
                value: this.vSliderValue1,
                min: 0,
                max: 100,
                style: SliderStyle.OutSet,
                direction: Axis.Vertical
              })
                .height(200)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x00CED1), offset: 0 },    // 青色
                  { color: ColorMetrics.numeric(0x191970), offset: 1 }     // 深蓝色
                ]))
                .blockColor('#FF1493')
                .selectedColor('#FF1493')
                .showTips(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue1 = value
                })

              Slider({
                value: this.vSliderValue2,
                min: 0,
                max: 100,
                step: 20,
                style: SliderStyle.InSet,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(200)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0xFF6B6B), offset: 0 },    // 红色
                  { color: ColorMetrics.numeric(0x6BCB77), offset: 1 }     // 绿色
                ]))
                .blockColor('#4169E1')
                .selectedColor('#4169E1')
                .showSteps(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue2 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第九部分：与sliderInteractionMode组合 ====================
          Divider()
          Text('九、与sliderInteractionMode组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例10：trackColorMetricsMetrics + sliderInteractionMode')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('交互模式：' + this.getInteractionModeText())
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 10 }) {
              Button('滑动+点击')
                .fontSize(11)
                .onClick(() => {
                  this.interactionMode = SliderInteraction.SLIDE_AND_CLICK
                })
              Button('仅滑动')
                .fontSize(11)
                .onClick(() => {
                  this.interactionMode = SliderInteraction.SLIDE_ONLY
                })
              Button('滑动+点击抬起')
                .fontSize(11)
                .onClick(() => {
                  this.interactionMode = SliderInteraction.SLIDE_AND_CLICK_UP
                })
            }

            Slider({
              value: this.sliderValue9,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x1E90FF), offset: 0 },    // 道奇蓝
                { color: ColorMetrics.numeric(0xFF69B4), offset: 1 }     // 热粉色
              ]))
              .blockColor('#FFD700')
              .selectedColor('#FF69B4')
              .showTips(true)
              .sliderInteractionMode(this.interactionMode)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue9 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue9.toFixed(0))
                .fontSize(12)
                .fontColor('#FF69B4')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5EE)
          .borderRadius(10)

          // ==================== 第十部分：与minResponsiveDistance组合 ====================
          Divider()
          Text('十、与minResponsiveDistance组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例11：trackColorMetrics + minResponsiveDistance')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('最小响应距离：' + this.minDistance)
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 10 }) {
              Button('距离0')
                .fontSize(11)
                .onClick(() => {
                  this.minDistance = 0
                })
              Button('距离5')
                .fontSize(11)
                .onClick(() => {
                  this.minDistance = 5
                })
              Button('距离10')
                .fontSize(11)
                .onClick(() => {
                  this.minDistance = 10
                })
            }

            Slider({
              value: this.sliderValue10,
              min: 0,
              max: 100,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x9370DB), offset: 0 },    // 紫色
                { color: ColorMetrics.numeric(0x20B2AA), offset: 1 }     // 深青色
              ]))
              .blockColor('#FF6347')
              .selectedColor('#20B2AA')
              .showTips(true)
              .minResponsiveDistance(this.minDistance)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue10 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue10.toFixed(0))
                .fontSize(12)
                .fontColor('#20B2AA')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF8F8FF)
          .borderRadius(10)

          // ==================== 第十一部分：与slideRange组合 ====================
          Divider()
          Text('十一、与slideRange组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例12：trackColorMetrics + slideRange')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('有效滑动区间：' + this.slideFrom + ' - ' + this.slideTo)
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 10 }) {
              Button('20-80')
                .fontSize(11)
                .onClick(() => {
                  this.slideFrom = 20
                  this.slideTo = 80
                })
              Button('30-70')
                .fontSize(11)
                .onClick(() => {
                  this.slideFrom = 30
                  this.slideTo = 70
                })
              Button('40-60')
                .fontSize(11)
                .onClick(() => {
                  this.slideFrom = 40
                  this.slideTo = 60
                })
            }

            Slider({
              value: this.sliderValue11,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0xFF8C00), offset: 0 },    // 深橙色
                { color: ColorMetrics.numeric(0x00CED1), offset: 1 }     // 青色
              ]))
              .blockColor('#FF4500')
              .selectedColor('#00CED1')
              .showSteps(true)
              .slideRange({ from: this.slideFrom, to: this.slideTo })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue11 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue11.toFixed(0))
                .fontSize(12)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF8)
          .borderRadius(10)

          // ==================== 第十二部分：综合示例1 ====================
          Divider()
          Text('十二、综合示例 - 音量调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例13：音量调节滑动条')
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
                value: this.sliderValue12,
                min: 0,
                max: 100,
                style: SliderStyle.OutSet
              })
                .layoutWeight(1)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x32CD32), offset: 0 },    // 绿色
                  { color: ColorMetrics.numeric(0xFFD700), offset: 0.7 },  // 金色
                  { color: ColorMetrics.numeric(0xFF4500), offset: 1 }     // 橙红色
                ]))
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF4500')
                .blockBorderWidth(2)
                .selectedColor('#FFD700')
                .showTips(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue12 = value
                })
              Text(this.sliderValue12.toFixed(0) + '%')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FF4500')
                .width(50)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // ==================== 第十三部分：综合示例2 ====================
          Divider()
          Text('十三、综合示例 - 亮度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例14：亮度调节滑动条')
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
                value: this.sliderValue13,
                min: 0,
                max: 100,
                style: SliderStyle.InSet
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x191970), offset: 0 },    // 深蓝色
                  { color: ColorMetrics.numeric(0x87CEEB), offset: 0.5 },  // 天蓝色
                  { color: ColorMetrics.numeric(0xFFFF00), offset: 1 }     // 黄色
                ]))
                .blockColor('#FFFFFF')
                .blockBorderColor('#FFD700')
                .blockBorderWidth(2)
                .selectedColor('#FFFF00')
                .showTips(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue13 = value
                })
              Text(this.sliderValue13.toFixed(0) + '%')
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

          // ==================== 第十四部分：综合示例3 ====================
          Divider()
          Text('十四、综合示例 - 进度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例15：进度控制滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟进度控制场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue14,
              min: 0,
              max: 100,
              step: 5,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x4169E1), offset: 0 },    // 蓝色
                { color: ColorMetrics.numeric(0x9370DB), offset: 1 }     // 紫色
              ]))
              .blockSize({ width: 18, height: 18 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#9370DB')
              .blockBorderWidth(2)
              .selectedColor('#9370DB')
              .showSteps(true)
              .stepColor('#9370DB')
              .stepSize(4)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue14 = value
              })

            Row() {
              Text('进度: ')
                .fontSize(12)
              Text(this.sliderValue14.toFixed(0) + '%')
                .fontSize(12)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // ==================== 第十五部分：综合示例4 ====================
          Divider()
          Text('十五、综合示例 - 温度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例16：温度调节滑动条')
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
                value: this.sliderValue15,
                min: 0,
                max: 100,
                style: SliderStyle.OutSet
              })
                .layoutWeight(1)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x00CED1), offset: 0 },    // 青色
                  { color: ColorMetrics.numeric(0x32CD32), offset: 0.3 },  // 绿色
                  { color: ColorMetrics.numeric(0xFFD700), offset: 0.6 },  // 金色
                  { color: ColorMetrics.numeric(0xFF4500), offset: 1 }     // 橙红色
                ]))
                .blockSize({ width: 22, height: 22 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF4500')
                .blockBorderWidth(2)
                .selectedColor('#FF4500')
                .showTips(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue15 = value
                })
              Text('🔥')
                .fontSize(20)
            }
            .width('100%')

            Row() {
              Text('温度: ')
                .fontSize(12)
              Text(this.sliderValue15.toFixed(0) + '°C')
                .fontSize(14)
                .fontColor('#FF4500')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第十六部分：综合示例5 ====================
          Divider()
          Text('十六、综合示例 - 垂直进度条')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例17：垂直进度条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，垂直进度条场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 30 }) {
              Slider({
                value: this.vSliderValue3,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.OutSet,
                direction: Axis.Vertical
              })
                .height(180)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x9370DB), offset: 0 },    // 紫色
                  { color: ColorMetrics.numeric(0x20B2AA), offset: 1 }     // 深青色
                ]))
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#20B2AA')
                .blockBorderWidth(2)
                .selectedColor('#20B2AA')
                .showSteps(true)
                .stepColor('#20B2AA')
                .stepSize(5)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue3 = value
                })

              Slider({
                value: this.vSliderValue4,
                min: 0,
                max: 100,
                step: 20,
                style: SliderStyle.InSet,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(180)
                .trackThickness(12)
                .trackBorderRadius(6)
                .selectedBorderRadius(6)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0xFF6B6B), offset: 0 },    // 红色
                  { color: ColorMetrics.numeric(0x6BCB77), offset: 1 }     // 绿色
                ]))
                .blockColor('#FFFFFF')
                .blockBorderColor('#6BCB77')
                .blockBorderWidth(2)
                .selectedColor('#6BCB77')
                .showSteps(true)
                .stepColor('#6BCB77')
                .stepSize(6)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue4 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第十七部分：综合示例6 ====================
          Divider()
          Text('十七、综合示例 - 速度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例18：速度控制滑动条')
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
                value: this.sliderValue16,
                min: 0,
                max: 100,
                step: 5,
                style: SliderStyle.OutSet
              })
                .layoutWeight(1)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x32CD32), offset: 0 },    // 绿色
                  { color: ColorMetrics.numeric(0xFFD700), offset: 0.5 },  // 金色
                  { color: ColorMetrics.numeric(0xFF4500), offset: 1 }     // 橙红色
                ]))
                .blockSize({ width: 16, height: 16 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF4500')
                .blockBorderWidth(2)
                .selectedColor('#FFD700')
                .showSteps(true)
                .stepColor('#FFD700')
                .stepSize(5)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue16 = value
                })
              Text(this.sliderValue16.toFixed(0) + ' km/h')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FF4500')
                .width(80)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFE4)
          .borderRadius(10)

          // ==================== 第十八部分：综合示例7 ====================
          Divider()
          Text('十八、综合示例 - 饱和度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例19：饱和度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟饱和度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue17,
              min: 0,
              max: 100,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(14)
              .trackBorderRadius(7)
              .selectedBorderRadius(7)
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x808080), offset: 0 },    // 灰色
                { color: ColorMetrics.numeric(0xFF6347), offset: 1 }     // 番茄色
              ]))
              .blockSize({ width: 24, height: 24 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#FF6347')
              .blockBorderWidth(3)
              .selectedColor('#FF6347')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue17 = value
              })

            Row() {
              Text('饱和度: ')
                .fontSize(12)
              Text(this.sliderValue17.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#FF6347')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第十九部分：综合示例8 ====================
          Divider()
          Text('十九、综合示例 - 对比度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例20：对比度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟对比度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue18,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0x000000), offset: 0 },    // 黑色
                { color: ColorMetrics.numeric(0x808080), offset: 0.5 },  // 灰色
                { color: ColorMetrics.numeric(0xFFFFFF), offset: 1 }     // 白色
              ]))
              .blockSize({ width: 20, height: 20 })
              .blockColor('#4169E1')
              .selectedColor('#4169E1')
              .showSteps(true)
              .stepColor('#4169E1')
              .stepSize(6)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue18 = value
              })

            Row() {
              Text('对比度: ')
                .fontSize(12)
              Text(this.sliderValue18.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F0F0)
          .borderRadius(10)

          // ==================== 第二十部分：综合示例9 ====================
          Divider()
          Text('二十、综合示例 - 缩放控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例21：缩放控制滑动条')
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
                value: this.sliderValue19,
                min: 0,
                max: 100,
                step: 25,
                style: SliderStyle.OutSet
              })
                .layoutWeight(1)
                .trackColorMetrics(new ColorMetricsLinearGradient([
                  { color: ColorMetrics.numeric(0x9370DB), offset: 0 },    // 紫色
                  { color: ColorMetrics.numeric(0x00CED1), offset: 1 }     // 青色
                ]))
                .blockSize({ width: 18, height: 18 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#00CED1')
                .blockBorderWidth(2)
                .selectedColor('#00CED1')
                .showSteps(true)
                .stepColor('#00CED1')
                .stepSize(5)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue19 = value
                })
              Text(this.getZoomText())
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

          // ==================== 第二十一部分：综合示例10 ====================
          Divider()
          Text('二十一、综合示例 - 透明度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例22：透明度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟透明度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue20,
              min: 0,
              max: 100,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(12)
              .trackBorderRadius(6)
              .selectedBorderRadius(6)
              .trackColorMetrics(new ColorMetricsLinearGradient([
                { color: ColorMetrics.numeric(0xFFFFFF), offset: 0 },    // 白色
                { color: ColorMetrics.numeric(0x4169E1), offset: 1 }     // 蓝色
              ]))
              .blockSize({ width: 22, height: 22 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#4169E1')
              .blockBorderWidth(2)
              .selectedColor('#4169E1')
              .showTips(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue20 = value
              })

            Row() {
              Text('透明度: ')
                .fontSize(12)
              Text(this.sliderValue20.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // 底部说明
          Divider()
          Text('说明')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 8 }) {
            Text('• trackColorMetrics是API 23新增功能')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 使用ColorMetricsLinearGradient创建线性渐变')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 颜色使用ColorMetrics.numeric()创建')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• offset范围0-1，表示渐变位置')
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
    .title('SliderTrackColorMetrics')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }

  // 获取交互模式文本
  getInteractionModeText(): string {
    switch (this.interactionMode) {
      case SliderInteraction.SLIDE_AND_CLICK:
        return '滑动+点击'
      case SliderInteraction.SLIDE_ONLY:
        return '仅滑动'
      case SliderInteraction.SLIDE_AND_CLICK_UP:
        return '滑动+点击抬起'
      default:
        return '未知'
    }
  }

  // 获取缩放文本
  getZoomText(): string {
    if (this.sliderValue19 <= 25) {
      return '25%'
    } else if (this.sliderValue19 <= 50) {
      return '50%'
    } else if (this.sliderValue19 <= 75) {
      return '75%'
    } else {
      return '100%'
    }
  }
}