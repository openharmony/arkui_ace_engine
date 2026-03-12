/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
export function SliderShowStepsBuilder(name: string, param: Object) {
  SliderShowStepsExample()
}

@Entry
@Component
struct SliderShowStepsExample {
  pathStack: NavPathStack = new NavPathStack()
  
  // 基础滑动条状态变量
  @State sliderValue1: number = 20
  @State sliderValue2: number = 40
  @State sliderValue3: number = 60
  @State sliderValue4: number = 30
  @State sliderValue5: number = 50
  @State sliderValue6: number = 70
  @State sliderValue7: number = 25
  @State sliderValue8: number = 55
  @State sliderValue9: number = 35
  @State sliderValue10: number = 65
  @State sliderValue11: number = 45
  @State sliderValue12: number = 75
  @State sliderValue13: number = 15
  @State sliderValue14: number = 85
  @State sliderValue15: number = 40
  @State sliderValue16: number = 60
  @State slider17: number = 50
  @State slider18: number = 30
  @State slider19: number = 70
  @State slider20: number = 20
  
  // 垂直滑动条状态变量
  @State vSliderValue1: number = 40
  @State vSliderValue2: number = 60
  @State vSliderValue3: number = 30
  @State vSliderValue4: number = 50
  
  // 无障碍文本映射
  @State optionMaps1: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps2: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps3: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps4: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps5: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps6: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps7: Map<number, SliderStepItemAccessibility> = new Map()
  @State optionMaps8: Map<number, SliderStepItemAccessibility> = new Map()
  
  // 刻度大小状态
  @State stepSizeValue: number = 8
  
  // 刻度颜色状态
  @State stepColorValue: string = '#FFD700'
  
