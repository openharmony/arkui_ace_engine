/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { DatePickerComponent, DateMode, DisplayMode, DatePickerComponentOptions, DateOptions } from '@ohos.arkui.advanced.DatePickerComponent'

@Entry
@Component
struct DatePickerComponentExample009 {
  @State selectedYear: number = 2026
  @State selectedMonth: number = 0
  @State selectedDay: number = 1
  @State logText: string = ''
  
  @State fontSize: number = 18
  @State selectedFontSize: number = 22
  @State textColor: string = '#333333'
  @State selectedTextColor: string = '#007DFF'
  @State fontWeight: FontWeight = FontWeight.Normal
  @State selectedFontWeight: FontWeight = FontWeight.Bold
  @State backgroundColor: string = '#FFFFFF'
  @State borderColor: string = '#E0E0E0'
  @State borderWidth: number = 1
  @State borderRadius: number = 8
  @State currentTheme: string = 'light'
  @State shadowSize: number = 0
  
  private themes: Record<string, ThemeConfig> = {
    'light': {
      background: '#FFFFFF',
      text: '#333333',
      selectedText: '#007DFF',
      border: '#E0E0E0',
      shadow: 0
    },
    'dark': {
      background: '#1A1A1A',
      text: '#CCCCCC',
      selectedText: '#4DA6FF',
      border: '#333333',
      shadow: 8
    },
    'blue': {
      background: '#E3F2FD',
      text: '#1976D2',
      selectedText: '#0D47A1',
      border: '#2196F3',
      shadow: 4
    },
    'green': {
      background: '#E8F5E9',
      text: '#2E7D32',
      selectedText: '#1B5E20',
      border: '#4CAF50',
      shadow: 4
    },
    'purple': {
      background: '#F3E5F5',
      text: '#6A1B9A',
      selectedText: '#4A148C',
      border: '#9C27B0',
      shadow: 6
    }
  }
  
  private fontSizes: number[] = [14, 16, 18, 20, 22, 24, 26, 28, 30]
  private selectedFontSizes: number[] = [18, 20, 22, 24, 26, 28, 30, 32, 34]
  private colors: string[] = [
    '#333333', '#007DFF', '#FF0000', '#00FF00', '#0000FF',
    '#FF9800', '#9C27B0', '#4CAF50', '#FF5722', '#607D8B'
  ]
  
