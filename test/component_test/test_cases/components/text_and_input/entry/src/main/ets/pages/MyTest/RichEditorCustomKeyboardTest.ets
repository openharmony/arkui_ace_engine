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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function richEditorCustomKeyboardTest() {
  /*
* RichEditor组件 CustomKeyboard属性
* 找到画面id为richEditorCustomKeyboard的RichEditor组件
* 点击RichEditor组件
* 找到text为1的被装饰器修饰的grid组件
* 获取grid的type类型与期待值Button比对
*/
  defineTest('richEditorCustomKeyboardTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("richEditorCustomKeyboardTestDemo running")
    let driver: Tester = Tester.create()

    let richEditor: Component = await driver.findComponent(Matcher.create().id('richEditorCustomKeyboard').enabled())
    await richEditor.tap()
    let grid: Component = await driver.findComponent(Matcher.create().text('1').enabled())
    let type: string = await grid.getType()
    assertEqual(type, 'Button')
  }, 0)
}