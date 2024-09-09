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

export default async function textCopyOptionTest() {
  /*
   * Text组件 CopyOption属性
   * 找到画面id为textCopyOption1,textCopyOption2的Text组件
   * 找到画面文本为TextCopyOption1,TextCopyOption2的Button组件
   * 获取text1的CopyOption属性与期待值'CopyOptions.CROSS_DEVICE'比对
   * 获取text2的CopyOption属性与期待值'CopyOptions.None'比对
   * 点击button1，变更text1的CopyOption属性值为CopyOptions.InApp
   * 获取text1的CopyOption属性与期待值'CopyOptions.InApp'比对
   * 点击button2，变更text1的CopyOption属性值为CopyOptions.LocalDevice
   * 获取text1的CopyOption属性与期待值'CopyOptions.Local'比对
   */
  defineTest('textCopyOptionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textCopyOptionTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textCopyOption1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textCopyOption2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextCopyOption1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextCopyOption2').enabled(true))

    let copyOption1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(copyOption1).$attrs.copyOption, 'CopyOptions.CROSS_DEVICE')
    let copyOption2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(copyOption2).$attrs.copyOption, 'CopyOptions.None')
    await button1.tap()
    let copyOption3: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(copyOption3).$attrs.copyOption, 'CopyOptions.InApp')
    await button2.tap()
    let copyOption4: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(copyOption4).$attrs.copyOption, 'CopyOptions.Local')
  }, 0)
}