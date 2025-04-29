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

export default async function idTest() {
  /*
  * text组件 id属性
  * 找到画面中 image 组件
  * 获取image组件的id属性与期待值'imageId'比对
  */
  defineTest('idTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("idTest running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().type('Image').enabled(true))
    let id1: string = await image.getId()
    assertEqual(id1, 'imageId')
  }, 0)
}