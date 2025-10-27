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
struct BindImageResizableDemo {
  // 图片资源数组：存储3张待切换的图片
  @State imageResource: Resource[] = [
    $r("app.media.startIcon"),
    $r("app.media.cat01"),
    $r("app.media.cloud")
  ]
  @State imgIdx: number = 0   // 图片索引：控制当前显示的图片

  // 图片切片调整参数：定义上下左右的切片边距（用于resizable属性）
  @State resizeMode: ResizableOptions = {
    slice: {
      top: "50px",
      bottom: "150px",
      left: "100px",
      right: "70px"
    }
  }

  build() {
    // 垂直布局容器：子组件间距20，整体居中对齐
    Column({ space: 20 }) {
      // 应用切片调整的图片
      Image(this.imageResource[this.imgIdx])
        .width(300)
        .height(300)
        .resizable(this.resizeMode) // 启用图片切片调整，应用resizeMode配置
        .objectFit(ImageFit.Cover) // 图片适配方式：覆盖容器（保持比例填充）
        .borderWidth(2)
        .contentTransition(ContentTransitionEffect.OPACITY) // 切换时淡入淡出
        .onClick(() => {
          // 点击循环切换图片
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })

      // 使用alt属性显示的图片（src为空时生效）
      Image("")
        .alt(this.imageResource[this.imgIdx])
        .width(300)
        .height(300)
        .objectFit(ImageFit.Cover)
        .borderWidth(2)
        .contentTransition(ContentTransitionEffect.OPACITY)
        .onClick(() => {
          // 点击循环切换图片
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })
    }
    .width("100%")
    .height("100%")
    .justifyContent(FlexAlign.Center) // 垂直居中
    .alignItems(HorizontalAlign.Center) // 水平居中
  }
}