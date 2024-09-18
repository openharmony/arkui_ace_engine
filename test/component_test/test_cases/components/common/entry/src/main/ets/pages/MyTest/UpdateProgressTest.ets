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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function updateProgressTest() {
  /*
  * image组件 UpdateProgress属性
  * 找到画面id为 imageUpdateProgress1 的image组件
  * 找到画面文本为ButtonUpdateProgress的Button组件
  * 获取updateProgress1的updateProgress属性与期待值10比对
  * 点击button1，变更updateProgress2的updateProgress属性值为20
  * 获取updateProgress2的updateProgress属性与期待值20
  */
  defineTest('updateProgressTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("updateProgressTestDemo running")
    let driver: Tester = Tester.create()
    let imageUpdateProgress1: Component =
      await driver.findComponent(Matcher.create().id('imageUpdateProgress1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonUpdateProgress').enabled(true))
    let updateProgress1: string = await imageUpdateProgress1.getInspectorInfo()
    assertEqual(JSON.parse(updateProgress1).$attrs.updateProgress, 10)
    await button1.tap()
    let updateProgress2: string = await imageUpdateProgress1.getInspectorInfo()
    assertEqual(JSON.parse(updateProgress2).$attrs.updateProgress, 20)
  }, 0)
}