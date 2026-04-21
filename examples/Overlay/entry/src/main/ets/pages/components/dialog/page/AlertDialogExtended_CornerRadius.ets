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


interface AlertDialogExtendedCornerRadiusInterface {
  radius: number;
  name: string;
}

@Entry
@Component
struct AlertDialogExtendedCornerRadius {
  pathStack: NavPathStack = new NavPathStack()
  @State currentRadius: string = '默认'
  @State logMessage: string = '选择上方圆角值查看效果'

  showAlertDialogWithRadius(radius: number, name: string) {
    this.currentRadius = name
    AlertDialog.show({
      title: '圆角测试',
      message: `当前圆角半径: ${name}\n\n观察弹窗的圆角效果`,
      cornerRadius: radius,
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {
          this.logMessage = `使用了 ${name} 圆角半径`
          console.log(`Dialog with corner radius ${name}`)
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          this.logMessage = '用户取消了圆角测试'
        }
      }
    })
  }

  build() {
    NavDestination() {
      Column({ space: 15 }) {
        Text('AlertDialog 圆角测试用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // 当前状态显示
        Row() {
          Text('当前圆角: ')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.currentRadius)
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Blue)
        }
        .width('100%')
        .padding(10)
        .backgroundColor('#F0F8FF')
        .borderRadius(8)
        .margin({ left: 10, right: 10 })

        // 小圆角测试
        Text('小圆角测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        Row({ space: 8 }) {
          ForEach([
            { radius: 0, name: '0px (直角)' },
            { radius: 2, name: '2px' },
            { radius: 4, name: '4px' },
            { radius: 6, name: '6px' },
            { radius: 8, name: '8px' }
          ], (item: AlertDialogExtendedCornerRadiusInterface) => {
            Button(item.name)
              .width('19%')
              .borderRadius(item.radius)
              .onClick(() => this.showAlertDialogWithRadius(item.radius, item.name))
          })
        }.width('100%').padding({ left: 10, right: 10 })

        // 中等圆角测试
        Text('中等圆角测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Row({ space: 8 }) {
          ForEach([
            { radius: 10, name: '10px' },
            { radius: 12, name: '12px' },
            { radius: 14, name: '14px' },
            { radius: 16, name: '16px' },
            { radius: 18, name: '18px' }
          ], (item: AlertDialogExtendedCornerRadiusInterface) => {
            Button(item.name)
              .width('19%')
              .borderRadius(item.radius)
              .onClick(() => this.showAlertDialogWithRadius(item.radius, item.name))
          })
        }.width('100%').padding({ left: 10, right: 10 })

        // 大圆角测试
        Text('大圆角测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Row({ space: 8 }) {
          ForEach([
            { radius: 20, name: '20px' },
            { radius: 24, name: '24px' },
            { radius: 28, name: '28px' },
            { radius: 32, name: '32px' }
          ], (item: AlertDialogExtendedCornerRadiusInterface) => {
            Button(item.name)
              .width('24%')
              .borderRadius(item.radius)
              .onClick(() => this.showAlertDialogWithRadius(item.radius, item.name))
          })
        }.width('100%').padding({ left: 10, right: 10 })

        // 超大圆角测试
        Text('超大圆角测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Row({ space: 8 }) {
          ForEach([
            { radius: 40, name: '40px' },
            { radius: 48, name: '48px' },
            { radius: 56, name: '56px' },
            { radius: 64, name: '64px' }
          ], (item: AlertDialogExtendedCornerRadiusInterface) => {
            Button(item.name)
              .width('24%')
              .borderRadius(item.radius)
              .onClick(() => this.showAlertDialogWithRadius(item.radius, item.name))
          })
        }.width('100%').padding({ left: 10, right: 10 })

        // 百分比圆角测试
        Text('百分比圆角测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Row({ space: 8 }) {
          ForEach([
            { radius: '5%', name: '5%' },
            { radius: '10%', name: '10%' },
            { radius: '15%', name: '15%' },
            { radius: '20%', name: '20%' }
          ], (item: AlertDialogExtendedCornerRadiusInterface) => {
            Button(item.name)
              .width('24%')
              .onClick(() => this.showAlertDialogWithRadius(item.radius, item.name))
          })
        }.width('100%').padding({ left: 10, right: 10 })

        // 特殊圆角测试
        Text('特殊圆角测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        GridRow({ columns: 2, gutter: 8 }) {
          GridCol() {
            Button('圆形弹窗')
              .width('100%')
              .onClick(() => this.showAlertDialogWithRadius(100, '100px'))
          }
          GridCol() {
            Button('默认圆角')
              .width('100%')
              .onClick(() => {
                this.currentRadius = '默认'
                AlertDialog.show({
                  title: '默认圆角测试',
                  message: '使用系统默认圆角\n不设置cornerRadius属性',
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '使用了默认圆角'
                    }
                  }
                })
              })
          }
        }.width('100%').margin({ left: 10, right: 10 })

        // 圆角对比测试
        Text('圆角对比测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Button('同时显示多个圆角')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => {
            const radii = [0, 8, 16, 24, 32]
            radii.forEach((radius, index) => {
              setTimeout(() => {
                AlertDialog.show({
                  title: `圆角 ${radius}px`,
                  message: `对比不同圆角半径的效果`,
                  cornerRadius: radius,
                  autoCancel: true,
                  primaryButton: {
                    value: '关闭',
                    action: () => {}
                  }
                })
              }, index * 300)
            })
          })

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
          .margin({ left: 10, right: 10 })

        Blank()
      }
      .width('100%')
      .height('100%')
    }
    .title('AlertDialog 圆角测试')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
