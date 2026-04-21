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

export class ComplainInfo {
  traceId: string = ''
  osVer: string = ''
  deviceType: string = ''
  deviceModel: string = ''
  osApi: string = ''
  appVer: string = ''
  anonId: string = ''
  bundleName: string = ''
  appId: string = ''
  sceneId: string = ''
  subSceneId: string = ''
  deviceId: string = ''
  accessToken?: string = ''
  sessionId?: string = ''
  jwtToken?: string = ''
  channelId?: string = ''
  fileList?: string[] = []
  source?: string = 'SingleFrame'
  businessKey?: string = ''
  darkMode?: WebDarkMode
  theme?: Record<string, string>
  isSheet?: boolean = false
  disableContactInfo?: boolean = false
  disableUserUpload?: boolean = false
  showBackButton?: boolean = true
  additionalContext: Record<string, string> = {}
  afterSubmit?: (jsonString?: string) => void
  historyBack?: () => void
  showMediaPreView?: ShowMediaPreView
  hideMediaPreView?: HideMediaPreView
  refreshAccessToken?: () => Promise<string>
  refreshComplainSessionId?: () => Promise<string>
  operate?: (options: string) => void
  onEvent?: (event: string) => void

  constructor() {
  }

  complainAddInfo(): string {
    return JSON.stringify(this);
  }
}

type ShowMediaPreView = () => void
type HideMediaPreView = () => void