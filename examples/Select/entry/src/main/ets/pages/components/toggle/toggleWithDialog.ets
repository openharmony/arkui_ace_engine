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


@Builder
export function ToggleWithDialogBuilder(name: string, param: Object) {
  toggleWithDialog()
}

@Component
export struct toggleWithDialog {
  @State isOpen: boolean = true;
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column() {
        Text('点击弹出弹框开启关闭toggle').fontSize(20).margin({ bottom: 15 })
        Row() {
          Toggle({ type: ToggleType.Switch, isOn: this.isOpen })
            .width(70)
            .height(40)
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .hitTestBehavior(HitTestMode.None)
            .onChange((isOn: boolean) => {
              console.info('Component status:' + isOn);
            })
        }.onClick(() => {
          this.getUIContext().showAlertDialog(
            {
              title: 'toggle弹框',
              message: `是否${this.isOpen ? '关闭' : '开启'}弹框`,
              autoCancel: true,
              alignment: DialogAlignment.Center,
              gridCount: 4,
              offset: { dx: 0, dy: -20 },
              primaryButton: {
                value: '取消',
                action: () => {
                  console.info('Callback when the first button is clicked');
                }
              },
              secondaryButton: {
                enabled: true,
                defaultFocus: true,
                style: DialogButtonStyle.HIGHLIGHT,
                value: this.isOpen ? '关闭' : '开启',
                action: () => {
                  this.isOpen = !this.isOpen;
                }
              },
              cancel: () => {
                console.info('Closed callbacks');
              },
              onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
                console.info('reason=' + JSON.stringify(dismissDialogAction.reason));
                console.log('dialog onWillDismiss');
                if (dismissDialogAction.reason === DismissReason.PRESS_BACK) {
                  dismissDialogAction.dismiss();
                }
                if (dismissDialogAction.reason === DismissReason.TOUCH_OUTSIDE) {
                  dismissDialogAction.dismiss();
                }
              }
            }
          )
        })
      }
      .justifyContent(FlexAlign.Center)
      .width('100%')
      .height(500)
      .justifyContent(FlexAlign.Center)
    }
    .title('toggle弹窗确认场景')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

