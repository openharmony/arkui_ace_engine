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

export default async function navigationMenusTestTest() {
  /*
* Navigation组件 Menus属性
* 找到画面id为navigationMenus1,navigationMenus2的Navigation组件
* 获取navigation1的Menus属性与期待值$r('sys.media.ohos_ic_public_text')比对
* 获取navigation2的Menus.value属性与期待值"menu"比对
* 获取navigation2的Menus.icon属性与期待值'../../../resources/base/media/test_image.png'比对
* 获取navigation2的Menus.action.builder属性与期待值$r('sys.media.ohos_ic_public_text')比对
*/
  defineTest('navigationMenusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationMenusTestDemo running")
    let driver: Tester = Tester.create()
    let navigation2: Component = await driver.findComponent(Matcher.create().id('navigationMenus2').enabled(true))
    let anyBuilder: Component = await driver.findComponent(Matcher.create().text('Exit').enabled(true))
    let myBuilder = await anyBuilder.getType()
    assertEqual(myBuilder, 'Text')

    let menus2: string = await navigation2.getInspectorInfo()
    assertEqual(JSON.parse(menus2).$attrs.menus.value, "menu")
    assertEqual(JSON.parse(menus2).$attrs.menus.icon, '../../../resources/base/media/test_image.png')
    assertEqual(JSON.parse(menus2)
      .$attrs
      .menus
      .action
      .builder, $r('sys.media.ohos_ic_public_text'))
  }, 0)
}