  aboutToAppear() {
    // 初始化无障碍文本映射1 - 温度刻度
    this.optionMaps1.set(0, { text: '0°C' })
    this.optionMaps1.set(20, { text: '20°C' })
    this.optionMaps1.set(40, { text: '40°C' })
    this.optionMaps1.set(60, { text: '60°C' })
    this.optionMaps1.set(80, { text: '80°C' })
    this.optionMaps1.set(100, { text: '100°C' })
    
    // 初始化无障碍文本映射2 - 音量刻度
    this.optionMaps2.set(0, { text: '静音' })
    this.optionMaps2.set(25, { text: '低音量' })
    this.optionMaps2.set(50, { text: '中音量' })
    this.optionMaps2.set(75, { text: '高音量' })
    this.optionMaps2.set(100, { text: '最大音量' })
    
    // 初始化无障碍文本映射3 - -亮度刻度
    this.optionMaps3.set(0, { text: '最暗' })
    this.optionMaps3.set(25, { text: '较暗' })
    this.optionMaps3.set(50, { text: '中等' })
    this.optionMaps3.set(75, { text: '较亮' })
    this.optionMaps3.set(100, { text: '最亮' })
    
    // 初始化无障碍文本映射4 - 速度刻度
    this.optionMaps4.set(0, { text: '停止' })
    this.optionMaps4.set(20, { text: '低速' })
    this.optionMaps4.set(40, { text: '中低速' })
    this.optionMaps4.set(60, { text: '中速' })
    this.optionMaps4.set(80, { text: '高速' })
    this.optionMaps4.set(100, { text: '极速' })
    
    // 初始化无障碍文本映射5 - 饱和度刻度
    this.optionMaps5.set(0, { text: '黑白' })
    this.optionMaps5.set(25, { text: '低饱和' })
    this.optionMaps5.set(50, { text: '中等饱和' })
    this.optionMaps5.set(75, { text: '高饱和' })
    this.optionMaps5.set(100, { text: '全饱和' })
    
    // 初始化无障碍文本映射6 - 缩放刻度
    this.optionMaps6.set(0, { text: '25%' })
    this.optionMaps6.set(25, { text: '50%' })
    this.optionMaps6.set(50, { text: '75%' })
    this.optionMaps6.set(75, { text: '100%' })
    this.optionMaps6.set(100, { text: '125%' })
    
    // 初始化无障碍文本映射7 - 透明度刻度
    this.optionMaps7.set(0, { text: '不透明' })
    this.optionMaps7.set(25, { text: '轻微透明' })
    this.optionMaps7.set(50, { text: '半透明' })
    this.optionMaps7.set(75, { text: '高度透明' })
    this.optionMaps7.set(100, { text: '完全透明' })
    
    // 初始化无障碍文本映射8 - 特殊字符刻度
    this.optionMaps8.set(0, { text: '0级' })
    this.optionMaps8.set(20, { text: '1级★' })
    this.optionMaps8.set(40, { text: '2级★★' })
    this.optionMaps8.set(60, { text: '3级★★★' })
    this.optionMaps8.set(80, { text: '4级★★★★' })
    this.optionMaps8.set(100, { text: '5级★★★★★' })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          // 标题部分
          Text('Slider ShowSteps 综合示例')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })
            .width('100%')
            .textAlign(TextAlign.Center)

          Text('showSteps API 用于显示滑动条的步长刻度值，支持设置无障碍文本')
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

          // 示例1：不显示刻度
          Column({ space: 10 }) {
            Text('示例1：不显示刻度 (showSteps: false)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('默认情况下不显示刻度，滑动条更简洁')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue1,
              step: 10,
              max: 100,
              min: 0,
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

          // 示例2：显示刻度
          Column({ space: 10 }) {
            Text('示例2：显示刻度 (showSteps: true)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('设置showSteps为true，显示步长刻度')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue2,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(8)
              .stepColor('#FFD700')
              .blockColor('#32CD32')
              .selectedColor('#32CD32')
              .showSteps(true)
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

          // 示例3：显示刻度并设置无障碍文本
          Column({ space: 10 }) {
            Text('示例3：显示刻度 + 无障碍文本')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('使用stepsAccessibility参数设置刻度点的无障碍文本')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue3,
              step: 20,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(8)
              .stepColor('#FF6347')
              .blockColor('#FF6347')
              .selectedColor('#FF6347')
              .showSteps(true, { stepsAccessibility: this.optionMaps1 })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue3 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue3.toFixed(0) + '°C')
                .fontSize(12)
                .fontColor('#FF6347')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第二部分：与stepColor组合 ====================
          Divider()
          Text('二、与stepColor属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例4：showSteps + stepColor (黄色刻度)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('自定义刻度颜色，增强视觉效果')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue4,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(8)
              .stepColor('#FFD700')
              .blockColor('#FF8C00')
              .selectedColor('#FF8C00')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue4 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue4.toFixed(0))
                .fontSize(12)
                .fontColor('#FF8C00')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          Column({ space: 10 }) {
            Text('示例5：showSteps + stepColor (蓝色刻度)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('不同颜色的刻度，适应不同主题')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue5,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(8)
              .stepColor('#4169E1')
              .blockColor('#1E90FF')
              .selectedColor('#1E90FF')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue5 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue5.toFixed(0))
                .fontSize(12)
                .fontColor('#1E90FF')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // ==================== 第三部分：与stepSize组合 ====================
          Divider()
          Text('三、与stepSize属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例6：showSteps + stepSize (小刻度)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('自定义刻度大小，适应不同设计需求')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue6,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(4)
              .stepColor('#32CD32')
              .blockColor('#32CD32')
              .selectedColor('#32CD32')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue6 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue6.toFixed(0))
                .fontSize(12)
                .fontColor('#32CD32')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          Column({ space: 10 }) {
            Text('示例7：showSteps + stepSize (大刻度)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('较大的刻度尺寸，更明显的视觉提示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue7,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(10)
              .stepColor('#FF6347')
              .blockColor('#FF6347')
              .selectedColor('#FF6347')
              .showSteps(true)
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

          // ==================== 第四部分：与blockColor组合 ====================
          Divider()
          Text('四、与blockColor属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例8：showSteps + blockColor')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('刻度配合自定义滑块颜色')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue8,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .stepSize(8)
              .stepColor('#9370DB')
              .blockColor('#9370DB')
              .selectedColor('#9370DB')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue8 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue8.toFixed(0))
                .fontSize(12)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第五部分：与blockSize组合 ====================
          Divider()
          Text('五、与blockSize属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例9：showSteps + blockSize')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('刻度配合自定义滑块大小')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue9,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockSize({ width: 24, height: 24 })
              .stepSize(8)
              .stepColor('#00CED1')
              .blockColor('#00CED1')
              .selectedColor('#00CED1')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue9 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue9.toFixed(0))
                .fontSize(12)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第六部分：与trackThickness组合 ====================
          Divider()
          Text('六、与trackThickness属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例10：showSteps + trackThickness')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('刻度配合自定义滑轨粗细')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue10,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(10)
              .stepSize(8)
              .stepColor('#FF69B4')
              .blockColor('#FF69B4')
              .selectedColor('#FF69B4')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue10 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue10.toFixed(0))
                .fontSize(12)
                .fontColor('#FF69B4')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF0F5)
          .borderRadius(10)

          // ==================== 第七部分：与direction组合 ====================
          Divider()
          Text('七、与direction属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例11：showSteps + direction (垂直)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('垂直滑动条配合刻度显示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 20 }) {
              Slider({
                style: SliderStyle.OutSet,
                value: this.vSliderValue1,
                step: 10,
                max: 100,
                min: 0,
                direction: Axis.Vertical
              })
                .height(200)
                .stepSize(8)
                .stepColor('#20B2AA')
                .blockColor('#20B2AA')
                .selectedColor('#20B2AA')
                .showSteps(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue1 = value
                })

              Slider({
                style: SliderStyle.InSet,
                value: this.vSliderValue2,
                step: 10,
                max: 100,
                min: 0,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(200)
                .stepSize(8)
                .stepColor('#FFD700')
                .blockColor('#FFD700')
                .selectedColor('#FFD700')
                .showSteps(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue2 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第八部分：与trackColor/selectedColor组合 ====================
          Divider()
          Text('八、与trackColor/selectedColor组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例12：showSteps + trackColor + selectedColor')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('刻度配合自定义滑轨颜色')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.sliderValue11,
              step: 10,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackColor('#E0E0E0')
              .selectedColor('#FF4500')
              .stepSize(8)
              .stepColor('#FF4500')
              .blockColor('#FF4500')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue11 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue11.toFixed(0))
                .fontSize(12)
                .fontColor('#FF4500')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第九部分：综合示例1 - 音量调节 ====================
          Divider()
          Text('九、综合示例 - 音量调节')
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
                style: SliderStyle.OutSet,
                value: this.sliderValue12,
                step: 25,
                max: 100,
                min: 0,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#32CD32')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#32CD32')
                .stepSize(8)
                .stepColor('#32CD32')
                .showSteps(true, { stepsAccessibility: this.optionMaps2 })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue12 = value
                })
              Text(this.sliderValue12.toFixed(0) + '%')
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
                style: SliderStyle.InSet,
                value: this.sliderValue13,
                step: 25,
                max: 100,
                min: 0,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .trackThickness(12)
                .trackBorderRadius(6)
                .selectedBorderRadius(6)
                .blockSize({ width: 22, height: 22 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FFD700')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FFD700')
                .stepSize(8)
                .stepColor('#FFD700')
                .showSteps(true, { stepsAccessibility: this.optionMaps3 })
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

          // ==================== 第十一部分：综合示例3 - 速度控制 ====================
          Divider()
          Text('十一、综合示例 - 速度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例15：速度控制滑动条')
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
                style: SliderStyle.OutSet,
                value: this.sliderValue14,
                step: 20,
                max: 100,
                min: 0,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .blockSize({ width: 18, height: 18 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF6347')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF6347')
                .stepSize(8)
                .stepColor('#FF6347')
                .showSteps(true, { stepsAccessibility: this.optionMaps4 })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue14 = value
                })
              Text(this.sliderValue14.toFixed(0) + ' km/h')
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

          // ==================== 第十二部分：综合示例4 - 饱和度调节 ====================
          Divider()
          Text('十二、综合示例 - 饱和度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例16：饱和度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟饱和度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.sliderValue15,
              step: 25,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(14)
              .trackBorderRadius(7)
              .selectedBorderRadius(7)
              .blockSize({ width: 24, height: 24 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#9370DB')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#9370DB')
              .stepSize(8)
              .stepColor('#9370DB')
              .showSteps(true, { stepsAccessibility: this.optionMaps5 })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue15 = value
              })

            Row() {
              Text('饱和度: ')
                .fontSize(12)
              Text(this.sliderValue15.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第十三部分：综合示例5 - 缩放控制 ====================
          Divider()
          Text('十三、综合示例 - 缩放控制')
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
                step: 25,
                max: 100,
                min: 0,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .blockSize({ width: 18, height: 18 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#00CED1')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#00CED1')
                .stepSize(8)
                .stepColor('#00CED1')
                .showSteps(true, { stepsAccessibility: this.optionMaps6 })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue16 = value
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

          // ==================== 第十四部分：综合示例6 - 透明度调节 ====================
          Divider()
          Text('十四、综合示例 - 透明度调节')
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
              value: this.slider17,
              step: 25,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(12)
              .trackBorderRadius(6)
              .selectedBorderRadius(6)
              .blockSize({ width: 22, height: 22 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#4169E1')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#4169E1')
              .stepSize(8)
              .stepColor('#4169E1')
              .showSteps(true, { stepsAccessibility: this.optionMaps7 })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.slider17 = value
              })

            Row() {
              Text('透明度: ')
                .fontSize(12)
              Text(this.slider17.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // ==================== 第十五部分：综合示例7 - 评级系统 ====================
          Divider()
          Text('十五、综合示例 - 评级系统')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例19：评级系统滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟评级系统场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.OutSet,
              value: this.slider18,
              step: 20,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFD700')
              .blockBorderColor('#FF8C00')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#FFD700')
              .stepSize(8)
              .stepColor('#FF8C00')
              .showSteps(true, { stepsAccessibility: this.optionMaps8 })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.slider18 = value
              })

            Row() {
              Text('评级: ')
                .fontSize(12)
              Text(this.getRatingText())
                .fontSize(14)
                .fontColor('#FFD700')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第十六部分：综合示例8 - 垂直进度条 ====================
          Divider()
          Text('十六、综合示例 - 垂直进度条')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例20：垂直进度条')
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
                step: 10,
                max: 100,
                min: 0,
                direction: Axis.Vertical
              })
                .height(180)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#32CD32')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#32CD32')
                .stepSize(8)
                .stepColor('#32CD32')
                .showSteps(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue3 = value
                })

              Slider({
                style: SliderStyle.InSet,
                value: this.vSliderValue4,
                step: 10,
                max: 100,
                min: 0,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(180)
                .trackThickness(12)
                .trackBorderRadius(6)
                .selectedBorderRadius(6)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF6347')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF6347')
                .stepSize(8)
                .stepColor('#FF6347')
                .showSteps(true)
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue4 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // ==================== 第十七部分：综合示例9 - 温度控制 ====================
          Divider()
          Text('十七、综合示例 - 温度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例21：温度控制滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟温度控制场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row() {
              Text('❄️')
                .fontSize(20)
              Slider({
                style: SliderStyle.OutSet,
                value: this.slider19,
                step: 20,
                max: 100,
                min: 0,
                direction: Axis.Horizontal
              })
                .layoutWeight(1)
                .blockSize({ width: 22, height: 22 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#00CED1')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#00CED1')
                .stepSize(8)
                .stepColor('#00CED1')
                .showSteps(true, { stepsAccessibility: this.optionMaps1 })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.slider19 = value
                })
              Text('🔥')
                .fontSize(20)
            }
            .width('100%')

            Row() {
              Text('温度: ')
                .fontSize(12)
              Text(this.slider19.toFixed(0) + '°C')
                .fontSize(14)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第十八部分：综合示例10 - 对比度调节 ====================
          Divider()
          Text('十八、综合示例 - 对比度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例22：对比度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟对比度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              style: SliderStyle.InSet,
              value: this.slider20,
              step: 25,
              max: 100,
              min: 0,
              direction: Axis.Horizontal
            })
              .width('90%')
              .trackThickness(14)
              .trackBorderRadius(7)
              .selectedBorderRadius(7)
              .blockSize({ width: 24, height: 24 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#9370DB')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#9370DB')
              .stepSize(8)
              .stepColor('#9370DB')
              .showSteps(true)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.slider20 = value
              })

            Row() {
              Text('对比度: ')
                .fontSize(12)
              Text(this.slider20.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // 底部说明
          Divider()
          Text('说明')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 8 }) {
            Text('• showSteps用于控制是否显示步长刻度值')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• stepsAccessibility参数可设置刻度点的无障碍文本')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• stepColor用于设置刻度颜色')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• stepSize用于设置刻度大小（直径）')
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
            Text('• 无障碍文本可增强可访问性')
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
    .title('SliderShowSteps')
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

  // 获取评级文本
  getRatingText(): string {
    if (this.slider18 <= 20) {
      return '0级'
    } else if (this.slider18 <= 40) {
      return '1级★'
    } else if (this.slider18 <= 60) {
      return '2级★★'
    } else if (this.slider18 <= 80) {
      return '3级★★★'
    } else {
      return '4级★★★★'
    }
  }
}