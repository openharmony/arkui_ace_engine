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
 * Image component memory usage control examples
 */
@Entry
@Component
struct ImageMemoryUsageExample {
  @State recycleEnabled: boolean = false

  build() {
    Column({ space: 20 }) {
      Text('内存使用控制示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 回收不可见图片内存
      Column({ space: 15 }) {
        Text('回收不可见图片内存')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Green })
        Text('图片在不可见时自动回收，避免内存占用')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      Divider().strokeWidth(2)

      // 控制开关
      Row({ space: 20 }) {
        Text('控制回收')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.recycleEnabled })
          .onChange((value: boolean) => {
            this.recycleEnabled = value
          })
        Button(this.recycleEnabled ? '已启用回收' : '已禁用回收')
          .fontSize(14)
      }

      // 图片缓存
      Column({ space: 15 }) {
        Text('图片缓存机制')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Blue })
        Text('系统会缓存已加载的图片，下次加载更快')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // 内存占用说明
      Column({ space: 15 }) {
        Text('内存占用:')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Red })
        Text('大图会占用较多内存，建议在不需要时释放')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      Divider().strokeWidth(2)

      Text('recycleEnabled 属性控制是否回收不可见图片内存')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
