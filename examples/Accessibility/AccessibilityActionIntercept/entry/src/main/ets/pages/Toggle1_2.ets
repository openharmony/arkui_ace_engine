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
"use static"

import { Entry, $$, AccessibilityAction, AccessibilityActionInterceptResult,
  AlertDialogParamWithButtons, Text, TextAttribute, Column, Scroll, Divider,
  Component, Tabs, TabsController, TabContent, TabsOptions, BarPosition, Builder,
  CommonAttribute, Button, ClickEvent, Row, Blank, Toggle, ToggleType, Color} from '@ohos.arkui.component'
import { State} from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct Toggle2 {
  @State private isOn: boolean = false;
  @State private isOn1: boolean = false;
  @State private isOn2: boolean = false;
  @State private isOn3: boolean = false;
  @State private isOn4: boolean = false;
  @State private isOn5: boolean = false;
  @State selectedFontColor: string = '#007DFF';
  @State fontColor: string = '#182431';
  private controller: TabsController = new TabsController;
  alterParam: AlertDialogParamWithButtons = {
    title: '标题',
    message: '内容信息',
    primaryButton: {
      value: '确认',
      action: () => {
        this.isOn = !this.isOn;
      }
    },
    secondaryButton: {
      value: '取消',
      action: () => {
      }
    }
  } as AlertDialogParamWithButtons;

  build() {
        Scroll() {
          Column(undefined) {
            Column(undefined) {
              Column(undefined) {
                Column(undefined) {
                  Text('B冒泡+C不注入+D继续,子组件冒泡：父节点B和D都能触发回调函数，并且字节点A能触发无障碍点击事件')
                  Toggle({ type: ToggleType.Switch, isOn: this.isOn4 })
                    .onAccessibilityActionIntercept((action) => {
                      if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                        console.info('InterceptChild:ok')
                        return AccessibilityActionInterceptResult.ACTION_RISE;
                      }
                      console.info('InterceptChild:no')
                      return AccessibilityActionInterceptResult.ACTION_INTERCEPT
                    })
                }
                .onAccessibilityActionIntercept((action) => {
                  if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                    console.info('InterceptDadB:ok')
                    return AccessibilityActionInterceptResult.ACTION_RISE
                  }
                  console.info('InterceptDad:no')
                  return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
                })
              }
            }
                .onAccessibilityActionIntercept((action) => {
              if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                console.info('InterceptDadD:ok')
                return AccessibilityActionInterceptResult.ACTION_CONTINUE
              }
              console.info('InterceptDad:no')
              return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
            })
            Column(undefined) {
              Column(undefined) {
                Column(undefined) {
                  Text('B冒泡+C不注入+D打断：父节点B和D都能触发回调函数，并且字节点A不能触发无障碍点击事件')
                  Toggle({ type: ToggleType.Switch, isOn: this.isOn1 })
                    .onAccessibilityActionIntercept((action) => {
                      if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                        console.info('InterceptChild:ok')
                        return AccessibilityActionInterceptResult.ACTION_RISE;
                      }
                      console.info('InterceptChild:no')
                      return AccessibilityActionInterceptResult.ACTION_INTERCEPT
                    })
                }.width('100%').padding(20)
                .onAccessibilityActionIntercept((action) => {
                  if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                    console.info('InterceptDadB:ok')
                    return AccessibilityActionInterceptResult.ACTION_RISE
                  }
                  console.info('InterceptDad:no')
                  return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
                })
              }
            }
            .onAccessibilityActionIntercept((action) => {
              if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                console.info('InterceptDadD:ok')
                return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
              }
              console.info('InterceptDadD:no')
              return AccessibilityActionInterceptResult.ACTION_CONTINUE
            })
            Column(undefined) {
              Column(undefined) {
                Column(undefined) {
                  Text('B冒泡+C不注入+D冒泡：父节点B和D都能触发回调函数，并且字节点A能触发无障碍点击事件')
                  Toggle({ type: ToggleType.Checkbox, isOn: this.isOn2 })
                    .onAccessibilityActionIntercept((action) => {
                      if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                        console.info('InterceptChild1:ok')
                        return AccessibilityActionInterceptResult.ACTION_RISE;
                      }
                      console.info('InterceptChild:no')
                      return AccessibilityActionInterceptResult.ACTION_INTERCEPT
                    })
                }.width('100%').backgroundColor(0xEFEFEF).padding(20)
                .onAccessibilityActionIntercept((action) => {
                  if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                    console.info('InterceptDadB:ok')
                    return AccessibilityActionInterceptResult.ACTION_RISE;
                  }
                  console.info('InterceptDadB:no')
                  return AccessibilityActionInterceptResult.ACTION_CONTINUE
                })
              }
            }
            .border({
              color: Color.Green,
              width: 8
            })
            .onAccessibilityActionIntercept((action) => {
              if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                console.info('InterceptDadD:ok')
                return AccessibilityActionInterceptResult.ACTION_RISE
              }
              console.info('InterceptDadD:no')
              return AccessibilityActionInterceptResult.ACTION_CONTINUE;
            })
            Column(undefined) {
              Column(undefined) {
                Text('父节点均不注入：无父节点能触发回调函数，并且字节点A能触发无障碍点击事件')
                Toggle({ type: ToggleType.Button, isOn: true }) {
                  Text('Toggle组件').fontColor('#182431').fontSize(12)
                }
                .onAccessibilityActionIntercept((action) => {
                  if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                    console.info('InterceptChild:ok')
                    return AccessibilityActionInterceptResult.ACTION_RISE;
                  }
                  console.info('InterceptChild:no')
                  return AccessibilityActionInterceptResult.ACTION_INTERCEPT
                })
              }
              .border({
                color: Color.Green,
                width: 8
              })
            }
            .padding(15)
            .width('100%')
            .border({
              color: Color.Red,
              width: 8
            })

            Column(undefined) {
              Column(undefined) {
                Text('子组件不设置Intercept,父组件冒泡')
                Toggle({ type: ToggleType.Button, isOn: true }) {
                  Text('Toggle组件').fontColor('#182431').fontSize(12)
                }
              }
              .border({
                color: Color.Green,
                width: 8
              })
              .onAccessibilityActionIntercept((action) => {
                if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                  console.info('InterceptDadB:ok')
                  return AccessibilityActionInterceptResult.ACTION_RISE
                }
                console.info('InterceptDadB:no')
                return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
              })
            }
            .padding(15)
            .width('100%')
            .border({
              color: Color.Red,
              width: 8
            })
            .onAccessibilityActionIntercept((action) => {
              if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                console.info('InterceptDadC:ok')
                return AccessibilityActionInterceptResult.ACTION_CONTINUE
              }
              console.info('InterceptDadC:no')
              return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
            })
        }
       }
  }
}