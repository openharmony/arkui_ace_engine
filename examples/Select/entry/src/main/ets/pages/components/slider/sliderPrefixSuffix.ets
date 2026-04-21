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

import { ComponentContent, ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);

@Builder
export function SliderPrefixSuffixBuilder(name: string, param: Object) {
  SliderPrefixSuffixExample()
}

class NodeParams {
  public param: ResourceStr = '';

  constructor(param: ResourceStr) {
    this.param = param;
  }
}

@Builder
function textBuilder(params: NodeParams) {
  Text(params.param)
    .fontSize(12)
    .clip(true)
    .textAlign(TextAlign.Center)
    .fontColor(Color.Black)
}

@Builder
function iconBuilder(params: NodeParams) {
  Text(params.param)
    .fontSize(18)
    .clip(true)
    .textAlign(TextAlign.Center)
}

@Entry
@Component
struct SliderPrefixSuffixExample {
  pathStack: NavPathStack = new NavPathStack()
  private uiContext: UIContext = this.getUIContext();
  
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
  
  // Prefix和Suffix文本
  @State preText1: string = '0'
  @State sufText1: string = '100'
  @State preText2: string = 'OFF'
  @State sufText2: string = 'ON'
  @State preText3: string = '低'
  @State sufText3: string = '高'
  @State preText4: string = 'Min'
  @State sufText4: string = 'Max'
  @State preText5: string = '开始'
  @State sufText5: string = '结束'
  @State preText6: string = '0%'
  @State sufText6: string = '100%'
  @State preText7: string = '0°C'
  @State sufText7: string = '100°C'
  @State preText8: string = '0dB'
  @State sufText8: string = '100dB'
  
