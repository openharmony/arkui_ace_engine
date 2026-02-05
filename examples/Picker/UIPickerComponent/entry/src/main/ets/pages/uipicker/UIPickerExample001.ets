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

import { LengthMetrics } from '@kit.ArkUI'

/**
 * UIPickerExample001: 基础选择器示例
 * 演示UIPickerComponent的基本用法
 */
@Component
export struct UIPickerExample001 {
  private dataArray: string[] = []

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('基础选择器示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .canLoop(true)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        console.info('UIPickerComponent item changed: ' + selectedIndex)
      })
      .onScrollStop((selectedIndex: number) => {
        console.info('UIPickerComponent scroll stopped: ' + selectedIndex)
      })

      Text('提示: 滚动选择器来选择不同的选项')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample002: 切换循环滚动和开关触控反馈
 */
@Component
export struct UIPickerExample002 {
  private dataArray: string[] = []
  @State loop: boolean = true
  @State hapticFeedback: boolean = true

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('切换循环滚动和开关触控反馈')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .canLoop(this.loop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.loop = isOn
          })
        Text('canLoop').fontSize(16)
      }
      .width('70%')
      .margin({ top: 20 })

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: true })
          .onChange((isOn: boolean) => {
            this.hapticFeedback = isOn
          })
        Text('enableHapticFeedback').fontSize(16)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 切换开关来体验不同的功能')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample003: 事件回调示例
 */
@Component
export struct UIPickerExample003 {
  private dataArray: string[] = ['待办', '进行中', '已完成', '已取消', '已延期']
  @State onChangeDesc: string = ''
  @State onScrollStopDesc: string = ''

