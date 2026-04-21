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
struct ActionSheetAdvancedIcons {
  pathStack: NavPathStack = new NavPathStack()
  @State logMessage: string = '选择上方按钮查看图标效果'

  showEmojiIcons() {
    this.logMessage = '显示Emoji图标ActionSheet'
    ActionSheet.show({
      title: 'Emoji图标',
      message: '使用emoji作为图标标识',
      autoCancel: true,
      confirm: {
        value: '确定',
        action: () => {}
      },
      sheets: [
        {
          title: '📱 手机',
          action: () => {
            this.logMessage = '选择了手机'
          }
        },
        {
          title: '💻 电脑',
          action: () => {
            this.logMessage = '选择了电脑'
          }
        },
        {
          title: '🎮 游戏',
          action: () => {
            this.logMessage = '选择了游戏'
          }
        },
        {
          title: '🎵 音乐',
          action: () => {
            this.logMessage = '选择了音乐'
          }
        },
        {
          title: '📷 相机',
          action: () => {
            this.logMessage = '选择了相机'
          }
        },
        {
          title: '🎨 画图',
          action: () => {
            this.logMessage = '选择了画图'
          }
        }
      ]
    })
  }

  showSystemIcons() {
    this.logMessage = '显示系统图标ActionSheet'
    ActionSheet.show({
      title: '系统图标',
      message: '常见的系统操作图标',
      autoCancel: true,
      confirm: {
        value: '完成',
        action: () => {}
      },
      sheets: [
        {
          title: '⚙️ 设置',
          action: () => {
            this.logMessage = '选择了设置'
          }
        },
        {
          title: '🔔 通知',
          action: () => {
            this.logMessage = '选择了通知'
          }
        },
        {
          title: '🔒 隐私',
          action: () => {
            this.logMessage = '选择了隐私'
          }
        },
        {
          title: '📊 数据',
          action: () => {
            this.logMessage = '选择了数据'
          }
        },
        {
          title: '🧹 清理',
          action: () => {
            this.logMessage = '选择了清理'
          }
        }
      ]
    })
  }

  showFileIcons() {
    this.logMessage = '显示文件图标ActionSheet'
    ActionSheet.show({
      title: '文件图标',
      message: '不同类型的文件图标',
      autoCancel: true,
      confirm: {
        value: '确认',
        action: () => {}
      },
      sheets: [
        {
          title: '📄 文档',
          action: () => {
            this.logMessage = '选择了文档'
          }
        },
        {
          title: '📁 文件夹',
          action: () => {
            this.logMessage = '选择了文件夹'
          }
        },
        {
          title: '🖼️ 图片',
          action: () => {
            this.logMessage = '选择了图片'
          }
        },
        {
          title: '🎵 音频',
          action: () => {
            this.logMessage = '选择了音频'
          }
        },
        {
          title: '🎬 视频',
          action: () => {
            this.logMessage = '选择了视频'
          }
        },
        {
          title: '📦 压缩包',
          action: () => {
            this.logMessage = '选择了压缩包'
          }
        }
      ]
    })
  }

  showStatusIcons() {
    this.logMessage = '显示状态图标ActionSheet'
    ActionSheet.show({
      title: '状态图标',
      message: '表示不同状态的图标',
      autoCancel: true,
      confirm: {
        value: '关闭',
        action: () => {}
      },
      sheets: [
        {
          title: '✅ 成功',
          action: () => {
            this.logMessage = '选择了成功状态'
          }
        },
        {
          title: '❌ 失败',
          action: () => {
            this.logMessage = '选择了失败状态'
          }
        },
        {
          title: '⚠️ 警告',
          action: () => {
            this.logMessage = '选择了警告状态'
          }
        },
        {
          title: '❓ 疑问',
          action: () => {
            this.logMessage = '选择了疑问状态'
          }
        },
        {
          title: 'ℹ️ 信息',
          action: () => {
            this.logMessage = '选择了信息状态'
          }
        }
      ]
    })
  }

  showNavigationIcons() {
    this.logMessage = '显示导航图标ActionSheet'
    ActionSheet.show({
      title: '导航图标',
      message: '导航和方向相关图标',
      autoCancel: true,
      confirm: {
        value: '返回',
        action: () => {}
      },
      sheets: [
        {
          title: '⬆️ 向上',
          action: () => {
            this.logMessage = '选择了向上'
          }
        },
        {
          title: '⬇️ 向下',
          action: () => {
            this.logMessage = '选择了向下'
          }
        },
        {
          title: '⬅️ 向左',
          action: () => {
            this.logMessage = '选择了向左'
          }
        },
        {
          title: '➡️ 向右',
          action: () => {
            this.logMessage = '选择了向右'
          }
        },
        {
          title: '🏠 首页',
          action: () => {
            this.logMessage = '选择了首页'
          }
        }
      ]
    })
  }

