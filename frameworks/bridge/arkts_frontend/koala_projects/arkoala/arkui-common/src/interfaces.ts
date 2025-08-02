/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { __memo_transformed, __memo_transformed_before, __memo_transformed_after } from "@koalaui/runtime"

type Development = __memo_transformed_before
type Production = __memo_transformed_after
type Current = __memo_transformed

export type ArkCommonShapeMethod<T> = Current extends Development ? CommonShapeMethod<T> : Object
export type ArkCustomComponent = Current extends Development ? CustomComponent  : Object

export type ArkBadgeAttribute = Current extends Development ? BadgeAttribute : Object
export type ArkBlankAttribute = Current extends Development ? BlankAttribute : Object
export type ArkButtonAttribute = Current extends Development ? ButtonAttribute : Object
export type ArkCanvasAttribute = Current extends Development ? CanvasAttribute : Object
export type ArkCheckboxAttribute = Current extends Development ? CheckboxAttribute : Object
export type ArkCheckboxGroupAttribute = Current extends Development ? CheckboxGroupAttribute : Object
export type ArkCircleAttribute = Current extends Development ? CircleAttribute : Object
export type ArkColumnAttribute = Current extends Development ? ColumnAttribute : Object
export type ArkColumnSplitAttribute = Current extends Development ? ColumnSplitAttribute : Object
export type ArkCounterAttribute = Current extends Development ? CounterAttribute : Object
export type ArkDatePickerAttribute = Current extends Development ? DatePickerAttribute : Object
export type ArkDividerAttribute = Current extends Development ? DividerAttribute : Object
export type ArkEllipseAttribute = Current extends Development ? EllipseAttribute : Object
export type ArkFlexAttribute = Current extends Development ? FlexAttribute : Object
export type ArkFlowItemAttribute = Current extends Development ? FlowItemAttribute : Object
export type ArkFormLinkAttribute = Current extends Development ? FormLinkAttribute : Object
export type ArkGaugeAttribute = Current extends Development ? GaugeAttribute : Object
export type ArkGridAttribute = Current extends Development ? GridAttribute : Object
export type ArkGridColAttribute = Current extends Development ? GridColAttribute : Object
export type ArkGridItemAttribute = Current extends Development ? GridItemAttribute : Object
export type ArkGridRowAttribute = Current extends Development ? GridRowAttribute : Object
export type ArkHyperlinkAttribute = Current extends Development ? HyperlinkAttribute : Object
export type ArkImageAttribute = Current extends Development ? ImageAttribute : Object
export type ArkMediaCachedImageAttribute = Current extends Development ? MediaCachedImageAttribute : Object
export type ArkImageAnimatorAttribute = Current extends Development ? ImageAnimatorAttribute : Object
export type ArkImageSpanAttribute = Current extends Development ? ImageSpanAttribute : Object
export type ArkLazyColumnAttribute = Current extends Development ? ColumnAttribute : Object
export type ArkLazyGridAttribute = Current extends Development ? GridAttribute : Object
export type ArkLazyListAttribute = Current extends Development ? ListAttribute : Object
export type ArkLazyRowAttribute = Current extends Development ? RowAttribute : Object
export type ArkLineAttribute = Current extends Development ? LineAttribute : Object
export type ArkListAttribute = Current extends Development ? ListAttribute : Object
export type ArkListItemAttribute = Current extends Development ? ListItemAttribute : Object
export type ArkListItemGroupAttribute = Current extends Development ? ListItemGroupAttribute : Object
export type ArkLoadingProgressAttribute = Current extends Development ? LoadingProgressAttribute : Object
export type ArkMarqueeAttribute = Current extends Development ? MarqueeAttribute : Object
export type ArkMenuAttribute = Current extends Development ? MenuAttribute : Object
export type ArkMenuItemAttribute = Current extends Development ? MenuItemAttribute : Object
export type ArkMenuItemGroupAttribute = Current extends Development ? MenuItemGroupAttribute : Object
export type ArkNavDestinationAttribute = Current extends Development ? NavDestinationAttribute : Object
export type ArkNavigationAttribute = Current extends Development ? NavigationAttribute : Object
export type ArkNavigatorAttribute = Current extends Development ? NavigatorAttribute : Object
export type ArkNavRouterAttribute = Current extends Development ? NavRouterAttribute : Object
//export type ArkPageTransitionEnterAttribute = Current extends Development ? PageTransitionEnterAttribute : Object
//export type ArkPageTransitionExitAttribute = Current extends Development ? PageTransitionExitAttribute : Object
export type ArkPanelAttribute = Current extends Development ? PanelAttribute : Object
export type ArkPathAttribute = Current extends Development ? PathAttribute : Object
export type ArkPolylineAttribute = Current extends Development ? PolylineAttribute : Object
export type ArkPolygonAttribute = Current extends Development ? PolygonAttribute : Object
export type ArkProgressAttribute = Current extends Development ? ProgressAttribute : Object
export type ArkQRCodeAttribute = Current extends Development ? QRCodeAttribute : Object
export type ArkRadioAttribute = Current extends Development ? RadioAttribute : Object
export type ArkRatingAttribute = Current extends Development ? RatingAttribute : Object
export type ArkRectAttribute = Current extends Development ? RectAttribute : Object
export type ArkRefreshAttribute = Current extends Development ? RefreshAttribute : Object
export type ArkRowAttribute = Current extends Development ? RowAttribute : Object
export type ArkRowSplitAttribute = Current extends Development ? RowSplitAttribute : Object
export type ArkScrollAttribute = Current extends Development ? ScrollAttribute : Object
export type ArkScrollBarAttribute = Current extends Development ? ScrollBarAttribute : Object
export type ArkSearchAttribute = Current extends Development ? SearchAttribute : Object
export type ArkSelectAttribute = Current extends Development ? SelectAttribute : Object
export type ArkShapeAttribute = Current extends Development ? ShapeAttribute : Object
export type ArkSliderAttribute = Current extends Development ? SliderAttribute : Object
export type ArkSpanAttribute = Current extends Development ? SpanAttribute : Object
export type ArkStackAttribute = Current extends Development ? StackAttribute : Object
export type ArkStepperAttribute = Current extends Development ? StepperAttribute : Object
export type ArkStepperItemAttribute = Current extends Development ? StepperItemAttribute : Object
export type ArkSwiperAttribute = Current extends Development ? SwiperAttribute : Object
export type ArkTabContentAttribute = Current extends Development ? TabContentAttribute : Object
export type ArkTabsAttribute = Current extends Development ? TabsAttribute : Object
export type ArkTextAreaAttribute = Current extends Development ? TextAreaAttribute : Object
export type ArkTextAttribute = Current extends Development ? TextAttribute : Object
export type ArkTextClockAttribute = Current extends Development ? TextClockAttribute : Object
export type ArkTextInputAttribute = Current extends Development ? TextInputAttribute : Object
export type ArkTextPickerAttribute = Current extends Development ? TextPickerAttribute : Object
export type ArkTextTimerAttribute = Current extends Development ? TextTimerAttribute : Object
export type ArkTimePickerAttribute = Current extends Development ? TimePickerAttribute : Object
export type ArkToggleAttribute = Current extends Development ? ToggleAttribute : Object
export type ArkVideoAttribute = Current extends Development ? VideoAttribute : Object
export type ArkWaterFlowAttribute = Current extends Development ? WaterFlowAttribute : Object
export type ArkWebAttribute = Current extends Development ? WebAttribute : Object
export type ArkAlphabetIndexerAttribute = Current extends Development ? AlphabetIndexerAttribute : Object
export type ArkPatternLockAttribute = Current extends Development ? PatternLockAttribute : Object
export type ArkRichEditorAttribute = Current extends Development ? RichEditorAttribute : Object
export type ArkDataPanelAttribute = Current extends Development ? DataPanelAttribute : Object
export type ArkSideBarContainerAttribute = Current extends Development ? SideBarContainerAttribute : Object
export type ArkXComponentAttribute = Current extends Development ? XComponentAttribute : Object
export type ArkRelativeContainerAttribute = Current extends Development ? RelativeContainerAttribute : Object
export type ArkEffectComponentAttribute = Object // TODO: not available in API11