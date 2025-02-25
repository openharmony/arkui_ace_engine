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

 #include <gmock/gmock.h>

 #include "accessor_test_base.h"
 #include "core/interfaces/native/implementation/path_shape_peer.h"
 #include "core/interfaces/native/utility/reverse_converter.h"
 #include "core/interfaces/native/utility/converter.h"
 
 namespace OHOS::Ace::NG {
 
 using namespace testing;
 using namespace testing::ext;
 
 namespace {
//  std::vector<double> NUMBER_TEST_PLAN = {
//      100, 10.25, 2.35, 5.42, 12.34, 56.73
//  };
 
//  class MockCanvasPath : public CanvasPath2D {
//  public:
//      MockCanvasPath() = default;
//      ~MockCanvasPath() override = default;
//      MOCK_METHOD(void, AddPath, (const RefPtr<CanvasPath2D>&));
//      MOCK_METHOD(void, SetTransform, (double, double, double, double, double, double));
//  };
 } // namespace
 
 class PathShapeAccessorTest
     : public AccessorTestBase<GENERATED_ArkUIPathShapeAccessor,
         &GENERATED_ArkUIAccessors::getPathShapeAccessor, PathShapePeer> {
 public:
     void SetUp(void) override
     {
         AccessorTestBase::SetUp();
        //  mockPath_ = new MockCanvasPath();
        //  mockPathKeeper_ = AceType::Claim(mockPath_);
        //  ASSERT_NE(mockPathKeeper_, nullptr);
        //  peer_->path = mockPathKeeper_;
        //  ASSERT_NE(mockPath_, nullptr);
     }
 
     void TearDown() override
     {
         AccessorTestBaseParent::TearDown();
         mockPathKeeper_ = nullptr;
         mockPath_ = nullptr;
     }
     MockCanvasPath* mockPath_ = nullptr;
     RefPtr<MockCanvasPath> mockPathKeeper_ = nullptr;
 };
 
 /**
  * @tc.name: addPathTest
  * @tc.desc:
  * @tc.type: FUNC
  */
 HWTEST_F(PathShapeAccessorTest, addPathTest, TestSize.Level1)
 {
     ASSERT_NE(accessor_->addPath, nullptr);
     auto peerPathImpl = Referenced::MakeRefPtr<PathShapePeer>();
     auto arkPath = Referenced::RawPtr(peerPathImpl);
     peerPathImpl->path = AceType::MakeRefPtr<MockCanvasPath>();
     auto peerMatrix = new Matrix2DPeer();
     auto optMatrix = Converter::ArkValue<Opt_Matrix2D>(peerMatrix);
     peerMatrix->transform.scaleX = NUMBER_TEST_PLAN[0];
     peerMatrix->transform.scaleY = NUMBER_TEST_PLAN[1];
     peerMatrix->transform.skewX = NUMBER_TEST_PLAN[2];
     peerMatrix->transform.skewY = NUMBER_TEST_PLAN[3];
     peerMatrix->transform.translateX = NUMBER_TEST_PLAN[4];
     peerMatrix->transform.translateY = NUMBER_TEST_PLAN[5];
     auto tr = peerMatrix->transform;
     EXPECT_CALL(*mockPath_, AddPath(peerPathImpl->path)).Times(3);
     EXPECT_CALL(*mockPath_, SetTransform(tr.scaleX, tr.skewX, tr.skewY, tr.scaleY, tr.translateX, tr.translateY))
         .Times(3);
     accessor_->addPath(peer_, arkPath, &optMatrix);
     accessor_->addPath(peer_, arkPath, &optMatrix);
     accessor_->addPath(peer_, arkPath, &optMatrix);
 }
 } // namespace OHOS::Ace::NG