  build() {
    Scroll() {
      Column() {
        Text('DatePickerComponent Style Customization')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
        
        Text('Comprehensive style and visual effects testing')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 })
        
        Column() {
          Text('1. Font Size Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            Text('Normal Font Size:')
              .fontSize(14)
              .width(120)
            Slider({
              value: this.fontSize,
              min: 14,
              max: 30,
              step: 2,
              style: SliderStyle.OutSet
            })
              .blockColor('#007DFF')
              .trackColor('#E0E0E0')
              .selectedColor('#007DFF')
              .showSteps(true)
              .width(150)
              .onChange((value: number) => {
                this.fontSize = value
                this.addLog('Normal font size: ' + value)
              })
            Text(`${this.fontSize}`)
              .fontSize(14)
              .width(40)
              .margin({ left: 10 })
          }
          .width('100%')
          .margin({ bottom: 10 })
          
          Row() {
            Text('Selected Font Size:')
              .fontSize(14)
              .width(120)
            Slider({
              value: this.selectedFontSize,
              min: 18,
              max: 34,
              step: 2,
              style: SliderStyle.OutSet
            })
              .blockColor('#007DFF')
              .trackColor('#E0E0E0')
              .selectedColor('#007DFF')
              .showSteps(true)
              .width(150)
              .onChange((value: number) => {
                this.selectedFontSize = value
                this.addLog('Selected font size: ' + value)
              })
            Text(`${this.selectedFontSize}`)
              .fontSize(14)
              .width(40)
              .margin({ left: 10 })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('2. Text Color Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            Text('Normal Text:')
              .fontSize(14)
              .width(120)
            ForEach(this.colors.slice(0, 5), (color: string) => {
              Button()
                .width(30)
                .height(30)
                .backgroundColor(color)
                .borderRadius(15)
                .border(this.textColor === color ? 3 : 1, '#FF0000')
                .margin(4)
                .onClick(() => {
                  this.textColor = color
                  this.addLog('Normal text color: ' + color)
                })
            })
          }
          .width('100%')
          .margin({ bottom: 10 })
          
          Row() {
            Text('Selected Text:')
              .fontSize(14)
              .width(120)
            ForEach(this.colors.slice(0, 5), (color: string) => {
              Button()
                .width(30)
                .height(30)
                .backgroundColor(color)
                .borderRadius(15)
                .border(this.selectedTextColor === color ? 3 : 1, '#FF0000')
                .margin(4)
                .onClick(() => {
                  this.selectedTextColor = color
                  this.addLog('Selected text color: ' + color)
                })
            })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('3. Font Weight Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            Text('Normal Weight:')
              .fontSize(14)
              .width(120)
            Button('Normal')
              .width(80)
              .height(30)
              .fontSize(12)
              .type(this.fontWeight === FontWeight.Normal ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.fontWeight === FontWeight.Normal ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.fontWeight = FontWeight.Normal
                this.addLog('Normal weight: Normal')
              })
              .margin(4)
            Button('Medium')
              .width(80)
              .height(30)
              .fontSize(12)
              .type(this.fontWeight === FontWeight.Medium ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.fontWeight === FontWeight.Medium ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.fontWeight = FontWeight.Medium
                this.addLog('Normal weight: Medium')
              })
              .margin(4)
            Button('Bold')
              .width(80)
              .height(30)
              .fontSize(12)
              .type(this.fontWeight === FontWeight.Bold ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.fontWeight === FontWeight.Bold ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.fontWeight = FontWeight.Bold
                this.addLog('Normal weight: Bold')
              })
              .margin(4)
          }
          .width('100%')
          .margin({ bottom: 10 })
          
          Row() {
            Text('Selected Weight:')
              .fontSize(14)
              .width(120)
            Button('Normal')
              .width(80)
              .height(30)
              .fontSize(12)
              .type(this.selectedFontWeight === FontWeight.Normal ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.selectedFontWeight === FontWeight.Normal ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.selectedFontWeight = FontWeight.Normal
                this.addLog('Selected weight: Normal')
              })
              .margin(4)
            Button('Medium')
              .width(80)
              .height(30)
              .fontSize(12)
              .type(this.selectedFontWeight === FontWeight.Medium ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.selectedFontWeight === FontWeight.Medium ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.selectedFontWeight = FontWeight.Medium
                this.addLog('Selected weight: Medium')
              })
              .margin(4)
            Button('Bold')
              .width(80)
              .height(30)
              .fontSize(12)
              .type(this.selectedFontWeight === FontWeight.Bold ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.selectedFontWeight === FontWeight.Bold ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.selectedFontWeight = FontWeight.Bold
                this.addLog('Selected weight: Bold')
              })
              .margin(4)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('4. Theme Selection')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            ForEach(Object.keys(this.themes), (themeName: string) => {
              Button(themeName.charAt(0).toUpperCase() + themeName.slice(1))
                .width(70)
                .height(35)
                .fontSize(12)
                .type(this.currentTheme === themeName ? ButtonType.Capsule : ButtonType.Normal)
                .backgroundColor(this.currentTheme === themeName ? '#007DFF' : '#E0E0E0')
                .onClick(() => {
                  this.applyTheme(themeName)
                })
                .margin(4)
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('5. Border Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            Text('Border Width:')
              .fontSize(14)
              .width(120)
            Slider({
              value: this.borderWidth,
              min: 0,
              max: 5,
              step: 1,
              style: SliderStyle.OutSet
            })
              .blockColor('#007DFF')
              .trackColor('#E0E0E0')
              .selectedColor('#007DFF')
              .showSteps(true)
              .width(150)
              .onChange((value: number) => {
                this.borderWidth = value
                this.addLog('Border width: ' + value)
              })
            Text(`${this.borderWidth}`)
              .fontSize(14)
              .width(30)
              .margin({ left: 10 })
          }
          .width('100%')
          .margin({ bottom: 10 })
          
          Row() {
            Text('Border Radius:')
              .fontSize(14)
              .width(120)
            Slider({
              value: this.borderRadius,
              min: 0,
              max: 20,
              step: 2,
              style: SliderStyle.OutSet
            })
              .blockColor('#007DFF')
              .trackColor('#E0E0E0')
              .selectedColor('#007DFF')
              .showSteps(true)
              .width(150)
              .onChange((value: number) => {
                this.borderRadius = value
                this.addLog('Border radius: ' + value)
              })
            Text(`${this.borderRadius}`)
              .fontSize(14)
              .width(30)
              .margin({ left: 10 })
          }
          .width('100%')
          .margin({ bottom: 10 })
          
          Row() {
            Text('Border Color:')
              .fontSize(14)
              .width(120)
            ForEach(this.colors.slice(0, 5), (color: string) => {
              Button()
                .width(30)
                .height(30)
                .backgroundColor(color)
                .borderRadius(15)
                .border(this.borderColor === color ? 3 : 1, '#FF0000')
                .margin(4)
                .onClick(() => {
                  this.borderColor = color
                  this.addLog('Border color: ' + color)
                })
            })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('6. Shadow Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            Text('Shadow Size:')
              .fontSize(14)
              .width(120)
            Slider({
              value: this.shadowSize,
              min: 0,
              max: 20,
              step: 2,
              style: SliderStyle.OutSet
            })
              .blockColor('#007DFF')
              .trackColor('#E0E0E0')
              .selectedColor('#007DFF')
              .showSteps(true)
              .width(150)
              .onChange((value: number) => {
                this.shadowSize = value
                this.addLog('Shadow size: ' + value)
              })
            Text(`${this.shadowSize}`)
              .fontSize(14)
              .width(30)
              .margin({ left: 10 })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Text('DatePickerComponent with Custom Styles')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 10, bottom: 10 })
        
        Column() {
          DatePickerComponent({
            options: {
              displayMode: DisplayMode.DATE,
              dateOptions: {
                mode: DateMode.DATE,
                lunar: false,
                start: new Date(1970, 0, 1),
                end: new Date(2100, 11, 31),
                selected: new Date(this.selectedYear, this.selectedMonth, this.selectedDay),
                loop: true,
                enableHapticFeedback: true,
onChange: (result) => {
                   this.addLog('onChange: ' + JSON.stringify(result))
                   if (result.year !== undefined) {
                     this.selectedYear = result.year
                   }
                   if (result.month !== undefined) {
                     this.selectedMonth = result.month
                   }
                   if (result.day !== undefined) {
                     this.selectedDay = result.day
                   }
                 },
                onScrollStop: (result) => {
                  this.addLog('onScrollStop: ' + JSON.stringify(result))
                }
              }
            }
          })
          .width('90%')
          .height(200)
        }
        .width('95%')
        .padding(12)
        .backgroundColor(this.backgroundColor)
        .border(this.borderWidth, this.borderColor)
        .borderRadius(this.borderRadius)
        .shadow({
          radius: this.shadowSize,
          color: '#000000',
          offsetX: 0,
          offsetY: 2
        })
        .margin({ bottom: 12 })
        
        Column() {
          Text('7. Style Preview Cards')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 12 })
          
          Row() {
            Column() {
              Text('Normal Text Style')
                .fontSize(this.fontSize)
                .fontColor(this.textColor)
                .fontWeight(this.fontWeight)
              Text(`${this.fontSize}px, ${this.textColor}`)
                .fontSize(10)
                .fontColor('#999999')
                .margin({ top: 5 })
            }
            .layoutWeight(1)
            .padding(12)
            .backgroundColor('#FAFAFA')
            .borderRadius(8)
            .margin(4)
            
            Column() {
              Text('Selected Text Style')
                .fontSize(this.selectedFontSize)
                .fontColor(this.selectedTextColor)
                .fontWeight(this.selectedFontWeight)
              Text(`${this.selectedFontSize}px, ${this.selectedTextColor}`)
                .fontSize(10)
                .fontColor('#999999')
                .margin({ top: 5 })
            }
            .layoutWeight(1)
            .padding(12)
            .backgroundColor('#FAFAFA')
            .borderRadius(8)
            .margin(4)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('8. Multiple Date Pickers with Different Styles')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 12 })
          
          Row() {
            Column() {
              Text('Small Style')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ bottom: 5 })
              DatePickerComponent({
                options: {
                  displayMode: DisplayMode.DATE,
                  dateOptions: {
                    mode: DateMode.DATE,
                    lunar: false,
                    start: new Date(2020, 0, 1),
                    end: new Date(2030, 11, 31),
                    selected: new Date(2026, 0, 1),
                    loop: true,
                    enableHapticFeedback: true,
                    onChange: (result) => {
                      this.addLog('Small picker: ' + JSON.stringify(result))
                    }
                  }
                }
              })
              .width('100%')
              .height(150)
            }
            .layoutWeight(1)
            .padding(8)
            .backgroundColor('#FFE8E8')
            .borderRadius(8)
            .margin(4)
            
            Column() {
              Text('Large Style')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ bottom: 5 })
              DatePickerComponent({
                options: {
                  displayMode: DisplayMode.DATE,
                  dateOptions: {
                    mode: DateMode.DATE,
                    lunar: false,
                    start: new Date(2020, 0, 1),
                    end: new Date(2030, 11, 31),
                    selected: new Date(2026, 0, 1),
                    loop: true,
                    enableHapticFeedback: true,
                    onChange: (result) => {
                      this.addLog('Large picker: ' + JSON.stringify(result))
                    }
                  }
                }
              })
              .width('100%')
              .height(150)
            }
            .layoutWeight(1)
            .padding(8)
            .backgroundColor('#E8F0FF')
            .borderRadius(8)
            .margin(4)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ bottom: 12 })
        
        Column() {
          Text('9. Gradient Background Test')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 12 })
          
          DatePickerComponent({
            options: {
              displayMode: DisplayMode.DATE,
              dateOptions: {
                mode: DateMode.DATE,
                lunar: false,
                start: new Date(2025, 0, 1),
                end: new Date(2027, 11, 31),
                selected: new Date(2026, 0, 1),
                loop: true,
                enableHapticFeedback: true,
                onChange: (result) => {
                  this.addLog('Gradient picker: ' + JSON.stringify(result))
                }
              }
            }
          })
          .width('90%')
          .height(200)
        }
        .width('95%')
        .padding(12)
        .linearGradient({
          angle: 135,
          colors: [['#667eea', 0.0], ['#764ba2', 1.0]]
        })
        .borderRadius(12)
        .margin({ bottom: 12 })
        
        Column() {
          Text('10. Responsive Width Test')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10, bottom: 12 })
          
          DatePickerComponent({
            options: {
              displayMode: DisplayMode.DATE,
              dateOptions: {
                mode: DateMode.DATE,
                lunar: false,
                start: new Date(2020, 0, 1),
                end: new Date(2030, 11, 31),
                selected: new Date(2026, 0, 1),
                loop: true,
                enableHapticFeedback: true,
                onChange: (result) => {
                  this.addLog('Responsive picker: ' + JSON.stringify(result))
                }
              }
            }
          })
          .width('90%')
          .height(180)
        }
        .width('95%')
        .padding(12)
        .backgroundColor('#F0F8FF')
        .borderRadius(12)
        .margin({ bottom: 12 })
        
        Column() {
          Text('Selected Date:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })
          
          Text(this.formatDate(this.selectedYear, this.selectedMonth, this.selectedDay))
            .fontSize(20)
            .fontColor('#1890FF')
            .fontWeight(FontWeight.Bold)
        }
        .width('90%')
        .margin({ top: 10 })
        .padding(16)
        .backgroundColor('#F5F5F5')
        .borderRadius(12)
        
        Column() {
          Text('Current Configuration:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })
          
          Grid() {
            GridItem() {
              Column() {
                Text('Font Size')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`${this.fontSize}/${this.selectedFontSize}`)
                  .fontSize(14)
                  .fontColor('#1890FF')
                  .fontWeight(FontWeight.Bold)
                  .margin({ top: 4 })
              }
              .padding(8)
            }
            
            GridItem() {
              Column() {
                Text('Text Color')
                  .fontSize(12)
                  .fontColor('#666666')
                Row() {
                  Text()
                    .width(20)
                    .height(20)
                    .backgroundColor(this.textColor)
                    .borderRadius(10)
                    .margin({ right: 5 })
                  Text()
                    .width(20)
                    .height(20)
                    .backgroundColor(this.selectedTextColor)
                    .borderRadius(10)
                }
                .margin({ top: 4 })
              }
              .padding(8)
            }
            
            GridItem() {
              Column() {
                Text('Font Weight')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(this.getWeightName(this.fontWeight))
                  .fontSize(14)
                  .fontColor('#1890FF')
                  .fontWeight(FontWeight.Bold)
                  .margin({ top: 4 })
              }
              .padding(8)
            }
            
            GridItem() {
              Column() {
                Text('Theme')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(this.currentTheme.charAt(0).toUpperCase() + this.currentTheme.slice(1))
                  .fontSize(14)
                  .fontColor('#1890FF')
                  .fontWeight(FontWeight.Bold)
                  .margin({ top: 4 })
              }
              .padding(8)
            }
            
            GridItem() {
              Column() {
                Text('Border')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`${this.borderWidth}px/${this.borderRadius}px`)
                  .fontSize(14)
                  .fontColor('#1890FF')
                  .fontWeight(FontWeight.Bold)
                  .margin({ top: 4 })
              }
              .padding(8)
            }
            
            GridItem() {
              Column() {
                Text('Shadow')
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`${this.shadowSize}px`)
                  .fontSize(14)
                  .fontColor('#1890FF')
                  .fontWeight(FontWeight.Bold)
                  .margin({ top: 4 })
              }
              .padding(8)
            }
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsTemplate('1fr 1fr')
          .columnsGap(8)
          .rowsGap(8)
          .width('100%')
          .height(150)
        }
        .width('90%')
        .margin({ top: 12 })
        .padding(16)
        .backgroundColor('#FAFAFA')
        .borderRadius(12)
        
        Column() {
          Text('Event Log:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })
          
          Scroll() {
            Text(this.logText)
              .fontSize(12)
              .fontColor('#333333')
              .width('100%')
          }
          .height(100)
          .width('100%')
        }
        .width('90%')
        .margin({ top: 12 })
        .padding(16)
        .backgroundColor('#FAFAFA')
        .borderRadius(12)
        
        Button('Reset to Default')
          .margin({ top: 20 })
          .onClick(() => {
            this.resetStyles()
          })
        
        Button('Back to Index')
          .margin({ top: 10, bottom: 20 })
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF')
  }
  
  applyTheme(themeName: string) {
    const theme = this.themes[themeName]
    if (theme) {
      this.currentTheme = themeName
      this.backgroundColor = theme.background
      this.textColor = theme.text
      this.selectedTextColor = theme.selectedText
      this.borderColor = theme.border
      this.shadowSize = theme.shadow
      this.addLog('Theme applied: ' + themeName)
    }
  }
  
  resetStyles() {
    this.fontSize = 18
    this.selectedFontSize = 22
    this.textColor = '#333333'
    this.selectedTextColor = '#007DFF'
    this.fontWeight = FontWeight.Normal
    this.selectedFontWeight = FontWeight.Bold
    this.backgroundColor = '#FFFFFF'
    this.borderColor = '#E0E0E0'
    this.borderWidth = 1
    this.borderRadius = 8
    this.currentTheme = 'light'
    this.shadowSize = 0
    this.addLog('Styles reset to default')
  }
  
  formatDate(year: number, month: number, day: number): string {
    return `${year}-${String(month + 1).padStart(2, '0')}-${String(day).padStart(2, '0')}`
  }
  
  getWeightName(weight: FontWeight): string {
    switch (weight) {
      case FontWeight.Normal: return 'Normal'
      case FontWeight.Medium: return 'Medium'
      case FontWeight.Bold: return 'Bold'
      default: return 'Unknown'
    }
  }
  
  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.logText = `[${timestamp}] ${message}\n` + this.logText
    if (this.logText.length > 5000) {
      this.logText = this.logText.substring(0, 5000)
    }
  }
}

interface ThemeConfig {
  background: string
  text: string
  selectedText: string
  border: string
  shadow: number
}