  build() {
    Column() {
      Text('事件回调示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.onChangeDesc = 'onChange: ' + this.dataArray[selectedIndex]
      })
      .onScrollStop((selectedIndex: number) => {
        this.onScrollStopDesc = 'onScrollStop: ' + this.dataArray[selectedIndex]
      })

      Text(this.onChangeDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text(this.onScrollStopDesc)
        .fontSize(16)
        .margin({ top: 10 })

      Text('提示: 滚动选择器查看事件回调')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample004: 设置选中项索引值
 */
@Component
export struct UIPickerExample004 {
  private dataArray: string[] = []
  @State selectedIndex: number = 0

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('设置选中项索引值')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent({
        selectedIndex: this.selectedIndex
      }) {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND
      })
      .onChange((selectedIndex: number) => {
        this.selectedIndex = selectedIndex
      })
      .onScrollStop((selectedIndex: number) => {
        this.selectedIndex = selectedIndex
      })

      Text('selectedIndex: ' + this.selectedIndex)
        .fontSize(18)
        .margin({ top: 20 })

      Text('提示: 滚动选择器查看索引值变化')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample005: 自定义月份选择器
 */
@Component
export struct UIPickerExample005 {
  private fontSize: number | string | Resource = '20vp'
  private monthArray: string[] = []

  aboutToAppear(): void {
    for (let i = 1; i <= 12; i++) {
      this.monthArray.push(i + '月')
    }
  }

  build() {
    Column() {
      Text('自定义月份选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.monthArray, (item: string) => {
          Text(item)
            .fontSize(this.fontSize)
            .textAlign(TextAlign.Center)
            .fontColor(Color.Black)
        })
      }
      .width('70%')
      .canLoop(true)
      .enableHapticFeedback(false)
      .selectionIndicator({
        type: PickerIndicatorType.DIVIDER
      })
      .onChange((idx: number) => {
        console.info('UIPickerComponent item changed: ' + this.monthArray[idx])
      })
      .onScrollStop((idx: number) => {
        console.info('UIPickerComponent scroll stopped: ' + this.monthArray[idx])
      })

      Text('提示: 选择月份')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample006: 自定义地区选择器（三级联动）
 */
@Component
export struct UIPickerExample006 {
  type RegionDict = Record<string, Record<string, string[]>>

  @State provinceIndex: number = 0
  @State cityIndex: number = 0
  @State countyIndex: number = 0
  @State provinces: string[] = []
  @State cities: string[] = []
  @State counties: string[] = []

  private regionData: RegionDict = {
    '辽宁省': {
      '沈阳市': ['沈河区', '和平区', '浑南区'],
      '大连市': ['中山区', '金州区', '长海县']
    },
    '吉林省': {
      '长春市': ['南关区', '宽城区', '朝阳区'],
      '四平市': ['铁西区', '铁东区', '梨树县']
    },
    '黑龙江省': {
      '哈尔滨市': ['道里区', '道外区', '南岗区'],
      '牡丹江市': ['东安区', '西安区', '爱民区']
    }
  }

  aboutToAppear(): void {
    this.provinces = Object.keys(this.regionData)
    this.flushCityColumn()
  }

  flushCityColumn() {
    let currentProvince = this.provinces[this.provinceIndex]
    this.cities = Object.keys(this.regionData[currentProvince])
    this.cityIndex = 0
    this.flushCountyColumn()
  }

  flushCountyColumn() {
    let currentProvince = this.provinces[this.provinceIndex]
    let currentCity = this.cities[this.cityIndex]
    this.counties = this.regionData[currentProvince][currentCity]
    this.countyIndex = 0
  }

  build() {
    Column() {
      Text('自定义地区选择器')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        UIPickerComponent({
          selectedIndex: this.provinceIndex
        }) {
          ForEach(this.provinces, (province: string) => {
            Text(province)
          })
        }
        .onChange((selectedIndex: number) => {
          this.provinceIndex = selectedIndex
          this.flushCityColumn()
        })
        .onScrollStop((selectedIndex: number) => {
          this.provinceIndex = selectedIndex
        })
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .width('30%')

        UIPickerComponent({
          selectedIndex: this.cityIndex
        }) {
          ForEach(this.cities, (city: string) => {
            Text(city)
          })
        }
        .onChange((selectedIndex: number) => {
          this.cityIndex = selectedIndex
          this.flushCountyColumn()
        })
        .onScrollStop((selectedIndex: number) => {
          this.cityIndex = selectedIndex
        })
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .width('30%')

        UIPickerComponent({
          selectedIndex: this.countyIndex
        }) {
          ForEach(this.counties, (county: string) => {
            Text(county)
          })
        }
        .onChange((selectedIndex: number) => {
          this.countyIndex = selectedIndex
        })
        .onScrollStop((selectedIndex: number) => {
          this.countyIndex = selectedIndex
        })
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER
        })
        .width('30%')
      }

      Text('提示: 省市区三级联动选择')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}

/**
 * UIPickerExample007: 设置选中项指示器（背景）
 */
@Component
export struct UIPickerExample007 {
  private dataArray: string[] = []
  @State bgColor: Color = Color.Blue
  @State bgBorderRadius: LengthMetrics = LengthMetrics.vp(10)

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.dataArray.push(i.toString())
    }
  }

  build() {
    Column() {
      Text('设置选中项指示器（背景）')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      UIPickerComponent() {
        ForEach(this.dataArray, (item: string) => {
          Text(item)
        })
      }
      .width('70%')
      .height(200)
      .selectionIndicator({
        type: PickerIndicatorType.BACKGROUND,
        backgroundColor: this.bgColor,
        borderRadius: this.bgBorderRadius
      })

      Text('背景色设置')
        .fontSize(14)
        .margin({ top: 20 })

      Row() {
        Button('蓝色')
          .onClick(() => {
            this.bgColor = Color.Blue
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('绿色')
          .onClick(() => {
            this.bgColor = Color.Green
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)

        Button('红色')
          .onClick(() => {
            this.bgColor = Color.Red
          })
          .fontSize(12)
          .height(30)
          .width(73)
          .margin(2)
      }
      .width('70%')
      .margin({ top: 10 })

      Text('提示: 点击按钮切换不同的背景色')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
