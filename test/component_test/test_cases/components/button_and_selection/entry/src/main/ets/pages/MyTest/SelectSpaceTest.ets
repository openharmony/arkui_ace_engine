/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function selectSpaceTest() {
  /*
    * Select组件 Space 属性
    * 找到画面id为selectSpace1,selectSpace2的Select组件
    * 找到画面文本为SelectSpace的Button组件
    * 获取selectSpace1的Space属性与期待值'30.00px'比对
    * 获取selectSpace2的Space属性与期待值'50.00vp'比对
    * 点击button，变更selectSpace2的Space属性值为$r('app.string.select_space')
    * 获取selectSpace2的Space属性与期待值$r('app.string.select_space')比对
    */
  defineTest('selectSpaceTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectSpaceTestDemo running')
    let driver: Tester = Tester.create()
    let selectSpace1: Component = await driver.findComponent(Matcher.create().id('selectSpace1').enabled(true))
    let selectSpace2: Component = await driver.findComponent(Matcher.create().id('selectSpace2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectSpace').enabled(true))

    let space1: string = await selectSpace1.getInspectorInfo()
    assertEqual(JSON.parse(space1).$attrs.space, '30.00px')

    let space2: string = await selectSpace2.getInspectorInfo()
    assertEqual(JSON.parse(space2).$attrs.space, '50.00vp')

    await button.tap()
    let space3: string = await selectSpace2.getInspectorInfo()
    assertEqual(JSON.parse(space3).$attrs.space, $r('app.string.select_space'))
  }, 0)
}