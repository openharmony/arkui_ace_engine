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

import { LengthMetrics } from '@kit.ArkUI'

/**
 * TextPickerExample001: 基础单列选择器示例
 * 演示TextPicker的基本用法
 */
@Component
export struct TextPickerExample001 {
  private select: number = 1
  private fruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']

  build() {
    Column() {
      Text('基础单列选择器示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits, selected: this.select })
        .onChange((value: string | string[], index: number | number[]) => {
          console.info('Picker item changed, value: ' + value + ', index: ' + index)
        })
        .onScrollStop((value: string | string[], index: number | number[]) => {
          console.info('Picker scroll stopped, value: ' + value + ', index: ' + index)
        })
        .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
          console.info('Picker item enter selected area, value: ' + value + ', index: ' + index)
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
 * TextPickerExample002: 多列选择器示例
 */
@Component
export struct TextPickerExample002 {
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private orfruits: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private pefruits: string[] = ['peach1', 'peach2', 'peach3', 'peach4']
  private multi: string[][] = [this.apfruits, this.orfruits, this.pefruits]

  build() {
    Column() {
      Text('多列选择器示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.multi })
        .onChange((value: string | string[], index: number | number[]) => {
          console.info('TextPicker 多列:onChange ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
        })
        .onScrollStop((value: string | string[], index: number |) => {
          console.info('TextPicker 多列:onScrollStop ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
        })
        .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
          console.info('TextPicker 多列:onEnterSelectedArea ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
        })

      Text('提示: 多列选择器可以同时选择多个值')
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
 * TextPickerExample003: 多列联动选择器示例
 */
@Component
export struct TextPickerExample003 {
  private cascade: TextCascadePickerRangeContent[] = [
    {
      text: '辽宁省',
      children: [{ text: '沈阳市', children: [{ text: '沈河区' }, { text: '和平区' }, { text: '浑南区' }] },
        { text: '大连市', children: [{ text: '中山区' }, { text: '金州区' }, { text: '长海县' }] }]
    },
    {
      text: '吉林省',
      children: [{ text: '长春市', children: [{ text: '南关区' }, { text: '宽城区' }, { text: '朝阳区' }] },
        { text: '四平市', children: [{ text: '铁西区' }, { text: '铁东区' }, { text: '梨树县' }] }]
    },
    {
      text: '黑龙江省',
      children: [{ text: '哈尔滨市', children: [{ text: '道里区' }, { text: '道外区' }, { text: '南岗区' }] },
        { text: '牡丹江市', children: [{ text: '东安区' }, { text: '西安区' }, { text: '爱民区' }] }]
    }
  ]

  build() {
    Column() {
      Text('多列联动选择器示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.cascade })
        .onChange((value: string | string[], index: number | number[]) => {
          console.info('TextPicker 多列联动:onChange ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
        })
        .onScrollStop((value: string | string[], index: number | number[]) => {
          console.info('TextPicker 多列联动:onScrollStop ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
        })
        .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
          console.info('TextPicker 多列联动:onEnterSelectedArea ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
        })

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
 * TextPickerExample004: 事件回调示例
 */
@Component
export struct TextPickerExample004 {
  private fruits: string[] = ['待办', '进行中', '已完成', '已取消', '已延期']
  @State onChangeDesc: string = ''
  @State onScrollStopDesc: string = ''
  @State onEnterSelectedAreaDesc: string = ''

  build() {
    Column() {
      Text('事件回调示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .onChange((value: string | string[], index: number | number[]) => {
          this.onChangeDesc = 'onChange: ' + value + ', index: ' + index
        })
        .onScrollStop((value: string | string[], index: number | number[]) => {
          this.onScrollStopDesc = 'onScrollStop: ' + value + ', index: ' + index
        })
        .onEnterSelectedArea((value: string | string[], index: number | number[]) => {
          this.onEnterSelectedAreaDesc = 'onEnterSelectedArea: ' + value + ', index: ' + index
        })

      Text(this.onChangeDesc)
        .fontSize(16)
        .margin({ top: 20 })

      Text(this.onScrollStopDesc)
        .fontSize(16)
        .margin({ top: 10 })

      Text(this.onEnterSelectedAreaDesc)
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
 * TextPickerExample005: 自定义列宽示例
 */
@Component
export struct TextPickerExample005 {
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private orfruits: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private pefruits: string[] = ['peach1', 'peach2', 'peach3', 'peach4']
  private multi: string[][] = [this.apfruits, this.orfruits, this.pefruits]

  private singleColumnWidths: LengthMetrics[] = [
    LengthMetrics.percent(50)
  ]

  private multipleColumnWidths: LengthMetrics[] = [
    LengthMetrics.vp(100),
    LengthMetrics.vp(200),
    LengthMetrics.vp(100)
  ]

  build() {
    Column() {
      Text('自定义列宽示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Text('单列选择器（50%宽度）')
        .fontSize(14)
        .margin({ bottom: 10 })

      TextPicker({ range: this.apfruits, columnWidths: this.singleColumnWidths })
        .margin({ bottom: 20 })

      Text('多列选择器（自定义宽度）')
        .fontSize(14)
        .margin({ bottom: 10 })

      TextPicker({ range: this.multi, columnWidths: this.multipleColumnWidths })

      Text('提示: 使用columnWidths属性自定义列宽')
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
 * TextPickerExample006: 设置选中项示例
 */
@Component
export struct TextPickerExample006 {
  private fruits: string[] = []
  @State selectedIndex: number = 2

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.fruits.push('选项 ' + i)
    }
  }

  build() {
    Column() {
      Text('设置选中项示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits, selected: this.selectedIndex })
        .onChange((value: string | string[], index: number | number[]) => {
          this.selectedIndex = index as number
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
 * TextPickerExample007: 禁用状态示例
 */
@Component
export struct TextPickerExample007 {
  private fruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  @State disabled: boolean = false

  build() {
    Column() {
      Text('禁用状态示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .enabled(!this.disabled)

      Row() {
        Toggle({ type: ToggleType.Switch, isOn: false })
          .onChange((isOn: boolean) => {
            this.disabled = isOn
          })
        Text('禁用选择器').fontSize(16)
      }
      .width('70%')
      .margin({ top: 20 })

      Text('提示: 切换开关来禁用/启用选择器')
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
 * TextPickerExample008: 自定义样式示例
 */
@Component
export struct TextPickerExample008 {
  private fruits: string[] = []
  @State fontSize: number = 18
  @State fontColor: Color = Color.Black

  aboutToAppear(): void {
    for (let i = 1; i <= 10; i++) {
      this.fruits.push('选项 ' + i)
    }
  }

  build() {
    Column() {
      Text('自定义样式示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      TextPicker({ range: this.fruits })
        .selectedTextStyle({
          fontSize: this.fontSize,
          color: this.fontColor
        })
        .textStyle({
          fontSize: this.fontSize - 2,
          color: '#999999'
        })

      Text('字体大小: ' + this.fontSize)
        .fontSize(14)
        .margin({ top: 20 })

      Slider({ value: this.fontSize, min: 12, max: 24, step: 1 })
        .width('70%')
        .blockColor('#007DFF')
        .onChange((value: number) => {
          this.fontSize = Math.round(value)
        })

      Text('提示: 调整字体大小和颜色')
        .fontSize(14)
        .fontColor('#999999')
        .margin({ top: 20 })
    }
    .width('100%')
    .padding(20)
    .backgroundColor('#F5F5F5')
  }
}
