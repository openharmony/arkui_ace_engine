/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import router from '@system.router'

/* Handles showing one page after another.
  After the last page callback is called so that caller can show the final report.
*/
export class PageController {
  private static pages: string[] = []
  private static current = 0
  private static onComplete: (() => void) | null = null

  static registerPages(pages: string[]) {
    this.pages = pages
    this.current = 0
  }

  static start(testsCompletedCallback : ()=>void) {
    PageController.onComplete = testsCompletedCallback;
    if (this.pages.length > 0) {
      router.push({ uri: this.pages[0] })
    }
  }

  static notifyPageFinished() {
    this.current++
    if (this.current < this.pages.length) {
      router.push({ uri: this.pages[this.current] })
    } else {
        this.onComplete()
    }
  }

}
