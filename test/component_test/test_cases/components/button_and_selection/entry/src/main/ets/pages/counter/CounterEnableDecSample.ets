/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

//测试代码路径
import counterEnableDecTest from '../MyTest/CounterEnableDecTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CounterEnableDecSample {
  @State value: number = 0
  @State enableDec: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(counterEnableDecTest)
  }

  build() {
    Row() {
      Counter() {
        Text(this.value.toString())
      }
      .margin(100)
      .id('counterEnableDec')
      .enableDec(this.enableDec)
      .onInc(() => {
        this.value++
      })
      .onDec(() => {
        this.value--
      })

      Button('CounterEnableDec')
        .onClick(() => {
          this.enableDec = !this.enableDec
        })
    }
  }
}