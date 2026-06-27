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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_QUATERNION_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_QUATERNION_H

namespace OHOS::Ace {

class Quaternion {
public:
    Quaternion() = default;
    Quaternion(double x, double y, double z, double w) : x_(x), y_(y), z_(z), w_(w) {}
    ~Quaternion() = default;

    double GetX() const
    {
        return x_;
    }
    double GetY() const
    {
        return y_;
    }
    double GetZ() const
    {
        return z_;
    }
    double GetW() const
    {
        return w_;
    }
    void SetX(double x)
    {
        x_ = x;
    }
    void SetY(double y)
    {
        y_ = y;
    }
    void SetZ(double z)
    {
        z_ = z;
    }
    void SetW(double w)
    {
        w_ = w;
    }

    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    bool operator==(const Quaternion& q) const;
    bool operator!=(const Quaternion& q) const;
    Quaternion inverse() const;
    Quaternion flip() const;

    // Blends with the given quaternion via spherical linear interpolation.
    // Values of t in the range [0, 1] interpolate between this and q.
    Quaternion Slerp(const Quaternion& q, double t) const;

private:
    double x_ = 0.0;
    double y_ = 0.0;
    double z_ = 0.0;
    double w_ = 0.0;
};

// Scalar multiplication with quaternion.
Quaternion operator*(const Quaternion& q, double s);
Quaternion operator*(double s, const Quaternion& q);

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_QUATERNION_H
