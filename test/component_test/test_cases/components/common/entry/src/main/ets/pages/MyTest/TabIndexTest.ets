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

export default async function tabIndexTest() {
  /*
  * 使用TextArea组件 TabIndex属性
  * 找到画面id为textAreaTabIndex的TextArea组件
  * 找到画面文本为ButtonTabIndex的Button组件
  * 获取textAreaTabIndex的TabIndex属性与期待值1比对
  * 点击button，变更textAreaTabIndex的TabIndex属性值为-1
  * 获取textAreaTabIndex的TabIndex属性与期待值-1比对
  */
  defineTest('tabIndexTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabIndexTestDemo running')
    let driver: Tester = Tester.create()
    let textAreaTabIndex: Component = await driver.findComponent(Matcher.create().id('textAreaTabIndex').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonTabIndex').enabled(true))
    let tabIndex1: string = await textAreaTabIndex.getInspectorInfo()
    assertEqual(JSON.parse(tabIndex1).$attrs.tabIndex, 1)
    await button.tap()
    let tabIndex2: string = await textAreaTabIndex.getInspectorInfo()
    assertEqual(JSON.parse(tabIndex2).$attrs.tabIndex, -1)
  }, 0)
}