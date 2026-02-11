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
struct BasicContextMenuExample1 {
  build() {
    Column({ space: 20 }) {
      Text('基础右键菜单示例')
        .fontSize(18)
        .fontColor('#333333')
        .padding(20)

      Text('长按我触发菜单')
        .fontSize(16)
        .width('80%')
        .height(60)
        .backgroundColor('#FF5722')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '复制' })
              .onClick(() => {
                console.info('复制被点击')
              })
            MenuItem({ content: '粘贴' })
              .onClick(() => {
                console.info('粘贴被点击')
              })
            MenuItem({ content: '删除' })
              .onClick(() => {
                console.info('删除被点击')
              })
          }
        })
    }
    .width('100%')
    .height('100%')
    .padding({ top: 50 })
  }
}

// 示例 1-2: 带有选项配置的基础用法
@Entry
@Component
struct BasicContextMenuExample2 {
  build() {
    Column({ space: 20 }) {
      Text('带有选项配置的右键菜单')
        .fontSize(18)
        .fontColor('#333333')
        .padding(20)

      Text('右键或长按我')
        .fontSize(16)
        .width('80%')
        .height(60)
        .backgroundColor('#2196F3')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '编辑' })
              .onClick(() => {
                console.info('编辑操作')
              })
            MenuItem({ content: '分享' })
              .onClick(() => {
                console.info('分享操作')
              })
            MenuItem({ content: '收藏' })
              .onClick(() => {
                console.info('收藏操作')
              })
          }
        }, {
          placement: Placement.Bottom,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .padding({ top: 50 })
  }
}

// 示例 1-3: 使用 undefined 解除绑定
@Entry
@Component
struct BasicContextMenuExample3 {
  @State isMenuBound: boolean = true

  build() {
    Column({ space: 20 }) {
      Text('动态绑定/解绑菜单')
        .fontSize(18)
        .fontColor('#333333')
        .padding(20)

      Text(this.isMenuBound ? '长按我有菜单' : '菜单已解绑')
        .fontSize(16)
        .width('80%')
        .height(60)
        .backgroundColor(this.isMenuBound ? '#4CAF50' : '#9E9E9E')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse(this.isMenuBound ? (responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '选项1' })
            MenuItem({ content: '选项2' })
          }
        } : undefined, {
          placement: Placement.Right
        } as ContextMenuOptions)

      Button(this.isMenuBound ? '解除菜单绑定' : '绑定菜单')
        .onClick(() => {
          this.isMenuBound = !this.isMenuBound
        })
    }
    .width('100%')
    .height('100%')
    .padding({ top: 50 })
  }
}

// ============================================
// 第二部分：Placement 位置配置示例
// ============================================

