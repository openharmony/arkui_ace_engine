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
struct BindClipShapeDemo {
  //存储图片资源数组，包含多个待展示的图片资源
  @State imageResource: Resource[] = [
    $r("app.media.startIcon"),
    $r("app.media.cat01"),
    $r("app.media.cloud")
  ]
  @State imgIdx: number = 0   // 图片索引
  //存储图片重复模式数组，包含四种重复方式
  @State repeatModes: ImageRepeat[] = [
    ImageRepeat.NoRepeat,    // 不重复
    ImageRepeat.X,           // 水平方向重复
    ImageRepeat.Y,           // 垂直方向重复
    ImageRepeat.XY           // 水平和垂直方向都重复
  ]
  @State repeatIdx: number = 0  // repeat 索引

  //定义图片的可调整选项，设置切片的上下左右边距
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
      // 第一个图片展示组件，显示当前索引对应的图片
      Image(this.imageResource[this.imgIdx])
        .width(300)  
        .height(300)
        .objectFit(ImageFit.Contain) // 图片适配方式：保持比例缩放以完全显示在容器内
        .borderWidth(2)
        .clipShape(new Circle({ width: '200vp', height: "200vp" }))
        .contentTransition(ContentTransitionEffect.OPACITY) // 图片切换时启用淡入淡出过渡效果
        .onClick(() => {
          // 点击时切换图片索引，通过取模实现循环切换
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })

      // 第二个图片展示组件，通过alt属性显示当前索引对应的图片（src为空时显示alt资源）
      Image("")
        .alt(this.imageResource[this.imgIdx]) // 设置替代图片资源，当src无效时显示
        .width(300) 
        .height(300)
        .objectFit(ImageFit.Contain)
        .borderWidth(2) 
        .clipShape(new Circle({ width: '200vp', height: "200vp" })) 
        .contentTransition(ContentTransitionEffect.OPACITY) // 图片切换时启用淡入淡出过渡效果
        .onClick(() => { 
          // 点击时切换图片索引，通过取模实现循环切换
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })

      // 用于切换图片重复模式的按钮，显示当前选中的重复模式
      Button(`Repeat: ${this.repeatModes[this.repeatIdx]}`)
        .onClick(() => {
          // 点击时切换重复模式索引，通过取模实现循环切换
          this.repeatIdx = (this.repeatIdx + 1) % this.repeatModes.length
        })
    }
    .width("100%")
    .height("100%")
    .justifyContent(FlexAlign.Center) 
    .alignItems(HorizontalAlign.Center) 
  }
}