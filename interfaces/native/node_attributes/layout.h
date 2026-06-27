/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides the layout-related types for the native module.
 *
 * @since 12
 */

/**
 * @file layout.h
 *
 * @brief Defines the layout-related types for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_LAYOUT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_LAYOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief specifies the alignment rules for subcomponents set in relative containers.
  *
  * @since 12
  */
typedef struct ArkUI_AlignmentRuleOption ArkUI_AlignmentRuleOption;

/**
  * @brief guideLine parameters, used to define the id, direction and position of the guideline.
  *
  * @since 12
  */
typedef struct ArkUI_GuidelineOption ArkUI_GuidelineOption;

/**
  * @brief barrier parameter, used to define the id,
  * direction and components of the barrier that it depends on when generating it.
  *
  * @since 12
  */
typedef struct ArkUI_BarrierOption ArkUI_BarrierOption;

/**
 * @brief Defines the PixelRound policy of a component's four edges.
 *
 * @since 21
 */
typedef struct ArkUI_PixelRoundPolicy ArkUI_PixelRoundPolicy;

/**
 * @brief Enumerates the alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** Top start. */
    ARKUI_ALIGNMENT_TOP_START = 0,
    /** Top center. */
    ARKUI_ALIGNMENT_TOP,
    /** Top end. */
    ARKUI_ALIGNMENT_TOP_END,
    /** Vertically centered start. */
    ARKUI_ALIGNMENT_START,
    /** Horizontally and vertically centered. */
    ARKUI_ALIGNMENT_CENTER,
    /** Vertically centered end. */
    ARKUI_ALIGNMENT_END,
    /** Bottom start. */
    ARKUI_ALIGNMENT_BOTTOM_START,
    /** Horizontally centered on the bottom. */
    ARKUI_ALIGNMENT_BOTTOM,
    /** Bottom end. */
    ARKUI_ALIGNMENT_BOTTOM_END,
} ArkUI_Alignment;

/**
 * @brief Enumerates the modes in which components are laid out along the cross axis of the container.
 *
 * @since 12
 */
typedef enum {
    /** The default configuration in the container is used. */
    ARKUI_ITEM_ALIGNMENT_AUTO = 0,
    /** The items in the container are aligned with the cross-start edge. */
    ARKUI_ITEM_ALIGNMENT_START,
    /** The items in the container are centered along the cross axis. */
    ARKUI_ITEM_ALIGNMENT_CENTER,
    /** The items in the container are aligned with the cross-end edge. */
    ARKUI_ITEM_ALIGNMENT_END,
    /** The items in the container are stretched and padded along the cross axis. */
    ARKUI_ITEM_ALIGNMENT_STRETCH,
    /** The items in the container are aligned in such a manner that their text baselines are aligned along the
     *  cross axis. */
    ARKUI_ITEM_ALIGNMENT_BASELINE,
} ArkUI_ItemAlignment;

/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** The child components are aligned with the start edge of the main axis. */
    ARKUI_FLEX_ALIGNMENT_START = 1,
    /** The child components are aligned in the center of the main axis. */
    ARKUI_FLEX_ALIGNMENT_CENTER = 2,
    /** The child components are aligned with the end edge of the main axis. */
    ARKUI_FLEX_ALIGNMENT_END = 3,
    /** The child components are evenly distributed along the main axis. The space between any two adjacent components
     *  is the same. The first component is aligned with the main-start, and the last component is aligned with
     *  the main-end. */
    ARKUI_FLEX_ALIGNMENT_SPACE_BETWEEN = 6,
    /** The child components are evenly distributed along the main axis. The space between any two adjacent components
     *  is the same. The space between the first component and main-start, and that between the last component and
     *  cross-main are both half the size of the space between two adjacent components. */
    ARKUI_FLEX_ALIGNMENT_SPACE_AROUND = 7,
    /** The child components are evenly distributed along the main axis. The space between the first component
     *  and main-start, the space between the last component and main-end, and the space between any two adjacent
     *  components are the same. */
    ARKUI_FLEX_ALIGNMENT_SPACE_EVENLY = 8,
} ArkUI_FlexAlignment;

/**
 * @brief Enumerates the directions of the main axis in the flex container.
 *
 * @since 12
 */
