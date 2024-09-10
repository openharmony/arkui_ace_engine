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
import matrix2DTranslateXTest from '../MyTest/Matrix2DTranslateXTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct Matrix2DTranslateXSample {
  @State message: string = 'Matrix2D TranslateX'

  aboutToAppear(): void {
    loadComponentTestEntry(matrix2DTranslateXTest)
  }

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Button("Matrix2DTranslateX")
          .onClick(() => {
            let matrix: Matrix2D = new Matrix2D()
            matrix.translateX = 10
          })
      }.width('100%')
    }.height('100%')
  }
}