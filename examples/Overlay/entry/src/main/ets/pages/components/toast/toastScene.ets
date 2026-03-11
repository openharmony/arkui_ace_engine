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

import { promptAction } from '@kit.ArkUI'
import { BusinessError } from '@kit.BasicServicesKit'

interface ToastConfig {
  message: string
  duration: number
  bottom?: number
  showMode?: promptAction.ToastShowMode
  alignment?: Alignment
  backgroundColor?: ResourceColor
  textColor?: ResourceColor
  backgroundBlurStyle?: BlurStyle
}

interface ToastInfo {
  id: number
  config: ToastConfig
  showTime: number
}

@Builder
export function ToastSceneBuilder(name: string, param: Object) {
  ToastScene()
}

@Entry
@Component
struct ToastScene {
  pathStack: NavPathStack = new NavPathStack()

  @State currentSection: string = 'basic'
  @State logMessages: string[] = []
  @State activeToastCount: number = 0
  @State toastHistory: ToastInfo[] = []

  private addLog(message: string) {
    let timestamp = new Date().toLocaleTimeString()
    this.logMessages.unshift(`[${timestamp}] ${message}`)
    if (this.logMessages.length > 30) {
      this.logMessages.pop()
    }
  }

  private showBasicToast(message: string, duration: number = 2000) {
    try {
      this.getUIContext().getPromptAction().showToast({
        message: message,
        duration: duration
      })
      this.addLog(`显示Toast: ${message}`)
      this.activeToastCount++
    } catch (error) {
      let err = error as BusinessError
      this.addLog(`Toast错误: ${err.code} - ${err.message}`)
    }
  }

  private showCustomToast(config: ToastConfig) {
    try {
      this.getUIContext().getPromptAction().showToast({
        message: config.message,
        duration: config.duration,
        bottom: config.bottom,
        showMode: config.showMode,
        alignment: config.alignment,
        backgroundColor: config.backgroundColor,
        textColor: config.textColor,
        backgroundBlurStyle: config.backgroundBlurStyle
      })
      this.addLog(`显示自定义Toast: ${config.message}`)
      this.activeToastCount++
    } catch (error) {
      let err = error as BusinessError
      this.addLog(`自定义Toast错误: ${err.code} - ${err.message}`)
    }
  }

  private async openToastAsync(config: ToastConfig): Promise<number> {
    return new Promise((resolve, reject) => {
      promptAction.openToast({
        message: config.message,
        duration: config.duration,
        bottom: config.bottom,
        showMode: config.showMode
      }).then((toastId: number) => {
        this.addLog(`openToast成功, ID: ${toastId}`)
        this.activeToastCount++
        this.toastHistory.push({
          id: toastId,
          config: config,
          showTime: Date.now()
        })
        resolve(toastId)
      }).catch((error: BusinessError) => {
        this.addLog(`openToast错误: ${error.code} - ${error.message}`)
        reject(error)
      })
    })
  }

  private closeToastById(toastId: number) {
    try {
      promptAction.closeToast(toastId)
      this.addLog(`关闭Toast: ${toastId}`)
      this.activeToastCount = Math.max(0, this.activeToastCount - 1)
    } catch (error) {
      let err = error as BusinessError
      this.addLog(`closeToast错误: ${err.code} - ${err.message}`)
    }
  }