typedef enum {
    /** The child components are arranged in the same direction as the main axis runs along the rows. */
    ARKUI_FLEX_DIRECTION_ROW = 0,
    /** The child components are arranged in the same direction as the main axis runs down the columns. */
    ARKUI_FLEX_DIRECTION_COLUMN,
    /** The child components are arranged opposite to the <b>ROW</b> direction. */
    ARKUI_FLEX_DIRECTION_ROW_REVERSE,
    /** The child components are arranged opposite to the <b>COLUMN</b> direction. */
    ARKUI_FLEX_DIRECTION_COLUMN_REVERSE,
} ArkUI_FlexDirection;

/**
 * @brief Defines whether the flex container has a single line or multiple lines.
 *
 * @since 12
 */
typedef enum {
    /** The child components in the flex container are arranged in a single line, and they cannot overflow. */
    ARKUI_FLEX_WRAP_NO_WRAP = 0,
    /** The child components in the flex container are arranged in multiple lines, and they may overflow. */
    ARKUI_FLEX_WRAP_WRAP,
    /** The child components in the flex container are reversely arranged in multiple lines, and they may overflow. */
    ARKUI_FLEX_WRAP_WRAP_REVERSE,
} ArkUI_FlexWrap;


/**
 * @brief Enumerates the modes in which components are laid out along the main axis of the container.
 *
 * @since 12
 */
typedef enum {
    /** Components are arranged from left to right. */
    ARKUI_DIRECTION_LTR = 0,
    /** Components are arranged from right to left. */
    ARKUI_DIRECTION_RTL,
    /** The default layout direction is used. */
    ARKUI_DIRECTION_AUTO = 3,
} ArkUI_Direction;

/**
 * @brief Enumerates the scroll directions for the <b><List></b> component.
 *
 * @since 12
 */
typedef enum {
    /** Only vertical scrolling is supported. */
    ARKUI_AXIS_VERTICAL = 0,
    /** Only horizontal scrolling is supported. */
    ARKUI_AXIS_HORIZONTAL,
} ArkUI_Axis;

/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** Top aligned. */
    ARKUI_VERTICAL_ALIGNMENT_TOP = 0,
    /** Center aligned. This is the default alignment mode. */
    ARKUI_VERTICAL_ALIGNMENT_CENTER,
    /** Bottom aligned. */
    ARKUI_VERTICAL_ALIGNMENT_BOTTOM,
} ArkUI_VerticalAlignment;

/**
 * @brief Enumerates the alignment mode in the horizontal direction.
 *
 * @since 12
 */
typedef enum {
    /** Aligned with the start edge in the same direction as the language in use. */
    ARKUI_HORIZONTAL_ALIGNMENT_START = 0,
    /** Center aligned. This is the default alignment mode. */
    ARKUI_HORIZONTAL_ALIGNMENT_CENTER,
    /** Aligned with the end edge in the same direction as the language in use. */
    ARKUI_HORIZONTAL_ALIGNMENT_END,
} ArkUI_HorizontalAlignment;

/**
  * @brief defines the direction of the barrier line.
  *
  * @since 12
  */
