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
struct ActionSheetAdvancedStyle {
  pathStack: NavPathStack = new NavPathStack()
  @State logMessage: string = '选择上方按钮查看样式效果'

  showBasicStyle() {
    this.logMessage = '显示基础样式ActionSheet'
    ActionSheet.show({
      title: '基础样式',
      message: '这是一个基础的ActionSheet样式',
      autoCancel: true,
      confirm: {
        value: '确定',
        action: () => {
          console.log('Basic ActionSheet confirmed')
        }
      },
      cancel: () => {
        this.logMessage = 'ActionSheet已取消'
      },
      sheets: [
        {
          title: '选项一',
          action: () => {
            this.logMessage = '选择了选项一'
          }
        },
        {
          title: '选项二',
          action: () => {
            this.logMessage = '选择了选项二'
          }
        }
      ]
    })
  }

  showColoredStyle() {
    this.logMessage = '显示彩色样式ActionSheet'
    ActionSheet.show({
      title: '彩色样式',
      subtitle: '不同颜色的选项项',
      autoCancel: true,
      confirm: {
        value: '确认',
        action: () => {
        }
      },
      sheets: [
        {
          title: '红色选项',
          action: () => {
            this.logMessage = '选择了红色选项'
          }
        },
        {
          title: '蓝色选项',
          action: () => {
            this.logMessage = '选择了蓝色选项'
          }
        },
        {
          title: '橙色选项',
          action: () => {
            this.logMessage = '选择了橙色选项'
          }
        }
      ],
      message: ''
    })
  }

  showLongText() {
    this.logMessage = '显示长文本ActionSheet'
    ActionSheet.show({
      title: '长文本样式',
      message: '这是一个包含较长文本的ActionSheet，用于测试文本的显示效果和布局适应性。当文本内容较长时，需要确保能够正确显示和滚动。',
      autoCancel: true,
      confirm: {
        value: '确定',
        action: () => {}
      },
      sheets: [
        {
          title: '这是一个很长的选项文本，用于测试长文本的显示效果',
          action: () => {
            this.logMessage = '选择了长文本选项'
          }
        }
      ]
    })
  }

  showWithSubtitle() {
    this.logMessage = '显示带副标题ActionSheet'
    ActionSheet.show({
      title: '主标题',
      subtitle: '这是一个副标题区域，用于提供额外的说明信息',
      autoCancel: true,
      confirm: {
        value: '确认',
        action: () => {
        }
      },
      sheets: [
        {
          title: '选项A',
          action: () => {
            this.logMessage = '选择了选项A'
          }
        },
        {
          title: '选项B',
          action: () => {
            this.logMessage = '选择了选项B'
          }
        }
      ],
      message: ''
    })
  }

  showWithMessage() {
    this.logMessage = '显示带消息ActionSheet'
    ActionSheet.show({
      title: '消息样式',
      message: '这条消息提示用户需要进行操作选择',
      autoCancel: true,
      confirm: {
        value: '完成',
        action: () => {}
      },
      sheets: [
        {
          title: '第一个操作',
          action: () => {
            this.logMessage = '选择了第一个操作'
          }
        },
        {
          title: '第二个操作',
          action: () => {
            this.logMessage = '选择了第二个操作'
          }
        },
        {
          title: '第三个操作',
          action: () => {
            this.logMessage = '选择了第三个操作'
          }
        }
      ]
    })
  }

  showMultipleSections() {
    this.logMessage = '显示多分区ActionSheet'
    ActionSheet.show({
      title: '多分区样式',
      subtitle: '不同的操作分为多个区域显示',
      autoCancel: true,
      confirm: {
        value: '完成',
        action: () => {
        }
      },
      sheets: [
        {
          title: '基础操作',
          action: () => {
            this.logMessage = '选择了基础操作'
          }
        },
        {
          title: '高级操作',
          action: () => {
            this.logMessage = '选择了高级操作'
          }
        },
        {
          title: '系统操作',
          action: () => {
            this.logMessage = '选择了系统操作'
          }
        }
      ],
      message: ''
    })
  }

  showWithDestructive() {
    this.logMessage = '显示警告样式ActionSheet'
    ActionSheet.show({
      title: '操作警告',
      message: '请注意以下操作的影响',
      autoCancel: true,
      confirm: {
        value: '确认',
        action: () => {}
      },
      sheets: [
        {
          title: '查看详情',
          action: () => {
            this.logMessage = '选择了查看详情'
          }
        },
        {
          title: '编辑内容',
          action: () => {
            this.logMessage = '选择了编辑内容'
          }
        },
        {
          title: '删除项目',
          action: () => {
            this.logMessage = '选择了删除项目'
          }
        }
      ]
    })
  }

  showDefaultFocus() {
    this.logMessage = '显示默认焦点ActionSheet'
    ActionSheet.show({
      title: '默认焦点测试',
      message: '确认按钮具有默认焦点',
      autoCancel: true,
      confirm: {
        value: '确定',
        defaultFocus: true,
        action: () => {
          this.logMessage = '确认按钮被点击'
        }
      },
      cancel: () => {
        this.logMessage = 'ActionSheet已取消'
      },
      sheets: [
        {
          title: '普通选项',
          action: () => {
            this.logMessage = '选择了普通选项'
          }
        }
      ]
    })
  }

  showNoAutoCancel() {
    this.logMessage = '显示不可自动取消ActionSheet'
    ActionSheet.show({
      title: '不可自动取消',
      message: '必须选择一个操作才能关闭',
      autoCancel: false,
      confirm: {
        value: '确认',
        action: () => {
          this.logMessage = '确认按钮被点击'
        }
      },
      sheets: [
        {
          title: '选项1',
          action: () => {
            this.logMessage = '选择了选项1'
          }
        },
        {
          title: '选项2',
          action: () => {
            this.logMessage = '选择了选项2'
          }
        }
      ]
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('ActionSheet 样式定制测试用例')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          // 基础样式
          Text('基础样式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10 })

          Button('基础ActionSheet')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showBasicStyle())

          // 内容样式
          Text('内容样式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('彩色样式')
                .width('100%')
                .onClick(() => this.showColoredStyle())
            }
            GridCol() {
              Button('长文本')
                .width('100%')
                .onClick(() => this.showLongText())
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 标题副标题样式
          Text('标题和副标题')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            Button('带副标题')
              .width('48%')
              .onClick(() => this.showWithSubtitle())
            Button('带消息')
              .width('48%')
              .onClick(() => this.showWithMessage())
          }.width('100%').padding({ left: 10, right: 10 })

          // 多分区样式
          Text('分区样式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Button('多分区样式')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showMultipleSections())

          // 特殊样式
          Text('特殊样式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('警告样式')
                .width('100%')
                .onClick(() => this.showWithDestructive())
            }
            GridCol() {
              Button('默认焦点')
                .width('100%')
                .onClick(() => this.showDefaultFocus())
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 自动取消控制
          Text('自动取消控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Button('不可自动取消')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showNoAutoCancel())

          // 日志显示区域
          Divider()
          Text('操作日志')
            .fontSize(14)
            .fontColor(Color.Gray)
            .margin({ left: 10 })

          Text(this.logMessage)
            .fontSize(12)
            .fontColor(Color.Black)
            .padding(10)
            .width('100%')
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
            .margin({ left: 10, right: 10, bottom: 10 })
        }
        .width('100%')
      }
    }
    .title('ActionSheet 样式定制')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
