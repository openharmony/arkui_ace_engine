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

@Entry
@Component
struct EllipseExample02 {
  build() {
    Column({ space: 10 }) {
      // 绘制一个 150 * 80 的椭圆
      Ellipse({ width: '150', height: '80' }) // 使用string类型
      // 绘制一个 80 * 150 的椭圆
      Ellipse({ width: 80, height: 150 }) // 使用number类型
      // 绘制一个 150 * 150 的椭圆
      Ellipse({ width: $r('app.string.EllipseWidth'), height: $r('app.string.EllipseHeight') }) // 使用Resource类型，需用户自定义
    }.width('100%')
  }
}