  showEditIcons() {
    this.logMessage = '显示编辑图标ActionSheet'
    ActionSheet.show({
      title: '编辑图标',
      message: '编辑操作相关图标',
      autoCancel: true,
      confirm: {
        value: '完成',
        action: () => {}
      },
      sheets: [
        {
          title: '✂️ 剪切',
          action: () => {
            this.logMessage = '选择了剪切'
          }
        },
        {
          title: '📋 复制',
          action: () => {
            this.logMessage = '选择了复制'
          }
        },
        {
          title: '📝 粘贴',
          action: () => {
            this.logMessage = '选择了粘贴'
          }
        },
        {
          title: '🔍 查找',
          action: () => {
            this.logMessage = '选择了查找'
          }
        },
        {
          title: '↩️ 撤销',
          action: () => {
            this.logMessage = '选择了撤销'
          }
        },
        {
          title: '↪️ 重做',
          action: () => {
            this.logMessage = '选择了重做'
          }
        }
      ]
    })
  }

  showNetworkIcons() {
    this.logMessage = '显示网络图标ActionSheet'
    ActionSheet.show({
      title: '网络图标',
      message: '网络连接相关图标',
      autoCancel: true,
      confirm: {
        value: '关闭',
        action: () => {}
      },
      sheets: [
        {
          title: '📶 WiFi',
          action: () => {
            this.logMessage = '选择了WiFi'
          }
        },
        {
          title: '📶 蓝牙',
          action: () => {
            this.logMessage = '选择了蓝牙'
          }
        },
        {
          title: '📶 流量',
          action: () => {
            this.logMessage = '选择了流量'
          }
        },
        {
          title: '📶 同步',
          action: () => {
            this.logMessage = '选择了同步'
          }
        },
        {
          title: '📶 云端',
          action: () => {
            this.logMessage = '选择了云端'
          }
        }
      ]
    })
  }

  showMediaIcons() {
    this.logMessage = '显示媒体图标ActionSheet'
    ActionSheet.show({
      title: '媒体图标',
      message: '媒体播放控制图标',
      autoCancel: true,
      confirm: {
        value: '退出',
        action: () => {}
      },
      sheets: [
        {
          title: '⏮️ 上一个',
          action: () => {
            this.logMessage = '选择了上一个'
          }
        },
        {
          title: '⏯️ 播放',
          action: () => {
            this.logMessage = '选择了播放'
          }
        },
        {
          title: '⏸️ 暂停',
          action: () => {
            this.logMessage = '选择了暂停'
          }
        },
        {
          title: '⏭️ 下一个',
          action: () => {
            this.logMessage = '选择了下一个'
          }
        },
        {
          title: '🔇 静音',
          action: () => {
            this.logMessage = '选择了静音'
          }
        },
        {
          title: '🔊 音量',
          action: () => {
            this.logMessage = '选择了音量'
          }
        }
      ]
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('ActionSheet 图标选项测试用例')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          // Emoji图标
          Text('Emoji图标')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10 })

          Button('Emoji图标')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showEmojiIcons())

          // 系统图标
          Text('系统图标')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Button('系统图标')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showSystemIcons())

          // 功能分类图标
          Text('功能分类图标')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('文件图标')
                .width('100%')
                .onClick(() => this.showFileIcons())
            }
            GridCol() {
              Button('状态图标')
                .width('100%')
                .onClick(() => this.showStatusIcons())
            }
            GridCol() {
              Button('导航图标')
                .width('100%')
                .onClick(() => this.showNavigationIcons())
            }
            GridCol() {
              Button('编辑图标')
                .width('100%')
                .onClick(() => this.showEditIcons())
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 媒体图标
          Text('媒体图标')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            Button('网络图标')
              .width('48%')
              .onClick(() => this.showNetworkIcons())
            Button('媒体图标')
              .width('48%')
              .onClick(() => this.showMediaIcons())
          }.width('100%').padding({ left: 10, right: 10 })

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
    .title('ActionSheet 图标选项')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
