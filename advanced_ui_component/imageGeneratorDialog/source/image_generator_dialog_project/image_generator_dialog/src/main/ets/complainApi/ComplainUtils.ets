/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { common } from "@kit.AbilityKit";
import { uiExtensionHost, window } from "@kit.ArkUI";
import { util } from "@kit.ArkTS";


export type ComplainPageContext = common.UIAbilityContext | common.UIExtensionContext

export class UploadCountVo {
  canUploadCount: number = 5
  limit: number = 5
}

export class ComplainMediaService {
  private static readonly IMAGE_SUFFIX =
    ['bmp', 'jpg', 'jpeg', 'png', 'gif', '3gp', 'mpg', 'mpe', 'mng', 'asf', 'wmv', 'wmx', 'wvx', 'ts', 'rv', 'mkv',
      'webp', 'heic', 'heif']
  private static readonly VIDEO_SUFFIX =
    ['mp4', 'avi', 'mov', 'wmv', 'movie', 'rmvb', 'flv', 'mkv']

  public static getFileSuffixFilters(): string {
    let fileSuffixFilters: string =
      ComplainMediaService.IMAGE_SUFFIX.toString() + ',' + ComplainMediaService.VIDEO_SUFFIX.toString()
    return fileSuffixFilters
  }
}

export class ConfigVo {
  windowStage?: window.WindowStage
  windowProxy?: uiExtensionHost.UIExtensionHostWindowProxy
  isFullPage?: boolean = false
  topPadding: number = 0
  aiBarHeight: number = 0
  sidePadding: number = 0
  keyBoardHeight: number = 0
  static bundleName: string = ''
  bottomPadding: number = 0
  windowIsActive: boolean = true
  context!: ComplainPageContext
  subWindowName: string = ''
}

export function generateUUID(): string {
  return util.generateRandomUUID(true).replace(new RegExp('-', 'g'), '')
}