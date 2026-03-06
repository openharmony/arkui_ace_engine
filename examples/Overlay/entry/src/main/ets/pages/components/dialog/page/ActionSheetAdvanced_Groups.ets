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
struct ActionSheetAdvancedGroups {
  pathStack: NavPathStack = new NavPathStack()
  @State logMessage: string = '选择上方按钮查看分组效果'

  showTwoGroups() {
    this.logMessage = '显示两分组ActionSheet'
    ActionSheet.show({
      title: '两分组样式',
      message: '操作分为两个不同的区域',
      autoCancel: true,
      confirm: {
        value: '完成',
        action: () => {}
      },
      sheets: [
        {
          title: '操作A',
          action: () => {
            this.logMessage = '选择了操作A'
          }
        },
        {
          title: '操作B',
          action: () => {
            this.logMessage = '选择了操作B'
          }
        },
        {
          title: '操作C',
          action: () => {
            this.logMessage = '选择了操作C'
          }
        },
        {
          title: '高级操作X',
          action: () => {
            this.logMessage = '选择了高级操作X'
          }
        },
        {
          title: '高级操作Y',
          action: () => {
            this.logMessage = '选择了高级操作Y'
          }
        }
      ]
    })
  }

  showThreeGroups() {
    this.logMessage = '显示三分组ActionSheet'
    ActionSheet.show({
      title: '三分组样式',
      message: '操作分为三个不同的功能区域',
      autoCancel: true,
      confirm: {
        value: '确认',
        action: () => {}
      },
      sheets: [
        {
          title: '编辑',
          action: () => {
            this.logMessage = '选择了编辑'
          }
        },
        {
          title: '删除',
          action: () => {
            this.logMessage = '选择了删除'
          }
        },
        {
          title: '分享',
          action: () => {
            this.logMessage = '选择了分享'
          }
        },
        {
          title: '系统设置',
          action: () => {
            this.logMessage = '选择了系统设置'
          }
        },
        {
          title: '帮助反馈',
          action: () => {
            this.logMessage = '选择了帮助反馈'
          }
        },
        {
          title: '关于',
          action: () => {
            this.logMessage = '选择了关于'
          }
        }
      ]
    })
  }

  showCategoryGroups() {
    this.logMessage = '显示分类分组ActionSheet'
    ActionSheet.show({
      title: '分类分组',
      autoCancel: true,
      confirm: {
        value: '完成',
        action: () => {
        }
      },
      sheets: [
        {
          title: '📁 文档操作',
          action: () => {
            this.logMessage = '选择了文档操作'
          }
        },
        {
          title: '🖼️ 图片操作',
          action: () => {
            this.logMessage = '选择了图片操作'
          }
        },
        {
          title: '🎵 音频操作',
          action: () => {
            this.logMessage = '选择了音频操作'
          }
        },
        {
          title: '🎬 视频操作',
          action: () => {
            this.logMessage = '选择了视频操作'
          }
        },
        {
          title: '⚙️ 系统操作',
          action: () => {
            this.logMessage = '选择了系统操作'
          }
        }
      ],
      message: ''
    })
  }

  showPriorityGroups() {
    this.logMessage = '显示优先级分组ActionSheet'
    ActionSheet.show({
      title: '优先级分组',
      message: '常用操作在上方，不常用在下方',
      autoCancel: true,
      confirm: {
        value: '确定',
        action: () => {}
      },
      sheets: [
        {
          title: '常用操作1',
          action: () => {
            this.logMessage = '选择了常用操作1'
          }
        },
        {
          title: '常用操作2',
          action: () => {
            this.logMessage = '选择了常用操作2'
          }
        },
        {
          title: '常用操作3',
          action: () => {
            this.logMessage = '选择了常用操作3'
          }
        },
        {
          title: '不常用操作A',
          action: () => {
            this.logMessage = '选择了不常用操作A'
          }
        },
        {
          title: '不常用操作B',
          action: () => {
            this.logMessage = '选择了不常用操作B'
          }
        }
      ]
    })
  }

  showActionTypeGroups() {
    this.logMessage = '显示操作类型分组ActionSheet'
    ActionSheet.show({
      title: '操作类型分组',
      autoCancel: true,
      confirm: {
        value: '关闭',
        action: () => {
        }
      },
      sheets: [
        {
          title: '➕ 添加',
          action: () => {
            this.logMessage = '选择了添加'
          }
        },
        {
          title: '✏️ 编辑',
          action: () => {
            this.logMessage = '选择了编辑'
          }
        },
        {
          title: '🗑️ 删除',
          action: () => {
            this.logMessage = '选择了删除'
          }
        },
        {
          title: '📋 复制',
          action: () => {
            this.logMessage = '选择了复制'
          }
        },
        {
          title: '📤 移动',
          action: () => {
            this.logMessage = '选择了移动'
          }
        }
      ],
      message: ''
    })
  }

  showUserLevelGroups() {
    this.logMessage = '显示用户级别分组ActionSheet'
    ActionSheet.show({
      title: '用户级别分组',
      autoCancel: true,
      confirm: {
        value: '确认',
        action: () => {
        }
      },
      sheets: [
        {
          title: '普通用户操作',
          action: () => {
            this.logMessage = '选择了普通用户操作'
          }
        },
        {
          title: '高级用户操作',
          action: () => {
            this.logMessage = '选择了高级用户操作'
          }
        },
        {
          title: '管理员操作',
          action: () => {
            this.logMessage = '选择了管理员操作'
          }
        }
      ],
      message: ''
    })
  }

  showContextGroups() {
    this.logMessage = '显示上下文分组ActionSheet'
    ActionSheet.show({
      title: '上下文分组',
      message: '根据当前上下文显示相关操作',
      autoCancel: true,
      confirm: {
        value: '取消',
        action: () => {}
      },
      sheets: [
        {
          title: '本地操作',
          action: () => {
            this.logMessage = '选择了本地操作'
          }
        },
        {
          title: '网络操作',
          action: () => {
            this.logMessage = '选择了网络操作'
          }
        },
        {
          title: '云端操作',
          action: () => {
            this.logMessage = '选择了云端操作'
          }
        }
      ]
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('ActionSheet 分组显示测试用例')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          // 基础分组
          Text('基础分组')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('两分组')
                .width('100%')
                .onClick(() => this.showTwoGroups())
            }
            GridCol() {
              Button('三分组')
                .width('100%')
                .onClick(() => this.showThreeGroups())
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 分类分组
          Text('分类分组')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('按类别分组')
                .width('100%')
                .onClick(() => this.showCategoryGroups())
            }
            GridCol() {
              Button('按优先级分组')
                .width('100%')
                .onClick(() => this.showPriorityGroups())
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 操作类型分组
          Text('操作类型分组')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('按操作类型')
                .width('100%')
                .onClick(() => this.showActionTypeGroups())
            }
            GridCol() {
              Button('按用户级别')
                .width('100%')
                .onClick(() => this.showUserLevelGroups())
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 上下文分组
          Text('上下文分组')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Button('按上下文分组')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showContextGroups())

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
    .title('ActionSheet 分组显示')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
