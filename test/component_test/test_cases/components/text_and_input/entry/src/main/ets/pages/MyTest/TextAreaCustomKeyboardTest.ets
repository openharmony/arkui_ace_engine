/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function textAreaCustomKeyboardTest() {
  /*
   * TextArea组件 CustomKeyboard属性
   * 找到画面id为textAreaCustomKeyboard的TextArea组件
   * 点击TextArea组件打开自定义键盘
   * 找到画面文本为1的组件
   * 获取组件的type属性与Button比对
   */
  defineTest('textAreaCustomKeyboardTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaCustomKeyboardTestDemo running")
    let driver: Tester = Tester.create()
    let textArea: Component = await driver.findComponent(Matcher.create().id('textAreaCustomKeyboard').enabled(true))
    textArea.tap()
    let grid: Component = await driver.findComponent(Matcher.create().text('1'))
    let type: string = await grid.getType()
    assertEqual(type, 'Button')
  }, 0)
}