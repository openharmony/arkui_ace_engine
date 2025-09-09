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

import { GridListItem } from './GridList';

export class CommonAppGridLayoutUtility {
  private static instance: CommonAppGridLayoutUtility;

  static getInstance(): CommonAppGridLayoutUtility {
    if (!CommonAppGridLayoutUtility.instance) {
      CommonAppGridLayoutUtility.instance = new CommonAppGridLayoutUtility();
    }
    return CommonAppGridLayoutUtility.instance;
  }

  /**
   * 获取行、列信息
   *
   * @param appListInfo
   * @returns
   */
  public getGridLayoutOptions(appListInfo: GridListItem[]): GridLayoutOptions {
    if (!appListInfo || appListInfo.length === 0) {
      return { regularSize: [1, 1] };
    }
    return {
      onGetRectByIndex: (index:number): number[] => {
        if (index >= appListInfo.length) {
          return [-1, 1, -1, 1];
        }
        return [appListInfo[index].row, appListInfo[index].col, 1, 1];
      },
      regularSize: [1, 1]
    };
  }
}
