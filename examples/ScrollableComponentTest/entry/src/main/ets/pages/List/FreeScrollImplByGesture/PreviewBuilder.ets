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

import { curves } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { ImageData, ImageViewModel, PreviewState, PageParams } from './ImageViewPage';

// Global variable for accessing pageNav in Builder
let globalPageNav: NavPathStack = new NavPathStack();

// Gesture state variables
let scaleOnPinchStart: number = 1.0;
let offsetXOnPinchStart: number = 0;
let offsetYOnPinchStart: number = 0;
let pinchCenterX: number = 0;
let pinchCenterY: number = 0;
let offsetXOnPanStart: number = 0;
let offsetYOnPanStart: number = 0;

// Set global pageNav
export function setGlobalPageStack(navStack: NavPathStack): void {
  globalPageNav = navStack;
}

// Animation execution function using UIContext's animateTo
function runAnimation(uiContext: UIContext, duration: number, curve: ICurve, callback: () => void, finishCallback: () => void): void {
  uiContext.animateTo({ duration: duration, curve: curve, onFinish: finishCallback }, callback);
}

// Build preview page
@Builder
export function PreviewPageBuilder(name: string, param: Object, viewModel: ImageViewModel,
  previewState: PreviewState, pageNav: NavPathStack, uiContext: UIContext): void {
  setGlobalPageStack(pageNav);

  NavDestination() {
    Stack() {
      // Title bar at top layer
      if (previewState.showTitleBar) {
        Row() {
          Button() {
            Image($r('sys.symbol.chevron_left'))
              .width(24)
              .height(24)
              .fillColor(Color.White)
          }
          .type(ButtonType.Normal)
          .backgroundColor(Color.Transparent)
          .onClick(() => {
            globalPageNav.pop();
          })

          Blank()

          Button('Download')
            .fontSize(16)
            .fontColor(Color.White)
            .backgroundColor(Color.Transparent)
            .onClick(() => {
            })
        }
        .width('100%')
        .height(56)
        .padding({ left: 16, right: 16 })
        .backgroundColor('rgba(0, 0, 0, 0.5)')
        .position({ x: 0, y: 0 })
        .zIndex(1)
      }

      // Image container
      Stack() {
        Image(viewModel.currentPixelMap)
          .width(viewModel.baseImageWidth * previewState.scale)
          .height(viewModel.baseImageHeight * previewState.scale)
          .objectFit(ImageFit.Fill)
          .offset({
            x: previewState.offsetX,
            y: previewState.offsetY
          })
          .geometryTransition(`shared_image_${viewModel.selectedIndex}`)
          .gesture(
            // Combined gesture: pinch and pan (exclusive)
            GestureGroup(GestureMode.Exclusive,
              // Pinch gesture
              PinchGesture({ fingers: 2 })
                .onActionStart((event: GestureEvent) => {
                  // Allow interruption during pinch rebound
                  if (previewState.isPinchRebounding) {
                    previewState.isPinchRebounding = false;
                    previewState.isAnimating = false;
                  }

                  // Only allow pinch when not dragging, not in double-tap animation, and not in page transition
                  if (previewState.isDragging || (!previewState.isPinchRebounding && previewState.isAnimating) || previewState.isPageTransitioning) {
                    return;
                  }

                  previewState.isPinching = true;
                  // Save scale and offset at gesture start as baseline for calculation
                  scaleOnPinchStart = previewState.scale;
                  offsetXOnPinchStart = previewState.offsetX;
                  offsetYOnPinchStart = previewState.offsetY;

                  // Get pinch center position as scale focus
                  if (event.fingerList && event.fingerList.length >= 2) {
                    const finger0 = event.fingerList[0];
                    const finger1 = event.fingerList[1];
                    pinchCenterX = (finger0.localX + finger1.localX) / 2;
                    pinchCenterY = (finger0.localY + finger1.localY) / 2;
                  } else {
                    // Fallback: use screen center
                    pinchCenterX = previewState.containerWidth / 2;
                    pinchCenterY = previewState.containerHeight / 2;
                  }
                })
                .onActionUpdate((event: GestureEvent) => {
                  if (previewState.isAnimating || !previewState.isPinching || previewState.isPageTransitioning) {
                    return;
                  }

                  // Use initial scale as baseline to calculate new scale
                  let newScale = scaleOnPinchStart * event.scale;

                  // Damping effect calculation
                  if (newScale < 1.0) {
                    const exceedPercent = 1.0 - newScale;
                    newScale = 1.0 - exceedPercent * 0.3;
                  } else if (newScale > 3.0) {
                    const exceedPercent = newScale - 2.0;
                    newScale = 2.0 + exceedPercent * 0.3;
                  }

                  // Calculate image display size at target scale
                  const imageDisplayWidth = viewModel.baseImageWidth * newScale;
                  const imageDisplayHeight = viewModel.baseImageHeight * newScale;
                  const screenWidth = previewState.containerWidth;
                  const screenHeight = previewState.containerHeight;

                  let newOffsetX: number;
                  let newOffsetY: number;

                  // Choose scale center based on image and screen size relationship
                  // If image is smaller than or equal to screen in a direction, use screen center (keep centered)
                  // If image is larger than screen in a direction, use pinch center (keep point under fingers unchanged)
                  if (imageDisplayWidth <= screenWidth) {
                    // Image width <= screen width, keep centered in X direction
                    newOffsetX = 0;
                  } else {
                    // Image width > screen width, use pinch center as scale center in X direction
                    const scaleRatio = newScale / scaleOnPinchStart;
                    const centerOffsetX = pinchCenterX - screenWidth / 2;
                    // Calculate new offset to keep pinch center position unchanged on screen
                    newOffsetX = offsetXOnPinchStart * scaleRatio + centerOffsetX * (1 - scaleRatio);

                    // Clamp to valid range
                    const minX = (screenWidth - imageDisplayWidth) / 2;
                    const maxX = (imageDisplayWidth - screenWidth) / 2;
                    if (newOffsetX < minX) {
                      newOffsetX = minX;
                    } else if (newOffsetX > maxX) {
                      newOffsetX = maxX;
                    }
                  }

                  if (imageDisplayHeight <= screenHeight) {
                    // Image height <= screen height, keep centered in Y direction
                    newOffsetY = 0;
                  } else {
                    // Image height > screen height, use pinch center as scale center in Y direction
                    const scaleRatio = newScale / scaleOnPinchStart;
                    const centerOffsetY = pinchCenterY - screenHeight / 2;
                    // Calculate new offset to keep pinch center position unchanged on screen
                    newOffsetY = offsetYOnPinchStart * scaleRatio + centerOffsetY * (1 - scaleRatio);

                    // Clamp to valid range
                    const minY = (screenHeight - imageDisplayHeight) / 2;
                    const maxY = (imageDisplayHeight - screenHeight) / 2;
                    if (newOffsetY < minY) {
                      newOffsetY = minY;
                    } else if (newOffsetY > maxY) {
                      newOffsetY = maxY;
                    }
                  }

                  previewState.scale = newScale;
                  previewState.offsetX = newOffsetX;
                  previewState.offsetY = newOffsetY;
                })
                .onActionEnd(() => {
                  previewState.isPinching = false;

                  // Determine final scale (handle boundary cases)
                  let targetScale = previewState.scale;
                  if (targetScale < 1.0) {
                    targetScale = 1.0;
                  } else if (targetScale > 2.0) {
                    targetScale = 2.0;
                  }

                  // Calculate image display size at target scale
                  const imageDisplayWidth = viewModel.baseImageWidth * targetScale;
                  const imageDisplayHeight = viewModel.baseImageHeight * targetScale;
                  const screenWidth = previewState.containerWidth;
                  const screenHeight = previewState.containerHeight;

                  let targetOffsetX: number;
                  let targetOffsetY: number;

                  // Choose scale center based on image and screen size relationship (consistent with onActionUpdate)
                  if (imageDisplayWidth <= screenWidth) {
                    targetOffsetX = 0;
                  } else {
                    const scaleRatio = targetScale / previewState.scale;
                    const centerOffsetX = pinchCenterX - screenWidth / 2;
                    targetOffsetX = previewState.offsetX * scaleRatio + centerOffsetX * (1 - scaleRatio);

                    // Clamp to valid range
                    const minX = (screenWidth - imageDisplayWidth) / 2;
                    const maxX = (imageDisplayWidth - screenWidth) / 2;
                    if (targetOffsetX < minX) {
                      targetOffsetX = minX;
                    } else if (targetOffsetX > maxX) {
                      targetOffsetX = maxX;
                    }
                  }

                  if (imageDisplayHeight <= screenHeight) {
                    targetOffsetY = 0;
                  } else {
                    const scaleRatio = targetScale / previewState.scale;
                    const centerOffsetY = pinchCenterY - screenHeight / 2;
                    targetOffsetY = previewState.offsetY * scaleRatio + centerOffsetY * (1 - scaleRatio);

                    // Clamp to valid range
                    const minY = (screenHeight - imageDisplayHeight) / 2;
                    const maxY = (imageDisplayHeight - screenHeight) / 2;
                    if (targetOffsetY < minY) {
                      targetOffsetY = minY;
                    } else if (targetOffsetY > maxY) {
                      targetOffsetY = maxY;
                    }
                  }

                  // Execute rebound animation if adjustment is needed
                  const needAdjustment = targetScale !== previewState.scale ||
                    targetOffsetX !== previewState.offsetX ||
                    targetOffsetY !== previewState.offsetY;

                  if (needAdjustment) {
                    previewState.isAnimating = true;
                    previewState.isPinchRebounding = true;
                    runAnimation(uiContext, 200, curves.springMotion(0.6, 0.8), () => {
                      previewState.scale = targetScale;
                      previewState.offsetX = targetOffsetX;
                      previewState.offsetY = targetOffsetY;
                    }, () => {
                      previewState.isAnimating = false;
                      previewState.isPinchRebounding = false;
                    });
                  }
                })
                .onActionCancel(() => {
                  previewState.isPinching = false;
                }),
              // Pan gesture
              PanGesture()
                .onActionStart(() => {
                  // Allow interruption during pan rebound
                  if (previewState.isPanRebounding) {
                    previewState.isPanRebounding = false;
                    previewState.isAnimating = false;
                  }

                  // Only allow pan when not pinching, not in double-tap animation, and not in page transition
                  if (previewState.isPinching || (!previewState.isPanRebounding && previewState.isAnimating) || previewState.isPageTransitioning) {
                    return;
                  }

                  previewState.isDragging = true;
                  // Save offset at gesture start as baseline for calculation
                  offsetXOnPanStart = previewState.offsetX;
                  offsetYOnPanStart = previewState.offsetY;
                })
                .onActionUpdate((event: GestureEvent) => {
                  if (previewState.isAnimating || previewState.isPinching || !previewState.isDragging || previewState.isPageTransitioning) {
                    return;
                  }

                  // Use initial offset as baseline to calculate new offset
                  let rawOffsetX = offsetXOnPanStart + event.offsetX;
                  let rawOffsetY = offsetYOnPanStart + event.offsetY;

                  let newOffsetX = rawOffsetX;
                  let newOffsetY = rawOffsetY;

                  const imageDisplayWidth = viewModel.baseImageWidth * previewState.scale;
                  const imageDisplayHeight = viewModel.baseImageHeight * previewState.scale;
                  const screenWidth = previewState.containerWidth;
                  const screenHeight = previewState.containerHeight;

                  // X direction damping and limits
                  if (imageDisplayWidth <= screenWidth) {
                    // Image does not fully cover screen width, legal offset is 0 (centered)
                    // Apply damping: allow out-of-bounds drag but with resistance
                    const legalOffsetX = 0;
                    const exceed = Math.abs(rawOffsetX - legalOffsetX);
                    const direction = rawOffsetX < legalOffsetX ? -1 : 1;
                    newOffsetX = legalOffsetX + direction * exceed * 0.3;
                  } else {
                    // Image width > screen width, apply damping
                    const minX = (screenWidth - imageDisplayWidth) / 2;
                    const maxX = (imageDisplayWidth - screenWidth) / 2;
                    if (rawOffsetX < minX) {
                      const exceed = minX - rawOffsetX;
                      newOffsetX = minX - exceed * 0.3;
                    } else if (rawOffsetX > maxX) {
                      const exceed = rawOffsetX - maxX;
                      newOffsetX = maxX + exceed * 0.3;
                    }
                  }

                  // Y direction damping and limits
                  if (imageDisplayHeight <= screenHeight) {
                    // Image does not fully cover screen height, legal offset is 0 (centered)
                    // Apply damping: allow out-of-bounds drag but with resistance
                    const legalOffsetY = 0;
                    const exceed = Math.abs(rawOffsetY - legalOffsetY);
                    const direction = rawOffsetY < legalOffsetY ? -1 : 1;
                    newOffsetY = legalOffsetY + direction * exceed * 0.3;
                  } else {
                    // Image height > screen height, apply damping
                    const minY = (screenHeight - imageDisplayHeight) / 2;
                    const maxY = (imageDisplayHeight - screenHeight) / 2;
                    if (rawOffsetY < minY) {
                      const exceed = minY - rawOffsetY;
                      newOffsetY = minY - exceed * 0.3;
                    } else if (rawOffsetY > maxY) {
                      const exceed = rawOffsetY - maxY;
                      newOffsetY = maxY + exceed * 0.3;
                    }
                  }

                  previewState.offsetX = newOffsetX;
                  previewState.offsetY = newOffsetY;
                })
                .onActionEnd(() => {
                  previewState.isDragging = false;

                  const imageDisplayWidth = viewModel.baseImageWidth * previewState.scale;
                  const imageDisplayHeight = viewModel.baseImageHeight * previewState.scale;
                  const screenWidth = previewState.containerWidth;
                  const screenHeight = previewState.containerHeight;

                  let targetOffsetX: number;
                  let targetOffsetY: number;
                  let needRebound = false;

                  // X direction: if image width <= screen width, force center; otherwise clamp to valid range
                  if (imageDisplayWidth <= screenWidth) {
                    // Image does not fully cover screen width, center display
                    if (previewState.offsetX !== 0) {
                      targetOffsetX = 0;
                      needRebound = true;
                    } else {
                      targetOffsetX = previewState.offsetX;
                    }
                  } else {
                    // Image width > screen width, calculate movable range and clamp
                    const minX = (screenWidth - imageDisplayWidth) / 2;
                    const maxX = (imageDisplayWidth - screenWidth) / 2;
                    // Adjust to nearest valid position based on shortest movement distance
                    if (previewState.offsetX < minX) {
                      targetOffsetX = minX;
                      needRebound = true;
                    } else if (previewState.offsetX > maxX) {
                      targetOffsetX = maxX;
                      needRebound = true;
                    } else {
                      targetOffsetX = previewState.offsetX;
                    }
                  }

                  // Y direction: if image height <= screen height, force center; otherwise clamp to valid range
                  if (imageDisplayHeight <= screenHeight) {
                    // Image does not fully cover screen height, center display
                    if (previewState.offsetY !== 0) {
                      targetOffsetY = 0;
                      needRebound = true;
                    } else {
                      targetOffsetY = previewState.offsetY;
                    }
                  } else {
                    // Image height > screen height, calculate movable range and clamp
                    const minY = (screenHeight - imageDisplayHeight) / 2;
                    const maxY = (imageDisplayHeight - screenHeight) / 2;
                    // Adjust to nearest valid position based on shortest movement distance
                    if (previewState.offsetY < minY) {
                      targetOffsetY = minY;
                      needRebound = true;
                    } else if (previewState.offsetY > maxY) {
                      targetOffsetY = maxY;
                      needRebound = true;
                    } else {
                      targetOffsetY = previewState.offsetY;
                    }
                  }

                  // Execute rebound animation if needed
                  if (needRebound) {
                    previewState.isAnimating = true;
                    previewState.isPanRebounding = true;
                    runAnimation(uiContext, 200, curves.springMotion(0.6, 0.8), () => {
                      previewState.offsetX = targetOffsetX;
                      previewState.offsetY = targetOffsetY;
                    }, () => {
                      previewState.isAnimating = false;
                      previewState.isPanRebounding = false;
                    });
                  }
                })
                .onActionCancel(() => {
                  previewState.isDragging = false;
                })
            )
          )
          .gesture(
            // Double tap gesture
            TapGesture({ count: 2 })
              .onAction((event: GestureEvent) => {
                // Double tap is not allowed when any gesture or animation is in progress
                if (previewState.isAnimating || previewState.isPinching || previewState.isDragging ||
                previewState.isPinchRebounding || previewState.isPanRebounding || previewState.isPageTransitioning) {
                  return;
                }

                previewState.isAnimating = true;

                // Get double tap position as scale focus
                let tapX = previewState.containerWidth / 2;
                let tapY = previewState.containerHeight / 2;

                if (event.fingerList && event.fingerList.length > 0) {
                  const finger = event.fingerList[0];
                  tapX = finger.localX;
                  tapY = finger.localY;
                }

                if (previewState.scale <= 1.0) {
                  // Zoom from 100% to 200%
                  const targetScale = 2.0;
                  const scaleRatio = targetScale / previewState.scale;
                  // Offset of double tap point relative to image center
                  const centerX = tapX - previewState.containerWidth / 2 - previewState.offsetX;
                  const centerY = tapY - previewState.containerHeight / 2 - previewState.offsetY;
                  let targetOffsetX = previewState.offsetX + centerX * (1 - scaleRatio);
                  let targetOffsetY = previewState.offsetY + centerY * (1 - scaleRatio);

                  // Calculate image display size at target scale
                  const imageDisplayWidth = viewModel.baseImageWidth * targetScale;
                  const imageDisplayHeight = viewModel.baseImageHeight * targetScale;
                  const screenWidth = previewState.containerWidth;
                  const screenHeight = previewState.containerHeight;

                  // Adjust target offset based on image and screen size relationship
                  // X direction: if image width <= screen width, force center; otherwise clamp to valid range
                  if (imageDisplayWidth <= screenWidth) {
                    targetOffsetX = 0;
                  } else {
                    const minX = (screenWidth - imageDisplayWidth) / 2;
                    const maxX = (imageDisplayWidth - screenWidth) / 2;
                    if (targetOffsetX < minX) {
                      targetOffsetX = minX;
                    } else if (targetOffsetX > maxX) {
                      targetOffsetX = maxX;
                    }
                  }

                  // Y direction: if image height <= screen height, force center; otherwise clamp to valid range
                  if (imageDisplayHeight <= screenHeight) {
                    targetOffsetY = 0;
                  } else {
                    const minY = (screenHeight - imageDisplayHeight) / 2;
                    const maxY = (imageDisplayHeight - screenHeight) / 2;
                    if (targetOffsetY < minY) {
                      targetOffsetY = minY;
                    } else if (targetOffsetY > maxY) {
                      targetOffsetY = maxY;
                    }
                  }

                  runAnimation(uiContext, 250, curves.springMotion(0.6, 0.8), () => {
                    previewState.scale = targetScale;
                    previewState.offsetX = targetOffsetX;
                    previewState.offsetY = targetOffsetY;
                  }, () => { previewState.isAnimating = false; });
                } else {
                  // Zoom from >100% to 100%
                  const targetScale = 1.0;
                  const targetOffsetX = 0;
                  const targetOffsetY = 0;

                  runAnimation(uiContext, 250, curves.springMotion(0.6, 0.8), () => {
                    previewState.scale = targetScale;
                    previewState.offsetX = targetOffsetX;
                    previewState.offsetY = targetOffsetY;
                  }, () => { previewState.isAnimating = false; });
                }
              })
            , GestureMask.Normal)
      }
      .width('100%')
      .height('100%')
      .onClick(() => {
        previewState.showTitleBar = !previewState.showTitleBar;
      })
      .onAreaChange((oldValue: Area, newValue: Area) => {
        const newWidth = newValue.width as number;
        const newHeight = newValue.height as number;
        previewState.setContainerSize(newWidth, newHeight);
        viewModel.setContainerSize(newWidth, newHeight);
      })
    }
    .width('100%')
    .height('100%')
    .alignContent(Alignment.Center)
    .opacity(previewState.pageTransitionProgress)
  }
  .systemTransition(1)
  .onShown(() => {
    const params = param as PageParams;
    viewModel.setSelectedIndex(params.index);
    // Reset state
    previewState.scale = 1.0;
    previewState.offsetX = 0;
    previewState.offsetY = 0;
    previewState.showTitleBar = true;
    previewState.isAnimating = false;
    previewState.isPinching = false;
    previewState.isDragging = false;
    previewState.isPinchRebounding = false;
    previewState.isPanRebounding = false;
    // Page enter animation
    previewState.pageTransitionProgress = 0;
    previewState.isPageTransitioning = true;
    uiContext.animateTo({ duration: 600, curve: curves.springMotion(0.6, 0.8), onFinish: () => {
      previewState.isPageTransitioning = false;
    } }, () => {
      previewState.pageTransitionProgress = 1;
    });
  })
  .onWillDisappear(() => {
    // Page exit animation - as backup, actually handled by back button
    // Just need to reset state
    previewState.pageTransitionProgress = 0;
  })
}
