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

import drawing from '@ohos.graphics.drawing';
import { DrawContext } from '@ohos.arkui.node';

export class MyFullDrawModifier extends DrawModifier {
  public scaleX: number = 1;
  public scaleY: number = 1;

  drawFront(context: DrawContext): void {
    let canvas = context.canvas;
    let pen = new drawing.Pen();
    pen.setAntiAlias(true)
    pen.setStrokeWidth(2);
    pen.setColor({
      alpha: 255,
      red: 0,
      green: 125,
      blue: 255
    });
    canvas.attachPen(pen);
    canvas.drawCircle(8, 28, 6);
    canvas.detachPen();

    pen.setStrokeWidth(6);
    pen.setColor({
      alpha: 255,
      red: 255,
      green: 255,
      blue: 255
    });
    canvas.attachPen(pen);
    canvas.drawCircle(8, 28, 1);
    canvas.detachPen();
  }

  drawBehind(context: DrawContext): void {
    let canvas = context.canvas;
    let pen = new drawing.Pen();
    pen.setAntiAlias(true)
    pen.setStrokeWidth(1);
    pen.setColor({
      alpha: 255,
      red: 157,
      green: 157,
      blue: 157
    });
    canvas.attachPen(pen);
    canvas.drawLine(8, 0, 8, 106);
    canvas.detachPen();
  }
}