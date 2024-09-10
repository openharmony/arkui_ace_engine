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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function setKeyboardAvoidModeTest() {
  /*
 * TextArea组件 setKeyboardAvoidMode属性
 * 获取 id 为 setKeyboardAvoidModeTextArea1 的 TextArea 组件
 * 点击 TextArea 组件来打开虚拟键盘
 * 查看页面中是否存在 'I can see the text of the page' 的text
 * getType 与 Text比对
 */
  defineTest('setKeyboardAvoidModeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("setKeyboardAvoidModeDemo running")
    let driver: Tester = Tester.create()
    let setKeyboardAvoidModeTextArea1: Component =
      await driver.findComponent(Matcher.create().id('setKeyboardAvoidModeTextArea1').enabled(true))
    await setKeyboardAvoidModeTextArea1.tap()
    let text1: Component =
      await driver.findComponent(Matcher.create().text('I can see the text of the page').enabled(true))
    let getType: string = await text1.getType()
    assertEqual(getType, 'Text')
    assertFalse(getType == 'Text')
  }, 0)
}