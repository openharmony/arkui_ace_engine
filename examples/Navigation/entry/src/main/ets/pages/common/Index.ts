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

import { hilog } from '@kit.PerformanceAnalysisKit';

export function getUITestSuffix(tag) {
  return `===${tag}===`;
}

export function printPathStack(pathInfo: object | string, tag: string, keys: string[] =  ['navigationId', 'name', 'state', 'index', 'navDestinationId']): string {
  const suffix = getUITestSuffix(tag);
  if (typeof pathInfo === 'string') {
    return `${suffix} ${pathInfo}`
  }
  let res = suffix
  Object.keys(pathInfo).forEach((key) => {
    if (keys?.includes(key)) {
      res += ` ${key}:${pathInfo[key]}`
    }
  })
  return res.slice(0, res.length)
}

export function getUITestLogInfo(tag, str) {
  return `${getUITestSuffix(tag)} ${str}`;
}

export function hilog_log(tag, message, domainId = 0x1000) {
  console.log(getUITestLogInfo(tag, message))
}

interface pathStackInfos {
  pathArray: [],
  type: string
}

function filterKey(pathInfo:object) {
  let newObj:pathStackInfos = {pathArray: [], type: ''}
  const keys = ['pathArray', 'type']
  Object.keys(pathInfo).forEach((key) => {
    if (keys?.includes(key)) {
      if (key === 'pathArray' && Array.isArray(pathInfo[key])) {
        newObj[key] = pathInfo[key].map((item) => {
          return {
            name: item['name'],
            param: item['param'],
            index: item['index']
          }
        })
      } else{
        newObj[key] = pathInfo[key]
      }
    }
  })
  return newObj
}

export function filterPathStackLog(pathInfo:object) {
  return JSON.stringify(filterKey(pathInfo))
}

export function filterNavigationLog(pathInfo:object) {
  return JSON.stringify({
    navigationId: pathInfo['navigationId'],
    pathStack: filterKey(pathInfo['pathStack'])
  })
}