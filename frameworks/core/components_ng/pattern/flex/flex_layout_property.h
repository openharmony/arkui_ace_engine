//
// Created by 陆泽辉 on 2022/8/8.
//

#ifndef ARKUI_ACE_ENGINE_FLEX_LAYOUT_PROPERTY_H
#define ARKUI_ACE_ENGINE_FLEX_LAYOUT_PROPERTY_H

#include "base/utils/macros.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/flex/flex_layout_styles.h"
#include "core/components_ng/property/property.h"


namespace OHOS::Ace::NG {
class ACE_EXPORT FlexLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(FlexLayoutProperty, LayoutProperty);

public:
    explicit FlexLayoutProperty() = default;

    ~FlexLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override {
        auto value = MakeRefPtr<FlexLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propFlexLayoutAttribute_ = CloneFlexLayoutAttribute();
        return value;
    }

    void Reset() override {
        LayoutProperty::Reset();
        ResetFlexLayoutAttribute();
    }

    ACE_DEFINE_PROPERTY_GROUP(FlexLayoutAttribute, FlexLayoutAttribute);

    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, FlexDirection, FlexDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, MainAxisAlign, FlexAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, CrossAxisAlign, FlexAlign, PROPERTY_UPDATE_MEASURE);

//    FlexDirection GetFlexDirection() const {
//        if (!propFlexLayoutAttribute_) {
//            return FlexDirection::ROW;
//        }
//        return propFlexLayoutAttribute_->GetFlexDirection().value_or(FlexDirection::ROW);
//    }

//    FlexAlign GetMainAxisAlign() const {
//        if (!propFlexLayoutAttribute_) {
//            return FlexAlign::FLEX_START;
//        }
//        return propFlexLayoutAttribute_->GetMainAxisAlign().value_or(FlexAlign::FLEX_START);
//    }

//    FlexAlign GetCrossAxisAlign() const {
//        if (!propFlexLayoutAttribute_) {
//            return FlexAlign::FLEX_START;
//        }
//        return propFlexLayoutAttribute_->GetCrossAxisAlign().value_or(FlexAlign::FLEX_START);
//    }
private:
    ACE_DISALLOW_COPY_AND_MOVE(FlexLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // ARKUI_ACE_ENGINE_FLEX_LAYOUT_PROPERTY_H