typedef enum {
    /** The barrier is the leftmost of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_START = 0,
    /** The barrier is on the rightmost side of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_END,
    /** The barrier is at the top of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_TOP,
    /** The barrier is at the bottom of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_BOTTOM
} ArkUI_BarrierDirection;

/**
  * @brief defines the style of the chain.
  *
  * @since 12
  */
typedef enum {
    /** Components are evenly distributed among constraint anchor points. */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD = 0,
    /** Except for the first and last two sub-components,
      * other components are evenly distributed between the constraint anchor points. */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD_INSIDE,
    /** No gaps in subcomponents within the chain. */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_PACKED,
} ArkUI_RelativeLayoutChainStyle;

/**
 * @brief Create auxiliary line information in the RelativeContaine container.
 *
 * @param size The number of auxiliary lines.
 * @return auxiliary line information.
 * @since 12
 */
ArkUI_GuidelineOption* OH_ArkUI_GuidelineOption_Create(int32_t size);

/**
 * @brief Destroy auxiliary line information.
 *
 * @param guideline auxiliary line information.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_Dispose(ArkUI_GuidelineOption* guideline);

/**
 * @brief Set the Id of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param value id, must be unique and cannot have the same name as the component in the container.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetId(ArkUI_GuidelineOption* guideline, const char* value, int32_t index);

/**
 * @brief Set the direction of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param value direction.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetDirection(ArkUI_GuidelineOption* guideline, ArkUI_Axis value, int32_t index);

/**
 * @brief Set the distance from the left or top of the container.
 *
 * @param guideline auxiliary line information.
 * @param value The distance from the left or top of the container.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetPositionStart(ArkUI_GuidelineOption* guideline, float value, int32_t index);

/**
 * @brief Set the distance from the right or bottom of the container.
 *
 * @param guideline auxiliary line information.
 * @param value The distance from the right side or bottom of the container.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetPositionEnd(ArkUI_GuidelineOption* guideline, float value, int32_t index);

/**
 * @brief Get the Id of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return Id.
 * @since 12
 */
const char* OH_ArkUI_GuidelineOption_GetId(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief Get the direction of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return direction.
 * @since 12
 */
ArkUI_Axis OH_ArkUI_GuidelineOption_GetDirection(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief Get the distance from the left or top of the container.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return The distance from the left or top of the container.
 * @since 12
 */
float OH_ArkUI_GuidelineOption_GetPositionStart(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief Get the distance from the right side or bottom of the container.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return The distance from the right side or bottom of the container.
 * @since 12
 */
float OH_ArkUI_GuidelineOption_GetPositionEnd(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief creates barrier information within the RelativeContaine container.
 *
 * @param size Number of barriers.
 * @return barrier information.
 * @since 12
 */
ArkUI_BarrierOption* OH_ArkUI_BarrierOption_Create(int32_t size);

/**
 * @brief Destroy barrier information.
 *
 * @param barrierStyle barrier information.
 * @since 12
 */
void OH_ArkUI_BarrierOption_Dispose(ArkUI_BarrierOption* barrierStyle);

/**
 * @brief Set the Id of the barrier.
 *
 * @param barrierStyle barrier information.
 * @param value id, must be unique and cannot have the same name as the component in the container.
 * @param index Barrier index value.
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index);

/**
 * @brief Set the direction of the barrier.
 *
 * @param barrierStyle barrier information.
 * @param value direction.
 * @param index Barrier index value.
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetDirection(
    ArkUI_BarrierOption* barrierStyle, ArkUI_BarrierDirection value, int32_t index);

/**
 * @brief Sets the dependent component of the barrier.
 *
 * @param barrierStyle barrier information.
 * @param value The ID of the dependent component.
 * @param index Barrier index value.
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetReferencedId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index);

/**
 * @brief Get the Id of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @return The Id of the barrier.
 * @since 12
 */
const char* OH_ArkUI_BarrierOption_GetId(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief Gets the direction of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @return The direction of the barrier.
 * @since 12
 */
ArkUI_BarrierDirection OH_ArkUI_BarrierOption_GetDirection(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief Get the dependent components of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @param referencedIndex dependent component Id index value.
 * @return The barrier's dependent components.
 * @since 12
 */
const char* OH_ArkUI_BarrierOption_GetReferencedId(
    ArkUI_BarrierOption* barrierStyle, int32_t index, int32_t referencedIndex);

/**
 * @brief Gets the number of dependent components of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @return The number of dependent components of the barrier.
 * @since 12
 */
int32_t OH_ArkUI_BarrierOption_GetReferencedIdSize(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief creates alignment rule information for subcomponents in relative containers.
 *
 * @return Alignment rule information.
 * @since 12
 */
ArkUI_AlignmentRuleOption* OH_ArkUI_AlignmentRuleOption_Create();


/**
 * @brief Destroys the alignment rule information of subcomponents in relative containers.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_Dispose(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Set the start alignment parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to the anchor component.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetStart(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
 * @brief Set the end alignment parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to the anchor component.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetEnd(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
* @brief Set the parameters for horizontal center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @param id The id value of the anchor component.
* @param alignment Alignment relative to anchor component
* @since 12
*/
void OH_ArkUI_AlignmentRuleOption_SetCenterHorizontal(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
 * @brief Set the parameters for top alignment.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to anchor component
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetTop(ArkUI_AlignmentRuleOption* option, const char* id,
    ArkUI_VerticalAlignment alignment);

/**
 * @brief Set the bottom alignment parameters.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to anchor component
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBottom(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment);

/**
* @brief Set the parameters for vertical center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @param id The id value of the anchor component.
* @param alignment Alignment relative to the anchor component.
* @since 12
*/
void OH_ArkUI_AlignmentRuleOption_SetCenterVertical(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment);

/**
 * @brief Sets the horizontal offset parameter of the component under the anchor point constraint.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param horizontal bias value in the horizontal direction.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBiasHorizontal(ArkUI_AlignmentRuleOption* option, float horizontal);

/**
 * @brief Set the vertical offset parameter of the component under the anchor point constraint.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param vertical bias value in the vertical direction.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBiasVertical(ArkUI_AlignmentRuleOption* option, float vertical);

/**
 * @brief Get the Id of the start-aligned parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return The id value of the anchor component.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetStartId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the alignment of the start-aligned parameter.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the parameters.
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetStartAlignment(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the end alignment parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return End-aligned parameter id.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetEndId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Get the end alignment parameter.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the end-aligned parameter.
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetEndAlignment(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of horizontal center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The id of the parameter of horizontal center alignment.
* @since 12
*/
const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdHorizontal(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of horizontal center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the horizontally centered alignment parameter.
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentHorizontal(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the top-aligned parameters.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return Top aligned parameter id.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetTopId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Get the top-aligned parameters.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the top-aligned parameter.
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetTopAlignment(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the bottom alignment parameters.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return The id of the bottom-aligned parameter.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetBottomId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Get the bottom alignment parameters.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the bottom-aligned parameter.
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetBottomAlignment(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of vertical center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The id of the vertical center alignment parameter.
* @since 12
*/
const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdVertical(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of vertical center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the vertical center alignment parameter.
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentVertical(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the bias value in the horizontal direction.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return The bias value in the horizontal direction.
 * @since 12
 */
float OH_ArkUI_AlignmentRuleOption_GetBiasHorizontal(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the bias value in the vertical direction.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return bias value in vertical direction.
 * @since 12
*/
float OH_ArkUI_AlignmentRuleOption_GetBiasVertical(ArkUI_AlignmentRuleOption* option);

/**
 * @brief defines the enumerated value of the direction of the extended security zone.
 *
 * @since 12
 */
typedef enum {
    /** Upper area. */
    ARKUI_SAFE_AREA_EDGE_TOP = 1,
    /** Lower area. */
    ARKUI_SAFE_AREA_EDGE_BOTTOM = 1 << 1,
    /** Front area. */
    ARKUI_SAFE_AREA_EDGE_START = 1 << 2,
    /** Tail area. */
    ARKUI_SAFE_AREA_EDGE_END = 1 << 3,
} ArkUI_SafeAreaEdge;

/**
 * @brief Define the types for expanding the safe area in layout.
 *
 * @since 23
 */
typedef enum {
    /** Default non-safe area of the system, including the status bar and navigation bar. */
    ARKUI_LAYOUT_SAFE_AREA_TYPE_SYSTEM = 1,
} ArkUI_LayoutSafeAreaType;

/**
 * @brief Define the edges for expanding the safe area in layout.
 *
 * @since 23
 */
typedef enum {
    /** Top edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP = 1,
    /** Bottom edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM = 1 << 1,
    /** Start edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_START = 1 << 2,
    /** End edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_END = 1 << 3,
    /** Vertical edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_VERTICAL = ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP | ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM,
    /** Horizontal edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_HORIZONTAL = ARKUI_LAYOUT_SAFE_AREA_EDGE_START | ARKUI_LAYOUT_SAFE_AREA_EDGE_END,
    /** All edges of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_ALL = ARKUI_LAYOUT_SAFE_AREA_EDGE_VERTICAL | ARKUI_LAYOUT_SAFE_AREA_EDGE_HORIZONTAL,
} ArkUI_LayoutSafeAreaEdge;

/**
 * @brief Enumerates the localizedAlignment modes.
 *
 * @since 23
 */
typedef enum {
    /** Top start. */
    ARKUI_LOCALIZED_ALIGNMENT_TOP_START = 0,
    /** Top center. */
    ARKUI_LOCALIZED_ALIGNMENT_TOP,
    /** Top end. */
    ARKUI_LOCALIZED_ALIGNMENT_TOP_END,
    /** Vertically centered start. */
    ARKUI_LOCALIZED_ALIGNMENT_START,
    /** Horizontally and vertically centered. */
    ARKUI_LOCALIZED_ALIGNMENT_CENTER,
    /** Vertically centered end. */
    ARKUI_LOCALIZED_ALIGNMENT_END,
    /** Bottom start. */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM_START,
    /** Horizontally centered on the bottom. */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM,
    /** Bottom end. */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM_END,
} ArkUI_LocalizedAlignment;

/**
 * @brief Enumerates the LayoutPolicy.
 *
 * @since 21
 */
typedef enum {
    /** The component fills its parent, which means its size is as large as its parent */
    ARKUI_LAYOUTPOLICY_MATCHPARENT = 0,
    /** The component fills its content, which means its size is as large as its children but it is constrained
        by its parent. */
    ARKUI_LAYOUTPOLICY_WRAPCONTENT,
    /** The component fills its content which means its size is as large as its children. */
    ARKUI_LAYOUTPOLICY_FIXATIDEALSIZE,
} ArkUI_LayoutPolicy;


/**
 * @brief Enumerates the PixelRoundPolicy.
 *
 * @since 21
 */
typedef enum {
    /** No Force round the component boundary coordinates to integer pixel. */
    ARKUI_PIXELROUNDCALCPOLICY_NOFORCEROUND = 0,
    /** Force ceil the component boundary coordinates to integer pixel. */
    ARKUI_PIXELROUNDCALCPOLICY_FORCECEIL,
    /** Force floor the component boundary coordinates to integer pixel. */
    ARKUI_PIXELROUNDCALCPOLICY_FORCEFLOOR,
} ArkUI_PixelRoundCalcPolicy;

/**
 * @brief Define the Edges describing the position of a component by distances to the container's four edges.
 *
 * @since 21
 */
typedef struct ArkUI_PositionEdges ArkUI_PositionEdges;

/**
 * @brief Create an edge object for position attribute.
 *
 * @return A pointer to the edge object.
 * @since 21
 */
ArkUI_PositionEdges* OH_ArkUI_PositionEdges_Create();

/**
 * @brief Creates a deep copy of an edge object for position attribute.
 *
 * @param edges A pointer to an edge object.
 * @return A pointer to the new edge object.
 * @since 21
 */
ArkUI_PositionEdges* OH_ArkUI_PositionEdges_Copy(const ArkUI_PositionEdges* edges);

/**
 * @brief Dispose an edge object for position attribute.
 *
 * @param edges Pointer to the edge object to be disposed.
 * @since 21
 */
void OH_ArkUI_PositionEdges_Dispose(ArkUI_PositionEdges* edges);

/**
 * @brief Sets the top edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of top edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetTop(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the top edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of top edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetTop(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Sets the left edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of left edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetLeft(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the left edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of left edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetLeft(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Sets the bottom edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of bottom edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetBottom(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the bottom edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of bottom edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetBottom(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Sets the right edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of right edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetRight(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the right edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of right edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetRight(ArkUI_PositionEdges* edges, float* value);



/**
 * @brief Create a policy object for PixelRound attribute.
 *
 * @return A pointer to the policy object.
 * @since 21
 */
ArkUI_PixelRoundPolicy* OH_ArkUI_PixelRoundPolicy_Create();

/**
 * @brief Dispose a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object to be disposed.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_Dispose(ArkUI_PixelRoundPolicy* policy);

/**
 * @brief Sets the top edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of top edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetTop(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the top edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of top edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetTop(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Sets the start edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of start edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetStart(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the start edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of start edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetStart(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Sets the bottom edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of bottom edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetBottom(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the bottom edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of bottom edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetBottom(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Sets the end edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of end edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetEnd(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the end edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of end edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetEnd(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LAYOUT_H
/** @} */
