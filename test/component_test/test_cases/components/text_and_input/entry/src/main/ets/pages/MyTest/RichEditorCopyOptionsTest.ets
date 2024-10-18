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

export default async function richEditorCopyOptionsTest() {
  /*
* RichEditor组件 CopyOptions属性
* 找到画面id为richEditorCopyOptions1,richEditorCopyOptions2的RichEditor组件
* 找到画面文本为RichEditorCopyOptions1,RichEditorCopyOptions2的Button组件
* 获取richEditor1的CopyOptions属性与期待值'CopyOptions.None'比对
* 点击button1，变更richEditor1的CopyOptions属性CopyOptions值为CopyOptions.LocalDevice
* 获取richEditor1的CopyOptions属性CopyOptions与期待值'CopyOptions.Local'比对
* 获取richEditor2的CopyOptions属性与期待值'CopyOptions.InApp'比对
* 点击button2，变更richEditor2的CopyOptions属性CopyOptions值为CopyOptions.CROSS_DEVICE
* 获取richEditor2的CopyOptions属性与期待值'CopyOptions.CROSS_DEVICE'比对
*/
  defineTest('richEditorCopyOptionsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("richEditorCopyOptionsTestDemo running")
    let driver: Tester = Tester.create()
    let richEditor1: Component = await driver.findComponent(Matcher.create().id('richEditorCopyOptions1').enabled(true))
    let richEditor2: Component = await driver.findComponent(Matcher.create().id('richEditorCopyOptions2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('RichEditorCopyOptions1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('RichEditorCopyOptions2').enabled(true))

    let copyOptions1: string = await richEditor1.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions1).$attrs.copyOption, 'CopyOptions.None')
    let copyOptions2: string = await richEditor2.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions2).$attrs.copyOption, 'CopyOptions.InApp')

    await button1.tap()
    let copyOptions3: string = await richEditor2.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions3).$attrs.copyOption, 'CopyOptions.Local')
    await button2.tap()
    let copyOptions4: string = await richEditor2.getInspectorInfo()
    assertEqual(JSON.parse(copyOptions4).$attrs.copyOption, 'CopyOptions.CROSS_DEVICE')
  }, 0)
}