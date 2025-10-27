/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct BindImageRepeatDemo {
  // 图片资源数组：存储4张待切换的图片
  @State imageResource: Resource[] = [
    $r("app.media.ic_page_empty"),
    $r("app.media.git01"),
    $r("app.media.cat01"),
    $r("app.media.cloud")
  ]
  @State imgIdx: number = 0 
  // 图片重复模式数组：包含4种重复方式（不重复、水平、垂直、双向）
  @State repeatModes: ImageRepeat[] = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY
  ]
  @State repeatIdx: number = 0

  // 图片切片调整参数
  @State resizeMode: ResizableOptions = {
    slice: {
      top: 30,
      bottom: 30,
      left: 30,
      right: 30
    }
  }

  build() {
    Column({ space: 20 }) {
      // 主图片展示：绑定当前索引的图片和重复模式
      Image(this.imageResource[this.imgIdx])
        .width(300)
        .height(300)
        .objectRepeat(this.repeatModes[this.repeatIdx]) // 应用当前选择的重复模式
        .objectFit(ImageFit.Contain)
        .borderWidth(2)
        .onClick(() => {
          // 点击切换图片：通过取模实现数组循环
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })

      Image("")
        .alt(this.imageResource[this.imgIdx])
        .width(300)
        .height(300)
        .objectRepeat(this.repeatModes[this.repeatIdx]) // 应用当前选择的重复模式
        .resizable(this.resizeMode)
        .objectFit(ImageFit.Contain)
        .borderWidth(2)
        .contentTransition(ContentTransitionEffect.OPACITY)
        .onClick(() => {
          // 点击切换图片
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })

      // 重复模式切换按钮：显示当前模式，点击循环切换
      Button(`Repeat: ${this.repeatModes[this.repeatIdx]}`)
        .onClick(() => {
          this.repeatIdx = (this.repeatIdx + 1) % this.repeatModes.length
        })
    }
    .width("100%")
    .height("100%")
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}