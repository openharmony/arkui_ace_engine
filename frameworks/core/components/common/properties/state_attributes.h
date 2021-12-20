/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_STATE_ATTRUBUTES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_STATE_ATTRUBUTES_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace {

enum class StyleState {
    NOTSET = 0,
    NORMAL,
    PRESSED,
    DISABLED
};

// Classes below (StateAttributeList) owned by Components
// and passed to RenderNodes for execution

template<class AttributeID>
class StateAttributeBase : public virtual AceType {
    DECLARE_ACE_TYPE(StateAttributeBase<AttributeID>, AceType);
public:
    StateAttributeBase(StyleState state, AttributeID id) : stateName_(state), id_(id) {}
    virtual ~StateAttributeBase() {}
    StyleState stateName_;
    AttributeID id_;
};

template<class AttributeID, class Attribute>
class StateAttributeValue : public StateAttributeBase<AttributeID> {
    DECLARE_ACE_TYPE(StateAttributeValue, StateAttributeBase<AttributeID>);
public:
    StateAttributeValue(StyleState state, AttributeID id, Attribute value)
        : StateAttributeBase<AttributeID>(state, id), value_(value)
    {}
    virtual ~StateAttributeValue() {}
    Attribute value_;
};

template<class AttributeID>
class StateAttributeList : public Referenced, public std::list<RefPtr<StateAttributeBase<AttributeID>>> {};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_STATE_ATTRUBUTES_H
