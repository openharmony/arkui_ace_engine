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
// 测试代码路径
import shapeAntiAliasTest from '../MyTest/ShapeAntiAliasTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeAntiAliasSample {
  @State shapeAntiAliasBool: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(shapeAntiAliasTest)
  }

  build() {
    Column({ space: 10 }) {
      Shape() {
        Rect().width(300).height(50)
      }
      .width(350)
      .height(80)
      .viewPort({
        x: 0,
        y: 0,
        width: 320,
        height: 70
      })
      .antiAlias(this.shapeAntiAliasBool)
      .id('shapeAntiAlias')

      Button('ShapeAntiAlias')
        .onClick(() => {
          this.shapeAntiAliasBool = !this.shapeAntiAliasBool
        })
    }
  }
}