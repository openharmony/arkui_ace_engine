/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { AnimateParam } from '../component'

export * from "./ArkStateStyle"
export * from "./ArkDragDrop"
export * from "./DatePickerOpsHandWritten"
export * from "./Router"
export * from "./ForeignFunctions"
export * from "./GridItemOpsHandWritten"
export * from "./SearchOpsHandWritten"
export * from "./TextFieldOpsHandWritten"
export * from "./CommonHandWritten"
export * from "./NavDestinationHandWritten"
export * from "./NavDestinationHandWrittenImpl"
export * from "./NavigationHandWritten"
export * from "./NavigationHandWrittenImpl"
export * from "./NavigationOpsHandWritten"
export * from "./SideBarContainerHandWritten"
export * from "./SideBarContainerHandWrittenImpl"
export * from "./SideBarContainerOpsHandWritten"
export * from "./StepperHandWritten"
export * from "./StepperHandWrittenImpl"
export * from "./StepperOpsHandWritten"
export * from "./StepperItemHandWritten"
export * from "./CheckboxGroupOpsHandWritten"
export * from "./CheckboxOpsHandWritten"
export * from "./MenuItemOpsHandWritten"
export * from "./RadioOpsHandWritten"
export * from "./RatingOpsHandWritten"
export * from "./SelectOpsHandWritten"
export * from "./SliderOpsHandWritten"
export * from "./ToggleOpsHandWritten"
export * from "./TabsOpsHandWritten"
export * from "./BindSheetHandWritten"
export * from "./ListImpl"
export * from "./TimePickerOpsHandWritten"
export * from "./ListItemOpsHandWritten"
export * from "./AlphabetIndexerOpsHandWritten"
export * from "./SwiperOpsHandWritten"
export * from "./RefreshOpsHandWritten"
export * from "./AttributeModifierOpsHandWritten"
export * from  "./ContentModifierHooks"
export * from "./utils/SerializeUtils"

// export interface PageTransitionExitInterface { }
// export interface CommonTransition { }
// export interface NavigationAttribute { }
// export interface SubscribaleAbstract { }
// export interface ISinglePropertyChangeSubscriber { }
// export interface IPropertySubscriber { }
// export interface AbstractProperty { }
// export interface BaseCustomComponent { }
// export interface CustomComponent { }
// export interface CustomComponentV2 { }
export interface UICommonBase {}
// export interface PageTransitionEnterInterface { }
// export interface SystemBarStyle { }

export function _animateTo(param: AnimateParam, event: (() => void)): void { }
export function _animationStart(param: AnimateParam, isFirstBuild: boolean) { }
export function _animationEnd(isFirstBuild: boolean, update: (() => void)): void { }