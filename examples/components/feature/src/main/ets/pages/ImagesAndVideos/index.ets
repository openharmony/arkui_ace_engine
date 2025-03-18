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

import { Route, RouteGroup } from 'common/src/main/ets/common/route';
import { ImageAnimatorBootcamp } from './ImageAnimatorBootcamp';
import { ImageboxGroupBootcamp } from './ImageBootcamp';


export const imagesAndVideosRoute: RouteGroup = {
  name: 'ImagesAndVideos',
  label: '图片与视频',
  children: [
    { name: 'Image', label: '图片/Image' },
    { name: 'ImageAnimator', label: '帧动画/ImageAnimator' }

  ]
};

@Builder
export function imagesAndVideosDestination(name: string, route: Route) {
  if (name === 'ImagesAndVideos/Image') {
    ImageboxGroupBootcamp({title: route.label})
  }else if (name === 'ImagesAndVideos/ImageAnimator'){
    ImageAnimatorBootcamp({title: route.label})
  }

}