// 示例 2-1: Placement.Top 配置
@Entry
@Component
struct PlacementTopExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.Top 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在上方显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#E91E63')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '顶部选项1' })
            MenuItem({ content: '顶部选项2' })
            MenuItem({ content: '顶部选项3' })
          }
        }, {
          placement: Placement.Top,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-2: Placement.Bottom 配置
@Entry
@Component
struct PlacementBottomExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.Bottom 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在下方显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#9C27B0')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '底部选项1' })
            MenuItem({ content: '底部选项2' })
          }
        }, {
          placement: Placement.Bottom,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-3: Placement.Left 配置
@Entry
@Component
struct PlacementLeftExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.Left 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在左侧显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#673AB7')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '左侧选项1' })
            MenuItem({ content: '左侧选项2' })
          }
        }, {
          placement: Placement.Left,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-4: Placement.Right 配置
@Entry
@Component
struct PlacementRightExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.Right 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在右侧显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#3F51B5')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '右侧选项1' })
            MenuItem({ content: '右侧选项2' })
          }
        }, {
          placement: Placement.Right,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-5: Placement.TopLeft 配置
@Entry
@Component
struct PlacementTopLeftExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.TopLeft 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在左上角显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#009688')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '左上选项1' })
            MenuItem({ content: '左上选项2' })
          }
        }, {
          placement: Placement.TopLeft,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-6: Placement.TopRight 配置
@Entry
@Component
struct PlacementTopRightExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.TopRight 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在右上角显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#00BCD4')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '右上选项1' })
            MenuItem({ content: '右上选项2' })
          }
        }, {
          placement: Placement.TopRight,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-7: Placement.BottomLeft 配置
@Entry
@Component
struct PlacementBottomLeftExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.BottomLeft 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在左下角显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#FF9800')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '左下选项1' })
            MenuItem({ content: '左下选项2' })
          }
        }, {
          placement: Placement.BottomLeft,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 2-8: Placement.BottomRight 配置
@Entry
@Component
struct PlacementBottomRightExample {
  build() {
    Column({ space: 20 }) {
      Text('Placement.BottomRight 示例')
        .fontSize(18)
        .padding(20)

      Text('菜单在右下角显示')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#FF5722')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '右下选项1' })
            MenuItem({ content: '右下选项2' })
          }
        }, {
          placement: Placement.BottomRight,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第三部分：Offset 偏移配置示例
// ============================================

// 示例 3-1: 简单偏移配置
@Entry
@Component
struct OffsetExample1 {
  build() {
    Column({ space: 20 }) {
      Text('Offset 偏移示例')
        .fontSize(18)
        .padding(20)

      Text('偏移 x:10, y:10')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#795548')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '偏移选项1' })
            MenuItem({ content: '偏移选项2' })
          }
        }, {
          placement: Placement.Bottom,
          offset: { x: 10, y: 10 }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 3-2: 较大偏移配置
@Entry
@Component
struct OffsetExample2 {
  build() {
    Column({ space: 20 }) {
      Text('较大偏移示例')
        .fontSize(18)
        .padding(20)

      Text('偏移 x:50, y:30')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#607D8B')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '大偏移选项1' })
            MenuItem({ content: '大偏移选项2' })
          }
        }, {
          placement: Placement.Right,
          offset: { x: 50, y: 30 }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 3-3: 负偏移配置
@Entry
@Component
struct OffsetExample3 {
  build() {
    Column({ space: 20 }) {
      Text('负偏移示例')
        .fontSize(18)
        .padding(20)

      Text('偏移 x:-20, y:-20')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#8BC34A')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '负偏移选项1' })
            MenuItem({ content: '负偏移选项2' })
          }
        }, {
          placement: Placement.Bottom,
          offset: { x: -20, y: -20 }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第四部分：箭头配置示例
// ============================================

// 示例 4-1: 启用箭头
@Entry
@Component
struct ArrowEnabledExample {
  build() {
    Column({ space: 20 }) {
      Text('启用箭头示例')
        .fontSize(18)
        .padding(20)

      Text('带箭头的菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#CDDC39')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '带箭头选项1' })
            MenuItem({ content: '带箭头选项2' })
            MenuItem({ content: '带箭头选项3' })
          }
        }, {
          placement: Placement.Top,
          enableArrow: true
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 4-2: 禁用箭头
@Entry
@Component
struct ArrowDisabledExample {
  build() {
    Column({ space: 20 }) {
      Text('禁用箭头示例')
        .fontSize(18)
        .padding(20)

      Text('不带箭头的菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#FFEB3B')
        .fontColor('#333333')
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '无箭头选项1' })
            MenuItem({ content: '无箭头选项2' })
          }
        }, {
          placement: Placement.Bottom,
          enableArrow: false
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 4-3: 箭头偏移配置
@Entry
@Component
struct ArrowOffsetExample {
  build() {
    Column({ space: 20 }) {
      Text('箭头偏移示例')
        .fontSize(18)
        .padding(20)

      Text('箭头偏移 30vp')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#FFC107')
        .fontColor('#333333')
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '箭头偏移选项1' })
            MenuItem({ content: '箭头偏移选项2' })
          }
        }, {
          placement: Placement.Top,
          enableArrow: true,
          arrowOffset: 30
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第五部分：回调函数示例
// ============================================

// 示例 5-1: onAppear 回调
@Entry
@Component
struct OnAppearExample {
  @State appearCount: number = 0

  build() {
    Column({ space: 20 }) {
      Text('onAppear 回调示例')
        .fontSize(18)
        .padding(20)

      Text(`菜单显示次数: ${this.appearCount}`)
        .fontSize(16)
        .fontColor('#FF5722')

      Text('长按我触发菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#2196F3')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '选项1' })
            MenuItem({ content: '选项2' })
          }
        }, {
          placement: Placement.Bottom,
          onAppear: () => {
            this.appearCount++
            console.info('菜单已显示')
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 5-2: onDisappear 回调
@Entry
@Component
struct OnDisappearExample {
  @State disappearCount: number = 0

  build() {
    Column({ space: 20 }) {
      Text('onDisappear 回调示例')
        .fontSize(18)
        .padding(20)

      Text(`菜单隐藏次数: ${this.disappearCount}`)
        .fontSize(16)
        .fontColor('#FF5722')

      Text('长按我触发菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#4CAF50')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '选项1' })
            MenuItem({ content: '选项2' })
          }
        }, {
          placement: Placement.Bottom,
          onDisappear: () => {
            this.disappearCount++
            console.info('菜单已隐藏')
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 5-3: aboutToAppear 回调
@Entry
@Component
struct AboutToAppearExample {
  @State aboutToAppearCount: number = 0

  build() {
    Column({ space: 20 }) {
      Text('aboutToAppear 回调示例')
        .fontSize(18)
        .padding(20)

      Text(`菜单即将显示次数: ${this.aboutToAppearCount}`)
        .fontSize(16)
        .fontColor('#FF5722')

      Text('长按我触发菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#9C27B0')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '选项1' })
            MenuItem({ content: '选项2' })
          }
        }, {
          placement: Placement.Bottom,
          aboutToAppear: () => {
            this.aboutToAppearCount++
            console.info('菜单即将显示')
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 5-4: aboutToDisappear 回调
@Entry
@Component
struct AboutToDisappearExample {
  @State aboutToDisappearCount: number = 0

  build() {
    Column({ space: 20 }) {
      Text('aboutToDisappear 回调示例')
        .fontSize(18)
        .padding(20)

      Text(`菜单即将隐藏次数: ${this.aboutToDisappearCount}`)
        .fontSize(16)
        .fontColor('#FF5722')

      Text('长按我触发菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#FF9800')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '选项1' })
            MenuItem({ content: '选项2' })
          }
        }, {
          placement: Placement.Bottom,
          aboutToDisappear: () => {
            this.aboutToDisappearCount++
            console.info('菜单即将隐藏')
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 5-5: 所有回调函数组合使用
@Entry
@Component
struct AllCallbacksExample {
  @State statusMessage: string = '等待操作...'

  build() {
    Column({ space: 20 }) {
      Text('所有回调函数示例')
        .fontSize(18)
        .padding(20)

      Text(this.statusMessage)
        .fontSize(14)
        .fontColor('#FF5722')
        .width('90%')
        .textAlign(TextAlign.Center)

      Text('长按我触发菜单')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#00BCD4')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '选项1' })
            MenuItem({ content: '选项2' })
          }
        }, {
          placement: Placement.Bottom,
          aboutToAppear: () => {
            this.statusMessage = '菜单即将显示...'
            console.info('aboutToAppear')
          },
          onAppear: () => {
            this.statusMessage = '菜单已显示！'
            console.info('onAppear')
          },
          aboutToDisappear: () => {
            this.statusMessage = '菜单即将隐藏...'
            console.info('aboutToDisappear')
          },
          onDisappear: () => {
            this.statusMessage = '菜单已隐藏！'
            console.info('onDisappear')
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第六部分：圆角配置示例
// ============================================

// 示例 6-1: 基础圆角配置
@Entry
@Component
struct BorderRadiusExample1 {
  build() {
    Column({ space: 20 }) {
      Text('基础圆角配置')
        .fontSize(18)
        .padding(20)

      Text('菜单圆角 20vp')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#E91E63')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '圆角选项1' })
            MenuItem({ content: '圆角选项2' })
            MenuItem({ content: '圆角选项3' })
          }
        }, {
          placement: Placement.Bottom,
          borderRadius: 20
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 6-2: 小圆角配置
@Entry
@Component
struct BorderRadiusExample2 {
  build() {
    Column({ space: 20 }) {
      Text('小圆角配置')
        .fontSize(18)
        .padding(20)

      Text('菜单圆角 5vp')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#9C27B0')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '小圆角选项1' })
            MenuItem({ content: '小圆角选项2' })
          }
        }, {
          placement: Placement.Bottom,
          borderRadius: 5
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 6-3: 大圆角配置
@Entry
@Component
struct BorderRadiusExample3 {
  build() {
    Column({ space: 20 }) {
      Text('大圆角配置')
        .fontSize(18)
        .padding(20)

      Text('菜单圆角 30vp')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#673AB7')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '大圆角选项1' })
            MenuItem({ content: '大圆角选项2' })
          }
        }, {
          placement: Placement.Bottom,
          borderRadius: 30
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第七部分：预览模式示例
// ============================================

// 示例 7-1: MenuPreviewMode.NONE
@Entry
@Component
struct PreviewNoneExample {
  build() {
    Column({ space: 20 }) {
      Text('预览模式 NONE 示例')
        .fontSize(18)
        .padding(20)

      Text('无预览内容')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#3F51B5')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '无预览选项1' })
            MenuItem({ content: '无预览选项2' })
          }
        }, {
          placement: Placement.Bottom,
          preview: MenuPreviewMode.NONE
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 7-2: MenuPreviewMode.IMAGE
@Entry
@Component
struct PreviewImageExample {
  build() {
    Column({ space: 20 }) {
      Text('预览模式 IMAGE 示例')
        .fontSize(18)
        .padding(20)

      Text('显示组件截图预览')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#2196F3')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '图片预览选项1' })
            MenuItem({ content: '图片预览选项2' })
          }
        }, {
          placement: Placement.Bottom,
          preview: MenuPreviewMode.IMAGE
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 7-3: 自定义预览内容
@Entry
@Component
struct CustomPreviewExample {
  @Builder
  customPreview() {
    Column() {
      Image($r('app.media.icon'))
        .width(100)
        .height(100)
        .borderRadius(8)
      Text('自定义预览')
        .fontSize(14)
        .margin({ top: 10 })
    }
    .padding(15)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  build() {
    Column({ space: 20 }) {
      Text('自定义预览示例')
        .fontSize(18)
        .padding(20)

      Text('自定义预览内容')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#009688')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '自定义选项1' })
            MenuItem({ content: '自定义选项2' })
          }
        }, {
          placement: Placement.Bottom,
          preview: this.customPreview
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第八部分：动画配置示例
// ============================================

// 示例 8-1: 自定义缩放动画
@Entry
@Component
struct AnimationScaleExample {
  build() {
    Column({ space: 20 }) {
      Text('缩放动画配置示例')
        .fontSize(18)
        .padding(20)

      Text('缩放从 0.8 到 1.2')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#FF5722')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '动画选项1' })
            MenuItem({ content: '动画选项2' })
          }
        }, {
          placement: Placement.Bottom,
          preview: MenuPreviewMode.IMAGE,
          previewAnimationOptions: {
            scale: [0.8, 1.2]
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// 示例 8-2: 大幅度缩放动画
@Entry
@Component
struct AnimationLargeScaleExample {
  build() {
    Column({ space: 20 }) {
      Text('大幅度缩放动画示例')
        .fontSize(18)
        .padding(20)

      Text('缩放从 0.5 到 1.5')
        .fontSize(16)
        .width('70%')
        .height(60)
        .backgroundColor('#E91E63')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(8)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '大缩放选项1' })
            MenuItem({ content: '大缩放选项2' })
          }
        }, {
          placement: Placement.Bottom,
          preview: MenuPreviewMode.IMAGE,
          previewAnimationOptions: {
            scale: [0.5, 1.5]
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}

// ============================================
// 第九部分：实际应用场景示例
// ============================================

// 示例 9-1: 文件管理器右键菜单
@Entry
@Component
struct FileContextMenuExample {
  @State selectedFileName: string = '未选择'
  @State lastAction: string = ''

  build() {
    Column({ space: 15 }) {
      Text('文件管理器右键菜单')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      Row() {
        Image($r('sys.media.ohos_ic_public_folder'))
          .width(40)
          .height(40)
        Text('我的文档')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .width('90%')
      .height(60)
      .padding({ left: 15 })
      .backgroundColor('#F5F5F5')
      .borderRadius(8)
      .bindContextMenuWithResponse((responseType: ResponseType) => {
        Menu() {
          MenuItem({
            content: '打开',
            startIcon: $r('sys.media.ohos_ic_public_folder')
          })
            .onClick(() => {
              this.selectedFileName = '我的文档'
              this.lastAction = '打开'
            })

          MenuItem({
            content: '重命名',
            startIcon: $r('sys.media.ohos_ic_public_edit')
          })
            .onClick(() => {
              this.selectedFileName = '我的文档'
              this.lastAction = '重命名'
            })

          MenuItem({
            content: '复制',
            startIcon: $r('sys.media.ohos_ic_public_copy')
          })
            .onClick(() => {
              this.selectedFileName = '我的文档'
              this.lastAction = '复制'
            })

          MenuItem({
            content: '剪切',
            startIcon: $r('sys.media.ohos_ic_public_cut')
          })
            .onClick(() => {
              this.selectedFileName = '我的文档'
              this.lastAction = '剪切'
            })

          MenuItem({
            content: '删除',
            startIcon: $r('sys.media.ohos_ic_public_delete')
          })
            .onClick(() => {
              this.selectedFileName = '我的文档'
              this.lastAction = '删除'
            })

          MenuItem({
            content: '属性',
            startIcon: $r('sys.media.ohos_ic_public_info')
          })
            .onClick(() => {
              this.selectedFileName = '我的文档'
              this.lastAction = '属性'
            })
        }
      }, {
        placement: Placement.BottomLeft,
        enableArrow: false
      } as ContextMenuOptions)

      Divider()
        .margin({ top: 10, bottom: 10 })

      Text(`选中文件: ${this.selectedFileName}`)
        .fontSize(14)
        .fontColor('#666666')

      Text(`上次操作: ${this.lastAction}`)
        .fontSize(14)
        .fontColor('#FF5722')
    }
    .width('100%')
    .height('100%')
    .padding({ top: 30 })
  }
}

// 示例 9-2: 聊天应用消息菜单
@Entry
@Component
struct ChatMessageContextMenuExample {
  @State actionMessage: string = ''

  build() {
    Column({ space: 15 }) {
      Text('聊天消息菜单')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      // 消息气泡 - 发送方
      Row() {
        Column() {
          Text('你好，最近怎么样？')
            .fontSize(15)
            .fontColor(Color.White)
        }
        .padding(12)
        .backgroundColor('#2196F3')
        .borderRadius({ topLeft: 12, topRight: 12, bottomLeft: 12, bottomRight: 4 })
      }
      .width('90%')
      .justifyContent(FlexAlign.End)
      .bindContextMenuWithResponse((responseType: ResponseType) => {
        Menu() {
          MenuItem({ content: '复制' })
            .onClick(() => {
              this.actionMessage = '复制消息: 你好，最近怎么样？'
            })

          MenuItem({ content: '转发' })
            .onClick(() => {
              this.actionMessage = '转发消息'
            })

          MenuItem({ content: '收藏' })
            .onClick(() => {
              this.actionMessage = '收藏消息'
            })

          MenuItem({ content: '删除' })
            .onClick(() => {
              this.actionMessage = '删除消息'
            })

          MenuItem({ content: '撤回' })
            .onClick(() => {
              this.actionMessage = '撤回消息'
            })

          MenuItem({ content: '多选' })
            .onClick(() => {
              this.actionMessage = '进入多选模式'
            })
        }
      }, {
        placement: Placement.Top,
        enableArrow: false
      } as ContextMenuOptions)

      // 消息气泡 - 接收方
      Row() {
        Column() {
          Text('我很好，谢谢关心！')
            .fontSize(15)
            .fontColor('#333333')
        }
        .padding(12)
        .backgroundColor('#FFFFFF')
        .borderRadius({ topLeft: 12, topRight: 12, bottomLeft: 4, bottomRight: 12 })
        .border({ width: 1, color: '#E0E0E0' })
      }
      .width('90%')
      .justifyContent(FlexAlign.Start)
      .bindContextMenuWithResponse((responseType: ResponseType) => {
        Menu() {
          MenuItem({ content: '复制' })
            .onClick(() => {
              this.actionMessage = '复制消息: 我很好，谢谢关心！'
            })

          MenuItem({ content: '引用' })
            .onClick(() => {
              this.actionMessage = '引用消息'
            })

          MenuItem({ content: '收藏' })
            .onClick(() => {
              this.actionMessage = '收藏消息'
            })
        }
      }, {
        placement: Placement.Top,
        enableArrow: false
      } as ContextMenuOptions)

      if (this.actionMessage !== '') {
        Text(this.actionMessage)
          .fontSize(14)
          .fontColor('#FF5722')
          .margin({ top: 20 })
      }
    }
    .width('100%')
    .height('100%')
    .padding({ top: 30 })
  }
}

// 示例 9-3: 图片编辑器右键菜单
@Entry
@Component
struct ImageEditorContextMenuExample {
  @State editAction: string = '等待操作...'

  build() {
    Column({ space: 15 }) {
      Text('图片编辑器菜单')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      Stack() {
        Image($r('app.media.icon'))
          .width('80%')
          .height(300)
          .objectFit(ImageFit.Contain)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
          .bindContextMenuWithResponse((responseType: ResponseType) => {
            Menu() {
              MenuItem({ content: '旋转90度' })
                .onClick(() => {
                  this.editAction = '旋转90度'
                })

              MenuItem({ content: '翻转' })
                .onClick(() => {
                  this.editAction = '翻转图片'
                })

              MenuItem({ content: '裁剪' })
                .onClick(() => {
                  this.editAction = '裁剪图片'
                })

              MenuItem({ content: '调整' })
                .onClick(() => {
                  this.editAction = '调整大小'
                })

              MenuItem({ content: '滤镜' })
                .onClick(() => {
                  this.editAction = '应用滤镜'
                })

              MenuItem({ content: '水印' })
                .onClick(() => {
                  this.editAction = '添加水印'
                })

              MenuItem({ content: '导出' })
                .onClick(() => {
                  this.editAction = '导出图片'
                })
            }
          }, {
            placement: Placement.Bottom,
            preview: MenuPreviewMode.IMAGE,
            previewBorderRadius: 12
          } as ContextMenuOptions)
      }
      .width('100%')
      .height(350)

      Text(this.editAction)
        .fontSize(16)
        .fontColor('#2196F3')
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
  }
}

// 示例 9-4: 任务列表右键菜单
@Entry
@Component
struct TaskListContextMenuExample {
  @State tasks: Array<string> = [
    '完成项目文档',
    '修复登录Bug',
    '优化性能',
    'Code Review'
  ]
  @State message: string = ''

  build() {
    Column({ space: 10 }) {
      Text('任务列表')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      List({ space: 10 }) {
        ForEach(this.tasks, (task: string, index: number) => {
          ListItem() {
            Row() {
              Text(`${index + 1}. ${task}`)
                .fontSize(15)
                .layoutWeight(1)
            }
            .width('100%')
            .height(50)
            .padding({ left: 15, right: 15 })
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .shadow({ radius: 3, color: '#E0E0E0' })
            .bindContextMenuWithResponse((responseType: ResponseType) => {
              Menu() {
                MenuItem({ content: '开始任务' })
                  .onClick(() => {
                    this.message = `开始任务: ${task}`
                  })

                MenuItem({ content: '标记完成' })
                  .onClick(() => {
                    this.message = `完成任务: ${task}`
                  })

                MenuItem({ content: '编辑' })
                  .onClick(() => {
                    this.message = `编辑任务: ${task}`
                  })

                MenuItem({ content: '复制任务' })
                  .onClick(() => {
                    this.message = `复制任务: ${task}`
                  })

                MenuItem({ content: '删除' })
                  .onClick(() => {
                    this.message = `删除任务: ${task}`
                  })
              }
            }, {
              placement: Placement.BottomLeft
            } as ContextMenuOptions)
          }
        })
      }
      .width('90%')
      .layoutWeight(1)

      if (this.message !== '') {
        Text(this.message)
          .fontSize(14)
          .fontColor('#FF5722')
          .padding(10)
      }
    }
    .width('100%')
    .height('100%')
  }
}

// 示例 9-5: 音乐播放器播放列表菜单
@Entry
@Component
struct MusicPlayerContextMenuExample {
  @State songs: Array<string> = [
    '歌曲1 - 演唱者A',
    '歌曲2 - 演唱者B',
    '歌曲3 - 演唱者C',
    '歌曲4 - 演唱者D'
  ]
  @State currentAction: string = ''

  build() {
    Column({ space: 10 }) {
      Text('播放列表')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      List({ space: 8 }) {
        ForEach(this.songs, (song: string, index: number) => {
          ListItem() {
            Row({ space: 10 }) {
              Text(`${index + 1}`)
                .fontSize(14)
                .fontColor('#999999')
                .width(30)

              Text(song)
                .fontSize(15)
                .layoutWeight(1)

              Image($r('sys.media.ohos_ic_public_play'))
                .width(24)
                .height(24)
            }
            .width('100%')
            .height(55)
            .padding({ left: 15, right: 15 })
            .backgroundColor(index % 2 === 0 ? '#F9F9F9' : '#FFFFFF')
            .borderRadius(8)
            .bindContextMenuWithResponse((responseType: ResponseType) => {
              Menu() {
                MenuItem({ content: '立即播放' })
                  .onClick(() => {
                    this.currentAction = `播放: ${song}`
                  })

                MenuItem({ content: '添加到播放队列' })
                  .onClick(() => {
                    this.currentAction = `已添加: ${song}`
                  })

                MenuItem({ content: '添加到收藏' })
                  .onClick(() => {
                    this.currentAction = `收藏: ${song}`
                  })

                MenuItem({ content: '添加到歌单' })
                  .onClick(() => {
                    this.currentAction = `添加到歌单: ${song}`
                  })

                MenuItem({ content: '查看歌手' })
                  .onClick(() => {
                    this.currentAction = `查看歌手信息`
                  })

                MenuItem({ content: '分享' })
                  .onClick(() => {
                    this.currentAction = `分享: ${song}`
                  })

                MenuItem({ content: '下载' })
                  .onClick(() => {
                    this.currentAction = `下载: ${song}`
                  })
              }
            }, {
              placement: Placement.BottomRight
            } as ContextMenuOptions)
          }
        })
      }
      .width('90%')
      .layoutWeight(1)

      if (this.currentAction !== '') {
        Text(this.currentAction)
          .fontSize(14)
          .fontColor('#2196F3')
          .padding(10)
      }
    }
    .width('100%')
    .height('100%')
  }
}

// 示例 9-6: 联系人列表右键菜单
@Entry
@Component
struct ContactListContextMenuExample {
  @State contacts: Array<{ name: string, phone: string }> = [
    { name: '张三', phone: '138****1234' },
    { name: '李四', phone: '139****5678' },
    { name: '王五', phone: '136****9012' }
  ]
  @State actionLog: string = ''

  build() {
    Column({ space: 10 }) {
      Text('联系人')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      List({ space: 10 }) {
        ForEach(this.contacts, (contact: { name: string, phone: string }) => {
          ListItem() {
            Row({ space: 15 }) {
              Text(contact.name[0])
                .fontSize(18)
                .fontColor(Color.White)
                .width(45)
                .height(45)
                .textAlign(TextAlign.Center)
                .backgroundColor('#2196F3')
                .borderRadius(22.5)

              Column({ space: 5 }) {
                Text(contact.name)
                  .fontSize(16)
                  .fontWeight(FontWeight.Medium)

                Text(contact.phone)
                  .fontSize(13)
                  .fontColor('#999999')
              }
              .alignItems(HorizontalAlign.Start)
              .layoutWeight(1)
            }
            .width('100%')
            .padding(15)
            .backgroundColor('#FFFFFF')
            .borderRadius(10)
            .shadow({ radius: 2, color: '#E0E0E0' })
            .bindContextMenuWithResponse((responseType: ResponseType) => {
              Menu() {
                MenuItem({ content: '拨打电话' })
                  .onClick(() => {
                    this.actionLog = `拨打 ${contact.name} 的电话`
                  })

                MenuItem({ content: '发送短信' })
                  .onClick(() => {
                    this.actionLog = `给 ${contact.name} 发送短信`
                  })

                MenuItem({ content: '视频通话' })
                  .onClick(() => {
                    this.actionLog = `与 ${contact.name} 视频通话`
                  })

                MenuItem({ content: '编辑联系人' })
                  .onClick(() => {
                    this.actionLog = `编辑 ${contact.name} 的信息`
                  })

                MenuItem({ content: '分享联系人' })
                  .onClick(() => {
                    this.actionLog = `分享 ${contact.name} 的名片`
                  })

                MenuItem({ content: '删除联系人' })
                  .onClick(() => {
                    this.actionLog = `删除 ${contact.name}`
                  })
              }
            }, {
              placement: Placement.BottomLeft,
              enableArrow: true
            } as ContextMenuOptions)
          }
        })
      }
      .width('90%')
      .layoutWeight(1)

      if (this.actionLog !== '') {
        Text(this.actionLog)
          .fontSize(14)
          .fontColor('#4CAF50')
          .padding(10)
      }
    }
    .width('100%')
    .height('100%')
  }
}

// 示例 9-7: 邮件列表右键菜单
@Entry
@Component
struct MailListContextMenuExample {
  @State emails: Array<{
    sender: string,
    subject: string,
    time: string
  }> = [
    { sender: '系统通知', subject: '您的账户安全提醒', time: '10:30' },
    { sender: '项目组', subject: '本周项目进度报告', time: '09:15' },
    { sender: 'HR部门', subject: '五一假期通知', time: '昨天' }
  ]
  @State mailAction: string = ''

  build() {
    Column({ space: 10 }) {
      Text('收件箱')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      List({ space: 10 }) {
        ForEach(this.emails, (email: { sender: string, subject: string, time: string }) => {
          ListItem() {
            Column({ space: 8 }) {
              Row() {
                Text(email.sender)
                  .fontSize(15)
                  .fontWeight(FontWeight.Medium)
                  .layoutWeight(1)

                Text(email.time)
                  .fontSize(12)
                  .fontColor('#999999')
              }
              .width('100%')

              Text(email.subject)
                .fontSize(14)
                .fontColor('#666666')
            }
            .width('100%')
            .padding(15)
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .shadow({ radius: 2, color: '#EEEEEE' })
            .bindContextMenuWithResponse((responseType: ResponseType) => {
              Menu() {
                MenuItem({ content: '打开邮件' })
                  .onClick(() => {
                    this.mailAction = `打开: ${email.subject}`
                  })

                MenuItem({ content: '标记为已读' })
                  .onClick(() => {
                    this.mailAction = '标记为已读'
                  })

                MenuItem({ content: '标记为未读' })
                  .onClick(() => {
                    this.mailAction = '标记为未读'
                  })

                MenuItem({ content: '标星' })
                  .onClick(() => {
                    this.mailAction = '已标星'
                  })

                MenuItem({ content: '归档' })
                  .onClick(() => {
                    this.mailAction = '已归档'
                  })

                MenuItem({ content: '删除' })
                  .onClick(() => {
                    this.mailAction = '已删除'
                  })

                MenuItem({ content: '标记垃圾邮件' })
                  .onClick(() => {
                    this.mailAction = '标记为垃圾邮件'
                  })
              }
            }, {
              placement: Placement.BottomLeft
            } as ContextMenuOptions)
          }
        })
      }
      .width('90%')
      .layoutWeight(1)

      if (this.mailAction !== '') {
        Text(this.mailAction)
          .fontSize(14)
          .fontColor('#FF9800')
          .padding(10)
      }
    }
    .width('100%')
    .height('100%')
  }
}


// ============================================
// 第十部分：高级组合示例
// ============================================

// 示例 10-1: 完整配置的组合使用
@Entry
@Component
struct FullConfigExample {
  @State menuState: string = '菜单未激活'

  build() {
    Column({ space: 20 }) {
      Text('完整配置示例')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .padding(20)

      Text(this.menuState)
        .fontSize(16)
        .fontColor('#2196F3')

      Text('长按或右键触发')
        .fontSize(16)
        .width('70%')
        .height(70)
        .backgroundColor('#9C27B0')
        .fontColor(Color.White)
        .textAlign(TextAlign.Center)
        .borderRadius(12)
        .bindContextMenuWithResponse((responseType: ResponseType) => {
          Menu() {
            MenuItem({ content: '完整配置选项1' })
              .onClick(() => {
                console.info('选项1被点击')
              })
            MenuItem({ content: '完整配置选项2' })
              .onClick(() => {
                console.info('选项2被点击')
              })
            MenuItem({ content: '完整配置选项3' })
              .onClick(() => {
                console.info('选项3被点击')
              })
          }
        }, {
          placement: Placement.Bottom,
          offset: { x: 0, y: 10 },
          enableArrow: true,
          arrowOffset: 50,
          preview: MenuPreviewMode.IMAGE,
          previewBorderRadius: 16,
          borderRadius: 24,
          aboutToAppear: () => {
            this.menuState = '菜单即将显示...'
          },
          onAppear: () => {
            this.menuState = '菜单已显示！'
          },
          aboutToDisappear: () => {
            this.menuState = '菜单即将隐藏...'
          },
          onDisappear: () => {
            this.menuState = '菜单已隐藏'
          },
          previewAnimationOptions: {
            scale: [0.9, 1.15]
          }
        } as ContextMenuOptions)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}
