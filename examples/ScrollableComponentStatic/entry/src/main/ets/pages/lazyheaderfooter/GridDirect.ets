'use static'

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
import {
  Entry,
  Component,
  Column,
  ColumnOptions,
  Scroll,
  Text,
  Color,
  FontWeight,
  TextAlign,
  EdgeEffect,
  LazyForEach,
  LazyVGridLayout,
  LazyVGridLayoutAttribute,
} from '@ohos.arkui.component'
import { LazyDataSource } from './DataSource'

// Diagnostic page: LazyVGridLayout placed DIRECTLY under Scroll (no LazyColumnLayout nesting).
// If items render here, the static grid + LazyForEach work standalone and the bug is the
// nested-under-LazyColumnLayout measurement. If items are still 0-size, the static grid item
// path itself differs from the 1.1 implementation.
@Entry
@Component
struct GridDirect {
  private arr: LazyDataSource = new LazyDataSource()

  aboutToAppear(): void {
    for (let i: int = 0; i < 30; i++) {
      this.arr.pushData(i.toString())
    }
  }

  build(): void {
    Column(undefined) {
      Text('GridDirect: LazyVGridLayout 直接在 Scroll 下（无 LazyColumnLayout 嵌套）')
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 12, bottom: 8 })

      Scroll() {
        LazyVGridLayout() {
          LazyForEach(this.arr, (item: string) => {
            Text('Direct grid item ' + item)
              .height(80)
              .width('100%')
              .borderWidth(1)
              .backgroundColor(Color.Orange)
              .textAlign(TextAlign.Center)
          }, (item: string): string => item)
        }
        .columnsTemplate('1fr')
      }
      .width('92%')
      .layoutWeight(1)
      .borderWidth(1)
      .edgeEffect(EdgeEffect.Spring)
    }
    .width('100%')
    .height('100%')
  }
}
