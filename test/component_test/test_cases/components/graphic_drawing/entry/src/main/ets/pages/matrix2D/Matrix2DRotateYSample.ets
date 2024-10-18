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
import matrix2DRotateYTest from '../MyTest/Matrix2DRotateYTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct Matrix2DRotateYSample {
  @State message: string = 'Matrix2D RotateY'

  aboutToAppear(): void {
    loadComponentTestEntry(matrix2DRotateYTest)
  }

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Button("Matrix2DRotateY")
          .onClick(() => {
            let matrix: Matrix2D = new Matrix2D()
            matrix.rotateY = Math.cos(45 / Math.PI)
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}