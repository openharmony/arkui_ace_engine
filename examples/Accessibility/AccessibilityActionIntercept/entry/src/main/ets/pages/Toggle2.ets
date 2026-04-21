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

import { Entry, $$, Text, TextAttribute, Column, AlertDialogParamWithButtons,
  ColumnAttribute, ButtonAttribute, AttributeModifier, Component,CommonAttribute,
  AccessibilityActionInterceptResult, AccessibilityAction, Button, ClickEvent, Row,
  Blank, Toggle, ToggleType, } from '@ohos.arkui.component'
import { State} from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

class MyButtonModifier implements AttributeModifier<ButtonAttribute> {
  isDark: boolean = false
  applyNormalAttribute(instance: ButtonAttribute): void {
    instance.onAccessibilityActionIntercept((action : AccessibilityAction) => {
      console.info('InterceptChildmodifier:ok')
      return AccessibilityActionInterceptResult.ACTION_RISE;
    })
  }
}

class MyButtonModifier1 implements AttributeModifier<ColumnAttribute> {
  isOn: boolean = false

  applyNormalAttribute(instance: ColumnAttribute): void {
    instance.onAccessibilityActionIntercept((action : AccessibilityAction) => {
      console.info('[symacc][modifier]father intercept 1')
      if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
        console.info('InterceptDadmodifier:ok')
        return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
      }
      console.info('[symacc][modifier]father intercept 2')
      return AccessibilityActionInterceptResult.ACTION_CONTINUE ;
    })
  }
}
@Entry
@Component
struct Toggle3 {
  @State modifier: MyButtonModifier = new MyButtonModifier()
  @State modifier1: MyButtonModifier1 = new MyButtonModifier1()
  @State private isOn: boolean = false;
  @State private isOn1: boolean = false;
  @State private isOn4: boolean = false;
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
    Column() {
      Column() {
        Column() {
          Text('子父都写成modifier,父组件打断')
          Button("intercept_button")
            .attributeModifier(this.modifier)
        }
        .padding(24)
        .width('100%')
        .attributeModifier(this.modifier1)

        Column(undefined) {
          Text('父组件设置modifier，子组件直接设置接口，父组件打断')
          Button("intercept_button1")
            .onAccessibilityActionIntercept((action: AccessibilityAction) => {
              if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
                console.info('InterceptChild:ok')
                return AccessibilityActionInterceptResult.ACTION_RISE;
              }
              return AccessibilityActionInterceptResult.ACTION_INTERCEPT
            })
        }
        .padding(24)
        .width('100%')
        .attributeModifier(this.modifier1)

        Column() {
          Text('父组件直接设置接口，父组件打断，子组件设置modifier')
          Button("intercept_button2")
            .attributeModifier(this.modifier)
        }
        .padding(24)
        .width('100%')
        .onAccessibilityActionIntercept((action: AccessibilityAction) => {
          console.info('[symacc][4]father acc intercept 1')
          if (action === AccessibilityAction.ACCESSIBILITY_CLICK) {
            console.info('[symacc][4]father acc intercept 1.1')
            this.getUIContext().showAlertDialog(this.alterParam)
            console.info('[symacc][4]father acc intercept 1.2')
            console.info('InterceptDad:ok')
            return AccessibilityActionInterceptResult.ACTION_INTERCEPT;
          }
          console.info('[symacc][4]father acc intercept 2')
          return AccessibilityActionInterceptResult.ACTION_CONTINUE;
        })
      }
    }
  }
}