  private sections: { title: string, key: string }[] = [
    { title: '基础功能', key: 'basic' },
    { title: '持续时间', key: 'duration' },
    { title: '位置设置', key: 'position' },
    { title: '显示模式', key: 'showMode' },
    { title: '样式设置', key: 'style' },
    { title: '背景模糊', key: 'blur' },
    { title: 'openToast', key: 'openToast' },
    { title: 'closeToast', key: 'closeToast' },
    { title: '多Toast管理', key: 'multiToast' },
    { title: '批量测试', key: 'batch' },
    { title: '边界测试', key: 'edgeCase' },
    { title: '性能测试', key: 'performance' },
  ]

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Text('Toast 综合测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Row({ space: 4 }) {
          Text(`活跃Toast: ${this.activeToastCount}`)
            .fontSize(12)
          Text(` | `)
            .fontSize(12)
          Text(`历史记录: ${this.toastHistory.length}`)
            .fontSize(12)
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Scroll() {
          Row({ space: 4 }) {
            ForEach(this.sections, (item: { title: string, key: string }) => {
              Button(item.title)
                .fontSize(10)
                .height(32)
                .padding(4)
                .backgroundColor(this.currentSection === item.key ? '#4CAF50' : '#2196F3')
                .onClick(() => {
                  this.currentSection = item.key
                })
            })
          }
        }
        .scrollable(ScrollDirection.Horizontal)
        .width('100%')
        .height(44)
        .scrollBar(BarState.Off)

        Scroll() {
          Column({ space: 12 }) {
            if (this.currentSection === 'basic') {
              this.BasicSection()
            } else if (this.currentSection === 'duration') {
              this.DurationSection()
            } else if (this.currentSection === 'position') {
              this.PositionSection()
            } else if (this.currentSection === 'showMode') {
              this.ShowModeSection()
            } else if (this.currentSection === 'style') {
              this.StyleSection()
            } else if (this.currentSection === 'blur') {
              this.BlurSection()
            } else if (this.currentSection === 'openToast') {
              this.OpenToastSection()
            } else if (this.currentSection === 'closeToast') {
              this.CloseToastSection()
            } else if (this.currentSection === 'multiToast') {
              this.MultiToastSection()
            } else if (this.currentSection === 'batch') {
              this.BatchSection()
            } else if (this.currentSection === 'performance') {
              this.PerformanceSection()
            }
          }
          .width('100%')
          .padding(8)
        }
        .layoutWeight(1)
        .width('100%')
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F5F5F5')
    }
    .title('Toast Demo')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }

  @Builder
  BasicSection() {
    Column({ space: 12 }) {
      Text('基础功能测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('showToast - 显示简单提示信息')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Button('显示 "Hello World"')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('Hello World')
        })

      Button('显示 "操作成功"')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('操作成功')
        })

      Button('显示 "请稍后再试"')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('请稍后再试')
        })

      Button('显示长文本消息')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('这是一条很长的Toast消息，用于测试长文本的显示效果，看看是否能够正常换行和显示完整内容')
        })

      Button('显示包含数字的消息')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('当前进度: 75%，剩余时间: 25秒')
        })

      Button('显示包含特殊字符的消息')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('特殊字符: !@#$%^&*()_+-={}[]|\\:";\'<>?,./~`')
        })

      Button('显示中英混合消息')
        .width('100%')
        .onClick(() => {
          this.showBasicToast('Welcome 欢迎 to 使用 ArkUI! 2025')
        })

      Divider()

      Text('基础用法说明:')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Text('showToast 是最简单的 Toast 显示方式，只需要传入 message 参数即可。')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('默认情况下:')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('• 持续时间: 1500ms (最低)')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')

      Text('• 显示位置: 底部居中')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')

      Text('• 显示模式: DEFAULT')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  DurationSection() {
    Column({ space: 12 }) {
      Text('持续时间测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('duration - 设置 Toast 显示时长')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('1500ms (默认)')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('显示1500ms', 1500)
          })

        Button('2000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('显示2000ms', 2000)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('3000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('显示3000ms', 3000)
          })

        Button('5000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('显示5000ms', 5000)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('10000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('显示10000ms (10秒)', 10000)
          })

        Button('30000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('显示30000ms (30秒)', 30000)
          })
      }
      .width('100%')

      Divider()

      Text('边界值测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('0ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('0ms测试', 0)
          })

        Button('1ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('1ms测试', 1)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('100ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('100ms测试', 100)
          })

        Button('500ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('500ms测试', 500)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('60000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('60000ms (1分钟)', 60000)
          })

        Button('300000ms')
          .layoutWeight(1)
          .onClick(() => {
            this.showBasicToast('300000ms (5分钟)', 300000)
          })
      }
      .width('100%')

      Divider()

      Text('持续时间说明:')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('• 最小值: 系统可能有最低限制 (约1500ms)')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')

      Text('• 推荐范围: 2000-3500ms')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')

      Text('• 长时间显示建议使用 openToast + closeToast')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  PositionSection() {
    Column({ space: 12 }) {
      Text('位置设置测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('alignment - 设置 Toast 显示位置')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('top / bottom 参数控制垂直偏移')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('顶部位置')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('左上')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '左上角 Toast',
              duration: 2000,
              alignment: Alignment.TopStart
            })
          })

        Button('顶部居中')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '顶部居中 Toast',
              duration: 2000,
              alignment: Alignment.Top
            })
          })

        Button('右上')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '右上角 Toast',
              duration: 2000,
              alignment: Alignment.TopEnd
            })
          })
      }
      .width('100%')

      Text('中间位置')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('左侧')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '左侧 Toast',
              duration: 2000,
              alignment: Alignment.Start
            })
          })

        Button('正中心')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '正中心 Toast',
              duration: 2000,
              alignment: Alignment.Center
            })
          })

        Button('右侧')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '右侧 Toast',
              duration: 2000,
              alignment: Alignment.End
            })
          })
      }
      .width('100%')

      Text('底部位置')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('左下')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '左下角 Toast',
              duration: 2000,
              alignment: Alignment.BottomStart
            })
          })

        Button('底部居中')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '底部居中 Toast',
              duration: 2000,
              alignment: Alignment.Bottom
            })
          })

        Button('右下')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '右下角 Toast',
              duration: 2000,
              alignment: Alignment.BottomEnd
            })
          })
      }
      .width('100%')

      Divider()

      Text('bottom 参数测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('bottom: 0')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'bottom: 0',
              duration: 2000,
              bottom: 0
            })
          })

        Button('bottom: 50')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'bottom: 50',
              duration: 2000,
              bottom: 50
            })
          })

        Button('bottom: 100')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'bottom: 100',
              duration: 2000,
              bottom: 100
            })
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('bottom: 200')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'bottom: 200',
              duration: 2000,
              bottom: 200
            })
          })

        Button('bottom: 300')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'bottom: 300',
              duration: 2000,
              bottom: 300
            })
          })

        Button('bottom: 500')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'bottom: 500',
              duration: 2000,
              bottom: 500
            })
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  ShowModeSection() {
    Column({ space: 12 }) {
      Text('显示模式测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('showMode - 设置 Toast 显示模式')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('ToastShowMode.DEFAULT')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Text('默认模式，Toast 显示在应用窗口内')
        .fontSize(12)
        .fontColor('#999999')
        .width('100%')

      Button('DEFAULT 模式')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: 'DEFAULT 模式 Toast',
            duration: 3000,
            showMode: promptAction.ToastShowMode.DEFAULT
          })
        })

      Text('ToastShowMode.TOP_MOST')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Text('顶层显示模式，Toast 显示在所有窗口之上')
        .fontSize(12)
        .fontColor('#999999')
        .width('100%')

      Button('TOP_MOST 模式')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: 'TOP_MOST 模式 Toast',
            duration: 3000,
            showMode: promptAction.ToastShowMode.TOP_MOST
          })
        })

      Divider()

      Text('模式对比测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('先 DEFAULT')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'DEFAULT - 在窗口内',
              duration: 5000,
              showMode: promptAction.ToastShowMode.DEFAULT,
              alignment: Alignment.Center
            })
          })

        Button('先 TOP_MOST')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: 'TOP_MOST - 在顶层',
              duration: 5000,
              showMode: promptAction.ToastShowMode.TOP_MOST,
              alignment: Alignment.Center
            })
          })
      }
      .width('100%')

      Text('使用场景说明:')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('• DEFAULT: 普通应用内提示')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')

      Text('• TOP_MOST: 系统级通知、重要警告')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  StyleSection() {
    Column({ space: 12 }) {
      Text('样式设置测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('backgroundColor - 设置背景颜色')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('红色背景')
          .layoutWeight(1)
          .backgroundColor('#F44336')
          .onClick(() => {
            this.showCustomToast({
              message: '红色背景 Toast',
              duration: 2000,
              backgroundColor: '#F44336'
            })
          })

        Button('绿色背景')
          .layoutWeight(1)
          .backgroundColor('#4CAF50')
          .onClick(() => {
            this.showCustomToast({
              message: '绿色背景 Toast',
              duration: 2000,
              backgroundColor: '#4CAF50'
            })
          })

        Button('蓝色背景')
          .layoutWeight(1)
          .backgroundColor('#2196F3')
          .onClick(() => {
            this.showCustomToast({
              message: '蓝色背景 Toast',
              duration: 2000,
              backgroundColor: '#2196F3'
            })
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('橙色背景')
          .layoutWeight(1)
          .backgroundColor('#FF9800')
          .onClick(() => {
            this.showCustomToast({
              message: '橙色背景 Toast',
              duration: 2000,
              backgroundColor: '#FF9800'
            })
          })

        Button('紫色背景')
          .layoutWeight(1)
          .backgroundColor('#9C27B0')
          .onClick(() => {
            this.showCustomToast({
              message: '紫色背景 Toast',
              duration: 2000,
              backgroundColor: '#9C27B0'
            })
          })

        Button('黑色背景')
          .layoutWeight(1)
          .backgroundColor('#333333')
          .onClick(() => {
            this.showCustomToast({
              message: '黑色背景 Toast',
              duration: 2000,
              backgroundColor: '#333333'
            })
          })
      }
      .width('100%')

      Divider()

      Text('textColor - 设置文字颜色')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('白色文字')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '白色文字 Toast',
              duration: 2000,
              backgroundColor: '#333333',
              textColor: '#FFFFFF'
            })
          })

        Button('黄色文字')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '黄色文字 Toast',
              duration: 2000,
              backgroundColor: '#333333',
              textColor: '#FFFF00'
            })
          })

        Button('青色文字')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '青色文字 Toast',
              duration: 2000,
              backgroundColor: '#333333',
              textColor: '#00FFFF'
            })
          })
      }
      .width('100%')

      Divider()

      Text('组合样式')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('成功提示')
          .layoutWeight(1)
          .backgroundColor('#4CAF50')
          .onClick(() => {
            this.showCustomToast({
              message: '✓ 操作成功！',
              duration: 2000,
              backgroundColor: '#4CAF50',
              textColor: '#FFFFFF'
            })
          })

        Button('警告提示')
          .layoutWeight(1)
          .backgroundColor('#FF9800')
          .onClick(() => {
            this.showCustomToast({
              message: '⚠ 请注意！',
              duration: 2000,
              backgroundColor: '#FF9800',
              textColor: '#FFFFFF'
            })
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('错误提示')
          .layoutWeight(1)
          .backgroundColor('#F44336')
          .onClick(() => {
            this.showCustomToast({
              message: '✗ 操作失败！',
              duration: 2000,
              backgroundColor: '#F44336',
              textColor: '#FFFFFF'
            })
          })

        Button('信息提示')
          .layoutWeight(1)
          .backgroundColor('#2196F3')
          .onClick(() => {
            this.showCustomToast({
              message: 'ℹ 提示信息',
              duration: 2000,
              backgroundColor: '#2196F3',
              textColor: '#FFFFFF'
            })
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('半透明背景')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '半透明背景效果',
              duration: 2000,
              backgroundColor: '#80000000'
            })
          })

        Button('渐变模拟')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '深色半透明效果',
              duration: 2000,
              backgroundColor: '#CC000000',
              textColor: '#FFFFFF'
            })
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  BlurSection() {
    Column({ space: 12 }) {
      Text('背景模糊测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('backgroundBlurStyle - 设置背景模糊样式')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('BlurStyle.NONE - 无模糊')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('NONE 模糊样式')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '无模糊效果',
            duration: 3000,
            backgroundBlurStyle: BlurStyle.NONE
          })
        })

      Text('BlurStyle.COMPONENT_ULTRA_THIN')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('COMPONENT_ULTRA_THIN')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '超薄模糊效果',
            duration: 3000,
            backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN
          })
        })

      Text('BlurStyle.COMPONENT_THIN')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('COMPONENT_THIN')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '薄模糊效果',
            duration: 3000,
            backgroundBlurStyle: BlurStyle.COMPONENT_THIN
          })
        })

      Text('BlurStyle.COMPONENT_REGULAR')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('COMPONENT_REGULAR')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '常规模糊效果',
            duration: 3000,
            backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR
          })
        })

      Text('BlurStyle.COMPONENT_THICK')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('COMPONENT_THICK')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '厚模糊效果',
            duration: 3000,
            backgroundBlurStyle: BlurStyle.COMPONENT_THICK
          })
        })

      Text('BlurStyle.COMPONENT_ULTRA_THICK')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('COMPONENT_ULTRA_THICK')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '超厚模糊效果',
            duration: 3000,
            backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK
          })
        })

      Divider()

      Text('组合效果测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('模糊+红色背景')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '红色模糊效果',
              duration: 3000,
              backgroundColor: '#80F44336',
              backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR
            })
          })

        Button('模糊+蓝色背景')
          .layoutWeight(1)
          .onClick(() => {
            this.showCustomToast({
              message: '蓝色模糊效果',
              duration: 3000,
              backgroundColor: '#802196F3',
              backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR
            })
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  OpenToastSection() {
    Column({ space: 12 }) {
      Text('openToast API 测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('openToast - 异步打开 Toast，返回 toastId')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      @State openToastId: number = -1

      Button('openToast - 10秒显示')
        .width('100%')
        .onClick(async () => {
          try {
            let id = await this.openToastAsync({
              message: 'openToast - 10秒后自动关闭',
              duration: 10000
            })
            this.openToastId = id
          } catch (e) {
            this.addLog('openToast 失败')
          }
        })

      Button('openToast - 30秒显示')
        .width('100%')
        .onClick(async () => {
          try {
            let id = await this.openToastAsync({
              message: 'openToast - 30秒后自动关闭，可以手动关闭',
              duration: 30000
            })
            this.openToastId = id
          } catch (e) {
            this.addLog('openToast 失败')
          }
        })

      Button('openToast - 60秒显示')
        .width('100%')
        .onClick(async () => {
          try {
            let id = await this.openToastAsync({
              message: 'openToast - 60秒长时显示，用于测试长时间Toast',
              duration: 60000
            })
            this.openToastId = id
          } catch (e) {
            this.addLog('openToast 失败')
          }
        })

      Divider()

      Text('带配置的 openToast')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('openToast + TOP_MOST')
        .width('100%')
        .onClick(async () => {
          try {
            let id = await this.openToastAsync({
              message: 'TOP_MOST 模式的 openToast',
              duration: 10000,
              showMode: promptAction.ToastShowMode.TOP_MOST
            })
            this.openToastId = id
          } catch (e) {
            this.addLog('openToast 失败')
          }
        })

      Button('openToast + 自定义位置')
        .width('100%')
        .onClick(async () => {
          try {
            let id = await this.openToastAsync({
              message: '顶部居中的 openToast',
              duration: 10000,
              alignment: Alignment.Top,
              bottom: 100
            })
            this.openToastId = id
          } catch (e) {
            this.addLog('openToast 失败')
          }
        })

      Text('当前 ToastId: ' + this.openToastId)
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text('说明: openToast 返回 toastId，可用于 closeToast 手动关闭')
        .fontSize(11)
        .fontColor('#999999')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  CloseToastSection() {
    Column({ space: 12 }) {
      Text('closeToast API 测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('closeToast - 通过 toastId 关闭指定的 Toast')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      @State managedToastIds: number[] = []

      Button('打开一个可管理的 Toast')
        .width('100%')
        .onClick(async () => {
          try {
            let id = await this.openToastAsync({
              message: `可管理 Toast #${this.managedToastIds.length + 1}`,
              duration: 60000
            })
            this.managedToastIds.push(id)
          } catch (e) {
            this.addLog('打开失败')
          }
        })

      Text(`已打开的 Toast 数量: ${this.managedToastIds.length}`)
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      if (this.managedToastIds.length > 0) {
        Text('Toast ID 列表:')
          .fontSize(12)
          .fontColor('#666666')
          .width('100%')

        ForEach(this.managedToastIds.slice(0, 10), (id: number, index: number) => {
          Row({ space: 8 }) {
            Text(`ID: ${id}`)
              .fontSize(12)
              .layoutWeight(1)
            Button('关闭')
              .fontSize(10)
              .height(28)
              .onClick(() => {
                this.closeToastById(id)
                this.managedToastIds = this.managedToastIds.filter(i => i !== id)
              })
          }
          .width('100%')
        })

        if (this.managedToastIds.length > 10) {
          Text(`... 还有 ${this.managedToastIds.length - 10} 个`)
            .fontSize(11)
            .fontColor('#999999')
            .width('100%')
        }
      }

      Button('关闭所有已管理的 Toast')
        .width('100%')
        .backgroundColor('#F44336')
        .onClick(() => {
          this.managedToastIds.forEach(id => {
            this.closeToastById(id)
          })
          this.managedToastIds = []
        })

      Divider()

      Text('边界情况测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('关闭不存在的ID')
          .layoutWeight(1)
          .onClick(() => {
            this.closeToastById(999999)
          })

        Button('关闭负数ID')
          .layoutWeight(1)
          .onClick(() => {
            this.closeToastById(-1)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('关闭0')
          .layoutWeight(1)
          .onClick(() => {
            this.closeToastById(0)
          })

        Button('重复关闭')
          .layoutWeight(1)
          .onClick(async () => {
            try {
              let id = await this.openToastAsync({
                message: '将被重复关闭',
                duration: 60000
              })
              this.closeToastById(id)
              setTimeout(() => {
                this.closeToastById(id)
              }, 500)
            } catch (e) {
              // ignore
            }
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  MultiToastSection() {
    Column({ space: 12 }) {
      Text('多 Toast 管理测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('测试多个 Toast 同时显示的情况')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Button('同时显示3个 Toast')
        .width('100%')
        .onClick(() => {
          this.showCustomToast({
            message: '第一个 Toast',
            duration: 5000,
            alignment: Alignment.Top,
            backgroundColor: '#F44336'
          })
          setTimeout(() => {
            this.showCustomToast({
              message: '第二个 Toast',
              duration: 5000,
              alignment: Alignment.Center,
              backgroundColor: '#4CAF50'
            })
          }, 200)
          setTimeout(() => {
            this.showCustomToast({
              message: '第三个 Toast',
              duration: 5000,
              alignment: Alignment.Bottom,
              backgroundColor: '#2196F3'
            })
          }, 400)
        })

      Button('快速连续显示5个 Toast')
        .width('100%')
        .onClick(() => {
          for (let i = 1; i <= 5; i++) {
            setTimeout(() => {
              this.showBasicToast(`Toast #${i}`, 3000)
            }, i * 100)
          }
        })

      Button('不同位置显示 Toast')
        .width('100%')
        .onClick(() => {
          let positions: Alignment[] = [
            Alignment.TopStart,
            Alignment.Top,
            Alignment.TopEnd,
            Alignment.Start,
            Alignment.Center,
            Alignment.End,
            Alignment.BottomStart,
            Alignment.Bottom,
            Alignment.BottomEnd
          ]
          positions.forEach((pos, index) => {
            setTimeout(() => {
              this.showCustomToast({
                message: `位置 ${index + 1}`,
                duration: 5000,
                alignment: pos
              })
            }, index * 200)
          })
        })

      Divider()

      Text('队列测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('显示10个 Toast 队列')
        .width('100%')
        .onClick(() => {
          for (let i = 1; i <= 10; i++) {
            setTimeout(() => {
              this.showBasicToast(`队列消息 ${i}/10`, 2000)
            }, i * 500)
          }
        })

      Button('显示20个 Toast 队列')
        .width('100%')
        .onClick(() => {
          for (let i = 1; i <= 20; i++) {
            setTimeout(() => {
              this.showBasicToast(`队列消息 ${i}/20`, 1500)
            }, i * 300)
          }
        })

      Divider()

      Text('并发测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Button('并发5个')
          .layoutWeight(1)
          .onClick(() => {
            Promise.all([
              this.openToastAsync({ message: '并发1', duration: 5000 }),
              this.openToastAsync({ message: '并发2', duration: 5000 }),
              this.openToastAsync({ message: '并发3', duration: 5000 }),
              this.openToastAsync({ message: '并发4', duration: 5000 }),
              this.openToastAsync({ message: '并发5', duration: 5000 })
            ]).then((ids) => {
              this.addLog(`并发打开 ${ids.length} 个 Toast`)
            }).catch(() => {
              this.addLog('并发打开失败')
            })
          })

        Button('并发10个')
          .layoutWeight(1)
          .onClick(() => {
            let promises: Promise<number>[] = []
            for (let i = 1; i <= 10; i++) {
              promises.push(this.openToastAsync({ message: `并发${i}`, duration: 5000 }))
            }
            Promise.all(promises).then((ids) => {
              this.addLog(`并发打开 ${ids.length} 个 Toast`)
            }).catch(() => {
              this.addLog('并发打开失败')
            })
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  BatchSection() {
    Column({ space: 12 }) {
      Text('批量测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('批量添加和移除 Toast')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      @State batchToastIds: number[] = []

      Row({ space: 8 }) {
        Button('批量打开5个')
          .layoutWeight(1)
          .onClick(async () => {
            for (let i = 0; i < 5; i++) {
              try {
                let id = await this.openToastAsync({
                  message: `批量 Toast ${this.batchToastIds.length + 1}`,
                  duration: 60000
                })
                this.batchToastIds.push(id)
              } catch (e) {
                // ignore
              }
            }
          })

        Button('批量打开10个')
          .layoutWeight(1)
          .onClick(async () => {
            for (let i = 0; i < 10; i++) {
              try {
                let id = await this.openToastAsync({
                  message: `批量 Toast ${this.batchToastIds.length + 1}`,
                  duration: 60000
                })
                this.batchToastIds.push(id)
              } catch (e) {
                // ignore
              }
            }
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('批量打开20个')
          .layoutWeight(1)
          .onClick(async () => {
            for (let i = 0; i < 20; i++) {
              try {
                let id = await this.openToastAsync({
                  message: `批量 Toast ${this.batchToastIds.length + 1}`,
                  duration: 60000
                })
                this.batchToastIds.push(id)
              } catch (e) {
                // ignore
              }
            }
          })

        Button('批量打开50个')
          .layoutWeight(1)
          .onClick(async () => {
            for (let i = 0; i < 50; i++) {
              try {
                let id = await this.openToastAsync({
                  message: `批量 Toast ${this.batchToastIds.length + 1}`,
                  duration: 60000
                })
                this.batchToastIds.push(id)
              } catch (e) {
                // ignore
              }
            }
          })
      }
      .width('100%')

      Text(`当前批量 Toast 数量: ${this.batchToastIds.length}`)
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Button('批量关闭所有')
        .width('100%')
        .backgroundColor('#F44336')
        .onClick(() => {
          this.batchToastIds.forEach(id => {
            this.closeToastById(id)
          })
          this.batchToastIds = []
        })

      Divider()

      Text('快速显示测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('快速显示100个 showToast')
        .width('100%')
        .onClick(() => {
          for (let i = 1; i <= 100; i++) {
            setTimeout(() => {
              this.showBasicToast(`快速 #${i}`, 1500)
            }, i * 50)
          }
        })

      Button('间隔100ms显示50个')
        .width('100%')
        .onClick(() => {
          for (let i = 1; i <= 50; i++) {
            setTimeout(() => {
              this.showBasicToast(`间隔 #${i}`, 2000)
            }, i * 100)
          }
        })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }

  @Builder
  PerformanceSection() {
    Column({ space: 12 }) {
      Text('性能测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      Text('Toast 性能压力测试')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      @State perfTestRunning: boolean = false
      @State perfTestCount: number = 0
      @State perfTestResult: string = ''

      Text(`已显示: ${this.perfTestCount}`)
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Row({ space: 8 }) {
        Button('快速100次')
          .layoutWeight(1)
          .enabled(!this.perfTestRunning)
          .onClick(() => {
            this.perfTestRunning = true
            this.perfTestCount = 0
            this.perfTestResult = '测试中...'
            let startTime = Date.now()
            for (let i = 0; i < 100; i++) {
              setTimeout(() => {
                this.showBasicToast(`性能测试 #${i + 1}`, 1000)
                this.perfTestCount++
                if (i === 99) {
                  let endTime = Date.now()
                  this.perfTestResult = `100次耗时: ${endTime - startTime}ms`
                  this.perfTestRunning = false
                }
              }, i * 30)
            }
          })

        Button('快速200次')
          .layoutWeight(1)
          .enabled(!this.perfTestRunning)
          .onClick(() => {
            this.perfTestRunning = true
            this.perfTestCount = 0
            this.perfTestResult = '测试中...'
            let startTime = Date.now()
            for (let i = 0; i < 200; i++) {
              setTimeout(() => {
                this.showBasicToast(`性能测试 #${i + 1}`, 1000)
                this.perfTestCount++
                if (i === 199) {
                  let endTime = Date.now()
                  this.perfTestResult = `200次耗时: ${endTime - startTime}ms`
                  this.perfTestRunning = false
                }
              }, i * 20)
            }
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('快速500次')
          .layoutWeight(1)
          .enabled(!this.perfTestRunning)
          .onClick(() => {
            this.perfTestRunning = true
            this.perfTestCount = 0
            this.perfTestResult = '测试中...'
            let startTime = Date.now()
            for (let i = 0; i < 500; i++) {
              setTimeout(() => {
                this.showBasicToast(`#`, 500)
                this.perfTestCount++
                if (i === 499) {
                  let endTime = Date.now()
                  this.perfTestResult = `500次耗时: ${endTime - startTime}ms`
                  this.perfTestRunning = false
                }
              }, i * 10)
            }
          })

        Button('快速1000次')
          .layoutWeight(1)
          .enabled(!this.perfTestRunning)
          .onClick(() => {
            this.perfTestRunning = true
            this.perfTestCount = 0
            this.perfTestResult = '测试中...'
            let startTime = Date.now()
            for (let i = 0; i < 1000; i++) {
              setTimeout(() => {
                this.showBasicToast(`#`, 500)
                this.perfTestCount++
                if (i === 999) {
                  let endTime = Date.now()
                  this.perfTestResult = `1000次耗时: ${endTime - startTime}ms`
                  this.perfTestRunning = false
                }
              }, i * 5)
            }
          })
      }
      .width('100%')

      Text(this.perfTestResult)
        .fontSize(12)
        .fontColor('#4CAF50')
        .width('100%')
        .textAlign(TextAlign.Center)

      Divider()

      Text('openToast 性能测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      @State openPerfIds: number[] = []

      Row({ space: 8 }) {
        Button('openToast x10')
          .layoutWeight(1)
          .onClick(async () => {
            let startTime = Date.now()
            for (let i = 0; i < 10; i++) {
              try {
                let id = await this.openToastAsync({
                  message: `OpenToast #${i + 1}`,
                  duration: 60000
                })
                this.openPerfIds.push(id)
              } catch (e) {
                // ignore
              }
            }
            let endTime = Date.now()
            this.perfTestResult = `openToast 10次耗时: ${endTime - startTime}ms`
          })

        Button('openToast x20')
          .layoutWeight(1)
          .onClick(async () => {
            let startTime = Date.now()
            for (let i = 0; i < 20; i++) {
              try {
                let id = await this.openToastAsync({
                  message: `OpenToast #${i + 1}`,
                  duration: 60000
                })
                this.openPerfIds.push(id)
              } catch (e) {
                // ignore
              }
            }
            let endTime = Date.now()
            this.perfTestResult = `openToast 20次耗时: ${endTime - startTime}ms`
          })
      }
      .width('100%')

      Text(`openToast 数量: ${this.openPerfIds.length}`)
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Button('清除所有 openToast')
        .width('100%')
        .backgroundColor('#F44336')
        .onClick(() => {
          this.openPerfIds.forEach(id => {
            this.closeToastById(id)
          })
          this.openPerfIds = []
        })

      Divider()

      Text('内存测试')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Button('内存压力测试 (1000次)')
        .width('100%')
        .onClick(async () => {
          this.perfTestResult = '内存测试中...'
          for (let i = 0; i < 100; i++) {
            try {
              let id = await this.openToastAsync({
                message: `内存测试 #${i + 1}`,
                duration: 500
              })
              setTimeout(() => {
                this.closeToastById(id)
              }, 600)
            } catch (e) {
              // ignore
            }
          }
          this.perfTestResult = '内存测试完成 (100次 open/close)'
        })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
  }
}
