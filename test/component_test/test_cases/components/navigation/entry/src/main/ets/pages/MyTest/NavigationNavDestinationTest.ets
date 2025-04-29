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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function navigationNavDestinationTestTest() {
  /*
* Navigation组件 NavDestination属性
* 找到画面id为navDestination的Navigation组件
* 获取navigation1的NavDestination属性与期待值'pageOne'比对
*/
  defineTest('navigationNavDestinationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationNavDestinationTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('pageOne').enabled(true))
    await button1.tap()
    let anyBuilder1: Component = await driver.findComponent(Matcher.create().text('pageOne').enabled(true))
    let navDestination1: string = await anyBuilder1.getType()
    assertEqual(navDestination1, 'TitleBar')
  }, 0)
}