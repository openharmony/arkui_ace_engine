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

import { UIPickerExample001 } from './uipicker/UIPickerExample001'
import { UIPickerExample002 } from './uipicker/UIPickerExample002'
import { UIPickerExample003 } from './uipicker/UIPickerExample003'
import { UIPickerExample004 } from './uipicker/UIPickerExample004'
import { UIPickerExample005 } from './uipicker/UIPickerExample005'
import { UIPickerExample006 } from './uipicker/UIPickerExample006'
import { UIPickerExample007 } from './uipicker/UIPickerExample007'
import { UIPickerExample008 } from './uipicker/UIPickerExample008'
import { UIPickerExample009 } from './uipicker/UIPickerExample009'
import { UIPickerExample010 } from './uipicker/UIPickerExample010'
import { UIPickerExample011 } from './uipicker/UIPickerExample011'
import { UIPickerExample012 } from './uipicker/UIPickerExample012'

@Entry
@Component
struct Index {
  @State currentExample: number = 0
  private exampleTitles: string[] = [
    'UIPickerExample001: 基础选择器',
    'UIPickerExample002: 多列选择器',
    'UIPickerExample003: 联动选择器',
    'UIPickerExample004: 自定义样式选择器',
    'UIPickerExample005: 事件回调选择器',
    'UIPickerExample006: 禁用状态选择器',
    'UIPickerExample007: 动态数据选择器',
    'UIPickerExample008: 性能测试选择器',
    'UIPickerExample009: 无障碍支持选择器',
    'UIPickerExample010: 边缘对齐选择器',
    'UIPickerExample011: 文本样式选择器',
    'UIPickerExample012: 高级功能选择器'
  ]

  build() {
    Column() {
      Text('UIPickerComponent Demo')
        .fontSize(28)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 20 })

      Scroll() {
        Column() {
          ForEach(this.exampleTitles, (title: string, index: number) => {
            Button(title)
              .width('90%')
              .margin({ bottom: 10 })
              .onClick(() => {
                this.currentExample = index
              })
              .backgroundColor(this.currentExample === index ? '#007DFF' : '#F1F3F5')
              .fontColor(this.currentExample === index ? '#FFFFFF' : '#000000')
          })
        }
        .width('100%')
      }
      .layoutWeight(1)
      .margin({ bottom: 20 })

      if (this.currentExample === 0) {
        UIPickerExample001()
      } else if (this.currentExample === 1) {
        UIPickerExample002()
      } else if (this.currentExample === 2) {
        UIPickerExample003()
      } else if (this.currentExample === 3) {
        UIPickerExample004()
      } else if (this.currentExample === 4) {
        UIPickerExample005()
      } else if (this.currentExample === 5) {
        UIPickerExample006()
      } else if (this.currentExample === 6) {
        UIPickerExample007()
      } else if (this.currentExample === 7) {
        UIPickerExample008()
      } else if (this.currentExample === 8) {
        UIPickerExample009()
      } else if (this.currentExample === 9) {
        UIPickerExample010()
      } else if (this.currentExample === 10) {
        UIPickerExample011()
      } else if (this.currentExample === 11) {
        UIPickerExample012()
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}
