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

/**
 * Image component colorFilter property examples
 */
@Entry
@Component
struct ImageColorFilterExample {
  @State imageWidth: number = 200
  @State imageHeight: number = 200

  build() {
    Column({ space: 20 }) {
      Text('ColorFilter 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 无滤镜
      Column({ space: 15 }) {
        Text('无滤镜 (原图)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .border({ width: 2, color: Color.Blue })
      }

      // 灰度滤镜
      Column({ space: 15 }) {
        Text('灰度滤镜 (brightness)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .colorFilter([1.0, 0.0, 0.0]) // 降低亮度
          .border({ width: 2, color: Color.Green })
      }

      // 反色滤镜
      Column({ space: 15 }) {
        Text('反色滤镜 (invert)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .colorFilter([-1.0, -1.0, -1.0, 0.0, -1.0, -1.0, 1.0]) // 反转
          .border({ width: 2, color: Color.Orange })
      }

      // 深褐色滤镜
      Column({ space: 15 }) {
        Text('深褐色滤镜 (sepia)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .colorFilter([0.39, 0.349, 0.272]) // 怀旧照片效果
          .border({ width: 2, color: Color.Pink })
      }

      // 自定义矩阵
      Column({ space: 15 }) {
        Text('自定义矩阵')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .colorFilter([
            1.0, 0.0, 0.0, 0.0,  // R通道
            0.0, 1.0, 0.0, 0.0,  // G通道
            0.0, 0.0, 0.0, 0.0,  // B通道
            0.0, 0.0, 0.0, 1.0   // A通道
          ]) // 增强蓝色
          .border({ width: 2, color: Color.Purple })
      }

      // 多个滤镜组合
      Column({ space: 15 }) {
        Text('组合滤镜 (灰度+反色)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .colorFilter([
            0.33, 0.33, 0.33, // 灰度
            0.0, 0.0, 0.0, 0.0,    // 保留透明度
            0.0, 0.0, 0.0, 1.0,    // 反转透明度
            1.0, 1.0, 1.0, 1.0     // 不反转RGB
          ])
          .border({ width: 2, color: Color.Red })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