  // ComponentContent节点
  private preOutSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText1));
  private sufOutSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText1));
  private preIntSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText2));
  private sufIntSetNode: ComponentContent<NodeParams> = 
    new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText2));
  
  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          // 标题部分
          Text('Slider Prefix/Suffix 综合示例')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })
            .width('100%')
            .textAlign(TextAlign.Center)

          Text('prefix和suffix API 20新增功能，用于设置滑动条的前缀和后缀内容')
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

          // 示例1：OutSet样式
          Column({ space: 10 }) {
            Text('示例1：OutSet样式 + Prefix/Suffix')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('滑块在滑轨上，配合前后缀文本')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue1,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#4169E1')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#4169E1')
              .stepSize(8)
              .stepColor('#4169E1')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText1)), {
                accessibilityText: '最小值',
                accessibilityDescription: '滑动条最小值',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText1)), {
                accessibilityText: '最大值',
                accessibilityDescription: '滑动条最大值',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
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

          // 示例2：InSet样式
          Column({ space: 10 }) {
            Text('示例2：InSet样式 + Prefix/Suffix')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('滑块在滑轨内，配合前后缀文本')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue2,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(36)
              .trackBorderRadius(18)
              .selectedBorderRadius(18)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#32CD32')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#32CD32')
              .stepSize(8)
              .stepColor('#32CD32')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText2)), {
                accessibilityText: '关闭',
                accessibilityDescription: '滑动条关闭状态',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText2)), {
                accessibilityText: '开启',
                accessibilityDescription: '滑动条开启状态',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
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

          // ==================== 第二部分：与blockColor组合 ====================
          Divider()
          Text('二、与blockColor属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例3：Prefix/Suffix + blockColor')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('前后缀配合自定义滑块颜色')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue3,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 22, height: 22 })
              .blockColor('#FF1493')
              .trackColor('#E0E0E0')
              .selectedColor('#FF1493')
              .stepSize(8)
              .stepColor('#FF1493')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText3)), {
                accessibilityText: '低值',
                accessibilityDescription: '滑动条低值',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText3)), {
                accessibilityText: '高值',
                accessibilityDescription: '滑动条高值',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
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
            Text('示例4：Prefix/Suffix + blockSize')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('前后缀配合自定义滑块大小')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue4,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 26, height: 26 })
              .blockColor('#FFD700')
              .blockBorderColor('#FF8C00')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#FFD700')
              .stepSize(8)
              .stepColor('#FFD700')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText4)), {
                accessibilityText: '最小值',
                accessibilityDescription: '滑动条最小值',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText4)), {
                accessibilityText: '最大值',
                accessibilityDescription: '滑动条最大值',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
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

          // ==================== 第四部分：与trackThickness组合 ====================
          Divider()
          Text('四、与trackThickness属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例5：Prefix/Suffix + trackThickness')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('前后缀配合自定义滑轨粗细')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue5,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(20)
              .trackBorderRadius(10)
              .selectedBorderRadius(10)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#9370DB')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#9370DB')
              .stepSize(8)
              .stepColor('#9370DB')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText5)), {
                accessibilityText: '开始',
                accessibilityDescription: '滑动条开始',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText5)), {
                accessibilityText: '结束',
                accessibilityDescription: '滑动条结束',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
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

          // ==================== 第五部分：与showSteps组合 ====================
          Divider()
          Text('五、与showSteps属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例6：Prefix/Suffix + showSteps')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('前后缀配合刻度显示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue6,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#20B2AA')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#20B2AA')
              .stepSize(8)
              .stepColor('#20B2AA')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText6)), {
                accessibilityText: '0%',
                accessibilityDescription: '滑动条0%',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText6)), {
                accessibilityText: '100%',
                accessibilityDescription: '滑动条100%',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
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

          // ==================== 第六部分：与showTips组合 ====================
          Divider()
          Text('六、与showTips属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例7：Prefix/Suffix + showTips')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('前后缀配合气泡提示')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue7,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(36)
              .trackBorderRadius(18)
              .selectedBorderRadius(18)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#FF6347')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#FF6347')
              .stepSize(8)
              .stepColor('#FF6347')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.preText7)), {
                accessibilityText: '0°C',
                accessibilityDescription: '滑动条0°C',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams(this.sufText7)), {
                accessibilityText: '100°C',
                accessibilityDescription: '滑动条100°C',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue7 = value
              })

            Row() {
              Text('当前值: ')
                .fontSize(12)
              Text(this.sliderValue7.toFixed(0) + '°C')
                .fontSize(12)
                .fontColor('#FF6347')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第七部分：与direction组合 ====================
          Divider()
          Text('七、与direction属性组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例8：Prefix/Suffix + direction (垂直)')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('垂直滑动条配合前后缀')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Row({ space: 20 }) {
              Slider({
                value: this.vSliderValue1,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.OutSet,
                direction: Axis.Vertical
              })
                .height(200)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#00CED1')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#00CED1')
                .stepSize(8)
                .stepColor('#00CED1')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                  accessibilityText: '0',
                  accessibilityDescription: '滑动条0',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                  accessibilityText: '100',
                  accessibilityDescription: '滑动条100',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue1 = value
                })

              Slider({
                value: this.vSliderValue2,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.InSet,
                direction: Axis.Vertical,
                reverse: true
              })
                .height(200)
                .trackThickness(36)
                .trackBorderRadius(18)
                .selectedBorderRadius(18)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF69B4')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF69B4')
                .stepSize(8)
                .stepColor('#FF69B4')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                  accessibilityText: '0',
                  accessibilityDescription: '滑动条0',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                  accessibilityText: '100',
                  accessibilityDescription: '滑动条100',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.vSliderValue2 = value
                })
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF0F5)
          .borderRadius(10)

          // ==================== 第八部分：综合示例1 - 音量调节 ====================
          Divider()
          Text('八、综合示例 - 音量调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例9：音量调节滑动')
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
                value: this.sliderValue8,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.OutSet
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
                .stepSize(8)
                .stepColor('#32CD32')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                  accessibilityText: '静音',
                  accessibilityDescription: '音量静音',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                  accessibilityText: '最大音量',
                  accessibilityDescription: '音量最大',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue8 = value
                })
              Text(this.sliderValue8.toFixed(0) + '%')
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

          // ==================== 第九部分：综合示例2 - 亮度调节 ====================
          Divider()
          Text('九、综合示例 - 亮度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例10：亮度调节滑动条')
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
                value: this.sliderValue9,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.InSet
              })
                .layoutWeight(1)
                .trackThickness(20)
                .trackBorderRadius(10)
                .selectedBorderRadius(10)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FFD700')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FFD700')
                .stepSize(8)
                .stepColor('#FFD700')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                  accessibilityText: '最暗',
                  accessibilityDescription: '亮度最暗',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                  accessibilityText: '最亮',
                  accessibilityDescription: '亮度最亮',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue9 = value
                })
              Text(this.sliderValue9.toFixed(0) + '%')
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

          // ==================== 第十部分：综合示例3 - 温度调节 ====================
          Divider()
          Text('十、综合示例 - 温度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例11：温度调节滑动条')
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
                value: this.sliderValue10,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.OutSet
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
                .stepSize(8)
                .stepColor('#00CED1')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0°C')), {
                  accessibilityText: '0°C',
                  accessibilityDescription: '温度0°C',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100°C')), {
                  accessibilityText: '100°C',
                  accessibilityDescription: '温度100°C',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue10 = value
                })
              Text('🔥')
                .fontSize(20)
            }
            .width('100%')

            Row() {
              Text('温度: ')
                .fontSize(12)
              Text(this.sliderValue10.toFixed(0) + '°C')
                .fontSize(14)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第十一部分：综合示例4 - 速度控制 ====================
          Divider()
          Text('十一、综合示例 - 速度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例12：速度控制滑动条')
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
                value: this.sliderValue11,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.InSet
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
                .stepSize(8)
                .stepColor('#FF6347')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                  accessibilityText: '停止',
                  accessibilityDescription: '速度停止',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                  accessibilityText: '极速',
                  accessibilityDescription: '速度极速',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue11 = value
                })
              Text(this.sliderValue11.toFixed(0) + ' km/h')
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

          // ==================== 第十二部分：综合示例5 - 饱和度调节 ====================
          Divider()
          Text('十二、综合示例 - 饱和度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例13：饱和度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟饱和度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue12,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
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
              .stepSize(8)
              .stepColor('#9370DB')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                accessibilityText: '黑白',
                accessibilityDescription: '饱和度黑白',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                accessibilityText: '全饱和',
                accessibilityDescription: '饱和度全饱和',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue12 = value
              })

            Row() {
              Text('饱和度: ')
                .fontSize(12)
              Text(this.sliderValue12.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#9370DB')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF5F5FF)
          .borderRadius(10)

          // ==================== 第十三部分：综合示例6 - 对比度调节 ====================
          Divider()
          Text('十三、综合示例 - 对比度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例14：对比度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟对比度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue13,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.InSet
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
              .stepSize(8)
              .stepColor('#4169E1')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                accessibilityText: '最低对比度',
                accessibilityDescription: '对比度最低',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                accessibilityText: '最高对比度',
                accessibilityDescription: '对比度最高',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue13 = value
              })

            Row() {
              Text('对比度: ')
                .fontSize(12)
              Text(this.sliderValue13.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#4169E1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0F8FF)
          .borderRadius(10)

          // ==================== 第十四部分：综合示例7 - 缩放控制 ====================
          Divider()
          Text('十四、综合示例 - 缩放控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例15：缩放控制滑动条')
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
                value: this.sliderValue14,
                min: 0,
                max: 100,
                step: 25,
                style: SliderStyle.OutSet
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF69B4')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF69B4')
                .stepSize(8)
                .stepColor('#FF69B4')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('25%')), {
                  accessibilityText: '25%',
                  accessibilityDescription: '缩放25%',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('125%')), {
                  accessibilityText: '125%',
                  accessibilityDescription: '缩放125%',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue14 = value
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

          // ==================== 第十五部分：综合示例8 - 透明度调节 ====================
          Divider()
          Text('十五、综合示例 - 透明度调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例16：透明度调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟透明度调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue15,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.InSet
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
              .stepSize(8)
              .stepColor('#FFD700')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0')), {
                accessibilityText: '不透明',
                accessibilityDescription: '透明度不透明',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100')), {
                accessibilityText: '完全透明',
                accessibilityDescription: '透明度完全透明',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue15 = value
              })

            Row() {
              Text('透明度: ')
                .fontSize(12)
              Text(this.sliderValue15.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#FFD700')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFF0)
          .borderRadius(10)

          // ==================== 第十六部分：综合示例9 - 进度控制 ====================
          Divider()
          Text('十六、综合示例 - 进度控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例17：进度控制滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟进度控制场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue16,
              min: 0,
              max: 100,
              step: 5,
              style: SliderStyle.OutSet
            })
              .width('90%')
              .trackThickness(10)
              .trackBorderRadius(5)
              .selectedBorderRadius(5)
              .blockSize({ width: 18, height: 18 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#32CD32')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#32CD32')
              .stepSize(4)
              .stepColor('#32CD32')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0%')), {
                accessibilityText: '0%',
                accessibilityDescription: '进度0%',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100%')), {
                accessibilityText: '100%',
                accessibilityDescription: '进度100%',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue16 = value
              })

            Row() {
              Text('进度: ')
                .fontSize(12)
              Text(this.sliderValue16.toFixed(0) + '%')
                .fontSize(14)
                .fontColor('#32CD32')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFF0)
          .borderRadius(10)

          // ==================== 第十七部分：综合示例10 - 频率调节 ====================
          Divider()
          Text('十七、综合示例 - 频率调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例18：频率调节滑动条')
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
                value: this.sliderValue17,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.InSet
              })
                .layoutWeight(1)
                .trackThickness(36)
                .trackBorderRadius(18)
                .selectedBorderRadius(18)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#9370DB')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#9370DB')
                .stepSize(8)
                .stepColor('#9370DB')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0Hz')), {
                  accessibilityText: '0Hz',
                  accessibilityDescription: '频率0Hz',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('100Hz')), {
                  accessibilityText: '100Hz',
                  accessibilityDescription: '频率100Hz',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue17 = value
                })
              Text(this.sliderValue17.toFixed(0) + 'Hz')
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

          // ==================== 第十八部分：综合示例11 - 增益调节 ====================
          Divider()
          Text('十八、综合示例 - 增益调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例19：增益调节滑动条')
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
                value: this.sliderValue18,
                min: 0,
                max: 100,
                step: 10,
                style: SliderStyle.OutSet
              })
                .layoutWeight(1)
                .trackThickness(10)
                .trackBorderRadius(5)
                .selectedBorderRadius(5)
                .blockSize({ width: 20, height: 20 })
                .blockColor('#FFFFFF')
                .blockBorderColor('#FF6347')
                .blockBorderWidth(2)
                .trackColor('#E0E0E0')
                .selectedColor('#FF6347')
                .stepSize(8)
                .stepColor('#FF6347')
                .showSteps(true)
                .showTips(true)
                .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('-12dB')), {
                  accessibilityText: '-12dB',
                  accessibilityDescription: '增益-12dB',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('+12dB')), {
                  accessibilityText: '+12dB',
                  accessibilityDescription: '增益+12dB',
                  accessibilityLevel: 'auto',
                  accessibilityGroup: true
                })
                .onChange((value: number, mode: SliderChangeMode) => {
                  this.sliderValue18 = value
                })
              Text(this.getGainText())
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .fontColor('#FF6347')
                .width(60)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFF5F5)
          .borderRadius(10)

          // ==================== 第十九部分：综合示例12 - 平衡调节 ====================
          Divider()
          Text('十九、综合示例 - 平衡调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例20：平衡调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟平衡调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue19,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.InSet
            })
              .width('90%')
              .trackThickness(36)
              .trackBorderRadius(18)
              .selectedBorderRadius(18)
              .blockSize({ width: 20, height: 20 })
              .blockColor('#FFFFFF')
              .blockBorderColor('#00CED1')
              .blockBorderWidth(2)
              .trackColor('#E0E0E0')
              .selectedColor('#00CED1')
              .stepSize(8)
              .stepColor('#00CED1')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('L')), {
                accessibilityText: '左声道',
                accessibilityDescription: '左声道',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('R')), {
                accessibilityText: '右声道',
                accessibilityDescription: '右声道',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue19 = value
              })

            Row() {
              Text('平衡: ')
                .fontSize(12)
              Text(this.getBalanceText())
                .fontSize(14)
                .fontColor('#00CED1')
                .fontWeight(FontWeight.Bold)
            }
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xF0FFFF)
          .borderRadius(10)

          // ==================== 第二十部分：综合示例13 - 相位调节 ====================
          Divider()
          Text('二十、综合示例 - 相位调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 5 })

          Column({ space: 10 }) {
            Text('示例21：相位调节滑动条')
              .fontSize(13)
              .fontColor(0x333333)
              .width('100%')
            
            Text('综合运用多种属性，模拟相位调节场景')
              .fontSize(11)
              .fontColor(0x888888)
              .width('100%')

            Slider({
              value: this.sliderValue20,
              min: 0,
              max: 100,
              step: 10,
              style: SliderStyle.OutSet
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
              .stepSize(8)
              .stepColor('#FF69B4')
              .showSteps(true)
              .showTips(true)
              .prefix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('0°')), {
                accessibilityText: '0度',
                accessibilityDescription: '相位0度',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .suffix(new ComponentContent(this.uiContext, wrapBuilder(textBuilder), new NodeParams('360°')), {
                accessibilityText: '360度',
                accessibilityDescription: '相位360度',
                accessibilityLevel: 'auto',
                accessibilityGroup: true
              })
              .onChange((value: number, mode: SliderChangeMode) => {
                this.sliderValue20 = value
              })

            Row() {
              Text('相位: ')
                .fontSize(12)
              Text(this.sliderValue20.toFixed(0) + '°')
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
            Text('• prefix和suffix是API 20新增功能')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 使用ComponentContent创建自定义组件内容')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 支持设置无障碍文本和描述')
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
            Text('• 前缀显示在滑动条起始位置')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 后缀显示在滑动条结束位置')
              .fontSize(12)
              .fontColor(0x666666)
              .width('100%')
            Text('• 增强用户体验和可访问性')
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
    .title('SliderPrefixSuffix')
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
    if (this.sliderValue14 <= 25) {
      return '25%'
    } else if (this.sliderValue14 <= 50) {
      return '50%'
    } else if (this.sliderValue14 <= 75) {
      return '75%'
    } else {
      return '125%'
    }
  }

  // 获取增益文本
  getGainText(): string {
    const gain = (this.sliderValue18 - 50) * 0.24
    return gain.toFixed(1) + 'dB'
  }

  // 获取平衡文本
  getBalanceText(): string {
    const balance = (this.sliderValue19 - 50) * 2
    if (balance === 0) {
      return 'C'
    } else if (balance > 0) {
      return 'R' + balance.toFixed(0)
    } else {
      return 'L' + Math.abs(balance).toFixed(0)
    }
  }
}

export { SliderPrefixSuffixExample };