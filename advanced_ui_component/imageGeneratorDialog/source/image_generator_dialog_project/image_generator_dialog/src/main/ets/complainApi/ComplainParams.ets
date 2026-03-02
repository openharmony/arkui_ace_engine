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

import { uiExtensionHost, window } from "@kit.ArkUI"
import { ComplainPageContext } from "./ComplainUtils"
import { IGrsClient } from "./IGrsClient"

export class EmphasizedColor {
  backgroundLight?: string
  backgroundDark?: string
  textLight?: string
  textDark?: string
}

export enum RefreshATEnum {
  PREFER_CACHE = 0,
  REMOTE = 1,
}

export class ComplainParams {
  // 半模态层级
  sheetMode?: SheetMode = SheetMode.OVERLAY
  // 应用ID
  appId: string = ''
  customTitle?: Resource
  context?: ComplainPageContext
  pathInfo: NavPathStack = new NavPathStack()
  setComplainAccessToken?: (mode?: RefreshATEnum) => Promise<string>
  SetComplainSessionId?: () => Promise<string>
  afterSubmit?: (jsonString?: string) => void
  onBackPressed?: () => void
  onHistoryBack?: () => void
  sceneId: string = ''
  subSceneId: string = ''
  deviceId?: string = ''
  jwtToken?: string
  channelId?: string
 grsClien?: IGrsClient
  emphasizedColor?: EmphasizedColor
  theme?: Record<string, string>
  fileList?: string[] = []
  colorMode?: ColorMode
  businessKey?: string
  disableContactInfo?: boolean = false
  disableUserUpload?: boolean = false
  additionalContext: Record<string, string> = {}
  windowStage?: window.WindowStage
  windowProxy?: uiExtensionHost.UIExtensionHostWindowProxy
  isFullPage?: boolean
  fromSheet?: boolean
  topPadding?: number
  hdsCloseBindSheet?: Callback<void>
}

export const PAGE_COMPLAIN = 'WISE_SUPPORT_COMPLAIN'